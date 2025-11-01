.PHONY: help build deploy actions-status clean serve docs-url rust-build rust-flash rust-monitor rust-check

help: ## Show this help message
	@echo 'Usage: make [target]'
	@echo ''
	@echo 'Available targets:'
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-20s\033[0m %s\n", $$1, $$2}'

build: ## Build the MkDocs site
	.venv/bin/python -m mkdocs build --clean

serve: ## Serve the MkDocs site locally
	.venv/bin/python -m mkdocs serve

deploy: build ## Build and push to GitHub Pages
	git add docs/
	git commit -m "Update GitHub Pages site" || echo "No changes to commit"
	git push

docs-url: ## Print documentation site URL
	@URL=$$(awk '/^site_url:/ {sub(/^site_url:[[:space:]]*/, "", $$0); print $$0; exit}' mkdocs.yml | tr -d '"' | tr -d "'" ); \
	if [ -n "$$URL" ]; then \
		printf "%s\n" "$$URL"; \
	else \
		REMOTE=$$(git remote get-url origin 2>/dev/null || echo ""); \
		if [ -n "$$REMOTE" ]; then \
			OWNER_REPO=$$(printf "%s" "$$REMOTE" | sed -E 's#.*github.com[:/ ]([^/]+)/([^/.]+)(\\.git)?$#\1/\2#'); \
			OWNER=$$(printf "%s" "$$OWNER_REPO" | cut -d/ -f1); \
			REPO=$$(printf "%s" "$$OWNER_REPO" | cut -d/ -f2); \
			if [ -n "$$OWNER" ] && [ -n "$$REPO" ]; then \
				printf "https://%s.github.io/%s/\n" "$$OWNER" "$$REPO"; \
			else \
				echo "Could not determine repository owner/name."; \
				exit 1; \
			fi; \
		else \
			echo "No git remote found and site_url not set in mkdocs.yml"; \
			exit 1; \
		fi; \
	fi

actions-status: ## Check GitHub Actions status
	@if ! command -v gh >/dev/null 2>&1; then \
		echo "❌ Error: GitHub CLI (gh) is not installed."; \
		echo ""; \
		echo "To install on macOS:"; \
		echo "  brew install gh"; \
		echo ""; \
		echo "Then authenticate with:"; \
		echo "  gh auth login"; \
		exit 1; \
	fi
	@if ! gh auth status >/dev/null 2>&1; then \
		echo "❌ Error: GitHub CLI is not authenticated."; \
		echo ""; \
		echo "Please run:"; \
		echo "  gh auth login"; \
		echo ""; \
		exit 1; \
	fi
	@echo "Checking GitHub Actions status for lanterno/office-wall-clock..."
	@echo ""
	@RUNS=$$(gh run list --limit 1 --json status 2>/dev/null || echo "[]"); \
	if [ "$$RUNS" = "[]" ] || [ -z "$$RUNS" ]; then \
		echo "ℹ️  No workflow runs found in this repository."; \
		echo ""; \
		echo "This could mean:"; \
		echo "  • No GitHub Actions workflows are configured yet"; \
		echo "  • Workflows exist but haven't been triggered"; \
		echo ""; \
		echo "To add workflows, create files in .github/workflows/"; \
		exit 0; \
	fi; \
	ACTIVE=$$(echo "$$RUNS" | jq '[.[] | select(.status == "in_progress" or .status == "queued")] | length' 2>/dev/null || echo "0"); \
	if [ "$$ACTIVE" -gt 0 ]; then \
		echo "⚡ Active workflow runs:"; \
		echo ""; \
		gh run list --limit 20 --json status,conclusion,name,databaseId,createdAt,displayTitle,workflowName | \
		jq -r '.[] | select(.status == "in_progress" or .status == "queued") | "  🔄 \(.workflowName // .name) - \(.displayTitle) - \(.status | ascii_upcase)"'; \
		echo ""; \
	else \
		echo "✅ No active workflow runs"; \
		echo ""; \
	fi; \
	echo "📊 Last run status for each workflow:"; \
	echo ""; \
	gh run list --limit 100 --json name,status,conclusion,createdAt,displayTitle,databaseId,workflowName | \
	jq -r 'group_by(.workflowName // .name) | map(sort_by(.createdAt) | reverse | .[0]) | sort_by(.workflowName // .name) | .[] | if .conclusion == "success" then "  ✅" elif .conclusion == "failure" then "  ❌" elif .conclusion == "cancelled" then "  ⊘" elif .status == "in_progress" then "  🔄" elif .status == "queued" then "  ⏳" else "  ○" end + " \(.workflowName // .name) - \(.conclusion // .status) (\(.createdAt | split("T")[0]))"'

clean: ## Clean build artifacts
	rm -rf docs/
	find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
	find . -type f -name "*.pyc" -delete 2>/dev/null || true

# -----------------
# Rust firmware (Modern esp-hal + Embassy)
# -----------------

RUST_DIR=firmware

rust-check: ## Check Rust toolchain and target are installed
	@echo "🦀 Checking Rust environment..."
	@command -v cargo >/dev/null 2>&1 || { echo "❌ cargo not found. Install Rust from https://rustup.rs"; exit 1; }
	@rustup target list | grep -q "riscv32imc-unknown-none-elf (installed)" || {\
	  echo "📦 Installing target riscv32imc-unknown-none-elf..."; \
	  rustup target add riscv32imc-unknown-none-elf; \
	}
	@command -v espflash >/dev/null 2>&1 || { echo "📦 Installing espflash..."; cargo install espflash --locked; }
	@echo "✅ Rust environment OK (stable + esp-hal)"

rust-build: rust-check ## Build Rust firmware with esp-hal (release)
	@echo "🔨 Building firmware (release, esp-hal + Embassy)..."
	cd $(RUST_DIR) && cargo build --release

rust-build-dev: rust-check ## Build Rust firmware (debug, faster compilation)
	@echo "🔨 Building firmware (debug mode)..."
	cd $(RUST_DIR) && cargo build

rust-build-size: rust-check ## Build with maximum size optimization
	@echo "🔨 Building firmware (size-optimized)..."
	cd $(RUST_DIR) && cargo build --profile release-size

rust-flash: rust-check ## Flash firmware to device and open serial monitor
	@echo "⚡ Flashing firmware to ESP32-C3..."
	cd $(RUST_DIR) && cargo run --release

rust-flash-dev: rust-check ## Flash debug build (faster iteration)
	@echo "⚡ Flashing firmware (debug build)..."
	cd $(RUST_DIR) && cargo run

rust-monitor: ## Open serial monitor to device
	@echo "📡 Opening serial monitor..."
	espflash monitor

rust-size: rust-check ## Show binary size breakdown
	@echo "📊 Binary size analysis..."
	cd $(RUST_DIR) && cargo size --release -- -A

rust-bloat: ## Analyze what's taking up space (requires cargo-bloat)
	@command -v cargo-bloat >/dev/null 2>&1 || { echo "Installing cargo-bloat..."; cargo install cargo-bloat; }
	@echo "🔍 Analyzing binary bloat..."
	cd $(RUST_DIR) && cargo bloat --release

rust-clean: ## Clean Rust firmware target
	@echo "🧹 Cleaning build artifacts..."
	cd $(RUST_DIR) && cargo clean

rust-clippy: rust-check ## Run Clippy linter
	@echo "🔍 Running Clippy..."
	cd $(RUST_DIR) && cargo clippy -- -D warnings

rust-fmt: ## Format Rust code
	@echo "✨ Formatting code..."
	cd $(RUST_DIR) && cargo fmt

rust-test: rust-check ## Run tests
	@echo "🧪 Running tests..."
	cd $(RUST_DIR) && cargo test

rust-doc: rust-check ## Generate and open documentation
	@echo "📚 Generating documentation..."
	cd $(RUST_DIR) && cargo doc --open

rust-update: ## Update Rust dependencies
	@echo "📦 Updating dependencies..."
	cd $(RUST_DIR) && cargo update

rust-audit: ## Audit dependencies for security issues
	@command -v cargo-audit >/dev/null 2>&1 || { echo "Installing cargo-audit..."; cargo install cargo-audit; }
	@echo "🔒 Auditing dependencies..."
	cd $(RUST_DIR) && cargo audit

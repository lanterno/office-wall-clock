.PHONY: help build deploy actions-status clean serve

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
	@echo "Checking GitHub Actions status..."
	@echo ""
	@ACTIVE=$$(gh run list --limit 100 --json status --jq '[.[] | select(.status == "in_progress" or .status == "queued")] | length' 2>/dev/null || echo "0"); \
	if [ "$$ACTIVE" -gt 0 ]; then \
		echo "⚡ Active workflow runs:"; \
		echo ""; \
		gh run list --limit 20 --json status,conclusion,name,databaseId,createdAt,displayTitle --jq '.[] | select(.status == "in_progress" or .status == "queued") | "  🔄 \(.name) - \(.displayTitle) (ID: \(.databaseId)) - \(.status)"'; \
	else \
		echo "✓ No active workflow runs"; \
		echo ""; \
		echo "📊 Last run status for each workflow:"; \
		echo ""; \
		gh run list --limit 100 --json name,status,conclusion,createdAt,displayTitle,databaseId 2>/dev/null | \
		jq -r 'group_by(.name) | map(.[0]) | .[] | if .conclusion == "success" then "  ✓" elif .conclusion == "failure" then "  ✗" elif .conclusion == "cancelled" then "  ⊘" else "  ○" end + " \(.name) - \(.displayTitle) (\(.conclusion // .status)) - \(.createdAt | split("T")[0])"' || echo "  No workflows found"; \
	fi

clean: ## Clean build artifacts
	rm -rf docs/
	find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true
	find . -type f -name "*.pyc" -delete 2>/dev/null || true

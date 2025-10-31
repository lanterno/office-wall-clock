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

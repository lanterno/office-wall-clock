# Documentation Deployment Guide

Complete guide for deploying the Wall Clock In Machine documentation to GitHub Pages.

## Quick Start (5 Minutes)

The repository is already configured for automatic deployment! Just follow these steps:

### 1. Enable GitHub Pages

1. Go to: `https://github.com/YOUR-USERNAME/office-wall-clock/settings/pages`
2. Under "Build and deployment":
   - **Source**: Deploy from a branch
   - **Branch**: `gh-pages` / `/ (root)`
3. Click **Save**

### 2. Push Your Code

```bash
git add .
git commit -m "Initial documentation"
git push origin main
```

### 3. Monitor Deployment

- Visit: `https://github.com/YOUR-USERNAME/office-wall-clock/actions`
- Wait 2-3 minutes for "Deploy Documentation" workflow
- Green ✓ = Success!

### 4. View Your Site

```
https://YOUR-USERNAME.github.io/office-wall-clock/
```

## Automatic Deployment

The GitHub Action (`.github/workflows/deploy-docs.yml`) automatically deploys when:

- ✅ You push to `main` branch
- ✅ Changes in `docs-site/**`
- ✅ Changes to `mkdocs.yml` or `requirements-docs.txt`
- ✅ Manual trigger via Actions tab

**No manual deployment needed!** 🎉

## Local Development

### Install Dependencies

```bash
# Install MkDocs and theme
pip install -r requirements-docs.txt
```

### Preview Site

```bash
# Start development server
mkdocs serve

# Site available at http://localhost:8000
# Auto-reloads on file changes
```

### Build Locally

```bash
# Build to site/ directory
mkdocs build

# Build with error checking
mkdocs build --strict

# Clean previous build
mkdocs build --clean
```

## Manual Deployment

If you prefer manual control over GitHub Actions:

```bash
# Deploy to GitHub Pages
mkdocs gh-deploy

# With custom commit message
mkdocs gh-deploy -m "Update documentation $(date)"
```

This builds and pushes directly to the `gh-pages` branch.

## Project Structure

```
wallClockInMachine/
├── mkdocs.yml                    # Site configuration
├── requirements-docs.txt         # Python dependencies
├── .github/workflows/
│   └── deploy-docs.yml          # GitHub Action
├── docs-site/                    # Documentation source
│   ├── index.md                 # Homepage
│   ├── getting-started/
│   ├── hardware/
│   ├── firmware/
│   ├── assembly/
│   └── ...
└── docs/                        # Generated site (deployed)
```

## Troubleshooting

### Workflow Fails

**Check these:**
1. Settings → Actions → Workflow permissions: "Read and write"
2. `requirements-docs.txt` exists and is valid
3. All markdown files have valid syntax

**Test locally:**
```bash
mkdocs build --strict
```

### Site Shows 404

- **Wait**: 2-3 minutes after first deployment
- **Verify**: Settings → Pages → Branch is `gh-pages`
- **Clear**: Browser cache (Ctrl+Shift+R / Cmd+Shift+R)

### Old Content Persists

- **Hard refresh**: Ctrl+Shift+R (Windows/Linux) or Cmd+Shift+R (Mac)
- **Note**: GitHub Pages CDN can take 5-10 minutes to update

### Changes Not Visible

1. Check Actions tab - did workflow complete?
2. View workflow logs for errors
3. Try manual deployment: `mkdocs gh-deploy`

## Custom Domain Setup

Want `docs.yourdomain.com`?

### 1. Configure DNS

Add a CNAME record in your DNS provider:

```
Type:  CNAME
Name:  docs
Value: YOUR-USERNAME.github.io
```

### 2. Add CNAME File

```bash
echo "docs.yourdomain.com" > docs-site/CNAME
git add docs-site/CNAME
git commit -m "Add custom domain"
git push
```

### 3. Enable in GitHub

- Settings → Pages → Custom domain: `docs.yourdomain.com`
- Wait 24-48 hours for DNS propagation
- Enable "Enforce HTTPS" (recommended)

## Alternative Platforms

### Netlify

**Features**: PR previews, instant rollbacks, forms

```bash
# Install CLI
npm install -g netlify-cli

# Deploy
mkdocs build
netlify deploy --dir=site --prod
```

**Or**: Connect GitHub repo in Netlify UI with:
- Build command: `pip install -r requirements-docs.txt && mkdocs build`
- Publish directory: `site`

### Vercel

**Features**: Global CDN, instant updates, analytics

```bash
# Install CLI
npm install -g vercel

# Deploy
mkdocs build
vercel --prod
```

### Cloudflare Pages

**Features**: Unlimited bandwidth, DDoS protection, free

1. Connect GitHub repository
2. Configure build:
   - Build command: `pip install -r requirements-docs.txt && mkdocs build`
   - Output directory: `site`
3. Deploy!

## Monitoring

### Add Build Badge

Show deployment status in README:

```markdown
![Documentation](https://github.com/YOUR-USERNAME/office-wall-clock/actions/workflows/deploy-docs.yml/badge.svg)
```

### Check Actions Status

```bash
# Using GitHub CLI
gh run list --workflow=deploy-docs.yml

# Watch latest run
gh run watch
```

### Using Makefile

The project includes helpful commands:

```bash
make serve          # Start local server
make build          # Build site
make deploy         # Build and commit to docs/
make docs-url       # Print documentation URL
make actions-status # Check GitHub Actions
make clean          # Clean build artifacts
```

## Quick Commands Reference

```bash
# Local development
mkdocs serve                    # Preview with auto-reload
mkdocs serve -a localhost:8080  # Custom port

# Building
mkdocs build                    # Build site
mkdocs build --strict          # Fail on warnings
mkdocs build --clean           # Clean build

# Deployment
mkdocs gh-deploy               # Deploy to GitHub Pages
git push origin main           # Auto-deploy via Actions

# Validation
mkdocs build --strict          # Check for errors
```

## Resources

- **MkDocs Documentation**: https://www.mkdocs.org/
- **Material Theme Docs**: https://squidfunk.github.io/mkdocs-material/
- **GitHub Pages Docs**: https://docs.github.com/en/pages
- **Project Docs**: See `docs-site/deployment/github-pages.md` for detailed guide

## Configuration Files

### mkdocs.yml

Main configuration:
- Site metadata
- Navigation structure
- Theme settings
- Plugin configuration

### requirements-docs.txt

Python dependencies:
- `mkdocs` - Static site generator
- `mkdocs-material` - Material Design theme
- Extensions and plugins

### .github/workflows/deploy-docs.yml

GitHub Action that:
1. Checks out code
2. Installs Python dependencies
3. Builds documentation
4. Deploys to `gh-pages` branch

## Getting Help

For detailed deployment instructions, see:
- `docs-site/deployment/github-pages.md` - Comprehensive GitHub Pages guide
- `docs-site/deployment/quick-start.md` - Quick reference

For issues:
1. Check workflow logs in Actions tab
2. Test build locally: `mkdocs build --strict`
3. Verify file structure matches expected layout

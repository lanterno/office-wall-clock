# Deployment Quick Start

Fast reference guide for getting your documentation online.

## GitHub Pages Setup

### 5-Minute Deployment

```bash
# 1. Enable GitHub Pages
# Go to: https://github.com/lanterno/office-wall-clock/settings/pages
# Source: Deploy from a branch → gh-pages → / (root) → Save

# 2. Push to GitHub
git add .
git commit -m "Add documentation and auto-deployment"
git push origin main

# 3. Monitor deployment
# https://github.com/lanterno/office-wall-clock/actions

# 4. Visit your site (2-3 minutes)
# https://lanterno.github.io/office-wall-clock/
```

### What Was Already Configured

✅ **GitHub Action** - `.github/workflows/deploy-docs.yml`  
✅ **MkDocs Config** - `mkdocs.yml`  
✅ **Dependencies** - `requirements-docs.txt`  
✅ **Content** - All documentation in `docs-site/`

### Auto-Deploy Triggers

Deployment happens automatically when:
- ✅ You push to `main` branch
- ✅ Any file in `docs-site/` changes
- ✅ `mkdocs.yml` is modified
- ✅ `requirements-docs.txt` is updated

## Local Testing

Before deploying, test locally:

```bash
# Install dependencies
pip install -r requirements-docs.txt

# Start development server
mkdocs serve

# Visit http://localhost:8000
# Changes auto-reload!
```

## Monitoring

### Check Build Status

**In GitHub**:
- Go to "Actions" tab
- Click latest workflow run
- Green ✓ = success
- Red ✗ = check logs

**Add Badge to README**:
```markdown
![Documentation](https://github.com/lanterno/office-wall-clock/actions/workflows/deploy-docs.yml/badge.svg)
```

## Troubleshooting

### Workflow Permission Error

**Settings → Actions → General**
- Workflow permissions: ✅ **Read and write permissions**
- Save and re-run workflow

### Site Shows 404

**Wait** 2-3 minutes after first deploy  
**Check** Settings → Pages → Branch = `gh-pages`  
**Clear** Browser cache (Ctrl+Shift+R)

### Build Fails

**Test locally first**:
```bash
mkdocs build --strict
```

**Check logs**:
```bash
gh run view --log-failed
```

## Next Steps

- Site URL (default): `https://lanterno.github.io/office-wall-clock/`

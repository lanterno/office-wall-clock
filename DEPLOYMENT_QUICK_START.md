# Documentation Deployment

Quick reference for deploying the Wall Clock In Machine documentation.

## GitHub Pages (Automatic) ⚡

**Status**: ✅ Configured and ready to use

### First-Time Setup (5 minutes)

```bash
# 1. Enable GitHub Pages
# Go to: Settings → Pages → Source: gh-pages branch

# 2. Push your code
git add .
git commit -m "Initial documentation"
git push origin main

# 3. Wait 2-3 minutes for GitHub Action to complete

# 4. Visit your site
# https://YOUR-USERNAME.github.io/wallClockInMachine/
```

### Automatic Updates

Every time you push to `main` branch:
1. GitHub Action triggers automatically
2. Builds documentation (1-2 minutes)
3. Deploys to gh-pages branch
4. Site updates automatically

**No manual deployment needed!** 🎉

### Files Configured

- ✅ `.github/workflows/deploy-docs.yml` - GitHub Action
- ✅ `mkdocs.yml` - Site configuration
- ✅ `requirements-docs.txt` - Dependencies
- ✅ `docs-site/` - Documentation content

### Monitor Deployment

**Check status**:
- Visit: `https://github.com/YOUR-USERNAME/wallClockInMachine/actions`
- Look for "Deploy Documentation to GitHub Pages" workflow
- Green ✓ = deployed successfully
- Red ✗ = build failed (check logs)

**Build badge** (add to README):
```markdown
![Documentation](https://github.com/YOUR-USERNAME/wallClockInMachine/actions/workflows/deploy-docs.yml/badge.svg)
```

## Local Preview

Test before deploying:

```bash
# Install dependencies
pip install -r requirements-docs.txt

# Start local server
mkdocs serve

# Open http://localhost:8000
# Auto-reloads on file changes
```

## Manual Deployment

If you prefer manual control:

```bash
# Build and deploy to GitHub Pages
mkdocs gh-deploy

# Or with custom message
mkdocs gh-deploy -m "Update documentation $(date)"
```

## Troubleshooting

### Workflow Fails

**Check**:
1. Settings → Actions → Permissions: "Read and write"
2. `requirements-docs.txt` exists and is correct
3. All markdown files have valid syntax

**Test locally**:
```bash
mkdocs build --strict
```

### Site Shows 404

**Wait**: 2-3 minutes after first deployment
**Check**: Settings → Pages → Branch is `gh-pages`
**Clear**: Browser cache (Ctrl+Shift+R)

### Old Content Shows

**Hard refresh**: Ctrl+Shift+R (Windows/Linux) or Cmd+Shift+R (Mac)
**Clear cache**: GitHub Pages CDN takes 5 minutes to update

## Custom Domain

Want `docs.yourdomain.com`?

1. **Add CNAME record** in DNS:
   ```
   Type:  CNAME
   Name:  docs
   Value: YOUR-USERNAME.github.io
   ```

2. **Add CNAME file**:
   ```bash
   echo "docs.yourdomain.com" > docs-site/CNAME
   git add docs-site/CNAME
   git commit -m "Add custom domain"
   git push
   ```

3. **Configure GitHub**:
   - Settings → Pages → Custom domain: `docs.yourdomain.com`
   - Wait 24-48 hours for DNS
   - Enable "Enforce HTTPS"

## Alternative Platforms

### Netlify (PR Previews)

```bash
# Install Netlify CLI
npm install -g netlify-cli

# Deploy
netlify deploy --dir=site --prod
```

Auto-deploy on push + PR previews!

### Vercel (Fast CDN)

```bash
# Install Vercel CLI
npm install -g vercel

# Deploy
vercel --prod
```

Global CDN, instant updates.

### Cloudflare Pages (Unlimited)

1. Connect GitHub repo
2. Build: `pip install -r requirements-docs.txt && mkdocs build`
3. Output: `site`
4. Deploy!

Unlimited bandwidth, free.

## Resources

- **GitHub Pages Guide**: [docs-site/deployment/github-pages.md](docs-site/deployment/github-pages.md)
- **MkDocs Docs**: https://www.mkdocs.org/
- **Material Theme**: https://squidfunk.github.io/mkdocs-material/

## Quick Commands

```bash
# Local preview
mkdocs serve

# Build only
mkdocs build

# Deploy to GitHub Pages
mkdocs gh-deploy

# Check for errors
mkdocs build --strict

# Clean build
mkdocs build --clean
```

---

**Need help?** See [GitHub Pages Deployment Guide](docs-site/deployment/github-pages.md) for detailed instructions.

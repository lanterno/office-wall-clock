# GitHub Pages Deployment Guide

Complete guide to deploying the Wall Clock In Machine documentation to GitHub Pages.

## Quick Setup (5 minutes)

### Step 1: Enable GitHub Pages

1. Go to your repository on GitHub
2. Click **Settings** (top right)
3. Scroll down to **Pages** section (left sidebar)
4. Under "Build and deployment":
   - **Source**: Deploy from a branch
   - **Branch**: `gh-pages` / `/ (root)`
5. Click **Save**

That's it! The GitHub Action will handle the rest.

### Step 2: Push Your Code

```bash
# Add all files
git add .

# Commit changes
git commit -m "Add documentation site with GitHub Pages deployment"

# Push to GitHub
git push origin main
```

### Step 3: Wait for Deployment

1. Go to **Actions** tab in your repository
2. Watch the "Deploy Documentation to GitHub Pages" workflow run
3. Wait 2-3 minutes for completion
4. Your site will be live at:
   ```
   https://YOUR-USERNAME.github.io/wallClockInMachine/
   ```

## Automatic Deployment

The GitHub Action (`.github/workflows/deploy-docs.yml`) automatically deploys when:

- ✅ You push to `main` branch
- ✅ Changes are made to:
  - `docs-site/**` (any documentation file)
  - `mkdocs.yml` (configuration)
  - `requirements-docs.txt` (dependencies)
- ✅ You manually trigger via "Actions" tab → "Run workflow"

### What the Action Does

```yaml
1. Checkout your code
2. Install Python 3.x
3. Install MkDocs + dependencies
4. Build static site
5. Deploy to gh-pages branch
6. GitHub Pages serves the site
```

### Workflow Status

Check deployment status:

```bash
# View recent workflow runs
gh run list --workflow=deploy-docs.yml

# Watch live workflow
gh run watch

# View logs if failed
gh run view --log-failed
```

Or visit: `https://github.com/YOUR-USERNAME/wallClockInMachine/actions`

## Manual Deployment

If you prefer to deploy manually:

```bash
# Install dependencies
pip install -r requirements-docs.txt

# Build and deploy
mkdocs gh-deploy

# Or with custom message
mkdocs gh-deploy -m "Update documentation $(date +%Y-%m-%d)"
```

This will:
1. Build the site to `site/` directory
2. Force push to `gh-pages` branch
3. GitHub Pages automatically serves the new version

## Custom Domain Setup

### Using GitHub Subdomain (Default)

Your site is at:
```
https://YOUR-USERNAME.github.io/wallClockInMachine/
```

No setup needed!

### Using Custom Domain

Want `docs.yourdomain.com`?

#### 1. Add CNAME Record in DNS

In your DNS provider (e.g., Cloudflare, Namecheap):

```
Type:  CNAME
Name:  docs (or whatever subdomain)
Value: YOUR-USERNAME.github.io
TTL:   Auto or 3600
```

#### 2. Add CNAME File

Create `docs-site/CNAME`:
```
docs.yourdomain.com
```

Commit and push:
```bash
echo "docs.yourdomain.com" > docs-site/CNAME
git add docs-site/CNAME
git commit -m "Add custom domain"
git push origin main
```

#### 3. Configure in GitHub

1. Go to Settings → Pages
2. Under "Custom domain", enter: `docs.yourdomain.com`
3. Click **Save**
4. Wait for DNS check (can take 24-48 hours)
5. Enable **Enforce HTTPS** (appears after DNS propagates)

#### 4. Update mkdocs.yml

```yaml
site_url: https://docs.yourdomain.com
```

### Custom Domain with EPFL

If you want `wallclockin.epfl.ch` or similar:

1. Contact EPFL IT (service.desk@epfl.ch)
2. Request subdomain for your project
3. They'll configure DNS
4. Follow steps above with EPFL domain

Alternatively, use EPFL's GitLab Pages or IC cluster hosting.

## Verifying Deployment

### Check Build Status

**Badge in README**:

Add to your `README.md`:
```markdown
![Documentation](https://github.com/YOUR-USERNAME/wallClockInMachine/actions/workflows/deploy-docs.yml/badge.svg)
```

### Test Site

1. **Visit URL**: https://YOUR-USERNAME.github.io/wallClockInMachine/
2. **Check pages load**: Navigate through documentation
3. **Test search**: Use search bar (top right)
4. **Mobile view**: Check responsive design
5. **Check links**: Ensure internal links work

### Common Issues

#### Site Shows 404

**Cause**: GitHub Pages not enabled or wrong branch

**Fix**:
1. Settings → Pages
2. Ensure "gh-pages" branch selected
3. Wait 2-3 minutes
4. Hard refresh browser (Ctrl+Shift+R)

#### Workflow Fails

**Cause**: Missing dependencies or permission issues

**Fix**:
```bash
# Check workflow logs
gh run view --log-failed

# Common issues:
# - requirements-docs.txt missing → Add file
# - Permission denied → Check repository settings
# - Build error → Test locally first: mkdocs build --strict
```

#### CSS Not Loading

**Cause**: Incorrect `site_url` in mkdocs.yml

**Fix** - Update `mkdocs.yml`:
```yaml
# For GitHub subdomain
site_url: https://YOUR-USERNAME.github.io/wallClockInMachine/

# For custom domain
site_url: https://docs.yourdomain.com
```

#### Pages Out of Date

**Cause**: Browser cache or CDN delay

**Fix**:
- Hard refresh: Ctrl+Shift+R (or Cmd+Shift+R on Mac)
- Clear browser cache
- Wait 5 minutes for CDN to update
- Check gh-pages branch has latest commit

## Advanced Configuration

### Deploy on Tags Only

Want to deploy only on version releases?

Edit `.github/workflows/deploy-docs.yml`:
```yaml
on:
  push:
    tags:
      - 'v*'  # Only deploy on version tags (v1.0.0, v1.1.0, etc.)
```

Then deploy with:
```bash
git tag v1.0.0
git push origin v1.0.0
```

### Multi-Version Documentation

Want to keep old versions accessible?

Use [mike](https://github.com/jimporter/mike):

```bash
# Install mike
pip install mike

# Deploy version
mike deploy 1.0 latest --push --update-aliases

# Set default version
mike set-default latest --push

# Deploy new version
mike deploy 1.1 latest --push --update-aliases
```

Users can switch versions via dropdown.

### Preview Pull Requests

Want to preview docs before merging?

Use [Netlify](https://www.netlify.com/) or [Vercel](https://vercel.com/) for PR previews:

**netlify.toml**:
```toml
[build]
  command = "pip install -r requirements-docs.txt && mkdocs build"
  publish = "site"

[build.environment]
  PYTHON_VERSION = "3.10"
```

Connect your repo to Netlify → automatic PR previews!

### Build Status in README

Show build status:

```markdown
# Wall Clock In Machine

[![Documentation](https://github.com/YOUR-USERNAME/wallClockInMachine/actions/workflows/deploy-docs.yml/badge.svg)](https://github.com/YOUR-USERNAME/wallClockInMachine/actions/workflows/deploy-docs.yml)
[![Pages](https://img.shields.io/badge/docs-GitHub%20Pages-blue)](https://YOUR-USERNAME.github.io/wallClockInMachine/)

[📖 Read the Documentation](https://YOUR-USERNAME.github.io/wallClockInMachine/)
```

## Monitoring & Analytics

### Google Analytics

Add to `mkdocs.yml`:
```yaml
extra:
  analytics:
    provider: google
    property: G-XXXXXXXXXX
```

Get tracking ID from [Google Analytics](https://analytics.google.com/).

### GitHub Insights

View traffic stats:
1. Repository → Insights
2. Traffic section
3. See views, unique visitors, referring sites

### Uptime Monitoring

Use [UptimeRobot](https://uptimerobot.com/) (free):
1. Add monitor: `https://YOUR-USERNAME.github.io/wallClockInMachine/`
2. Get alerts if site goes down
3. View uptime statistics

## Local Development Workflow

### Edit → Preview → Push

```bash
# 1. Edit documentation
vim docs-site/hardware/overview.md

# 2. Preview locally
mkdocs serve
# Open http://localhost:8000

# 3. Commit changes
git add docs-site/hardware/overview.md
git commit -m "Update hardware overview"

# 4. Push to trigger deployment
git push origin main

# 5. Wait 2-3 minutes, then check live site
open https://YOUR-USERNAME.github.io/wallClockInMachine/
```

### Pre-commit Hook

Automatically check docs before committing:

`.git/hooks/pre-commit`:
```bash
#!/bin/bash
echo "Checking documentation build..."
mkdocs build --strict --quiet
if [ $? -ne 0 ]; then
    echo "❌ Documentation build failed!"
    echo "Fix errors before committing."
    exit 1
fi
echo "✅ Documentation build successful!"
```

Make executable:
```bash
chmod +x .git/hooks/pre-commit
```

## Cost & Limits

### GitHub Pages Limits

- **Storage**: 1 GB max
- **Bandwidth**: 100 GB/month
- **Builds**: 10 per hour
- **Cost**: **FREE!** ✨

Our site is ~5 MB, well within limits.

### Bandwidth Estimates

If 1000 people visit per month:
- Page size: ~5 MB
- Total: 5 GB/month
- Limit: 100 GB/month
- **Usage**: 5% ✓

### Upgrading Limits

Need more? Alternatives:

| Service | Bandwidth | Cost |
|---------|-----------|------|
| **GitHub Pages** | 100 GB/month | Free |
| **Netlify** | 100 GB/month | Free |
| **Vercel** | 100 GB/month | Free |
| **Cloudflare Pages** | Unlimited | Free |
| **AWS S3 + CloudFront** | Pay per use | ~$1/month |

## Troubleshooting

### Workflow Permission Error

**Error**: `Permission denied`

**Fix**:
1. Settings → Actions → General
2. Workflow permissions → **Read and write permissions**
3. Save
4. Re-run workflow

### Build Fails: Module Not Found

**Error**: `ModuleNotFoundError: No module named 'mkdocs_material'`

**Fix**: Check `requirements-docs.txt` exists and contains:
```
mkdocs>=1.5.0
mkdocs-material>=9.4.0
mkdocs-minify-plugin>=0.7.0
mkdocs-git-revision-date-localized-plugin>=1.2.0
```

### Site Shows Old Content

**Causes**:
1. Browser cache
2. CDN delay
3. Wrong branch deployed

**Fixes**:
```bash
# Clear gh-pages branch
git push origin --delete gh-pages

# Redeploy
mkdocs gh-deploy --force

# Hard refresh browser
Ctrl + Shift + R
```

### Links Broken

**Cause**: Absolute paths in markdown

**Fix**: Use relative paths:
```markdown
❌ [Link](/hardware/overview.md)
✅ [Link](../hardware/overview.md)

❌ ![Image](/images/photo.jpg)
✅ ![Image](../images/photo.jpg)
```

### Search Not Working

**Cause**: Search plugin not enabled

**Fix** - Add to `mkdocs.yml`:
```yaml
plugins:
  - search:
      lang: en
```

## Security

### Secrets Management

**Never commit**:
- API keys
- Passwords
- Personal tokens

Use GitHub Secrets instead:
1. Settings → Secrets and variables → Actions
2. New repository secret
3. Reference in workflow: `${{ secrets.SECRET_NAME }}`

### HTTPS Enforcement

Always enable HTTPS:
1. Settings → Pages
2. ✅ Enforce HTTPS

### Branch Protection

Protect `gh-pages` branch:
1. Settings → Branches
2. Add rule for `gh-pages`
3. ✅ Require status checks
4. ✅ Require signed commits (optional)

## Maintenance

### Update Dependencies

Monthly or when security issues found:

```bash
# Update all packages
pip install --upgrade -r requirements-docs.txt

# Check for outdated
pip list --outdated

# Update requirements
pip freeze | grep mkdocs > requirements-docs.txt
```

### Monitor Build Times

Check workflow duration:
```bash
gh run list --workflow=deploy-docs.yml --json conclusion,startedAt,durationMs
```

Typical build: 1-2 minutes

### Cleanup Old Workflows

Delete old workflow runs:
```bash
# Delete runs older than 30 days
gh run list --limit 1000 --json databaseId --jq '.[].databaseId' | \
  xargs -I {} gh run delete {}
```

## Next Steps

**Your documentation is now live!** 🎉

- ✅ Automatic deployment on push
- ✅ HTTPS enabled
- ✅ Search functionality
- ✅ Mobile responsive
- ✅ Fast CDN delivery

**Share your site**:
- Add link to README
- Share on social media
- Submit to awesome lists
- Add to project website

**Improve SEO**:
- Add `site_description` in mkdocs.yml
- Add Open Graph tags
- Submit sitemap to Google
- Add meta descriptions to pages

**Monitor**:
- Set up Google Analytics
- Watch GitHub traffic stats
- Monitor build times
- Update dependencies monthly

---

**Questions?** 
- [GitHub Pages Docs](https://docs.github.com/en/pages)
- [MkDocs Deployment](https://www.mkdocs.org/user-guide/deploying-your-docs/)
- [Community Discussions](https://github.com/YOUR-USERNAME/wallClockInMachine/discussions)

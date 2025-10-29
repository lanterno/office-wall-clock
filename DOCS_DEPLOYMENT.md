# Documentation Website Deployment

This guide explains how to build and deploy the Wall Clock In Machine documentation website.

## Prerequisites

- Python 3.8 or higher
- pip (Python package manager)
- Git (for deployment to GitHub Pages)

## Local Development

### 1. Install Dependencies

```bash
# Navigate to project root
cd wallClockInMachine/

# Install documentation dependencies
pip install -r requirements-docs.txt
```

### 2. Preview Locally

```bash
# Start local development server
mkdocs serve

# Or specify custom port
mkdocs serve -a localhost:8080
```

Open your browser to `http://localhost:8000` (or your specified port).

The site will auto-reload when you edit markdown files!

### 3. File Structure

```
wallClockInMachine/
├── mkdocs.yml                    # Main configuration
├── requirements-docs.txt         # Python dependencies
├── docs-site/                    # Documentation source
│   ├── index.md                  # Homepage
│   ├── stylesheets/
│   │   └── extra.css            # Custom styles
│   ├── getting-started/
│   ├── hardware/
│   ├── firmware/
│   ├── assembly/
│   ├── usage/
│   ├── troubleshooting/
│   ├── development/
│   ├── reference/
│   └── about/
└── site/                         # Generated site (git ignored)
```

## Building the Site

### Build Static Files

```bash
# Build documentation to site/ directory
mkdocs build

# Build with strict mode (fails on warnings)
mkdocs build --strict

# Clean previous build
mkdocs build --clean
```

The generated site will be in the `site/` directory.

## Deployment Options

### Option 1: GitHub Pages (Recommended)

#### Automatic Deployment with GitHub Actions

✅ **Already configured!** The repository includes `.github/workflows/deploy-docs.yml`

**Quick Setup** (5 minutes):

1. **Enable GitHub Pages**:
   - Go to Settings → Pages
   - Source: "Deploy from a branch"
   - Branch: `gh-pages` / `/ (root)`
   - Save

2. **Push your code**:
   ```bash
   git add .
   git commit -m "Initial commit with documentation"
   git push origin main
   ```

3. **Wait 2-3 minutes** - GitHub Action automatically:
   - Builds the documentation
   - Deploys to gh-pages branch
   - Your site is live!

4. **Visit your site**:
   ```
   https://YOUR-USERNAME.github.io/wallClockInMachine/
   ```

**The workflow automatically deploys when**:
- You push to `main` branch
- Any files in `docs-site/` change
- `mkdocs.yml` or `requirements-docs.txt` change
- Or manually trigger via Actions tab

**Detailed instructions**: See [GitHub Pages Deployment Guide](docs-site/deployment/github-pages.md)

#### Manual Deployment

```bash
# Deploy to GitHub Pages
mkdocs gh-deploy

# Deploy with custom message
mkdocs gh-deploy -m "Update documentation"
```

This will:
1. Build the site
2. Push to `gh-pages` branch
3. Site available at `https://yourusername.github.io/wallClockInMachine/`

### Option 2: Netlify

#### Using Netlify CLI

```bash
# Install Netlify CLI
npm install -g netlify-cli

# Build site
mkdocs build

# Deploy to Netlify
netlify deploy --dir=site --prod
```

#### Using Netlify UI

1. Go to [Netlify](https://www.netlify.com/)
2. Click "Add new site" → "Import an existing project"
3. Connect your GitHub repository
4. Configure build settings:
   - **Build command**: `pip install -r requirements-docs.txt && mkdocs build`
   - **Publish directory**: `site`
5. Click "Deploy site"

Netlify will auto-deploy on every push!

### Option 3: Vercel

Create `vercel.json`:

```json
{
  "buildCommand": "pip install -r requirements-docs.txt && mkdocs build",
  "outputDirectory": "site",
  "installCommand": "pip install -r requirements-docs.txt"
}
```

Deploy:
```bash
# Install Vercel CLI
npm install -g vercel

# Deploy
vercel --prod
```

### Option 4: ReadTheDocs

1. Go to [ReadTheDocs.org](https://readthedocs.org/)
2. Import your GitHub repository
3. Configure:
   - **Documentation type**: Mkdocs
   - **Requirements file**: `requirements-docs.txt`
4. Build automatically on every commit

### Option 5: Custom Server

```bash
# Build static site
mkdocs build

# Copy site/ directory to your web server
scp -r site/* user@yourserver.com:/var/www/html/wallclockin/

# Or use rsync
rsync -avz site/ user@yourserver.com:/var/www/html/wallclockin/
```

Serve with any web server (nginx, Apache, etc.).

## Configuration

### Update Site URL

Edit `mkdocs.yml`:

```yaml
site_url: https://your-actual-domain.com
repo_url: https://github.com/yourusername/wallClockInMachine
```

### Update Repository Links

Edit `mkdocs.yml`:

```yaml
repo_name: yourusername/wallClockInMachine
repo_url: https://github.com/yourusername/wallClockInMachine
edit_uri: edit/main/docs-site/
```

### Customize Theme Colors

Edit `mkdocs.yml`:

```yaml
theme:
  palette:
    scheme: default
    primary: indigo    # Change to: red, pink, purple, etc.
    accent: blue       # Change to: amber, orange, etc.
```

Available colors: red, pink, purple, deep purple, indigo, blue, light blue, cyan, teal, green, light green, lime, yellow, amber, orange, deep orange

### Add Google Analytics

Edit `mkdocs.yml`:

```yaml
extra:
  analytics:
    provider: google
    property: G-XXXXXXXXXX  # Your GA4 measurement ID
```

## Custom Domain

### GitHub Pages

1. Add `CNAME` file to `docs-site/` directory:
   ```
   docs.yourdomain.com
   ```

2. In your DNS provider, add CNAME record:
   ```
   docs.yourdomain.com → yourusername.github.io
   ```

3. Enable HTTPS in GitHub repo settings

### Netlify

1. Go to site settings → Domain management
2. Add custom domain: `docs.yourdomain.com`
3. Follow DNS configuration instructions
4. HTTPS is automatic!

## Troubleshooting

### "Material not found" Error

```bash
# Ensure mkdocs-material is installed
pip install mkdocs-material

# Or reinstall all dependencies
pip install -r requirements-docs.txt --force-reinstall
```

### Build Fails with Import Error

```bash
# Install in editable mode
pip install -e .

# Or use virtual environment
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
pip install -r requirements-docs.txt
```

### GitHub Pages Shows 404

**Check**:
1. GitHub Pages enabled in repo settings?
2. `gh-pages` branch exists?
3. Correct branch selected in Pages settings?
4. Wait 1-2 minutes after deployment

### Links Not Working

**Ensure relative links** in markdown:
```markdown
✅ [Link](../hardware/overview.md)
❌ [Link](/hardware/overview.md)
```

### Images Not Showing

Place images in `docs-site/images/` and reference:
```markdown
![Alt text](../images/photo.jpg)
```

## Maintenance

### Updating Dependencies

```bash
# Check for updates
pip list --outdated

# Update all
pip install --upgrade -r requirements-docs.txt

# Or update individually
pip install --upgrade mkdocs-material
```

### Checking for Broken Links

```bash
# Install linkchecker
pip install linkchecker

# Build site
mkdocs build

# Check links
linkchecker site/
```

### Search Index

The search feature automatically indexes all markdown content. To improve search:

1. Use descriptive headings
2. Add keywords to content
3. Use proper markdown formatting

## Performance Optimization

### Enable Minification

Already configured in `mkdocs.yml`:
```yaml
plugins:
  - minify:
      minify_html: true
```

### Optimize Images

```bash
# Install imageoptim or similar
# Compress images before adding to docs

# Or use online tools:
# - TinyPNG.com
# - Squoosh.app
```

### Enable Caching

For custom server deployment, add cache headers:

**nginx example**:
```nginx
location ~* \.(js|css|png|jpg|jpeg|gif|ico|svg)$ {
    expires 1y;
    add_header Cache-Control "public, immutable";
}
```

## Advanced Features

### Versioning

Use [mike](https://github.com/jimporter/mike) for version management:

```bash
# Install mike
pip install mike

# Deploy version
mike deploy 1.0 latest --push --update-aliases

# Set default version
mike set-default latest --push
```

### Multi-language

Add languages in `mkdocs.yml`:

```yaml
plugins:
  - i18n:
      default_language: en
      languages:
        en: English
        es: Español
        fr: Français
```

### PDF Export

Install pdf plugin:

```bash
pip install mkdocs-pdf-export-plugin
```

Add to `mkdocs.yml`:

```yaml
plugins:
  - pdf-export
```

## CI/CD Integration

### Test Build in CI

Add to `.github/workflows/test.yml`:

```yaml
name: Test Documentation

on: [push, pull_request]

jobs:
  test-docs:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v4
        with:
          python-version: 3.x
      - run: pip install -r requirements-docs.txt
      - run: mkdocs build --strict
```

This ensures documentation builds successfully on every commit.

## Next Steps

- [Configure Custom Domain](#custom-domain)
- [Set Up Auto-Deployment](#automatic-deployment-with-github-actions)
- [Customize Theme](#customize-theme-colors)
- [Add Analytics](#add-google-analytics)

---

**Need Help?** Open an issue on [GitHub](https://github.com/yourusername/wallClockInMachine/issues)

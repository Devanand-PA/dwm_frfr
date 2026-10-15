#!/bin/bash
# DWM Installer Script for Fedora
# Installs all libraries, compiles dwm, and sets up .desktop file

set -e

echo "=== DWM Installer for Fedora ==="

# Update system
echo "Updating system..."
sudo dnf update -y

# Install dependencies for dwm
echo "Installing dependencies..."
sudo dnf install -y \
    xorg-x11-server-Xorg \
    xorg-x11-xinit \
    libXinerama-devel \
    libXft-devel \
    fontconfig-devel \
    freetype2-devel \
    libX11-devel \
    libXext-devel \
    libXrandr-devel \
    libXcomposite-devel \
    libXdamage-devel \
    gcc \
    make \
    tk-devel

# Create dwm directory if it doesn't exist
DWM_DIR="$HOME/dwm"
mkdir -p "$DWM_DIR"

# Copy project files
echo "Setting up dwm files..."
cp -r /home/devanandpa/sourced/dwm_frfr/dwm/* "$DWM_DIR/"

# Compile dwm
echo "Compiling dwm..."
cd "$DWM_DIR"
make clean
make

# Install dwm
echo "Installing dwm..."
sudo make install

# Set up .desktop file
echo "Setting up .desktop file..."
DESKTOP_DIR="/usr/share/applications"
mkdir -p "$DESKTOP_DIR"

cat > "$DESKTOP_DIR/dwm.desktop" << 'EOF'
[Desktop Entry]
Name=dwm
Comment=dynamic window manager
Exec=/usr/local/bin/dwm
Icon=dwm
Type=Application
Categories=WindowManager;X-WM;Application
EOF

chmod 644 "$DESKTOP_DIR/dwm.desktop"

# Install dwm icon
echo "Installing dwm icon..."
ICON_DIR="/usr/share/icons/hicolor"
if [ -d "$ICON_DIR" ]; then
    # Try to find appropriate size directory
    for size in 256 128 64 48 32 24 16; do
        size_dir="$ICON_DIR/$size/apps"
        if [ -d "$size_dir" ]; then
            sudo cp /home/devanandpa/sourced/dwm_frfr/dwm/dwm.png "$size_dir/dwm.png"
            break
        fi
    done
    # Also try pixmaps fallback
    if [ ! -f "$ICON_DIR/256x256/apps/dwm.png" ] && [ ! -f "$ICON_DIR/128x128/apps/dwm.png" ]; then
        sudo mkdir -p "$ICON_DIR/pixmaps"
        sudo cp /home/devanandpa/sourced/dwm_frfr/dwm/dwm.png "$ICON_DIR/pixmaps/dwm.png"
    fi
fi

# Set up compile command alias
echo "Setting up compile command..."
echo "alias dwm-compile='cd ~/dwm && make clean && make && sudo make install'" >> "$HOME/.bashrc"

echo ""
echo "=== DWM installed successfully! ==="
echo "Binary: /usr/local/bin/dwm"
echo "Desktop file: /usr/share/applications/dwm.desktop"
echo "To compile again: dwm-compile"
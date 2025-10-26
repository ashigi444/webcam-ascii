# 📹 Webcam ASCII Art Viewer

Transform your webcam feed into ASCII art directly in your terminal!

![Version](https://img.shields.io/badge/version-0.2.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)

## ✨ Features

- Real-time webcam to ASCII conversion
- **NEW: Multiple character palettes** (10, 12, or 70 characters)
- **NEW: Command line options** for palette selection
- Automatic terminal size detection
- Automatic aspect ratio correction
- Clean exit with Ctrl+C

## 🚀 Quick Start

### Prerequisites

You only need OpenCV installed:

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install libopencv-dev
```

**Fedora:**
```bash
sudo dnf install opencv-devel
```

**macOS:**
```bash
brew install opencv
```

**Arch Linux:**
```bash
sudo pacman -S opencv
```

### Build & Run

```bash
# Clone the repository
git clone https://github.com/ashigi444/webcam-ascii.git
cd webcam-ascii

# Build
mkdir build && cd build
cmake ..
make

# Run
./webcam-ascii
```

Or use the build script:
```bash
chmod +x build.sh
./build.sh
./build/webcam-ascii
```

## 🎮 Usage

### Basic usage
```bash
./webcam-ascii
```

### With options
```bash
# Use detailed palette for maximum quality
./webcam-ascii -p detailed

# Use standard palette (12 chars)
./webcam-ascii --palette standard

# Show help
./webcam-ascii --help
```

### Available Options

**Character Palettes:**
- `simple` (default) - 10 characters: ` .:-=+*#%@`
- `standard` - 12 characters: ` .·:ıİ+*oO#@`
- `detailed` - 70 characters for maximum detail and smooth gradients

**Controls:**
- **Ctrl+C** or **Q** - Exit the program

## 🛠️ Technical Details

- Written in C++17
- Uses OpenCV for video capture and image processing
- Multiple character palettes with varying levels of detail
- ANSI escape codes for terminal control
- Automatic aspect ratio correction (characters are ~2:1 tall:wide)
- Command line argument parsing

## 📝 Notes

- Works best in terminals with monospace fonts
- Bigger terminal = more detail! Try fullscreen and unzooming!
- The `detailed` palette provides significantly better image quality
- Default camera (device 0) is used

## 🗺️ Roadmap

Coming soon:
- ✅ ~~Multiple character palettes~~ (v0.2.0)
- Color support (ANSI 256 colors)
- FPS control
- Image quality improvements (CLAHE, gamma correction)
- Possibility to convert an image directly
- Camera selection

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features
- Submit pull requests

## 📄 License

MIT License - feel free to use this project however you like!

---

**ashigi444 <3**

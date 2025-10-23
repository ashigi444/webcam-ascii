# 📹 Webcam ASCII Art Viewer

Transform your webcam feed into ASCII art directly in your terminal!

![Version](https://img.shields.io/badge/version-0.1.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)

## ✨ Features

- Real-time webcam to ASCII conversion
- Automatic terminal size detection
- Simple ASCII character palette
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

Simply run the program:
```bash
./webcam-ascii
```

**Controls:**
- **Ctrl+C** or **Q** - Exit the program

## 🛠️ Technical Details

- Written in C++17
- Uses OpenCV for video capture
- Character palette: ` .:-=+*#%@`
- Automatic aspect ratio correction

## 📝 Notes

- Works best in terminals with monospace fonts
- Bigger terminal = more detail! Try fullscreen and unzooming !
- Default camera (device 0) is used

## 🗺️ Roadmap

Coming soon:
- Multiple character palettes
- Color support
- FPS control
- Possibility to convert an image directly
- Camera selection
- Image quality improvements

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features
- Submit pull requests

## 📄 License

MIT License - feel free to use this project however you like!

---

**ashigi444 <3**
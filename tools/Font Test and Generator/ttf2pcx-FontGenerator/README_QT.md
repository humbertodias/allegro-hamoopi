# TTF to PCX Font Generator (Qt Version)

This is a cross-platform Qt6-based version of the TTF to PCX font generator, converted from the original Windows MFC application.

## Features

- Platform-agnostic implementation using Qt6
- Converts TrueType fonts to PCX files for use with Allegro
- Supports both monochrome and antialiased output
- Preview of selected fonts
- Configurable character ranges (Unicode support up to 0xFFFF)
- Antialiased fonts use 8x8 supersampling for 64 intensity levels

## Building

### Requirements

- CMake 3.16 or later
- Qt6 (Core, Gui, Widgets modules)
- C++17 compatible compiler

### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install qt6-base-dev cmake build-essential

# Build
cd "tools/Font Test and Generator/ttf2pcx-FontGenerator"
mkdir build && cd build
cmake ..
make
```

### Windows

```bash
# Install Qt6 from https://www.qt.io/download
# Make sure Qt6 is in your PATH

mkdir build
cd build
cmake ..
cmake --build .
```

### macOS

```bash
# Install Qt6 via Homebrew
brew install qt6

# Build
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=$(brew --prefix qt6) ..
make
```

## Usage

1. Launch the application
2. Select a font family, size, and style
3. Choose output mode (Monochrome or Antialiased)
4. Set the character range (e.g., 0x20 to 0x7F for ASCII)
5. Click "Export..." to save the font as a PCX file
6. Import the PCX file into the Allegro grabber program

## Antialiased Fonts

Antialiased fonts are rendered at 8x the requested size and then scaled down using an 8x8 supersampling grid, providing 64 intensity levels. To use antialiased fonts in Allegro, pass -1 as the color parameter to `textout()` and ensure you have a suitable gradient in your palette.

## Original Credits

Based on TTF -> PCX CONVERTER, version 2.2, April 2002
By Shawn Hargreaves

Qt conversion: 2025

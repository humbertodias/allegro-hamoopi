# Palette Generator - SDL2 Conversion

## Overview

The palette generator has been successfully converted from Allegro 4 to SDL2 using the platform abstraction layer.

## Changes Made

### 1. Platform Abstraction Layer Enhancements
Added new functions to the platform abstraction layer to support the palette generator:

- **`platform_save_bitmap()`** - Saves bitmaps to PNG format (SDL2 doesn't support PCX natively)
- **`platform_get_default_font()`** - Returns a default system font for text rendering
- **`platform_create_sub_bitmap()`** - Creates sub-bitmaps (regions of existing bitmaps)

### 2. New SDL2 Implementation
- Created `PalleteGenerator_SDL2.c` which uses the platform abstraction layer
- All Allegro-specific calls have been replaced with platform-agnostic calls
- The functionality remains identical to the original Allegro version

### 3. Build System
- Updated `CMakeLists.txt` to support both Allegro 4 and SDL2 backends
- SDL2 is now the default backend (can be changed with `-DUSE_SDL2=OFF`)
- Uses pkg-config to properly find and link SDL2 libraries

## Building

### SDL2 Version (Default)
```bash
cd tools/pallete-generator
mkdir -p build && cd build
cmake -DUSE_SDL2=ON ..
make
```

### Allegro 4 Version (Original)
```bash
cd tools/pallete-generator
mkdir -p build && cd build
cmake -DUSE_SDL2=OFF ..
make
```

## Image Format

**Important**: SDL2 uses PNG format instead of PCX. The palette generator will:
- Load `.pcx` files but automatically look for `.png` versions
- Save output as `.png` files when saving `.pcx` filenames

To convert existing PCX files to PNG:
```bash
cd data
for f in *.pcx; do convert "$f" "${f%.pcx}.png"; done
cd system
for f in *.pcx; do convert "$f" "${f%.pcx}.png"; done
```

## Dependencies

### SDL2 Backend
- SDL2 (>= 2.0)
- SDL2_image (>= 2.0)
- SDL2_mixer (>= 2.0)
- SDL2_ttf (>= 2.0)
- libinih (for configuration files)

### Allegro 4 Backend
- Allegro 4 (>= 4.4)

## Usage

The palette generator works the same way in both versions:

1. Place your color palette images in `data/pal0.png` through `data/pal8.png`
2. Run the palette generator: `./PALLETEGEN`
3. Press **F1** to generate a new palette from the input images
4. Press **ESC** to exit
5. The resulting palette will be saved to `data/pallete.png`

## Key Bindings

- **F1** - Generate new palette from input images
- **ESC** - Exit the program
- **Alt+Enter** - Toggle fullscreen mode

## Technical Details

The conversion maintains 100% functional compatibility with the original Allegro version by using the platform abstraction layer. The main benefits of the SDL2 version include:

- Better cross-platform support (Windows, Linux, macOS)
- Modern graphics API
- Active development and maintenance
- Better integration with modern build systems

## Files

- `PalleteGenerator.c` - Original Allegro 4 version (preserved)
- `PalleteGenerator_SDL2.c` - New SDL2 version using platform abstraction
- `CMakeLists.txt` - Build configuration supporting both backends
- `data/` - Input palette images and system resources

# SDL2 Port - Quick Start Guide

## Overview

HAMOOPI now supports both Allegro 4 and SDL2 backends through a platform abstraction layer. You can build with either backend without changing any game code.

## Building

### Allegro 4 (Default)
```bash
cmake -Bbuild
cmake --build build
./HAMOOPI
```

### SDL2
```bash
cmake -Bbuild -DUSE_SDL2=ON
cmake --build build
./HAMOOPI
```

## Dependencies

### For Allegro 4
```bash
sudo apt-get install liballegro4-dev
```

### For SDL2
```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

## Features Implemented

### Graphics
- ✅ Bitmap management (create, load, destroy)
- ✅ Drawing operations (sprites, blits, stretch, masked)
- ✅ Primitives (lines, rectangles, circles, filled shapes)
- ✅ Text rendering with TTF fonts
- ✅ Color manipulation (makecol, getr, getg, getb)
- ✅ Transparency and alpha blending
- ✅ Horizontal/vertical sprite flipping

### Audio
- ✅ Sample loading and playback (WAV, OGG)
- ✅ MIDI/Music support
- ✅ Volume control
- ✅ Multiple audio channels

### Input
- ✅ Keyboard input (full key mapping)
- ✅ Mouse position and buttons
- ✅ Event handling

### System
- ✅ Window management (windowed/fullscreen)
- ✅ Timer callbacks (60 FPS support)
- ✅ Config file parsing (INI format)
- ✅ File utilities
- ✅ Message boxes

## File Structure

```
src/
├── HAMOOPI.c              # Game code (uses platform_compat.h)
├── platform.h             # Platform abstraction API
├── platform_compat.h      # Compatibility macros
├── platform_allegro.c     # Allegro 4 implementation
└── platform_sdl2.c        # SDL2 implementation
```

## Switching Backends

To switch from Allegro 4 to SDL2:
1. Clean build directory: `rm -rf build`
2. Configure with SDL2: `cmake -Bbuild -DUSE_SDL2=ON`
3. Build: `cmake --build build`

To switch back to Allegro 4:
1. Clean build directory: `rm -rf build`
2. Configure (default): `cmake -Bbuild`
3. Build: `cmake --build build`

## Performance

Both backends have minimal overhead:
- Allegro 4: Direct typedef (zero overhead)
- SDL2: Thin wrapper functions (negligible overhead)

## Known Differences

- SDL2 uses PNG/JPG for images (PCX loading attempts PNG fallback)
- SDL2 uses TTF for fonts (PCX fonts need TTF conversion)
- SDL2 uses OGG/MP3 for audio (WAV also supported)
- Rotation/pivot functions are stubs in SDL2 (can be implemented with SDL2_gfx if needed)

## Future Work

If you need advanced features:
- Install SDL2_gfx for rotation support: `sudo apt-get install libsdl2-gfx-dev`
- Uncomment rotation code in platform_sdl2.c
- Add SDL2_gfx to CMakeLists.txt

## Troubleshooting

**SDL2 build fails:**
- Ensure all SDL2 dependencies are installed
- Check CMake output for missing packages

**Assets not loading:**
- SDL2 prefers PNG/OGG formats
- Convert PCX → PNG, MIDI/WAV → OGG if needed

**Performance issues:**
- Use hardware acceleration (enabled by default)
- Check SDL_RENDERER_ACCELERATED in platform_sdl2.c

## Credits

Platform abstraction layer developed to enable easy backend switching while maintaining 100% game code compatibility.

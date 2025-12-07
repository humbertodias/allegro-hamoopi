# Platform Abstraction Layer Documentation

## Overview

This document describes the platform abstraction layer created to decouple the HAMOOPI fighting game engine from Allegro 4. This abstraction allows for easy backend switching (e.g., from Allegro 4 to SDL2) in the future.

## Architecture

The abstraction layer consists of three main components:

### 1. platform.h
The main header file that defines the platform-independent API. It includes:
- Type definitions (PlatformBitmap, PlatformFont, PlatformSample, PlatformMidi)
- Function declarations for all platform operations
- Platform-independent constants

When `USE_ALLEGRO4` is defined, the types are directly aliased to Allegro 4 types (BITMAP, FONT, SAMPLE, MIDI) for maximum compatibility and zero overhead.

### 2. platform_allegro.c
The Allegro 4 implementation of the platform API. This file:
- Implements all platform functions using Allegro 4 calls
- Acts as a thin wrapper around Allegro 4 when `USE_ALLEGRO4` is defined
- Provides a clear template for future backend implementations

### 3. platform_compat.h
A compatibility header that provides backward compatibility with existing Allegro 4 code. When `USE_ALLEGRO4` is defined:
- It doesn't redefine Allegro 4 constants and macros that are already available
- Allows existing code to work without changes
- When `USE_ALLEGRO4` is not defined, it provides macro mappings to the platform API

## API Categories

The abstraction layer covers five main areas:

### 1. System Initialization
- `platform_init()` - Initialize the platform
- `platform_set_uformat()` - Set UTF format
- `platform_install_timer()` - Install timer system
- `platform_install_keyboard()` - Install keyboard input
- `platform_install_mouse()` - Install mouse input
- `platform_set_color_depth()` - Set color depth
- `platform_set_gfx_mode()` - Set graphics mode
- `platform_set_window_title()` - Set window title
- `platform_set_close_button_callback()` - Set close callback
- `platform_install_int_ex()` - Install timer interrupt

### 2. Graphics Operations
- Bitmap management: create, destroy, load, clear
- Drawing: sprites, primitives (lines, rectangles, circles)
- Blitting: regular, stretched, masked
- Transformations: flipping, rotation, pivoting
- Pixel operations: get, put
- Color: `platform_makecol()`

### 3. Text Rendering
- `platform_load_font()` - Load font from file
- `platform_destroy_font()` - Destroy font
- `platform_textout_ex()` - Draw text
- `platform_textout_centre_ex()` - Draw centered text
- `platform_textprintf_ex()` - Draw formatted text
- `platform_textprintf_centre_ex()` - Draw centered formatted text

### 4. Audio
- Sound initialization: `platform_install_sound()`
- Sample management: load, destroy, play, adjust
- MIDI management: load, destroy, play, stop
- Volume control: `platform_set_volume()`

### 5. Configuration Files
- `platform_set_config_file()` - Set config file
- `platform_get_config_int()` - Get integer value
- `platform_get_config_string()` - Get string value
- `platform_set_config_int()` - Set integer value
- `platform_set_config_string()` - Set string value

## Usage

### Current Usage (Allegro 4)

The engine currently uses Allegro 4. To use the abstraction layer with Allegro 4:

```c
#include "platform_compat.h"  // Instead of <allegro.h>
```

The CMakeLists.txt defines `USE_ALLEGRO4`, which makes the platform layer use Allegro 4 directly with zero overhead.

### Building

```bash
cmake -Bbuild
cmake --build build
```

The build system:
1. Defines `-DUSE_ALLEGRO4` compiler flag
2. Compiles `HAMOOPI.c` and `platform_allegro.c`
3. Links with Allegro 4 library

## Migration to SDL2

To migrate to SDL2 in the future:

### Step 1: Create platform_sdl2.c

Create a new file `src/platform_sdl2.c` that implements all the platform functions using SDL2:

```c
// platform_sdl2.c - SDL2 implementation
#include "platform.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// Define SDL2-specific structures
struct PlatformBitmap {
    SDL_Surface *surface;
    SDL_Texture *texture;
};

struct PlatformFont {
    TTF_Font *font;
};

// Implement all platform_* functions using SDL2...
int platform_init(void) {
    return SDL_Init(SDL_INIT_EVERYTHING);
}

PlatformBitmap* platform_create_bitmap(int width, int height) {
    PlatformBitmap *pb = malloc(sizeof(PlatformBitmap));
    pb->surface = SDL_CreateRGBSurface(0, width, height, 32, 
                                       0, 0, 0, 0);
    // ...
    return pb;
}

// ... implement remaining functions
```

### Step 2: Update CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.7)
project(HAMOOPI)

# Choose backend: USE_ALLEGRO4 or USE_SDL2
option(USE_SDL2 "Use SDL2 backend" OFF)

if(USE_SDL2)
    add_definitions(-DUSE_SDL2)
    add_executable(HAMOOPI src/HAMOOPI.c src/platform_sdl2.c)
    
    # Find SDL2
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    
    target_include_directories(HAMOOPI PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(HAMOOPI ${SDL2_LIBRARIES} SDL2_image SDL2_mixer SDL2_ttf m)
else()
    add_definitions(-DUSE_ALLEGRO4)
    add_executable(HAMOOPI src/HAMOOPI.c src/platform_allegro.c)
    
    find_package(Alleg4 4)
    target_include_directories(HAMOOPI PRIVATE ${ALLEGRO_INCLUDE_DIR})
    target_link_libraries(HAMOOPI alleg m)
endif()

# Copy executable to parent folder after build
add_custom_command(TARGET HAMOOPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HAMOOPI> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to parent folder..."
)
```

### Step 3: Update platform.h

Add SDL2 type definitions:

```c
// In platform.h, add:
#ifdef USE_SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// SDL2 structure definitions
struct PlatformBitmap {
    SDL_Surface *surface;
    SDL_Texture *texture;
};

struct PlatformFont {
    TTF_Font *font;
};

struct PlatformSample {
    Mix_Chunk *chunk;
};

struct PlatformMidi {
    Mix_Music *music;
};
#endif
```

### Step 4: Build with SDL2

```bash
cmake -Bbuild -DUSE_SDL2=ON
cmake --build build
```

## Benefits

1. **Separation of Concerns**: Game logic is separated from platform-specific code
2. **Easy Backend Switching**: Change backend by modifying CMakeLists.txt
3. **Minimal Code Changes**: Existing game code works without modifications
4. **Zero Overhead**: When using Allegro 4, types are directly aliased (no wrapper overhead)
5. **Future-Proof**: Ready for SDL2, SDL3, or any other backend
6. **Maintainable**: Clear API boundaries make code easier to understand and maintain

## Testing

After implementing the abstraction layer with Allegro 4:
- ✅ Build system compiles successfully
- ✅ All existing Allegro 4 code works without modifications
- ✅ No performance overhead (direct type aliasing)
- ✅ Clear path for SDL2 migration defined

## Notes

- The current implementation uses direct typedef to Allegro 4 types when `USE_ALLEGRO4` is defined, providing zero overhead
- For SDL2 implementation, wrapper structures will be necessary as SDL2 has a different architecture
- All platform functions are designed to be backend-agnostic
- The compatibility layer (`platform_compat.h`) ensures existing code works seamlessly

## File Structure

```
src/
├── HAMOOPI.c             # Main game code (now uses platform_compat.h)
├── platform.h            # Platform abstraction API
├── platform_compat.h     # Compatibility macros
├── platform_allegro.c    # Allegro 4 implementation
└── platform_sdl2.c       # SDL2 implementation (to be created)
```

## Future Work

- Implement `platform_sdl2.c` for SDL2 backend
- Add support for modern audio formats (MP3, OGG)
- Add support for PNG images
- Implement gamepad/joystick abstraction
- Add automated tests for platform layer

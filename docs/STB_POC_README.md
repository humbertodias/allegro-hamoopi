# STB Backend Proof of Concept

This directory contains a proof-of-concept implementation showing how HAMOOPI can use STB libraries instead of Allegro for image and font handling.

## Files

- `hamoopi_image.h` - Abstract image type interface
- `hamoopi_font.h` - Abstract font type interface  
- `stb_backend_poc.c` - Proof-of-concept STB backend implementation

## What This Demonstrates

1. **Abstract Types**: `HamoopiImage` and `HamoopiFont` hide implementation details
2. **Backend Interface**: Function pointer tables for image and font operations
3. **STB Implementation**: Shows how to implement using STB libraries instead of Allegro

## Required STB Headers

Download these single-header libraries from https://github.com/nothings/stb:

- `stb_image.h` - Image loading (PNG, JPG, BMP, TGA, PSD, GIF, HDR, PIC)
- `stb_image_write.h` - Image writing (PNG, JPG, BMP, TGA)
- `stb_truetype.h` - TrueType font rendering
- `stb_image_resize.h` - Image resizing (optional, for scaling)
- `stb_rect_pack.h` - Rectangle packing (optional, for font atlases)

## Current Status

This is a **proof-of-concept skeleton**. The functions are defined but not fully implemented because:

1. The actual STB headers need to be downloaded
2. Glyph atlas management needs to be implemented for fonts
3. Math library needs to be linked for sqrt()

## How to Complete the Implementation

### Step 1: Download STB Headers

```bash
cd src/
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
wget https://raw.githubusercontent.com/nothings/stb/master/stb_truetype.h
```

### Step 2: Complete Image Loading

In `stb_backend_poc.c`, uncomment and implement:

```c
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static HamoopiImage* stb_load_image(const char* filename) {
    HamoopiImage* img = malloc(sizeof(HamoopiImage));
    img->pixels = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    return img;
}
```

### Step 3: Complete Font Rendering

Font rendering with STB is more complex. You need to:

1. Load TTF file into memory
2. Initialize `stbtt_fontinfo`
3. Create glyph atlas (texture with all characters)
4. Render text by copying glyphs from atlas

Example:

```c
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

static HamoopiFont* stb_load_font(const char* filename, int size) {
    HamoopiFont* font = malloc(sizeof(HamoopiFont));
    
    /* Read entire TTF file */
    FILE* f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    font->ttf_buffer = malloc(fsize);
    fread(font->ttf_buffer, 1, fsize, f);
    fclose(f);
    
    /* Initialize font */
    stbtt_fontinfo* info = malloc(sizeof(stbtt_fontinfo));
    stbtt_InitFont(info, font->ttf_buffer, 0);
    
    font->font_size = size;
    /* Store info in font struct */
    
    return font;
}
```

## Migration Path for HAMOOPI.c

To use these abstract types in HAMOOPI.c, you would need to:

### Replace All Type Declarations

```c
/* Old: */
BITMAP* sprite = load_bitmap("sprite.pcx", NULL);
FONT* font = load_font("font.pcx", NULL, NULL);

/* New: */
HamoopiImage* sprite = image_backend->load_image("sprite.png");
HamoopiFont* font = font_backend->load_font("font.ttf", 16);
```

### Update All Function Calls

```c
/* Old: */
blit(sprite, screen, 0, 0, x, y, w, h);
textout_ex(screen, font, "Hello", x, y, color, -1);

/* New: */
image_backend->blit_image(sprite, screen, 0, 0, x, y, w, h);
font_backend->draw_text(screen, font, "Hello", x, y, color);
```

### Update All Struct Members

```c
/* Old: */
typedef struct {
    BITMAP* sprite;
    FONT* font;
} Player;

/* New: */
typedef struct {
    HamoopiImage* sprite;
    HamoopiFont* font;
} Player;
```

## Estimated Changes

- **~500 BITMAP declarations** → HamoopiImage
- **~50 FONT declarations** → HamoopiFont
- **~2000 function calls** → backend function calls
- **~100 struct members** → new types

## Benefits of Completion

1. **No Allegro Dependency**: Project becomes truly library-agnostic
2. **Modern Image Formats**: Support for PNG, JPG, etc. out of the box
3. **TrueType Fonts**: Use any TTF font, not just bitmap fonts
4. **Cross-Platform**: STB works everywhere
5. **Single Header**: No external library dependencies
6. **Public Domain**: STB is public domain, no licensing concerns

## Challenges

1. **Bitmap Font Compatibility**: HAMOOPI uses .PCX bitmap fonts extensively
   - Need to either convert them or keep Allegro for bitmap fonts
   - Or implement a PCX loader using stb_image

2. **Performance**: STB may be slower than hardware-accelerated Allegro
   - Consider using STB only for loading, Allegro/SDL for rendering
   
3. **Testing**: Need to test every drawing operation for correctness

## Recommendation

Due to the scope (30-40 hours of work), consider a **hybrid approach**:

1. Keep Allegro for now
2. Add STB backend as an option
3. Allow runtime selection of backend
4. Gradually migrate code sections
5. Eventually remove Allegro

This allows incremental progress while maintaining a working system.

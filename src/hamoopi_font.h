#ifndef HAMOOPI_FONT_H
#define HAMOOPI_FONT_H

#include "hamoopi_image.h"

/* Abstract font type - hides implementation details */
typedef struct HamoopiFont HamoopiFont;

/* Font metrics */
typedef struct {
    int ascent;
    int descent;
    int line_gap;
    int max_advance;
} FontMetrics;

/* Glyph information */
typedef struct {
    int advance;
    int bearing_x;
    int bearing_y;
    int width;
    int height;
    unsigned char* bitmap;
} GlyphInfo;

/* Font backend interface */
typedef struct FontBackend {
    /* Font loading/creation */
    HamoopiFont* (*load_font)(const char* filename, int size);
    HamoopiFont* (*load_bitmap_font)(const char* filename);  /* For PCX fonts */
    void (*destroy_font)(HamoopiFont* font);
    
    /* Font metrics */
    void (*get_font_metrics)(HamoopiFont* font, FontMetrics* metrics);
    int (*get_text_width)(HamoopiFont* font, const char* text);
    int (*get_text_height)(HamoopiFont* font);
    
    /* Text rendering */
    void (*draw_text)(HamoopiImage* image, HamoopiFont* font, 
                      const char* text, int x, int y, unsigned int color);
    void (*draw_text_centered)(HamoopiImage* image, HamoopiFont* font,
                               const char* text, int x, int y, unsigned int color);
    
    /* Glyph operations */
    int (*get_glyph_info)(HamoopiFont* font, int codepoint, GlyphInfo* info);
} FontBackend;

#endif /* HAMOOPI_FONT_H */

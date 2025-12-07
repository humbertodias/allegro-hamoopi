/* STB Graphics Backend - Proof of Concept
 * 
 * This demonstrates how to implement the graphics backend using STB libraries
 * instead of Allegro. This is a starting point for Phase 2 migration.
 * 
 * STB Libraries needed:
 * - stb_image.h: https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
 * - stb_image_write.h: https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
 * - stb_truetype.h: https://raw.githubusercontent.com/nothings/stb/master/stb_truetype.h
 */

#include "hamoopi_image.h"
#include "hamoopi_font.h"
#include <stdlib.h>
#include <string.h>

/* Note: STB headers should be downloaded and included here
 * For now, this is a skeleton showing the structure
 */

/* Image implementation using STB */
struct HamoopiImage {
    int width;
    int height;
    int channels;
    unsigned char* pixels;
};

/* Font implementation using STB */
struct HamoopiFont {
    unsigned char* ttf_buffer;  /* TrueType font data */
    int font_size;
    /* stbtt_fontinfo would go here */
};

/* ============================================================================
 * STB IMAGE BACKEND IMPLEMENTATION (Proof of Concept)
 * ============================================================================ */

static HamoopiImage* stb_load_image(const char* filename) {
    /* Implementation would use:
     * unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
     */
    HamoopiImage* img = (HamoopiImage*)malloc(sizeof(HamoopiImage));
    if (!img) return NULL;
    
    /* TODO: Actual STB image loading here */
    img->width = 0;
    img->height = 0;
    img->channels = 4;
    img->pixels = NULL;
    
    return img;
}

static HamoopiImage* stb_create_image(int width, int height, int channels) {
    HamoopiImage* img = (HamoopiImage*)malloc(sizeof(HamoopiImage));
    if (!img) return NULL;
    
    img->width = width;
    img->height = height;
    img->channels = channels;
    img->pixels = (unsigned char*)calloc(width * height * channels, 1);
    
    if (!img->pixels) {
        free(img);
        return NULL;
    }
    
    return img;
}

static void stb_destroy_image(HamoopiImage* image) {
    if (image) {
        if (image->pixels) {
            free(image->pixels);
        }
        free(image);
    }
}

static int stb_image_width(HamoopiImage* image) {
    return image ? image->width : 0;
}

static int stb_image_height(HamoopiImage* image) {
    return image ? image->height : 0;
}

static void stb_blit_image(HamoopiImage* src, HamoopiImage* dest,
                           int src_x, int src_y, int dest_x, int dest_y,
                           int width, int height) {
    if (!src || !dest || !src->pixels || !dest->pixels) return;
    
    /* Simple blit implementation */
    for (int y = 0; y < height; y++) {
        int sy = src_y + y;
        int dy = dest_y + y;
        
        if (sy < 0 || sy >= src->height || dy < 0 || dy >= dest->height) continue;
        
        for (int x = 0; x < width; x++) {
            int sx = src_x + x;
            int dx = dest_x + x;
            
            if (sx < 0 || sx >= src->width || dx < 0 || dx >= dest->width) continue;
            
            int src_idx = (sy * src->width + sx) * src->channels;
            int dest_idx = (dy * dest->width + dx) * dest->channels;
            
            memcpy(&dest->pixels[dest_idx], &src->pixels[src_idx], 
                   src->channels < dest->channels ? src->channels : dest->channels);
        }
    }
}

static void stb_draw_pixel(HamoopiImage* image, int x, int y, unsigned int color) {
    if (!image || !image->pixels) return;
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) return;
    
    int idx = (y * image->width + x) * image->channels;
    
    /* RGBA color */
    image->pixels[idx + 0] = (color >> 16) & 0xFF;  /* R */
    image->pixels[idx + 1] = (color >> 8) & 0xFF;   /* G */
    image->pixels[idx + 2] = (color) & 0xFF;        /* B */
    if (image->channels == 4) {
        image->pixels[idx + 3] = (color >> 24) & 0xFF;  /* A */
    }
}

static unsigned int stb_get_pixel(HamoopiImage* image, int x, int y) {
    if (!image || !image->pixels) return 0;
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) return 0;
    
    int idx = (y * image->width + x) * image->channels;
    
    unsigned int r = image->pixels[idx + 0];
    unsigned int g = image->pixels[idx + 1];
    unsigned int b = image->pixels[idx + 2];
    unsigned int a = (image->channels == 4) ? image->pixels[idx + 3] : 0xFF;
    
    return (a << 24) | (r << 16) | (g << 8) | b;
}

static void stb_draw_rect(HamoopiImage* image, int x1, int y1, int x2, int y2, unsigned int color) {
    if (!image) return;
    
    /* Draw four lines */
    for (int x = x1; x <= x2; x++) {
        stb_draw_pixel(image, x, y1, color);
        stb_draw_pixel(image, x, y2, color);
    }
    for (int y = y1; y <= y2; y++) {
        stb_draw_pixel(image, x1, y, color);
        stb_draw_pixel(image, x2, y, color);
    }
}

static void stb_fill_rect(HamoopiImage* image, int x1, int y1, int x2, int y2, unsigned int color) {
    if (!image) return;
    
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            stb_draw_pixel(image, x, y, color);
        }
    }
}

static void stb_draw_line(HamoopiImage* image, int x1, int y1, int x2, int y2, unsigned int color) {
    /* Bresenham's line algorithm */
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    
    while (1) {
        stb_draw_pixel(image, x1, y1, color);
        
        if (x1 == x2 && y1 == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

static void stb_draw_circle(HamoopiImage* image, int cx, int cy, int radius, unsigned int color) {
    /* Midpoint circle algorithm */
    int x = radius;
    int y = 0;
    int err = 0;
    
    while (x >= y) {
        stb_draw_pixel(image, cx + x, cy + y, color);
        stb_draw_pixel(image, cx + y, cy + x, color);
        stb_draw_pixel(image, cx - y, cy + x, color);
        stb_draw_pixel(image, cx - x, cy + y, color);
        stb_draw_pixel(image, cx - x, cy - y, color);
        stb_draw_pixel(image, cx - y, cy - x, color);
        stb_draw_pixel(image, cx + y, cy - x, color);
        stb_draw_pixel(image, cx + x, cy - y, color);
        
        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

static void stb_fill_circle(HamoopiImage* image, int cx, int cy, int radius, unsigned int color) {
    /* Fill circle by drawing horizontal lines */
    for (int y = -radius; y <= radius; y++) {
        int x = (int)(sqrt(radius * radius - y * y) + 0.5);
        stb_draw_line(image, cx - x, cy + y, cx + x, cy + y, color);
    }
}

static unsigned int stb_make_color(int r, int g, int b, int a) {
    return (a << 24) | (r << 16) | (g << 8) | b;
}

static int stb_save_image(HamoopiImage* image, const char* filename) {
    if (!image || !image->pixels) return 0;
    
    /* Implementation would use:
     * stbi_write_png(filename, image->width, image->height, image->channels, 
     *                image->pixels, image->width * image->channels);
     */
    return 0;  /* TODO: Actual save implementation */
}

/* Create STB image backend instance */
static ImageBackend stb_image_backend = {
    stb_load_image,
    stb_create_image,
    stb_destroy_image,
    stb_image_width,
    stb_image_height,
    stb_blit_image,
    stb_draw_pixel,
    stb_get_pixel,
    stb_draw_rect,
    stb_fill_rect,
    stb_draw_line,
    stb_draw_circle,
    stb_fill_circle,
    stb_make_color,
    stb_save_image
};

/* ============================================================================
 * STB FONT BACKEND IMPLEMENTATION (Proof of Concept)
 * ============================================================================ */

static HamoopiFont* stb_load_font(const char* filename, int size) {
    /* Implementation would use stb_truetype */
    HamoopiFont* font = (HamoopiFont*)malloc(sizeof(HamoopiFont));
    if (!font) return NULL;
    
    /* TODO: Load TTF file and initialize stbtt_fontinfo */
    font->ttf_buffer = NULL;
    font->font_size = size;
    
    return font;
}

static HamoopiFont* stb_load_bitmap_font(const char* filename) {
    /* Load bitmap font (PCX format) */
    /* This would need to be converted or we keep Allegro for bitmap fonts */
    return NULL;
}

static void stb_destroy_font(HamoopiFont* font) {
    if (font) {
        if (font->ttf_buffer) {
            free(font->ttf_buffer);
        }
        free(font);
    }
}

static void stb_get_font_metrics(HamoopiFont* font, FontMetrics* metrics) {
    /* Implementation would use stbtt_GetFontVMetrics */
    if (metrics) {
        metrics->ascent = 0;
        metrics->descent = 0;
        metrics->line_gap = 0;
        metrics->max_advance = 0;
    }
}

static int stb_get_text_width(HamoopiFont* font, const char* text) {
    /* Implementation would measure text width using stbtt */
    return 0;
}

static int stb_get_text_height(HamoopiFont* font) {
    return font ? font->font_size : 0;
}

static void stb_draw_text(HamoopiImage* image, HamoopiFont* font,
                          const char* text, int x, int y, unsigned int color) {
    /* Implementation would render glyphs using stbtt_BakeFontBitmap or similar */
    /* This is complex and requires glyph atlas management */
}

static void stb_draw_text_centered(HamoopiImage* image, HamoopiFont* font,
                                   const char* text, int x, int y, unsigned int color) {
    int text_width = stb_get_text_width(font, text);
    stb_draw_text(image, font, text, x - text_width / 2, y, color);
}

static int stb_get_glyph_info(HamoopiFont* font, int codepoint, GlyphInfo* info) {
    /* Implementation would use stbtt_GetCodepointBitmapBox and related functions */
    return 0;
}

/* Create STB font backend instance */
static FontBackend stb_font_backend = {
    stb_load_font,
    stb_load_bitmap_font,
    stb_destroy_font,
    stb_get_font_metrics,
    stb_get_text_width,
    stb_get_text_height,
    stb_draw_text,
    stb_draw_text_centered,
    stb_get_glyph_info
};

/* ============================================================================
 * PUBLIC API
 * ============================================================================ */

ImageBackend* get_stb_image_backend(void) {
    return &stb_image_backend;
}

FontBackend* get_stb_font_backend(void) {
    return &stb_font_backend;
}

/* STB Graphics Backend - Full Implementation
 * 
 * This implements the graphics backend using STB libraries instead of Allegro.
 */

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_ONLY_BMP
#define STBI_ONLY_TGA
#define STBI_ONLY_JPEG
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include "hamoopi_image.h"
#include "hamoopi_font.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

/* ============================================================================
 * IMAGE STRUCTURE
 * ============================================================================ */

struct HamoopiImage {
    int width;
    int height;
    int channels;
    unsigned char* pixels;
};

/* ============================================================================
 * FONT STRUCTURE
 * ============================================================================ */

#define FONT_ATLAS_WIDTH 512
#define FONT_ATLAS_HEIGHT 512
#define FIRST_CHAR 32
#define NUM_CHARS 95

struct HamoopiFont {
    unsigned char* ttf_buffer;
    stbtt_fontinfo font_info;
    int font_size;
    float scale;
    
    /* Bitmap atlas for baked glyphs */
    unsigned char* atlas;
    int atlas_width;
    int atlas_height;
    stbtt_bakedchar cdata[NUM_CHARS];
    
    /* Metrics */
    int ascent;
    int descent;
    int line_gap;
};

/* ============================================================================
 * STB IMAGE BACKEND IMPLEMENTATION
 * ============================================================================ */

static HamoopiImage* stb_load_image(const char* filename) {
    HamoopiImage* img = (HamoopiImage*)malloc(sizeof(HamoopiImage));
    if (!img) return NULL;
    
    img->pixels = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    
    if (!img->pixels) {
        free(img);
        return NULL;
    }
    
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
            stbi_image_free(image->pixels);
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
            
            int copy_channels = (src->channels < dest->channels) ? src->channels : dest->channels;
            memcpy(&dest->pixels[dest_idx], &src->pixels[src_idx], copy_channels);
        }
    }
}

static void stb_draw_pixel(HamoopiImage* image, int x, int y, unsigned int color) {
    if (!image || !image->pixels) return;
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) return;
    
    int idx = (y * image->width + x) * image->channels;
    
    unsigned int r = (color >> 16) & 0xFF;
    unsigned int g = (color >> 8) & 0xFF;
    unsigned int b = color & 0xFF;
    unsigned int a = (color >> 24) & 0xFF;
    
    if (image->channels >= 1) image->pixels[idx + 0] = r;
    if (image->channels >= 2) image->pixels[idx + 1] = g;
    if (image->channels >= 3) image->pixels[idx + 2] = b;
    if (image->channels >= 4) image->pixels[idx + 3] = a;
}

static unsigned int stb_get_pixel(HamoopiImage* image, int x, int y) {
    if (!image || !image->pixels) return 0;
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) return 0;
    
    int idx = (y * image->width + x) * image->channels;
    
    unsigned int r = (image->channels >= 1) ? image->pixels[idx + 0] : 0;
    unsigned int g = (image->channels >= 2) ? image->pixels[idx + 1] : 0;
    unsigned int b = (image->channels >= 3) ? image->pixels[idx + 2] : 0;
    unsigned int a = (image->channels >= 4) ? image->pixels[idx + 3] : 0xFF;
    
    return (a << 24) | (r << 16) | (g << 8) | b;
}

static void stb_draw_rect(HamoopiImage* image, int x1, int y1, int x2, int y2, unsigned int color) {
    if (!image) return;
    
    for (int x = x1; x <= x2; x++) {
        stb_draw_pixel(image, x, y1, color);
        stb_draw_pixel(image, x, y2, color);
    }
    for (int y = y1 + 1; y < y2; y++) {
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
    for (int y = -radius; y <= radius; y++) {
        int x = (int)(sqrt((double)(radius * radius - y * y)) + 0.5);
        stb_draw_line(image, cx - x, cy + y, cx + x, cy + y, color);
    }
}

static unsigned int stb_make_color(int r, int g, int b, int a) {
    return (a << 24) | (r << 16) | (g << 8) | b;
}

static int stb_save_image(HamoopiImage* image, const char* filename) {
    if (!image || !image->pixels) return 0;
    
    const char* ext = strrchr(filename, '.');
    if (!ext) return 0;
    
    if (strcmp(ext, ".png") == 0) {
        return stbi_write_png(filename, image->width, image->height, 
                             image->channels, image->pixels, 
                             image->width * image->channels);
    } else if (strcmp(ext, ".bmp") == 0) {
        return stbi_write_bmp(filename, image->width, image->height, 
                             image->channels, image->pixels);
    } else if (strcmp(ext, ".tga") == 0) {
        return stbi_write_tga(filename, image->width, image->height, 
                             image->channels, image->pixels);
    } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
        return stbi_write_jpg(filename, image->width, image->height, 
                             image->channels, image->pixels, 90);
    }
    
    return 0;
}

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
 * STB FONT BACKEND IMPLEMENTATION
 * ============================================================================ */

static HamoopiFont* stb_load_font(const char* filename, int size) {
    /* Read TTF file */
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;
    
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    HamoopiFont* font = (HamoopiFont*)malloc(sizeof(HamoopiFont));
    if (!font) {
        fclose(f);
        return NULL;
    }
    
    font->ttf_buffer = (unsigned char*)malloc(fsize);
    if (!font->ttf_buffer) {
        free(font);
        fclose(f);
        return NULL;
    }
    
    fread(font->ttf_buffer, 1, fsize, f);
    fclose(f);
    
    /* Initialize font */
    if (!stbtt_InitFont(&font->font_info, font->ttf_buffer, 0)) {
        free(font->ttf_buffer);
        free(font);
        return NULL;
    }
    
    font->font_size = size;
    font->scale = stbtt_ScaleForPixelHeight(&font->font_info, (float)size);
    
    /* Get metrics */
    stbtt_GetFontVMetrics(&font->font_info, &font->ascent, &font->descent, &font->line_gap);
    font->ascent = (int)(font->ascent * font->scale);
    font->descent = (int)(font->descent * font->scale);
    font->line_gap = (int)(font->line_gap * font->scale);
    
    /* Bake font atlas */
    font->atlas_width = FONT_ATLAS_WIDTH;
    font->atlas_height = FONT_ATLAS_HEIGHT;
    font->atlas = (unsigned char*)malloc(font->atlas_width * font->atlas_height);
    
    stbtt_BakeFontBitmap(font->ttf_buffer, 0, (float)size, 
                        font->atlas, font->atlas_width, font->atlas_height,
                        FIRST_CHAR, NUM_CHARS, font->cdata);
    
    return font;
}

static HamoopiFont* stb_load_bitmap_font(const char* filename) {
    /* STB doesn't support bitmap fonts directly */
    /* Would need to load as image and parse manually */
    return NULL;
}

static void stb_destroy_font(HamoopiFont* font) {
    if (font) {
        if (font->ttf_buffer) free(font->ttf_buffer);
        if (font->atlas) free(font->atlas);
        free(font);
    }
}

static void stb_get_font_metrics(HamoopiFont* font, FontMetrics* metrics) {
    if (!font || !metrics) return;
    
    metrics->ascent = font->ascent;
    metrics->descent = font->descent;
    metrics->line_gap = font->line_gap;
    metrics->max_advance = font->font_size; /* Approximate */
}

static int stb_get_text_width(HamoopiFont* font, const char* text) {
    if (!font || !text) return 0;
    
    float x = 0;
    while (*text) {
        if (*text >= FIRST_CHAR && *text < FIRST_CHAR + NUM_CHARS) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(font->cdata, font->atlas_width, font->atlas_height,
                             *text - FIRST_CHAR, &x, NULL, &q, 1);
        }
        text++;
    }
    
    return (int)x;
}

static int stb_get_text_height(HamoopiFont* font) {
    return font ? font->font_size : 0;
}

static void stb_draw_text(HamoopiImage* image, HamoopiFont* font,
                          const char* text, int x, int y, unsigned int color) {
    if (!image || !font || !text) return;
    
    float fx = (float)x;
    float fy = (float)y;
    
    while (*text) {
        if (*text >= FIRST_CHAR && *text < FIRST_CHAR + NUM_CHARS) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(font->cdata, font->atlas_width, font->atlas_height,
                             *text - FIRST_CHAR, &fx, &fy, &q, 1);
            
            /* Draw glyph from atlas */
            int gx0 = (int)q.x0;
            int gy0 = (int)q.y0;
            int gx1 = (int)q.x1;
            int gy1 = (int)q.y1;
            
            int s0 = (int)(q.s0 * font->atlas_width);
            int t0 = (int)(q.t0 * font->atlas_height);
            int s1 = (int)(q.s1 * font->atlas_width);
            int t1 = (int)(q.t1 * font->atlas_height);
            
            for (int gy = gy0; gy < gy1; gy++) {
                for (int gx = gx0; gx < gx1; gx++) {
                    int sx = s0 + (gx - gx0);
                    int sy = t0 + (gy - gy0);
                    
                    if (sx >= 0 && sx < font->atlas_width && sy >= 0 && sy < font->atlas_height) {
                        unsigned char alpha = font->atlas[sy * font->atlas_width + sx];
                        if (alpha > 0) {
                            unsigned int pixel_color = (color & 0x00FFFFFF) | (alpha << 24);
                            stb_draw_pixel(image, gx, gy, pixel_color);
                        }
                    }
                }
            }
        }
        text++;
    }
}

static void stb_draw_text_centered(HamoopiImage* image, HamoopiFont* font,
                                   const char* text, int x, int y, unsigned int color) {
    int text_width = stb_get_text_width(font, text);
    stb_draw_text(image, font, text, x - text_width / 2, y, color);
}

static int stb_get_glyph_info(HamoopiFont* font, int codepoint, GlyphInfo* info) {
    if (!font || !info) return 0;
    
    int glyph_index = stbtt_FindGlyphIndex(&font->font_info, codepoint);
    if (glyph_index == 0) return 0;
    
    int advance, bearing;
    stbtt_GetGlyphHMetrics(&font->font_info, glyph_index, &advance, &bearing);
    
    info->advance = (int)(advance * font->scale);
    info->bearing_x = (int)(bearing * font->scale);
    
    int x0, y0, x1, y1;
    stbtt_GetGlyphBitmapBox(&font->font_info, glyph_index, font->scale, font->scale,
                           &x0, &y0, &x1, &y1);
    
    info->width = x1 - x0;
    info->height = y1 - y0;
    info->bearing_y = -y0;
    info->bitmap = NULL; /* Would need to render separately */
    
    return 1;
}

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

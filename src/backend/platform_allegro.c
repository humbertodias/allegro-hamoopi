// platform_allegro.c - Allegro 4 implementation of platform abstraction layer

#include "platform.h"
#include <stdarg.h>
#include <string.h>
#include <png.h>

// ============================================================================
// INITIALIZATION & SYSTEM
// ============================================================================

int platform_init(void) {
    return allegro_init();
}

void platform_set_uformat(int format) {
    // For Allegro 4, we respect the format parameter
    set_uformat(format);
}

int platform_install_timer(void) {
    return install_timer();
}

int platform_install_keyboard(void) {
    return install_keyboard();
}

int platform_install_mouse(void) {
    return install_mouse();
}

void platform_set_color_depth(int depth) {
    set_color_depth(depth);
}

int platform_set_gfx_mode(int mode, int width, int height, int v_width, int v_height) {
    int allegro_mode;
    if (mode == PGFX_AUTODETECT_FULLSCREEN) {
        allegro_mode = GFX_AUTODETECT_FULLSCREEN;
    } else {
        allegro_mode = GFX_AUTODETECT_WINDOWED;
    }
    return set_gfx_mode(allegro_mode, width, height, v_width, v_height);
}

void platform_set_window_title(const char *title) {
    set_window_title(title);
}

void platform_set_close_button_callback(void (*callback)(void)) {
    set_close_button_callback(callback);
}

void platform_install_int_ex(void (*callback)(void), int bps) {
    install_int_ex(callback, BPS_TO_TIMER(bps));
}

volatile char* platform_get_key_state(void) {
    return key;
}

PlatformBitmap* platform_get_screen(void) {
    return screen;
}

// ============================================================================
// GRAPHICS - BITMAP OPERATIONS
// ============================================================================

// Helper function to load PNG files and convert to Allegro BITMAP in memory
static BITMAP* load_png_to_bitmap(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        return NULL;
    }

    // Check PNG signature
    unsigned char header[8];
    if (fread(header, 1, 8, fp) != 8 || png_sig_cmp(header, 0, 8) != 0) {
        fclose(fp);
        return NULL;
    }

    // Initialize PNG structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        return NULL;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(fp);
        return NULL;
    }

    // Set error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return NULL;
    }

    // Initialize PNG reading
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    // Get image information
    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    // Transform to RGBA8 format
    if (bit_depth == 16)
        png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    // Allocate row pointers
    png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    if (!row_pointers) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return NULL;
    }

    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));
        if (!row_pointers[y]) {
            for (int i = 0; i < y; i++)
                free(row_pointers[i]);
            free(row_pointers);
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return NULL;
        }
    }

    // Read the image data
    png_read_image(png_ptr, row_pointers);

    // Create Allegro bitmap
    BITMAP *bmp = create_bitmap(width, height);
    if (!bmp) {
        for (int y = 0; y < height; y++)
            free(row_pointers[y]);
        free(row_pointers);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return NULL;
    }

    // Convert PNG data to Allegro bitmap
    // PNG data is in RGBA format, we need to convert to Allegro's format
    for (int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            int r = px[0];
            int g = px[1];
            int b = px[2];
            int a = px[3];
            
            // In Allegro and this game engine, magenta (255, 0, 255) is the standard
            // color key for transparency. Convert fully transparent pixels or existing
            // magenta pixels to this color key format. Note: This means solid magenta
            // pixels in the PNG will also be transparent, which is the expected behavior
            // for this game engine where magenta is reserved for transparency.
            if (a == 0 || (r == 255 && g == 0 && b == 255)) {
                putpixel(bmp, x, y, makecol(255, 0, 255));
            } else {
                putpixel(bmp, x, y, makecol(r, g, b));
            }
        }
    }

    // Cleanup
    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);

    return bmp;
}

PlatformBitmap* platform_create_bitmap(int width, int height) {
    return create_bitmap(width, height);
}

void platform_destroy_bitmap(PlatformBitmap *bitmap) {
    if (bitmap) {
        destroy_bitmap(bitmap);
    }
}

PlatformBitmap* platform_load_bitmap(const char *filename, void *palette) {
    if (!filename) {
        return NULL;
    }

    // Check if the file has a .png extension (case-insensitive)
    const char *ext = strrchr(filename, '.');
    if (ext && (strcmp(ext, ".png") == 0 || strcmp(ext, ".PNG") == 0)) {
        // Load PNG file and convert to Allegro bitmap in memory
        return load_png_to_bitmap(filename);
    }

    // For non-PNG files, use Allegro's native load_bitmap (supports PCX, BMP, etc.)
    return load_bitmap(filename, palette);
}

void platform_clear_bitmap(PlatformBitmap *bitmap) {
    if (bitmap) {
        clear_bitmap(bitmap);
    }
}

void platform_clear_to_color(PlatformBitmap *bitmap, PlatformColor color) {
    if (bitmap) {
        clear_to_color(bitmap, color);
    }
}

void platform_draw_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && src) {
        draw_sprite(dest, src, x, y);
    }
}

void platform_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                          int src_x, int src_y, int src_w, int src_h,
                          int dest_x, int dest_y, int dest_w, int dest_h) {
    if (src && dest) {
        stretch_blit(src, dest, src_x, src_y, src_w, src_h, dest_x, dest_y, dest_w, dest_h);
    }
}

void platform_blit(PlatformBitmap *src, PlatformBitmap *dest,
                  int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    if (src && dest) {
        blit(src, dest, src_x, src_y, dest_x, dest_y, w, h);
    }
}

void platform_masked_blit(PlatformBitmap *src, PlatformBitmap *dest,
                         int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    if (src && dest) {
        masked_blit(src, dest, src_x, src_y, dest_x, dest_y, w, h);
    }
}

void platform_draw_sprite_h_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && src) {
        draw_sprite_h_flip(dest, src, x, y);
    }
}

void platform_draw_sprite_v_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && src) {
        draw_sprite_v_flip(dest, src, x, y);
    }
}

void platform_draw_sprite_vh_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && src) {
        draw_sprite_vh_flip(dest, src, x, y);
    }
}

void platform_rotate_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                           int x, int y, int angle) {
    if (dest && src) {
        rotate_sprite(dest, src, x, y, itofix(angle));
    }
}

void platform_pivot_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                          int x, int y, int cx, int cy, int angle) {
    if (dest && src) {
        pivot_sprite(dest, src, x, y, cx, cy, itofix(angle));
    }
}

PlatformColor platform_getpixel(PlatformBitmap *bitmap, int x, int y) {
    if (bitmap) {
        return getpixel(bitmap, x, y);
    }
    return 0;
}

void platform_putpixel(PlatformBitmap *bitmap, int x, int y, PlatformColor color) {
    if (bitmap) {
        putpixel(bitmap, x, y, color);
    }
}

// ============================================================================
// GRAPHICS - PRIMITIVES
// ============================================================================

void platform_line(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap) {
        line(bitmap, x1, y1, x2, y2, color);
    }
}

void platform_rect(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap) {
        rect(bitmap, x1, y1, x2, y2, color);
    }
}

void platform_rectfill(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap) {
        rectfill(bitmap, x1, y1, x2, y2, color);
    }
}

void platform_circle(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color) {
    if (bitmap) {
        circle(bitmap, x, y, radius, color);
    }
}

void platform_circlefill(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color) {
    if (bitmap) {
        circlefill(bitmap, x, y, radius, color);
    }
}

PlatformColor platform_makecol(int r, int g, int b) {
    return makecol(r, g, b);
}

int platform_bitmap_width(PlatformBitmap *bitmap) {
    return bitmap ? bitmap->w : 0;
}

int platform_bitmap_height(PlatformBitmap *bitmap) {
    return bitmap ? bitmap->h : 0;
}

// ============================================================================
// GRAPHICS - TEXT
// ============================================================================

PlatformFont* platform_load_font(const char *filename, void *palette, void *param) {
    return load_font(filename, palette, param);
}

void platform_destroy_font(PlatformFont *font) {
    if (font) {
        destroy_font(font);
    }
}

void platform_textout_ex(PlatformBitmap *bitmap, PlatformFont *font,
                        const char *text, int x, int y,
                        PlatformColor color, PlatformColor bg) {
    if (bitmap && font) {
        textout_ex(bitmap, font, text, x, y, color, bg);
    }
}

void platform_textout_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                               const char *text, int x, int y,
                               PlatformColor color, PlatformColor bg) {
    if (bitmap && font) {
        textout_centre_ex(bitmap, font, text, x, y, color, bg);
    }
}

void platform_textprintf_ex(PlatformBitmap *bitmap, PlatformFont *font,
                           int x, int y, PlatformColor color, PlatformColor bg,
                           const char *format, ...) {
    if (bitmap && font) {
        va_list args;
        va_start(args, format);
        char buffer[1024];
        int written = vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        // Ensure null termination even if truncated
        if (written >= (int)sizeof(buffer)) {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        textout_ex(bitmap, font, buffer, x, y, color, bg);
    }
}

void platform_textprintf_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                                  int x, int y, PlatformColor color, PlatformColor bg,
                                  const char *format, ...) {
    if (bitmap && font) {
        va_list args;
        va_start(args, format);
        char buffer[1024];
        int written = vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        // Ensure null termination even if truncated
        if (written >= (int)sizeof(buffer)) {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        textout_centre_ex(bitmap, font, buffer, x, y, color, bg);
    }
}

// ============================================================================
// AUDIO
// ============================================================================

int platform_install_sound(int digi, int midi, const char *cfg) {
    // For Allegro 4, pass through parameters but use autodetect if they are the platform-independent values
    int digi_mode = (digi == PDIGI_AUTODETECT) ? DIGI_AUTODETECT : digi;
    int midi_mode = (midi == PMIDI_AUTODETECT) ? MIDI_AUTODETECT : midi;
    return install_sound(digi_mode, midi_mode, cfg);
}

PlatformSample* platform_load_sample(const char *filename) {
    return load_sample(filename);
}

PlatformMidi* platform_load_midi(const char *filename) {
    return load_midi(filename);
}

void platform_destroy_sample(PlatformSample *sample) {
    if (sample) {
        destroy_sample(sample);
    }
}

void platform_destroy_midi(PlatformMidi *midi) {
    if (midi) {
        destroy_midi(midi);
    }
}

int platform_play_sample(PlatformSample *sample, int vol, int pan, int freq, int loop) {
    if (sample) {
        return play_sample(sample, vol, pan, freq, loop);
    }
    return -1;
}

int platform_play_midi(PlatformMidi *midi, int loop) {
    if (midi) {
        return play_midi(midi, loop);
    }
    return -1;
}

void platform_stop_midi(void) {
    stop_midi();
}

void platform_set_volume(int digi, int midi) {
    set_volume(digi, midi);
}

void platform_adjust_sample(PlatformSample *sample, int vol, int pan, int freq, int loop) {
    if (sample) {
        adjust_sample(sample, vol, pan, freq, loop);
    }
}

// ============================================================================
// CONFIG FILE
// ============================================================================

void platform_set_config_file(const char *filename) {
    set_config_file(filename);
}

int platform_get_config_int(const char *section, const char *key, int default_value) {
    return get_config_int(section, key, default_value);
}

const char* platform_get_config_string(const char *section, const char *key, const char *default_value) {
    return get_config_string(section, key, default_value);
}

void platform_set_config_int(const char *section, const char *key, int value) {
    set_config_int(section, key, value);
}

void platform_set_config_string(const char *section, const char *key, const char *value) {
    set_config_string(section, key, value);
}


int platform_file_exists(const char *filename) {
    return exists(filename);
}

float platform_get_config_float(const char *section, const char *key, float default_value) {
    const char *str = get_config_string(section, key, "");
    if (str && *str) {
        return atof(str);
    }
    return default_value;
}

int platform_getr(PlatformColor color) {
    return getr(color);
}

int platform_getg(PlatformColor color) {
    return getg(color);
}

int platform_getb(PlatformColor color) {
    return getb(color);
}

void platform_rest(int milliseconds) {
    rest(milliseconds);
}

void platform_drawing_mode(int mode, void *pattern, int x_anchor, int y_anchor) {
    drawing_mode(mode, pattern, x_anchor, y_anchor);
}

void platform_masked_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                                  int src_x, int src_y, int src_w, int src_h,
                                  int dest_x, int dest_y, int dest_w, int dest_h) {
    if (src && dest) {
        masked_stretch_blit(src, dest, src_x, src_y, src_w, src_h, dest_x, dest_y, dest_w, dest_h);
    }
}

void platform_clear(PlatformBitmap *bitmap) {
    if (bitmap) {
        clear(bitmap);
    }
}

void platform_clear_keybuf(void) {
    clear_keybuf();
}

void platform_set_trans_blender(int r, int g, int b, int a) {
    set_trans_blender(r, g, b, a);
}

void platform_textprintf_right_ex(PlatformBitmap *bitmap, PlatformFont *font,
                                  int x, int y, PlatformColor color, PlatformColor bg,
                                  const char *format, ...) {
    if (bitmap && font) {
        va_list args;
        va_start(args, format);
        char buffer[1024];
        int written = vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        if (written >= (int)sizeof(buffer)) {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        textprintf_right_ex(bitmap, font, x, y, color, bg, "%s", buffer);
    }
}

void platform_alert_message(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    allegro_message("%s", buffer);
}

void platform_stretch_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y, int w, int h) {
    if (dest && src) {
        stretch_sprite(dest, src, x, y, w, h);
    }
}
void platform_solid_mode(void) { solid_mode(); }
void platform_draw_trans_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) { if (dest && src) draw_trans_sprite(dest, src, x, y); }

void platform_present_screen(void) {
    // Allegro 4 doesn't need explicit screen presentation
    // The screen buffer is automatically displayed
}

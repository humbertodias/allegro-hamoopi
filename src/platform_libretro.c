// platform_libretro.c - Libretro implementation of platform abstraction layer
// This allows HAMOOPI to run as a libretro core in RetroArch and other frontends

#include "platform.h"
#include "libretro.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

// ============================================================================
// LIBRETRO GLOBAL STATE
// ============================================================================

static retro_video_refresh_t video_cb = NULL;
static retro_audio_sample_t audio_cb = NULL;
static retro_audio_sample_batch_t audio_batch_cb = NULL;
static retro_environment_t environ_cb = NULL;
static retro_input_poll_t input_poll_cb = NULL;
static retro_input_state_t input_state_cb = NULL;

// Screen buffer
static PlatformBitmap *g_screen = NULL;
static uint32_t *g_framebuffer = NULL;
static int g_screen_width = 640;
static int g_screen_height = 480;

// Keyboard state array (Allegro-style indexed)
static volatile char g_key_state[256];

// Mouse state (exported for compatibility)
volatile int platform_mouse_x = 0;
volatile int platform_mouse_y = 0;
volatile int platform_mouse_b = 0;

// Timer state
static void (*g_timer_callback)(void) = NULL;
static int g_timer_interval = 0;
static int g_timer_counter = 0;

// Close button callback
static void (*g_close_callback)(void) = NULL;

// Config file state
static char g_config_file[512] = "config.ini";

// ============================================================================
// LIBRETRO INPUT MAPPING
// ============================================================================

// Transparency color (magenta) - standard Allegro/HAMOOPI convention
#define TRANSPARENCY_COLOR_MAGENTA 0x00FF00FF

// Map libretro joypad buttons to platform keys
static const int libretro_to_platform_key_map[RETRO_DEVICE_ID_JOYPAD_R3 + 1] = {
    [RETRO_DEVICE_ID_JOYPAD_B] = PKEY_Z,      // Button B -> Z (punch)
    [RETRO_DEVICE_ID_JOYPAD_Y] = PKEY_X,      // Button Y -> X (punch)
    [RETRO_DEVICE_ID_JOYPAD_SELECT] = PKEY_5,  // Select -> Coin
    [RETRO_DEVICE_ID_JOYPAD_START] = PKEY_1,   // Start -> Start
    [RETRO_DEVICE_ID_JOYPAD_UP] = PKEY_UP,
    [RETRO_DEVICE_ID_JOYPAD_DOWN] = PKEY_DOWN,
    [RETRO_DEVICE_ID_JOYPAD_LEFT] = PKEY_LEFT,
    [RETRO_DEVICE_ID_JOYPAD_RIGHT] = PKEY_RIGHT,
    [RETRO_DEVICE_ID_JOYPAD_A] = PKEY_C,      // Button A -> C (kick)
    [RETRO_DEVICE_ID_JOYPAD_X] = PKEY_A,      // Button X -> A (punch)
    [RETRO_DEVICE_ID_JOYPAD_L] = PKEY_S,      // L -> S (kick)
    [RETRO_DEVICE_ID_JOYPAD_R] = PKEY_D,      // R -> D (kick)
    // All other entries default to 0 (unmapped)
};

// ============================================================================
// LIBRETRO CORE IMPLEMENTATION
// ============================================================================

void retro_init(void)
{
    // Initialize screen buffer
    g_framebuffer = (uint32_t*)calloc(g_screen_width * g_screen_height, sizeof(uint32_t));
    
    g_screen = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (g_screen) {
        g_screen->surface = g_framebuffer;
        g_screen->w = g_screen_width;
        g_screen->h = g_screen_height;
    }
    
    // Initialize key state
    memset((void*)g_key_state, 0, sizeof(g_key_state));
}

void retro_deinit(void)
{
    if (g_framebuffer) {
        free(g_framebuffer);
        g_framebuffer = NULL;
    }
    if (g_screen) {
        free(g_screen);
        g_screen = NULL;
    }
}

unsigned retro_api_version(void)
{
    return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
    // Accept any device
}

void retro_get_system_info(struct retro_system_info *info)
{
    memset(info, 0, sizeof(*info));
    info->library_name     = "HAMOOPI";
    info->library_version  = "0.001A";
    info->need_fullpath    = false;
    info->valid_extensions = "ham|bin";
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
    info->timing.fps = 60.0;
    info->timing.sample_rate = 44100.0;
    
    info->geometry.base_width   = g_screen_width;
    info->geometry.base_height  = g_screen_height;
    info->geometry.max_width    = g_screen_width;
    info->geometry.max_height   = g_screen_height;
    info->geometry.aspect_ratio = (float)g_screen_width / (float)g_screen_height;
}

void retro_set_environment(retro_environment_t cb)
{
    environ_cb = cb;
    
    bool no_content = true;
    cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_content);
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
    audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
    audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
    input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb)
{
    input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
    video_cb = cb;
}

void retro_reset(void)
{
    // Reset game state if needed
}

static void update_input(void)
{
    if (!input_poll_cb || !input_state_cb)
        return;
    
    input_poll_cb();
    
    // Clear key state
    memset((void*)g_key_state, 0, sizeof(g_key_state));
    
    // Poll player 1 joypad
    for (int i = 0; i <= RETRO_DEVICE_ID_JOYPAD_R3; i++) {
        if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, i)) {
            int key_index = libretro_to_platform_key_map[i];
            if (key_index > 0 && key_index < 256) {
                g_key_state[key_index] = 1;
            }
        }
    }
    
    // Also map keyboard for player 1
    // Arrow keys
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_UP))
        g_key_state[PKEY_UP] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_DOWN))
        g_key_state[PKEY_DOWN] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_LEFT))
        g_key_state[PKEY_LEFT] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_RIGHT))
        g_key_state[PKEY_RIGHT] = 1;
    
    // Action buttons (Z, X, C for punches/kicks)
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_z))
        g_key_state[PKEY_Z] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_x))
        g_key_state[PKEY_X] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_c))
        g_key_state[PKEY_C] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_a))
        g_key_state[PKEY_A] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_s))
        g_key_state[PKEY_S] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_d))
        g_key_state[PKEY_D] = 1;
    
    // Start/Select
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_RETURN))
        g_key_state[PKEY_ENTER] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_ESCAPE))
        g_key_state[PKEY_ESC] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_SPACE))
        g_key_state[PKEY_SPACE] = 1;
    
    // F keys for debug
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_F1))
        g_key_state[PKEY_F1] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_F2))
        g_key_state[PKEY_F2] = 1;
    if (input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, RETROK_F3))
        g_key_state[PKEY_F3] = 1;
}

void retro_run(void)
{
    // Update input state
    update_input();
    
    // Call timer callback if set
    if (g_timer_callback && g_timer_interval > 0) {
        g_timer_counter++;
        if (g_timer_counter >= g_timer_interval) {
            g_timer_callback();
            g_timer_counter = 0;
        }
    }
    
    // NOTE: The main game loop is called externally from HAMOOPI.c
    // This function just updates the framebuffer to the frontend
    
    // Send video frame
    if (video_cb && g_framebuffer) {
        video_cb(g_framebuffer, g_screen_width, g_screen_height, g_screen_width * sizeof(uint32_t));
    }
}

bool retro_load_game(const struct retro_game_info *info)
{
    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
        return false;
    }
    
    // Game can run without content (uses internal data folder)
    return true;
}

void retro_unload_game(void)
{
}

unsigned retro_get_region(void)
{
    return RETRO_REGION_NTSC;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num)
{
    return false;
}

size_t retro_serialize_size(void)
{
    return 0;
}

bool retro_serialize(void *data, size_t size)
{
    return false;
}

bool retro_unserialize(const void *data, size_t size)
{
    return false;
}

void *retro_get_memory_data(unsigned id)
{
    return NULL;
}

size_t retro_get_memory_size(unsigned id)
{
    return 0;
}

void retro_cheat_reset(void)
{
}

void retro_cheat_set(unsigned index, bool enabled, const char *code)
{
}

// ============================================================================
// PLATFORM ABSTRACTION IMPLEMENTATION
// ============================================================================

int platform_init(void)
{
    return 0;
}

void platform_set_uformat(int format)
{
    // UTF-8 is default
}

int platform_install_timer(void)
{
    return 0;
}

int platform_install_keyboard(void)
{
    return 0;
}

int platform_install_mouse(void)
{
    return 0;
}

void platform_set_color_depth(int depth)
{
    // Fixed at 32-bit
}

int platform_set_gfx_mode(int mode, int width, int height, int v_width, int v_height)
{
    g_screen_width = width;
    g_screen_height = height;
    
    // Reallocate framebuffer if size changed
    if (g_framebuffer) {
        free(g_framebuffer);
    }
    g_framebuffer = (uint32_t*)calloc(width * height, sizeof(uint32_t));
    
    if (g_screen) {
        g_screen->surface = g_framebuffer;
        g_screen->w = width;
        g_screen->h = height;
    }
    
    return 0;
}

void platform_set_window_title(const char *title)
{
    // Not applicable in libretro
}

void platform_set_close_button_callback(void (*callback)(void))
{
    g_close_callback = callback;
}

void platform_install_int_ex(void (*callback)(void), int bps)
{
    g_timer_callback = callback;
    // Convert BPS to frame count (assuming 60 FPS)
    // Prevent division by zero
    if (bps > 0) {
        g_timer_interval = 60 / bps;
        if (g_timer_interval < 1) g_timer_interval = 1;
    } else {
        g_timer_interval = 1;  // Default to every frame
    }
}

volatile char* platform_get_key_state(void)
{
    return g_key_state;
}

PlatformBitmap* platform_get_screen(void)
{
    return g_screen;
}

void platform_present_screen(void)
{
    // Screen is automatically presented in retro_run
}

// ============================================================================
// GRAPHICS - BITMAP OPERATIONS
// ============================================================================

PlatformBitmap* platform_create_bitmap(int width, int height)
{
    PlatformBitmap *pb = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (pb) {
        pb->surface = (uint32_t*)calloc(width * height, sizeof(uint32_t));
        pb->w = width;
        pb->h = height;
    }
    return pb;
}

void platform_destroy_bitmap(PlatformBitmap *bitmap)
{
    if (bitmap) {
        if (bitmap->surface && bitmap != g_screen) {
            free(bitmap->surface);
        }
        free(bitmap);
    }
}

PlatformBitmap* platform_load_bitmap(const char *filename, void *palette)
{
    // For now, just create an empty bitmap
    // TODO: Implement actual image loading
    return NULL;
}

void platform_clear_bitmap(PlatformBitmap *bitmap)
{
    if (bitmap && bitmap->surface) {
        memset(bitmap->surface, 0, bitmap->w * bitmap->h * sizeof(uint32_t));
    }
}

void platform_clear_to_color(PlatformBitmap *bitmap, PlatformColor color)
{
    if (bitmap && bitmap->surface) {
        uint32_t *pixels = (uint32_t*)bitmap->surface;
        for (int i = 0; i < bitmap->w * bitmap->h; i++) {
            pixels[i] = color;
        }
    }
}

void platform_draw_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y)
{
    if (!dest || !dest->surface || !src || !src->surface)
        return;
    
    uint32_t *dest_pixels = (uint32_t*)dest->surface;
    uint32_t *src_pixels = (uint32_t*)src->surface;
    
    for (int sy = 0; sy < src->h; sy++) {
        int dy = y + sy;
        if (dy < 0 || dy >= dest->h) continue;
        
        for (int sx = 0; sx < src->w; sx++) {
            int dx = x + sx;
            if (dx < 0 || dx >= dest->w) continue;
            
            uint32_t pixel = src_pixels[sy * src->w + sx];
            // Skip magenta (transparency color)
            if ((pixel & 0x00FFFFFF) == TRANSPARENCY_COLOR_MAGENTA) continue;
            
            dest_pixels[dy * dest->w + dx] = pixel;
        }
    }
}

void platform_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                          int src_x, int src_y, int src_w, int src_h,
                          int dest_x, int dest_y, int dest_w, int dest_h)
{
    if (!src || !src->surface || !dest || !dest->surface)
        return;
    
    uint32_t *src_pixels = (uint32_t*)src->surface;
    uint32_t *dest_pixels = (uint32_t*)dest->surface;
    
    for (int dy = 0; dy < dest_h; dy++) {
        int sy = src_y + (dy * src_h) / dest_h;
        if (sy >= src->h) continue;
        
        int dest_row = dest_y + dy;
        if (dest_row < 0 || dest_row >= dest->h) continue;
        
        for (int dx = 0; dx < dest_w; dx++) {
            int sx = src_x + (dx * src_w) / dest_w;
            if (sx >= src->w) continue;
            
            int dest_col = dest_x + dx;
            if (dest_col < 0 || dest_col >= dest->w) continue;
            
            uint32_t pixel = src_pixels[sy * src->w + sx];
            dest_pixels[dest_row * dest->w + dest_col] = pixel;
        }
    }
}

void platform_blit(PlatformBitmap *src, PlatformBitmap *dest,
                  int src_x, int src_y, int dest_x, int dest_y, int w, int h)
{
    platform_stretch_blit(src, dest, src_x, src_y, w, h, dest_x, dest_y, w, h);
}

void platform_masked_blit(PlatformBitmap *src, PlatformBitmap *dest,
                         int src_x, int src_y, int dest_x, int dest_y, int w, int h)
{
    platform_blit(src, dest, src_x, src_y, dest_x, dest_y, w, h);
}

void platform_draw_sprite_h_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y)
{
    // TODO: Implement horizontal flip
    platform_draw_sprite(dest, src, x, y);
}

void platform_draw_sprite_v_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y)
{
    // TODO: Implement vertical flip
    platform_draw_sprite(dest, src, x, y);
}

void platform_draw_sprite_vh_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y)
{
    // TODO: Implement both flips
    platform_draw_sprite(dest, src, x, y);
}

void platform_rotate_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                           int x, int y, int angle)
{
    // TODO: Implement rotation
    platform_draw_sprite(dest, src, x, y);
}

void platform_pivot_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                          int x, int y, int cx, int cy, int angle)
{
    // TODO: Implement pivot rotation
    platform_draw_sprite(dest, src, x - cx, y - cy);
}

PlatformColor platform_getpixel(PlatformBitmap *bitmap, int x, int y)
{
    if (!bitmap || !bitmap->surface || x < 0 || x >= bitmap->w || y < 0 || y >= bitmap->h)
        return 0;
    
    uint32_t *pixels = (uint32_t*)bitmap->surface;
    return pixels[y * bitmap->w + x];
}

void platform_putpixel(PlatformBitmap *bitmap, int x, int y, PlatformColor color)
{
    if (!bitmap || !bitmap->surface || x < 0 || x >= bitmap->w || y < 0 || y >= bitmap->h)
        return;
    
    uint32_t *pixels = (uint32_t*)bitmap->surface;
    pixels[y * bitmap->w + x] = color;
}

int platform_bitmap_width(PlatformBitmap *bitmap)
{
    return bitmap ? bitmap->w : 0;
}

int platform_bitmap_height(PlatformBitmap *bitmap)
{
    return bitmap ? bitmap->h : 0;
}

// ============================================================================
// GRAPHICS - PRIMITIVES
// ============================================================================

void platform_line(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color)
{
    if (!bitmap) return;
    
    // Bresenham's line algorithm
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    
    while (1) {
        platform_putpixel(bitmap, x1, y1, color);
        
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

void platform_rect(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color)
{
    platform_line(bitmap, x1, y1, x2, y1, color);
    platform_line(bitmap, x2, y1, x2, y2, color);
    platform_line(bitmap, x2, y2, x1, y2, color);
    platform_line(bitmap, x1, y2, x1, y1, color);
}

void platform_rectfill(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color)
{
    if (!bitmap || !bitmap->surface) return;
    
    if (x1 > x2) { int t = x1; x1 = x2; x2 = t; }
    if (y1 > y2) { int t = y1; y1 = y2; y2 = t; }
    
    for (int y = y1; y <= y2 && y < bitmap->h; y++) {
        if (y < 0) continue;
        for (int x = x1; x <= x2 && x < bitmap->w; x++) {
            if (x < 0) continue;
            platform_putpixel(bitmap, x, y, color);
        }
    }
}

void platform_circle(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color)
{
    // Midpoint circle algorithm
    int dx = radius;
    int dy = 0;
    int err = 0;
    
    while (dx >= dy) {
        platform_putpixel(bitmap, x + dx, y + dy, color);
        platform_putpixel(bitmap, x + dy, y + dx, color);
        platform_putpixel(bitmap, x - dy, y + dx, color);
        platform_putpixel(bitmap, x - dx, y + dy, color);
        platform_putpixel(bitmap, x - dx, y - dy, color);
        platform_putpixel(bitmap, x - dy, y - dx, color);
        platform_putpixel(bitmap, x + dy, y - dx, color);
        platform_putpixel(bitmap, x + dx, y - dy, color);
        
        if (err <= 0) {
            dy += 1;
            err += 2 * dy + 1;
        }
        
        if (err > 0) {
            dx -= 1;
            err -= 2 * dx + 1;
        }
    }
}

void platform_circlefill(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color)
{
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            if (i * i + j * j <= radius * radius) {
                platform_putpixel(bitmap, x + i, y + j, color);
            }
        }
    }
}

PlatformColor platform_makecol(int r, int g, int b)
{
    return 0xFF000000 | (r << 16) | (g << 8) | b;
}

// ============================================================================
// GRAPHICS - TEXT
// ============================================================================

PlatformFont* platform_load_font(const char *filename, void *palette, void *param)
{
    // TODO: Implement font loading
    return NULL;
}

void platform_destroy_font(PlatformFont *font)
{
    if (font) {
        free(font);
    }
}

void platform_textout_ex(PlatformBitmap *bitmap, PlatformFont *font,
                        const char *text, int x, int y,
                        PlatformColor color, PlatformColor bg)
{
    // TODO: Implement text rendering
}

void platform_textout_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                               const char *text, int x, int y,
                               PlatformColor color, PlatformColor bg)
{
    // TODO: Implement centered text
}

void platform_textprintf_ex(PlatformBitmap *bitmap, PlatformFont *font,
                           int x, int y, PlatformColor color, PlatformColor bg,
                           const char *format, ...)
{
    // TODO: Implement formatted text
}

void platform_textprintf_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                                  int x, int y, PlatformColor color, PlatformColor bg,
                                  const char *format, ...)
{
    // TODO: Implement centered formatted text
}

// ============================================================================
// AUDIO (Stub implementations)
// ============================================================================

int platform_install_sound(int digi, int midi, const char *cfg)
{
    return 0;
}

PlatformSample* platform_load_sample(const char *filename)
{
    return NULL;
}

PlatformMidi* platform_load_midi(const char *filename)
{
    return NULL;
}

void platform_destroy_sample(PlatformSample *sample)
{
}

void platform_destroy_midi(PlatformMidi *midi)
{
}

int platform_play_sample(PlatformSample *sample, int vol, int pan, int freq, int loop)
{
    return -1;
}

int platform_play_midi(PlatformMidi *midi, int loop)
{
    return -1;
}

void platform_stop_midi(void)
{
}

void platform_set_volume(int digi, int midi)
{
}

void platform_adjust_sample(PlatformSample *sample, int vol, int pan, int freq, int loop)
{
}

// ============================================================================
// FILE UTILITIES
// ============================================================================

int platform_file_exists(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

// ============================================================================
// CONFIG FILE (Stub implementations)
// ============================================================================

void platform_set_config_file(const char *filename)
{
    if (filename) {
        strncpy(g_config_file, filename, sizeof(g_config_file) - 1);
        g_config_file[sizeof(g_config_file) - 1] = '\0';  // Ensure null termination
    }
}

int platform_get_config_int(const char *section, const char *key, int default_value)
{
    return default_value;
}

const char* platform_get_config_string(const char *section, const char *key, const char *default_value)
{
    return default_value;
}

float platform_get_config_float(const char *section, const char *key, float default_value)
{
    return default_value;
}

void platform_set_config_int(const char *section, const char *key, int value)
{
}

void platform_set_config_string(const char *section, const char *key, const char *value)
{
}

// ============================================================================
// COLOR UTILITIES
// ============================================================================

int platform_getr(PlatformColor color)
{
    return (color >> 16) & 0xFF;
}

int platform_getg(PlatformColor color)
{
    return (color >> 8) & 0xFF;
}

int platform_getb(PlatformColor color)
{
    return color & 0xFF;
}

// ============================================================================
// TIMING UTILITIES
// ============================================================================

void platform_rest(int milliseconds)
{
    // Not applicable in libretro frame-based execution
}

// ============================================================================
// ADDITIONAL FUNCTIONS
// ============================================================================

void platform_drawing_mode(int mode, void *pattern, int x_anchor, int y_anchor)
{
}

void platform_masked_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                                  int src_x, int src_y, int src_w, int src_h,
                                  int dest_x, int dest_y, int dest_w, int dest_h)
{
    platform_stretch_blit(src, dest, src_x, src_y, src_w, src_h, dest_x, dest_y, dest_w, dest_h);
}

void platform_clear(PlatformBitmap *bitmap)
{
    platform_clear_bitmap(bitmap);
}

void platform_clear_keybuf(void)
{
}

void platform_set_trans_blender(int r, int g, int b, int a)
{
}

void platform_textprintf_right_ex(PlatformBitmap *bitmap, PlatformFont *font,
                                  int x, int y, PlatformColor color, PlatformColor bg,
                                  const char *format, ...)
{
}

void platform_alert_message(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}

void platform_stretch_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y, int w, int h)
{
    if (dest && src) {
        platform_stretch_blit(src, dest, 0, 0, src->w, src->h, x, y, w, h);
    }
}

void platform_solid_mode(void)
{
}

void platform_draw_trans_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y)
{
    platform_draw_sprite(dest, src, x, y);
}

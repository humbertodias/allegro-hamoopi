// platform.h - Platform abstraction layer for HAMOOPI
// SDL2 implementation for graphics, audio, input, and system functions

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdio.h>
#include <stdlib.h>

// Include SDL2 headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// SDL2 structures with exposed w,h for compatibility
struct PlatformBitmap {
    void *surface;  // SDL_Surface*
    int w, h;       // Exposed for Allegro compatibility
};

struct PlatformFont {
    void *font;     // TTF_Font*
    int size;
};

struct PlatformSample {
    void *chunk;    // Mix_Chunk*
    int channel;
};

struct PlatformMidi {
    void *music;    // Mix_Music*
};

typedef struct PlatformBitmap PlatformBitmap;
typedef struct PlatformFont PlatformFont;
typedef struct PlatformSample PlatformSample;
typedef struct PlatformMidi PlatformMidi;

// Color type
typedef unsigned int PlatformColor;

// Key codes (matching Allegro's KEY_* constants)
#define PKEY_A           1
#define PKEY_B           2
#define PKEY_C           3
#define PKEY_D           4
#define PKEY_E           5
#define PKEY_F           6
#define PKEY_G           7
#define PKEY_H           8
#define PKEY_I           9
#define PKEY_J           10
#define PKEY_K           11
#define PKEY_L           12
#define PKEY_M           13
#define PKEY_N           14
#define PKEY_O           15
#define PKEY_P           16
#define PKEY_Q           17
#define PKEY_R           18
#define PKEY_S           19
#define PKEY_T           20
#define PKEY_U           21
#define PKEY_V           22
#define PKEY_W           23
#define PKEY_X           24
#define PKEY_Y           25
#define PKEY_Z           26
#define PKEY_0           27
#define PKEY_1           28
#define PKEY_2           29
#define PKEY_3           30
#define PKEY_4           31
#define PKEY_5           32
#define PKEY_6           33
#define PKEY_7           34
#define PKEY_8           35
#define PKEY_9           36
#define PKEY_F1          47
#define PKEY_F2          48
#define PKEY_F3          49
#define PKEY_F4          50
#define PKEY_F5          51
#define PKEY_F6          52
#define PKEY_F7          53
#define PKEY_F8          54
#define PKEY_F9          55
#define PKEY_F10         56
#define PKEY_F11         57
#define PKEY_F12         58
#define PKEY_ESC         59
#define PKEY_ENTER       67
#define PKEY_SPACE       75
#define PKEY_LEFT        82
#define PKEY_RIGHT       83
#define PKEY_UP          84
#define PKEY_DOWN        85
#define PKEY_LSHIFT      115
#define PKEY_RSHIFT      116
#define PKEY_LCONTROL    117
#define PKEY_RCONTROL    118
#define PKEY_ALT         119
#define PKEY_ALTGR       120

// Graphics modes
#define PGFX_AUTODETECT_FULLSCREEN 0
#define PGFX_AUTODETECT_WINDOWED   1

// Audio detection
#define PDIGI_AUTODETECT 0
#define PMIDI_AUTODETECT 0

// UTF8 support
#define PU_UTF8 1

// Drawing modes
#define PDRAW_MODE_SOLID 0
#define PDRAW_MODE_TRANS 1

// Mouse variables (globals for compatibility)
extern volatile int platform_mouse_x;
extern volatile int platform_mouse_y;
extern volatile int platform_mouse_b;

// ============================================================================
// INITIALIZATION & SYSTEM
// ============================================================================

// Initialize the platform (equivalent to allegro_init)
int platform_init(void);

// Set UTF format (equivalent to set_uformat)
void platform_set_uformat(int format);

// Install timer system
int platform_install_timer(void);

// Install keyboard system
int platform_install_keyboard(void);

// Install mouse system
int platform_install_mouse(void);

// Set color depth (8, 15, 16, 24, 32)
void platform_set_color_depth(int depth);

// Set graphics mode
int platform_set_gfx_mode(int mode, int width, int height, int v_width, int v_height);

// Set window title
void platform_set_window_title(const char *title);

// Set close button callback
void platform_set_close_button_callback(void (*callback)(void));

// Install timer callback (BPS = beats per second)
void platform_install_int_ex(void (*callback)(void), int bps);

// Get key state array
volatile char* platform_get_key_state(void);

// Get screen bitmap for drawing
PlatformBitmap* platform_get_screen(void);

// Present/flip screen (updates display with drawn content)
void platform_present_screen(void);

// ============================================================================
// GRAPHICS - BITMAP OPERATIONS
// ============================================================================

// Create a new bitmap
PlatformBitmap* platform_create_bitmap(int width, int height);

// Destroy a bitmap
void platform_destroy_bitmap(PlatformBitmap *bitmap);

// Load bitmap from file
PlatformBitmap* platform_load_bitmap(const char *filename, void *palette);

// Clear bitmap to specific color
void platform_clear_bitmap(PlatformBitmap *bitmap);

// Clear bitmap to specific color
void platform_clear_to_color(PlatformBitmap *bitmap, PlatformColor color);

// Draw sprite (bitmap) onto another bitmap at position
void platform_draw_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y);

// Stretch blit (scale bitmap from src to dest)
void platform_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                          int src_x, int src_y, int src_w, int src_h,
                          int dest_x, int dest_y, int dest_w, int dest_h);

// Blit (copy bitmap region)
void platform_blit(PlatformBitmap *src, PlatformBitmap *dest,
                  int src_x, int src_y, int dest_x, int dest_y, int w, int h);

// Masked blit (copy with transparency)
void platform_masked_blit(PlatformBitmap *src, PlatformBitmap *dest,
                         int src_x, int src_y, int dest_x, int dest_y, int w, int h);

// Draw sprite with horizontal flip
void platform_draw_sprite_h_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y);

// Draw sprite with vertical flip
void platform_draw_sprite_v_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y);

// Draw sprite with horizontal and vertical flip
void platform_draw_sprite_vh_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y);

// Rotate sprite
void platform_rotate_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                           int x, int y, int angle);

// Pivot sprite with rotation and scaling
void platform_pivot_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                          int x, int y, int cx, int cy, int angle);

// Get pixel color
PlatformColor platform_getpixel(PlatformBitmap *bitmap, int x, int y);

// Put pixel
void platform_putpixel(PlatformBitmap *bitmap, int x, int y, PlatformColor color);

// Get bitmap width
int platform_bitmap_width(PlatformBitmap *bitmap);

// Get bitmap height
int platform_bitmap_height(PlatformBitmap *bitmap);

// ============================================================================
// GRAPHICS - PRIMITIVES
// ============================================================================

// Draw line
void platform_line(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color);

// Draw rectangle outline
void platform_rect(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color);

// Draw filled rectangle
void platform_rectfill(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color);

// Draw circle outline
void platform_circle(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color);

// Draw filled circle
void platform_circlefill(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color);

// Make color from RGB values
PlatformColor platform_makecol(int r, int g, int b);

// ============================================================================
// GRAPHICS - TEXT
// ============================================================================

// Load font from file
PlatformFont* platform_load_font(const char *filename, void *palette, void *param);

// Destroy font
void platform_destroy_font(PlatformFont *font);

// Draw text
void platform_textout_ex(PlatformBitmap *bitmap, PlatformFont *font,
                        const char *text, int x, int y,
                        PlatformColor color, PlatformColor bg);

// Draw centered text
void platform_textout_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                               const char *text, int x, int y,
                               PlatformColor color, PlatformColor bg);

// Draw formatted text (printf style)
void platform_textprintf_ex(PlatformBitmap *bitmap, PlatformFont *font,
                           int x, int y, PlatformColor color, PlatformColor bg,
                           const char *format, ...);

// Draw centered formatted text
void platform_textprintf_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                                  int x, int y, PlatformColor color, PlatformColor bg,
                                  const char *format, ...);

// ============================================================================
// AUDIO
// ============================================================================

// Install sound system
int platform_install_sound(int digi, int midi, const char *cfg);

// Load audio sample
PlatformSample* platform_load_sample(const char *filename);

// Load MIDI
PlatformMidi* platform_load_midi(const char *filename);

// Destroy sample
void platform_destroy_sample(PlatformSample *sample);

// Destroy MIDI
void platform_destroy_midi(PlatformMidi *midi);

// Play sample (vol: 0-255, pan: 0-255, freq: 1000=normal, loop: 0=no, 1=yes)
int platform_play_sample(PlatformSample *sample, int vol, int pan, int freq, int loop);

// Play MIDI (loop: 0=no, 1=yes)
int platform_play_midi(PlatformMidi *midi, int loop);

// Stop MIDI
void platform_stop_midi(void);

// Set volume (0-255)
void platform_set_volume(int digi, int midi);

// Adjust sample volume
void platform_adjust_sample(PlatformSample *sample, int vol, int pan, int freq, int loop);

// ============================================================================
// FILE UTILITIES
// ============================================================================

// Check if file exists
int platform_file_exists(const char *filename);

// ============================================================================
// CONFIG FILE
// ============================================================================

// Set config file
void platform_set_config_file(const char *filename);

// Get config integer
int platform_get_config_int(const char *section, const char *key, int default_value);

// Get config string
const char* platform_get_config_string(const char *section, const char *key, const char *default_value);

// Get config float
float platform_get_config_float(const char *section, const char *key, float default_value);

// Set config integer
void platform_set_config_int(const char *section, const char *key, int value);

// Set config string
void platform_set_config_string(const char *section, const char *key, const char *value);

// ============================================================================
// UTILITY MACROS
// ============================================================================

// Timer to BPS conversion
#define PLATFORM_BPS_TO_TIMER(x) ((long)(1000000.0 / (x)))

#endif // PLATFORM_H

// ============================================================================
// COLOR UTILITIES
// ============================================================================

// Extract red component from color
int platform_getr(PlatformColor color);

// Extract green component from color
int platform_getg(PlatformColor color);

// Extract blue component from color
int platform_getb(PlatformColor color);

// ============================================================================
// TIMING UTILITIES
// ============================================================================

// Rest/sleep for specified milliseconds
void platform_rest(int milliseconds);


// Set drawing mode
void platform_drawing_mode(int mode, void *pattern, int x_anchor, int y_anchor);

// Masked stretch blit
void platform_masked_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                                  int src_x, int src_y, int src_w, int src_h,
                                  int dest_x, int dest_y, int dest_w, int dest_h);

// Clear screen
void platform_clear(PlatformBitmap *bitmap);

// Clear keyboard buffer
void platform_clear_keybuf(void);

void platform_set_trans_blender(int r, int g, int b, int a);
void platform_textprintf_right_ex(PlatformBitmap *bitmap, PlatformFont *font, int x, int y, PlatformColor color, PlatformColor bg, const char *format, ...);

// Display alert message
void platform_alert_message(const char *format, ...);

// Stretch sprite
void platform_stretch_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y, int w, int h);

void platform_solid_mode(void);
void platform_draw_trans_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y);
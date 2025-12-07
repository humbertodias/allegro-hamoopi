#ifndef BACKEND_H
#define BACKEND_H

// Abstract backend header for HAMOOPI
// This header provides an abstraction layer between HAMOOPI and the underlying graphics/audio library
// Currently implemented with Allegro 4, but can be replaced with other backends in the future

#include <stdio.h>

// Opaque types - these will be defined by the backend implementation
typedef void* HM_BITMAP;
typedef void* HM_FONT;
typedef void* HM_SAMPLE;
typedef void* HM_MIDI;

// Color type
typedef int HM_COLOR;

// Key codes - these map to keyboard keys
extern volatile char* backend_key;

// Mouse state
extern volatile int backend_mouse_x;
extern volatile int backend_mouse_y;
extern volatile int backend_mouse_b;

// Screen buffer
extern HM_BITMAP backend_screen;

// Backend initialization and cleanup
int backend_init(void);
void backend_exit(void);
int backend_set_color_depth(int depth);
int backend_set_gfx_mode(int card, int w, int h, int v_w, int v_h);
void backend_set_window_title(const char* title);
void backend_message(const char* msg);

// Timer functions
void backend_install_timer(void);
int backend_install_int_ex(void (*proc)(void), int speed);
void backend_rest(int time);

// Input functions
int backend_install_keyboard(void);
int backend_install_mouse(void);
void backend_clear_keybuf(void);

// Sound functions
int backend_install_sound(int digi, int midi);
void backend_set_volume(int digi_volume, int midi_volume);
HM_SAMPLE backend_load_sample(const char* filename);
void backend_destroy_sample(HM_SAMPLE sample);
int backend_play_sample(HM_SAMPLE sample, int vol, int pan, int freq, int loop);
void backend_stop_sample(HM_SAMPLE sample);
HM_MIDI backend_load_midi(const char* filename);
void backend_destroy_midi(HM_MIDI midi);
int backend_play_midi(HM_MIDI midi, int loop);
void backend_stop_midi(void);

// Bitmap functions
HM_BITMAP backend_create_bitmap(int width, int height);
void backend_destroy_bitmap(HM_BITMAP bmp);
HM_BITMAP backend_load_bitmap(const char* filename, void* pal);
int backend_save_bitmap(const char* filename, HM_BITMAP bmp, void* pal);
void backend_clear_bitmap(HM_BITMAP bmp);
void backend_clear_to_color(HM_BITMAP bmp, HM_COLOR color);
int backend_bitmap_width(HM_BITMAP bmp);
int backend_bitmap_height(HM_BITMAP bmp);

// Drawing functions
void backend_blit(HM_BITMAP source, HM_BITMAP dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void backend_masked_blit(HM_BITMAP source, HM_BITMAP dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void backend_stretch_blit(HM_BITMAP source, HM_BITMAP dest, int source_x, int source_y, int source_width, int source_height, int dest_x, int dest_y, int dest_width, int dest_height);
void backend_stretch_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y, int w, int h);
void backend_draw_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y);
void backend_draw_sprite_h_flip(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y);
void backend_draw_sprite_v_flip(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y);
void backend_draw_trans_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y);
void backend_rotate_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y, int angle);

// Primitive drawing functions
void backend_putpixel(HM_BITMAP bmp, int x, int y, HM_COLOR color);
HM_COLOR backend_getpixel(HM_BITMAP bmp, int x, int y);
void backend_hline(HM_BITMAP bmp, int x1, int y, int x2, HM_COLOR color);
void backend_vline(HM_BITMAP bmp, int x, int y1, int y2, HM_COLOR color);
void backend_line(HM_BITMAP bmp, int x1, int y1, int x2, int y2, HM_COLOR color);
void backend_rect(HM_BITMAP bmp, int x1, int y1, int x2, int y2, HM_COLOR color);
void backend_rectfill(HM_BITMAP bmp, int x1, int y1, int x2, int y2, HM_COLOR color);
void backend_circle(HM_BITMAP bmp, int x, int y, int radius, HM_COLOR color);
void backend_circlefill(HM_BITMAP bmp, int x, int y, int radius, HM_COLOR color);

// Color functions
HM_COLOR backend_makecol(int r, int g, int b);
void backend_getr(HM_COLOR color, int* r);
void backend_getg(HM_COLOR color, int* g);
void backend_getb(HM_COLOR color, int* b);

// Blending functions
void backend_set_trans_blender(int r, int g, int b, int a);
void backend_drawing_mode(int mode, HM_BITMAP pattern, int x_anchor, int y_anchor);

// Text functions
HM_FONT backend_load_font(const char* filename);
void backend_destroy_font(HM_FONT font);
void backend_textout_ex(HM_BITMAP bmp, HM_FONT font, const char* text, int x, int y, HM_COLOR color, HM_COLOR bg);
void backend_textout_centre_ex(HM_BITMAP bmp, HM_FONT font, const char* text, int x, int y, HM_COLOR color, HM_COLOR bg);
void backend_textout_right_ex(HM_BITMAP bmp, HM_FONT font, const char* text, int x, int y, HM_COLOR color, HM_COLOR bg);
void backend_textprintf_ex(HM_BITMAP bmp, HM_FONT font, int x, int y, HM_COLOR color, HM_COLOR bg, const char* format, ...);
void backend_textprintf_centre_ex(HM_BITMAP bmp, HM_FONT font, int x, int y, HM_COLOR color, HM_COLOR bg, const char* format, ...);
void backend_textprintf_right_ex(HM_BITMAP bmp, HM_FONT font, int x, int y, HM_COLOR color, HM_COLOR bg, const char* format, ...);
int backend_text_length(HM_FONT font, const char* text);
int backend_text_height(HM_FONT font);

// Configuration file functions
void backend_set_config_file(const char* filename);
const char* backend_get_config_string(const char* section, const char* name, const char* def);
int backend_get_config_int(const char* section, const char* name, int def);
float backend_get_config_float(const char* section, const char* name, float def);
void backend_set_config_string(const char* section, const char* name, const char* val);
void backend_set_config_int(const char* section, const char* name, int val);
void backend_set_config_float(const char* section, const char* name, float val);

// File functions
int backend_file_exists(const char* filename);
void backend_set_uformat(int format);

// Callback functions
void backend_set_close_button_callback(void (*proc)(void));

// Key code constants
#define HM_KEY_ESC      1
#define HM_KEY_ENTER    28
#define HM_KEY_SPACE    57
#define HM_KEY_F1       59
#define HM_KEY_F2       60
#define HM_KEY_F3       61
#define HM_KEY_F4       62
#define HM_KEY_F5       63
#define HM_KEY_F6       64
#define HM_KEY_F7       65
#define HM_KEY_F8       66
#define HM_KEY_F9       67
#define HM_KEY_F10      68
#define HM_KEY_F11      87
#define HM_KEY_F12      88
#define HM_KEY_ALT      56
#define HM_KEY_LSHIFT   42
#define HM_KEY_RSHIFT   54
#define HM_KEY_LCONTROL 29
#define HM_KEY_RCONTROL 97
#define HM_KEY_UP       72
#define HM_KEY_DOWN     80
#define HM_KEY_LEFT     75
#define HM_KEY_RIGHT    77
#define HM_KEY_A        30
#define HM_KEY_B        48
#define HM_KEY_C        46
#define HM_KEY_D        32
#define HM_KEY_E        18
#define HM_KEY_F        33
#define HM_KEY_G        34
#define HM_KEY_H        35
#define HM_KEY_I        23
#define HM_KEY_J        36
#define HM_KEY_K        37
#define HM_KEY_L        38
#define HM_KEY_M        50
#define HM_KEY_N        49
#define HM_KEY_O        24
#define HM_KEY_P        25
#define HM_KEY_Q        16
#define HM_KEY_R        19
#define HM_KEY_S        31
#define HM_KEY_T        20
#define HM_KEY_U        22
#define HM_KEY_V        47
#define HM_KEY_W        17
#define HM_KEY_X        45
#define HM_KEY_Y        21
#define HM_KEY_Z        44
#define HM_KEY_0        11
#define HM_KEY_1        2
#define HM_KEY_2        3
#define HM_KEY_3        4
#define HM_KEY_4        5
#define HM_KEY_5        6
#define HM_KEY_6        7
#define HM_KEY_7        8
#define HM_KEY_8        9
#define HM_KEY_9        10

// Drawing modes
#define HM_DRAW_MODE_SOLID            0
#define HM_DRAW_MODE_XOR              1
#define HM_DRAW_MODE_COPY_PATTERN     2
#define HM_DRAW_MODE_SOLID_PATTERN    3
#define HM_DRAW_MODE_MASKED_PATTERN   4
#define HM_DRAW_MODE_TRANS            5

// Graphics mode
#define HM_GFX_AUTODETECT_WINDOWED    0
#define HM_GFX_AUTODETECT_FULLSCREEN  1

// Unicode formats
#define HM_U_ASCII       0
#define HM_U_UTF8        1

// Sound constants
#define HM_DIGI_AUTODETECT   -1
#define HM_MIDI_AUTODETECT   -1

// Timer conversion macro
#define BPS_TO_TIMER(x) (1000000L / (x))

// Platform-specific macro (required by some backends)
#ifdef __GNUC__
    #define END_OF_MAIN()
#else
    #define END_OF_MAIN() void _mangled_main_address() { }
#endif

#endif // BACKEND_H

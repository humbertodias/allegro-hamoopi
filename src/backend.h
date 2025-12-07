#ifndef BACKEND_H
#define BACKEND_H

/*
 * HAMOOPI Backend Abstraction Layer
 * This file defines the interface between the game engine and the graphics/audio library.
 * Different backends (Allegro, SDL2, etc.) can be implemented by providing these functions.
 */

#include <stdint.h>

/* Forward declarations for opaque types */
typedef struct HM_BITMAP HM_BITMAP;
typedef struct HM_FONT HM_FONT;
typedef struct HM_SAMPLE HM_SAMPLE;
typedef struct HM_MIDI HM_MIDI;

/* Color format */
typedef uint32_t HM_COLOR;

/* Graphics modes */
#define HM_GFX_AUTODETECT_WINDOWED 0
#define HM_GFX_AUTODETECT_FULLSCREEN 1

/* Backend interface structure */
typedef struct {
    /* System functions */
    int (*init)(void);
    void (*exit)(void);
    int (*install_timer)(void);
    int (*install_keyboard)(void);
    int (*install_mouse)(void);
    int (*install_sound)(int, int);
    int (*set_gfx_mode)(int mode, int w, int h, int v_w, int v_h);
    void (*set_window_title)(const char *title);
    void (*set_close_button_callback)(void (*callback)(void));
    void (*rest)(int msec);
    int (*keypressed)(void);
    int (*readkey)(void);
    
    /* Timing */
    void (*install_int_ex)(void (*proc)(void), int speed);
    void (*remove_int)(void (*proc)(void));
    
    /* Graphics functions */
    HM_BITMAP* (*create_bitmap)(int width, int height);
    void (*destroy_bitmap)(HM_BITMAP *bmp);
    HM_BITMAP* (*load_bitmap)(const char *filename, void *pal);
    void (*clear_bitmap)(HM_BITMAP *bmp);
    void (*clear_to_color)(HM_BITMAP *bmp, HM_COLOR color);
    void (*blit)(HM_BITMAP *source, HM_BITMAP *dest, int source_x, int source_y, 
                 int dest_x, int dest_y, int width, int height);
    void (*masked_blit)(HM_BITMAP *source, HM_BITMAP *dest, int source_x, int source_y,
                        int dest_x, int dest_y, int width, int height);
    void (*stretch_blit)(HM_BITMAP *source, HM_BITMAP *dest, int source_x, int source_y,
                         int source_w, int source_h, int dest_x, int dest_y,
                         int dest_w, int dest_h);
    void (*draw_sprite)(HM_BITMAP *bmp, HM_BITMAP *sprite, int x, int y);
    void (*draw_sprite_h_flip)(HM_BITMAP *bmp, HM_BITMAP *sprite, int x, int y);
    void (*draw_sprite_v_flip)(HM_BITMAP *bmp, HM_BITMAP *sprite, int x, int y);
    void (*draw_sprite_vh_flip)(HM_BITMAP *bmp, HM_BITMAP *sprite, int x, int y);
    void (*rect)(HM_BITMAP *bmp, int x1, int y1, int x2, int y2, HM_COLOR color);
    void (*rectfill)(HM_BITMAP *bmp, int x1, int y1, int x2, int y2, HM_COLOR color);
    void (*circle)(HM_BITMAP *bmp, int x, int y, int radius, HM_COLOR color);
    void (*circlefill)(HM_BITMAP *bmp, int x, int y, int radius, HM_COLOR color);
    void (*line)(HM_BITMAP *bmp, int x1, int y1, int x2, int y2, HM_COLOR color);
    void (*hline)(HM_BITMAP *bmp, int x1, int y, int x2, HM_COLOR color);
    void (*vline)(HM_BITMAP *bmp, int x, int y1, int y2, HM_COLOR color);
    void (*putpixel)(HM_BITMAP *bmp, int x, int y, HM_COLOR color);
    HM_COLOR (*getpixel)(HM_BITMAP *bmp, int x, int y);
    HM_COLOR (*makecol)(int r, int g, int b);
    int (*getr)(HM_COLOR c);
    int (*getg)(HM_COLOR c);
    int (*getb)(HM_COLOR c);
    
    /* Text functions */
    HM_FONT* (*load_font)(const char *filename, void *pal1, void *pal2);
    void (*destroy_font)(HM_FONT *f);
    void (*textout_centre_ex)(HM_BITMAP *bmp, HM_FONT *f, const char *s, int x, int y,
                              HM_COLOR fg, HM_COLOR bg);
    void (*textout_ex)(HM_BITMAP *bmp, HM_FONT *f, const char *s, int x, int y,
                       HM_COLOR fg, HM_COLOR bg);
    void (*textprintf_ex)(HM_BITMAP *bmp, HM_FONT *f, int x, int y,
                          HM_COLOR fg, HM_COLOR bg, const char *fmt, ...);
    int (*text_length)(HM_FONT *f, const char *str);
    int (*text_height)(HM_FONT *f);
    
    /* Audio functions */
    HM_SAMPLE* (*load_sample)(const char *filename);
    void (*destroy_sample)(HM_SAMPLE *spl);
    int (*play_sample)(HM_SAMPLE *spl, int vol, int pan, int freq, int loop);
    void (*stop_sample)(HM_SAMPLE *spl);
    void (*adjust_sample)(HM_SAMPLE *spl, int vol, int pan, int freq, int loop);
    HM_MIDI* (*load_midi)(const char *filename);
    void (*destroy_midi)(HM_MIDI *midi);
    int (*play_midi)(HM_MIDI *midi, int loop);
    void (*stop_midi)(void);
    void (*set_volume)(int digi, int midi);
    
    /* Input - Keyboard */
    int* key_array;
    int key_shifts;
    
    /* Input - Mouse */
    int (*mouse_x)(void);
    int (*mouse_y)(void);
    int (*mouse_b)(void);
    void (*position_mouse)(int x, int y);
    void (*show_mouse)(HM_BITMAP *bmp);
    
    /* Screen buffer */
    HM_BITMAP* screen;
    
    /* Palette functions */
    void (*set_palette)(void *p);
    void (*select_palette)(void *p);
    void (*unselect_palette)(void);
    
    /* Config file functions */
    void (*set_config_file)(const char *filename);
    const char* (*get_config_string)(const char *section, const char *name, const char *def);
    int (*get_config_int)(const char *section, const char *name, int def);
    void (*set_config_string)(const char *section, const char *name, const char *val);
    void (*set_config_int)(const char *section, const char *name, int val);
    
    /* File utility functions */
    int (*exists)(const char *filename);
    
} Backend;

/* Global backend instance */
extern Backend *backend;

/* Backend initialization functions */
Backend* backend_allegro4_create(void);
Backend* backend_sdl2_create(void);

/* Convenience macros for easier migration */
#define hm_init() backend->init()
#define hm_exit() backend->exit()
#define hm_install_timer() backend->install_timer()
#define hm_install_keyboard() backend->install_keyboard()
#define hm_install_mouse() backend->install_mouse()
#define hm_install_sound(a, b) backend->install_sound(a, b)
#define hm_set_gfx_mode(m, w, h, vw, vh) backend->set_gfx_mode(m, w, h, vw, vh)
#define hm_set_window_title(t) backend->set_window_title(t)
#define hm_set_close_button_callback(c) backend->set_close_button_callback(c)
#define hm_rest(m) backend->rest(m)
#define hm_keypressed() backend->keypressed()
#define hm_readkey() backend->readkey()

#define hm_create_bitmap(w, h) backend->create_bitmap(w, h)
#define hm_destroy_bitmap(b) backend->destroy_bitmap(b)
#define hm_load_bitmap(f, p) backend->load_bitmap(f, p)
#define hm_clear_bitmap(b) backend->clear_bitmap(b)
#define hm_clear_to_color(b, c) backend->clear_to_color(b, c)
#define hm_blit(s, d, sx, sy, dx, dy, w, h) backend->blit(s, d, sx, sy, dx, dy, w, h)
#define hm_masked_blit(s, d, sx, sy, dx, dy, w, h) backend->masked_blit(s, d, sx, sy, dx, dy, w, h)
#define hm_stretch_blit(s, d, sx, sy, sw, sh, dx, dy, dw, dh) backend->stretch_blit(s, d, sx, sy, sw, sh, dx, dy, dw, dh)
#define hm_draw_sprite(b, s, x, y) backend->draw_sprite(b, s, x, y)
#define hm_draw_sprite_h_flip(b, s, x, y) backend->draw_sprite_h_flip(b, s, x, y)
#define hm_draw_sprite_v_flip(b, s, x, y) backend->draw_sprite_v_flip(b, s, x, y)
#define hm_draw_sprite_vh_flip(b, s, x, y) backend->draw_sprite_vh_flip(b, s, x, y)
#define hm_rect(b, x1, y1, x2, y2, c) backend->rect(b, x1, y1, x2, y2, c)
#define hm_rectfill(b, x1, y1, x2, y2, c) backend->rectfill(b, x1, y1, x2, y2, c)
#define hm_circle(b, x, y, r, c) backend->circle(b, x, y, r, c)
#define hm_circlefill(b, x, y, r, c) backend->circlefill(b, x, y, r, c)
#define hm_line(b, x1, y1, x2, y2, c) backend->line(b, x1, y1, x2, y2, c)
#define hm_hline(b, x1, y, x2, c) backend->hline(b, x1, y, x2, c)
#define hm_vline(b, x, y1, y2, c) backend->vline(b, x, y1, y2, c)
#define hm_putpixel(b, x, y, c) backend->putpixel(b, x, y, c)
#define hm_getpixel(b, x, y) backend->getpixel(b, x, y)
#define hm_makecol(r, g, b) backend->makecol(r, g, b)
#define hm_getr(c) backend->getr(c)
#define hm_getg(c) backend->getg(c)
#define hm_getb(c) backend->getb(c)

#define hm_screen backend->screen
#define hm_key backend->key_array

#define hm_mouse_x() backend->mouse_x()
#define hm_mouse_y() backend->mouse_y()
#define hm_mouse_b() backend->mouse_b()

#define hm_load_font(f, p1, p2) backend->load_font(f, p1, p2)
#define hm_textout_centre_ex(b, f, s, x, y, fg, bg) backend->textout_centre_ex(b, f, s, x, y, fg, bg)
#define hm_textout_ex(b, f, s, x, y, fg, bg) backend->textout_ex(b, f, s, x, y, fg, bg)
#define hm_textprintf_ex(b, f, x, y, fg, bg, fmt, ...) backend->textprintf_ex(b, f, x, y, fg, bg, fmt, ##__VA_ARGS__)

#define hm_load_sample(f) backend->load_sample(f)
#define hm_play_sample(s, v, p, f, l) backend->play_sample(s, v, p, f, l)
#define hm_stop_sample(s) backend->stop_sample(s)
#define hm_load_midi(f) backend->load_midi(f)
#define hm_play_midi(m, l) backend->play_midi(m, l)
#define hm_stop_midi() backend->stop_midi()
#define hm_set_volume(d, m) backend->set_volume(d, m)

#define hm_set_config_file(f) backend->set_config_file(f)
#define hm_get_config_string(s, n, d) backend->get_config_string(s, n, d)
#define hm_get_config_int(s, n, d) backend->get_config_int(s, n, d)
#define hm_set_config_string(s, n, v) backend->set_config_string(s, n, v)
#define hm_set_config_int(s, n, v) backend->set_config_int(s, n, v)

#define hm_exists(f) backend->exists(f)

/* Key scan codes - common across backends */
#define HM_KEY_A 0
#define HM_KEY_B 1
#define HM_KEY_C 2
#define HM_KEY_D 3
#define HM_KEY_E 4
#define HM_KEY_F 5
#define HM_KEY_G 6
#define HM_KEY_H 7
#define HM_KEY_I 8
#define HM_KEY_J 9
#define HM_KEY_K 10
#define HM_KEY_L 11
#define HM_KEY_M 12
#define HM_KEY_N 13
#define HM_KEY_O 14
#define HM_KEY_P 15
#define HM_KEY_Q 16
#define HM_KEY_R 17
#define HM_KEY_S 18
#define HM_KEY_T 19
#define HM_KEY_U 20
#define HM_KEY_V 21
#define HM_KEY_W 22
#define HM_KEY_X 23
#define HM_KEY_Y 24
#define HM_KEY_Z 25
#define HM_KEY_0 26
#define HM_KEY_1 27
#define HM_KEY_2 28
#define HM_KEY_3 29
#define HM_KEY_4 30
#define HM_KEY_5 31
#define HM_KEY_6 32
#define HM_KEY_7 33
#define HM_KEY_8 34
#define HM_KEY_9 35
#define HM_KEY_PAD_0 36
#define HM_KEY_PAD_1 37
#define HM_KEY_PAD_2 38
#define HM_KEY_PAD_3 39
#define HM_KEY_PAD_4 40
#define HM_KEY_PAD_5 41
#define HM_KEY_PAD_6 42
#define HM_KEY_PAD_7 43
#define HM_KEY_PAD_8 44
#define HM_KEY_PAD_9 45
#define HM_KEY_F1 46
#define HM_KEY_F2 47
#define HM_KEY_F3 48
#define HM_KEY_F4 49
#define HM_KEY_F5 50
#define HM_KEY_F6 51
#define HM_KEY_F7 52
#define HM_KEY_F8 53
#define HM_KEY_F9 54
#define HM_KEY_F10 55
#define HM_KEY_F11 56
#define HM_KEY_F12 57
#define HM_KEY_ESC 58
#define HM_KEY_TILDE 59
#define HM_KEY_MINUS 60
#define HM_KEY_EQUALS 61
#define HM_KEY_BACKSPACE 62
#define HM_KEY_TAB 63
#define HM_KEY_OPENBRACE 64
#define HM_KEY_CLOSEBRACE 65
#define HM_KEY_ENTER 66
#define HM_KEY_COLON 67
#define HM_KEY_QUOTE 68
#define HM_KEY_BACKSLASH 69
#define HM_KEY_COMMA 70
#define HM_KEY_STOP 71
#define HM_KEY_SLASH 72
#define HM_KEY_SPACE 73
#define HM_KEY_INSERT 74
#define HM_KEY_DEL 75
#define HM_KEY_HOME 76
#define HM_KEY_END 77
#define HM_KEY_PGUP 78
#define HM_KEY_PGDN 79
#define HM_KEY_LEFT 80
#define HM_KEY_RIGHT 81
#define HM_KEY_UP 82
#define HM_KEY_DOWN 83
#define HM_KEY_PAD_SLASH 84
#define HM_KEY_PAD_ASTERISK 85
#define HM_KEY_PAD_MINUS 86
#define HM_KEY_PAD_PLUS 87
#define HM_KEY_PAD_DELETE 88
#define HM_KEY_PAD_ENTER 89
#define HM_KEY_PRTSCR 90
#define HM_KEY_PAUSE 91
#define HM_KEY_LSHIFT 92
#define HM_KEY_RSHIFT 93
#define HM_KEY_LCONTROL 94
#define HM_KEY_RCONTROL 95
#define HM_KEY_ALT 96
#define HM_KEY_ALTGR 97
#define HM_KEY_LWIN 98
#define HM_KEY_RWIN 99
#define HM_KEY_MENU 100
#define HM_KEY_SCRLOCK 101
#define HM_KEY_NUMLOCK 102
#define HM_KEY_CAPSLOCK 103
#define HM_KEY_MAX 128

#endif /* BACKEND_H */

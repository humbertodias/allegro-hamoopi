// platform_compat.h - Compatibility layer for gradual migration
// This provides macro aliases from Allegro 4 to platform abstraction
// allowing for minimal code changes during migration

#ifndef PLATFORM_COMPAT_H
#define PLATFORM_COMPAT_H

#include "platform.h"

// ============================================================================
// TYPE COMPATIBILITY MAPPINGS
// ============================================================================

// With USE_ALLEGRO4, types are already aliased in platform.h
// Just define BITMAP, FONT, SAMPLE, MIDI if not already defined
#ifndef USE_ALLEGRO4
#define BITMAP PlatformBitmap
#define FONT PlatformFont
#define SAMPLE PlatformSample
#define MIDI PlatformMidi
#endif

// ============================================================================
// KEY CODE MAPPINGS
// ============================================================================

// When using Allegro 4, Allegro's key codes are already available
// For other backends, map to platform key codes
#ifndef USE_ALLEGRO4
#define KEY_A       PKEY_A
#define KEY_B       PKEY_B
#define KEY_C       PKEY_C
#define KEY_D       PKEY_D
#define KEY_E       PKEY_E
#define KEY_F       PKEY_F
#define KEY_G       PKEY_G
#define KEY_H       PKEY_H
#define KEY_I       PKEY_I
#define KEY_J       PKEY_J
#define KEY_K       PKEY_K
#define KEY_L       PKEY_L
#define KEY_M       PKEY_M
#define KEY_N       PKEY_N
#define KEY_O       PKEY_O
#define KEY_P       PKEY_P
#define KEY_Q       PKEY_Q
#define KEY_R       PKEY_R
#define KEY_S       PKEY_S
#define KEY_T       PKEY_T
#define KEY_U       PKEY_U
#define KEY_V       PKEY_V
#define KEY_W       PKEY_W
#define KEY_X       PKEY_X
#define KEY_Y       PKEY_Y
#define KEY_Z       PKEY_Z
#define KEY_0       PKEY_0
#define KEY_1       PKEY_1
#define KEY_2       PKEY_2
#define KEY_3       PKEY_3
#define KEY_4       PKEY_4
#define KEY_5       PKEY_5
#define KEY_6       PKEY_6
#define KEY_7       PKEY_7
#define KEY_8       PKEY_8
#define KEY_9       PKEY_9
#define KEY_ESC     PKEY_ESC
#define KEY_SPACE   PKEY_SPACE
#define KEY_ENTER   PKEY_ENTER
#define KEY_UP      PKEY_UP
#define KEY_DOWN    PKEY_DOWN
#define KEY_LEFT    PKEY_LEFT
#define KEY_RIGHT   PKEY_RIGHT
#define KEY_LSHIFT  PKEY_LSHIFT
#define KEY_RSHIFT  PKEY_RSHIFT
#define KEY_LCONTROL PKEY_LCONTROL
#define KEY_RCONTROL PKEY_RCONTROL
#define KEY_ALT     PKEY_ALT
#define KEY_ALTGR   PKEY_ALTGR
#define KEY_F1      PKEY_F1
#define KEY_F2      PKEY_F2
#define KEY_F3      PKEY_F3
#define KEY_F4      PKEY_F4
#define KEY_F5      PKEY_F5
#define KEY_F6      PKEY_F6
#define KEY_F7      PKEY_F7
#define KEY_F8      PKEY_F8
#define KEY_F9      PKEY_F9
#define KEY_F10     PKEY_F10
#define KEY_F11     PKEY_F11
#define KEY_F12     PKEY_F12
#endif

// ============================================================================
// GRAPHICS MODE MAPPINGS
// ============================================================================

#ifndef USE_ALLEGRO4
#define GFX_AUTODETECT_FULLSCREEN PGFX_AUTODETECT_FULLSCREEN
#define GFX_AUTODETECT_WINDOWED   PGFX_AUTODETECT_WINDOWED
#endif

// ============================================================================
// AUDIO MODE MAPPINGS
// ============================================================================

#ifndef USE_ALLEGRO4
#define DIGI_AUTODETECT PDIGI_AUTODETECT
#define MIDI_AUTODETECT PMIDI_AUTODETECT
#endif

// ============================================================================
// UTF8 MAPPINGS
// ============================================================================

#ifndef USE_ALLEGRO4
#define U_UTF8 PU_UTF8
#define DRAW_MODE_SOLID PDRAW_MODE_SOLID
#define DRAW_MODE_TRANS PDRAW_MODE_TRANS
#define mouse_x platform_mouse_x
#define mouse_y platform_mouse_y
#define mouse_b platform_mouse_b
#endif

// ============================================================================
// FUNCTION MAPPINGS - INITIALIZATION & SYSTEM
// ============================================================================

// Only create function mappings if not using Allegro 4 directly
#ifndef USE_ALLEGRO4
#define allegro_init() platform_init()
#define set_uformat(format) platform_set_uformat(format)
#define install_timer() platform_install_timer()
#define install_keyboard() platform_install_keyboard()
#define install_mouse() platform_install_mouse()
#define set_color_depth(depth) platform_set_color_depth(depth)
#define set_gfx_mode(mode, w, h, vw, vh) platform_set_gfx_mode(mode, w, h, vw, vh)
#define set_window_title(title) platform_set_window_title(title)
#define set_close_button_callback(cb) platform_set_close_button_callback(cb)
#define install_int_ex(cb, bps) platform_install_int_ex(cb, bps)
#define BPS_TO_TIMER(x) PLATFORM_BPS_TO_TIMER(x)

// Key array access
#define key platform_get_key_state()

// Screen access
#define screen platform_get_screen()

// ============================================================================
// FUNCTION MAPPINGS - GRAPHICS/BITMAP
// ============================================================================

#define create_bitmap(w, h) platform_create_bitmap(w, h)
#define destroy_bitmap(bmp) platform_destroy_bitmap(bmp)
#define load_bitmap(file, pal) platform_load_bitmap(file, pal)
#define clear_bitmap(bmp) platform_clear_bitmap(bmp)
#define clear_to_color(bmp, col) platform_clear_to_color(bmp, col)
#define draw_sprite(dest, src, x, y) platform_draw_sprite(dest, src, x, y)
#define stretch_blit(src, dest, sx, sy, sw, sh, dx, dy, dw, dh) \
    platform_stretch_blit(src, dest, sx, sy, sw, sh, dx, dy, dw, dh)
#define blit(src, dest, sx, sy, dx, dy, w, h) \
    platform_blit(src, dest, sx, sy, dx, dy, w, h)
#define masked_blit(src, dest, sx, sy, dx, dy, w, h) \
    platform_masked_blit(src, dest, sx, sy, dx, dy, w, h)
#define draw_sprite_h_flip(dest, src, x, y) platform_draw_sprite_h_flip(dest, src, x, y)
#define draw_sprite_v_flip(dest, src, x, y) platform_draw_sprite_v_flip(dest, src, x, y)
#define draw_sprite_vh_flip(dest, src, x, y) platform_draw_sprite_vh_flip(dest, src, x, y)
#define rotate_sprite(dest, src, x, y, angle) platform_rotate_sprite(dest, src, x, y, angle)
#define pivot_sprite(dest, src, x, y, cx, cy, angle) \
    platform_pivot_sprite(dest, src, x, y, cx, cy, angle)
#define getpixel(bmp, x, y) platform_getpixel(bmp, x, y)
#define putpixel(bmp, x, y, col) platform_putpixel(bmp, x, y, col)

// ============================================================================
// FUNCTION MAPPINGS - PRIMITIVES
// ============================================================================

#define line(bmp, x1, y1, x2, y2, col) platform_line(bmp, x1, y1, x2, y2, col)
#define rect(bmp, x1, y1, x2, y2, col) platform_rect(bmp, x1, y1, x2, y2, col)
#define rectfill(bmp, x1, y1, x2, y2, col) platform_rectfill(bmp, x1, y1, x2, y2, col)
#define circle(bmp, x, y, r, col) platform_circle(bmp, x, y, r, col)
#define circlefill(bmp, x, y, r, col) platform_circlefill(bmp, x, y, r, col)
#define makecol(r, g, b) platform_makecol(r, g, b)

// ============================================================================
// FUNCTION MAPPINGS - TEXT
// ============================================================================

#define load_font(file, pal, param) platform_load_font(file, pal, param)
#define destroy_font(font) platform_destroy_font(font)
#define textout_ex(bmp, font, text, x, y, col, bg) \
    platform_textout_ex(bmp, font, text, x, y, col, bg)
#define textout_centre_ex(bmp, font, text, x, y, col, bg) \
    platform_textout_centre_ex(bmp, font, text, x, y, col, bg)
#define textprintf_ex platform_textprintf_ex
#define textprintf_centre_ex platform_textprintf_centre_ex

// ============================================================================
// FUNCTION MAPPINGS - AUDIO
// ============================================================================

#define install_sound(digi, midi, cfg) platform_install_sound(digi, midi, cfg)
#define load_sample(file) platform_load_sample(file)
#define load_midi(file) platform_load_midi(file)
#define destroy_sample(sample) platform_destroy_sample(sample)
#define destroy_midi(midi) platform_destroy_midi(midi)
#define play_sample(sample, vol, pan, freq, loop) \
    platform_play_sample(sample, vol, pan, freq, loop)
#define play_midi(midi, loop) platform_play_midi(midi, loop)
#define stop_midi() platform_stop_midi()
#define set_volume(digi, midi) platform_set_volume(digi, midi)
#define adjust_sample(sample, vol, pan, freq, loop) \
    platform_adjust_sample(sample, vol, pan, freq, loop)

// ============================================================================
// FUNCTION MAPPINGS - CONFIG
// ============================================================================

#define set_config_file(file) platform_set_config_file(file)
#define get_config_int(sec, key, def) platform_get_config_int(sec, key, def)
#define get_config_string(sec, key, def) platform_get_config_string(sec, key, def)
#define get_config_float(sec, key, def) platform_get_config_float(sec, key, def)
#define set_config_int(sec, key, val) platform_set_config_int(sec, key, val)
#define set_config_string(sec, key, val) platform_set_config_string(sec, key, val)

// Color utilities
#define getr(c) platform_getr(c)
#define getg(c) platform_getg(c)
#define getb(c) platform_getb(c)

// Timing
#define rest(ms) platform_rest(ms)

// File utilities
#define exists(filename) platform_file_exists(filename)

// Drawing mode
#define drawing_mode(mode, pattern, x, y) platform_drawing_mode(mode, pattern, x, y)
#define solid_mode() platform_solid_mode()

// Additional blits and drawing
#define masked_stretch_blit(src, dest, sx, sy, sw, sh, dx, dy, dw, dh) \
    platform_masked_stretch_blit(src, dest, sx, sy, sw, sh, dx, dy, dw, dh)
#define stretch_sprite(dest, src, x, y, w, h) platform_stretch_sprite(dest, src, x, y, w, h)
#define draw_trans_sprite(dest, src, x, y) platform_draw_trans_sprite(dest, src, x, y)

// Clear functions
#define clear(bmp) platform_clear(bmp)
#define clear_keybuf() platform_clear_keybuf()

// Blending
#define set_trans_blender(r, g, b, a) platform_set_trans_blender(r, g, b, a)

// Text (right-aligned)
#define textprintf_right_ex platform_textprintf_right_ex

// Alert
#define allegro_message platform_alert_message

#endif // !USE_ALLEGRO4

#endif // PLATFORM_COMPAT_H

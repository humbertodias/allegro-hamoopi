#ifndef HAMOOPI_WRAPPER_H
#define HAMOOPI_WRAPPER_H

// This file provides compatibility wrappers that allow gradual migration
// from direct Allegro calls to the backend abstraction layer

#include "backend_manager.h"
#include <allegro.h>

// Global pointer to backend manager (for convenience)
extern BackendManager* g_backend;

// Compatibility macros for key checking
// These allow the existing code to work with minimal changes
#define KEY_CHECK(scancode) (key[scancode])

// Graphics compatibility wrappers
// Note: Background color parameter is ignored in these wrappers as the backend
// interface uses -1 for transparent background by default
inline BITMAP* wrapper_create_bitmap(int w, int h) {
    return (BITMAP*)g_backend->getGraphics()->create_bitmap(w, h);
}

inline BITMAP* wrapper_load_bitmap(const char* filename) {
    return (BITMAP*)g_backend->getGraphics()->load_bitmap(filename);
}

inline void wrapper_destroy_bitmap(BITMAP* bmp) {
    g_backend->getGraphics()->destroy_bitmap(bmp);
}

inline void wrapper_blit(BITMAP* src, BITMAP* dest, int sx, int sy, int dx, int dy, int w, int h) {
    g_backend->getGraphics()->blit(src, dest, sx, sy, dx, dy, w, h);
}

inline void wrapper_stretch_blit(BITMAP* src, BITMAP* dest, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh) {
    g_backend->getGraphics()->stretch_blit(src, dest, sx, sy, sw, sh, dx, dy, dw, dh);
}

inline void wrapper_draw_sprite(BITMAP* dest, BITMAP* sprite, int x, int y) {
    g_backend->getGraphics()->draw_sprite(dest, sprite, x, y);
}

inline void wrapper_draw_sprite_h_flip(BITMAP* dest, BITMAP* sprite, int x, int y) {
    g_backend->getGraphics()->draw_sprite_h_flip(dest, sprite, x, y);
}

inline void wrapper_rectfill(BITMAP* bmp, int x1, int y1, int x2, int y2, int color) {
    g_backend->getGraphics()->rectfill(bmp, x1, y1, x2, y2, color);
}

inline void wrapper_rect(BITMAP* bmp, int x1, int y1, int x2, int y2, int color) {
    g_backend->getGraphics()->rect(bmp, x1, y1, x2, y2, color);
}

inline void wrapper_line(BITMAP* bmp, int x1, int y1, int x2, int y2, int color) {
    g_backend->getGraphics()->line(bmp, x1, y1, x2, y2, color);
}

inline void wrapper_circle(BITMAP* bmp, int x, int y, int radius, int color) {
    g_backend->getGraphics()->circle(bmp, x, y, radius, color);
}

inline void wrapper_circlefill(BITMAP* bmp, int x, int y, int radius, int color) {
    g_backend->getGraphics()->circlefill(bmp, x, y, radius, color);
}

inline FONT* wrapper_load_font(const char* filename) {
    return (FONT*)g_backend->getGraphics()->load_font(filename);
}

// IMPORTANT: These wrapper functions for textout accept a background color parameter
// for compatibility with Allegro's textout_ex functions, but the parameter is
// intentionally ignored. The backend implementation always uses -1 (transparent background)
// which is the most common use case. If you need a specific background color,
// use rectfill to draw a background rectangle before drawing text.
inline void wrapper_textout_ex(BITMAP* bmp, FONT* font, const char* text, int x, int y, int color, int bg) {
    // Note: 'bg' parameter is ignored - backend uses transparent background (-1)
    g_backend->getGraphics()->textout(bmp, font, text, x, y, color);
}

inline void wrapper_textout_centre_ex(BITMAP* bmp, FONT* font, const char* text, int x, int y, int color, int bg) {
    // Note: 'bg' parameter is ignored - backend uses transparent background (-1)
    g_backend->getGraphics()->textout_centre(bmp, font, text, x, y, color);
}

inline int wrapper_makecol(int r, int g, int b) {
    return g_backend->getGraphics()->makecol(r, g, b);
}

inline void wrapper_clear_to_color(BITMAP* bmp, int color) {
    g_backend->getGraphics()->clear_to_color(bmp, color);
}

inline BITMAP* wrapper_get_screen() {
    return (BITMAP*)g_backend->getGraphics()->get_screen();
}

// System compatibility wrappers
inline void wrapper_rest(int ms) {
    g_backend->getSystem()->rest(ms);
}

inline int wrapper_exists(const char* filename) {
    return g_backend->getSystem()->file_exists(filename) ? 1 : 0;
}

inline void wrapper_set_config_file(const char* filename) {
    g_backend->getSystem()->set_config_file(filename);
}

inline const char* wrapper_get_config_string(const char* section, const char* key, const char* def) {
    return g_backend->getSystem()->get_config_string(section, key, def);
}

inline int wrapper_get_config_int(const char* section, const char* key, int def) {
    return g_backend->getSystem()->get_config_int(section, key, def);
}

inline void wrapper_set_config_int(const char* section, const char* key, int value) {
    g_backend->getSystem()->set_config_int(section, key, value);
}

inline void wrapper_allegro_message(const char* msg) {
    g_backend->getSystem()->show_message(msg);
}

// Audio compatibility wrappers
inline SAMPLE* wrapper_load_sample(const char* filename) {
    return (SAMPLE*)g_backend->getAudio()->load_sample(filename);
}

inline void wrapper_play_sample(SAMPLE* spl, int vol, int pan, int freq, int loop) {
    g_backend->getAudio()->play_sample(spl, vol, pan, freq, loop != 0);
}

// Mouse compatibility wrappers
inline void wrapper_poll_mouse() {
    g_backend->getInput()->poll_mouse();
}

inline int wrapper_mouse_x() {
    return g_backend->getInput()->mouse_x();
}

inline int wrapper_mouse_y() {
    return g_backend->getInput()->mouse_y();
}

inline void wrapper_show_mouse(BITMAP* bmp) {
    g_backend->getInput()->show_mouse(bmp);
}

#endif // HAMOOPI_WRAPPER_H

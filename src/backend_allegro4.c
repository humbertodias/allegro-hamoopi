#include "backend.h"
#include <allegro.h>
#include <stdarg.h>
#include <string.h>

// Export global variables
volatile char* backend_key = NULL;
volatile int backend_mouse_x = 0;
volatile int backend_mouse_y = 0;
volatile int backend_mouse_b = 0;
HM_BITMAP backend_screen = NULL;

// Backend initialization and cleanup
int backend_init(void) {
    int result = allegro_init();
    if (result == 0) {
        backend_key = (volatile char*)key;
        backend_screen = (HM_BITMAP)screen;
    }
    return result;
}

void backend_exit(void) {
    allegro_exit();
}

int backend_set_color_depth(int depth) {
    set_color_depth(depth);
    return 0;
}

int backend_set_gfx_mode(int card, int w, int h, int v_w, int v_h) {
    int result = set_gfx_mode(card, w, h, v_w, v_h);
    backend_screen = (HM_BITMAP)screen;
    return result;
}

void backend_set_window_title(const char* title) {
    set_window_title(title);
}

void backend_message(const char* msg) {
    allegro_message("%s", msg);
}

// Timer functions
void backend_install_timer(void) {
    install_timer();
}

int backend_install_int_ex(void (*proc)(void), int speed) {
    return install_int_ex(proc, speed);
}

void backend_rest(int time) {
    rest(time);
}

// Input functions
int backend_install_keyboard(void) {
    int result = install_keyboard();
    backend_key = (volatile char*)key;
    return result;
}

int backend_install_mouse(void) {
    int result = install_mouse();
    return result;
}

void backend_clear_keybuf(void) {
    clear_keybuf();
}

// Sound functions
int backend_install_sound(int digi, int midi) {
    return install_sound(digi, midi);
}

void backend_set_volume(int digi_volume, int midi_volume) {
    set_volume(digi_volume, midi_volume);
}

HM_SAMPLE backend_load_sample(const char* filename) {
    return (HM_SAMPLE)load_sample(filename);
}

void backend_destroy_sample(HM_SAMPLE sample) {
    destroy_sample((SAMPLE*)sample);
}

int backend_play_sample(HM_SAMPLE sample, int vol, int pan, int freq, int loop) {
    return play_sample((SAMPLE*)sample, vol, pan, freq, loop);
}

void backend_stop_sample(HM_SAMPLE sample) {
    stop_sample((SAMPLE*)sample);
}

HM_MIDI backend_load_midi(const char* filename) {
    return (HM_MIDI)load_midi(filename);
}

void backend_destroy_midi(HM_MIDI midi) {
    destroy_midi((MIDI*)midi);
}

int backend_play_midi(HM_MIDI midi, int loop) {
    return play_midi((MIDI*)midi, loop);
}

void backend_stop_midi(void) {
    stop_midi();
}

// Bitmap functions
HM_BITMAP backend_create_bitmap(int width, int height) {
    return (HM_BITMAP)create_bitmap(width, height);
}

void backend_destroy_bitmap(HM_BITMAP bmp) {
    destroy_bitmap((BITMAP*)bmp);
}

HM_BITMAP backend_load_bitmap(const char* filename, void* pal) {
    return (HM_BITMAP)load_bitmap(filename, (RGB*)pal);
}

int backend_save_bitmap(const char* filename, HM_BITMAP bmp, void* pal) {
    return save_bitmap(filename, (BITMAP*)bmp, (RGB*)pal);
}

void backend_clear_bitmap(HM_BITMAP bmp) {
    clear_bitmap((BITMAP*)bmp);
}

void backend_clear_to_color(HM_BITMAP bmp, HM_COLOR color) {
    clear_to_color((BITMAP*)bmp, color);
}

int backend_bitmap_width(HM_BITMAP bmp) {
    return ((BITMAP*)bmp)->w;
}

int backend_bitmap_height(HM_BITMAP bmp) {
    return ((BITMAP*)bmp)->h;
}

// Drawing functions
void backend_blit(HM_BITMAP source, HM_BITMAP dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) {
    blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, dest_x, dest_y, width, height);
}

void backend_masked_blit(HM_BITMAP source, HM_BITMAP dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) {
    masked_blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, dest_x, dest_y, width, height);
}

void backend_stretch_blit(HM_BITMAP source, HM_BITMAP dest, int source_x, int source_y, int source_width, int source_height, int dest_x, int dest_y, int dest_width, int dest_height) {
    stretch_blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, source_width, source_height, dest_x, dest_y, dest_width, dest_height);
}

void backend_stretch_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y, int w, int h) {
    stretch_sprite((BITMAP*)bmp, (BITMAP*)sprite, x, y, w, h);
}

void backend_draw_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y) {
    draw_sprite((BITMAP*)bmp, (BITMAP*)sprite, x, y);
}

void backend_draw_sprite_h_flip(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y) {
    draw_sprite_h_flip((BITMAP*)bmp, (BITMAP*)sprite, x, y);
}

void backend_draw_sprite_v_flip(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y) {
    draw_sprite_v_flip((BITMAP*)bmp, (BITMAP*)sprite, x, y);
}

void backend_draw_trans_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y) {
    draw_trans_sprite((BITMAP*)bmp, (BITMAP*)sprite, x, y);
}

void backend_rotate_sprite(HM_BITMAP bmp, HM_BITMAP sprite, int x, int y, int angle) {
    rotate_sprite((BITMAP*)bmp, (BITMAP*)sprite, x, y, itofix(angle));
}

// Primitive drawing functions
void backend_putpixel(HM_BITMAP bmp, int x, int y, HM_COLOR color) {
    putpixel((BITMAP*)bmp, x, y, color);
}

HM_COLOR backend_getpixel(HM_BITMAP bmp, int x, int y) {
    return getpixel((BITMAP*)bmp, x, y);
}

void backend_hline(HM_BITMAP bmp, int x1, int y, int x2, HM_COLOR color) {
    hline((BITMAP*)bmp, x1, y, x2, color);
}

void backend_vline(HM_BITMAP bmp, int x, int y1, int y2, HM_COLOR color) {
    vline((BITMAP*)bmp, x, y1, y2, color);
}

void backend_line(HM_BITMAP bmp, int x1, int y1, int x2, int y2, HM_COLOR color) {
    line((BITMAP*)bmp, x1, y1, x2, y2, color);
}

void backend_rect(HM_BITMAP bmp, int x1, int y1, int x2, int y2, HM_COLOR color) {
    rect((BITMAP*)bmp, x1, y1, x2, y2, color);
}

void backend_rectfill(HM_BITMAP bmp, int x1, int y1, int x2, int y2, HM_COLOR color) {
    rectfill((BITMAP*)bmp, x1, y1, x2, y2, color);
}

void backend_circle(HM_BITMAP bmp, int x, int y, int radius, HM_COLOR color) {
    circle((BITMAP*)bmp, x, y, radius, color);
}

void backend_circlefill(HM_BITMAP bmp, int x, int y, int radius, HM_COLOR color) {
    circlefill((BITMAP*)bmp, x, y, radius, color);
}

// Color functions
HM_COLOR backend_makecol(int r, int g, int b) {
    return makecol(r, g, b);
}

void backend_getr(HM_COLOR color, int* r) {
    *r = getr(color);
}

void backend_getg(HM_COLOR color, int* g) {
    *g = getg(color);
}

void backend_getb(HM_COLOR color, int* b) {
    *b = getb(color);
}

// Blending functions
void backend_set_trans_blender(int r, int g, int b, int a) {
    set_trans_blender(r, g, b, a);
}

void backend_drawing_mode(int mode, HM_BITMAP pattern, int x_anchor, int y_anchor) {
    drawing_mode(mode, (BITMAP*)pattern, x_anchor, y_anchor);
}

// Text functions
HM_FONT backend_load_font(const char* filename) {
    return (HM_FONT)load_font(filename, NULL, NULL);
}

void backend_destroy_font(HM_FONT font) {
    destroy_font((FONT*)font);
}

void backend_textout_ex(HM_BITMAP bmp, HM_FONT font, const char* text, int x, int y, HM_COLOR color, HM_COLOR bg) {
    textout_ex((BITMAP*)bmp, (FONT*)font, text, x, y, color, bg);
}

void backend_textout_centre_ex(HM_BITMAP bmp, HM_FONT font, const char* text, int x, int y, HM_COLOR color, HM_COLOR bg) {
    textout_centre_ex((BITMAP*)bmp, (FONT*)font, text, x, y, color, bg);
}

void backend_textout_right_ex(HM_BITMAP bmp, HM_FONT font, const char* text, int x, int y, HM_COLOR color, HM_COLOR bg) {
    textout_right_ex((BITMAP*)bmp, (FONT*)font, text, x, y, color, bg);
}

void backend_textprintf_ex(HM_BITMAP bmp, HM_FONT font, int x, int y, HM_COLOR color, HM_COLOR bg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    textout_ex((BITMAP*)bmp, (FONT*)font, buffer, x, y, color, bg);
}

void backend_textprintf_centre_ex(HM_BITMAP bmp, HM_FONT font, int x, int y, HM_COLOR color, HM_COLOR bg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    textout_centre_ex((BITMAP*)bmp, (FONT*)font, buffer, x, y, color, bg);
}

void backend_textprintf_right_ex(HM_BITMAP bmp, HM_FONT font, int x, int y, HM_COLOR color, HM_COLOR bg, const char* format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    textout_right_ex((BITMAP*)bmp, (FONT*)font, buffer, x, y, color, bg);
}

int backend_text_length(HM_FONT font, const char* text) {
    return text_length((FONT*)font, text);
}

int backend_text_height(HM_FONT font) {
    return text_height((FONT*)font);
}

// Configuration file functions
void backend_set_config_file(const char* filename) {
    set_config_file(filename);
}

const char* backend_get_config_string(const char* section, const char* name, const char* def) {
    return get_config_string(section, name, def);
}

int backend_get_config_int(const char* section, const char* name, int def) {
    return get_config_int(section, name, def);
}

float backend_get_config_float(const char* section, const char* name, float def) {
    return get_config_float(section, name, def);
}

void backend_set_config_string(const char* section, const char* name, const char* val) {
    set_config_string(section, name, val);
}

void backend_set_config_int(const char* section, const char* name, int val) {
    set_config_int(section, name, val);
}

void backend_set_config_float(const char* section, const char* name, float val) {
    set_config_float(section, name, val);
}

// File functions
int backend_file_exists(const char* filename) {
    return exists(filename);
}

void backend_set_uformat(int format) {
    set_uformat(format);
}

// Callback functions
void backend_set_close_button_callback(void (*proc)(void)) {
    set_close_button_callback(proc);
}

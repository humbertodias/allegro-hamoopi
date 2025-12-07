// platform_sdl2.c - SDL2 implementation of platform abstraction layer

#include "platform.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdarg.h>
#include <string.h>

// Global state
static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static PlatformBitmap *g_screen = NULL;
static volatile Uint8 *g_key_state = NULL;
static int g_key_state_size = 0;
static void (*g_close_callback)(void) = NULL;
static SDL_TimerID g_timer_id = 0;
static void (*g_timer_callback)(void) = NULL;

// Mouse state (exported for compatibility)
volatile int platform_mouse_x = 0;
volatile int platform_mouse_y = 0;
volatile int platform_mouse_b = 0;

// Key mapping from platform keys to SDL scancodes
static SDL_Scancode platform_to_sdl_key[256];

// Initialize key mapping
static void init_key_mapping(void) {
    memset(platform_to_sdl_key, 0, sizeof(platform_to_sdl_key));
    
    // Letters
    platform_to_sdl_key[PKEY_A] = SDL_SCANCODE_A;
    platform_to_sdl_key[PKEY_B] = SDL_SCANCODE_B;
    platform_to_sdl_key[PKEY_C] = SDL_SCANCODE_C;
    platform_to_sdl_key[PKEY_D] = SDL_SCANCODE_D;
    platform_to_sdl_key[PKEY_E] = SDL_SCANCODE_E;
    platform_to_sdl_key[PKEY_F] = SDL_SCANCODE_F;
    platform_to_sdl_key[PKEY_G] = SDL_SCANCODE_G;
    platform_to_sdl_key[PKEY_H] = SDL_SCANCODE_H;
    platform_to_sdl_key[PKEY_I] = SDL_SCANCODE_I;
    platform_to_sdl_key[PKEY_J] = SDL_SCANCODE_J;
    platform_to_sdl_key[PKEY_K] = SDL_SCANCODE_K;
    platform_to_sdl_key[PKEY_L] = SDL_SCANCODE_L;
    platform_to_sdl_key[PKEY_M] = SDL_SCANCODE_M;
    platform_to_sdl_key[PKEY_N] = SDL_SCANCODE_N;
    platform_to_sdl_key[PKEY_O] = SDL_SCANCODE_O;
    platform_to_sdl_key[PKEY_P] = SDL_SCANCODE_P;
    platform_to_sdl_key[PKEY_Q] = SDL_SCANCODE_Q;
    platform_to_sdl_key[PKEY_R] = SDL_SCANCODE_R;
    platform_to_sdl_key[PKEY_S] = SDL_SCANCODE_S;
    platform_to_sdl_key[PKEY_T] = SDL_SCANCODE_T;
    platform_to_sdl_key[PKEY_U] = SDL_SCANCODE_U;
    platform_to_sdl_key[PKEY_V] = SDL_SCANCODE_V;
    platform_to_sdl_key[PKEY_W] = SDL_SCANCODE_W;
    platform_to_sdl_key[PKEY_X] = SDL_SCANCODE_X;
    platform_to_sdl_key[PKEY_Y] = SDL_SCANCODE_Y;
    platform_to_sdl_key[PKEY_Z] = SDL_SCANCODE_Z;
    
    // Numbers
    platform_to_sdl_key[PKEY_0] = SDL_SCANCODE_0;
    platform_to_sdl_key[PKEY_1] = SDL_SCANCODE_1;
    platform_to_sdl_key[PKEY_2] = SDL_SCANCODE_2;
    platform_to_sdl_key[PKEY_3] = SDL_SCANCODE_3;
    platform_to_sdl_key[PKEY_4] = SDL_SCANCODE_4;
    platform_to_sdl_key[PKEY_5] = SDL_SCANCODE_5;
    platform_to_sdl_key[PKEY_6] = SDL_SCANCODE_6;
    platform_to_sdl_key[PKEY_7] = SDL_SCANCODE_7;
    platform_to_sdl_key[PKEY_8] = SDL_SCANCODE_8;
    platform_to_sdl_key[PKEY_9] = SDL_SCANCODE_9;
    
    // Function keys
    platform_to_sdl_key[PKEY_F1] = SDL_SCANCODE_F1;
    platform_to_sdl_key[PKEY_F2] = SDL_SCANCODE_F2;
    platform_to_sdl_key[PKEY_F3] = SDL_SCANCODE_F3;
    platform_to_sdl_key[PKEY_F4] = SDL_SCANCODE_F4;
    platform_to_sdl_key[PKEY_F5] = SDL_SCANCODE_F5;
    platform_to_sdl_key[PKEY_F6] = SDL_SCANCODE_F6;
    platform_to_sdl_key[PKEY_F7] = SDL_SCANCODE_F7;
    platform_to_sdl_key[PKEY_F8] = SDL_SCANCODE_F8;
    platform_to_sdl_key[PKEY_F9] = SDL_SCANCODE_F9;
    platform_to_sdl_key[PKEY_F10] = SDL_SCANCODE_F10;
    platform_to_sdl_key[PKEY_F11] = SDL_SCANCODE_F11;
    platform_to_sdl_key[PKEY_F12] = SDL_SCANCODE_F12;
    
    // Special keys
    platform_to_sdl_key[PKEY_ESC] = SDL_SCANCODE_ESCAPE;
    platform_to_sdl_key[PKEY_ENTER] = SDL_SCANCODE_RETURN;
    platform_to_sdl_key[PKEY_SPACE] = SDL_SCANCODE_SPACE;
    platform_to_sdl_key[PKEY_LEFT] = SDL_SCANCODE_LEFT;
    platform_to_sdl_key[PKEY_RIGHT] = SDL_SCANCODE_RIGHT;
    platform_to_sdl_key[PKEY_UP] = SDL_SCANCODE_UP;
    platform_to_sdl_key[PKEY_DOWN] = SDL_SCANCODE_DOWN;
    platform_to_sdl_key[PKEY_LSHIFT] = SDL_SCANCODE_LSHIFT;
    platform_to_sdl_key[PKEY_RSHIFT] = SDL_SCANCODE_RSHIFT;
    platform_to_sdl_key[PKEY_LCONTROL] = SDL_SCANCODE_LCTRL;
    platform_to_sdl_key[PKEY_RCONTROL] = SDL_SCANCODE_RCTRL;
    platform_to_sdl_key[PKEY_ALT] = SDL_SCANCODE_LALT;
    platform_to_sdl_key[PKEY_ALTGR] = SDL_SCANCODE_RALT;
}

// Timer callback wrapper
static Uint32 timer_callback_wrapper(Uint32 interval, void *param) {
    if (g_timer_callback) {
        g_timer_callback();
    }
    return interval;
}

// ============================================================================
// INITIALIZATION & SYSTEM
// ============================================================================

int platform_init(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    
    init_key_mapping();
    
    // Initialize SDL_image for PNG support
    int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        fprintf(stderr, "IMG_Init failed: %s\n", IMG_GetError());
    }
    
    return 0;
}

void platform_set_uformat(int format) {
    // SDL2 uses UTF-8 internally, no action needed
}

int platform_install_timer(void) {
    // SDL2 timer is initialized with SDL_Init
    return 0;
}

int platform_install_keyboard(void) {
    // SDL2 keyboard is initialized with SDL_Init
    g_key_state = SDL_GetKeyboardState(&g_key_state_size);
    return 0;
}

int platform_install_mouse(void) {
    // SDL2 mouse is initialized with SDL_Init
    return 0;
}

void platform_set_color_depth(int depth) {
    // SDL2 handles color depth automatically
}

int platform_set_gfx_mode(int mode, int width, int height, int v_width, int v_height) {
    Uint32 flags = SDL_WINDOW_SHOWN;
    
    if (mode == PGFX_AUTODETECT_FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    
    g_window = SDL_CreateWindow("HAMOOPI",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 width, height,
                                 flags);
    
    if (!g_window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return -1;
    }
    
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(g_window);
        return -1;
    }
    
    // Create screen surface
    g_screen = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (g_screen) {
        g_screen->surface = SDL_CreateRGBSurface(0, width, height, 32,
                                                  0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        g_screen->texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888,
                                              SDL_TEXTUREACCESS_STREAMING, width, height);
        g_screen->w = width;
        g_screen->h = height;
    }
    
    return 0;
}

void platform_set_window_title(const char *title) {
    if (g_window) {
        SDL_SetWindowTitle(g_window, title);
    }
}

void platform_set_close_button_callback(void (*callback)(void)) {
    g_close_callback = callback;
}

void platform_install_int_ex(void (*callback)(void), int bps) {
    g_timer_callback = callback;
    
    // Convert BPS to milliseconds interval
    Uint32 interval = PLATFORM_BPS_TO_TIMER(bps) / 1000;
    if (interval < 1) interval = 1;
    
    if (g_timer_id) {
        SDL_RemoveTimer(g_timer_id);
    }
    
    g_timer_id = SDL_AddTimer(interval, timer_callback_wrapper, NULL);
}

volatile char* platform_get_key_state(void) {
    // Update SDL events to refresh keyboard state
    SDL_PumpEvents();
    
    // Update mouse state
    Uint32 mouse_state = SDL_GetMouseState((int*)&platform_mouse_x, (int*)&platform_mouse_y);
    platform_mouse_b = 0;
    if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) platform_mouse_b |= 1;
    if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT)) platform_mouse_b |= 2;
    if (mouse_state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) platform_mouse_b |= 4;
    
    // Check for close button
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT && g_close_callback) {
            g_close_callback();
        }
    }
    
    return (volatile char*)g_key_state;
}

PlatformBitmap* platform_get_screen(void) {
    return g_screen;
}

// ============================================================================
// GRAPHICS - BITMAP OPERATIONS
// ============================================================================

PlatformBitmap* platform_create_bitmap(int width, int height) {
    PlatformBitmap *pb = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (pb) {
        pb->surface = SDL_CreateRGBSurface(0, width, height, 32,
                                           0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        pb->texture = NULL;  // Created on demand
        pb->w = width;
        pb->h = height;
        
        if (!pb->surface) {
            free(pb);
            return NULL;
        }
    }
    return pb;
}

void platform_destroy_bitmap(PlatformBitmap *bitmap) {
    if (bitmap) {
        if (bitmap->surface) {
            SDL_FreeSurface(bitmap->surface);
        }
        if (bitmap->texture) {
            SDL_DestroyTexture(bitmap->texture);
        }
        free(bitmap);
    }
}

PlatformBitmap* platform_load_bitmap(const char *filename, void *palette) {
    // Try to load as PCX first (Allegro format), fall back to PNG/JPG
    SDL_Surface *surface = IMG_Load(filename);
    
    if (!surface) {
        // Try alternate extension
        char alt_filename[512];
        strncpy(alt_filename, filename, sizeof(alt_filename) - 5);
        alt_filename[sizeof(alt_filename) - 5] = '\0';
        
        // Replace .pcx with .png
        char *ext = strrchr(alt_filename, '.');
        if (ext) {
            strcpy(ext, ".png");
            surface = IMG_Load(alt_filename);
        }
    }
    
    if (!surface) {
        return NULL;
    }
    
    PlatformBitmap *pb = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (pb) {
        pb->surface = surface;
        pb->texture = NULL;
        pb->w = surface->w;
        pb->h = surface->h;
    } else {
        SDL_FreeSurface(surface);
    }
    
    return pb;
}

void platform_clear_bitmap(PlatformBitmap *bitmap) {
    if (bitmap && bitmap->surface) {
        SDL_FillRect(bitmap->surface, NULL, 0);
    }
}

void platform_clear_to_color(PlatformBitmap *bitmap, PlatformColor color) {
    if (bitmap && bitmap->surface) {
        SDL_FillRect(bitmap->surface, NULL, color);
    }
}

void platform_draw_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->surface && src && ((SDL_Surface*)src->surface)) {
        SDL_Rect dest_rect = { x, y, src->w, src->h };
        SDL_BlitSurface(((SDL_Surface*)src->surface), NULL, dest->surface, &dest_rect);
    }
}

void platform_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                          int src_x, int src_y, int src_w, int src_h,
                          int dest_x, int dest_y, int dest_w, int dest_h) {
    if (src && ((SDL_Surface*)src->surface) && dest && dest->surface) {
        SDL_Rect src_rect = { src_x, src_y, src_w, src_h };
        SDL_Rect dest_rect = { dest_x, dest_y, dest_w, dest_h };
        SDL_BlitScaled(((SDL_Surface*)src->surface), &src_rect, dest->surface, &dest_rect);
    }
}

void platform_blit(PlatformBitmap *src, PlatformBitmap *dest,
                  int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    if (src && ((SDL_Surface*)src->surface) && dest && dest->surface) {
        SDL_Rect src_rect = { src_x, src_y, w, h };
        SDL_Rect dest_rect = { dest_x, dest_y, w, h };
        SDL_BlitSurface(((SDL_Surface*)src->surface), &src_rect, dest->surface, &dest_rect);
    }
}

void platform_masked_blit(PlatformBitmap *src, PlatformBitmap *dest,
                         int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    // SDL2 blit is already masked by alpha channel
    platform_blit(src, dest, src_x, src_y, dest_x, dest_y, w, h);
}

void platform_draw_sprite_h_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->surface && src && ((SDL_Surface*)src->surface)) {
        // Create flipped surface
        SDL_Surface *flipped = SDL_CreateRGBSurface(0, src->w, src->h, 32,
                                                     0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        if (flipped) {
            // Manual horizontal flip
            SDL_Surface *src_surf = (SDL_Surface*)((SDL_Surface*)src->surface);
            SDL_LockSurface(src_surf);
            SDL_LockSurface(flipped);
            
            for (int i = 0; i < src->h; i++) {
                for (int j = 0; j < src->w; j++) {
                    Uint32 *src_pixel = (Uint32*)((Uint8*)src_surf->pixels + i * src_surf->pitch + j * 4);
                    Uint32 *dst_pixel = (Uint32*)((Uint8*)flipped->pixels + i * flipped->pitch + (src->w - 1 - j) * 4);
                    *dst_pixel = *src_pixel;
                }
            }
            
            SDL_UnlockSurface(flipped);
            SDL_UnlockSurface(src_surf);
            
            SDL_Rect dest_rect = { x, y, src->w, src->h };
            SDL_BlitSurface(flipped, NULL, dest->surface, &dest_rect);
            SDL_FreeSurface(flipped);
        }
    }
}

void platform_draw_sprite_v_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->surface && src && ((SDL_Surface*)src->surface)) {
        // Create flipped surface
        SDL_Surface *flipped = SDL_CreateRGBSurface(0, src->w, src->h, 32,
                                                     0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        if (flipped) {
            // Manual vertical flip
            SDL_Surface *src_surf = (SDL_Surface*)((SDL_Surface*)src->surface);
            SDL_LockSurface(src_surf);
            SDL_LockSurface(flipped);
            
            for (int i = 0; i < src->h; i++) {
                memcpy((Uint8*)flipped->pixels + (src->h - 1 - i) * flipped->pitch,
                       (Uint8*)src_surf->pixels + i * src_surf->pitch,
                       src->w * 4);
            }
            
            SDL_UnlockSurface(flipped);
            SDL_UnlockSurface(src_surf);
            
            SDL_Surface *dest_surf = (SDL_Surface*)dest->surface;
            SDL_Rect dest_rect = { x, y, src->w, src->h };
            SDL_BlitSurface(flipped, NULL, dest_surf, &dest_rect);
            SDL_FreeSurface(flipped);
        }
    }
}

void platform_draw_sprite_vh_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->surface && src && ((SDL_Surface*)src->surface)) {
        // Create flipped surface
        SDL_Surface *flipped = SDL_CreateRGBSurface(0, src->w, src->h, 32,
                                                     0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        if (flipped) {
            // Manual horizontal and vertical flip
            SDL_LockSurface(((SDL_Surface*)src->surface));
            SDL_LockSurface(flipped);
            
            for (int i = 0; i < src->h; i++) {
                for (int j = 0; j < src->w; j++) {
                    Uint32 *src_pixel = (Uint32*)((Uint8*)((SDL_Surface*)src->surface)->pixels + i * ((SDL_Surface*)src->surface)->pitch + j * 4);
                    Uint32 *dst_pixel = (Uint32*)((Uint8*)flipped->pixels + (src->h - 1 - i) * flipped->pitch + (src->w - 1 - j) * 4);
                    *dst_pixel = *src_pixel;
                }
            }
            
            SDL_UnlockSurface(flipped);
            SDL_UnlockSurface(((SDL_Surface*)src->surface));
            
            SDL_Rect dest_rect = { x, y, src->w, src->h };
            SDL_BlitSurface(flipped, NULL, dest->surface, &dest_rect);
            SDL_FreeSurface(flipped);
        }
    }
}

void platform_rotate_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                           int x, int y, int angle) {
    // Rotation requires SDL2_gfx or manual implementation
    // For now, just draw without rotation
    platform_draw_sprite(dest, src, x, y);
}

void platform_pivot_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                          int x, int y, int cx, int cy, int angle) {
    // Rotation requires SDL2_gfx or manual implementation
    // For now, just draw without rotation
    platform_draw_sprite(dest, src, x - cx, y - cy);
}

PlatformColor platform_getpixel(PlatformBitmap *bitmap, int x, int y) {
    if (bitmap && bitmap->surface && x >= 0 && x < bitmap->w && y >= 0 && y < bitmap->h) {
        SDL_Surface *surf = (SDL_Surface*)bitmap->surface;
        SDL_LockSurface(surf);
        Uint32 *pixels = (Uint32*)surf->pixels;
        PlatformColor color = pixels[y * (surf->pitch / 4) + x];
        SDL_UnlockSurface(surf);
        return color;
    }
    return 0;
}

void platform_putpixel(PlatformBitmap *bitmap, int x, int y, PlatformColor color) {
    if (bitmap && bitmap->surface && x >= 0 && x < bitmap->w && y >= 0 && y < bitmap->h) {
        SDL_Surface *surf = (SDL_Surface*)bitmap->surface;
        SDL_LockSurface(surf);
        Uint32 *pixels = (Uint32*)surf->pixels;
        pixels[y * (surf->pitch / 4) + x] = color;
        SDL_UnlockSurface(surf);
    }
}

// ============================================================================
// GRAPHICS - PRIMITIVES
// ============================================================================

void platform_line(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap && bitmap->surface) {
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
}

void platform_rect(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap && bitmap->surface) {
        platform_line(bitmap, x1, y1, x2, y1, color);
        platform_line(bitmap, x2, y1, x2, y2, color);
        platform_line(bitmap, x2, y2, x1, y2, color);
        platform_line(bitmap, x1, y2, x1, y1, color);
    }
}

void platform_rectfill(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap && bitmap->surface) {
        SDL_Rect rect = { x1, y1, x2 - x1 + 1, y2 - y1 + 1 };
        SDL_FillRect(bitmap->surface, &rect, color);
    }
}

void platform_circle(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color) {
    if (bitmap && bitmap->surface) {
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
}

void platform_circlefill(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color) {
    if (bitmap && bitmap->surface) {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (i * i + j * j <= radius * radius) {
                    platform_putpixel(bitmap, x + i, y + j, color);
                }
            }
        }
    }
}

PlatformColor platform_makecol(int r, int g, int b) {
    return SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), r, g, b);
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
    // Try to load as TTF, with fallback size
    int size = 16;  // Default size
    
    TTF_Font *font = TTF_OpenFont(filename, size);
    if (!font) {
        // Try alternate extension
        char alt_filename[512];
        strncpy(alt_filename, filename, sizeof(alt_filename) - 5);
        alt_filename[sizeof(alt_filename) - 5] = '\0';
        
        char *ext = strrchr(alt_filename, '.');
        if (ext) {
            strcpy(ext, ".ttf");
            font = TTF_OpenFont(alt_filename, size);
        }
    }
    
    if (!font) {
        return NULL;
    }
    
    PlatformFont *pf = (PlatformFont*)malloc(sizeof(PlatformFont));
    if (pf) {
        pf->font = font;
        pf->size = size;
    } else {
        TTF_CloseFont(font);
    }
    
    return pf;
}

void platform_destroy_font(PlatformFont *font) {
    if (font) {
        if (font->font) {
            TTF_CloseFont(font->font);
        }
        free(font);
    }
}

void platform_textout_ex(PlatformBitmap *bitmap, PlatformFont *font,
                        const char *text, int x, int y,
                        PlatformColor color, PlatformColor bg) {
    if (bitmap && bitmap->surface && font && font->font && text) {
        SDL_Color fg = { (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 255 };
        SDL_Surface *text_surface = TTF_RenderText_Solid(font->font, text, fg);
        
        if (text_surface) {
            SDL_Rect dest_rect = { x, y, text_surface->w, text_surface->h };
            SDL_BlitSurface(text_surface, NULL, bitmap->surface, &dest_rect);
            SDL_FreeSurface(text_surface);
        }
    }
}

void platform_textout_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                               const char *text, int x, int y,
                               PlatformColor color, PlatformColor bg) {
    if (bitmap && bitmap->surface && font && font->font && text) {
        int w, h;
        if (TTF_SizeText(font->font, text, &w, &h) == 0) {
            platform_textout_ex(bitmap, font, text, x - w / 2, y, color, bg);
        }
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
        
        if (written >= (int)sizeof(buffer)) {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        
        platform_textout_ex(bitmap, font, buffer, x, y, color, bg);
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
        
        if (written >= (int)sizeof(buffer)) {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        
        platform_textout_centre_ex(bitmap, font, buffer, x, y, color, bg);
    }
}

// ============================================================================
// AUDIO
// ============================================================================

int platform_install_sound(int digi, int midi, const char *cfg) {
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        return -1;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio failed: %s\n", Mix_GetError());
        return -1;
    }
    
    Mix_AllocateChannels(16);
    return 0;
}

PlatformSample* platform_load_sample(const char *filename) {
    Mix_Chunk *chunk = Mix_LoadWAV(filename);
    
    if (!chunk) {
        // Try alternate extension
        char alt_filename[512];
        strncpy(alt_filename, filename, sizeof(alt_filename) - 5);
        alt_filename[sizeof(alt_filename) - 5] = '\0';
        
        char *ext = strrchr(alt_filename, '.');
        if (ext) {
            strcpy(ext, ".ogg");
            chunk = Mix_LoadWAV(alt_filename);
        }
    }
    
    if (!chunk) {
        return NULL;
    }
    
    PlatformSample *ps = (PlatformSample*)malloc(sizeof(PlatformSample));
    if (ps) {
        ps->chunk = chunk;
        ps->channel = -1;
    } else {
        Mix_FreeChunk(chunk);
    }
    
    return ps;
}

PlatformMidi* platform_load_midi(const char *filename) {
    Mix_Music *music = Mix_LoadMUS(filename);
    
    if (!music) {
        // Try alternate extension
        char alt_filename[512];
        strncpy(alt_filename, filename, sizeof(alt_filename) - 5);
        alt_filename[sizeof(alt_filename) - 5] = '\0';
        
        char *ext = strrchr(alt_filename, '.');
        if (ext) {
            strcpy(ext, ".ogg");
            music = Mix_LoadMUS(alt_filename);
        }
    }
    
    if (!music) {
        return NULL;
    }
    
    PlatformMidi *pm = (PlatformMidi*)malloc(sizeof(PlatformMidi));
    if (pm) {
        pm->music = music;
    } else {
        Mix_FreeMusic(music);
    }
    
    return pm;
}

void platform_destroy_sample(PlatformSample *sample) {
    if (sample) {
        if (sample->chunk) {
            Mix_FreeChunk(sample->chunk);
        }
        free(sample);
    }
}

void platform_destroy_midi(PlatformMidi *midi) {
    if (midi) {
        if (midi->music) {
            Mix_FreeMusic(midi->music);
        }
        free(midi);
    }
}

int platform_play_sample(PlatformSample *sample, int vol, int pan, int freq, int loop) {
    if (sample && sample->chunk) {
        Mix_VolumeChunk(sample->chunk, (vol * MIX_MAX_VOLUME) / 255);
        sample->channel = Mix_PlayChannel(-1, sample->chunk, loop ? -1 : 0);
        return sample->channel;
    }
    return -1;
}

int platform_play_midi(PlatformMidi *midi, int loop) {
    if (midi && midi->music) {
        return Mix_PlayMusic(midi->music, loop ? -1 : 0);
    }
    return -1;
}

void platform_stop_midi(void) {
    Mix_HaltMusic();
}

void platform_set_volume(int digi, int midi) {
    Mix_Volume(-1, (digi * MIX_MAX_VOLUME) / 255);
    Mix_VolumeMusic((midi * MIX_MAX_VOLUME) / 255);
}

void platform_adjust_sample(PlatformSample *sample, int vol, int pan, int freq, int loop) {
    if (sample && sample->chunk) {
        Mix_VolumeChunk(sample->chunk, (vol * MIX_MAX_VOLUME) / 255);
        if (sample->channel >= 0) {
            Mix_Volume(sample->channel, (vol * MIX_MAX_VOLUME) / 255);
        }
    }
}

// ============================================================================
// CONFIG FILE
// ============================================================================

// Simple INI file parser for SDL2
static char config_file[512] = "config.ini";
static char config_buffer[65536];

void platform_set_config_file(const char *filename) {
    strncpy(config_file, filename, sizeof(config_file) - 1);
    config_file[sizeof(config_file) - 1] = '\0';
}

int platform_get_config_int(const char *section, const char *key, int default_value) {
    FILE *f = fopen(config_file, "r");
    if (!f) return default_value;
    
    char line[256];
    int in_section = 0;
    
    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        
        // Check for section
        if (line[0] == '[') {
            char *end = strchr(line, ']');
            if (end) {
                *end = 0;
                in_section = (strcmp(line + 1, section) == 0);
            }
        } else if (in_section) {
            // Check for key
            char *eq = strchr(line, '=');
            if (eq) {
                *eq = 0;
                char *k = line;
                char *v = eq + 1;
                
                // Trim whitespace
                while (*k == ' ') k++;
                while (*v == ' ') v++;
                
                if (strcmp(k, key) == 0) {
                    fclose(f);
                    return atoi(v);
                }
            }
        }
    }
    
    fclose(f);
    return default_value;
}

const char* platform_get_config_string(const char *section, const char *key, const char *default_value) {
    FILE *f = fopen(config_file, "r");
    if (!f) return default_value;
    
    char line[256];
    int in_section = 0;
    
    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        
        // Check for section
        if (line[0] == '[') {
            char *end = strchr(line, ']');
            if (end) {
                *end = 0;
                in_section = (strcmp(line + 1, section) == 0);
            }
        } else if (in_section) {
            // Check for key
            char *eq = strchr(line, '=');
            if (eq) {
                *eq = 0;
                char *k = line;
                char *v = eq + 1;
                
                // Trim whitespace
                while (*k == ' ') k++;
                while (*v == ' ') v++;
                
                if (strcmp(k, key) == 0) {
                    fclose(f);
                    strncpy(config_buffer, v, sizeof(config_buffer) - 1);
                    config_buffer[sizeof(config_buffer) - 1] = '\0';
                    return config_buffer;
                }
            }
        }
    }
    
    fclose(f);
    return default_value;
}

void platform_set_config_int(const char *section, const char *key, int value) {
    // Not implemented for now
}

void platform_set_config_string(const char *section, const char *key, const char *value) {
    // Not implemented for now
}


int platform_file_exists(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return 1;
    }
    return 0;
}

float platform_get_config_float(const char *section, const char *key, float default_value) {
    const char *str = platform_get_config_string(section, key, "");
    if (str && *str) {
        return atof(str);
    }
    return default_value;
}

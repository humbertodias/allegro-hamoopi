// platform_sdl2.c - SDL2 implementation of platform abstraction layer

#include "platform.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include "minIni.h"


// Global state
static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_Texture *g_screen_texture = NULL;
static PlatformBitmap *g_screen = NULL;
static volatile Uint8 *g_sdl_key_state = NULL;
static int g_key_state_size = 0;
static void (*g_close_callback)(void) = NULL;

// Drawing state
static int g_drawing_mode = PDRAW_MODE_SOLID;
static int g_trans_alpha = 255;

// Helper function to update screen using renderer and texture
static void update_screen_with_renderer(void) {
    if (g_screen && g_screen->surface && g_renderer && g_screen_texture) {
        // Update texture with screen surface data
        SDL_UpdateTexture(g_screen_texture, NULL,
                        ((SDL_Surface*)g_screen->surface)->pixels,
                        ((SDL_Surface*)g_screen->surface)->pitch);

        // Clear renderer
        SDL_RenderClear(g_renderer);

        // Copy texture to renderer
        SDL_RenderCopy(g_renderer, g_screen_texture, NULL, NULL);

        // Present renderer
        SDL_RenderPresent(g_renderer);
    }
}

// Mouse state (exported for compatibility)
volatile int platform_mouse_x = 0;
volatile int platform_mouse_y = 0;
volatile int platform_mouse_b = 0;

// Key mapping from platform keys to SDL scancodes
static SDL_Scancode platform_to_sdl_key[256];

// Translated key state array (Allegro-indexed to SDL state)
static volatile char g_translated_key_state[256];

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


// ============================================================================
// INITIALIZATION & SYSTEM
// ============================================================================

int platform_init(void) {
    // Set SDL hints for better performance
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");  // Disable VSync via hint as well
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  // Nearest neighbor (faster)
    SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "1");  // Enable if available
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d,opengl,opengles2,software");  // Prefer hardware

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
    g_sdl_key_state = SDL_GetKeyboardState(&g_key_state_size);

    // Initialize translated key state array
    memset((void*)g_translated_key_state, 0, sizeof(g_translated_key_state));

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

    // Destroy existing resources if they exist
    if (g_screen_texture) {
        SDL_DestroyTexture(g_screen_texture);
        g_screen_texture = NULL;
    }
    if (g_renderer) {
        SDL_DestroyRenderer(g_renderer);
        g_renderer = NULL;
    }
    if (g_screen) {
        if (g_screen->surface) {
            SDL_FreeSurface((SDL_Surface*)g_screen->surface);
        }
        free(g_screen);
        g_screen = NULL;
    }
    if (g_window) {
        SDL_DestroyWindow(g_window);
        g_window = NULL;
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

    // Create renderer with hardware acceleration
    // Note: PRESENTVSYNC removed - let game loop control frame timing
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(g_window);
        g_window = NULL;
        return -1;
    }

    // Create streaming texture for the screen
    g_screen_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888,
                                         SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!g_screen_texture) {
        fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
        SDL_DestroyRenderer(g_renderer);
        SDL_DestroyWindow(g_window);
        g_renderer = NULL;
        g_window = NULL;
        return -1;
    }

    // Create screen surface (for drawing operations)
    g_screen = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (g_screen) {
        g_screen->surface = SDL_CreateRGBSurface(0, width, height, 32,
                                                  0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        g_screen->w = width;
        g_screen->h = height;

        // Don't set color key on screen surface - it's the final composite
        // Screen surface should have blending disabled for direct pixel writes
        if (g_screen->surface) {
            SDL_Surface *surf = (SDL_Surface*)g_screen->surface;
            SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_NONE);
        }
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

void platform_install_int_ex(void (*callback)(void), int interval_us) {
    // Timer callbacks are no longer used in SDL2 implementation
    // Frame timing is now handled by platform_present_screen() and SDL_Delay()
    // This function is kept for API compatibility but does nothing
    (void)callback;
    (void)interval_us;
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

    // Translate SDL keyboard state to Allegro key indices
    // Clear the translated state first
    memset((void*)g_translated_key_state, 0, sizeof(g_translated_key_state));

    // Map each platform key to SDL scancode and check if it's pressed
    for (int i = 0; i < 256; i++) {
        SDL_Scancode scancode = platform_to_sdl_key[i];
        if (scancode != 0 && scancode < g_key_state_size) {
            g_translated_key_state[i] = g_sdl_key_state[scancode];
        }
    }

    return g_translated_key_state;
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
        pb->w = width;
        pb->h = height;

        if (!pb->surface) {
            free(pb);
            return NULL;
        }

        // Set magenta (255, 0, 255) as the color key for transparency
        SDL_Surface *surf = (SDL_Surface*)pb->surface;
        SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));
    }
    return pb;
}

void platform_destroy_bitmap(PlatformBitmap *bitmap) {
    if (bitmap) {
        if (bitmap->surface) {
            SDL_FreeSurface(bitmap->surface);
        }
        free(bitmap);
    }
}

PlatformBitmap* platform_load_bitmap(const char *filename, void *palette) {

    SDL_Surface *loaded = IMG_Load(filename);
    if (!loaded) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "IMG_Load failed for '%s': %s",
                     filename, IMG_GetError());
        return NULL;
    }

    SDL_Surface *surface = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(loaded);

    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "SDL_ConvertSurfaceFormat failed for '%s': %s",
                     filename, SDL_GetError());
        return NULL;
    }

    // Enable transparency (magenta)
    Uint32 colorkey = SDL_MapRGB(surface->format, 255, 0, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorkey);

    PlatformBitmap *pb = malloc(sizeof(PlatformBitmap));
    if (!pb) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "malloc() failed allocating PlatformBitmap for '%s'", filename);
        SDL_FreeSurface(surface);
        return NULL;
    }

    pb->surface = surface;
    pb->w = surface->w;
    pb->h = surface->h;

    return pb;
}



void platform_clear_bitmap(PlatformBitmap *bitmap) {
    if (bitmap && bitmap->surface) {
        SDL_FillRect(bitmap->surface, NULL, 0);
    }
}

void platform_clear_to_color(PlatformBitmap *bitmap, PlatformColor color) {
    if (bitmap && bitmap->surface) {
        SDL_Surface *surf = (SDL_Surface*)bitmap->surface;
        SDL_FillRect(surf, NULL, color);

        // If clearing to magenta (255, 0, 255), set it as the color key for transparency
        // This is the standard Allegro transparency color
        if ((color & 0x00FFFFFF) == 0x00FF00FF) {  // Check if RGB is 255, 0, 255
            SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));
        }
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
    if (src && src->surface && dest && dest->surface) {
        SDL_Rect src_rect = { src_x, src_y, src_w, src_h };
        SDL_Rect dest_rect = { dest_x, dest_y, dest_w, dest_h };
        SDL_BlitScaled((SDL_Surface*)src->surface, &src_rect, (SDL_Surface*)dest->surface, &dest_rect);
    }
}

void platform_blit(PlatformBitmap *src, PlatformBitmap *dest,
                  int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    if (src && src->surface && dest && dest->surface) {
        // Clear destination surface if blitting to the top-left corner (0,0)
        // This prevents artifacts when reusing sprite buffers across frames
        if (dest_x == 0 && dest_y == 0 && src_x == 0 && src_y == 0) {
            SDL_FillRect((SDL_Surface*)dest->surface, NULL,
                         SDL_MapRGBA(((SDL_Surface*)dest->surface)->format, 0, 0, 0, 0));
        }

        SDL_Rect src_rect = { src_x, src_y, w, h };
        SDL_Rect dest_rect = { dest_x, dest_y, w, h };
        SDL_BlitSurface((SDL_Surface*)src->surface, &src_rect, (SDL_Surface*)dest->surface, &dest_rect);
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
        SDL_Surface *surface = (SDL_Surface *)bitmap->surface;
        SDL_Rect rect = { x1, y1, x2 - x1 + 1, y2 - y1 + 1 };

        if (g_drawing_mode == PDRAW_MODE_TRANS) {
            // Extract RGB components from the color
            SDL_PixelFormat *fmt = surface->format;
            Uint8 r, g, b, a;
            SDL_GetRGBA(color, fmt, &r, &g, &b, &a);

            // Apply transparency by blending manually
            SDL_LockSurface(surface);
            for (int y = rect.y; y < rect.y + rect.h && y < surface->h; y++) {
                for (int x = rect.x; x < rect.x + rect.w && x < surface->w; x++) {
                    if (x >= 0 && y >= 0) {
                        // Get the destination pixel
                        Uint32 *pixels = (Uint32 *)surface->pixels;
                        Uint32 dst_pixel = pixels[y * (surface->pitch / 4) + x];

                        // Get destination RGB
                        Uint8 dst_r, dst_g, dst_b;
                        SDL_GetRGB(dst_pixel, fmt, &dst_r, &dst_g, &dst_b);

                        // Alpha blend: result = src * alpha + dst * (1 - alpha)
                        float alpha = g_trans_alpha / 255.0f;
                        Uint8 result_r = (Uint8)(r * alpha + dst_r * (1.0f - alpha));
                        Uint8 result_g = (Uint8)(g * alpha + dst_g * (1.0f - alpha));
                        Uint8 result_b = (Uint8)(b * alpha + dst_b * (1.0f - alpha));

                        // Write blended pixel
                        pixels[y * (surface->pitch / 4) + x] = SDL_MapRGB(fmt, result_r, result_g, result_b);
                    }
                }
            }
            SDL_UnlockSurface(surface);
        } else {
            // Solid mode - use normal SDL_FillRect
            SDL_FillRect(surface, &rect, color);
        }
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

    int size = 16;  // Default size
    TTF_Font *font = TTF_OpenFont(filename, size);

    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "TTF_OpenFont failed for '%s': %s",
                     filename, TTF_GetError());
        return NULL;
    }

    PlatformFont *pf = (PlatformFont*)malloc(sizeof(PlatformFont));
    if (!pf) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "malloc() failed when allocating PlatformFont.");
        TTF_CloseFont(font);
        return NULL;
    }

    pf->font = font;
    pf->size = size;

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
        SDL_Surface *text_surface = TTF_RenderUTF8_Blended(font->font, text, fg);

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

// minIni configuration - uses standard stdio
static char config_file[512] = "config.ini";

void platform_set_config_file(const char *filename) {
    strncpy(config_file, filename, sizeof(config_file) - 1);
    config_file[sizeof(config_file) - 1] = '\0';
}

int platform_get_config_int(const char *section, const char *key, int default_value) {
    return (int)ini_getl(section, key, (long)default_value, config_file);
}

const char* platform_get_config_string(const char *section, const char *key, const char *default_value)
{
    static char out[256]; // static buffer for return value
    ini_gets(section, key, default_value ? default_value : "", out, sizeof(out), config_file);
    return out;
}

void platform_set_config_int(const char *section, const char *key, int value) {
    ini_putl(section, key, (long)value, config_file);
}

void platform_set_config_string(const char *section, const char *key, const char *value) {
    ini_puts(section, key, value, config_file);
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

int platform_getr(PlatformColor color) {
    return (color >> 16) & 0xFF;
}

int platform_getg(PlatformColor color) {
    return (color >> 8) & 0xFF;
}

int platform_getb(PlatformColor color) {
    return color & 0xFF;
}

void platform_rest(int milliseconds) {
    SDL_Delay(milliseconds);
}

void platform_drawing_mode(int mode, void *pattern, int x_anchor, int y_anchor) {
    g_drawing_mode = mode;
    // Note: SDL2 doesn't have direct equivalent, would need custom implementation
}

void platform_masked_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                                  int src_x, int src_y, int src_w, int src_h,
                                  int dest_x, int dest_y, int dest_w, int dest_h) {
    // SDL2 blit is already masked
    platform_stretch_blit(src, dest, src_x, src_y, src_w, src_h, dest_x, dest_y, dest_w, dest_h);
}

void platform_clear(PlatformBitmap *bitmap) {
    platform_clear_bitmap(bitmap);
}

void platform_clear_keybuf(void) {
    // SDL2 event queue is cleared automatically
    SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYUP);
}

void platform_set_trans_blender(int r, int g, int b, int a) {
    // Store alpha value for transparent drawing operations
    g_trans_alpha = a;
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

        // Calculate width and draw right-aligned
        int w, h;
        if (TTF_SizeText((TTF_Font*)font->font, buffer, &w, &h) == 0) {
            platform_textout_ex(bitmap, font, buffer, x - w, y, color, bg);
        }
    }
}

void platform_alert_message(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    fprintf(stderr, "ALERT: %s\n", buffer);
    if (g_window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "HAMOOPI", buffer, g_window);
    }
}

void platform_stretch_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y, int w, int h) {
    if (dest && src) {
        platform_stretch_blit(src, dest, 0, 0, src->w, src->h, x, y, w, h);
    }
}
void platform_solid_mode(void) { g_drawing_mode = PDRAW_MODE_SOLID; }
void platform_draw_trans_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) { platform_draw_sprite(dest, src, x, y); }

void platform_present_screen(void) {
    // Update the screen texture and present it to the window
    update_screen_with_renderer();
}
#include "allegro_compat.h"
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

// Global variables
SDL_Window* _sdl_window = nullptr;
SDL_Renderer* _sdl_renderer = nullptr;
BITMAP* screen = nullptr;
const Uint8* key = nullptr;
int mouse_x = 0;
int mouse_y = 0;
int mouse_b = 0;

// Configuration management
std::map<std::string, std::map<std::string, std::string>> _config_data;
std::string _current_config_file;

// Timer management
static Uint32 _timer_callback_id = 0;
static timer_callback_t _timer_callback = nullptr;
static int _timer_interval = 0;

// Close button callback
static void (*_close_callback)(void) = nullptr;

// Keyboard state
static Uint8* _key_state = nullptr;

// Drawing mode state
static int _current_drawing_mode = DRAW_MODE_SOLID;
static Uint8 _trans_alpha = 255;

// Timer callback wrapper
static Uint32 _timer_callback_wrapper(Uint32 interval, void* param) {
    if (_timer_callback) {
        _timer_callback();
    }
    return interval;
}

// Initialization functions
int allegro_init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        fprintf(stderr, "IMG_Init failed: %s\n", IMG_GetError());
    }
    
    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
    }
    
    return 0;
}

void install_timer() {
    // Timer is initialized with SDL_Init
}

void install_keyboard() {
    _key_state = (Uint8*)SDL_GetKeyboardState(nullptr);
    key = (const Uint8*)_key_state;
}

void install_mouse() {
    // Mouse is automatically available in SDL2
}

int install_sound(int digi, int midi, const char* cfg_path) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio failed: %s\n", Mix_GetError());
        return -1;
    }
    
    Mix_AllocateChannels(16);
    return 0;
}

void set_color_depth(int depth) {
    // Color depth is handled by SDL2 automatically
}

int set_gfx_mode(int card, int w, int h, int v_w, int v_h) {
    Uint32 flags = SDL_WINDOW_SHOWN;
    
    if (card == GFX_AUTODETECT_FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    
    if (_sdl_window) {
        if (card == GFX_AUTODETECT_FULLSCREEN) {
            SDL_SetWindowFullscreen(_sdl_window, SDL_WINDOW_FULLSCREEN);
        } else {
            SDL_SetWindowFullscreen(_sdl_window, 0);
            SDL_SetWindowSize(_sdl_window, w, h);
        }
    } else {
        _sdl_window = SDL_CreateWindow("HAMOOPI",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       w, h, flags);
        if (!_sdl_window) {
            fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
            return -1;
        }
        
        _sdl_renderer = SDL_CreateRenderer(_sdl_window, -1,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!_sdl_renderer) {
            fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
            return -1;
        }
        
        SDL_SetRenderDrawBlendMode(_sdl_renderer, SDL_BLENDMODE_BLEND);
        
        // Create screen bitmap
        if (!screen) {
            screen = create_bitmap(w, h);
        }
    }
    
    return 0;
}

void set_window_title(const char* title) {
    if (_sdl_window) {
        SDL_SetWindowTitle(_sdl_window, title);
    }
}

void set_close_button_callback(void (*callback)(void)) {
    _close_callback = callback;
}

void install_int_ex(timer_callback_t callback, int speed) {
    _timer_callback = callback;
    _timer_interval = speed / 1000; // Convert microseconds to milliseconds
    if (_timer_callback_id) {
        SDL_RemoveTimer(_timer_callback_id);
    }
    _timer_callback_id = SDL_AddTimer(_timer_interval, _timer_callback_wrapper, nullptr);
}

void set_uformat(int format) {
    // UTF-8 is default in SDL2
}

// Bitmap functions
BITMAP* create_bitmap(int width, int height) {
    BITMAP* bmp = new BITMAP();
    bmp->w = width;
    bmp->h = height;
    
    // Create surface
    bmp->surface = SDL_CreateRGBSurface(0, width, height, 32,
                                        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    
    // Create texture with TARGET access so we can render to it
    if (_sdl_renderer) {
        bmp->texture = SDL_CreateTexture(_sdl_renderer, SDL_PIXELFORMAT_ARGB8888,
                                         SDL_TEXTUREACCESS_TARGET, width, height);
        if (bmp->texture) {
            SDL_SetTextureBlendMode(bmp->texture, SDL_BLENDMODE_BLEND);
        }
    } else {
        bmp->texture = nullptr;
    }
    
    bmp->line = nullptr;
    
    return bmp;
}

SDL_Surface* _load_pcx(const char* filename) {
    // PCX files need special handling
    SDL_Surface* surf = IMG_Load(filename);
    if (!surf) {
        // Try with SDL_LoadBMP as fallback
        surf = SDL_LoadBMP(filename);
    }
    return surf;
}

BITMAP* load_bitmap(const char* filename, void* pal) {
    SDL_Surface* surf = _load_pcx(filename);
    if (!surf) {
        return nullptr;
    }
    
    BITMAP* bmp = new BITMAP();
    bmp->w = surf->w;
    bmp->h = surf->h;
    
    // Set magenta (255, 0, 255) as transparent
    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 255, 0, 255));
    
    bmp->surface = surf;
    
    // Create TARGET texture so we can render to it later
    if (_sdl_renderer) {
        bmp->texture = SDL_CreateTexture(_sdl_renderer, SDL_PIXELFORMAT_ARGB8888,
                                         SDL_TEXTUREACCESS_TARGET, surf->w, surf->h);
        if (bmp->texture) {
            SDL_SetTextureBlendMode(bmp->texture, SDL_BLENDMODE_BLEND);
            
            // Copy surface content to texture
            SDL_Texture* temp_tex = SDL_CreateTextureFromSurface(_sdl_renderer, surf);
            if (temp_tex) {
                SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
                SDL_RenderCopy(_sdl_renderer, temp_tex, nullptr, nullptr);
                SDL_SetRenderTarget(_sdl_renderer, nullptr);
                SDL_DestroyTexture(temp_tex);
            }
        }
    } else {
        bmp->texture = nullptr;
    }
    
    bmp->line = nullptr;
    
    return bmp;
}

void destroy_bitmap(BITMAP* bmp) {
    if (!bmp) return;
    
    if (bmp->texture) {
        SDL_DestroyTexture(bmp->texture);
    }
    if (bmp->surface) {
        SDL_FreeSurface(bmp->surface);
    }
    delete bmp;
}

void clear(BITMAP* bmp) {
    if (!bmp || !bmp->surface) return;
    SDL_FillRect(bmp->surface, nullptr, 0);
    
    if (bmp->texture && _sdl_renderer) {
        SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
        SDL_SetRenderDrawColor(_sdl_renderer, 0, 0, 0, 0);
        SDL_RenderClear(_sdl_renderer);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void clear_to_color(BITMAP* bmp, int color) {
    if (!bmp || !bmp->surface) return;
    
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;
    
    SDL_FillRect(bmp->surface, nullptr, SDL_MapRGB(bmp->surface->format, r, g, b));
    
    if (bmp->texture && _sdl_renderer) {
        SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
        SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, 255);
        SDL_RenderClear(_sdl_renderer);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void clear_keybuf() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            // Clear keyboard events
        }
    }
}

// Drawing functions - these need to update both surface and texture
void blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) {
    if (!source || !dest) return;
    
    SDL_Rect src_rect = {source_x, source_y, width, height};
    SDL_Rect dst_rect = {dest_x, dest_y, width, height};
    
    // Blit to surface
    if (source->surface && dest->surface) {
        SDL_BlitSurface(source->surface, &src_rect, dest->surface, &dst_rect);
    }
    
    // Blit to texture
    if (source->texture && dest == screen && _sdl_renderer) {
        SDL_RenderCopy(_sdl_renderer, source->texture, &src_rect, &dst_rect);
    } else if (source->texture && dest->texture && _sdl_renderer) {
        SDL_SetRenderTarget(_sdl_renderer, dest->texture);
        SDL_RenderCopy(_sdl_renderer, source->texture, &src_rect, &dst_rect);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void masked_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) {
    // Same as blit for SDL2 with alpha blending
    blit(source, dest, source_x, source_y, dest_x, dest_y, width, height);
}

void stretch_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h) {
    if (!source || !dest) return;
    
    SDL_Rect src_rect = {source_x, source_y, source_w, source_h};
    SDL_Rect dst_rect = {dest_x, dest_y, dest_w, dest_h};
    
    // Blit to surface with scaling
    if (source->surface && dest->surface) {
        SDL_BlitScaled(source->surface, &src_rect, dest->surface, &dst_rect);
    }
    
    // Render to screen
    if (dest == screen && _sdl_renderer) {
        if (source->texture) {
            SDL_RenderCopy(_sdl_renderer, source->texture, &src_rect, &dst_rect);
        } else if (source->surface && source->texture) {
            // Update texture from surface if needed
            SDL_UpdateTexture(source->texture, nullptr, source->surface->pixels, source->surface->pitch);
            SDL_RenderCopy(_sdl_renderer, source->texture, &src_rect, &dst_rect);
        }
        // Note: SDL_RenderPresent is called once per frame in main game loop, not here
    } else if (source->texture && dest->texture && _sdl_renderer) {
        SDL_SetRenderTarget(_sdl_renderer, dest->texture);
        SDL_RenderCopy(_sdl_renderer, source->texture, &src_rect, &dst_rect);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void masked_stretch_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h) {
    stretch_blit(source, dest, source_x, source_y, source_w, source_h, dest_x, dest_y, dest_w, dest_h);
}

void draw_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y) {
    if (!sprite || !bmp) return;
    blit(sprite, bmp, 0, 0, x, y, sprite->w, sprite->h);
}

void draw_trans_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y) {
    if (!sprite || !bmp) return;
    
    // Transparent drawing with current alpha
    if (sprite->texture && _sdl_renderer) {
        SDL_SetTextureAlphaMod(sprite->texture, _trans_alpha);
    }
    
    blit(sprite, bmp, 0, 0, x, y, sprite->w, sprite->h);
    
    // Restore full alpha
    if (sprite->texture && _sdl_renderer) {
        SDL_SetTextureAlphaMod(sprite->texture, 255);
    }
}

void draw_sprite_h_flip(BITMAP* bmp, BITMAP* sprite, int x, int y) {
    if (!sprite || !bmp || !_sdl_renderer) return;
    
    SDL_Rect dst_rect = {x, y, sprite->w, sprite->h};
    
    if (bmp == screen) {
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void draw_sprite_v_flip(BITMAP* bmp, BITMAP* sprite, int x, int y) {
    if (!sprite || !bmp || !_sdl_renderer) return;
    
    SDL_Rect dst_rect = {x, y, sprite->w, sprite->h};
    
    if (bmp == screen) {
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, 0, nullptr, SDL_FLIP_VERTICAL);
    } else {
        SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, 0, nullptr, SDL_FLIP_VERTICAL);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void draw_sprite_vh_flip(BITMAP* bmp, BITMAP* sprite, int x, int y) {
    if (!sprite || !bmp || !_sdl_renderer) return;
    
    SDL_Rect dst_rect = {x, y, sprite->w, sprite->h};
    SDL_RendererFlip flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    
    if (bmp == screen) {
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, 0, nullptr, flip);
    } else {
        SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, 0, nullptr, flip);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void stretch_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y, int w, int h) {
    if (!sprite || !bmp) return;
    stretch_blit(sprite, bmp, 0, 0, sprite->w, sprite->h, x, y, w, h);
}

void rotate_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y, int angle) {
    if (!sprite || !bmp || !_sdl_renderer) return;
    
    SDL_Rect dst_rect = {x, y, sprite->w, sprite->h};
    double degrees = (angle / 256.0) * 360.0;
    
    if (bmp == screen) {
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, degrees, nullptr, SDL_FLIP_NONE);
    } else {
        SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, degrees, nullptr, SDL_FLIP_NONE);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void pivot_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y, int cx, int cy, int angle) {
    if (!sprite || !bmp || !_sdl_renderer) return;
    
    SDL_Rect dst_rect = {x - cx, y - cy, sprite->w, sprite->h};
    SDL_Point center = {cx, cy};
    double degrees = (angle / 256.0) * 360.0;
    
    if (bmp == screen) {
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, degrees, &center, SDL_FLIP_NONE);
    } else {
        SDL_SetRenderTarget(_sdl_renderer, bmp->texture);
        SDL_RenderCopyEx(_sdl_renderer, sprite->texture, nullptr, &dst_rect, degrees, &center, SDL_FLIP_NONE);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

// Drawing mode functions
void drawing_mode(int mode, BITMAP* pattern, int x_anchor, int y_anchor) {
    _current_drawing_mode = mode;
}

void solid_mode() {
    _current_drawing_mode = DRAW_MODE_SOLID;
    _trans_alpha = 255;
}

void set_trans_blender(int r, int g, int b, int a) {
    _trans_alpha = a;
}

// Primitive drawing functions
void rectfill(BITMAP* bmp, int x1, int y1, int x2, int y2, int color) {
    if (!bmp) return;
    
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;
    
    SDL_Rect rect = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
    
    if (bmp->surface) {
        SDL_FillRect(bmp->surface, &rect, SDL_MapRGB(bmp->surface->format, r, g, b));
    }
    
    if (bmp->texture && _sdl_renderer) {
        SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
        SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, 255);
        SDL_RenderFillRect(_sdl_renderer, &rect);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void rect(BITMAP* bmp, int x1, int y1, int x2, int y2, int color) {
    if (!bmp || !_sdl_renderer) return;
    
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;
    
    SDL_Rect rect_sdl = {x1, y1, x2 - x1 + 1, y2 - y1 + 1};
    
    SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
    SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, 255);
    SDL_RenderDrawRect(_sdl_renderer, &rect_sdl);
    SDL_SetRenderTarget(_sdl_renderer, nullptr);
}

void line(BITMAP* bmp, int x1, int y1, int x2, int y2, int color) {
    if (!bmp || !_sdl_renderer) return;
    
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;
    
    SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
    SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, 255);
    SDL_RenderDrawLine(_sdl_renderer, x1, y1, x2, y2);
    SDL_SetRenderTarget(_sdl_renderer, nullptr);
}

void hline(BITMAP* bmp, int x1, int y, int x2, int color) {
    line(bmp, x1, y, x2, y, color);
}

void vline(BITMAP* bmp, int x, int y1, int y2, int color) {
    line(bmp, x, y1, x, y2, color);
}

void circle(BITMAP* bmp, int x, int y, int radius, int color) {
    if (!bmp || !_sdl_renderer) return;
    
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;
    
    SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
    SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, 255);
    
    // Midpoint circle algorithm
    int cx = 0;
    int cy = radius;
    int d = 3 - 2 * radius;
    
    while (cy >= cx) {
        SDL_RenderDrawPoint(_sdl_renderer, x + cx, y + cy);
        SDL_RenderDrawPoint(_sdl_renderer, x - cx, y + cy);
        SDL_RenderDrawPoint(_sdl_renderer, x + cx, y - cy);
        SDL_RenderDrawPoint(_sdl_renderer, x - cx, y - cy);
        SDL_RenderDrawPoint(_sdl_renderer, x + cy, y + cx);
        SDL_RenderDrawPoint(_sdl_renderer, x - cy, y + cx);
        SDL_RenderDrawPoint(_sdl_renderer, x + cy, y - cx);
        SDL_RenderDrawPoint(_sdl_renderer, x - cy, y - cx);
        cx++;
        if (d > 0) {
            cy--;
            d = d + 4 * (cx - cy) + 10;
        } else {
            d = d + 4 * cx + 6;
        }
    }
    
    SDL_SetRenderTarget(_sdl_renderer, nullptr);
}

void circlefill(BITMAP* bmp, int x, int y, int radius, int color) {
    if (!bmp || !_sdl_renderer) return;
    
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;
    
    SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
    SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, 255);
    
    // Draw filled circle using horizontal lines
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = (int)sqrt(radius * radius - dy * dy);
        SDL_RenderDrawLine(_sdl_renderer, x - dx, y + dy, x + dx, y + dy);
    }
    
    SDL_SetRenderTarget(_sdl_renderer, nullptr);
}

void putpixel(BITMAP* bmp, int x, int y, int color) {
    if (!bmp || !_sdl_renderer) return;
    
    Uint8 r = (color >> 16) & 0xFF;
    Uint8 g = (color >> 8) & 0xFF;
    Uint8 b = color & 0xFF;
    
    SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
    SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, 255);
    SDL_RenderDrawPoint(_sdl_renderer, x, y);
    SDL_SetRenderTarget(_sdl_renderer, nullptr);
}

int getpixel(BITMAP* bmp, int x, int y) {
    if (!bmp || !bmp->surface) return 0;
    
    SDL_Surface* surf = bmp->surface;
    if (x < 0 || x >= surf->w || y < 0 || y >= surf->h) return 0;
    
    Uint32* pixels = (Uint32*)surf->pixels;
    Uint32 pixel = pixels[y * surf->w + x];
    
    Uint8 r, g, b;
    SDL_GetRGB(pixel, surf->format, &r, &g, &b);
    
    return (r << 16) | (g << 8) | b;
}

// Color functions
int makecol(int r, int g, int b) {
    return (r << 16) | (g << 8) | b;
}

int getr(int color) {
    return (color >> 16) & 0xFF;
}

int getg(int color) {
    return (color >> 8) & 0xFF;
}

int getb(int color) {
    return color & 0xFF;
}

// Font functions
FONT* _load_pcx_font(const char* filename) {
    // Load PCX as bitmap font
    SDL_Surface* surf = _load_pcx(filename);
    if (!surf) return nullptr;
    
    // Convert surface to RGBA format for easier manipulation
    SDL_Surface* rgba_surf = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surf);
    
    if (!rgba_surf) return nullptr;
    
    // Process pixels: make background transparent, keep characters opaque
    SDL_LockSurface(rgba_surf);
    Uint32* pixels = (Uint32*)rgba_surf->pixels;
    int pixel_count = rgba_surf->w * rgba_surf->h;
    
    for (int i = 0; i < pixel_count; i++) {
        Uint8 r, g, b, a;
        SDL_GetRGBA(pixels[i], rgba_surf->format, &r, &g, &b, &a);
        
        // Magenta (transparency color) → fully transparent
        if (r == 255 && g == 0 && b == 255) {
            pixels[i] = SDL_MapRGBA(rgba_surf->format, 255, 255, 255, 0);
        }
        // Yellow borders and other colored pixels (not character) → transparent
        else if ((r == 255 && g == 255 && b == 0) || // yellow
                 (r > 200 && g > 200 && b < 50) ||     // yellowish
                 (r < 50 && g < 50 && b < 50)) {       // black (shouldn't exist but just in case)
            pixels[i] = SDL_MapRGBA(rgba_surf->format, 255, 255, 255, 0);
        }
        // White/light pixels (the characters) → keep as opaque white
        else if (r > 200 && g > 200 && b > 200) {
            pixels[i] = SDL_MapRGBA(rgba_surf->format, 255, 255, 255, 255);
        }
        // Everything else → make transparent
        else {
            pixels[i] = SDL_MapRGBA(rgba_surf->format, 255, 255, 255, 0);
        }
    }
    
    SDL_UnlockSurface(rgba_surf);
    
    FONT* font = new FONT();
    font->ttf_font = nullptr;
    font->char_height = rgba_surf->h / 16; // Assume 16 rows
    font->char_width = rgba_surf->w / 16;  // Assume 16 cols
    
    // Create texture from the modified surface
    font->bitmap_font = SDL_CreateTextureFromSurface(_sdl_renderer, rgba_surf);
    if (font->bitmap_font) {
        SDL_SetTextureBlendMode(font->bitmap_font, SDL_BLENDMODE_BLEND);
    }
    
    SDL_FreeSurface(rgba_surf);
    return font;
}

FONT* load_font(const char* filename, void* pal, void* param) {
    // Try to load as PCX bitmap font first
    FONT* font = _load_pcx_font(filename);
    if (font) return font;
    
    // Try TTF font
    font = new FONT();
    font->ttf_font = TTF_OpenFont(filename, 16);
    font->bitmap_font = nullptr;
    font->char_height = 16;
    font->char_width = 8;
    
    if (!font->ttf_font) {
        delete font;
        return nullptr;
    }
    
    return font;
}

void destroy_font(FONT* f) {
    if (!f) return;
    
    if (f->ttf_font) {
        TTF_CloseFont(f->ttf_font);
    }
    if (f->bitmap_font) {
        SDL_DestroyTexture(f->bitmap_font);
    }
    delete f;
}

void textout_ex(BITMAP* bmp, FONT* f, const char* str, int x, int y, int color, int bg) {
    if (!bmp || !f || !str || !_sdl_renderer) return;
    
    if (f->ttf_font) {
        // TTF font rendering
        SDL_Color fg = {(Uint8)((color >> 16) & 0xFF), (Uint8)((color >> 8) & 0xFF), (Uint8)(color & 0xFF), 255};
        SDL_Surface* text_surf = TTF_RenderText_Solid(f->ttf_font, str, fg);
        if (!text_surf) return;
        
        SDL_Texture* text_tex = SDL_CreateTextureFromSurface(_sdl_renderer, text_surf);
        SDL_Rect dst = {x, y, text_surf->w, text_surf->h};
        
        SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
        SDL_RenderCopy(_sdl_renderer, text_tex, nullptr, &dst);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
        
        SDL_DestroyTexture(text_tex);
        SDL_FreeSurface(text_surf);
    } else if (f->bitmap_font) {
        // Bitmap font rendering
        // Fonts are now white characters on transparent background (converted during loading)
        // So color modulation will work: white * color = color
        
        if (!bmp->texture) return;
        
        SDL_SetRenderTarget(_sdl_renderer, bmp == screen ? nullptr : bmp->texture);
        
        Uint8 r = (color >> 16) & 0xFF;
        Uint8 g = (color >> 8) & 0xFF;
        Uint8 b = color & 0xFF;
        
        // Set color modulation for the bitmap font
        SDL_SetTextureColorMod(f->bitmap_font, r, g, b);
        SDL_SetTextureAlphaMod(f->bitmap_font, 255);
        
        int current_x = x;
        for (const char* c = str; *c != '\0'; c++) {
            unsigned char ch = (unsigned char)*c;
            
            // Calculate source rect in the bitmap font (16x16 grid)
            int char_row = ch / 16;
            int char_col = ch % 16;
            SDL_Rect src_rect = {
                char_col * f->char_width,
                char_row * f->char_height,
                f->char_width,
                f->char_height
            };
            
            SDL_Rect dst_rect = {current_x, y, f->char_width, f->char_height};
            SDL_RenderCopy(_sdl_renderer, f->bitmap_font, &src_rect, &dst_rect);
            
            current_x += f->char_width;
        }
        
        // Reset color modulation
        SDL_SetTextureColorMod(f->bitmap_font, 255, 255, 255);
        SDL_SetTextureAlphaMod(f->bitmap_font, 255);
        SDL_SetRenderTarget(_sdl_renderer, nullptr);
    }
}

void textout_centre_ex(BITMAP* bmp, FONT* f, const char* str, int x, int y, int color, int bg) {
    if (!f || !str) return;
    
    int len = text_length(f, str);
    textout_ex(bmp, f, str, x - len / 2, y, color, bg);
}

void textprintf_ex(BITMAP* bmp, FONT* f, int x, int y, int color, int bg, const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    
    textout_ex(bmp, f, buffer, x, y, color, bg);
}

void textprintf_centre_ex(BITMAP* bmp, FONT* f, int x, int y, int color, int bg, const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    
    textout_centre_ex(bmp, f, buffer, x, y, color, bg);
}

void textprintf_right_ex(BITMAP* bmp, FONT* f, int x, int y, int color, int bg, const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    
    int len = text_length(f, buffer);
    textout_ex(bmp, f, buffer, x - len, y, color, bg);
}

int text_length(FONT* f, const char* str) {
    if (!f || !str) return 0;
    
    if (f->ttf_font) {
        int w = 0;
        TTF_SizeText(f->ttf_font, str, &w, nullptr);
        return w;
    }
    
    return strlen(str) * f->char_width;
}

int text_height(FONT* f) {
    if (!f) return 0;
    return f->char_height;
}

// Audio functions
SAMPLE* load_sample(const char* filename) {
    Mix_Chunk* chunk = Mix_LoadWAV(filename);
    if (!chunk) {
        return nullptr;
    }
    
    SAMPLE* spl = new SAMPLE();
    spl->chunk = chunk;
    return spl;
}

void destroy_sample(SAMPLE* spl) {
    if (!spl) return;
    
    if (spl->chunk) {
        Mix_FreeChunk(spl->chunk);
    }
    delete spl;
}

int play_sample(SAMPLE* spl, int vol, int pan, int freq, int loop) {
    if (!spl || !spl->chunk) return -1;
    
    int channel = Mix_PlayChannel(-1, spl->chunk, loop ? -1 : 0);
    if (channel >= 0) {
        Mix_Volume(channel, (vol * MIX_MAX_VOLUME) / 255);
    }
    return channel;
}

void stop_sample(SAMPLE* spl) {
    // SDL_mixer doesn't track samples, so we stop all channels
    Mix_HaltChannel(-1);
}

void adjust_sample(SAMPLE* spl, int vol, int pan, int freq, int loop) {
    // Adjust all playing channels
    Mix_Volume(-1, (vol * MIX_MAX_VOLUME) / 255);
}

MIDI* load_midi(const char* filename) {
    Mix_Music* music = Mix_LoadMUS(filename);
    if (!music) {
        return nullptr;
    }
    
    MIDI* midi = new MIDI();
    midi->music = music;
    return midi;
}

void destroy_midi(MIDI* midi) {
    if (!midi) return;
    
    if (midi->music) {
        Mix_FreeMusic(midi->music);
    }
    delete midi;
}

int play_midi(MIDI* midi, int loop) {
    if (!midi || !midi->music) return -1;
    
    return Mix_PlayMusic(midi->music, loop ? -1 : 0);
}

void stop_midi() {
    Mix_HaltMusic();
}

void set_volume(int digi_volume, int midi_volume) {
    Mix_Volume(-1, (digi_volume * MIX_MAX_VOLUME) / 255);
    Mix_VolumeMusic((midi_volume * MIX_MAX_VOLUME) / 255);
}

// Configuration functions
void set_config_file(const char* filename) {
    _current_config_file = filename;
    _config_data.clear();
    
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    std::string current_section;
    std::string line;
    
    while (std::getline(file, line)) {
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;
        
        if (line[0] == '[' && line[line.length() - 1] == ']') {
            current_section = line.substr(1, line.length() - 2);
        } else {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                
                // Trim key and value
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                
                _config_data[current_section][key] = value;
            }
        }
    }
    
    file.close();
}

const char* get_config_string(const char* section, const char* key, const char* def) {
    auto sec_it = _config_data.find(section);
    if (sec_it == _config_data.end()) return def;
    
    auto key_it = sec_it->second.find(key);
    if (key_it == sec_it->second.end()) return def;
    
    return key_it->second.c_str();
}

int get_config_int(const char* section, const char* key, int def) {
    const char* str = get_config_string(section, key, nullptr);
    if (!str) return def;
    
    return atoi(str);
}

float get_config_float(const char* section, const char* key, float def) {
    const char* str = get_config_string(section, key, nullptr);
    if (!str) return def;
    
    return atof(str);
}

void set_config_string(const char* section, const char* key, const char* val) {
    _config_data[section][key] = val;
    
    // Write back to file
    std::ofstream file(_current_config_file);
    if (!file.is_open()) return;
    
    for (auto& sec : _config_data) {
        file << "[" << sec.first << "]" << std::endl;
        for (auto& kv : sec.second) {
            file << kv.first << "=" << kv.second << std::endl;
        }
        file << std::endl;
    }
    
    file.close();
}

void set_config_int(const char* section, const char* key, int val) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d", val);
    set_config_string(section, key, buffer);
}

// Utility functions
void allegro_message(const char* msg, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, msg);
    vsnprintf(buffer, sizeof(buffer), msg, args);
    va_end(args);
    
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "HAMOOPI", buffer, _sdl_window);
}

void rest(int ms) {
    SDL_Delay(ms);
}

int exists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0) ? 1 : 0;
}

// Event processing
void _process_sdl_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                if (_close_callback) {
                    _close_callback();
                }
                break;
            case SDL_MOUSEMOTION:
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mouse_b = SDL_GetMouseState(&mouse_x, &mouse_y);
                break;
        }
    }
}

void _update_keyboard_state() {
    SDL_PumpEvents();
    _key_state = (Uint8*)SDL_GetKeyboardState(nullptr);
    key = (const Uint8*)_key_state;
}

void _present_screen() {
    if (_sdl_renderer) {
        SDL_RenderPresent(_sdl_renderer);
    }
}

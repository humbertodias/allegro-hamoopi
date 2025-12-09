#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <string.h>

// 2025 - v02 - SDL2 Version

// DECLARACOES INICIAIS //
int sair = 0;
int timer = 0;
int Ctrl_FPS = 60;
float delay = 0;

// SDL2 globals
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *buffer_texture = NULL;
SDL_Surface *buffer_surface = NULL;
Uint32 timer_interval = 0;

// Timer callback
Uint32 tempo_callback(Uint32 interval, void *param) {
    timer++;
    return interval;
}

// Color functions
Uint32 makecol(int r, int g, int b) {
    return SDL_MapRGB(buffer_surface->format, r, g, b);
}

int getr(Uint32 color) {
    Uint8 r, g, b;
    SDL_GetRGB(color, buffer_surface->format, &r, &g, &b);
    return r;
}

int getg(Uint32 color) {
    Uint8 r, g, b;
    SDL_GetRGB(color, buffer_surface->format, &r, &g, &b);
    return g;
}

int getb(Uint32 color) {
    Uint8 r, g, b;
    SDL_GetRGB(color, buffer_surface->format, &r, &g, &b);
    return b;
}

// Get pixel from surface
Uint32 getpixel(SDL_Surface *surface, int x, int y) {
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return 0;
    
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    
    switch (surface->format->BytesPerPixel) {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

// Put pixel to surface
void putpixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;
    
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
    
    switch (surface->format->BytesPerPixel) {
        case 1:
            *p = color;
            break;
        case 2:
            *(Uint16 *)p = color;
            break;
        case 3:
            p[0] = (color) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
            break;
        case 4:
            *(Uint32 *)p = color;
            break;
    }
}

// Clear surface to color
void clear_to_color(SDL_Surface *surface, Uint32 color) {
    SDL_FillRect(surface, NULL, color);
}

// Blit (copy) one surface to another
void blit(SDL_Surface *src, SDL_Surface *dest, int src_x, int src_y, int dest_x, int dest_y, int width, int height) {
    SDL_Rect src_rect = {src_x, src_y, width, height};
    SDL_Rect dest_rect = {dest_x, dest_y, width, height};
    SDL_BlitSurface(src, &src_rect, dest, &dest_rect);
}

// Stretch blit
void stretch_blit(SDL_Surface *src, SDL_Surface *dest, int src_x, int src_y, int src_w, int src_h,
                  int dest_x, int dest_y, int dest_w, int dest_h) {
    SDL_Rect src_rect = {src_x, src_y, src_w, src_h};
    SDL_Rect dest_rect = {dest_x, dest_y, dest_w, dest_h};
    SDL_BlitScaled(src, &src_rect, dest, &dest_rect);
}

// Draw sprite
void draw_sprite(SDL_Surface *dest, SDL_Surface *sprite, int x, int y) {
    SDL_Rect dest_rect = {x, y, sprite->w, sprite->h};
    SDL_BlitSurface(sprite, NULL, dest, &dest_rect);
}

// Load bitmap (replaces .pcx with .png)
SDL_Surface* load_bitmap(const char *filename) {
    // Replace .pcx with .png
    char png_filename[256];
    strncpy(png_filename, filename, sizeof(png_filename) - 1);
    png_filename[sizeof(png_filename) - 1] = '\0';
    
    char *ext = strrchr(png_filename, '.');
    if (ext && strcmp(ext, ".pcx") == 0) {
        strcpy(ext, ".png");
    }
    
    SDL_Surface *loaded = IMG_Load(png_filename);
    if (!loaded) {
        printf("Failed to load %s: %s\n", png_filename, IMG_GetError());
        return NULL;
    }
    
    // Convert to the same format as buffer for consistent pixel operations
    SDL_Surface *converted = SDL_ConvertSurface(loaded, buffer_surface->format, 0);
    SDL_FreeSurface(loaded);
    
    return converted;
}

// Save bitmap
int save_bitmap(const char *filename, SDL_Surface *surface) {
    // Replace .pcx with .png
    char png_filename[256];
    strncpy(png_filename, filename, sizeof(png_filename) - 1);
    png_filename[sizeof(png_filename) - 1] = '\0';
    
    char *ext = strrchr(png_filename, '.');
    if (ext && strcmp(ext, ".pcx") == 0) {
        strcpy(ext, ".png");
    }
    
    return IMG_SavePNG(surface, png_filename);
}

// Create bitmap
SDL_Surface* create_bitmap(int width, int height) {
    return SDL_CreateRGBSurface(0, width, height, 32, 
                                0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

// Create sub-bitmap
SDL_Surface* create_sub_bitmap(SDL_Surface *parent, int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_Surface *sub = create_bitmap(width, height);
    if (sub) {
        SDL_BlitSurface(parent, &rect, sub, NULL);
    }
    return sub;
}

// Text rendering (simplified - SDL2 doesn't have built-in font, using simple placeholder)
void textprintf_centre_ex(SDL_Surface *surface, int x, int y, Uint32 color, const char *text) {
    // For now, skip text rendering as it requires SDL_ttf and font files
    // This is a minimal implementation
}

void textprintf_right_ex(SDL_Surface *surface, int x, int y, Uint32 color, const char *text) {
    // For now, skip text rendering as it requires SDL_ttf and font files
    // This is a minimal implementation
}

// INICIALIZACAO SDL2 //
int main(int argc, char *argv[])
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    
    // Initialize SDL_image for PNG support
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        printf("IMG_Init failed: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Create window
    window = SDL_CreateWindow("HAMOOPI - PALLETE GENERATOR",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640, 480,
                              SDL_WINDOW_SHOWN);
    
    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    // Create buffer surface
    buffer_surface = create_bitmap(640, 480);
    if (!buffer_surface) {
        printf("Failed to create buffer surface\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    // Create texture for rendering
    buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                       SDL_TEXTUREACCESS_STREAMING, 640, 480);
    
    // Install timer (60fps = ~16.67ms per frame)
    timer_interval = 1000 / 60;
    SDL_TimerID timer_id = SDL_AddTimer(timer_interval, tempo_callback, NULL);
    
    // Declaração de variáveis
    int x, y;
    int Pal0found, Pal1found, Pal2found, Pal3found, Pal4found, Pal5found, Pal6found, Pal7found, Pal8found;
    Pal0found = Pal1found = Pal2found = Pal3found = Pal4found = Pal5found = Pal6found = Pal7found = Pal8found = 1;
    int Palletefound = 1;
    int ModoFullscreen = 0;
    int ArrayPallete[32][4];
    int r = 0, g = 0, b = 0, ValorDeCor = 0;
    int CorNum = 0;
    int podeatualizar = 1;
    int AtualizaSlotPallete = 0;
    int SlotNum = 0;
    int ATUALIZA_S0 = 0; int ATUALIZA_S1 = 0; int ATUALIZA_S2 = 0; int ATUALIZA_S3 = 0;
    int ATUALIZA_S4 = 0; int ATUALIZA_S5 = 0; int ATUALIZA_S6 = 0; int ATUALIZA_S7 = 0;
    int ATUALIZA_S8 = 0; int GERAR_NOVA_PALETA = 0;
    int Slot0OK = 0; int Slot1OK = 0; int Slot2OK = 0; int Slot3OK = 0;
    int Slot4OK = 0; int Slot5OK = 0; int Slot6OK = 0; int Slot7OK = 0; 
    int Slot8OK = 0;
    
    for(y = 0; y < 4; y++) {
        for(x = 0; x < 32; x++) {
            ArrayPallete[x][y] = 0; //zera o array
        }
    }
    
    // Declaração de Bitmaps
    SDL_Surface *SlotPallete = create_bitmap(32, 10);
    SDL_Surface *temp = load_bitmap("data/pallete.pcx");
    if (temp) {
        blit(temp, SlotPallete, 0, 0, 0, 0, 32, 10);
        SDL_FreeSurface(temp);
    } else {
        Palletefound = 0;
    }
    
    if (Palletefound == 0) {
        clear_to_color(SlotPallete, makecol(255, 0, 255));
        save_bitmap("data/pallete.pcx", SlotPallete);
    }
    
    SDL_Surface *SlotPalleteDisplay = create_bitmap(256, 80);
    SDL_Surface *EditorBackground = load_bitmap("data/system/EditorBackground.pcx");
    SDL_Surface *SlotVazio = load_bitmap("data/system/SlotVazio.pcx");
    SDL_Surface *StatusOK = load_bitmap("data/system/StatusOK.pcx");
    SDL_Surface *StripPal0 = create_bitmap(32, 1); clear_to_color(StripPal0, makecol(255, 0, 255));
    SDL_Surface *StripPal1 = create_bitmap(32, 1); clear_to_color(StripPal1, makecol(255, 0, 255));
    SDL_Surface *StripPal2 = create_bitmap(32, 1); clear_to_color(StripPal2, makecol(255, 0, 255));
    SDL_Surface *StripPal3 = create_bitmap(32, 1); clear_to_color(StripPal3, makecol(255, 0, 255));
    SDL_Surface *StripPal4 = create_bitmap(32, 1); clear_to_color(StripPal4, makecol(255, 0, 255));
    SDL_Surface *StripPal5 = create_bitmap(32, 1); clear_to_color(StripPal5, makecol(255, 0, 255));
    SDL_Surface *StripPal6 = create_bitmap(32, 1); clear_to_color(StripPal6, makecol(255, 0, 255));
    SDL_Surface *StripPal7 = create_bitmap(32, 1); clear_to_color(StripPal7, makecol(255, 0, 255));
    SDL_Surface *StripPal8 = create_bitmap(32, 1); clear_to_color(StripPal8, makecol(255, 0, 255));
    SDL_Surface *Slot0 = load_bitmap("data/pal0.pcx"); if (!Slot0) { Pal0found = 0; }
    SDL_Surface *Slot1 = load_bitmap("data/pal1.pcx"); if (!Slot1) { Pal1found = 0; }
    SDL_Surface *Slot2 = load_bitmap("data/pal2.pcx"); if (!Slot2) { Pal2found = 0; }
    SDL_Surface *Slot3 = load_bitmap("data/pal3.pcx"); if (!Slot3) { Pal3found = 0; }
    SDL_Surface *Slot4 = load_bitmap("data/pal4.pcx"); if (!Slot4) { Pal4found = 0; }
    SDL_Surface *Slot5 = load_bitmap("data/pal5.pcx"); if (!Slot5) { Pal5found = 0; }
    SDL_Surface *Slot6 = load_bitmap("data/pal6.pcx"); if (!Slot6) { Pal6found = 0; }
    SDL_Surface *Slot7 = load_bitmap("data/pal7.pcx"); if (!Slot7) { Pal7found = 0; }
    SDL_Surface *Slot8 = load_bitmap("data/pal8.pcx"); if (!Slot8) { Pal8found = 0; }
    
    // LOOP DE JOGO //
    SDL_Event event;
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    
    while (sair == 0)
    { 
        delay = timer;
        clear_to_color(buffer_surface, makecol(100, 149, 237));
        
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                sair = 1;
            }
        }
        
        // Update key state
        SDL_PumpEvents();
        
        if (key_state[SDL_SCANCODE_ESCAPE]) { sair = 1; }
        
        /* < INICIO > */
        
        if (ModoFullscreen == 0 && key_state[SDL_SCANCODE_LALT] && key_state[SDL_SCANCODE_RETURN]) {
            ModoFullscreen = 1;
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        }
        if (ModoFullscreen == 1 && key_state[SDL_SCANCODE_LALT] && key_state[SDL_SCANCODE_RETURN]) {
            ModoFullscreen = 0;
            SDL_SetWindowFullscreen(window, 0);
        }
        
        if (key_state[SDL_SCANCODE_F1]) {
            ATUALIZA_S0 = 1;
            ATUALIZA_S1 = 1;
            ATUALIZA_S2 = 1;
            ATUALIZA_S3 = 1;
            ATUALIZA_S4 = 1;
            ATUALIZA_S5 = 1;
            ATUALIZA_S6 = 1;
            ATUALIZA_S7 = 1;
            ATUALIZA_S8 = 1;
            GERAR_NOVA_PALETA = 1;
        }
        
        if (ATUALIZA_S0 == 1 && Slot0) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot0->h; y++) {
                    for(x = 0; x < Slot0->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot0, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot0, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot0->h; y++) {
                    for(x = 0; x < Slot0->w; x++) {
                        if (getpixel(Slot0, x, y) == makecol(r, g, b)) {
                            putpixel(Slot0, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal0, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S0 = 0;
        }
        
        if (ATUALIZA_S1 == 1 && Slot1) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot1->h; y++) {
                    for(x = 0; x < Slot1->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot1, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot1, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot1->h; y++) {
                    for(x = 0; x < Slot1->w; x++) {
                        if (getpixel(Slot1, x, y) == makecol(r, g, b)) {
                            putpixel(Slot1, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal1, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S1 = 0;
        }
        
        if (ATUALIZA_S2 == 1 && Slot2) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot2->h; y++) {
                    for(x = 0; x < Slot2->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot2, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot2, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot2->h; y++) {
                    for(x = 0; x < Slot2->w; x++) {
                        if (getpixel(Slot2, x, y) == makecol(r, g, b)) {
                            putpixel(Slot2, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal2, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S2 = 0;
        }
        
        if (ATUALIZA_S3 == 1 && Slot3) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot3->h; y++) {
                    for(x = 0; x < Slot3->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot3, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot3, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot3->h; y++) {
                    for(x = 0; x < Slot3->w; x++) {
                        if (getpixel(Slot3, x, y) == makecol(r, g, b)) {
                            putpixel(Slot3, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal3, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S3 = 0;
        }
        
        if (ATUALIZA_S4 == 1 && Slot4) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot4->h; y++) {
                    for(x = 0; x < Slot4->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot4, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot4, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot4->h; y++) {
                    for(x = 0; x < Slot4->w; x++) {
                        if (getpixel(Slot4, x, y) == makecol(r, g, b)) {
                            putpixel(Slot4, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal4, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S4 = 0;
        }
        
        if (ATUALIZA_S5 == 1 && Slot5) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot5->h; y++) {
                    for(x = 0; x < Slot5->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot5, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot5, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot5->h; y++) {
                    for(x = 0; x < Slot5->w; x++) {
                        if (getpixel(Slot5, x, y) == makecol(r, g, b)) {
                            putpixel(Slot5, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal5, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S5 = 0;
        }
        
        if (ATUALIZA_S6 == 1 && Slot6) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot6->h; y++) {
                    for(x = 0; x < Slot6->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot6, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot6, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot6->h; y++) {
                    for(x = 0; x < Slot6->w; x++) {
                        if (getpixel(Slot6, x, y) == makecol(r, g, b)) {
                            putpixel(Slot6, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal6, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S6 = 0;
        }
        
        if (ATUALIZA_S7 == 1 && Slot7) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot7->h; y++) {
                    for(x = 0; x < Slot7->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot7, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot7, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot7->h; y++) {
                    for(x = 0; x < Slot7->w; x++) {
                        if (getpixel(Slot7, x, y) == makecol(r, g, b)) {
                            putpixel(Slot7, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal7, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S7 = 0;
        }
        
        if (ATUALIZA_S8 == 1 && Slot8) { 
            for(int i = 1; i <= 32; i++) {
                podeatualizar = 1;
                for(y = 0; y < Slot8->h; y++) {
                    for(x = 0; x < Slot8->w; x++) {
                        if (podeatualizar == 1) {
                            if (getpixel(Slot8, x, y) != makecol(255, 0, 255)) {
                                ValorDeCor = getpixel(Slot8, x, y);
                                r = getr(ValorDeCor); g = getg(ValorDeCor); b = getb(ValorDeCor);
                                ArrayPallete[CorNum][1] = r; ArrayPallete[CorNum][2] = g; ArrayPallete[CorNum][3] = b;
                                CorNum++; podeatualizar = 0;
                            }
                        }
                    }
                }
                for(y = 0; y < Slot8->h; y++) {
                    for(x = 0; x < Slot8->w; x++) {
                        if (getpixel(Slot8, x, y) == makecol(r, g, b)) {
                            putpixel(Slot8, x, y, makecol(255, 0, 255));
                        }
                    }
                }
                if (CorNum > 33) { CorNum = 33; }
                if (i == 32) { AtualizaSlotPallete = 1; }
            }
        }
        if (AtualizaSlotPallete == 1) {
            for(int i = 0; i <= CorNum - 1; i++) {
                putpixel(StripPal8, i, 0, makecol(ArrayPallete[i][1], ArrayPallete[i][2], ArrayPallete[i][3]));
            }
            AtualizaSlotPallete = 0; CorNum = 0; ATUALIZA_S8 = 0;
        }
        
        if (GERAR_NOVA_PALETA == 1) {
            blit(StripPal0, SlotPallete, 0, 0, 0, 0, 32, 1);
            blit(StripPal1, SlotPallete, 0, 0, 0, 1, 32, 1);
            blit(StripPal2, SlotPallete, 0, 0, 0, 2, 32, 1);
            blit(StripPal3, SlotPallete, 0, 0, 0, 3, 32, 1);
            blit(StripPal4, SlotPallete, 0, 0, 0, 4, 32, 1);
            blit(StripPal5, SlotPallete, 0, 0, 0, 5, 32, 1);
            blit(StripPal6, SlotPallete, 0, 0, 0, 6, 32, 1);
            blit(StripPal7, SlotPallete, 0, 0, 0, 7, 32, 1);
            blit(StripPal8, SlotPallete, 0, 0, 0, 8, 32, 1);
            save_bitmap("data/pallete.pcx", SlotPallete);
            if (Pal0found == 1) { Slot0OK = 1; }
            if (Pal1found == 1) { Slot1OK = 1; }
            if (Pal2found == 1) { Slot2OK = 1; }
            if (Pal3found == 1) { Slot3OK = 1; }
            if (Pal4found == 1) { Slot4OK = 1; }
            if (Pal5found == 1) { Slot5OK = 1; }
            if (Pal6found == 1) { Slot6OK = 1; }
            if (Pal7found == 1) { Slot7OK = 1; }
            if (Pal8found == 1) { Slot8OK = 1; }
            GERAR_NOVA_PALETA = 0;
        }
        
        // Draw everything
        if (EditorBackground) {
            draw_sprite(buffer_surface, EditorBackground, 0, 0);
        }
        
        // Draw text (simplified - no actual text rendering in this minimal version)
        // textprintf_centre_ex(buffer_surface, 320, 20, makecol(255, 255, 255), "HAMOOPI - PALLETE GENERATOR");
        // textprintf_centre_ex(buffer_surface, 320, 35, makecol(255, 255, 255), "Aperte F1 para criar uma nova paleta");
        // textprintf_centre_ex(buffer_surface, 320, 45, makecol(255, 255, 255), "Aperte ESC para sair");
        
        // Draw SlotPallete
        stretch_blit(SlotPallete, SlotPalleteDisplay,
                    0, 0, SlotPallete->w, SlotPallete->h,
                    0, 0, SlotPalleteDisplay->w, SlotPalleteDisplay->h);
        draw_sprite(buffer_surface, SlotPalleteDisplay, 252, 91);
        
        // Draw slots
        if (Pal0found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 0 + 0, 76 + 128 * 0 + 0); }
        if (Pal1found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 0 + 0, 76 + 128 * 1 + 2); }
        if (Pal2found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 1 + 2, 76 + 128 * 1 + 2); }
        if (Pal3found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 2 + 4, 76 + 128 * 1 + 2); }
        if (Pal4found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 3 + 6, 76 + 128 * 1 + 2); }
        if (Pal5found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 0 + 0, 76 + 128 * 2 + 4); }
        if (Pal6found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 1 + 2, 76 + 128 * 2 + 4); }
        if (Pal7found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 2 + 4, 76 + 128 * 2 + 4); }
        if (Pal8found == 0 && SlotVazio) { draw_sprite(buffer_surface, SlotVazio, 64 + 128 * 3 + 6, 76 + 128 * 2 + 4); }
        
        if (Pal0found == 1 && Slot0) { draw_sprite(buffer_surface, Slot0, 64 + 128 * 0 + 0, 76 + 128 * 0 + 0); }
        if (Pal1found == 1 && Slot1) { draw_sprite(buffer_surface, Slot1, 64 + 128 * 0 + 0, 76 + 128 * 1 + 2); }
        if (Pal2found == 1 && Slot2) { draw_sprite(buffer_surface, Slot2, 64 + 128 * 1 + 2, 76 + 128 * 1 + 2); }
        if (Pal3found == 1 && Slot3) { draw_sprite(buffer_surface, Slot3, 64 + 128 * 2 + 4, 76 + 128 * 1 + 2); }
        if (Pal4found == 1 && Slot4) { draw_sprite(buffer_surface, Slot4, 64 + 128 * 3 + 6, 76 + 128 * 1 + 2); }
        if (Pal5found == 1 && Slot5) { draw_sprite(buffer_surface, Slot5, 64 + 128 * 0 + 0, 76 + 128 * 2 + 4); }
        if (Pal6found == 1 && Slot6) { draw_sprite(buffer_surface, Slot6, 64 + 128 * 1 + 2, 76 + 128 * 2 + 4); }
        if (Pal7found == 1 && Slot7) { draw_sprite(buffer_surface, Slot7, 64 + 128 * 2 + 4, 76 + 128 * 2 + 4); }
        if (Pal8found == 1 && Slot8) { draw_sprite(buffer_surface, Slot8, 64 + 128 * 3 + 6, 76 + 128 * 2 + 4); }
        
        if (Slot0OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 0 + 0, 32 + 76 + 128 * 0 + 0); }
        if (Slot1OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 0 + 0, 32 + 76 + 128 * 1 + 2); }
        if (Slot2OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 1 + 2, 32 + 76 + 128 * 1 + 2); }
        if (Slot3OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 2 + 4, 32 + 76 + 128 * 1 + 2); }
        if (Slot4OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 3 + 6, 32 + 76 + 128 * 1 + 2); }
        if (Slot5OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 0 + 0, 32 + 76 + 128 * 2 + 4); }
        if (Slot6OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 1 + 2, 32 + 76 + 128 * 2 + 4); }
        if (Slot7OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 2 + 4, 32 + 76 + 128 * 2 + 4); }
        if (Slot8OK == 1 && StatusOK) { draw_sprite(buffer_surface, StatusOK, 32 + 64 + 128 * 3 + 6, 32 + 76 + 128 * 2 + 4); }
        
        // DEBUG - Draw strips
        draw_sprite(buffer_surface, StripPal0, 80, 30 + 3);
        draw_sprite(buffer_surface, StripPal1, 80, 32 + 3);
        draw_sprite(buffer_surface, StripPal2, 80, 34 + 3);
        draw_sprite(buffer_surface, StripPal3, 80, 36 + 3);
        draw_sprite(buffer_surface, StripPal4, 80, 38 + 3);
        draw_sprite(buffer_surface, StripPal5, 80, 40 + 3);
        draw_sprite(buffer_surface, StripPal6, 80, 42 + 3);
        draw_sprite(buffer_surface, StripPal7, 80, 44 + 3);
        draw_sprite(buffer_surface, StripPal8, 80, 46 + 3);
        
        // Update texture and render
        SDL_UpdateTexture(buffer_texture, NULL, buffer_surface->pixels, buffer_surface->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, buffer_texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        // FINALIZACOES //
        while (timer == delay) {
            SDL_Delay(1);
        }
    }
    
    // Cleanup
    SDL_RemoveTimer(timer_id);
    if (Slot0) SDL_FreeSurface(Slot0);
    if (Slot1) SDL_FreeSurface(Slot1);
    if (Slot2) SDL_FreeSurface(Slot2);
    if (Slot3) SDL_FreeSurface(Slot3);
    if (Slot4) SDL_FreeSurface(Slot4);
    if (Slot5) SDL_FreeSurface(Slot5);
    if (Slot6) SDL_FreeSurface(Slot6);
    if (Slot7) SDL_FreeSurface(Slot7);
    if (Slot8) SDL_FreeSurface(Slot8);
    if (StripPal0) SDL_FreeSurface(StripPal0);
    if (StripPal1) SDL_FreeSurface(StripPal1);
    if (StripPal2) SDL_FreeSurface(StripPal2);
    if (StripPal3) SDL_FreeSurface(StripPal3);
    if (StripPal4) SDL_FreeSurface(StripPal4);
    if (StripPal5) SDL_FreeSurface(StripPal5);
    if (StripPal6) SDL_FreeSurface(StripPal6);
    if (StripPal7) SDL_FreeSurface(StripPal7);
    if (StripPal8) SDL_FreeSurface(StripPal8);
    if (StatusOK) SDL_FreeSurface(StatusOK);
    if (SlotVazio) SDL_FreeSurface(SlotVazio);
    if (EditorBackground) SDL_FreeSurface(EditorBackground);
    if (SlotPalleteDisplay) SDL_FreeSurface(SlotPalleteDisplay);
    if (SlotPallete) SDL_FreeSurface(SlotPallete);
    
    SDL_DestroyTexture(buffer_texture);
    SDL_FreeSurface(buffer_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}

// Pallete Editor by Daniel Moura - danielmouradesigner@gmail.com - 16/03/2019
// SDL2 Port - 2025

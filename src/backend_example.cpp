// Example demonstrating the backend abstraction layer
// This file shows how new code should use the abstraction instead of direct Allegro calls

#include "backend_manager.h"
#include "allegro_graphics_backend.h"
#include "allegro_input_backend.h"
#include "allegro_audio_backend.h"
#include "allegro_system_backend.h"
#include <allegro.h>

// Use external backend pointer defined in backend_init.cpp
extern BackendManager* g_backend;

void example_usage() {
    // Initialize backends
    g_backend = BackendManager::getInstance();
    
    AllegroSystemBackend* systemBackend = new AllegroSystemBackend();
    AllegroGraphicsBackend* graphicsBackend = new AllegroGraphicsBackend();
    AllegroInputBackend* inputBackend = new AllegroInputBackend();
    AllegroAudioBackend* audioBackend = new AllegroAudioBackend();
    
    g_backend->setSystemBackend(systemBackend);
    g_backend->setGraphicsBackend(graphicsBackend);
    g_backend->setInputBackend(inputBackend);
    g_backend->setAudioBackend(audioBackend);
    
    // Initialize Allegro (still needed for Allegro backend)
    allegro_init();
    install_keyboard();
    install_mouse();
    install_timer();
    
    // Set up graphics using the abstraction
    GraphicsBackend* gfx = g_backend->getGraphics();
    gfx->set_color_depth(32);
    gfx->set_graphics_mode(false, 640, 480);
    gfx->set_window_title("HAMOOPI - Backend Abstraction Example");
    
    // Create bitmaps using the abstraction
    GraphicsBitmap buffer = gfx->create_bitmap(640, 480);
    GraphicsBitmap sprite = gfx->load_bitmap("data/test.pcx");
    
    // Load fonts using the abstraction
    GraphicsFont font = gfx->load_font("data/system/font_debug.pcx");
    
    // Main game loop
    bool running = true;
    while (running) {
        // Check input using the abstraction
        InputBackend* input = g_backend->getInput();
        if (input->is_key_pressed(KEY_ESC)) {
            running = false;
        }
        
        // Clear screen
        gfx->clear_to_color(buffer, gfx->makecol(0, 0, 0));
        
        // Draw something
        gfx->rectfill(buffer, 100, 100, 200, 200, gfx->makecol(255, 0, 0));
        gfx->textout(buffer, font, "Backend Abstraction Example", 10, 10, gfx->makecol(255, 255, 255));
        
        // Draw sprite if loaded
        if (sprite) {
            gfx->draw_sprite(buffer, sprite, 300, 200);
        }
        
        // Blit to screen
        gfx->blit(buffer, gfx->get_screen(), 0, 0, 0, 0, 640, 480);
        
        // Rest
        g_backend->getSystem()->rest(16); // ~60 FPS
    }
    
    // Cleanup
    if (sprite) gfx->destroy_bitmap(sprite);
    if (font) gfx->destroy_font(font);
    gfx->destroy_bitmap(buffer);
    
    g_backend->shutdownAll();
}

// This example shows:
// 1. How to initialize the backend system
// 2. How to use graphics operations through the abstraction
// 3. How to check input through the abstraction
// 4. How to maintain a game loop with the abstraction
// 5. How to properly cleanup resources

int main() {
    example_usage();
    return 0;
}
END_OF_MAIN()

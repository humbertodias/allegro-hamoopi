#include "backend_manager.h"
#include "allegro_graphics_backend.h"
#include "allegro_input_backend.h"
#include "allegro_audio_backend.h"
#include "allegro_system_backend.h"
#include <allegro.h>

// Global backend manager instance
BackendManager* g_backend = nullptr;

// Initialize all backends with Allegro implementations
bool init_backends() {
    g_backend = BackendManager::getInstance();
    
    // Create Allegro backend implementations
    AllegroSystemBackend* systemBackend = new AllegroSystemBackend();
    AllegroGraphicsBackend* graphicsBackend = new AllegroGraphicsBackend();
    AllegroInputBackend* inputBackend = new AllegroInputBackend();
    AllegroAudioBackend* audioBackend = new AllegroAudioBackend();
    
    // Register backends
    g_backend->setSystemBackend(systemBackend);
    g_backend->setGraphicsBackend(graphicsBackend);
    g_backend->setInputBackend(inputBackend);
    g_backend->setAudioBackend(audioBackend);
    
    // Initialize all backends - this initializes Allegro library internally
    allegro_init();  // Core Allegro initialization
    install_timer(); // Timer system
    install_keyboard(); // Keyboard input
    install_mouse(); // Mouse input
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL); // Audio system
    
    return true;
}

void shutdown_backends() {
    if (g_backend) {
        g_backend->shutdownAll();
    }
}

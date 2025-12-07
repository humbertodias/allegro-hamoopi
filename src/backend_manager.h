#ifndef BACKEND_MANAGER_H
#define BACKEND_MANAGER_H

#include "graphics_backend.h"
#include "input_backend.h"
#include "audio_backend.h"
#include "system_backend.h"

// Singleton class to manage all backends
class BackendManager {
private:
    static BackendManager* instance;
    
    GraphicsBackend* graphics;
    InputBackend* input;
    AudioBackend* audio;
    SystemBackend* system;
    
    BackendManager() : graphics(nullptr), input(nullptr), audio(nullptr), system(nullptr) {}
    
public:
    static BackendManager* getInstance() {
        if (!instance) {
            instance = new BackendManager();
        }
        return instance;
    }
    
    void setGraphicsBackend(GraphicsBackend* backend) { graphics = backend; }
    void setInputBackend(InputBackend* backend) { input = backend; }
    void setAudioBackend(AudioBackend* backend) { audio = backend; }
    void setSystemBackend(SystemBackend* backend) { system = backend; }
    
    GraphicsBackend* getGraphics() { return graphics; }
    InputBackend* getInput() { return input; }
    AudioBackend* getAudio() { return audio; }
    SystemBackend* getSystem() { return system; }
    
    bool initAll() {
        if (system && !system->init()) return false;
        if (graphics && !graphics->init()) return false;
        if (input && !input->init()) return false;
        if (audio && !audio->init()) return false;
        return true;
    }
    
    void shutdownAll() {
        if (audio) audio->shutdown();
        if (input) input->shutdown();
        if (graphics) graphics->shutdown();
        if (system) system->shutdown();
    }
    
    ~BackendManager() {
        shutdownAll();
    }
};

#endif // BACKEND_MANAGER_H

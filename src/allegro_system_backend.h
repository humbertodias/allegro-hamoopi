#ifndef ALLEGRO_SYSTEM_BACKEND_H
#define ALLEGRO_SYSTEM_BACKEND_H

#include "system_backend.h"
#include <allegro.h>
#include <cstdarg>

class AllegroSystemBackend : public SystemBackend {
public:
    AllegroSystemBackend() {}
    
    bool init() override {
        return allegro_init() == 0 && ::install_timer() == 0;
    }
    
    void shutdown() override {
        allegro_exit();
    }
    
    void install_timer(TimerCallback callback, int fps) override {
        ::install_int_ex(callback, BPS_TO_TIMER(fps));
    }
    
    void rest(int milliseconds) override {
        ::rest(milliseconds);
    }
    
    bool file_exists(const char* filename) override {
        return ::exists(filename) != 0;
    }
    
    void set_config_file(const char* filename) override {
        ::set_config_file(filename);
    }
    
    const char* get_config_string(const char* section, const char* key, const char* default_value) override {
        return ::get_config_string(section, key, default_value);
    }
    
    int get_config_int(const char* section, const char* key, int default_value) override {
        return ::get_config_int(section, key, default_value);
    }
    
    void set_config_string(const char* section, const char* key, const char* value) override {
        ::set_config_string(section, key, value);
    }
    
    void set_config_int(const char* section, const char* key, int value) override {
        ::set_config_int(section, key, value);
    }
    
    void show_message(const char* message) override {
        ::allegro_message("%s", message);
    }
    
    void set_close_button_callback(CloseCallback callback) override {
        ::set_close_button_callback(callback);
    }
    
    void set_utf8_format() override {
        ::set_uformat(U_UTF8);
    }
};

#endif // ALLEGRO_SYSTEM_BACKEND_H

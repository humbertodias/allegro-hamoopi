#ifndef ALLEGRO_INPUT_BACKEND_H
#define ALLEGRO_INPUT_BACKEND_H

#include "input_backend.h"
#include <allegro.h>

class AllegroInputBackend : public InputBackend {
private:
    // NOTE: Key mapping limitation
    // Currently maps abstract KeyCode enums to Allegro KEY_* constants.
    // This creates a dependency on Allegro constants in the abstraction layer.
    // For full library independence, this should use integer key codes that are
    // backend-agnostic, with each backend doing its own translation.
    // However, for backward compatibility with existing HAMOOPI code that uses
    // Allegro's key[] array directly, we maintain this mapping for now.
    int mapKeyCode(KeyCode keycode) {
        switch (keycode) {
            case KEY_A: return KEY_A;
            case KEY_B: return KEY_B;
            case KEY_C: return KEY_C;
            case KEY_D: return KEY_D;
            case KEY_E: return KEY_E;
            case KEY_F: return KEY_F;
            case KEY_G: return KEY_G;
            case KEY_H: return KEY_H;
            case KEY_I: return KEY_I;
            case KEY_J: return KEY_J;
            case KEY_K: return KEY_K;
            case KEY_L: return KEY_L;
            case KEY_M: return KEY_M;
            case KEY_N: return KEY_N;
            case KEY_O: return KEY_O;
            case KEY_P: return KEY_P;
            case KEY_Q: return KEY_Q;
            case KEY_R: return KEY_R;
            case KEY_S: return KEY_S;
            case KEY_T: return KEY_T;
            case KEY_U: return KEY_U;
            case KEY_V: return KEY_V;
            case KEY_W: return KEY_W;
            case KEY_X: return KEY_X;
            case KEY_Y: return KEY_Y;
            case KEY_Z: return KEY_Z;
            case KEY_0: return KEY_0;
            case KEY_1: return KEY_1;
            case KEY_2: return KEY_2;
            case KEY_3: return KEY_3;
            case KEY_4: return KEY_4;
            case KEY_5: return KEY_5;
            case KEY_6: return KEY_6;
            case KEY_7: return KEY_7;
            case KEY_8: return KEY_8;
            case KEY_9: return KEY_9;
            case KEY_UP: return KEY_UP;
            case KEY_DOWN: return KEY_DOWN;
            case KEY_LEFT: return KEY_LEFT;
            case KEY_RIGHT: return KEY_RIGHT;
            case KEY_SPACE: return KEY_SPACE;
            case KEY_ENTER: return KEY_ENTER;
            case KEY_ESC: return KEY_ESC;
            case KEY_LSHIFT: return KEY_LSHIFT;
            case KEY_RSHIFT: return KEY_RSHIFT;
            case KEY_LCONTROL: return KEY_LCONTROL;
            case KEY_RCONTROL: return KEY_RCONTROL;
            case KEY_F1: return KEY_F1;
            case KEY_F2: return KEY_F2;
            case KEY_F3: return KEY_F3;
            case KEY_F4: return KEY_F4;
            case KEY_F5: return KEY_F5;
            case KEY_F6: return KEY_F6;
            case KEY_F7: return KEY_F7;
            case KEY_F8: return KEY_F8;
            case KEY_F9: return KEY_F9;
            case KEY_F10: return KEY_F10;
            case KEY_F11: return KEY_F11;
            case KEY_F12: return KEY_F12;
            default: return 0;
        }
    }
    
public:
    bool init() override {
        return install_keyboard() == 0;
    }
    
    void shutdown() override {
        // Handled by allegro_exit
    }
    
    bool is_key_pressed(KeyCode keycode) override {
        int scancode = mapKeyCode(keycode);
        return key[scancode] != 0;
    }
    
    int get_scancode(int key_constant) override {
        return key_constant;
    }
    
    void poll_mouse() override {
        ::poll_mouse();
    }
    
    int mouse_x() override {
        return ::mouse_x;
    }
    
    int mouse_y() override {
        return ::mouse_y;
    }
    
    bool mouse_button_left() override {
        return (mouse_b & 1) != 0;
    }
    
    bool mouse_button_right() override {
        return (mouse_b & 2) != 0;
    }
    
    bool mouse_button_middle() override {
        return (mouse_b & 4) != 0;
    }
    
    void show_mouse(void* bitmap) override {
        ::show_mouse((BITMAP*)bitmap);
    }
    
    bool init_joystick() override {
        return install_joystick(JOY_TYPE_AUTODETECT) == 0;
    }
    
    int num_joysticks() override {
        return ::num_joysticks;
    }
};

#endif // ALLEGRO_INPUT_BACKEND_H

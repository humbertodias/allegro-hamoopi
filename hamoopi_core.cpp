#include "hamoopi_core.h"
#include "libretro.h"
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Global state variables
static BITMAP* screen_buffer = NULL;
static BITMAP* game_buffer = NULL;
static bool initialized = false;
static bool running = false;
static int frame_count = 0;

// Input state for two players
hamoopi_input_t hamoopi_input[2] = {};

// Game state
typedef struct {
    float x, y;
    float vx, vy;
    int health;
    int state; // 0=idle, 1=walk, 2=jump, 3=attack, 4=hit
    int anim_frame;
    int facing; // 1=right, -1=left
    bool on_ground;
    int character_id; // Character selection (0-3)
    bool is_blocking; // Whether player is currently blocking
} Player;

static Player players[2];
static int game_mode = 0; // 0=title, 1=character_select, 2=fight, 3=winner

// Character selection state
static int p1_cursor = 0;
static int p2_cursor = 1;
static bool p1_ready = false;
static bool p2_ready = false;

// Input tracking for character selection
static bool p1_left_pressed = false;
static bool p1_right_pressed = false;
static bool p1_a_pressed = false;
static bool p2_left_pressed = false;
static bool p2_right_pressed = false;
static bool p2_a_pressed = false;

// Character system constants
#define NUM_CHARACTERS 4

// Combat balance constants
#define NORMAL_DAMAGE 5
#define BLOCKED_DAMAGE 1
#define BLOCKING_SPEED_MULTIPLIER 0.5f
#define BLOCKING_COLOR_DIVISOR 2

// Stage/background animation
static int stage_animation_frame = 0;

// Audio constants
#define AUDIO_SAMPLE_RATE 44100
#define AUDIO_BUFFER_SIZE 735  // ~60 FPS: 44100/60 = 735 samples per frame

// Sound effect types
enum SoundEffect {
    SOUND_NONE = 0,
    SOUND_JUMP = 1,
    SOUND_ATTACK = 2,
    SOUND_HIT = 3,
    SOUND_BLOCK = 4
};

// Audio state
// Sound effect queue (simple system)
static enum SoundEffect sound_queue[4] = {SOUND_NONE, SOUND_NONE, SOUND_NONE, SOUND_NONE};
static int sound_effect_timer[4] = {0, 0, 0, 0};
static int sound_effect_duration[4] = {0, 0, 0, 0};

// Character colors for visual distinction
static const int char_colors[NUM_CHARACTERS][3] = {
    {255, 100, 100},  // Red - FIRE
    {100, 100, 255},  // Blue - WATER
    {100, 255, 100},  // Green - EARTH
    {255, 255, 100}   // Yellow - WIND
};

// Fonts
static FONT* game_font = NULL;

// Function to play a sound effect
static void play_sound(enum SoundEffect effect)
{
    // Find an empty slot in the sound queue
    for (int i = 0; i < 4; i++)
    {
        if (sound_effect_timer[i] <= 0)
        {
            sound_queue[i] = effect;
            
            // Set duration based on effect type
            switch (effect)
            {
                case SOUND_JUMP:
                    sound_effect_duration[i] = AUDIO_SAMPLE_RATE / 20; // 0.05 seconds
                    break;
                case SOUND_ATTACK:
                    sound_effect_duration[i] = AUDIO_SAMPLE_RATE / 15; // 0.067 seconds
                    break;
                case SOUND_HIT:
                    sound_effect_duration[i] = AUDIO_SAMPLE_RATE / 25; // 0.04 seconds
                    break;
                case SOUND_BLOCK:
                    sound_effect_duration[i] = AUDIO_SAMPLE_RATE / 30; // 0.033 seconds
                    break;
                default:
                    sound_effect_duration[i] = 0;
                    break;
            }
            
            // Initialize timer to duration
            sound_effect_timer[i] = sound_effect_duration[i];
            break;
        }
    }
}

// Generate a single audio sample for a sound effect
static int16_t generate_sound_sample(enum SoundEffect effect, int position, int duration)
{
    if (effect == SOUND_NONE || duration == 0)
        return 0;
    
    float t = (float)position / (float)duration;
    float amplitude = (1.0f - t) * 0.15f; // Decay envelope
    int16_t sample = 0;
    
    switch (effect)
    {
        case SOUND_JUMP:
            // Rising pitch sweep
            {
                float freq = 200.0f + t * 400.0f; // 200Hz to 600Hz sweep
                float phase = (float)position * freq * 2.0f * 3.14159f / AUDIO_SAMPLE_RATE;
                sample = (int16_t)(sin(phase) * amplitude * 32767.0f);
            }
            break;
            
        case SOUND_ATTACK:
            // Sharp percussive sound
            {
                float freq = 150.0f * (1.0f - t * 0.5f); // Falling pitch
                float phase = (float)position * freq * 2.0f * 3.14159f / AUDIO_SAMPLE_RATE;
                sample = (int16_t)(sin(phase) * amplitude * 32767.0f);
            }
            break;
            
        case SOUND_HIT:
            // Impact sound with noise
            {
                float noise = ((float)(rand() % 1000) / 500.0f - 1.0f);
                sample = (int16_t)(noise * amplitude * 32767.0f);
            }
            break;
            
        case SOUND_BLOCK:
            // Metallic clang
            {
                float freq = 800.0f + (float)(rand() % 200);
                float phase = (float)position * freq * 2.0f * 3.14159f / AUDIO_SAMPLE_RATE;
                sample = (int16_t)(sin(phase) * amplitude * 32767.0f * 0.5f);
            }
            break;
            
        default:
            sample = 0;
            break;
    }
    
    return sample;
}

// Fill audio buffer with generated sound effects
void hamoopi_get_audio_samples(int16_t* buffer, size_t frames)
{
    for (size_t i = 0; i < frames; i++)
    {
        int16_t left = 0;
        int16_t right = 0;
        
        // Mix all active sound effects
        for (int j = 0; j < 4; j++)
        {
            if (sound_effect_timer[j] > 0)
            {
                int pos = sound_effect_duration[j] - sound_effect_timer[j];
                int16_t sample = generate_sound_sample(sound_queue[j], pos, sound_effect_duration[j]);
                
                left += sample;
                right += sample;
                
                sound_effect_timer[j]--;
                
                if (sound_effect_timer[j] <= 0)
                {
                    sound_queue[j] = SOUND_NONE;
                    sound_effect_duration[j] = 0;
                }
            }
        }
        
        // Clamp to prevent overflow
        if (left > 32767) left = 32767;
        if (left < -32768) left = -32768;
        if (right > 32767) right = 32767;
        if (right < -32768) right = -32768;
        
        buffer[i * 2] = left;
        buffer[i * 2 + 1] = right;
    }
}

// Key mapping for players
// Player 1 keys
static int p1_up_key = KEY_W;
static int p1_down_key = KEY_S;
static int p1_left_key = KEY_A;
static int p1_right_key = KEY_D;
static int p1_bt1_key = KEY_J;
static int p1_bt2_key = KEY_K;
static int p1_bt3_key = KEY_L;
static int p1_bt4_key = KEY_U;
static int p1_bt5_key = KEY_I;
static int p1_bt6_key = KEY_O;
static int p1_select_key = KEY_1;
static int p1_start_key = KEY_ENTER;

// Player 2 keys
static int p2_up_key = KEY_UP;
static int p2_down_key = KEY_DOWN;
static int p2_left_key = KEY_LEFT;
static int p2_right_key = KEY_RIGHT;
static int p2_bt1_key = KEY_1_PAD;
static int p2_bt2_key = KEY_2_PAD;
static int p2_bt3_key = KEY_3_PAD;
static int p2_bt4_key = KEY_4_PAD;
static int p2_bt5_key = KEY_5_PAD;
static int p2_bt6_key = KEY_6_PAD;
static int p2_select_key = KEY_7_PAD;
static int p2_start_key = KEY_8_PAD;

// Initialize player state
static void init_player(Player* p, int player_num)
{
    p->x = (player_num == 0) ? 150.0f : 490.0f;
    p->y = 350.0f;
    p->vx = 0.0f;
    p->vy = 0.0f;
    p->health = 100;
    p->state = 0;
    p->anim_frame = 0;
    p->facing = (player_num == 0) ? 1 : -1;
    p->on_ground = true;
    p->is_blocking = false;
    // character_id is preserved from selection
}

// Draw a simple fighter sprite with character color
static void draw_player(BITMAP* dest, Player* p)
{
    int x = (int)p->x;
    int y = (int)p->y;
    
    // Get character color
    int color = makecol(char_colors[p->character_id][0], 
                        char_colors[p->character_id][1], 
                        char_colors[p->character_id][2]);
    
    // If blocking, draw shield in front and darker body
    if (p->is_blocking)
    {
        // Draw darker body when blocking
        int dark_color = makecol(char_colors[p->character_id][0] / BLOCKING_COLOR_DIVISOR, 
                                  char_colors[p->character_id][1] / BLOCKING_COLOR_DIVISOR, 
                                  char_colors[p->character_id][2] / BLOCKING_COLOR_DIVISOR);
        rectfill(dest, x - 15, y - 50, x + 15, y, dark_color);
        circlefill(dest, x, y - 60, 10, dark_color);
        
        // Draw shield in front of player
        int shield_x = x + (p->facing * 20);
        int shield_color = makecol(150, 150, 255); // Blue shield
        circlefill(dest, shield_x, y - 30, 15, shield_color);
        circle(dest, shield_x, y - 30, 16, makecol(255, 255, 255));
        circle(dest, shield_x, y - 30, 17, makecol(255, 255, 255));
    }
    else
    {
        // Draw normal body
        rectfill(dest, x - 15, y - 50, x + 15, y, color);
        
        // Draw head
        circlefill(dest, x, y - 60, 10, color);
    }
    
    // Draw health bar above player
    int bar_width = 60;
    int health_width = (p->health * bar_width) / 100;
    rect(dest, x - 30, y - 80, x + 30, y - 75, makecol(255, 255, 255));
    rectfill(dest, x - 30, y - 80, x - 30 + health_width, y - 75, makecol(0, 255, 0));
    
    // Draw facing indicator (simple line)
    int dir = p->facing;
    line(dest, x, y - 60, x + dir * 20, y - 60, makecol(255, 255, 0));
}

// Draw character selection box
static void draw_character_box(BITMAP* dest, int char_id, int x, int y, bool selected, bool ready)
{
    int color = makecol(char_colors[char_id][0], 
                        char_colors[char_id][1], 
                        char_colors[char_id][2]);
    
    // Draw character preview
    rectfill(dest, x, y, x + 80, y + 100, color);
    
    // Draw character body in box
    rectfill(dest, x + 25, y + 40, x + 55, y + 80, color);
    circlefill(dest, x + 40, y + 30, 8, color);
    
    // Draw selection border
    if (selected)
    {
        rect(dest, x - 2, y - 2, x + 82, y + 102, makecol(255, 255, 255));
        rect(dest, x - 3, y - 3, x + 83, y + 103, makecol(255, 255, 255));
    }
    
    // Draw ready indicator
    if (ready)
    {
        textout_centre_ex(dest, font, "READY!", x + 40, y + 85, makecol(255, 255, 255), -1);
    }
    
    // Draw character name
    const char* names[] = {"FIRE", "WATER", "EARTH", "WIND"};
    textout_centre_ex(dest, font, names[char_id], x + 40, y - 12, makecol(255, 255, 255), -1);
}

// Draw stage background based on characters
static void draw_stage_background(BITMAP* dest, int p1_char, int p2_char)
{
    // Determine stage theme based on characters (use P1's character primarily)
    int stage_theme = p1_char;
    
    // Animated background frame
    stage_animation_frame++;
    if (stage_animation_frame >= 360) stage_animation_frame = 0;
    
    // Sky/background layer
    switch (stage_theme)
    {
        case 0: // FIRE stage - Volcano/Lava
            {
                // Red-orange gradient sky
                for (int y = 0; y < 300; y++)
                {
                    int r = 180 + (y * 75 / 300);
                    int g = 50 + (y * 30 / 300);
                    int b = 20;
                    hline(dest, 0, y, 640, makecol(r, g, b));
                }
                
                // Distant mountains (dark)
                for (int x = 0; x < 640; x++)
                {
                    int height = 250 + (int)(20 * sin((x + stage_animation_frame) * 0.02f));
                    vline(dest, x, height, 300, makecol(60, 20, 10));
                }
                
                // Lava glow effect (animated)
                int glow = 200 + (int)(30 * sin(stage_animation_frame * 0.1f));
                hline(dest, 0, 395, 640, makecol(glow, 100, 30));
                hline(dest, 0, 396, 640, makecol(glow - 20, 80, 20));
            }
            break;
            
        case 1: // WATER stage - Ocean/Beach
            {
                // Blue gradient sky
                for (int y = 0; y < 300; y++)
                {
                    int r = 100 + (y * 55 / 300);
                    int g = 150 + (y * 55 / 300);
                    int b = 220 - (y * 20 / 300);
                    hline(dest, 0, y, 640, makecol(r, g, b));
                }
                
                // Ocean waves (animated)
                for (int x = 0; x < 640; x++)
                {
                    int wave1 = 200 + (int)(15 * sin((x + stage_animation_frame) * 0.03f));
                    int wave2 = 240 + (int)(10 * sin((x + stage_animation_frame * 1.5f) * 0.04f));
                    
                    vline(dest, x, wave1, wave2, makecol(60, 100, 180));
                    vline(dest, x, wave2, 300, makecol(40, 80, 150));
                }
                
                // Beach/sand
                rectfill(dest, 0, 300, 640, 400, makecol(220, 200, 140));
            }
            break;
            
        case 2: // EARTH stage - Forest
            {
                // Green-blue sky
                for (int y = 0; y < 300; y++)
                {
                    int r = 120 - (y * 20 / 300);
                    int g = 180 - (y * 30 / 300);
                    int b = 140 - (y * 40 / 300);
                    hline(dest, 0, y, 640, makecol(r, g, b));
                }
                
                // Distant trees (dark green)
                for (int i = 0; i < 20; i++)
                {
                    int x = i * 35 + ((stage_animation_frame / 2) % 35);
                    int y = 220 + (i % 3) * 10;
                    triangle(dest, x, y, x - 15, y + 60, x + 15, y + 60, makecol(30, 80, 30));
                }
                
                // Grass ground
                rectfill(dest, 0, 300, 640, 400, makecol(80, 140, 60));
                
                // Grass blades (simple details)
                for (int i = 0; i < 40; i++)
                {
                    int x = (i * 16 + stage_animation_frame) % 640;
                    vline(dest, x, 380, 385, makecol(100, 160, 80));
                }
            }
            break;
            
        case 3: // WIND stage - Sky/Clouds
            {
                // Light blue sky gradient
                for (int y = 0; y < 300; y++)
                {
                    int r = 150 + (y * 55 / 300);
                    int g = 200 + (y * 35 / 300);
                    int b = 255 - (y * 25 / 300);
                    hline(dest, 0, y, 640, makecol(r, g, b));
                }
                
                // Floating clouds (animated)
                for (int i = 0; i < 6; i++)
                {
                    int x = ((i * 120) - stage_animation_frame + 1280) % 800 - 100;
                    int y = 80 + i * 30;
                    
                    // Cloud puffs
                    circlefill(dest, x, y, 25, makecol(255, 255, 255));
                    circlefill(dest, x + 20, y, 20, makecol(255, 255, 255));
                    circlefill(dest, x + 40, y, 25, makecol(255, 255, 255));
                    circlefill(dest, x - 20, y, 20, makecol(255, 255, 255));
                }
                
                // Distant platforms/mountains
                for (int i = 0; i < 8; i++)
                {
                    int x = i * 90 + ((stage_animation_frame / 3) % 90);
                    int y = 260 + (i % 2) * 20;
                    rectfill(dest, x - 40, y, x + 40, y + 10, makecol(180, 180, 200));
                }
                
                // Ground platform
                rectfill(dest, 0, 300, 640, 310, makecol(200, 200, 220));
            }
            break;
    }
    
    // Draw ground line (common for all stages)
    hline(dest, 0, 400, 640, makecol(80, 80, 80));
}

void hamoopi_init(void)
{
    if (initialized)
        return;
    
    // Create screen buffer for rendering
    screen_buffer = create_bitmap(640, 480);
    game_buffer = create_bitmap(640, 480);
    
    if (!screen_buffer || !game_buffer)
    {
        fprintf(stderr, "Failed to create screen buffers\n");
        return;
    }
    
    clear_to_color(screen_buffer, makecol(0, 0, 0));
    clear_to_color(game_buffer, makecol(0, 0, 0));
    
    // Override the global Allegro 'screen' variable
    screen = screen_buffer;
    
    // Initialize keyboard state
    install_keyboard();
    
    // Initialize game font
    game_font = font;
    
    // Initialize players with default characters
    init_player(&players[0], 0);
    players[0].character_id = 0;
    init_player(&players[1], 1);
    players[1].character_id = 1;
    
    game_mode = 0; // Start at title screen
    frame_count = 0;
    
    // Reset character selection state
    p1_cursor = 0;
    p2_cursor = 1;
    p1_ready = false;
    p2_ready = false;
    
    initialized = true;
    running = false;
}

void hamoopi_deinit(void)
{
    if (!initialized)
        return;
    
    if (game_buffer)
    {
        destroy_bitmap(game_buffer);
        game_buffer = NULL;
    }
    
    if (screen_buffer)
    {
        destroy_bitmap(screen_buffer);
        screen_buffer = NULL;
    }
    
    screen = NULL;
    initialized = false;
    running = false;
}

void hamoopi_reset(void)
{
    // Reset game state
    init_player(&players[0], 0);
    players[0].character_id = 0;
    init_player(&players[1], 1);
    players[1].character_id = 1;
    
    game_mode = 0;
    frame_count = 0;
    
    // Reset character selection state
    p1_cursor = 0;
    p2_cursor = 1;
    p1_ready = false;
    p2_ready = false;
    
    if (screen_buffer)
        clear_to_color(screen_buffer, makecol(0, 0, 0));
    if (game_buffer)
        clear_to_color(game_buffer, makecol(0, 0, 0));
}

void hamoopi_run_frame(void)
{
    if (!initialized || !screen_buffer || !game_buffer)
        return;
    
    frame_count++;
    
    // Update the Allegro key array based on hamoopi_input state
    key[p1_up_key] = hamoopi_input[0].up;
    key[p1_down_key] = hamoopi_input[0].down;
    key[p1_left_key] = hamoopi_input[0].left;
    key[p1_right_key] = hamoopi_input[0].right;
    key[p1_bt1_key] = hamoopi_input[0].a;
    key[p1_bt2_key] = hamoopi_input[0].b;
    key[p1_bt3_key] = hamoopi_input[0].y;
    key[p1_bt4_key] = hamoopi_input[0].x;
    key[p1_bt5_key] = hamoopi_input[0].l;
    key[p1_bt6_key] = hamoopi_input[0].r;
    key[p1_select_key] = hamoopi_input[0].select;
    key[p1_start_key] = hamoopi_input[0].start;
    
    key[p2_up_key] = hamoopi_input[1].up;
    key[p2_down_key] = hamoopi_input[1].down;
    key[p2_left_key] = hamoopi_input[1].left;
    key[p2_right_key] = hamoopi_input[1].right;
    key[p2_bt1_key] = hamoopi_input[1].a;
    key[p2_bt2_key] = hamoopi_input[1].b;
    key[p2_bt3_key] = hamoopi_input[1].y;
    key[p2_bt4_key] = hamoopi_input[1].x;
    key[p2_bt5_key] = hamoopi_input[1].l;
    key[p2_bt6_key] = hamoopi_input[1].r;
    key[p2_select_key] = hamoopi_input[1].select;
    key[p2_start_key] = hamoopi_input[1].start;
    
    // Clear game buffer
    clear_to_color(game_buffer, makecol(20, 40, 80));
    
    // Game mode logic
    if (game_mode == 0)
    {
        // Title screen
        textout_centre_ex(game_buffer, game_font, "HAMOOPI", 320, 150, makecol(255, 255, 255), -1);
        textout_centre_ex(game_buffer, game_font, "Libretro Core - Fighting Game Demo", 320, 180, makecol(200, 200, 200), -1);
        textout_centre_ex(game_buffer, game_font, "Press START to begin", 320, 240, makecol(150, 200, 150), -1);
        textout_centre_ex(game_buffer, game_font, "Player 1: WASD + JKL", 320, 300, makecol(150, 150, 200), -1);
        textout_centre_ex(game_buffer, game_font, "Player 2: Arrows + Numpad", 320, 320, makecol(150, 150, 200), -1);
        
        if (key[p1_start_key] || key[p2_start_key])
        {
            game_mode = 1; // Go to character select
            p1_ready = false;
            p2_ready = false;
        }
    }
    else if (game_mode == 1)
    {
        // Character selection screen
        textout_centre_ex(game_buffer, game_font, "SELECT YOUR FIGHTER", 320, 30, makecol(255, 255, 255), -1);
        
        // Draw character selection boxes
        int start_x = 120;
        int start_y = 100;
        int spacing = 100;
        
        for (int i = 0; i < NUM_CHARACTERS; i++)
        {
            int x = start_x + (i * spacing);
            draw_character_box(game_buffer, i, x, start_y, 
                             (i == p1_cursor), p1_ready);
        }
        
        // Draw second row for Player 2
        for (int i = 0; i < NUM_CHARACTERS; i++)
        {
            int x = start_x + (i * spacing);
            draw_character_box(game_buffer, i, x, start_y + 150, 
                             (i == p2_cursor), p2_ready);
        }
        
        // Draw player labels
        textout_ex(game_buffer, game_font, "PLAYER 1", 50, start_y + 40, makecol(255, 100, 100), -1);
        textout_ex(game_buffer, game_font, "PLAYER 2", 50, start_y + 190, makecol(100, 100, 255), -1);
        
        // Instructions
        textout_centre_ex(game_buffer, game_font, "Left/Right to select, A to confirm", 320, 420, makecol(200, 200, 200), -1);
        
        // Player 1 input (only if not ready)
        if (!p1_ready)
        {
            if (key[p1_left_key] && !p1_left_pressed)
            {
                p1_cursor = (p1_cursor - 1 + NUM_CHARACTERS) % NUM_CHARACTERS;
                p1_left_pressed = true;
            }
            if (!key[p1_left_key]) p1_left_pressed = false;
            
            if (key[p1_right_key] && !p1_right_pressed)
            {
                p1_cursor = (p1_cursor + 1) % NUM_CHARACTERS;
                p1_right_pressed = true;
            }
            if (!key[p1_right_key]) p1_right_pressed = false;
            
            if (key[p1_bt1_key] && !p1_a_pressed)
            {
                p1_ready = true;
                players[0].character_id = p1_cursor;
                p1_a_pressed = true;
            }
            if (!key[p1_bt1_key]) p1_a_pressed = false;
        }
        
        // Player 2 input (only if not ready)
        if (!p2_ready)
        {
            if (key[p2_left_key] && !p2_left_pressed)
            {
                p2_cursor = (p2_cursor - 1 + NUM_CHARACTERS) % NUM_CHARACTERS;
                p2_left_pressed = true;
            }
            if (!key[p2_left_key]) p2_left_pressed = false;
            
            if (key[p2_right_key] && !p2_right_pressed)
            {
                p2_cursor = (p2_cursor + 1) % NUM_CHARACTERS;
                p2_right_pressed = true;
            }
            if (!key[p2_right_key]) p2_right_pressed = false;
            
            if (key[p2_bt1_key] && !p2_a_pressed)
            {
                p2_ready = true;
                players[1].character_id = p2_cursor;
                p2_a_pressed = true;
            }
            if (!key[p2_bt1_key]) p2_a_pressed = false;
        }
        
        // Both players ready - start fight
        if (p1_ready && p2_ready)
        {
            game_mode = 2; // Go to fight
            init_player(&players[0], 0);
            players[0].character_id = p1_cursor;
            init_player(&players[1], 1);
            players[1].character_id = p2_cursor;
        }
    }
    else if (game_mode == 2)
    {
        // Fighting game logic
        
        // Draw stage background
        draw_stage_background(game_buffer, players[0].character_id, players[1].character_id);
        
        // Update Player 1
        Player* p1 = &players[0];
        static int p1_attack_cooldown = 0;
        if (p1_attack_cooldown > 0) p1_attack_cooldown--;
        
        if (p1->health > 0)
        {
            // Check if blocking (B button / bt2)
            bool was_blocking = p1->is_blocking;
            p1->is_blocking = key[p1_bt2_key];
            
            // Block sound effect (when starting to block)
            if (p1->is_blocking && !was_blocking)
            {
                play_sound(SOUND_BLOCK);
            }
            
            // Movement (slower when blocking)
            float speed_multiplier = p1->is_blocking ? BLOCKING_SPEED_MULTIPLIER : 1.0f;
            if (key[p1_left_key]) { p1->vx = -3.0f * speed_multiplier; p1->facing = -1; }
            else if (key[p1_right_key]) { p1->vx = 3.0f * speed_multiplier; p1->facing = 1; }
            else { p1->vx *= 0.8f; }
            
            // Jump (can't jump while blocking)
            if (key[p1_up_key] && p1->on_ground && !p1->is_blocking)
            {
                p1->vy = -12.0f;
                p1->on_ground = false;
                play_sound(SOUND_JUMP); // Jump sound effect
            }
            
            // Attack with cooldown (can't attack while blocking)
            if (key[p1_bt1_key] && p1_attack_cooldown == 0 && !p1->is_blocking)
            {
                play_sound(SOUND_ATTACK); // Attack sound effect
                
                // Simple punch attack - check collision with P2
                Player* p2 = &players[1];
                float dist = fabs(p1->x - p2->x);
                if (dist < 50.0f && p2->health > 0)
                {
                    // Check if P2 is blocking
                    if (p2->is_blocking)
                    {
                        // Reduced damage when blocking
                        p2->health -= BLOCKED_DAMAGE;
                        if (p2->health < 0) p2->health = 0;
                        play_sound(SOUND_BLOCK); // Block impact sound
                    }
                    else
                    {
                        // Full damage
                        p2->health -= NORMAL_DAMAGE;
                        if (p2->health < 0) p2->health = 0;
                        play_sound(SOUND_HIT); // Hit sound effect
                    }
                    p1_attack_cooldown = 15; // 15 frames cooldown (~0.25 seconds)
                }
            }
            
            // Physics
            p1->vy += 0.5f; // Gravity
            p1->x += p1->vx;
            p1->y += p1->vy;
            
            // Collision with ground
            if (p1->y >= 350.0f)
            {
                p1->y = 350.0f;
                p1->vy = 0.0f;
                p1->on_ground = true;
            }
            
            // Boundary check
            if (p1->x < 20.0f) p1->x = 20.0f;
            if (p1->x > 620.0f) p1->x = 620.0f;
        }
        
        // Update Player 2
        Player* p2 = &players[1];
        static int p2_attack_cooldown = 0;
        if (p2_attack_cooldown > 0) p2_attack_cooldown--;
        
        if (p2->health > 0)
        {
            // Check if blocking (B button / bt2)
            bool was_blocking = p2->is_blocking;
            p2->is_blocking = key[p2_bt2_key];
            
            // Block sound effect (when starting to block)
            if (p2->is_blocking && !was_blocking)
            {
                play_sound(SOUND_BLOCK);
            }
            
            // Movement (slower when blocking)
            float speed_multiplier = p2->is_blocking ? BLOCKING_SPEED_MULTIPLIER : 1.0f;
            if (key[p2_left_key]) { p2->vx = -3.0f * speed_multiplier; p2->facing = -1; }
            else if (key[p2_right_key]) { p2->vx = 3.0f * speed_multiplier; p2->facing = 1; }
            else { p2->vx *= 0.8f; }
            
            // Jump (can't jump while blocking)
            if (key[p2_up_key] && p2->on_ground && !p2->is_blocking)
            {
                p2->vy = -12.0f;
                p2->on_ground = false;
                play_sound(SOUND_JUMP); // Jump sound effect
            }
            
            // Attack with cooldown (can't attack while blocking)
            if (key[p2_bt1_key] && p2_attack_cooldown == 0 && !p2->is_blocking)
            {
                play_sound(SOUND_ATTACK); // Attack sound effect
                
                // Simple punch attack - check collision with P1
                float dist = fabs(p2->x - p1->x);
                if (dist < 50.0f && p1->health > 0)
                {
                    // Check if P1 is blocking
                    if (p1->is_blocking)
                    {
                        // Reduced damage when blocking
                        p1->health -= BLOCKED_DAMAGE;
                        if (p1->health < 0) p1->health = 0;
                        play_sound(SOUND_BLOCK); // Block impact sound
                    }
                    else
                    {
                        // Full damage
                        p1->health -= NORMAL_DAMAGE;
                        if (p1->health < 0) p1->health = 0;
                        play_sound(SOUND_HIT); // Hit sound effect
                    }
                    p2_attack_cooldown = 15; // 15 frames cooldown (~0.25 seconds)
                }
            }
            
            // Physics
            p2->vy += 0.5f; // Gravity
            p2->x += p2->vx;
            p2->y += p2->vy;
            
            // Collision with ground
            if (p2->y >= 350.0f)
            {
                p2->y = 350.0f;
                p2->vy = 0.0f;
                p2->on_ground = true;
            }
            
            // Boundary check
            if (p2->x < 20.0f) p2->x = 20.0f;
            if (p2->x > 620.0f) p2->x = 620.0f;
        }
        
        // Draw players
        draw_player(game_buffer, p1);
        draw_player(game_buffer, p2);
        
        // Draw HUD
        textout_ex(game_buffer, game_font, "P1", 50, 20, makecol(255, 100, 100), -1);
        char p1_health_str[32];
        sprintf(p1_health_str, "HP: %d", p1->health);
        textout_ex(game_buffer, game_font, p1_health_str, 50, 35, makecol(255, 255, 255), -1);
        
        textout_ex(game_buffer, game_font, "P2", 550, 20, makecol(100, 100, 255), -1);
        char p2_health_str[32];
        sprintf(p2_health_str, "HP: %d", p2->health);
        textout_ex(game_buffer, game_font, p2_health_str, 550, 35, makecol(255, 255, 255), -1);
        
        // Check for winner
        if (p1->health <= 0 || p2->health <= 0)
        {
            game_mode = 3;
        }
    }
    else if (game_mode == 3)
    {
        // Winner screen
        clear_to_color(game_buffer, makecol(20, 20, 40));
        
        if (players[0].health > 0)
        {
            textout_centre_ex(game_buffer, game_font, "PLAYER 1 WINS!", 320, 200, makecol(255, 200, 100), -1);
        }
        else
        {
            textout_centre_ex(game_buffer, game_font, "PLAYER 2 WINS!", 320, 200, makecol(100, 200, 255), -1);
        }
        
        textout_centre_ex(game_buffer, game_font, "Press START for rematch", 320, 250, makecol(200, 200, 200), -1);
        
        if (key[p1_start_key] || key[p2_start_key])
        {
            game_mode = 1; // Back to character select
            p1_ready = false;
            p2_ready = false;
            p1_cursor = players[0].character_id;
            p2_cursor = players[1].character_id;
        }
    }
    
    // Copy game buffer to screen buffer
    blit(game_buffer, screen_buffer, 0, 0, 0, 0, 640, 480);
}

BITMAP* hamoopi_get_screen_buffer(void)
{
   return screen_buffer;
}

void hamoopi_set_input_state(unsigned port, unsigned device, unsigned index, unsigned id, int16_t state)
{
   if (port > 1)
      return;
   
   switch (id)
   {
      case RETRO_DEVICE_ID_JOYPAD_UP:
         hamoopi_input[port].up = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_DOWN:
         hamoopi_input[port].down = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_LEFT:
         hamoopi_input[port].left = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_RIGHT:
         hamoopi_input[port].right = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_A:
         hamoopi_input[port].a = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_B:
         hamoopi_input[port].b = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_X:
         hamoopi_input[port].x = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_Y:
         hamoopi_input[port].y = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_L:
         hamoopi_input[port].l = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_R:
         hamoopi_input[port].r = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_SELECT:
         hamoopi_input[port].select = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_START:
         hamoopi_input[port].start = state;
         break;
   }
}

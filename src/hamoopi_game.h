#ifndef HAMOOPI_GAME_H
#define HAMOOPI_GAME_H

#include "hamoopi_types.h"

// Funções do game loop principal
void game_loop_intro();
void game_loop_donation_screen();
void game_loop_apresentacao();
void game_loop_select_char();
void game_loop_versus_screen();
void game_loop_gameplay();
void game_loop_options();
void game_loop_editor();

// Funções auxiliares do game loop
void update_game_timers();
void handle_alt_enter();

#endif // HAMOOPI_GAME_H

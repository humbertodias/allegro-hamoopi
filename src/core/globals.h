#ifndef HAMOOPI_GLOBALS_H
#define HAMOOPI_GLOBALS_H

#include "types.h"
#include <SDL2/SDL.h>  // For Uint64 type

// Global variable declarations for HAMOOPI game engine
// These are defined in HAMOOPI.c and accessible to all modules

// Key mapping macros (defined in HAMOOPI.c)
#ifndef P1_UP
#define P1_UP     ( key[ p1_up     ] )
#define P1_DOWN   ( key[ p1_down   ] )
#define P1_LEFT   ( key[ p1_left   ] )
#define P1_RIGHT  ( key[ p1_right  ] )
#define P1_BT1    ( key[ p1_bt1    ] )
#define P1_BT2    ( key[ p1_bt2    ] )
#define P1_BT3    ( key[ p1_bt3    ] )
#define P1_BT4    ( key[ p1_bt4    ] )
#define P1_BT5    ( key[ p1_bt5    ] )
#define P1_BT6    ( key[ p1_bt6    ] )
#define P1_SELECT ( key[ p1_select ] )
#define P1_START  ( key[ p1_start  ] )
#define P2_UP     ( key[ p2_up     ] )
#define P2_DOWN   ( key[ p2_down   ] )
#define P2_LEFT   ( key[ p2_left   ] )
#define P2_RIGHT  ( key[ p2_right  ] )
#define P2_BT1    ( key[ p2_bt1    ] )
#define P2_BT2    ( key[ p2_bt2    ] )
#define P2_BT3    ( key[ p2_bt3    ] )
#define P2_BT4    ( key[ p2_bt4    ] )
#define P2_BT5    ( key[ p2_bt5    ] )
#define P2_BT6    ( key[ p2_bt6    ] )
#define P2_SELECT ( key[ p2_select ] )
#define P2_START  ( key[ p2_start  ] )
#define MAX_CHARS 8
#endif

// Core timing variables
extern Uint64 frame_count;  // Frame counter for SDL2 timing
extern float delay;
extern int timermenus;
extern float EndRoundSlowDown;

// Player global arrays
extern struct HitSparkDEF HitSpark[99];
extern struct FireballsDEF Fireball[3];
extern struct PlayerDEF P[3];

// Key configuration
extern int p1_up, p2_up;
extern int p1_down, p2_down;
extern int p1_left, p2_left;
extern int p1_right, p2_right;
extern int p1_bt1, p2_bt1;
extern int p1_bt2, p2_bt2;
extern int p1_bt3, p2_bt3;
extern int p1_bt4, p2_bt4;
extern int p1_bt5, p2_bt5;
extern int p1_bt6, p2_bt6;
extern int p1_select, p2_select;
extern int p1_start, p2_start;

// Game state
extern int desabilita_players;
extern int GamePlayMode;
extern int EditMode;

// Mouse and function key states
extern int key_Mouse_L_pressed, key_Mouse_L_hold, key_Mouse_L_released, key_Mouse_L_status;
extern int key_Mouse_R_pressed, key_Mouse_R_hold, key_Mouse_R_released, key_Mouse_R_status;
extern int key_F1_pressed, key_F1_hold, key_F1_released, key_F1_status;
extern int key_F2_pressed, key_F2_hold, key_F2_released, key_F2_status;
extern int key_F3_pressed, key_F3_hold, key_F3_released, key_F3_status;
extern int key_F4_pressed, key_F4_hold, key_F4_released, key_F4_status;

// Collision and hit detection globals
extern int AlturaPiso;
extern int MeioDaTela;
extern int Qtde_HitBox;
extern unsigned int HitPauseKO;

// Hit box variables - Player 1
extern int P1_HurtBox01x1, P1_HurtBox01y1, P1_HurtBox01x2, P1_HurtBox01y2;
extern int P1_HurtBox02x1, P1_HurtBox02y1, P1_HurtBox02x2, P1_HurtBox02y2;
extern int P1_HurtBox03x1, P1_HurtBox03y1, P1_HurtBox03x2, P1_HurtBox03y2;
extern int P1_HurtBox04x1, P1_HurtBox04y1, P1_HurtBox04x2, P1_HurtBox04y2;
extern int P1_HurtBox05x1, P1_HurtBox05y1, P1_HurtBox05x2, P1_HurtBox05y2;
extern int P1_HurtBox06x1, P1_HurtBox06y1, P1_HurtBox06x2, P1_HurtBox06y2;
extern int P1_HurtBox07x1, P1_HurtBox07y1, P1_HurtBox07x2, P1_HurtBox07y2;
extern int P1_HurtBox08x1, P1_HurtBox08y1, P1_HurtBox08x2, P1_HurtBox08y2;
extern int P1_HurtBox09x1, P1_HurtBox09y1, P1_HurtBox09x2, P1_HurtBox09y2;
extern int P1_HitBox01x1, P1_HitBox01y1, P1_HitBox01x2, P1_HitBox01y2;
extern int P1_HitBox02x1, P1_HitBox02y1, P1_HitBox02x2, P1_HitBox02y2;
extern int P1_HitBox03x1, P1_HitBox03y1, P1_HitBox03x2, P1_HitBox03y2;
extern int P1_HitBox04x1, P1_HitBox04y1, P1_HitBox04x2, P1_HitBox04y2;
extern int P1_HitBox05x1, P1_HitBox05y1, P1_HitBox05x2, P1_HitBox05y2;
extern int P1_HitBox06x1, P1_HitBox06y1, P1_HitBox06x2, P1_HitBox06y2;
extern int P1_HitBox07x1, P1_HitBox07y1, P1_HitBox07x2, P1_HitBox07y2;
extern int P1_HitBox08x1, P1_HitBox08y1, P1_HitBox08x2, P1_HitBox08y2;
extern int P1_HitBox09x1, P1_HitBox09y1, P1_HitBox09x2, P1_HitBox09y2;
extern int P1_HurtBox_tot, P1_HitBox_tot;

// Hit box variables - Player 2
extern int P2_HurtBox01x1, P2_HurtBox01y1, P2_HurtBox01x2, P2_HurtBox01y2;
extern int P2_HurtBox02x1, P2_HurtBox02y1, P2_HurtBox02x2, P2_HurtBox02y2;
extern int P2_HurtBox03x1, P2_HurtBox03y1, P2_HurtBox03x2, P2_HurtBox03y2;
extern int P2_HurtBox04x1, P2_HurtBox04y1, P2_HurtBox04x2, P2_HurtBox04y2;
extern int P2_HurtBox05x1, P2_HurtBox05y1, P2_HurtBox05x2, P2_HurtBox05y2;
extern int P2_HurtBox06x1, P2_HurtBox06y1, P2_HurtBox06x2, P2_HurtBox06y2;
extern int P2_HurtBox07x1, P2_HurtBox07y1, P2_HurtBox07x2, P2_HurtBox07y2;
extern int P2_HurtBox08x1, P2_HurtBox08y1, P2_HurtBox08x2, P2_HurtBox08y2;
extern int P2_HurtBox09x1, P2_HurtBox09y1, P2_HurtBox09x2, P2_HurtBox09y2;
extern int P2_HitBox01x1, P2_HitBox01y1, P2_HitBox01x2, P2_HitBox01y2;
extern int P2_HitBox02x1, P2_HitBox02y1, P2_HitBox02x2, P2_HitBox02y2;
extern int P2_HitBox03x1, P2_HitBox03y1, P2_HitBox03x2, P2_HitBox03y2;
extern int P2_HitBox04x1, P2_HitBox04y1, P2_HitBox04x2, P2_HitBox04y2;
extern int P2_HitBox05x1, P2_HitBox05y1, P2_HitBox05x2, P2_HitBox05y2;
extern int P2_HitBox06x1, P2_HitBox06y1, P2_HitBox06x2, P2_HitBox06y2;
extern int P2_HitBox07x1, P2_HitBox07y1, P2_HitBox07x2, P2_HitBox07y2;
extern int P2_HitBox08x1, P2_HitBox08y1, P2_HitBox08x2, P2_HitBox08y2;
extern int P2_HitBox09x1, P2_HitBox09y1, P2_HitBox09x2, P2_HitBox09y2;
extern int P2_HurtBox_tot, P2_HitBox_tot;

// Fireball hit boxes
extern int P1_Fireball_HurtBox01x1, P1_Fireball_HurtBox01y1, P1_Fireball_HurtBox01x2, P1_Fireball_HurtBox01y2;
extern int P2_Fireball_HurtBox01x1, P2_Fireball_HurtBox01y1, P2_Fireball_HurtBox01x2, P2_Fireball_HurtBox01y2;
extern int P1_Fireball_HitBox01x1, P1_Fireball_HitBox01y1, P1_Fireball_HitBox01x2, P1_Fireball_HitBox01y2;
extern int P2_Fireball_HitBox01x1, P2_Fireball_HitBox01y1, P2_Fireball_HitBox01x2, P2_Fireball_HitBox01y2;

// Hit detection variables
extern int P1_Hit_x, P1_Hit_y;
extern int P2_Hit_x, P2_Hit_y;
extern int colisaoxP1, alturadohitp2;
extern int colisaoxP2, alturadohitp1;
extern int colisaoxP1Fireball;
extern int colisaoxP2Fireball;
extern int temp1x, temp1y, temp2x, temp2y;
extern int HitPause1, HitPause2, HitPause3;
extern int P1_DMG1, P1_DMG2, P1_DMG3;
extern int P2_DMG1, P2_DMG2, P2_DMG3;
extern int MomentoDoP1, MomentoDoP2;
extern int ForcaDoGolpeP1, ForcaDoGolpeP2;
extern int AHitP1, AHitP2;
extern int P1HitPause, P2HitPause;
extern int P1HitOn, P2HitOn;
extern int ShakeDist;
extern int contatofisico;
extern int PlaySoundHitLvl1;
extern int PlaySoundHitLvl2;
extern int PlaySoundHitLvl3;

// Color palette variables
extern char P1_Pallete_string[40];
extern char P2_Pallete_string[40];
extern BITMAP *P1_Pallete;
extern BITMAP *P2_Pallete;
extern int P1_ContadorDeCor;
extern int P2_ContadorDeCor;

// Player 1 color manipulation
extern int P1_COR_ORIGINAL;
extern int P1_COR_ORIGINAL_R;
extern int P1_COR_ORIGINAL_G;
extern int P1_COR_ORIGINAL_B;
extern int P1_COR_ALTERNATIVA;
extern int P1_COR_ALTERNATIVA_R;
extern int P1_COR_ALTERNATIVA_G;
extern int P1_COR_ALTERNATIVA_B;

// Player 2 color manipulation
extern int P2_COR_ORIGINAL;
extern int P2_COR_ORIGINAL_R;
extern int P2_COR_ORIGINAL_G;
extern int P2_COR_ORIGINAL_B;
extern int P2_COR_ALTERNATIVA;
extern int P2_COR_ALTERNATIVA_R;
extern int P2_COR_ALTERNATIVA_G;
extern int P2_COR_ALTERNATIVA_B;

// Editor variables
extern char ED_Name[50];
extern int ED_CharID;
extern int ED_Tipo;
extern int ED_MODE;
extern int ED_Special_Version;
extern int ED_StartFrame;
extern int ED_TotalFrames;
extern int ED_State;
extern int ED_IndexAnim;
extern int ED_Lado;
extern int ED_XAlign, ED_YAlign;
extern int ED_x, ED_y;
extern int ED_Altura, ED_Largura;
extern int ED_Altura_100, ED_Largura_100;
extern int MovPossiveis[99];
extern int MovPossiveisIndex;
extern int ED_Pause;
extern int ED_DrawBlueMode, ED_DrawRedMode;
extern int ED_CarregarDados;
extern int ED_ShowMsgSaving;
extern int ED_alertsave;
extern int ED_bt_Null;
extern int ED_Mx1, ED_My1, ED_Mx2, ED_My2;
extern int Edtimer;
extern int ED_StartFrame;
extern char ED_Name_Display[50];
extern int ED_HitBox01x1, ED_HitBox01y1, ED_HitBox01x2, ED_HitBox01y2;
extern int ED_HitBox02x1, ED_HitBox02y1, ED_HitBox02x2, ED_HitBox02y2;
extern int ED_HitBox03x1, ED_HitBox03y1, ED_HitBox03x2, ED_HitBox03y2;
extern int ED_HitBox04x1, ED_HitBox04y1, ED_HitBox04x2, ED_HitBox04y2;
extern int ED_HitBox05x1, ED_HitBox05y1, ED_HitBox05x2, ED_HitBox05y2;
extern int ED_HitBox06x1, ED_HitBox06y1, ED_HitBox06x2, ED_HitBox06y2;
extern int ED_HitBox07x1, ED_HitBox07y1, ED_HitBox07x2, ED_HitBox07y2;
extern int ED_HitBox08x1, ED_HitBox08y1, ED_HitBox08x2, ED_HitBox08y2;
extern int ED_HitBox09x1, ED_HitBox09y1, ED_HitBox09x2, ED_HitBox09y2;
extern int ED_HurtBox01x1, ED_HurtBox01y1, ED_HurtBox01x2, ED_HurtBox01y2;
extern int ED_HurtBox02x1, ED_HurtBox02y1, ED_HurtBox02x2, ED_HurtBox02y2;
extern int ED_HurtBox03x1, ED_HurtBox03y1, ED_HurtBox03x2, ED_HurtBox03y2;
extern int ED_HurtBox04x1, ED_HurtBox04y1, ED_HurtBox04x2, ED_HurtBox04y2;
extern int ED_HurtBox05x1, ED_HurtBox05y1, ED_HurtBox05x2, ED_HurtBox05y2;
extern int ED_HurtBox06x1, ED_HurtBox06y1, ED_HurtBox06x2, ED_HurtBox06y2;
extern int ED_HurtBox07x1, ED_HurtBox07y1, ED_HurtBox07x2, ED_HurtBox07y2;
extern int ED_HurtBox08x1, ED_HurtBox08y1, ED_HurtBox08x2, ED_HurtBox08y2;
extern int ED_HurtBox09x1, ED_HurtBox09y1, ED_HurtBox09x2, ED_HurtBox09y2;
extern int ED_HitBox_tot, ED_HurtBox_tot;

// Frame time variables for animation
extern int P1_FrameTime_00, P1_FrameTime_01, P1_FrameTime_02, P1_FrameTime_03, P1_FrameTime_04, P1_FrameTime_05;
extern int P1_FrameTime_06, P1_FrameTime_07, P1_FrameTime_08, P1_FrameTime_09, P1_FrameTime_10;
extern int P1_FrameTime_11, P1_FrameTime_12, P1_FrameTime_13, P1_FrameTime_14, P1_FrameTime_15;
extern int P1_FrameTime_16, P1_FrameTime_17, P1_FrameTime_18, P1_FrameTime_19, P1_FrameTime_20;
extern int P1_FrameTime_21, P1_FrameTime_22, P1_FrameTime_23, P1_FrameTime_24, P1_FrameTime_25;
extern int P1_FrameTime_26, P1_FrameTime_27, P1_FrameTime_28, P1_FrameTime_29, P1_FrameTime;

extern int P2_FrameTime_00, P2_FrameTime_01, P2_FrameTime_02, P2_FrameTime_03, P2_FrameTime_04, P2_FrameTime_05;
extern int P2_FrameTime_06, P2_FrameTime_07, P2_FrameTime_08, P2_FrameTime_09, P2_FrameTime_10;
extern int P2_FrameTime_11, P2_FrameTime_12, P2_FrameTime_13, P2_FrameTime_14, P2_FrameTime_15;
extern int P2_FrameTime_16, P2_FrameTime_17, P2_FrameTime_18, P2_FrameTime_19, P2_FrameTime_20;
extern int P2_FrameTime_21, P2_FrameTime_22, P2_FrameTime_23, P2_FrameTime_24, P2_FrameTime_25;
extern int P2_FrameTime_26, P2_FrameTime_27, P2_FrameTime_28, P2_FrameTime_29, P2_FrameTime;

extern int ED_FrameTime_00, ED_FrameTime_01, ED_FrameTime_02, ED_FrameTime_03, ED_FrameTime_04, ED_FrameTime_05;
extern int ED_FrameTime_06, ED_FrameTime_07, ED_FrameTime_08, ED_FrameTime_09, ED_FrameTime_10;
extern int ED_FrameTime_11, ED_FrameTime_12, ED_FrameTime_13, ED_FrameTime_14, ED_FrameTime_15;
extern int ED_FrameTime_16, ED_FrameTime_17, ED_FrameTime_18, ED_FrameTime_19, ED_FrameTime_20;
extern int ED_FrameTime_21, ED_FrameTime_22, ED_FrameTime_23, ED_FrameTime_24, ED_FrameTime_25;
extern int ED_FrameTime_26, ED_FrameTime_27, ED_FrameTime_28, ED_FrameTime_29, ED_FrameTime;

extern int P1_Fireball_FrameTime_00, P1_Fireball_FrameTime_01, P1_Fireball_FrameTime_02;
extern int P1_Fireball_FrameTime_03, P1_Fireball_FrameTime_04, P1_Fireball_FrameTime_05;
extern int P1_Fireball_FrameTime_06, P1_Fireball_FrameTime_07, P1_Fireball_FrameTime_08;
extern int P1_Fireball_FrameTime_09, P1_Fireball_FrameTime_10, P1_Fireball_FrameTime;

extern int P2_Fireball_FrameTime_00, P2_Fireball_FrameTime_01, P2_Fireball_FrameTime_02;
extern int P2_Fireball_FrameTime_03, P2_Fireball_FrameTime_04, P2_Fireball_FrameTime_05;
extern int P2_Fireball_FrameTime_06, P2_Fireball_FrameTime_07, P2_Fireball_FrameTime_08;
extern int P2_Fireball_FrameTime_09, P2_Fireball_FrameTime_10, P2_Fireball_FrameTime;

// game_play
extern int FadeIN, FadeOUT, FadeCtr, sair, IntroTimer, DonationScreen, ApresentacaoMode, IntroMode, SelectCharMode,
        OptionsMode;
extern char IDIOMA[3];
// presentation
extern int menu_op, options_op;
extern char ChoiceP1[50];
extern char ChoiceP2[50];
extern char ChoiceBG[50];

extern char versao[45];

// game_play
extern int timer_rounds, RoundTime, timer_final_de_rounds, EndRoundT, RoundAtual, RoundTotal, ModoHistoria, ModoMapa, SelectCharMode, EditModeTime;
extern BITMAP *P1_1, *P2_1, *bg_test;
extern MIDI *bgm_select_screen;
extern SAMPLE *back;
extern int Ctrl_FPS, Draw_Debug, Draw_Input, Draw_Box, ativa_especial, bta, btb, btc;
extern int ZoomMaximoAtingido, Zoom_eixo, VScreen_FatorZoom;
extern float VScreen_w, VScreen_h, VScreen_x, VScreen_y, VScreen_x2, VScreen_y2;
extern int op_ShowFrameData, op_Zoom, op_desenhar_sombras;
extern SAMPLE *attacklvl1, *attacklvl2, *attacklvl3, *hitlvl1, *hitlvl2, *hitlvl3, *ko, *perfect, *round1, *round2, *
        round3, *fight;

extern BITMAP *bufferx, *LayerHUD, *LayerHUDa, *LayerHUDb;
extern FONT *font_debug, *font_10, *font_19, *font_20, *font_30;

extern BITMAP *P1_Sombra, *P2_Sombra, *P1_Sombra_Aux, *P2_Sombra_Aux, *P1_energy_flip, *P1_energy_red_flip;
extern BITMAP *HitSparkspr, *HitSpark_Aux;

extern float delay;
extern int Horas, Minutos, Segundos;

extern BITMAP *spr991_00, *spr991_01, *spr991_02, *spr991_03, *spr991_04, *spr991_05, *spr992_00, *spr992_01, *spr992_02
        , *spr992_03, *spr992_04, *spr992_05, *spr993_00, *spr993_01, *spr993_02, *spr993_03, *spr993_04, *spr993_05, *
        spr994_00, *spr994_01, *spr994_02, *spr994_03, *spr994_04, *spr994_05;
extern BITMAP *spr_input_0, *spr_input_1, *spr_input_2, *spr_input_3, *spr_input_4, *spr_input_5, *spr_input_6, *
        spr_input_7, *spr_input_8, *spr_input_9, *spr_input_10, *spr_input_11, *spr_input_12, *spr_input_13, *
        spr_input_14, *spr_input_15, *spr_input_16, *spr_input_17, *spr_bg_bar, *spr_energy_bar, *spr_energy_bar_full, *
        spr_energy_red_bar, *spr_energy_red_bar_ful, *spr_bg_bar_sp, *spr_bg_energy_bar_sp, *GAME_logo, *flag_BR, *
        sel_mark_p1, *sel_mark_p2, *flag_US, *SELECT_CHARS, *VS_SCREEN, *vs_icon, *SELECT_BG, *donation, *spr_p1_cursor,
        *spr_p2_cursor, *spr_cursor_historia, *spr_cursor_vazio, *spr_ponteiro, *spr_menu_icon, *GAME_intro, *
        GAME_options, *char_generic, *char_generic2x, *spr_mold_results, *spr_result_perfect, *spr_result_win, *
        spr_splash_round1, *spr_splash_round2, *spr_splash_round3, *spr_splash_round4, *spr_splash_round5, *
        spr_splash_fight, *spr_splash_youwin, *spr_splash_p1win, *spr_splash_p2win, *spr_splash_youlose, *spr_splash_ko,
        *spr_splash_perfect, *spr_splash_draw, *spr_splash_time_ove, *spr, *edit_bt_blue, *edit_bt_red, *edit_bt_null, *
        edit_bt_null0, *edit_prevst, *edit_nextst, *edit_prevchar, *edit_nextchar, *edit_firstchar, *edit_lastchar, *
        spr_nao_implementad, *edit_playback, *edit_pause, *edit_bt_FrameTime, *edit_bt_plus, *edit_bt_minus, *mouse, *
        mouse2, *save_file, *bt_pivot, *spr000_00, *spr000_01, *bt_joystick, *ed_mode1_on, *ed_mode2_on, *ed_mode1_off,
        *ed_mode2_off, *bt_reset_input, *bt_up_1, *bt_up_2, *bt_up_3, *bt_down_1, *bt_down_2, *bt_down_3, *bt_left_1, *
        bt_left_2, *bt_left_3, *bt_right_1, *bt_right_2, *bt_right_3, *bt_1, *bt_2, *bt_3, *bt_ss_1, *bt_ss_2, *bt_ss_3,
        *P1_Sombra, *P2_Sombra, *P1_Sombra_Aux, *P2_Sombra_Aux, *P1_energy_flip, *P1_energy_red_fli, *ED_Spr, *ED_Mini,
        *P1_Spr_Aux, *P2_Spr_Aux, *ED_Spr_Aux, *HitSparkspr, *HitSpark_Aux, *P1_Pallete, *P2_Pallete;

extern int FD_P1_Status, FD_P1_Startup, FD_P1_Active, FD_P1_Recovery, FD_P1_Active_IN, FD_P1_Active_OUT, FD_P1_HitBox01,
        FD_P1_HitBox01x1, FD_P2_Status, FD_P2_Startup, FD_P2_Active, FD_P2_Recovery, FD_P2_Active_IN, FD_P2_Active_OUT,
        FD_P2_HitBox01x1;
extern BITMAP *spr_input_0, *spr_input_1, *spr_input_2, *spr_input_3, *spr_input_4, *spr_input_5, *spr_input_6, *
        spr_input_7, *spr_input_8, *spr_input_9, *spr_input_10, *spr_input_11, *spr_input_12, *spr_input_13, *
        spr_input_14, *spr_input_15, *spr_input_16, *spr_input_17, *spr_bg_bar, *spr_energy_bar, *spr_energy_bar_full, *
        spr_energy_red_bar, *spr_energy_red_bar_full, *spr_bg_bar_sp, *spr_bg_energy_bar_sp, *GAME_logo, *flag_BR, *
        sel_mark_p1, *sel_mark_p2, *flag_US, *SELECT_CHARS, *VS_SCREEN, *vs_icon, *SELECT_BG, *donation, *spr_p1_cursor,
        *spr_p2_cursor, *spr_cursor_historia, *spr_cursor_vazio, *spr_ponteiro, *spr_menu_icon, *GAME_intro, *
        GAME_options, *char_generic, *char_generic2x, *spr_mold_results, *spr_result_perfect, *spr_result_win, *
        spr_splash_round1, *spr_splash_round2, *spr_splash_round3, *spr_splash_round4, *spr_splash_round5, *
        spr_splash_fight, *spr_splash_youwin, *spr_splash_p1win, *spr_splash_p2win, *spr_splash_youlose, *spr_splash_ko,
        *spr_splash_perfect, *spr_splash_draw, *spr_splash_time_over, *spr_num[10], *edit_bt_blue, *edit_bt_red, *
        edit_bt_null, *edit_bt_null0, *edit_prevst, *edit_nextst, *edit_prevchar, *edit_nextchar, *edit_firstchar, *
        edit_lastchar, *spr_nao_implementado, *edit_playback, *edit_pause, *edit_bt_FrameTime, *edit_bt_plus, *
        edit_bt_minus, *mouse, *mouse2, *save_file, *bt_pivot, *spr000_00, *spr000_01, *bt_joystick, *ed_mode1_on, *
        ed_mode2_on, *ed_mode1_off, *ed_mode2_off, *bt_reset_input, *bt_up_1, *bt_up_2, *bt_up_3, *bt_down_1, *bt_down_2
        , *bt_down_3, *bt_left_1, *bt_left_2, *bt_left_3, *bt_right_1, *bt_right_2, *bt_right_3, *bt_1, *bt_2, *bt_3, *
        bt_ss_1, *bt_ss_2, *bt_ss_3, *P1_Sombra, *P2_Sombra, *P1_Sombra_Aux, *P2_Sombra_Aux, *P1_energy_flip, *
        P1_energy_red_flip, *ED_Spr, *ED_Mini, *P1_Spr_Aux, *P2_Spr_Aux, *ED_Spr_Aux, *HitSparkspr, *HitSpark_Aux, *
        P1_Pallete, *P2_Pallete;
extern MIDI *bgm_versus_mode, *bgm_apresentacao;
extern int NumPersonagensEscolhidos, SelectCharTimerAnim, ModoMapaTimerAnim, Estagio_Atual, MapPosX, MapPosY, MapCenterX
        , MapCenterY;
extern char P1BIGDisplaystring[40], P2BIGDisplaystring[40], P1_Pallete_string[40], P2_Pallete_string[40];
extern BITMAP *P1BIGDisplay, *P2BIGDisplay, *P2BIGDisplayInv, *MINIsprDisplayArcadeMode[9], *MINIsprDisplay[9], *bg_test, *bg_hamoopi[9];
extern char Lista_de_Personagens_Instalados[9][50], Lista_de_Personagens_ArcadeMode[9][50], Lista_de_Cenarios_Instalados
        [9][50], Lista_de_Cenarios_ArcadeMode[9][50];
extern int Qtde_Personagens_Instalados, Qtde_Cenarios_Instalados, SelectCharP1ID, SelectCharP2ID, SelectBGID, TelaDeVersusTimer, TelaDeVersus, ModoFullscreen, WindowResX, WindowResY, op_sfx_volume, op_sound_volume, WindowResNumber;
extern SAMPLE *cursor, *choice, *intro, *confirm;
extern float AnimTransTimer;
extern int ED_MovimentaPivot, ED_alertsave2, ED_io, SelectBGID;

#endif // HAMOOPI_GLOBALS_H
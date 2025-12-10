#ifndef HAMOOPI_GLOBALS_H
#define HAMOOPI_GLOBALS_H

#include "hamoopi_types.h"

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
extern int timer;
extern float delay;
extern int timermenus;

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

#endif // HAMOOPI_GLOBALS_H

#ifndef HAMOOPI_TYPES_H
#define HAMOOPI_TYPES_H

#include "platform_compat.h"

// Macros para controles dos jogadores
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

// Estruturas de dados
struct HitSparkDEF {
    int x;
    int y;
    int Type;
    int StartFrame;
    int FrameTime;
    int IndexAnim;
    int TotalFrames;
    int QtdeFrames;
    int XAlign;
    int YAlign;
};

struct FireballsDEF {
    BITMAP *Spr;
    int Ativa;
    int ThrowFireball;
    int Direcao;
    int HSpeed;
    int VSpeed;
    int x;
    int y;
    int XAlign;
    int YAlign;
    int IndexAnim;
    int State;
    char State_s[3];
    int StartFrame;
    int TotalFrames;
};

struct PlayerDEF {
    BITMAP *Spr;
    char Name[50];
    char Name_Display[50];
    int Prioridade;
    int TotalDeImagensUtilizadas;
    BITMAP *SprAtlas[501];
    int TableAtlas[501][51];
    int Special_Inputs_c[10][17];
    int Special_Inputs_b[10][17];
    int Special_Inputs[10][17];
    int Special_Inputs_Ord[10][17];
    int PodeTestarEspecial;
    int Special_Version;
    int slot[17];
    int bt_slot[17];
    int t_slot[17];
    int ticks_4slot;
    int Pode_Mexer;
    int PossuiPaletaDeCor;
    int DefineCorDaPaleta;
    int Type;
    int Wins;
    int Loses;
    int Draws;
    int Perfects;
    int Round_Wins;
    int x;
    int y;
    int State;
    char State_s[3];
    char State_chs[99];
    int TotalStates;
    int IndexAnim;
    int StartFrame;
    int MovStartFrame;
    int TotalFrames;
    int QtdeFrames;
    int TotalDeFramesMov[999];
    int XAlign;
    int YAlign;
    int Lado;
    int Altura;
    int Largura;
    int ConstanteY;
    int Altura_100;
    int Largura_100;
    float Hspeed;
    float Vspeed;
    float Hspeed_temp;
    float Vspeed_temp;
    float Friction;
    float Gravity;
    float Gravity_temp;
    float Energy;
    int ChangeDamage;
    int EnergyChange;
    int EnergyRedBar;
    int EnergyRedBarSleep;
    int Special;
    int SpecialChange;
    int QtdeMagias;
    int Visible;
    int RoomLimit;
    char HitType[9];
    char HitType_string[9];
    char HitStack[9];
    char HitStack_string[9];
    int HitPause;
    int Damage;
    char Caminho_CHBOX[99];
    int ChangeState;
    int Freeze;
    int Color;
    int TempoPulo;
    float other_Hspeed;
    float other_Vspeed;
    float other_Friction;
    float other_Gravity;
    int other_Energy;
    int other_EnergyChange;
    int other_Special;
    int other_SpecialChange;
    int other_Visible;
    int other_RoomLimit;
    int other_HitType;
    int other_HitPause;
    int other_ChangeState;
    int other_Freeze;
    int other_Color;
    int other_TempoPulo;
    int key_UP_pressed, key_UP_hold, key_UP_released, key_UP_status;
    int key_DOWN_pressed, key_DOWN_hold, key_DOWN_released, key_DOWN_status;
    int key_LEFT_pressed, key_LEFT_hold, key_LEFT_released, key_LEFT_status;
    int key_RIGHT_pressed, key_RIGHT_hold, key_RIGHT_released, key_RIGHT_status;
    int key_BT1_pressed, key_BT1_hold, key_BT1_released, key_BT1_status;
    int key_BT2_pressed, key_BT2_hold, key_BT2_released, key_BT2_status;
    int key_BT3_pressed, key_BT3_hold, key_BT3_released, key_BT3_status;
    int key_BT4_pressed, key_BT4_hold, key_BT4_released, key_BT4_status;
    int key_BT5_pressed, key_BT5_hold, key_BT5_released, key_BT5_status;
    int key_BT6_pressed, key_BT6_hold, key_BT6_released, key_BT6_status;
    int key_SELECT_pressed, key_SELECT_hold, key_SELECT_released, key_SELECT_status;
    int key_START_pressed, key_START_hold, key_START_released, key_START_status;
    int key_W_pressed, key_W_hold, key_W_released, key_W_status;
    int key_A_pressed, key_A_hold, key_A_released, key_A_status;
    int key_S_pressed, key_S_hold, key_S_released, key_S_status;
    int key_D_pressed, key_D_hold, key_D_released, key_D_status;
    int Hbox[2][18][4];
    int Align[2][999][2];
};

// Variáveis globais externas
extern char versao[45];
extern int sair;
extern int timer;
extern float delay;
extern int Horas, Minutos, Segundos;
extern int timermenus;
extern int Ctrl_FPS;
extern int WindowResNumber;
extern int WindowResX;
extern int WindowResY;

extern struct HitSparkDEF HitSpark[99];
extern struct FireballsDEF Fireball[3];
extern struct PlayerDEF P[3];

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

// Outras variáveis de estado do jogo
extern int op_sound_volume;
extern int op_sfx_volume;
extern char IDIOMA[2];
extern int IntroMode;
extern int IntroTimer;
extern int DonationScreen;
extern int ApresentacaoMode;
extern int menu_op;
extern int OptionsMode;
extern int options_op;
extern int op_desenhar_sombras;
extern int op_ShowFrameData;
extern int GamePlayMode;
extern int EditMode;
extern int Draw_Debug;
extern int Draw_Input;
extern int Draw_Box;

#endif // HAMOOPI_TYPES_H

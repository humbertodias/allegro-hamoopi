#ifndef HAMOOPI_TYPES_H
#define HAMOOPI_TYPES_H

#include "../backend/platform_compat.h"

// Type definitions for HAMOOPI game structures
// 
// These structures depend on BITMAP type from platform_compat.h which provides
// platform-independent type definitions. The BITMAP type is mapped to:
// - Allegro 4: BITMAP (native Allegro type, directly available)
// - SDL2: struct PlatformBitmap wrapping SDL_Surface
// - Other: Forward declared struct for future implementations
//
// This header is designed to be included via hamoopi_core.h after platform_compat.h

struct HitSparkDEF {
    int x;
    int y;
    int Type; //991, 992, 993, 994, 995
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
    char State_s[4];
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
    /*--------------------
        Valores do TableAtlas (Parcialmente implementado)
        [0][ 0] State
        [0][ 1] Anim
        [0][ 2] TotalDeImagensUtilizadas; numero desta imagem no total de imagens do char
        [0][ 3] Frame_Time
        [0][ 4] XAlign
        [0][ 5] YAlign
        [0][ 6] x
        [0][ 7] y
        [0][ 8] VSpeed
        [0][ 9] HSpeed
        [0][10] Gravity
        [0][11] Friction
        [0][12] EnergyChange
        [0][13] SpecialChange
        [0][14] Visible
        [0][15] RoomLimit
        [0][16] HitType
        [0][17] ChangeState
        [0][18] Freeze
        [0][19] Color
        [0][20] HitStack
        ...
        [0][] other_x
        [0][] other_y
        [0][] other_VSpeed
        [0][] other_HSpeed
        [0][] other_Gravity
        [0][] other_Friction
        [0][] other_EnergyChange
        [0][] other_SpecialChange
        [0][] other_Visible
        [0][] other_RoomLimit
        [0][] other_HitType
        [0][] other_ChangeState
        [0][] other_Freeze
        [0][] other_Color
        [0][] other_HitStack
    --------------------*/
    int Special_Inputs_c[10][17]; //comandos direcionais
    int Special_Inputs_b[10][17]; //botoes
    int Special_Inputs[10][17]; //input combinado (dir+bt)
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
    int Type; //tipo de grafico: 1=Normal 2=HD Sprites
    int Wins;
    int Loses;
    int Draws;
    int Perfects;
    int Round_Wins;
    int x;
    int y;
    int State;
    char State_s[7];
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
    int Hbox[2][18][4]; //Player, Hit/HurtBox, (x1,y1,x2,y2)
    int Align[2][999][2]; //Player, State, (XAlign, YAlign)
};

#endif // HAMOOPI_TYPES_H

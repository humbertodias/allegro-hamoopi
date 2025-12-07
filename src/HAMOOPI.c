//   __  __     ______     __    __     ______     ______     ______   __     //
//  /\ \_\ \   /\  __ \   /\ "-./  \   /\  __ \   /\  __ \   /\  == \ /\ \    //
//  \ \  __ \  \ \  __ \  \ \ \-./\ \  \ \ \/\ \  \ \ \/\ \  \ \  _-/ \ \ \   //
//   \ \_\ \_\  \ \_\ \_\  \ \_\ \ \_\  \ \_____\  \ \_____\  \ \_\    \ \_\  //
//    \/_/\/_/   \/_/\/_/   \/_/  \/_/   \/_____/   \/_____/   \/_/     \/_/  //
//                                          by Daniel Moura (dev@hamoopi.com) //
//                                                                            //
// [**01] Declaracoes Iniciais                                                //
// [**02] Ini Allegro                                                         //
// [**03] Loop de Jogo                                                        //
// [**04] Sistema de Colisao                                                  //
// [**05] FSM                                                                 //
// [**06] Difs                                                                //
// [**07] Funcoes de Desenho                                                  //
// [**08] Debug                                                               //
// [**09] Edit Mode                                                           //
// [**10] Finalizacoes                                                        //
// [**11] Checar Teclas                                                       //
// [**12] STATES (Chg)                                                        //
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
	TO DO LIST: 
	Aqui vai a minha lista de Prioridades (não está em ordem):
	1- Configurar teclas / botoes / joystick no menu de opcoes
	2- Adicionar suporte para PNG, MP3 e OGG
	3- Adicionar modo Arcade, o jogo deve simular uma rom de fliperama,
	inclusive colocar fichas para jogar, modo Historia e Final
	4- Implementar corretamente todo o sistema de especiais - 40% concluido
	5- Backgrounds com multiplas layers animadas, musica do background
	6- Reescrever o Editor de Personagens
	7- Escrever a documentação do jogo
	8- Revisar / otimizar todo o código
*******************************************************************************/

#include "backend.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define P1_UP     ( backend_key[ p1_up     ] )
#define P1_DOWN   ( backend_key[ p1_down   ] )
#define P1_LEFT   ( backend_key[ p1_left   ] )
#define P1_RIGHT  ( backend_key[ p1_right  ] )
#define P1_BT1    ( backend_key[ p1_bt1    ] )
#define P1_BT2    ( backend_key[ p1_bt2    ] )
#define P1_BT3    ( backend_key[ p1_bt3    ] )
#define P1_BT4    ( backend_key[ p1_bt4    ] )
#define P1_BT5    ( backend_key[ p1_bt5    ] )
#define P1_BT6    ( backend_key[ p1_bt6    ] )
#define P1_SELECT ( backend_key[ p1_select ] )
#define P1_START  ( backend_key[ p1_start  ] )
#define P2_UP     ( backend_key[ p2_up     ] )
#define P2_DOWN   ( backend_key[ p2_down   ] )
#define P2_LEFT   ( backend_key[ p2_left   ] )
#define P2_RIGHT  ( backend_key[ p2_right  ] )
#define P2_BT1    ( backend_key[ p2_bt1    ] )
#define P2_BT2    ( backend_key[ p2_bt2    ] )
#define P2_BT3    ( backend_key[ p2_bt3    ] )
#define P2_BT4    ( backend_key[ p2_bt4    ] )
#define P2_BT5    ( backend_key[ p2_bt5    ] )
#define P2_BT6    ( backend_key[ p2_bt6    ] )
#define P2_SELECT ( backend_key[ p2_select ] )
#define P2_START  ( backend_key[ p2_start  ] )
#define MAX_CHARS 8

///////////////////////////////////////////////////////////////////////////////
// DECLARACOES INICIAIS -------------------------------------------------[**01]
///////////////////////////////////////////////////////////////////////////////

char versao[45]="HAMOOPI v.001A";

int sair=0; void sair_allegro() {sair=1;}
int timer=0; void tempo() {timer++;} float delay=0;
int Horas=0; int Minutos=0; int Segundos=0;
int timermenus=-1;
int Ctrl_FPS=60;
int WindowResNumber = 2;
int WindowResX = 640;
int WindowResY = 480;

int ativa_especial=0;
int bta=0;
int btb=0;
int btc=0;
int navAtlas=0; //utilizado para navegar no debug Atlas
int contatofisico=0;

//DECLARACAO DE FUNCOES
void check_keys_P1();
void check_keys_P2();
void Draw_CHBoxes_P1();
void Draw_CHBoxes_P2();
void Draw_CHBoxes_ED();
void Checar_Colisao();
void Aplicar_HIT();
void zeraListaDeInputs();
void MovSlots_P1();
void MovSlots_P2();
void LOAD_PLAYERS();
void New_HitBox(int Qtde_HitBoxes);
void New_Fireball(int Player);
void PLAYER_STATE(int Player, int State, int AnimIndex, int P1_QtdeFrames);
void AddTableAtlas(int PlayerInd, int State, int AnimIndex, int TotImg);
void ED_inicializar();
void ED_save_charini();
void ED_load_charini();
void ED_load_inputs(int ED_STATE);

//DECLARACOES DE STRUCTS E VARIAVEIS
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
}; struct HitSparkDEF HitSpark[99];

struct FireballsDEF {
HM_BITMAP Spr;
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
}; struct FireballsDEF Fireball[3];

struct PlayerDEF {
HM_BITMAP Spr;
char Name[50];
char Name_Display[50];
int Prioridade;
int TotalDeImagensUtilizadas;
HM_BITMAP SprAtlas[501];
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
int Hbox[2][18][4]; //Player, Hit/HurtBox, (x1,y1,x2,y2)
int Align[2][999][2]; //Player, State, (XAlign, YAlign)
}; struct PlayerDEF P[3];

//permite a config de teclas
int p1_up, p2_up;
int p1_down, p2_down;
int p1_left, p2_left;
int p1_right, p2_right;
int p1_bt1, p2_bt1;
int p1_bt2, p2_bt2;
int p1_bt3, p2_bt3;
int p1_bt4, p2_bt4;
int p1_bt5, p2_bt5;
int p1_bt6, p2_bt6;
int p1_select, p2_select;
int p1_start, p2_start;

int op_sound_volume=255;
int op_sfx_volume=255;
char IDIOMA[2];
int IntroMode=1; int IntroTimer=0;
float AnimIntroTimer=0; //animacao de intro timer
float AnimTransTimer=-1; //animacao de transicao timer
int CtrlAnimIntro[16];
int CtrlAnimTrans[30];
float EndRoundSlowDown=60;
int EndRoundT=500; //tempo de espera até reinciar os rounds
int DonationScreen=0;
int ApresentacaoMode=0;
int menu_op=1;
int OptionsMode=0;
int options_op=1;
int op_desenhar_sombras=1;
int op_ShowFrameData=0;
int GamePlayMode=0;
int TelaDeVersus=0;
int TelaDeVersusTimer=0;
int SelectCharMode=0;
int SelectCharP1ID=0;
int SelectCharP2ID=0;
char ChoiceP1[50];
char ChoiceP2[50];
char ChoiceBG[50];
int NumPersonagensEscolhidos=0;
char P1BIGDisplaystring[25]="";
char P2BIGDisplaystring[25]="";
char P1_Pallete_string[25]="";
char P2_Pallete_string[25]="";
int SelectCharTimerAnim=0;
int EditMode=0; int EditModeTime=0;
int Draw_Debug=0;
int Draw_Input=0;
int Draw_Box=0;
int FadeCtr=255;
int FadeIN=0;
int FadeOUT=1; //inicia em FadeOUT... na intro
float FadeVelocidade=10;

//modo historia e versus
int ModoHistoria=0;
int difficulty=3;
int ModoMapa=0;
int ModoMapaTimerAnim=0;
int Qtde_HitBox=0;
char Lista_de_Personagens_Instalados[9][50];
char Lista_de_Personagens_ArcadeMode[9][50];
char Lista_de_Cenarios_Instalados[9][50];
char Lista_de_Cenarios_ArcadeMode[9][50];
int Qtde_Personagens_Instalados;
int Qtde_Cenarios_Instalados;
int Estagio_Atual=1;
int Maximo_de_Estagios=8;
int MapCenterX;
int MapCenterY;
int MapPosX;
int MapPosY;

int desabilita_players=0;
unsigned int HitPauseKO=500;
int key_Mouse_L_pressed, key_Mouse_L_hold, key_Mouse_L_released, key_Mouse_L_status;
int key_Mouse_R_pressed, key_Mouse_R_hold, key_Mouse_R_released, key_Mouse_R_status;
int key_F1_pressed, key_F1_hold, key_F1_released, key_F1_status;
int key_F2_pressed, key_F2_hold, key_F2_released, key_F2_status;
int key_F3_pressed, key_F3_hold, key_F3_released, key_F3_status;
int key_F4_pressed, key_F4_hold, key_F4_released, key_F4_status;
int AlturaPiso=0; int MeioDaTela=0;
float VScreen_x=0; float VScreen_y=0;
float VScreen_x2=0; float VScreen_y2=0;
float VScreen_w=640; float VScreen_h=480;
int VScreen_FatorZoom=0;
int Zoom_eixo=0;
int ZoomMaximoAtingido=0;
int op_Zoom=0;
int VariacaoY=0; //usado no deslocamento do eixo y ex: pulos
int RoundTime=0; int RoundTotal=0; int RoundAtual=1;
int timer_rounds=0; //utilizado para controlar animacoes dos rounds
int timer_final_de_rounds=0;
int P1_FrameTime_00=0;
int P1_FrameTime_01=0; int P1_FrameTime_02=0; int P1_FrameTime_03=0; int P1_FrameTime_04=0; int P1_FrameTime_05=0;
int P1_FrameTime_06=0; int P1_FrameTime_07=0; int P1_FrameTime_08=0; int P1_FrameTime_09=0; int P1_FrameTime_10=0;
int P1_FrameTime_11=0; int P1_FrameTime_12=0; int P1_FrameTime_13=0; int P1_FrameTime_14=0; int P1_FrameTime_15=0;
int P1_FrameTime_16=0; int P1_FrameTime_17=0; int P1_FrameTime_18=0; int P1_FrameTime_19=0; int P1_FrameTime_20=0;
int P1_FrameTime_21=0; int P1_FrameTime_22=0; int P1_FrameTime_23=0; int P1_FrameTime_24=0; int P1_FrameTime_25=0;
int P1_FrameTime_26=0; int P1_FrameTime_27=0; int P1_FrameTime_28=0; int P1_FrameTime_29=0; int P1_FrameTime=0;
int ED_FrameTime_00=0;
int ED_FrameTime_01=0; int ED_FrameTime_02=0; int ED_FrameTime_03=0; int ED_FrameTime_04=0; int ED_FrameTime_05=0;
int ED_FrameTime_06=0; int ED_FrameTime_07=0; int ED_FrameTime_08=0; int ED_FrameTime_09=0; int ED_FrameTime_10=0;
int ED_FrameTime_11=0; int ED_FrameTime_12=0; int ED_FrameTime_13=0; int ED_FrameTime_14=0; int ED_FrameTime_15=0;
int ED_FrameTime_16=0; int ED_FrameTime_17=0; int ED_FrameTime_18=0; int ED_FrameTime_19=0; int ED_FrameTime_20=0;
int ED_FrameTime_21=0; int ED_FrameTime_22=0; int ED_FrameTime_23=0; int ED_FrameTime_24=0; int ED_FrameTime_25=0;
int ED_FrameTime_26=0; int ED_FrameTime_27=0; int ED_FrameTime_28=0; int ED_FrameTime_29=0; int ED_FrameTime=0;
int P2_FrameTime_00=0;
int P2_FrameTime_01=0; int P2_FrameTime_02=0; int P2_FrameTime_03=0; int P2_FrameTime_04=0; int P2_FrameTime_05=0;
int P2_FrameTime_06=0; int P2_FrameTime_07=0; int P2_FrameTime_08=0; int P2_FrameTime_09=0; int P2_FrameTime_10=0;
int P2_FrameTime_11=0; int P2_FrameTime_12=0; int P2_FrameTime_13=0; int P2_FrameTime_14=0; int P2_FrameTime_15=0;
int P2_FrameTime_16=0; int P2_FrameTime_17=0; int P2_FrameTime_18=0; int P2_FrameTime_19=0; int P2_FrameTime_20=0;
int P2_FrameTime_21=0; int P2_FrameTime_22=0; int P2_FrameTime_23=0; int P2_FrameTime_24=0; int P2_FrameTime_25=0;
int P2_FrameTime_26=0; int P2_FrameTime_27=0; int P2_FrameTime_28=0; int P2_FrameTime_29=0; int P2_FrameTime=0;
int P1_Fireball_FrameTime_00=0;
int P1_Fireball_FrameTime_01=0; int P1_Fireball_FrameTime_02=0;
int P1_Fireball_FrameTime_03=0; int P1_Fireball_FrameTime_04=0;
int P1_Fireball_FrameTime_05=0; int P1_Fireball_FrameTime_06=0;
int P1_Fireball_FrameTime_07=0; int P1_Fireball_FrameTime_08=0;
int P1_Fireball_FrameTime_09=0; int P1_Fireball_FrameTime_10=0; int P1_Fireball_FrameTime=0;
int P2_Fireball_FrameTime_00=0;
int P2_Fireball_FrameTime_01=0; int P2_Fireball_FrameTime_02=0;
int P2_Fireball_FrameTime_03=0; int P2_Fireball_FrameTime_04=0;
int P2_Fireball_FrameTime_05=0; int P2_Fireball_FrameTime_06=0;
int P2_Fireball_FrameTime_07=0; int P2_Fireball_FrameTime_08=0;
int P2_Fireball_FrameTime_09=0; int P2_Fireball_FrameTime_10=0; int P2_Fireball_FrameTime=0;
int P1_HurtBox01x1=0; int P1_HurtBox01y1=0; int P1_HurtBox01x2=0; int P1_HurtBox01y2=0;
int P1_HurtBox02x1=0; int P1_HurtBox02y1=0; int P1_HurtBox02x2=0; int P1_HurtBox02y2=0;
int P1_HurtBox03x1=0; int P1_HurtBox03y1=0; int P1_HurtBox03x2=0; int P1_HurtBox03y2=0;
int P1_HurtBox04x1=0; int P1_HurtBox04y1=0; int P1_HurtBox04x2=0; int P1_HurtBox04y2=0;
int P1_HurtBox05x1=0; int P1_HurtBox05y1=0; int P1_HurtBox05x2=0; int P1_HurtBox05y2=0;
int P1_HurtBox06x1=0; int P1_HurtBox06y1=0; int P1_HurtBox06x2=0; int P1_HurtBox06y2=0;
int P1_HurtBox07x1=0; int P1_HurtBox07y1=0; int P1_HurtBox07x2=0; int P1_HurtBox07y2=0;
int P1_HurtBox08x1=0; int P1_HurtBox08y1=0; int P1_HurtBox08x2=0; int P1_HurtBox08y2=0;
int P1_HurtBox09x1=0; int P1_HurtBox09y1=0; int P1_HurtBox09x2=0; int P1_HurtBox09y2=0;
int P1_HitBox01x1=0; int P1_HitBox01y1=0; int P1_HitBox01x2=0; int P1_HitBox01y2=0;
int P1_HitBox02x1=0; int P1_HitBox02y1=0; int P1_HitBox02x2=0; int P1_HitBox02y2=0;
int P1_HitBox03x1=0; int P1_HitBox03y1=0; int P1_HitBox03x2=0; int P1_HitBox03y2=0;
int P1_HitBox04x1=0; int P1_HitBox04y1=0; int P1_HitBox04x2=0; int P1_HitBox04y2=0;
int P1_HitBox05x1=0; int P1_HitBox05y1=0; int P1_HitBox05x2=0; int P1_HitBox05y2=0;
int P1_HitBox06x1=0; int P1_HitBox06y1=0; int P1_HitBox06x2=0; int P1_HitBox06y2=0;
int P1_HitBox07x1=0; int P1_HitBox07y1=0; int P1_HitBox07x2=0; int P1_HitBox07y2=0;
int P1_HitBox08x1=0; int P1_HitBox08y1=0; int P1_HitBox08x2=0; int P1_HitBox08y2=0;
int P1_HitBox09x1=0; int P1_HitBox09y1=0; int P1_HitBox09x2=0; int P1_HitBox09y2=0;
int P1_HurtBox_tot=0; int P1_HitBox_tot=0;
int P1_Fireball_HurtBox01x1=0; int P1_Fireball_HurtBox01y1=0; int P1_Fireball_HurtBox01x2=0; int P1_Fireball_HurtBox01y2=0;
int P2_Fireball_HurtBox01x1=0; int P2_Fireball_HurtBox01y1=0; int P2_Fireball_HurtBox01x2=0; int P2_Fireball_HurtBox01y2=0;
int P2_HurtBox01x1=0; int P2_HurtBox01y1=0; int P2_HurtBox01x2=0; int P2_HurtBox01y2=0;
int P2_HurtBox02x1=0; int P2_HurtBox02y1=0; int P2_HurtBox02x2=0; int P2_HurtBox02y2=0;
int P2_HurtBox03x1=0; int P2_HurtBox03y1=0; int P2_HurtBox03x2=0; int P2_HurtBox03y2=0;
int P2_HurtBox04x1=0; int P2_HurtBox04y1=0; int P2_HurtBox04x2=0; int P2_HurtBox04y2=0;
int P2_HurtBox05x1=0; int P2_HurtBox05y1=0; int P2_HurtBox05x2=0; int P2_HurtBox05y2=0;
int P2_HurtBox06x1=0; int P2_HurtBox06y1=0; int P2_HurtBox06x2=0; int P2_HurtBox06y2=0;
int P2_HurtBox07x1=0; int P2_HurtBox07y1=0; int P2_HurtBox07x2=0; int P2_HurtBox07y2=0;
int P2_HurtBox08x1=0; int P2_HurtBox08y1=0; int P2_HurtBox08x2=0; int P2_HurtBox08y2=0;
int P2_HurtBox09x1=0; int P2_HurtBox09y1=0; int P2_HurtBox09x2=0; int P2_HurtBox09y2=0;
int P2_HitBox01x1=0; int P2_HitBox01y1=0; int P2_HitBox01x2=0; int P2_HitBox01y2=0;
int P2_HitBox02x1=0; int P2_HitBox02y1=0; int P2_HitBox02x2=0; int P2_HitBox02y2=0;
int P2_HitBox03x1=0; int P2_HitBox03y1=0; int P2_HitBox03x2=0; int P2_HitBox03y2=0;
int P2_HitBox04x1=0; int P2_HitBox04y1=0; int P2_HitBox04x2=0; int P2_HitBox04y2=0;
int P2_HitBox05x1=0; int P2_HitBox05y1=0; int P2_HitBox05x2=0; int P2_HitBox05y2=0;
int P2_HitBox06x1=0; int P2_HitBox06y1=0; int P2_HitBox06x2=0; int P2_HitBox06y2=0;
int P2_HitBox07x1=0; int P2_HitBox07y1=0; int P2_HitBox07x2=0; int P2_HitBox07y2=0;
int P2_HitBox08x1=0; int P2_HitBox08y1=0; int P2_HitBox08x2=0; int P2_HitBox08y2=0;
int P2_HitBox09x1=0; int P2_HitBox09y1=0; int P2_HitBox09x2=0; int P2_HitBox09y2=0;
int P2_HurtBox_tot=0; int P2_HitBox_tot=0;
int P1_Fireball_HitBox01x1=0; int P1_Fireball_HitBox01y1=0; int P1_Fireball_HitBox01x2=0; int P1_Fireball_HitBox01y2=0;
int P2_Fireball_HitBox01x1=0; int P2_Fireball_HitBox01y1=0; int P2_Fireball_HitBox01x2=0; int P2_Fireball_HitBox01y2=0;
int P1_Hit_x=0; int P1_Hit_y=0;
int P2_Hit_x=0; int P2_Hit_y=0;
int colisaoxP1=0; int alturadohitp2=0;
int colisaoxP2=0; int alturadohitp1=0;
int colisaoxP1Fireball=0;
int colisaoxP2Fireball=0;
int temp1x, temp1y, temp2x, temp2y; //usado para corrigir os HBoxes
int HitPause1=15;
int HitPause2=15;
int HitPause3=15;
int P1_DMG1=0; int P1_DMG2=0; int P1_DMG3=0;
int P2_DMG1=0; int P2_DMG2=0; int P2_DMG3=0;
int MomentoDoP1=0;
int MomentoDoP2=0;
int ForcaDoGolpeP1=0;
int ForcaDoGolpeP2=0;
int AHitP1=1;
int AHitP2=1;
int P1HitPause=0;
int P2HitPause=0;
int P1HitOn=0;
int P2HitOn=0;
int ShakeDist=1;
int PlaySoundHitLvl1 = 0;
int PlaySoundHitLvl2 = 0;
int PlaySoundHitLvl3 = 0;
int P1_ContadorDeCor=0;
int P1_COR_ORIGINAL;
int P1_COR_ORIGINAL_R;
int P1_COR_ORIGINAL_G;
int P1_COR_ORIGINAL_B;
int P1_COR_ALTERNATIVA;
int P1_COR_ALTERNATIVA_R;
int P1_COR_ALTERNATIVA_G;
int P1_COR_ALTERNATIVA_B;
int P2_ContadorDeCor=0;
int P2_COR_ORIGINAL;
int P2_COR_ORIGINAL_R;
int P2_COR_ORIGINAL_G;
int P2_COR_ORIGINAL_B;
int P2_COR_ALTERNATIVA;
int P2_COR_ALTERNATIVA_R;
int P2_COR_ALTERNATIVA_G;
int P2_COR_ALTERNATIVA_B;

//Show FrameData
int FD_P1_Status; //1=STARTUP, 2=ACTIVE, 3=RECOVERY
int FD_P1_Startup=0;
int FD_P1_Active=0;
int FD_P1_Recovery=0;
int FD_P1_Active_IN=-1;
int FD_P1_Active_OUT=-1;
int FD_P1_HitBox01x1;
int FD_P2_Status; //1=STARTUP, 2=ACTIVE, 3=RECOVERY
int FD_P2_Startup=0;
int FD_P2_Active=0;
int FD_P2_Recovery=0;
int FD_P2_Active_IN=-1;
int FD_P2_Active_OUT=-1;
int FD_P2_HitBox01x1;

//Editor
char ED_Name[50]="";
int Edtimer=0;
int ED_CharID=1;
int ED_Tipo;
int ED_MODE=1;
int ED_Special_Version=1;
int ED_StartFrame=0;
int ED_TotalFrames=0;
int ED_State=100;
int ED_IndexAnim=0;
int ED_Lado=1;
int ED_XAlign=0;
int ED_YAlign=0;
int ED_x=0;
int ED_y=0;
int ED_Altura=0;
int ED_Largura=0;
int ED_Altura_100=0;
int ED_Largura_100=0;
int MovPossiveis[99];
int MovPossiveisIndex=0;
int ED_Pause=0;
int ED_DrawBlueMode=0;
int ED_DrawRedMode=0;
int ED_bt_Null=0;
int ED_CarregarDados=0;
int ED_Mx1=-1;
int ED_My1=-1;
int ED_Mx2=-1;
int ED_My2=-1;
int ED_HitBox01x1= -1; int ED_HitBox01y1 =-1; int ED_HitBox01x2 =-1; int ED_HitBox01y2 =-1;
int ED_HitBox02x1= -1; int ED_HitBox02y1 =-1; int ED_HitBox02x2 =-1; int ED_HitBox02y2 =-1;
int ED_HitBox03x1= -1; int ED_HitBox03y1 =-1; int ED_HitBox03x2 =-1; int ED_HitBox03y2 =-1;
int ED_HitBox04x1= -1; int ED_HitBox04y1 =-1; int ED_HitBox04x2 =-1; int ED_HitBox04y2 =-1;
int ED_HitBox05x1= -1; int ED_HitBox05y1 =-1; int ED_HitBox05x2 =-1; int ED_HitBox05y2 =-1;
int ED_HitBox06x1= -1; int ED_HitBox06y1 =-1; int ED_HitBox06x2 =-1; int ED_HitBox06y2 =-1;
int ED_HitBox07x1= -1; int ED_HitBox07y1 =-1; int ED_HitBox07x2 =-1; int ED_HitBox07y2 =-1;
int ED_HitBox08x1= -1; int ED_HitBox08y1 =-1; int ED_HitBox08x2 =-1; int ED_HitBox08y2 =-1;
int ED_HitBox09x1= -1; int ED_HitBox09y1 =-1; int ED_HitBox09x2 =-1; int ED_HitBox09y2 =-1;
int ED_HurtBox01x1=-1; int ED_HurtBox01y1=-1; int ED_HurtBox01x2=-1; int ED_HurtBox01y2=-1;
int ED_HurtBox02x1=-1; int ED_HurtBox02y1=-1; int ED_HurtBox02x2=-1; int ED_HurtBox02y2=-1;
int ED_HurtBox03x1=-1; int ED_HurtBox03y1=-1; int ED_HurtBox03x2=-1; int ED_HurtBox03y2=-1;
int ED_HurtBox04x1=-1; int ED_HurtBox04y1=-1; int ED_HurtBox04x2=-1; int ED_HurtBox04y2=-1;
int ED_HurtBox05x1=-1; int ED_HurtBox05y1=-1; int ED_HurtBox05x2=-1; int ED_HurtBox05y2=-1;
int ED_HurtBox06x1=-1; int ED_HurtBox06y1=-1; int ED_HurtBox06x2=-1; int ED_HurtBox06y2=-1;
int ED_HurtBox07x1=-1; int ED_HurtBox07y1=-1; int ED_HurtBox07x2=-1; int ED_HurtBox07y2=-1;
int ED_HurtBox08x1=-1; int ED_HurtBox08y1=-1; int ED_HurtBox08x2=-1; int ED_HurtBox08y2=-1;
int ED_HurtBox09x1=-1; int ED_HurtBox09y1=-1; int ED_HurtBox09x2=-1; int ED_HurtBox09y2=-1;
int ED_HitBox_tot=0; int ED_HurtBox_tot=0;
int ED_io=1;
int ED_alertsave=0; int ED_alertsave2=0;
int ED_ShowMsgSaving=0;
int ED_MovimentaPivot=0;
char ED_Name_Display[50]="char1";

///////////////////////////////////////////////////////////////////////////////
// INICIALIZACAO ALLEGRO ------------------------------------------------[**02]
///////////////////////////////////////////////////////////////////////////////

int main()
{
backend_set_uformat(HM_U_UTF8); //permite usar acentuação no jogo (diacríticos)
backend_init(); backend_install_timer(); backend_install_keyboard(); backend_install_mouse(); backend_set_color_depth(32);
//backend_set_gfx_mode() é declarado logo abaixo, apos carregar dados do SETUP.INI
backend_install_sound(HM_DIGI_AUTODETECT, HM_MIDI_AUTODETECT);
int ModoFullscreen=0;
HM_FONT font_debug = backend_load_font("data/system/font_debug.pcx");
HM_FONT font_10    = backend_load_font("data/system/font_10.pcx"   );
HM_FONT font_19    = backend_load_font("data/system/font_19.pcx"   );
HM_FONT font_20    = backend_load_font("data/system/font_20.pcx"   );
HM_FONT font_30    = backend_load_font("data/system/font_30.pcx"   );
backend_install_int_ex(tempo, BPS_TO_TIMER(60)); //60fps
backend_set_window_title("HAMOOPI is Loading... Please wait :) ");
backend_set_close_button_callback( sair_allegro );

//Valores de Referencia:
//Genesis [320x224]
//Snes [256x224]
//CapcomCPS1 [384x224]
//NeoGeo [320x224]
HM_BITMAP bg_test = backend_create_bitmap(1280,960); //tamanho max do cenario
HM_BITMAP bg_hamoopi[9];

//carrega os dados do setup.ini
backend_set_config_file("SETUP.ini");

//opcao de desenhar sombras
op_desenhar_sombras = backend_get_config_int ( "CONFIG" , "draw_shadows",  1 ) ;
//opcao que ativa o zoom
op_Zoom = backend_get_config_int ( "CONFIG" , "zoom",  1 ) ;
//opcao que mostra os inputs ingame
Draw_Input = backend_get_config_int ( "CONFIG" , "show_inputs",  0 ) ;
//sound e soundfx volumes
op_sound_volume = backend_get_config_int ( "CONFIG" , "sound_volume",  255 ) ;
op_sfx_volume = backend_get_config_int ( "CONFIG" , "sfx_volume",  255 ) ;
//resolucao de tela no modo windowed
WindowResX = backend_get_config_int ( "CONFIG" , "window_res_x",  640 ) ;
WindowResY = backend_get_config_int ( "CONFIG" , "window_res_y",  480 ) ;
//define o ResWindowNumber
if(WindowResX== 320 && WindowResY==240) WindowResNumber=1;
if(WindowResX== 640 && WindowResY==480) WindowResNumber=2;
if(WindowResX== 720 && WindowResY==480) WindowResNumber=3; //SD
if(WindowResX== 800 && WindowResY==600) WindowResNumber=4;
if(WindowResX== 960 && WindowResY==640) WindowResNumber=5;
if(WindowResX== 960 && WindowResY==720) WindowResNumber=6;
if(WindowResX==1024 && WindowResY==600) WindowResNumber=7;
if(WindowResX==1280 && WindowResY==720) WindowResNumber=8; //HD
//define se resolucao é fullscreen
ModoFullscreen = backend_get_config_int ( "CONFIG" , "FullScreen",  0 ) ;
//ajusta a tela com as novas configuracoes
if(ModoFullscreen==1) { backend_set_gfx_mode(HM_GFX_AUTODETECT_FULLSCREEN, WindowResX, WindowResY, 0, 0); }
if(ModoFullscreen==0) { backend_set_gfx_mode(HM_GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0); }
//opcao de framedata
op_ShowFrameData = backend_get_config_int ( "CONFIG" , "frame_data",  0 ) ;

//carrega a lista de Cenarios instalados
for(int ind=1;ind<=MAX_CHARS;ind++){
char strtemp[9]="";
sprintf(strtemp, "bg%i", ind);
strcpy(Lista_de_Cenarios_Instalados[ind], (char *)backend_get_config_string("BACKGROUNDS", strtemp, ""));
}
//abastece Atlas de cenario
char bg_choice[25]="";
for(int ind=1;ind<=8;ind++)
{
sprintf(bg_choice, "data/backgrounds/%s/000_00.pcx", Lista_de_Cenarios_Instalados[ind]);
bg_hamoopi[ind]= backend_load_bitmap(bg_choice, NULL);
}

HM_BITMAP bufferx = backend_create_bitmap(2560,1920); //layer do cenario e personagens escalonados
HM_BITMAP LayerHUD = backend_create_bitmap(WindowResX,WindowResY); //layer das barras de energia
HM_BITMAP LayerHUDa = backend_create_bitmap(640,480); //layer das barras de energia
HM_BITMAP LayerHUDb = backend_create_bitmap(WindowResX,WindowResY); //layer das barras de energia

for(int ind=0;ind<=500;ind++){
P[1].SprAtlas[ind]= backend_create_bitmap(480,480); //reserva memoria para sprites dos players
P[2].SprAtlas[ind]= backend_create_bitmap(480,480); //reserva memoria para sprites dos players
}

P[1].Spr              = backend_create_bitmap(480,480);
P[2].Spr              = backend_create_bitmap(480,480);
Fireball[1].Spr       = backend_create_bitmap(480,480);
Fireball[2].Spr       = backend_create_bitmap(480,480);
HM_BITMAP P1_Sombra     = backend_create_bitmap(480,128);
HM_BITMAP P2_Sombra     = backend_create_bitmap(480,128);
HM_BITMAP P1_Sombra_Aux = backend_create_bitmap(480,128);
HM_BITMAP P2_Sombra_Aux = backend_create_bitmap(480,128);
HM_BITMAP P1_energy_flip = backend_create_bitmap(250,40);
HM_BITMAP P1_energy_red_flip = backend_create_bitmap(250,40);
HM_BITMAP ED_Spr        = backend_create_bitmap(480,480); //Editor
HM_BITMAP ED_Mini       = backend_create_bitmap(32,32);
HM_BITMAP P1_Spr_Aux    = backend_create_bitmap(480,480); //sprite auxiliar utilizado na funcao de animacao
HM_BITMAP P2_Spr_Aux    = backend_create_bitmap(480,480); //sprite auxiliar utilizado na funcao de animacao
HM_BITMAP ED_Spr_Aux    = backend_create_bitmap(480,480); //sprite auxiliar utilizado na funcao de animacao
HM_BITMAP HitSparkspr   = backend_create_bitmap(260,260);
HM_BITMAP HitSpark_Aux  = backend_create_bitmap(130,130);
HM_BITMAP P1_Pallete    = backend_create_bitmap(32,10);
HM_BITMAP P2_Pallete    = backend_create_bitmap(32,10);
backend_clear_to_color(HitSparkspr , backend_makecol(255, 0, 255));
backend_clear_to_color(HitSpark_Aux, backend_makecol(255, 0, 255));
backend_clear_to_color(P1_Pallete  , backend_makecol(255, 0, 255));
backend_clear_to_color(P2_Pallete  , backend_makecol(255, 0, 255));

int HamoopiError=0;
HM_BITMAP GAME_logo            = backend_load_bitmap("data/system/GAME_logo.pcx", NULL);            if (!GAME_logo)            { HamoopiError=1; }
HM_BITMAP flag_BR              = backend_load_bitmap("data/system/flag_BR.pcx", NULL);              if (!flag_BR)              { HamoopiError=1; }
HM_BITMAP sel_mark_p1          = backend_load_bitmap("data/system/sel_mark_p1.pcx", NULL);          if (!sel_mark_p1)          { HamoopiError=1; }
HM_BITMAP sel_mark_p2          = backend_load_bitmap("data/system/sel_mark_p2.pcx", NULL);          if (!sel_mark_p2)          { HamoopiError=1; }
HM_BITMAP flag_US              = backend_load_bitmap("data/system/flag_US.pcx", NULL);              if (!flag_US)              { HamoopiError=1; }
HM_BITMAP SELECT_CHARS         = backend_load_bitmap("data/system/SELECT_CHARS.pcx", NULL);         if (!SELECT_CHARS)         { HamoopiError=1; }
HM_BITMAP VS_SCREEN            = backend_load_bitmap("data/system/VS_SCREEN.pcx", NULL);            if (!VS_SCREEN)            { HamoopiError=1; }
HM_BITMAP vs_icon              = backend_load_bitmap("data/system/vs_icon.pcx", NULL);              if (!vs_icon)              { HamoopiError=1; }
HM_BITMAP SELECT_BG            = backend_load_bitmap("data/system/SELECT_BG.pcx", NULL);            if (!SELECT_BG)            { HamoopiError=1; }
HM_BITMAP donation             = backend_load_bitmap("data/system/donation.pcx", NULL);             if (!donation)             { HamoopiError=1; }
HM_BITMAP spr_p1_cursor        = backend_load_bitmap("data/system/spr_p1_cursor.pcx", NULL);        if (!spr_p1_cursor)        { HamoopiError=1; }
HM_BITMAP spr_p2_cursor        = backend_load_bitmap("data/system/spr_p2_cursor.pcx", NULL);        if (!spr_p2_cursor)        { HamoopiError=1; }
HM_BITMAP spr_cursor_historia  = backend_load_bitmap("data/system/spr_cursor_historia.pcx", NULL);  if (!spr_cursor_historia)  { HamoopiError=1; }
HM_BITMAP spr_cursor_vazio     = backend_load_bitmap("data/system/spr_cursor_vazio.pcx", NULL);     if (!spr_cursor_vazio)     { HamoopiError=1; }
HM_BITMAP spr_ponteiro         = backend_load_bitmap("data/system/spr_ponteiro.pcx", NULL);         if (!spr_ponteiro)         { HamoopiError=1; }
HM_BITMAP spr_menu_icon        = backend_load_bitmap("data/system/spr_menu_icon.pcx", NULL);        if (!spr_menu_icon)        { HamoopiError=1; }
HM_BITMAP GAME_intro           = backend_load_bitmap("data/system/GAME_intro.pcx", NULL);           if (!GAME_intro)           { HamoopiError=1; }
HM_BITMAP GAME_options         = backend_load_bitmap("data/system/GAME_options.pcx", NULL);         if (!GAME_options)         { HamoopiError=1; }
HM_BITMAP char_generic         = backend_load_bitmap("data/system/char_generic.pcx", NULL);         if (!char_generic)         { HamoopiError=1; }
HM_BITMAP char_generic2x       = backend_load_bitmap("data/system/char_generic2x.pcx", NULL);       if (!char_generic2x)       { HamoopiError=1; }
HM_BITMAP spr_mold_results     = backend_load_bitmap("data/system/spr_mold_results.pcx", NULL);     if (!spr_mold_results)     { HamoopiError=1; }
HM_BITMAP spr_result_perfect   = backend_load_bitmap("data/system/spr_result_perfect.pcx", NULL);   if (!spr_result_perfect)   { HamoopiError=1; }
HM_BITMAP spr_result_win       = backend_load_bitmap("data/system/spr_result_win.pcx", NULL);       if (!spr_result_win)       { HamoopiError=1; }
HM_BITMAP spr_splash_round1    = backend_load_bitmap("data/system/spr_splash_round1.pcx", NULL);    if (!spr_splash_round1)    { HamoopiError=1; }
HM_BITMAP spr_splash_round2    = backend_load_bitmap("data/system/spr_splash_round2.pcx", NULL);    if (!spr_splash_round2)    { HamoopiError=1; }
HM_BITMAP spr_splash_round3    = backend_load_bitmap("data/system/spr_splash_round3.pcx", NULL);    if (!spr_splash_round3)    { HamoopiError=1; }
HM_BITMAP spr_splash_round4    = backend_load_bitmap("data/system/spr_splash_round4.pcx", NULL);    if (!spr_splash_round4)    { HamoopiError=1; }
HM_BITMAP spr_splash_round5    = backend_load_bitmap("data/system/spr_splash_round5.pcx", NULL);    if (!spr_splash_round5)    { HamoopiError=1; }
HM_BITMAP spr_splash_fight     = backend_load_bitmap("data/system/spr_splash_fight.pcx", NULL);     if (!spr_splash_fight)     { HamoopiError=1; }
HM_BITMAP spr_splash_youwin    = backend_load_bitmap("data/system/spr_splash_youwin.pcx", NULL);    if (!spr_splash_youwin)    { HamoopiError=1; }
HM_BITMAP spr_splash_p1win     = backend_load_bitmap("data/system/spr_splash_p1win.pcx", NULL);     if (!spr_splash_p1win)     { HamoopiError=1; }
HM_BITMAP spr_splash_p2win     = backend_load_bitmap("data/system/spr_splash_p2win.pcx", NULL);     if (!spr_splash_p2win)     { HamoopiError=1; }
HM_BITMAP spr_splash_youlose   = backend_load_bitmap("data/system/spr_splash_youlose.pcx", NULL);   if (!spr_splash_youlose)   { HamoopiError=1; }
HM_BITMAP spr_splash_ko        = backend_load_bitmap("data/system/spr_splash_ko.pcx", NULL);        if (!spr_splash_ko)        { HamoopiError=1; }
HM_BITMAP spr_splash_perfect   = backend_load_bitmap("data/system/spr_splash_perfect.pcx", NULL);   if (!spr_splash_perfect)   { HamoopiError=1; }
HM_BITMAP spr_splash_draw      = backend_load_bitmap("data/system/spr_splash_draw.pcx", NULL);      if (!spr_splash_draw)      { HamoopiError=1; }
HM_BITMAP spr_splash_time_over = backend_load_bitmap("data/system/spr_splash_time_over.pcx", NULL); if (!spr_splash_time_over) { HamoopiError=1; }
HM_BITMAP bt_joystick          = backend_load_bitmap("data/system/bt_joystick.pcx", NULL);          if (!bt_joystick)          { HamoopiError=1; }
HM_BITMAP ed_mode1_on          = backend_load_bitmap("data/system/ed_mode1_on.pcx", NULL);          if (!ed_mode1_on)          { HamoopiError=1; }
HM_BITMAP ed_mode2_on          = backend_load_bitmap("data/system/ed_mode2_on.pcx", NULL);          if (!ed_mode2_on)          { HamoopiError=1; }
HM_BITMAP ed_mode1_off         = backend_load_bitmap("data/system/ed_mode1_off.pcx", NULL);         if (!ed_mode1_off)         { HamoopiError=1; }
HM_BITMAP ed_mode2_off         = backend_load_bitmap("data/system/ed_mode2_off.pcx", NULL);         if (!ed_mode2_off)         { HamoopiError=1; }
HM_BITMAP bt_reset_input       = backend_load_bitmap("data/system/bt_reset_input.pcx", NULL);       if (!bt_reset_input)       { HamoopiError=1; }
HM_BITMAP bt_up_1              = backend_load_bitmap("data/system/bt_up_1.pcx", NULL);              if (!bt_up_1)              { HamoopiError=1; }
HM_BITMAP bt_up_2              = backend_load_bitmap("data/system/bt_up_2.pcx", NULL);              if (!bt_up_2)              { HamoopiError=1; }
HM_BITMAP bt_up_3              = backend_load_bitmap("data/system/bt_up_3.pcx", NULL);              if (!bt_up_3)              { HamoopiError=1; }
HM_BITMAP bt_down_1            = backend_load_bitmap("data/system/bt_down_1.pcx", NULL);            if (!bt_down_1)            { HamoopiError=1; }
HM_BITMAP bt_down_2            = backend_load_bitmap("data/system/bt_down_2.pcx", NULL);            if (!bt_down_2)            { HamoopiError=1; }
HM_BITMAP bt_down_3            = backend_load_bitmap("data/system/bt_down_3.pcx", NULL);            if (!bt_down_3)            { HamoopiError=1; }
HM_BITMAP bt_left_1            = backend_load_bitmap("data/system/bt_left_1.pcx", NULL);            if (!bt_left_1)            { HamoopiError=1; }
HM_BITMAP bt_left_2            = backend_load_bitmap("data/system/bt_left_2.pcx", NULL);            if (!bt_left_2)            { HamoopiError=1; }
HM_BITMAP bt_left_3            = backend_load_bitmap("data/system/bt_left_3.pcx", NULL);            if (!bt_left_3)            { HamoopiError=1; }
HM_BITMAP bt_right_1           = backend_load_bitmap("data/system/bt_right_1.pcx", NULL);           if (!bt_right_1)           { HamoopiError=1; }
HM_BITMAP bt_right_2           = backend_load_bitmap("data/system/bt_right_2.pcx", NULL);           if (!bt_right_2)           { HamoopiError=1; }
HM_BITMAP bt_right_3           = backend_load_bitmap("data/system/bt_right_3.pcx", NULL);           if (!bt_right_3)           { HamoopiError=1; }
HM_BITMAP bt_1                 = backend_load_bitmap("data/system/bt_1.pcx", NULL);                 if (!bt_1)                 { HamoopiError=1; }
HM_BITMAP bt_2                 = backend_load_bitmap("data/system/bt_2.pcx", NULL);                 if (!bt_2)                 { HamoopiError=1; }
HM_BITMAP bt_3                 = backend_load_bitmap("data/system/bt_3.pcx", NULL);                 if (!bt_3)                 { HamoopiError=1; }
HM_BITMAP bt_ss_1              = backend_load_bitmap("data/system/bt_ss_1.pcx", NULL);              if (!bt_ss_1)              { HamoopiError=1; }
HM_BITMAP bt_ss_2              = backend_load_bitmap("data/system/bt_ss_2.pcx", NULL);              if (!bt_ss_2)              { HamoopiError=1; }
HM_BITMAP bt_ss_3              = backend_load_bitmap("data/system/bt_ss_3.pcx", NULL);              if (!bt_ss_3)              { HamoopiError=1; }
HM_BITMAP spr_input_0          = backend_load_bitmap("data/system/spr_input_0.pcx", NULL);          if (!spr_input_0)          { HamoopiError=1; }
HM_BITMAP spr_input_1          = backend_load_bitmap("data/system/spr_input_1.pcx", NULL);          if (!spr_input_1)          { HamoopiError=1; }
HM_BITMAP spr_input_2          = backend_load_bitmap("data/system/spr_input_2.pcx", NULL);          if (!spr_input_2)          { HamoopiError=1; }
HM_BITMAP spr_input_3          = backend_load_bitmap("data/system/spr_input_3.pcx", NULL);          if (!spr_input_3)          { HamoopiError=1; }
HM_BITMAP spr_input_4          = backend_load_bitmap("data/system/spr_input_4.pcx", NULL);          if (!spr_input_4)          { HamoopiError=1; }
HM_BITMAP spr_input_5          = backend_load_bitmap("data/system/spr_input_5.pcx", NULL);          if (!spr_input_5)          { HamoopiError=1; }
HM_BITMAP spr_input_6          = backend_load_bitmap("data/system/spr_input_6.pcx", NULL);          if (!spr_input_6)          { HamoopiError=1; }
HM_BITMAP spr_input_7          = backend_load_bitmap("data/system/spr_input_7.pcx", NULL);          if (!spr_input_7)          { HamoopiError=1; }
HM_BITMAP spr_input_8          = backend_load_bitmap("data/system/spr_input_8.pcx", NULL);          if (!spr_input_8)          { HamoopiError=1; }
HM_BITMAP spr_input_9          = backend_load_bitmap("data/system/spr_input_9.pcx", NULL);          if (!spr_input_9)          { HamoopiError=1; }
HM_BITMAP spr_input_10         = backend_load_bitmap("data/system/spr_input_10.pcx", NULL);         if (!spr_input_10)         { HamoopiError=1; }
HM_BITMAP spr_input_11         = backend_load_bitmap("data/system/spr_input_11.pcx", NULL);         if (!spr_input_11)         { HamoopiError=1; }
HM_BITMAP spr_input_12         = backend_load_bitmap("data/system/spr_input_12.pcx", NULL);         if (!spr_input_12)         { HamoopiError=1; }
HM_BITMAP spr_input_13         = backend_load_bitmap("data/system/spr_input_13.pcx", NULL);         if (!spr_input_13)         { HamoopiError=1; }
HM_BITMAP spr_input_14         = backend_load_bitmap("data/system/spr_input_14.pcx", NULL);         if (!spr_input_14)         { HamoopiError=1; }
HM_BITMAP spr_input_15         = backend_load_bitmap("data/system/spr_input_15.pcx", NULL);         if (!spr_input_15)         { HamoopiError=1; }
HM_BITMAP spr_input_16         = backend_load_bitmap("data/system/spr_input_16.pcx", NULL);         if (!spr_input_16)         { HamoopiError=1; }
HM_BITMAP spr_input_17         = backend_load_bitmap("data/system/spr_input_17.pcx", NULL);         if (!spr_input_17)         { HamoopiError=1; }
HM_BITMAP spr_bg_bar           = backend_load_bitmap("data/system/spr_bg_bar.pcx", NULL);           if (!spr_bg_bar)           { HamoopiError=1; }
HM_BITMAP spr_energy_bar       = backend_load_bitmap("data/system/spr_energy_bar.pcx", NULL);       if (!spr_energy_bar)       { HamoopiError=1; }
HM_BITMAP spr_energy_bar_full  = backend_load_bitmap("data/system/spr_energy_bar_full.pcx", NULL);  if (!spr_energy_bar_full)  { HamoopiError=1; }
HM_BITMAP spr_energy_red_bar   = backend_load_bitmap("data/system/spr_energy_red_bar.pcx", NULL);   if (!spr_energy_red_bar)   { HamoopiError=1; }
HM_BITMAP spr_energy_red_bar_full = backend_load_bitmap("data/system/spr_energy_red_bar_full.pcx", NULL); if (!spr_energy_red_bar_full) { HamoopiError=1; }
HM_BITMAP spr_bg_bar_sp        = backend_load_bitmap("data/system/spr_bg_bar_sp.pcx", NULL);        if (!spr_bg_bar_sp)        { HamoopiError=1; }
HM_BITMAP spr_bg_energy_bar_sp = backend_load_bitmap("data/system/spr_bg_energy_bar_sp.pcx", NULL); if (!spr_bg_energy_bar_sp) { HamoopiError=1; }
HM_BITMAP spr_num[10];
spr_num[0]=backend_load_bitmap("data/system/spr_num_0.pcx",NULL); if (!spr_num[0]) { HamoopiError=1; }
spr_num[1]=backend_load_bitmap("data/system/spr_num_1.pcx",NULL); if (!spr_num[1]) { HamoopiError=1; }
spr_num[2]=backend_load_bitmap("data/system/spr_num_2.pcx",NULL); if (!spr_num[2]) { HamoopiError=1; }
spr_num[3]=backend_load_bitmap("data/system/spr_num_3.pcx",NULL); if (!spr_num[3]) { HamoopiError=1; }
spr_num[4]=backend_load_bitmap("data/system/spr_num_4.pcx",NULL); if (!spr_num[4]) { HamoopiError=1; }
spr_num[5]=backend_load_bitmap("data/system/spr_num_5.pcx",NULL); if (!spr_num[5]) { HamoopiError=1; }
spr_num[6]=backend_load_bitmap("data/system/spr_num_6.pcx",NULL); if (!spr_num[6]) { HamoopiError=1; }
spr_num[7]=backend_load_bitmap("data/system/spr_num_7.pcx",NULL); if (!spr_num[7]) { HamoopiError=1; }
spr_num[8]=backend_load_bitmap("data/system/spr_num_8.pcx",NULL); if (!spr_num[8]) { HamoopiError=1; }
spr_num[9]=backend_load_bitmap("data/system/spr_num_9.pcx",NULL); if (!spr_num[9]) { HamoopiError=1; }
HM_BITMAP edit_bt_blue         = backend_load_bitmap("data/system/edit_bt_blue.pcx", NULL);         if (!edit_bt_blue)         { HamoopiError=1; }
HM_BITMAP edit_bt_red          = backend_load_bitmap("data/system/edit_bt_red.pcx", NULL);          if (!edit_bt_red)          { HamoopiError=1; }
HM_BITMAP edit_bt_null         = backend_load_bitmap("data/system/edit_bt_null.pcx", NULL);         if (!edit_bt_null)         { HamoopiError=1; }
HM_BITMAP edit_bt_null0        = backend_load_bitmap("data/system/edit_bt_null0.pcx", NULL);        if (!edit_bt_null0)        { HamoopiError=1; }
HM_BITMAP edit_prevst          = backend_load_bitmap("data/system/edit_prevst.pcx", NULL);          if (!edit_prevst)          { HamoopiError=1; }
HM_BITMAP edit_nextst          = backend_load_bitmap("data/system/edit_nextst.pcx", NULL);          if (!edit_nextst)          { HamoopiError=1; }
HM_BITMAP edit_prevchar        = backend_load_bitmap("data/system/edit_prevchar.pcx", NULL);        if (!edit_prevchar)        { HamoopiError=1; }
HM_BITMAP edit_nextchar        = backend_load_bitmap("data/system/edit_nextchar.pcx", NULL);        if (!edit_nextchar)        { HamoopiError=1; }
HM_BITMAP edit_firstchar       = backend_load_bitmap("data/system/edit_firstchar.pcx", NULL);       if (!edit_firstchar)       { HamoopiError=1; }
HM_BITMAP edit_lastchar        = backend_load_bitmap("data/system/edit_lastchar.pcx", NULL);        if (!edit_lastchar)        { HamoopiError=1; }
HM_BITMAP spr_nao_implementado = backend_load_bitmap("data/system/spr_nao_implementado.pcx", NULL); if (!spr_nao_implementado) { HamoopiError=1; }
HM_BITMAP edit_playback        = backend_load_bitmap("data/system/edit_playback.pcx", NULL);        if (!edit_playback)        { HamoopiError=1; }
HM_BITMAP edit_pause           = backend_load_bitmap("data/system/edit_pause.pcx", NULL);           if (!edit_pause)           { HamoopiError=1; }
HM_BITMAP edit_bt_FrameTime    = backend_load_bitmap("data/system/edit_bt_FrameTime.pcx", NULL);    if (!edit_bt_FrameTime)    { HamoopiError=1; }
HM_BITMAP edit_bt_plus         = backend_load_bitmap("data/system/edit_bt_plus.pcx", NULL);         if (!edit_bt_plus)         { HamoopiError=1; }
HM_BITMAP edit_bt_minus        = backend_load_bitmap("data/system/edit_bt_minus.pcx", NULL);        if (!edit_bt_minus)        { HamoopiError=1; }
HM_BITMAP mouse                = backend_load_bitmap("data/system/mouse.pcx", NULL);                if (!mouse)                { HamoopiError=1; }
HM_BITMAP mouse2               = backend_load_bitmap("data/system/mouse2.pcx", NULL);               if (!mouse2)               { HamoopiError=1; }
HM_BITMAP save_file            = backend_load_bitmap("data/system/save_file.pcx", NULL);            if (!save_file)            { HamoopiError=1; }
HM_BITMAP bt_pivot             = backend_load_bitmap("data/system/bt_pivot.pcx", NULL);             if (!bt_pivot)             { HamoopiError=1; }
HM_BITMAP spr000_00            = backend_load_bitmap("data/system/000_00.pcx", NULL);               if (!spr000_00)            { HamoopiError=1; }
HM_BITMAP spr000_01            = backend_load_bitmap("data/system/000_01.pcx", NULL);               if (!spr000_01)            { HamoopiError=1; }
HM_BITMAP spr991_00            = backend_load_bitmap("data/system/991_00.pcx", NULL);               if (!spr991_00)            { HamoopiError=1; }
HM_BITMAP spr991_01            = backend_load_bitmap("data/system/991_01.pcx", NULL);               if (!spr991_01)            { HamoopiError=1; }
HM_BITMAP spr991_02            = backend_load_bitmap("data/system/991_02.pcx", NULL);               if (!spr991_02)            { HamoopiError=1; }
HM_BITMAP spr991_03            = backend_load_bitmap("data/system/991_03.pcx", NULL);               if (!spr991_03)            { HamoopiError=1; }
HM_BITMAP spr991_04            = backend_load_bitmap("data/system/991_04.pcx", NULL);               if (!spr991_04)            { HamoopiError=1; }
HM_BITMAP spr991_05            = backend_load_bitmap("data/system/991_05.pcx", NULL);               if (!spr991_05)            { HamoopiError=1; }
HM_BITMAP spr992_00            = backend_load_bitmap("data/system/992_00.pcx", NULL);               if (!spr992_00)            { HamoopiError=1; }
HM_BITMAP spr992_01            = backend_load_bitmap("data/system/992_01.pcx", NULL);               if (!spr992_01)            { HamoopiError=1; }
HM_BITMAP spr992_02            = backend_load_bitmap("data/system/992_02.pcx", NULL);               if (!spr992_02)            { HamoopiError=1; }
HM_BITMAP spr992_03            = backend_load_bitmap("data/system/992_03.pcx", NULL);               if (!spr992_03)            { HamoopiError=1; }
HM_BITMAP spr992_04            = backend_load_bitmap("data/system/992_04.pcx", NULL);               if (!spr992_04)            { HamoopiError=1; }
HM_BITMAP spr992_05            = backend_load_bitmap("data/system/992_05.pcx", NULL);               if (!spr992_05)            { HamoopiError=1; }
HM_BITMAP spr993_00            = backend_load_bitmap("data/system/993_00.pcx", NULL);               if (!spr993_00)            { HamoopiError=1; }
HM_BITMAP spr993_01            = backend_load_bitmap("data/system/993_01.pcx", NULL);               if (!spr993_01)            { HamoopiError=1; }
HM_BITMAP spr993_02            = backend_load_bitmap("data/system/993_02.pcx", NULL);               if (!spr993_02)            { HamoopiError=1; }
HM_BITMAP spr993_03            = backend_load_bitmap("data/system/993_03.pcx", NULL);               if (!spr993_03)            { HamoopiError=1; }
HM_BITMAP spr993_04            = backend_load_bitmap("data/system/993_04.pcx", NULL);               if (!spr993_04)            { HamoopiError=1; }
HM_BITMAP spr993_05            = backend_load_bitmap("data/system/993_05.pcx", NULL);               if (!spr993_05)            { HamoopiError=1; }
HM_BITMAP spr994_00            = backend_load_bitmap("data/system/994_00.pcx", NULL);               if (!spr994_00)            { HamoopiError=1; }
HM_BITMAP spr994_01            = backend_load_bitmap("data/system/994_01.pcx", NULL);               if (!spr994_01)            { HamoopiError=1; }
HM_BITMAP spr994_02            = backend_load_bitmap("data/system/994_02.pcx", NULL);               if (!spr994_02)            { HamoopiError=1; }
HM_BITMAP spr994_03            = backend_load_bitmap("data/system/994_03.pcx", NULL);               if (!spr994_03)            { HamoopiError=1; }
HM_BITMAP spr994_04            = backend_load_bitmap("data/system/994_04.pcx", NULL);               if (!spr994_04)            { HamoopiError=1; }
HM_BITMAP spr994_05            = backend_load_bitmap("data/system/994_05.pcx", NULL);               if (!spr994_05)            { HamoopiError=1; }
//defesa - nao implementada ainda :)
//HM_BITMAP spr995_00            = backend_load_bitmap("data/system/995_00.pcx", NULL);               if (!spr995_00)            { HamoopiError=1; }
//HM_BITMAP spr995_01            = backend_load_bitmap("data/system/995_01.pcx", NULL);               if (!spr995_01)            { HamoopiError=1; }
//HM_BITMAP spr995_02            = backend_load_bitmap("data/system/995_02.pcx", NULL);               if (!spr995_02)            { HamoopiError=1; }
//HM_BITMAP spr995_03            = backend_load_bitmap("data/system/995_03.pcx", NULL);               if (!spr995_03)            { HamoopiError=1; }
//HM_BITMAP spr995_04            = backend_load_bitmap("data/system/995_04.pcx", NULL);               if (!spr995_04)            { HamoopiError=1; }
//HM_BITMAP spr995_05            = backend_load_bitmap("data/system/995_05.pcx", NULL);               if (!spr995_05)            { HamoopiError=1; }
HM_BITMAP AnimTrans[30];
AnimTrans[0]  = backend_load_bitmap("data/system/AnimTrans00.pcx",NULL); if (!AnimTrans[0])  { CtrlAnimTrans[0] =0; } else { CtrlAnimTrans[0] =1; }
AnimTrans[1]  = backend_load_bitmap("data/system/AnimTrans01.pcx",NULL); if (!AnimTrans[1])  { CtrlAnimTrans[1] =0; } else { CtrlAnimTrans[1] =1; }
AnimTrans[2]  = backend_load_bitmap("data/system/AnimTrans02.pcx",NULL); if (!AnimTrans[2])  { CtrlAnimTrans[2] =0; } else { CtrlAnimTrans[2] =1; }
AnimTrans[3]  = backend_load_bitmap("data/system/AnimTrans03.pcx",NULL); if (!AnimTrans[3])  { CtrlAnimTrans[3] =0; } else { CtrlAnimTrans[3] =1; }
AnimTrans[4]  = backend_load_bitmap("data/system/AnimTrans04.pcx",NULL); if (!AnimTrans[4])  { CtrlAnimTrans[4] =0; } else { CtrlAnimTrans[4] =1; }
AnimTrans[5]  = backend_load_bitmap("data/system/AnimTrans05.pcx",NULL); if (!AnimTrans[5])  { CtrlAnimTrans[5] =0; } else { CtrlAnimTrans[5] =1; }
AnimTrans[6]  = backend_load_bitmap("data/system/AnimTrans06.pcx",NULL); if (!AnimTrans[6])  { CtrlAnimTrans[6] =0; } else { CtrlAnimTrans[6] =1; }
AnimTrans[7]  = backend_load_bitmap("data/system/AnimTrans07.pcx",NULL); if (!AnimTrans[7])  { CtrlAnimTrans[7] =0; } else { CtrlAnimTrans[7] =1; }
AnimTrans[8]  = backend_load_bitmap("data/system/AnimTrans08.pcx",NULL); if (!AnimTrans[8])  { CtrlAnimTrans[8] =0; } else { CtrlAnimTrans[8] =1; }
AnimTrans[9]  = backend_load_bitmap("data/system/AnimTrans09.pcx",NULL); if (!AnimTrans[9])  { CtrlAnimTrans[9] =0; } else { CtrlAnimTrans[9] =1; }
AnimTrans[10] = backend_load_bitmap("data/system/AnimTrans10.pcx",NULL); if (!AnimTrans[10]) { CtrlAnimTrans[10]=0; } else { CtrlAnimTrans[10]=1; }
AnimTrans[11] = backend_load_bitmap("data/system/AnimTrans11.pcx",NULL); if (!AnimTrans[11]) { CtrlAnimTrans[11]=0; } else { CtrlAnimTrans[11]=1; }
AnimTrans[12] = backend_load_bitmap("data/system/AnimTrans12.pcx",NULL); if (!AnimTrans[12]) { CtrlAnimTrans[12]=0; } else { CtrlAnimTrans[12]=1; }
AnimTrans[13] = backend_load_bitmap("data/system/AnimTrans13.pcx",NULL); if (!AnimTrans[13]) { CtrlAnimTrans[13]=0; } else { CtrlAnimTrans[13]=1; }
AnimTrans[14] = backend_load_bitmap("data/system/AnimTrans14.pcx",NULL); if (!AnimTrans[14]) { CtrlAnimTrans[14]=0; } else { CtrlAnimTrans[14]=1; }
AnimTrans[15] = backend_load_bitmap("data/system/AnimTrans15.pcx",NULL); if (!AnimTrans[15]) { CtrlAnimTrans[15]=0; } else { CtrlAnimTrans[15]=1; }
AnimTrans[16] = backend_load_bitmap("data/system/AnimTrans16.pcx",NULL); if (!AnimTrans[16]) { CtrlAnimTrans[16]=0; } else { CtrlAnimTrans[16]=1; }
AnimTrans[17] = backend_load_bitmap("data/system/AnimTrans17.pcx",NULL); if (!AnimTrans[17]) { CtrlAnimTrans[17]=0; } else { CtrlAnimTrans[17]=1; }
AnimTrans[18] = backend_load_bitmap("data/system/AnimTrans18.pcx",NULL); if (!AnimTrans[18]) { CtrlAnimTrans[18]=0; } else { CtrlAnimTrans[18]=1; }
AnimTrans[19] = backend_load_bitmap("data/system/AnimTrans19.pcx",NULL); if (!AnimTrans[19]) { CtrlAnimTrans[19]=0; } else { CtrlAnimTrans[19]=1; }
AnimTrans[20] = backend_load_bitmap("data/system/AnimTrans20.pcx",NULL); if (!AnimTrans[20]) { CtrlAnimTrans[20]=0; } else { CtrlAnimTrans[20]=1; }
AnimTrans[21] = backend_load_bitmap("data/system/AnimTrans21.pcx",NULL); if (!AnimTrans[21]) { CtrlAnimTrans[21]=0; } else { CtrlAnimTrans[21]=1; }
AnimTrans[22] = backend_load_bitmap("data/system/AnimTrans22.pcx",NULL); if (!AnimTrans[22]) { CtrlAnimTrans[22]=0; } else { CtrlAnimTrans[22]=1; }
AnimTrans[23] = backend_load_bitmap("data/system/AnimTrans23.pcx",NULL); if (!AnimTrans[23]) { CtrlAnimTrans[23]=0; } else { CtrlAnimTrans[23]=1; }
AnimTrans[24] = backend_load_bitmap("data/system/AnimTrans24.pcx",NULL); if (!AnimTrans[24]) { CtrlAnimTrans[24]=0; } else { CtrlAnimTrans[24]=1; }
AnimTrans[25] = backend_load_bitmap("data/system/AnimTrans25.pcx",NULL); if (!AnimTrans[25]) { CtrlAnimTrans[25]=0; } else { CtrlAnimTrans[25]=1; }
AnimTrans[26] = backend_load_bitmap("data/system/AnimTrans26.pcx",NULL); if (!AnimTrans[26]) { CtrlAnimTrans[26]=0; } else { CtrlAnimTrans[26]=1; }
AnimTrans[27] = backend_load_bitmap("data/system/AnimTrans27.pcx",NULL); if (!AnimTrans[27]) { CtrlAnimTrans[27]=0; } else { CtrlAnimTrans[27]=1; }
AnimTrans[28] = backend_load_bitmap("data/system/AnimTrans28.pcx",NULL); if (!AnimTrans[28]) { CtrlAnimTrans[28]=0; } else { CtrlAnimTrans[28]=1; }
AnimTrans[29] = backend_load_bitmap("data/system/AnimTrans29.pcx",NULL); if (!AnimTrans[29]) { CtrlAnimTrans[29]=0; } else { CtrlAnimTrans[29]=1; }
HM_BITMAP AnimIntro[16];
AnimIntro[0]  = backend_load_bitmap("data/system/AnimIntro00.pcx",NULL); if (!AnimIntro[0])  { CtrlAnimIntro[0] =0; } else { CtrlAnimIntro[0] =1; }
AnimIntro[1]  = backend_load_bitmap("data/system/AnimIntro01.pcx",NULL); if (!AnimIntro[1])  { CtrlAnimIntro[1] =0; } else { CtrlAnimIntro[1] =1; }
AnimIntro[2]  = backend_load_bitmap("data/system/AnimIntro02.pcx",NULL); if (!AnimIntro[2])  { CtrlAnimIntro[2] =0; } else { CtrlAnimIntro[2] =1; }
AnimIntro[3]  = backend_load_bitmap("data/system/AnimIntro03.pcx",NULL); if (!AnimIntro[3])  { CtrlAnimIntro[3] =0; } else { CtrlAnimIntro[3] =1; }
AnimIntro[4]  = backend_load_bitmap("data/system/AnimIntro04.pcx",NULL); if (!AnimIntro[4])  { CtrlAnimIntro[4] =0; } else { CtrlAnimIntro[4] =1; }
AnimIntro[5]  = backend_load_bitmap("data/system/AnimIntro05.pcx",NULL); if (!AnimIntro[5])  { CtrlAnimIntro[5] =0; } else { CtrlAnimIntro[5] =1; }
AnimIntro[6]  = backend_load_bitmap("data/system/AnimIntro06.pcx",NULL); if (!AnimIntro[6])  { CtrlAnimIntro[6] =0; } else { CtrlAnimIntro[6] =1; }
AnimIntro[7]  = backend_load_bitmap("data/system/AnimIntro07.pcx",NULL); if (!AnimIntro[7])  { CtrlAnimIntro[7] =0; } else { CtrlAnimIntro[7] =1; }
AnimIntro[8]  = backend_load_bitmap("data/system/AnimIntro08.pcx",NULL); if (!AnimIntro[8])  { CtrlAnimIntro[8] =0; } else { CtrlAnimIntro[8] =1; }
AnimIntro[9]  = backend_load_bitmap("data/system/AnimIntro09.pcx",NULL); if (!AnimIntro[9])  { CtrlAnimIntro[9] =0; } else { CtrlAnimIntro[9] =1; }
AnimIntro[10] = backend_load_bitmap("data/system/AnimIntro10.pcx",NULL); if (!AnimIntro[10]) { CtrlAnimIntro[10]=0; } else { CtrlAnimIntro[10]=1; }
AnimIntro[11] = backend_load_bitmap("data/system/AnimIntro11.pcx",NULL); if (!AnimIntro[11]) { CtrlAnimIntro[11]=0; } else { CtrlAnimIntro[11]=1; }
AnimIntro[12] = backend_load_bitmap("data/system/AnimIntro12.pcx",NULL); if (!AnimIntro[12]) { CtrlAnimIntro[12]=0; } else { CtrlAnimIntro[12]=1; }
AnimIntro[13] = backend_load_bitmap("data/system/AnimIntro13.pcx",NULL); if (!AnimIntro[13]) { CtrlAnimIntro[13]=0; } else { CtrlAnimIntro[13]=1; }
AnimIntro[14] = backend_load_bitmap("data/system/AnimIntro14.pcx",NULL); if (!AnimIntro[14]) { CtrlAnimIntro[14]=0; } else { CtrlAnimIntro[14]=1; }
AnimIntro[15] = backend_load_bitmap("data/system/AnimIntro15.pcx",NULL); if (!AnimIntro[15]) { CtrlAnimIntro[15]=0; } else { CtrlAnimIntro[15]=1; }
HM_BITMAP MINIspr[9];
MINIspr[0] = backend_load_bitmap("data/system/000_01.pcx", NULL); if (!MINIspr[0]) { HamoopiError=1; }
MINIspr[1] = backend_create_bitmap(32,32);
MINIspr[2] = backend_create_bitmap(32,32);
MINIspr[3] = backend_create_bitmap(32,32);
MINIspr[4] = backend_create_bitmap(32,32);
MINIspr[5] = backend_create_bitmap(32,32);
MINIspr[6] = backend_create_bitmap(32,32);
MINIspr[7] = backend_create_bitmap(32,32);
MINIspr[8] = backend_create_bitmap(32,32);
HM_BITMAP MINIsprDisplay[9];
MINIsprDisplay[0] = backend_create_bitmap(64,64);
MINIsprDisplay[1] = backend_create_bitmap(64,64);
MINIsprDisplay[2] = backend_create_bitmap(64,64);
MINIsprDisplay[3] = backend_create_bitmap(64,64);
MINIsprDisplay[4] = backend_create_bitmap(64,64);
MINIsprDisplay[5] = backend_create_bitmap(64,64);
MINIsprDisplay[6] = backend_create_bitmap(64,64);
MINIsprDisplay[7] = backend_create_bitmap(64,64);
MINIsprDisplay[8] = backend_create_bitmap(64,64);
HM_BITMAP MINIsprDisplayArcadeMode[9];
MINIsprDisplayArcadeMode[0] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[1] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[2] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[3] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[4] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[5] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[6] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[7] = backend_create_bitmap(64,64);
MINIsprDisplayArcadeMode[8] = backend_create_bitmap(64,64);
HM_BITMAP P1BIGDisplay = backend_create_bitmap(128,128);
HM_BITMAP P2BIGDisplay = backend_create_bitmap(128,128);
HM_BITMAP P2BIGDisplayInv = backend_create_bitmap(128,128);

//idioma do jogo
strcpy(IDIOMA, (char *)backend_get_config_string("CONFIG", "language", "BR"));
if (strcmp (IDIOMA,"BR")==0){ if (HamoopiError==1) backend_message("ARQUIVOS OU DIRETORIOS NAO ENCONTRADOS."); };
if (strcmp (IDIOMA,"US")==0){ if (HamoopiError==1) backend_message("FILES OR DIRECTORIES NOT FOUND."); };

//define centro do mapa
MapCenterX=backend_get_config_int ( "TEMPLATE", "MapCenterX", 320 );
MapCenterY=backend_get_config_int ( "TEMPLATE", "MapCenterY", 118 );
difficulty=backend_get_config_int ( "CONFIG", "difficulty", 3 );

//modo historia
//carrega a lista de personagens instalados
for(int ind=1;ind<=MAX_CHARS;ind++){
char strtemp[9]="";
sprintf(strtemp, "char%i", ind);
strcpy(Lista_de_Personagens_Instalados[ind], (char *)backend_get_config_string("CHARS", strtemp, ""));
}

//atualiza a qtde de personagens instalados
for(int ind=1;ind<=MAX_CHARS;ind++){
if (strcmp (Lista_de_Personagens_Instalados[ind],"") != 0){ Qtde_Personagens_Instalados++; }
}
//faz o sorteio de personagens do modo historia <nao utilizado no momento, aguardando futura implementacao>
// Ao sortear, levar em consideracao o total de personagens instalados, abastecendo a lista arcade apropriadamente
for(int ind=1;ind<=MAX_CHARS;ind++){
strcpy(Lista_de_Personagens_ArcadeMode[ind],Lista_de_Personagens_Instalados[ind]);
}

//carrega a lista de Cenarios instalados
for(int ind=1;ind<=MAX_CHARS;ind++){
char strtemp[9]="";
sprintf(strtemp, "bg%i", ind);
strcpy(Lista_de_Cenarios_Instalados[ind], (char *)backend_get_config_string("BACKGROUNDS", strtemp, ""));
}
//atualiza a qtde de Cenarios instalados
for(int ind=1;ind<=MAX_CHARS;ind++){
if (strcmp (Lista_de_Cenarios_Instalados[ind],"") != 0){ Qtde_Cenarios_Instalados++; }
}
//faz o sorteio de Cenarios do modo historia <nao utilizado no momento, aguardando futura implementacao>
// Ao sortear, levar em consideracao o total de Cenarios instalados, abastecendo a lista arcade apropriadamente
for(int ind=1;ind<=MAX_CHARS;ind++){
strcpy(Lista_de_Cenarios_ArcadeMode[ind],Lista_de_Cenarios_Instalados[ind]);
}
int SelectBGID=1;

//Carrega Miniaturas - SELECT CHARS
for(int ind=1;ind<=MAX_CHARS;ind++){
if (Qtde_Personagens_Instalados>=ind) {
char MINIstring[99]=""; sprintf(MINIstring, "data/data/chars/%s/000_01.pcx", Lista_de_Personagens_Instalados[ind]);
MINIspr[ind] = backend_load_bitmap(MINIstring, NULL);
if (!MINIspr[ind]) { MINIspr[ind]=backend_load_bitmap("data/system/000_01.pcx", NULL); }
backend_stretch_blit(MINIspr[ind], MINIsprDisplay[ind], 0, 0, backend_bitmap_width(MINIspr[ind]), backend_bitmap_height(MINIspr[ind]), 0, 0, backend_bitmap_width(MINIsprDisplay[1]), backend_bitmap_height(MINIsprDisplay[1]));
backend_destroy_bitmap(MINIspr[ind]);
}
}

//miniaturas do arcade mode
for(int ind=1;ind<=8;ind++){
if (Qtde_Personagens_Instalados>=ind) {
char MINIstring[99]=""; sprintf(MINIstring, "data/data/chars/%s/000_01.pcx", Lista_de_Personagens_ArcadeMode[ind]);
MINIspr[ind] = backend_load_bitmap(MINIstring, NULL);
if (!MINIspr[ind]) { MINIspr[ind]=backend_load_bitmap("data/system/000_01.pcx", NULL); }
backend_stretch_blit(MINIspr[ind], MINIsprDisplayArcadeMode[ind], 0, 0, backend_bitmap_width(MINIspr[ind]), backend_bitmap_height(MINIspr[ind]), 0, 0, backend_bitmap_width(MINIsprDisplay[1]), backend_bitmap_height(MINIsprDisplay[1]));
backend_destroy_bitmap(MINIspr[ind]);
}
}

//P1 miniatura da foto ingame
strcpy(P[1].Name, (char *)backend_get_config_string("CHARS", "char1", ""));
char P1_1s[25]="";
sprintf(P1_1s, "data/data/chars/%s/000_01.pcx", P[1].Name);
HM_BITMAP P1_1 = backend_load_bitmap(P1_1s, NULL);
if (!P1_1) { P1_1=backend_load_bitmap("data/system/000_01.pcx", NULL); }
//P2 miniatura da foto ingame
strcpy(P[2].Name, (char *)backend_get_config_string("CHARS", "char2", ""));
char P2_1s[25]="";
sprintf(P2_1s, "data/chars/%s/000_01.pcx", P[2].Name);
HM_BITMAP P2_1 = backend_load_bitmap(P2_1s, NULL);
if (!P2_1) { P2_1=backend_load_bitmap("data/system/000_01.pcx", NULL); }

//propriedades de round
RoundTime = backend_get_config_int ("CONFIG", "time", 99 );
RoundTime = RoundTime*60+59;
RoundTotal = backend_get_config_int ("CONFIG", "rounds", 3 );

//inputs dos jogadores
p1_up     = backend_get_config_int ( "P1_CONTROL" , "P1_UP"     ,  84 ) ;
p1_down   = backend_get_config_int ( "P1_CONTROL" , "P1_DOWN"   ,  85 ) ;
p1_left   = backend_get_config_int ( "P1_CONTROL" , "P1_LEFT"   ,  82 ) ;
p1_right  = backend_get_config_int ( "P1_CONTROL" , "P1_RIGHT"  ,  83 ) ;
p1_bt1    = backend_get_config_int ( "P1_CONTROL" , "P1_BT1"    ,   1 ) ;
p1_bt2    = backend_get_config_int ( "P1_CONTROL" , "P1_BT2"    ,  19 ) ;
p1_bt3    = backend_get_config_int ( "P1_CONTROL" , "P1_BT3"    ,   4 ) ;
p1_bt4    = backend_get_config_int ( "P1_CONTROL" , "P1_BT4"    ,  26 ) ;
p1_bt5    = backend_get_config_int ( "P1_CONTROL" , "P1_BT5"    ,  24 ) ;
p1_bt6    = backend_get_config_int ( "P1_CONTROL" , "P1_BT6"    ,   3 ) ;
p1_select = backend_get_config_int ( "P1_CONTROL" , "P1_SELECT" ,  75 ) ;
p1_start  = backend_get_config_int ( "P1_CONTROL" , "P1_START"  ,  67 ) ;
p2_up     = backend_get_config_int ( "P2_CONTROL" , "P2_UP"     ,   9 ) ;
p2_down   = backend_get_config_int ( "P2_CONTROL" , "P2_DOWN"   ,  11 ) ;
p2_left   = backend_get_config_int ( "P2_CONTROL" , "P2_LEFT"   ,  10 ) ;
p2_right  = backend_get_config_int ( "P2_CONTROL" , "P2_RIGHT"  ,  12 ) ;
p2_bt1    = backend_get_config_int ( "P2_CONTROL" , "P2_BT1"    ,   6 ) ;
p2_bt2    = backend_get_config_int ( "P2_CONTROL" , "P2_BT2"    ,   7 ) ;
p2_bt3    = backend_get_config_int ( "P2_CONTROL" , "P2_BT3"    ,   8 ) ;
p2_bt4    = backend_get_config_int ( "P2_CONTROL" , "P2_BT4"    ,  22 ) ;
p2_bt5    = backend_get_config_int ( "P2_CONTROL" , "P2_BT5"    ,   2 ) ;
p2_bt6    = backend_get_config_int ( "P2_CONTROL" , "P2_BT6"    ,  14 ) ;
p2_select = backend_get_config_int ( "P2_CONTROL" , "P2_SELECT" ,  18 ) ;
p2_start  = backend_get_config_int ( "P2_CONTROL" , "P2_START"  ,  20 ) ;

//propriedades da paleta de cor
P[1].DefineCorDaPaleta=0;
P[2].DefineCorDaPaleta=0;

//musicas e efeitos
HM_SAMPLE intro   = backend_load_sample("data/sounds/intro.wav");
HM_SAMPLE round1  = backend_load_sample("data/sounds/round1.wav");
HM_SAMPLE round2  = backend_load_sample("data/sounds/round2.wav");
HM_SAMPLE round3  = backend_load_sample("data/sounds/round3.wav");
HM_SAMPLE fight   = backend_load_sample("data/sounds/fight.wav");
HM_SAMPLE ko      = backend_load_sample("data/sounds/ko.wav");
HM_SAMPLE perfect = backend_load_sample("data/sounds/perfect.wav");
HM_SAMPLE back    = backend_load_sample("data/sounds/back.wav");
HM_SAMPLE choice  = backend_load_sample("data/sounds/choice.wav");
HM_SAMPLE confirm = backend_load_sample("data/sounds/confirm.wav");
HM_SAMPLE cursor  = backend_load_sample("data/sounds/cursor.wav");
HM_SAMPLE attacklvl1 = backend_load_sample("data/sounds/attacklvl1.wav");
HM_SAMPLE attacklvl2 = backend_load_sample("data/sounds/attacklvl2.wav");
HM_SAMPLE attacklvl3 = backend_load_sample("data/sounds/attacklvl3.wav");
HM_SAMPLE hitlvl1 = backend_load_sample("data/sounds/hitlvl1.wav");
HM_SAMPLE hitlvl2 = backend_load_sample("data/sounds/hitlvl2.wav");
HM_SAMPLE hitlvl3 = backend_load_sample("data/sounds/hitlvl3.wav");
HM_MIDI bgm_apresentacao  = backend_load_midi("data/sounds/bgm_apresentacao.mid");
HM_MIDI bgm_continue      = backend_load_midi("data/sounds/bgm_continue.mid");
HM_MIDI bgm_select_screen = backend_load_midi("data/sounds/bgm_select_screen.mid");
HM_MIDI bgm_versus_mode   = backend_load_midi("data/sounds/bgm_versus_mode.mid");

backend_set_window_title(versao);

/////////////////////////////////////////////////////////////////////////////
// LOOP DE JOGO -------------------------------------------------------[**03]
/////////////////////////////////////////////////////////////////////////////

while (sair==0)
{

check_keys_P1(); check_keys_P2(); //verifica teclas key_press, key_hold, key_released
delay=timer;
Segundos=((timer/60)-Minutos*60)-Horas*3600;
if (Segundos>=60) { Minutos++; Segundos=0; if(Minutos>=60){ Horas++; Minutos=0; } }
if (timermenus<15) { timermenus++; } //utilizado para melhor navegacao entre os menus
MeioDaTela=(P[1].x+P[2].x)/2;
if (P[1].State==300 || P[1].State==310 || P[1].State==320) { P[1].TempoPulo=P[1].TempoPulo+1; }
if (P[2].State==300 || P[2].State==310 || P[2].State==320) { P[2].TempoPulo=P[2].TempoPulo+1; }
P[1].ticks_4slot=P[1].ticks_4slot+1;
P[2].ticks_4slot=P[2].ticks_4slot+1;
if (ModoFullscreen==0 && backend_key[HM_KEY_ALT] && backend_key[HM_KEY_ENTER]) { ModoFullscreen=1; backend_set_gfx_mode(HM_GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0); }
if (ModoFullscreen==1 && backend_key[HM_KEY_ALT] && backend_key[HM_KEY_ENTER]) { ModoFullscreen=0; backend_set_gfx_mode(HM_GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0); }
backend_set_volume(op_sfx_volume, op_sound_volume); //volume //backend_set_volume(int digi_volume, int midi_volume);

/////////////////////////////////////////////////////////////////////////////
// INTRO --------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (IntroMode==1){
if(timermenus==0) {
backend_play_sample(intro, 255, 128, 1000, 0);
}

IntroTimer++;
P[1].Pode_Mexer=1;
P[2].Pode_Mexer=1;

if (timermenus==15){
if (backend_key[HM_KEY_ESC]) {sair=1;}
if (backend_key[HM_KEY_ALT] && backend_key[HM_KEY_F4]) {sair=1;}
if (P[1].key_START_pressed==1) { timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; IntroMode=0; IntroTimer=0; DonationScreen=1; }
}

if (IntroTimer==300-30){ FadeIN=1; FadeOUT=0; }
if (IntroTimer>=300){ timermenus=0; IntroMode=0; IntroTimer=0; DonationScreen=1; }
backend_draw_sprite(bufferx, GAME_intro, 0, 0);
backend_stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

/////////////////////////////////////////////////////////////////////////////
// DONATION SCREEN ----------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (DonationScreen==1){
if(timermenus==0) {
FadeIN=0; FadeOUT=1;
}

IntroTimer++;

if (timermenus==15){
if (backend_key[HM_KEY_ESC]) {sair=1;}
if (backend_key[HM_KEY_ALT] && backend_key[HM_KEY_F4]) {sair=1;}
if (P[1].key_START_pressed==1) { timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; DonationScreen=0; ApresentacaoMode=1; }
}

if (IntroTimer==300-30){ FadeIN=1; FadeOUT=0; }
if (IntroTimer>=300){ timermenus=0; DonationScreen=0; ApresentacaoMode=1; }
backend_draw_sprite(bufferx, donation, 0, 0);

backend_rectfill(bufferx, 160,  20, 600, 150, backend_makecol(255,255,255));
backend_rectfill(bufferx, 100, 370, 600, 460, backend_makecol(255,255,255));

if (strcmp (IDIOMA,"US")==0){
backend_textprintf_centre_ex(bufferx, font_19, 380, 40+15, backend_makecol(000,000,000), -1, "Please donate any amount of" );
backend_textprintf_centre_ex(bufferx, font_19, 380, 65+15, backend_makecol(000,000,000), -1, "   to keep project alive" );
backend_textprintf_centre_ex(bufferx, font_19, 380, 65+15, backend_makecol(000,140,010), -1, "   BTC                        " );
backend_textprintf_centre_ex(bufferx, font_19, 320,   400, backend_makecol(000,000,000), -1, "Thanks, Hamoopi Team" );
}
if (strcmp (IDIOMA,"BR")==0){
backend_textprintf_centre_ex(bufferx, font_19, 380, 30+10, backend_makecol(000,000,000), -1, "Por favor considere fazer uma" );
backend_textprintf_centre_ex(bufferx, font_19, 380, 55+10, backend_makecol(000,000,000), -1, "doação de qualquer quantia de" );
backend_textprintf_centre_ex(bufferx, font_19, 380, 80+10, backend_makecol(000,000,000), -1, "   para manter o projeto vivo" );
backend_textprintf_centre_ex(bufferx, font_19, 380, 80+10, backend_makecol(000,140,010), -1, "   BTC                            " );
backend_textprintf_centre_ex(bufferx, font_19, 320,   400, backend_makecol(000,000,000), -1, "Obrigado, Equipe Hamoopi" );
}

backend_stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

/////////////////////////////////////////////////////////////////////////////
// APRESENTACAO -------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (ApresentacaoMode==1){
if(timermenus==0) { backend_play_midi(bgm_apresentacao, 1); FadeIN=0; FadeOUT=1; } //bgm
backend_draw_sprite(bufferx, GAME_logo, 0, 0);

// atencao! modo Arcade desativado no momento!!! //
/*temporario*/ if (timermenus==0){ menu_op=2; } if(menu_op==1){ menu_op=2; } /*temporario*/

if (timermenus==15){
if (P[1].key_UP_pressed  ==1) { menu_op--; backend_play_sample(cursor, 255, 128, 1000, 0); if (menu_op<1) { menu_op=5; }}
if (P[1].key_DOWN_pressed==1) { menu_op++; backend_play_sample(cursor, 255, 128, 1000, 0); if (menu_op>5) { menu_op=1; }}
//if (P[1].key_START_pressed==1 && menu_op==1) { backend_play_sample(confirm, 255, 128, 1000, 0); timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; menu_op=1; ApresentacaoMode=0; SelectCharMode=1; ModoHistoria=1; }
if (P[1].key_START_pressed==1 && menu_op==2) { backend_play_sample(confirm, 255, 128, 1000, 0); timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; menu_op=1; ApresentacaoMode=0; SelectCharMode=1; strcpy(ChoiceP2,""); strcpy(P[2].Name,""); }
if (P[1].key_START_pressed==1 && menu_op==3) { backend_play_sample(confirm, 255, 128, 1000, 0); timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; menu_op=1; ApresentacaoMode=0; EditMode=1; }
if (P[1].key_START_pressed==1 && menu_op==4) { backend_play_sample(confirm, 255, 128, 1000, 0); timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; menu_op=1; ApresentacaoMode=0; OptionsMode=1; options_op=1; }
if (P[1].key_START_pressed==1 && menu_op==5) { sair=1; }
if (backend_key[HM_KEY_ALT] && backend_key[HM_KEY_F4]) {sair=1;}
if (backend_key[HM_KEY_ESC]) {sair=1;}
}
strcpy(ChoiceP1,""); strcpy(ChoiceP2,""); strcpy(ChoiceBG,"");
int espacamento=30;
if (menu_op==1){ backend_draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*0)); }
if (menu_op==2){ backend_draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*1)); }
if (menu_op==3){ backend_draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*2)); }
if (menu_op==4){ backend_draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*3)); }
if (menu_op==5){ backend_draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*4)); }

if (strcmp (IDIOMA,"US")==0){
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*0, backend_makecol(000,000,000), -1, "ARCADE" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*1, backend_makecol(000,000,000), -1, "VERSUS" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*2, backend_makecol(000,000,000), -1, "EDITOR" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*3, backend_makecol(000,000,000), -1, "OPTIONS" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*4, backend_makecol(000,000,000), -1, "EXIT" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*0, backend_makecol(155,155,155), -1, "ARCADE" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*1, backend_makecol(255,255,255), -1, "VERSUS" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*2, backend_makecol(255,255,255), -1, "EDITOR" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*3, backend_makecol(255,255,255), -1, "OPTIONS" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*4, backend_makecol(255,010,005), -1, "EXIT" );
if (menu_op==1) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*0, backend_makecol(255,170,000), -1, "ARCADE" );
if (menu_op==2) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*1, backend_makecol(255,170,000), -1, "VERSUS" );
if (menu_op==3) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*2, backend_makecol(255,170,000), -1, "EDITOR" );
if (menu_op==4) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*3, backend_makecol(255,170,000), -1, "OPTIONS" );
if (menu_op==5) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*4, backend_makecol(255,170,000), -1, "EXIT" );
}
if (strcmp (IDIOMA,"BR")==0){
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*0, backend_makecol(000,000,000), -1, "ARCADE" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*1, backend_makecol(000,000,000), -1, "VERSUS" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*2, backend_makecol(000,000,000), -1, "EDITOR" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*3, backend_makecol(000,000,000), -1, "OPÇÕES" );
backend_textprintf_centre_ex(bufferx, font_30, 322, 227+30*4, backend_makecol(000,000,000), -1, "SAIR" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*0, backend_makecol(155,155,155), -1, "ARCADE" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*1, backend_makecol(255,255,255), -1, "VERSUS" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*2, backend_makecol(255,255,255), -1, "EDITOR" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*3, backend_makecol(255,255,255), -1, "OPÇÕES" );
backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*4, backend_makecol(255,010,005), -1, "SAIR" );
if (menu_op==1) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*0, backend_makecol(255,170,000), -1, "ARCADE" );
if (menu_op==2) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*1, backend_makecol(255,170,000), -1, "VERSUS" );
if (menu_op==3) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*2, backend_makecol(255,170,000), -1, "EDITOR" );
if (menu_op==4) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*3, backend_makecol(255,170,000), -1, "OPÇÕES" );
if (menu_op==5) backend_textprintf_centre_ex(bufferx, font_30, 320, 225+30*4, backend_makecol(255,170,000), -1, "SAIR" );
}

//versao da HAMOOPI
backend_textprintf_right_ex(bufferx, font_debug, 629, 457, backend_makecol(000,000,000), -1, "%s", versao); //sombra do texto
backend_textprintf_right_ex(bufferx, font_debug, 627, 455, backend_makecol(255,255,255), -1, "%s", versao); //texto

backend_stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

/////////////////////////////////////////////////////////////////////////////
// OPTIONS ------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (OptionsMode==1){
if (timermenus>=15){
int salvardados=0;
if (backend_key[HM_KEY_ESC]) { backend_play_sample(back, 255, 128, 1000, 0); timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; menu_op=1; ApresentacaoMode=1; OptionsMode=0; salvardados=1; }
if (backend_key[HM_KEY_ALT] && backend_key[HM_KEY_F4]) {sair=1;}
if (P[1].key_START_pressed==1 && options_op==15) { backend_play_sample(confirm, 255, 128, 1000, 0); timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; menu_op=1; ApresentacaoMode=1; OptionsMode=0; salvardados=1; }
if (P[1].key_UP_pressed  ==1) { options_op--; backend_play_sample(cursor, 255, 128, 1000, 0); if (options_op< 1) { options_op=15; }}
if (P[1].key_DOWN_pressed==1) { options_op++; backend_play_sample(cursor, 255, 128, 1000, 0); if (options_op>15) { options_op= 1; }}

if(salvardados==1){
salvardados=0;
//salva dados
backend_set_config_file("SETUP.ini");
set_config_string ( "CONFIG", "language", IDIOMA );
set_config_int ( "CONFIG", "rounds", RoundTotal );
set_config_int ( "CONFIG", "time", RoundTime/60 );
set_config_int ( "CONFIG", "P1_Energy", P[1].Energy );
set_config_int ( "CONFIG", "P2_Energy", P[2].Energy );
set_config_int ( "CONFIG", "P1_Special", P[1].Special );
set_config_int ( "CONFIG", "P2_Special", P[2].Special );
set_config_int ( "CONFIG", "FullScreen", ModoFullscreen );
set_config_int ( "CONFIG", "draw_shadows", op_desenhar_sombras );
set_config_int ( "CONFIG", "zoom", op_Zoom );
set_config_int ( "CONFIG", "show_inputs", Draw_Input );
set_config_int ( "CONFIG", "window_res_x", WindowResX );
set_config_int ( "CONFIG", "window_res_y", WindowResY );
set_config_int ( "CONFIG", "frame_data", op_ShowFrameData );
backend_set_volume(op_sfx_volume, op_sound_volume);
}
}

if(timermenus==0){
backend_set_config_file("SETUP.ini");
RoundTotal = backend_get_config_int ("CONFIG", "rounds", 3 );
RoundTime  = backend_get_config_int ("CONFIG", "time", 99 ); RoundTime=RoundTime*60+59;
P[1].Energy=backend_get_config_int ( "CONFIG", "P1_Energy", 1000 );
P[2].Energy=backend_get_config_int ( "CONFIG", "P2_Energy", 1000 );
P[1].Special=backend_get_config_int ( "CONFIG", "P1_Special", 1000 );
P[2].Special=backend_get_config_int ( "CONFIG", "P2_Special", 1000 );
ModoFullscreen=backend_get_config_int ( "CONFIG", "FullScreen", 0 );
op_desenhar_sombras = backend_get_config_int ( "CONFIG" , "draw_shadows",  1 ) ;
op_Zoom = backend_get_config_int ( "CONFIG" , "zoom",  1 ) ;
Draw_Input = backend_get_config_int ( "CONFIG" , "show_inputs",  0 ) ;
op_sound_volume = backend_get_config_int ( "CONFIG" , "sound_volume",  255 ) ;
op_sfx_volume = backend_get_config_int ( "CONFIG" , "sfx_volume",  255 ) ;
WindowResX = backend_get_config_int ( "CONFIG" , "window_res_x",  640 ) ;
WindowResY = backend_get_config_int ( "CONFIG" , "window_res_y",  480 ) ;
if(WindowResX== 320 && WindowResY==240) WindowResNumber=1;
if(WindowResX== 640 && WindowResY==480) WindowResNumber=2;
if(WindowResX== 720 && WindowResY==480) WindowResNumber=3; //SD
if(WindowResX== 800 && WindowResY==600) WindowResNumber=4;
if(WindowResX== 960 && WindowResY==640) WindowResNumber=5;
if(WindowResX== 960 && WindowResY==720) WindowResNumber=6;
if(WindowResX==1024 && WindowResY==600) WindowResNumber=7;
if(WindowResX==1280 && WindowResY==720) WindowResNumber=8; //HD
}

backend_draw_sprite(bufferx, GAME_options, 0, 0);
int espacamento=22;
if (options_op== 1){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 0)); }
if (options_op== 2){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 1)); }
if (options_op== 3){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 2)); }
if (options_op== 4){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 3)); }
if (options_op== 5){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 4)); }
if (options_op== 6){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 5)); }
if (options_op== 7){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 6)); }
if (options_op== 8){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 7)); }
if (options_op== 9){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 8)); }
if (options_op==10){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 9)); }
if (options_op==11){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*10)); }
if (options_op==12){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*11)); }
if (options_op==13){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*12)); }
if (options_op==14){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*13)); }
if (options_op==15){ backend_draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*14)); }

//desenha valores configuraveis

if (strcmp (IDIOMA,"US")==0){
backend_draw_sprite(bufferx, flag_US, 422, 58);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 0), backend_makecol(025,025,025), -1, "Language: %s", IDIOMA);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 1), backend_makecol(025,025,025), -1, "Rounds: %i", RoundTotal);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 2), backend_makecol(025,025,025), -1, "Timer: %i", RoundTime/60);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 3), backend_makecol(025,025,025), -1, "P1 Energy: %i", P[1].Energy/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 4), backend_makecol(025,025,025), -1, "P1 Special: %i", P[1].Special/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 5), backend_makecol(025,025,025), -1, "P2 Energy: %i", P[2].Energy/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 6), backend_makecol(025,025,025), -1, "P2 Special: %i", P[2].Special/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 7), backend_makecol(025,025,025), -1, "Full Screen: %i", ModoFullscreen);
if (WindowResNumber==1) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 320x240");
if (WindowResNumber==2) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 640x480");
if (WindowResNumber==3) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 720x480");
if (WindowResNumber==4) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 800x600");
if (WindowResNumber==5) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 960x640");
if (WindowResNumber==6) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 960x720");
if (WindowResNumber==7) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 1024x600");
if (WindowResNumber==8) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 1280x720");
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 9), backend_makecol(025,025,025), -1, "Draw Shadows: %i", op_desenhar_sombras );
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*10), backend_makecol(025,025,025), -1, "Enable Zoom: %i", op_Zoom );
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*11), backend_makecol(025,025,025), -1, "Draw Inputs: %i", Draw_Input );
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*12), backend_makecol(025,025,025), -1, "Frame Data: %i", op_ShowFrameData );

backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*14), backend_makecol(025,025,025), -1, "EXIT" );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 0), backend_makecol(255,255,255), -1, "Language: %s", IDIOMA);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 1), backend_makecol(255,255,255), -1, "Rounds: %i", RoundTotal);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 2), backend_makecol(255,255,255), -1, "Timer: %i", RoundTime/60);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 3), backend_makecol(255,255,255), -1, "P1 Energy: %i", P[1].Energy/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 4), backend_makecol(255,255,255), -1, "P1 Special: %i", P[1].Special/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 5), backend_makecol(255,255,255), -1, "P2 Energy: %i", P[2].Energy/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 6), backend_makecol(255,255,255), -1, "P2 Special: %i", P[2].Special/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 7), backend_makecol(255,255,255), -1, "Full Screen: %i", ModoFullscreen);
if (WindowResNumber==1) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 320x240");
if (WindowResNumber==2) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 640x480");
if (WindowResNumber==3) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 720x480");
if (WindowResNumber==4) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 800x600");
if (WindowResNumber==5) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 960x640");
if (WindowResNumber==6) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 960x720");
if (WindowResNumber==7) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 1024x600");
if (WindowResNumber==8) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 1280x720");
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 9), backend_makecol(255,255,255), -1, "Draw Shadows: %i", op_desenhar_sombras );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*10), backend_makecol(255,255,255), -1, "Enable Zoom: %i", op_Zoom );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*11), backend_makecol(255,255,255), -1, "Draw Inputs: %i", Draw_Input );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*12), backend_makecol(255,255,255), -1, "Frame Data: %i", op_ShowFrameData );

backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*14), backend_makecol(255,010,005), -1, "EXIT" );
if (options_op== 1) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 0), backend_makecol(255,170,000), -1, "Language: %s", IDIOMA);
if (options_op== 2) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 1), backend_makecol(255,170,000), -1, "Rounds: %i", RoundTotal);
if (options_op== 3) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 2), backend_makecol(255,170,000), -1, "Timer: %i", RoundTime/60);
if (options_op== 4) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 3), backend_makecol(255,170,000), -1, "P1 Energy: %i", P[1].Energy/10);
if (options_op== 5) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 4), backend_makecol(255,170,000), -1, "P1 Special: %i", P[1].Special/10);
if (options_op== 6) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 5), backend_makecol(255,170,000), -1, "P2 Energy: %i", P[2].Energy/10);
if (options_op== 7) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 6), backend_makecol(255,170,000), -1, "P2 Special: %i", P[2].Special/10);
if (options_op== 8) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 7), backend_makecol(255,170,000), -1, "Full Screen: %i", ModoFullscreen );
if (options_op== 9){
if (WindowResNumber==1) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 320x240");
if (WindowResNumber==2) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 640x480");
if (WindowResNumber==3) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 720x480");
if (WindowResNumber==4) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 800x600");
if (WindowResNumber==5) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 960x640");
if (WindowResNumber==6) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 960x720");
if (WindowResNumber==7) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 1024x600");
if (WindowResNumber==8) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 1280x720");
}
if (options_op==10) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 9), backend_makecol(255,170,000), -1, "Draw Shadows: %i", op_desenhar_sombras );
if (options_op==11) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*10), backend_makecol(255,170,000), -1, "Enable Zoom: %i", op_Zoom );
if (options_op==12) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*11), backend_makecol(255,170,000), -1, "Draw Inputs: %i", Draw_Input );
if (options_op==13) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*12), backend_makecol(255,170,000), -1, "Frame Data: %i", op_ShowFrameData );

if (options_op==15) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*14), backend_makecol(255,170,000), -1, "EXIT" );
}

if (strcmp (IDIOMA,"BR")==0){
backend_draw_sprite(bufferx, flag_BR, 422, 58);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 0), backend_makecol(025,025,025), -1, "Idioma: %s", IDIOMA);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 1), backend_makecol(025,025,025), -1, "Rounds: %i", RoundTotal);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 2), backend_makecol(025,025,025), -1, "Relógio: %i", RoundTime/60);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 3), backend_makecol(025,025,025), -1, "P1 Energia: %i", P[1].Energy/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 4), backend_makecol(025,025,025), -1, "P1 Especial: %i", P[1].Special/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 5), backend_makecol(025,025,025), -1, "P2 Energia: %i", P[2].Energy/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 6), backend_makecol(025,025,025), -1, "P2 Especial: %i", P[2].Special/10);
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 7), backend_makecol(025,025,025), -1, "Tela Cheia: %i", ModoFullscreen);
if (WindowResNumber==1) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 320x240");
if (WindowResNumber==2) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 640x480");
if (WindowResNumber==3) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 720x480");
if (WindowResNumber==4) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 800x600");
if (WindowResNumber==5) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 960x640");
if (WindowResNumber==6) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 960x720");
if (WindowResNumber==7) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 1024x600");
if (WindowResNumber==8) backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 8), backend_makecol(025,025,025), -1, "Win Res: 1280x720");
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento* 9), backend_makecol(025,025,025), -1, "Desenhar Sombras: %i", op_desenhar_sombras );
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*10), backend_makecol(025,025,025), -1, "Ativar Zoom: %i", op_Zoom );
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*11), backend_makecol(025,025,025), -1, "Desenhar Inputs: %i", Draw_Input );
backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*12), backend_makecol(025,025,025), -1, "Frame Data: %i", op_ShowFrameData );

backend_textprintf_ex(bufferx, font_20, 192, 82+(espacamento*14), backend_makecol(025,025,025), -1, "SAIR" );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 0), backend_makecol(255,255,255), -1, "Idioma: %s", IDIOMA);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 1), backend_makecol(255,255,255), -1, "Rounds: %i", RoundTotal);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 2), backend_makecol(255,255,255), -1, "Relógio: %i", RoundTime/60);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 3), backend_makecol(255,255,255), -1, "P1 Energia: %i", P[1].Energy/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 4), backend_makecol(255,255,255), -1, "P1 Especial: %i", P[1].Special/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 5), backend_makecol(255,255,255), -1, "P2 Energia: %i", P[2].Energy/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 6), backend_makecol(255,255,255), -1, "P2 Especial: %i", P[2].Special/10);
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 7), backend_makecol(255,255,255), -1, "Tela Cheia: %i", ModoFullscreen);
if (WindowResNumber==1) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 320x240");
if (WindowResNumber==2) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 640x480");
if (WindowResNumber==3) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 720x480");
if (WindowResNumber==4) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 800x600");
if (WindowResNumber==5) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 960x640");
if (WindowResNumber==6) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 960x720");
if (WindowResNumber==7) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 1024x600");
if (WindowResNumber==8) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,255,255), -1, "Win Res: 1280x720");
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 9), backend_makecol(255,255,255), -1, "Desenhar Sombras: %i", op_desenhar_sombras );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*10), backend_makecol(255,255,255), -1, "Ativar Zoom: %i", op_Zoom );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*11), backend_makecol(255,255,255), -1, "Desenhar Inputs: %i", Draw_Input );
backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*12), backend_makecol(255,255,255), -1, "Frame Data: %i", op_ShowFrameData );

backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*14), backend_makecol(255,010,005), -1, "SAIR" );
if (options_op== 1) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 0), backend_makecol(255,170,000), -1, "Idioma: %s", IDIOMA);
if (options_op== 2) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 1), backend_makecol(255,170,000), -1, "Rounds: %i", RoundTotal);
if (options_op== 3) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 2), backend_makecol(255,170,000), -1, "Relógio: %i", RoundTime/60);
if (options_op== 4) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 3), backend_makecol(255,170,000), -1, "P1 Energia: %i", P[1].Energy/10);
if (options_op== 5) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 4), backend_makecol(255,170,000), -1, "P1 Especial: %i", P[1].Special/10);
if (options_op== 6) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 5), backend_makecol(255,170,000), -1, "P2 Energia: %i", P[2].Energy/10);
if (options_op== 7) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 6), backend_makecol(255,170,000), -1, "P2 Especial: %i", P[2].Special/10);
if (options_op== 8) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 7), backend_makecol(255,170,000), -1, "Tela Cheia: %i", ModoFullscreen );
if (options_op== 9){
if (WindowResNumber==1) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 320x240");
if (WindowResNumber==2) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 640x480");
if (WindowResNumber==3) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 720x480");
if (WindowResNumber==4) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 800x600");
if (WindowResNumber==5) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 960x640");
if (WindowResNumber==6) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 960x720");
if (WindowResNumber==7) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 1024x600");
if (WindowResNumber==8) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 8), backend_makecol(255,170,000), -1, "Win Res: 1280x720");
}
if (options_op==10) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento* 9), backend_makecol(255,170,000), -1, "Desenhar Sombras: %i", op_desenhar_sombras );
if (options_op==11) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*10), backend_makecol(255,170,000), -1, "Ativar Zoom: %i", op_Zoom );
if (options_op==12) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*11), backend_makecol(255,170,000), -1, "Desenhar Inputs: %i", Draw_Input );
if (options_op==13) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*12), backend_makecol(255,170,000), -1, "Frame Data: %i", op_ShowFrameData );

if (options_op==15) backend_textprintf_ex(bufferx, font_20, 190, 80+(espacamento*14), backend_makecol(255,170,000), -1, "SAIR" );
}

//altera valores configuraveis
if (P[1].key_RIGHT_pressed ==1 && options_op==1 ) { strcpy(IDIOMA, "BR"); }
if (P[1].key_LEFT_pressed  ==1 && options_op==1 ) { strcpy(IDIOMA, "US"); }
if (P[1].key_RIGHT_pressed ==1 && options_op==2 && RoundTotal<=  4) { RoundTotal=RoundTotal+1; }
if (P[1].key_LEFT_pressed  ==1 && options_op==2 && RoundTotal>=  2) { RoundTotal=RoundTotal-1; }
if ((/*P[1].key_RIGHT_pressed ==1 || */P[1].key_RIGHT_hold==1) && options_op==3 && RoundTime<=60*99) { RoundTime =RoundTime+60; if(RoundTime>60*99)RoundTime=60*99; }
if ((/*P[1].key_LEFT_pressed  ==1 || */P[1].key_LEFT_hold==1) && options_op==3 && RoundTime>=66*10) { RoundTime =RoundTime-60; if(RoundTime<60*10)RoundTime=60*10; }
if (P[1].key_RIGHT_pressed ==1 && options_op==4 && P[1].Energy<1000) { P[1].Energy =P[1].Energy+100; }
if (P[1].key_LEFT_pressed  ==1 && options_op==4 && P[1].Energy> 100) { P[1].Energy =P[1].Energy-100; }
if (P[1].key_RIGHT_pressed ==1 && options_op==5 && P[1].Special<1000) { P[1].Special =P[1].Special+100; }
if (P[1].key_LEFT_pressed  ==1 && options_op==5 && P[1].Special>   0) { P[1].Special =P[1].Special-100; }
if (P[1].key_RIGHT_pressed ==1 && options_op==6 && P[2].Energy<1000) { P[2].Energy =P[2].Energy+100; }
if (P[1].key_LEFT_pressed  ==1 && options_op==6 && P[2].Energy> 100) { P[2].Energy =P[2].Energy-100; }
if (P[1].key_RIGHT_pressed ==1 && options_op==7 && P[2].Special<1000) { P[2].Special =P[2].Special+100; }
if (P[1].key_LEFT_pressed  ==1 && options_op==7 && P[2].Special>   0) { P[2].Special =P[2].Special-100; }
if (P[1].key_RIGHT_pressed ==1 && options_op==8 && ModoFullscreen==0 ) { ModoFullscreen=1; backend_set_gfx_mode(HM_GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0); }
if (P[1].key_LEFT_pressed  ==1 && options_op==8 && ModoFullscreen==1 ) { ModoFullscreen=0; backend_set_gfx_mode(HM_GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0); }
if (P[1].key_RIGHT_pressed ==1 && options_op==9 && WindowResNumber<=7) { WindowResNumber++; }
if (P[1].key_LEFT_pressed  ==1 && options_op==9 && WindowResNumber>=2) { WindowResNumber--; }
if (P[1].key_START_pressed ==1 && options_op==9 && ModoFullscreen==0) {
if(WindowResNumber==1) { WindowResX= 320; WindowResY=240; }
if(WindowResNumber==2) { WindowResX= 640; WindowResY=480; }
if(WindowResNumber==3) { WindowResX= 720; WindowResY=480; }
if(WindowResNumber==4) { WindowResX= 800; WindowResY=600; }
if(WindowResNumber==5) { WindowResX= 960; WindowResY=640; }
if(WindowResNumber==6) { WindowResX= 960; WindowResY=720; }
if(WindowResNumber==7) { WindowResX=1024; WindowResY=600; }
if(WindowResNumber==8) { WindowResX=1280; WindowResY=720; }
backend_set_gfx_mode(HM_GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0);
}
if (P[1].key_LEFT_pressed  ==1 && options_op==10) op_desenhar_sombras=0;
if (P[1].key_RIGHT_pressed ==1 && options_op==10) op_desenhar_sombras=1;
if (P[1].key_LEFT_pressed  ==1 && options_op==11) op_Zoom=0;
if (P[1].key_RIGHT_pressed ==1 && options_op==11) op_Zoom=1;
if (P[1].key_LEFT_pressed  ==1 && options_op==12) Draw_Input=0;
if (P[1].key_RIGHT_pressed ==1 && options_op==12) Draw_Input=1;
if (P[1].key_LEFT_pressed  ==1 && options_op==13) op_ShowFrameData=0;
if (P[1].key_RIGHT_pressed ==1 && options_op==13) op_ShowFrameData=1;

backend_stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

/////////////////////////////////////////////////////////////////////////////
// SELECT CHARACTERS & BACKGROUNDS ------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (SelectCharMode==1) {

if(timermenus==0) { backend_play_midi(bgm_select_screen, 1); } //bgm
//atribui IDs de Navegação / Carrega primeira imagem BIG ao inicializar
if (Qtde_Personagens_Instalados>=1 && timermenus==0) {
SelectCharP1ID=1;
SelectCharP2ID=Qtde_Personagens_Instalados;
if (ModoHistoria==1) { strcpy(ChoiceP2,"-P2CPU-"); strcpy(P[2].Name,"-P2CPU-"); NumPersonagensEscolhidos=1; }
//BIG P1
sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[1]);
P1BIGDisplay = backend_load_bitmap(P1BIGDisplaystring, NULL);
if (!P1BIGDisplay) { P1BIGDisplay=backend_load_bitmap("data/system/000_00.pcx", NULL); }
//BIG P2
if (strcmp( ChoiceP2,"-P2CPU-") !=0) {
if (SelectCharP2ID==1){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[1]); }
if (SelectCharP2ID==2){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[2]); }
if (SelectCharP2ID==3){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[3]); }
if (SelectCharP2ID==4){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[4]); }
if (SelectCharP2ID==5){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[5]); }
if (SelectCharP2ID==6){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[6]); }
if (SelectCharP2ID==7){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[7]); }
if (SelectCharP2ID==8){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[8]); }
P2BIGDisplay = backend_load_bitmap(P2BIGDisplaystring, NULL);
if (!P2BIGDisplay) { P2BIGDisplay=backend_load_bitmap("data/system/000_00.pcx", NULL); }
}
}

if (timermenus==15){
if (backend_key[HM_KEY_ESC]) {
backend_play_sample(back, 255, 128, 1000, 0);
FadeCtr=255; FadeIN=0; FadeOUT=1;
timermenus=0; NumPersonagensEscolhidos=0;
menu_op=1; ApresentacaoMode=1; SelectCharMode=0; ModoHistoria=0;
backend_play_midi(bgm_apresentacao, 1); //bgm
}
if (backend_key[HM_KEY_ALT] && backend_key[HM_KEY_F4]) {sair=1;}

//seleciona o personagem P1
if (P[1].key_RIGHT_pressed==1 && NumPersonagensEscolhidos<2){ SelectCharP1ID++; }
if (P[1].key_LEFT_pressed ==1 && NumPersonagensEscolhidos<2){ SelectCharP1ID--; }
char SelectCharP1Caminho[99];
if (P[1].key_RIGHT_pressed==1 && (strcmp( ChoiceP1,"") ==0)) {
backend_play_sample(cursor, 255, 128, 1000, 0);
if(SelectCharP1ID>Qtde_Personagens_Instalados) SelectCharP1ID=1;
if (SelectCharP1ID==1){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[1]);	}
if (SelectCharP1ID==2){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[2]);	}
if (SelectCharP1ID==3){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[3]);	}
if (SelectCharP1ID==4){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[4]);	}
if (SelectCharP1ID==5){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[5]);	}
if (SelectCharP1ID==6){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[6]);	}
if (SelectCharP1ID==7){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[7]);	}
if (SelectCharP1ID==8){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[8]);	}
P1BIGDisplay = backend_load_bitmap(P1BIGDisplaystring, NULL);
if (!P1BIGDisplay) { P1BIGDisplay=backend_load_bitmap("data/system/000_00.pcx", NULL); }
}
if (P[1].key_LEFT_pressed ==1 && (strcmp( ChoiceP1,"") ==0)) {
backend_play_sample(cursor, 255, 128, 1000, 0);
if(SelectCharP1ID<1) SelectCharP1ID=Qtde_Personagens_Instalados;
if (SelectCharP1ID==8){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[8]);	}
if (SelectCharP1ID==7){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[7]);	}
if (SelectCharP1ID==6){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[6]);	}
if (SelectCharP1ID==5){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[5]);	}
if (SelectCharP1ID==4){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[4]);	}
if (SelectCharP1ID==3){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[3]);	}
if (SelectCharP1ID==2){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[2]);	}
if (SelectCharP1ID==1){ sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[1]);	}
P1BIGDisplay = backend_load_bitmap(P1BIGDisplaystring, NULL);
if (!P1BIGDisplay) { P1BIGDisplay=backend_load_bitmap("data/system/000_00.pcx", NULL); }
}

//seleciona o personagem P2
if (P[2].key_RIGHT_pressed==1 && NumPersonagensEscolhidos<2){ SelectCharP2ID++; }
if (P[2].key_LEFT_pressed ==1 && NumPersonagensEscolhidos<2){ SelectCharP2ID--; }
if (P[2].key_RIGHT_pressed==1 && (strcmp( ChoiceP2,"") ==0)) {
backend_play_sample(cursor, 255, 128, 1000, 0);
if(SelectCharP2ID>Qtde_Personagens_Instalados) SelectCharP2ID=1;
if (SelectCharP2ID==1){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[1]); }
if (SelectCharP2ID==2){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[2]); }
if (SelectCharP2ID==3){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[3]); }
if (SelectCharP2ID==4){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[4]); }
if (SelectCharP2ID==5){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[5]); }
if (SelectCharP2ID==6){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[6]); }
if (SelectCharP2ID==7){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[7]); }
if (SelectCharP2ID==8){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[8]); }
P2BIGDisplay = backend_load_bitmap(P2BIGDisplaystring, NULL);
if (!P2BIGDisplay) { P2BIGDisplay=backend_load_bitmap("data/system/000_00.pcx", NULL); }
}
if (P[2].key_LEFT_pressed ==1 && (strcmp( ChoiceP2,"") ==0)) {
backend_play_sample(cursor, 255, 128, 1000, 0);
if(SelectCharP2ID<1) SelectCharP2ID=Qtde_Personagens_Instalados;
if (SelectCharP2ID==8){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[8]);	}
if (SelectCharP2ID==7){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[7]);	}
if (SelectCharP2ID==6){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[6]); }
if (SelectCharP2ID==5){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[5]);	}
if (SelectCharP2ID==4){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[4]); }
if (SelectCharP2ID==3){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[3]); }
if (SelectCharP2ID==2){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[2]); }
if (SelectCharP2ID==1){ sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", Lista_de_Personagens_Instalados[1]); }
P2BIGDisplay = backend_load_bitmap(P2BIGDisplaystring, NULL);
if (!P2BIGDisplay) { P2BIGDisplay=backend_load_bitmap("data/system/000_00.pcx", NULL); }
}
}

//define nome dos personagens
//P1 name
char SelectCharP1Caminho[99];
if (SelectCharP1ID==1){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[1]); }
if (SelectCharP1ID==2){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[2]); }
if (SelectCharP1ID==3){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[3]); }
if (SelectCharP1ID==4){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[4]); }
if (SelectCharP1ID==5){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[5]); }
if (SelectCharP1ID==6){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[6]); }
if (SelectCharP1ID==7){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[7]); }
if (SelectCharP1ID==8){ sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[8]); }
backend_set_config_file(SelectCharP1Caminho); strcpy(P[1].Name_Display, (char *)backend_get_config_string("Info", "Name", "-"));
//P2 name
char SelectCharP2Caminho[99];
if (SelectCharP2ID==1){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[1]); }
if (SelectCharP2ID==2){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[2]); }
if (SelectCharP2ID==3){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[3]); }
if (SelectCharP2ID==4){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[4]); }
if (SelectCharP2ID==5){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[5]); }
if (SelectCharP2ID==6){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[6]); }
if (SelectCharP2ID==7){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[7]); }
if (SelectCharP2ID==8){ sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[8]); }
backend_set_config_file(SelectCharP2Caminho); strcpy(P[2].Name_Display, (char *)backend_get_config_string("Info", "Name", "-"));

SelectCharTimerAnim++; if (SelectCharTimerAnim>5) { SelectCharTimerAnim=0; } //usado para animar o cursor e elementos da tela
backend_draw_sprite(bufferx, SELECT_CHARS, 0, 0); //bg
if (NumPersonagensEscolhidos<2) {
if (strcmp (IDIOMA,"US")==0){
backend_textprintf_centre_ex(bufferx, font_20, 323, 5, backend_makecol(000,000,000), -1, "Select your Character"); //sombra do texto
backend_textprintf_centre_ex(bufferx, font_20, 320, 2, backend_makecol(255,255,255), -1, "Select your Character"); //texto
}
if (strcmp (IDIOMA,"BR")==0){
backend_textprintf_centre_ex(bufferx, font_20, 323, 5, backend_makecol(000,000,000), -1, "Escolha seu Personagem"); //sombra do texto
backend_textprintf_centre_ex(bufferx, font_20, 320, 2, backend_makecol(255,255,255), -1, "Escolha seu Personagem"); //texto
}
}

//miniaturas
if (NumPersonagensEscolhidos<2) {
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*0), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*1), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*2), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*3), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*4), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*5), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*6), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*7), 400);
if (Qtde_Personagens_Instalados>=1) { backend_draw_sprite(bufferx, MINIsprDisplay[1], 64+(64*0), 400); }
if (Qtde_Personagens_Instalados>=2) { backend_draw_sprite(bufferx, MINIsprDisplay[2], 64+(64*1), 400); }
if (Qtde_Personagens_Instalados>=3) { backend_draw_sprite(bufferx, MINIsprDisplay[3], 64+(64*2), 400); }
if (Qtde_Personagens_Instalados>=4) { backend_draw_sprite(bufferx, MINIsprDisplay[4], 64+(64*3), 400); }
if (Qtde_Personagens_Instalados>=5) { backend_draw_sprite(bufferx, MINIsprDisplay[5], 64+(64*4), 400); }
if (Qtde_Personagens_Instalados>=6) { backend_draw_sprite(bufferx, MINIsprDisplay[6], 64+(64*5), 400); }
if (Qtde_Personagens_Instalados>=7) { backend_draw_sprite(bufferx, MINIsprDisplay[7], 64+(64*6), 400); }
if (Qtde_Personagens_Instalados>=8) { backend_draw_sprite(bufferx, MINIsprDisplay[8], 64+(64*7), 400); }
}

//seleciona o cenario
if (Qtde_Cenarios_Instalados>=1 && NumPersonagensEscolhidos==2) {

//ponteiro gps
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2){
backend_draw_sprite(bufferx, spr_ponteiro, MapCenterX+MapPosX-16, MapCenterY+MapPosY-16);
} //16 pq o ponteiro tem 32x32px

backend_draw_sprite(bufferx, SELECT_BG, 20, 405);
if (strcmp (IDIOMA,"US")==0){
backend_textprintf_centre_ex(bufferx, font_20, 323, 410, backend_makecol(000,000,000), -1, "Background Choice");
backend_textprintf_centre_ex(bufferx, font_20, 320, 407, backend_makecol(255,255,255), -1, "Background Choice");
}
if (strcmp (IDIOMA,"BR")==0){
backend_textprintf_centre_ex(bufferx, font_20, 323, 410, backend_makecol(000,000,000), -1, "Escolha o Cenario");
backend_textprintf_centre_ex(bufferx, font_20, 320, 407, backend_makecol(255,255,255), -1, "Escolha o Cenario");
}

//desenha nome do cenario na tela
backend_set_config_file("SETUP.ini");
char bg_read[25]="";
if (SelectBGID==1) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg1", "")); }
if (SelectBGID==2) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg2", "")); }
if (SelectBGID==3) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg3", "")); }
if (SelectBGID==4) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg4", "")); }
if (SelectBGID==5) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg5", "")); }
if (SelectBGID==6) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg6", "")); }
if (SelectBGID==7) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg7", "")); }
if (SelectBGID==8) { strcpy(bg_read, (char *)backend_get_config_string("BACKGROUNDS", "bg8", "")); }
backend_textprintf_centre_ex(bufferx, font_20, 322, 439, backend_makecol(000,000,000), -1, "%s", bg_read);
backend_textprintf_centre_ex(bufferx, font_20, 320, 437, backend_makecol(255,255,000), -1, "%s", bg_read);
}

//escolha dos personagens
//p1
if (timermenus>=15 && NumPersonagensEscolhidos<2 && (
P[1].key_BT1_pressed==1 || P[1].key_BT2_pressed==1 || P[1].key_BT3_pressed==1 || P[1].key_SELECT_pressed==1 ||
P[1].key_BT4_pressed==1 || P[1].key_BT5_pressed==1 || P[1].key_BT6_pressed==1 || P[1].key_START_pressed==1 )){

if (strcmp( ChoiceP1,"") ==0) { NumPersonagensEscolhidos++; backend_play_sample(choice, 255, 128, 1000, 0); }
if (SelectCharP1ID==1) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[1]); }
if (SelectCharP1ID==2) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[2]); }
if (SelectCharP1ID==3) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[3]); }
if (SelectCharP1ID==4) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[4]); }
if (SelectCharP1ID==5) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[5]); }
if (SelectCharP1ID==6) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[6]); }
if (SelectCharP1ID==7) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[7]); }
if (SelectCharP1ID==8) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[8]); }
//carrega o tipo grafico do personagem
char SelectCharP1Caminho[99];
sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", ChoiceP1);
backend_set_config_file(SelectCharP1Caminho); P[1].Type=backend_get_config_int("Info", "Type", 1);
//verifica se o personagem possui paleta de cores
sprintf(P1_Pallete_string, "data/chars/%s/pallete.pcx", ChoiceP1);
P1_Pallete = backend_load_bitmap(P1_Pallete_string, NULL);
if (!P1_Pallete) { P[1].PossuiPaletaDeCor=0; } else { P[1].PossuiPaletaDeCor=1; }
//define a cor do personagem, se ele tiver paleta de cores
if(P[1].PossuiPaletaDeCor==1){
if(P[1].key_BT1_pressed    ==1) { P[1].DefineCorDaPaleta=0; }
if(P[1].key_BT2_pressed    ==1) { P[1].DefineCorDaPaleta=1; }
if(P[1].key_BT3_pressed    ==1) { P[1].DefineCorDaPaleta=2; }
if(P[1].key_BT4_pressed    ==1) { P[1].DefineCorDaPaleta=3; }
if(P[1].key_BT5_pressed    ==1) { P[1].DefineCorDaPaleta=4; }
if(P[1].key_BT6_pressed    ==1) { P[1].DefineCorDaPaleta=5; }
if(P[1].key_SELECT_pressed ==1) { P[1].DefineCorDaPaleta=6; }
if(P[1].key_START_pressed  ==1) { P[1].DefineCorDaPaleta=7; }
//if(P[1].key_HOLD_pressed   ==1) { P[1].DefineCorDaPaleta=8; } //precisa ser implementado
}

//---
//atualiza tabela de golpes especiais - magias - special

//zera o array dos especiais
for(int indx=0; indx<=9; indx++){
for(int ind=0; ind<=16; ind++){
P[1].Special_Inputs_c[indx][ind]=0;
P[1].Special_Inputs_b[indx][ind]=0;
P[1].Special_Inputs[indx][ind]=0;
}
}

char StrSpecialInput[99];
sprintf(StrSpecialInput, "data/chars/%s/special.ini", ChoiceP1);
backend_set_config_file(StrSpecialInput);
char str[3];
//carrega os inputs dos especiais
for(int ind=0; ind<=9; ind++){
if(ind==0) { sprintf(str, "700"); }
if(ind==1) { sprintf(str, "710"); }
if(ind==2) { sprintf(str, "720"); }
if(ind==3) { sprintf(str, "730"); }
if(ind==4) { sprintf(str, "740"); }
if(ind==5) { sprintf(str, "750"); }
if(ind==6) { sprintf(str, "760"); }
if(ind==7) { sprintf(str, "770"); }
if(ind==8) { sprintf(str, "780"); }
if(ind==9) { sprintf(str, "790"); }
P[1].Special_Inputs_c[ind][1]  = backend_get_config_int(str, "c1" , 0); //0 é neutro
P[1].Special_Inputs_c[ind][2]  = backend_get_config_int(str, "c2" , 0);
P[1].Special_Inputs_c[ind][3]  = backend_get_config_int(str, "c3" , 0);
P[1].Special_Inputs_c[ind][4]  = backend_get_config_int(str, "c4" , 0);
P[1].Special_Inputs_c[ind][5]  = backend_get_config_int(str, "c5" , 0);
P[1].Special_Inputs_c[ind][6]  = backend_get_config_int(str, "c6" , 0);
P[1].Special_Inputs_c[ind][7]  = backend_get_config_int(str, "c7" , 0);
P[1].Special_Inputs_c[ind][8]  = backend_get_config_int(str, "c8" , 0);
P[1].Special_Inputs_c[ind][9]  = backend_get_config_int(str, "c9" , 0);
P[1].Special_Inputs_c[ind][10] = backend_get_config_int(str, "c10", 0);
P[1].Special_Inputs_c[ind][11] = backend_get_config_int(str, "c11", 0);
P[1].Special_Inputs_c[ind][12] = backend_get_config_int(str, "c12", 0);
P[1].Special_Inputs_c[ind][13] = backend_get_config_int(str, "c13", 0);
P[1].Special_Inputs_c[ind][14] = backend_get_config_int(str, "c14", 0);
P[1].Special_Inputs_c[ind][15] = backend_get_config_int(str, "c15", 0);
P[1].Special_Inputs_c[ind][16] = backend_get_config_int(str, "c16", 0);
P[1].Special_Inputs_b[ind][1]  = backend_get_config_int(str, "b1" , 0)*-1; //0 é neutro
P[1].Special_Inputs_b[ind][2]  = backend_get_config_int(str, "b2" , 0)*-1;
P[1].Special_Inputs_b[ind][3]  = backend_get_config_int(str, "b3" , 0)*-1;
P[1].Special_Inputs_b[ind][4]  = backend_get_config_int(str, "b4" , 0)*-1;
P[1].Special_Inputs_b[ind][5]  = backend_get_config_int(str, "b5" , 0)*-1;
P[1].Special_Inputs_b[ind][6]  = backend_get_config_int(str, "b6" , 0)*-1;
P[1].Special_Inputs_b[ind][7]  = backend_get_config_int(str, "b7" , 0)*-1;
P[1].Special_Inputs_b[ind][8]  = backend_get_config_int(str, "b8" , 0)*-1;
P[1].Special_Inputs_b[ind][9]  = backend_get_config_int(str, "b9" , 0)*-1;
P[1].Special_Inputs_b[ind][10] = backend_get_config_int(str, "b10", 0)*-1;
P[1].Special_Inputs_b[ind][11] = backend_get_config_int(str, "b11", 0)*-1;
P[1].Special_Inputs_b[ind][12] = backend_get_config_int(str, "b12", 0)*-1;
P[1].Special_Inputs_b[ind][13] = backend_get_config_int(str, "b13", 0)*-1;
P[1].Special_Inputs_b[ind][14] = backend_get_config_int(str, "b14", 0)*-1;
P[1].Special_Inputs_b[ind][15] = backend_get_config_int(str, "b15", 0)*-1;
P[1].Special_Inputs_b[ind][16] = backend_get_config_int(str, "b16", 0)*-1;
}

//contagem da qtde de comandos e botoes
for(int ind=1; ind<=16; ind++){
if( P[1].Special_Inputs_c[0][ind]!=0 ) { P[1].Special_Inputs_c[0][0]++; }
if( P[1].Special_Inputs_b[0][ind]!=0 ) { P[1].Special_Inputs_b[0][0]++; }
if( P[1].Special_Inputs_c[1][ind]!=0 ) { P[1].Special_Inputs_c[1][0]++; }
if( P[1].Special_Inputs_b[1][ind]!=0 ) { P[1].Special_Inputs_b[1][0]++; }
if( P[1].Special_Inputs_c[2][ind]!=0 ) { P[1].Special_Inputs_c[2][0]++; }
if( P[1].Special_Inputs_b[2][ind]!=0 ) { P[1].Special_Inputs_b[2][0]++; }
if( P[1].Special_Inputs_c[3][ind]!=0 ) { P[1].Special_Inputs_c[3][0]++; }
if( P[1].Special_Inputs_b[3][ind]!=0 ) { P[1].Special_Inputs_b[3][0]++; }
if( P[1].Special_Inputs_c[4][ind]!=0 ) { P[1].Special_Inputs_c[4][0]++; }
if( P[1].Special_Inputs_b[4][ind]!=0 ) { P[1].Special_Inputs_b[4][0]++; }
if( P[1].Special_Inputs_c[5][ind]!=0 ) { P[1].Special_Inputs_c[5][0]++; }
if( P[1].Special_Inputs_b[5][ind]!=0 ) { P[1].Special_Inputs_b[5][0]++; }
if( P[1].Special_Inputs_c[6][ind]!=0 ) { P[1].Special_Inputs_c[6][0]++; }
if( P[1].Special_Inputs_b[6][ind]!=0 ) { P[1].Special_Inputs_b[6][0]++; }
if( P[1].Special_Inputs_c[7][ind]!=0 ) { P[1].Special_Inputs_c[7][0]++; }
if( P[1].Special_Inputs_b[7][ind]!=0 ) { P[1].Special_Inputs_b[7][0]++; }
if( P[1].Special_Inputs_c[8][ind]!=0 ) { P[1].Special_Inputs_c[8][0]++; }
if( P[1].Special_Inputs_b[8][ind]!=0 ) { P[1].Special_Inputs_b[8][0]++; }
if( P[1].Special_Inputs_c[9][ind]!=0 ) { P[1].Special_Inputs_c[9][0]++; }
if( P[1].Special_Inputs_b[9][ind]!=0 ) { P[1].Special_Inputs_b[9][0]++; }
}

//input combinado
for(int indx=0; indx<=9; indx++){
for(int ind=1; ind<=P[1].Special_Inputs_c[indx][0]; ind++){
P[1].Special_Inputs[indx][ind] = P[1].Special_Inputs_c[indx][ind];
}
for(int ind=1; ind<=P[1].Special_Inputs_b[indx][0]; ind++){
P[1].Special_Inputs[indx][ind+P[1].Special_Inputs_c[indx][0]] = P[1].Special_Inputs_b[indx][ind];
}
P[1].Special_Inputs[indx][0]=P[1].Special_Inputs_c[indx][0]+P[1].Special_Inputs_b[indx][0];
}
//---

if (NumPersonagensEscolhidos==2) { timermenus=0; if(ModoHistoria==1){timermenus=15;} }
}
//p2
if (timermenus>=15 && NumPersonagensEscolhidos<2 && (
P[2].key_BT1_pressed==1 || P[2].key_BT2_pressed==1 || P[2].key_BT3_pressed==1 || P[2].key_SELECT_pressed==1 ||
P[2].key_BT4_pressed==1 || P[2].key_BT5_pressed==1 || P[2].key_BT6_pressed==1 || P[2].key_START_pressed==1 )){

if (strcmp( ChoiceP2,"") ==0) { NumPersonagensEscolhidos++; backend_play_sample(choice, 255, 128, 1000, 0); }
if (SelectCharP2ID==1) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[1]); }
if (SelectCharP2ID==2) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[2]); }
if (SelectCharP2ID==3) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[3]); }
if (SelectCharP2ID==4) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[4]); }
if (SelectCharP2ID==5) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[5]); }
if (SelectCharP2ID==6) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[6]); }
if (SelectCharP2ID==7) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[7]); }
if (SelectCharP2ID==8) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[8]); }
//carrega o tipo grafico do personagem
char SelectCharP2Caminho[99];
sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", ChoiceP2);
backend_set_config_file(SelectCharP2Caminho); P[2].Type=backend_get_config_int("Info", "Type", 1);
//verifica se o personagem possui paleta de cores
sprintf(P2_Pallete_string, "data/chars/%s/pallete.pcx", ChoiceP2);
P2_Pallete = backend_load_bitmap(P2_Pallete_string, NULL);
if (!P2_Pallete) { P[2].PossuiPaletaDeCor=0; } else { P[2].PossuiPaletaDeCor=1; }
//define a cor do personagem, se ele tiver paleta de cores
if(P[2].PossuiPaletaDeCor==1){
if(P[2].key_BT1_pressed    ==1) { P[2].DefineCorDaPaleta=0; }
if(P[2].key_BT2_pressed    ==1) { P[2].DefineCorDaPaleta=1; }
if(P[2].key_BT3_pressed    ==1) { P[2].DefineCorDaPaleta=2; }
if(P[2].key_BT4_pressed    ==1) { P[2].DefineCorDaPaleta=3; }
if(P[2].key_BT5_pressed    ==1) { P[2].DefineCorDaPaleta=4; }
if(P[2].key_BT6_pressed    ==1) { P[2].DefineCorDaPaleta=5; }
if(P[2].key_SELECT_pressed ==1) { P[2].DefineCorDaPaleta=6; }
if(P[2].key_START_pressed  ==1) { P[2].DefineCorDaPaleta=7; }
//if(P[2].key_HOLD_pressed   ==1) { P[2].DefineCorDaPaleta=8; } //precisa ser implementado
}

//---
//atualiza tabela de golpes especiais - magias - special

//zera o array dos especiais
for(int indx=0; indx<=9; indx++){
for(int ind=0; ind<=16; ind++){
P[2].Special_Inputs_c[indx][ind]=0;
P[2].Special_Inputs_b[indx][ind]=0;
P[2].Special_Inputs[indx][ind]=0;
}
}

char StrSpecialInput[99];
sprintf(StrSpecialInput, "data/chars/%s/special.ini", ChoiceP2);
backend_set_config_file(StrSpecialInput);
char str[3];
//carrega os inputs dos especiais
for(int ind=0; ind<=9; ind++){
if(ind==0) { sprintf(str, "700"); }
if(ind==1) { sprintf(str, "710"); }
if(ind==2) { sprintf(str, "720"); }
if(ind==3) { sprintf(str, "730"); }
if(ind==4) { sprintf(str, "740"); }
if(ind==5) { sprintf(str, "750"); }
if(ind==6) { sprintf(str, "760"); }
if(ind==7) { sprintf(str, "770"); }
if(ind==8) { sprintf(str, "780"); }
if(ind==9) { sprintf(str, "790"); }
P[2].Special_Inputs_c[ind][1]  = backend_get_config_int(str, "c1" , 0); //0 é neutro
P[2].Special_Inputs_c[ind][2]  = backend_get_config_int(str, "c2" , 0);
P[2].Special_Inputs_c[ind][3]  = backend_get_config_int(str, "c3" , 0);
P[2].Special_Inputs_c[ind][4]  = backend_get_config_int(str, "c4" , 0);
P[2].Special_Inputs_c[ind][5]  = backend_get_config_int(str, "c5" , 0);
P[2].Special_Inputs_c[ind][6]  = backend_get_config_int(str, "c6" , 0);
P[2].Special_Inputs_c[ind][7]  = backend_get_config_int(str, "c7" , 0);
P[2].Special_Inputs_c[ind][8]  = backend_get_config_int(str, "c8" , 0);
P[2].Special_Inputs_c[ind][9]  = backend_get_config_int(str, "c9" , 0);
P[2].Special_Inputs_c[ind][10] = backend_get_config_int(str, "c10", 0);
P[2].Special_Inputs_c[ind][11] = backend_get_config_int(str, "c11", 0);
P[2].Special_Inputs_c[ind][12] = backend_get_config_int(str, "c12", 0);
P[2].Special_Inputs_c[ind][13] = backend_get_config_int(str, "c13", 0);
P[2].Special_Inputs_c[ind][14] = backend_get_config_int(str, "c14", 0);
P[2].Special_Inputs_c[ind][15] = backend_get_config_int(str, "c15", 0);
P[2].Special_Inputs_c[ind][16] = backend_get_config_int(str, "c16", 0);
P[2].Special_Inputs_b[ind][1]  = backend_get_config_int(str, "b1" , 0)*-1; //0 é neutro
P[2].Special_Inputs_b[ind][2]  = backend_get_config_int(str, "b2" , 0)*-1;
P[2].Special_Inputs_b[ind][3]  = backend_get_config_int(str, "b3" , 0)*-1;
P[2].Special_Inputs_b[ind][4]  = backend_get_config_int(str, "b4" , 0)*-1;
P[2].Special_Inputs_b[ind][5]  = backend_get_config_int(str, "b5" , 0)*-1;
P[2].Special_Inputs_b[ind][6]  = backend_get_config_int(str, "b6" , 0)*-1;
P[2].Special_Inputs_b[ind][7]  = backend_get_config_int(str, "b7" , 0)*-1;
P[2].Special_Inputs_b[ind][8]  = backend_get_config_int(str, "b8" , 0)*-1;
P[2].Special_Inputs_b[ind][9]  = backend_get_config_int(str, "b9" , 0)*-1;
P[2].Special_Inputs_b[ind][10] = backend_get_config_int(str, "b10", 0)*-1;
P[2].Special_Inputs_b[ind][11] = backend_get_config_int(str, "b11", 0)*-1;
P[2].Special_Inputs_b[ind][12] = backend_get_config_int(str, "b12", 0)*-1;
P[2].Special_Inputs_b[ind][13] = backend_get_config_int(str, "b13", 0)*-1;
P[2].Special_Inputs_b[ind][14] = backend_get_config_int(str, "b14", 0)*-1;
P[2].Special_Inputs_b[ind][15] = backend_get_config_int(str, "b15", 0)*-1;
P[2].Special_Inputs_b[ind][16] = backend_get_config_int(str, "b16", 0)*-1;
}

//contagem da qtde de comandos e botoes
for(int ind=1; ind<=16; ind++){
if( P[2].Special_Inputs_c[0][ind]!=0 ) { P[2].Special_Inputs_c[0][0]++; }
if( P[2].Special_Inputs_b[0][ind]!=0 ) { P[2].Special_Inputs_b[0][0]++; }
if( P[2].Special_Inputs_c[1][ind]!=0 ) { P[2].Special_Inputs_c[1][0]++; }
if( P[2].Special_Inputs_b[1][ind]!=0 ) { P[2].Special_Inputs_b[1][0]++; }
if( P[2].Special_Inputs_c[2][ind]!=0 ) { P[2].Special_Inputs_c[2][0]++; }
if( P[2].Special_Inputs_b[2][ind]!=0 ) { P[2].Special_Inputs_b[2][0]++; }
if( P[2].Special_Inputs_c[3][ind]!=0 ) { P[2].Special_Inputs_c[3][0]++; }
if( P[2].Special_Inputs_b[3][ind]!=0 ) { P[2].Special_Inputs_b[3][0]++; }
if( P[2].Special_Inputs_c[4][ind]!=0 ) { P[2].Special_Inputs_c[4][0]++; }
if( P[2].Special_Inputs_b[4][ind]!=0 ) { P[2].Special_Inputs_b[4][0]++; }
if( P[2].Special_Inputs_c[5][ind]!=0 ) { P[2].Special_Inputs_c[5][0]++; }
if( P[2].Special_Inputs_b[5][ind]!=0 ) { P[2].Special_Inputs_b[5][0]++; }
if( P[2].Special_Inputs_c[6][ind]!=0 ) { P[2].Special_Inputs_c[6][0]++; }
if( P[2].Special_Inputs_b[6][ind]!=0 ) { P[2].Special_Inputs_b[6][0]++; }
if( P[2].Special_Inputs_c[7][ind]!=0 ) { P[2].Special_Inputs_c[7][0]++; }
if( P[2].Special_Inputs_b[7][ind]!=0 ) { P[2].Special_Inputs_b[7][0]++; }
if( P[2].Special_Inputs_c[8][ind]!=0 ) { P[2].Special_Inputs_c[8][0]++; }
if( P[2].Special_Inputs_b[8][ind]!=0 ) { P[2].Special_Inputs_b[8][0]++; }
if( P[2].Special_Inputs_c[9][ind]!=0 ) { P[2].Special_Inputs_c[9][0]++; }
if( P[2].Special_Inputs_b[9][ind]!=0 ) { P[2].Special_Inputs_b[9][0]++; }
}

//input combinado
for(int indx=0; indx<=9; indx++){
for(int ind=1; ind<=P[2].Special_Inputs_c[indx][0]; ind++){
P[2].Special_Inputs[indx][ind] = P[2].Special_Inputs_c[indx][ind];
}
for(int ind=1; ind<=P[2].Special_Inputs_b[indx][0]; ind++){
P[2].Special_Inputs[indx][ind+P[2].Special_Inputs_c[indx][0]] = P[2].Special_Inputs_b[indx][ind];
}
P[2].Special_Inputs[indx][0]=P[2].Special_Inputs_c[indx][0]+P[2].Special_Inputs_b[indx][0];
}
//---

if (NumPersonagensEscolhidos==2) { timermenus=0; }
}

//atualiza gps do mapa
if (Qtde_Cenarios_Instalados>=1 && timermenus==0){
char bg_choice_string[25];
if (SelectBGID==1) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[1]); }
if (SelectBGID==2) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[2]); }
if (SelectBGID==3) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[3]); }
if (SelectBGID==4) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[4]); }
if (SelectBGID==5) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[5]); }
if (SelectBGID==6) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[6]); }
if (SelectBGID==7) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[7]); }
if (SelectBGID==8) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[8]); }
backend_set_config_file(bg_choice_string);
MapPosX=backend_get_config_int ( "DATA", "MapPosX", 0 );
MapPosY=backend_get_config_int ( "DATA", "MapPosY", 0 );
}

//cursor p1
if (strcmp( ChoiceP1,"") ==0) {
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==1) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*0), 400); }
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==2) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*1), 400); }
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==3) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*2), 400); }
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==4) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*3), 400); }
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==5) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*4), 400); }
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==6) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*5), 400); }
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==7) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*6), 400); }
if (SelectCharTimerAnim>=0 && SelectCharTimerAnim<=2 && SelectCharP1ID==8) { backend_draw_sprite(bufferx, spr_p1_cursor, 64+(64*7), 400); }
}
//cursor p2
if (strcmp( ChoiceP2,"") ==0) {
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==1) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*0), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==2) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*1), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==3) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*2), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==4) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*3), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==5) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*4), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==6) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*5), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==7) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*6), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==8) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*7), 400); }
if (SelectCharTimerAnim>=3 && SelectCharTimerAnim<=5 && SelectCharP2ID==9) { backend_draw_sprite(bufferx, spr_p2_cursor, 64+(64*8), 400); }
}
//marcadores de selecao
if (strcmp( ChoiceP1,"") ==0) { backend_draw_sprite(bufferx, sel_mark_p1, 64+(64*(SelectCharP1ID-1)), 400); }
if (strcmp( ChoiceP2,"") ==0) { backend_draw_sprite(bufferx, sel_mark_p2, -32+64+(64*(SelectCharP2ID)), 449); }

//BIG DISPLAYs
//P1
masked_backend_stretch_blit(P1BIGDisplay, bufferx, 0, 0, 128, 128,   5, 140, 256, 256);
//P2
if (strcmp( ChoiceP2,"-P2CPU-") !=0) {
backend_clear_to_color(P2BIGDisplayInv, backend_makecol(255, 0, 255)); backend_draw_sprite_h_flip(P2BIGDisplayInv, P2BIGDisplay, 0, 0);
masked_backend_stretch_blit(P2BIGDisplayInv, bufferx, 0, 0, 128, 128, 379, 140, 256, 256);
}
//nomes
backend_textprintf_ex( bufferx, font_10,  12, 382, backend_makecol(000,000,000), -1, "%s", P[1].Name_Display);
backend_textprintf_ex( bufferx, font_10,  10, 380, backend_makecol(255,255,255), -1, "%s", P[1].Name_Display);
if (strcmp( ChoiceP2,"-P2CPU-") !=0) {
backend_textprintf_right_ex( bufferx, font_10, 632, 382, backend_makecol(000,000,000), -1, "%s", P[2].Name_Display);
backend_textprintf_right_ex( bufferx, font_10, 630, 380, backend_makecol(255,255,255), -1, "%s", P[2].Name_Display);
}

//escolha do cenario
if (NumPersonagensEscolhidos==2 && timermenus>=15) {
int AtualizaGPS=0;
if (((P[1].key_RIGHT_pressed==1) || (P[2].key_RIGHT_pressed==1)) && SelectBGID<Qtde_Cenarios_Instalados) {
SelectBGID++; backend_play_sample(cursor, 255, 128, 1000, 0); AtualizaGPS=1;
}
if (((P[1].key_LEFT_pressed ==1) || (P[2].key_LEFT_pressed ==1)) && SelectBGID>1) {
SelectBGID--; backend_play_sample(cursor, 255, 128, 1000, 0); AtualizaGPS=1;
}
if (AtualizaGPS==1){
AtualizaGPS=0;
char bg_choice_string[25];
if (SelectBGID==1) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[1]); }
if (SelectBGID==2) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[2]); }
if (SelectBGID==3) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[3]); }
if (SelectBGID==4) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[4]); }
if (SelectBGID==5) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[5]); }
if (SelectBGID==6) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[6]); }
if (SelectBGID==7) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[7]); }
if (SelectBGID==8) { sprintf(bg_choice_string, "backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[8]); }
backend_set_config_file(bg_choice_string);
MapPosX=backend_get_config_int ( "DATA", "MapPosX", 0 );
MapPosY=backend_get_config_int ( "DATA", "MapPosY", 0 );
}
if (strcmp( ChoiceP2,"-P2CPU-") ==0) { //estamos no modo arcade
TelaDeVersusTimer=0;
strcpy(P[1].Name,ChoiceP1);
if(Estagio_Atual==1){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[1]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[1]); }
if(Estagio_Atual==2){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[2]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[2]); }
if(Estagio_Atual==3){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[3]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[3]); }
if(Estagio_Atual==4){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[4]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[4]); }
if(Estagio_Atual==5){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[5]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[5]); }
if(Estagio_Atual==6){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[6]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[6]); }
if(Estagio_Atual==7){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[7]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[7]); }
if(Estagio_Atual==8){ strcpy(P[2].Name,Lista_de_Personagens_ArcadeMode[8]); strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[8]); }
strcpy(ChoiceP1,"");
strcpy(ChoiceP2,"");
timermenus=0; NumPersonagensEscolhidos=0;
menu_op=1; ModoMapa=1; SelectCharMode=0;
}

if ( strcmp( ChoiceBG,"") ==0 &&
(P[1].key_BT1_pressed==1 || P[1].key_BT2_pressed==1 || P[1].key_BT3_pressed==1 ||
P[1].key_BT4_pressed==1 || P[1].key_BT5_pressed==1 || P[1].key_BT6_pressed==1 || P[1].key_START_pressed==1 ||
P[2].key_BT1_pressed==1 || P[2].key_BT2_pressed==1 || P[2].key_BT3_pressed==1 ||
P[2].key_BT4_pressed==1 || P[2].key_BT5_pressed==1 || P[2].key_BT6_pressed==1 || P[2].key_START_pressed==1) ){
backend_play_sample(choice, 255, 128, 1000, 0);
if (SelectBGID==1) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[1]); }
if (SelectBGID==2) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[2]); }
if (SelectBGID==3) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[3]); }
if (SelectBGID==4) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[4]); }
if (SelectBGID==5) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[5]); }
if (SelectBGID==6) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[6]); }
if (SelectBGID==7) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[7]); }
if (SelectBGID==8) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[8]); }

//posiciona os players

//cenario, atribuicao
for(int ind=1;ind<=8;ind++){
if(SelectBGID==ind){
// Note: bitmap dimensions are immutable; use backend_blit to copy the data
backend_blit(bg_hamoopi[ind], bg_test, 0, 0, 0, 0, backend_bitmap_width(bg_hamoopi[ind]), backend_bitmap_height(bg_hamoopi[ind]));
}
}

//posicao dos players
P[1].x=backend_bitmap_width(bg_test)/2-80;
P[2].x=backend_bitmap_width(bg_test)/2+80;
AlturaPiso=backend_bitmap_height(bg_test)-20;
P[1].y=AlturaPiso;
P[2].y=AlturaPiso;
P[1].State=100; P[2].State=100; //define estado inicial
P[1].Lado=1; P[2].Lado=-1;
P[1].Energy=1000; P[2].Energy=1000;
P[1].EnergyRedBar=1000; P[2].EnergyRedBar=1000;
P[1].Color=-1; P[2].Color=-1;
P[1].Visible=1; P[2].Visible=1;
P[1].RoomLimit=1; P[2].RoomLimit=1;

///SAIR PARA A PROXIMA TELA///
if (strcmp( ChoiceP2,"-P2CPU-") !=0) { //estamos no modo versus
TelaDeVersusTimer=0;
strcpy(P[1].Name,ChoiceP1);
strcpy(P[2].Name,ChoiceP2);
strcpy(ChoiceP1,"");
strcpy(ChoiceP2,"");
timermenus=0; NumPersonagensEscolhidos=0;
menu_op=1; TelaDeVersus=1; SelectCharMode=0;
}
}
}

backend_stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

/////////////////////////////////////////////////////////////////////////////
// MODO MAPA (ARCADE) -------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (ModoMapa==1){
if(timermenus==0) { backend_play_midi(bgm_versus_mode, 0); } //bgm
if (backend_key[HM_KEY_ESC]) {
backend_play_sample(back, 255, 128, 1000, 0);
timermenus=0; menu_op=1; ModoMapa=0; SelectCharMode=1; ModoHistoria=1;
strcpy(ChoiceP1,""); strcpy(ChoiceP2,"-P2CPU-"); NumPersonagensEscolhidos=1; SelectCharTimerAnim=0;
backend_play_midi(bgm_select_screen, 1); //bgm
}

ModoMapaTimerAnim++; if (ModoMapaTimerAnim>5) { ModoMapaTimerAnim=0; } //usado para animar elementos da tela

//define qual imagem mostrar para o P2
sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.pcx", P[2].Name);
P2BIGDisplay = backend_load_bitmap(P2BIGDisplaystring, NULL);
if (!P2BIGDisplay) { P2BIGDisplay=backend_load_bitmap("data/system/000_00.pcx", NULL); }

backend_draw_sprite(bufferx, SELECT_CHARS, 0, 0); //bg
backend_textprintf_centre_ex(bufferx, font_20, 323, 5, backend_makecol(000,000,000), -1, "Proximo Oponente");
backend_textprintf_centre_ex(bufferx, font_20, 320, 2, backend_makecol(255,255,255), -1, "Proximo Oponente");
//miniaturas
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*0), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*1), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*2), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*3), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*4), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*5), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*6), 400);
backend_draw_sprite(bufferx, spr_cursor_vazio, 64+(64*7), 400);
if (strcmp(Lista_de_Personagens_ArcadeMode[1],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[1], 64+(64*0), 400); }
if (strcmp(Lista_de_Personagens_ArcadeMode[2],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[2], 64+(64*1), 400); }
if (strcmp(Lista_de_Personagens_ArcadeMode[3],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[3], 64+(64*2), 400); }
if (strcmp(Lista_de_Personagens_ArcadeMode[4],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[4], 64+(64*3), 400); }
if (strcmp(Lista_de_Personagens_ArcadeMode[5],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[5], 64+(64*4), 400); }
if (strcmp(Lista_de_Personagens_ArcadeMode[6],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[6], 64+(64*5), 400); }
if (strcmp(Lista_de_Personagens_ArcadeMode[7],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[7], 64+(64*6), 400); }
if (strcmp(Lista_de_Personagens_ArcadeMode[8],"") !=0) { backend_draw_sprite(bufferx, MINIsprDisplayArcadeMode[8], 64+(64*7), 400); }

//A animacao [spr_cursor_historia] esta desligada no momento
//if (ModoMapaTimerAnim>=0 && ModoMapaTimerAnim<=4){
if (Estagio_Atual==1){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*0), 400); }
if (Estagio_Atual==2){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*1), 400); }
if (Estagio_Atual==3){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*2), 400); }
if (Estagio_Atual==4){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*3), 400); }
if (Estagio_Atual==5){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*4), 400); }
if (Estagio_Atual==6){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*5), 400); }
if (Estagio_Atual==7){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*6), 400); }
if (Estagio_Atual==8){ backend_draw_sprite(bufferx, spr_cursor_historia, 64+(64*7), 400); }
//}

//desenha gps do mapa
if (timermenus==0){
char bg_choice_string[25];
sprintf(bg_choice_string, "backgrounds/%s/config.ini", ChoiceBG);
backend_set_config_file(bg_choice_string);
MapPosX=backend_get_config_int ( "DATA", "MapPosX", 0 );
MapPosY=backend_get_config_int ( "DATA", "MapPosY", 0 );
}
if (ModoMapaTimerAnim>=0 && ModoMapaTimerAnim<=2){
backend_draw_sprite(bufferx, spr_ponteiro, MapCenterX+MapPosX-16, MapCenterY+MapPosY-16); //16 pq o ponteiro tem 32x32px
}

//P1
masked_backend_stretch_blit(P1BIGDisplay, bufferx, 0, 0, 128, 128,   5, 140, 256, 256);
//P2
if (strcmp( ChoiceP2,"-P2CPU-") !=0) {
backend_clear_to_color(P2BIGDisplayInv, backend_makecol(255, 0, 255)); backend_draw_sprite_h_flip(P2BIGDisplayInv, P2BIGDisplay, 0, 0);
masked_backend_stretch_blit(P2BIGDisplayInv, bufferx, 0, 0, 128, 128, 379, 140, 256, 256);
}

backend_stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

/////////////////////////////////////////////////////////////////////////////
// TELA DE VERSUS -----------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (TelaDeVersus==1){
if(timermenus==0) { backend_play_midi(bgm_versus_mode, 0); } //bgm
int iniciaRound=0;
if (backend_key[HM_KEY_ESC]) {
backend_play_sample(back, 255, 128, 1000, 0);
timermenus=0; SelectCharMode=1; TelaDeVersus=0; if( ModoHistoria==0 ){ strcpy( ChoiceBG,""); }
backend_play_midi(bgm_select_screen, 1); //bgm
}

TelaDeVersusTimer++;

int numtemp=57;

if ((P[1].key_START_pressed==1 || P[2].key_START_pressed==1) && timermenus>=15) {
TelaDeVersusTimer=350-numtemp;
zeraListaDeInputs();
desabilita_players=1;
}

if (TelaDeVersusTimer==350-numtemp){ FadeIN=1; FadeOUT=0; AnimTransTimer=0; }
if (TelaDeVersusTimer>350){ iniciaRound=1; desabilita_players=0; }

if(iniciaRound==1){
iniciaRound=0;
timermenus=0; TelaDeVersus=0; GamePlayMode=1; RoundAtual=1; zeraListaDeInputs(); LOAD_PLAYERS();
//carrega dados
backend_set_config_file("SETUP.ini");
RoundTotal = backend_get_config_int ( "CONFIG", "rounds", 3 );
RoundTime  = backend_get_config_int ( "CONFIG", "time", 99 ); RoundTime=RoundTime*60+59;
P[1].Energy=backend_get_config_int ( "CONFIG", "P1_Energy", 1000 );
P[2].Energy=backend_get_config_int ( "CONFIG", "P2_Energy", 1000 );
P[1].Special=backend_get_config_int ( "CONFIG", "P1_Special", 1000 );
P[2].Special=backend_get_config_int ( "CONFIG", "P2_Special", 1000 );
}

//bg
backend_draw_sprite(bufferx, VS_SCREEN, 0, 0);
//P1
masked_backend_stretch_blit(P1BIGDisplay, bufferx, 0, 0, 128, 128,   5, 140, 256, 256);
//P2
backend_clear_to_color(P2BIGDisplayInv, backend_makecol(255, 0, 255)); backend_draw_sprite_h_flip(P2BIGDisplayInv, P2BIGDisplay, 0, 0);
masked_backend_stretch_blit(P2BIGDisplayInv, bufferx, 0, 0, 128, 128, 379, 140, 256, 256);
//VS
backend_draw_sprite(bufferx, vs_icon, 195, 20);
//informacoes
//sombra
backend_textprintf_centre_ex(bufferx, font_debug, 152,  405, backend_makecol(000,000,000), -1, "P1 WINS: %i", P[1].Wins);
backend_textprintf_centre_ex(bufferx, font_debug, 152,  420, backend_makecol(000,000,000), -1, "P1 LOSES: %i", P[1].Loses);
backend_textprintf_centre_ex(bufferx, font_debug, 152,  435, backend_makecol(000,000,000), -1, "P1 DRAWS: %i", P[1].Draws);
backend_textprintf_centre_ex(bufferx, font_debug, 152,  450, backend_makecol(000,000,000), -1, "P1 PERFECTS: %i", P[1].Perfects);
backend_textprintf_centre_ex(bufferx, font_debug, 492,  405, backend_makecol(000,000,000), -1, "P2 WINS: %i", P[2].Wins);
backend_textprintf_centre_ex(bufferx, font_debug, 492,  420, backend_makecol(000,000,000), -1, "P2 LOSES: %i", P[2].Loses);
backend_textprintf_centre_ex(bufferx, font_debug, 492,  435, backend_makecol(000,000,000), -1, "P2 DRAWS: %i", P[2].Draws);
backend_textprintf_centre_ex(bufferx, font_debug, 492,  450, backend_makecol(000,000,000), -1, "P2 PERFECTS: %i", P[2].Perfects);
//texto
backend_textprintf_centre_ex(bufferx, font_debug, 150,  403, backend_makecol(255,255,255), -1, "P1 WINS: %i", P[1].Wins);
backend_textprintf_centre_ex(bufferx, font_debug, 150,  418, backend_makecol(255,255,255), -1, "P1 LOSES: %i", P[1].Loses);
backend_textprintf_centre_ex(bufferx, font_debug, 150,  433, backend_makecol(255,255,255), -1, "P1 DRAWS: %i", P[1].Draws);
backend_textprintf_centre_ex(bufferx, font_debug, 150,  448, backend_makecol(255,255,255), -1, "P1 PERFECTS: %i", P[1].Perfects);
backend_textprintf_centre_ex(bufferx, font_debug, 490,  403, backend_makecol(255,255,255), -1, "P2 WINS: %i", P[2].Wins);
backend_textprintf_centre_ex(bufferx, font_debug, 490,  418, backend_makecol(255,255,255), -1, "P2 LOSES: %i", P[2].Loses);
backend_textprintf_centre_ex(bufferx, font_debug, 490,  433, backend_makecol(255,255,255), -1, "P2 DRAWS: %i", P[2].Draws);
backend_textprintf_centre_ex(bufferx, font_debug, 490,  448, backend_makecol(255,255,255), -1, "P2 PERFECTS: %i", P[2].Perfects);

backend_stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

/////////////////////////////////////////////////////////////////////////////
// GAME PLAY ----------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

if (GamePlayMode==1){

//inicio de round
if (timer_rounds==0) {
desabilita_players=1; FadeCtr=255; FadeIN=0; FadeOUT=1;
//P1 miniatura da foto ingame
char P1_1s[25]="";
sprintf(P1_1s, "data/chars/%s/000_01.pcx", P[1].Name);
P1_1 = backend_load_bitmap(P1_1s, NULL);
if (!P1_1) { P1_1=backend_load_bitmap("data/system/000_01.pcx", NULL); }
//P2 miniatura da foto ingame
char P2_1s[25]="";
sprintf(P2_1s, "data/chars/%s/000_01.pcx", P[2].Name);
P2_1 = backend_load_bitmap(P2_1s, NULL);
if (!P2_1) { P2_1=backend_load_bitmap("data/system/000_01.pcx", NULL); }
}

//timer_rounds é um contador de frames crescente utilizado em animacoes
timer_rounds++;
if (timer_rounds>=250) { desabilita_players=0; } else { RoundTime++; }

//final de round //RoundTime é um contador de frames decrescente utilizado pelo relogio da luta
if(RoundTime==60) { RoundTime=0; } //segundo zero nao conta
if (RoundTime==0) {
desabilita_players=1;
if(timer_final_de_rounds==0){ zeraListaDeInputs(); }
timer_final_de_rounds++;
}

//interrompe o relogio da luta em caso de KO
if(P[1].Energy==0 || P[2].Energy==0){ RoundTime++; timer_final_de_rounds++; desabilita_players=1; zeraListaDeInputs(); }
//SlowDown no final do Round Apos o hit que causou o KO
if(EndRoundSlowDown<60){
if(EndRoundSlowDown==1){EndRoundSlowDown=15;} //ajuste do valor definido na hora do hit. ref Mov 570
if(timer_final_de_rounds<=50){ EndRoundSlowDown+=0.2;  }
if(timer_final_de_rounds >50){ EndRoundSlowDown+=1 ;  }
if(EndRoundSlowDown>60) { EndRoundSlowDown=60; }
Ctrl_FPS=floor(EndRoundSlowDown);
backend_install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS));
}

if (timer_final_de_rounds>=EndRoundT) {
//reinicia rounds ou sai da luta
RoundAtual++;

//sair da luta
int sairDaLuta=0;
if (RoundAtual>RoundTotal) { sairDaLuta=1; }
for(int ind=1;ind<=2;ind++){
if (P[ind].Round_Wins>=1 && RoundTotal==1) { sairDaLuta=1; }
if (P[ind].Round_Wins>=2 && RoundTotal==2) { sairDaLuta=1; }
if (P[ind].Round_Wins>=2 && RoundTotal==3) { sairDaLuta=1; }
if (P[ind].Round_Wins>=3 && RoundTotal==4) { sairDaLuta=1; }
if (P[ind].Round_Wins>=3 && RoundTotal==5) { sairDaLuta=1; }
}
if (RoundAtual>RoundTotal) { sairDaLuta=1; }

if(sairDaLuta==1){
sairDaLuta=0;
desabilita_players=0; timermenus=0; timer_rounds=0; timer_final_de_rounds=0; SelectCharMode=1; GamePlayMode=0;
if( ModoHistoria==0 ){ strcpy( ChoiceBG,""); }
if ( P[1].Round_Wins >P[2].Round_Wins ) { P[1].Wins++; P[2].Loses++; }
if ( P[1].Round_Wins <P[2].Round_Wins ) { P[2].Wins++; P[1].Loses++; }
if ( P[1].Round_Wins==P[2].Round_Wins ) { P[1].Draws++; P[2].Draws++; }
P[1].Round_Wins=0; P[2].Round_Wins=0;
backend_play_midi(bgm_select_screen, 1); //bgm
timer_rounds=0;
timer_final_de_rounds=0;
backend_set_config_file("SETUP.ini"); RoundTime  = backend_get_config_int ("CONFIG", "time", 99 ); RoundTime=RoundTime*60+59;
//desliga as fireballs
Fireball[1].Ativa = 0;
Fireball[2].Ativa = 0;
P[1].QtdeMagias = 0;
P[2].QtdeMagias = 0;
//posicao dos players
P[1].x=backend_bitmap_width(bg_test)/2-80;
P[2].x=backend_bitmap_width(bg_test)/2+80;
AlturaPiso=backend_bitmap_height(bg_test)-20;
P[1].y=AlturaPiso;
P[2].y=AlturaPiso;
MeioDaTela=(P[1].x+P[2].x)/2;
//define estado inicial
P[1].Lado=1; P[2].Lado=-1;
P[1].Energy=1000; P[2].Energy=1000;
P[1].EnergyRedBar=1000; P[2].EnergyRedBar=1000;
P[1].Color=-1; P[2].Color=-1;
P[1].Visible=1; P[2].Visible=1;
P[1].RoomLimit=1; P[2].RoomLimit=1;
P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1();
P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2();
}

/*reinicia a luta*/
timer_rounds=0;
timer_final_de_rounds=0;
backend_set_config_file("SETUP.ini"); RoundTime  = backend_get_config_int ("CONFIG", "time", 99 ); RoundTime=RoundTime*60+59;
//desliga as fireballs
Fireball[1].Ativa = 0;
Fireball[2].Ativa = 0;
P[1].QtdeMagias = 0;
P[2].QtdeMagias = 0;
//posicao dos players
P[1].x=backend_bitmap_width(bg_test)/2-80;
P[2].x=backend_bitmap_width(bg_test)/2+80;
AlturaPiso=backend_bitmap_height(bg_test)-20;
P[1].y=AlturaPiso;
P[2].y=AlturaPiso;
MeioDaTela=(P[1].x+P[2].x)/2;
//define estado inicial
P[1].Lado=1; P[2].Lado=-1;
P[1].Energy=1000; P[2].Energy=1000;
P[1].EnergyRedBar=1000; P[2].EnergyRedBar=1000;
P[1].Color=-1; P[2].Color=-1;
P[1].Visible=1; P[2].Visible=1;
P[1].RoomLimit=1; P[2].RoomLimit=1;
P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1();
P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2();
}

/*TECLAS DE SISTEMA*/
if (timermenus==15){
if (backend_key[HM_KEY_ESC]) {
backend_play_sample(back, 255, 128, 1000, 0);
Ctrl_FPS=60; backend_install_int_ex(tempo, BPS_TO_TIMER(60));
desabilita_players=0; timermenus=0; timer_rounds=0; timer_final_de_rounds=0; SelectCharMode=1; GamePlayMode=0;
if( ModoHistoria==0 ){ strcpy( ChoiceBG,""); }
backend_play_midi(bgm_select_screen, 1); //bgm
timer_rounds=0;
timer_final_de_rounds=0;
backend_set_config_file("SETUP.ini"); RoundTime  = backend_get_config_int ("CONFIG", "time", 99 ); RoundTime=RoundTime*60+59;
//desliga as fireballs
Fireball[1].Ativa = 0;
Fireball[2].Ativa = 0;
P[1].QtdeMagias = 0;
P[2].QtdeMagias = 0;
//posicao dos players
P[1].x=backend_bitmap_width(bg_test)/2-80;
P[2].x=backend_bitmap_width(bg_test)/2+80;
AlturaPiso=backend_bitmap_height(bg_test)-20;
P[1].y=AlturaPiso;
P[2].y=AlturaPiso;
//define estado inicial
P[1].Lado=1; P[2].Lado=-1;
P[1].Energy=1000; P[2].Energy=1000;
P[1].EnergyRedBar=1000; P[2].EnergyRedBar=1000;
P[1].Color=-1; P[2].Color=-1;
P[1].Visible=1; P[2].Visible=1;
P[1].RoomLimit=1; P[2].RoomLimit=1;
P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1();
P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2();
}
if (backend_key[HM_KEY_ALT] && backend_key[HM_KEY_F4]) {sair=1;}
if ( key_F1_status==1 && Draw_Debug==0) { Draw_Debug=1; } else if ( key_F1_status==1 && Draw_Debug==1) { Draw_Debug=0; }
if ( key_F2_status==1 && Draw_Box==0) { Draw_Box=1; } else if ( key_F2_status==1 && Draw_Box==1) { Draw_Box=0; }
if ( key_F3_status==1 && Draw_Input==0) { Draw_Input=1; } else if ( key_F3_status==1 && Draw_Input==1) { Draw_Input=0; }
if ( key_F4_status==1 && op_ShowFrameData==0) { op_ShowFrameData=1; } else if ( key_F4_status==1 && op_ShowFrameData==1) { op_ShowFrameData=0; }
if ( backend_key[HM_KEY_F5 ] ) { P[1].Energy+=-10; P[1].Special+=-10; }
if ( backend_key[HM_KEY_F6 ] ) { P[1].Energy+= 10; P[1].Special+= 10; }
if ( backend_key[HM_KEY_F7 ] ) { P[2].Energy+=-10; P[2].Special+=-10; }
if ( backend_key[HM_KEY_F8 ] ) { P[2].Energy+= 10; P[2].Special+= 10; }
if ( backend_key[HM_KEY_F9 ] ) { Ctrl_FPS= 1; backend_install_int_ex(tempo, BPS_TO_TIMER( 1)); }
if ( backend_key[HM_KEY_F10] ) { Ctrl_FPS+=-1; if (Ctrl_FPS<1 ) { Ctrl_FPS= 1; } backend_install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS)); }
if ( backend_key[HM_KEY_F11] ) { Ctrl_FPS+=+1; if (Ctrl_FPS>60) { Ctrl_FPS=60; } backend_install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS)); }
if ( backend_key[HM_KEY_F12] ) { Ctrl_FPS=60; backend_install_int_ex(tempo, BPS_TO_TIMER(60)); }
}

if (P[1].Special<0) { P[1].Special=0; } if (P[1].Special>1000) { P[1].Special=1000; }
if (P[2].Special<0) { P[2].Special=0; } if (P[2].Special>1000) { P[2].Special=1000; }
if (P[1].Energy<0) { P[1].Energy=0; } if (P[1].Energy>1000) { P[1].Energy=1000; }
if (P[2].Energy<0) { P[2].Energy=0; } if (P[2].Energy>1000) { P[2].Energy=1000; }

/*COLISAO*/
Checar_Colisao();
Aplicar_HIT();

//controle dos especiais
for(int ind=1; ind<=2; ind++){
P[ind].PodeTestarEspecial=0;
if(
P[ind].key_LEFT_pressed==1 ||
P[ind].key_RIGHT_pressed==1 ||
P[ind].key_UP_pressed==1 ||
P[ind].key_DOWN_pressed==1 ||
P[ind].key_BT1_pressed==1 ||
P[ind].key_BT2_pressed==1 ||
P[ind].key_BT3_pressed==1 ||
P[ind].key_BT4_pressed==1 ||
P[ind].key_BT5_pressed==1 ||
P[ind].key_BT6_pressed==1 ||
P[ind].key_SELECT_pressed==1 ||
P[ind].key_START_pressed==1
){ P[ind].PodeTestarEspecial=1; }
}

///////////////////////////////////////////////////////////////////////////
// MAQUINA DE ESTADOS - FSM -----------------------------------------[**05]
///////////////////////////////////////////////////////////////////////////

//Faz a transicao de um estado para outro e define o comportamento dos personagens.
//Um pre requisito para ativar os movimentos é ter as imagens correspondentes na pasta do personagem.

for(int ind=1;ind<=2;ind++){

int other;
if(ind==1){other=2;}
if(ind==2){other=1;}

//---
/*
				//MAGIAS - ESPECIAIS//
				P[1].slot[x] << Armazena os direcionais
				P[1].bt_slot[x] << Armazena os botoes pressionados

				DIRECIONAIS - SAO BASEADOS NO TECLADO NUMERICO!!!
				>Cima           (UP)         = 8
				>Cima+Direita   (UP+RIGHT)   = 9
				>Direita        (RIGHT)      = 6
				>Direita+Baixo  (RIGHT+DOWN) = 3
				>Baixo          (DOWN)       = 2
				>Baixo+Esquerda (DOWN+LEFT)  = 1
				>Esquerda       (LEFT)       = 4
				>Esquerda+Cima  (LEFT+UP)    = 7

				BOTOES
				>Soco Fraco  - LP = 1
				>Soco Medio  - MP = 2
				>Soco Forte  - HP = 3
				>Chute Fraco - LK = 4
				>Chute Medio - MK = 5
				>Chute Forte - HK = 6
				>Any Punch        = 7
				>Any Kick         = 8
			*/

//inverte array de inputs, abastece "Special_Inputs_Ord"
for(int indxx=0; indxx<=9; indxx++){
int a=0;
int b=P[ind].Special_Inputs[indxx][0]+1;
for(int indx=1; indx<=P[ind].Special_Inputs[indxx][0]; indx++){
a++; b--;
P[ind].Special_Inputs_Ord[indxx][a] = P[ind].Special_Inputs[indxx][b];
}
P[ind].Special_Inputs_Ord[indxx][0]=P[ind].Special_Inputs[indxx][0];
}

//inverte os direcionais
for(int indx=0; indx<=9; indx++){
if(P[ind].Lado==-1){
for(int inds=1; inds<=P[ind].Special_Inputs_Ord[indx][0]; inds++){
int a=0; int b=0; int c=0;
if(P[ind].Special_Inputs_Ord[indx][inds]==1) { P[ind].Special_Inputs_Ord[indx][inds]=3; a=1; }
if(P[ind].Special_Inputs_Ord[indx][inds]==4) { P[ind].Special_Inputs_Ord[indx][inds]=6; b=1; }
if(P[ind].Special_Inputs_Ord[indx][inds]==7) { P[ind].Special_Inputs_Ord[indx][inds]=9; c=1; }
if(a==0) { if(P[ind].Special_Inputs_Ord[indx][inds]==3) { P[ind].Special_Inputs_Ord[indx][inds]=1; a=1; } }
if(b==0) { if(P[ind].Special_Inputs_Ord[indx][inds]==6) { P[ind].Special_Inputs_Ord[indx][inds]=4; b=1; } }
if(c==0) { if(P[ind].Special_Inputs_Ord[indx][inds]==9) { P[ind].Special_Inputs_Ord[indx][inds]=7; c=1; } }
}
}
}

//zera variaveis
ativa_especial=0;
int especial_ativado=-1;

int AtivadorDeMagia=0;
int AtivadorDeMagiaNumeroDoEspecial=0;

//testa os inputs dos especiais
for(int esp=0; esp<=9; esp++){
ativa_especial=0;
for(int indx=1; indx<=16; indx++){
if (P[ind].Special_Inputs_Ord[esp][0]>=indx){
//prepara os inputs dos botoes
bta=-999; btb=-999; btc=-999;
if (P[ind].Special_Inputs_Ord[esp][indx]>=-6 && P[ind].Special_Inputs_Ord[esp][indx]<=1){
bta=P[ind].Special_Inputs_Ord[esp][indx]; btb=bta; btc=bta;
}
if (P[ind].Special_Inputs_Ord[esp][indx]==-7){ bta=-1; btb=-2; btc=-3; }
if (P[ind].Special_Inputs_Ord[esp][indx]==-8){ bta=-4; btb=-5; btc=-6; }
//teste de comparacao
if(P[ind].slot[indx]!=P[ind].Special_Inputs_Ord[esp][indx]) {
if(P[ind].bt_slot[indx]*-1!=bta){
if(P[ind].bt_slot[indx]*-1!=btb){
if(P[ind].bt_slot[indx]*-1!=btc){
ativa_especial=0;
} else { ativa_especial++; }
} else { ativa_especial++; }
} else { ativa_especial++; }
} else { ativa_especial++; }
if( P[ind].Special_Inputs_Ord[esp][0]==ativa_especial ){
//força do golpe
if(ind==1){ if(P[1].bt_slot[1]*-1==-1 || P[1].bt_slot[1]*-1==-4){ ForcaDoGolpeP1=1; P[1].Special_Version=1; } }
if(ind==1){ if(P[1].bt_slot[1]*-1==-2 || P[1].bt_slot[1]*-1==-5){ ForcaDoGolpeP1=2; P[1].Special_Version=2; } }
if(ind==1){ if(P[1].bt_slot[1]*-1==-3 || P[1].bt_slot[1]*-1==-6){ ForcaDoGolpeP1=3; P[1].Special_Version=3; } }
if(ind==2){ if(P[2].bt_slot[1]*-1==-1 || P[2].bt_slot[1]*-1==-4){ ForcaDoGolpeP2=1; P[2].Special_Version=1; } }
if(ind==2){ if(P[2].bt_slot[1]*-1==-2 || P[2].bt_slot[1]*-1==-5){ ForcaDoGolpeP2=2; P[2].Special_Version=2; } }
if(ind==2){ if(P[2].bt_slot[1]*-1==-3 || P[2].bt_slot[1]*-1==-6){ ForcaDoGolpeP2=3; P[2].Special_Version=3; } }
especial_ativado=esp;
}

//Implementa os Especiais / MAGIAS
if(P[ind].PodeTestarEspecial==1){
for(int indx=0; indx<=9; indx++){
int num;
if(indx==0) { num=700; }
if(indx==1) { num=710; }
if(indx==2) { num=720; }
if(indx==3) { num=730; }
if(indx==4) { num=740; }
if(indx==5) { num=750; }
if(indx==6) { num=760; }
if(indx==7) { num=770; }
if(indx==8) { num=780; }
if(indx==9) { num=790; }
if( especial_ativado==indx ){
if( P[ind].TotalDeFramesMov[num]>-1 && P[ind].State!=num  ){
// validacao evita soltar especial no ar
// MomentoDoP...==1 significa que o Player esta de Pé
// solucao temporaria
int validacao=0;
if(ind==1 && MomentoDoP1==1){validacao=1;}
if(ind==2 && MomentoDoP2==1){validacao=1;}
if(validacao==1){

//tudo ok para soltar a magia, mas antes, preciso verificar se
//todos os comandos feitos pelo jogador foram realizados dentro do tempo de 1,5 segundos

//primeiro preciso saber quantos inputs tem o especial em questão
int totaldeinputs=0;
if(num==700){ totaldeinputs=P[ind].Special_Inputs_c[0][0]+P[ind].Special_Inputs_b[0][0]; }
if(num==710){ totaldeinputs=P[ind].Special_Inputs_c[1][0]+P[ind].Special_Inputs_b[1][0]; }
if(num==720){ totaldeinputs=P[ind].Special_Inputs_c[2][0]+P[ind].Special_Inputs_b[2][0]; }
if(num==730){ totaldeinputs=P[ind].Special_Inputs_c[3][0]+P[ind].Special_Inputs_b[3][0]; }
if(num==740){ totaldeinputs=P[ind].Special_Inputs_c[4][0]+P[ind].Special_Inputs_b[4][0]; }
if(num==750){ totaldeinputs=P[ind].Special_Inputs_c[5][0]+P[ind].Special_Inputs_b[5][0]; }
if(num==760){ totaldeinputs=P[ind].Special_Inputs_c[6][0]+P[ind].Special_Inputs_b[6][0]; }
if(num==770){ totaldeinputs=P[ind].Special_Inputs_c[7][0]+P[ind].Special_Inputs_b[7][0]; }
if(num==780){ totaldeinputs=P[ind].Special_Inputs_c[8][0]+P[ind].Special_Inputs_b[8][0]; }
if(num==790){ totaldeinputs=P[ind].Special_Inputs_c[9][0]+P[ind].Special_Inputs_b[9][0]; }
//depois preciso somar o total de tempo dos inputs inseridos
int totaldetempodosinputs=0;
for(int ttime=1; ttime<=totaldeinputs; ttime++){
totaldetempodosinputs += P[ind].t_slot[ttime];
}
//agora, ativo o especial se o tempo for menor a 1,5 segundos (90 frames +15 de canja rs)
if(totaldetempodosinputs<=105){
AtivadorDeMagia=1;
AtivadorDeMagiaNumeroDoEspecial=num;
}

}
}
}
}
}
}
}
}

//executa o audio do golpe especial
if(AtivadorDeMagia==1){

//inicializa a magia
P[ind].QtdeMagias=0;
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
PLAYER_STATE(ind, AtivadorDeMagiaNumeroDoEspecial, 0, P[ind].TotalDeFramesMov[AtivadorDeMagiaNumeroDoEspecial]);
Fireball[ind].StartFrame=timer;
New_Fireball(ind);

//som da magia
for(int iii=700; iii<=890; iii+=10){
char txtaudio[50]="";
if(P[ind].State==iii && P[ind].TotalDeFramesMov[P[ind].State]>0){
sprintf(txtaudio, "data/chars/%s/%i.wav", P[ind].Name, P[ind].State);
HM_SAMPLE snd   = backend_load_sample(txtaudio);
if (snd){ backend_play_sample(snd, 255, 128, 1000, 0); }
AtivadorDeMagia=0;
//backend_destroy_sample(snd);
}
}
}

//---

/*101 Soco Fraco em Pe*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602 || P[ind].State==101)
&& (P[ind].key_BT1_pressed==1)
&& (abs(P[1].x-P[2].x)>=60)
&& (P[ind].TotalDeFramesMov[101]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=101; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*102 Soco Medio em Pe*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT2_pressed==1)
&& (abs(P[1].x-P[2].x)>=60)
&& (P[ind].TotalDeFramesMov[102]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=102; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*103 Soco Forte em Pe*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT3_pressed==1)
&& (abs(P[1].x-P[2].x)>=60)
&& (P[ind].TotalDeFramesMov[103]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=103; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*104 Chute Fraco em Pe*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT4_pressed==1)
&& (abs(P[1].x-P[2].x)>=60)
&& (P[ind].TotalDeFramesMov[104]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=104; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*105 Chute Medio em Pe*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT5_pressed==1)
&& (abs(P[1].x-P[2].x)>=60)
&& (P[ind].TotalDeFramesMov[105]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=105; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*106 Chute Forte em Pe*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT6_pressed==1)
&& (abs(P[1].x-P[2].x)>=60)
&& (P[ind].TotalDeFramesMov[106]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=106; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*151 Soco Fraco em Pe (PERTO)*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT1_pressed==1)
&& (abs(P[1].x-P[2].x)<60) )
{
if(P[ind].TotalDeFramesMov[151] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=151; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
if(P[ind].TotalDeFramesMov[151]==-1
&& P[ind].TotalDeFramesMov[101] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=101; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
}
/*152 Soco Medio em Pe (PERTO)*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT2_pressed==1)
&& (abs(P[1].x-P[2].x)<60) )
{
if(P[ind].TotalDeFramesMov[152] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=152; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
if(P[ind].TotalDeFramesMov[152]==-1
&& P[ind].TotalDeFramesMov[102] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=102; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
}
/*153 Soco Forte em Pe (PERTO)*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT3_pressed==1)
&& (abs(P[1].x-P[2].x)<60) )
{
if(P[ind].TotalDeFramesMov[153] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=153; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
if(P[ind].TotalDeFramesMov[153]==-1
&& P[ind].TotalDeFramesMov[103] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=103; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
}
/*154 Chute Fraco em Pe (PERTO)*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT4_pressed==1)
&& (abs(P[1].x-P[2].x)<60) )
{
if(P[ind].TotalDeFramesMov[154] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=154; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
if(P[ind].TotalDeFramesMov[154]==-1
&& P[ind].TotalDeFramesMov[104] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=104; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
}
/*155 Chute Medio em Pe (PERTO)*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT5_pressed==1)
&& (abs(P[1].x-P[2].x)<60) )
{
if(P[ind].TotalDeFramesMov[155] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=155; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
if(P[ind].TotalDeFramesMov[155]==-1
&& P[ind].TotalDeFramesMov[105] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=105; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
}
/*156 Chute Forte em Pe (PERTO)*/
if ( (P[ind].State==100 || P[ind].State==410 || P[ind].State==420 || P[ind].State==602)
&& (P[ind].key_BT6_pressed==1)
&& (abs(P[1].x-P[2].x)<60) )
{
if(P[ind].TotalDeFramesMov[156] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=156; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
if(P[ind].TotalDeFramesMov[156]==-1
&& P[ind].TotalDeFramesMov[106] >-1){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=106; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
}
/*211 Soco Fraco Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT1_pressed==1
&& (P[ind].TotalDeFramesMov[211]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=211; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*211 Soco Fraco Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT1_pressed==1
&& (P[ind].TotalDeFramesMov[211]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=211; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*212 Soco Medio Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT2_pressed==1
&& (P[ind].TotalDeFramesMov[212]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=212; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*212 Soco Medio Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT2_pressed==1
&& (P[ind].TotalDeFramesMov[212]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=212; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*213 Soco Forte Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT3_pressed==1
&& (P[ind].TotalDeFramesMov[213]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=213; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*213 Soco Forte Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT3_pressed==1
&& (P[ind].TotalDeFramesMov[213]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=213; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*214 Chute Fraco Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT4_pressed==1
&& (P[ind].TotalDeFramesMov[214]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=214; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*214 Chute Fraco Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT4_pressed==1
&& (P[ind].TotalDeFramesMov[214]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=214; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*215 Chute Medio Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT5_pressed==1
&& (P[ind].TotalDeFramesMov[215]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=215; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*215 Chute Medio Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT5_pressed==1
&& (P[ind].TotalDeFramesMov[215]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=215; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*216 Chute Forte Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT6_pressed==1
&& (P[ind].TotalDeFramesMov[216]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=216; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*216 Chute Forte Abaixado + Tras*/
if ( (P[ind].State==200 || P[ind].State==210 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT6_pressed==1
&& (P[ind].TotalDeFramesMov[216]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=216; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*221 Soco Fraco Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT1_pressed==1
&& (P[ind].TotalDeFramesMov[221]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=221; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*221 Soco Fraco Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT1_pressed==1
&& (P[ind].TotalDeFramesMov[221]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=221; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*222 Soco Medio Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT2_pressed==1 && (P[ind].TotalDeFramesMov[222]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=222; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*222 Soco Medio Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT2_pressed==1
&& (P[ind].TotalDeFramesMov[222]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=222; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*223 Soco Forte Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT3_pressed==1
&& (P[ind].TotalDeFramesMov[223]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=223; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*223 Soco Forte Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT3_pressed==1
&& (P[ind].TotalDeFramesMov[223]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=223; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*224 Chute Fraco Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT4_pressed==1
&& (P[ind].TotalDeFramesMov[224]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=224; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*224 Chute Fraco Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT4_pressed==1
&& (P[ind].TotalDeFramesMov[224]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=224; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*225 Chute Medio Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT5_pressed==1 && (P[ind].TotalDeFramesMov[225]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=225; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*225 Chute Medio Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT5_pressed==1
&& (P[ind].TotalDeFramesMov[225]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=225; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*226 Chute Forte Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& P[ind].key_BT6_pressed==1
&& (P[ind].TotalDeFramesMov[226]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=226; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*226 Chute Forte Abaixado + Frente*/
if ( (P[ind].State==200 || P[ind].State==220 )
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& P[ind].key_BT6_pressed==1
&& (P[ind].TotalDeFramesMov[226]>-1) ) {
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=226; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*201 Soco Fraco Abaixado*/
if ( (P[ind].State==200 || P[ind].State==601)
&& P[ind].key_BT1_pressed==1
&& (P[ind].TotalDeFramesMov[201]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=201; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*202 Soco Medio Abaixado*/
if ( (P[ind].State==200 || P[ind].State==601)
&& P[ind].key_BT2_pressed==1
&& (P[ind].TotalDeFramesMov[202]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=202; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*203 Soco Forte Abaixado*/
if ( (P[ind].State==200 || P[ind].State==601)
&& P[ind].key_BT3_pressed==1
&& (P[ind].TotalDeFramesMov[203]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=203; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*204 Chute Fraco Abaixado*/
if ( (P[ind].State==200 || P[ind].State==601)
&& P[ind].key_BT4_pressed==1
&& (P[ind].TotalDeFramesMov[204]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=204; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*205 Chute Medio Abaixado*/
if ( (P[ind].State==200 || P[ind].State==601)
&& P[ind].key_BT5_pressed==1
&& (P[ind].TotalDeFramesMov[205]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=205; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*206 Chute Forte Abaixado*/
if ( (P[ind].State==200 || P[ind].State==601)
&& P[ind].key_BT6_pressed==1
&& (P[ind].TotalDeFramesMov[206]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=206; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*210 Baixo e Tras*/
if (  P[ind].State==200
&& P[ind].Lado== 1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& (P[ind].TotalDeFramesMov[210]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=210; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*210 Baixo e Tras*/
if (  P[ind].State==200
&& P[ind].Lado==-1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& (P[ind].TotalDeFramesMov[210]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=210; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*220 Baixo e Frente*/
if (  P[ind].State==200
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& (P[ind].TotalDeFramesMov[220]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=220; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*220 Baixo e Frente*/
if (  P[ind].State==200
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& (P[ind].TotalDeFramesMov[220]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=220; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*410 Andando para Tras*/
if (  P[ind].State==100
&& P[ind].Lado== 1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& (P[ind].TotalDeFramesMov[410]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=410; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*410 Andando para Tras*/
if (  P[ind].State==100
&& P[ind].Lado==-1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& (P[ind].TotalDeFramesMov[410]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=410; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*420 Andando para Frente*/
if (  P[ind].State==100
&& P[ind].Lado== 1
&& (P[ind].key_RIGHT_pressed==1 || P[ind].key_RIGHT_hold==1)
&& (P[ind].TotalDeFramesMov[420]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=420; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*420 Andando para Frente*/
if (  P[ind].State==100
&& P[ind].Lado==-1
&& (P[ind].key_LEFT_pressed==1 || P[ind].key_LEFT_hold==1)
&& (P[ind].TotalDeFramesMov[420]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=420; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*507 End Reversao Aerea 507->606*/
if ( P[ind].State==507
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[606]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=606; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*507 End Reversao Aerea 507->100*/
if ( P[ind].State==507
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[100]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=100; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*551 End Queda*/
if ( P[ind].State==550
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[550]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=551; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*552 End Queda continuacao*/
if ( P[ind].State==551
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[551]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=552; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*571 End Queda p/ KO*/
if ( P[ind].State==570
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[570]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=571; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*572 End Queda p/ KO continuacao*/
if ( P[ind].State==571
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[571]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=572; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*601 Abaixando*/
if ( P[ind].State==100
&& (P[ind].key_DOWN_pressed==1 || P[ind].key_DOWN_hold==1)
&& (P[ind].TotalDeFramesMov[601]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=601; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*601 Abaixando*/
if ( P[ind].State==410
&& (P[ind].key_DOWN_pressed==1 || P[ind].key_DOWN_hold==1)
&& (P[ind].TotalDeFramesMov[601]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=601; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*601 Abaixando*/
if ( P[ind].State==420
&& (P[ind].key_DOWN_pressed==1 || P[ind].key_DOWN_hold==1)
&& (P[ind].TotalDeFramesMov[601]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=601; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*601/608 Abaixando/Virando de Lado abaixado*/
if (  P[ind].State==606 && P[ind].key_DOWN_status>0 ) {
int a=1;
if (a==1 && P[ind].Lado== 1 && P[ind].x<MeioDaTela && (P[ind].TotalDeFramesMov[601]>-1) ) {
a=0; AHitP1=1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=601; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
if (a==1 && P[ind].Lado== 1 && P[ind].x>MeioDaTela && (P[ind].TotalDeFramesMov[608]>-1) ) {
a=0; AHitP1=1;
P[ind].Lado=-1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=608; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
if (a==1 && P[ind].Lado==-1 && P[ind].x>MeioDaTela && (P[ind].TotalDeFramesMov[601]>-1) ) {
a=0; AHitP1=1; P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=601; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
if (a==1 && P[ind].Lado==-1 && P[ind].x<MeioDaTela && (P[ind].TotalDeFramesMov[608]>-1) ) {
a=0; AHitP1=1;
P[ind].Lado= 1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=608; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
}
/*602 Levantando*/
if ( P[ind].State==200
&& (P[ind].key_DOWN_released==1 || P[ind].key_DOWN_hold==0)
&& (P[ind].TotalDeFramesMov[602]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=602; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*603 Intro Pulo Tras*/
if ( P[ind].State==410
&& P[ind].Lado== 1
&& (P[ind].key_UP_status>0)
&& P[ind].key_LEFT_status> 0
&& P[ind].key_RIGHT_status==0
&& (P[ind].TotalDeFramesMov[603]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=603; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*603 Intro Pulo Tras*/
if ( P[ind].State==410
&& P[ind].Lado==-1
&& (P[ind].key_UP_status>0)
&& P[ind].key_LEFT_status==0
&& P[ind].key_RIGHT_status> 0
&& (P[ind].TotalDeFramesMov[603]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=603; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*604 Intro Pulo Neutro*/
if ( P[ind].State==100
&& (P[ind].key_UP_status>0)
&& P[ind].key_LEFT_status==0
&& P[ind].key_RIGHT_status==0
&& (P[ind].TotalDeFramesMov[604]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=604; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*605 Intro Pulo Frente*/
if ( P[ind].State==420
&& P[ind].Lado==-1
&& (P[ind].key_UP_status>0)
&& P[ind].key_LEFT_status> 0
&& P[ind].key_RIGHT_status==0
&& (P[ind].TotalDeFramesMov[605]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=605; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*605 Intro Pulo Frente*/
if ( P[ind].State==420
&& P[ind].Lado== 1
&& (P[ind].key_UP_status>0)
&& P[ind].key_LEFT_status==0
&& P[ind].key_RIGHT_status> 0
&& (P[ind].TotalDeFramesMov[605]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=605; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*606 End Pulo*/
if ( (P[ind].State==300
|| P[ind].State==301 || P[ind].State==302 || P[ind].State==303
|| P[ind].State==304 || P[ind].State==305 || P[ind].State==306)
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[606]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=606; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*606 End Pulo*/
if ( (P[ind].State==310
|| P[ind].State==311 || P[ind].State==312 || P[ind].State==313
|| P[ind].State==314 || P[ind].State==315 || P[ind].State==316)
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[606]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=606; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*606 End Pulo*/
if ( (P[ind].State==320
|| P[ind].State==321 || P[ind].State==322 || P[ind].State==323
|| P[ind].State==324 || P[ind].State==325 || P[ind].State==326)
&& P[ind].y==AlturaPiso
&& P[ind].Vspeed>=0
&& (P[ind].TotalDeFramesMov[606]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=606; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*301 Pulo Neutro + Soco Fraco*/
if ( P[ind].State==300
&& P[ind].key_BT1_status==1
&& (P[ind].TotalDeFramesMov[301]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=301; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*302 Pulo Neutro + Soco Medio*/
if ( P[ind].State==300
&& P[ind].key_BT2_status==1
&& (P[ind].TotalDeFramesMov[302]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=302; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*303 Pulo Neutro + Soco Forte*/
if ( P[ind].State==300
&& P[ind].key_BT3_status==1
&& (P[ind].TotalDeFramesMov[303]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=303; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*304 Pulo Neutro + Chute Fraco*/
if ( P[ind].State==300
&& P[ind].key_BT4_status==1
&& (P[ind].TotalDeFramesMov[304]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=304; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*305 Pulo Neutro + Chute Medio*/
if ( P[ind].State==300
&& P[ind].key_BT5_status==1
&& (P[ind].TotalDeFramesMov[305]>-1) ){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=305; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*306 Pulo Neutro + Chute Forte*/
if ( P[ind].State==300
&& P[ind].key_BT6_status==1
&& (P[ind].TotalDeFramesMov[306]>-1) ){
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=306; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*321 Pulo Frente + Soco Fraco*/
if ( (P[ind].State==310 || P[ind].State==320)
&& P[ind].key_BT1_status==1
&& (P[ind].TotalDeFramesMov[321]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=321; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*322 Pulo Frente + Soco Medio*/
if ( (P[ind].State==310 || P[ind].State==320)
&& P[ind].key_BT2_status==1
&& (P[ind].TotalDeFramesMov[322]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=322; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*323 Pulo Frente + Soco Forte*/
if ( (P[ind].State==310 || P[ind].State==320)
&& P[ind].key_BT3_status==1
&& (P[ind].TotalDeFramesMov[323]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=323; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*324 Pulo Frente + Chute Fraco*/
if ( (P[ind].State==310 || P[ind].State==320)
&& P[ind].key_BT4_status==1
&& (P[ind].TotalDeFramesMov[324]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=324; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl1, 255, 128, 1000, 0);
}
/*325 Pulo Frente + Chute Medio*/
if ( (P[ind].State==310 || P[ind].State==320)
&& P[ind].key_BT5_status==1
&& (P[ind].TotalDeFramesMov[325]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=325; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl2, 255, 128, 1000, 0);
}
/*326 Pulo Frente + Chute Forte*/
if ( (P[ind].State==310 || P[ind].State==320)
&& P[ind].key_BT6_status==1
&& (P[ind].TotalDeFramesMov[326]>-1) )	{
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
int set=326; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
backend_play_sample(attacklvl3, 255, 128, 1000, 0);
}
/*607 Virando de Lado em Pe*/
if ( P[ind].State==100
&& (P[ind].x>MeioDaTela
&& P[ind].Lado== 1)
&& (P[ind].TotalDeFramesMov[607]>-1) )	{
P[ind].Lado=-1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=607; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*607 Virando de Lado em Pe*/
if ( P[ind].State==100
&& (P[ind].x<MeioDaTela
&& P[ind].Lado==-1)
&& (P[ind].TotalDeFramesMov[607]>-1) )	{
P[ind].Lado= 1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=607; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*607 Virando de Lado em Pe*/
if ( P[ind].State==420
&& P[ind].Lado== 1
&& P[ind].x>MeioDaTela
&& (P[ind].TotalDeFramesMov[607]>-1) )	{
P[ind].Lado=-1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=607; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*607 Virando de Lado em Pe*/
if ( P[ind].State==420
&& P[ind].Lado==-1
&& P[ind].x<MeioDaTela
&& (P[ind].TotalDeFramesMov[607]>-1) )	{
P[ind].Lado= 1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=607; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*608 Virando de Lado Abaixado*/
if ( P[ind].State==200
&& (P[ind].x>MeioDaTela
&& P[ind].Lado== 1)
&& (P[ind].TotalDeFramesMov[608]>-1) )	{
P[ind].Lado=-1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=608; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*608 Virando de Lado Abaixado*/
if ( P[ind].State==200
&& (P[ind].x<MeioDaTela
&& P[ind].Lado==-1)
&& (P[ind].TotalDeFramesMov[608]>-1) )	{
P[ind].Lado= 1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=608; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*608 Virando de Lado Abaixado*/
if ( P[ind].State==220
&& P[ind].Lado== 1
&& P[ind].x>MeioDaTela
&& (P[ind].TotalDeFramesMov[608]>-1) )	{
P[ind].Lado=-1;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=608; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*608 Virando de Lado Abaixado*/
if ( P[ind].State==220
&& P[ind].Lado==-1
&& P[ind].x<MeioDaTela
&& (P[ind].TotalDeFramesMov[608]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=608; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*210 Abaixado Andando para Tras*/
if ( P[ind].State==210
&& P[ind].key_LEFT_released==1
&& (P[ind].TotalDeFramesMov[200]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=200; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*210 Abaixado Andando para Tras*/
if ( P[ind].State==210
&& P[ind].key_RIGHT_released==1
&& P[ind].Lado==-1
&& (P[ind].TotalDeFramesMov[200]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=200; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*220 Abaixado Andando para Frente*/
if ( P[ind].State==220
&& P[ind].key_RIGHT_released==1
&& (P[ind].TotalDeFramesMov[200]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=200; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*220 Abaixado Andando para Frente*/
if ( P[ind].State==220
&& P[ind].key_LEFT_released==1
&& P[ind].Lado==-1
&& (P[ind].TotalDeFramesMov[200]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=200; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*210;220 Stop*/
if ( (P[ind].State==210 || P[ind].State==220)
&& (P[ind].key_DOWN_released==1 || P[ind].key_DOWN_hold==0) ) {
int set=0;
if(P[ind].TotalDeFramesMov[602]>-1){ set=602; }else{ set=100; }
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*100 Parado*/
if ( P[ind].State==410
&& P[ind].key_LEFT_released==1
&& (P[ind].TotalDeFramesMov[100]>-1) ) {
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=100; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*100 Parado*/
if ( P[ind].State==410
&& P[ind].key_RIGHT_released==1
&& P[ind].Lado==-1
&& (P[ind].TotalDeFramesMov[100]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=100; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*100 Parado*/
if ( P[ind].State==420
&& P[ind].key_RIGHT_released==1
&& (P[ind].TotalDeFramesMov[100]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=100; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*100 Parado*/
if ( P[ind].State==420
&& P[ind].key_LEFT_released==1
&& P[ind].Lado==-1
&& (P[ind].TotalDeFramesMov[100]>-1) )	{
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=100; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
/*611 Ganhou por KO ou Time Over*/
if (
P[ind].State==100
&& timer_final_de_rounds>0
&& P[ind].Energy>=P[other].Energy
&& (P[other].State==572
|| P[other].State==616 || P[other].State==617
|| P[other].State==618 || P[other].State==100) ){
if(P[ind].TotalDeFramesMov[611]> -1){
P[ind].Hspeed=0;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=611; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
if(P[ind].TotalDeFramesMov[611]==-1){
P[ind].Hspeed=0;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=100; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
}
/*616 Perdeu por Time Over*/
if ( ( P[ind].State!=616
&& P[ind].State!=570 && P[ind].State!=571 && P[ind].State!=572
&& P[ind].State!=550 && P[ind].State!=551 && P[ind].State!=552
&& P[ind].State!=623 && P[ind].State!=626
&& P[ind].State!=310
&& P[ind].State!=311 && P[ind].State!=312 && P[ind].State!=313
&& P[ind].State!=314 && P[ind].State!=315 && P[ind].State!=316
&&	P[ind].State!=300
&& P[ind].State!=301 && P[ind].State!=302 && P[ind].State!=303
&& P[ind].State!=304 && P[ind].State!=305 && P[ind].State!=306
&& P[ind].State!=320
&& P[ind].State!=321 && P[ind].State!=322 && P[ind].State!=323
&& P[ind].State!=324 && P[ind].State!=325 && P[ind].State!=326
&& P[ind].State!= 11 && P[ind].State!= 12 && P[ind].State!= 13
&& P[ind].State!= 16 )
&& timer_final_de_rounds>0
&& P[ind].Energy<=P[other].Energy
&& P[ind].Energy>0 ){
if(P[ind].TotalDeFramesMov[616]> -1){
P[ind].Hspeed=0;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=616; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
if(P[ind].TotalDeFramesMov[616]==-1){
P[ind].Hspeed=0;
P[ind].StartFrame=timer; //P[ind].MovStartFrame=P[ind].StartFrame;
int set=100; PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}
}

//SONS DE HIT
if(PlaySoundHitLvl1==1){ backend_play_sample(hitlvl1, 255, 128, 1000, 0); PlaySoundHitLvl1=0; }
if(PlaySoundHitLvl2==1){ backend_play_sample(hitlvl2, 255, 128, 1000, 0); PlaySoundHitLvl2=0; }
if(PlaySoundHitLvl3==1){ backend_play_sample(hitlvl3, 255, 128, 1000, 0); PlaySoundHitLvl3=0; }

}//fim do for - FSM

///////////////////////////////////////////////////////////////////////////
// DIFS / APLICA ALTERACAO NOS PARAMETROS DOS PERSONAGENS -----------[**06]
///////////////////////////////////////////////////////////////////////////

//Afasta os jogadores quando ocorre sobreposicao de posicao
//Dois corpos nao ocupam o mesmo lugar no espaço :)
if(contatofisico==1){
if(P[1].x<=P[2].x) { P[1].x-=1; P[2].x+=1;
if(P[1].x <= 30){ P[1].x = 30; P[2].x += 1;}
if(P[2].x >= backend_bitmap_width(bg_test)-30){ P[1].x -= 1; P[2].x = backend_bitmap_width(bg_test)-30;}
}
if(P[1].x >P[2].x) { P[1].x+=1; P[2].x-=1;
if(P[2].x <= 30){ P[2].x = 30; P[1].x += 1;}
if(P[1].x >= backend_bitmap_width(bg_test)-30){ P[2].x -= 1; P[1].x = backend_bitmap_width(bg_test)-30;}
}
}

/* <P1> */
//DIF01 - Mantem o personagem dentro da tela
if ( P[1].Hspeed!=0 && P1HitPause==0 ) {
P[1].x+=P[1].Hspeed;
if(P[1].x<=30){
P[1].x=30;
}
if(P[1].x>=backend_bitmap_width(bg_test)-30){
P[1].x=backend_bitmap_width(bg_test)-30;
}
}
//DIF02 - Define a distancia maxima entre os jogadores
if(op_Zoom==1) { if (abs(P[1].x-P[2].x)>backend_bitmap_height(bufferx)*0.6) { P[1].x+=(P[1].Hspeed*-1); P[2].x+=(P[2].Hspeed*-1); } }
if(op_Zoom==0) { if (abs(P[1].x-P[2].x)>250) { P[1].x+=(P[1].Hspeed*-1); } }
//DIF03 - Calcula o pulo e o pouso no chao
if ( P[1].Vspeed!=0 && P1HitPause==0 ) {
P[1].y+=P[1].Vspeed; //if(P[1].y<=0){P[1].y=0;}
P[1].ConstanteY+=P[1].Vspeed-P[1].Gravity;
if (P[1].y>=AlturaPiso){
P[1].y=AlturaPiso;
P[1].Hspeed=0;
P[1].Vspeed=0;
P[1].Gravity=0;
P[1].ConstanteY=0;
}
}
//DIF04 - Aplica gravidade ao Vspeed
if ( P[1].Gravity!=0 && P1HitPause==0 ) { P[1].Vspeed+=P[1].Gravity; }
//DIF05 - Reseta velocidade se o player estiver parado no State 100
if(P[1].State==100) { P[1].Hspeed=0; P[1].Vspeed=0; }

/* <P2> */
//DIF01 - Mantem o personagem dentro da tela
if ( P[2].Hspeed!=0 && P2HitPause==0 ) {
P[2].x+=P[2].Hspeed;
if(P[2].x<=30){
P[2].x=30;
}
if(P[2].x>=backend_bitmap_width(bg_test)-30){
P[2].x=backend_bitmap_width(bg_test)-30;
}
}
//DIF02 - Define a distancia maxima entre os jogadores
if(op_Zoom==1) { if (abs(P[1].x-P[2].x)>backend_bitmap_height(bufferx)*0.6) { P[1].x+=(P[1].Hspeed*-1); P[2].x+=(P[2].Hspeed*-1); } }
if(op_Zoom==0) { if (abs(P[1].x-P[2].x)>250) { P[2].x+=(P[2].Hspeed*-1); } }
//DIF03 - Calcula o pulo e o pouso no chao
if ( P[2].Vspeed!=0 && P2HitPause==0 ) {
P[2].y+=P[2].Vspeed; //if(P[2].y<=0){P[2].y=0;}
P[2].ConstanteY+=P[2].Vspeed-P[2].Gravity;
if (P[2].y>=AlturaPiso){
P[2].y=AlturaPiso;
P[2].Hspeed=0;
P[2].Vspeed=0;
P[2].Gravity=0;
P[2].ConstanteY=0;
}
}
//DIF04 - Aplica gravidade ao Vspeed
if ( P[2].Gravity!=0 && P2HitPause==0 ) { P[2].Vspeed+=P[2].Gravity; }
//DIF05 - Reseta velocidade se o player estiver parado no State 100
if(P[2].State==100) { P[2].Hspeed=0; P[2].Vspeed=0; }

///////////////////////////////////////////////////////////////////////////
// FUNCOES DE DESENHO -----------------------------------------------[**07]
///////////////////////////////////////////////////////////////////////////

int Atuador1=0;
int Atuador2=0;

//backend_clear_to_color(bufferx,backend_makecol(100,149,237)); //fundo azul
backend_clear_to_color(bufferx,backend_makecol(0,0,0)); //fundo preto

/* <P1> anim */
if ( P1HitPause==0 && P2HitPause==0 )
{
int HitStackChange=0;
if (P[1].IndexAnim== 0) { if (timer>P[1].StartFrame+P1_FrameTime_00) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_01; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 1) { if (timer>P[1].StartFrame+P1_FrameTime_01) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_02; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 2) { if (timer>P[1].StartFrame+P1_FrameTime_02) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_03; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 3) { if (timer>P[1].StartFrame+P1_FrameTime_03) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_04; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 4) { if (timer>P[1].StartFrame+P1_FrameTime_04) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_05; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 5) { if (timer>P[1].StartFrame+P1_FrameTime_05) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_06; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 6) { if (timer>P[1].StartFrame+P1_FrameTime_06) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_07; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 7) { if (timer>P[1].StartFrame+P1_FrameTime_07) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_08; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 8) { if (timer>P[1].StartFrame+P1_FrameTime_08) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_09; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim== 9) { if (timer>P[1].StartFrame+P1_FrameTime_09) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_10; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==10) { if (timer>P[1].StartFrame+P1_FrameTime_10) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_11; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==11) { if (timer>P[1].StartFrame+P1_FrameTime_11) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_12; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==12) { if (timer>P[1].StartFrame+P1_FrameTime_12) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_13; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==13) { if (timer>P[1].StartFrame+P1_FrameTime_13) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_14; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==14) { if (timer>P[1].StartFrame+P1_FrameTime_14) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_15; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==15) { if (timer>P[1].StartFrame+P1_FrameTime_15) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_16; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==16) { if (timer>P[1].StartFrame+P1_FrameTime_16) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_17; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==17) { if (timer>P[1].StartFrame+P1_FrameTime_17) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_18; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==18) { if (timer>P[1].StartFrame+P1_FrameTime_18) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_19; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==19) { if (timer>P[1].StartFrame+P1_FrameTime_19) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_20; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==20) { if (timer>P[1].StartFrame+P1_FrameTime_20) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_21; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==21) { if (timer>P[1].StartFrame+P1_FrameTime_21) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_22; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==22) { if (timer>P[1].StartFrame+P1_FrameTime_22) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_23; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==23) { if (timer>P[1].StartFrame+P1_FrameTime_23) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_24; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==24) { if (timer>P[1].StartFrame+P1_FrameTime_24) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_25; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==25) { if (timer>P[1].StartFrame+P1_FrameTime_25) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_26; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==26) { if (timer>P[1].StartFrame+P1_FrameTime_26) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_27; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==27) { if (timer>P[1].StartFrame+P1_FrameTime_27) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_28; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[1].IndexAnim==28) { if (timer>P[1].StartFrame+P1_FrameTime_28) {
Atuador1=1; P[1].IndexAnim++; P1_FrameTime=P1_FrameTime_29; P[1].StartFrame=timer; Draw_CHBoxes_P1();
if (strcmp (P[1].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if(HitStackChange==1){
if(P[1].State!=301 && P[1].State!=321 && P[1].State!=304 && P[1].State!=324) {
AHitP1=1;
}
}
//if (P[1].IndexAnim==29) {}
}

/* <P1> end of anim vai pro LOOP*/
//vai para o loop, caso nao seja nenhum dos movimentos contidos neste IF
if (P[1].IndexAnim>P[1].TotalFrames
&& P[1].State!=101 && P[1].State!=102 && P[1].State!=103 && P[1].State!=104 && P[1].State!=105 && P[1].State!=106 //EXCESSOES DE NON LOOPS
&& P[1].State!=151 && P[1].State!=152 && P[1].State!=153 && P[1].State!=154 && P[1].State!=155 && P[1].State!=156 //EXCESSOES DE NON LOOPS
&& P[1].State!=201 && P[1].State!=202 && P[1].State!=203 && P[1].State!=204 && P[1].State!=205 && P[1].State!=206 //EXCESSOES DE NON LOOPS
//&& P[1].State!=300                                                                                              //EXCESSOES DE NON LOOPS
&& P[1].State!=301 && P[1].State!=302 && P[1].State!=303 && P[1].State!=304 && P[1].State!=305 && P[1].State!=306 //EXCESSOES DE NON LOOPS
//&& P[1].State!=310                                                                                              //EXCESSOES DE NON LOOPS
&& P[1].State!=311 && P[1].State!=312 && P[1].State!=313 && P[1].State!=314 && P[1].State!=315 && P[1].State!=316 //EXCESSOES DE NON LOOPS
//&& P[1].State!=320                                                                                              //EXCESSOES DE NON LOOPS
&& P[1].State!=321 && P[1].State!=322 && P[1].State!=323 && P[1].State!=324 && P[1].State!=325 && P[1].State!=326 //EXCESSOES DE NON LOOPS
&& P[1].State!=501 && P[1].State!=502 && P[1].State!=503 && P[1].State!=504 && P[1].State!=505 && P[1].State!=506 //EXCESSOES DE NON LOOPS
&& P[1].State!=507 && P[1].State!=508 && P[1].State!=509 && P[1].State!=511 && P[1].State!=512 && P[1].State!=513 //EXCESSOES DE NON LOOPS
//&& P[1].State!=550                                                                                              //EXCESSOES DE NON LOOPS
&& P[1].State!=552 && P[1].State!=601 && P[1].State!=602 && P[1].State!=603 && P[1].State!=604 && P[1].State!=605 //EXCESSOES DE NON LOOPS
&& P[1].State!=606 && P[1].State!=607 && P[1].State!=608 && P[1].State!=611 && P[1].State!=612 && P[1].State!=613 //EXCESSOES DE NON LOOPS
&& P[1].State!=616 && P[1].State!=617 && P[1].State!=618
&& P[1].State!=700 && P[1].State!=710 && P[1].State!=720 && P[1].State!=730
&& P[1].State!=740 && P[1].State!=750 && P[1].State!=760
&& P[1].State!=770 && P[1].State!=780 && P[1].State!=790
) //EXCESSOES DE NON LOOPS
{ P[1].IndexAnim=0; P1_FrameTime=P1_FrameTime_00; P[1].StartFrame=timer; Draw_CHBoxes_P1(); } //-loop
/* <P1> Non Loops FSM! */
//movimentos sem loop terminam e carregam outros movimentos, exemplo: final do soco fraco [101] carrega movimento parado [100]
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==101) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==102) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==103) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==104) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==105) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==106) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==151) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==152) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==153) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==154) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==155) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==156) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==201) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==202) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==203) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==204) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==205) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==206) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==501) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==502) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==503) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==504) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==505) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==506) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==511) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==512) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==513) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==601) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==552) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==602) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==603) { P[1].StartFrame=timer; PLAYER_STATE(1, 310, 0, P[1].TotalDeFramesMov[310]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==604) { P[1].StartFrame=timer; PLAYER_STATE(1, 300, 0, P[1].TotalDeFramesMov[300]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==605) { P[1].StartFrame=timer; PLAYER_STATE(1, 320, 0, P[1].TotalDeFramesMov[320]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==606) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==607) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==608) { P[1].StartFrame=timer; PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==700) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==710) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==720) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==730) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==740) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==750) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==760) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==770) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==780) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==790) { P[1].StartFrame=timer; PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]); Draw_CHBoxes_P1(); }

//Anim Infinita
//if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==300) {  }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==301) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 301, P[1].IndexAnim, P[1].TotalDeFramesMov[301]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==302) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 302, P[1].IndexAnim, P[1].TotalDeFramesMov[302]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==303) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 303, P[1].IndexAnim, P[1].TotalDeFramesMov[303]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==304) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 304, P[1].IndexAnim, P[1].TotalDeFramesMov[304]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==305) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 305, P[1].IndexAnim, P[1].TotalDeFramesMov[305]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==306) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 306, 0, P[1].TotalDeFramesMov[306]); Draw_CHBoxes_P1(); }
//if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==310) {  }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==311) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 311, P[1].IndexAnim, P[1].TotalDeFramesMov[311]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==312) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 312, P[1].IndexAnim, P[1].TotalDeFramesMov[312]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==313) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 313, P[1].IndexAnim, P[1].TotalDeFramesMov[313]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==314) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 314, P[1].IndexAnim, P[1].TotalDeFramesMov[314]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==315) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 315, P[1].IndexAnim, P[1].TotalDeFramesMov[315]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==316) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 316, P[1].IndexAnim, P[1].TotalDeFramesMov[316]); Draw_CHBoxes_P1(); }
//if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==320) {  }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==321) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 321, P[1].IndexAnim, P[1].TotalDeFramesMov[321]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==322) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 322, P[1].IndexAnim, P[1].TotalDeFramesMov[322]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==323) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 323, P[1].IndexAnim, P[1].TotalDeFramesMov[323]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==324) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 324, P[1].IndexAnim, P[1].TotalDeFramesMov[324]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==325) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 325, P[1].IndexAnim, P[1].TotalDeFramesMov[325]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==326) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 326, P[1].IndexAnim, P[1].TotalDeFramesMov[326]); Draw_CHBoxes_P1(); }
//if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==507) {  }
//if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==550) {  }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==611) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 611, P[1].IndexAnim, P[1].TotalDeFramesMov[611]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==612) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 612, P[1].IndexAnim, P[1].TotalDeFramesMov[612]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==613) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 613, P[1].IndexAnim, P[1].TotalDeFramesMov[613]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==616) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 616, P[1].IndexAnim, P[1].TotalDeFramesMov[616]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==617) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 617, P[1].IndexAnim, P[1].TotalDeFramesMov[617]); Draw_CHBoxes_P1(); }
if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==618) { P[1].IndexAnim--; P[1].StartFrame=timer; PLAYER_STATE(1, 618, P[1].IndexAnim, P[1].TotalDeFramesMov[618]); Draw_CHBoxes_P1(); }

//garante que o IndexAnim nunca vai ser maior que TotalFrames
if (P[1].IndexAnim>P[1].TotalFrames){ P[1].IndexAnim=P[1].TotalFrames; }

/* <P2> anim */
if ( P2HitPause==0 && P1HitPause==0 )
{
int HitStackChange=0;
if (P[2].IndexAnim== 0) { if (timer>P[2].StartFrame+P2_FrameTime_00) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_01; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 1) { if (timer>P[2].StartFrame+P2_FrameTime_01) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_02; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 2) { if (timer>P[2].StartFrame+P2_FrameTime_02) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_03; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 3) { if (timer>P[2].StartFrame+P2_FrameTime_03) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_04; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 4) { if (timer>P[2].StartFrame+P2_FrameTime_04) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_05; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 5) { if (timer>P[2].StartFrame+P2_FrameTime_05) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_06; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 6) { if (timer>P[2].StartFrame+P2_FrameTime_06) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_07; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 7) { if (timer>P[2].StartFrame+P2_FrameTime_07) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_08; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 8) { if (timer>P[2].StartFrame+P2_FrameTime_08) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_09; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim== 9) { if (timer>P[2].StartFrame+P2_FrameTime_09) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_10; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==10) { if (timer>P[2].StartFrame+P2_FrameTime_10) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_11; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==11) { if (timer>P[2].StartFrame+P2_FrameTime_11) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_12; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==12) { if (timer>P[2].StartFrame+P2_FrameTime_12) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_13; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==13) { if (timer>P[2].StartFrame+P2_FrameTime_13) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_14; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==14) { if (timer>P[2].StartFrame+P2_FrameTime_14) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_15; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==15) { if (timer>P[2].StartFrame+P2_FrameTime_15) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_16; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==16) { if (timer>P[2].StartFrame+P2_FrameTime_16) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_17; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==17) { if (timer>P[2].StartFrame+P2_FrameTime_17) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_18; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==18) { if (timer>P[2].StartFrame+P2_FrameTime_18) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_19; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==19) { if (timer>P[2].StartFrame+P2_FrameTime_19) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_20; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==20) { if (timer>P[2].StartFrame+P2_FrameTime_20) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_21; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==21) { if (timer>P[2].StartFrame+P2_FrameTime_21) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_22; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==22) { if (timer>P[2].StartFrame+P2_FrameTime_22) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_23; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==23) { if (timer>P[2].StartFrame+P2_FrameTime_23) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_24; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==24) { if (timer>P[2].StartFrame+P2_FrameTime_24) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_25; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==25) { if (timer>P[2].StartFrame+P2_FrameTime_25) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_26; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==26) { if (timer>P[2].StartFrame+P2_FrameTime_26) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_27; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==27) { if (timer>P[2].StartFrame+P2_FrameTime_27) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_28; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if (P[2].IndexAnim==28) { if (timer>P[2].StartFrame+P2_FrameTime_28) {
Atuador2=1; P[2].IndexAnim++; P2_FrameTime=P2_FrameTime_29; P[2].StartFrame=timer; Draw_CHBoxes_P2();
if (strcmp (P[2].HitStack,"Multi")==0){ HitStackChange=1; }
}}
if(HitStackChange==1){
if(P[2].State!=301 && P[2].State!=321 && P[2].State!=304 && P[2].State!=324) {
AHitP2=1;
}
}
//if (P[2].IndexAnim==29) { }
}
/* <P2> end of anim vai pro LOOP*/
//vai para o loop, caso nao seja nenhum dos movimentos contidos neste IF
if (P[2].IndexAnim>P[2].TotalFrames
&& P[2].State!=101 && P[2].State!=102 && P[2].State!=103 && P[2].State!=104 && P[2].State!=105 && P[2].State!=106 //EXCESSOES DE NON LOOPS
&& P[2].State!=151 && P[2].State!=152 && P[2].State!=153 && P[2].State!=154 && P[2].State!=155 && P[2].State!=156 //EXCESSOES DE NON LOOPS
&& P[2].State!=201 && P[2].State!=202 && P[2].State!=203 && P[2].State!=204 && P[2].State!=205 && P[2].State!=206 //EXCESSOES DE NON LOOPS
//&& P[2].State!=300                                                                                              //EXCESSOES DE NON LOOPS
&& P[2].State!=301 && P[2].State!=302 && P[2].State!=303 && P[2].State!=304 && P[2].State!=305 && P[2].State!=306 //EXCESSOES DE NON LOOPS
//&& P[2].State!=310                                                                                              //EXCESSOES DE NON LOOPS
&& P[2].State!=311 && P[2].State!=312 && P[2].State!=313 && P[2].State!=314 && P[2].State!=315 && P[2].State!=316 //EXCESSOES DE NON LOOPS
//&& P[2].State!=320                                                                                              //EXCESSOES DE NON LOOPS
&& P[2].State!=321 && P[2].State!=322 && P[2].State!=323 && P[2].State!=324 && P[2].State!=325 && P[2].State!=326 //EXCESSOES DE NON LOOPS
&& P[2].State!=501 && P[2].State!=502 && P[2].State!=503 && P[2].State!=504 && P[2].State!=505 && P[2].State!=506 //EXCESSOES DE NON LOOPS
&& P[2].State!=507 && P[2].State!=508 && P[2].State!=509 && P[2].State!=511 && P[2].State!=512 && P[2].State!=513 //EXCESSOES DE NON LOOPS
//&& P[2].State!=550                                                                                              //EXCESSOES DE NON LOOPS
&& P[2].State!=552 && P[2].State!=601 && P[2].State!=602 && P[2].State!=603 && P[2].State!=604 && P[2].State!=605 //EXCESSOES DE NON LOOPS
&& P[2].State!=606 && P[2].State!=607 && P[2].State!=608 && P[2].State!=611 && P[2].State!=612 && P[2].State!=613 //EXCESSOES DE NON LOOPS
&& P[2].State!=616 && P[2].State!=617 && P[2].State!=618
&& P[2].State!=700 && P[2].State!=710 && P[2].State!=720 && P[2].State!=730
&& P[2].State!=740 && P[2].State!=750 && P[2].State!=760
&& P[2].State!=770 && P[2].State!=780 && P[2].State!=790
) //EXCESSOES DE NON LOOPS
{ P[2].IndexAnim=0; P2_FrameTime=P2_FrameTime_00; P[2].StartFrame=timer; Draw_CHBoxes_P2(); } //-loop
/* <P2> Non Loops FSM! */
//movimentos sem loop terminam e carregam outros movimentos, exemplo: final do soco fraco [101] carrega movimento parado [100]
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==101) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==102) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==103) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==104) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==105) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==106) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==151) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==152) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==153) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==154) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==155) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==156) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==201) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==202) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==203) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==204) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==205) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==206) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==501) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==502) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==503) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==504) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==505) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==506) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==511) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==512) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==513) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==601) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==552) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==602) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==603) { P[2].StartFrame=timer; PLAYER_STATE(2, 310, 0, P[2].TotalDeFramesMov[310]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==604) { P[2].StartFrame=timer; PLAYER_STATE(2, 300, 0, P[2].TotalDeFramesMov[300]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==605) { P[2].StartFrame=timer; PLAYER_STATE(2, 320, 0, P[2].TotalDeFramesMov[320]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==606) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==607) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==608) { P[2].StartFrame=timer; PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==700) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==710) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==720) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==730) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==740) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==750) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==760) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==770) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==780) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==790) { P[2].StartFrame=timer; PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]); Draw_CHBoxes_P2(); }

//Anim Infinita
//if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==300) {  }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==301) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 301, P[2].IndexAnim, P[2].TotalDeFramesMov[301]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==302) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 302, P[2].IndexAnim, P[2].TotalDeFramesMov[302]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==303) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 303, P[2].IndexAnim, P[2].TotalDeFramesMov[303]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==304) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 304, P[2].IndexAnim, P[2].TotalDeFramesMov[304]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==305) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 305, P[2].IndexAnim, P[2].TotalDeFramesMov[305]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==306) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(1, 306, 0, P[2].TotalDeFramesMov[306]); Draw_CHBoxes_P2(); }
//if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==310) {  }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==311) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 311, P[2].IndexAnim, P[2].TotalDeFramesMov[311]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==312) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 312, P[2].IndexAnim, P[2].TotalDeFramesMov[312]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==313) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 313, P[2].IndexAnim, P[2].TotalDeFramesMov[313]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==314) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 314, P[2].IndexAnim, P[2].TotalDeFramesMov[314]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==315) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 315, P[2].IndexAnim, P[2].TotalDeFramesMov[315]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==316) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 316, P[2].IndexAnim, P[2].TotalDeFramesMov[316]); Draw_CHBoxes_P2(); }
//if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==320) {  }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==321) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 321, P[2].IndexAnim, P[2].TotalDeFramesMov[321]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==322) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 322, P[2].IndexAnim, P[2].TotalDeFramesMov[322]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==323) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 323, P[2].IndexAnim, P[2].TotalDeFramesMov[323]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==324) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 324, P[2].IndexAnim, P[2].TotalDeFramesMov[324]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==325) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 325, P[2].IndexAnim, P[2].TotalDeFramesMov[325]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==326) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 326, P[2].IndexAnim, P[2].TotalDeFramesMov[326]); Draw_CHBoxes_P2(); }
//if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==507) {  }
//if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==550) {  }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==611) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 611, P[2].IndexAnim, P[2].TotalDeFramesMov[611]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==612) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 612, P[2].IndexAnim, P[2].TotalDeFramesMov[612]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==613) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 613, P[2].IndexAnim, P[2].TotalDeFramesMov[613]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==616) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 616, P[2].IndexAnim, P[2].TotalDeFramesMov[616]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==617) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 617, P[2].IndexAnim, P[2].TotalDeFramesMov[617]); Draw_CHBoxes_P2(); }
if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==618) { P[2].IndexAnim--; P[2].StartFrame=timer; PLAYER_STATE(2, 618, P[2].IndexAnim, P[2].TotalDeFramesMov[618]); Draw_CHBoxes_P2(); }

//garante que o IndexAnim nunca vai ser maior que TotalFrames
if (P[2].IndexAnim>P[2].TotalFrames){ P[2].IndexAnim=P[2].TotalFrames; }

///////////////////////////////////////////////////////////////////////////
// ATUADORES --------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////

int LIMITEINF=0;
int LIMITESUP=0;

if(Atuador1==1){ LIMITEINF=1; } else { LIMITEINF=2; }
if(Atuador2==1){ LIMITESUP=2; } else { LIMITESUP=1; }

//---
for(int ind=LIMITEINF; ind<=LIMITESUP; ind++){

if(Atuador1==1){ Atuador1=0; }
if(Atuador2==1){ Atuador2=0; }

//localiza a linha especifica no TableAtlas
int line=0;
for(int indx=0;indx<=500;indx++){
if( P[ind].State==P[ind].TableAtlas[indx][0]
&& P[ind].IndexAnim==P[ind].TableAtlas[indx][1]){
line=P[ind].TableAtlas[indx][2];
}
if(line!=0) break;
}

//somente aplica os atuadores do 2 frame em diante da animacao
//lembrando que o atuador do primeiro frame é carregado no LOAD_PLAYER
if( P[ind].IndexAnim>0 ){

//X//
if(P[ind].TableAtlas[line][6]!=-5555){
P[ind].x+=P[ind].TableAtlas[line][6];
}

//Y//
if(P[ind].TableAtlas[line][7]!=-5555){
P[ind].y+=P[ind].TableAtlas[line][7];
}

//Vspeed//
if(P[ind].TableAtlas[line][8]!=-5555){
P[ind].Vspeed=P[ind].TableAtlas[line][8];
}

//Hspeed//
if(P[ind].TableAtlas[line][9]!=-5555){
P[ind].Hspeed=P[ind].TableAtlas[line][9];
if(P[ind].Lado==-1) { P[ind].Hspeed=P[ind].Hspeed*-1; }
}

//Gravity//
if(P[ind].TableAtlas[line][10]!=-5555){
P[ind].Gravity+=P[ind].TableAtlas[line][10];
}

//Friction//
if(P[ind].TableAtlas[line][11]!=-5555){
P[ind].Friction+=P[ind].TableAtlas[line][11];
}

//Energy Change//
if(P[ind].TableAtlas[line][12]!=-5555){
P[ind].Energy+=P[ind].TableAtlas[line][12];
}
if (P[ind].Energy>1000) { P[ind].Energy=1000; }
if (P[ind].Energy<0) { P[ind].Energy=0; }

//Special Change//
if(P[ind].TableAtlas[line][13]!=-5555){
P[ind].Special+=P[ind].TableAtlas[line][13];
}
if (P[ind].Special>1000) { P[ind].Special=1000; }
if (P[ind].Special<0) { P[ind].Special=0; }

//Visible//
if(P[ind].TableAtlas[line][14]!=-5555){
P[ind].Visible=P[ind].TableAtlas[line][14];
}

//RoomLimit// nao implementado
if(P[ind].TableAtlas[line][15]!=-5555){
//P[ind].RoomLimit=P[ind].TableAtlas[line][15];
}

//HitType//
if(P[ind].TableAtlas[line][16]!=-5555){
int a=P[ind].TableAtlas[line][16];
if(a==1) { strcpy(P[ind].HitType, "Normal"); }
if(a==2) { strcpy(P[ind].HitType, "Fall");}
}

//ChangeState//
if(P[ind].TableAtlas[line][17]!=-5555){
int set=P[ind].TableAtlas[line][17];
P[ind].StartFrame=timer; P[ind].MovStartFrame=P[ind].StartFrame;
PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
}

//Freeze// nao implementado
if(P[ind].TableAtlas[line][18]!=-5555){
//P[ind].TableAtlas[line][18];
}

//Color// nao implementado
if(P[ind].TableAtlas[line][19]!=-5555){
//P[ind].TableAtlas[line][19];
}

//HitStack//
if(P[ind].TableAtlas[line][20]!=-5555){
int a=P[ind].TableAtlas[line][20];
if(a==1) { strcpy(P[ind].HitStack, "Single"); }
if(a==2) { strcpy(P[ind].HitStack, "Multi"); }
}
}

}
//---

///////////////////////////////////////////////////////////////////////////
// DESENHA PERSONAGENS NA TELA --------------------------------------------
///////////////////////////////////////////////////////////////////////////

//desenha o cenario em render 2X em bufferx
// Note: bufferx dimensions are already set when created
backend_stretch_blit(bg_test, bufferx, 0, 0, backend_bitmap_width(bg_test), backend_bitmap_height(bg_test), 0, 0, backend_bitmap_width(bufferx), backend_bitmap_height(bufferx));

//---VScreen+Zoom---//

if(op_Zoom==1) {
if( (VScreen_h-VScreen_y)/backend_bitmap_height(bufferx) < 1 ) {
ZoomMaximoAtingido=0;
}
else {
if(ZoomMaximoAtingido==0){
Zoom_eixo=(VScreen_w-VScreen_x)/2;
}
ZoomMaximoAtingido=1; //limite max do zoom atingido
}
}

if(P[1].x<MeioDaTela) { VScreen_FatorZoom=abs((P[1].x-80)-(P[2].x+80)); } //no inicio do round o valor é 320 }
else                  { VScreen_FatorZoom=abs((P[2].x-80)-(P[1].x+80)); } //no inicio do round o valor é 320 }
if(VScreen_FatorZoom<=250) { VScreen_FatorZoom=250; } //limita a diminuicao do zoom

if(ZoomMaximoAtingido==0){
//VS_x
VScreen_x=MeioDaTela*2-VScreen_FatorZoom;
if(VScreen_x>backend_bitmap_width(bufferx)-VScreen_FatorZoom*2) VScreen_x=backend_bitmap_width(bufferx)-VScreen_FatorZoom*2;
if(VScreen_x<0) { VScreen_x=0; }
//VS_y
VScreen_y=backend_bitmap_height(bg_test)*2-(480*VScreen_FatorZoom/320);
VScreen_y+=P[1].ConstanteY+P[2].ConstanteY;
if(VScreen_y<0) { VScreen_y=0; }
//VS_w, VS_h
VScreen_w=VScreen_x+VScreen_FatorZoom*2;
if(VScreen_w>backend_bitmap_width(bufferx)) { VScreen_w=backend_bitmap_width(bufferx); }
VScreen_h=VScreen_y+(480*VScreen_FatorZoom/320);
//VS_x2
VScreen_x2=VScreen_w-VScreen_x;
if(VScreen_x2>backend_bitmap_width(bufferx)) { VScreen_x2=backend_bitmap_width(bufferx); }
//VS_y2
VScreen_y2=VScreen_h-VScreen_y;
if(VScreen_y2>backend_bitmap_height(bufferx)) { VScreen_y2=backend_bitmap_height(bufferx); }
}

//desliga o efeito de zoom
if(op_Zoom==0) { if(ZoomMaximoAtingido==0){Zoom_eixo=(VScreen_w-VScreen_x)/2;} ZoomMaximoAtingido=1; }

if(ZoomMaximoAtingido==1){
VScreen_x=MeioDaTela*2-Zoom_eixo;
if(VScreen_x<0) { VScreen_x=0; }
if((VScreen_x+Zoom_eixo*2)>backend_bitmap_width(bufferx)) { VScreen_x=backend_bitmap_width(bufferx)-Zoom_eixo*2; }
if(op_Zoom==1){
//calcular a reentrada do zoom
int ZVScreen_y;
int ZVScreen_h;
//VS_y
ZVScreen_y=backend_bitmap_height(bg_test)*2-(480*VScreen_FatorZoom/320);
ZVScreen_y+=P[1].ConstanteY+P[2].ConstanteY;
if(ZVScreen_y<0) { ZVScreen_y=0; }
//VS_h
ZVScreen_h=ZVScreen_y+(480*VScreen_FatorZoom/320);
//ativa o zoom in
if( (ZVScreen_h-ZVScreen_y)/backend_bitmap_height(bufferx) < 1 ) {
ZoomMaximoAtingido=0;
VScreen_h=ZVScreen_h;
VScreen_y=ZVScreen_y;
}
}
}
//---fim de VScreen+Zoom---//

int ShakeTemp1=ShakeDist;
int ShakeTemp2=ShakeDist;
if (P2HitPause==0) { ShakeTemp1=0; }
if (P1HitPause==0) { ShakeTemp2=0; }
int carga; //indexador para o SprAtlas

//define a prioridade de desenho, quem ataca é desenhado por cima do oponente
for(int ind=1;ind<=2;ind++){
if(
/*P1_HitBox_tot>0 || */
P[ind].State==101 || P[ind].State==102 || P[ind].State==103 ||
P[ind].State==104 || P[ind].State==105 || P[ind].State==106 ||
P[ind].State==151 || P[ind].State==152 || P[ind].State==153 ||
P[ind].State==154 || P[ind].State==155 || P[ind].State==156 ||
P[ind].State==201 || P[ind].State==202 || P[ind].State==203 ||
P[ind].State==204 || P[ind].State==205 || P[ind].State==206 ||
P[ind].State==211 || P[ind].State==212 || P[ind].State==213 ||
P[ind].State==214 || P[ind].State==215 || P[ind].State==216 ||
P[ind].State==221 || P[ind].State==222 || P[ind].State==223 ||
P[ind].State==224 || P[ind].State==225 || P[ind].State==226 ||
P[ind].State==201 || P[ind].State==202 || P[ind].State==203 ||
P[ind].State==204 || P[ind].State==205 || P[ind].State==206 ||
P[ind].State==211 || P[ind].State==212 || P[ind].State==213 ||
P[ind].State==214 || P[ind].State==215 || P[ind].State==216 ||
P[ind].State==221 || P[ind].State==222 || P[ind].State==223 ||
P[ind].State==224 || P[ind].State==225 || P[ind].State==226 ||
P[ind].State==301 || P[ind].State==302 || P[ind].State==303 ||
P[ind].State==304 || P[ind].State==305 || P[ind].State==306 ||
P[ind].State==311 || P[ind].State==312 || P[ind].State==313 ||
P[ind].State==314 || P[ind].State==315 || P[ind].State==316 ||
P[ind].State==321 || P[ind].State==322 || P[ind].State==323 ||
P[ind].State==324 || P[ind].State==325 || P[ind].State==326 ||
P[ind].State==411 || P[ind].State==412 || P[ind].State==413 ||
P[ind].State==414 || P[ind].State==415 || P[ind].State==416 ||
P[ind].State==421 || P[ind].State==422 || P[ind].State==423 ||
P[ind].State==424 || P[ind].State==425 || P[ind].State==426 || P[ind].State==480 ||
P[ind].State==611 || P[ind].State==612 || P[ind].State==613 ||
P[ind].State==701 || P[ind].State==702 || P[ind].State==703 ||
P[ind].State==704 || P[ind].State==705 || P[ind].State==706 ||
P[ind].State==707 || P[ind].State==708 || P[ind].State==709 || P[ind].State==710 ||
P[ind].State==711 || P[ind].State==712 || P[ind].State==713 ||
P[ind].State==714 || P[ind].State==715 || P[ind].State==716 ||
P[ind].State==717 || P[ind].State==718 || P[ind].State==719 || P[ind].State==720 ||
P[ind].State==721 || P[ind].State==722 || P[ind].State==723 ||
P[ind].State==724 || P[ind].State==725 || P[ind].State==726 ||
P[ind].State==727 || P[ind].State==728 || P[ind].State==729 || P[ind].State==730
) { P[ind].Prioridade=1; } else { P[ind].Prioridade=0; }
}

/* CARREGA SPRITE */
for(int indx=1;indx<=2;indx++){
//primeiro, encontra na TableAtlas o indexador correspondente a imagem que vai ser carregada
//relembrando os Valores do TableAtlas...
//[ind][0] State
//[ind][1] Anim
//[ind][2] TotalDeImagensUtilizadas (numero desta imagem no total de imagens do char)
carga=0;
for(int ind=0;ind<=500;ind++){
if( P[indx].State==P[indx].TableAtlas[ind][0]
&& P[indx].IndexAnim==P[indx].TableAtlas[ind][1]){
carga=P[indx].TableAtlas[ind][2];
}
if(carga!=0) break;
}
//depois, pega a imagem SprAtlas correspondente ao indexador, e a coloca em P[n].Spr
backend_blit(P[indx].SprAtlas[carga], P[indx].Spr, 0, 0, 0, 0, backend_bitmap_width(P[indx].SprAtlas[carga]), backend_bitmap_height(P[indx].SprAtlas[carga]));
// Note: bitmap dimensions are accessed via backend functions
P[indx].Altura  = backend_bitmap_height(P[indx].Spr);
P[indx].Largura = backend_bitmap_width(P[indx].Spr);
if (P[indx].State==100) { P[indx].Altura_100=P[indx].Altura; P[indx].Largura_100=P[indx].Largura; }
}

if (op_desenhar_sombras==1){
int x, y;
//sombra p1 preparacao
backend_clear_to_color(P1_Sombra, backend_makecol(255, 0, 255));
backend_clear_to_color(P1_Sombra_Aux, backend_makecol(255, 0, 255));
// Note: bitmap dimensions are immutable; P1_Sombra already has its size
backend_stretch_sprite( P1_Sombra, P[1].Spr, 0, 0, backend_bitmap_width(P[1].Spr), backend_bitmap_height(P[1].Spr)/5 );
for(y = 0; y < backend_bitmap_height(P1_Sombra); y++) {
for(x = 0; x < backend_bitmap_width(P1_Sombra); x++) {
if(backend_getpixel(P1_Sombra, x, y) != backend_makecol(255,000,255)) backend_putpixel(P1_Sombra, x, y, backend_makecol(000,000,000));
}
}
// Note: bitmap dimensions are immutable; P1_Sombra_Aux already has its size
///*debug temp*/backend_clear_to_color(P1_Sombra_Aux, backend_makecol(255, 255, 255));
///*debug temp*/backend_line( P1_Sombra_Aux, 0, 0, backend_bitmap_width(P1_Sombra_Aux), backend_bitmap_height(P1_Sombra_Aux), backend_makecol(000,000,000) );
///*debug temp*/backend_line( P1_Sombra_Aux, 0, backend_bitmap_height(P1_Sombra_Aux), backend_bitmap_width(P1_Sombra_Aux), 0, backend_makecol(000,000,000) );
if(P[1].Visible==1){
if(P[1].Lado== 1){ backend_draw_sprite(P1_Sombra_Aux, P1_Sombra, 0, 0); }
if(P[1].Lado==-1){ backend_draw_sprite_h_flip(P1_Sombra_Aux, P1_Sombra, 0, 0); }
}

//sombra p2 preparacao
backend_clear_to_color(P2_Sombra, backend_makecol(255, 0, 255));
backend_clear_to_color(P2_Sombra_Aux, backend_makecol(255, 0, 255));
// Note: bitmap dimensions are immutable; P2_Sombra already has its size
backend_stretch_sprite( P2_Sombra, P[2].Spr, 0, 0, backend_bitmap_width(P[2].Spr), backend_bitmap_height(P[2].Spr)/5 );
for(y = 0; y < backend_bitmap_height(P2_Sombra); y++) {
for(x = 0; x < backend_bitmap_width(P2_Sombra); x++) {
if(backend_getpixel(P2_Sombra, x, y) != backend_makecol(255,000,255)) backend_putpixel(P2_Sombra, x, y, backend_makecol(000,000,000));
}
}
// Note: bitmap dimensions are immutable; P2_Sombra_Aux already has its size
///*debug temp*/backend_clear_to_color(P2_Sombra_Aux, backend_makecol(255, 255, 255));
///*debug temp*/backend_line( P2_Sombra_Aux, 0, 0, backend_bitmap_width(P2_Sombra_Aux), backend_bitmap_height(P2_Sombra_Aux), backend_makecol(000,000,000) );
///*debug temp*/backend_line( P2_Sombra_Aux, 0, backend_bitmap_height(P2_Sombra_Aux), backend_bitmap_width(P2_Sombra_Aux), 0, backend_makecol(000,000,000) );
if(P[2].Visible==1){
if(P[1].Lado==-1){ backend_draw_sprite(P2_Sombra_Aux, P2_Sombra, 0, 0); }
if(P[1].Lado== 1){ backend_draw_sprite_h_flip(P2_Sombra_Aux, P2_Sombra, 0, 0); }
}

backend_drawing_mode(HM_DRAW_MODE_TRANS,NULL,0,0); backend_set_trans_blender(0,0,0,100);
/* sombra <P2> no bufferx */
if(P[2].Visible==1){
if(P[2].Lado== 1){ backend_draw_trans_sprite(bufferx, P2_Sombra_Aux, (P[2].x*2+ShakeTemp2*2)-P[2].XAlign*2, AlturaPiso*2-backend_bitmap_height(P2_Sombra_Aux)+P[2].ConstanteY/3 ); }
if(P[2].Lado==-1){ backend_draw_trans_sprite(bufferx, P2_Sombra_Aux, ((P[2].x*2+ShakeTemp2*2)-backend_bitmap_width(P[2].Spr))+P[2].XAlign*2, AlturaPiso*2-backend_bitmap_height(P2_Sombra_Aux)+P[2].ConstanteY/3 ); }
}
/* sombra <P1> no bufferx */
if(P[1].Visible==1){
if(P[1].Lado== 1){ backend_draw_trans_sprite(bufferx, P1_Sombra_Aux, (P[1].x*2+ShakeTemp1*2)-P[1].XAlign*2, AlturaPiso*2-backend_bitmap_height(P1_Sombra_Aux)+P[1].ConstanteY/3 ); }
if(P[1].Lado==-1){ backend_draw_trans_sprite(bufferx, P1_Sombra_Aux, ((P[1].x*2+ShakeTemp1*2)-backend_bitmap_width(P[1].Spr))+P[1].XAlign*2, AlturaPiso*2-backend_bitmap_height(P1_Sombra_Aux)+P[1].ConstanteY/3 ); }
}
solid_mode();
}

for(int indp=0;indp<=1;indp++){

/* <P2> desenhado no bufferx */
if(P[2].Visible==1){
if(P[2].Prioridade==indp){
if (P[2].State!=607 && P[2].State!=608) {
if (P[2].Lado== 1) { backend_draw_sprite(bufferx, P[2].Spr, (P[2].x*2+ShakeTemp2*2)-P[2].XAlign*2, P[2].y*2-P[2].YAlign*2); }
if (P[2].Lado==-1) { backend_draw_sprite_h_flip(bufferx, P[2].Spr, ((P[2].x*2+ShakeTemp2*2)-backend_bitmap_width(P[2].Spr))+P[2].XAlign*2, P[2].y*2-P[2].YAlign*2); }
}
else {
if (P[2].Lado==-1) { backend_draw_sprite(bufferx, P[2].Spr, (P[2].x*2+ShakeTemp2*2)-P[2].XAlign*2, P[2].y*2-P[2].YAlign*2); }
if (P[2].Lado== 1) { backend_draw_sprite_h_flip(bufferx, P[2].Spr, ((P[2].x*2+ShakeTemp2*2)-backend_bitmap_width(P[2].Spr))+P[2].XAlign*2, P[2].y*2-P[2].YAlign*2); }
}
}
}

/* <P1> desenhado no bufferx */
if(P[1].Visible==1){
if(P[1].Prioridade==indp){
if (P[1].State!=607 && P[1].State!=608) {
if (P[1].Lado== 1) { backend_draw_sprite(bufferx, P[1].Spr, (P[1].x*2+ShakeTemp1*2)-P[1].XAlign*2, P[1].y*2-P[1].YAlign*2); }
if (P[1].Lado==-1) { backend_draw_sprite_h_flip(bufferx, P[1].Spr, ((P[1].x*2+ShakeTemp1*2)-backend_bitmap_width(P[1].Spr))+P[1].XAlign*2, P[1].y*2-P[1].YAlign*2); }
}
else {
if (P[1].Lado==-1) { backend_draw_sprite(bufferx, P[1].Spr, (P[1].x*2+ShakeTemp1*2)-P[1].XAlign*2, P[1].y*2-P[1].YAlign*2); }
if (P[1].Lado== 1) { backend_draw_sprite_h_flip(bufferx, P[1].Spr, ((P[1].x*2+ShakeTemp1*2)-backend_bitmap_width(P[1].Spr))+P[1].XAlign*2, P[1].y*2-P[1].YAlign*2); }
}
}
}

}

//Controle de Fireball´s
for(int ind=1; ind<=2; ind++){

if(P[ind].QtdeMagias>0){
//primeiro, encontra na TableAtlas o indexador correspondente a imagem que vai ser carregada
carga=0;
for(int indx=0;indx<=500;indx++){
if( Fireball[ind].State==P[ind].TableAtlas[indx][0]
&& Fireball[ind].IndexAnim==P[ind].TableAtlas[indx][1]){
carga=P[ind].TableAtlas[indx][2];
}
if(carga!=0) break;
}
//depois, pega a imagem SprAtlas correspondente ao indexador, e a coloca em Fireball[n].Spr
//precisa otimizar, pois nao é reamente necessario fazer  blit toda hora, apenas na hora de mudar o frame de animacao
backend_blit(P[ind].SprAtlas[carga], Fireball[ind].Spr, 0, 0, 0, 0, backend_bitmap_width(P[ind].SprAtlas[carga]), backend_bitmap_height(P[ind].SprAtlas[carga]));
// Note: Fireball[ind].Spr dimensions are already set
}

if(Fireball[ind].Ativa==1 && P[ind].IndexAnim==Fireball[ind].ThrowFireball){ Fireball[ind].Ativa=2; }
if(Fireball[ind].Ativa==2){
if(Fireball[ind].HSpeed>0){Fireball[ind].x+=Fireball[ind].HSpeed*Fireball[ind].Direcao;} //movimenta a fireball no Eixo X
if(Fireball[ind].VSpeed>0){Fireball[ind].y+=Fireball[ind].VSpeed;} //movimenta a fireball no Eixo Y

//Teste de colisao das Fireballs
//No momento testa apenas 1 Hitbox contra 1 Collision Box
//É necessario armazenar os valores em vetores, matriz bidimensional, para otimizar o codigo

int P1hb_HurtBox01x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x1)*2;
int P1hb_HurtBox01x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x2)*2;
int P1hb_HurtBox01y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox01y1*2);
int P1hb_HurtBox01y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox01y2*2);
int P1hb_HitBox01x1 = ((Fireball[1].x)*2)+(Fireball[1].Direcao*P1_Fireball_HitBox01x1)*2;
int P1hb_HitBox01x2 = ((Fireball[1].x)*2)+(Fireball[1].Direcao*P1_Fireball_HitBox01x2)*2;
int P1hb_HitBox01y1 = (AlturaPiso+(Fireball[1].y*2)+P1_Fireball_HitBox01y1*2);
int P1hb_HitBox01y2 = (AlturaPiso+(Fireball[1].y*2)+P1_Fireball_HitBox01y2*2);
int P2hb_HurtBox01x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x1)*2;
int P2hb_HurtBox01x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x2)*2;
int P2hb_HurtBox01y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox01y1*2);
int P2hb_HurtBox01y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox01y2*2);
int P2hb_HitBox01x1 = ((Fireball[2].x)*2)+(Fireball[2].Direcao*P2_Fireball_HitBox01x1)*2;
int P2hb_HitBox01x2 = ((Fireball[2].x)*2)+(Fireball[2].Direcao*P2_Fireball_HitBox01x2)*2;
int P2hb_HitBox01y1 = (AlturaPiso+(Fireball[2].y*2)+P2_Fireball_HitBox01y1*2);
int P2hb_HitBox01y2 = (AlturaPiso+(Fireball[2].y*2)+P2_Fireball_HitBox01y2*2);

//P1_Fireball x P2 HurtBox
if (P[1].QtdeMagias>0) {
temp1x=P1hb_HitBox01x1; temp1y=P1hb_HitBox01y1; temp2x=P1hb_HitBox01x2; temp2y=P1hb_HitBox01y2;
if (temp1x<=temp2x) { P1hb_HitBox01x1=temp1x; P1hb_HitBox01x2=temp2x; } else { P1hb_HitBox01x1=temp2x; P1hb_HitBox01x2=temp1x; } if (P1hb_HitBox01x1<0) { P1hb_HitBox01x1=0; }
//x1
if (colisaoxP2==0
&& P1_Fireball_HitBox01x1 !=0 && P1_Fireball_HitBox01y1 !=0
&& P1_Fireball_HitBox01x2 !=0 && P1_Fireball_HitBox01y2 !=0
&& P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555
&& P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox01x1) && (P2hb_HurtBox01x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox01y1) && (P2hb_HurtBox01y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) )
{ colisaoxP2Fireball=1; alturadohitp2=1; } else { /* nao acertou o P2 */ }
}
}

//P2_Fireball x P1 HurtBox
if (P[2].QtdeMagias>0) {
temp1x=P2hb_HitBox01x1; temp1y=P2hb_HitBox01y1; temp2x=P2hb_HitBox01x2; temp2y=P2hb_HitBox01y2;
if (temp1x<=temp2x) { P2hb_HitBox01x1=temp1x; P2hb_HitBox01x2=temp2x; } else { P2hb_HitBox01x1=temp2x; P2hb_HitBox01x2=temp1x; } if (P2hb_HitBox01x1<0) { P2hb_HitBox01x1=0; }
//x1
if (colisaoxP1==0
&& P2_Fireball_HitBox01x1 !=0 && P2_Fireball_HitBox01y1 !=0
&& P2_Fireball_HitBox01x2 !=0 && P2_Fireball_HitBox01y2 !=0
&& P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555
&& P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox01x1) && (P1hb_HurtBox01x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox01y1) && (P1hb_HurtBox01y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) )
{ colisaoxP1Fireball=1; alturadohitp2=1; } else { /* nao acertou o P1 */ }
}
}

//som quando a magia acerta
if(colisaoxP1Fireball==1){
if (ForcaDoGolpeP2==1) {backend_play_sample(hitlvl1, 255, 128, 1000, 0);}
if (ForcaDoGolpeP2==2) {backend_play_sample(hitlvl2, 255, 128, 1000, 0);}
if (ForcaDoGolpeP2==3) {backend_play_sample(hitlvl3, 255, 128, 1000, 0);}
}
if(colisaoxP2Fireball==1){
if (ForcaDoGolpeP1==1) {backend_play_sample(hitlvl1, 255, 128, 1000, 0);}
if (ForcaDoGolpeP1==2) {backend_play_sample(hitlvl2, 255, 128, 1000, 0);}
if (ForcaDoGolpeP1==3) {backend_play_sample(hitlvl3, 255, 128, 1000, 0);}
}

//desenha a Fireball na tela (bufferx)
if (Fireball[ind].Direcao== 1) {
backend_draw_sprite(
bufferx,
Fireball[ind].Spr,
(Fireball[ind].x*2)-Fireball[ind].XAlign*2,
Fireball[ind].y*2-Fireball[ind].YAlign*2
);
}
if (Fireball[ind].Direcao==-1) {
backend_draw_sprite_h_flip(
bufferx,
Fireball[ind].Spr,
(Fireball[ind].x*2)-Fireball[ind].XAlign*2,
Fireball[ind].y*2-Fireball[ind].YAlign*2
);
}
//destruir a fireball caso ela passe os limites da tela
//esq
if(Fireball[ind].x<-300){
Fireball[ind].Ativa=0;
Fireball[ind].x=-999;
Fireball[ind].y=-999;
P[ind].QtdeMagias=0;
}
//dir
if(Fireball[ind].x>backend_bitmap_width(bg_test)+300){
Fireball[ind].Ativa=0;
Fireball[ind].x=-999;
Fireball[ind].y=-999;
P[ind].QtdeMagias=0;
}
//circlefill (bufferx, Fireball[ind].x*2, Fireball[ind].y*2, 5, backend_makecol(255,000,000)); //debug de posicionamento fireball
}

if(Fireball[ind].Ativa==2){
//animacao da fireball /no momento limitada a 10frames! Preciso otimizar o codigo.
if (Fireball[ind].IndexAnim== 0) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_00) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_01; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 1) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_01) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_02; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 2) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_02) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_03; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 3) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_03) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_04; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 4) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_04) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_05; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 5) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_05) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_05; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 6) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_06) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_06; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 7) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_07) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_07; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 8) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_08) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_08; Fireball[ind].StartFrame=timer; }}
if (Fireball[ind].IndexAnim== 9) {
if (timer>Fireball[ind].StartFrame+P1_Fireball_FrameTime_09) {
Fireball[ind].IndexAnim++; P1_Fireball_FrameTime=P1_Fireball_FrameTime_10; Fireball[ind].StartFrame=timer; }}
//loop
if(Fireball[ind].IndexAnim>Fireball[ind].TotalFrames){
if(Fireball[ind].State==701){ Fireball[ind].IndexAnim=0; P1_Fireball_FrameTime=P1_FrameTime_00; Fireball[ind].StartFrame=timer; }
if(Fireball[ind].State==702){ Fireball[ind].Ativa=0; }
}
}

}

//desenha / anima hitboxes

if (Qtde_HitBox>0){
for(int ind=1; ind<=Qtde_HitBox; ind++){
if (HitSpark[ind].IndexAnim==0) {
if (timer > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) { HitSpark[ind].IndexAnim++; HitSpark[ind].StartFrame=timer; }}
if (HitSpark[ind].IndexAnim==1) {
if (timer > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) { HitSpark[ind].IndexAnim++; HitSpark[ind].StartFrame=timer; }}
if (HitSpark[ind].IndexAnim==2) {
if (timer > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) { HitSpark[ind].IndexAnim++; HitSpark[ind].StartFrame=timer; }}
if (HitSpark[ind].IndexAnim==3) {
if (timer > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) { HitSpark[ind].IndexAnim++; HitSpark[ind].StartFrame=timer; }}
if (HitSpark[ind].IndexAnim==4) {
if (timer > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) { HitSpark[ind].IndexAnim++; HitSpark[ind].StartFrame=timer; }}
if (HitSpark[ind].IndexAnim==5) {
if (timer > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) { HitSpark[ind].IndexAnim++; HitSpark[ind].StartFrame=timer; }}
if (HitSpark[ind].IndexAnim==6) {
Qtde_HitBox--;
}

backend_clear_to_color(HitSparkspr, backend_makecol(255, 0, 255));
//backend_clear_to_color(HitSpark_Aux, backend_makecol(255, 0, 255));
if (HitSpark[ind].Type==991 && HitSpark[ind].IndexAnim==0) { HitSpark_Aux=spr991_00; }
if (HitSpark[ind].Type==991 && HitSpark[ind].IndexAnim==1) { HitSpark_Aux=spr991_01; }
if (HitSpark[ind].Type==991 && HitSpark[ind].IndexAnim==2) { HitSpark_Aux=spr991_02; }
if (HitSpark[ind].Type==991 && HitSpark[ind].IndexAnim==3) { HitSpark_Aux=spr991_03; }
if (HitSpark[ind].Type==991 && HitSpark[ind].IndexAnim==4) { HitSpark_Aux=spr991_04; }
if (HitSpark[ind].Type==991 && HitSpark[ind].IndexAnim==5) { HitSpark_Aux=spr991_05; }
if (HitSpark[ind].Type==992 && HitSpark[ind].IndexAnim==0) { HitSpark_Aux=spr992_00; }
if (HitSpark[ind].Type==992 && HitSpark[ind].IndexAnim==1) { HitSpark_Aux=spr992_01; }
if (HitSpark[ind].Type==992 && HitSpark[ind].IndexAnim==2) { HitSpark_Aux=spr992_02; }
if (HitSpark[ind].Type==992 && HitSpark[ind].IndexAnim==3) { HitSpark_Aux=spr992_03; }
if (HitSpark[ind].Type==992 && HitSpark[ind].IndexAnim==4) { HitSpark_Aux=spr992_04; }
if (HitSpark[ind].Type==992 && HitSpark[ind].IndexAnim==5) { HitSpark_Aux=spr992_05; }
if (HitSpark[ind].Type==993 && HitSpark[ind].IndexAnim==0) { HitSpark_Aux=spr993_00; }
if (HitSpark[ind].Type==993 && HitSpark[ind].IndexAnim==1) { HitSpark_Aux=spr993_01; }
if (HitSpark[ind].Type==993 && HitSpark[ind].IndexAnim==2) { HitSpark_Aux=spr993_02; }
if (HitSpark[ind].Type==993 && HitSpark[ind].IndexAnim==3) { HitSpark_Aux=spr993_03; }
if (HitSpark[ind].Type==993 && HitSpark[ind].IndexAnim==4) { HitSpark_Aux=spr993_04; }
if (HitSpark[ind].Type==993 && HitSpark[ind].IndexAnim==5) { HitSpark_Aux=spr993_05; }
if (HitSpark[ind].Type==994 && HitSpark[ind].IndexAnim==0) { HitSpark_Aux=spr994_00; }
if (HitSpark[ind].Type==994 && HitSpark[ind].IndexAnim==1) { HitSpark_Aux=spr994_01; }
if (HitSpark[ind].Type==994 && HitSpark[ind].IndexAnim==2) { HitSpark_Aux=spr994_02; }
if (HitSpark[ind].Type==994 && HitSpark[ind].IndexAnim==3) { HitSpark_Aux=spr994_03; }
if (HitSpark[ind].Type==994 && HitSpark[ind].IndexAnim==4) { HitSpark_Aux=spr994_04; }
if (HitSpark[ind].Type==994 && HitSpark[ind].IndexAnim==5) { HitSpark_Aux=spr994_05; }

backend_stretch_blit(HitSpark_Aux , HitSparkspr, 0, 0, backend_bitmap_width(HitSpark_Aux), backend_bitmap_height(HitSpark_Aux), 0, 0, backend_bitmap_width(HitSpark_Aux)*2, backend_bitmap_height(HitSpark_Aux)*2);
backend_draw_sprite(bufferx, HitSparkspr, HitSpark[ind].x+HitSpark[ind].XAlign*2, HitSpark[ind].y+HitSpark[ind].YAlign*2);
}
}

if (Draw_Box==1) {
//Desenha Caixas
if (P1_HurtBox01x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox01x1)*2, ((P[1].y*2)+P1_HurtBox01y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox01x2)*2, ((P[1].y*2)+P1_HurtBox01y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox02x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox02x1)*2, ((P[1].y*2)+P1_HurtBox02y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox02x2)*2, ((P[1].y*2)+P1_HurtBox02y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox03x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox03x1)*2, ((P[1].y*2)+P1_HurtBox03y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox03x2)*2, ((P[1].y*2)+P1_HurtBox03y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox04x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox04x1)*2, ((P[1].y*2)+P1_HurtBox04y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox04x2)*2, ((P[1].y*2)+P1_HurtBox04y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox05x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox05x1)*2, ((P[1].y*2)+P1_HurtBox05y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox05x2)*2, ((P[1].y*2)+P1_HurtBox05y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox06x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox06x1)*2, ((P[1].y*2)+P1_HurtBox06y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox06x2)*2, ((P[1].y*2)+P1_HurtBox06y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox07x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox07x1)*2, ((P[1].y*2)+P1_HurtBox07y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox07x2)*2, ((P[1].y*2)+P1_HurtBox07y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox08x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox08x1)*2, ((P[1].y*2)+P1_HurtBox08y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox08x2)*2, ((P[1].y*2)+P1_HurtBox08y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox09x1!=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox09x1)*2, ((P[1].y*2)+P1_HurtBox09y1*2), (P[1].x*2)+(P[1].Lado*P1_HurtBox09x2)*2, ((P[1].y*2)+P1_HurtBox09y2*2), backend_makecol(000,000,255)); }
if (P1_HitBox01x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox01x1)*2 , ((P[1].y*2)+P1_HitBox01y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox01x2)*2 , ((P[1].y*2)+P1_HitBox01y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox02x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox02x1)*2 , ((P[1].y*2)+P1_HitBox02y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox02x2)*2 , ((P[1].y*2)+P1_HitBox02y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox03x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox03x1)*2 , ((P[1].y*2)+P1_HitBox03y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox03x2)*2 , ((P[1].y*2)+P1_HitBox03y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox04x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox04x1)*2 , ((P[1].y*2)+P1_HitBox04y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox04x2)*2 , ((P[1].y*2)+P1_HitBox04y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox05x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox05x1)*2 , ((P[1].y*2)+P1_HitBox05y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox05x2)*2 , ((P[1].y*2)+P1_HitBox05y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox06x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox06x1)*2 , ((P[1].y*2)+P1_HitBox06y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox06x2)*2 , ((P[1].y*2)+P1_HitBox06y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox07x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox07x1)*2 , ((P[1].y*2)+P1_HitBox07y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox07x2)*2 , ((P[1].y*2)+P1_HitBox07y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox08x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox08x1)*2 , ((P[1].y*2)+P1_HitBox08y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox08x2)*2 , ((P[1].y*2)+P1_HitBox08y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox09x1 !=-5555) { backend_rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox09x1)*2 , ((P[1].y*2)+P1_HitBox09y1*2) , (P[1].x*2)+(P[1].Lado*P1_HitBox09x2)*2 , ((P[1].y*2)+P1_HitBox09y2*2) , backend_makecol(255,000,000)); }

if (P2_HurtBox01x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox01x1)*2, ((P[2].y*2)+P2_HurtBox01y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox01x2)*2, ((P[2].y*2)+P2_HurtBox01y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox02x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox02x1)*2, ((P[2].y*2)+P2_HurtBox02y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox02x2)*2, ((P[2].y*2)+P2_HurtBox02y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox03x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox03x1)*2, ((P[2].y*2)+P2_HurtBox03y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox03x2)*2, ((P[2].y*2)+P2_HurtBox03y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox04x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox04x1)*2, ((P[2].y*2)+P2_HurtBox04y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox04x2)*2, ((P[2].y*2)+P2_HurtBox04y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox05x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox05x1)*2, ((P[2].y*2)+P2_HurtBox05y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox05x2)*2, ((P[2].y*2)+P2_HurtBox05y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox06x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox06x1)*2, ((P[2].y*2)+P2_HurtBox06y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox06x2)*2, ((P[2].y*2)+P2_HurtBox06y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox07x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox07x1)*2, ((P[2].y*2)+P2_HurtBox07y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox07x2)*2, ((P[2].y*2)+P2_HurtBox07y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox08x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox08x1)*2, ((P[2].y*2)+P2_HurtBox08y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox08x2)*2, ((P[2].y*2)+P2_HurtBox08y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox09x1!=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox09x1)*2, ((P[2].y*2)+P2_HurtBox09y1*2), (P[2].x*2)+(P[2].Lado*P2_HurtBox09x2)*2, ((P[2].y*2)+P2_HurtBox09y2*2), backend_makecol(000,000,255)); }
if (P2_HitBox01x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox01x1)*2 , ((P[2].y*2)+P2_HitBox01y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox01x2)*2 , ((P[2].y*2)+P2_HitBox01y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox02x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox02x1)*2 , ((P[2].y*2)+P2_HitBox02y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox02x2)*2 , ((P[2].y*2)+P2_HitBox02y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox03x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox03x1)*2 , ((P[2].y*2)+P2_HitBox03y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox03x2)*2 , ((P[2].y*2)+P2_HitBox03y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox04x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox04x1)*2 , ((P[2].y*2)+P2_HitBox04y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox04x2)*2 , ((P[2].y*2)+P2_HitBox04y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox05x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox05x1)*2 , ((P[2].y*2)+P2_HitBox05y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox05x2)*2 , ((P[2].y*2)+P2_HitBox05y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox06x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox06x1)*2 , ((P[2].y*2)+P2_HitBox06y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox06x2)*2 , ((P[2].y*2)+P2_HitBox06y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox07x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox07x1)*2 , ((P[2].y*2)+P2_HitBox07y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox07x2)*2 , ((P[2].y*2)+P2_HitBox07y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox08x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox08x1)*2 , ((P[2].y*2)+P2_HitBox08y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox08x2)*2 , ((P[2].y*2)+P2_HitBox08y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox09x1 !=+5555) { backend_rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox09x1)*2 , ((P[2].y*2)+P2_HitBox09y1*2) , (P[2].x*2)+(P[2].Lado*P2_HitBox09x2)*2 , ((P[2].y*2)+P2_HitBox09y2*2) , backend_makecol(255,000,000)); }
} //fim Draw_Box

if (Draw_Box==1) {
//desenha caixas com transparencia
backend_drawing_mode(HM_DRAW_MODE_TRANS, 0, 0, 0);
backend_set_trans_blender(0, 0, 0, 77);
//Desenha Caixas
if (P1_HurtBox01x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x1)*2, ((P[1].y*2)+P1_HurtBox01y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x2)*2, ((P[1].y*2)+P1_HurtBox01y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox02x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox02x1)*2, ((P[1].y*2)+P1_HurtBox02y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox02x2)*2, ((P[1].y*2)+P1_HurtBox02y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox03x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox03x1)*2, ((P[1].y*2)+P1_HurtBox03y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox03x2)*2, ((P[1].y*2)+P1_HurtBox03y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox04x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox04x1)*2, ((P[1].y*2)+P1_HurtBox04y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox04x2)*2, ((P[1].y*2)+P1_HurtBox04y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox05x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox05x1)*2, ((P[1].y*2)+P1_HurtBox05y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox05x2)*2, ((P[1].y*2)+P1_HurtBox05y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox06x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox06x1)*2, ((P[1].y*2)+P1_HurtBox06y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox06x2)*2, ((P[1].y*2)+P1_HurtBox06y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox07x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox07x1)*2, ((P[1].y*2)+P1_HurtBox07y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox07x2)*2, ((P[1].y*2)+P1_HurtBox07y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox08x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox08x1)*2, ((P[1].y*2)+P1_HurtBox08y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox08x2)*2, ((P[1].y*2)+P1_HurtBox08y2*2), backend_makecol(000,000,255)); }
if (P1_HurtBox09x1!=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox09x1)*2, ((P[1].y*2)+P1_HurtBox09y1*2), ((P[1].x)*2)+(P[1].Lado*P1_HurtBox09x2)*2, ((P[1].y*2)+P1_HurtBox09y2*2), backend_makecol(000,000,255)); }
if (P1_HitBox01x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox01x1)*2 , ((P[1].y*2)+P1_HitBox01y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox01x2)*2 , ((P[1].y*2)+P1_HitBox01y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox02x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox02x1)*2 , ((P[1].y*2)+P1_HitBox02y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox02x2)*2 , ((P[1].y*2)+P1_HitBox02y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox03x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox03x1)*2 , ((P[1].y*2)+P1_HitBox03y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox03x2)*2 , ((P[1].y*2)+P1_HitBox03y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox04x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox04x1)*2 , ((P[1].y*2)+P1_HitBox04y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox04x2)*2 , ((P[1].y*2)+P1_HitBox04y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox05x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox05x1)*2 , ((P[1].y*2)+P1_HitBox05y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox05x2)*2 , ((P[1].y*2)+P1_HitBox05y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox06x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox06x1)*2 , ((P[1].y*2)+P1_HitBox06y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox06x2)*2 , ((P[1].y*2)+P1_HitBox06y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox07x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox07x1)*2 , ((P[1].y*2)+P1_HitBox07y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox07x2)*2 , ((P[1].y*2)+P1_HitBox07y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox08x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox08x1)*2 , ((P[1].y*2)+P1_HitBox08y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox08x2)*2 , ((P[1].y*2)+P1_HitBox08y2*2) , backend_makecol(255,000,000)); }
if (P1_HitBox09x1 !=-5555) { backend_rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox09x1)*2 , ((P[1].y*2)+P1_HitBox09y1*2) , ((P[1].x)*2)+(P[1].Lado*P1_HitBox09x2)*2 , ((P[1].y*2)+P1_HitBox09y2*2) , backend_makecol(255,000,000)); }

if (P2_HurtBox01x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x1)*2, ((P[2].y*2)+P2_HurtBox01y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x2)*2, ((P[2].y*2)+P2_HurtBox01y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox02x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox02x1)*2, ((P[2].y*2)+P2_HurtBox02y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox02x2)*2, ((P[2].y*2)+P2_HurtBox02y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox03x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox03x1)*2, ((P[2].y*2)+P2_HurtBox03y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox03x2)*2, ((P[2].y*2)+P2_HurtBox03y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox04x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox04x1)*2, ((P[2].y*2)+P2_HurtBox04y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox04x2)*2, ((P[2].y*2)+P2_HurtBox04y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox05x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox05x1)*2, ((P[2].y*2)+P2_HurtBox05y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox05x2)*2, ((P[2].y*2)+P2_HurtBox05y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox06x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox06x1)*2, ((P[2].y*2)+P2_HurtBox06y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox06x2)*2, ((P[2].y*2)+P2_HurtBox06y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox07x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox07x1)*2, ((P[2].y*2)+P2_HurtBox07y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox07x2)*2, ((P[2].y*2)+P2_HurtBox07y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox08x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox08x1)*2, ((P[2].y*2)+P2_HurtBox08y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox08x2)*2, ((P[2].y*2)+P2_HurtBox08y2*2), backend_makecol(000,000,255)); }
if (P2_HurtBox09x1!=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox09x1)*2, ((P[2].y*2)+P2_HurtBox09y1*2), ((P[2].x)*2)+(P[2].Lado*P2_HurtBox09x2)*2, ((P[2].y*2)+P2_HurtBox09y2*2), backend_makecol(000,000,255)); }
if (P2_HitBox01x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox01x1)*2 , ((P[2].y*2)+P2_HitBox01y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox01x2)*2 , ((P[2].y*2)+P2_HitBox01y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox02x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox02x1)*2 , ((P[2].y*2)+P2_HitBox02y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox02x2)*2 , ((P[2].y*2)+P2_HitBox02y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox03x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox03x1)*2 , ((P[2].y*2)+P2_HitBox03y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox03x2)*2 , ((P[2].y*2)+P2_HitBox03y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox04x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox04x1)*2 , ((P[2].y*2)+P2_HitBox04y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox04x2)*2 , ((P[2].y*2)+P2_HitBox04y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox05x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox05x1)*2 , ((P[2].y*2)+P2_HitBox05y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox05x2)*2 , ((P[2].y*2)+P2_HitBox05y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox06x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox06x1)*2 , ((P[2].y*2)+P2_HitBox06y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox06x2)*2 , ((P[2].y*2)+P2_HitBox06y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox07x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox07x1)*2 , ((P[2].y*2)+P2_HitBox07y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox07x2)*2 , ((P[2].y*2)+P2_HitBox07y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox08x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox08x1)*2 , ((P[2].y*2)+P2_HitBox08y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox08x2)*2 , ((P[2].y*2)+P2_HitBox08y2*2) , backend_makecol(255,000,000)); }
if (P2_HitBox09x1 !=+5555) { backend_rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox09x1)*2 , ((P[2].y*2)+P2_HitBox09y1*2) , ((P[2].x)*2)+(P[2].Lado*P2_HitBox09x2)*2 , ((P[2].y*2)+P2_HitBox09y2*2) , backend_makecol(255,000,000)); }
backend_drawing_mode(HM_DRAW_MODE_SOLID, 0, 0, 0);
}

if (Draw_Debug==1) {
backend_line(bufferx, 0, AlturaPiso*2, backend_bitmap_width(bufferx), AlturaPiso*2, backend_makecol(020,020,020));
circlefill (bufferx, P[1].x*2, P[1].y*2, 3, backend_makecol(000,000,000));
circlefill (bufferx, P[1].x*2, P[1].y*2, 1, backend_makecol(255,255,255));
circlefill (bufferx, P[2].x*2, P[2].y*2, 3, backend_makecol(000,000,000));
circlefill (bufferx, P[2].x*2, P[2].y*2, 1, backend_makecol(255,255,255));
backend_textprintf_centre_ex(bufferx, font_debug, MeioDaTela*2+1, AlturaPiso*2-20+1, backend_makecol(000,000,000), -1, "%i", abs(P[1].x-P[2].x) );
backend_textprintf_centre_ex(bufferx, font_debug, MeioDaTela*2, AlturaPiso*2-20, backend_makecol(255,255,255), -1, "%i", abs(P[1].x-P[2].x) );
circlefill (bufferx, MeioDaTela*2, AlturaPiso*2, 3, backend_makecol(255,000,000));
circlefill (bufferx, MeioDaTela*2, AlturaPiso*2, 1, backend_makecol(255,255,255));
}

/*
			// debug de Spark´s
			if(Qtde_HitBox>0){
			backend_textprintf_centre_ex(LayerHUD, font_debug, 320,  50, backend_makecol(255,255,255), -1, "HitSpark[1].x: %i", HitSpark[1].x);
			backend_textprintf_centre_ex(LayerHUD, font_debug, 320,  60, backend_makecol(255,255,255), -1, "HitSpark[1].y: %i", HitSpark[1].y);
			circlefill (bufferx, HitSpark[1].x, HitSpark[1].y, 5, backend_makecol(000,000,255));
			circlefill (bufferx, HitSpark[1].x, HitSpark[1].y, 3, backend_makecol(255,255,255));
			backend_rect(bufferx,
			HitSpark[1].x-HitSpark[1].XAlign*2,
			HitSpark[1].y-HitSpark[1].YAlign*2,
			HitSpark[1].x+HitSpark[1].XAlign*2,
			HitSpark[1].y+HitSpark[1].YAlign*2, 0);
			}
		*/

/////////////////////////////////
// DESENHA BUFFERX em LAYERHUD //
/////////////////////////////////

backend_stretch_blit(bufferx, LayerHUDa, VScreen_x, VScreen_y, VScreen_x2, VScreen_y2, 0, 0, backend_bitmap_width(LayerHUDa), backend_bitmap_height(LayerHUDa));
backend_stretch_blit(bufferx, LayerHUDb, VScreen_x, VScreen_y, VScreen_x2, VScreen_y2, 0, 0, backend_bitmap_width(LayerHUDb), backend_bitmap_height(LayerHUDb));

/////////////////////////////////////////////////////////////////////////////
// DEBUG --------------------------------------------------------------[**08]
/////////////////////////////////////////////////////////////////////////////

// DEBUG DICAS DE CODIGO --------------------------------------------------------------------------------------------------------------------------
// exibir um numero inteiro -> backend_textprintf_centre_ex(LayerHUDa, font_debug, 320,  50, backend_makecol(255,255,255), -1, "Texto: %i", variavel_int);
// exibir um texto / string -> backend_textprintf_centre_ex(LayerHUDa, font_debug, 320,  60, backend_makecol(255,255,255), -1, "Texto: %s", variavel_char);
// exibir caixa de mensagem -> backend_message("SUA MENSAGEM AQUI!");
// exibir caixa de mensagem c/ variaveis numero inteiro -> backend_message("SUA MENSAGEM AQUI! x: %i y: %i", variavelx, variavely);
//-------------------------------------------------------------------------------------------------------------------------------------------------

/*
			//DEBUG TABLEATLAS
			//Use as teclas + e - para visualizar a TableAtlas do P1
			if (backend_key[HM_KEY_PLUS_PAD]) { navAtlas++; if(navAtlas>P[1].TotalDeImagensUtilizadas){navAtlas=P[1].TotalDeImagensUtilizadas;} }
			if (backend_key[HM_KEY_MINUS_PAD]) { navAtlas--; if(navAtlas<0) {navAtlas=0;} }
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 0, 0xff0000, -1, "[%i][%i]", P[1].TableAtlas[navAtlas][0], P[1].TableAtlas[navAtlas][1]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 1, 0xffffff, -1, "NUM_IMG: %i",	P[1].TableAtlas[navAtlas][2]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 2, 0xffffff, -1, "Frame_Time: %i",	P[1].TableAtlas[navAtlas][3]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 3, 0xffffff, -1, "XAlign: %i, YAlign: %i",	P[1].TableAtlas[navAtlas][4], P[1].TableAtlas[navAtlas][5]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 4, 0xffffff, -1, "X: %i, Y: %i",	P[1].TableAtlas[navAtlas][6], P[1].TableAtlas[navAtlas][7]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 5, 0xffffff, -1, "VSpeed: %i, HSpeed: %i",	P[1].TableAtlas[navAtlas][8], P[1].TableAtlas[navAtlas][9]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 6, 0xffffff, -1, "Gravity: %i, Friction: %i",	P[1].TableAtlas[navAtlas][10], P[1].TableAtlas[navAtlas][11]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 7, 0xffffff, -1, "EnergyChange: %i, SpecialChange: %i",	P[1].TableAtlas[navAtlas][12], P[1].TableAtlas[navAtlas][13]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 8, 0xffffff, -1, "Visible: %i, RoomLimit: %i",	P[1].TableAtlas[navAtlas][14], P[1].TableAtlas[navAtlas][15]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 9, 0xffffff, -1, "HitType: %i, ChangeState: %i",	P[1].TableAtlas[navAtlas][16], P[1].TableAtlas[navAtlas][17]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*10, 0xffffff, -1, "Freeze: %i, Color: %i",	P[1].TableAtlas[navAtlas][18], P[1].TableAtlas[navAtlas][19]);
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*11, 0xffffff, -1, "HitStack: %i",	P[1].TableAtlas[navAtlas][20]);

			if (strcmp (P[1].HitStack,"Multi")==0){	backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*15, 0xffffff, -1, "P[1].HitStack: MULTI");	}
			if (strcmp (P[1].HitStack,"Single")==0){ backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*15, 0xffffff, -1, "P[1].HitStack: SINGLE"); }
			backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*17, 0xffffff, -1, "AHitP1: %i", AHitP1);
		*/

//mostra a lista de especiais na tela
if (Draw_Debug==1) {
for(int indp=1; indp<=2; indp++){
for(int ind2=0; ind2<=9; ind2++){
for(int ind1=1; ind1<=16; ind1++){
int espacamentox=20;
int espacamentoy=20;
int mxalign=70;
int myalign=50;
int correcao;
if(indp==2) { correcao=480; espacamentox=espacamentox*-1; } else { correcao=0; }
if(indp==1){
if(P[indp].Special_Inputs[ind2][ind1]== 8) { backend_draw_sprite(LayerHUDa, spr_input_0 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 9) { backend_draw_sprite(LayerHUDa, spr_input_1 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 6) { backend_draw_sprite(LayerHUDa, spr_input_2 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 3) { backend_draw_sprite(LayerHUDa, spr_input_3 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 2) { backend_draw_sprite(LayerHUDa, spr_input_4 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 1) { backend_draw_sprite(LayerHUDa, spr_input_5 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 4) { backend_draw_sprite(LayerHUDa, spr_input_6 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 7) { backend_draw_sprite(LayerHUDa, spr_input_7 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-1) { backend_draw_sprite(LayerHUDa, spr_input_8 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-2) { backend_draw_sprite(LayerHUDa, spr_input_9 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-3) { backend_draw_sprite(LayerHUDa, spr_input_10, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-4) { backend_draw_sprite(LayerHUDa, spr_input_11, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-5) { backend_draw_sprite(LayerHUDa, spr_input_12, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-6) { backend_draw_sprite(LayerHUDa, spr_input_13, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-7) { backend_draw_sprite(LayerHUDa, spr_input_16, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-8) { backend_draw_sprite(LayerHUDa, spr_input_17, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
}
if(indp==2){
if(P[indp].Special_Inputs[ind2][ind1]== 8) { backend_draw_sprite(LayerHUDa, spr_input_0 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 7) { backend_draw_sprite(LayerHUDa, spr_input_1 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 4) { backend_draw_sprite(LayerHUDa, spr_input_2 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 1) { backend_draw_sprite(LayerHUDa, spr_input_3 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 2) { backend_draw_sprite(LayerHUDa, spr_input_4 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 3) { backend_draw_sprite(LayerHUDa, spr_input_5 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 6) { backend_draw_sprite(LayerHUDa, spr_input_6 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]== 9) { backend_draw_sprite(LayerHUDa, spr_input_7 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-1) { backend_draw_sprite(LayerHUDa, spr_input_8 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-2) { backend_draw_sprite(LayerHUDa, spr_input_9 , mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-3) { backend_draw_sprite(LayerHUDa, spr_input_10, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-4) { backend_draw_sprite(LayerHUDa, spr_input_11, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-5) { backend_draw_sprite(LayerHUDa, spr_input_12, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-6) { backend_draw_sprite(LayerHUDa, spr_input_13, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-7) { backend_draw_sprite(LayerHUDa, spr_input_16, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
if(P[indp].Special_Inputs[ind2][ind1]==-8) { backend_draw_sprite(LayerHUDa, spr_input_17, mxalign+ind1*espacamentox+correcao, myalign+ind2*espacamentoy); }
}

}
}
}
}

//FrameData//
if(op_ShowFrameData==1){

//inicializacao
backend_rectfill(LayerHUDa, 10, 10, 630, 140, backend_makecol(040,040,040)); //fundo
int FD_P1_MovFramesTot;
int FD_P2_MovFramesTot;
//zerar no inicio do round
if(timer_rounds==1){
FD_P1_MovFramesTot=0;
FD_P1_Status=0;
FD_P1_Startup=0;
FD_P1_Active=0;
FD_P1_Recovery=0;
FD_P2_MovFramesTot=0;
FD_P2_Status=0;
FD_P2_Startup=0;
FD_P2_Active=0;
FD_P2_Recovery=0;
}

if(P[1].MovStartFrame==P[1].StartFrame){
//inicializacao P1
FD_P1_Status; //1=STARTUP, 2=ACTIVE, 3=RECOVERY
FD_P1_Startup=0;
FD_P1_Active=0;
FD_P1_Recovery=0;
FD_P1_Active_IN=-1;
FD_P1_Active_OUT=-1;
FD_P1_HitBox01x1;
//chbox.ini
sprintf(P[1].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[1].Name);
backend_set_config_file(P[1].Caminho_CHBOX);
//encontra o inicio de Active (active_in)
for(int ind=0; ind<=P[1].TotalFrames; ind++){
if (P[1].IndexAnim<10)  { sprintf(P[1].State_chs, "%i_0%i", P[1].State, ind); }
if (P[1].IndexAnim>=10) { sprintf(P[1].State_chs, "%i_%i", P[1].State, ind); }
FD_P1_HitBox01x1 = backend_get_config_int (P[1].State_chs, "HitBox01x1", -5555 );
if (FD_P1_HitBox01x1!=-5555) { FD_P1_Active_IN=ind; break; }
}
//encontra o final de Active (active_out)
for(int ind=P[1].TotalFrames; ind>=0; ind--){
if (P[1].IndexAnim<10)  { sprintf(P[1].State_chs, "%i_0%i", P[1].State, ind); }
if (P[1].IndexAnim>=10) { sprintf(P[1].State_chs, "%i_%i", P[1].State, ind); }
FD_P1_HitBox01x1 = backend_get_config_int (P[1].State_chs, "HitBox01x1", -5555 );
if (FD_P1_HitBox01x1!=-5555) { FD_P1_Active_OUT=ind; break; }
}
//char.ini
sprintf(P[1].Caminho_CHBOX, "data/chars/%s/char.ini", P[1].Name);
backend_set_config_file(P[1].Caminho_CHBOX);
//soma todos os frames de Startup usando active_in-1
for(int ind=0; ind<=FD_P1_Active_IN-1; ind++){
sprintf(P[1].State_chs, "%i", P[1].State);
char Index_chs[15];
int sum;
if (P[1].IndexAnim<10)  { sprintf(Index_chs, "FrameTime_0%i", ind); }
if (P[1].IndexAnim>=10) { sprintf(Index_chs, "FrameTime_%i" , ind); }
sum = backend_get_config_int (P[1].State_chs, Index_chs, 6 );
if(sum!=-5555) { FD_P1_Startup+=sum; }
}
//soma todos os frames de Recovery usando active_out+1
for(int ind=FD_P1_Active_OUT+1; ind<=P[1].TotalFrames; ind++){
sprintf(P[1].State_chs, "%i", P[1].State);
char Index_chs[15];
int sum;
if (P[1].IndexAnim<10)  { sprintf(Index_chs, "FrameTime_0%i", ind); }
if (P[1].IndexAnim>=10) { sprintf(Index_chs, "FrameTime_%i" , ind); }
sum = backend_get_config_int (P[1].State_chs, Index_chs, 6 );
if(sum!=-5555) { FD_P1_Recovery+=sum; }
}
//soma todos os frames de Active usando o intervalo active_in e active_out
for(int ind=FD_P1_Active_IN; ind<=FD_P1_Active_OUT; ind++){
sprintf(P[1].State_chs, "%i", P[1].State);
char Index_chs[15];
int sum;
if (P[1].IndexAnim<10)  { sprintf(Index_chs, "FrameTime_0%i", ind); }
if (P[1].IndexAnim>=10) { sprintf(Index_chs, "FrameTime_%i" , ind); }
sum = backend_get_config_int (P[1].State_chs, Index_chs, 6 );
if(sum!=-5555) { FD_P1_Active+=sum; }
}
//soma todos os frames deste Mov
FD_P1_MovFramesTot=FD_P1_Startup+FD_P1_Active+FD_P1_Recovery;
}

//define o status do P1
if(timer-P[1].MovStartFrame<FD_P1_Startup) { FD_P1_Status=1; }
if( ((timer-P[1].MovStartFrame)>=FD_P1_Startup) && ((timer-P[1].MovStartFrame)<FD_P1_MovFramesTot-FD_P1_Recovery) ) { FD_P1_Status=2; }
if(timer-P[1].MovStartFrame>=FD_P1_MovFramesTot-FD_P1_Recovery) { FD_P1_Status=3; }
if( timer-P[1].MovStartFrame>=FD_P1_MovFramesTot ) {
FD_P1_Status=0;
FD_P1_Startup=0;
FD_P1_Active=0;
FD_P1_Recovery=0;
FD_P1_MovFramesTot=0;
}
//desenha retangulos: Startup P1
if( FD_P1_Status==1 ){
for(int ind=0; ind<=FD_P1_Startup-1;ind++){
if((timer-P[1].MovStartFrame)>=ind) {
backend_rectfill(LayerHUDa,  86+ 15*ind, 50, 86+ 15+15*ind, 50+15, backend_makecol(000,255,000)); //verde
}
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 51, backend_makecol(050,050,050), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 51, backend_makecol(050,050,050), -1,  "%d", ind+1); }
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 50, backend_makecol(255,255,255), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 50, backend_makecol(255,255,255), -1,  "%d", ind+1); }
backend_rect(LayerHUDa,  86+ 15*ind, 50, 86+ 15+15*ind, 50+15, backend_makecol(255,255,255));
}
}
//desenha retangulos: Active P1
if( FD_P1_Status==2 ){
for(int ind=0; ind<=FD_P1_Active-1;ind++){
if((timer-P[1].MovStartFrame-FD_P1_Startup)>=ind) {
backend_rectfill(LayerHUDa,  86+ 15*ind, 50, 86+ 15+15*ind, 50+15, backend_makecol(255,000,000)); //vermelho
}
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 51, backend_makecol(050,050,050), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 51, backend_makecol(050,050,050), -1,  "%d", ind+1); }
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 50, backend_makecol(255,255,255), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 50, backend_makecol(255,255,255), -1,  "%d", ind+1); }
backend_rect(LayerHUDa,  86+ 15*ind, 50, 86+ 15+15*ind, 50+15, backend_makecol(255,255,255));
}
}
//desenha retangulos: Recovery P1
if( FD_P1_Status==3 ){
for(int ind=0; ind<=FD_P1_Recovery-1;ind++){
if((timer-P[1].MovStartFrame-FD_P1_Startup-FD_P1_Active)>=ind) {
backend_rectfill(LayerHUDa,  86+ 15*ind, 50, 86+ 15+15*ind, 50+15, backend_makecol(255,255,000)); //amarelo
}
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 51, backend_makecol(050,050,050), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 51, backend_makecol(050,050,050), -1,  "%d", ind+1); }
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 50, backend_makecol(255,255,255), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 50, backend_makecol(255,255,255), -1,  "%d", ind+1); }
backend_rect(LayerHUDa,  86+ 15*ind, 50, 86+ 15+15*ind, 50+15, backend_makecol(255,255,255));
}
}

if(P[2].MovStartFrame==P[2].StartFrame){
//inicializacao P2
FD_P2_Status; //1=STARTUP, 2=ACTIVE, 3=RECOVERY
FD_P2_Startup=0;
FD_P2_Active=0;
FD_P2_Recovery=0;
FD_P2_Active_IN=-1;
FD_P2_Active_OUT=-1;
FD_P2_HitBox01x1;
//chbox.ini
sprintf(P[2].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[2].Name);
backend_set_config_file(P[2].Caminho_CHBOX);
//encontra o inicio de Active (active_in)
for(int ind=0; ind<=P[2].TotalFrames; ind++){
if (P[2].IndexAnim<10)  { sprintf(P[2].State_chs, "%i_0%i", P[2].State, ind); }
if (P[2].IndexAnim>=10) { sprintf(P[2].State_chs, "%i_%i", P[2].State, ind); }
FD_P2_HitBox01x1 = backend_get_config_int (P[2].State_chs, "HitBox01x1", -5555 );
if (FD_P2_HitBox01x1!=-5555) { FD_P2_Active_IN=ind; break; }
}
//encontra o final de Active (active_out)
for(int ind=P[2].TotalFrames; ind>=0; ind--){
if (P[2].IndexAnim<10)  { sprintf(P[2].State_chs, "%i_0%i", P[2].State, ind); }
if (P[2].IndexAnim>=10) { sprintf(P[2].State_chs, "%i_%i", P[2].State, ind); }
FD_P2_HitBox01x1 = backend_get_config_int (P[2].State_chs, "HitBox01x1", -5555 );
if (FD_P2_HitBox01x1!=-5555) { FD_P2_Active_OUT=ind; break; }
}
//char.ini
sprintf(P[2].Caminho_CHBOX, "data/chars/%s/char.ini", P[2].Name);
backend_set_config_file(P[2].Caminho_CHBOX);
//soma todos os frames de Startup usando active_in-1
for(int ind=0; ind<=FD_P2_Active_IN-1; ind++){
sprintf(P[2].State_chs, "%i", P[2].State);
char Index_chs[15];
int sum;
if (P[2].IndexAnim<10)  { sprintf(Index_chs, "FrameTime_0%i", ind); }
if (P[2].IndexAnim>=10) { sprintf(Index_chs, "FrameTime_%i" , ind); }
sum = backend_get_config_int (P[2].State_chs, Index_chs, 6 );
if(sum!=-5555) { FD_P2_Startup+=sum; }
}
//soma todos os frames de Recovery usando active_out+1
for(int ind=FD_P2_Active_OUT+1; ind<=P[2].TotalFrames; ind++){
sprintf(P[2].State_chs, "%i", P[2].State);
char Index_chs[15];
int sum;
if (P[2].IndexAnim<10)  { sprintf(Index_chs, "FrameTime_0%i", ind); }
if (P[2].IndexAnim>=10) { sprintf(Index_chs, "FrameTime_%i" , ind); }
sum = backend_get_config_int (P[2].State_chs, Index_chs, 6 );
if(sum!=-5555) { FD_P2_Recovery+=sum; }
}
//soma todos os frames de Active usando o intervalo active_in e active_out
for(int ind=FD_P2_Active_IN; ind<=FD_P2_Active_OUT; ind++){
sprintf(P[2].State_chs, "%i", P[2].State);
char Index_chs[15];
int sum;
if (P[2].IndexAnim<10)  { sprintf(Index_chs, "FrameTime_0%i", ind); }
if (P[2].IndexAnim>=10) { sprintf(Index_chs, "FrameTime_%i" , ind); }
sum = backend_get_config_int (P[2].State_chs, Index_chs, 6 );
if(sum!=-5555) { FD_P2_Active+=sum; }
}
//soma todos os frames deste Mov
FD_P2_MovFramesTot=FD_P2_Startup+FD_P2_Active+FD_P2_Recovery;
}

//define o status do P2
if(timer-P[2].MovStartFrame<FD_P2_Startup) { FD_P2_Status=1; }
if( ((timer-P[2].MovStartFrame)>=FD_P2_Startup) && ((timer-P[2].MovStartFrame)<FD_P2_MovFramesTot-FD_P2_Recovery) ) { FD_P2_Status=2; }
if(timer-P[2].MovStartFrame>=FD_P2_MovFramesTot-FD_P2_Recovery) { FD_P2_Status=3; }
if( timer-P[2].MovStartFrame>=FD_P2_MovFramesTot ) {
FD_P2_Status=0;
FD_P2_Startup=0;
FD_P2_Active=0;
FD_P2_Recovery=0;
FD_P2_MovFramesTot=0;
}
//desenha retangulos: Startup P2
if( FD_P2_Status==1 ){
for(int ind=0; ind<=FD_P2_Startup-1;ind++){
if((timer-P[2].MovStartFrame)>=ind) {
backend_rectfill(LayerHUDa,  86+ 15*ind, 65, 86+ 15+15*ind, 65+15, backend_makecol(000,255,000)); //verde
}
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 66, backend_makecol(050,050,050), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 66, backend_makecol(050,050,050), -1,  "%d", ind+1); }
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 65, backend_makecol(255,255,255), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 65, backend_makecol(255,255,255), -1,  "%d", ind+1); }
backend_rect(LayerHUDa,  86+ 15*ind, 65, 86+ 15+15*ind, 65+15, backend_makecol(255,255,255));
}
}
//desenha retangulos: Active P2
if( FD_P2_Status==2 ){
for(int ind=0; ind<=FD_P2_Active-1;ind++){
if((timer-P[2].MovStartFrame-FD_P2_Startup)>=ind) {
backend_rectfill(LayerHUDa,  86+ 15*ind, 65, 86+ 15+15*ind, 65+15, backend_makecol(255,000,000)); //vermelho
}
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 66, backend_makecol(050,050,050), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 66, backend_makecol(050,050,050), -1,  "%d", ind+1); }
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 65, backend_makecol(255,255,255), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 65, backend_makecol(255,255,255), -1,  "%d", ind+1); }
backend_rect(LayerHUDa,  86+ 15*ind, 65, 86+ 15+15*ind, 65+15, backend_makecol(255,255,255));
}
}
//desenha retangulos: Recovery P2
if( FD_P2_Status==3 ){
for(int ind=0; ind<=FD_P2_Recovery-1;ind++){
if((timer-P[2].MovStartFrame-FD_P2_Startup-FD_P2_Active)>=ind) {
backend_rectfill(LayerHUDa,  86+ 15*ind, 65, 86+ 15+15*ind, 65+15, backend_makecol(255,255,000)); //amarelo
}
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 66, backend_makecol(050,050,050), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 88+ ind*15, 66, backend_makecol(050,050,050), -1,  "%d", ind+1); }
if(ind< 9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 65, backend_makecol(255,255,255), -1, "0%d", ind+1); }
if(ind>=9) { backend_textprintf_ex(LayerHUDa, font_10, 87+ ind*15, 65, backend_makecol(255,255,255), -1,  "%d", ind+1); }
backend_rect(LayerHUDa,  86+ 15*ind, 65, 86+ 15+15*ind, 65+15, backend_makecol(255,255,255));
}
}

//desenha moldura grande
for(int ind=0; ind<=30;ind++){
backend_rect(LayerHUDa,  86+ 15*ind, 50, 86+ 15+15*ind, 50+15, backend_makecol(255,255,255));
backend_rect(LayerHUDa,  86+ 15*ind, 65, 86+ 15+15*ind, 65+15, backend_makecol(255,255,255));
}

//exibe o status
//txt sombra P1
if(FD_P1_Status==0) { backend_textprintf_ex(LayerHUDa, font_10, 88,  81, backend_makecol(0,0,0), -1, "P1 STATUS: ---"); }
if(FD_P1_Status==1) { backend_textprintf_ex(LayerHUDa, font_10, 88,  81, backend_makecol(0,0,0), -1, "P1 STATUS: STARTUP"); }
if(FD_P1_Status==2) { backend_textprintf_ex(LayerHUDa, font_10, 88,  81, backend_makecol(0,0,0), -1, "P1 STATUS: ACTIVE"); }
if(FD_P1_Status==3) { backend_textprintf_ex(LayerHUDa, font_10, 88,  81, backend_makecol(0,0,0), -1, "P1 STATUS: RECOVERY"); }
backend_textprintf_ex(LayerHUDa, font_10, 88,  91, backend_makecol(0,0,0), -1, "P1_Startup: %d", FD_P1_Startup);
backend_textprintf_ex(LayerHUDa, font_10, 88, 101, backend_makecol(0,0,0), -1, "P1_Active: %d", FD_P1_Active);
backend_textprintf_ex(LayerHUDa, font_10, 88, 111, backend_makecol(0,0,0), -1, "P1_Recovery: %d", FD_P1_Recovery);
backend_textprintf_ex(LayerHUDa, font_10, 88, 121, backend_makecol(0,0,0), -1, "P1_FramesTot: %d", FD_P1_MovFramesTot);
//txt P1
if(FD_P1_Status==0) { backend_textprintf_ex(LayerHUDa, font_10, 87,  80, backend_makecol(255,255,255), -1, "P1 STATUS: ---"); }
if(FD_P1_Status==1) { backend_textprintf_ex(LayerHUDa, font_10, 87,  80, backend_makecol(255,255,255), -1, "P1 STATUS: STARTUP"); }
if(FD_P1_Status==2) { backend_textprintf_ex(LayerHUDa, font_10, 87,  80, backend_makecol(255,255,255), -1, "P1 STATUS: ACTIVE"); }
if(FD_P1_Status==3) { backend_textprintf_ex(LayerHUDa, font_10, 87,  80, backend_makecol(255,255,255), -1, "P1 STATUS: RECOVERY"); }
backend_textprintf_ex(LayerHUDa, font_10, 87,  90, backend_makecol(255,255,255), -1, "P1_Startup: %d", FD_P1_Startup);
backend_textprintf_ex(LayerHUDa, font_10, 87, 100, backend_makecol(255,255,255), -1, "P1_Active: %d", FD_P1_Active);
backend_textprintf_ex(LayerHUDa, font_10, 87, 110, backend_makecol(255,255,255), -1, "P1_Recovery: %d", FD_P1_Recovery);
backend_textprintf_ex(LayerHUDa, font_10, 87, 120, backend_makecol(255,255,255), -1, "P1_FramesTot: %d", FD_P1_MovFramesTot);
//txt sombra P2
if(FD_P2_Status==0) { backend_textprintf_ex(LayerHUDa, font_10, 448,  81, backend_makecol(0,0,0), -1, "P2 STATUS: ---"); }
if(FD_P2_Status==1) { backend_textprintf_ex(LayerHUDa, font_10, 448,  81, backend_makecol(0,0,0), -1, "P2 STATUS: STARTUP"); }
if(FD_P2_Status==2) { backend_textprintf_ex(LayerHUDa, font_10, 448,  81, backend_makecol(0,0,0), -1, "P2 STATUS: ACTIVE"); }
if(FD_P2_Status==3) { backend_textprintf_ex(LayerHUDa, font_10, 448,  81, backend_makecol(0,0,0), -1, "P2 STATUS: RECOVERY"); }
backend_textprintf_ex(LayerHUDa, font_10, 448,  91, backend_makecol(0,0,0), -1, "P2_Startup: %d", FD_P2_Startup);
backend_textprintf_ex(LayerHUDa, font_10, 448, 101, backend_makecol(0,0,0), -1, "P2_Active: %d", FD_P2_Active);
backend_textprintf_ex(LayerHUDa, font_10, 448, 111, backend_makecol(0,0,0), -1, "P2_Recovery: %d", FD_P2_Recovery);
backend_textprintf_ex(LayerHUDa, font_10, 448, 121, backend_makecol(0,0,0), -1, "P2_FramesTot: %d", FD_P2_MovFramesTot);
//txt P2
if(FD_P2_Status==0) { backend_textprintf_ex(LayerHUDa, font_10, 447,  80, backend_makecol(255,255,255), -1, "P2 STATUS: ---"); }
if(FD_P2_Status==1) { backend_textprintf_ex(LayerHUDa, font_10, 447,  80, backend_makecol(255,255,255), -1, "P2 STATUS: STARTUP"); }
if(FD_P2_Status==2) { backend_textprintf_ex(LayerHUDa, font_10, 447,  80, backend_makecol(255,255,255), -1, "P2 STATUS: ACTIVE"); }
if(FD_P2_Status==3) { backend_textprintf_ex(LayerHUDa, font_10, 447,  80, backend_makecol(255,255,255), -1, "P2 STATUS: RECOVERY"); }
backend_textprintf_ex(LayerHUDa, font_10, 447,  90, backend_makecol(255,255,255), -1, "P2_Startup: %d", FD_P2_Startup);
backend_textprintf_ex(LayerHUDa, font_10, 447, 100, backend_makecol(255,255,255), -1, "P2_Active: %d", FD_P2_Active);
backend_textprintf_ex(LayerHUDa, font_10, 447, 110, backend_makecol(255,255,255), -1, "P2_Recovery: %d", FD_P2_Recovery);
backend_textprintf_ex(LayerHUDa, font_10, 447, 120, backend_makecol(255,255,255), -1, "P2_FramesTot: %d", FD_P2_MovFramesTot);

} //<-end ShowFrameData

//Nomes dos Personagens ingame
backend_textprintf_ex(       LayerHUDa, font_debug,  49, 26, backend_makecol(000,000,000), -1, "%s", P[1].Name_Display);
backend_textprintf_right_ex( LayerHUDa, font_debug, 593, 26, backend_makecol(000,000,000), -1, "%s", P[2].Name_Display);
backend_textprintf_ex(       LayerHUDa, font_debug,  47, 24, backend_makecol(000,000,000), -1, "%s", P[1].Name_Display);
backend_textprintf_right_ex( LayerHUDa, font_debug, 591, 24, backend_makecol(000,000,000), -1, "%s", P[2].Name_Display);
backend_textprintf_ex(       LayerHUDa, font_debug,  47, 26, backend_makecol(000,000,000), -1, "%s", P[1].Name_Display);
backend_textprintf_right_ex( LayerHUDa, font_debug, 591, 26, backend_makecol(000,000,000), -1, "%s", P[2].Name_Display);
backend_textprintf_ex(       LayerHUDa, font_debug,  49, 24, backend_makecol(000,000,000), -1, "%s", P[1].Name_Display);
backend_textprintf_right_ex( LayerHUDa, font_debug, 593, 24, backend_makecol(000,000,000), -1, "%s", P[2].Name_Display);
backend_textprintf_ex(       LayerHUDa, font_debug,  48, 25, backend_makecol(255,255,255), -1, "%s", P[1].Name_Display);
backend_textprintf_right_ex( LayerHUDa, font_debug, 592, 25, backend_makecol(255,255,255), -1, "%s", P[2].Name_Display);

if (Draw_Input==1)
{
//INPUT SLOTS sombra
if (P[1].bt_slot[1]>0  || P[1].slot[1]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38,  71+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[1],  P[1].slot[1],  P[1].bt_slot[1]  ); }
if (P[1].bt_slot[2]>0  || P[1].slot[2]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38,  91+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[2],  P[1].slot[2],  P[1].bt_slot[2]  ); }
if (P[1].bt_slot[3]>0  || P[1].slot[3]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 111+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[3],  P[1].slot[3],  P[1].bt_slot[3]  ); }
if (P[1].bt_slot[4]>0  || P[1].slot[4]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 131+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[4],  P[1].slot[4],  P[1].bt_slot[4]  ); }
if (P[1].bt_slot[5]>0  || P[1].slot[5]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 151+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[5],  P[1].slot[5],  P[1].bt_slot[5]  ); }
if (P[1].bt_slot[6]>0  || P[1].slot[6]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 171+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[6],  P[1].slot[6],  P[1].bt_slot[6]  ); }
if (P[1].bt_slot[7]>0  || P[1].slot[7]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 191+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[7],  P[1].slot[7],  P[1].bt_slot[7]  ); }
if (P[1].bt_slot[8]>0  || P[1].slot[8]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 211+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[8],  P[1].slot[8],  P[1].bt_slot[8]  ); }
if (P[1].bt_slot[9]>0  || P[1].slot[9]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 231+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[9],  P[1].slot[9],  P[1].bt_slot[9]  ); }
if (P[1].bt_slot[10]>0 || P[1].slot[10]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 251+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[10], P[1].slot[10], P[1].bt_slot[10] ); }
if (P[1].bt_slot[11]>0 || P[1].slot[11]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 271+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[11], P[1].slot[11], P[1].bt_slot[11] ); }
if (P[1].bt_slot[12]>0 || P[1].slot[12]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 291+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[12], P[1].slot[12], P[1].bt_slot[12] ); }
if (P[1].bt_slot[13]>0 || P[1].slot[13]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 311+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[13], P[1].slot[13], P[1].bt_slot[13] ); }
if (P[1].bt_slot[14]>0 || P[1].slot[14]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 331+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[14], P[1].slot[14], P[1].bt_slot[14] ); }
if (P[1].bt_slot[15]>0 || P[1].slot[15]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 351+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[15], P[1].slot[15], P[1].bt_slot[15] ); }
if (P[1].bt_slot[16]>0 || P[1].slot[16]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 38, 371+20, backend_makecol(000,000,000), -1, "[%i]", P[1].t_slot[16], P[1].slot[16], P[1].bt_slot[16] ); }
//INPUT SLOTS
if (P[1].bt_slot[1]>0  || P[1].slot[1]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37,  70+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[1],  P[1].slot[1],  P[1].bt_slot[1]  ); }
if (P[1].bt_slot[2]>0  || P[1].slot[2]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37,  90+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[2],  P[1].slot[2],  P[1].bt_slot[2]  ); }
if (P[1].bt_slot[3]>0  || P[1].slot[3]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 110+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[3],  P[1].slot[3],  P[1].bt_slot[3]  ); }
if (P[1].bt_slot[4]>0  || P[1].slot[4]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 130+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[4],  P[1].slot[4],  P[1].bt_slot[4]  ); }
if (P[1].bt_slot[5]>0  || P[1].slot[5]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 150+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[5],  P[1].slot[5],  P[1].bt_slot[5]  ); }
if (P[1].bt_slot[6]>0  || P[1].slot[6]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 170+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[6],  P[1].slot[6],  P[1].bt_slot[6]  ); }
if (P[1].bt_slot[7]>0  || P[1].slot[7]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 190+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[7],  P[1].slot[7],  P[1].bt_slot[7]  ); }
if (P[1].bt_slot[8]>0  || P[1].slot[8]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 210+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[8],  P[1].slot[8],  P[1].bt_slot[8]  ); }
if (P[1].bt_slot[9]>0  || P[1].slot[9]>0)  { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 230+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[9],  P[1].slot[9],  P[1].bt_slot[9]  ); }
if (P[1].bt_slot[10]>0 || P[1].slot[10]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 250+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[10], P[1].slot[10], P[1].bt_slot[10] ); }
if (P[1].bt_slot[11]>0 || P[1].slot[11]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 270+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[11], P[1].slot[11], P[1].bt_slot[11] ); }
if (P[1].bt_slot[12]>0 || P[1].slot[12]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 290+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[12], P[1].slot[12], P[1].bt_slot[12] ); }
if (P[1].bt_slot[13]>0 || P[1].slot[13]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 310+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[13], P[1].slot[13], P[1].bt_slot[13] ); }
if (P[1].bt_slot[14]>0 || P[1].slot[14]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 330+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[14], P[1].slot[14], P[1].bt_slot[14] ); }
if (P[1].bt_slot[15]>0 || P[1].slot[15]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 350+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[15], P[1].slot[15], P[1].bt_slot[15] ); }
if (P[1].bt_slot[16]>0 || P[1].slot[16]>0) { backend_textprintf_right_ex(LayerHUDa, font_debug, 37, 370+20, backend_makecol(255,255,255), -1, "[%i]", P[1].t_slot[16], P[1].slot[16], P[1].bt_slot[16] ); }

for (int i=0; i<=16; i++) 	{ //Desenha slots usando sprites
if ( P[1].slot[i]==8 ){ backend_draw_sprite(LayerHUDa, spr_input_0, 40, 50+i*20+20); }
if ( P[1].slot[i]==9 ){ backend_draw_sprite(LayerHUDa, spr_input_1, 40, 50+i*20+20); }
if ( P[1].slot[i]==6 ){ backend_draw_sprite(LayerHUDa, spr_input_2, 40, 50+i*20+20); }
if ( P[1].slot[i]==3 ){ backend_draw_sprite(LayerHUDa, spr_input_3, 40, 50+i*20+20); }
if ( P[1].slot[i]==2 ){ backend_draw_sprite(LayerHUDa, spr_input_4, 40, 50+i*20+20); }
if ( P[1].slot[i]==1 ){ backend_draw_sprite(LayerHUDa, spr_input_5, 40, 50+i*20+20); }
if ( P[1].slot[i]==4 ){ backend_draw_sprite(LayerHUDa, spr_input_6, 40, 50+i*20+20); }
if ( P[1].slot[i]==7 ){ backend_draw_sprite(LayerHUDa, spr_input_7, 40, 50+i*20+20); }
int a=P[1].bt_slot[i]%10;
int b=((P[1].bt_slot[i]/10)%10)%10;
int c=((((P[1].bt_slot[i]/10)/10)%10)%10)%10;
if (a!=0 || b!=0 || c!=0) { while (a==0) { a=b; b=c; } }
if (a==b && b==c) { b=0; c=0; }
if (b==c) { c=0; }
if ( a==1 ){ backend_draw_sprite(LayerHUDa, spr_input_8,  60+0*20, 50+i*20+20); }
if ( a==2 ){ backend_draw_sprite(LayerHUDa, spr_input_9,  60+0*20, 50+i*20+20); }
if ( a==3 ){ backend_draw_sprite(LayerHUDa, spr_input_10, 60+0*20, 50+i*20+20); }
if ( a==4 ){ backend_draw_sprite(LayerHUDa, spr_input_11, 60+0*20, 50+i*20+20); }
if ( a==5 ){ backend_draw_sprite(LayerHUDa, spr_input_12, 60+0*20, 50+i*20+20); }
if ( a==6 ){ backend_draw_sprite(LayerHUDa, spr_input_13, 60+0*20, 50+i*20+20); }
if ( a==7 ){ backend_draw_sprite(LayerHUDa, spr_input_14, 60+0*20, 50+i*20+20); }
if ( a==8 ){ backend_draw_sprite(LayerHUDa, spr_input_15, 60+0*20, 50+i*20+20); }
if ( b==1 ){ backend_draw_sprite(LayerHUDa, spr_input_8,  60+1*20, 50+i*20+20); }
if ( b==2 ){ backend_draw_sprite(LayerHUDa, spr_input_9,  60+1*20, 50+i*20+20); }
if ( b==3 ){ backend_draw_sprite(LayerHUDa, spr_input_10, 60+1*20, 50+i*20+20); }
if ( b==4 ){ backend_draw_sprite(LayerHUDa, spr_input_11, 60+1*20, 50+i*20+20); }
if ( b==5 ){ backend_draw_sprite(LayerHUDa, spr_input_12, 60+1*20, 50+i*20+20); }
if ( b==6 ){ backend_draw_sprite(LayerHUDa, spr_input_13, 60+1*20, 50+i*20+20); }
if ( b==7 ){ backend_draw_sprite(LayerHUDa, spr_input_14, 60+1*20, 50+i*20+20); }
if ( b==8 ){ backend_draw_sprite(LayerHUDa, spr_input_15, 60+1*20, 50+i*20+20); }
if ( c==1 ){ backend_draw_sprite(LayerHUDa, spr_input_8,  60+2*20, 50+i*20+20); }
if ( c==2 ){ backend_draw_sprite(LayerHUDa, spr_input_9,  60+2*20, 50+i*20+20); }
if ( c==3 ){ backend_draw_sprite(LayerHUDa, spr_input_10, 60+2*20, 50+i*20+20); }
if ( c==4 ){ backend_draw_sprite(LayerHUDa, spr_input_11, 60+2*20, 50+i*20+20); }
if ( c==5 ){ backend_draw_sprite(LayerHUDa, spr_input_12, 60+2*20, 50+i*20+20); }
if ( c==6 ){ backend_draw_sprite(LayerHUDa, spr_input_13, 60+2*20, 50+i*20+20); }
if ( c==7 ){ backend_draw_sprite(LayerHUDa, spr_input_14, 60+2*20, 50+i*20+20); }
if ( c==8 ){ backend_draw_sprite(LayerHUDa, spr_input_15, 60+2*20, 50+i*20+20); }
}

//INPUT SLOTS P2 sombra
if (P[2].bt_slot[1]>0  || P[2].slot[1]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603,  71+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[1],  P[2].slot[1],  P[2].bt_slot[1]  ); }
if (P[2].bt_slot[2]>0  || P[2].slot[2]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603,  91+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[2],  P[2].slot[2],  P[2].bt_slot[2]  ); }
if (P[2].bt_slot[3]>0  || P[2].slot[3]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603, 111+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[3],  P[2].slot[3],  P[2].bt_slot[3]  ); }
if (P[2].bt_slot[4]>0  || P[2].slot[4]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603, 131+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[4],  P[2].slot[4],  P[2].bt_slot[4]  ); }
if (P[2].bt_slot[5]>0  || P[2].slot[5]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603, 151+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[5],  P[2].slot[5],  P[2].bt_slot[5]  ); }
if (P[2].bt_slot[6]>0  || P[2].slot[6]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603, 171+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[6],  P[2].slot[6],  P[2].bt_slot[6]  ); }
if (P[2].bt_slot[7]>0  || P[2].slot[7]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603, 191+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[7],  P[2].slot[7],  P[2].bt_slot[7]  ); }
if (P[2].bt_slot[8]>0  || P[2].slot[8]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603, 211+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[8],  P[2].slot[8],  P[2].bt_slot[8]  ); }
if (P[2].bt_slot[9]>0  || P[2].slot[9]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 603, 231+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[9],  P[2].slot[9],  P[2].bt_slot[9]  ); }
if (P[2].bt_slot[10]>0 || P[2].slot[10]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 603, 251+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[10], P[2].slot[10], P[2].bt_slot[10] ); }
if (P[2].bt_slot[11]>0 || P[2].slot[11]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 603, 271+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[11], P[2].slot[11], P[2].bt_slot[11] ); }
if (P[2].bt_slot[12]>0 || P[2].slot[12]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 603, 291+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[12], P[2].slot[12], P[2].bt_slot[12] ); }
if (P[2].bt_slot[13]>0 || P[2].slot[13]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 603, 311+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[13], P[2].slot[13], P[2].bt_slot[13] ); }
if (P[2].bt_slot[14]>0 || P[2].slot[14]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 603, 331+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[14], P[2].slot[14], P[2].bt_slot[14] ); }
if (P[2].bt_slot[15]>0 || P[2].slot[15]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 603, 351+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[15], P[2].slot[15], P[2].bt_slot[15] ); }
if (P[2].bt_slot[16]>0 || P[2].slot[16]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 603, 371+20, backend_makecol(000,000,000), -1, "[%i]", P[2].t_slot[16], P[2].slot[16], P[2].bt_slot[16] ); }
//INPUT SLOTS P2
if (P[2].bt_slot[1]>0  || P[2].slot[1]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602,  70+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[1],  P[2].slot[1],  P[2].bt_slot[1]  ); }
if (P[2].bt_slot[2]>0  || P[2].slot[2]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602,  90+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[2],  P[2].slot[2],  P[2].bt_slot[2]  ); }
if (P[2].bt_slot[3]>0  || P[2].slot[3]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602, 110+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[3],  P[2].slot[3],  P[2].bt_slot[3]  ); }
if (P[2].bt_slot[4]>0  || P[2].slot[4]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602, 130+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[4],  P[2].slot[4],  P[2].bt_slot[4]  ); }
if (P[2].bt_slot[5]>0  || P[2].slot[5]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602, 150+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[5],  P[2].slot[5],  P[2].bt_slot[5]  ); }
if (P[2].bt_slot[6]>0  || P[2].slot[6]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602, 170+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[6],  P[2].slot[6],  P[2].bt_slot[6]  ); }
if (P[2].bt_slot[7]>0  || P[2].slot[7]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602, 190+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[7],  P[2].slot[7],  P[2].bt_slot[7]  ); }
if (P[2].bt_slot[8]>0  || P[2].slot[8]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602, 210+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[8],  P[2].slot[8],  P[2].bt_slot[8]  ); }
if (P[2].bt_slot[9]>0  || P[2].slot[9]>0)  { backend_textprintf_ex(LayerHUDa, font_debug, 602, 230+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[9],  P[2].slot[9],  P[2].bt_slot[9]  ); }
if (P[2].bt_slot[10]>0 || P[2].slot[10]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 602, 250+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[10], P[2].slot[10], P[2].bt_slot[10] ); }
if (P[2].bt_slot[11]>0 || P[2].slot[11]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 602, 270+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[11], P[2].slot[11], P[2].bt_slot[11] ); }
if (P[2].bt_slot[12]>0 || P[2].slot[12]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 602, 290+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[12], P[2].slot[12], P[2].bt_slot[12] ); }
if (P[2].bt_slot[13]>0 || P[2].slot[13]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 602, 310+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[13], P[2].slot[13], P[2].bt_slot[13] ); }
if (P[2].bt_slot[14]>0 || P[2].slot[14]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 602, 330+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[14], P[2].slot[14], P[2].bt_slot[14] ); }
if (P[2].bt_slot[15]>0 || P[2].slot[15]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 602, 350+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[15], P[2].slot[15], P[2].bt_slot[15] ); }
if (P[2].bt_slot[16]>0 || P[2].slot[16]>0) { backend_textprintf_ex(LayerHUDa, font_debug, 602, 370+20, backend_makecol(255,255,255), -1, "[%i]", P[2].t_slot[16], P[2].slot[16], P[2].bt_slot[16] ); }

for (int i=0; i<=16; i++) { //Desenha slots usando sprites
if ( P[2].slot[i]==8 ){ backend_draw_sprite(LayerHUDa, spr_input_0, 580, 50+i*20+20); }
if ( P[2].slot[i]==9 ){ backend_draw_sprite(LayerHUDa, spr_input_1, 580, 50+i*20+20); }
if ( P[2].slot[i]==6 ){ backend_draw_sprite(LayerHUDa, spr_input_2, 580, 50+i*20+20); }
if ( P[2].slot[i]==3 ){ backend_draw_sprite(LayerHUDa, spr_input_3, 580, 50+i*20+20); }
if ( P[2].slot[i]==2 ){ backend_draw_sprite(LayerHUDa, spr_input_4, 580, 50+i*20+20); }
if ( P[2].slot[i]==1 ){ backend_draw_sprite(LayerHUDa, spr_input_5, 580, 50+i*20+20); }
if ( P[2].slot[i]==4 ){ backend_draw_sprite(LayerHUDa, spr_input_6, 580, 50+i*20+20); }
if ( P[2].slot[i]==7 ){ backend_draw_sprite(LayerHUDa, spr_input_7, 580, 50+i*20+20); }
int a=P[2].bt_slot[i]%10;
int b=((P[2].bt_slot[i]/10)%10)%10;
int c=((((P[2].bt_slot[i]/10)/10)%10)%10)%10;
if (a!=0 || b!=0 || c!=0) { while (a==0) { a=b; b=c; } }
if (a==b && b==c) { b=0; c=0; }
if (b==c) { c=0; }
if ( a==1 ){ backend_draw_sprite(LayerHUDa, spr_input_8,  560-0*20, 50+i*20+20); }
if ( a==2 ){ backend_draw_sprite(LayerHUDa, spr_input_9,  560-0*20, 50+i*20+20); }
if ( a==3 ){ backend_draw_sprite(LayerHUDa, spr_input_10, 560-0*20, 50+i*20+20); }
if ( a==4 ){ backend_draw_sprite(LayerHUDa, spr_input_11, 560-0*20, 50+i*20+20); }
if ( a==5 ){ backend_draw_sprite(LayerHUDa, spr_input_12, 560-0*20, 50+i*20+20); }
if ( a==6 ){ backend_draw_sprite(LayerHUDa, spr_input_13, 560-0*20, 50+i*20+20); }
if ( a==7 ){ backend_draw_sprite(LayerHUDa, spr_input_14, 560-0*20, 50+i*20+20); }
if ( a==8 ){ backend_draw_sprite(LayerHUDa, spr_input_15, 560-0*20, 50+i*20+20); }
if ( b==1 ){ backend_draw_sprite(LayerHUDa, spr_input_8,  560-1*20, 50+i*20+20); }
if ( b==2 ){ backend_draw_sprite(LayerHUDa, spr_input_9,  560-1*20, 50+i*20+20); }
if ( b==3 ){ backend_draw_sprite(LayerHUDa, spr_input_10, 560-1*20, 50+i*20+20); }
if ( b==4 ){ backend_draw_sprite(LayerHUDa, spr_input_11, 560-1*20, 50+i*20+20); }
if ( b==5 ){ backend_draw_sprite(LayerHUDa, spr_input_12, 560-1*20, 50+i*20+20); }
if ( b==6 ){ backend_draw_sprite(LayerHUDa, spr_input_13, 560-1*20, 50+i*20+20); }
if ( b==7 ){ backend_draw_sprite(LayerHUDa, spr_input_14, 560-1*20, 50+i*20+20); }
if ( b==8 ){ backend_draw_sprite(LayerHUDa, spr_input_15, 560-1*20, 50+i*20+20); }
if ( c==1 ){ backend_draw_sprite(LayerHUDa, spr_input_8,  560-2*20, 50+i*20+20); }
if ( c==2 ){ backend_draw_sprite(LayerHUDa, spr_input_9,  560-2*20, 50+i*20+20); }
if ( c==3 ){ backend_draw_sprite(LayerHUDa, spr_input_10, 560-2*20, 50+i*20+20); }
if ( c==4 ){ backend_draw_sprite(LayerHUDa, spr_input_11, 560-2*20, 50+i*20+20); }
if ( c==5 ){ backend_draw_sprite(LayerHUDa, spr_input_12, 560-2*20, 50+i*20+20); }
if ( c==6 ){ backend_draw_sprite(LayerHUDa, spr_input_13, 560-2*20, 50+i*20+20); }
if ( c==7 ){ backend_draw_sprite(LayerHUDa, spr_input_14, 560-2*20, 50+i*20+20); }
if ( c==8 ){ backend_draw_sprite(LayerHUDa, spr_input_15, 560-2*20, 50+i*20+20); }
}
}//fim Draw_Input

if (Draw_Debug==1) {
backend_rect(LayerHUDa, 320-70, 20+240-115, 320+70, 20+240+135, backend_makecol(255,255,255));
backend_rect(LayerHUDa, 320-75, 20+240-120, 320+75, 20+240+140, backend_makecol(255,255,255));
backend_rect(LayerHUDa, 320-75-150, 20+240-120-5, 320+75+150, 20+240+140+5, backend_makecol(255,255,255));
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+131, backend_makecol(000,000,000), -1, "[F1] DEBUG");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+151, backend_makecol(000,000,000), -1, "[F2] H.BOXES");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+171, backend_makecol(000,000,000), -1, "[F3] INPUTS");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+191, backend_makecol(000,000,000), -1, "[F4] FRAMEDATA");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+211, backend_makecol(000,000,000), -1, "[F5] P1 ENERGY-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+231, backend_makecol(000,000,000), -1, "[F6] P1 ENERGY+");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+251, backend_makecol(000,000,000), -1, "[F7] P2 ENERGY-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+271, backend_makecol(000,000,000), -1, "[F8] P2 ENERGY-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+291, backend_makecol(000,000,000), -1, "[F9] FPS1");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+311, backend_makecol(000,000,000), -1, "[F10] FPS-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+331, backend_makecol(000,000,000), -1, "[F11] FPS+");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 20+351, backend_makecol(000,000,000), -1, "[F12] FPS60");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+130, backend_makecol(255,255,255), -1, "[F1] DEBUG");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+150, backend_makecol(255,255,255), -1, "[F2] H.BOXES");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+170, backend_makecol(255,255,255), -1, "[F3] INPUTS");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+190, backend_makecol(255,255,255), -1, "[F4] FRAMEDATA");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+210, backend_makecol(255,255,255), -1, "[F5] P1 ENERGY-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+230, backend_makecol(255,255,255), -1, "[F6] P1 ENERGY+");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+250, backend_makecol(255,230,255), -1, "[F7] P2 ENERGY-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+270, backend_makecol(255,230,255), -1, "[F8] P2 ENERGY-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+290, backend_makecol(255,255,255), -1, "[F9] FPS1");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+310, backend_makecol(255,255,255), -1, "[F10] FPS-");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+330, backend_makecol(255,255,255), -1, "[F11] FPS+");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 20+350, backend_makecol(255,255,255), -1, "[F12] FPS60");
backend_textprintf_centre_ex(LayerHUDa, font_debug, 321,  86, backend_makecol(000,000,000), -1, "FPS[%d] [%d]", Ctrl_FPS, timer);
backend_textprintf_centre_ex(LayerHUDa, font_debug, 320,  85, backend_makecol(255,255,000), -1, "FPS[%d] [%d]", Ctrl_FPS, timer);
backend_textprintf_right_ex( LayerHUDa, font_debug, 311, 436, backend_makecol(000,000,000), -1, "[P1] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[1].x, P[1].y, abs(P[1].Vspeed), abs(P[1].Hspeed), abs(P[1].Gravity), P[1].TempoPulo); //P1
backend_textprintf_right_ex( LayerHUDa, font_debug, 310, 435, backend_makecol(255,255,255), -1, "[P1] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[1].x, P[1].y, abs(P[1].Vspeed), abs(P[1].Hspeed), abs(P[1].Gravity), P[1].TempoPulo); //P1
backend_textprintf_ex(       LayerHUDa, font_debug, 331, 436, backend_makecol(000,000,000), -1, "[P2] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[2].x, P[2].y, abs(P[2].Vspeed), abs(P[2].Hspeed), abs(P[2].Gravity), P[2].TempoPulo); //P2
backend_textprintf_ex(       LayerHUDa, font_debug, 330, 435, backend_makecol(255,255,255), -1, "[P2] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[2].x, P[2].y, abs(P[2].Vspeed), abs(P[2].Hspeed), abs(P[2].Gravity), P[2].TempoPulo); //P2

//-status do -P1- sombra
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[%i/%i]"    , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[%i/0%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[0%i/%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[0%i/0%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[%i/%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[%i/0%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[0%i/%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[0%i/0%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[%i/%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[%i/0%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[0%i/%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[0%i/0%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[%i/%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[%i/0%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[0%i/%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 171, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[0%i/0%i]", P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
//-status do -P2- sombra
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[%i/%i]"    , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[%i/0%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[0%i/%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/%i]-[0%i/0%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[%i/%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[%i/0%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[0%i/%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[%i/0%i]-[0%i/0%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[%i/%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[%i/0%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[0%i/%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/%i]-[0%i/0%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[%i/%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[%i/0%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[0%i/%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 331, 455, backend_makecol(000,000,000), -1, "[%i]-[0%i/0%i]-[0%i/0%i]", P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }

//-status do -P1-
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[%i/%i]"    , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[%i/0%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[0%i/%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[0%i/0%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[%i/%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[%i/0%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[0%i/%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim>=10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[0%i/0%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[%i/%i]"   , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[%i/0%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[0%i/%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames>=10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[0%i/0%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[%i/%i]"  , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame>=10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[%i/0%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[0%i/%i]" , P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
if ( P[1].IndexAnim< 10 && P[1].TotalFrames< 10 && (timer-P[1].StartFrame< 10) && P1_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 170, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[0%i/0%i]", P[1].State, P[1].IndexAnim, P[1].TotalFrames, (timer-P[1].StartFrame)+1, P1_FrameTime+1); }
//-status do -P2-
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[%i/%i]"    , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[%i/0%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[0%i/%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/%i]-[0%i/0%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[%i/%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[%i/0%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[0%i/%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim>=10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[%i/0%i]-[0%i/0%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[%i/%i]"   , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[%i/0%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[0%i/%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames>=10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/%i]-[0%i/0%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[%i/%i]"  , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame>=10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[%i/0%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime>=10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[0%i/%i]" , P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }
if ( P[2].IndexAnim< 10 && P[2].TotalFrames< 10 && (timer-P[2].StartFrame< 10) && P2_FrameTime< 10 ) { backend_textprintf_ex(LayerHUDa, font_debug, 330, 454, backend_makecol(255,255,255), -1, "[%i]-[0%i/0%i]-[0%i/0%i]", P[2].State, P[2].IndexAnim, P[2].TotalFrames, timer-P[2].StartFrame, P2_FrameTime); }

//exibe relogio sombra
if (Horas>=10 && Minutos>=10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[%d:%d:%d]"   , Horas, Minutos, Segundos); }
if (Horas>=10 && Minutos>=10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[%d:%d:0%d]"  , Horas, Minutos, Segundos); }
if (Horas>=10 && Minutos <10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[%d:0%d:%d]"  , Horas, Minutos, Segundos); }
if (Horas>=10 && Minutos <10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[%d:0%d:0%d]" , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos>=10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[0%d:%d:%d]"  , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos>=10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[0%d:%d:0%d]" , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos <10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[0%d:0%d:%d]" , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos <10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, backend_makecol(000,000,000), -1, "[0%d:0%d:0%d]", Horas, Minutos, Segundos); }
//exibe relogio
if (Horas>=10 && Minutos>=10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[%d:%d:%d]"   , Horas, Minutos, Segundos); }
if (Horas>=10 && Minutos>=10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[%d:%d:0%d]"  , Horas, Minutos, Segundos); }
if (Horas>=10 && Minutos <10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[%d:0%d:%d]"  , Horas, Minutos, Segundos); }
if (Horas>=10 && Minutos <10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[%d:0%d:0%d]" , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos>=10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[0%d:%d:%d]"  , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos>=10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[0%d:%d:0%d]" , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos <10 && Segundos>=10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[0%d:0%d:%d]" , Horas, Minutos, Segundos); }
if (Horas <10 && Minutos <10 && Segundos <10) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, backend_makecol(255,255,255), -1, "[0%d:0%d:0%d]", Horas, Minutos, Segundos); }

//exibe joystick virtual
backend_draw_sprite(LayerHUDa, bt_joystick,   5, 440-400);
backend_draw_sprite(LayerHUDa, bt_joystick, 605, 440-400);
if ( P[1].key_UP_status==1 )     { backend_draw_sprite(LayerHUDa,    bt_up_1, 005+5, 227+215-400); }
if ( P[1].key_UP_status==2 )     { backend_draw_sprite(LayerHUDa,    bt_up_2, 005+5, 227+215-400); }
if ( P[1].key_UP_status==3 )     { backend_draw_sprite(LayerHUDa,    bt_up_3, 005+5, 227+215-400); } if ( P[1].key_UP_status==0 ){  }
if ( P[1].key_DOWN_status==1 )   { backend_draw_sprite(LayerHUDa,  bt_down_1, 005+5, 233+215-400); }
if ( P[1].key_DOWN_status==2 )   { backend_draw_sprite(LayerHUDa,  bt_down_2, 005+5, 233+215-400); }
if ( P[1].key_DOWN_status==3 )   { backend_draw_sprite(LayerHUDa,  bt_down_3, 005+5, 233+215-400); } if ( P[1].key_DOWN_status==0 ){  }
if ( P[1].key_LEFT_status==1 )   { backend_draw_sprite(LayerHUDa,  bt_left_1, 002+5, 230+215-400); }
if ( P[1].key_LEFT_status==2 )   { backend_draw_sprite(LayerHUDa,  bt_left_2, 002+5, 230+215-400); }
if ( P[1].key_LEFT_status==3 )   { backend_draw_sprite(LayerHUDa,  bt_left_3, 002+5, 230+215-400); } if ( P[1].key_LEFT_status==0 ){  }
if ( P[1].key_RIGHT_status==1 )  { backend_draw_sprite(LayerHUDa, bt_right_1, 010+5, 230+215-400); }
if ( P[1].key_RIGHT_status==2 )  { backend_draw_sprite(LayerHUDa, bt_right_2, 010+5, 230+215-400); }
if ( P[1].key_RIGHT_status==3 )  { backend_draw_sprite(LayerHUDa, bt_right_3, 010+5, 230+215-400); } if ( P[1].key_RIGHT_status==0 ){  }
if ( P[1].key_BT1_status==1 )    { backend_draw_sprite(LayerHUDa,       bt_1, 016+5, 229+215-400); }
if ( P[1].key_BT1_status==2 )    { backend_draw_sprite(LayerHUDa,       bt_2, 016+5, 229+215-400); }
if ( P[1].key_BT1_status==3 )    { backend_draw_sprite(LayerHUDa,       bt_3, 016+5, 229+215-400); } if ( P[1].key_BT1_status==0 ){  }
if ( P[1].key_BT2_status==1 )    { backend_draw_sprite(LayerHUDa,       bt_1, 023+5, 229+215-400); }
if ( P[1].key_BT2_status==2 )    { backend_draw_sprite(LayerHUDa,       bt_2, 023+5, 229+215-400); }
if ( P[1].key_BT2_status==3 )    { backend_draw_sprite(LayerHUDa,       bt_3, 023+5, 229+215-400); } if ( P[1].key_BT2_status==0 ){  }
if ( P[1].key_BT3_status==1 )    { backend_draw_sprite(LayerHUDa,       bt_1, 030+5, 229+215-400); }
if ( P[1].key_BT3_status==2 )    { backend_draw_sprite(LayerHUDa,       bt_2, 030+5, 229+215-400); }
if ( P[1].key_BT3_status==3 )    { backend_draw_sprite(LayerHUDa,       bt_3, 030+5, 229+215-400); } if ( P[1].key_BT3_status==0 ){  }
if ( P[1].key_BT4_status==1 )    { backend_draw_sprite(LayerHUDa,       bt_1, 016+5, 234+215-400); }
if ( P[1].key_BT4_status==2 )    { backend_draw_sprite(LayerHUDa,       bt_2, 016+5, 234+215-400); }
if ( P[1].key_BT4_status==3 )    { backend_draw_sprite(LayerHUDa,       bt_3, 016+5, 234+215-400); } if ( P[1].key_BT4_status==0 ){  }
if ( P[1].key_BT5_status==1 )    { backend_draw_sprite(LayerHUDa,       bt_1, 023+5, 234+215-400); }
if ( P[1].key_BT5_status==2 )    { backend_draw_sprite(LayerHUDa,       bt_2, 023+5, 234+215-400); }
if ( P[1].key_BT5_status==3 )    { backend_draw_sprite(LayerHUDa,       bt_3, 023+5, 234+215-400); } if ( P[1].key_BT5_status==0 ){  }
if ( P[1].key_BT6_status==1 )    { backend_draw_sprite(LayerHUDa,       bt_1, 030+5, 234+215-400); }
if ( P[1].key_BT6_status==2 )    { backend_draw_sprite(LayerHUDa,       bt_2, 030+5, 234+215-400); }
if ( P[1].key_BT6_status==3 )    { backend_draw_sprite(LayerHUDa,       bt_3, 030+5, 234+215-400); } if ( P[1].key_BT6_status==0 ){  }
if ( P[1].key_SELECT_status==1 ) { backend_draw_sprite(LayerHUDa,    bt_ss_1, 020+5, 227+215-400); }
if ( P[1].key_SELECT_status==2 ) { backend_draw_sprite(LayerHUDa,    bt_ss_2, 020+5, 227+215-400); }
if ( P[1].key_SELECT_status==3 ) { backend_draw_sprite(LayerHUDa,    bt_ss_3, 020+5, 227+215-400); } if ( P[1].key_SELECT_status==0 ){  }
if ( P[1].key_START_status==1 )  { backend_draw_sprite(LayerHUDa,    bt_ss_1, 026+5, 227+215-400); }
if ( P[1].key_START_status==2 )  { backend_draw_sprite(LayerHUDa,    bt_ss_2, 026+5, 227+215-400); }
if ( P[1].key_START_status==3 )  { backend_draw_sprite(LayerHUDa,    bt_ss_3, 026+5, 227+215-400); } if ( P[1].key_START_status==0 ){  }
}//fim Draw_Debug

if (Draw_Debug==1){
//Hit/Collision Box DATA_INFO
backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 1*10, backend_makecol(000,000,000), -1, "HurtBox Total: %i", P1_HurtBox_tot);
backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 2*10, backend_makecol(000,000,000), -1, "HitBox Total: %i", P1_HitBox_tot);
if (P1_HurtBox01x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 3*10, backend_makecol(000,000,000), -1, "HurtBox1: %i,%i,%i,%i", P1_HurtBox01x1, P1_HurtBox01y1, P1_HurtBox01x2, P1_HurtBox01y2); }
if (P1_HurtBox02x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 4*10, backend_makecol(000,000,000), -1, "HurtBox2: %i,%i,%i,%i", P1_HurtBox02x1, P1_HurtBox02y1, P1_HurtBox02x2, P1_HurtBox02y2); }
if (P1_HurtBox03x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 5*10, backend_makecol(000,000,000), -1, "HurtBox3: %i,%i,%i,%i", P1_HurtBox03x1, P1_HurtBox03y1, P1_HurtBox03x2, P1_HurtBox03y2); }
if (P1_HurtBox04x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 6*10, backend_makecol(000,000,000), -1, "HurtBox4: %i,%i,%i,%i", P1_HurtBox04x1, P1_HurtBox04y1, P1_HurtBox04x2, P1_HurtBox04y2); }
if (P1_HurtBox05x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 7*10, backend_makecol(000,000,000), -1, "HurtBox5: %i,%i,%i,%i", P1_HurtBox05x1, P1_HurtBox05y1, P1_HurtBox05x2, P1_HurtBox05y2); }
if (P1_HurtBox06x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 8*10, backend_makecol(000,000,000), -1, "HurtBox6: %i,%i,%i,%i", P1_HurtBox06x1, P1_HurtBox06y1, P1_HurtBox06x2, P1_HurtBox06y2); }
if (P1_HurtBox07x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 9*10, backend_makecol(000,000,000), -1, "HurtBox7: %i,%i,%i,%i", P1_HurtBox07x1, P1_HurtBox07y1, P1_HurtBox07x2, P1_HurtBox07y2); }
if (P1_HurtBox08x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+10*10, backend_makecol(000,000,000), -1, "HurtBox8: %i,%i,%i,%i", P1_HurtBox08x1, P1_HurtBox08y1, P1_HurtBox08x2, P1_HurtBox08y2); }
if (P1_HurtBox09x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+11*10, backend_makecol(000,000,000), -1, "HurtBox9: %i,%i,%i,%i", P1_HurtBox09x1, P1_HurtBox09y1, P1_HurtBox09x2, P1_HurtBox09y2); }
if (P1_HitBox01x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+12*10, backend_makecol(000,000,000), -1, "HitBox1.: %i,%i,%i,%i", P1_HitBox01x1, P1_HitBox01y1, P1_HitBox01x2, P1_HitBox01y2); }
if (P1_HitBox02x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+13*10, backend_makecol(000,000,000), -1, "HitBox2.: %i,%i,%i,%i", P1_HitBox02x1, P1_HitBox02y1, P1_HitBox02x2, P1_HitBox02y2); }
if (P1_HitBox03x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+14*10, backend_makecol(000,000,000), -1, "HitBox3.: %i,%i,%i,%i", P1_HitBox03x1, P1_HitBox03y1, P1_HitBox03x2, P1_HitBox03y2); }
if (P1_HitBox04x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+15*10, backend_makecol(000,000,000), -1, "HitBox4.: %i,%i,%i,%i", P1_HitBox04x1, P1_HitBox04y1, P1_HitBox04x2, P1_HitBox04y2); }
if (P1_HitBox05x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+16*10, backend_makecol(000,000,000), -1, "HitBox5.: %i,%i,%i,%i", P1_HitBox05x1, P1_HitBox05y1, P1_HitBox05x2, P1_HitBox05y2); }
if (P1_HitBox06x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+17*10, backend_makecol(000,000,000), -1, "HitBox6.: %i,%i,%i,%i", P1_HitBox06x1, P1_HitBox06y1, P1_HitBox06x2, P1_HitBox06y2); }
if (P1_HitBox07x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+18*10, backend_makecol(000,000,000), -1, "HitBox7.: %i,%i,%i,%i", P1_HitBox07x1, P1_HitBox07y1, P1_HitBox07x2, P1_HitBox07y2); }
if (P1_HitBox08x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+19*10, backend_makecol(000,000,000), -1, "HitBox8.: %i,%i,%i,%i", P1_HitBox08x1, P1_HitBox08y1, P1_HitBox08x2, P1_HitBox08y2); }
if (P1_HitBox09x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+20*10, backend_makecol(000,000,000), -1, "HitBox9.: %i,%i,%i,%i", P1_HitBox09x1, P1_HitBox09y1, P1_HitBox09x2, P1_HitBox09y2); }
if (P1_HurtBox01x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 3*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox02x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 4*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox03x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 5*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox04x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 6*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox05x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 7*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox06x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 8*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox07x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+ 9*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox08x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+10*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HurtBox09x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+11*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox01x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+12*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox02x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+13*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox03x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+14*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox04x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+15*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox05x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+16*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox06x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+17*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox07x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+18*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox08x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+19*10, backend_makecol(000,000,000), -1, "----"); }
if (P1_HitBox09x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+20*10, backend_makecol(000,000,000), -1, "----"); }
if (colisaoxP1==1) { backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+21*10, backend_makecol(000,000,000), -1, "COLISAOxP1!!!"); }
backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 1*10, backend_makecol(000,000,000), -1, "HurtBox Total: %i", P2_HurtBox_tot);
backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 2*10, backend_makecol(000,000,000), -1, "HitBox Total: %i", P2_HitBox_tot);
if (P2_HurtBox01x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 3*10, backend_makecol(000,000,000), -1, "HurtBox1: %i,%i,%i,%i", P2_HurtBox01x1, P2_HurtBox01y1, P2_HurtBox01x2, P2_HurtBox01y2); }
if (P2_HurtBox02x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 4*10, backend_makecol(000,000,000), -1, "HurtBox2: %i,%i,%i,%i", P2_HurtBox02x1, P2_HurtBox02y1, P2_HurtBox02x2, P2_HurtBox02y2); }
if (P2_HurtBox03x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 5*10, backend_makecol(000,000,000), -1, "HurtBox3: %i,%i,%i,%i", P2_HurtBox03x1, P2_HurtBox03y1, P2_HurtBox03x2, P2_HurtBox03y2); }
if (P2_HurtBox04x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 6*10, backend_makecol(000,000,000), -1, "HurtBox4: %i,%i,%i,%i", P2_HurtBox04x1, P2_HurtBox04y1, P2_HurtBox04x2, P2_HurtBox04y2); }
if (P2_HurtBox05x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 7*10, backend_makecol(000,000,000), -1, "HurtBox5: %i,%i,%i,%i", P2_HurtBox05x1, P2_HurtBox05y1, P2_HurtBox05x2, P2_HurtBox05y2); }
if (P2_HurtBox06x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 8*10, backend_makecol(000,000,000), -1, "HurtBox6: %i,%i,%i,%i", P2_HurtBox06x1, P2_HurtBox06y1, P2_HurtBox06x2, P2_HurtBox06y2); }
if (P2_HurtBox07x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 9*10, backend_makecol(000,000,000), -1, "HurtBox7: %i,%i,%i,%i", P2_HurtBox07x1, P2_HurtBox07y1, P2_HurtBox07x2, P2_HurtBox07y2); }
if (P2_HurtBox08x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+10*10, backend_makecol(000,000,000), -1, "HurtBox8: %i,%i,%i,%i", P2_HurtBox08x1, P2_HurtBox08y1, P2_HurtBox08x2, P2_HurtBox08y2); }
if (P2_HurtBox09x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+11*10, backend_makecol(000,000,000), -1, "HurtBox9: %i,%i,%i,%i", P2_HurtBox09x1, P2_HurtBox09y1, P2_HurtBox09x2, P2_HurtBox09y2); }
if (P2_HitBox01x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+12*10, backend_makecol(000,000,000), -1, "HitBox1.: %i,%i,%i,%i", P2_HitBox01x1, P2_HitBox01y1, P2_HitBox01x2, P2_HitBox01y2); }
if (P2_HitBox02x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+13*10, backend_makecol(000,000,000), -1, "HitBox2.: %i,%i,%i,%i", P2_HitBox02x1, P2_HitBox02y1, P2_HitBox02x2, P2_HitBox02y2); }
if (P2_HitBox03x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+14*10, backend_makecol(000,000,000), -1, "HitBox3.: %i,%i,%i,%i", P2_HitBox03x1, P2_HitBox03y1, P2_HitBox03x2, P2_HitBox03y2); }
if (P2_HitBox04x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+15*10, backend_makecol(000,000,000), -1, "HitBox4.: %i,%i,%i,%i", P2_HitBox04x1, P2_HitBox04y1, P2_HitBox04x2, P2_HitBox04y2); }
if (P2_HitBox05x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+16*10, backend_makecol(000,000,000), -1, "HitBox5.: %i,%i,%i,%i", P2_HitBox05x1, P2_HitBox05y1, P2_HitBox05x2, P2_HitBox05y2); }
if (P2_HitBox06x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+17*10, backend_makecol(000,000,000), -1, "HitBox6.: %i,%i,%i,%i", P2_HitBox06x1, P2_HitBox06y1, P2_HitBox06x2, P2_HitBox06y2); }
if (P2_HitBox07x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+18*10, backend_makecol(000,000,000), -1, "HitBox7.: %i,%i,%i,%i", P2_HitBox07x1, P2_HitBox07y1, P2_HitBox07x2, P2_HitBox07y2); }
if (P2_HitBox08x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+19*10, backend_makecol(000,000,000), -1, "HitBox8.: %i,%i,%i,%i", P2_HitBox08x1, P2_HitBox08y1, P2_HitBox08x2, P2_HitBox08y2); }
if (P2_HitBox09x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+20*10, backend_makecol(000,000,000), -1, "HitBox9.: %i,%i,%i,%i", P2_HitBox09x1, P2_HitBox09y1, P2_HitBox09x2, P2_HitBox09y2); }
if (P2_HurtBox01x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 3*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox02x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 4*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox03x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 5*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox04x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 6*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox05x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 7*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox06x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 8*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox07x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+ 9*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox08x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+10*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HurtBox09x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+11*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox01x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+12*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox02x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+13*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox03x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+14*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox04x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+15*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox05x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+16*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox06x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+17*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox07x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+18*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox08x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+19*10, backend_makecol(000,000,000), -1, "----"); }
if (P2_HitBox09x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+20*10, backend_makecol(000,000,000), -1, "----"); }
if (colisaoxP2==1) { backend_textprintf_ex(LayerHUDa, font_10, 401, 131+21*10, backend_makecol(000,000,000), -1, "COLISAOxP2!!!"); }
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 1*10, backend_makecol(255,255,255), -1, "HurtBox Total: %i", P1_HurtBox_tot);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 2*10, backend_makecol(255,255,255), -1, "HitBox Total: %i", P1_HitBox_tot);
if (P1_HurtBox01x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 3*10, backend_makecol(255,255,255), -1, "HurtBox1: %i,%i,%i,%i", P1_HurtBox01x1, P1_HurtBox01y1, P1_HurtBox01x2, P1_HurtBox01y2); }
if (P1_HurtBox02x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 4*10, backend_makecol(255,255,255), -1, "HurtBox2: %i,%i,%i,%i", P1_HurtBox02x1, P1_HurtBox02y1, P1_HurtBox02x2, P1_HurtBox02y2); }
if (P1_HurtBox03x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 5*10, backend_makecol(255,255,255), -1, "HurtBox3: %i,%i,%i,%i", P1_HurtBox03x1, P1_HurtBox03y1, P1_HurtBox03x2, P1_HurtBox03y2); }
if (P1_HurtBox04x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 6*10, backend_makecol(255,255,255), -1, "HurtBox4: %i,%i,%i,%i", P1_HurtBox04x1, P1_HurtBox04y1, P1_HurtBox04x2, P1_HurtBox04y2); }
if (P1_HurtBox05x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 7*10, backend_makecol(255,255,255), -1, "HurtBox5: %i,%i,%i,%i", P1_HurtBox05x1, P1_HurtBox05y1, P1_HurtBox05x2, P1_HurtBox05y2); }
if (P1_HurtBox06x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 8*10, backend_makecol(255,255,255), -1, "HurtBox6: %i,%i,%i,%i", P1_HurtBox06x1, P1_HurtBox06y1, P1_HurtBox06x2, P1_HurtBox06y2); }
if (P1_HurtBox07x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 9*10, backend_makecol(255,255,255), -1, "HurtBox7: %i,%i,%i,%i", P1_HurtBox07x1, P1_HurtBox07y1, P1_HurtBox07x2, P1_HurtBox07y2); }
if (P1_HurtBox08x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+10*10, backend_makecol(255,255,255), -1, "HurtBox8: %i,%i,%i,%i", P1_HurtBox08x1, P1_HurtBox08y1, P1_HurtBox08x2, P1_HurtBox08y2); }
if (P1_HurtBox09x1!=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+11*10, backend_makecol(255,255,255), -1, "HurtBox9: %i,%i,%i,%i", P1_HurtBox09x1, P1_HurtBox09y1, P1_HurtBox09x2, P1_HurtBox09y2); }
if (P1_HitBox01x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+12*10, backend_makecol(255,255,255), -1, "HitBox1.: %i,%i,%i,%i", P1_HitBox01x1, P1_HitBox01y1, P1_HitBox01x2, P1_HitBox01y2); }
if (P1_HitBox02x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+13*10, backend_makecol(255,255,255), -1, "HitBox2.: %i,%i,%i,%i", P1_HitBox02x1, P1_HitBox02y1, P1_HitBox02x2, P1_HitBox02y2); }
if (P1_HitBox03x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+14*10, backend_makecol(255,255,255), -1, "HitBox3.: %i,%i,%i,%i", P1_HitBox03x1, P1_HitBox03y1, P1_HitBox03x2, P1_HitBox03y2); }
if (P1_HitBox04x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+15*10, backend_makecol(255,255,255), -1, "HitBox4.: %i,%i,%i,%i", P1_HitBox04x1, P1_HitBox04y1, P1_HitBox04x2, P1_HitBox04y2); }
if (P1_HitBox05x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+16*10, backend_makecol(255,255,255), -1, "HitBox5.: %i,%i,%i,%i", P1_HitBox05x1, P1_HitBox05y1, P1_HitBox05x2, P1_HitBox05y2); }
if (P1_HitBox06x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+17*10, backend_makecol(255,255,255), -1, "HitBox6.: %i,%i,%i,%i", P1_HitBox06x1, P1_HitBox06y1, P1_HitBox06x2, P1_HitBox06y2); }
if (P1_HitBox07x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+18*10, backend_makecol(255,255,255), -1, "HitBox7.: %i,%i,%i,%i", P1_HitBox07x1, P1_HitBox07y1, P1_HitBox07x2, P1_HitBox07y2); }
if (P1_HitBox08x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+19*10, backend_makecol(255,255,255), -1, "HitBox8.: %i,%i,%i,%i", P1_HitBox08x1, P1_HitBox08y1, P1_HitBox08x2, P1_HitBox08y2); }
if (P1_HitBox09x1 !=-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+20*10, backend_makecol(255,255,255), -1, "HitBox9.: %i,%i,%i,%i", P1_HitBox09x1, P1_HitBox09y1, P1_HitBox09x2, P1_HitBox09y2); }
if (P1_HurtBox01x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 3*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox02x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 4*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox03x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 5*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox04x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 6*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox05x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 7*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox06x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 8*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox07x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+ 9*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox08x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+10*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HurtBox09x1==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+11*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox01x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+12*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox02x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+13*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox03x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+14*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox04x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+15*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox05x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+16*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox06x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+17*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox07x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+18*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox08x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+19*10, backend_makecol(255,255,255), -1, "----"); }
if (P1_HitBox09x1 ==-5555) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+20*10, backend_makecol(255,255,255), -1, "----"); }
if (colisaoxP1==1) { backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+21*10, backend_makecol(255,255,000), -1, "COLISAOxP1!!!"); }
backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 1*10, backend_makecol(255,255,255), -1, "HurtBox Total: %i", P2_HurtBox_tot);
backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 2*10, backend_makecol(255,255,255), -1, "HitBox Total: %i", P2_HitBox_tot);
if (P2_HurtBox01x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 3*10, backend_makecol(255,255,255), -1, "HurtBox1: %i,%i,%i,%i", P2_HurtBox01x1, P2_HurtBox01y1, P2_HurtBox01x2, P2_HurtBox01y2); }
if (P2_HurtBox02x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 4*10, backend_makecol(255,255,255), -1, "HurtBox2: %i,%i,%i,%i", P2_HurtBox02x1, P2_HurtBox02y1, P2_HurtBox02x2, P2_HurtBox02y2); }
if (P2_HurtBox03x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 5*10, backend_makecol(255,255,255), -1, "HurtBox3: %i,%i,%i,%i", P2_HurtBox03x1, P2_HurtBox03y1, P2_HurtBox03x2, P2_HurtBox03y2); }
if (P2_HurtBox04x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 6*10, backend_makecol(255,255,255), -1, "HurtBox4: %i,%i,%i,%i", P2_HurtBox04x1, P2_HurtBox04y1, P2_HurtBox04x2, P2_HurtBox04y2); }
if (P2_HurtBox05x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 7*10, backend_makecol(255,255,255), -1, "HurtBox5: %i,%i,%i,%i", P2_HurtBox05x1, P2_HurtBox05y1, P2_HurtBox05x2, P2_HurtBox05y2); }
if (P2_HurtBox06x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 8*10, backend_makecol(255,255,255), -1, "HurtBox6: %i,%i,%i,%i", P2_HurtBox06x1, P2_HurtBox06y1, P2_HurtBox06x2, P2_HurtBox06y2); }
if (P2_HurtBox07x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 9*10, backend_makecol(255,255,255), -1, "HurtBox7: %i,%i,%i,%i", P2_HurtBox07x1, P2_HurtBox07y1, P2_HurtBox07x2, P2_HurtBox07y2); }
if (P2_HurtBox08x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+10*10, backend_makecol(255,255,255), -1, "HurtBox8: %i,%i,%i,%i", P2_HurtBox08x1, P2_HurtBox08y1, P2_HurtBox08x2, P2_HurtBox08y2); }
if (P2_HurtBox09x1!=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+11*10, backend_makecol(255,255,255), -1, "HurtBox9: %i,%i,%i,%i", P2_HurtBox09x1, P2_HurtBox09y1, P2_HurtBox09x2, P2_HurtBox09y2); }
if (P2_HitBox01x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+12*10, backend_makecol(255,255,255), -1, "HitBox1.: %i,%i,%i,%i", P2_HitBox01x1, P2_HitBox01y1, P2_HitBox01x2, P2_HitBox01y2); }
if (P2_HitBox02x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+13*10, backend_makecol(255,255,255), -1, "HitBox2.: %i,%i,%i,%i", P2_HitBox02x1, P2_HitBox02y1, P2_HitBox02x2, P2_HitBox02y2); }
if (P2_HitBox03x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+14*10, backend_makecol(255,255,255), -1, "HitBox3.: %i,%i,%i,%i", P2_HitBox03x1, P2_HitBox03y1, P2_HitBox03x2, P2_HitBox03y2); }
if (P2_HitBox04x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+15*10, backend_makecol(255,255,255), -1, "HitBox4.: %i,%i,%i,%i", P2_HitBox04x1, P2_HitBox04y1, P2_HitBox04x2, P2_HitBox04y2); }
if (P2_HitBox05x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+16*10, backend_makecol(255,255,255), -1, "HitBox5.: %i,%i,%i,%i", P2_HitBox05x1, P2_HitBox05y1, P2_HitBox05x2, P2_HitBox05y2); }
if (P2_HitBox06x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+17*10, backend_makecol(255,255,255), -1, "HitBox6.: %i,%i,%i,%i", P2_HitBox06x1, P2_HitBox06y1, P2_HitBox06x2, P2_HitBox06y2); }
if (P2_HitBox07x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+18*10, backend_makecol(255,255,255), -1, "HitBox7.: %i,%i,%i,%i", P2_HitBox07x1, P2_HitBox07y1, P2_HitBox07x2, P2_HitBox07y2); }
if (P2_HitBox08x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+19*10, backend_makecol(255,255,255), -1, "HitBox8.: %i,%i,%i,%i", P2_HitBox08x1, P2_HitBox08y1, P2_HitBox08x2, P2_HitBox08y2); }
if (P2_HitBox09x1 !=+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+20*10, backend_makecol(255,255,255), -1, "HitBox9.: %i,%i,%i,%i", P2_HitBox09x1, P2_HitBox09y1, P2_HitBox09x2, P2_HitBox09y2); }
if (P2_HurtBox01x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 3*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox02x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 4*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox03x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 5*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox04x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 6*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox05x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 7*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox06x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 8*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox07x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+ 9*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox08x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+10*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HurtBox09x1==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+11*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox01x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+12*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox02x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+13*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox03x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+14*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox04x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+15*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox05x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+16*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox06x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+17*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox07x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+18*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox08x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+19*10, backend_makecol(255,255,255), -1, "----"); }
if (P2_HitBox09x1 ==+5555) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+20*10, backend_makecol(255,255,255), -1, "----"); }
if (colisaoxP2==1) { backend_textprintf_ex(LayerHUDa, font_10, 400, 130+21*10, backend_makecol(255,255,000), -1, "COLISAOxP2!!!"); }

backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+22*10, backend_makecol(000,000,000), -1, "MomentoDoP1: %i" , MomentoDoP1);
backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+23*10, backend_makecol(000,000,000), -1, "ForcaDoGolpe: %i", ForcaDoGolpeP1);
backend_textprintf_right_ex(LayerHUDa, font_10, 241, 131+24*10, backend_makecol(000,000,000), -1, "P1HitPause: %i", P1HitPause);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 131+25*10, backend_makecol(000,000,000), -1, "P1HitType: %s", P[1].HitType_string);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 131+26*10, backend_makecol(000,000,000), -1, "P1HitStack: %s", P[1].HitStack_string);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+22*10, backend_makecol(255,255,255), -1, "MomentoDoP1: %i" , MomentoDoP1);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+23*10, backend_makecol(255,255,255), -1, "ForcaDoGolpe: %i", ForcaDoGolpeP1);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+24*10, backend_makecol(255,255,255), -1, "P1HitPause: %i", P1HitPause);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+25*10, backend_makecol(255,255,255), -1, "P1HitType: %s", P[1].HitType_string);
backend_textprintf_right_ex(LayerHUDa, font_10, 240, 130+26*10, backend_makecol(255,255,255), -1, "P1HitStack: %s", P[1].HitStack_string);
backend_textprintf_ex(LayerHUDa, font_10, 401, 131+22*10, backend_makecol(000,000,000), -1, "MomentoDoP2: %i" , MomentoDoP2);
backend_textprintf_ex(LayerHUDa, font_10, 401, 131+23*10, backend_makecol(000,000,000), -1, "ForcaDoGolpe: %i", ForcaDoGolpeP2);
backend_textprintf_ex(LayerHUDa, font_10, 401, 131+24*10, backend_makecol(000,000,000), -1, "P2HitPause: %i", P2HitPause);
backend_textprintf_ex(LayerHUDa, font_10, 400, 131+25*10, backend_makecol(000,000,000), -1, "P2HitType: %s", P[2].HitType_string);
backend_textprintf_ex(LayerHUDa, font_10, 400, 131+26*10, backend_makecol(000,000,000), -1, "P2HitStack: %s", P[2].HitStack_string);
backend_textprintf_ex(LayerHUDa, font_10, 400, 130+22*10, backend_makecol(255,255,255), -1, "MomentoDoP2: %i" , MomentoDoP2);
backend_textprintf_ex(LayerHUDa, font_10, 400, 130+23*10, backend_makecol(255,255,255), -1, "ForcaDoGolpe: %i", ForcaDoGolpeP2);
backend_textprintf_ex(LayerHUDa, font_10, 400, 130+24*10, backend_makecol(255,255,255), -1, "P2HitPause: %i", P2HitPause);
backend_textprintf_ex(LayerHUDa, font_10, 400, 130+25*10, backend_makecol(255,255,255), -1, "P2HitType: %s", P[2].HitType_string);
backend_textprintf_ex(LayerHUDa, font_10, 400, 130+26*10, backend_makecol(255,255,255), -1, "P2HitStack: %s", P[2].HitStack_string);
}

/*Barras de energia*/

//Barra Red
for(int ind=1;ind<=2;ind++){
if(P[ind].EnergyRedBar==P[ind].Energy){ P[ind].EnergyRedBarSleep=60; }
if(P[ind].EnergyRedBar!=P[ind].Energy){ P[ind].EnergyRedBarSleep--; if(P[ind].EnergyRedBarSleep<0) {P[ind].EnergyRedBarSleep=0;} }
if( (P[ind].EnergyRedBar!=P[ind].Energy) && P[ind].EnergyRedBarSleep==0 ){ P[ind].EnergyRedBar-=5; }
}

backend_draw_sprite(LayerHUDa, spr_bg_bar,  320-(backend_bitmap_width(spr_bg_bar)/2), 0);

//dica de codigo
//backend_stretch_blit(BITMAP*source, BITMAP*dest, source_x, source_y, source_width, source_height, dest_x, dest_y, dest_width, dest_height);
//backend_masked_blit(HM_BITMAP source, HM_BITMAP dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);

//energia

/*p1red*/
backend_clear_to_color(P1_energy_red_flip, backend_makecol(255, 0, 255));
backend_draw_sprite_h_flip(P1_energy_red_flip, spr_energy_red_bar_full, 0, 0);
backend_masked_blit(P1_energy_red_flip, LayerHUDa, backend_bitmap_width(P1_energy_red_flip)-(P[1].EnergyRedBar*250)/1000, 0, 50+(backend_bitmap_width(P1_energy_red_flip)-(P[1].EnergyRedBar*250)/1000), 0, backend_bitmap_width(P1_energy_red_flip), backend_bitmap_height(P1_energy_red_flip));
/*p2red*/
backend_masked_blit(spr_energy_red_bar_full, LayerHUDa, 0, 0, 320+20, 0, (P[2].EnergyRedBar*250)/1000, backend_bitmap_height(spr_energy_red_bar_full));
/*p1*/
backend_clear_to_color(P1_energy_flip, backend_makecol(255, 0, 255));
backend_draw_sprite_h_flip(P1_energy_flip, spr_energy_bar_full, 0, 0);
backend_masked_blit(P1_energy_flip, LayerHUDa, backend_bitmap_width(P1_energy_flip)-((((P[1].Energy*100)/1000)/100)*250), 0, 50+(backend_bitmap_width(P1_energy_flip)-((((P[1].Energy*100)/1000)/100)*250)), 0, backend_bitmap_width(P1_energy_flip), backend_bitmap_height(P1_energy_flip));
/*p2*/
backend_masked_blit(spr_energy_bar_full, LayerHUDa, 0, 0, 320+20, 0, (((P[2].Energy*100)/1000)/100)*250, backend_bitmap_height(spr_energy_bar_full));

//Special
/*p1*/backend_stretch_blit(spr_bg_energy_bar_sp  , LayerHUDa, 0, 0, backend_bitmap_width(spr_bg_energy_bar_sp), backend_bitmap_height(spr_bg_energy_bar_sp) ,                                  30, 457, (P[1].Special*250)/2000     , backend_bitmap_height(spr_bg_energy_bar_sp));
/*p2*/backend_stretch_blit(spr_bg_energy_bar_sp  , LayerHUDa, 0, 0, backend_bitmap_width(spr_bg_energy_bar_sp), backend_bitmap_height(spr_bg_energy_bar_sp) , 360+(250-((P[2].Special*125)/1000)), 457, (P[2].Special*250)/2000     , backend_bitmap_height(spr_bg_energy_bar_sp));
//molduras barra de Special
/*p1*/backend_draw_sprite(LayerHUDa, spr_bg_bar_sp, 0, 440);
/*p2*/backend_draw_sprite_h_flip(LayerHUDa, spr_bg_bar_sp, 480, 440);

//mini fotos in game
backend_draw_sprite(LayerHUDa, P1_1, 5, 5);
backend_draw_sprite_h_flip(LayerHUDa, P2_1, 602, 5);

/*relogio*/
//calculo de digitos
if (RoundTime>0) { RoundTime=RoundTime-1; }
float RelogioTimer=RoundTime/60/10;
int RelogioTimerParteInteira;
int RelogioTimerParteDecimal;
RelogioTimerParteInteira=abs(RelogioTimer);
RelogioTimerParteDecimal=((RoundTime/60)-(RelogioTimerParteInteira*10));
//desenha os digitos
for(int ind=0;ind<=9;ind++){
if(RelogioTimerParteDecimal==ind) {
backend_draw_sprite(LayerHUDa, spr_num[ind], 320-10, 0);
}
if(RelogioTimerParteInteira==ind) {
backend_draw_sprite(LayerHUDa, spr_num[ind], 320-30, 0);
}
}

//desenha numero (valor) do Special 1,2,3
if (P[1].Special<333)                      { backend_textprintf_centre_ex(LayerHUDa, font_debug,  18,  449, backend_makecol(255,255,255), -1, "0"); }
if (P[1].Special>=333 && P[1].Special<666) { backend_textprintf_centre_ex(LayerHUDa, font_debug,  18,  449, backend_makecol(255,255,255), -1, "1"); }
if (P[1].Special>=666 && P[1].Special<999) { backend_textprintf_centre_ex(LayerHUDa, font_debug,  18,  449, backend_makecol(255,255,255), -1, "2"); }
if (P[1].Special==1000)                    { backend_textprintf_centre_ex(LayerHUDa, font_debug,  18,  449, backend_makecol(255,255,255), -1, "3"); }
if (P[2].Special<333)                      { backend_textprintf_centre_ex(LayerHUDa, font_debug, 622,  449, backend_makecol(255,255,255), -1, "0"); }
if (P[2].Special>=333 && P[2].Special<666) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 622,  449, backend_makecol(255,255,255), -1, "1"); }
if (P[2].Special>=666 && P[2].Special<999) { backend_textprintf_centre_ex(LayerHUDa, font_debug, 622,  449, backend_makecol(255,255,255), -1, "2"); }
if (P[2].Special==1000)                    { backend_textprintf_centre_ex(LayerHUDa, font_debug, 622,  449, backend_makecol(255,255,255), -1, "3"); }

//desenha splash round 1 fight
if (timer_rounds>= 30 && timer_rounds<150){
if(RoundAtual==1){ backend_draw_sprite(LayerHUDa, spr_splash_round1, 170, 80); if(timer_rounds==30){backend_play_sample(round1, 255, 128, 1000, 0);} }
if(RoundAtual==2){ backend_draw_sprite(LayerHUDa, spr_splash_round2, 170, 80); if(timer_rounds==30){backend_play_sample(round2, 255, 128, 1000, 0);} }
if(RoundAtual==3){ backend_draw_sprite(LayerHUDa, spr_splash_round3, 170, 80); if(timer_rounds==30){backend_play_sample(round3, 255, 128, 1000, 0);} }
if(RoundAtual==4){ backend_draw_sprite(LayerHUDa, spr_splash_round4, 170, 80); }
if(RoundAtual==5){ backend_draw_sprite(LayerHUDa, spr_splash_round5, 170, 80); }
}
if (timer_rounds>=150 && timer_rounds<250){
backend_draw_sprite(LayerHUDa, spr_splash_fight, 120, 100);
if(timer_rounds==150){backend_play_sample(fight, 255, 128, 1000, 0);}
}

//desenha splash de vitoria, derrota, draw
if(timer_final_de_rounds>0){
if (timer_final_de_rounds>= 30 && timer_final_de_rounds<180){
if(P[1].Energy>0 && P[2].Energy>0) { backend_draw_sprite(LayerHUDa, spr_splash_time_over, 170, 190);  }else //time over
{ backend_draw_sprite(LayerHUDa, spr_splash_ko, 170, 120); if(timer_final_de_rounds==30){backend_play_sample(ko, 255, 128, 1000, 0);}  } //KO
}

//Splashs de final de round
if (timer_final_de_rounds>=200 && timer_final_de_rounds<380){
int resultadoRound=1;
if(ModoHistoria==1) { if(P[1].Energy>P[2].Energy ) { backend_draw_sprite(LayerHUDa, spr_splash_youwin , 170, 190); } }//youwin
if(ModoHistoria==0) { if(P[1].Energy>P[2].Energy ) { backend_draw_sprite(LayerHUDa, spr_splash_p1win  , 170, 190); } }//p1win
if(ModoHistoria==1) { if(P[1].Energy<P[2].Energy ) { backend_draw_sprite(LayerHUDa, spr_splash_youlose, 170, 190); } }//youlose
if(ModoHistoria==0) { if(P[1].Energy<P[2].Energy ) { backend_draw_sprite(LayerHUDa, spr_splash_p2win  , 170, 190); } }//p2win
if(P[1].Energy==P[2].Energy) { backend_draw_sprite(LayerHUDa, spr_splash_draw   , 170, 190);    //draw
if(timer_final_de_rounds>300){timer_final_de_rounds=EndRoundT; } } //acelera o reinicio do round em caso de draw
if( (P[1].Energy==1000 || P[2].Energy==1000) && (P[1].Energy!=P[2].Energy) ) {
backend_draw_sprite(LayerHUDa, spr_splash_perfect, 170, 100);
if(timer_final_de_rounds==200){backend_play_sample(perfect, 255, 128, 1000, 0);}
}
}

if(timer_final_de_rounds==1){
if(P[1].Energy>P[2].Energy){ P[1].Round_Wins++; if(P[1].Energy==1000){ P[1].Perfects++; } }
if(P[1].Energy<P[2].Energy){ P[2].Round_Wins++; if(P[2].Energy==1000){ P[2].Perfects++; } }
}
}

//desenha molduras com transparencia
backend_drawing_mode(HM_DRAW_MODE_TRANS,NULL,0,0);
backend_set_trans_blender(0,0,0,77); //aprox 25% transparente
if(RoundTotal>=1){ backend_draw_trans_sprite(LayerHUDa, spr_mold_results, 5+40*0+0, 45); }
if(RoundTotal>=2){ backend_draw_trans_sprite(LayerHUDa, spr_mold_results, 5+40*1+1, 45); }
if(RoundTotal>=4){ backend_draw_trans_sprite(LayerHUDa, spr_mold_results, 5+40*2+2, 45); }
if(RoundTotal>=1){ backend_draw_trans_sprite(LayerHUDa, spr_mold_results, 640-5-40*1-1, 45); }
if(RoundTotal>=2){ backend_draw_trans_sprite(LayerHUDa, spr_mold_results, 640-5-40*2-2, 45); }
if(RoundTotal>=4){ backend_draw_trans_sprite(LayerHUDa, spr_mold_results, 640-5-40*3-3, 45); }
solid_mode();
if(P[1].Round_Wins>=1){ backend_draw_sprite(LayerHUDa, spr_result_win, 5+40*0+0, 45); }
if(P[1].Round_Wins>=2){ backend_draw_sprite(LayerHUDa, spr_result_win, 5+40*1+1, 45); }
if(P[1].Round_Wins>=3){ backend_draw_sprite(LayerHUDa, spr_result_win, 5+40*2+2, 45); }
if(P[2].Round_Wins>=1){ backend_draw_sprite(LayerHUDa, spr_result_win, 640-5-40*1-1, 45); }
if(P[2].Round_Wins>=2){ backend_draw_sprite(LayerHUDa, spr_result_win, 640-5-40*2-2, 45); }
if(P[2].Round_Wins>=3){ backend_draw_sprite(LayerHUDa, spr_result_win, 640-5-40*3-3, 45); }
}

///////////////////////////////////////////////////////////////////////////
//-EDIT MODE---------------------------------------------------------[**09]
///////////////////////////////////////////////////////////////////////////

if (EditMode==1) {

if (backend_key[HM_KEY_ESC] && EditMode==1) {
backend_play_sample(back, 255, 128, 1000, 0);
FadeCtr=255; FadeIN=0; FadeOUT=1;

if ( ED_alertsave==1 )
{
ED_save_charini();
}
timermenus=0; ApresentacaoMode=1; EditMode=0; backend_rest(100);
}

if ( backend_key[HM_KEY_F9 ] ) { Ctrl_FPS= 1; backend_install_int_ex(tempo, BPS_TO_TIMER( 1)); }
if ( backend_key[HM_KEY_F10] ) { Ctrl_FPS+=-1; if (Ctrl_FPS<1 ) { Ctrl_FPS= 1; } backend_install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS)); }
if ( backend_key[HM_KEY_F11] ) { Ctrl_FPS+=+1; if (Ctrl_FPS>60) { Ctrl_FPS=60; } backend_install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS)); }
if ( backend_key[HM_KEY_F12] ) { Ctrl_FPS=60; backend_install_int_ex(tempo, BPS_TO_TIMER(60)); }
//movimenta o player, dentro do editor
if ( ED_y> 50/2 && ( P[1].key_W_status ==1 || P[1].key_W_status ==2 ) ) { ED_y--; } //w
if ( ED_y<470/2 && ( P[1].key_S_status ==1 || P[1].key_S_status ==2 ) ) { ED_y++; } //s
if ( ED_x>180/2 && ( P[1].key_A_status ==1 || P[1].key_A_status ==2 ) ) { ED_x--; } //a
if ( ED_x<630/2 && ( P[1].key_D_status ==1 || P[1].key_D_status ==2 ) ) { ED_x++; } //d
//se segurar o shift, movimenta 1 pixel de cada vez.
//o codigo abaixo anula o movimento ao manter pressionado,
//mantendo entao apenas o deslocamento do key_pressed (key_status==1)
if ( ED_y> 50/2 && P[1].key_W_status ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_y++; } //w+shift
if ( ED_y<470/2 && P[1].key_S_status ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_y--; } //s+shift
if ( ED_x>180/2 && P[1].key_A_status ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_x++; } //a+shift
if ( ED_x<630/2 && P[1].key_D_status ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_x--; } //d+shift
//movimenta o eixo
if (ED_MovimentaPivot==1 && P[1].key_START_status==1) { ED_alertsave2=1; ED_MovimentaPivot=0; }
if (ED_MovimentaPivot==1)
{
int AuxEixoX=0; int AuxEixoY=0;
if ( ED_y> 50/2 && ( P[1].key_UP_status    ==1 || P[1].key_UP_status    ==2 ) ) { ED_YAlign++; AuxEixoY=-1; }
if ( ED_y<470/2 && ( P[1].key_DOWN_status  ==1 || P[1].key_DOWN_status  ==2 ) ) { ED_YAlign--; AuxEixoY=+1; }
if ( ED_x>180/2 && ( P[1].key_LEFT_status  ==1 || P[1].key_LEFT_status  ==2 ) ) { ED_XAlign++; AuxEixoX=-1; }
if ( ED_x<630/2 && ( P[1].key_RIGHT_status ==1 || P[1].key_RIGHT_status ==2 ) ) { ED_XAlign--; AuxEixoX=+1; }
//se segurar o shift, movimenta 1 pixel de cada vez.
//o codigo abaixo anula o movimento ao manter pressionado,
//mantendo entao apenas o deslocamento do key_pressed (key_status==1)
if ( ED_y> 50/2 && P[1].key_UP_status    ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_YAlign--; AuxEixoY=+1; }
if ( ED_y<470/2 && P[1].key_DOWN_status  ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_YAlign++; AuxEixoY=-1; }
if ( ED_x>180/2 && P[1].key_LEFT_status  ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_XAlign--; AuxEixoX=+1; }
if ( ED_x<630/2 && P[1].key_RIGHT_status ==2 && (backend_key[HM_KEY_LSHIFT] || backend_key[HM_KEY_RSHIFT]) ) { ED_XAlign++; AuxEixoX=-1; }
}

//Inicializa as variaveis do Editor
if (EditModeTime==0)
{
ED_inicializar();
char ED_Caminho[99];
sprintf(ED_Caminho, "data/chars/%s/000_01.pcx", P[1].Name);
ED_Mini = backend_load_bitmap(ED_Caminho, NULL);
if(!ED_Mini){ ED_Mini = backend_load_bitmap("data/system/000_01.pcx", NULL); }
}

//botoes para alterar os STATES
if (key_Mouse_L_status==1 && backend_mouse_x>5 && backend_mouse_x<81 && backend_mouse_y>120 && backend_mouse_y<150) //Recuar States L
{ MovPossiveisIndex--; if (MovPossiveisIndex<0) { MovPossiveisIndex=0; } ED_CarregarDados=1; }
if (key_Mouse_R_status==1 && backend_mouse_x>5 && backend_mouse_x<81 && backend_mouse_y>120 && backend_mouse_y<150) //Recuar States R
{ MovPossiveisIndex-=10; if (MovPossiveisIndex<0) { MovPossiveisIndex=0; } ED_CarregarDados=1; }

if (key_Mouse_L_status==1 && backend_mouse_x>88 && backend_mouse_x<165 && backend_mouse_y>120 && backend_mouse_y<150) //Avançar States L
{ MovPossiveisIndex++; if (MovPossiveis[MovPossiveisIndex]==0) { MovPossiveisIndex--; } ED_CarregarDados=1; }
if (key_Mouse_R_status==1 && backend_mouse_x>88 && backend_mouse_x<165 && backend_mouse_y>120 && backend_mouse_y<150) //Avançar States R
{ MovPossiveisIndex+=10; if (MovPossiveis[MovPossiveisIndex]==0) { MovPossiveisIndex-=10; } ED_CarregarDados=1; }

if
(
ED_alertsave==1 &&
(
(key_Mouse_L_status==1 && backend_mouse_x>5 && backend_mouse_x<81 && backend_mouse_y>120 && backend_mouse_y<150) ||
(key_Mouse_R_status==1 && backend_mouse_x>5 && backend_mouse_x<81 && backend_mouse_y>120 && backend_mouse_y<150) ||
(key_Mouse_L_status==1 && backend_mouse_x>88 && backend_mouse_x<165 && backend_mouse_y>120 && backend_mouse_y<150) ||
(key_Mouse_R_status==1 && backend_mouse_x>88 && backend_mouse_x<165 && backend_mouse_y>120 && backend_mouse_y<150)
)
)
{
ED_save_charini();
ED_alertsave=0;
}

if (ED_alertsave2==1) //salva o eixo, apos movimentacao do mesmo
{
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3]; sprintf(ED_State_s, "%i", ED_State);
backend_set_config_int(ED_State_s, "XAlign"      , ED_XAlign );
backend_set_config_int(ED_State_s, "YAlign"      , ED_YAlign );
ED_alertsave2=0;
}

if (ED_CarregarDados==1) {

//verifica qtos frames existem na animacao selecionada
int ED_tot[999];
for(int ind=100;ind<=999;ind++){
if (MovPossiveis[MovPossiveisIndex]== ind) {
ED_State= ind;
ED_tot[ind]=-1;
for (int i=0; i<=29; i++) {
char txt[50]="";
if ( i< 10 ) { sprintf(txt, "data/chars/%s/%i_0%i.pcx", ED_Name, ind, i); }
if ( i>=10 ) { sprintf(txt, "data/chars/%s/%i_%i.pcx" , ED_Name, ind, i); }
if ( backend_file_exists(txt)) { ED_tot[ind]++; } else {i=29;}
ED_TotalFrames=ED_tot[ind];
}
}
}

ED_load_charini();
Draw_CHBoxes_ED();
ED_CarregarDados=0;
}

if(ED_MODE==1){
if (key_Mouse_L_status==1 && backend_mouse_x>5 && backend_mouse_x<55 && backend_mouse_y>60 && backend_mouse_y<110) //Draw Hurt Box
{ ED_Pause=1; ED_MovimentaPivot=0; ED_DrawBlueMode=1; ED_DrawRedMode=0; ED_bt_Null=1; Draw_CHBoxes_ED(); }
if (key_Mouse_L_status==1 && backend_mouse_x>60 && backend_mouse_x<110 && backend_mouse_y>60 && backend_mouse_y<110) //Draw Hit Box
{ ED_Pause=1; ED_MovimentaPivot=0; ED_DrawRedMode=1; ED_DrawBlueMode=0; ED_bt_Null=1; Draw_CHBoxes_ED(); }
if (key_Mouse_L_status==1 && backend_mouse_x>115 && backend_mouse_x<165 && backend_mouse_y>60 && backend_mouse_y<110) //Bt Null
{ ED_Pause=0; ED_MovimentaPivot=0; ED_DrawBlueMode=0; ED_DrawRedMode=0; ED_bt_Null=0; }
}

if (key_Mouse_R_status==1 && backend_mouse_x>170 && backend_mouse_y>40) {

if (ED_DrawRedMode==1)
{
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/chbox.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3];
if (ED_IndexAnim <10) { sprintf(ED_State_s, "%i_0%i", ED_State, ED_IndexAnim); }
if (ED_IndexAnim>=10) { sprintf(ED_State_s, "%i_%i" , ED_State, ED_IndexAnim); }
if ( ED_HitBox_tot==9 ) { ED_HitBox09x1=-5555; ED_HitBox09y1=-5555; ED_HitBox09x2=-5555; ED_HitBox09y2=-5555;
backend_set_config_int(ED_State_s, "HitBox09x1", ED_HitBox09x1);
backend_set_config_int(ED_State_s, "HitBox09y1", ED_HitBox09y1);
backend_set_config_int(ED_State_s, "HitBox09x2", ED_HitBox09x2);
backend_set_config_int(ED_State_s, "HitBox09y2", ED_HitBox09y2); }
else if ( ED_HitBox_tot==8 ) { ED_HitBox08x1=-5555; ED_HitBox08y1=-5555; ED_HitBox08x2=-5555; ED_HitBox08y2=-5555;
backend_set_config_int(ED_State_s, "HitBox08x1", ED_HitBox08x1);
backend_set_config_int(ED_State_s, "HitBox08y1", ED_HitBox08y1);
backend_set_config_int(ED_State_s, "HitBox08x2", ED_HitBox08x2);
backend_set_config_int(ED_State_s, "HitBox08y2", ED_HitBox08y2); }
else if ( ED_HitBox_tot==7 ) { ED_HitBox07x1=-5555; ED_HitBox07y1=-5555; ED_HitBox07x2=-5555; ED_HitBox07y2=-5555;
backend_set_config_int(ED_State_s, "HitBox07x1", ED_HitBox07x1);
backend_set_config_int(ED_State_s, "HitBox07y1", ED_HitBox07y1);
backend_set_config_int(ED_State_s, "HitBox07x2", ED_HitBox07x2);
backend_set_config_int(ED_State_s, "HitBox07y2", ED_HitBox07y2); }
else if ( ED_HitBox_tot==6 ) { ED_HitBox06x1=-5555; ED_HitBox06y1=-5555; ED_HitBox06x2=-5555; ED_HitBox06y2=-5555;
backend_set_config_int(ED_State_s, "HitBox06x1", ED_HitBox06x1);
backend_set_config_int(ED_State_s, "HitBox06y1", ED_HitBox06y1);
backend_set_config_int(ED_State_s, "HitBox06x2", ED_HitBox06x2);
backend_set_config_int(ED_State_s, "HitBox06y2", ED_HitBox06y2); }
else if ( ED_HitBox_tot==5 ) { ED_HitBox05x1=-5555; ED_HitBox05y1=-5555; ED_HitBox05x2=-5555; ED_HitBox05y2=-5555;
backend_set_config_int(ED_State_s, "HitBox05x1", ED_HitBox05x1);
backend_set_config_int(ED_State_s, "HitBox05y1", ED_HitBox05y1);
backend_set_config_int(ED_State_s, "HitBox05x2", ED_HitBox05x2);
backend_set_config_int(ED_State_s, "HitBox05y2", ED_HitBox05y2); }
else if ( ED_HitBox_tot==4 ) { ED_HitBox04x1=-5555; ED_HitBox04y1=-5555; ED_HitBox04x2=-5555; ED_HitBox04y2=-5555;
backend_set_config_int(ED_State_s, "HitBox04x1", ED_HitBox04x1);
backend_set_config_int(ED_State_s, "HitBox04y1", ED_HitBox04y1);
backend_set_config_int(ED_State_s, "HitBox04x2", ED_HitBox04x2);
backend_set_config_int(ED_State_s, "HitBox04y2", ED_HitBox04y2); }
else if ( ED_HitBox_tot==3 ) { ED_HitBox03x1=-5555; ED_HitBox03y1=-5555; ED_HitBox03x2=-5555; ED_HitBox03y2=-5555;
backend_set_config_int(ED_State_s, "HitBox03x1", ED_HitBox03x1);
backend_set_config_int(ED_State_s, "HitBox03y1", ED_HitBox03y1);
backend_set_config_int(ED_State_s, "HitBox03x2", ED_HitBox03x2);
backend_set_config_int(ED_State_s, "HitBox03y2", ED_HitBox03y2); }
else if ( ED_HitBox_tot==2 ) { ED_HitBox02x1=-5555; ED_HitBox02y1=-5555; ED_HitBox02x2=-5555; ED_HitBox02y2=-5555;
backend_set_config_int(ED_State_s, "HitBox02x1", ED_HitBox02x1);
backend_set_config_int(ED_State_s, "HitBox02y1", ED_HitBox02y1);
backend_set_config_int(ED_State_s, "HitBox02x2", ED_HitBox02x2);
backend_set_config_int(ED_State_s, "HitBox02y2", ED_HitBox02y2); }
else if ( ED_HitBox_tot==1 ) { ED_HitBox01x1=-5555; ED_HitBox01y1=-5555; ED_HitBox01x2=-5555; ED_HitBox01y2=-5555;
backend_set_config_int(ED_State_s, "HitBox01x1", ED_HitBox01x1);
backend_set_config_int(ED_State_s, "HitBox01y1", ED_HitBox01y1);
backend_set_config_int(ED_State_s, "HitBox01x2", ED_HitBox01x2);
backend_set_config_int(ED_State_s, "HitBox01y2", ED_HitBox01y2); }
ED_HitBox_tot--;  } if (ED_HitBox_tot<0 ) { ED_HitBox_tot=0;
}
if (ED_DrawBlueMode==1)
{
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/chbox.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3];
if (ED_IndexAnim<10 ) { sprintf(ED_State_s, "%i_0%i", ED_State, ED_IndexAnim); }
if (ED_IndexAnim>=10) { sprintf(ED_State_s, "%i_%i" , ED_State, ED_IndexAnim); }
if ( ED_HurtBox_tot==9 ) { ED_HurtBox09x1=-5555; ED_HurtBox09y1=-5555; ED_HurtBox09x2=-5555; ED_HurtBox09y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox09x1", ED_HurtBox09x1);
backend_set_config_int(ED_State_s, "HurtBox09y1", ED_HurtBox09y1);
backend_set_config_int(ED_State_s, "HurtBox09x2", ED_HurtBox09x2);
backend_set_config_int(ED_State_s, "HurtBox09y2", ED_HurtBox09y2); }
else if ( ED_HurtBox_tot==8 ) { ED_HurtBox08x1=-5555; ED_HurtBox08y1=-5555; ED_HurtBox08x2=-5555; ED_HurtBox08y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox08x1", ED_HurtBox08x1);
backend_set_config_int(ED_State_s, "HurtBox08y1", ED_HurtBox08y1);
backend_set_config_int(ED_State_s, "HurtBox08x2", ED_HurtBox08x2);
backend_set_config_int(ED_State_s, "HurtBox08y2", ED_HurtBox08y2); }
else if ( ED_HurtBox_tot==7 ) { ED_HurtBox07x1=-5555; ED_HurtBox07y1=-5555; ED_HurtBox07x2=-5555; ED_HurtBox07y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox07x1", ED_HurtBox07x1);
backend_set_config_int(ED_State_s, "HurtBox07y1", ED_HurtBox07y1);
backend_set_config_int(ED_State_s, "HurtBox07x2", ED_HurtBox07x2);
backend_set_config_int(ED_State_s, "HurtBox07y2", ED_HurtBox07y2); }
else if ( ED_HurtBox_tot==6 ) { ED_HurtBox06x1=-5555; ED_HurtBox06y1=-5555; ED_HurtBox06x2=-5555; ED_HurtBox06y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox06x1", ED_HurtBox06x1);
backend_set_config_int(ED_State_s, "HurtBox06y1", ED_HurtBox06y1);
backend_set_config_int(ED_State_s, "HurtBox06x2", ED_HurtBox06x2);
backend_set_config_int(ED_State_s, "HurtBox06y2", ED_HurtBox06y2); }
else if ( ED_HurtBox_tot==5 ) { ED_HurtBox05x1=-5555; ED_HurtBox05y1=-5555; ED_HurtBox05x2=-5555; ED_HurtBox05y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox05x1", ED_HurtBox05x1);
backend_set_config_int(ED_State_s, "HurtBox05y1", ED_HurtBox05y1);
backend_set_config_int(ED_State_s, "HurtBox05x2", ED_HurtBox05x2);
backend_set_config_int(ED_State_s, "HurtBox05y2", ED_HurtBox05y2); }
else if ( ED_HurtBox_tot==4 ) { ED_HurtBox04x1=-5555; ED_HurtBox04y1=-5555; ED_HurtBox04x2=-5555; ED_HurtBox04y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox04x1", ED_HurtBox04x1);
backend_set_config_int(ED_State_s, "HurtBox04y1", ED_HurtBox04y1);
backend_set_config_int(ED_State_s, "HurtBox04x2", ED_HurtBox04x2);
backend_set_config_int(ED_State_s, "HurtBox04y2", ED_HurtBox04y2); }
else if ( ED_HurtBox_tot==3 ) { ED_HurtBox03x1=-5555; ED_HurtBox03y1=-5555; ED_HurtBox03x2=-5555; ED_HurtBox03y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox03x1", ED_HurtBox03x1);
backend_set_config_int(ED_State_s, "HurtBox03y1", ED_HurtBox03y1);
backend_set_config_int(ED_State_s, "HurtBox03x2", ED_HurtBox03x2);
backend_set_config_int(ED_State_s, "HurtBox03y2", ED_HurtBox03y2); }
else if ( ED_HurtBox_tot==2 ) { ED_HurtBox02x1=-5555; ED_HurtBox02y1=-5555; ED_HurtBox02x2=-5555; ED_HurtBox02y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox02x1", ED_HurtBox02x1);
backend_set_config_int(ED_State_s, "HurtBox02y1", ED_HurtBox02y1);
backend_set_config_int(ED_State_s, "HurtBox02x2", ED_HurtBox02x2);
backend_set_config_int(ED_State_s, "HurtBox02y2", ED_HurtBox02y2); }
else if ( ED_HurtBox_tot==1 ) { ED_HurtBox01x1=-5555; ED_HurtBox01y1=-5555; ED_HurtBox01x2=-5555; ED_HurtBox01y2=-5555;
backend_set_config_int(ED_State_s, "HurtBox01x1", ED_HurtBox01x1);
backend_set_config_int(ED_State_s, "HurtBox01y1", ED_HurtBox01y1);
backend_set_config_int(ED_State_s, "HurtBox01x2", ED_HurtBox01x2);
backend_set_config_int(ED_State_s, "HurtBox01y2", ED_HurtBox01y2); }
ED_HurtBox_tot--; } if (ED_HurtBox_tot<0) { ED_HurtBox_tot=0;
}
}

if ( (ED_DrawRedMode==1 || ED_DrawBlueMode==1) && key_Mouse_L_status==1 && backend_mouse_x>170 && backend_mouse_y>40 ) //inicia desenho Red/Blue
{ ED_Mx1=backend_mouse_x; ED_My1=backend_mouse_y; }

int atualiza=0;

if (key_Mouse_L_status==1 && backend_mouse_x>5 && backend_mouse_x<34 && backend_mouse_y>172 && backend_mouse_y<202) //Prev+
{ ED_Pause=1; ED_IndexAnim=0; ED_StartFrame=Edtimer; atualiza=1; Draw_CHBoxes_ED(); }

if (key_Mouse_L_status==1 && backend_mouse_x>37 && backend_mouse_x<66 && backend_mouse_y>172 && backend_mouse_y<202) //Prev L
{ ED_Pause=1; ED_IndexAnim--; if (ED_IndexAnim<0) { ED_IndexAnim=ED_TotalFrames; } ED_StartFrame=Edtimer; atualiza=1; Draw_CHBoxes_ED(); }
if (key_Mouse_R_status==1 && backend_mouse_x>37 && backend_mouse_x<66 && backend_mouse_y>172 && backend_mouse_y<202) //Prev R
{ ED_Pause=1; ED_IndexAnim-=3; if (ED_IndexAnim<0) { ED_IndexAnim=0; } ED_StartFrame=Edtimer; atualiza=1; Draw_CHBoxes_ED(); }

if (key_Mouse_L_status==1 && backend_mouse_x>70 && backend_mouse_x<100 && backend_mouse_y>168 && backend_mouse_y<198) //Pause/Play
{ if (ED_Pause==0) { ED_Pause=1; } else { ED_Pause=0; } }

if (key_Mouse_L_status==1 && backend_mouse_x>103 && backend_mouse_x<133 && backend_mouse_y>172 && backend_mouse_y<202) //Next L
{ ED_Pause=1; ED_IndexAnim++; if (ED_IndexAnim>ED_TotalFrames) { ED_IndexAnim=0; } ED_StartFrame=Edtimer; atualiza=1; Draw_CHBoxes_ED(); }
if (key_Mouse_R_status==1 && backend_mouse_x>103 && backend_mouse_x<133 && backend_mouse_y>172 && backend_mouse_y<202) //Next R
{ ED_Pause=1; ED_IndexAnim+=3; if (ED_IndexAnim>ED_TotalFrames) { ED_IndexAnim=ED_TotalFrames; } ED_StartFrame=Edtimer; atualiza=1; Draw_CHBoxes_ED(); }

if (key_Mouse_L_status==1 && backend_mouse_x>135 && backend_mouse_x<165 && backend_mouse_y>172 && backend_mouse_y<202) //Next+
{ ED_Pause=1; ED_IndexAnim=ED_TotalFrames; ED_StartFrame=Edtimer; atualiza=1; Draw_CHBoxes_ED(); }

if (atualiza==1) {
if (ED_IndexAnim== 0) { ED_FrameTime=ED_FrameTime_00; }
if (ED_IndexAnim== 1) { ED_FrameTime=ED_FrameTime_01; }
if (ED_IndexAnim== 2) { ED_FrameTime=ED_FrameTime_02; }
if (ED_IndexAnim== 3) { ED_FrameTime=ED_FrameTime_03; }
if (ED_IndexAnim== 4) { ED_FrameTime=ED_FrameTime_04; }
if (ED_IndexAnim== 5) { ED_FrameTime=ED_FrameTime_05; }
if (ED_IndexAnim== 6) { ED_FrameTime=ED_FrameTime_06; }
if (ED_IndexAnim== 7) { ED_FrameTime=ED_FrameTime_07; }
if (ED_IndexAnim== 8) { ED_FrameTime=ED_FrameTime_08; }
if (ED_IndexAnim== 9) { ED_FrameTime=ED_FrameTime_09; }
if (ED_IndexAnim==10) { ED_FrameTime=ED_FrameTime_10; }
if (ED_IndexAnim==11) { ED_FrameTime=ED_FrameTime_11; }
if (ED_IndexAnim==12) { ED_FrameTime=ED_FrameTime_12; }
if (ED_IndexAnim==13) { ED_FrameTime=ED_FrameTime_13; }
if (ED_IndexAnim==14) { ED_FrameTime=ED_FrameTime_14; }
if (ED_IndexAnim==15) { ED_FrameTime=ED_FrameTime_15; }
if (ED_IndexAnim==16) { ED_FrameTime=ED_FrameTime_16; }
if (ED_IndexAnim==17) { ED_FrameTime=ED_FrameTime_17; }
if (ED_IndexAnim==18) { ED_FrameTime=ED_FrameTime_18; }
if (ED_IndexAnim==19) { ED_FrameTime=ED_FrameTime_19; }
if (ED_IndexAnim==20) { ED_FrameTime=ED_FrameTime_20; }
if (ED_IndexAnim==21) { ED_FrameTime=ED_FrameTime_21; }
if (ED_IndexAnim==22) { ED_FrameTime=ED_FrameTime_22; }
if (ED_IndexAnim==23) { ED_FrameTime=ED_FrameTime_23; }
if (ED_IndexAnim==24) { ED_FrameTime=ED_FrameTime_24; }
if (ED_IndexAnim==25) { ED_FrameTime=ED_FrameTime_25; }
if (ED_IndexAnim==26) { ED_FrameTime=ED_FrameTime_26; }
if (ED_IndexAnim==27) { ED_FrameTime=ED_FrameTime_27; }
if (ED_IndexAnim==28) { ED_FrameTime=ED_FrameTime_28; }
if (ED_IndexAnim==29) { ED_FrameTime=ED_FrameTime_29; }
}
atualiza=0;

if (key_Mouse_L_status==1 && backend_mouse_x>6 && backend_mouse_x<34 && backend_mouse_y>211 && backend_mouse_y<238) //Minus Time L
{
ED_Pause=1; ED_FrameTime--; if (ED_FrameTime<0) { ED_FrameTime=0; }
ED_alertsave=1; atualiza=1;
}
if (key_Mouse_R_status==1 && backend_mouse_x>6 && backend_mouse_x<34 && backend_mouse_y>211 && backend_mouse_y<238) //Minus Time R
{
ED_Pause=1; ED_FrameTime-=10; if (ED_FrameTime<0) { ED_FrameTime=0; }
ED_alertsave=1; atualiza=1;
}

if (key_Mouse_L_status==1 && backend_mouse_x>136 && backend_mouse_x<164 && backend_mouse_y>211 && backend_mouse_y<238) //Plus Time L
{
ED_Pause=1; ED_FrameTime++; if (ED_FrameTime>998) { ED_FrameTime=998; }
ED_alertsave=1; atualiza=1;
}
if (key_Mouse_R_status==1 && backend_mouse_x>136 && backend_mouse_x<164 && backend_mouse_y>211 && backend_mouse_y<238) //Plus Time R
{
ED_Pause=1; ED_FrameTime+=10; if (ED_FrameTime>998) { ED_FrameTime=998; }
ED_alertsave=1; atualiza=1;
}

if (key_Mouse_L_status==1 && backend_mouse_x>5 && backend_mouse_x<164 && backend_mouse_y>420 && backend_mouse_y<450) //Movimenta Pivot
{
if (ED_MovimentaPivot==0) { ED_MovimentaPivot=1; ED_DrawBlueMode=0; ED_DrawRedMode=0; ED_bt_Null=0; }
else
{
ED_alertsave2=1;
ED_MovimentaPivot=0;
}
}

if (atualiza==1)
{
if (ED_IndexAnim== 0) { ED_FrameTime_00=ED_FrameTime; }
if (ED_IndexAnim== 1) { ED_FrameTime_01=ED_FrameTime; }
if (ED_IndexAnim== 2) { ED_FrameTime_02=ED_FrameTime; }
if (ED_IndexAnim== 3) { ED_FrameTime_03=ED_FrameTime; }
if (ED_IndexAnim== 4) { ED_FrameTime_04=ED_FrameTime; }
if (ED_IndexAnim== 5) { ED_FrameTime_05=ED_FrameTime; }
if (ED_IndexAnim== 6) { ED_FrameTime_06=ED_FrameTime; }
if (ED_IndexAnim== 7) { ED_FrameTime_07=ED_FrameTime; }
if (ED_IndexAnim== 8) { ED_FrameTime_08=ED_FrameTime; }
if (ED_IndexAnim== 9) { ED_FrameTime_09=ED_FrameTime; }
if (ED_IndexAnim==10) { ED_FrameTime_10=ED_FrameTime; }
if (ED_IndexAnim==11) { ED_FrameTime_11=ED_FrameTime; }
if (ED_IndexAnim==12) { ED_FrameTime_12=ED_FrameTime; }
if (ED_IndexAnim==13) { ED_FrameTime_13=ED_FrameTime; }
if (ED_IndexAnim==14) { ED_FrameTime_14=ED_FrameTime; }
if (ED_IndexAnim==15) { ED_FrameTime_15=ED_FrameTime; }
if (ED_IndexAnim==16) { ED_FrameTime_16=ED_FrameTime; }
if (ED_IndexAnim==17) { ED_FrameTime_17=ED_FrameTime; }
if (ED_IndexAnim==18) { ED_FrameTime_18=ED_FrameTime; }
if (ED_IndexAnim==19) { ED_FrameTime_19=ED_FrameTime; }
if (ED_IndexAnim==20) { ED_FrameTime_20=ED_FrameTime; }
if (ED_IndexAnim==21) { ED_FrameTime_21=ED_FrameTime; }
if (ED_IndexAnim==22) { ED_FrameTime_22=ED_FrameTime; }
if (ED_IndexAnim==23) { ED_FrameTime_23=ED_FrameTime; }
if (ED_IndexAnim==24) { ED_FrameTime_24=ED_FrameTime; }
if (ED_IndexAnim==25) { ED_FrameTime_25=ED_FrameTime; }
if (ED_IndexAnim==26) { ED_FrameTime_26=ED_FrameTime; }
if (ED_IndexAnim==27) { ED_FrameTime_27=ED_FrameTime; }
if (ED_IndexAnim==28) { ED_FrameTime_28=ED_FrameTime; }
if (ED_IndexAnim==29) { ED_FrameTime_29=ED_FrameTime; }
}

//-ED-anim++
if (ED_IndexAnim== 0) { if (Edtimer>ED_StartFrame+ED_FrameTime_00) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_01; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 1) { if (Edtimer>ED_StartFrame+ED_FrameTime_01) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_02; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 2) { if (Edtimer>ED_StartFrame+ED_FrameTime_02) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_03; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 3) { if (Edtimer>ED_StartFrame+ED_FrameTime_03) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_04; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 4) { if (Edtimer>ED_StartFrame+ED_FrameTime_04) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_05; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 5) { if (Edtimer>ED_StartFrame+ED_FrameTime_05) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_06; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 6) { if (Edtimer>ED_StartFrame+ED_FrameTime_06) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_07; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 7) { if (Edtimer>ED_StartFrame+ED_FrameTime_07) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_08; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 8) { if (Edtimer>ED_StartFrame+ED_FrameTime_08) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_09; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim== 9) { if (Edtimer>ED_StartFrame+ED_FrameTime_09) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_10; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==10) { if (Edtimer>ED_StartFrame+ED_FrameTime_10) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_11; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==11) { if (Edtimer>ED_StartFrame+ED_FrameTime_11) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_12; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==12) { if (Edtimer>ED_StartFrame+ED_FrameTime_12) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_13; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==13) { if (Edtimer>ED_StartFrame+ED_FrameTime_13) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_14; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==14) { if (Edtimer>ED_StartFrame+ED_FrameTime_14) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_15; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==15) { if (Edtimer>ED_StartFrame+ED_FrameTime_15) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_16; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==16) { if (Edtimer>ED_StartFrame+ED_FrameTime_16) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_17; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==17) { if (Edtimer>ED_StartFrame+ED_FrameTime_17) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_18; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==18) { if (Edtimer>ED_StartFrame+ED_FrameTime_18) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_19; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==19) { if (Edtimer>ED_StartFrame+ED_FrameTime_19) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_20; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==20) { if (Edtimer>ED_StartFrame+ED_FrameTime_20) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_21; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==21) { if (Edtimer>ED_StartFrame+ED_FrameTime_21) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_22; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==22) { if (Edtimer>ED_StartFrame+ED_FrameTime_22) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_23; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==23) { if (Edtimer>ED_StartFrame+ED_FrameTime_23) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_24; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==24) { if (Edtimer>ED_StartFrame+ED_FrameTime_24) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_25; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==25) { if (Edtimer>ED_StartFrame+ED_FrameTime_25) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_26; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==26) { if (Edtimer>ED_StartFrame+ED_FrameTime_26) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_27; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==27) { if (Edtimer>ED_StartFrame+ED_FrameTime_27) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_28; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
if (ED_IndexAnim==28) { if (Edtimer>ED_StartFrame+ED_FrameTime_28) { ED_IndexAnim++; ED_FrameTime=ED_FrameTime_29; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); }}
//-ED-end of anim
if (ED_IndexAnim>ED_TotalFrames) { ED_IndexAnim=0; ED_FrameTime=ED_FrameTime_00; ED_StartFrame=Edtimer; Draw_CHBoxes_ED(); } //-loop

backend_rectfill(bufferx, 0,0,320,240,backend_makecol(100,149,237));

//3-Desenha Caixas
if (ED_bt_Null==1)
{
backend_drawing_mode(HM_DRAW_MODE_TRANS, 0, 0, 0);
backend_set_trans_blender(0, 0, 0, 77);
if (ED_HurtBox01x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox01x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox01y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox01x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox01y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox02x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox02x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox02y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox02x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox02y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox03x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox03x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox03y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox03x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox03y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox04x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox04x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox04y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox04x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox04y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox05x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox05x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox05y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox05x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox05y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox06x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox06x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox06y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox06x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox06y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox07x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox07x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox07y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox07x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox07y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox08x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox08x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox08y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox08x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox08y2*1, backend_makecol(050,000,255)); }
if (ED_HurtBox09x1!=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox09x1*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox09y1*1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox09x2*1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox09y2*1, backend_makecol(050,000,255)); }
if (ED_HitBox01x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox01x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox01y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox01x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox01y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox02x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox02x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox02y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox02x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox02y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox03x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox03x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox03y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox03x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox03y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox04x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox04x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox04y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox04x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox04y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox05x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox05x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox05y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox05x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox05y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox06x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox06x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox06y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox06x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox06y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox07x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox07x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox07y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox07x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox07y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox08x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox08x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox08y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox08x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox08y2 *1, backend_makecol(255,000,050)); }
if (ED_HitBox09x1 !=-5555) { backend_rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox09x1 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox09y1 *1, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox09x2 *1, (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox09y2 *1, backend_makecol(255,000,050)); }
backend_drawing_mode(HM_DRAW_MODE_SOLID, 0, 0, 0);
}

//draw char -ED-
{
char txt[3];
char txt2[20];
if (ED_IndexAnim<10) { sprintf(txt, "%i_0%i", ED_State, ED_IndexAnim); }  // <10
else { sprintf(txt,  "%i_%i", ED_State, ED_IndexAnim); } //>=10
if (ED_IndexAnim<10) {
if (ED_State!=603 && ED_State!=605) { sprintf(txt2, "data/chars/%s/%i_0%i.pcx", ED_Name, ED_State, ED_IndexAnim); } //<10
if (ED_State==603  || ED_State==605) { sprintf(txt2, "data/chars/%s/604_0%i.pcx", ED_Name, ED_IndexAnim); }
} //<10
else {
if (ED_State!=603 && ED_State!=605) { sprintf(txt2, "data/chars/%s/%i_%i.pcx", ED_Name, ED_State, ED_IndexAnim); } //>=10
if (ED_State==603  || ED_State==605) { sprintf(txt2, "data/chars/%s/604_%i.pcx", ED_Name, ED_IndexAnim); }
} //>=10

//if (Edtimer-ED_StartFrame==0) { //Atualiza o sprite SOMENTE no primeiro frame de animacao
backend_clear_bitmap(ED_Spr);
ED_Spr_Aux = backend_load_bitmap(txt2, NULL);
if (!ED_Spr_Aux){ ED_Spr_Aux=char_generic; } //se falhar o carregamento, usar imagem generica
if(ED_Tipo==1) {
// Note: ED_Spr already has its size; stretch blit handles scaling
backend_stretch_blit(ED_Spr_Aux, ED_Spr, 0, 0, backend_bitmap_width(ED_Spr_Aux), backend_bitmap_height(ED_Spr_Aux), 0, 0, backend_bitmap_width(ED_Spr_Aux)*2, backend_bitmap_height(ED_Spr_Aux)*2);
}
if(ED_Tipo==2) {
// Note: ED_Spr already has its size; just blit the data
backend_blit(ED_Spr_Aux, ED_Spr, 0, 0, 0, 0, backend_bitmap_width(ED_Spr_Aux), backend_bitmap_height(ED_Spr_Aux));
}
backend_destroy_bitmap(ED_Spr_Aux);
ED_Altura  = backend_bitmap_height(ED_Spr); ED_Largura = backend_bitmap_width(ED_Spr);
if (ED_State==100) { ED_Altura_100=ED_Altura; ED_Largura_100=ED_Largura; }
//}
}
//fim draw_char

backend_rectfill(LayerHUD, 0,0,320,240,backend_makecol(100,149,237));
backend_rectfill(LayerHUD, 0,0, 85,240,backend_makecol( 50, 75,119));
backend_rectfill(LayerHUD, 0,0,320, 20,backend_makecol( 35, 45, 75));

if (ED_Pause==0) { EditModeTime+=1; Edtimer=EditModeTime; }

//draw hud
backend_stretch_blit(LayerHUD, bufferx, 0, 0, 320, 240, 0, 0, 640, 480);

//Render Tipo 1 Normal Sprites
if (ED_Tipo==1){
if (ED_State!=607 && ED_State!=608) {
if (ED_Lado== 1) { backend_draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
if (ED_Lado==-1) { backend_draw_sprite_h_flip(bufferx, ED_Spr, ((ED_x*2)-backend_bitmap_width(P[1].Spr))+ED_XAlign*2, ED_y*2-ED_YAlign*2); }
}
else {
//if (ED_Lado==-1) { backend_draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
if (ED_Lado== 1) { backend_draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
}
}

//Render Tipo 2 HD Sprites
if (ED_Tipo==2){
if (ED_State!=607 && ED_State!=608) {
if (ED_Lado== 1) { backend_draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
if (ED_Lado==-1) { backend_draw_sprite_h_flip(bufferx, ED_Spr, ((ED_x*2)-backend_bitmap_width(ED_Spr))+ED_XAlign*2, ED_y*2-ED_YAlign*2); }
}
else {
//if (ED_Lado==-1) { backend_draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
if (ED_Lado== 1) { backend_draw_sprite_h_flip(bufferx, ED_Spr, ((ED_x*2)-backend_bitmap_width(ED_Spr))+ED_XAlign*2, ED_y*2-ED_YAlign*2); }
}
}

//3b-Desenha Caixas com transparencia
if (ED_bt_Null==1)
{
backend_drawing_mode(HM_DRAW_MODE_TRANS, 0, 0, 0);
backend_set_trans_blender(0, 0, 0, 77);
if (ED_HurtBox01x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox01x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox01y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox01x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox01y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox02x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox02x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox02y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox02x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox02y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox03x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox03x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox03y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox03x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox03y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox04x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox04x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox04y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox04x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox04y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox05x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox05x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox05y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox05x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox05y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox06x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox06x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox06y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox06x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox06y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox07x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox07x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox07y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox07x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox07y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox08x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox08x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox08y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox08x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox08y2*2, backend_makecol(050,000,255)); }
if (ED_HurtBox09x1!=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox09x1*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox09y1*2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox09x2*2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox09y2*2, backend_makecol(050,000,255)); }
if (ED_HitBox01x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox01x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox01y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox01x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox01y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox02x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox02x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox02y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox02x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox02y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox03x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox03x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox03y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox03x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox03y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox04x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox04x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox04y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox04x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox04y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox05x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox05x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox05y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox05x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox05y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox06x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox06x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox06y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox06x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox06y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox07x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox07x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox07y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox07x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox07y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox08x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox08x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox08y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox08x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox08y2 *2, backend_makecol(255,000,050)); }
if (ED_HitBox09x1 !=-5555) { backend_rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox09x1 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox09y1 *2, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox09x2 *2, (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox09y2 *2, backend_makecol(255,000,050)); }
backend_drawing_mode(HM_DRAW_MODE_SOLID, 0, 0, 0);
}

if (ED_MovimentaPivot==1) //hud para movimentacao do eixo
{
backend_line(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)-250, (((ED_y-ED_YAlign)*2)+ED_YAlign*2), (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+250, (((ED_y-ED_YAlign)*2)+ED_YAlign*2), backend_makecol(000,000,000));
backend_line(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2)-250, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+250, backend_makecol(000,000,000));
backend_circle(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2),  50, backend_makecol(000,000,000));
backend_circle(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2), 100, backend_makecol(000,000,000));
backend_circle(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2), 150, backend_makecol(000,000,000));
}
if(ED_MODE==1){
backend_draw_sprite(bufferx, edit_bt_blue ,      5,  60); if (ED_DrawBlueMode==1) { backend_rect(bufferx,  5-2, 60-2,  5+backend_bitmap_width(edit_bt_blue)+2,60+backend_bitmap_height(edit_bt_blue)+2,backend_makecol(255,255,255)); }
backend_draw_sprite(bufferx, edit_bt_red  ,     60,  60); if (ED_DrawRedMode  ==1) { backend_rect(bufferx, 60-2, 60-2, 60+ backend_bitmap_width(edit_bt_red)+2,60+ backend_bitmap_height(edit_bt_red)+2,backend_makecol(255,255,255)); }
backend_draw_sprite(bufferx, edit_bt_null ,    115,  60); if (ED_bt_Null==0) { backend_draw_sprite(bufferx, edit_bt_null0, 115, 60); }
}

//interface
backend_draw_sprite(bufferx, edit_prevst,         5, 120);
backend_draw_sprite(bufferx, edit_nextst,        88, 120);
backend_draw_sprite(bufferx, edit_prevchar,     173,   6);
backend_draw_sprite(bufferx, edit_nextchar,     229,   6);
backend_draw_sprite(bufferx, edit_firstchar,    173,  22);
backend_draw_sprite(bufferx, edit_lastchar,     229,  22);
backend_draw_sprite(bufferx, edit_playback,       5, 172); if (ED_Pause==1) { backend_draw_sprite(bufferx, edit_pause, 70, 172); }
backend_draw_sprite(bufferx, edit_bt_minus,       5, 210);
backend_draw_sprite(bufferx, edit_bt_FrameTime,  35, 210); backend_textprintf_centre_ex(bufferx, font_debug, 90, 215, backend_makecol(255,255,255), -1, "%i", ED_FrameTime+1 );
backend_draw_sprite(bufferx, edit_bt_plus,      135, 210);
backend_draw_sprite(bufferx, bt_pivot,            5, 420);

//backend_textprintf_centre_ex(bufferx, font_debug, 84, 463, backend_makecol(255,255,000), -1, "FPS[%d] [%d]", Ctrl_FPS, Edtimer);
backend_textprintf_centre_ex(bufferx, font_debug, 84, 453, backend_makecol(255,255,255), -1, "Mx:%i My:%i", backend_mouse_x-ED_x*2, backend_mouse_y-ED_y*2);
circlefill (bufferx, ((ED_x-ED_XAlign)*2)+ED_XAlign*2, ((ED_y-ED_YAlign)*2)+ED_YAlign*2, 3, backend_makecol(000,000,000));
circlefill (bufferx, ((ED_x-ED_XAlign)*2)+ED_XAlign*2, ((ED_y-ED_YAlign)*2)+ED_YAlign*2, 1, backend_makecol(255,255,255));

backend_rectfill(bufferx, 5,152,163,150+19,backend_makecol(000,000,000));
backend_rect(bufferx, 5,152,163,150+19,backend_makecol(100,100,100));

//debug - draw states numerados V1
/*
		for (int ii=0; ii<=14; ii++) { if (ii < 9) { backend_textprintf_ex(bufferx, font_debug, 190      , 50+ ii    *12, backend_makecol(70,105,165), -1, "0%i[%i]", ii+1, MovPossiveis[ii] ); }
		if (ii>= 9) { backend_textprintf_ex(bufferx, font_debug, 190      , 50+ ii    *12, backend_makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); } }
		for (int ii=15; ii<=29; ii++) { backend_textprintf_ex(bufferx, font_debug, 190+ 63*1, 50+(ii-15)*12, backend_makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
		for (int ii=30; ii<=44; ii++) { backend_textprintf_ex(bufferx, font_debug, 190+ 63*2, 50+(ii-30)*12, backend_makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
		for (int ii=45; ii<=59; ii++) { backend_textprintf_ex(bufferx, font_debug, 190+ 63*3, 50+(ii-45)*12, backend_makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
		for (int ii=60; ii<=74; ii++) { backend_textprintf_ex(bufferx, font_debug, 190+ 63*4, 50+(ii-60)*12, backend_makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
		for (int ii=75; ii<=89; ii++) { backend_textprintf_ex(bufferx, font_debug, 190+ 63*5, 50+(ii-75)*12, backend_makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
		for (int ii=90; ii<=98; ii++) { backend_textprintf_ex(bufferx, font_debug, 190+ 63*6, 50+(ii-90)*12, backend_makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
	*/

//debug - draw states numerados V2
/*
		for (int ii=  0; ii<= 19; ii++) { if(MovPossiveis[ii]!=0) backend_textprintf_ex(bufferx, font_debug, 190      , 50+ ii     *21, backend_makecol(255,255,255), backend_makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
		for (int ii= 20; ii<= 39; ii++) { if(MovPossiveis[ii]!=0) backend_textprintf_ex(bufferx, font_debug, 190+ 37*1, 50+(ii- 20)*21, backend_makecol(255,255,255), backend_makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
		for (int ii= 40; ii<= 59; ii++) { if(MovPossiveis[ii]!=0) backend_textprintf_ex(bufferx, font_debug, 190+ 37*2, 50+(ii- 40)*21, backend_makecol(255,255,255), backend_makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
		for (int ii= 60; ii<= 79; ii++) { if(MovPossiveis[ii]!=0) backend_textprintf_ex(bufferx, font_debug, 190+ 37*3, 50+(ii- 60)*21, backend_makecol(255,255,255), backend_makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
		for (int ii= 80; ii<= 99; ii++) { if(MovPossiveis[ii]!=0) backend_textprintf_ex(bufferx, font_debug, 190+ 37*4, 50+(ii- 80)*21, backend_makecol(255,255,255), backend_makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
		for (int ii=100; ii<=119; ii++) { if(MovPossiveis[ii]!=0) backend_textprintf_ex(bufferx, font_debug, 190+ 37*5, 50+(ii-100)*21, backend_makecol(255,255,255), backend_makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
		for (int ii=120; ii<=139; ii++) { if(MovPossiveis[ii]!=0) backend_textprintf_ex(bufferx, font_debug, 190+ 37*6, 50+(ii-120)*21, backend_makecol(255,255,255), backend_makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
	*/

//botoes ED_MODE
if(key_Mouse_L_status==1 && backend_mouse_x>550 && backend_mouse_x<590 && backend_mouse_y>0 && backend_mouse_y<40){ ED_MODE=1; }
if(key_Mouse_L_status==1 && backend_mouse_x>595 && backend_mouse_x<635 && backend_mouse_y>0 && backend_mouse_y<40){
ED_MODE=2;
//ED_Pause=1;
ED_MovimentaPivot=0;
ED_DrawBlueMode=0;
ED_DrawRedMode=0; ED_bt_Null=0;
ED_load_inputs(ED_State);
}

if(ED_MODE==1){
backend_draw_sprite(bufferx, ed_mode1_on, 550, 0);
backend_draw_sprite(bufferx, ed_mode2_off, 595, 0);
}

//retangulos marcacao do botoes do ED_MODE
backend_rectfill(bufferx, 550-90, 0, 550+40-90, 0+40, 0x777777);
backend_rectfill(bufferx, 595-90, 0, 595+40-90, 0+40, 0x777777);
backend_rect(bufferx, 550-90, 0, 550+40-90, 0+40, 0xffffff);
backend_rect(bufferx, 595-90, 0, 595+40-90, 0+40, 0xffffff);

backend_rect(bufferx, 550, 0, 550+40, 0+40, 0xffffff);
backend_rect(bufferx, 595, 0, 595+40, 0+40, 0xffffff);

if(ED_MODE==2){

backend_draw_sprite(bufferx, ed_mode1_off, 550, 0);
backend_draw_sprite(bufferx, ed_mode2_on, 595, 0);

//desenha controles dos especiais
//backend_rect(bufferx,180-2+265, 50-2,630+2,100+2,0xffffff);//moldura grande

backend_drawing_mode(HM_DRAW_MODE_TRANS, 0, 0, 0); backend_set_trans_blender(0, 0, 0, 50);
backend_rectfill(bufferx,278, 50,630,100,0x000000); backend_drawing_mode(HM_DRAW_MODE_SOLID, 0, 0, 0);
backend_rect(bufferx,278, 50,630,100,0xffffff);//moldura inputs

backend_draw_sprite(bufferx, bt_reset_input, 195+20*16+90, 47);

backend_drawing_mode(HM_DRAW_MODE_TRANS, 0, 0, 0); backend_set_trans_blender(0, 0, 0, 50);
backend_rectfill(bufferx,178, 50,267,100,0x000000); backend_drawing_mode(HM_DRAW_MODE_SOLID, 0, 0, 0);
backend_rect(bufferx,178, 50,267,100,0xffffff);//moldura variation

if(ED_Special_Version==1) backend_rectfill(bufferx,195-10,75,220-10,95,0xff0000); //v1
if(ED_Special_Version==2) backend_rectfill(bufferx,220-10,75,245-10,95,0xff0000); //v2
if(ED_Special_Version==3) backend_rectfill(bufferx,245-10,75,270-10,95,0xff0000); //v3
backend_rect(bufferx,195-10,75,220-10,95,0xffffff); //moldura v1
backend_rect(bufferx,220-10,75,245-10,95,0xffffff); //moldura v2
backend_rect(bufferx,245-10,75,270-10,95,0xffffff); //moldura v3
backend_textprintf_ex(bufferx, font_debug, 195-10, 55, 0xffff00, -1,  "Variation" );
backend_textprintf_ex(bufferx, font_debug, 205-10, 75, 0xffffff, -1,  "1" );
backend_textprintf_ex(bufferx, font_debug, 230-10, 75, 0xffffff, -1,  "2" );
backend_textprintf_ex(bufferx, font_debug, 255-10, 75, 0xffffff, -1,  "3" );
backend_textprintf_ex(bufferx, font_debug, 195+90, 55, 0xffff00, -1,  "Input" );

//desenha inputs no ED
for(int ind=0; ind<=15; ind++){
//backend_draw_sprite(bufferx, spr_input_0, 195+20*ind+90, 75);
backend_circlefill(bufferx,195+20* ind+90+8,75+8,2,0x000000);
if(ED_State>=700){
int indexador;
if(ED_State>=700 && ED_State<710){ indexador=0; }
if(ED_State==710 && ED_State<720){ indexador=1; }
if(ED_State==720 && ED_State<730){ indexador=2; }
if(ED_State==730 && ED_State<740){ indexador=3; }
if(ED_State==740 && ED_State<750){ indexador=4; }
if(ED_State==750 && ED_State<760){ indexador=5; }
if(ED_State==760 && ED_State<770){ indexador=6; }
if(ED_State==770 && ED_State<780){ indexador=7; }
if(ED_State==780 && ED_State<790){ indexador=8; }
if(ED_State==790 && ED_State<800){ indexador=9; }
if (P[1].Special_Inputs[indexador][ind+1]== 8) { backend_draw_sprite(bufferx, spr_input_0 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]== 9) { backend_draw_sprite(bufferx, spr_input_1 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]== 6) { backend_draw_sprite(bufferx, spr_input_2 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]== 3) { backend_draw_sprite(bufferx, spr_input_3 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]== 2) { backend_draw_sprite(bufferx, spr_input_4 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]== 1) { backend_draw_sprite(bufferx, spr_input_5 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]== 4) { backend_draw_sprite(bufferx, spr_input_6 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]== 7) { backend_draw_sprite(bufferx, spr_input_7 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-1) { backend_draw_sprite(bufferx, spr_input_8 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-2) { backend_draw_sprite(bufferx, spr_input_9 , 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-3) { backend_draw_sprite(bufferx, spr_input_10, 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-4) { backend_draw_sprite(bufferx, spr_input_11, 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-5) { backend_draw_sprite(bufferx, spr_input_12, 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-6) { backend_draw_sprite(bufferx, spr_input_13, 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-7) { backend_draw_sprite(bufferx, spr_input_16, 195+20*ind+90, 75); }
if (P[1].Special_Inputs[indexador][ind+1]==-8) { backend_draw_sprite(bufferx, spr_input_17, 195+20*ind+90, 75); }
}else{
if(ED_State==101){ backend_draw_sprite(bufferx, spr_input_8 , 195+20*0+90, 75); }
if(ED_State==102){ backend_draw_sprite(bufferx, spr_input_9 , 195+20*0+90, 75); }
if(ED_State==103){ backend_draw_sprite(bufferx, spr_input_10, 195+20*0+90, 75); }
if(ED_State==104){ backend_draw_sprite(bufferx, spr_input_11, 195+20*0+90, 75); }
if(ED_State==105){ backend_draw_sprite(bufferx, spr_input_12, 195+20*0+90, 75); }
if(ED_State==106){ backend_draw_sprite(bufferx, spr_input_13, 195+20*0+90, 75); }
if(ED_State==151){ backend_draw_sprite(bufferx, spr_input_8 , 195+20*0+90, 75); }
if(ED_State==152){ backend_draw_sprite(bufferx, spr_input_9 , 195+20*0+90, 75); }
if(ED_State==153){ backend_draw_sprite(bufferx, spr_input_10, 195+20*0+90, 75); }
if(ED_State==154){ backend_draw_sprite(bufferx, spr_input_11, 195+20*0+90, 75); }
if(ED_State==155){ backend_draw_sprite(bufferx, spr_input_12, 195+20*0+90, 75); }
if(ED_State==156){ backend_draw_sprite(bufferx, spr_input_13, 195+20*0+90, 75); }
if(ED_State>=200 && ED_State<=256){ backend_draw_sprite(bufferx, spr_input_4 , 195+20*0+90, 75); }
if(ED_State==201){ backend_draw_sprite(bufferx, spr_input_8 , 195+20*1+90, 75); }
if(ED_State==202){ backend_draw_sprite(bufferx, spr_input_9 , 195+20*1+90, 75); }
if(ED_State==203){ backend_draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
if(ED_State==204){ backend_draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
if(ED_State==205){ backend_draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
if(ED_State==206){ backend_draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
if(ED_State>=300 && ED_State<=306){ backend_draw_sprite(bufferx, spr_input_0, 195+20*0+90, 75); }
if(ED_State==301){ backend_draw_sprite(bufferx, spr_input_8 , 195+20*1+90, 75); }
if(ED_State==302){ backend_draw_sprite(bufferx, spr_input_9 , 195+20*1+90, 75); }
if(ED_State==303){ backend_draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
if(ED_State==304){ backend_draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
if(ED_State==305){ backend_draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
if(ED_State==306){ backend_draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
if(ED_State==310){ backend_draw_sprite(bufferx, spr_input_7 , 195+20*0+90, 75); }
if(ED_State==311){ backend_draw_sprite(bufferx, spr_input_8 , 195+20*1+90, 75); }
if(ED_State==312){ backend_draw_sprite(bufferx, spr_input_9 , 195+20*1+90, 75); }
if(ED_State==313){ backend_draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
if(ED_State==314){ backend_draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
if(ED_State==315){ backend_draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
if(ED_State==316){ backend_draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
if(ED_State==320){ backend_draw_sprite(bufferx, spr_input_1 , 195+20*0+90, 75); }
if(ED_State>=320 && ED_State<=326){ backend_draw_sprite(bufferx, spr_input_1, 195+20*0+90, 75); }
if(ED_State==321){ backend_draw_sprite(bufferx, spr_input_8 , 195+20*1+90, 75); }
if(ED_State==322){ backend_draw_sprite(bufferx, spr_input_9 , 195+20*1+90, 75); }
if(ED_State==323){ backend_draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
if(ED_State==324){ backend_draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
if(ED_State==325){ backend_draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
if(ED_State==326){ backend_draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
if(ED_State==410){ backend_draw_sprite(bufferx, spr_input_6 , 195+20*0+90, 75); }
if(ED_State==420){ backend_draw_sprite(bufferx, spr_input_2 , 195+20*0+90, 75); }
}
}

backend_rect(bufferx,10-2,50-2,150,110,0xffff00); //moldura keys

//brilho redondo nos botoes

if(backend_mouse_x>19+20*0-9 && backend_mouse_x<19+20*0+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) backend_circlefill(bufferx, 19+20*0, 59, 12, 0xffff00);
if(backend_mouse_x>19+20*1-9 && backend_mouse_x<19+20*1+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) backend_circlefill(bufferx, 19+20*1, 59, 12, 0xffff00);
if(backend_mouse_x>19+20*2-9 && backend_mouse_x<19+20*2+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) backend_circlefill(bufferx, 19+20*2, 59, 12, 0xffff00);
if(backend_mouse_x>19+20*4-9 && backend_mouse_x<19+20*4+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) backend_circlefill(bufferx, 19+20*4, 59, 12, 0xffff00);
if(backend_mouse_x>19+20*5-9 && backend_mouse_x<19+20*5+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) backend_circlefill(bufferx, 19+20*5, 59, 12, 0xffff00);
//if(backend_mouse_x>19+20*6-9 && backend_mouse_x<19+20*6+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) backend_circlefill(bufferx, 19+20*6, 59, 12, 0xffff00);

if(backend_mouse_x>19+20*0-9 && backend_mouse_x<19+20*0+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) backend_circlefill(bufferx, 19+20*0, 79, 12, 0xffff00);
//if(backend_mouse_x>19+20*1-9 && backend_mouse_x<19+20*1+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) backend_circlefill(bufferx, 19+20*1, 79, 12, 0xffff00);
if(backend_mouse_x>19+20*2-9 && backend_mouse_x<19+20*2+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) backend_circlefill(bufferx, 19+20*2, 79, 12, 0xffff00);
if(backend_mouse_x>19+20*4-9 && backend_mouse_x<19+20*4+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) backend_circlefill(bufferx, 19+20*4, 79, 12, 0xffff00);
if(backend_mouse_x>19+20*5-9 && backend_mouse_x<19+20*5+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) backend_circlefill(bufferx, 19+20*5, 79, 12, 0xffff00);
if(backend_mouse_x>19+20*6-9 && backend_mouse_x<19+20*6+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) backend_circlefill(bufferx, 19+20*6, 79, 12, 0xffff00);

if(backend_mouse_x>19+20*0-9 && backend_mouse_x<19+20*0+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) backend_circlefill(bufferx, 19+20*0, 99, 12, 0xffff00);
if(backend_mouse_x>19+20*1-9 && backend_mouse_x<19+20*1+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) backend_circlefill(bufferx, 19+20*1, 99, 12, 0xffff00);
if(backend_mouse_x>19+20*2-9 && backend_mouse_x<19+20*2+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) backend_circlefill(bufferx, 19+20*2, 99, 12, 0xffff00);
if(backend_mouse_x>19+20*4-9 && backend_mouse_x<19+20*4+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) backend_circlefill(bufferx, 19+20*4, 99, 12, 0xffff00);
if(backend_mouse_x>19+20*5-9 && backend_mouse_x<19+20*5+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) backend_circlefill(bufferx, 19+20*5, 99, 12, 0xffff00);
if(backend_mouse_x>19+20*6-9 && backend_mouse_x<19+20*6+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) backend_circlefill(bufferx, 19+20*6, 99, 12, 0xffff00);

backend_draw_sprite(bufferx, spr_input_7, 10+20*0, 50);
backend_draw_sprite(bufferx, spr_input_0, 10+20*1, 50);
backend_draw_sprite(bufferx, spr_input_1, 10+20*2, 50);
backend_draw_sprite(bufferx, spr_input_6, 10+20*0, 70);
//backend_draw_sprite(bufferx, spr_input_0, 10+20*1, 70);
backend_draw_sprite(bufferx, spr_input_2, 10+20*2, 70);
backend_draw_sprite(bufferx, spr_input_5, 10+20*0, 90);
backend_draw_sprite(bufferx, spr_input_4, 10+20*1, 90);
backend_draw_sprite(bufferx, spr_input_3, 10+20*2, 90);
backend_draw_sprite(bufferx, spr_input_16, 10+20*4, 50);
backend_draw_sprite(bufferx, spr_input_17, 10+20*5, 50);
//backend_draw_sprite(bufferx, spr_input_10, 10+20*6, 50);
backend_draw_sprite(bufferx, spr_input_8, 10+20*4, 70);
backend_draw_sprite(bufferx, spr_input_9, 10+20*5, 70);
backend_draw_sprite(bufferx, spr_input_10, 10+20*6, 70);
backend_draw_sprite(bufferx, spr_input_11, 10+20*4, 90);
backend_draw_sprite(bufferx, spr_input_12, 10+20*5, 90);
backend_draw_sprite(bufferx, spr_input_13, 10+20*6, 90);

//add com&& input list
int add_command=0;
if(key_Mouse_L_status==1){
if(backend_mouse_x>19+20*0-9 && backend_mouse_x<19+20*0+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) add_command=7;
if(backend_mouse_x>19+20*1-9 && backend_mouse_x<19+20*1+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) add_command=8;
if(backend_mouse_x>19+20*2-9 && backend_mouse_x<19+20*2+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) add_command=9;

if(backend_mouse_x>19+20*4-9 && backend_mouse_x<19+20*4+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) add_command=-7;
if(backend_mouse_x>19+20*5-9 && backend_mouse_x<19+20*5+9 && backend_mouse_y>59-9 && backend_mouse_y<59+9) add_command=-8;

if(backend_mouse_x>19+20*0-9 && backend_mouse_x<19+20*0+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) add_command=4;
//if(backend_mouse_x>19+20*1-9 && backend_mouse_x<19+20*1+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) add_command=5;
if(backend_mouse_x>19+20*2-9 && backend_mouse_x<19+20*2+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) add_command=6;

if(backend_mouse_x>19+20*4-9 && backend_mouse_x<19+20*4+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) add_command=-1;
if(backend_mouse_x>19+20*5-9 && backend_mouse_x<19+20*5+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) add_command=-2;
if(backend_mouse_x>19+20*6-9 && backend_mouse_x<19+20*6+9 && backend_mouse_y>79-9 && backend_mouse_y<79+9) add_command=-3;

if(backend_mouse_x>19+20*0-9 && backend_mouse_x<19+20*0+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) add_command=1;
if(backend_mouse_x>19+20*1-9 && backend_mouse_x<19+20*1+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) add_command=2;
if(backend_mouse_x>19+20*2-9 && backend_mouse_x<19+20*2+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) add_command=3;

if(backend_mouse_x>19+20*4-9 && backend_mouse_x<19+20*4+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) add_command=-4;
if(backend_mouse_x>19+20*5-9 && backend_mouse_x<19+20*5+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) add_command=-5;
if(backend_mouse_x>19+20*6-9 && backend_mouse_x<19+20*6+9 && backend_mouse_y>99-9 && backend_mouse_y<99+9) add_command=-6;
}
if(add_command!=0 && ED_State>=700){
int addcmd=0;
if(ED_State==700) { addcmd=0; }
if(ED_State==710) { addcmd=1; }
if(ED_State==720) { addcmd=2; }
if(ED_State==730) { addcmd=3; }
if(ED_State==740) { addcmd=4; }
if(ED_State==750) { addcmd=5; }
if(ED_State==760) { addcmd=6; }
if(ED_State==770) { addcmd=7; }
if(ED_State==780) { addcmd=8; }
if(ED_State==790) { addcmd=9; }
//P[1].Special_Inputs[addcmd][0]++;
if(add_command>0){
P[1].Special_Inputs_c[addcmd][P[1].Special_Inputs_c[addcmd][0]+1]=add_command;
P[1].Special_Inputs_c[addcmd][0]++;
}
if(add_command<0){
P[1].Special_Inputs_b[addcmd][P[1].Special_Inputs_b[addcmd][0]+1]=add_command;
P[1].Special_Inputs_b[addcmd][0]++;
}
//input combinado
for(int indx=0; indx<=9; indx++){
for(int ind=1; ind<=P[1].Special_Inputs_c[indx][0]; ind++){
P[1].Special_Inputs[indx][ind] = P[1].Special_Inputs_c[indx][ind];
}
for(int ind=1; ind<=P[1].Special_Inputs_b[indx][0]; ind++){
P[1].Special_Inputs[indx][ind+P[1].Special_Inputs_c[indx][0]] = P[1].Special_Inputs_b[indx][ind];
}
P[1].Special_Inputs[indx][0]=P[1].Special_Inputs_c[indx][0]+P[1].Special_Inputs_b[indx][0];
}

//BUG// Nota: Tem que salvar o novo input no special.ini!
}

//botao reset input list
if(key_Mouse_L_status==1 && ED_State>=700){
if(backend_mouse_x>609 && backend_mouse_x<609+20 && backend_mouse_y>51 && backend_mouse_y<51+20) {
int addcmd=0;
if(ED_State==700) { addcmd=0; }
if(ED_State==710) { addcmd=1; }
if(ED_State==720) { addcmd=2; }
if(ED_State==730) { addcmd=3; }
if(ED_State==740) { addcmd=4; }
if(ED_State==750) { addcmd=5; }
if(ED_State==760) { addcmd=6; }
if(ED_State==770) { addcmd=7; }
if(ED_State==780) { addcmd=8; }
if(ED_State==790) { addcmd=9; }
//zera o array dos especiais
for(int ind=0; ind<=16; ind++){
P[1].Special_Inputs_c[addcmd][ind]=0;
P[1].Special_Inputs_b[addcmd][ind]=0;
P[1].Special_Inputs[addcmd][ind]=0;
}
}
}

//botoes special variation
if(key_Mouse_L_status==1 && backend_mouse_x>185 && backend_mouse_x<210 && backend_mouse_y>75 && backend_mouse_y<95){ ED_Special_Version=1; ED_load_charini(); }
if(key_Mouse_L_status==1 && backend_mouse_x>210 && backend_mouse_x<235 && backend_mouse_y>75 && backend_mouse_y<95){ ED_Special_Version=2; ED_load_charini(); }
if(key_Mouse_L_status==1 && backend_mouse_x>235 && backend_mouse_x<260 && backend_mouse_y>75 && backend_mouse_y<95){ ED_Special_Version=3; ED_load_charini(); }

//botoes de config e caixas
for(int ind=4; ind<=18; ind++){
backend_rectfill(bufferx,365+220,58+15*ind,395+220,71+15*ind,0x000000);
backend_rect(bufferx,365+220,58+15*ind,395+220,71+15*ind,0xffffff);
backend_drawing_mode(HM_DRAW_MODE_TRANS, 0, 0, 0);
backend_set_trans_blender(0, 0, 0, 50);
backend_rectfill(bufferx,450,58+15*ind,630,71+15*ind,0x000000);
backend_drawing_mode(HM_DRAW_MODE_SOLID, 0, 0, 0);
backend_circlefill(bufferx,355+220,65+15*ind,7,0x000000);
backend_circlefill(bufferx,404+220,65+15*ind,7,0x000000);
backend_circle(bufferx,355+220,65+15*ind,7,0xffffff);
backend_circle(bufferx,404+220,65+15*ind,7,0xffffff);
backend_textprintf_centre_ex(bufferx, font_debug, 381+220, 55+15*ind, 0xffffff, -1,  "999" );
backend_textprintf_centre_ex(bufferx, font_debug, 355+220, 55+15*ind, 0xffffff, -1,  "-" );
backend_textprintf_centre_ex(bufferx, font_debug, 404+220, 55+15*ind, 0xffffff, -1,  "+" );
}

backend_textprintf_ex(bufferx, font_debug, 460, 55+15* 3, 0xffff00, -1,  "Actuators" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15* 4, 0xffffff, -1,  "X" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15* 5, 0xffffff, -1,  "Y" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15* 6, 0xffffff, -1,  "VSpeed" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15* 7, 0xffffff, -1,  "HSpeed" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15* 8, 0xffffff, -1,  "Gravity" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15* 9, 0x000000, -1,  "Friction" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*10, 0xffffff, -1,  "EnergyChange" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*11, 0xffffff, -1,  "SpecialChange" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*12, 0xffffff, -1,  "Visible" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*13, 0x000000, -1,  "RoomLimit" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*14, 0xffffff, -1,  "HitType" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*15, 0xffffff, -1,  "HitStack" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*16, 0xffffff, -1,  "ChangeState" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*17, 0x000000, -1,  "Freeze" );
backend_textprintf_ex(bufferx, font_debug, 460, 55+15*18, 0x000000, -1,  "Color" );

}

for (int i=0; i<=9; i++) { for (int j=0; j<=2; j++) { int z=55;
if (j==0) { backend_rectfill(bufferx, 5+j*z,245+i*15,53+j*z,258+i*15,backend_makecol(000,000,000)); }
if (j!=0) { backend_rectfill(bufferx, 5+j*z,245+i*15,53+j*z,258+i*15,backend_makecol(000,000,000)); }
if (ED_IndexAnim==i) { if (ED_IndexAnim<9) { backend_rect(bufferx, 5+0*z,245+i*15,53+0*55,258+i*15,backend_makecol(255,000,000)); }
if (ED_IndexAnim>=10 && ED_IndexAnim<20 ) { backend_rect(bufferx, 5+1*z,245+i*15,53+1*55,258+i*15,backend_makecol(255,000,000)); }
if (ED_IndexAnim>=20 && ED_IndexAnim<30 ) { backend_rect(bufferx, 5+2*z,245+i*15,53+2*55,258+i*15,backend_makecol(255,000,000)); }
} } }
backend_rectfill(bufferx, 5, 396, 163, 413,backend_makecol(000,000,000));
backend_rect(bufferx, 5, 396, 163, 413,backend_makecol(100,100,100));
int sum=0;
if (ED_TotalFrames>= 0) { sum=sum+ED_FrameTime_00+1; }
if (ED_TotalFrames>= 1) { sum=sum+ED_FrameTime_01+1; }
if (ED_TotalFrames>= 2) { sum=sum+ED_FrameTime_02+1; }
if (ED_TotalFrames>= 3) { sum=sum+ED_FrameTime_03+1; }
if (ED_TotalFrames>= 4) { sum=sum+ED_FrameTime_04+1; }
if (ED_TotalFrames>= 5) { sum=sum+ED_FrameTime_05+1; }
if (ED_TotalFrames>= 6) { sum=sum+ED_FrameTime_06+1; }
if (ED_TotalFrames>= 7) { sum=sum+ED_FrameTime_07+1; }
if (ED_TotalFrames>= 8) { sum=sum+ED_FrameTime_08+1; }
if (ED_TotalFrames>= 9) { sum=sum+ED_FrameTime_09+1; }
if (ED_TotalFrames>=10) { sum=sum+ED_FrameTime_10+1; }
if (ED_TotalFrames>=11) { sum=sum+ED_FrameTime_11+1; }
if (ED_TotalFrames>=12) { sum=sum+ED_FrameTime_12+1; }
if (ED_TotalFrames>=13) { sum=sum+ED_FrameTime_13+1; }
if (ED_TotalFrames>=14) { sum=sum+ED_FrameTime_14+1; }
if (ED_TotalFrames>=15) { sum=sum+ED_FrameTime_15+1; }
if (ED_TotalFrames>=16) { sum=sum+ED_FrameTime_16+1; }
if (ED_TotalFrames>=17) { sum=sum+ED_FrameTime_17+1; }
if (ED_TotalFrames>=18) { sum=sum+ED_FrameTime_18+1; }
if (ED_TotalFrames>=19) { sum=sum+ED_FrameTime_19+1; }
if (ED_TotalFrames>=20) { sum=sum+ED_FrameTime_20+1; }
if (ED_TotalFrames>=21) { sum=sum+ED_FrameTime_21+1; }
if (ED_TotalFrames>=22) { sum=sum+ED_FrameTime_22+1; }
if (ED_TotalFrames>=23) { sum=sum+ED_FrameTime_23+1; }
if (ED_TotalFrames>=24) { sum=sum+ED_FrameTime_24+1; }
if (ED_TotalFrames>=25) { sum=sum+ED_FrameTime_25+1; }
if (ED_TotalFrames>=26) { sum=sum+ED_FrameTime_26+1; }
if (ED_TotalFrames>=27) { sum=sum+ED_FrameTime_27+1; }
if (ED_TotalFrames>=28) { sum=sum+ED_FrameTime_28+1; }
if (ED_TotalFrames>=29) { sum=sum+ED_FrameTime_29+1; }
backend_textprintf_centre_ex(bufferx, font_debug, 84, 395, backend_makecol(255,255,255), -1, "TOTAL: %i", sum);

if ( ED_TotalFrames>= 0 && ED_FrameTime_00!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+0*15, backend_makecol(255,255,255), -1, "00. %i", ED_FrameTime_00+1); }
if ( ED_TotalFrames>= 1 && ED_FrameTime_01!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+1*15, backend_makecol(255,255,255), -1, "01. %i", ED_FrameTime_01+1); }
if ( ED_TotalFrames>= 2 && ED_FrameTime_02!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+2*15, backend_makecol(255,255,255), -1, "02. %i", ED_FrameTime_02+1); }
if ( ED_TotalFrames>= 3 && ED_FrameTime_03!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+3*15, backend_makecol(255,255,255), -1, "03. %i", ED_FrameTime_03+1); }
if ( ED_TotalFrames>= 4 && ED_FrameTime_04!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+4*15, backend_makecol(255,255,255), -1, "04. %i", ED_FrameTime_04+1); }
if ( ED_TotalFrames>= 5 && ED_FrameTime_05!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+5*15, backend_makecol(255,255,255), -1, "05. %i", ED_FrameTime_05+1); }
if ( ED_TotalFrames>= 6 && ED_FrameTime_06!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+6*15, backend_makecol(255,255,255), -1, "06. %i", ED_FrameTime_06+1); }
if ( ED_TotalFrames>= 7 && ED_FrameTime_07!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+7*15, backend_makecol(255,255,255), -1, "07. %i", ED_FrameTime_07+1); }
if ( ED_TotalFrames>= 8 && ED_FrameTime_08!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+8*15, backend_makecol(255,255,255), -1, "08. %i", ED_FrameTime_08+1); }
if ( ED_TotalFrames>= 9 && ED_FrameTime_09!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+0*55, 242+9*15, backend_makecol(255,255,255), -1, "09. %i", ED_FrameTime_09+1); }
if ( ED_TotalFrames>=10 && ED_FrameTime_10!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+0*15, backend_makecol(255,255,255), -1, "10. %i", ED_FrameTime_10+1); }
if ( ED_TotalFrames>=11 && ED_FrameTime_11!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+1*15, backend_makecol(255,255,255), -1, "11. %i", ED_FrameTime_11+1); }
if ( ED_TotalFrames>=12 && ED_FrameTime_12!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+2*15, backend_makecol(255,255,255), -1, "12. %i", ED_FrameTime_12+1); }
if ( ED_TotalFrames>=13 && ED_FrameTime_13!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+3*15, backend_makecol(255,255,255), -1, "13. %i", ED_FrameTime_13+1); }
if ( ED_TotalFrames>=14 && ED_FrameTime_14!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+4*15, backend_makecol(255,255,255), -1, "14. %i", ED_FrameTime_14+1); }
if ( ED_TotalFrames>=15 && ED_FrameTime_15!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+5*15, backend_makecol(255,255,255), -1, "15. %i", ED_FrameTime_15+1); }
if ( ED_TotalFrames>=16 && ED_FrameTime_16!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+6*15, backend_makecol(255,255,255), -1, "16. %i", ED_FrameTime_16+1); }
if ( ED_TotalFrames>=17 && ED_FrameTime_17!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+7*15, backend_makecol(255,255,255), -1, "17. %i", ED_FrameTime_17+1); }
if ( ED_TotalFrames>=18 && ED_FrameTime_18!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+8*15, backend_makecol(255,255,255), -1, "18. %i", ED_FrameTime_18+1); }
if ( ED_TotalFrames>=19 && ED_FrameTime_19!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+1*55, 242+9*15, backend_makecol(255,255,255), -1, "19. %i", ED_FrameTime_19+1); }
if ( ED_TotalFrames>=20 && ED_FrameTime_20!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+0*15, backend_makecol(255,255,255), -1, "20. %i", ED_FrameTime_20+1); }
if ( ED_TotalFrames>=21 && ED_FrameTime_21!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+1*15, backend_makecol(255,255,255), -1, "21. %i", ED_FrameTime_21+1); }
if ( ED_TotalFrames>=22 && ED_FrameTime_22!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+2*15, backend_makecol(255,255,255), -1, "22. %i", ED_FrameTime_22+1); }
if ( ED_TotalFrames>=23 && ED_FrameTime_23!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+3*15, backend_makecol(255,255,255), -1, "23. %i", ED_FrameTime_23+1); }
if ( ED_TotalFrames>=24 && ED_FrameTime_24!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+4*15, backend_makecol(255,255,255), -1, "24. %i", ED_FrameTime_24+1); }
if ( ED_TotalFrames>=25 && ED_FrameTime_25!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+5*15, backend_makecol(255,255,255), -1, "25. %i", ED_FrameTime_25+1); }
if ( ED_TotalFrames>=26 && ED_FrameTime_26!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+6*15, backend_makecol(255,255,255), -1, "26. %i", ED_FrameTime_26+1); }
if ( ED_TotalFrames>=27 && ED_FrameTime_27!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+7*15, backend_makecol(255,255,255), -1, "27. %i", ED_FrameTime_27+1); }
if ( ED_TotalFrames>=28 && ED_FrameTime_28!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+8*15, backend_makecol(255,255,255), -1, "28. %i", ED_FrameTime_28+1); }
if ( ED_TotalFrames>=29 && ED_FrameTime_29!=-1 ) { backend_textprintf_centre_ex(bufferx, font_debug, 30+2*55, 242+9*15, backend_makecol(255,255,255), -1, "29. %i", ED_FrameTime_29+1); }

if ( key_Mouse_L_status>0 && ED_Mx1>-1 && ED_My1>-1 ) { //efeito ao desenhar hboxes
if ( ED_DrawRedMode ==1 ) { if (ED_io>=0 && ED_io<=1) { backend_rect(bufferx, ED_Mx1,ED_My1,backend_mouse_x,backend_mouse_y,backend_makecol(255,255,255)); } if (ED_io>=2 && ED_io<=3) { backend_rect(bufferx, ED_Mx1,ED_My1,backend_mouse_x,backend_mouse_y,backend_makecol(255,000,000)); } }
if ( ED_DrawBlueMode==1 ) { if (ED_io>=0 && ED_io<=1) { backend_rect(bufferx, ED_Mx1,ED_My1,backend_mouse_x,backend_mouse_y,backend_makecol(255,255,255)); } if (ED_io>=2 && ED_io<=3) { backend_rect(bufferx, ED_Mx1,ED_My1,backend_mouse_x,backend_mouse_y,backend_makecol(000,000,255)); } } }
if ( key_Mouse_L_status==3 && ED_Mx1>-1 && ED_My1>-1 )
{ ED_Mx2=backend_mouse_x; ED_My2=backend_mouse_y; }

if ( ED_Mx1>-1 && ED_My1>-1 && ED_Mx2>-1 && ED_My2>-1 )
{
// DESENHO DO RETANGULO FEITO!
if (ED_DrawBlueMode==1) { ED_HurtBox_tot++; } if (ED_HurtBox_tot>9) { ED_HurtBox_tot=9; }
if (ED_DrawRedMode==1)  { ED_HitBox_tot++;  } if (ED_HitBox_tot>9 ) { ED_HitBox_tot =9; }

//1-Correcao do box
int temp1x=0;  int temp1y=0;  int temp2x=0;  int temp2y=0;
temp1x=ED_Mx1; temp1y=ED_My1; temp2x=ED_Mx2; temp2y=ED_My2;
if (temp1x<=temp2x) { ED_Mx1=temp1x; }
if (temp1x >temp2x) { ED_Mx1=temp2x; }
if (temp1y<=temp2y) { ED_My1=temp1y; }
if (temp1y >temp2y) { ED_My1=temp2y; }
if (temp2x >temp1x) { ED_Mx2=temp2x; }
if (temp2x<=temp1x) { ED_Mx2=temp1x; }
if (temp2y >temp1y) { ED_My2=temp2y; }
if (temp2y<=temp1y) { ED_My2=temp1y; }

// 2- Empilha o box
if ( ED_DrawBlueMode==1 ) {
if ( ED_HurtBox_tot==1 ) { ED_HurtBox01x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox01y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox01x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox01y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==2 ) { ED_HurtBox02x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox02y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox02x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox02y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==3 ) { ED_HurtBox03x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox03y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox03x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox03y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==4 ) { ED_HurtBox04x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox04y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox04x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox04y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==5 ) { ED_HurtBox05x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox05y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox05x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox05y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==6 ) { ED_HurtBox06x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox06y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox06x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox06y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==7 ) { ED_HurtBox07x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox07y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox07x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox07y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==8 ) { ED_HurtBox08x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox08y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox08x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox08y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HurtBox_tot==9 ) { ED_HurtBox09x1=((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HurtBox09y1=((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HurtBox09x2=((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HurtBox09y2=((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; } }
if ( ED_DrawRedMode==1 ) {
if ( ED_HitBox_tot==1 ) { ED_HitBox01x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox01y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox01x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox01y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==2 ) { ED_HitBox02x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox02y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox02x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox02y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==3 ) { ED_HitBox03x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox03y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox03x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox03y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==4 ) { ED_HitBox04x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox04y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox04x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox04y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==5 ) { ED_HitBox05x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox05y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox05x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox05y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==6 ) { ED_HitBox06x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox06y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox06x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox06y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==7 ) { ED_HitBox07x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox07y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox07x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox07y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==8 ) { ED_HitBox08x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox08y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox08x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox08y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; }
else if ( ED_HitBox_tot==9 ) { ED_HitBox09x1 =((ED_Mx1/2)-(ED_x-ED_XAlign))-ED_XAlign; ED_HitBox09y1 =((ED_My1/2)-(ED_y-ED_YAlign))-ED_YAlign; ED_HitBox09x2 =((ED_Mx2/2)-(ED_x-ED_XAlign))-ED_XAlign;  ED_HitBox09y2 =((ED_My2/2)-(ED_y-ED_YAlign))-ED_YAlign; } }

//4-salva novo HBox
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/chbox.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3];
if (ED_IndexAnim<10 ) { sprintf(ED_State_s, "%i_0%i", ED_State, ED_IndexAnim); }
if (ED_IndexAnim>=10) { sprintf(ED_State_s, "%i_%i" , ED_State, ED_IndexAnim); }
if (ED_DrawBlueMode==1) {
if ( ED_HurtBox_tot==1 ) { backend_set_config_int(ED_State_s, "HurtBox01x1", ED_HurtBox01x1); }
if ( ED_HurtBox_tot==1 ) { backend_set_config_int(ED_State_s, "HurtBox01y1", ED_HurtBox01y1); }
if ( ED_HurtBox_tot==1 ) { backend_set_config_int(ED_State_s, "HurtBox01x2", ED_HurtBox01x2); }
if ( ED_HurtBox_tot==1 ) { backend_set_config_int(ED_State_s, "HurtBox01y2", ED_HurtBox01y2); }
if ( ED_HurtBox_tot==2 ) { backend_set_config_int(ED_State_s, "HurtBox02x1", ED_HurtBox02x1); }
if ( ED_HurtBox_tot==2 ) { backend_set_config_int(ED_State_s, "HurtBox02y1", ED_HurtBox02y1); }
if ( ED_HurtBox_tot==2 ) { backend_set_config_int(ED_State_s, "HurtBox02x2", ED_HurtBox02x2); }
if ( ED_HurtBox_tot==2 ) { backend_set_config_int(ED_State_s, "HurtBox02y2", ED_HurtBox02y2); }
if ( ED_HurtBox_tot==3 ) { backend_set_config_int(ED_State_s, "HurtBox03x1", ED_HurtBox03x1); }
if ( ED_HurtBox_tot==3 ) { backend_set_config_int(ED_State_s, "HurtBox03y1", ED_HurtBox03y1); }
if ( ED_HurtBox_tot==3 ) { backend_set_config_int(ED_State_s, "HurtBox03x2", ED_HurtBox03x2); }
if ( ED_HurtBox_tot==3 ) { backend_set_config_int(ED_State_s, "HurtBox03y2", ED_HurtBox03y2); }
if ( ED_HurtBox_tot==4 ) { backend_set_config_int(ED_State_s, "HurtBox04x1", ED_HurtBox04x1); }
if ( ED_HurtBox_tot==4 ) { backend_set_config_int(ED_State_s, "HurtBox04y1", ED_HurtBox04y1); }
if ( ED_HurtBox_tot==4 ) { backend_set_config_int(ED_State_s, "HurtBox04x2", ED_HurtBox04x2); }
if ( ED_HurtBox_tot==4 ) { backend_set_config_int(ED_State_s, "HurtBox04y2", ED_HurtBox04y2); }
if ( ED_HurtBox_tot==5 ) { backend_set_config_int(ED_State_s, "HurtBox05x1", ED_HurtBox05x1); }
if ( ED_HurtBox_tot==5 ) { backend_set_config_int(ED_State_s, "HurtBox05y1", ED_HurtBox05y1); }
if ( ED_HurtBox_tot==5 ) { backend_set_config_int(ED_State_s, "HurtBox05x2", ED_HurtBox05x2); }
if ( ED_HurtBox_tot==5 ) { backend_set_config_int(ED_State_s, "HurtBox05y2", ED_HurtBox05y2); }
if ( ED_HurtBox_tot==6 ) { backend_set_config_int(ED_State_s, "HurtBox06x1", ED_HurtBox06x1); }
if ( ED_HurtBox_tot==6 ) { backend_set_config_int(ED_State_s, "HurtBox06y1", ED_HurtBox06y1); }
if ( ED_HurtBox_tot==6 ) { backend_set_config_int(ED_State_s, "HurtBox06x2", ED_HurtBox06x2); }
if ( ED_HurtBox_tot==6 ) { backend_set_config_int(ED_State_s, "HurtBox06y2", ED_HurtBox06y2); }
if ( ED_HurtBox_tot==7 ) { backend_set_config_int(ED_State_s, "HurtBox07x1", ED_HurtBox07x1); }
if ( ED_HurtBox_tot==7 ) { backend_set_config_int(ED_State_s, "HurtBox07y1", ED_HurtBox07y1); }
if ( ED_HurtBox_tot==7 ) { backend_set_config_int(ED_State_s, "HurtBox07x2", ED_HurtBox07x2); }
if ( ED_HurtBox_tot==7 ) { backend_set_config_int(ED_State_s, "HurtBox07y2", ED_HurtBox07y2); }
if ( ED_HurtBox_tot==8 ) { backend_set_config_int(ED_State_s, "HurtBox08x1", ED_HurtBox08x1); }
if ( ED_HurtBox_tot==8 ) { backend_set_config_int(ED_State_s, "HurtBox08y1", ED_HurtBox08y1); }
if ( ED_HurtBox_tot==8 ) { backend_set_config_int(ED_State_s, "HurtBox08x2", ED_HurtBox08x2); }
if ( ED_HurtBox_tot==8 ) { backend_set_config_int(ED_State_s, "HurtBox08y2", ED_HurtBox08y2); }
if ( ED_HurtBox_tot==9 ) { backend_set_config_int(ED_State_s, "HurtBox09x1", ED_HurtBox09x1); }
if ( ED_HurtBox_tot==9 ) { backend_set_config_int(ED_State_s, "HurtBox09y1", ED_HurtBox09y1); }
if ( ED_HurtBox_tot==9 ) { backend_set_config_int(ED_State_s, "HurtBox09x2", ED_HurtBox09x2); }
if ( ED_HurtBox_tot==9 ) { backend_set_config_int(ED_State_s, "HurtBox09y2", ED_HurtBox09y2); }
}
if (ED_DrawRedMode==1)
{
if ( ED_HitBox_tot==1 ) { backend_set_config_int(ED_State_s, "HitBox01x1", ED_HitBox01x1); }
if ( ED_HitBox_tot==1 ) { backend_set_config_int(ED_State_s, "HitBox01y1", ED_HitBox01y1); }
if ( ED_HitBox_tot==1 ) { backend_set_config_int(ED_State_s, "HitBox01x2", ED_HitBox01x2); }
if ( ED_HitBox_tot==1 ) { backend_set_config_int(ED_State_s, "HitBox01y2", ED_HitBox01y2); }
if ( ED_HitBox_tot==2 ) { backend_set_config_int(ED_State_s, "HitBox02x1", ED_HitBox02x1); }
if ( ED_HitBox_tot==2 ) { backend_set_config_int(ED_State_s, "HitBox02y1", ED_HitBox02y1); }
if ( ED_HitBox_tot==2 ) { backend_set_config_int(ED_State_s, "HitBox02x2", ED_HitBox02x2); }
if ( ED_HitBox_tot==2 ) { backend_set_config_int(ED_State_s, "HitBox02y2", ED_HitBox02y2); }
if ( ED_HitBox_tot==3 ) { backend_set_config_int(ED_State_s, "HitBox03x1", ED_HitBox03x1); }
if ( ED_HitBox_tot==3 ) { backend_set_config_int(ED_State_s, "HitBox03y1", ED_HitBox03y1); }
if ( ED_HitBox_tot==3 ) { backend_set_config_int(ED_State_s, "HitBox03x2", ED_HitBox03x2); }
if ( ED_HitBox_tot==3 ) { backend_set_config_int(ED_State_s, "HitBox03y2", ED_HitBox03y2); }
if ( ED_HitBox_tot==4 ) { backend_set_config_int(ED_State_s, "HitBox04x1", ED_HitBox04x1); }
if ( ED_HitBox_tot==4 ) { backend_set_config_int(ED_State_s, "HitBox04y1", ED_HitBox04y1); }
if ( ED_HitBox_tot==4 ) { backend_set_config_int(ED_State_s, "HitBox04x2", ED_HitBox04x2); }
if ( ED_HitBox_tot==4 ) { backend_set_config_int(ED_State_s, "HitBox04y2", ED_HitBox04y2); }
if ( ED_HitBox_tot==5 ) { backend_set_config_int(ED_State_s, "HitBox05x1", ED_HitBox05x1); }
if ( ED_HitBox_tot==5 ) { backend_set_config_int(ED_State_s, "HitBox05y1", ED_HitBox05y1); }
if ( ED_HitBox_tot==5 ) { backend_set_config_int(ED_State_s, "HitBox05x2", ED_HitBox05x2); }
if ( ED_HitBox_tot==5 ) { backend_set_config_int(ED_State_s, "HitBox05y2", ED_HitBox05y2); }
if ( ED_HitBox_tot==6 ) { backend_set_config_int(ED_State_s, "HitBox06x1", ED_HitBox06x1); }
if ( ED_HitBox_tot==6 ) { backend_set_config_int(ED_State_s, "HitBox06y1", ED_HitBox06y1); }
if ( ED_HitBox_tot==6 ) { backend_set_config_int(ED_State_s, "HitBox06x2", ED_HitBox06x2); }
if ( ED_HitBox_tot==6 ) { backend_set_config_int(ED_State_s, "HitBox06y2", ED_HitBox06y2); }
if ( ED_HitBox_tot==7 ) { backend_set_config_int(ED_State_s, "HitBox07x1", ED_HitBox07x1); }
if ( ED_HitBox_tot==7 ) { backend_set_config_int(ED_State_s, "HitBox07y1", ED_HitBox07y1); }
if ( ED_HitBox_tot==7 ) { backend_set_config_int(ED_State_s, "HitBox07x2", ED_HitBox07x2); }
if ( ED_HitBox_tot==7 ) { backend_set_config_int(ED_State_s, "HitBox07y2", ED_HitBox07y2); }
if ( ED_HitBox_tot==8 ) { backend_set_config_int(ED_State_s, "HitBox08x1", ED_HitBox08x1); }
if ( ED_HitBox_tot==8 ) { backend_set_config_int(ED_State_s, "HitBox08y1", ED_HitBox08y1); }
if ( ED_HitBox_tot==8 ) { backend_set_config_int(ED_State_s, "HitBox08x2", ED_HitBox08x2); }
if ( ED_HitBox_tot==8 ) { backend_set_config_int(ED_State_s, "HitBox08y2", ED_HitBox08y2); }
if ( ED_HitBox_tot==9 ) { backend_set_config_int(ED_State_s, "HitBox09x1", ED_HitBox09x1); }
if ( ED_HitBox_tot==9 ) { backend_set_config_int(ED_State_s, "HitBox09y1", ED_HitBox09y1); }
if ( ED_HitBox_tot==9 ) { backend_set_config_int(ED_State_s, "HitBox09x2", ED_HitBox09x2); }
if ( ED_HitBox_tot==9 ) { backend_set_config_int(ED_State_s, "HitBox09y2", ED_HitBox09y2); }
}

//5-Zera os controles de posicao do cursor MXs
ED_Mx1=-1; ED_My1=-1; ED_Mx2=-1; ED_My2=-1;
}

if (ED_DrawRedMode==1 || ED_DrawBlueMode==1)
{
//3-Desenha Caixas
if (ED_bt_Null==1)
{
if (ED_HurtBox01x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox01x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox01y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox01x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox01y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox02x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox02x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox02y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox02x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox02y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox03x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox03x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox03y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox03x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox03y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox04x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox04x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox04y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox04x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox04y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox05x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox05x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox05y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox05x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox05y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox06x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox06x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox06y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox06x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox06y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox07x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox07x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox07y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox07x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox07y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox08x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox08x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox08y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox08x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox08y2*2, backend_makecol(000,000,255)); }
if (ED_HurtBox09x1!=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox09x1*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox09y1*2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox09x2*2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox09y2*2, backend_makecol(000,000,255)); }
if (ED_HitBox01x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox01x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox01y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox01x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox01y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox02x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox02x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox02y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox02x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox02y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox03x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox03x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox03y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox03x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox03y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox04x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox04x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox04y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox04x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox04y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox05x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox05x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox05y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox05x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox05y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox06x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox06x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox06y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox06x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox06y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox07x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox07x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox07y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox07x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox07y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox08x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox08x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox08y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox08x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox08y2 *2, backend_makecol(255,000,000)); }
if (ED_HitBox09x1 !=-5555) { backend_rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox09x1 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox09y1 *2, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox09x2 *2, (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox09y2 *2, backend_makecol(255,000,000)); }
}

/*
				//debug do EDITOR
				//if (key_Mouse_L_status>0 && backend_mouse_x>170 && backend_mouse_y>40) { backend_textprintf_ex(bufferx, font_debug, 190, 50+ 0*15, backend_makecol(255,255,255), -1, "x1[%i] y1[%i] x2:%i y2:%i", ED_Mx1, ED_My1, backend_mouse_x, backend_mouse_y); }
				if (ED_DrawRedMode ==1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 0*10, backend_makecol(255,255,255), -1, "Modo de Desenho: HitBox"); }
				if (ED_DrawBlueMode==1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 0*10, backend_makecol(255,255,255), -1, "Modo de Desenho: HurtBox"); }
				{ backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 1*10, backend_makecol(255,255,255), -1, "HurtBox Total: %i", ED_HurtBox_tot); }
				{ backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 2*10, backend_makecol(255,255,255), -1, "HitBox Total: %i", ED_HitBox_tot);  }
				if (ED_HurtBox01x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 3*10, backend_makecol(255,255,255), -1, "HurtBox1: %i,%i,%i,%i", ED_HurtBox01x1, ED_HurtBox01y1, ED_HurtBox01x2, ED_HurtBox01y2); }
				if (ED_HurtBox02x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 4*10, backend_makecol(255,255,255), -1, "HurtBox2: %i,%i,%i,%i", ED_HurtBox02x1, ED_HurtBox02y1, ED_HurtBox02x2, ED_HurtBox02y2); }
				if (ED_HurtBox03x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 5*10, backend_makecol(255,255,255), -1, "HurtBox3: %i,%i,%i,%i", ED_HurtBox03x1, ED_HurtBox03y1, ED_HurtBox03x2, ED_HurtBox03y2); }
				if (ED_HurtBox04x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 6*10, backend_makecol(255,255,255), -1, "HurtBox4: %i,%i,%i,%i", ED_HurtBox04x1, ED_HurtBox04y1, ED_HurtBox04x2, ED_HurtBox04y2); }
				if (ED_HurtBox05x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 7*10, backend_makecol(255,255,255), -1, "HurtBox5: %i,%i,%i,%i", ED_HurtBox05x1, ED_HurtBox05y1, ED_HurtBox05x2, ED_HurtBox05y2); }
				if (ED_HurtBox06x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 8*10, backend_makecol(255,255,255), -1, "HurtBox6: %i,%i,%i,%i", ED_HurtBox06x1, ED_HurtBox06y1, ED_HurtBox06x2, ED_HurtBox06y2); }
				if (ED_HurtBox07x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 9*10, backend_makecol(255,255,255), -1, "HurtBox7: %i,%i,%i,%i", ED_HurtBox07x1, ED_HurtBox07y1, ED_HurtBox07x2, ED_HurtBox07y2); }
				if (ED_HurtBox08x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+10*10, backend_makecol(255,255,255), -1, "HurtBox8: %i,%i,%i,%i", ED_HurtBox08x1, ED_HurtBox08y1, ED_HurtBox08x2, ED_HurtBox08y2); }
				if (ED_HurtBox09x1!=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+11*10, backend_makecol(255,255,255), -1, "HurtBox9: %i,%i,%i,%i", ED_HurtBox09x1, ED_HurtBox09y1, ED_HurtBox09x2, ED_HurtBox09y2); }
				if (ED_HitBox01x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+12*10, backend_makecol(255,255,255), -1, "HitBox1.: %i,%i,%i,%i", ED_HitBox01x1, ED_HitBox01y1, ED_HitBox01x2, ED_HitBox01y2); }
				if (ED_HitBox02x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+13*10, backend_makecol(255,255,255), -1, "HitBox2.: %i,%i,%i,%i", ED_HitBox02x1, ED_HitBox02y1, ED_HitBox02x2, ED_HitBox02y2); }
				if (ED_HitBox03x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+14*10, backend_makecol(255,255,255), -1, "HitBox3.: %i,%i,%i,%i", ED_HitBox03x1, ED_HitBox03y1, ED_HitBox03x2, ED_HitBox03y2); }
				if (ED_HitBox04x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+15*10, backend_makecol(255,255,255), -1, "HitBox4.: %i,%i,%i,%i", ED_HitBox04x1, ED_HitBox04y1, ED_HitBox04x2, ED_HitBox04y2); }
				if (ED_HitBox05x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+16*10, backend_makecol(255,255,255), -1, "HitBox5.: %i,%i,%i,%i", ED_HitBox05x1, ED_HitBox05y1, ED_HitBox05x2, ED_HitBox05y2); }
				if (ED_HitBox06x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+17*10, backend_makecol(255,255,255), -1, "HitBox6.: %i,%i,%i,%i", ED_HitBox06x1, ED_HitBox06y1, ED_HitBox06x2, ED_HitBox06y2); }
				if (ED_HitBox07x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+18*10, backend_makecol(255,255,255), -1, "HitBox7.: %i,%i,%i,%i", ED_HitBox07x1, ED_HitBox07y1, ED_HitBox07x2, ED_HitBox07y2); }
				if (ED_HitBox08x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+19*10, backend_makecol(255,255,255), -1, "HitBox8.: %i,%i,%i,%i", ED_HitBox08x1, ED_HitBox08y1, ED_HitBox08x2, ED_HitBox08y2); }
				if (ED_HitBox09x1 !=-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+20*10, backend_makecol(255,255,255), -1, "HitBox9.: %i,%i,%i,%i", ED_HitBox09x1, ED_HitBox09y1, ED_HitBox09x2, ED_HitBox09y2); }
				if (ED_HurtBox01x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 3*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox02x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 4*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox03x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 5*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox04x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 6*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox05x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 7*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox06x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 8*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox07x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+ 9*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox08x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+10*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HurtBox09x1==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+11*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox01x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+12*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox02x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+13*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox03x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+14*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox04x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+15*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox05x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+16*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox06x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+17*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox07x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+18*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox08x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+19*10, backend_makecol(255,255,255), -1, "----"); }
				if (ED_HitBox09x1 ==-1) { backend_textprintf_right_ex(bufferx, font_10, 630, 50+20*10, backend_makecol(255,255,255), -1, "----"); }
			*/

//new EDIT_MODE
backend_textprintf_right_ex(bufferx, font_10,  56, 98, backend_makecol(255,255,255), -1, "%i", ED_HurtBox_tot);
backend_textprintf_right_ex(bufferx, font_10, 111, 98, backend_makecol(255,255,255), -1, "%i", ED_HitBox_tot);
}

if (ED_ShowMsgSaving==1) {
backend_draw_sprite(bufferx, save_file, 185, 460);
backend_textprintf_centre_ex(bufferx, font_debug, 425, 458, backend_makecol(255,255,255), -1, "Saving...");
}

backend_textprintf_centre_ex(bufferx, font_debug, 84, 150, backend_makecol(255,255,255), -1, "St [%i] Fr [%i/%i]", ED_State, ED_IndexAnim, ED_TotalFrames);

//escolha do personagem
backend_draw_sprite(bufferx, ED_Mini, 192, 5);
backend_rect(bufferx,172,    5, 172+15,   5+15, 0xffffff);
backend_rect(bufferx,172, 20+1, 172+15, 5+30+1, 0xffffff);
backend_rect(bufferx,228,    5, 228+15,   5+15, 0xffffff);
backend_rect(bufferx,228, 20+1, 228+15, 5+30+1, 0xffffff);

int deveinicializar=0;

// botao CharID--
if(key_Mouse_L_status==1 && backend_mouse_x>172 && backend_mouse_x<187 && backend_mouse_y>5 && backend_mouse_y<20){
ED_CharID--; if(ED_CharID<1) {ED_CharID=1;}
strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
deveinicializar=1;
}

// botao CharID++
if(key_Mouse_L_status==1 && backend_mouse_x>228 && backend_mouse_x<243 && backend_mouse_y>5 && backend_mouse_y<20){
ED_CharID++; if(ED_CharID>Qtde_Personagens_Instalados) {ED_CharID=Qtde_Personagens_Instalados;}
strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
deveinicializar=1;
}

// botao CharID=1
if(key_Mouse_L_status==1 && backend_mouse_x>172 && backend_mouse_x<187 && backend_mouse_y>21 && backend_mouse_y<36){
ED_CharID=1;
strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
deveinicializar=1;
}

// botao CharID=Qtde_Personagens_Instalados
if(key_Mouse_L_status==1 && backend_mouse_x>228 && backend_mouse_x<243 && backend_mouse_y>21 && backend_mouse_y<36){
ED_CharID=Qtde_Personagens_Instalados;
strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
deveinicializar=1;
}

//render type
backend_rect(bufferx, 260, 5, 260+15, 5+15, 0xffffff);
if(ED_Tipo==2) backend_rectfill(bufferx, 260, 5, 260+15, 5+15, 0x00ff00);
backend_textprintf_ex(bufferx, font_debug, 280,  5-2, backend_makecol(255,255,255), -1, "HD Sprite");
if(key_Mouse_L_status==1 && backend_mouse_x>260 && backend_mouse_x<275 && backend_mouse_y>5 && backend_mouse_y<20){
//	int a=1;
//	if(ED_Tipo==2 && a==1) { ED_Tipo=1; a=0; deveinicializar=1; }
//	if(ED_Tipo==1 && a==1) { ED_Tipo=2; a=0; deveinicializar=1; }
//	char ED_Caminho[99];
//	sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
//	backend_set_config_file(ED_Caminho);
//	if(ED_Tipo==1) backend_set_config_int("Info", "Type", 1);
//	if(ED_Tipo==2) backend_set_config_int("Info", "Type", 2);
}

backend_rect(bufferx, 260, 21, 260+15, 36, 0xffffff);
backend_textprintf_ex(bufferx, font_debug, 280,  20-2, backend_makecol(255,255,255), -1, "Onion Skin");

backend_rect(bufferx, 370, 5, 370+15, 20, 0xffffff);
backend_textprintf_ex(bufferx, font_debug, 390,  5-2, backend_makecol(255,255,255), -1, "Grid");
backend_rect(bufferx, 370, 21, 370+15, 36, 0xffffff);
backend_textprintf_ex(bufferx, font_debug, 390,  20-2, backend_makecol(255,255,255), -1, "Floor");

/*temporario*/ backend_draw_sprite(bufferx, spr_nao_implementado, 259, 0); /*temporario*/

//---deve inicializar---//
if(deveinicializar==1){
ED_inicializar();
char ED_Caminho[99];
sprintf(ED_Caminho, "data/chars/%s/000_01.pcx", P[1].Name);
ED_Mini = backend_load_bitmap(ED_Caminho, NULL);
if(!ED_Mini){ ED_Mini = backend_load_bitmap("data/system/000_01.pcx", NULL); }
}

backend_textprintf_ex(bufferx, font_debug, 13,  8-2, backend_makecol(000,000,000), -1, "HAMOOPI EDITOR");
backend_textprintf_ex(bufferx, font_debug, 10,  5-2, backend_makecol(255,255,000), -1, "HAMOOPI EDITOR");
backend_textprintf_ex(bufferx, font_debug, 13, 23-2, backend_makecol(0,0,0), -1, "%s", P[1].Name);
backend_textprintf_ex(bufferx, font_debug, 10, 20-2, backend_makecol(255,255,255), -1, "%s", P[1].Name);

//mouse
if(ED_MODE==1){
if(backend_mouse_x>175 && backend_mouse_y>45){
backend_draw_sprite(bufferx, mouse, backend_mouse_x-(backend_bitmap_width(mouse)/2), backend_mouse_y-(backend_bitmap_height(mouse)/2));
backend_circle(bufferx,backend_mouse_x, backend_mouse_y,12,0xffffff);
}else{
backend_draw_sprite(bufferx, mouse2, backend_mouse_x-(backend_bitmap_width(mouse)/2), backend_mouse_y-(backend_bitmap_height(mouse)/2));
}
}
if(ED_MODE==2){
backend_draw_sprite(bufferx, mouse2, backend_mouse_x-(backend_bitmap_width(mouse)/2), backend_mouse_y-(backend_bitmap_height(mouse)/2));
}

ED_io++; if (ED_io>3) { ED_io=0; } //usado para animacoes
}//fim if (EditMode==1)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FINALIZACOES ------------------------------------------------------------------------------------------------------------------------------ [**10] //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//efeito de Fade
if(FadeIN ==1){ FadeOUT=0; FadeCtr+=FadeVelocidade; if(FadeCtr>255){ FadeCtr=255; } }
if(FadeOUT==1){ FadeIN=0;  FadeCtr-=FadeVelocidade; if(FadeCtr<0  ){ FadeCtr=  0; } }
if(FadeCtr!=0){
backend_set_trans_blender(0, 0, 0, FadeCtr);
backend_drawing_mode(HM_DRAW_MODE_TRANS, 0, 0, 0);
int fx_w;
int fx_h;
fx_w=WindowResX;
fx_h=WindowResY;
if(fx_w==320) { fx_w=640; fx_h=480; }
backend_rectfill(bufferx, 0, 0, fx_w, fx_h, backend_makecol(0, 0, 0));
if(CtrlAnimTrans[16]==0){ backend_rectfill(LayerHUDa, 0, 0, fx_w, fx_h, backend_makecol(0, 0, 0)); }
backend_drawing_mode(HM_DRAW_MODE_SOLID, 0, 0, 0);
}

//efeito animação de Introducao (AnimIntro)
if(ApresentacaoMode==1){
if (AnimIntroTimer!=-1){
for (int ind=0;ind<16;ind++){
if(ind==floor(AnimIntroTimer)) {
if(CtrlAnimIntro[ind]==1){ backend_draw_sprite(bufferx, AnimIntro[ind], 0, 120);  }
}
}
}
if (AnimIntroTimer>=0) {
AnimIntroTimer+=0.35;
if(AnimIntroTimer>=16){
AnimIntroTimer=0;
}
}
}

//Efeito Animacao de Transicao (AnimTrans)
if (AnimTransTimer!=-1){
for (int ind=0;ind<=14;ind++){
if(ind==floor(AnimTransTimer)) {
if(CtrlAnimTrans[ind]==1){
backend_draw_sprite(bufferx, AnimTrans[ind], 0, 0); //bufferx, antes de entrar na tela de gameplay
}
}
}
}
if (AnimTransTimer!=-1){
for (int ind=14;ind<=29;ind++){
if(ind==floor(AnimTransTimer)) {
if(CtrlAnimTrans[ind]==1){
backend_draw_sprite(LayerHUDa, AnimTrans[ind], 0, 0); //LayerHUD, ja dentro de gameplay
}
}
}
}
if (AnimTransTimer>=0) {
AnimTransTimer+=0.25;
if(AnimTransTimer>=30){
AnimTransTimer=-1;
}
}

//////////////////////////////
//BLIT de BUFFERX em SCREEN!//
//////////////////////////////
if (GamePlayMode==0) { backend_stretch_blit(bufferx, backend_screen, 0, 0, 640, 480, 0, 0, backend_bitmap_width(backend_screen), backend_bitmap_height(backend_screen)); }
if (GamePlayMode==1) {
masked_backend_stretch_blit(LayerHUDa, LayerHUDb, 0, 0, backend_bitmap_width(LayerHUDa), backend_bitmap_height(LayerHUDa), 0, 0, backend_bitmap_width(LayerHUDb), backend_bitmap_height(LayerHUDb));
backend_stretch_blit(LayerHUDb, backend_screen, 0, 0, backend_bitmap_width(LayerHUDb), backend_bitmap_height(LayerHUDb), 0, 0, backend_bitmap_width(backend_screen), backend_bitmap_height(backend_screen)); //resolucao adaptativa
//backend_draw_sprite(backend_screen, LayerHUDb, 0, 0); //PS: desativado, resolucao fixa em 640x480, stretch_blit funciona melhor
}
//show_mouse(backend_screen);
while(timer==delay){}
backend_clear_bitmap(LayerHUD);
backend_clear_to_color(LayerHUD, backend_makecol(255, 0, 255));
backend_clear_to_color(LayerHUDa, backend_makecol(255, 0, 255));
backend_clear_to_color(LayerHUDb, backend_makecol(255, 0, 255));
backend_clear_bitmap(bufferx);

} //(while sair==0)

//limpa a memoria, destroi imagens e audios utilizados no jogo
backend_destroy_bitmap(donation);
for(int ind=0;ind<=500;ind++){
backend_destroy_bitmap(P[1].SprAtlas[ind]);
backend_destroy_bitmap(P[2].SprAtlas[ind]);
}
for(int ind=0;ind<10;ind++){ backend_destroy_bitmap(spr_num[ind]); }
for(int ind=0;ind<30;ind++){ backend_destroy_bitmap(AnimTrans[ind]); }
backend_destroy_bitmap(LayerHUD);
backend_destroy_bitmap(LayerHUDa);
backend_destroy_bitmap(LayerHUDb);
backend_destroy_bitmap(ed_mode1_on);
backend_destroy_bitmap(ed_mode2_on);
backend_destroy_bitmap(ed_mode1_off);
backend_destroy_bitmap(ed_mode2_off);
backend_destroy_bitmap(edit_prevchar);
backend_destroy_bitmap(edit_nextchar );
backend_destroy_bitmap(edit_firstchar);
backend_destroy_bitmap(edit_lastchar);
backend_destroy_bitmap(spr_nao_implementado);
backend_destroy_bitmap(bt_reset_input);
backend_destroy_bitmap(mouse);
backend_destroy_bitmap(mouse2);
backend_destroy_bitmap(spr_input_0);
backend_destroy_bitmap(spr_input_1);
backend_destroy_bitmap(spr_input_2);
backend_destroy_bitmap(spr_input_3);
backend_destroy_bitmap(spr_input_4);
backend_destroy_bitmap(spr_input_5);
backend_destroy_bitmap(spr_input_6);
backend_destroy_bitmap(spr_input_7);
backend_destroy_bitmap(spr_input_8);
backend_destroy_bitmap(spr_input_9);
backend_destroy_bitmap(spr_input_10);
backend_destroy_bitmap(spr_input_11);
backend_destroy_bitmap(spr_input_12);
backend_destroy_bitmap(spr_input_13);
backend_destroy_bitmap(spr_input_14);
backend_destroy_bitmap(spr_input_15);
backend_destroy_bitmap(spr_input_16);
backend_destroy_bitmap(spr_input_17);
backend_destroy_bitmap(bufferx); backend_destroy_bitmap(bt_joystick);
backend_destroy_bitmap(bt_up_1); backend_destroy_bitmap(bt_up_2); backend_destroy_bitmap(bt_up_3);
backend_destroy_bitmap(bt_down_1); backend_destroy_bitmap(bt_down_2); backend_destroy_bitmap(bt_down_3);
backend_destroy_bitmap(bt_left_1); backend_destroy_bitmap(bt_left_2); backend_destroy_bitmap(bt_left_3);
backend_destroy_bitmap(bt_right_1); backend_destroy_bitmap(bt_right_2); backend_destroy_bitmap(bt_right_3);
backend_destroy_bitmap(bt_1); backend_destroy_bitmap(bt_2); backend_destroy_bitmap(bt_3);
backend_destroy_bitmap(bt_ss_1); backend_destroy_bitmap(bt_ss_2); backend_destroy_bitmap(bt_ss_3);
backend_destroy_bitmap(P[1].Spr); backend_destroy_bitmap(P[2].Spr); backend_destroy_bitmap(ED_Spr);
backend_destroy_bitmap(Fireball[1].Spr); backend_destroy_bitmap(Fireball[2].Spr);
//backend_destroy_bitmap(P1_Spr_Aux); backend_destroy_bitmap(P2_Spr_Aux); backend_destroy_bitmap(ED_Spr_Aux); //desativado, pois sao destruidos durante o loop de jogo
backend_destroy_bitmap(P1_1); backend_destroy_bitmap(P2_1);
for(int ind=0;ind<MAX_CHARS;ind++){ backend_destroy_bitmap(MINIsprDisplay[ind]); }
for(int ind=0;ind<MAX_CHARS;ind++){ backend_destroy_bitmap(MINIsprDisplayArcadeMode[ind]); }
backend_destroy_bitmap(P1BIGDisplay); backend_destroy_bitmap(P2BIGDisplay); backend_destroy_bitmap(P2BIGDisplayInv);
backend_destroy_bitmap(spr_energy_bar);
backend_destroy_bitmap(spr_energy_bar_full);
backend_destroy_bitmap(P1_energy_flip);
backend_destroy_bitmap(P1_energy_red_flip);
backend_destroy_bitmap(char_generic);
backend_destroy_bitmap(char_generic2x);
backend_destroy_bitmap(spr_mold_results);
backend_destroy_bitmap(spr_result_perfect);
backend_destroy_bitmap(spr_result_win);
backend_destroy_bitmap(spr_splash_draw);
backend_destroy_bitmap(spr_splash_fight);
backend_destroy_bitmap(spr_splash_ko);
backend_destroy_bitmap(spr_splash_perfect);
backend_destroy_bitmap(spr_splash_round1);
backend_destroy_bitmap(spr_splash_round2);
backend_destroy_bitmap(spr_splash_round3);
backend_destroy_bitmap(spr_splash_round4);
backend_destroy_bitmap(spr_splash_round5);
backend_destroy_bitmap(spr_splash_youlose);
backend_destroy_bitmap(spr_splash_youwin);
backend_destroy_sample(round1);
backend_destroy_sample(round2);
backend_destroy_sample(round3);
backend_destroy_sample(fight);
backend_destroy_sample(ko);
backend_destroy_sample(perfect);
backend_destroy_sample(intro);
backend_destroy_sample(back);
backend_destroy_sample(choice);
backend_destroy_sample(confirm);
backend_destroy_sample(cursor);
backend_destroy_sample(attacklvl1);
backend_destroy_sample(attacklvl2);
backend_destroy_sample(attacklvl3);
backend_destroy_sample(hitlvl1);
backend_destroy_sample(hitlvl2);
backend_destroy_sample(hitlvl3);
backend_destroy_midi(bgm_apresentacao);
backend_destroy_midi(bgm_continue);
backend_destroy_midi(bgm_select_screen);
backend_destroy_midi(bgm_versus_mode);
backend_clear_keybuf();
return 0;
} //main()
END_OF_MAIN();
/* FIM DO PROGRAMA */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCOES ------------------------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CHECAR TECLAS ------------------------------------------------------------------------------------------------------------------------------[**11]
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check_keys_P1()
{
if (backend_mouse_b & 1) {
if (key_Mouse_L_pressed==1 && key_Mouse_L_hold==0) { key_Mouse_L_hold=1; key_Mouse_L_pressed=0; }
if (key_Mouse_L_pressed==0 && key_Mouse_L_hold==0) { key_Mouse_L_pressed=1; }}
if (!(backend_mouse_b & 1)) {
if (key_Mouse_L_released==1) { key_Mouse_L_released=0; key_Mouse_L_pressed=0; key_Mouse_L_hold=0; }
if (key_Mouse_L_pressed>0 || key_Mouse_L_hold>0) { key_Mouse_L_released=1; }}
if ( key_Mouse_L_pressed==0 && key_Mouse_L_hold==0 && key_Mouse_L_released==0 ) { key_Mouse_L_status=0; }
if ( key_Mouse_L_pressed==1  ) { key_Mouse_L_status=1; }
if ( key_Mouse_L_hold==1     ) { key_Mouse_L_status=2; }
if ( key_Mouse_L_released==1 ) { key_Mouse_L_status=3; }
if (backend_mouse_b & 2) {
if (key_Mouse_R_pressed==1 && key_Mouse_R_hold==0) { key_Mouse_R_hold=1; key_Mouse_R_pressed=0; }
if (key_Mouse_R_pressed==0 && key_Mouse_R_hold==0) { key_Mouse_R_pressed=1; }}
if (!(backend_mouse_b & 2)) {
if (key_Mouse_R_released==1) { key_Mouse_R_released=0; key_Mouse_R_pressed=0; key_Mouse_R_hold=0; }
if (key_Mouse_R_pressed>0 || key_Mouse_R_hold>0) { key_Mouse_R_released=1; }}
if ( key_Mouse_R_pressed==0 && key_Mouse_R_hold==0 && key_Mouse_R_released==0 ) { key_Mouse_R_status=0; }
if ( key_Mouse_R_pressed==1  ) { key_Mouse_R_status=1; }
if ( key_Mouse_R_hold==1     ) { key_Mouse_R_status=2; }
if ( key_Mouse_R_released==1 ) { key_Mouse_R_status=3; }
if (backend_key[HM_KEY_F1]) {
if (key_F1_pressed==1 && key_F1_hold==0) { key_F1_hold=1; key_F1_pressed=0; }
if (key_F1_pressed==0 && key_F1_hold==0) { key_F1_pressed=1; }}
if (!backend_key[HM_KEY_F1]) {
if (key_F1_released==1) { key_F1_released=0; key_F1_pressed=0; key_F1_hold=0; }
if (key_F1_pressed>0 || key_F1_hold>0) { key_F1_released=1; }}
if ( key_F1_pressed==0 && key_F1_hold==0 && key_F1_released==0 ) { key_F1_status=0; }
if ( key_F1_pressed==1  ) { key_F1_status=1; }
if ( key_F1_hold==1     ) { key_F1_status=2; }
if ( key_F1_released==1 ) { key_F1_status=3; }
if (backend_key[HM_KEY_F2]) {
if (key_F2_pressed==1 && key_F2_hold==0) { key_F2_hold=1; key_F2_pressed=0; }
if (key_F2_pressed==0 && key_F2_hold==0) { key_F2_pressed=1; }}
if (!backend_key[HM_KEY_F2]) {
if (key_F2_released==1) { key_F2_released=0; key_F2_pressed=0; key_F2_hold=0; }
if (key_F2_pressed>0 || key_F2_hold>0) { key_F2_released=1; }}
if ( key_F2_pressed==0 && key_F2_hold==0 && key_F2_released==0 ) { key_F2_status=0; }
if ( key_F2_pressed==1  ) { key_F2_status=1; }
if ( key_F2_hold==1     ) { key_F2_status=2; }
if ( key_F2_released==1 ) { key_F2_status=3; }
if (backend_key[HM_KEY_F3]) {
if (key_F3_pressed==1 && key_F3_hold==0) { key_F3_hold=1; key_F3_pressed=0; }
if (key_F3_pressed==0 && key_F3_hold==0) { key_F3_pressed=1; }}
if (!backend_key[HM_KEY_F3]) {
if (key_F3_released==1) { key_F3_released=0; key_F3_pressed=0; key_F3_hold=0; }
if (key_F3_pressed>0 || key_F3_hold>0) { key_F3_released=1; }}
if ( key_F3_pressed==0 && key_F3_hold==0 && key_F3_released==0 ) { key_F3_status=0; }
if ( key_F3_pressed==1  ) { key_F3_status=1; }
if ( key_F3_hold==1     ) { key_F3_status=2; }
if ( key_F3_released==1 ) { key_F3_status=3; }
if (backend_key[HM_KEY_F4]) {
if (key_F4_pressed==1 && key_F4_hold==0) { key_F4_hold=1; key_F4_pressed=0; }
if (key_F4_pressed==0 && key_F4_hold==0) { key_F4_pressed=1; }}
if (!backend_key[HM_KEY_F4]) {
if (key_F4_released==1) { key_F4_released=0; key_F4_pressed=0; key_F4_hold=0; }
if (key_F4_pressed>0 || key_F4_hold>0) { key_F4_released=1; }}
if ( key_F4_pressed==0 && key_F4_hold==0 && key_F4_released==0 ) { key_F4_status=0; }
if ( key_F4_pressed==1  ) { key_F4_status=1; }
if ( key_F4_hold==1     ) { key_F4_status=2; }
if ( key_F4_released==1 ) { key_F4_status=3; }
//WASD sao utilizados no editor
if (backend_key[HM_KEY_W]) {
if (P[1].key_W_pressed==1 && P[1].key_W_hold==0) { P[1].key_W_hold=1; P[1].key_W_pressed=0; }
if (P[1].key_W_pressed==0 && P[1].key_W_hold==0) { P[1].key_W_pressed=1; }}
if (!backend_key[HM_KEY_W]) {
if (P[1].key_W_released==1) { P[1].key_W_released=0; P[1].key_W_pressed=0; P[1].key_W_hold=0; }
if (P[1].key_W_pressed>0 || P[1].key_W_hold>0) { P[1].key_W_released=1; }}
if ( P[1].key_W_pressed==0 && P[1].key_W_hold==0 && P[1].key_W_released==0 ) { P[1].key_W_status=0; }
if ( P[1].key_W_pressed==1  ) { P[1].key_W_status=1; }
if ( P[1].key_W_hold==1     ) { P[1].key_W_status=2; }
if ( P[1].key_W_released==1 ) { P[1].key_W_status=3; }
if (backend_key[HM_KEY_S]) {
if (P[1].key_S_pressed==1 && P[1].key_S_hold==0) { P[1].key_S_hold=1; P[1].key_S_pressed=0; }
if (P[1].key_S_pressed==0 && P[1].key_S_hold==0) { P[1].key_S_pressed=1; }}
if (!backend_key[HM_KEY_S]) {
if (P[1].key_S_released==1) { P[1].key_S_released=0; P[1].key_S_pressed=0; P[1].key_S_hold=0; }
if (P[1].key_S_pressed>0 || P[1].key_S_hold>0) { P[1].key_S_released=1; }}
if ( P[1].key_S_pressed==0 && P[1].key_S_hold==0 && P[1].key_S_released==0 ) { P[1].key_S_status=0; }
if ( P[1].key_S_pressed==1  ) { P[1].key_S_status=1; }
if ( P[1].key_S_hold==1     ) { P[1].key_S_status=2; }
if ( P[1].key_S_released==1 ) { P[1].key_S_status=3; }
if (backend_key[HM_KEY_A]) {
if (P[1].key_A_pressed==1 && P[1].key_A_hold==0) { P[1].key_A_hold=1; P[1].key_A_pressed=0; }
if (P[1].key_A_pressed==0 && P[1].key_A_hold==0) { P[1].key_A_pressed=1; }}
if (!backend_key[HM_KEY_A]) {
if (P[1].key_A_released==1) { P[1].key_A_released=0; P[1].key_A_pressed=0; P[1].key_A_hold=0; }
if (P[1].key_A_pressed>0 || P[1].key_A_hold>0) { P[1].key_A_released=1; }}
if ( P[1].key_A_pressed==0 && P[1].key_A_hold==0 && P[1].key_A_released==0 ) { P[1].key_A_status=0; }
if ( P[1].key_A_pressed==1  ) { P[1].key_A_status=1; }
if ( P[1].key_A_hold==1     ) { P[1].key_A_status=2; }
if ( P[1].key_A_released==1 ) { P[1].key_A_status=3; }
if (backend_key[HM_KEY_D]) {
if (P[1].key_D_pressed==1 && P[1].key_D_hold==0) { P[1].key_D_hold=1; P[1].key_D_pressed=0; }
if (P[1].key_D_pressed==0 && P[1].key_D_hold==0) { P[1].key_D_pressed=1; }}
if (!backend_key[HM_KEY_D]) {
if (P[1].key_D_released==1) { P[1].key_D_released=0; P[1].key_D_pressed=0; P[1].key_D_hold=0; }
if (P[1].key_D_pressed>0 || P[1].key_D_hold>0) { P[1].key_D_released=1; }}
if ( P[1].key_D_pressed==0 && P[1].key_D_hold==0 && P[1].key_D_released==0 ) { P[1].key_D_status=0; }
if ( P[1].key_D_pressed==1  ) { P[1].key_D_status=1; }
if ( P[1].key_D_hold==1     ) { P[1].key_D_status=2; }
if ( P[1].key_D_released==1 ) { P[1].key_D_status=3; }

if(desabilita_players==0 && P[1].Pode_Mexer==1){
if (P1_UP) {
if (P[1].key_UP_pressed==1 && P[1].key_UP_hold==0) { P[1].key_UP_hold=1; P[1].key_UP_pressed=0; }
if (P[1].key_UP_pressed==0 && P[1].key_UP_hold==0) { P[1].key_UP_pressed=1; }}
if (!P1_UP) {
if (P[1].key_UP_released==1) { P[1].key_UP_released=0; P[1].key_UP_pressed=0; P[1].key_UP_hold=0; }
if (P[1].key_UP_pressed>0 || P[1].key_UP_hold>0) { P[1].key_UP_released=1; }}
if ( P[1].key_UP_pressed==0 && P[1].key_UP_hold==0 && P[1].key_UP_released==0 ) { P[1].key_UP_status=0; }
if ( P[1].key_UP_pressed==1  ) { P[1].key_UP_status=1; }
if ( P[1].key_UP_hold==1     ) { P[1].key_UP_status=2; }
if ( P[1].key_UP_released==1 ) { P[1].key_UP_status=3; }
if (P1_DOWN) {
if (P[1].key_DOWN_pressed==1 && P[1].key_DOWN_hold==0) { P[1].key_DOWN_hold=1; P[1].key_DOWN_pressed=0; }
if (P[1].key_DOWN_pressed==0 && P[1].key_DOWN_hold==0) { P[1].key_DOWN_pressed=1; }}
if (!P1_DOWN) {
if (P[1].key_DOWN_released==1) { P[1].key_DOWN_released=0; P[1].key_DOWN_pressed=0; P[1].key_DOWN_hold=0; }
if (P[1].key_DOWN_pressed>0 || P[1].key_DOWN_hold>0) { P[1].key_DOWN_released=1; }}
if ( P[1].key_DOWN_pressed==0 && P[1].key_DOWN_hold==0 && P[1].key_DOWN_released==0 ) { P[1].key_DOWN_status=0; }
if ( P[1].key_DOWN_pressed==1  ) { P[1].key_DOWN_status=1; }
if ( P[1].key_DOWN_hold==1     ) { P[1].key_DOWN_status=2; }
if ( P[1].key_DOWN_released==1 ) { P[1].key_DOWN_status=3; }
if (P1_LEFT) {
if (P[1].key_LEFT_pressed==1 && P[1].key_LEFT_hold==0) { P[1].key_LEFT_hold=1; P[1].key_LEFT_pressed=0; }
if (P[1].key_LEFT_pressed==0 && P[1].key_LEFT_hold==0) { P[1].key_LEFT_pressed=1; }}
if (!P1_LEFT) {
if (P[1].key_LEFT_released==1) { P[1].key_LEFT_released=0; P[1].key_LEFT_pressed=0; P[1].key_LEFT_hold=0; }
if (P[1].key_LEFT_pressed>0 || P[1].key_LEFT_hold>0) { P[1].key_LEFT_released=1; }}
if ( P[1].key_LEFT_pressed==0 && P[1].key_LEFT_hold==0 && P[1].key_LEFT_released==0 ) { P[1].key_LEFT_status=0; }
if ( P[1].key_LEFT_pressed==1  ) { P[1].key_LEFT_status=1; }
if ( P[1].key_LEFT_hold==1     ) { P[1].key_LEFT_status=2; }
if ( P[1].key_LEFT_released==1 ) { P[1].key_LEFT_status=3; }
if (P1_RIGHT) {
if (P[1].key_RIGHT_pressed==1 && P[1].key_RIGHT_hold==0) { P[1].key_RIGHT_hold=1; P[1].key_RIGHT_pressed=0; }
if (P[1].key_RIGHT_pressed==0 && P[1].key_RIGHT_hold==0) { P[1].key_RIGHT_pressed=1; }}
if (!P1_RIGHT) {
if (P[1].key_RIGHT_released==1) { P[1].key_RIGHT_released=0; P[1].key_RIGHT_pressed=0; P[1].key_RIGHT_hold=0; }
if (P[1].key_RIGHT_pressed>0 || P[1].key_RIGHT_hold>0) { P[1].key_RIGHT_released=1; }}
if ( P[1].key_RIGHT_pressed==0 && P[1].key_RIGHT_hold==0 && P[1].key_RIGHT_released==0 ) { P[1].key_RIGHT_status=0; }
if ( P[1].key_RIGHT_pressed==1  ) { P[1].key_RIGHT_status=1; }
if ( P[1].key_RIGHT_hold==1     ) { P[1].key_RIGHT_status=2; }
if ( P[1].key_RIGHT_released==1 ) { P[1].key_RIGHT_status=3; }
if (P1_BT1) {
if (P[1].key_BT1_pressed==1 && P[1].key_BT1_hold==0) { P[1].key_BT1_hold=1; P[1].key_BT1_pressed=0; }
if (P[1].key_BT1_pressed==0 && P[1].key_BT1_hold==0) { P[1].key_BT1_pressed=1; }}
if (!P1_BT1) {
if (P[1].key_BT1_released==1) { P[1].key_BT1_released=0; P[1].key_BT1_pressed=0; P[1].key_BT1_hold=0; }
if (P[1].key_BT1_pressed>0 || P[1].key_BT1_hold>0) { P[1].key_BT1_released=1; }}
if ( P[1].key_BT1_pressed==0 && P[1].key_BT1_hold==0 && P[1].key_BT1_released==0 ) { P[1].key_BT1_status=0; }
if ( P[1].key_BT1_pressed==1  ) { P[1].key_BT1_status=1; }
if ( P[1].key_BT1_hold==1     ) { P[1].key_BT1_status=2; }
if ( P[1].key_BT1_released==1 ) { P[1].key_BT1_status=3; }
if (P1_BT2) {
if (P[1].key_BT2_pressed==1 && P[1].key_BT2_hold==0) { P[1].key_BT2_hold=1; P[1].key_BT2_pressed=0; }
if (P[1].key_BT2_pressed==0 && P[1].key_BT2_hold==0) { P[1].key_BT2_pressed=1; }}
if (!P1_BT2) {
if (P[1].key_BT2_released==1) { P[1].key_BT2_released=0; P[1].key_BT2_pressed=0; P[1].key_BT2_hold=0; }
if (P[1].key_BT2_pressed>0 || P[1].key_BT2_hold>0) { P[1].key_BT2_released=1; }}
if ( P[1].key_BT2_pressed==0 && P[1].key_BT2_hold==0 && P[1].key_BT2_released==0 ) { P[1].key_BT2_status=0; }
if ( P[1].key_BT2_pressed==1  ) { P[1].key_BT2_status=1; }
if ( P[1].key_BT2_hold==1     ) { P[1].key_BT2_status=2; }
if ( P[1].key_BT2_released==1 ) { P[1].key_BT2_status=3; }
if (P1_BT3) {
if (P[1].key_BT3_pressed==1 && P[1].key_BT3_hold==0) { P[1].key_BT3_hold=1; P[1].key_BT3_pressed=0; }
if (P[1].key_BT3_pressed==0 && P[1].key_BT3_hold==0) { P[1].key_BT3_pressed=1; }}
if (!P1_BT3) {
if (P[1].key_BT3_released==1) { P[1].key_BT3_released=0; P[1].key_BT3_pressed=0; P[1].key_BT3_hold=0; }
if (P[1].key_BT3_pressed>0 || P[1].key_BT3_hold>0) { P[1].key_BT3_released=1; }}
if ( P[1].key_BT3_pressed==0 && P[1].key_BT3_hold==0 && P[1].key_BT3_released==0 ) { P[1].key_BT3_status=0; }
if ( P[1].key_BT3_pressed==1  ) { P[1].key_BT3_status=1; }
if ( P[1].key_BT3_hold==1     ) { P[1].key_BT3_status=2; }
if ( P[1].key_BT3_released==1 ) { P[1].key_BT3_status=3; }
if (P1_BT4) {
if (P[1].key_BT4_pressed==1 && P[1].key_BT4_hold==0) { P[1].key_BT4_hold=1; P[1].key_BT4_pressed=0; }
if (P[1].key_BT4_pressed==0 && P[1].key_BT4_hold==0) { P[1].key_BT4_pressed=1; }}
if (!P1_BT4) {
if (P[1].key_BT4_released==1) { P[1].key_BT4_released=0; P[1].key_BT4_pressed=0; P[1].key_BT4_hold=0; }
if (P[1].key_BT4_pressed>0 || P[1].key_BT4_hold>0) { P[1].key_BT4_released=1; }}
if ( P[1].key_BT4_pressed==0 && P[1].key_BT4_hold==0 && P[1].key_BT4_released==0 ) { P[1].key_BT4_status=0; }
if ( P[1].key_BT4_pressed==1  ) { P[1].key_BT4_status=1; }
if ( P[1].key_BT4_hold==1     ) { P[1].key_BT4_status=2; }
if ( P[1].key_BT4_released==1 ) { P[1].key_BT4_status=3; }
if (P1_BT5) {
if (P[1].key_BT5_pressed==1 && P[1].key_BT5_hold==0) { P[1].key_BT5_hold=1; P[1].key_BT5_pressed=0; }
if (P[1].key_BT5_pressed==0 && P[1].key_BT5_hold==0) { P[1].key_BT5_pressed=1; }}
if (!P1_BT5) {
if (P[1].key_BT5_released==1) { P[1].key_BT5_released=0; P[1].key_BT5_pressed=0; P[1].key_BT5_hold=0; }
if (P[1].key_BT5_pressed>0 || P[1].key_BT5_hold>0) { P[1].key_BT5_released=1; }}
if ( P[1].key_BT5_pressed==0 && P[1].key_BT5_hold==0 && P[1].key_BT5_released==0 ) { P[1].key_BT5_status=0; }
if ( P[1].key_BT5_pressed==1  ) { P[1].key_BT5_status=1; }
if ( P[1].key_BT5_hold==1     ) { P[1].key_BT5_status=2; }
if ( P[1].key_BT5_released==1 ) { P[1].key_BT5_status=3; }
if (P1_BT6) {
if (P[1].key_BT6_pressed==1 && P[1].key_BT6_hold==0) { P[1].key_BT6_hold=1; P[1].key_BT6_pressed=0; }
if (P[1].key_BT6_pressed==0 && P[1].key_BT6_hold==0) { P[1].key_BT6_pressed=1; }}
if (!P1_BT6) {
if (P[1].key_BT6_released==1) { P[1].key_BT6_released=0; P[1].key_BT6_pressed=0; P[1].key_BT6_hold=0; }
if (P[1].key_BT6_pressed>0 || P[1].key_BT6_hold>0) { P[1].key_BT6_released=1; }}
if ( P[1].key_BT6_pressed==0 && P[1].key_BT6_hold==0 && P[1].key_BT6_released==0 ) { P[1].key_BT6_status=0; }
if ( P[1].key_BT6_pressed==1  ) { P[1].key_BT6_status=1; }
if ( P[1].key_BT6_hold==1     ) { P[1].key_BT6_status=2; }
if ( P[1].key_BT6_released==1 ) { P[1].key_BT6_status=3; }
if (P1_SELECT) {
if (P[1].key_SELECT_pressed==1 && P[1].key_SELECT_hold==0) { P[1].key_SELECT_hold=1; P[1].key_SELECT_pressed=0; }
if (P[1].key_SELECT_pressed==0 && P[1].key_SELECT_hold==0) { P[1].key_SELECT_pressed=1; }}
if (!P1_SELECT) {
if (P[1].key_SELECT_released==1) { P[1].key_SELECT_released=0; P[1].key_SELECT_pressed=0; P[1].key_SELECT_hold=0; }
if (P[1].key_SELECT_pressed>0 || P[1].key_SELECT_hold>0) { P[1].key_SELECT_released=1; }}
if ( P[1].key_SELECT_pressed==0 && P[1].key_SELECT_hold==0 && P[1].key_SELECT_released==0 ) { P[1].key_SELECT_status=0; }
if ( P[1].key_SELECT_pressed==1  ) { P[1].key_SELECT_status=1; }
if ( P[1].key_SELECT_hold==1     ) { P[1].key_SELECT_status=2; }
if ( P[1].key_SELECT_released==1 ) { P[1].key_SELECT_status=3; }
if (P1_START) {
if (P[1].key_START_pressed==1 && P[1].key_START_hold==0) { P[1].key_START_hold=1; P[1].key_START_pressed=0; }
if (P[1].key_START_pressed==0 && P[1].key_START_hold==0) { P[1].key_START_pressed=1; }}
if (!P1_START) {
if (P[1].key_START_released==1) { P[1].key_START_released=0; P[1].key_START_pressed=0; P[1].key_START_hold=0; }
if (P[1].key_START_pressed>0 || P[1].key_START_hold>0) { P[1].key_START_released=1; }}
if ( P[1].key_START_pressed==0 && P[1].key_START_hold==0 && P[1].key_START_released==0 ) { P[1].key_START_status=0; }
if ( P[1].key_START_pressed==1  ) { P[1].key_START_status=1; }
if ( P[1].key_START_hold==1     ) { P[1].key_START_status=2; }
if ( P[1].key_START_released==1 ) { P[1].key_START_status=3; }

/*ABASTECE SLOTS*/
if (P[1].key_UP_status==1 || P[1].key_DOWN_status==1 || P[1].key_LEFT_status==1 || P[1].key_RIGHT_status==1
|| P[1].key_BT1_status==1 || P[1].key_BT2_status==1 || P[1].key_BT3_status==1
|| P[1].key_BT4_status==1 || P[1].key_BT5_status==1 || P[1].key_BT6_status==1
|| P[1].key_SELECT_status==1 || P[1].key_START_status==1)
{
char StrBotoes[8]="";
int a=0; int b=0; int c=0; int d=0;
int e=0; int f=0; int g=0; int h=0;
MovSlots_P1();
if (P[1].key_UP_status     ==1 && P[1].key_LEFT_status==0 && P[1].key_RIGHT_status==0) { P[1].slot[1]= 8; }
if (P[1].key_DOWN_status   ==1 && P[1].key_LEFT_status==0 && P[1].key_RIGHT_status==0) { P[1].slot[1]= 2; }
if (P[1].key_LEFT_status   ==1 && P[1].key_DOWN_status==0 && P[1].key_UP_status   ==0) { P[1].slot[1]= 4; }
if (P[1].key_RIGHT_status  ==1 && P[1].key_DOWN_status==0 && P[1].key_UP_status   ==0) { P[1].slot[1]= 6; }
if (P[1].key_BT1_status    ==1) { P[1].bt_slot[1]=1; a=1; }
if (P[1].key_BT2_status    ==1) { P[1].bt_slot[1]=2; b=1; }
if (P[1].key_BT3_status    ==1) { P[1].bt_slot[1]=3; c=1; }
if (P[1].key_BT4_status    ==1) { P[1].bt_slot[1]=4; d=1; }
if (P[1].key_BT5_status    ==1) { P[1].bt_slot[1]=5; e=1; }
if (P[1].key_BT6_status    ==1) { P[1].bt_slot[1]=6; f=1; }
if (P[1].key_SELECT_status ==1) { P[1].bt_slot[1]=7; g=1; }
if (P[1].key_START_status  ==1) { P[1].bt_slot[1]=8; h=1; }
if (P[1].key_BT1_status==1 || P[1].key_BT2_status==1 || P[1].key_BT3_status==1 || P[1].key_BT4_status==1
|| P[1].key_BT5_status==1 || P[1].key_BT6_status==1 || P[1].key_SELECT_status==1 || P[1].key_START_status==1)
{
if (a==1) { strcat(StrBotoes, "1"); } P[1].bt_slot[1] = atoi(StrBotoes);
if (b==1) { strcat(StrBotoes, "2"); } P[1].bt_slot[1] = atoi(StrBotoes);
if (c==1) { strcat(StrBotoes, "3"); } P[1].bt_slot[1] = atoi(StrBotoes);
if (d==1) { strcat(StrBotoes, "4"); } P[1].bt_slot[1] = atoi(StrBotoes);
if (e==1) { strcat(StrBotoes, "5"); } P[1].bt_slot[1] = atoi(StrBotoes);
if (f==1) { strcat(StrBotoes, "6"); } P[1].bt_slot[1] = atoi(StrBotoes);
if (g==1) { strcat(StrBotoes, "7"); } P[1].bt_slot[1] = atoi(StrBotoes);
if (h==1) { strcat(StrBotoes, "8"); } P[1].bt_slot[1] = atoi(StrBotoes);
}
if (P[1].key_LEFT_status  ==1 && P[1].key_UP_status    ==1) { P[1].slot[1]=7; }
if (P[1].key_UP_status    ==1 && P[1].key_RIGHT_status ==1) { P[1].slot[1]=9; }
if (P[1].key_RIGHT_status ==1 && P[1].key_DOWN_status  ==1) { P[1].slot[1]=3; }
if (P[1].key_DOWN_status  ==1 && P[1].key_LEFT_status  ==1) { P[1].slot[1]=1; }
if (P[1].key_DOWN_status   >1 && P[1].key_RIGHT_status ==1) { P[1].slot[1]=3; }
if (P[1].key_RIGHT_status  >1 && P[1].key_DOWN_status  ==1) { P[1].slot[1]=3; }
if (P[1].key_DOWN_status   >1 && P[1].key_LEFT_status  ==1) { P[1].slot[1]=1; }
if (P[1].key_LEFT_status   >1 && P[1].key_DOWN_status  ==1) { P[1].slot[1]=1; }
if (P[1].key_UP_status     >1 && P[1].key_RIGHT_status ==1) { P[1].slot[1]=9; }
if (P[1].key_RIGHT_status  >1 && P[1].key_UP_status    ==1) { P[1].slot[1]=9; }
if (P[1].key_UP_status     >1 && P[1].key_LEFT_status  ==1) { P[1].slot[1]=7; }
if (P[1].key_LEFT_status   >1 && P[1].key_UP_status    ==1) { P[1].slot[1]=7; }
P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0;
}
if (P[1].key_DOWN_status  ==3 && P[1].key_RIGHT_status>1) { MovSlots_P1(); P[1].slot[1]=6; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].key_DOWN_status  ==3 && P[1].key_LEFT_status >1) { MovSlots_P1(); P[1].slot[1]=4; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].key_RIGHT_status ==3 && P[1].key_DOWN_status >1) { MovSlots_P1(); P[1].slot[1]=2; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].key_LEFT_status  ==3 && P[1].key_DOWN_status >1) { MovSlots_P1(); P[1].slot[1]=2; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].key_UP_status    ==3 && P[1].key_RIGHT_status>1) { MovSlots_P1(); P[1].slot[1]=6; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].key_UP_status    ==3 && P[1].key_LEFT_status >1) { MovSlots_P1(); P[1].slot[1]=4; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].key_RIGHT_status ==3 && P[1].key_UP_status   >1) { MovSlots_P1(); P[1].slot[1]=8; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].key_LEFT_status  ==3 && P[1].key_UP_status   >1) { MovSlots_P1(); P[1].slot[1]=8; P[1].t_slot[1]=P[1].ticks_4slot; P[1].ticks_4slot=0; }
if (P[1].t_slot[1]>999) { P[1].t_slot[1]=999; }
}
}

void check_keys_P2()
{
if(desabilita_players==0 && P[2].Pode_Mexer==1){
if (P2_UP) {
if (P[2].key_UP_pressed==1 && P[2].key_UP_hold==0) { P[2].key_UP_hold=1; P[2].key_UP_pressed=0; }
if (P[2].key_UP_pressed==0 && P[2].key_UP_hold==0) { P[2].key_UP_pressed=1; }}
if (!P2_UP) {
if (P[2].key_UP_released==1) { P[2].key_UP_released=0; P[2].key_UP_pressed=0; P[2].key_UP_hold=0; }
if (P[2].key_UP_pressed>0 || P[2].key_UP_hold>0) { P[2].key_UP_released=1; }}
if ( P[2].key_UP_pressed==0 && P[2].key_UP_hold==0 && P[2].key_UP_released==0 ) { P[2].key_UP_status=0; }
if ( P[2].key_UP_pressed==1  ) { P[2].key_UP_status=1; }
if ( P[2].key_UP_hold==1     ) { P[2].key_UP_status=2; }
if ( P[2].key_UP_released==1 ) { P[2].key_UP_status=3; }
if (P2_DOWN) {
if (P[2].key_DOWN_pressed==1 && P[2].key_DOWN_hold==0) { P[2].key_DOWN_hold=1; P[2].key_DOWN_pressed=0; }
if (P[2].key_DOWN_pressed==0 && P[2].key_DOWN_hold==0) { P[2].key_DOWN_pressed=1; }}
if (!P2_DOWN) {
if (P[2].key_DOWN_released==1) { P[2].key_DOWN_released=0; P[2].key_DOWN_pressed=0; P[2].key_DOWN_hold=0; }
if (P[2].key_DOWN_pressed>0 || P[2].key_DOWN_hold>0) { P[2].key_DOWN_released=1; }}
if ( P[2].key_DOWN_pressed==0 && P[2].key_DOWN_hold==0 && P[2].key_DOWN_released==0 ) { P[2].key_DOWN_status=0; }
if ( P[2].key_DOWN_pressed==1  ) { P[2].key_DOWN_status=1; }
if ( P[2].key_DOWN_hold==1     ) { P[2].key_DOWN_status=2; }
if ( P[2].key_DOWN_released==1 ) { P[2].key_DOWN_status=3; }
if (P2_LEFT) {
if (P[2].key_LEFT_pressed==1 && P[2].key_LEFT_hold==0) { P[2].key_LEFT_hold=1; P[2].key_LEFT_pressed=0; }
if (P[2].key_LEFT_pressed==0 && P[2].key_LEFT_hold==0) { P[2].key_LEFT_pressed=1; }}
if (!P2_LEFT) {
if (P[2].key_LEFT_released==1) { P[2].key_LEFT_released=0; P[2].key_LEFT_pressed=0; P[2].key_LEFT_hold=0; }
if (P[2].key_LEFT_pressed>0 || P[2].key_LEFT_hold>0) { P[2].key_LEFT_released=1; }}
if ( P[2].key_LEFT_pressed==0 && P[2].key_LEFT_hold==0 && P[2].key_LEFT_released==0 ) { P[2].key_LEFT_status=0; }
if ( P[2].key_LEFT_pressed==1  ) { P[2].key_LEFT_status=1; }
if ( P[2].key_LEFT_hold==1     ) { P[2].key_LEFT_status=2; }
if ( P[2].key_LEFT_released==1 ) { P[2].key_LEFT_status=3; }
if (P2_RIGHT) {
if (P[2].key_RIGHT_pressed==1 && P[2].key_RIGHT_hold==0) { P[2].key_RIGHT_hold=1; P[2].key_RIGHT_pressed=0; }
if (P[2].key_RIGHT_pressed==0 && P[2].key_RIGHT_hold==0) { P[2].key_RIGHT_pressed=1; }}
if (!P2_RIGHT) {
if (P[2].key_RIGHT_released==1) { P[2].key_RIGHT_released=0; P[2].key_RIGHT_pressed=0; P[2].key_RIGHT_hold=0; }
if (P[2].key_RIGHT_pressed>0 || P[2].key_RIGHT_hold>0) { P[2].key_RIGHT_released=1; }}
if ( P[2].key_RIGHT_pressed==0 && P[2].key_RIGHT_hold==0 && P[2].key_RIGHT_released==0 ) { P[2].key_RIGHT_status=0; }
if ( P[2].key_RIGHT_pressed==1  ) { P[2].key_RIGHT_status=1; }
if ( P[2].key_RIGHT_hold==1     ) { P[2].key_RIGHT_status=2; }
if ( P[2].key_RIGHT_released==1 ) { P[2].key_RIGHT_status=3; }
if (P2_BT1) {
if (P[2].key_BT1_pressed==1 && P[2].key_BT1_hold==0) { P[2].key_BT1_hold=1; P[2].key_BT1_pressed=0; }
if (P[2].key_BT1_pressed==0 && P[2].key_BT1_hold==0) { P[2].key_BT1_pressed=1; }}
if (!P2_BT1) {
if (P[2].key_BT1_released==1) { P[2].key_BT1_released=0; P[2].key_BT1_pressed=0; P[2].key_BT1_hold=0; }
if (P[2].key_BT1_pressed>0 || P[2].key_BT1_hold>0) { P[2].key_BT1_released=1; }}
if ( P[2].key_BT1_pressed==0 && P[2].key_BT1_hold==0 && P[2].key_BT1_released==0 ) { P[2].key_BT1_status=0; }
if ( P[2].key_BT1_pressed==1  ) { P[2].key_BT1_status=1; }
if ( P[2].key_BT1_hold==1     ) { P[2].key_BT1_status=2; }
if ( P[2].key_BT1_released==1 ) { P[2].key_BT1_status=3; }
if (P2_BT2) {
if (P[2].key_BT2_pressed==1 && P[2].key_BT2_hold==0) { P[2].key_BT2_hold=1; P[2].key_BT2_pressed=0; }
if (P[2].key_BT2_pressed==0 && P[2].key_BT2_hold==0) { P[2].key_BT2_pressed=1; }}
if (!P2_BT2) {
if (P[2].key_BT2_released==1) { P[2].key_BT2_released=0; P[2].key_BT2_pressed=0; P[2].key_BT2_hold=0; }
if (P[2].key_BT2_pressed>0 || P[2].key_BT2_hold>0) { P[2].key_BT2_released=1; }}
if ( P[2].key_BT2_pressed==0 && P[2].key_BT2_hold==0 && P[2].key_BT2_released==0 ) { P[2].key_BT2_status=0; }
if ( P[2].key_BT2_pressed==1  ) { P[2].key_BT2_status=1; }
if ( P[2].key_BT2_hold==1     ) { P[2].key_BT2_status=2; }
if ( P[2].key_BT2_released==1 ) { P[2].key_BT2_status=3; }
if (P2_BT3) {
if (P[2].key_BT3_pressed==1 && P[2].key_BT3_hold==0) { P[2].key_BT3_hold=1; P[2].key_BT3_pressed=0; }
if (P[2].key_BT3_pressed==0 && P[2].key_BT3_hold==0) { P[2].key_BT3_pressed=1; }}
if (!P2_BT3) {
if (P[2].key_BT3_released==1) { P[2].key_BT3_released=0; P[2].key_BT3_pressed=0; P[2].key_BT3_hold=0; }
if (P[2].key_BT3_pressed>0 || P[2].key_BT3_hold>0) { P[2].key_BT3_released=1; }}
if ( P[2].key_BT3_pressed==0 && P[2].key_BT3_hold==0 && P[2].key_BT3_released==0 ) { P[2].key_BT3_status=0; }
if ( P[2].key_BT3_pressed==1  ) { P[2].key_BT3_status=1; }
if ( P[2].key_BT3_hold==1     ) { P[2].key_BT3_status=2; }
if ( P[2].key_BT3_released==1 ) { P[2].key_BT3_status=3; }
if (P2_BT4) {
if (P[2].key_BT4_pressed==1 && P[2].key_BT4_hold==0) { P[2].key_BT4_hold=1; P[2].key_BT4_pressed=0; }
if (P[2].key_BT4_pressed==0 && P[2].key_BT4_hold==0) { P[2].key_BT4_pressed=1; }}
if (!P2_BT4) {
if (P[2].key_BT4_released==1) { P[2].key_BT4_released=0; P[2].key_BT4_pressed=0; P[2].key_BT4_hold=0; }
if (P[2].key_BT4_pressed>0 || P[2].key_BT4_hold>0) { P[2].key_BT4_released=1; }}
if ( P[2].key_BT4_pressed==0 && P[2].key_BT4_hold==0 && P[2].key_BT4_released==0 ) { P[2].key_BT4_status=0; }
if ( P[2].key_BT4_pressed==1  ) { P[2].key_BT4_status=1; }
if ( P[2].key_BT4_hold==1     ) { P[2].key_BT4_status=2; }
if ( P[2].key_BT4_released==1 ) { P[2].key_BT4_status=3; }
if (P2_BT5) {
if (P[2].key_BT5_pressed==1 && P[2].key_BT5_hold==0) { P[2].key_BT5_hold=1; P[2].key_BT5_pressed=0; }
if (P[2].key_BT5_pressed==0 && P[2].key_BT5_hold==0) { P[2].key_BT5_pressed=1; }}
if (!P2_BT5) {
if (P[2].key_BT5_released==1) { P[2].key_BT5_released=0; P[2].key_BT5_pressed=0; P[2].key_BT5_hold=0; }
if (P[2].key_BT5_pressed>0 || P[2].key_BT5_hold>0) { P[2].key_BT5_released=1; }}
if ( P[2].key_BT5_pressed==0 && P[2].key_BT5_hold==0 && P[2].key_BT5_released==0 ) { P[2].key_BT5_status=0; }
if ( P[2].key_BT5_pressed==1  ) { P[2].key_BT5_status=1; }
if ( P[2].key_BT5_hold==1     ) { P[2].key_BT5_status=2; }
if ( P[2].key_BT5_released==1 ) { P[2].key_BT5_status=3; }
if (P2_BT6) {
if (P[2].key_BT6_pressed==1 && P[2].key_BT6_hold==0) { P[2].key_BT6_hold=1; P[2].key_BT6_pressed=0; }
if (P[2].key_BT6_pressed==0 && P[2].key_BT6_hold==0) { P[2].key_BT6_pressed=1; }}
if (!P2_BT6) {
if (P[2].key_BT6_released==1) { P[2].key_BT6_released=0; P[2].key_BT6_pressed=0; P[2].key_BT6_hold=0; }
if (P[2].key_BT6_pressed>0 || P[2].key_BT6_hold>0) { P[2].key_BT6_released=1; }}
if ( P[2].key_BT6_pressed==0 && P[2].key_BT6_hold==0 && P[2].key_BT6_released==0 ) { P[2].key_BT6_status=0; }
if ( P[2].key_BT6_pressed==1  ) { P[2].key_BT6_status=1; }
if ( P[2].key_BT6_hold==1     ) { P[2].key_BT6_status=2; }
if ( P[2].key_BT6_released==1 ) { P[2].key_BT6_status=3; }
if (P2_SELECT) {
if (P[2].key_SELECT_pressed==1 && P[2].key_SELECT_hold==0) { P[2].key_SELECT_hold=1; P[2].key_SELECT_pressed=0; }
if (P[2].key_SELECT_pressed==0 && P[2].key_SELECT_hold==0) { P[2].key_SELECT_pressed=1; }}
if (!P2_SELECT) {
if (P[2].key_SELECT_released==1) { P[2].key_SELECT_released=0; P[2].key_SELECT_pressed=0; P[2].key_SELECT_hold=0; }
if (P[2].key_SELECT_pressed>0 || P[2].key_SELECT_hold>0) { P[2].key_SELECT_released=1; }}
if ( P[2].key_SELECT_pressed==0 && P[2].key_SELECT_hold==0 && P[2].key_SELECT_released==0 ) { P[2].key_SELECT_status=0; }
if ( P[2].key_SELECT_pressed==1  ) { P[2].key_SELECT_status=1; }
if ( P[2].key_SELECT_hold==1     ) { P[2].key_SELECT_status=2; }
if ( P[2].key_SELECT_released==1 ) { P[2].key_SELECT_status=3; }
if (P2_START) {
if (P[2].key_START_pressed==1 && P[2].key_START_hold==0) { P[2].key_START_hold=1; P[2].key_START_pressed=0; }
if (P[2].key_START_pressed==0 && P[2].key_START_hold==0) { P[2].key_START_pressed=1; }}
if (!P2_START) {
if (P[2].key_START_released==1) { P[2].key_START_released=0; P[2].key_START_pressed=0; P[2].key_START_hold=0; }
if (P[2].key_START_pressed>0 || P[2].key_START_hold>0) { P[2].key_START_released=1; }}
if ( P[2].key_START_pressed==0 && P[2].key_START_hold==0 && P[2].key_START_released==0 ) { P[2].key_START_status=0; }
if ( P[2].key_START_pressed==1  ) { P[2].key_START_status=1; }
if ( P[2].key_START_hold==1     ) { P[2].key_START_status=2; }
if ( P[2].key_START_released==1 ) { P[2].key_START_status=3; }

/*ABASTECE SLOTS*/
if (P[2].key_UP_status==1 || P[2].key_DOWN_status==1 || P[2].key_LEFT_status==1 || P[2].key_RIGHT_status==1
|| P[2].key_BT1_status==1 || P[2].key_BT2_status==1 || P[2].key_BT3_status==1
|| P[2].key_BT4_status==1 || P[2].key_BT5_status==1 || P[2].key_BT6_status==1
|| P[2].key_SELECT_status==1 || P[2].key_START_status==1)
{
char StrBotoes[8]="";
int a=0; int b=0; int c=0; int d=0;
int e=0; int f=0; int g=0; int h=0;
MovSlots_P2();
if (P[2].key_UP_status     ==1 && P[2].key_LEFT_status==0 && P[2].key_RIGHT_status==0) { P[2].slot[1]= 8; }
if (P[2].key_DOWN_status   ==1 && P[2].key_LEFT_status==0 && P[2].key_RIGHT_status==0) { P[2].slot[1]= 2; }
if (P[2].key_LEFT_status   ==1 && P[2].key_DOWN_status==0 && P[2].key_UP_status   ==0) { P[2].slot[1]= 4; }
if (P[2].key_RIGHT_status  ==1 && P[2].key_DOWN_status==0 && P[2].key_UP_status   ==0) { P[2].slot[1]= 6; }
if (P[2].key_BT1_status    ==1) { P[2].bt_slot[1]=1; a=1; }
if (P[2].key_BT2_status    ==1) { P[2].bt_slot[1]=2; b=1; }
if (P[2].key_BT3_status    ==1) { P[2].bt_slot[1]=3; c=1; }
if (P[2].key_BT4_status    ==1) { P[2].bt_slot[1]=4; d=1; }
if (P[2].key_BT5_status    ==1) { P[2].bt_slot[1]=5; e=1; }
if (P[2].key_BT6_status    ==1) { P[2].bt_slot[1]=6; f=1; }
if (P[2].key_SELECT_status ==1) { P[2].bt_slot[1]=7; g=1; }
if (P[2].key_START_status  ==1) { P[2].bt_slot[1]=8; h=1; }
if (P[2].key_BT1_status==1 || P[2].key_BT2_status==1 || P[2].key_BT3_status==1 || P[2].key_BT4_status==1
|| P[2].key_BT5_status==1 || P[2].key_BT6_status==1 || P[2].key_SELECT_status==1 || P[2].key_START_status==1)
{
if (a==1) { strcat(StrBotoes, "1"); } P[2].bt_slot[1] = atoi(StrBotoes);
if (b==1) { strcat(StrBotoes, "2"); } P[2].bt_slot[1] = atoi(StrBotoes);
if (c==1) { strcat(StrBotoes, "3"); } P[2].bt_slot[1] = atoi(StrBotoes);
if (d==1) { strcat(StrBotoes, "4"); } P[2].bt_slot[1] = atoi(StrBotoes);
if (e==1) { strcat(StrBotoes, "5"); } P[2].bt_slot[1] = atoi(StrBotoes);
if (f==1) { strcat(StrBotoes, "6"); } P[2].bt_slot[1] = atoi(StrBotoes);
if (g==1) { strcat(StrBotoes, "7"); } P[2].bt_slot[1] = atoi(StrBotoes);
if (h==1) { strcat(StrBotoes, "8"); } P[2].bt_slot[1] = atoi(StrBotoes);
}
if (P[2].key_LEFT_status  ==1 && P[2].key_UP_status    ==1) { P[2].slot[1]=7; }
if (P[2].key_UP_status    ==1 && P[2].key_RIGHT_status ==1) { P[2].slot[1]=9; }
if (P[2].key_RIGHT_status ==1 && P[2].key_DOWN_status  ==1) { P[2].slot[1]=3; }
if (P[2].key_DOWN_status  ==1 && P[2].key_LEFT_status  ==1) { P[2].slot[1]=1; }
if (P[2].key_DOWN_status  >1 && P[2].key_RIGHT_status ==1) { P[2].slot[1]=3; }
if (P[2].key_RIGHT_status >1 && P[2].key_DOWN_status  ==1) { P[2].slot[1]=3; }
if (P[2].key_DOWN_status  >1 && P[2].key_LEFT_status  ==1) { P[2].slot[1]=1; }
if (P[2].key_LEFT_status  >1 && P[2].key_DOWN_status  ==1) { P[2].slot[1]=1; }
if (P[2].key_UP_status    >1 && P[2].key_RIGHT_status ==1) { P[2].slot[1]=9; }
if (P[2].key_RIGHT_status >1 && P[2].key_UP_status    ==1) { P[2].slot[1]=9; }
if (P[2].key_UP_status    >1 && P[2].key_LEFT_status  ==1) { P[2].slot[1]=7; }
if (P[2].key_LEFT_status  >1 && P[2].key_UP_status    ==1) { P[2].slot[1]=7; }
P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0;
}
if (P[2].key_DOWN_status  ==3 && P[2].key_RIGHT_status>1) { MovSlots_P2(); P[2].slot[1]=6; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].key_DOWN_status  ==3 && P[2].key_LEFT_status >1) { MovSlots_P2(); P[2].slot[1]=4; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].key_RIGHT_status ==3 && P[2].key_DOWN_status >1) { MovSlots_P2(); P[2].slot[1]=2; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].key_LEFT_status  ==3 && P[2].key_DOWN_status >1) { MovSlots_P2(); P[2].slot[1]=2; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].key_UP_status    ==3 && P[2].key_RIGHT_status>1) { MovSlots_P2(); P[2].slot[1]=6; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].key_UP_status    ==3 && P[2].key_LEFT_status >1) { MovSlots_P2(); P[2].slot[1]=4; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].key_RIGHT_status ==3 && P[2].key_UP_status   >1) { MovSlots_P2(); P[2].slot[1]=8; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].key_LEFT_status  ==3 && P[2].key_UP_status   >1) { MovSlots_P2(); P[2].slot[1]=8; P[2].t_slot[1]=P[2].ticks_4slot; P[2].ticks_4slot=0; }
if (P[2].t_slot[1]>999) { P[2].t_slot[1]=999; }
}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MOVIMENTA SLOTS DO INPUT DISPLAY -----------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MovSlots_P1()
{
P[1].bt_slot[16] = P[1].bt_slot[15];
P[1].bt_slot[15] = P[1].bt_slot[14];
P[1].bt_slot[14] = P[1].bt_slot[13];
P[1].bt_slot[13] = P[1].bt_slot[12];
P[1].bt_slot[12] = P[1].bt_slot[11];
P[1].bt_slot[11] = P[1].bt_slot[10];
P[1].bt_slot[10] = P[1].bt_slot[9];
P[1].bt_slot[9]  = P[1].bt_slot[8];
P[1].bt_slot[8]  = P[1].bt_slot[7];
P[1].bt_slot[7]  = P[1].bt_slot[6];
P[1].bt_slot[6]  = P[1].bt_slot[5];
P[1].bt_slot[5]  = P[1].bt_slot[4];
P[1].bt_slot[4]  = P[1].bt_slot[3];
P[1].bt_slot[3]  = P[1].bt_slot[2];
P[1].bt_slot[2]  = P[1].bt_slot[1];
P[1].bt_slot[1]  = 0;

P[1].slot[16] = P[1].slot[15];
P[1].slot[15] = P[1].slot[14];
P[1].slot[14] = P[1].slot[13];
P[1].slot[13] = P[1].slot[12];
P[1].slot[12] = P[1].slot[11];
P[1].slot[11] = P[1].slot[10];
P[1].slot[10] = P[1].slot[9];
P[1].slot[9]  = P[1].slot[8];
P[1].slot[8]  = P[1].slot[7];
P[1].slot[7]  = P[1].slot[6];
P[1].slot[6]  = P[1].slot[5];
P[1].slot[5]  = P[1].slot[4];
P[1].slot[4]  = P[1].slot[3];
P[1].slot[3]  = P[1].slot[2];
P[1].slot[2]  = P[1].slot[1];
P[1].slot[1]  = 0;

P[1].t_slot[16] = P[1].t_slot[15];
P[1].t_slot[15] = P[1].t_slot[14];
P[1].t_slot[14] = P[1].t_slot[13];
P[1].t_slot[13] = P[1].t_slot[12];
P[1].t_slot[12] = P[1].t_slot[11];
P[1].t_slot[11] = P[1].t_slot[10];
P[1].t_slot[10] = P[1].t_slot[9];
P[1].t_slot[9]  = P[1].t_slot[8];
P[1].t_slot[8]  = P[1].t_slot[7];
P[1].t_slot[7]  = P[1].t_slot[6];
P[1].t_slot[6]  = P[1].t_slot[5];
P[1].t_slot[5]  = P[1].t_slot[4];
P[1].t_slot[4]  = P[1].t_slot[3];
P[1].t_slot[3]  = P[1].t_slot[2];
P[1].t_slot[2]  = P[1].t_slot[1];
P[1].t_slot[1]  = 0;
}

void MovSlots_P2()
{
P[2].bt_slot[16] = P[2].bt_slot[15];
P[2].bt_slot[15] = P[2].bt_slot[14];
P[2].bt_slot[14] = P[2].bt_slot[13];
P[2].bt_slot[13] = P[2].bt_slot[12];
P[2].bt_slot[12] = P[2].bt_slot[11];
P[2].bt_slot[11] = P[2].bt_slot[10];
P[2].bt_slot[10] = P[2].bt_slot[9];
P[2].bt_slot[9]  = P[2].bt_slot[8];
P[2].bt_slot[8]  = P[2].bt_slot[7];
P[2].bt_slot[7]  = P[2].bt_slot[6];
P[2].bt_slot[6]  = P[2].bt_slot[5];
P[2].bt_slot[5]  = P[2].bt_slot[4];
P[2].bt_slot[4]  = P[2].bt_slot[3];
P[2].bt_slot[3]  = P[2].bt_slot[2];
P[2].bt_slot[2]  = P[2].bt_slot[1];
P[2].bt_slot[1]  = 0;

P[2].slot[16] = P[2].slot[15];
P[2].slot[15] = P[2].slot[14];
P[2].slot[14] = P[2].slot[13];
P[2].slot[13] = P[2].slot[12];
P[2].slot[12] = P[2].slot[11];
P[2].slot[11] = P[2].slot[10];
P[2].slot[10] = P[2].slot[9];
P[2].slot[9]  = P[2].slot[8];
P[2].slot[8]  = P[2].slot[7];
P[2].slot[7]  = P[2].slot[6];
P[2].slot[6]  = P[2].slot[5];
P[2].slot[5]  = P[2].slot[4];
P[2].slot[4]  = P[2].slot[3];
P[2].slot[3]  = P[2].slot[2];
P[2].slot[2]  = P[2].slot[1];
P[2].slot[1]  = 0;

P[2].t_slot[16] = P[2].t_slot[15];
P[2].t_slot[15] = P[2].t_slot[14];
P[2].t_slot[14] = P[2].t_slot[13];
P[2].t_slot[13] = P[2].t_slot[12];
P[2].t_slot[12] = P[2].t_slot[11];
P[2].t_slot[11] = P[2].t_slot[10];
P[2].t_slot[10] = P[2].t_slot[9];
P[2].t_slot[9]  = P[2].t_slot[8];
P[2].t_slot[8]  = P[2].t_slot[7];
P[2].t_slot[7]  = P[2].t_slot[6];
P[2].t_slot[6]  = P[2].t_slot[5];
P[2].t_slot[5]  = P[2].t_slot[4];
P[2].t_slot[4]  = P[2].t_slot[3];
P[2].t_slot[3]  = P[2].t_slot[2];
P[2].t_slot[2]  = P[2].t_slot[1];
P[2].t_slot[1]  = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INICIALIZA PLAYERS -------------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LOAD_PLAYERS(){

//conta as imagens dos players, abastece o total de frames de cada movimento
char txt[50]="";
for (int indPlayer=1;indPlayer<=2;indPlayer++){
P[indPlayer].TotalDeImagensUtilizadas=-1;
for(int indState=100; indState<=999; indState++){
P[indPlayer].TotalDeFramesMov[indState]=-1;
for(int indAnim=0; indAnim<=29; indAnim++){
if ( indAnim< 10 ) { sprintf(txt, "data/chars/%s/%d_0%d.pcx", P[indPlayer].Name, indState, indAnim); }
if ( indAnim>=10 ) { sprintf(txt, "data/chars/%s/%d_%d.pcx" , P[indPlayer].Name, indState, indAnim); }
if ( backend_file_exists(txt) ) {
P[indPlayer].TotalDeFramesMov[indState]++; //contagem de numero de frames de cada State (Movimento)
P[indPlayer].TotalDeImagensUtilizadas++; //contagem total da quantidade de frames deste personagem

/*COLOCA A IMAGENS NA MEMORIA*/
HM_BITMAP Spr_Aux = backend_create_bitmap(480,480);
Spr_Aux = backend_load_bitmap(txt, NULL);
// Note: bitmap dimensions are stored internally and accessed via backend_bitmap_width/height()

//--!	PALETA DE COR
HM_BITMAP P1_Pallete = backend_create_bitmap(32,10);
HM_BITMAP P2_Pallete = backend_create_bitmap(32,10);
backend_clear_to_color(P1_Pallete, backend_makecol(255, 0, 255));
backend_clear_to_color(P2_Pallete, backend_makecol(255, 0, 255));
sprintf(P1_Pallete_string, "data/chars/%s/pallete.pcx", P[1].Name);
P1_Pallete = backend_load_bitmap(P1_Pallete_string, NULL);
sprintf(P2_Pallete_string, "data/chars/%s/pallete.pcx", P[2].Name);
P2_Pallete = backend_load_bitmap(P2_Pallete_string, NULL);

if(indPlayer==1){
/*P1 PALETA DE COR*/
if (P[1].PossuiPaletaDeCor==1){
int x,y;
//etapa0: conta a quantidade de cores da paleta
for(int ind=0;ind<32;ind++) {
P1_ContadorDeCor=0;
for(int ind=0;ind<32;ind++){ if(backend_getpixel(P1_Pallete,ind,0)!=backend_makecol(255,0,255)) { P1_ContadorDeCor++; } }
}
//etapa1: pega as duas cores
for(int ind=0;ind<P1_ContadorDeCor;ind++){
P1_COR_ORIGINAL = backend_getpixel(P1_Pallete, ind, 0); //cor0
backend_getr(P1_COR_ORIGINAL, &P1_COR_ORIGINAL_R);
backend_getg(P1_COR_ORIGINAL, &P1_COR_ORIGINAL_G);
backend_getb(P1_COR_ORIGINAL, &P1_COR_ORIGINAL_B);
P1_COR_ALTERNATIVA = backend_getpixel(P1_Pallete, ind, P[1].DefineCorDaPaleta); //cor escolhida
backend_getr(P1_COR_ALTERNATIVA, &P1_COR_ALTERNATIVA_R);
backend_getg(P1_COR_ALTERNATIVA, &P1_COR_ALTERNATIVA_G);
backend_getb(P1_COR_ALTERNATIVA, &P1_COR_ALTERNATIVA_B);
//etapa2: faz a substituicao das cores, se a cor COR_ALTERNATIVA nao for transparente
int PodeTrocarAsCores=1;
if(P1_COR_ALTERNATIVA_R==255 && P1_COR_ALTERNATIVA_G==0 && P1_COR_ALTERNATIVA_B==255){ PodeTrocarAsCores=0; }
if(PodeTrocarAsCores==1){
for(y = 0; y < backend_bitmap_height(Spr_Aux); y++) { for(x = 0; x < backend_bitmap_width(Spr_Aux); x++) {
if(backend_getpixel(Spr_Aux, x, y) == backend_makecol( P1_COR_ORIGINAL_R,P1_COR_ORIGINAL_G,P1_COR_ORIGINAL_B)) {
backend_putpixel(Spr_Aux, x, y, backend_makecol(P1_COR_ALTERNATIVA_R,P1_COR_ALTERNATIVA_G,P1_COR_ALTERNATIVA_B)); }}
}
}
}
}
}

if(indPlayer==2){
/*P2 PALETA DE COR*/
if (P[2].PossuiPaletaDeCor==1){
int x,y;
//etapa0: conta a quantidade de cores da paleta
for(int ind=0;ind<32;ind++) {
P2_ContadorDeCor=0;
for(int ind=0;ind<32;ind++){ if(backend_getpixel(P2_Pallete,ind,0)!=backend_makecol(255,0,255)) { P2_ContadorDeCor++; } }
}
//etapa1: pega as duas cores
for(int ind=0;ind<P2_ContadorDeCor;ind++){
P2_COR_ORIGINAL = backend_getpixel(P2_Pallete, ind, 0); //cor0
backend_getr(P2_COR_ORIGINAL, &P2_COR_ORIGINAL_R);
backend_getg(P2_COR_ORIGINAL, &P2_COR_ORIGINAL_G);
backend_getb(P2_COR_ORIGINAL, &P2_COR_ORIGINAL_B);
P2_COR_ALTERNATIVA = backend_getpixel(P2_Pallete, ind, P[2].DefineCorDaPaleta); //cor escolhida
backend_getr(P2_COR_ALTERNATIVA, &P2_COR_ALTERNATIVA_R);
backend_getg(P2_COR_ALTERNATIVA, &P2_COR_ALTERNATIVA_G);
backend_getb(P2_COR_ALTERNATIVA, &P2_COR_ALTERNATIVA_B);
//etapa2: faz a substituicao das cores, se a cor COR_ALTERNATIVA nao for transparente
int PodeTrocarAsCores=1;
if(P2_COR_ALTERNATIVA_R==255 && P2_COR_ALTERNATIVA_G==0 && P2_COR_ALTERNATIVA_B==255){ PodeTrocarAsCores=0; }
if(PodeTrocarAsCores==1){
for(y = 0; y < backend_bitmap_height(Spr_Aux); y++) { for(x = 0; x < backend_bitmap_width(Spr_Aux); x++) {
if(backend_getpixel(Spr_Aux, x, y) == backend_makecol( P2_COR_ORIGINAL_R,P2_COR_ORIGINAL_G,P2_COR_ORIGINAL_B)) {
backend_putpixel(Spr_Aux, x, y, backend_makecol(P2_COR_ALTERNATIVA_R,P2_COR_ALTERNATIVA_G,P2_COR_ALTERNATIVA_B)); }}
}
}
}
}
}

backend_destroy_bitmap(P1_Pallete);
backend_destroy_bitmap(P2_Pallete);
//--!

//se for Type 1 dobra o tamanho do Sprite, e abastece o Atlas
if(P[indPlayer].Type==1){
// Create a bitmap with double dimensions for Type 1 sprites
int orig_w = backend_bitmap_width(Spr_Aux);
int orig_h = backend_bitmap_height(Spr_Aux);
P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas] = backend_create_bitmap(orig_w * 2, orig_h * 2);
//abastece o Atlas type1
backend_stretch_blit( Spr_Aux , P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas] ,
0,0,orig_w,orig_h,
0,0,orig_w*2,orig_h*2);
}
//abastece o Atlas type2
if(P[indPlayer].Type==2) { backend_blit(Spr_Aux, P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas], 0, 0, 0, 0, backend_bitmap_width(Spr_Aux), backend_bitmap_height(Spr_Aux));  }
backend_destroy_bitmap(Spr_Aux);
//tabela do Atlas
P[indPlayer].TableAtlas[P[indPlayer].TotalDeImagensUtilizadas][0]=indState;
P[indPlayer].TableAtlas[P[indPlayer].TotalDeImagensUtilizadas][1]=indAnim;
P[indPlayer].TableAtlas[P[indPlayer].TotalDeImagensUtilizadas][2]=P[indPlayer].TotalDeImagensUtilizadas;

AddTableAtlas(indPlayer, indState, indAnim, P[indPlayer].TotalDeImagensUtilizadas);

}
else { indAnim=29; }
}
if (indState==100) { P[indPlayer].QtdeFrames=P[indPlayer].TotalDeFramesMov[100]; }
}

//movimentos ignorados, pois nao sao utilizados em jogos de luta
// A sequencia de Movs 311-316 correspondem a golpes aereos pulando para tras,
//   assume-se que sao iguais os golpes aereos pulando para frente.
// A sequencia 603 e 605 sao end Pulo para frente e para tras,
//   assume-se que sao iguais o end Pulo do Pulo Neutro.
P[indPlayer].TotalDeFramesMov[311]=P[indPlayer].TotalDeFramesMov[321]; //movimentos 311-316 ignorados
P[indPlayer].TotalDeFramesMov[312]=P[indPlayer].TotalDeFramesMov[322]; //movimentos 311-316 ignorados
P[indPlayer].TotalDeFramesMov[313]=P[indPlayer].TotalDeFramesMov[323]; //movimentos 311-316 ignorados
P[indPlayer].TotalDeFramesMov[314]=P[indPlayer].TotalDeFramesMov[324]; //movimentos 311-316 ignorados
P[indPlayer].TotalDeFramesMov[315]=P[indPlayer].TotalDeFramesMov[325]; //movimentos 311-316 ignorados
P[indPlayer].TotalDeFramesMov[316]=P[indPlayer].TotalDeFramesMov[326]; //movimentos 311-316 ignorados
P[indPlayer].TotalDeFramesMov[603]=P[indPlayer].TotalDeFramesMov[604]; //movimentos 603 e 605 ignorados
P[indPlayer].TotalDeFramesMov[605]=P[indPlayer].TotalDeFramesMov[604]; //movimentos 603 e 605 ignorados

if (indPlayer==1) { PLAYER_STATE(1, 100, 0, P[indPlayer].QtdeFrames); }
if (indPlayer==2) { PLAYER_STATE(2, 100, 0, P[indPlayer].QtdeFrames); }
}

//cria o char vazio
for(int ind=1; ind<=2; ind++){
if(P[ind].TotalDeImagensUtilizadas==-1){
P[ind].TotalDeImagensUtilizadas=0;
HM_BITMAP Spr_Aux = backend_create_bitmap(480,480);
Spr_Aux = backend_load_bitmap("data/system/char_generic2x.pcx", NULL);
// Note: bitmap dimensions are stored internally
backend_blit(Spr_Aux, P[ind].SprAtlas[0], 0, 0, 0, 0, backend_bitmap_width(Spr_Aux), backend_bitmap_height(Spr_Aux));
backend_destroy_bitmap(Spr_Aux);
P[ind].TableAtlas[P[ind].TotalDeImagensUtilizadas][0]=100;
P[ind].TableAtlas[P[ind].TotalDeImagensUtilizadas][1]=0;
P[ind].TableAtlas[P[ind].TotalDeImagensUtilizadas][2]=P[ind].TotalDeImagensUtilizadas;
}
}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STATES sao funcoes muito importantes para o jogo, PLAYER_STATE() ---------------------------------------------------------------------------[**12]
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PLAYER_STATE(int Player, int State, int IndexAnim, int QtdeFrames)
{

//for(int ind=1;ind<=2;ind++){

int ind=Player;

P[ind].State=State;
P[ind].State=State;

P[ind].IndexAnim=IndexAnim;
P[ind].QtdeFrames=QtdeFrames;

Draw_CHBoxes_P1();
Draw_CHBoxes_P2();

char P1_Caminho[99];
if(ind==1){
sprintf(P1_Caminho, "data/chars/%s/char.ini", P[ind].Name);
backend_set_config_file(P1_Caminho);
}

char P2_Caminho[99];
if(ind==2){
sprintf(P2_Caminho, "data/chars/%s/char.ini", P[ind].Name);
backend_set_config_file(P2_Caminho);
}

P[ind].Vspeed_temp=P[ind].Vspeed;
P[ind].Hspeed_temp=P[ind].Hspeed;
P[ind].Gravity_temp=P[ind].Gravity;

if (P[ind].State>=100) { sprintf(P[ind].State_s, "%i" , P[ind].State);	}
if (P[ind].State <100) { sprintf(P[ind].State_s, "0%i", P[ind].State);	}

strcpy(P[ind].Name_Display, (char *)backend_get_config_string("Info", "Name", "-"));

P[ind].XAlign        = backend_get_config_int   (P[ind].State_s, "XAlign" , P[ind].Largura/2 ); //P[ind].Largura_100
P[ind].YAlign        = backend_get_config_int   (P[ind].State_s, "YAlign"       , P[ind].Altura );
P[ind].Vspeed        = backend_get_config_float (P[ind].State_s, "Vspeed"       ,          0 );
P[ind].Hspeed        = backend_get_config_float (P[ind].State_s, "Hspeed"       ,          0 );
P[ind].Gravity       = backend_get_config_float (P[ind].State_s, "Gravity"      ,          0 );
P[ind].Friction      = backend_get_config_float (P[ind].State_s, "Friction"     ,          0 );
P[ind].ChangeDamage  = backend_get_config_int   (P[ind].State_s, "Damage"       ,          0 );
P[ind].Energy       += backend_get_config_int   (P[ind].State_s, "Energy"       ,          0 );
P[ind].Special      += backend_get_config_int   (P[ind].State_s, "Special"      ,          0 );
P[ind].EnergyChange  = backend_get_config_int   (P[ind].State_s, "EnergyChange" ,          0 );
P[ind].SpecialChange = backend_get_config_int   (P[ind].State_s, "SpecialChange",          0 );
P[ind].Visible       = backend_get_config_int   (P[ind].State_s, "Visible"      ,          1 );
P[ind].RoomLimit     = backend_get_config_int   (P[ind].State_s, "RoomLimit"    ,          1 );
strcpy(P[ind].HitType, (char *)backend_get_config_string(P[ind].State_s, "HitType","Normal"));
strcpy(P[ind].HitStack, (char *)backend_get_config_string(P[ind].State_s, "HitStack","Multi"));
P[ind].HitPause      = backend_get_config_int   (P[ind].State_s, "HitPause"     ,          0 );
P[ind].ChangeState   = backend_get_config_int   (P[ind].State_s, "ChangeState"  ,          0 );
P[ind].Freeze        = backend_get_config_int   (P[ind].State_s, "Freeze"       ,          0 );
P[ind].Color         = backend_get_config_int   (P[ind].State_s, "Color"        ,         -1 );
P[ind].TotalFrames   = backend_get_config_int   (P[ind].State_s, "TotalFrames"  , QtdeFrames );

//Altera a Energia
P[ind].Energy+=P[ind].EnergyChange;
if (P[ind].Energy>1000) { P[ind].Energy=1000; }
if (P[ind].Energy<0) { P[ind].Energy=0; }

//Altera o Special
P[ind].Special+=P[ind].SpecialChange;
if (P[ind].Special>1000) { P[ind].Special=1000; }
if (P[ind].Special<0) { P[ind].Special=0; }

if(ind==1){
if (P[1].TotalFrames>= 0) {P1_FrameTime_00 = backend_get_config_int(P[1].State_s, "FrameTime_00", 6)-1; }
if (P[1].TotalFrames>= 1) {P1_FrameTime_01 = backend_get_config_int(P[1].State_s, "FrameTime_01", 6)-1; }
if (P[1].TotalFrames>= 2) {P1_FrameTime_02 = backend_get_config_int(P[1].State_s, "FrameTime_02", 6)-1; }
if (P[1].TotalFrames>= 3) {P1_FrameTime_03 = backend_get_config_int(P[1].State_s, "FrameTime_03", 6)-1; }
if (P[1].TotalFrames>= 4) {P1_FrameTime_04 = backend_get_config_int(P[1].State_s, "FrameTime_04", 6)-1; }
if (P[1].TotalFrames>= 5) {P1_FrameTime_05 = backend_get_config_int(P[1].State_s, "FrameTime_05", 6)-1; }
if (P[1].TotalFrames>= 6) {P1_FrameTime_06 = backend_get_config_int(P[1].State_s, "FrameTime_06", 6)-1; }
if (P[1].TotalFrames>= 7) {P1_FrameTime_07 = backend_get_config_int(P[1].State_s, "FrameTime_07", 6)-1; }
if (P[1].TotalFrames>= 8) {P1_FrameTime_08 = backend_get_config_int(P[1].State_s, "FrameTime_08", 6)-1; }
if (P[1].TotalFrames>= 9) {P1_FrameTime_09 = backend_get_config_int(P[1].State_s, "FrameTime_09", 6)-1; }
if (P[1].TotalFrames>=10) {P1_FrameTime_10 = backend_get_config_int(P[1].State_s, "FrameTime_10", 6)-1; }
if (P[1].TotalFrames>=11) {P1_FrameTime_11 = backend_get_config_int(P[1].State_s, "FrameTime_11", 6)-1; }
if (P[1].TotalFrames>=12) {P1_FrameTime_12 = backend_get_config_int(P[1].State_s, "FrameTime_12", 6)-1; }
if (P[1].TotalFrames>=13) {P1_FrameTime_13 = backend_get_config_int(P[1].State_s, "FrameTime_13", 6)-1; }
if (P[1].TotalFrames>=14) {P1_FrameTime_14 = backend_get_config_int(P[1].State_s, "FrameTime_14", 6)-1; }
if (P[1].TotalFrames>=15) {P1_FrameTime_15 = backend_get_config_int(P[1].State_s, "FrameTime_15", 6)-1; }
if (P[1].TotalFrames>=16) {P1_FrameTime_16 = backend_get_config_int(P[1].State_s, "FrameTime_16", 6)-1; }
if (P[1].TotalFrames>=17) {P1_FrameTime_17 = backend_get_config_int(P[1].State_s, "FrameTime_17", 6)-1; }
if (P[1].TotalFrames>=18) {P1_FrameTime_18 = backend_get_config_int(P[1].State_s, "FrameTime_18", 6)-1; }
if (P[1].TotalFrames>=19) {P1_FrameTime_19 = backend_get_config_int(P[1].State_s, "FrameTime_19", 6)-1; }
if (P[1].TotalFrames>=20) {P1_FrameTime_20 = backend_get_config_int(P[1].State_s, "FrameTime_20", 6)-1; }
if (P[1].TotalFrames>=21) {P1_FrameTime_21 = backend_get_config_int(P[1].State_s, "FrameTime_21", 6)-1; }
if (P[1].TotalFrames>=22) {P1_FrameTime_22 = backend_get_config_int(P[1].State_s, "FrameTime_22", 6)-1; }
if (P[1].TotalFrames>=23) {P1_FrameTime_23 = backend_get_config_int(P[1].State_s, "FrameTime_23", 6)-1; }
if (P[1].TotalFrames>=24) {P1_FrameTime_24 = backend_get_config_int(P[1].State_s, "FrameTime_24", 6)-1; }
if (P[1].TotalFrames>=25) {P1_FrameTime_25 = backend_get_config_int(P[1].State_s, "FrameTime_25", 6)-1; }
if (P[1].TotalFrames>=26) {P1_FrameTime_26 = backend_get_config_int(P[1].State_s, "FrameTime_26", 6)-1; }
if (P[1].TotalFrames>=27) {P1_FrameTime_27 = backend_get_config_int(P[1].State_s, "FrameTime_27", 6)-1; }
if (P[1].TotalFrames>=28) {P1_FrameTime_28 = backend_get_config_int(P[1].State_s, "FrameTime_28", 6)-1; }
if (P[1].TotalFrames>=29) {P1_FrameTime_29 = backend_get_config_int(P[1].State_s, "FrameTime_29", 6)-1; }
P1_FrameTime = P1_FrameTime_00;
}

if(ind==2){
if (P[2].TotalFrames>= 0) {P2_FrameTime_00 = backend_get_config_int(P[2].State_s, "FrameTime_00", 6)-1; }
if (P[2].TotalFrames>= 1) {P2_FrameTime_01 = backend_get_config_int(P[2].State_s, "FrameTime_01", 6)-1; }
if (P[2].TotalFrames>= 2) {P2_FrameTime_02 = backend_get_config_int(P[2].State_s, "FrameTime_02", 6)-1; }
if (P[2].TotalFrames>= 3) {P2_FrameTime_03 = backend_get_config_int(P[2].State_s, "FrameTime_03", 6)-1; }
if (P[2].TotalFrames>= 4) {P2_FrameTime_04 = backend_get_config_int(P[2].State_s, "FrameTime_04", 6)-1; }
if (P[2].TotalFrames>= 5) {P2_FrameTime_05 = backend_get_config_int(P[2].State_s, "FrameTime_05", 6)-1; }
if (P[2].TotalFrames>= 6) {P2_FrameTime_06 = backend_get_config_int(P[2].State_s, "FrameTime_06", 6)-1; }
if (P[2].TotalFrames>= 7) {P2_FrameTime_07 = backend_get_config_int(P[2].State_s, "FrameTime_07", 6)-1; }
if (P[2].TotalFrames>= 8) {P2_FrameTime_08 = backend_get_config_int(P[2].State_s, "FrameTime_08", 6)-1; }
if (P[2].TotalFrames>= 9) {P2_FrameTime_09 = backend_get_config_int(P[2].State_s, "FrameTime_09", 6)-1; }
if (P[2].TotalFrames>=10) {P2_FrameTime_10 = backend_get_config_int(P[2].State_s, "FrameTime_10", 6)-1; }
if (P[2].TotalFrames>=11) {P2_FrameTime_11 = backend_get_config_int(P[2].State_s, "FrameTime_11", 6)-1; }
if (P[2].TotalFrames>=12) {P2_FrameTime_12 = backend_get_config_int(P[2].State_s, "FrameTime_12", 6)-1; }
if (P[2].TotalFrames>=13) {P2_FrameTime_13 = backend_get_config_int(P[2].State_s, "FrameTime_13", 6)-1; }
if (P[2].TotalFrames>=14) {P2_FrameTime_14 = backend_get_config_int(P[2].State_s, "FrameTime_14", 6)-1; }
if (P[2].TotalFrames>=15) {P2_FrameTime_15 = backend_get_config_int(P[2].State_s, "FrameTime_15", 6)-1; }
if (P[2].TotalFrames>=16) {P2_FrameTime_16 = backend_get_config_int(P[2].State_s, "FrameTime_16", 6)-1; }
if (P[2].TotalFrames>=17) {P2_FrameTime_17 = backend_get_config_int(P[2].State_s, "FrameTime_17", 6)-1; }
if (P[2].TotalFrames>=18) {P2_FrameTime_18 = backend_get_config_int(P[2].State_s, "FrameTime_18", 6)-1; }
if (P[2].TotalFrames>=19) {P2_FrameTime_19 = backend_get_config_int(P[2].State_s, "FrameTime_19", 6)-1; }
if (P[2].TotalFrames>=20) {P2_FrameTime_20 = backend_get_config_int(P[2].State_s, "FrameTime_20", 6)-1; }
if (P[2].TotalFrames>=21) {P2_FrameTime_21 = backend_get_config_int(P[2].State_s, "FrameTime_21", 6)-1; }
if (P[2].TotalFrames>=22) {P2_FrameTime_22 = backend_get_config_int(P[2].State_s, "FrameTime_22", 6)-1; }
if (P[2].TotalFrames>=23) {P2_FrameTime_23 = backend_get_config_int(P[2].State_s, "FrameTime_23", 6)-1; }
if (P[2].TotalFrames>=24) {P2_FrameTime_24 = backend_get_config_int(P[2].State_s, "FrameTime_24", 6)-1; }
if (P[2].TotalFrames>=25) {P2_FrameTime_25 = backend_get_config_int(P[2].State_s, "FrameTime_25", 6)-1; }
if (P[2].TotalFrames>=26) {P2_FrameTime_26 = backend_get_config_int(P[2].State_s, "FrameTime_26", 6)-1; }
if (P[2].TotalFrames>=27) {P2_FrameTime_27 = backend_get_config_int(P[2].State_s, "FrameTime_27", 6)-1; }
if (P[2].TotalFrames>=28) {P2_FrameTime_28 = backend_get_config_int(P[2].State_s, "FrameTime_28", 6)-1; }
if (P[2].TotalFrames>=29) {P2_FrameTime_29 = backend_get_config_int(P[2].State_s, "FrameTime_29", 6)-1; }
P2_FrameTime = P2_FrameTime_00;
}

if(ind==1){
if(ForcaDoGolpeP1==1){
if (P[1].TotalFrames>= 0) {P1_FrameTime_00 = backend_get_config_int(P[1].State_s, "V1_FrameTime_00", 6)-1; }
if (P[1].TotalFrames>= 1) {P1_FrameTime_01 = backend_get_config_int(P[1].State_s, "V1_FrameTime_01", 6)-1; }
if (P[1].TotalFrames>= 2) {P1_FrameTime_02 = backend_get_config_int(P[1].State_s, "V1_FrameTime_02", 6)-1; }
if (P[1].TotalFrames>= 3) {P1_FrameTime_03 = backend_get_config_int(P[1].State_s, "V1_FrameTime_03", 6)-1; }
if (P[1].TotalFrames>= 4) {P1_FrameTime_04 = backend_get_config_int(P[1].State_s, "V1_FrameTime_04", 6)-1; }
if (P[1].TotalFrames>= 5) {P1_FrameTime_05 = backend_get_config_int(P[1].State_s, "V1_FrameTime_05", 6)-1; }
if (P[1].TotalFrames>= 6) {P1_FrameTime_06 = backend_get_config_int(P[1].State_s, "V1_FrameTime_06", 6)-1; }
if (P[1].TotalFrames>= 7) {P1_FrameTime_07 = backend_get_config_int(P[1].State_s, "V1_FrameTime_07", 6)-1; }
if (P[1].TotalFrames>= 8) {P1_FrameTime_08 = backend_get_config_int(P[1].State_s, "V1_FrameTime_08", 6)-1; }
if (P[1].TotalFrames>= 9) {P1_FrameTime_09 = backend_get_config_int(P[1].State_s, "V1_FrameTime_09", 6)-1; }
if (P[1].TotalFrames>=10) {P1_FrameTime_10 = backend_get_config_int(P[1].State_s, "V1_FrameTime_10", 6)-1; }
if (P[1].TotalFrames>=11) {P1_FrameTime_11 = backend_get_config_int(P[1].State_s, "V1_FrameTime_11", 6)-1; }
if (P[1].TotalFrames>=12) {P1_FrameTime_12 = backend_get_config_int(P[1].State_s, "V1_FrameTime_12", 6)-1; }
if (P[1].TotalFrames>=13) {P1_FrameTime_13 = backend_get_config_int(P[1].State_s, "V1_FrameTime_13", 6)-1; }
if (P[1].TotalFrames>=14) {P1_FrameTime_14 = backend_get_config_int(P[1].State_s, "V1_FrameTime_14", 6)-1; }
if (P[1].TotalFrames>=15) {P1_FrameTime_15 = backend_get_config_int(P[1].State_s, "V1_FrameTime_15", 6)-1; }
if (P[1].TotalFrames>=16) {P1_FrameTime_16 = backend_get_config_int(P[1].State_s, "V1_FrameTime_16", 6)-1; }
if (P[1].TotalFrames>=17) {P1_FrameTime_17 = backend_get_config_int(P[1].State_s, "V1_FrameTime_17", 6)-1; }
if (P[1].TotalFrames>=18) {P1_FrameTime_18 = backend_get_config_int(P[1].State_s, "V1_FrameTime_18", 6)-1; }
if (P[1].TotalFrames>=19) {P1_FrameTime_19 = backend_get_config_int(P[1].State_s, "V1_FrameTime_19", 6)-1; }
if (P[1].TotalFrames>=20) {P1_FrameTime_20 = backend_get_config_int(P[1].State_s, "V1_FrameTime_20", 6)-1; }
if (P[1].TotalFrames>=21) {P1_FrameTime_21 = backend_get_config_int(P[1].State_s, "V1_FrameTime_21", 6)-1; }
if (P[1].TotalFrames>=22) {P1_FrameTime_22 = backend_get_config_int(P[1].State_s, "V1_FrameTime_22", 6)-1; }
if (P[1].TotalFrames>=23) {P1_FrameTime_23 = backend_get_config_int(P[1].State_s, "V1_FrameTime_23", 6)-1; }
if (P[1].TotalFrames>=24) {P1_FrameTime_24 = backend_get_config_int(P[1].State_s, "V1_FrameTime_24", 6)-1; }
if (P[1].TotalFrames>=25) {P1_FrameTime_25 = backend_get_config_int(P[1].State_s, "V1_FrameTime_25", 6)-1; }
if (P[1].TotalFrames>=26) {P1_FrameTime_26 = backend_get_config_int(P[1].State_s, "V1_FrameTime_26", 6)-1; }
if (P[1].TotalFrames>=27) {P1_FrameTime_27 = backend_get_config_int(P[1].State_s, "V1_FrameTime_27", 6)-1; }
if (P[1].TotalFrames>=28) {P1_FrameTime_28 = backend_get_config_int(P[1].State_s, "V1_FrameTime_28", 6)-1; }
if (P[1].TotalFrames>=29) {P1_FrameTime_29 = backend_get_config_int(P[1].State_s, "V1_FrameTime_29", 6)-1; }
P1_FrameTime = P1_FrameTime_00;
}
if(ForcaDoGolpeP1==2){
if (P[1].TotalFrames>= 0) {P1_FrameTime_00 = backend_get_config_int(P[1].State_s, "V2_FrameTime_00", 6)-1; }
if (P[1].TotalFrames>= 1) {P1_FrameTime_01 = backend_get_config_int(P[1].State_s, "V2_FrameTime_01", 6)-1; }
if (P[1].TotalFrames>= 2) {P1_FrameTime_02 = backend_get_config_int(P[1].State_s, "V2_FrameTime_02", 6)-1; }
if (P[1].TotalFrames>= 3) {P1_FrameTime_03 = backend_get_config_int(P[1].State_s, "V2_FrameTime_03", 6)-1; }
if (P[1].TotalFrames>= 4) {P1_FrameTime_04 = backend_get_config_int(P[1].State_s, "V2_FrameTime_04", 6)-1; }
if (P[1].TotalFrames>= 5) {P1_FrameTime_05 = backend_get_config_int(P[1].State_s, "V2_FrameTime_05", 6)-1; }
if (P[1].TotalFrames>= 6) {P1_FrameTime_06 = backend_get_config_int(P[1].State_s, "V2_FrameTime_06", 6)-1; }
if (P[1].TotalFrames>= 7) {P1_FrameTime_07 = backend_get_config_int(P[1].State_s, "V2_FrameTime_07", 6)-1; }
if (P[1].TotalFrames>= 8) {P1_FrameTime_08 = backend_get_config_int(P[1].State_s, "V2_FrameTime_08", 6)-1; }
if (P[1].TotalFrames>= 9) {P1_FrameTime_09 = backend_get_config_int(P[1].State_s, "V2_FrameTime_09", 6)-1; }
if (P[1].TotalFrames>=10) {P1_FrameTime_10 = backend_get_config_int(P[1].State_s, "V2_FrameTime_10", 6)-1; }
if (P[1].TotalFrames>=11) {P1_FrameTime_11 = backend_get_config_int(P[1].State_s, "V2_FrameTime_11", 6)-1; }
if (P[1].TotalFrames>=12) {P1_FrameTime_12 = backend_get_config_int(P[1].State_s, "V2_FrameTime_12", 6)-1; }
if (P[1].TotalFrames>=13) {P1_FrameTime_13 = backend_get_config_int(P[1].State_s, "V2_FrameTime_13", 6)-1; }
if (P[1].TotalFrames>=14) {P1_FrameTime_14 = backend_get_config_int(P[1].State_s, "V2_FrameTime_14", 6)-1; }
if (P[1].TotalFrames>=15) {P1_FrameTime_15 = backend_get_config_int(P[1].State_s, "V2_FrameTime_15", 6)-1; }
if (P[1].TotalFrames>=16) {P1_FrameTime_16 = backend_get_config_int(P[1].State_s, "V2_FrameTime_16", 6)-1; }
if (P[1].TotalFrames>=17) {P1_FrameTime_17 = backend_get_config_int(P[1].State_s, "V2_FrameTime_17", 6)-1; }
if (P[1].TotalFrames>=18) {P1_FrameTime_18 = backend_get_config_int(P[1].State_s, "V2_FrameTime_18", 6)-1; }
if (P[1].TotalFrames>=19) {P1_FrameTime_19 = backend_get_config_int(P[1].State_s, "V2_FrameTime_19", 6)-1; }
if (P[1].TotalFrames>=20) {P1_FrameTime_20 = backend_get_config_int(P[1].State_s, "V2_FrameTime_20", 6)-1; }
if (P[1].TotalFrames>=21) {P1_FrameTime_21 = backend_get_config_int(P[1].State_s, "V2_FrameTime_21", 6)-1; }
if (P[1].TotalFrames>=22) {P1_FrameTime_22 = backend_get_config_int(P[1].State_s, "V2_FrameTime_22", 6)-1; }
if (P[1].TotalFrames>=23) {P1_FrameTime_23 = backend_get_config_int(P[1].State_s, "V2_FrameTime_23", 6)-1; }
if (P[1].TotalFrames>=24) {P1_FrameTime_24 = backend_get_config_int(P[1].State_s, "V2_FrameTime_24", 6)-1; }
if (P[1].TotalFrames>=25) {P1_FrameTime_25 = backend_get_config_int(P[1].State_s, "V2_FrameTime_25", 6)-1; }
if (P[1].TotalFrames>=26) {P1_FrameTime_26 = backend_get_config_int(P[1].State_s, "V2_FrameTime_26", 6)-1; }
if (P[1].TotalFrames>=27) {P1_FrameTime_27 = backend_get_config_int(P[1].State_s, "V2_FrameTime_27", 6)-1; }
if (P[1].TotalFrames>=28) {P1_FrameTime_28 = backend_get_config_int(P[1].State_s, "V2_FrameTime_28", 6)-1; }
if (P[1].TotalFrames>=29) {P1_FrameTime_29 = backend_get_config_int(P[1].State_s, "V2_FrameTime_29", 6)-1; }
P1_FrameTime = P1_FrameTime_00;
}
if(ForcaDoGolpeP1==3){
if (P[1].TotalFrames>= 0) {P1_FrameTime_00 = backend_get_config_int(P[1].State_s, "V3_FrameTime_00", 6)-1; }
if (P[1].TotalFrames>= 1) {P1_FrameTime_01 = backend_get_config_int(P[1].State_s, "V3_FrameTime_01", 6)-1; }
if (P[1].TotalFrames>= 2) {P1_FrameTime_02 = backend_get_config_int(P[1].State_s, "V3_FrameTime_02", 6)-1; }
if (P[1].TotalFrames>= 3) {P1_FrameTime_03 = backend_get_config_int(P[1].State_s, "V3_FrameTime_03", 6)-1; }
if (P[1].TotalFrames>= 4) {P1_FrameTime_04 = backend_get_config_int(P[1].State_s, "V3_FrameTime_04", 6)-1; }
if (P[1].TotalFrames>= 5) {P1_FrameTime_05 = backend_get_config_int(P[1].State_s, "V3_FrameTime_05", 6)-1; }
if (P[1].TotalFrames>= 6) {P1_FrameTime_06 = backend_get_config_int(P[1].State_s, "V3_FrameTime_06", 6)-1; }
if (P[1].TotalFrames>= 7) {P1_FrameTime_07 = backend_get_config_int(P[1].State_s, "V3_FrameTime_07", 6)-1; }
if (P[1].TotalFrames>= 8) {P1_FrameTime_08 = backend_get_config_int(P[1].State_s, "V3_FrameTime_08", 6)-1; }
if (P[1].TotalFrames>= 9) {P1_FrameTime_09 = backend_get_config_int(P[1].State_s, "V3_FrameTime_09", 6)-1; }
if (P[1].TotalFrames>=10) {P1_FrameTime_10 = backend_get_config_int(P[1].State_s, "V3_FrameTime_10", 6)-1; }
if (P[1].TotalFrames>=11) {P1_FrameTime_11 = backend_get_config_int(P[1].State_s, "V3_FrameTime_11", 6)-1; }
if (P[1].TotalFrames>=12) {P1_FrameTime_12 = backend_get_config_int(P[1].State_s, "V3_FrameTime_12", 6)-1; }
if (P[1].TotalFrames>=13) {P1_FrameTime_13 = backend_get_config_int(P[1].State_s, "V3_FrameTime_13", 6)-1; }
if (P[1].TotalFrames>=14) {P1_FrameTime_14 = backend_get_config_int(P[1].State_s, "V3_FrameTime_14", 6)-1; }
if (P[1].TotalFrames>=15) {P1_FrameTime_15 = backend_get_config_int(P[1].State_s, "V3_FrameTime_15", 6)-1; }
if (P[1].TotalFrames>=16) {P1_FrameTime_16 = backend_get_config_int(P[1].State_s, "V3_FrameTime_16", 6)-1; }
if (P[1].TotalFrames>=17) {P1_FrameTime_17 = backend_get_config_int(P[1].State_s, "V3_FrameTime_17", 6)-1; }
if (P[1].TotalFrames>=18) {P1_FrameTime_18 = backend_get_config_int(P[1].State_s, "V3_FrameTime_18", 6)-1; }
if (P[1].TotalFrames>=19) {P1_FrameTime_19 = backend_get_config_int(P[1].State_s, "V3_FrameTime_19", 6)-1; }
if (P[1].TotalFrames>=20) {P1_FrameTime_20 = backend_get_config_int(P[1].State_s, "V3_FrameTime_20", 6)-1; }
if (P[1].TotalFrames>=21) {P1_FrameTime_21 = backend_get_config_int(P[1].State_s, "V3_FrameTime_21", 6)-1; }
if (P[1].TotalFrames>=22) {P1_FrameTime_22 = backend_get_config_int(P[1].State_s, "V3_FrameTime_22", 6)-1; }
if (P[1].TotalFrames>=23) {P1_FrameTime_23 = backend_get_config_int(P[1].State_s, "V3_FrameTime_23", 6)-1; }
if (P[1].TotalFrames>=24) {P1_FrameTime_24 = backend_get_config_int(P[1].State_s, "V3_FrameTime_24", 6)-1; }
if (P[1].TotalFrames>=25) {P1_FrameTime_25 = backend_get_config_int(P[1].State_s, "V3_FrameTime_25", 6)-1; }
if (P[1].TotalFrames>=26) {P1_FrameTime_26 = backend_get_config_int(P[1].State_s, "V3_FrameTime_26", 6)-1; }
if (P[1].TotalFrames>=27) {P1_FrameTime_27 = backend_get_config_int(P[1].State_s, "V3_FrameTime_27", 6)-1; }
if (P[1].TotalFrames>=28) {P1_FrameTime_28 = backend_get_config_int(P[1].State_s, "V3_FrameTime_28", 6)-1; }
if (P[1].TotalFrames>=29) {P1_FrameTime_29 = backend_get_config_int(P[1].State_s, "V3_FrameTime_29", 6)-1; }
P1_FrameTime = P1_FrameTime_00;
}
}

if(ind==2){
if(ForcaDoGolpeP2==1){
if (P[2].TotalFrames>= 0) {P2_FrameTime_00 = backend_get_config_int(P[2].State_s, "V1_FrameTime_00", 6)-1; }
if (P[2].TotalFrames>= 1) {P2_FrameTime_01 = backend_get_config_int(P[2].State_s, "V1_FrameTime_01", 6)-1; }
if (P[2].TotalFrames>= 2) {P2_FrameTime_02 = backend_get_config_int(P[2].State_s, "V1_FrameTime_02", 6)-1; }
if (P[2].TotalFrames>= 3) {P2_FrameTime_03 = backend_get_config_int(P[2].State_s, "V1_FrameTime_03", 6)-1; }
if (P[2].TotalFrames>= 4) {P2_FrameTime_04 = backend_get_config_int(P[2].State_s, "V1_FrameTime_04", 6)-1; }
if (P[2].TotalFrames>= 5) {P2_FrameTime_05 = backend_get_config_int(P[2].State_s, "V1_FrameTime_05", 6)-1; }
if (P[2].TotalFrames>= 6) {P2_FrameTime_06 = backend_get_config_int(P[2].State_s, "V1_FrameTime_06", 6)-1; }
if (P[2].TotalFrames>= 7) {P2_FrameTime_07 = backend_get_config_int(P[2].State_s, "V1_FrameTime_07", 6)-1; }
if (P[2].TotalFrames>= 8) {P2_FrameTime_08 = backend_get_config_int(P[2].State_s, "V1_FrameTime_08", 6)-1; }
if (P[2].TotalFrames>= 9) {P2_FrameTime_09 = backend_get_config_int(P[2].State_s, "V1_FrameTime_09", 6)-1; }
if (P[2].TotalFrames>=10) {P2_FrameTime_10 = backend_get_config_int(P[2].State_s, "V1_FrameTime_10", 6)-1; }
if (P[2].TotalFrames>=11) {P2_FrameTime_11 = backend_get_config_int(P[2].State_s, "V1_FrameTime_11", 6)-1; }
if (P[2].TotalFrames>=12) {P2_FrameTime_12 = backend_get_config_int(P[2].State_s, "V1_FrameTime_12", 6)-1; }
if (P[2].TotalFrames>=13) {P2_FrameTime_13 = backend_get_config_int(P[2].State_s, "V1_FrameTime_13", 6)-1; }
if (P[2].TotalFrames>=14) {P2_FrameTime_14 = backend_get_config_int(P[2].State_s, "V1_FrameTime_14", 6)-1; }
if (P[2].TotalFrames>=15) {P2_FrameTime_15 = backend_get_config_int(P[2].State_s, "V1_FrameTime_15", 6)-1; }
if (P[2].TotalFrames>=16) {P2_FrameTime_16 = backend_get_config_int(P[2].State_s, "V1_FrameTime_16", 6)-1; }
if (P[2].TotalFrames>=17) {P2_FrameTime_17 = backend_get_config_int(P[2].State_s, "V1_FrameTime_17", 6)-1; }
if (P[2].TotalFrames>=18) {P2_FrameTime_18 = backend_get_config_int(P[2].State_s, "V1_FrameTime_18", 6)-1; }
if (P[2].TotalFrames>=19) {P2_FrameTime_19 = backend_get_config_int(P[2].State_s, "V1_FrameTime_19", 6)-1; }
if (P[2].TotalFrames>=20) {P2_FrameTime_20 = backend_get_config_int(P[2].State_s, "V1_FrameTime_20", 6)-1; }
if (P[2].TotalFrames>=21) {P2_FrameTime_21 = backend_get_config_int(P[2].State_s, "V1_FrameTime_21", 6)-1; }
if (P[2].TotalFrames>=22) {P2_FrameTime_22 = backend_get_config_int(P[2].State_s, "V1_FrameTime_22", 6)-1; }
if (P[2].TotalFrames>=23) {P2_FrameTime_23 = backend_get_config_int(P[2].State_s, "V1_FrameTime_23", 6)-1; }
if (P[2].TotalFrames>=24) {P2_FrameTime_24 = backend_get_config_int(P[2].State_s, "V1_FrameTime_24", 6)-1; }
if (P[2].TotalFrames>=25) {P2_FrameTime_25 = backend_get_config_int(P[2].State_s, "V1_FrameTime_25", 6)-1; }
if (P[2].TotalFrames>=26) {P2_FrameTime_26 = backend_get_config_int(P[2].State_s, "V1_FrameTime_26", 6)-1; }
if (P[2].TotalFrames>=27) {P2_FrameTime_27 = backend_get_config_int(P[2].State_s, "V1_FrameTime_27", 6)-1; }
if (P[2].TotalFrames>=28) {P2_FrameTime_28 = backend_get_config_int(P[2].State_s, "V1_FrameTime_28", 6)-1; }
if (P[2].TotalFrames>=29) {P2_FrameTime_29 = backend_get_config_int(P[2].State_s, "V1_FrameTime_29", 6)-1; }
P2_FrameTime = P2_FrameTime_00;
}
if(ForcaDoGolpeP2==2){
if (P[2].TotalFrames>= 0) {P2_FrameTime_00 = backend_get_config_int(P[2].State_s, "V2_FrameTime_00", 6)-1; }
if (P[2].TotalFrames>= 1) {P2_FrameTime_01 = backend_get_config_int(P[2].State_s, "V2_FrameTime_01", 6)-1; }
if (P[2].TotalFrames>= 2) {P2_FrameTime_02 = backend_get_config_int(P[2].State_s, "V2_FrameTime_02", 6)-1; }
if (P[2].TotalFrames>= 3) {P2_FrameTime_03 = backend_get_config_int(P[2].State_s, "V2_FrameTime_03", 6)-1; }
if (P[2].TotalFrames>= 4) {P2_FrameTime_04 = backend_get_config_int(P[2].State_s, "V2_FrameTime_04", 6)-1; }
if (P[2].TotalFrames>= 5) {P2_FrameTime_05 = backend_get_config_int(P[2].State_s, "V2_FrameTime_05", 6)-1; }
if (P[2].TotalFrames>= 6) {P2_FrameTime_06 = backend_get_config_int(P[2].State_s, "V2_FrameTime_06", 6)-1; }
if (P[2].TotalFrames>= 7) {P2_FrameTime_07 = backend_get_config_int(P[2].State_s, "V2_FrameTime_07", 6)-1; }
if (P[2].TotalFrames>= 8) {P2_FrameTime_08 = backend_get_config_int(P[2].State_s, "V2_FrameTime_08", 6)-1; }
if (P[2].TotalFrames>= 9) {P2_FrameTime_09 = backend_get_config_int(P[2].State_s, "V2_FrameTime_09", 6)-1; }
if (P[2].TotalFrames>=10) {P2_FrameTime_10 = backend_get_config_int(P[2].State_s, "V2_FrameTime_10", 6)-1; }
if (P[2].TotalFrames>=11) {P2_FrameTime_11 = backend_get_config_int(P[2].State_s, "V2_FrameTime_11", 6)-1; }
if (P[2].TotalFrames>=12) {P2_FrameTime_12 = backend_get_config_int(P[2].State_s, "V2_FrameTime_12", 6)-1; }
if (P[2].TotalFrames>=13) {P2_FrameTime_13 = backend_get_config_int(P[2].State_s, "V2_FrameTime_13", 6)-1; }
if (P[2].TotalFrames>=14) {P2_FrameTime_14 = backend_get_config_int(P[2].State_s, "V2_FrameTime_14", 6)-1; }
if (P[2].TotalFrames>=15) {P2_FrameTime_15 = backend_get_config_int(P[2].State_s, "V2_FrameTime_15", 6)-1; }
if (P[2].TotalFrames>=16) {P2_FrameTime_16 = backend_get_config_int(P[2].State_s, "V2_FrameTime_16", 6)-1; }
if (P[2].TotalFrames>=17) {P2_FrameTime_17 = backend_get_config_int(P[2].State_s, "V2_FrameTime_17", 6)-1; }
if (P[2].TotalFrames>=18) {P2_FrameTime_18 = backend_get_config_int(P[2].State_s, "V2_FrameTime_18", 6)-1; }
if (P[2].TotalFrames>=19) {P2_FrameTime_19 = backend_get_config_int(P[2].State_s, "V2_FrameTime_19", 6)-1; }
if (P[2].TotalFrames>=20) {P2_FrameTime_20 = backend_get_config_int(P[2].State_s, "V2_FrameTime_20", 6)-1; }
if (P[2].TotalFrames>=21) {P2_FrameTime_21 = backend_get_config_int(P[2].State_s, "V2_FrameTime_21", 6)-1; }
if (P[2].TotalFrames>=22) {P2_FrameTime_22 = backend_get_config_int(P[2].State_s, "V2_FrameTime_22", 6)-1; }
if (P[2].TotalFrames>=23) {P2_FrameTime_23 = backend_get_config_int(P[2].State_s, "V2_FrameTime_23", 6)-1; }
if (P[2].TotalFrames>=24) {P2_FrameTime_24 = backend_get_config_int(P[2].State_s, "V2_FrameTime_24", 6)-1; }
if (P[2].TotalFrames>=25) {P2_FrameTime_25 = backend_get_config_int(P[2].State_s, "V2_FrameTime_25", 6)-1; }
if (P[2].TotalFrames>=26) {P2_FrameTime_26 = backend_get_config_int(P[2].State_s, "V2_FrameTime_26", 6)-1; }
if (P[2].TotalFrames>=27) {P2_FrameTime_27 = backend_get_config_int(P[2].State_s, "V2_FrameTime_27", 6)-1; }
if (P[2].TotalFrames>=28) {P2_FrameTime_28 = backend_get_config_int(P[2].State_s, "V2_FrameTime_28", 6)-1; }
if (P[2].TotalFrames>=29) {P2_FrameTime_29 = backend_get_config_int(P[2].State_s, "V2_FrameTime_29", 6)-1; }
P2_FrameTime = P2_FrameTime_00;
}
if(ForcaDoGolpeP2==3){
if (P[2].TotalFrames>= 0) {P2_FrameTime_00 = backend_get_config_int(P[2].State_s, "V3_FrameTime_00", 6)-1; }
if (P[2].TotalFrames>= 1) {P2_FrameTime_01 = backend_get_config_int(P[2].State_s, "V3_FrameTime_01", 6)-1; }
if (P[2].TotalFrames>= 2) {P2_FrameTime_02 = backend_get_config_int(P[2].State_s, "V3_FrameTime_02", 6)-1; }
if (P[2].TotalFrames>= 3) {P2_FrameTime_03 = backend_get_config_int(P[2].State_s, "V3_FrameTime_03", 6)-1; }
if (P[2].TotalFrames>= 4) {P2_FrameTime_04 = backend_get_config_int(P[2].State_s, "V3_FrameTime_04", 6)-1; }
if (P[2].TotalFrames>= 5) {P2_FrameTime_05 = backend_get_config_int(P[2].State_s, "V3_FrameTime_05", 6)-1; }
if (P[2].TotalFrames>= 6) {P2_FrameTime_06 = backend_get_config_int(P[2].State_s, "V3_FrameTime_06", 6)-1; }
if (P[2].TotalFrames>= 7) {P2_FrameTime_07 = backend_get_config_int(P[2].State_s, "V3_FrameTime_07", 6)-1; }
if (P[2].TotalFrames>= 8) {P2_FrameTime_08 = backend_get_config_int(P[2].State_s, "V3_FrameTime_08", 6)-1; }
if (P[2].TotalFrames>= 9) {P2_FrameTime_09 = backend_get_config_int(P[2].State_s, "V3_FrameTime_09", 6)-1; }
if (P[2].TotalFrames>=10) {P2_FrameTime_10 = backend_get_config_int(P[2].State_s, "V3_FrameTime_10", 6)-1; }
if (P[2].TotalFrames>=11) {P2_FrameTime_11 = backend_get_config_int(P[2].State_s, "V3_FrameTime_11", 6)-1; }
if (P[2].TotalFrames>=12) {P2_FrameTime_12 = backend_get_config_int(P[2].State_s, "V3_FrameTime_12", 6)-1; }
if (P[2].TotalFrames>=13) {P2_FrameTime_13 = backend_get_config_int(P[2].State_s, "V3_FrameTime_13", 6)-1; }
if (P[2].TotalFrames>=14) {P2_FrameTime_14 = backend_get_config_int(P[2].State_s, "V3_FrameTime_14", 6)-1; }
if (P[2].TotalFrames>=15) {P2_FrameTime_15 = backend_get_config_int(P[2].State_s, "V3_FrameTime_15", 6)-1; }
if (P[2].TotalFrames>=16) {P2_FrameTime_16 = backend_get_config_int(P[2].State_s, "V3_FrameTime_16", 6)-1; }
if (P[2].TotalFrames>=17) {P2_FrameTime_17 = backend_get_config_int(P[2].State_s, "V3_FrameTime_17", 6)-1; }
if (P[2].TotalFrames>=18) {P2_FrameTime_18 = backend_get_config_int(P[2].State_s, "V3_FrameTime_18", 6)-1; }
if (P[2].TotalFrames>=19) {P2_FrameTime_19 = backend_get_config_int(P[2].State_s, "V3_FrameTime_19", 6)-1; }
if (P[2].TotalFrames>=20) {P2_FrameTime_20 = backend_get_config_int(P[2].State_s, "V3_FrameTime_20", 6)-1; }
if (P[2].TotalFrames>=21) {P2_FrameTime_21 = backend_get_config_int(P[2].State_s, "V3_FrameTime_21", 6)-1; }
if (P[2].TotalFrames>=22) {P2_FrameTime_22 = backend_get_config_int(P[2].State_s, "V3_FrameTime_22", 6)-1; }
if (P[2].TotalFrames>=23) {P2_FrameTime_23 = backend_get_config_int(P[2].State_s, "V3_FrameTime_23", 6)-1; }
if (P[2].TotalFrames>=24) {P2_FrameTime_24 = backend_get_config_int(P[2].State_s, "V3_FrameTime_24", 6)-1; }
if (P[2].TotalFrames>=25) {P2_FrameTime_25 = backend_get_config_int(P[2].State_s, "V3_FrameTime_25", 6)-1; }
if (P[2].TotalFrames>=26) {P2_FrameTime_26 = backend_get_config_int(P[2].State_s, "V3_FrameTime_26", 6)-1; }
if (P[2].TotalFrames>=27) {P2_FrameTime_27 = backend_get_config_int(P[2].State_s, "V3_FrameTime_27", 6)-1; }
if (P[2].TotalFrames>=28) {P2_FrameTime_28 = backend_get_config_int(P[2].State_s, "V3_FrameTime_28", 6)-1; }
if (P[2].TotalFrames>=29) {P2_FrameTime_29 = backend_get_config_int(P[2].State_s, "V3_FrameTime_29", 6)-1; }
P2_FrameTime = P2_FrameTime_00;
}

}

//Mov Automatico ao andar
if ( (P[ind].State==410 || P[ind].State==420) && P[ind].Hspeed==0 ) {
P[ind].Hspeed=2;
if (P[ind].State==410) { P[ind].Hspeed=-2; }
}

//Mov Automatico ao pular
if ( (P[ind].State==310 || P[ind].State==300 || P[ind].State==320 ) && ( P[ind].Vspeed==0 && P[ind].Gravity==0 ) ) {
if (P[ind].State==300) { P[ind].Vspeed=-12; P[ind].Gravity=0.6; }
if (P[ind].State==310) { P[ind].Vspeed=-12; P[ind].Gravity=0.6; P[ind].Hspeed=-3; }
if (P[ind].State==320) { P[ind].Vspeed=-12; P[ind].Gravity=0.6; P[ind].Hspeed= 3; }
}

//Mov Automatico reversao aerea
if ( (P[ind].State==507 ) && ( P[ind].Vspeed==0 && P[ind].Gravity==0 ) ) {
P[ind].Vspeed=-8;
P[ind].Gravity=0.5;
P[ind].Hspeed=-4;
}

//Mov Automatico ao cair
if ( (P[ind].State==550 ) && ( P[ind].Vspeed==0 && P[ind].Gravity==0 ) ) {
P[ind].Vspeed=-8;
P[ind].Gravity=0.5;
P[ind].Hspeed=-1;
}

//Mov Automatico ao cair2
if ( (P[ind].State==551 ) && ( P[ind].Vspeed==0 && P[ind].Gravity==0 ) ) {
P[ind].Vspeed=-1;
P[ind].Gravity=0.3;
P[ind].Hspeed=-1;
}

//Mov Automatico ao cair por KO
if ( (P[ind].State==570 ) ) {
P[ind].Vspeed=-6;
P[ind].Gravity=0.3;
P[ind].Hspeed=-2;
}

//Mov Automatico ao cair2 por KO
if ( (P[ind].State==571 ) ) {
P[ind].Vspeed=-1;
P[ind].Gravity=0.1;
P[ind].Hspeed=-1;
}

//inverte a velocidade hotizontal se estiver do lado direto da tela
if (P[ind].Lado==-1) {
P[ind].Hspeed=P[ind].Hspeed*-1;
}

//Atribui atributos do pulo em golpes aereos
if (P[ind].State==301 || P[ind].State==302 || P[ind].State==303
|| P[ind].State ==304 || P[ind].State==305 || P[ind].State==306
|| P[ind].State ==311 || P[ind].State==312 || P[ind].State==313
|| P[ind].State ==314 || P[ind].State==315 || P[ind].State==316
|| P[ind].State ==321 || P[ind].State==322 || P[ind].State==323
|| P[ind].State ==324 || P[ind].State==325 || P[ind].State==326) {
P[ind].Hspeed=P[ind].Hspeed_temp;
P[ind].Vspeed=P[ind].Vspeed_temp;
P[ind].Gravity=P[ind].Gravity_temp;
}

//}

//special
if(P[ind].State>=700){

if(ind==1){
sprintf(P1_Caminho, "data/chars/%s/special.ini", P[ind].Name);
backend_set_config_file(P1_Caminho);
}
if(ind==2){
sprintf(P2_Caminho, "data/chars/%s/special.ini", P[ind].Name);
backend_set_config_file(P2_Caminho);
}
//P[ind].XAlign        = backend_get_config_int   (P[ind].State_s, "XAlign" , P[ind].Largura/2 ); //P[ind].Largura_100
//P[ind].YAlign        = backend_get_config_int   (P[ind].State_s, "YAlign"      , P[ind].Altura );
P[ind].Vspeed        = backend_get_config_float (P[ind].State_s, "Vspeed"      ,          0 );
P[ind].Hspeed        = backend_get_config_float (P[ind].State_s, "Hspeed"      ,          0 );
P[ind].Gravity       = backend_get_config_float (P[ind].State_s, "Gravity"     ,          0 );
P[ind].Friction      = backend_get_config_float (P[ind].State_s, "Friction"    ,          0 );
P[ind].Energy       += backend_get_config_int  (P[ind].State_s, "Energy"       ,          0 );
P[ind].Special      += backend_get_config_int  (P[ind].State_s, "Special"      ,          0 );
P[ind].EnergyChange  = backend_get_config_int  (P[ind].State_s, "EnergyChange" ,          0 );
P[ind].SpecialChange = backend_get_config_int  (P[ind].State_s, "SpecialChange",          0 );
P[ind].Visible       = backend_get_config_int  (P[ind].State_s, "Visible"      ,          1 );
P[ind].RoomLimit     = backend_get_config_int  (P[ind].State_s, "RoomLimit"    ,          1 );
strcpy(P[ind].HitType, (char *)backend_get_config_string(P[ind].State_s, "HitType","Normal"));
strcpy(P[ind].HitStack, (char *)backend_get_config_string(P[ind].State_s, "HitStack","Multi"));
P[ind].HitPause      = backend_get_config_int  (P[ind].State_s, "HitPause"     ,          0 );
P[ind].ChangeState   = backend_get_config_int  (P[ind].State_s, "ChangeState"  ,          0 );
P[ind].Freeze        = backend_get_config_int  (P[ind].State_s, "Freeze"       ,          0 );
P[ind].Color         = backend_get_config_int  (P[ind].State_s, "Color"        ,         -1 );
P[ind].TotalFrames   = backend_get_config_int  (P[ind].State_s, "TotalFrames"  , QtdeFrames );
if(ind==1){
if(ForcaDoGolpeP1==1){ P[1].ChangeDamage = backend_get_config_int (P[1].State_s, "V1_Damage",  0 ); }
if(ForcaDoGolpeP1==2){ P[1].ChangeDamage = backend_get_config_int (P[1].State_s, "V2_Damage",  0 ); }
if(ForcaDoGolpeP1==3){ P[1].ChangeDamage = backend_get_config_int (P[1].State_s, "V3_Damage",  0 ); }
}
if(ind==2){
if(ForcaDoGolpeP2==1){ P[2].ChangeDamage = backend_get_config_int (P[2].State_s, "V1_Damage",  0 ); }
if(ForcaDoGolpeP2==2){ P[2].ChangeDamage = backend_get_config_int (P[2].State_s, "V2_Damage",  0 ); }
if(ForcaDoGolpeP2==3){ P[2].ChangeDamage = backend_get_config_int (P[2].State_s, "V3_Damage",  0 ); }
}
}

/*
	//debug - caso especial, char vazio
	if (strcmp (P[ind].Name_Display,"-")==0){
	backend_message("Char Empty");
	}
*/

}

///////////////////////////////////////////////////////////////////////////////
// DESENHA HIT e COLISION BOXES -----------------------------------------------
///////////////////////////////////////////////////////////////////////////////

void Draw_CHBoxes_P1()
{
P1_HitBox01x1=-5555; P1_HitBox01y1=-5555; P1_HitBox01x2=-5555; P1_HitBox01y2=-5555;
P1_HitBox02x1=-5555; P1_HitBox02y1=-5555; P1_HitBox02x2=-5555; P1_HitBox02y2=-5555;
P1_HitBox03x1=-5555; P1_HitBox03y1=-5555; P1_HitBox03x2=-5555; P1_HitBox03y2=-5555;
P1_HitBox04x1=-5555; P1_HitBox04y1=-5555; P1_HitBox04x2=-5555; P1_HitBox04y2=-5555;
P1_HitBox05x1=-5555; P1_HitBox05y1=-5555; P1_HitBox05x2=-5555; P1_HitBox05y2=-5555;
P1_HitBox06x1=-5555; P1_HitBox06y1=-5555; P1_HitBox06x2=-5555; P1_HitBox06y2=-5555;
P1_HitBox07x1=-5555; P1_HitBox07y1=-5555; P1_HitBox07x2=-5555; P1_HitBox07y2=-5555;
P1_HitBox08x1=-5555; P1_HitBox08y1=-5555; P1_HitBox08x2=-5555; P1_HitBox08y2=-5555;
P1_HitBox09x1=-5555; P1_HitBox09y1=-5555; P1_HitBox09x2=-5555; P1_HitBox09y2=-5555;
P1_HurtBox01x1=-5555; P1_HurtBox01y1=-5555; P1_HurtBox01x2=-5555; P1_HurtBox01y2=-5555;
P1_HurtBox02x1=-5555; P1_HurtBox02y1=-5555; P1_HurtBox02x2=-5555; P1_HurtBox02y2=-5555;
P1_HurtBox03x1=-5555; P1_HurtBox03y1=-5555; P1_HurtBox03x2=-5555; P1_HurtBox03y2=-5555;
P1_HurtBox04x1=-5555; P1_HurtBox04y1=-5555; P1_HurtBox04x2=-5555; P1_HurtBox04y2=-5555;
P1_HurtBox05x1=-5555; P1_HurtBox05y1=-5555; P1_HurtBox05x2=-5555; P1_HurtBox05y2=-5555;
P1_HurtBox06x1=-5555; P1_HurtBox06y1=-5555; P1_HurtBox06x2=-5555; P1_HurtBox06y2=-5555;
P1_HurtBox07x1=-5555; P1_HurtBox07y1=-5555; P1_HurtBox07x2=-5555; P1_HurtBox07y2=-5555;
P1_HurtBox08x1=-5555; P1_HurtBox08y1=-5555; P1_HurtBox08x2=-5555; P1_HurtBox08y2=-5555;
P1_HurtBox09x1=-5555; P1_HurtBox09y1=-5555; P1_HurtBox09x2=-5555; P1_HurtBox09y2=-5555;
P1_HurtBox_tot=0; P1_HitBox_tot=0;

sprintf(P[1].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[1].Name);
if (P[1].IndexAnim<10)  { sprintf(P[1].State_chs, "%i_0%i", P[1].State, P[1].IndexAnim); }
if (P[1].IndexAnim>=10) { sprintf(P[1].State_chs, "%i_%i", P[1].State, P[1].IndexAnim); }

backend_set_config_file(P[1].Caminho_CHBOX);
P1_HitBox01x1 = backend_get_config_int (P[1].State_chs, "HitBox01x1", -5555 ); if (P1_HitBox01x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox01y1 = backend_get_config_int (P[1].State_chs, "HitBox01y1", -5555 );
P1_HitBox01x2 = backend_get_config_int (P[1].State_chs, "HitBox01x2", -5555 );
P1_HitBox01y2 = backend_get_config_int (P[1].State_chs, "HitBox01y2", -5555 );
P1_HitBox02x1 = backend_get_config_int (P[1].State_chs, "HitBox02x1", -5555 ); if (P1_HitBox02x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox02y1 = backend_get_config_int (P[1].State_chs, "HitBox02y1", -5555 );
P1_HitBox02x2 = backend_get_config_int (P[1].State_chs, "HitBox02x2", -5555 );
P1_HitBox02y2 = backend_get_config_int (P[1].State_chs, "HitBox02y2", -5555 );
P1_HitBox03x1 = backend_get_config_int (P[1].State_chs, "HitBox03x1", -5555 ); if (P1_HitBox03x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox03y1 = backend_get_config_int (P[1].State_chs, "HitBox03y1", -5555 );
P1_HitBox03x2 = backend_get_config_int (P[1].State_chs, "HitBox03x2", -5555 );
P1_HitBox03y2 = backend_get_config_int (P[1].State_chs, "HitBox03y2", -5555 );
P1_HitBox04x1 = backend_get_config_int (P[1].State_chs, "HitBox04x1", -5555 ); if (P1_HitBox04x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox04y1 = backend_get_config_int (P[1].State_chs, "HitBox04y1", -5555 );
P1_HitBox04x2 = backend_get_config_int (P[1].State_chs, "HitBox04x2", -5555 );
P1_HitBox04y2 = backend_get_config_int (P[1].State_chs, "HitBox04y2", -5555 );
P1_HitBox05x1 = backend_get_config_int (P[1].State_chs, "HitBox05x1", -5555 ); if (P1_HitBox05x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox05y1 = backend_get_config_int (P[1].State_chs, "HitBox05y1", -5555 );
P1_HitBox05x2 = backend_get_config_int (P[1].State_chs, "HitBox05x2", -5555 );
P1_HitBox05y2 = backend_get_config_int (P[1].State_chs, "HitBox05y2", -5555 );
P1_HitBox06x1 = backend_get_config_int (P[1].State_chs, "HitBox06x1", -5555 ); if (P1_HitBox06x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox06y1 = backend_get_config_int (P[1].State_chs, "HitBox06y1", -5555 );
P1_HitBox06x2 = backend_get_config_int (P[1].State_chs, "HitBox06x2", -5555 );
P1_HitBox06y2 = backend_get_config_int (P[1].State_chs, "HitBox06y2", -5555 );
P1_HitBox07x1 = backend_get_config_int (P[1].State_chs, "HitBox07x1", -5555 ); if (P1_HitBox07x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox07y1 = backend_get_config_int (P[1].State_chs, "HitBox07y1", -5555 );
P1_HitBox07x2 = backend_get_config_int (P[1].State_chs, "HitBox07x2", -5555 );
P1_HitBox07y2 = backend_get_config_int (P[1].State_chs, "HitBox07y2", -5555 );
P1_HitBox08x1 = backend_get_config_int (P[1].State_chs, "HitBox08x1", -5555 ); if (P1_HitBox08x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox08y1 = backend_get_config_int (P[1].State_chs, "HitBox08y1", -5555 );
P1_HitBox08x2 = backend_get_config_int (P[1].State_chs, "HitBox08x2", -5555 );
P1_HitBox08y2 = backend_get_config_int (P[1].State_chs, "HitBox08y2", -5555 );
P1_HitBox09x1 = backend_get_config_int (P[1].State_chs, "HitBox09x1", -5555 ); if (P1_HitBox09x1!=-5555) { P1_HitBox_tot++; }
P1_HitBox09y1 = backend_get_config_int (P[1].State_chs, "HitBox09y1", -5555 );
P1_HitBox09x2 = backend_get_config_int (P[1].State_chs, "HitBox09x2", -5555 );
P1_HitBox09y2 = backend_get_config_int (P[1].State_chs, "HitBox09y2", -5555 );
P1_HurtBox01x1 = backend_get_config_int (P[1].State_chs, "HurtBox01x1", -5555 ); if (P1_HurtBox01x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox01y1 = backend_get_config_int (P[1].State_chs, "HurtBox01y1", -5555 );
P1_HurtBox01x2 = backend_get_config_int (P[1].State_chs, "HurtBox01x2", -5555 );
P1_HurtBox01y2 = backend_get_config_int (P[1].State_chs, "HurtBox01y2", -5555 );
P1_HurtBox02x1 = backend_get_config_int (P[1].State_chs, "HurtBox02x1", -5555 ); if (P1_HurtBox02x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox02y1 = backend_get_config_int (P[1].State_chs, "HurtBox02y1", -5555 );
P1_HurtBox02x2 = backend_get_config_int (P[1].State_chs, "HurtBox02x2", -5555 );
P1_HurtBox02y2 = backend_get_config_int (P[1].State_chs, "HurtBox02y2", -5555 );
P1_HurtBox03x1 = backend_get_config_int (P[1].State_chs, "HurtBox03x1", -5555 ); if (P1_HurtBox03x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox03y1 = backend_get_config_int (P[1].State_chs, "HurtBox03y1", -5555 );
P1_HurtBox03x2 = backend_get_config_int (P[1].State_chs, "HurtBox03x2", -5555 );
P1_HurtBox03y2 = backend_get_config_int (P[1].State_chs, "HurtBox03y2", -5555 );
P1_HurtBox04x1 = backend_get_config_int (P[1].State_chs, "HurtBox04x1", -5555 ); if (P1_HurtBox04x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox04y1 = backend_get_config_int (P[1].State_chs, "HurtBox04y1", -5555 );
P1_HurtBox04x2 = backend_get_config_int (P[1].State_chs, "HurtBox04x2", -5555 );
P1_HurtBox04y2 = backend_get_config_int (P[1].State_chs, "HurtBox04y2", -5555 );
P1_HurtBox05x1 = backend_get_config_int (P[1].State_chs, "HurtBox05x1", -5555 ); if (P1_HurtBox05x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox05y1 = backend_get_config_int (P[1].State_chs, "HurtBox05y1", -5555 );
P1_HurtBox05x2 = backend_get_config_int (P[1].State_chs, "HurtBox05x2", -5555 );
P1_HurtBox05y2 = backend_get_config_int (P[1].State_chs, "HurtBox05y2", -5555 );
P1_HurtBox06x1 = backend_get_config_int (P[1].State_chs, "HurtBox06x1", -5555 ); if (P1_HurtBox06x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox06y1 = backend_get_config_int (P[1].State_chs, "HurtBox06y1", -5555 );
P1_HurtBox06x2 = backend_get_config_int (P[1].State_chs, "HurtBox06x2", -5555 );
P1_HurtBox06y2 = backend_get_config_int (P[1].State_chs, "HurtBox06y2", -5555 );
P1_HurtBox07x1 = backend_get_config_int (P[1].State_chs, "HurtBox07x1", -5555 ); if (P1_HurtBox07x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox07y1 = backend_get_config_int (P[1].State_chs, "HurtBox07y1", -5555 );
P1_HurtBox07x2 = backend_get_config_int (P[1].State_chs, "HurtBox07x2", -5555 );
P1_HurtBox07y2 = backend_get_config_int (P[1].State_chs, "HurtBox07y2", -5555 );
P1_HurtBox08x1 = backend_get_config_int (P[1].State_chs, "HurtBox08x1", -5555 ); if (P1_HurtBox08x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox08y1 = backend_get_config_int (P[1].State_chs, "HurtBox08y1", -5555 );
P1_HurtBox08x2 = backend_get_config_int (P[1].State_chs, "HurtBox08x2", -5555 );
P1_HurtBox08y2 = backend_get_config_int (P[1].State_chs, "HurtBox08y2", -5555 );
P1_HurtBox09x1 = backend_get_config_int (P[1].State_chs, "HurtBox09x1", -5555 ); if (P1_HurtBox09x1!=-5555) { P1_HurtBox_tot++; }
P1_HurtBox09y1 = backend_get_config_int (P[1].State_chs, "HurtBox09y1", -5555 );
P1_HurtBox09x2 = backend_get_config_int (P[1].State_chs, "HurtBox09x2", -5555 );
P1_HurtBox09y2 = backend_get_config_int (P[1].State_chs, "HurtBox09y2", -5555 );
}

void Draw_CHBoxes_P2()
{
P2_HitBox01x1=+5555; P2_HitBox01y1=+5555; P2_HitBox01x2=+5555; P2_HitBox01y2=+5555;
P2_HitBox02x1=+5555; P2_HitBox02y1=+5555; P2_HitBox02x2=+5555; P2_HitBox02y2=+5555;
P2_HitBox03x1=+5555; P2_HitBox03y1=+5555; P2_HitBox03x2=+5555; P2_HitBox03y2=+5555;
P2_HitBox04x1=+5555; P2_HitBox04y1=+5555; P2_HitBox04x2=+5555; P2_HitBox04y2=+5555;
P2_HitBox05x1=+5555; P2_HitBox05y1=+5555; P2_HitBox05x2=+5555; P2_HitBox05y2=+5555;
P2_HitBox06x1=+5555; P2_HitBox06y1=+5555; P2_HitBox06x2=+5555; P2_HitBox06y2=+5555;
P2_HitBox07x1=+5555; P2_HitBox07y1=+5555; P2_HitBox07x2=+5555; P2_HitBox07y2=+5555;
P2_HitBox08x1=+5555; P2_HitBox08y1=+5555; P2_HitBox08x2=+5555; P2_HitBox08y2=+5555;
P2_HitBox09x1=+5555; P2_HitBox09y1=+5555; P2_HitBox09x2=+5555; P2_HitBox09y2=+5555;
P2_HurtBox01x1=+5555; P2_HurtBox01y1=+5555; P2_HurtBox01x2=+5555; P2_HurtBox01y2=+5555;
P2_HurtBox02x1=+5555; P2_HurtBox02y1=+5555; P2_HurtBox02x2=+5555; P2_HurtBox02y2=+5555;
P2_HurtBox03x1=+5555; P2_HurtBox03y1=+5555; P2_HurtBox03x2=+5555; P2_HurtBox03y2=+5555;
P2_HurtBox04x1=+5555; P2_HurtBox04y1=+5555; P2_HurtBox04x2=+5555; P2_HurtBox04y2=+5555;
P2_HurtBox05x1=+5555; P2_HurtBox05y1=+5555; P2_HurtBox05x2=+5555; P2_HurtBox05y2=+5555;
P2_HurtBox06x1=+5555; P2_HurtBox06y1=+5555; P2_HurtBox06x2=+5555; P2_HurtBox06y2=+5555;
P2_HurtBox07x1=+5555; P2_HurtBox07y1=+5555; P2_HurtBox07x2=+5555; P2_HurtBox07y2=+5555;
P2_HurtBox08x1=+5555; P2_HurtBox08y1=+5555; P2_HurtBox08x2=+5555; P2_HurtBox08y2=+5555;
P2_HurtBox09x1=+5555; P2_HurtBox09y1=+5555; P2_HurtBox09x2=+5555; P2_HurtBox09y2=+5555;
P2_HurtBox_tot=0; P2_HitBox_tot=0;

sprintf(P[2].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[2].Name);
if (P[2].IndexAnim<10)  { sprintf(P[2].State_chs, "%i_0%i", P[2].State, P[2].IndexAnim); }
if (P[2].IndexAnim>=10) { sprintf(P[2].State_chs, "%i_%i", P[2].State, P[2].IndexAnim); }

backend_set_config_file(P[2].Caminho_CHBOX);
P2_HitBox01x1 = backend_get_config_int (P[2].State_chs, "HitBox01x1", +5555 ); if (P2_HitBox01x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox01y1 = backend_get_config_int (P[2].State_chs, "HitBox01y1", +5555 );
P2_HitBox01x2 = backend_get_config_int (P[2].State_chs, "HitBox01x2", +5555 );
P2_HitBox01y2 = backend_get_config_int (P[2].State_chs, "HitBox01y2", +5555 );
P2_HitBox02x1 = backend_get_config_int (P[2].State_chs, "HitBox02x1", +5555 ); if (P2_HitBox02x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox02y1 = backend_get_config_int (P[2].State_chs, "HitBox02y1", +5555 );
P2_HitBox02x2 = backend_get_config_int (P[2].State_chs, "HitBox02x2", +5555 );
P2_HitBox02y2 = backend_get_config_int (P[2].State_chs, "HitBox02y2", +5555 );
P2_HitBox03x1 = backend_get_config_int (P[2].State_chs, "HitBox03x1", +5555 ); if (P2_HitBox03x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox03y1 = backend_get_config_int (P[2].State_chs, "HitBox03y1", +5555 );
P2_HitBox03x2 = backend_get_config_int (P[2].State_chs, "HitBox03x2", +5555 );
P2_HitBox03y2 = backend_get_config_int (P[2].State_chs, "HitBox03y2", +5555 );
P2_HitBox04x1 = backend_get_config_int (P[2].State_chs, "HitBox04x1", +5555 ); if (P2_HitBox04x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox04y1 = backend_get_config_int (P[2].State_chs, "HitBox04y1", +5555 );
P2_HitBox04x2 = backend_get_config_int (P[2].State_chs, "HitBox04x2", +5555 );
P2_HitBox04y2 = backend_get_config_int (P[2].State_chs, "HitBox04y2", +5555 );
P2_HitBox05x1 = backend_get_config_int (P[2].State_chs, "HitBox05x1", +5555 ); if (P2_HitBox05x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox05y1 = backend_get_config_int (P[2].State_chs, "HitBox05y1", +5555 );
P2_HitBox05x2 = backend_get_config_int (P[2].State_chs, "HitBox05x2", +5555 );
P2_HitBox05y2 = backend_get_config_int (P[2].State_chs, "HitBox05y2", +5555 );
P2_HitBox06x1 = backend_get_config_int (P[2].State_chs, "HitBox06x1", +5555 ); if (P2_HitBox06x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox06y1 = backend_get_config_int (P[2].State_chs, "HitBox06y1", +5555 );
P2_HitBox06x2 = backend_get_config_int (P[2].State_chs, "HitBox06x2", +5555 );
P2_HitBox06y2 = backend_get_config_int (P[2].State_chs, "HitBox06y2", +5555 );
P2_HitBox07x1 = backend_get_config_int (P[2].State_chs, "HitBox07x1", +5555 ); if (P2_HitBox07x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox07y1 = backend_get_config_int (P[2].State_chs, "HitBox07y1", +5555 );
P2_HitBox07x2 = backend_get_config_int (P[2].State_chs, "HitBox07x2", +5555 );
P2_HitBox07y2 = backend_get_config_int (P[2].State_chs, "HitBox07y2", +5555 );
P2_HitBox08x1 = backend_get_config_int (P[2].State_chs, "HitBox08x1", +5555 ); if (P2_HitBox08x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox08y1 = backend_get_config_int (P[2].State_chs, "HitBox08y1", +5555 );
P2_HitBox08x2 = backend_get_config_int (P[2].State_chs, "HitBox08x2", +5555 );
P2_HitBox08y2 = backend_get_config_int (P[2].State_chs, "HitBox08y2", +5555 );
P2_HitBox09x1 = backend_get_config_int (P[2].State_chs, "HitBox09x1", +5555 ); if (P2_HitBox09x1!=+5555) { P2_HitBox_tot++; }
P2_HitBox09y1 = backend_get_config_int (P[2].State_chs, "HitBox09y1", +5555 );
P2_HitBox09x2 = backend_get_config_int (P[2].State_chs, "HitBox09x2", +5555 );
P2_HitBox09y2 = backend_get_config_int (P[2].State_chs, "HitBox09y2", +5555 );
P2_HurtBox01x1 = backend_get_config_int (P[2].State_chs, "HurtBox01x1", +5555 ); if (P2_HurtBox01x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox01y1 = backend_get_config_int (P[2].State_chs, "HurtBox01y1", +5555 );
P2_HurtBox01x2 = backend_get_config_int (P[2].State_chs, "HurtBox01x2", +5555 );
P2_HurtBox01y2 = backend_get_config_int (P[2].State_chs, "HurtBox01y2", +5555 );
P2_HurtBox02x1 = backend_get_config_int (P[2].State_chs, "HurtBox02x1", +5555 ); if (P2_HurtBox02x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox02y1 = backend_get_config_int (P[2].State_chs, "HurtBox02y1", +5555 );
P2_HurtBox02x2 = backend_get_config_int (P[2].State_chs, "HurtBox02x2", +5555 );
P2_HurtBox02y2 = backend_get_config_int (P[2].State_chs, "HurtBox02y2", +5555 );
P2_HurtBox03x1 = backend_get_config_int (P[2].State_chs, "HurtBox03x1", +5555 ); if (P2_HurtBox03x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox03y1 = backend_get_config_int (P[2].State_chs, "HurtBox03y1", +5555 );
P2_HurtBox03x2 = backend_get_config_int (P[2].State_chs, "HurtBox03x2", +5555 );
P2_HurtBox03y2 = backend_get_config_int (P[2].State_chs, "HurtBox03y2", +5555 );
P2_HurtBox04x1 = backend_get_config_int (P[2].State_chs, "HurtBox04x1", +5555 ); if (P2_HurtBox04x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox04y1 = backend_get_config_int (P[2].State_chs, "HurtBox04y1", +5555 );
P2_HurtBox04x2 = backend_get_config_int (P[2].State_chs, "HurtBox04x2", +5555 );
P2_HurtBox04y2 = backend_get_config_int (P[2].State_chs, "HurtBox04y2", +5555 );
P2_HurtBox05x1 = backend_get_config_int (P[2].State_chs, "HurtBox05x1", +5555 ); if (P2_HurtBox05x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox05y1 = backend_get_config_int (P[2].State_chs, "HurtBox05y1", +5555 );
P2_HurtBox05x2 = backend_get_config_int (P[2].State_chs, "HurtBox05x2", +5555 );
P2_HurtBox05y2 = backend_get_config_int (P[2].State_chs, "HurtBox05y2", +5555 );
P2_HurtBox06x1 = backend_get_config_int (P[2].State_chs, "HurtBox06x1", +5555 ); if (P2_HurtBox06x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox06y1 = backend_get_config_int (P[2].State_chs, "HurtBox06y1", +5555 );
P2_HurtBox06x2 = backend_get_config_int (P[2].State_chs, "HurtBox06x2", +5555 );
P2_HurtBox06y2 = backend_get_config_int (P[2].State_chs, "HurtBox06y2", +5555 );
P2_HurtBox07x1 = backend_get_config_int (P[2].State_chs, "HurtBox07x1", +5555 ); if (P2_HurtBox07x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox07y1 = backend_get_config_int (P[2].State_chs, "HurtBox07y1", +5555 );
P2_HurtBox07x2 = backend_get_config_int (P[2].State_chs, "HurtBox07x2", +5555 );
P2_HurtBox07y2 = backend_get_config_int (P[2].State_chs, "HurtBox07y2", +5555 );
P2_HurtBox08x1 = backend_get_config_int (P[2].State_chs, "HurtBox08x1", +5555 ); if (P2_HurtBox08x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox08y1 = backend_get_config_int (P[2].State_chs, "HurtBox08y1", +5555 );
P2_HurtBox08x2 = backend_get_config_int (P[2].State_chs, "HurtBox08x2", +5555 );
P2_HurtBox08y2 = backend_get_config_int (P[2].State_chs, "HurtBox08y2", +5555 );
P2_HurtBox09x1 = backend_get_config_int (P[2].State_chs, "HurtBox09x1", +5555 ); if (P2_HurtBox09x1!=+5555) { P2_HurtBox_tot++; }
P2_HurtBox09y1 = backend_get_config_int (P[2].State_chs, "HurtBox09y1", +5555 );
P2_HurtBox09x2 = backend_get_config_int (P[2].State_chs, "HurtBox09x2", +5555 );
P2_HurtBox09y2 = backend_get_config_int (P[2].State_chs, "HurtBox09y2", +5555 );
}

void Draw_CHBoxes_ED()
{
ED_HitBox01x1=-1; ED_HitBox01y1=-1; ED_HitBox01x2=-1; ED_HitBox01y2=-1;
ED_HitBox02x1=-1; ED_HitBox02y1=-1; ED_HitBox02x2=-1; ED_HitBox02y2=-1;
ED_HitBox03x1=-1; ED_HitBox03y1=-1; ED_HitBox03x2=-1; ED_HitBox03y2=-1;
ED_HitBox04x1=-1; ED_HitBox04y1=-1; ED_HitBox04x2=-1; ED_HitBox04y2=-1;
ED_HitBox05x1=-1; ED_HitBox05y1=-1; ED_HitBox05x2=-1; ED_HitBox05y2=-1;
ED_HitBox06x1=-1; ED_HitBox06y1=-1; ED_HitBox06x2=-1; ED_HitBox06y2=-1;
ED_HitBox07x1=-1; ED_HitBox07y1=-1; ED_HitBox07x2=-1; ED_HitBox07y2=-1;
ED_HitBox08x1=-1; ED_HitBox08y1=-1; ED_HitBox08x2=-1; ED_HitBox08y2=-1;
ED_HitBox09x1=-1; ED_HitBox09y1=-1; ED_HitBox09x2=-1; ED_HitBox09y2=-1;
ED_HurtBox01x1=-1; ED_HurtBox01y1=-1; ED_HurtBox01x2=-1; ED_HurtBox01y2=-1;
ED_HurtBox02x1=-1; ED_HurtBox02y1=-1; ED_HurtBox02x2=-1; ED_HurtBox02y2=-1;
ED_HurtBox03x1=-1; ED_HurtBox03y1=-1; ED_HurtBox03x2=-1; ED_HurtBox03y2=-1;
ED_HurtBox04x1=-1; ED_HurtBox04y1=-1; ED_HurtBox04x2=-1; ED_HurtBox04y2=-1;
ED_HurtBox05x1=-1; ED_HurtBox05y1=-1; ED_HurtBox05x2=-1; ED_HurtBox05y2=-1;
ED_HurtBox06x1=-1; ED_HurtBox06y1=-1; ED_HurtBox06x2=-1; ED_HurtBox06y2=-1;
ED_HurtBox07x1=-1; ED_HurtBox07y1=-1; ED_HurtBox07x2=-1; ED_HurtBox07y2=-1;
ED_HurtBox08x1=-1; ED_HurtBox08y1=-1; ED_HurtBox08x2=-1; ED_HurtBox08y2=-1;
ED_HurtBox09x1=-1; ED_HurtBox09y1=-1; ED_HurtBox09x2=-1; ED_HurtBox09y2=-1;
ED_HitBox_tot=0; ED_HurtBox_tot=0;

char ED_Caminho_CHBOX[99];
char ED_State_chs[99];
sprintf(ED_Caminho_CHBOX, "data/chars/%s/chbox.ini", ED_Name);
if (ED_IndexAnim<10)  { sprintf(ED_State_chs, "%i_0%i", ED_State, ED_IndexAnim); }
if (ED_IndexAnim>=10) { sprintf(ED_State_chs, "%i_%i", ED_State, ED_IndexAnim); }

backend_set_config_file(ED_Caminho_CHBOX);
ED_HitBox01x1 = backend_get_config_int (ED_State_chs, "HitBox01x1", -5555 ); if (ED_HitBox01x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox01y1 = backend_get_config_int (ED_State_chs, "HitBox01y1", -5555 );
ED_HitBox01x2 = backend_get_config_int (ED_State_chs, "HitBox01x2", -5555 );
ED_HitBox01y2 = backend_get_config_int (ED_State_chs, "HitBox01y2", -5555 );
ED_HitBox02x1 = backend_get_config_int (ED_State_chs, "HitBox02x1", -5555 ); if (ED_HitBox02x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox02y1 = backend_get_config_int (ED_State_chs, "HitBox02y1", -5555 );
ED_HitBox02x2 = backend_get_config_int (ED_State_chs, "HitBox02x2", -5555 );
ED_HitBox02y2 = backend_get_config_int (ED_State_chs, "HitBox02y2", -5555 );
ED_HitBox03x1 = backend_get_config_int (ED_State_chs, "HitBox03x1", -5555 ); if (ED_HitBox03x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox03y1 = backend_get_config_int (ED_State_chs, "HitBox03y1", -5555 );
ED_HitBox03x2 = backend_get_config_int (ED_State_chs, "HitBox03x2", -5555 );
ED_HitBox03y2 = backend_get_config_int (ED_State_chs, "HitBox03y2", -5555 );
ED_HitBox04x1 = backend_get_config_int (ED_State_chs, "HitBox04x1", -5555 ); if (ED_HitBox04x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox04y1 = backend_get_config_int (ED_State_chs, "HitBox04y1", -5555 );
ED_HitBox04x2 = backend_get_config_int (ED_State_chs, "HitBox04x2", -5555 );
ED_HitBox04y2 = backend_get_config_int (ED_State_chs, "HitBox04y2", -5555 );
ED_HitBox05x1 = backend_get_config_int (ED_State_chs, "HitBox05x1", -5555 ); if (ED_HitBox05x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox05y1 = backend_get_config_int (ED_State_chs, "HitBox05y1", -5555 );
ED_HitBox05x2 = backend_get_config_int (ED_State_chs, "HitBox05x2", -5555 );
ED_HitBox05y2 = backend_get_config_int (ED_State_chs, "HitBox05y2", -5555 );
ED_HitBox06x1 = backend_get_config_int (ED_State_chs, "HitBox06x1", -5555 ); if (ED_HitBox06x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox06y1 = backend_get_config_int (ED_State_chs, "HitBox06y1", -5555 );
ED_HitBox06x2 = backend_get_config_int (ED_State_chs, "HitBox06x2", -5555 );
ED_HitBox06y2 = backend_get_config_int (ED_State_chs, "HitBox06y2", -5555 );
ED_HitBox07x1 = backend_get_config_int (ED_State_chs, "HitBox07x1", -5555 ); if (ED_HitBox07x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox07y1 = backend_get_config_int (ED_State_chs, "HitBox07y1", -5555 );
ED_HitBox07x2 = backend_get_config_int (ED_State_chs, "HitBox07x2", -5555 );
ED_HitBox07y2 = backend_get_config_int (ED_State_chs, "HitBox07y2", -5555 );
ED_HitBox08x1 = backend_get_config_int (ED_State_chs, "HitBox08x1", -5555 ); if (ED_HitBox08x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox08y1 = backend_get_config_int (ED_State_chs, "HitBox08y1", -5555 );
ED_HitBox08x2 = backend_get_config_int (ED_State_chs, "HitBox08x2", -5555 );
ED_HitBox08y2 = backend_get_config_int (ED_State_chs, "HitBox08y2", -5555 );
ED_HitBox09x1 = backend_get_config_int (ED_State_chs, "HitBox09x1", -5555 ); if (ED_HitBox09x1!=-5555) {ED_HitBox_tot++;}
ED_HitBox09y1 = backend_get_config_int (ED_State_chs, "HitBox09y1", -5555 );
ED_HitBox09x2 = backend_get_config_int (ED_State_chs, "HitBox09x2", -5555 );
ED_HitBox09y2 = backend_get_config_int (ED_State_chs, "HitBox09y2", -5555 );
ED_HurtBox01x1 = backend_get_config_int (ED_State_chs, "HurtBox01x1", -5555 ); if (ED_HurtBox01x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox01y1 = backend_get_config_int (ED_State_chs, "HurtBox01y1", -5555 );
ED_HurtBox01x2 = backend_get_config_int (ED_State_chs, "HurtBox01x2", -5555 );
ED_HurtBox01y2 = backend_get_config_int (ED_State_chs, "HurtBox01y2", -5555 );
ED_HurtBox02x1 = backend_get_config_int (ED_State_chs, "HurtBox02x1", -5555 ); if (ED_HurtBox02x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox02y1 = backend_get_config_int (ED_State_chs, "HurtBox02y1", -5555 );
ED_HurtBox02x2 = backend_get_config_int (ED_State_chs, "HurtBox02x2", -5555 );
ED_HurtBox02y2 = backend_get_config_int (ED_State_chs, "HurtBox02y2", -5555 );
ED_HurtBox03x1 = backend_get_config_int (ED_State_chs, "HurtBox03x1", -5555 ); if (ED_HurtBox03x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox03y1 = backend_get_config_int (ED_State_chs, "HurtBox03y1", -5555 );
ED_HurtBox03x2 = backend_get_config_int (ED_State_chs, "HurtBox03x2", -5555 );
ED_HurtBox03y2 = backend_get_config_int (ED_State_chs, "HurtBox03y2", -5555 );
ED_HurtBox04x1 = backend_get_config_int (ED_State_chs, "HurtBox04x1", -5555 ); if (ED_HurtBox04x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox04y1 = backend_get_config_int (ED_State_chs, "HurtBox04y1", -5555 );
ED_HurtBox04x2 = backend_get_config_int (ED_State_chs, "HurtBox04x2", -5555 );
ED_HurtBox04y2 = backend_get_config_int (ED_State_chs, "HurtBox04y2", -5555 );
ED_HurtBox05x1 = backend_get_config_int (ED_State_chs, "HurtBox05x1", -5555 ); if (ED_HurtBox05x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox05y1 = backend_get_config_int (ED_State_chs, "HurtBox05y1", -5555 );
ED_HurtBox05x2 = backend_get_config_int (ED_State_chs, "HurtBox05x2", -5555 );
ED_HurtBox05y2 = backend_get_config_int (ED_State_chs, "HurtBox05y2", -5555 );
ED_HurtBox06x1 = backend_get_config_int (ED_State_chs, "HurtBox06x1", -5555 ); if (ED_HurtBox06x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox06y1 = backend_get_config_int (ED_State_chs, "HurtBox06y1", -5555 );
ED_HurtBox06x2 = backend_get_config_int (ED_State_chs, "HurtBox06x2", -5555 );
ED_HurtBox06y2 = backend_get_config_int (ED_State_chs, "HurtBox06y2", -5555 );
ED_HurtBox07x1 = backend_get_config_int (ED_State_chs, "HurtBox07x1", -5555 ); if (ED_HurtBox07x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox07y1 = backend_get_config_int (ED_State_chs, "HurtBox07y1", -5555 );
ED_HurtBox07x2 = backend_get_config_int (ED_State_chs, "HurtBox07x2", -5555 );
ED_HurtBox07y2 = backend_get_config_int (ED_State_chs, "HurtBox07y2", -5555 );
ED_HurtBox08x1 = backend_get_config_int (ED_State_chs, "HurtBox08x1", -5555 ); if (ED_HurtBox08x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox08y1 = backend_get_config_int (ED_State_chs, "HurtBox08y1", -5555 );
ED_HurtBox08x2 = backend_get_config_int (ED_State_chs, "HurtBox08x2", -5555 );
ED_HurtBox08y2 = backend_get_config_int (ED_State_chs, "HurtBox08y2", -5555 );
ED_HurtBox09x1 = backend_get_config_int (ED_State_chs, "HurtBox09x1", -5555 ); if (ED_HurtBox09x1!=-5555) {ED_HurtBox_tot++;}
ED_HurtBox09y1 = backend_get_config_int (ED_State_chs, "HurtBox09y1", -5555 );
ED_HurtBox09x2 = backend_get_config_int (ED_State_chs, "HurtBox09x2", -5555 );
ED_HurtBox09y2 = backend_get_config_int (ED_State_chs, "HurtBox09y2", -5555 );
}

///////////////////////////////////////////////////////////////////////////////
// CHECAR COLISAO -------------------------------------------------------[**04]
///////////////////////////////////////////////////////////////////////////////

void Checar_Colisao(){
//INICIALIZACAO DE VARIAVEIS
colisaoxP1=0; alturadohitp1=0;
colisaoxP2=0; alturadohitp2=0;
int P1hb_HurtBox01x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x1)*2;
int P1hb_HurtBox01x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x2)*2;
int P1hb_HurtBox01y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox01y1*2);
int P1hb_HurtBox01y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox01y2*2);
int P1hb_HurtBox02x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox02x1)*2;
int P1hb_HurtBox02x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox02x2)*2;
int P1hb_HurtBox02y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox02y1*2);
int P1hb_HurtBox02y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox02y2*2);
int P1hb_HurtBox03x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox03x1)*2;
int P1hb_HurtBox03x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox03x2)*2;
int P1hb_HurtBox03y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox03y1*2);
int P1hb_HurtBox03y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox03y2*2);
int P1hb_HurtBox04x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox04x1)*2;
int P1hb_HurtBox04x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox04x2)*2;
int P1hb_HurtBox04y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox04y1*2);
int P1hb_HurtBox04y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox04y2*2);
int P1hb_HurtBox05x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox05x1)*2;
int P1hb_HurtBox05x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox05x2)*2;
int P1hb_HurtBox05y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox05y1*2);
int P1hb_HurtBox05y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox05y2*2);
int P1hb_HurtBox06x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox06x1)*2;
int P1hb_HurtBox06x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox06x2)*2;
int P1hb_HurtBox06y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox06y1*2);
int P1hb_HurtBox06y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox06y2*2);
int P1hb_HurtBox07x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox07x1)*2;
int P1hb_HurtBox07x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox07x2)*2;
int P1hb_HurtBox07y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox07y1*2);
int P1hb_HurtBox07y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox07y2*2);
int P1hb_HurtBox08x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox08x1)*2;
int P1hb_HurtBox08x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox08x2)*2;
int P1hb_HurtBox08y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox08y1*2);
int P1hb_HurtBox08y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox08y2*2);
int P1hb_HurtBox09x1 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox09x1)*2;
int P1hb_HurtBox09x2 = ((P[1].x)*2)+(P[1].Lado*P1_HurtBox09x2)*2;
int P1hb_HurtBox09y1 = (AlturaPiso+(P[1].y*2)+P1_HurtBox09y1*2);
int P1hb_HurtBox09y2 = (AlturaPiso+(P[1].y*2)+P1_HurtBox09y2*2);
int P1hb_HitBox01x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox01x1)*2;
int P1hb_HitBox01x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox01x2)*2;
int P1hb_HitBox01y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox01y1*2);
int P1hb_HitBox01y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox01y2*2);
int P1hb_HitBox02x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox02x1)*2;
int P1hb_HitBox02x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox02x2)*2;
int P1hb_HitBox02y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox02y1*2);
int P1hb_HitBox02y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox02y2*2);
int P1hb_HitBox03x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox03x1)*2;
int P1hb_HitBox03x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox03x2)*2;
int P1hb_HitBox03y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox03y1*2);
int P1hb_HitBox03y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox03y2*2);
int P1hb_HitBox04x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox04x1)*2;
int P1hb_HitBox04x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox04x2)*2;
int P1hb_HitBox04y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox04y1*2);
int P1hb_HitBox04y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox04y2*2);
int P1hb_HitBox05x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox05x1)*2;
int P1hb_HitBox05x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox05x2)*2;
int P1hb_HitBox05y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox05y1*2);
int P1hb_HitBox05y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox05y2*2);
int P1hb_HitBox06x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox06x1)*2;
int P1hb_HitBox06x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox06x2)*2;
int P1hb_HitBox06y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox06y1*2);
int P1hb_HitBox06y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox06y2*2);
int P1hb_HitBox07x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox07x1)*2;
int P1hb_HitBox07x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox07x2)*2;
int P1hb_HitBox07y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox07y1*2);
int P1hb_HitBox07y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox07y2*2);
int P1hb_HitBox08x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox08x1)*2;
int P1hb_HitBox08x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox08x2)*2;
int P1hb_HitBox08y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox08y1*2);
int P1hb_HitBox08y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox08y2*2);
int P1hb_HitBox09x1 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox09x1)*2;
int P1hb_HitBox09x2 = ((P[1].x)*2)+(P[1].Lado*P1_HitBox09x2)*2;
int P1hb_HitBox09y1 = (AlturaPiso+(P[1].y*2)+P1_HitBox09y1*2);
int P1hb_HitBox09y2 = (AlturaPiso+(P[1].y*2)+P1_HitBox09y2*2);

int P2hb_HurtBox01x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x1)*2;
int P2hb_HurtBox01x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x2)*2;
int P2hb_HurtBox01y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox01y1*2);
int P2hb_HurtBox01y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox01y2*2);
int P2hb_HurtBox02x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox02x1)*2;
int P2hb_HurtBox02x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox02x2)*2;
int P2hb_HurtBox02y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox02y1*2);
int P2hb_HurtBox02y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox02y2*2);
int P2hb_HurtBox03x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox03x1)*2;
int P2hb_HurtBox03x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox03x2)*2;
int P2hb_HurtBox03y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox03y1*2);
int P2hb_HurtBox03y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox03y2*2);
int P2hb_HurtBox04x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox04x1)*2;
int P2hb_HurtBox04x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox04x2)*2;
int P2hb_HurtBox04y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox04y1*2);
int P2hb_HurtBox04y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox04y2*2);
int P2hb_HurtBox05x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox05x1)*2;
int P2hb_HurtBox05x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox05x2)*2;
int P2hb_HurtBox05y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox05y1*2);
int P2hb_HurtBox05y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox05y2*2);
int P2hb_HurtBox06x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox06x1)*2;
int P2hb_HurtBox06x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox06x2)*2;
int P2hb_HurtBox06y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox06y1*2);
int P2hb_HurtBox06y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox06y2*2);
int P2hb_HurtBox07x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox07x1)*2;
int P2hb_HurtBox07x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox07x2)*2;
int P2hb_HurtBox07y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox07y1*2);
int P2hb_HurtBox07y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox07y2*2);
int P2hb_HurtBox08x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox08x1)*2;
int P2hb_HurtBox08x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox08x2)*2;
int P2hb_HurtBox08y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox08y1*2);
int P2hb_HurtBox08y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox08y2*2);
int P2hb_HurtBox09x1 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox09x1)*2;
int P2hb_HurtBox09x2 = ((P[2].x)*2)+(P[2].Lado*P2_HurtBox09x2)*2;
int P2hb_HurtBox09y1 = (AlturaPiso+(P[2].y*2)+P2_HurtBox09y1*2);
int P2hb_HurtBox09y2 = (AlturaPiso+(P[2].y*2)+P2_HurtBox09y2*2);
int P2hb_HitBox01x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox01x1)*2;
int P2hb_HitBox01x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox01x2)*2;
int P2hb_HitBox01y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox01y1*2);
int P2hb_HitBox01y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox01y2*2);
int P2hb_HitBox02x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox02x1)*2;
int P2hb_HitBox02x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox02x2)*2;
int P2hb_HitBox02y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox02y1*2);
int P2hb_HitBox02y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox02y2*2);
int P2hb_HitBox03x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox03x1)*2;
int P2hb_HitBox03x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox03x2)*2;
int P2hb_HitBox03y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox03y1*2);
int P2hb_HitBox03y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox03y2*2);
int P2hb_HitBox04x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox04x1)*2;
int P2hb_HitBox04x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox04x2)*2;
int P2hb_HitBox04y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox04y1*2);
int P2hb_HitBox04y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox04y2*2);
int P2hb_HitBox05x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox05x1)*2;
int P2hb_HitBox05x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox05x2)*2;
int P2hb_HitBox05y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox05y1*2);
int P2hb_HitBox05y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox05y2*2);
int P2hb_HitBox06x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox06x1)*2;
int P2hb_HitBox06x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox06x2)*2;
int P2hb_HitBox06y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox06y1*2);
int P2hb_HitBox06y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox06y2*2);
int P2hb_HitBox07x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox07x1)*2;
int P2hb_HitBox07x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox07x2)*2;
int P2hb_HitBox07y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox07y1*2);
int P2hb_HitBox07y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox07y2*2);
int P2hb_HitBox08x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox08x1)*2;
int P2hb_HitBox08x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox08x2)*2;
int P2hb_HitBox08y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox08y1*2);
int P2hb_HitBox08y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox08y2*2);
int P2hb_HitBox09x1 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox09x1)*2;
int P2hb_HitBox09x2 = ((P[2].x)*2)+(P[2].Lado*P2_HitBox09x2)*2;
int P2hb_HitBox09y1 = (AlturaPiso+(P[2].y*2)+P2_HitBox09y1*2);
int P2hb_HitBox09y2 = (AlturaPiso+(P[2].y*2)+P2_HitBox09y2*2);

//Checar Contato Fisico//
//preparacao dos hurt boxes
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x;
} else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; }
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x;
} else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; }
//calcula colisao entre 2 HurtBoxes
if (
P2_HurtBox01x1 !=+5555 && P2_HurtBox01y1 !=+5555 && P2_HurtBox01x2 !=+5555 && P2_HurtBox01y2 !=+5555 &&
P1_HurtBox01x1 !=-5555 && P1_HurtBox01y1 !=-5555 && P1_HurtBox01x2 !=-5555 && P1_HurtBox01y2 !=-5555 ) {
if (
(P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HurtBox01x1) &&
(P1hb_HurtBox01x1<P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HurtBox01y1) &&
(P1hb_HurtBox01y1<P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)) ) {
contatofisico=1;
} else {
contatofisico=0;
}
}
if(P[1].Energy==0 || P[2].Energy==0){ contatofisico=0; }
if(P1_HurtBox01x1 ==-5555){ contatofisico=0; }
if(P2_HurtBox01x1 == 5555){ contatofisico=0; }

// Nota sobre os testes de colisao
// Esse codigo a seguir testa TODAS as 9 caixas de hurt contra TODAS as 9 caixas de hit
// 9 * 9 = 81 repeticoes do codigo!
// Desculpem por isso...
// Me ajudem a otimizar? Valeu! :)

///Checar Colisao contra P1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if (P2_HitBox_tot>=1) { //1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox01x1; temp1y=P2hb_HitBox01y1; temp2x=P2hb_HitBox01x2; temp2y=P2hb_HitBox01y2;
if (temp1x<=temp2x) { P2hb_HitBox01x1=temp1x; P2hb_HitBox01x2=temp2x; } else { P2hb_HitBox01x1=temp2x; P2hb_HitBox01x2=temp1x; } if (P2hb_HitBox01x1<0) { P2hb_HitBox01x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox01x1) && (P1hb_HurtBox01x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox01y1) && (P1hb_HurtBox01y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox01x1) && (P1hb_HurtBox02x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox01y1) && (P1hb_HurtBox02y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox01x1) && (P1hb_HurtBox03x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox01y1) && (P1hb_HurtBox03y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox01x1) && (P1hb_HurtBox04x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox01y1) && (P1hb_HurtBox04y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox01x1) && (P1hb_HurtBox05x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox01y1) && (P1hb_HurtBox05y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox01x1) && (P1hb_HurtBox06x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox01y1) && (P1hb_HurtBox06y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox01x1) && (P1hb_HurtBox07x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox01y1) && (P1hb_HurtBox07y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox01x1) && (P1hb_HurtBox08x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox01y1) && (P1hb_HurtBox08y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox01x1 !=+5555 && P2_HitBox01y1 !=+5555 && P2_HitBox01x2 !=+5555 && P2_HitBox01y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox01x1) && (P1hb_HurtBox09x1<P2hb_HitBox01x1+(P2hb_HitBox01x2-P2hb_HitBox01x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox01y1) && (P1hb_HurtBox09y1<P2hb_HitBox01y1+(P2hb_HitBox01y2-P2hb_HitBox01y1)) ) { colisaoxP1=1; alturadohitp2=1; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=2) { //2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox02x1; temp1y=P2hb_HitBox02y1; temp2x=P2hb_HitBox02x2; temp2y=P2hb_HitBox02y2;
if (temp1x<=temp2x) { P2hb_HitBox02x1=temp1x; P2hb_HitBox02x2=temp2x; } else { P2hb_HitBox02x1=temp2x; P2hb_HitBox02x2=temp1x; } if (P2hb_HitBox02x1<0) { P2hb_HitBox02x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox02x1) && (P1hb_HurtBox01x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox02y1) && (P1hb_HurtBox01y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox02x1) && (P1hb_HurtBox02x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox02y1) && (P1hb_HurtBox02y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox02x1) && (P1hb_HurtBox03x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox02y1) && (P1hb_HurtBox03y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox02x1) && (P1hb_HurtBox04x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox02y1) && (P1hb_HurtBox04y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox02x1) && (P1hb_HurtBox05x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox02y1) && (P1hb_HurtBox05y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox02x1) && (P1hb_HurtBox06x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox02y1) && (P1hb_HurtBox06y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox02x1) && (P1hb_HurtBox07x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox02y1) && (P1hb_HurtBox07y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox02x1) && (P1hb_HurtBox08x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox02y1) && (P1hb_HurtBox08y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox02x1 !=+5555 && P2_HitBox02y1 !=+5555 && P2_HitBox02x2 !=+5555 && P2_HitBox02y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox02x1) && (P1hb_HurtBox09x1<P2hb_HitBox02x1+(P2hb_HitBox02x2-P2hb_HitBox02x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox02y1) && (P1hb_HurtBox09y1<P2hb_HitBox02y1+(P2hb_HitBox02y2-P2hb_HitBox02y1)) ) { colisaoxP1=1; alturadohitp2=2; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=3) { //3//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox03x1; temp1y=P2hb_HitBox03y1; temp2x=P2hb_HitBox03x2; temp2y=P2hb_HitBox03y2;
if (temp1x<=temp2x) { P2hb_HitBox03x1=temp1x; P2hb_HitBox03x2=temp2x; } else { P2hb_HitBox03x1=temp2x; P2hb_HitBox03x2=temp1x; } if (P2hb_HitBox03x1<0) { P2hb_HitBox03x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox03x1) && (P1hb_HurtBox01x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox03y1) && (P1hb_HurtBox01y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox03x1) && (P1hb_HurtBox02x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox03y1) && (P1hb_HurtBox02y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox03x1) && (P1hb_HurtBox03x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox03y1) && (P1hb_HurtBox03y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox03x1) && (P1hb_HurtBox04x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox03y1) && (P1hb_HurtBox04y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox03x1) && (P1hb_HurtBox05x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox03y1) && (P1hb_HurtBox05y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox03x1) && (P1hb_HurtBox06x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox03y1) && (P1hb_HurtBox06y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox03x1) && (P1hb_HurtBox07x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox03y1) && (P1hb_HurtBox07y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox03x1) && (P1hb_HurtBox08x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox03y1) && (P1hb_HurtBox08y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox03x1 !=+5555 && P2_HitBox03y1 !=+5555 && P2_HitBox03x2 !=+5555 && P2_HitBox03y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox03x1) && (P1hb_HurtBox09x1<P2hb_HitBox03x1+(P2hb_HitBox03x2-P2hb_HitBox03x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox03y1) && (P1hb_HurtBox09y1<P2hb_HitBox03y1+(P2hb_HitBox03y2-P2hb_HitBox03y1)) ) { colisaoxP1=1; alturadohitp2=3; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=4) { //4//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox04x1; temp1y=P2hb_HitBox04y1; temp2x=P2hb_HitBox04x2; temp2y=P2hb_HitBox04y2;
if (temp1x<=temp2x) { P2hb_HitBox04x1=temp1x; P2hb_HitBox04x2=temp2x; } else { P2hb_HitBox04x1=temp2x; P2hb_HitBox04x2=temp1x; } if (P2hb_HitBox04x1<0) { P2hb_HitBox04x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox04x1) && (P1hb_HurtBox01x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox04y1) && (P1hb_HurtBox01y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox04x1) && (P1hb_HurtBox02x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox04y1) && (P1hb_HurtBox02y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox04x1) && (P1hb_HurtBox03x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox04y1) && (P1hb_HurtBox03y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox04x1) && (P1hb_HurtBox04x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox04y1) && (P1hb_HurtBox04y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox04x1) && (P1hb_HurtBox05x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox04y1) && (P1hb_HurtBox05y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox04x1) && (P1hb_HurtBox06x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox04y1) && (P1hb_HurtBox06y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox04x1) && (P1hb_HurtBox07x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox04y1) && (P1hb_HurtBox07y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox04x1) && (P1hb_HurtBox08x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox04y1) && (P1hb_HurtBox08y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox04x1 !=+5555 && P2_HitBox04y1 !=+5555 && P2_HitBox04x2 !=+5555 && P2_HitBox04y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox04x1) && (P1hb_HurtBox09x1<P2hb_HitBox04x1+(P2hb_HitBox04x2-P2hb_HitBox04x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox04y1) && (P1hb_HurtBox09y1<P2hb_HitBox04y1+(P2hb_HitBox04y2-P2hb_HitBox04y1)) ) { colisaoxP1=1; alturadohitp2=4; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=5) { //5//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox05x1; temp1y=P2hb_HitBox05y1; temp2x=P2hb_HitBox05x2; temp2y=P2hb_HitBox05y2;
if (temp1x<=temp2x) { P2hb_HitBox05x1=temp1x; P2hb_HitBox05x2=temp2x; } else { P2hb_HitBox05x1=temp2x; P2hb_HitBox05x2=temp1x; } if (P2hb_HitBox05x1<0) { P2hb_HitBox05x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox05x1) && (P1hb_HurtBox01x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox05y1) && (P1hb_HurtBox01y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox05x1) && (P1hb_HurtBox02x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox05y1) && (P1hb_HurtBox02y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox05x1) && (P1hb_HurtBox03x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox05y1) && (P1hb_HurtBox03y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox05x1) && (P1hb_HurtBox04x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox05y1) && (P1hb_HurtBox04y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox05x1) && (P1hb_HurtBox05x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox05y1) && (P1hb_HurtBox05y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox05x1) && (P1hb_HurtBox06x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox05y1) && (P1hb_HurtBox06y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox05x1) && (P1hb_HurtBox07x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox05y1) && (P1hb_HurtBox07y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox05x1) && (P1hb_HurtBox08x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox05y1) && (P1hb_HurtBox08y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox05x1 !=+5555 && P2_HitBox05y1 !=+5555 && P2_HitBox05x2 !=+5555 && P2_HitBox05y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox05x1) && (P1hb_HurtBox09x1<P2hb_HitBox05x1+(P2hb_HitBox05x2-P2hb_HitBox05x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox05y1) && (P1hb_HurtBox09y1<P2hb_HitBox05y1+(P2hb_HitBox05y2-P2hb_HitBox05y1)) ) { colisaoxP1=1; alturadohitp2=5; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=6) { //6//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox06x1; temp1y=P2hb_HitBox06y1; temp2x=P2hb_HitBox06x2; temp2y=P2hb_HitBox06y2;
if (temp1x<=temp2x) { P2hb_HitBox06x1=temp1x; P2hb_HitBox06x2=temp2x; } else { P2hb_HitBox06x1=temp2x; P2hb_HitBox06x2=temp1x; } if (P2hb_HitBox06x1<0) { P2hb_HitBox06x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox06x1) && (P1hb_HurtBox01x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox06y1) && (P1hb_HurtBox01y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox06x1) && (P1hb_HurtBox02x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox06y1) && (P1hb_HurtBox02y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox06x1) && (P1hb_HurtBox03x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox06y1) && (P1hb_HurtBox03y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox06x1) && (P1hb_HurtBox04x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox06y1) && (P1hb_HurtBox04y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox06x1) && (P1hb_HurtBox05x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox06y1) && (P1hb_HurtBox05y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox06x1) && (P1hb_HurtBox06x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox06y1) && (P1hb_HurtBox06y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox06x1) && (P1hb_HurtBox07x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox06y1) && (P1hb_HurtBox07y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox06x1) && (P1hb_HurtBox08x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox06y1) && (P1hb_HurtBox08y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox06x1 !=+5555 && P2_HitBox06y1 !=+5555 && P2_HitBox06x2 !=+5555 && P2_HitBox06y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox06x1) && (P1hb_HurtBox09x1<P2hb_HitBox06x1+(P2hb_HitBox06x2-P2hb_HitBox06x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox06y1) && (P1hb_HurtBox09y1<P2hb_HitBox06y1+(P2hb_HitBox06y2-P2hb_HitBox06y1)) ) { colisaoxP1=1; alturadohitp2=6; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=7) { //7//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox07x1; temp1y=P2hb_HitBox07y1; temp2x=P2hb_HitBox07x2; temp2y=P2hb_HitBox07y2;
if (temp1x<=temp2x) { P2hb_HitBox07x1=temp1x; P2hb_HitBox07x2=temp2x; } else { P2hb_HitBox07x1=temp2x; P2hb_HitBox07x2=temp1x; } if (P2hb_HitBox07x1<0) { P2hb_HitBox07x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox07x1) && (P1hb_HurtBox01x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox07y1) && (P1hb_HurtBox01y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox07x1) && (P1hb_HurtBox02x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox07y1) && (P1hb_HurtBox02y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox07x1) && (P1hb_HurtBox03x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox07y1) && (P1hb_HurtBox03y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox07x1) && (P1hb_HurtBox04x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox07y1) && (P1hb_HurtBox04y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox07x1) && (P1hb_HurtBox05x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox07y1) && (P1hb_HurtBox05y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox07x1) && (P1hb_HurtBox06x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox07y1) && (P1hb_HurtBox06y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox07x1) && (P1hb_HurtBox07x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox07y1) && (P1hb_HurtBox07y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox07x1) && (P1hb_HurtBox08x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox07y1) && (P1hb_HurtBox08y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox07x1 !=+5555 && P2_HitBox07y1 !=+5555 && P2_HitBox07x2 !=+5555 && P2_HitBox07y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox07x1) && (P1hb_HurtBox09x1<P2hb_HitBox07x1+(P2hb_HitBox07x2-P2hb_HitBox07x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox07y1) && (P1hb_HurtBox09y1<P2hb_HitBox07y1+(P2hb_HitBox07y2-P2hb_HitBox07y1)) ) { colisaoxP1=1; alturadohitp2=7; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=8) { //8//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox08x1; temp1y=P2hb_HitBox08y1; temp2x=P2hb_HitBox08x2; temp2y=P2hb_HitBox08y2;
if (temp1x<=temp2x) { P2hb_HitBox08x1=temp1x; P2hb_HitBox08x2=temp2x; } else { P2hb_HitBox08x1=temp2x; P2hb_HitBox08x2=temp1x; } if (P2hb_HitBox08x1<0) { P2hb_HitBox08x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox08x1) && (P1hb_HurtBox01x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox08y1) && (P1hb_HurtBox01y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox08x1) && (P1hb_HurtBox02x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox08y1) && (P1hb_HurtBox02y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox08x1) && (P1hb_HurtBox03x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox08y1) && (P1hb_HurtBox03y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox08x1) && (P1hb_HurtBox04x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox08y1) && (P1hb_HurtBox04y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox08x1) && (P1hb_HurtBox05x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox08y1) && (P1hb_HurtBox05y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox08x1) && (P1hb_HurtBox06x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox08y1) && (P1hb_HurtBox06y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox08x1) && (P1hb_HurtBox07x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox08y1) && (P1hb_HurtBox07y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox08x1) && (P1hb_HurtBox08x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox08y1) && (P1hb_HurtBox08y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox08x1 !=+5555 && P2_HitBox08y1 !=+5555 && P2_HitBox08x2 !=+5555 && P2_HitBox08y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox08x1) && (P1hb_HurtBox09x1<P2hb_HitBox08x1+(P2hb_HitBox08x2-P2hb_HitBox08x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox08y1) && (P1hb_HurtBox09y1<P2hb_HitBox08y1+(P2hb_HitBox08y2-P2hb_HitBox08y1)) ) { colisaoxP1=1; alturadohitp2=8; } else { colisaoxP1=0; } } }

if (P2_HitBox_tot>=9) { //9//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P2hb_HitBox09x1; temp1y=P2hb_HitBox09y1; temp2x=P2hb_HitBox09x2; temp2y=P2hb_HitBox09y2;
if (temp1x<=temp2x) { P2hb_HitBox09x1=temp1x; P2hb_HitBox09x2=temp2x; } else { P2hb_HitBox09x1=temp2x; P2hb_HitBox09x2=temp1x; } if (P2hb_HitBox09x1<0) { P2hb_HitBox09x1=0; }
//x1
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox01x1!=-5555 && P1_HurtBox01y1!=-5555 && P1_HurtBox01x2!=-5555 && P1_HurtBox01y2!=-5555 ) {
temp1x=P1hb_HurtBox01x1; temp1y=P1hb_HurtBox01y1; temp2x=P1hb_HurtBox01x2; temp2y=P1hb_HurtBox01y2;
if (temp1x<=temp2x) { P1hb_HurtBox01x1=temp1x; P1hb_HurtBox01x2=temp2x; } else { P1hb_HurtBox01x1=temp2x; P1hb_HurtBox01x2=temp1x; } if (P1hb_HurtBox01x1<0) { P1hb_HurtBox01x1=0; }
if ( (P1hb_HurtBox01x1+(P1hb_HurtBox01x2-P1hb_HurtBox01x1)>P2hb_HitBox09x1) && (P1hb_HurtBox01x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox01y1+(P1hb_HurtBox01y2-P1hb_HurtBox01y1)>P2hb_HitBox09y1) && (P1hb_HurtBox01y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; }  }
//x2
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox02x1!=-5555 && P1_HurtBox02y1!=-5555 && P1_HurtBox02x2!=-5555 && P1_HurtBox02y2!=-5555 ) {
temp1x=P1hb_HurtBox02x1; temp1y=P1hb_HurtBox02y1; temp2x=P1hb_HurtBox02x2; temp2y=P1hb_HurtBox02y2;
if (temp1x<=temp2x) { P1hb_HurtBox02x1=temp1x; P1hb_HurtBox02x2=temp2x; } else { P1hb_HurtBox02x1=temp2x; P1hb_HurtBox02x2=temp1x; } if (P1hb_HurtBox02x1<0) { P1hb_HurtBox02x1=0; }
if ( (P1hb_HurtBox02x1+(P1hb_HurtBox02x2-P1hb_HurtBox02x1)>P2hb_HitBox09x1) && (P1hb_HurtBox02x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox02y1+(P1hb_HurtBox02y2-P1hb_HurtBox02y1)>P2hb_HitBox09y1) && (P1hb_HurtBox02y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; }  }
//x3
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox03x1!=-5555 && P1_HurtBox03y1!=-5555 && P1_HurtBox03x2!=-5555 && P1_HurtBox03y2!=-5555 ) {
temp1x=P1hb_HurtBox03x1; temp1y=P1hb_HurtBox03y1; temp2x=P1hb_HurtBox03x2; temp2y=P1hb_HurtBox03y2;
if (temp1x<=temp2x) { P1hb_HurtBox03x1=temp1x; P1hb_HurtBox03x2=temp2x; } else { P1hb_HurtBox03x1=temp2x; P1hb_HurtBox03x2=temp1x; } if (P1hb_HurtBox03x1<0) { P1hb_HurtBox03x1=0; }
if ( (P1hb_HurtBox03x1+(P1hb_HurtBox03x2-P1hb_HurtBox03x1)>P2hb_HitBox09x1) && (P1hb_HurtBox03x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox03y1+(P1hb_HurtBox03y2-P1hb_HurtBox03y1)>P2hb_HitBox09y1) && (P1hb_HurtBox03y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; }  }
//x4
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox04x1!=-5555 && P1_HurtBox04y1!=-5555 && P1_HurtBox04x2!=-5555 && P1_HurtBox04y2!=-5555 ) {
temp1x=P1hb_HurtBox04x1; temp1y=P1hb_HurtBox04y1; temp2x=P1hb_HurtBox04x2; temp2y=P1hb_HurtBox04y2;
if (temp1x<=temp2x) { P1hb_HurtBox04x1=temp1x; P1hb_HurtBox04x2=temp2x; } else { P1hb_HurtBox04x1=temp2x; P1hb_HurtBox04x2=temp1x; } if (P1hb_HurtBox04x1<0) { P1hb_HurtBox04x1=0; }
if ( (P1hb_HurtBox04x1+(P1hb_HurtBox04x2-P1hb_HurtBox04x1)>P2hb_HitBox09x1) && (P1hb_HurtBox04x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox04y1+(P1hb_HurtBox04y2-P1hb_HurtBox04y1)>P2hb_HitBox09y1) && (P1hb_HurtBox04y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; }  }
//x5
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox05x1!=-5555 && P1_HurtBox05y1!=-5555 && P1_HurtBox05x2!=-5555 && P1_HurtBox05y2!=-5555 ) {
temp1x=P1hb_HurtBox05x1; temp1y=P1hb_HurtBox05y1; temp2x=P1hb_HurtBox05x2; temp2y=P1hb_HurtBox05y2;
if (temp1x<=temp2x) { P1hb_HurtBox05x1=temp1x; P1hb_HurtBox05x2=temp2x; } else { P1hb_HurtBox05x1=temp2x; P1hb_HurtBox05x2=temp1x; } if (P1hb_HurtBox05x1<0) { P1hb_HurtBox05x1=0; }
if ( (P1hb_HurtBox05x1+(P1hb_HurtBox05x2-P1hb_HurtBox05x1)>P2hb_HitBox09x1) && (P1hb_HurtBox05x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox05y1+(P1hb_HurtBox05y2-P1hb_HurtBox05y1)>P2hb_HitBox09y1) && (P1hb_HurtBox05y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; }  }
//x6
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox06x1!=-5555 && P1_HurtBox06y1!=-5555 && P1_HurtBox06x2!=-5555 && P1_HurtBox06y2!=-5555 ) {
temp1x=P1hb_HurtBox06x1; temp1y=P1hb_HurtBox06y1; temp2x=P1hb_HurtBox06x2; temp2y=P1hb_HurtBox06y2;
if (temp1x<=temp2x) { P1hb_HurtBox06x1=temp1x; P1hb_HurtBox06x2=temp2x; } else { P1hb_HurtBox06x1=temp2x; P1hb_HurtBox06x2=temp1x; } if (P1hb_HurtBox06x1<0) { P1hb_HurtBox06x1=0; }
if ( (P1hb_HurtBox06x1+(P1hb_HurtBox06x2-P1hb_HurtBox06x1)>P2hb_HitBox09x1) && (P1hb_HurtBox06x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox06y1+(P1hb_HurtBox06y2-P1hb_HurtBox06y1)>P2hb_HitBox09y1) && (P1hb_HurtBox06y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; } }
//x7
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox07x1!=-5555 && P1_HurtBox07y1!=-5555 && P1_HurtBox07x2!=-5555 && P1_HurtBox07y2!=-5555 ) {
temp1x=P1hb_HurtBox07x1; temp1y=P1hb_HurtBox07y1; temp2x=P1hb_HurtBox07x2; temp2y=P1hb_HurtBox07y2;
if (temp1x<=temp2x) { P1hb_HurtBox07x1=temp1x; P1hb_HurtBox07x2=temp2x; } else { P1hb_HurtBox07x1=temp2x; P1hb_HurtBox07x2=temp1x; } if (P1hb_HurtBox07x1<0) { P1hb_HurtBox07x1=0; }
if ( (P1hb_HurtBox07x1+(P1hb_HurtBox07x2-P1hb_HurtBox07x1)>P2hb_HitBox09x1) && (P1hb_HurtBox07x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox07y1+(P1hb_HurtBox07y2-P1hb_HurtBox07y1)>P2hb_HitBox09y1) && (P1hb_HurtBox07y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; } }
//x8
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox08x1!=-5555 && P1_HurtBox08y1!=-5555 && P1_HurtBox08x2!=-5555 && P1_HurtBox08y2!=-5555 ) {
temp1x=P1hb_HurtBox08x1; temp1y=P1hb_HurtBox08y1; temp2x=P1hb_HurtBox08x2; temp2y=P1hb_HurtBox08y2;
if (temp1x<=temp2x) { P1hb_HurtBox08x1=temp1x; P1hb_HurtBox08x2=temp2x; } else { P1hb_HurtBox08x1=temp2x; P1hb_HurtBox08x2=temp1x; } if (P1hb_HurtBox08x1<0) { P1hb_HurtBox08x1=0; }
if ( (P1hb_HurtBox08x1+(P1hb_HurtBox08x2-P1hb_HurtBox08x1)>P2hb_HitBox09x1) && (P1hb_HurtBox08x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox08y1+(P1hb_HurtBox08y2-P1hb_HurtBox08y1)>P2hb_HitBox09y1) && (P1hb_HurtBox08y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; } }
//x9
if (colisaoxP1==0 && P2_HitBox09x1 !=+5555 && P2_HitBox09y1 !=+5555 && P2_HitBox09x2 !=+5555 && P2_HitBox09y2 !=+5555 && P1_HurtBox09x1!=-5555 && P1_HurtBox09y1!=-5555 && P1_HurtBox09x2!=-5555 && P1_HurtBox09y2!=-5555 ) {
temp1x=P1hb_HurtBox09x1; temp1y=P1hb_HurtBox09y1; temp2x=P1hb_HurtBox09x2; temp2y=P1hb_HurtBox09y2;
if (temp1x<=temp2x) { P1hb_HurtBox09x1=temp1x; P1hb_HurtBox09x2=temp2x; } else { P1hb_HurtBox09x1=temp2x; P1hb_HurtBox09x2=temp1x; } if (P1hb_HurtBox09x1<0) { P1hb_HurtBox09x1=0; }
if ( (P1hb_HurtBox09x1+(P1hb_HurtBox09x2-P1hb_HurtBox09x1)>P2hb_HitBox09x1) && (P1hb_HurtBox09x1<P2hb_HitBox09x1+(P2hb_HitBox09x2-P2hb_HitBox09x1)) &&
(P1hb_HurtBox09y1+(P1hb_HurtBox09y2-P1hb_HurtBox09y1)>P2hb_HitBox09y1) && (P1hb_HurtBox09y1<P2hb_HitBox09y1+(P2hb_HitBox09y2-P2hb_HitBox09y1)) ) { colisaoxP1=1; alturadohitp2=9; } else { colisaoxP1=0; } } }

///Checar Colisao contra P2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

if (P1_HitBox_tot>=1) { //1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox01x1; temp1y=P1hb_HitBox01y1; temp2x=P1hb_HitBox01x2; temp2y=P1hb_HitBox01y2;
if (temp1x<=temp2x) { P1hb_HitBox01x1=temp1x; P1hb_HitBox01x2=temp2x; } else { P1hb_HitBox01x1=temp2x; P1hb_HitBox01x2=temp1x; } if (P1hb_HitBox01x1<0) { P1hb_HitBox01x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox01x1) && (P2hb_HurtBox01x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox01y1) && (P2hb_HurtBox01y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox01x1) && (P2hb_HurtBox02x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox01y1) && (P2hb_HurtBox02y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox01x1) && (P2hb_HurtBox03x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox01y1) && (P2hb_HurtBox03y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox01x1) && (P2hb_HurtBox04x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox01y1) && (P2hb_HurtBox04y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox01x1) && (P2hb_HurtBox05x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox01y1) && (P2hb_HurtBox05y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox01x1) && (P2hb_HurtBox06x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox01y1) && (P2hb_HurtBox06y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox01x1) && (P2hb_HurtBox07x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox01y1) && (P2hb_HurtBox07y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox01x1) && (P2hb_HurtBox08x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox01y1) && (P2hb_HurtBox08y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox01x1 !=+5555 && P1_HitBox01y1 !=+5555 && P1_HitBox01x2 !=+5555 && P1_HitBox01y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox01x1) && (P2hb_HurtBox09x1<P1hb_HitBox01x1+(P1hb_HitBox01x2-P1hb_HitBox01x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox01y1) && (P2hb_HurtBox09y1<P1hb_HitBox01y1+(P1hb_HitBox01y2-P1hb_HitBox01y1)) ) { colisaoxP2=1; alturadohitp1=1; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=2) { //2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox02x1; temp1y=P1hb_HitBox02y1; temp2x=P1hb_HitBox02x2; temp2y=P1hb_HitBox02y2;
if (temp1x<=temp2x) { P1hb_HitBox02x1=temp1x; P1hb_HitBox02x2=temp2x; } else { P1hb_HitBox02x1=temp2x; P1hb_HitBox02x2=temp1x; } if (P1hb_HitBox02x1<0) { P1hb_HitBox02x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox02x1) && (P2hb_HurtBox01x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox02y1) && (P2hb_HurtBox01y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox02x1) && (P2hb_HurtBox02x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox02y1) && (P2hb_HurtBox02y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox02x1) && (P2hb_HurtBox03x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox02y1) && (P2hb_HurtBox03y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox02x1) && (P2hb_HurtBox04x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox02y1) && (P2hb_HurtBox04y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox02x1) && (P2hb_HurtBox05x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox02y1) && (P2hb_HurtBox05y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox02x1) && (P2hb_HurtBox06x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox02y1) && (P2hb_HurtBox06y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox02x1) && (P2hb_HurtBox07x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox02y1) && (P2hb_HurtBox07y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox02x1) && (P2hb_HurtBox08x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox02y1) && (P2hb_HurtBox08y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox02x1 !=+5555 && P1_HitBox02y1 !=+5555 && P1_HitBox02x2 !=+5555 && P1_HitBox02y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox02x1) && (P2hb_HurtBox09x1<P1hb_HitBox02x1+(P1hb_HitBox02x2-P1hb_HitBox02x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox02y1) && (P2hb_HurtBox09y1<P1hb_HitBox02y1+(P1hb_HitBox02y2-P1hb_HitBox02y1)) ) { colisaoxP2=1; alturadohitp1=2; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=3) { //3//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox03x1; temp1y=P1hb_HitBox03y1; temp2x=P1hb_HitBox03x2; temp2y=P1hb_HitBox03y2;
if (temp1x<=temp2x) { P1hb_HitBox03x1=temp1x; P1hb_HitBox03x2=temp2x; } else { P1hb_HitBox03x1=temp2x; P1hb_HitBox03x2=temp1x; } if (P1hb_HitBox03x1<0) { P1hb_HitBox03x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox03x1) && (P2hb_HurtBox01x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox03y1) && (P2hb_HurtBox01y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox03x1) && (P2hb_HurtBox02x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox03y1) && (P2hb_HurtBox02y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox03x1) && (P2hb_HurtBox03x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox03y1) && (P2hb_HurtBox03y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox03x1) && (P2hb_HurtBox04x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox03y1) && (P2hb_HurtBox04y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox03x1) && (P2hb_HurtBox05x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox03y1) && (P2hb_HurtBox05y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox03x1) && (P2hb_HurtBox06x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox03y1) && (P2hb_HurtBox06y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox03x1) && (P2hb_HurtBox07x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox03y1) && (P2hb_HurtBox07y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox03x1) && (P2hb_HurtBox08x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox03y1) && (P2hb_HurtBox08y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox03x1 !=+5555 && P1_HitBox03y1 !=+5555 && P1_HitBox03x2 !=+5555 && P1_HitBox03y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox03x1) && (P2hb_HurtBox09x1<P1hb_HitBox03x1+(P1hb_HitBox03x2-P1hb_HitBox03x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox03y1) && (P2hb_HurtBox09y1<P1hb_HitBox03y1+(P1hb_HitBox03y2-P1hb_HitBox03y1)) ) { colisaoxP2=1; alturadohitp1=3; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=4) { //4//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox04x1; temp1y=P1hb_HitBox04y1; temp2x=P1hb_HitBox04x2; temp2y=P1hb_HitBox04y2;
if (temp1x<=temp2x) { P1hb_HitBox04x1=temp1x; P1hb_HitBox04x2=temp2x; } else { P1hb_HitBox04x1=temp2x; P1hb_HitBox04x2=temp1x; } if (P1hb_HitBox04x1<0) { P1hb_HitBox04x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox04x1) && (P2hb_HurtBox01x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox04y1) && (P2hb_HurtBox01y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox04x1) && (P2hb_HurtBox02x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox04y1) && (P2hb_HurtBox02y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox04x1) && (P2hb_HurtBox03x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox04y1) && (P2hb_HurtBox03y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox04x1) && (P2hb_HurtBox04x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox04y1) && (P2hb_HurtBox04y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox04x1) && (P2hb_HurtBox05x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox04y1) && (P2hb_HurtBox05y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox04x1) && (P2hb_HurtBox06x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox04y1) && (P2hb_HurtBox06y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox04x1) && (P2hb_HurtBox07x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox04y1) && (P2hb_HurtBox07y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox04x1) && (P2hb_HurtBox08x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox04y1) && (P2hb_HurtBox08y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox04x1 !=+5555 && P1_HitBox04y1 !=+5555 && P1_HitBox04x2 !=+5555 && P1_HitBox04y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox04x1) && (P2hb_HurtBox09x1<P1hb_HitBox04x1+(P1hb_HitBox04x2-P1hb_HitBox04x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox04y1) && (P2hb_HurtBox09y1<P1hb_HitBox04y1+(P1hb_HitBox04y2-P1hb_HitBox04y1)) ) { colisaoxP2=1; alturadohitp1=4; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=5) { //5//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox05x1; temp1y=P1hb_HitBox05y1; temp2x=P1hb_HitBox05x2; temp2y=P1hb_HitBox05y2;
if (temp1x<=temp2x) { P1hb_HitBox05x1=temp1x; P1hb_HitBox05x2=temp2x; } else { P1hb_HitBox05x1=temp2x; P1hb_HitBox05x2=temp1x; } if (P1hb_HitBox05x1<0) { P1hb_HitBox05x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox05x1) && (P2hb_HurtBox01x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox05y1) && (P2hb_HurtBox01y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox05x1) && (P2hb_HurtBox02x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox05y1) && (P2hb_HurtBox02y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox05x1) && (P2hb_HurtBox03x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox05y1) && (P2hb_HurtBox03y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox05x1) && (P2hb_HurtBox04x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox05y1) && (P2hb_HurtBox04y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox05x1) && (P2hb_HurtBox05x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox05y1) && (P2hb_HurtBox05y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox05x1) && (P2hb_HurtBox06x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox05y1) && (P2hb_HurtBox06y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox05x1) && (P2hb_HurtBox07x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox05y1) && (P2hb_HurtBox07y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox05x1) && (P2hb_HurtBox08x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox05y1) && (P2hb_HurtBox08y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox05x1 !=+5555 && P1_HitBox05y1 !=+5555 && P1_HitBox05x2 !=+5555 && P1_HitBox05y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox05x1) && (P2hb_HurtBox09x1<P1hb_HitBox05x1+(P1hb_HitBox05x2-P1hb_HitBox05x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox05y1) && (P2hb_HurtBox09y1<P1hb_HitBox05y1+(P1hb_HitBox05y2-P1hb_HitBox05y1)) ) { colisaoxP2=1; alturadohitp1=5; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=6) { //6//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox06x1; temp1y=P1hb_HitBox06y1; temp2x=P1hb_HitBox06x2; temp2y=P1hb_HitBox06y2;
if (temp1x<=temp2x) { P1hb_HitBox06x1=temp1x; P1hb_HitBox06x2=temp2x; } else { P1hb_HitBox06x1=temp2x; P1hb_HitBox06x2=temp1x; } if (P1hb_HitBox06x1<0) { P1hb_HitBox06x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox06x1) && (P2hb_HurtBox01x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox06y1) && (P2hb_HurtBox01y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox06x1) && (P2hb_HurtBox02x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox06y1) && (P2hb_HurtBox02y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox06x1) && (P2hb_HurtBox03x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox06y1) && (P2hb_HurtBox03y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox06x1) && (P2hb_HurtBox04x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox06y1) && (P2hb_HurtBox04y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox06x1) && (P2hb_HurtBox05x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox06y1) && (P2hb_HurtBox05y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox06x1) && (P2hb_HurtBox06x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox06y1) && (P2hb_HurtBox06y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox06x1) && (P2hb_HurtBox07x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox06y1) && (P2hb_HurtBox07y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox06x1) && (P2hb_HurtBox08x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox06y1) && (P2hb_HurtBox08y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox06x1 !=+5555 && P1_HitBox06y1 !=+5555 && P1_HitBox06x2 !=+5555 && P1_HitBox06y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox06x1) && (P2hb_HurtBox09x1<P1hb_HitBox06x1+(P1hb_HitBox06x2-P1hb_HitBox06x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox06y1) && (P2hb_HurtBox09y1<P1hb_HitBox06y1+(P1hb_HitBox06y2-P1hb_HitBox06y1)) ) { colisaoxP2=1; alturadohitp1=6; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=7) { //7//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox07x1; temp1y=P1hb_HitBox07y1; temp2x=P1hb_HitBox07x2; temp2y=P1hb_HitBox07y2;
if (temp1x<=temp2x) { P1hb_HitBox07x1=temp1x; P1hb_HitBox07x2=temp2x; } else { P1hb_HitBox07x1=temp2x; P1hb_HitBox07x2=temp1x; } if (P1hb_HitBox07x1<0) { P1hb_HitBox07x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox07x1) && (P2hb_HurtBox01x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox07y1) && (P2hb_HurtBox01y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox07x1) && (P2hb_HurtBox02x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox07y1) && (P2hb_HurtBox02y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox07x1) && (P2hb_HurtBox03x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox07y1) && (P2hb_HurtBox03y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox07x1) && (P2hb_HurtBox04x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox07y1) && (P2hb_HurtBox04y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox07x1) && (P2hb_HurtBox05x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox07y1) && (P2hb_HurtBox05y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox07x1) && (P2hb_HurtBox06x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox07y1) && (P2hb_HurtBox06y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox07x1) && (P2hb_HurtBox07x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox07y1) && (P2hb_HurtBox07y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox07x1) && (P2hb_HurtBox08x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox07y1) && (P2hb_HurtBox08y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox07x1 !=+5555 && P1_HitBox07y1 !=+5555 && P1_HitBox07x2 !=+5555 && P1_HitBox07y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox07x1) && (P2hb_HurtBox09x1<P1hb_HitBox07x1+(P1hb_HitBox07x2-P1hb_HitBox07x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox07y1) && (P2hb_HurtBox09y1<P1hb_HitBox07y1+(P1hb_HitBox07y2-P1hb_HitBox07y1)) ) { colisaoxP2=1; alturadohitp1=7; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=8) { //8//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox08x1; temp1y=P1hb_HitBox08y1; temp2x=P1hb_HitBox08x2; temp2y=P1hb_HitBox08y2;
if (temp1x<=temp2x) { P1hb_HitBox08x1=temp1x; P1hb_HitBox08x2=temp2x; } else { P1hb_HitBox08x1=temp2x; P1hb_HitBox08x2=temp1x; } if (P1hb_HitBox08x1<0) { P1hb_HitBox08x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox08x1) && (P2hb_HurtBox01x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox08y1) && (P2hb_HurtBox01y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox08x1) && (P2hb_HurtBox02x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox08y1) && (P2hb_HurtBox02y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox08x1) && (P2hb_HurtBox03x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox08y1) && (P2hb_HurtBox03y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox08x1) && (P2hb_HurtBox04x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox08y1) && (P2hb_HurtBox04y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox08x1) && (P2hb_HurtBox05x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox08y1) && (P2hb_HurtBox05y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox08x1) && (P2hb_HurtBox06x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox08y1) && (P2hb_HurtBox06y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox08x1) && (P2hb_HurtBox07x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox08y1) && (P2hb_HurtBox07y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox08x1) && (P2hb_HurtBox08x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox08y1) && (P2hb_HurtBox08y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox08x1 !=+5555 && P1_HitBox08y1 !=+5555 && P1_HitBox08x2 !=+5555 && P1_HitBox08y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox08x1) && (P2hb_HurtBox09x1<P1hb_HitBox08x1+(P1hb_HitBox08x2-P1hb_HitBox08x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox08y1) && (P2hb_HurtBox09y1<P1hb_HitBox08y1+(P1hb_HitBox08y2-P1hb_HitBox08y1)) ) { colisaoxP2=1; alturadohitp1=8; } else { colisaoxP2=0; } } }

if (P1_HitBox_tot>=9) { //9//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
temp1x=P1hb_HitBox09x1; temp1y=P1hb_HitBox09y1; temp2x=P1hb_HitBox09x2; temp2y=P1hb_HitBox09y2;
if (temp1x<=temp2x) { P1hb_HitBox09x1=temp1x; P1hb_HitBox09x2=temp2x; } else { P1hb_HitBox09x1=temp2x; P1hb_HitBox09x2=temp1x; } if (P1hb_HitBox09x1<0) { P1hb_HitBox09x1=0; }
//x1
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox01x1!=-5555 && P2_HurtBox01y1!=-5555 && P2_HurtBox01x2!=-5555 && P2_HurtBox01y2!=-5555 ) {
temp1x=P2hb_HurtBox01x1; temp1y=P2hb_HurtBox01y1; temp2x=P2hb_HurtBox01x2; temp2y=P2hb_HurtBox01y2;
if (temp1x<=temp2x) { P2hb_HurtBox01x1=temp1x; P2hb_HurtBox01x2=temp2x; } else { P2hb_HurtBox01x1=temp2x; P2hb_HurtBox01x2=temp1x; } if (P2hb_HurtBox01x1<0) { P2hb_HurtBox01x1=0; }
if ( (P2hb_HurtBox01x1+(P2hb_HurtBox01x2-P2hb_HurtBox01x1)>P1hb_HitBox09x1) && (P2hb_HurtBox01x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox01y1+(P2hb_HurtBox01y2-P2hb_HurtBox01y1)>P1hb_HitBox09y1) && (P2hb_HurtBox01y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; }  }
//x2
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox02x1!=-5555 && P2_HurtBox02y1!=-5555 && P2_HurtBox02x2!=-5555 && P2_HurtBox02y2!=-5555 ) {
temp1x=P2hb_HurtBox02x1; temp1y=P2hb_HurtBox02y1; temp2x=P2hb_HurtBox02x2; temp2y=P2hb_HurtBox02y2;
if (temp1x<=temp2x) { P2hb_HurtBox02x1=temp1x; P2hb_HurtBox02x2=temp2x; } else { P2hb_HurtBox02x1=temp2x; P2hb_HurtBox02x2=temp1x; } if (P2hb_HurtBox02x1<0) { P2hb_HurtBox02x1=0; }
if ( (P2hb_HurtBox02x1+(P2hb_HurtBox02x2-P2hb_HurtBox02x1)>P1hb_HitBox09x1) && (P2hb_HurtBox02x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox02y1+(P2hb_HurtBox02y2-P2hb_HurtBox02y1)>P1hb_HitBox09y1) && (P2hb_HurtBox02y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; }  }
//x3
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox03x1!=-5555 && P2_HurtBox03y1!=-5555 && P2_HurtBox03x2!=-5555 && P2_HurtBox03y2!=-5555 ) {
temp1x=P2hb_HurtBox03x1; temp1y=P2hb_HurtBox03y1; temp2x=P2hb_HurtBox03x2; temp2y=P2hb_HurtBox03y2;
if (temp1x<=temp2x) { P2hb_HurtBox03x1=temp1x; P2hb_HurtBox03x2=temp2x; } else { P2hb_HurtBox03x1=temp2x; P2hb_HurtBox03x2=temp1x; } if (P2hb_HurtBox03x1<0) { P2hb_HurtBox03x1=0; }
if ( (P2hb_HurtBox03x1+(P2hb_HurtBox03x2-P2hb_HurtBox03x1)>P1hb_HitBox09x1) && (P2hb_HurtBox03x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox03y1+(P2hb_HurtBox03y2-P2hb_HurtBox03y1)>P1hb_HitBox09y1) && (P2hb_HurtBox03y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; }  }
//x4
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox04x1!=-5555 && P2_HurtBox04y1!=-5555 && P2_HurtBox04x2!=-5555 && P2_HurtBox04y2!=-5555 ) {
temp1x=P2hb_HurtBox04x1; temp1y=P2hb_HurtBox04y1; temp2x=P2hb_HurtBox04x2; temp2y=P2hb_HurtBox04y2;
if (temp1x<=temp2x) { P2hb_HurtBox04x1=temp1x; P2hb_HurtBox04x2=temp2x; } else { P2hb_HurtBox04x1=temp2x; P2hb_HurtBox04x2=temp1x; } if (P2hb_HurtBox04x1<0) { P2hb_HurtBox04x1=0; }
if ( (P2hb_HurtBox04x1+(P2hb_HurtBox04x2-P2hb_HurtBox04x1)>P1hb_HitBox09x1) && (P2hb_HurtBox04x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox04y1+(P2hb_HurtBox04y2-P2hb_HurtBox04y1)>P1hb_HitBox09y1) && (P2hb_HurtBox04y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; }  }
//x5
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox05x1!=-5555 && P2_HurtBox05y1!=-5555 && P2_HurtBox05x2!=-5555 && P2_HurtBox05y2!=-5555 ) {
temp1x=P2hb_HurtBox05x1; temp1y=P2hb_HurtBox05y1; temp2x=P2hb_HurtBox05x2; temp2y=P2hb_HurtBox05y2;
if (temp1x<=temp2x) { P2hb_HurtBox05x1=temp1x; P2hb_HurtBox05x2=temp2x; } else { P2hb_HurtBox05x1=temp2x; P2hb_HurtBox05x2=temp1x; } if (P2hb_HurtBox05x1<0) { P2hb_HurtBox05x1=0; }
if ( (P2hb_HurtBox05x1+(P2hb_HurtBox05x2-P2hb_HurtBox05x1)>P1hb_HitBox09x1) && (P2hb_HurtBox05x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox05y1+(P2hb_HurtBox05y2-P2hb_HurtBox05y1)>P1hb_HitBox09y1) && (P2hb_HurtBox05y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; }  }
//x6
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox06x1!=-5555 && P2_HurtBox06y1!=-5555 && P2_HurtBox06x2!=-5555 && P2_HurtBox06y2!=-5555 ) {
temp1x=P2hb_HurtBox06x1; temp1y=P2hb_HurtBox06y1; temp2x=P2hb_HurtBox06x2; temp2y=P2hb_HurtBox06y2;
if (temp1x<=temp2x) { P2hb_HurtBox06x1=temp1x; P2hb_HurtBox06x2=temp2x; } else { P2hb_HurtBox06x1=temp2x; P2hb_HurtBox06x2=temp1x; } if (P2hb_HurtBox06x1<0) { P2hb_HurtBox06x1=0; }
if ( (P2hb_HurtBox06x1+(P2hb_HurtBox06x2-P2hb_HurtBox06x1)>P1hb_HitBox09x1) && (P2hb_HurtBox06x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox06y1+(P2hb_HurtBox06y2-P2hb_HurtBox06y1)>P1hb_HitBox09y1) && (P2hb_HurtBox06y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; } }
//x7
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox07x1!=-5555 && P2_HurtBox07y1!=-5555 && P2_HurtBox07x2!=-5555 && P2_HurtBox07y2!=-5555 ) {
temp1x=P2hb_HurtBox07x1; temp1y=P2hb_HurtBox07y1; temp2x=P2hb_HurtBox07x2; temp2y=P2hb_HurtBox07y2;
if (temp1x<=temp2x) { P2hb_HurtBox07x1=temp1x; P2hb_HurtBox07x2=temp2x; } else { P2hb_HurtBox07x1=temp2x; P2hb_HurtBox07x2=temp1x; } if (P2hb_HurtBox07x1<0) { P2hb_HurtBox07x1=0; }
if ( (P2hb_HurtBox07x1+(P2hb_HurtBox07x2-P2hb_HurtBox07x1)>P1hb_HitBox09x1) && (P2hb_HurtBox07x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox07y1+(P2hb_HurtBox07y2-P2hb_HurtBox07y1)>P1hb_HitBox09y1) && (P2hb_HurtBox07y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; } }
//x8
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox08x1!=-5555 && P2_HurtBox08y1!=-5555 && P2_HurtBox08x2!=-5555 && P2_HurtBox08y2!=-5555 ) {
temp1x=P2hb_HurtBox08x1; temp1y=P2hb_HurtBox08y1; temp2x=P2hb_HurtBox08x2; temp2y=P2hb_HurtBox08y2;
if (temp1x<=temp2x) { P2hb_HurtBox08x1=temp1x; P2hb_HurtBox08x2=temp2x; } else { P2hb_HurtBox08x1=temp2x; P2hb_HurtBox08x2=temp1x; } if (P2hb_HurtBox08x1<0) { P2hb_HurtBox08x1=0; }
if ( (P2hb_HurtBox08x1+(P2hb_HurtBox08x2-P2hb_HurtBox08x1)>P1hb_HitBox09x1) && (P2hb_HurtBox08x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox08y1+(P2hb_HurtBox08y2-P2hb_HurtBox08y1)>P1hb_HitBox09y1) && (P2hb_HurtBox08y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; } }
//x9
if (colisaoxP2==0 && P1_HitBox09x1 !=+5555 && P1_HitBox09y1 !=+5555 && P1_HitBox09x2 !=+5555 && P1_HitBox09y2 !=+5555 && P2_HurtBox09x1!=-5555 && P2_HurtBox09y1!=-5555 && P2_HurtBox09x2!=-5555 && P2_HurtBox09y2!=-5555 ) {
temp1x=P2hb_HurtBox09x1; temp1y=P2hb_HurtBox09y1; temp2x=P2hb_HurtBox09x2; temp2y=P2hb_HurtBox09y2;
if (temp1x<=temp2x) { P2hb_HurtBox09x1=temp1x; P2hb_HurtBox09x2=temp2x; } else { P2hb_HurtBox09x1=temp2x; P2hb_HurtBox09x2=temp1x; } if (P2hb_HurtBox09x1<0) { P2hb_HurtBox09x1=0; }
if ( (P2hb_HurtBox09x1+(P2hb_HurtBox09x2-P2hb_HurtBox09x1)>P1hb_HitBox09x1) && (P2hb_HurtBox09x1<P1hb_HitBox09x1+(P1hb_HitBox09x2-P1hb_HitBox09x1)) &&
(P2hb_HurtBox09y1+(P2hb_HurtBox09y2-P2hb_HurtBox09y1)>P1hb_HitBox09y1) && (P2hb_HurtBox09y1<P1hb_HitBox09y1+(P1hb_HitBox09y2-P1hb_HitBox09y1)) ) { colisaoxP2=1; alturadohitp1=9; } else { colisaoxP2=0; } } }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HIT! houve colisao, o golpe acertou ----------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//aumenta barra de Special
if ( colisaoxP1==1 && AHitP2==1 ) { P[2].Special+=P[2].SpecialChange; P[1].EnergyRedBarSleep=60; }
if ( colisaoxP2==1 && AHitP1==1 ) { P[1].Special+=P[1].SpecialChange; P[2].EnergyRedBarSleep=60; }

//Calcula x e y dos hits
if ( colisaoxP1==1 ) {
if ( alturadohitp2==1 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox01x2)*2;
int y1=((P[2].y*2)+P2_HitBox01y1*2);
int y2=((P[2].y*2)+P2_HitBox01y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==2 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox02x2)*2;
int y1=((P[2].y*2)+P2_HitBox02y1*2);
int y2=((P[2].y*2)+P2_HitBox02y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==3 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox03x2)*2;
int y1=((P[2].y*2)+P2_HitBox03y1*2);
int y2=((P[2].y*2)+P2_HitBox03y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==4 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox04x2)*2;
int y1=((P[2].y*2)+P2_HitBox04y1*2);
int y2=((P[2].y*2)+P2_HitBox04y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==5 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox05x2)*2;
int y1=((P[2].y*2)+P2_HitBox05y1*2);
int y2=((P[2].y*2)+P2_HitBox05y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==6 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox06x2)*2;
int y1=((P[2].y*2)+P2_HitBox06y1*2);
int y2=((P[2].y*2)+P2_HitBox06y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==7 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox07x2)*2;
int y1=((P[2].y*2)+P2_HitBox07y1*2);
int y2=((P[2].y*2)+P2_HitBox07y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==8 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox08x2)*2;
int y1=((P[2].y*2)+P2_HitBox08y1*2);
int y2=((P[2].y*2)+P2_HitBox08y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp2==9 ) {
P2_Hit_x=(P[2].x*2)+(P[2].Lado*P2_HitBox09x2)*2;
int y1=((P[2].y*2)+P2_HitBox09y1*2);
int y2=((P[2].y*2)+P2_HitBox09y2*2);
P2_Hit_y=((y1-y2)/2)+y2;
}
}
if ( colisaoxP2==1 ) {
if ( alturadohitp1==1 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox01x2)*2;
int y1=((P[1].y*2)+P1_HitBox01y1*2);
int y2=((P[1].y*2)+P1_HitBox01y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==2 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox02x2)*2;
int y1=((P[1].y*2)+P1_HitBox02y1*2);
int y2=((P[1].y*2)+P1_HitBox02y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==3 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox03x2)*2;
int y1=((P[1].y*2)+P1_HitBox03y1*2);
int y2=((P[1].y*2)+P1_HitBox03y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==4 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox04x2)*2;
int y1=((P[1].y*2)+P1_HitBox04y1*2);
int y2=((P[1].y*2)+P1_HitBox04y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==5 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox05x2)*2;
int y1=((P[1].y*2)+P1_HitBox05y1*2);
int y2=((P[1].y*2)+P1_HitBox05y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==6 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox06x2)*2;
int y1=((P[1].y*2)+P1_HitBox06y1*2);
int y2=((P[1].y*2)+P1_HitBox06y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==7 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox07x2)*2;
int y1=((P[1].y*2)+P1_HitBox07y1*2);
int y2=((P[1].y*2)+P1_HitBox07y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==8 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox08x2)*2;
int y1=((P[1].y*2)+P1_HitBox08y1*2);
int y2=((P[1].y*2)+P1_HitBox08y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
if ( alturadohitp1==9 ) {
P1_Hit_x=(P[1].x*2)+(P[1].Lado*P1_HitBox09x2)*2;
int y1=((P[1].y*2)+P1_HitBox09y1*2);
int y2=((P[1].y*2)+P1_HitBox09y2*2);
P1_Hit_y=((y1-y2)/2)+y2;
}
}

//if P1_HurtBoxNum==0 { colisaoxP1=0; }
//if P2_HitBoxNum==0 { colisaoxP1=0; }
}

//Aplicar HIT
void Aplicar_HIT(){
///HIT!!!

MomentoDoP1=0;
MomentoDoP2=0;

//ForcaDoGolpeP1=0;
//ForcaDoGolpeP2=0;
//Ao nao zerar a ForcaDoGolpe, essa variavel acaba guardando a forca do ultimo golpe dado

if (
P[1].State==101 || P[1].State==104 ||
P[1].State==111 || P[1].State==114 ||
P[1].State==151 || P[1].State==154 ||
P[1].State==201 || P[1].State==204 ||
P[1].State==211 || P[1].State==214 ||
P[1].State==221 || P[1].State==224 ||
P[1].State==301 || P[1].State==304 ||
P[1].State==311 || P[1].State==314 ||
P[1].State==321 || P[1].State==324 ||
P[1].State==411 || P[1].State==414 ||
P[1].State==421 || P[1].State==424 )
{ ForcaDoGolpeP1=1; }

if (
P[1].State==102 || P[1].State==105 ||
P[1].State==112 || P[1].State==115 ||
P[1].State==152 || P[1].State==155 ||
P[1].State==202 || P[1].State==205 ||
P[1].State==212 || P[1].State==215 ||
P[1].State==222 || P[1].State==225 ||
P[1].State==302 || P[1].State==305 ||
P[1].State==312 || P[1].State==315 ||
P[1].State==322 || P[1].State==325 ||
P[1].State==412 || P[1].State==415 ||
P[1].State==422 || P[1].State==425 )
{ ForcaDoGolpeP1=2; }

if (
P[1].State==103 || P[1].State==106 ||
P[1].State==113 || P[1].State==116 ||
P[1].State==153 || P[1].State==156 ||
P[1].State==203 || P[1].State==206 ||
P[1].State==213 || P[1].State==216 ||
P[1].State==223 || P[1].State==226 ||
P[1].State==303 || P[1].State==306 ||
P[1].State==313 || P[1].State==316 ||
P[1].State==323 || P[1].State==326 ||
P[1].State==413 || P[1].State==416 ||
P[1].State==423 || P[1].State==426 )
{ ForcaDoGolpeP1=3; }

if (colisaoxP2==1 && AHitP1==1)New_HitBox(Qtde_HitBox+1);
if (colisaoxP1==1 && AHitP2==1)New_HitBox(Qtde_HitBox+1);

if (
P[1].State==100 ||
P[1].State==101 || P[1].State==102 || P[1].State==103 || P[1].State==104 || P[1].State==105 || P[1].State==106 ||
P[1].State==151 || P[1].State==152 || P[1].State==153 || P[1].State==154 || P[1].State==155 || P[1].State==156 ||
P[1].State==111 || P[1].State==112 || P[1].State==113 || P[1].State==114 || P[1].State==115 || P[1].State==116 ||
P[1].State==411 || P[1].State==412 || P[1].State==413 || P[1].State==414 || P[1].State==415 || P[1].State==416 ||
P[1].State==421 || P[1].State==422 || P[1].State==423 || P[1].State==424 || P[1].State==425 || P[1].State==426 ||
P[1].State==410 || P[1].State==420 || P[1].State==602 || P[1].State==603 || P[1].State==604 || P[1].State==605 ||
P[1].State==606 || P[1].State==607 )
{ MomentoDoP1=1; } //De pe

if (
P[1].State==200 ||
P[1].State==201 || P[1].State==202 || P[1].State==203 || P[1].State==204 || P[1].State==205 || P[1].State==206 ||
P[1].State==211 || P[1].State==212 || P[1].State==213 || P[1].State==214 || P[1].State==215 || P[1].State==216 ||
P[1].State==221 || P[1].State==222 || P[1].State==223 || P[1].State==224 || P[1].State==225 || P[1].State==226 ||
P[1].State==601 || P[1].State==608 )
{ MomentoDoP1=2; } //Abaixado

if (
P[1].State==300 || P[1].State==310 || P[1].State==320 ||
P[1].State==301 || P[1].State==302 || P[1].State==303 || P[1].State==304 || P[1].State==305 || P[1].State==306 ||
P[1].State==311 || P[1].State==312 || P[1].State==313 || P[1].State==314 || P[1].State==315 || P[1].State==316 ||
P[1].State==321 || P[1].State==322 || P[1].State==323 || P[1].State==324 || P[1].State==325 || P[1].State==326 )
{ MomentoDoP1=3; } //Pulando

if (P[1].State==501 || P[1].State==502 || P[1].State==503 )
{ MomentoDoP1=51; } //Hurt em pe
if (P[1].State==511 || P[1].State==512 || P[1].State==513 )
{ MomentoDoP1=51; } //Hurt em pe
if ( P[1].State==504 || P[1].State==505 || P[1].State==506  )
{ MomentoDoP1=52; } //Hurt abaixado
if ( P[1].State==507 || P[1].State==508 || P[1].State==509  )
{ MomentoDoP1=53; } //Hurt em pe

if ( P[1].State==250 )
{ MomentoDoP1=9; } //Defesa Abaixado
if ( P[1].State==450 )
{ MomentoDoP1=9; } //Defesa em Pe

if (
P[2].State==101 || P[2].State==104 ||
P[2].State==111 || P[2].State==114 ||
P[2].State==151 || P[2].State==154 ||
P[2].State==201 || P[2].State==204 ||
P[2].State==211 || P[2].State==214 ||
P[2].State==221 || P[2].State==224 ||
P[2].State==301 || P[2].State==304 ||
P[2].State==311 || P[2].State==314 ||
P[2].State==321 || P[2].State==324 ||
P[2].State==411 || P[2].State==414 ||
P[2].State==421 || P[2].State==424 )
{ ForcaDoGolpeP2=1; }

if (
P[2].State==102 || P[2].State==105 ||
P[2].State==112 || P[2].State==115 ||
P[2].State==152 || P[2].State==155 ||
P[2].State==202 || P[2].State==205 ||
P[2].State==212 || P[2].State==215 ||
P[2].State==222 || P[2].State==225 ||
P[2].State==302 || P[2].State==305 ||
P[2].State==312 || P[2].State==315 ||
P[2].State==322 || P[2].State==325 ||
P[2].State==412 || P[2].State==415 ||
P[2].State==422 || P[2].State==425 )
{ ForcaDoGolpeP2=2; }

if (
P[2].State==103 || P[2].State==106 ||
P[2].State==113 || P[2].State==116 ||
P[2].State==153 || P[2].State==156 ||
P[2].State==203 || P[2].State==206 ||
P[2].State==213 || P[2].State==216 ||
P[2].State==223 || P[2].State==226 ||
P[2].State==303 || P[2].State==306 ||
P[2].State==313 || P[2].State==316 ||
P[2].State==323 || P[2].State==326 ||
P[2].State==413 || P[2].State==416 ||
P[2].State==423 || P[2].State==426 )
{ ForcaDoGolpeP2=3; }

if (
P[2].State==100 ||
P[2].State==101 || P[2].State==102 || P[2].State==103 || P[2].State==104 || P[2].State==105 || P[2].State==106 ||
P[2].State==151 || P[2].State==152 || P[2].State==153 || P[2].State==154 || P[2].State==155 || P[2].State==156 ||
P[2].State==111 || P[2].State==112 || P[2].State==113 || P[2].State==114 || P[2].State==115 || P[2].State==116 ||
P[2].State==411 || P[2].State==412 || P[2].State==413 || P[2].State==414 || P[2].State==415 || P[2].State==416 ||
P[2].State==421 || P[2].State==422 || P[2].State==423 || P[2].State==424 || P[2].State==425 || P[2].State==426 ||
P[2].State==410 || P[2].State==420 || P[2].State==602 || P[2].State==603 || P[2].State==604 || P[2].State==605 ||
P[2].State==606 || P[2].State==607 )
{ MomentoDoP2=1; } //De Pe

if (
P[2].State==200 ||
P[2].State==201 || P[2].State==202 || P[2].State==203 || P[2].State==204 || P[2].State==205 || P[2].State==206 ||
P[2].State==211 || P[2].State==212 || P[2].State==213 || P[2].State==214 || P[2].State==215 || P[2].State==216 ||
P[2].State==221 || P[2].State==222 || P[2].State==223 || P[2].State==224 || P[2].State==225 || P[2].State==226 ||
P[2].State==601 || P[2].State==608 )
{ MomentoDoP2=2; } //Abaixado

if (
P[2].State==300 || P[2].State==310 || P[2].State==320 ||
P[2].State==301 || P[2].State==302 || P[2].State==303 || P[2].State==304 || P[2].State==305 || P[2].State==306 ||
P[2].State==311 || P[2].State==312 || P[2].State==313 || P[2].State==314 || P[2].State==315 || P[2].State==316 ||
P[2].State==321 || P[2].State==322 || P[2].State==323 || P[2].State==324 || P[2].State==325 || P[2].State==326 )
{ MomentoDoP2=3; } //Pulando

if ( P[2].State==501 || P[2].State==502 || P[2].State==503  )
{ MomentoDoP2=51; } //Hurt em pe
if ( P[2].State==511 || P[2].State==512 || P[2].State==513  )
{ MomentoDoP2=51; } //Hurt em pe
if ( P[2].State==504 || P[2].State==505 || P[2].State==506  )
{ MomentoDoP2=52; } //Hurt abaixado
if ( P[2].State==507 || P[2].State==508 || P[2].State==509  )
{ MomentoDoP2=53; } //Hurt no ar

if ( P[2].State==250 )
{ MomentoDoP2=9; } //Defesa Abaixado
if ( P[2].State==450 )
{ MomentoDoP2=9; } //Defesa em Pe

//importante!
//HitPause Padrao
HitPause1=15; HitPause2=15; HitPause3=15; //<-hitpause
//damage
if(P[1].ChangeDamage==0){
P1_DMG1=50;
P1_DMG2=100;
P1_DMG3=150;
}else{
P1_DMG1=P[1].ChangeDamage;
P1_DMG2=P[1].ChangeDamage;
P1_DMG3=P[1].ChangeDamage;
}
if(P[2].ChangeDamage==0){
P2_DMG1=50;
P2_DMG2=100;
P2_DMG3=150;
}else{
P2_DMG1=P[2].ChangeDamage;
P2_DMG2=P[2].ChangeDamage;
P2_DMG3=P[2].ChangeDamage;
}

char P1_Caminho[99];
char P2_Caminho[99];

//P2 HitType
int line=0;
for(int indx=0;indx<=500;indx++){
if( P[2].State==P[2].TableAtlas[indx][0]
&& P[2].IndexAnim==P[2].TableAtlas[indx][1]){
line=P[2].TableAtlas[indx][2];
}
if(line!=0) break;
}
if(P[2].TableAtlas[line][16] == 1) { strcpy(P[2].HitType_string, "Normal"); }
if(P[2].TableAtlas[line][16] == 2) { strcpy(P[2].HitType_string, "Fall"); }
if(P[2].TableAtlas[line][20] == 1) { strcpy(P[2].HitStack_string, "Single"); }
if(P[2].TableAtlas[line][20] == 2) { strcpy(P[2].HitStack_string, "Multi"); }

if ( colisaoxP1==1 || colisaoxP1Fireball==1 )
{

//colisao contra P1 de uma fireball lançada pelo P2
if(colisaoxP1Fireball==1){
if(P[2].TotalDeFramesMov[702] >-1){
Fireball[2].State=702;
char P2_Caminho[99];
sprintf(P2_Caminho, "data/chars/%s/char.ini", P[2].Name);
backend_set_config_file(P2_Caminho);
Fireball[2].XAlign = backend_get_config_int ("702", "XAlign" , 0 );
Fireball[2].YAlign = backend_get_config_int ("702", "YAlign" , 0 );
Fireball[2].TotalFrames=P[2].TotalDeFramesMov[702];
//Fireball[2].Ativa=0;
Fireball[2].IndexAnim=0; //dan
Fireball[2].VSpeed=0;
Fireball[2].HSpeed=0;
colisaoxP1Fireball=0;
P2_Fireball_HitBox01x1=+5555;
P2_Fireball_HitBox01y1=+5555;
P2_Fireball_HitBox01x2=+5555;
P2_Fireball_HitBox01y2=+5555;
}else{
colisaoxP1Fireball=0;
Fireball[2].Ativa=0;
Fireball[2].x=-999;
Fireball[2].y=-999;
P[2].QtdeMagias=0;
}
}

//FSM
if ( strcmp( P[2].HitType_string,"Fall") ==0 && AHitP2==1 ) {
AHitP2=0;
P[1].StartFrame=timer;
PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]);
P1HitPause=HitPause3; //teste
P2HitPause=HitPause3;
if (ForcaDoGolpeP2==1) {P[1].Energy-=P2_DMG1;}
if (ForcaDoGolpeP2==2) {P[1].Energy-=P2_DMG2;}
if (ForcaDoGolpeP2==3) {P[1].Energy-=P2_DMG3;}
P2HitOn=P[2].IndexAnim;
}
if ( ForcaDoGolpeP2== 1 && MomentoDoP1== 1 && MomentoDoP2== 3 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 511, 0, P[1].TotalDeFramesMov[511]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1== 1 && MomentoDoP2== 3 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 512, 0, P[1].TotalDeFramesMov[512]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1== 1 && MomentoDoP2== 3 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 513, 0, P[1].TotalDeFramesMov[513]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 1 && MomentoDoP1== 1 && MomentoDoP2== 2 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 511, 0, P[1].TotalDeFramesMov[511]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1== 1 && MomentoDoP2== 2 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 512, 0, P[1].TotalDeFramesMov[512]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1== 1 && MomentoDoP2== 2 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 513, 0, P[1].TotalDeFramesMov[513]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 1 && MomentoDoP1== 1 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 501, 0, P[1].TotalDeFramesMov[501]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1== 1 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 502, 0, P[1].TotalDeFramesMov[502]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1== 1 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 503, 0, P[1].TotalDeFramesMov[503]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 1 && MomentoDoP1== 2 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 504, 0, P[1].TotalDeFramesMov[504]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1== 2 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 505, 0, P[1].TotalDeFramesMov[505]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1== 2 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 506, 0, P[1].TotalDeFramesMov[506]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
//reversao aerea do P1 Mov 507
if ( ForcaDoGolpeP2== 1 && MomentoDoP1== 3 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 507, 0, P[1].TotalDeFramesMov[507]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1== 3 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 507, 0, P[1].TotalDeFramesMov[507]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1== 3 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 507, 0, P[1].TotalDeFramesMov[507]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
//fim das reversoes
if ( ForcaDoGolpeP2==51 && MomentoDoP1== 1 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 501, 0, P[1].TotalDeFramesMov[501]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2==51 && MomentoDoP1== 1 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 502, 0, P[1].TotalDeFramesMov[502]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2==51 && MomentoDoP1== 1 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 503, 0, P[1].TotalDeFramesMov[503]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 1 && MomentoDoP1==51 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 501, 0, P[1].TotalDeFramesMov[501]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1==51 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 502, 0, P[1].TotalDeFramesMov[502]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1==51 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 503, 0, P[1].TotalDeFramesMov[503]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 1 && MomentoDoP1==52 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 504, 0, P[1].TotalDeFramesMov[504]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1==52 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 505, 0, P[1].TotalDeFramesMov[505]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1==52 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 506, 0, P[1].TotalDeFramesMov[506]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 1 && MomentoDoP1==53 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]); P2HitPause=HitPause1; P[1].Energy-=P2_DMG1; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1==53 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]); P2HitPause=HitPause2; P[1].Energy-=P2_DMG2; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1==53 && AHitP2==1 ) { AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]); P2HitPause=HitPause3; P[1].Energy-=P2_DMG3; P2HitOn=P[2].IndexAnim; }
//defesa
if ( ForcaDoGolpeP2== 1 && MomentoDoP1== 9 && AHitP2==1 ) { AHitP2=0; P2HitPause=HitPause1; P[1].Energy-=0; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 2 && MomentoDoP1== 9 && AHitP2==1 ) { AHitP2=0; P2HitPause=HitPause2; P[1].Energy-=0; P2HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP2== 3 && MomentoDoP1== 9 && AHitP2==1 ) { AHitP2=0; P2HitPause=HitPause3; P[1].Energy-=0; P2HitOn=P[2].IndexAnim; }
//derrota por KO
if (P[1].Energy<=0) { backend_rest(HitPauseKO); EndRoundSlowDown=1; AHitP2=0; P[1].StartFrame=timer; PLAYER_STATE(1, 570, 0, P[1].TotalDeFramesMov[570]); P2HitPause=HitPause3; P[1].Energy=0; P2HitOn=P[2].IndexAnim; }
}

//P1 HitType
line=0;
for(int indx=0;indx<=500;indx++){
if( P[1].State==P[1].TableAtlas[indx][0]
&& P[1].IndexAnim==P[1].TableAtlas[indx][1]){
line=P[1].TableAtlas[indx][2];
}
if(line!=0) break;
}
if(P[1].TableAtlas[line][16] == 1) { strcpy(P[1].HitType_string, "Normal"); }
if(P[1].TableAtlas[line][16] == 2) { strcpy(P[1].HitType_string, "Fall"); }
if(P[1].TableAtlas[line][20] == 1) { strcpy(P[1].HitStack_string, "Single"); }
if(P[1].TableAtlas[line][20] == 2) { strcpy(P[1].HitStack_string, "Multi"); }

if ( colisaoxP2==1 || colisaoxP2Fireball==1 )
{

//colisao contra P2 de uma fireball lançada pelo P1
if(colisaoxP2Fireball==1){
if(P[1].TotalDeFramesMov[702] >-1){
Fireball[1].State=702;
char P1_Caminho[99];
sprintf(P1_Caminho, "data/chars/%s/char.ini", P[1].Name);
backend_set_config_file(P1_Caminho);
Fireball[1].XAlign = backend_get_config_int ("702", "XAlign" , 0 );
Fireball[1].YAlign = backend_get_config_int ("702", "YAlign" , 0 );
Fireball[1].TotalFrames=P[1].TotalDeFramesMov[702];
//Fireball[1].Ativa=0;
Fireball[1].IndexAnim=0; //dan
Fireball[1].VSpeed=0;
Fireball[1].HSpeed=0;
colisaoxP2Fireball=0;
P1_Fireball_HitBox01x1=-5555;
P1_Fireball_HitBox01y1=-5555;
P1_Fireball_HitBox01x2=-5555;
P1_Fireball_HitBox01y2=-5555;
}else{
colisaoxP2Fireball=0;
Fireball[1].Ativa=0;
Fireball[1].x=-999;
Fireball[1].y=-999;
P[1].QtdeMagias=0;
}
}

//FSM
if ( strcmp( P[1].HitType_string,"Fall") ==0 && AHitP1==1 ) {
AHitP1=0;
P[2].StartFrame=timer;
PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]);
P2HitPause=HitPause3; //teste
P1HitPause=HitPause3;
if (ForcaDoGolpeP1==1) {P[2].Energy-=P1_DMG1;}
if (ForcaDoGolpeP1==2) {P[2].Energy-=P1_DMG2;}
if (ForcaDoGolpeP1==3) {P[2].Energy-=P1_DMG3;}
P1HitOn=P[2].IndexAnim;
}
if ( ForcaDoGolpeP1== 1 && MomentoDoP2== 1 && MomentoDoP1== 3 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 511, 0, P[2].TotalDeFramesMov[511]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2== 1 && MomentoDoP1== 3 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 512, 0, P[2].TotalDeFramesMov[512]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2== 1 && MomentoDoP1== 3 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 513, 0, P[2].TotalDeFramesMov[513]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 1 && MomentoDoP2== 1 && MomentoDoP1== 2 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 511, 0, P[2].TotalDeFramesMov[511]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2== 1 && MomentoDoP1== 2 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 512, 0, P[2].TotalDeFramesMov[512]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2== 1 && MomentoDoP1== 2 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 513, 0, P[2].TotalDeFramesMov[513]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 1 && MomentoDoP2== 1 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 501, 0, P[2].TotalDeFramesMov[501]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2== 1 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 502, 0, P[2].TotalDeFramesMov[502]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2== 1 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 503, 0, P[2].TotalDeFramesMov[503]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 1 && MomentoDoP2== 2 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 504, 0, P[2].TotalDeFramesMov[504]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2== 2 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 505, 0, P[2].TotalDeFramesMov[505]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2== 2 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 506, 0, P[2].TotalDeFramesMov[506]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
//reversao aerea do P2 Mov 507
if ( ForcaDoGolpeP1== 1 && MomentoDoP2== 3 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 507, 0, P[2].TotalDeFramesMov[507]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2== 3 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 507, 0, P[2].TotalDeFramesMov[507]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2== 3 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 507, 0, P[2].TotalDeFramesMov[507]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
//fim das reversoes
if ( ForcaDoGolpeP1==51 && MomentoDoP2== 1 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 501, 0, P[2].TotalDeFramesMov[501]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1==51 && MomentoDoP2== 1 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 502, 0, P[2].TotalDeFramesMov[502]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1==51 && MomentoDoP2== 1 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 503, 0, P[2].TotalDeFramesMov[503]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 1 && MomentoDoP2==51 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 501, 0, P[2].TotalDeFramesMov[501]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2==51 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 502, 0, P[2].TotalDeFramesMov[502]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2==51 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 503, 0, P[2].TotalDeFramesMov[503]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 1 && MomentoDoP2==52 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 504, 0, P[2].TotalDeFramesMov[504]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2==52 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 505, 0, P[2].TotalDeFramesMov[505]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2==52 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 506, 0, P[2].TotalDeFramesMov[506]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 1 && MomentoDoP2==53 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]); P1HitPause=HitPause1; P[2].Energy-=P1_DMG1; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2==53 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]); P1HitPause=HitPause2; P[2].Energy-=P1_DMG2; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2==53 && AHitP1==1 ) { AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]); P1HitPause=HitPause3; P[2].Energy-=P1_DMG3; P1HitOn=P[2].IndexAnim; }
//defesa
if ( ForcaDoGolpeP1== 1 && MomentoDoP2== 9 && AHitP1==1 ) { AHitP1=0; P1HitPause=HitPause1; P[2].Energy-=0; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 2 && MomentoDoP2== 9 && AHitP1==1 ) { AHitP1=0; P1HitPause=HitPause2; P[2].Energy-=0; P1HitOn=P[2].IndexAnim; }
if ( ForcaDoGolpeP1== 3 && MomentoDoP2== 9 && AHitP1==1 ) { AHitP1=0; P1HitPause=HitPause3; P[2].Energy-=0; P1HitOn=P[2].IndexAnim; }
//derrota por KO
if (P[2].Energy<=0) { backend_rest(HitPauseKO); EndRoundSlowDown=1; AHitP1=0; P[2].StartFrame=timer; PLAYER_STATE(2, 570, 0, P[2].TotalDeFramesMov[570]); P1HitPause=HitPause3; P[2].Energy=0; P1HitOn=P[2].IndexAnim; }
}

//Chacoalha os personagens após o Hit, e os desloca
if (P1HitPause>0 || P2HitPause>0)
{
ShakeDist=ShakeDist*-1;
int AcelFraca=1.8;
int AcelMedia=2.0;
int AcelForte=2.2;
if (P1HitPause>0)
{
P1HitPause--;
if ( P1HitPause==1 )
{
if ( ForcaDoGolpeP1==1 ) { P[2].Hspeed=AcelFraca*P[1].Lado; P[2].Friction=5; }
if ( ForcaDoGolpeP1==2 ) { P[2].Hspeed=AcelMedia*P[1].Lado; P[2].Friction=5; }
if ( ForcaDoGolpeP1==3 ) { P[2].Hspeed=AcelForte*P[1].Lado; P[2].Friction=5; }
}
}
if (P2HitPause>0)
{
P2HitPause--;
if ( P2HitPause==1 )
{
if ( ForcaDoGolpeP2==1 ) { P[1].Hspeed=AcelFraca*P[2].Lado; P[1].Friction=5; }
if ( ForcaDoGolpeP2==2 ) { P[1].Hspeed=AcelMedia*P[2].Lado; P[1].Friction=5; }
if ( ForcaDoGolpeP2==3 ) { P[1].Hspeed=AcelForte*P[2].Lado; P[1].Friction=5; }
}
}
}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ZERA INPUTS DO INPUT DISPLAY -----------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zeraListaDeInputs(){
int i;
for(i=0;i<=17;i++){
P[1].slot[i]=0;
P[1].bt_slot[i]=0;
P[1].t_slot[i]=0;
P[1].ticks_4slot=0;
P[2].slot[i]=0;
P[2].bt_slot[i]=0;
P[2].t_slot[i]=0;
P[2].ticks_4slot=0;
}
for(i=1; i<=2;i++){
P[i].key_UP_pressed=0; P[i].key_UP_released=0; P[i].key_UP_hold=0; P[i].key_UP_status=0;
P[i].key_DOWN_pressed=0; P[i].key_DOWN_released=0; P[i].key_DOWN_hold=0; P[i].key_DOWN_status=0;
P[i].key_LEFT_pressed=0; P[i].key_LEFT_released=0; P[i].key_LEFT_hold=0; P[i].key_LEFT_status=0;
P[i].key_RIGHT_pressed=0; P[i].key_RIGHT_released=0; P[i].key_RIGHT_hold=0; P[i].key_RIGHT_status=0;
P[i].key_BT1_pressed=0; P[i].key_BT1_released=0; P[i].key_BT1_hold=0; P[i].key_BT1_status=0;
P[i].key_BT2_pressed=0; P[i].key_BT2_released=0; P[i].key_BT2_hold=0; P[i].key_BT2_status=0;
P[i].key_BT3_pressed=0; P[i].key_BT3_released=0; P[i].key_BT3_hold=0; P[i].key_BT3_status=0;
P[i].key_BT4_pressed=0; P[i].key_BT4_released=0; P[i].key_BT4_hold=0; P[i].key_BT4_status=0;
P[i].key_BT5_pressed=0; P[i].key_BT5_released=0; P[i].key_BT5_hold=0; P[i].key_BT5_status=0;
P[i].key_BT6_pressed=0; P[i].key_BT6_released=0; P[i].key_BT6_hold=0; P[i].key_BT6_status=0;
P[i].key_SELECT_pressed=0; P[i].key_SELECT_released=0; P[i].key_SELECT_hold=0; P[i].key_SELECT_status=0;
P[i].key_START_pressed=0; P[i].key_START_released=0; P[i].key_START_hold=0; P[i].key_START_status=0;
}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CRIA NOVA FIREBALL ---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void New_Fireball(int Player){

char P1_Caminho[99];
char P2_Caminho[99];
char P1_Caminho_sp[99];
char P2_Caminho_sp[99];

if(P[Player].State==700 && P[Player].TotalDeFramesMov[701]>-1 && P[Player].QtdeMagias==0){

if(Player==1){
sprintf(P1_Caminho, "data/chars/%s/char.ini", P[Player].Name);
backend_set_config_file(P1_Caminho);
}
if(Player==2){
sprintf(P2_Caminho, "data/chars/%s/char.ini", P[Player].Name);
backend_set_config_file(P2_Caminho);
}

P[Player].QtdeMagias++;
Fireball[Player].Ativa = 1;
Fireball[Player].Direcao = P[Player].Lado;
Fireball[Player].State = 701;
sprintf(Fireball[Player].State_s, "%i" , Fireball[Player].State);
Fireball[Player].XAlign = backend_get_config_int (Fireball[Player].State_s, "XAlign" , 0 );
Fireball[Player].YAlign = backend_get_config_int (Fireball[Player].State_s, "YAlign" , 0 );
Fireball[Player].TotalFrames=P[Player].TotalDeFramesMov[701];
//Fireball[Player].StartFrame=time;
if(Player==1){
//tem q verificar a força de variacao tb (DMG), vou implementar depois.
//V1 = fraco, V2 = medio, V3 = forte
if(ForcaDoGolpeP1==1){
if (Fireball[Player].TotalFrames>= 0) {P1_Fireball_FrameTime_00 = backend_get_config_int("701", "V1_FrameTime_00", 6)-1; }
if (Fireball[Player].TotalFrames>= 1) {P1_Fireball_FrameTime_01 = backend_get_config_int("701", "V1_FrameTime_01", 6)-1; }
if (Fireball[Player].TotalFrames>= 2) {P1_Fireball_FrameTime_02 = backend_get_config_int("701", "V1_FrameTime_02", 6)-1; }
if (Fireball[Player].TotalFrames>= 3) {P1_Fireball_FrameTime_03 = backend_get_config_int("701", "V1_FrameTime_03", 6)-1; }
if (Fireball[Player].TotalFrames>= 4) {P1_Fireball_FrameTime_04 = backend_get_config_int("701", "V1_FrameTime_04", 6)-1; }
if (Fireball[Player].TotalFrames>= 5) {P1_Fireball_FrameTime_05 = backend_get_config_int("701", "V1_FrameTime_05", 6)-1; }
if (Fireball[Player].TotalFrames>= 6) {P1_Fireball_FrameTime_06 = backend_get_config_int("701", "V1_FrameTime_06", 6)-1; }
if (Fireball[Player].TotalFrames>= 7) {P1_Fireball_FrameTime_07 = backend_get_config_int("701", "V1_FrameTime_07", 6)-1; }
if (Fireball[Player].TotalFrames>= 8) {P1_Fireball_FrameTime_08 = backend_get_config_int("701", "V1_FrameTime_08", 6)-1; }
if (Fireball[Player].TotalFrames>= 9) {P1_Fireball_FrameTime_09 = backend_get_config_int("701", "V1_FrameTime_09", 6)-1; }
if (Fireball[Player].TotalFrames>=10) {P1_Fireball_FrameTime_10 = backend_get_config_int("701", "V1_FrameTime_10", 6)-1; }
}
if(ForcaDoGolpeP1==2){
if (Fireball[Player].TotalFrames>= 0) {P1_Fireball_FrameTime_00 = backend_get_config_int("701", "V2_FrameTime_00", 6)-1; }
if (Fireball[Player].TotalFrames>= 1) {P1_Fireball_FrameTime_01 = backend_get_config_int("701", "V2_FrameTime_01", 6)-1; }
if (Fireball[Player].TotalFrames>= 2) {P1_Fireball_FrameTime_02 = backend_get_config_int("701", "V2_FrameTime_02", 6)-1; }
if (Fireball[Player].TotalFrames>= 3) {P1_Fireball_FrameTime_03 = backend_get_config_int("701", "V2_FrameTime_03", 6)-1; }
if (Fireball[Player].TotalFrames>= 4) {P1_Fireball_FrameTime_04 = backend_get_config_int("701", "V2_FrameTime_04", 6)-1; }
if (Fireball[Player].TotalFrames>= 5) {P1_Fireball_FrameTime_05 = backend_get_config_int("701", "V2_FrameTime_05", 6)-1; }
if (Fireball[Player].TotalFrames>= 6) {P1_Fireball_FrameTime_06 = backend_get_config_int("701", "V2_FrameTime_06", 6)-1; }
if (Fireball[Player].TotalFrames>= 7) {P1_Fireball_FrameTime_07 = backend_get_config_int("701", "V2_FrameTime_07", 6)-1; }
if (Fireball[Player].TotalFrames>= 8) {P1_Fireball_FrameTime_08 = backend_get_config_int("701", "V2_FrameTime_08", 6)-1; }
if (Fireball[Player].TotalFrames>= 9) {P1_Fireball_FrameTime_09 = backend_get_config_int("701", "V2_FrameTime_09", 6)-1; }
if (Fireball[Player].TotalFrames>=10) {P1_Fireball_FrameTime_10 = backend_get_config_int("701", "V2_FrameTime_10", 6)-1; }
}
if(ForcaDoGolpeP1==3){
if (Fireball[Player].TotalFrames>= 0) {P1_Fireball_FrameTime_00 = backend_get_config_int("701", "V3_FrameTime_00", 6)-1; }
if (Fireball[Player].TotalFrames>= 1) {P1_Fireball_FrameTime_01 = backend_get_config_int("701", "V3_FrameTime_01", 6)-1; }
if (Fireball[Player].TotalFrames>= 2) {P1_Fireball_FrameTime_02 = backend_get_config_int("701", "V3_FrameTime_02", 6)-1; }
if (Fireball[Player].TotalFrames>= 3) {P1_Fireball_FrameTime_03 = backend_get_config_int("701", "V3_FrameTime_03", 6)-1; }
if (Fireball[Player].TotalFrames>= 4) {P1_Fireball_FrameTime_04 = backend_get_config_int("701", "V3_FrameTime_04", 6)-1; }
if (Fireball[Player].TotalFrames>= 5) {P1_Fireball_FrameTime_05 = backend_get_config_int("701", "V3_FrameTime_05", 6)-1; }
if (Fireball[Player].TotalFrames>= 6) {P1_Fireball_FrameTime_06 = backend_get_config_int("701", "V3_FrameTime_06", 6)-1; }
if (Fireball[Player].TotalFrames>= 7) {P1_Fireball_FrameTime_07 = backend_get_config_int("701", "V3_FrameTime_07", 6)-1; }
if (Fireball[Player].TotalFrames>= 8) {P1_Fireball_FrameTime_08 = backend_get_config_int("701", "V3_FrameTime_08", 6)-1; }
if (Fireball[Player].TotalFrames>= 9) {P1_Fireball_FrameTime_09 = backend_get_config_int("701", "V3_FrameTime_09", 6)-1; }
if (Fireball[Player].TotalFrames>=10) {P1_Fireball_FrameTime_10 = backend_get_config_int("701", "V3_FrameTime_10", 6)-1; }
}
P1_Fireball_FrameTime = P1_Fireball_FrameTime_00;

sprintf(P1_Caminho_sp, "data/chars/%s/special.ini", P[Player].Name);
backend_set_config_file(P1_Caminho_sp);

int LocalPosX=backend_get_config_int (Fireball[Player].State_s, "LocalPosX" , 0 );
int LocalPosY=backend_get_config_int (Fireball[Player].State_s, "LocalPosY" , 0 );
Fireball[Player].x = P[Player].x+(LocalPosX*Fireball[Player].Direcao);
Fireball[Player].y = P[Player].y+LocalPosY;
Fireball[Player].HSpeed = backend_get_config_int("701", "HSpeed", 4)-1;
Fireball[Player].HSpeed+=1;
Fireball[Player].VSpeed = backend_get_config_int("701", "VSpeed", -1)-1;
Fireball[Player].VSpeed+=1;
Fireball[Player].ThrowFireball = backend_get_config_int (P[Player].State_s, "ThrowFireball" , 1 );

sprintf(P1_Caminho_sp, "data/chars/%s/chbox.ini", P[Player].Name);
backend_set_config_file(P1_Caminho_sp);
P1_Fireball_HurtBox01x1 = backend_get_config_int ("701_00", "HurtBox01x1" , -15 );
P1_Fireball_HurtBox01y1 = backend_get_config_int ("701_00", "HurtBox01y1" , -15 );
P1_Fireball_HurtBox01x2 = backend_get_config_int ("701_00", "HurtBox01x2" , 15 );
P1_Fireball_HurtBox01y2 = backend_get_config_int ("701_00", "HurtBox01y2" , 15 );
P1_Fireball_HitBox01x1 = backend_get_config_int ("701_00", "HitBox01x1" , -10 );
P1_Fireball_HitBox01y1 = backend_get_config_int ("701_00", "HitBox01y1" , -10 );
P1_Fireball_HitBox01x2 = backend_get_config_int ("701_00", "HitBox01x2" , -10 );
P1_Fireball_HitBox01y2 = backend_get_config_int ("701_00", "HitBox01y2" , -10 );
}

if(Player==2){
//tem q verificar a força de variacao tb (DMG), vou implementar depois.
//V1 = fraco, V2 = medio, V3 = forte
if(ForcaDoGolpeP2==1){
if (Fireball[Player].TotalFrames>= 0) {P2_Fireball_FrameTime_00 = backend_get_config_int("701", "V1_FrameTime_00", 6)-1; }
if (Fireball[Player].TotalFrames>= 1) {P2_Fireball_FrameTime_01 = backend_get_config_int("701", "V1_FrameTime_01", 6)-1; }
if (Fireball[Player].TotalFrames>= 2) {P2_Fireball_FrameTime_02 = backend_get_config_int("701", "V1_FrameTime_02", 6)-1; }
if (Fireball[Player].TotalFrames>= 3) {P2_Fireball_FrameTime_03 = backend_get_config_int("701", "V1_FrameTime_03", 6)-1; }
if (Fireball[Player].TotalFrames>= 4) {P2_Fireball_FrameTime_04 = backend_get_config_int("701", "V1_FrameTime_04", 6)-1; }
if (Fireball[Player].TotalFrames>= 5) {P2_Fireball_FrameTime_05 = backend_get_config_int("701", "V1_FrameTime_05", 6)-1; }
if (Fireball[Player].TotalFrames>= 6) {P2_Fireball_FrameTime_06 = backend_get_config_int("701", "V1_FrameTime_06", 6)-1; }
if (Fireball[Player].TotalFrames>= 7) {P2_Fireball_FrameTime_07 = backend_get_config_int("701", "V1_FrameTime_07", 6)-1; }
if (Fireball[Player].TotalFrames>= 8) {P2_Fireball_FrameTime_08 = backend_get_config_int("701", "V1_FrameTime_08", 6)-1; }
if (Fireball[Player].TotalFrames>= 9) {P2_Fireball_FrameTime_09 = backend_get_config_int("701", "V1_FrameTime_09", 6)-1; }
if (Fireball[Player].TotalFrames>=10) {P2_Fireball_FrameTime_10 = backend_get_config_int("701", "V1_FrameTime_10", 6)-1; }
}
if(ForcaDoGolpeP2==2){
if (Fireball[Player].TotalFrames>= 0) {P2_Fireball_FrameTime_00 = backend_get_config_int("701", "V2_FrameTime_00", 6)-1; }
if (Fireball[Player].TotalFrames>= 1) {P2_Fireball_FrameTime_01 = backend_get_config_int("701", "V2_FrameTime_01", 6)-1; }
if (Fireball[Player].TotalFrames>= 2) {P2_Fireball_FrameTime_02 = backend_get_config_int("701", "V2_FrameTime_02", 6)-1; }
if (Fireball[Player].TotalFrames>= 3) {P2_Fireball_FrameTime_03 = backend_get_config_int("701", "V2_FrameTime_03", 6)-1; }
if (Fireball[Player].TotalFrames>= 4) {P2_Fireball_FrameTime_04 = backend_get_config_int("701", "V2_FrameTime_04", 6)-1; }
if (Fireball[Player].TotalFrames>= 5) {P2_Fireball_FrameTime_05 = backend_get_config_int("701", "V2_FrameTime_05", 6)-1; }
if (Fireball[Player].TotalFrames>= 6) {P2_Fireball_FrameTime_06 = backend_get_config_int("701", "V2_FrameTime_06", 6)-1; }
if (Fireball[Player].TotalFrames>= 7) {P2_Fireball_FrameTime_07 = backend_get_config_int("701", "V2_FrameTime_07", 6)-1; }
if (Fireball[Player].TotalFrames>= 8) {P2_Fireball_FrameTime_08 = backend_get_config_int("701", "V2_FrameTime_08", 6)-1; }
if (Fireball[Player].TotalFrames>= 9) {P2_Fireball_FrameTime_09 = backend_get_config_int("701", "V2_FrameTime_09", 6)-1; }
if (Fireball[Player].TotalFrames>=10) {P2_Fireball_FrameTime_10 = backend_get_config_int("701", "V2_FrameTime_10", 6)-1; }
}
if(ForcaDoGolpeP2==3){
if (Fireball[Player].TotalFrames>= 0) {P2_Fireball_FrameTime_00 = backend_get_config_int("701", "V3_FrameTime_00", 6)-1; }
if (Fireball[Player].TotalFrames>= 1) {P2_Fireball_FrameTime_01 = backend_get_config_int("701", "V3_FrameTime_01", 6)-1; }
if (Fireball[Player].TotalFrames>= 2) {P2_Fireball_FrameTime_02 = backend_get_config_int("701", "V3_FrameTime_02", 6)-1; }
if (Fireball[Player].TotalFrames>= 3) {P2_Fireball_FrameTime_03 = backend_get_config_int("701", "V3_FrameTime_03", 6)-1; }
if (Fireball[Player].TotalFrames>= 4) {P2_Fireball_FrameTime_04 = backend_get_config_int("701", "V3_FrameTime_04", 6)-1; }
if (Fireball[Player].TotalFrames>= 5) {P2_Fireball_FrameTime_05 = backend_get_config_int("701", "V3_FrameTime_05", 6)-1; }
if (Fireball[Player].TotalFrames>= 6) {P2_Fireball_FrameTime_06 = backend_get_config_int("701", "V3_FrameTime_06", 6)-1; }
if (Fireball[Player].TotalFrames>= 7) {P2_Fireball_FrameTime_07 = backend_get_config_int("701", "V3_FrameTime_07", 6)-1; }
if (Fireball[Player].TotalFrames>= 8) {P2_Fireball_FrameTime_08 = backend_get_config_int("701", "V3_FrameTime_08", 6)-1; }
if (Fireball[Player].TotalFrames>= 9) {P2_Fireball_FrameTime_09 = backend_get_config_int("701", "V3_FrameTime_09", 6)-1; }
if (Fireball[Player].TotalFrames>=10) {P2_Fireball_FrameTime_10 = backend_get_config_int("701", "V3_FrameTime_10", 6)-1; }
}
P2_Fireball_FrameTime = P2_Fireball_FrameTime_00;

sprintf(P2_Caminho_sp, "data/chars/%s/special.ini", P[Player].Name);
backend_set_config_file(P2_Caminho_sp);

int LocalPosX=backend_get_config_int (Fireball[Player].State_s, "LocalPosX" , 0 );
int LocalPosY=backend_get_config_int (Fireball[Player].State_s, "LocalPosY" , 0 );
Fireball[Player].x = P[Player].x+(LocalPosX*Fireball[Player].Direcao);
Fireball[Player].y = P[Player].y+LocalPosY;
Fireball[Player].HSpeed = backend_get_config_int("701", "HSpeed", 4)-1;
Fireball[Player].HSpeed+=1;
Fireball[Player].VSpeed = backend_get_config_int("701", "VSpeed", -1)-1;
Fireball[Player].VSpeed+=1;
Fireball[Player].ThrowFireball = backend_get_config_int (P[Player].State_s, "ThrowFireball" , 1 );

sprintf(P2_Caminho_sp, "data/chars/%s/chbox.ini", P[Player].Name);
backend_set_config_file(P2_Caminho_sp);
P2_Fireball_HurtBox01x1 = backend_get_config_int ("701_00", "HurtBox01x1" , -15 );
P2_Fireball_HurtBox01y1 = backend_get_config_int ("701_00", "HurtBox01y1" , -15 );
P2_Fireball_HurtBox01x2 = backend_get_config_int ("701_00", "HurtBox01x2" , 15 );
P2_Fireball_HurtBox01y2 = backend_get_config_int ("701_00", "HurtBox01y2" , 15 );
P2_Fireball_HitBox01x1 = backend_get_config_int ("701_00", "HitBox01x1" , -10 );
P2_Fireball_HitBox01y1 = backend_get_config_int ("701_00", "HitBox01y1" , -10 );
P2_Fireball_HitBox01x2 = backend_get_config_int ("701_00", "HitBox01x2" , -10 );
P2_Fireball_HitBox01y2 = backend_get_config_int ("701_00", "HitBox01y2" , -10 );
}
}
if(P[Player].State!=700){
Fireball[Player].Ativa = 0;
Fireball[Player].x = -9999;
Fireball[Player].y = -9999;
}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CRIA NOVO HITSPARK ---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void New_HitBox(int Qtde_HitBoxes){
//if ( colisaoxP2==1 ){
Qtde_HitBox++;

//SONS DE HIT
if(colisaoxP1==1){
if(ForcaDoGolpeP2==1){ PlaySoundHitLvl1=1; }
if(ForcaDoGolpeP2==2){ PlaySoundHitLvl2=1; }
if(ForcaDoGolpeP2==3){ PlaySoundHitLvl3=1; }
}
if(colisaoxP2==1){
if(ForcaDoGolpeP1==1){ PlaySoundHitLvl1=1; }
if(ForcaDoGolpeP1==2){ PlaySoundHitLvl2=1; }
if(ForcaDoGolpeP1==3){ PlaySoundHitLvl3=1; }
}

if ( colisaoxP2==1 ){
HitSpark[Qtde_HitBoxes].x = P1_Hit_x;
HitSpark[Qtde_HitBoxes].y = P1_Hit_y;
if ( ForcaDoGolpeP1==1 ) { HitSpark[Qtde_HitBoxes].Type = 991; HitSpark[Qtde_HitBox].XAlign=-30; }
if ( ForcaDoGolpeP1==2 ) { HitSpark[Qtde_HitBoxes].Type = 992; HitSpark[Qtde_HitBox].XAlign=-50; }
if ( ForcaDoGolpeP1==3 ) { HitSpark[Qtde_HitBoxes].Type = 993; HitSpark[Qtde_HitBox].XAlign=-65; }
}
if ( colisaoxP1==1 ){
HitSpark[Qtde_HitBoxes].x = P2_Hit_x;
HitSpark[Qtde_HitBoxes].y = P2_Hit_y;
if ( ForcaDoGolpeP2==1 ) { HitSpark[Qtde_HitBoxes].Type = 991; HitSpark[Qtde_HitBox].XAlign=-30; }
if ( ForcaDoGolpeP2==2 ) { HitSpark[Qtde_HitBoxes].Type = 992; HitSpark[Qtde_HitBox].XAlign=-50; }
if ( ForcaDoGolpeP2==3 ) { HitSpark[Qtde_HitBoxes].Type = 993; HitSpark[Qtde_HitBox].XAlign=-65; }
}

HitSpark[Qtde_HitBoxes].StartFrame=timer;
HitSpark[Qtde_HitBoxes].FrameTime=1;
HitSpark[Qtde_HitBoxes].TotalFrames=5;
HitSpark[Qtde_HitBoxes].IndexAnim=0;
HitSpark[Qtde_HitBoxes].YAlign=HitSpark[Qtde_HitBoxes].XAlign;
//}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ADITIVO TABLE ATLAS --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AddTableAtlas(int PlayerInd, int State, int AnimIndex, int TotImg){

int line = TotImg;
int ind = PlayerInd;
P[ind].State=State;
P[ind].IndexAnim=AnimIndex;

//char.ini
char P1_Caminho[99]; char P2_Caminho[99];
if(ind==1){ sprintf(P1_Caminho, "data/chars/%s/char.ini", P[ind].Name); backend_set_config_file(P1_Caminho); }
if(ind==2){ sprintf(P2_Caminho, "data/chars/%s/char.ini", P[ind].Name); backend_set_config_file(P2_Caminho); }

//strcpy(P[ind].Name_Display, (char *)backend_get_config_string("Info", "Name", "-"));

//-----------------------------------------------------------------------------------------------------------------

if( P[ind].IndexAnim==0 ){

sprintf(P[ind].State_s, "%i" , P[ind].State); //State String

if (P[ind].State<700) {
P[ind].TableAtlas[line][ 4] = backend_get_config_int ( P[ind].State_s, "XAlign", P[ind].Largura/2 );
P[ind].TableAtlas[line][ 5] = backend_get_config_int ( P[ind].State_s, "YAlign", P[ind].Altura );
P[ind].TableAtlas[line][ 6] = backend_get_config_int ( P[ind].State_s, "X", -5555 );
P[ind].TableAtlas[line][ 7] = backend_get_config_int ( P[ind].State_s, "Y", -5555 );
P[ind].TableAtlas[line][ 8] = backend_get_config_float ( P[ind].State_s, "VSpeed", -5555 );
P[ind].TableAtlas[line][ 9] = backend_get_config_float ( P[ind].State_s, "HSpeed", -5555 );
P[ind].TableAtlas[line][10] = backend_get_config_float ( P[ind].State_s, "Gravity", -5555 );
P[ind].TableAtlas[line][11] = backend_get_config_float ( P[ind].State_s, "Friction", -5555 );
P[ind].TableAtlas[line][12] = backend_get_config_int ( P[ind].State_s, "EnergyChange" , -5555 );
P[ind].TableAtlas[line][13] = backend_get_config_int ( P[ind].State_s, "SpecialChange", -5555 );
P[ind].TableAtlas[line][14] = backend_get_config_int ( P[ind].State_s, "Visible", -5555 );
P[ind].TableAtlas[line][15] = backend_get_config_int ( P[ind].State_s, "RoomLimit", -5555 );
strcpy(P[ind].HitType, (char *)backend_get_config_string(P[ind].State_s, "HitType","Normal")); //pega o hittype em char
//if (strcmp (P[ind].HitType,"")==0){ P[ind].TableAtlas[line][16] = -5555; }
if (strcmp (P[ind].HitType,"Normal")==0){ P[ind].TableAtlas[line][16] = 1; }
if (strcmp (P[ind].HitType,"Fall")  ==0){ P[ind].TableAtlas[line][16] = 2; }
P[ind].TableAtlas[line][17] = backend_get_config_int ( P[ind].State_s, "ChangeState", -5555 );
P[ind].TableAtlas[line][18] = backend_get_config_int ( P[ind].State_s, "Freeze", -5555 );
P[ind].TableAtlas[line][19] = backend_get_config_int ( P[ind].State_s, "Color", -5555 );
strcpy(P[ind].HitStack, (char *)backend_get_config_string(P[ind].State_s, "HitStack","Multi")); //pega o hitstack em char
//if (strcmp (P[ind].HitStack,"")==0){ P[ind].TableAtlas[line][20] = -5555; }
if (strcmp (P[ind].HitStack,"Single")==0){ P[ind].TableAtlas[line][20] = 1; }
if (strcmp (P[ind].HitStack,"Multi") ==0){ P[ind].TableAtlas[line][20] = 2; }
}

if (P[ind].State>=700) {

//carrega X e do char.ini
P[ind].TableAtlas[line][ 4] = backend_get_config_int ( P[ind].State_s, "XAlign", P[ind].Largura/2 );
P[ind].TableAtlas[line][ 5] = backend_get_config_int ( P[ind].State_s, "YAlign", P[ind].Altura );

//special.ini
if(ind==1){ sprintf(P1_Caminho, "data/chars/%s/special.ini", P[ind].Name); backend_set_config_file(P1_Caminho); }
if(ind==2){ sprintf(P2_Caminho, "data/chars/%s/special.ini", P[ind].Name); backend_set_config_file(P2_Caminho); }

P[ind].TableAtlas[line][ 6] = backend_get_config_int ( P[ind].State_s, "X", -5555 );
P[ind].TableAtlas[line][ 7] = backend_get_config_int ( P[ind].State_s, "Y", -5555 );
P[ind].TableAtlas[line][ 8] = backend_get_config_float ( P[ind].State_s, "VSpeed", -5555 );
P[ind].TableAtlas[line][ 9] = backend_get_config_float ( P[ind].State_s, "HSpeed", -5555 );
P[ind].TableAtlas[line][10] = backend_get_config_float ( P[ind].State_s, "Gravity", -5555 );
P[ind].TableAtlas[line][11] = backend_get_config_float ( P[ind].State_s, "Friction", -5555 );
P[ind].TableAtlas[line][12] = backend_get_config_int ( P[ind].State_s, "EnergyChange" , -5555 );
P[ind].TableAtlas[line][13] = backend_get_config_int ( P[ind].State_s, "SpecialChange", -5555 );
P[ind].TableAtlas[line][14] = backend_get_config_int ( P[ind].State_s, "Visible", -5555 );
P[ind].TableAtlas[line][15] = backend_get_config_int ( P[ind].State_s, "RoomLimit", -5555 );
strcpy(P[ind].HitType, (char *)backend_get_config_string(P[ind].State_s, "HitType","Normal")); //pega o hittype em char
//if (strcmp (P[ind].HitType,"")==0){ P[ind].TableAtlas[line][16] = -5555; }
if (strcmp (P[ind].HitType,"Normal")==0){ P[ind].TableAtlas[line][16] = 1; }
if (strcmp (P[ind].HitType,"Fall")  ==0){ P[ind].TableAtlas[line][16] = 2; }
P[ind].TableAtlas[line][17] = backend_get_config_int ( P[ind].State_s, "ChangeState", -5555 );
P[ind].TableAtlas[line][18] = backend_get_config_int ( P[ind].State_s, "Freeze", -5555 );
P[ind].TableAtlas[line][19] = backend_get_config_int ( P[ind].State_s, "Color", -5555 );
strcpy(P[ind].HitStack, (char *)backend_get_config_string(P[ind].State_s, "HitStack","Multi")); //pega o hitstack em char
//if (strcmp (P[ind].HitStack,"")==0){ P[ind].TableAtlas[line][20] = -5555; }
if (strcmp (P[ind].HitStack,"Single")==0){ P[ind].TableAtlas[line][20] = 1; }
if (strcmp (P[ind].HitStack,"Multi") ==0){ P[ind].TableAtlas[line][20] = 2; }
}

} //fim "P[ind].IndexAnim==0"

//-----------------------------------------------------------------------------------------------------------------

if( P[ind].IndexAnim>0 ){

if( P[ind].IndexAnim< 10 ){ sprintf(P[ind].State_s, "%i_0%i" , P[ind].State, P[ind].IndexAnim); } //State String
if( P[ind].IndexAnim>=10 ){ sprintf(P[ind].State_s, "%i_%i"  , P[ind].State, P[ind].IndexAnim); } //State String

if (P[ind].State<700) {
P[ind].TableAtlas[line][ 4] = backend_get_config_int ( P[ind].State_s, "XAlign", -5555 );
P[ind].TableAtlas[line][ 5] = backend_get_config_int ( P[ind].State_s, "YAlign", -5555 );
P[ind].TableAtlas[line][ 6] = backend_get_config_int ( P[ind].State_s, "X", -5555 );
P[ind].TableAtlas[line][ 7] = backend_get_config_int ( P[ind].State_s, "Y", -5555 );
P[ind].TableAtlas[line][ 8] = backend_get_config_float ( P[ind].State_s, "VSpeed", -5555 );
P[ind].TableAtlas[line][ 9] = backend_get_config_float ( P[ind].State_s, "HSpeed", -5555 );
P[ind].TableAtlas[line][10] = backend_get_config_float ( P[ind].State_s, "Gravity", -5555 );
P[ind].TableAtlas[line][11] = backend_get_config_float ( P[ind].State_s, "Friction", -5555 );
P[ind].TableAtlas[line][12] = backend_get_config_int ( P[ind].State_s, "EnergyChange" , -5555 );
P[ind].TableAtlas[line][13] = backend_get_config_int ( P[ind].State_s, "SpecialChange", -5555 );
P[ind].TableAtlas[line][14] = backend_get_config_int ( P[ind].State_s, "Visible", -5555 );
P[ind].TableAtlas[line][15] = backend_get_config_int ( P[ind].State_s, "RoomLimit", -5555 );
strcpy(P[ind].HitType, (char *)backend_get_config_string(P[ind].State_s, "HitType","")); //pega o hittype em char
if (strcmp (P[ind].HitType,"")==0){ P[ind].TableAtlas[line][16] = -5555; }
if (strcmp (P[ind].HitType,"Normal")==0){ P[ind].TableAtlas[line][16] = 1; }
if (strcmp (P[ind].HitType,"Fall")  ==0){ P[ind].TableAtlas[line][16] = 2; }
P[ind].TableAtlas[line][17] = backend_get_config_int ( P[ind].State_s, "ChangeState", -5555 );
P[ind].TableAtlas[line][18] = backend_get_config_int ( P[ind].State_s, "Freeze", -5555 );
P[ind].TableAtlas[line][19] = backend_get_config_int ( P[ind].State_s, "Color", -5555 );
strcpy(P[ind].HitStack, (char *)backend_get_config_string(P[ind].State_s, "HitStack","")); //pega o hitstack em char
if (strcmp (P[ind].HitStack,"")==0){ P[ind].TableAtlas[line][20] = -5555; }
if (strcmp (P[ind].HitStack,"Single")==0){ P[ind].TableAtlas[line][20] = 1; }
if (strcmp (P[ind].HitStack,"Multi") ==0){ P[ind].TableAtlas[line][20] = 2; }
}

if (P[ind].State>=700) {

//carrega X e do char.ini
P[ind].TableAtlas[line][ 4] = backend_get_config_int ( P[ind].State_s, "XAlign", -5555 );
P[ind].TableAtlas[line][ 5] = backend_get_config_int ( P[ind].State_s, "YAlign", -5555 );

//special.ini
if(ind==1){ sprintf(P1_Caminho, "data/chars/%s/special.ini", P[ind].Name); backend_set_config_file(P1_Caminho); }
if(ind==2){ sprintf(P2_Caminho, "data/chars/%s/special.ini", P[ind].Name); backend_set_config_file(P2_Caminho); }

P[ind].TableAtlas[line][ 6] = backend_get_config_int ( P[ind].State_s, "X", -5555 );
P[ind].TableAtlas[line][ 7] = backend_get_config_int ( P[ind].State_s, "Y", -5555 );
P[ind].TableAtlas[line][ 8] = backend_get_config_float ( P[ind].State_s, "VSpeed", -5555 );
P[ind].TableAtlas[line][ 9] = backend_get_config_float ( P[ind].State_s, "HSpeed", -5555 );
P[ind].TableAtlas[line][10] = backend_get_config_float ( P[ind].State_s, "Gravity", -5555 );
P[ind].TableAtlas[line][11] = backend_get_config_float ( P[ind].State_s, "Friction", -5555 );
P[ind].TableAtlas[line][12] = backend_get_config_int ( P[ind].State_s, "EnergyChange" , -5555 );
P[ind].TableAtlas[line][13] = backend_get_config_int ( P[ind].State_s, "SpecialChange", -5555 );
P[ind].TableAtlas[line][14] = backend_get_config_int ( P[ind].State_s, "Visible", -5555 );
P[ind].TableAtlas[line][15] = backend_get_config_int ( P[ind].State_s, "RoomLimit", -5555 );
strcpy(P[ind].HitType, (char *)backend_get_config_string(P[ind].State_s, "HitType","")); //pega o hittype em char
if (strcmp (P[ind].HitType,"")==0){ P[ind].TableAtlas[line][16] = -5555; }
if (strcmp (P[ind].HitType,"Normal")==0){ P[ind].TableAtlas[line][16] = 1; }
if (strcmp (P[ind].HitType,"Fall")  ==0){ P[ind].TableAtlas[line][16] = 2; }
P[ind].TableAtlas[line][17] = backend_get_config_int ( P[ind].State_s, "ChangeState", -5555 );
P[ind].TableAtlas[line][18] = backend_get_config_int ( P[ind].State_s, "Freeze", -5555 );
P[ind].TableAtlas[line][19] = backend_get_config_int ( P[ind].State_s, "Color", -5555 );
strcpy(P[ind].HitStack, (char *)backend_get_config_string(P[ind].State_s, "HitStack","")); //pega o hitstack em char
if (strcmp (P[ind].HitStack,"")==0){ P[ind].TableAtlas[line][20] = -5555; }
if (strcmp (P[ind].HitStack,"Single")==0){ P[ind].TableAtlas[line][20] = 1; }
if (strcmp (P[ind].HitStack,"Multi") ==0){ P[ind].TableAtlas[line][20] = 2; }
}

} //fim "P[ind].IndexAnim>0"

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EDITOR SAVE CHAR.INI --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ED_save_charini(){

if(ED_State<700){
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3]; sprintf(ED_State_s, "%i", ED_State);
if (ED_TotalFrames>= 0) { backend_set_config_int(ED_State_s, "FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1) { backend_set_config_int(ED_State_s, "FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2) { backend_set_config_int(ED_State_s, "FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3) { backend_set_config_int(ED_State_s, "FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4) { backend_set_config_int(ED_State_s, "FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5) { backend_set_config_int(ED_State_s, "FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6) { backend_set_config_int(ED_State_s, "FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7) { backend_set_config_int(ED_State_s, "FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8) { backend_set_config_int(ED_State_s, "FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9) { backend_set_config_int(ED_State_s, "FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10) { backend_set_config_int(ED_State_s, "FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11) { backend_set_config_int(ED_State_s, "FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12) { backend_set_config_int(ED_State_s, "FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13) { backend_set_config_int(ED_State_s, "FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14) { backend_set_config_int(ED_State_s, "FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15) { backend_set_config_int(ED_State_s, "FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16) { backend_set_config_int(ED_State_s, "FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17) { backend_set_config_int(ED_State_s, "FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18) { backend_set_config_int(ED_State_s, "FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19) { backend_set_config_int(ED_State_s, "FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20) { backend_set_config_int(ED_State_s, "FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21) { backend_set_config_int(ED_State_s, "FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22) { backend_set_config_int(ED_State_s, "FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23) { backend_set_config_int(ED_State_s, "FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24) { backend_set_config_int(ED_State_s, "FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25) { backend_set_config_int(ED_State_s, "FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26) { backend_set_config_int(ED_State_s, "FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27) { backend_set_config_int(ED_State_s, "FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28) { backend_set_config_int(ED_State_s, "FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29) { backend_set_config_int(ED_State_s, "FrameTime_29", ED_FrameTime_29+1); }
backend_set_config_int(ED_State_s, "XAlign"      , ED_XAlign );
backend_set_config_int(ED_State_s, "YAlign"      , ED_YAlign );
ED_alertsave=0; ED_ShowMsgSaving=1;
}

if(ED_State>=700 && ED_Special_Version==1){
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3]; sprintf(ED_State_s, "%i", ED_State);
if (ED_TotalFrames>= 0) { backend_set_config_int(ED_State_s, "V1_FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1) { backend_set_config_int(ED_State_s, "V1_FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2) { backend_set_config_int(ED_State_s, "V1_FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3) { backend_set_config_int(ED_State_s, "V1_FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4) { backend_set_config_int(ED_State_s, "V1_FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5) { backend_set_config_int(ED_State_s, "V1_FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6) { backend_set_config_int(ED_State_s, "V1_FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7) { backend_set_config_int(ED_State_s, "V1_FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8) { backend_set_config_int(ED_State_s, "V1_FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9) { backend_set_config_int(ED_State_s, "V1_FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10) { backend_set_config_int(ED_State_s, "V1_FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11) { backend_set_config_int(ED_State_s, "V1_FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12) { backend_set_config_int(ED_State_s, "V1_FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13) { backend_set_config_int(ED_State_s, "V1_FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14) { backend_set_config_int(ED_State_s, "V1_FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15) { backend_set_config_int(ED_State_s, "V1_FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16) { backend_set_config_int(ED_State_s, "V1_FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17) { backend_set_config_int(ED_State_s, "V1_FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18) { backend_set_config_int(ED_State_s, "V1_FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19) { backend_set_config_int(ED_State_s, "V1_FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20) { backend_set_config_int(ED_State_s, "V1_FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21) { backend_set_config_int(ED_State_s, "V1_FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22) { backend_set_config_int(ED_State_s, "V1_FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23) { backend_set_config_int(ED_State_s, "V1_FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24) { backend_set_config_int(ED_State_s, "V1_FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25) { backend_set_config_int(ED_State_s, "V1_FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26) { backend_set_config_int(ED_State_s, "V1_FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27) { backend_set_config_int(ED_State_s, "V1_FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28) { backend_set_config_int(ED_State_s, "V1_FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29) { backend_set_config_int(ED_State_s, "V1_FrameTime_29", ED_FrameTime_29+1); }
backend_set_config_int(ED_State_s, "XAlign"      , ED_XAlign );
backend_set_config_int(ED_State_s, "YAlign"      , ED_YAlign );
ED_alertsave=0; ED_ShowMsgSaving=1;
}

if(ED_State>=700 && ED_Special_Version==2){
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3]; sprintf(ED_State_s, "%i", ED_State);
if (ED_TotalFrames>= 0) { backend_set_config_int(ED_State_s, "V2_FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1) { backend_set_config_int(ED_State_s, "V2_FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2) { backend_set_config_int(ED_State_s, "V2_FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3) { backend_set_config_int(ED_State_s, "V2_FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4) { backend_set_config_int(ED_State_s, "V2_FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5) { backend_set_config_int(ED_State_s, "V2_FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6) { backend_set_config_int(ED_State_s, "V2_FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7) { backend_set_config_int(ED_State_s, "V2_FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8) { backend_set_config_int(ED_State_s, "V2_FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9) { backend_set_config_int(ED_State_s, "V2_FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10) { backend_set_config_int(ED_State_s, "V2_FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11) { backend_set_config_int(ED_State_s, "V2_FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12) { backend_set_config_int(ED_State_s, "V2_FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13) { backend_set_config_int(ED_State_s, "V2_FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14) { backend_set_config_int(ED_State_s, "V2_FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15) { backend_set_config_int(ED_State_s, "V2_FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16) { backend_set_config_int(ED_State_s, "V2_FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17) { backend_set_config_int(ED_State_s, "V2_FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18) { backend_set_config_int(ED_State_s, "V2_FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19) { backend_set_config_int(ED_State_s, "V2_FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20) { backend_set_config_int(ED_State_s, "V2_FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21) { backend_set_config_int(ED_State_s, "V2_FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22) { backend_set_config_int(ED_State_s, "V2_FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23) { backend_set_config_int(ED_State_s, "V2_FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24) { backend_set_config_int(ED_State_s, "V2_FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25) { backend_set_config_int(ED_State_s, "V2_FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26) { backend_set_config_int(ED_State_s, "V2_FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27) { backend_set_config_int(ED_State_s, "V2_FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28) { backend_set_config_int(ED_State_s, "V2_FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29) { backend_set_config_int(ED_State_s, "V2_FrameTime_29", ED_FrameTime_29+1); }
backend_set_config_int(ED_State_s, "XAlign"      , ED_XAlign );
backend_set_config_int(ED_State_s, "YAlign"      , ED_YAlign );
ED_alertsave=0; ED_ShowMsgSaving=1;
}

if(ED_State>=700 && ED_Special_Version==3){
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3]; sprintf(ED_State_s, "%i", ED_State);
if (ED_TotalFrames>= 0) { backend_set_config_int(ED_State_s, "V3_FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1) { backend_set_config_int(ED_State_s, "V3_FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2) { backend_set_config_int(ED_State_s, "V3_FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3) { backend_set_config_int(ED_State_s, "V3_FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4) { backend_set_config_int(ED_State_s, "V3_FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5) { backend_set_config_int(ED_State_s, "V3_FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6) { backend_set_config_int(ED_State_s, "V3_FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7) { backend_set_config_int(ED_State_s, "V3_FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8) { backend_set_config_int(ED_State_s, "V3_FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9) { backend_set_config_int(ED_State_s, "V3_FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10) { backend_set_config_int(ED_State_s, "V3_FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11) { backend_set_config_int(ED_State_s, "V3_FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12) { backend_set_config_int(ED_State_s, "V3_FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13) { backend_set_config_int(ED_State_s, "V3_FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14) { backend_set_config_int(ED_State_s, "V3_FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15) { backend_set_config_int(ED_State_s, "V3_FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16) { backend_set_config_int(ED_State_s, "V3_FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17) { backend_set_config_int(ED_State_s, "V3_FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18) { backend_set_config_int(ED_State_s, "V3_FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19) { backend_set_config_int(ED_State_s, "V3_FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20) { backend_set_config_int(ED_State_s, "V3_FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21) { backend_set_config_int(ED_State_s, "V3_FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22) { backend_set_config_int(ED_State_s, "V3_FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23) { backend_set_config_int(ED_State_s, "V3_FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24) { backend_set_config_int(ED_State_s, "V3_FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25) { backend_set_config_int(ED_State_s, "V3_FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26) { backend_set_config_int(ED_State_s, "V3_FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27) { backend_set_config_int(ED_State_s, "V3_FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28) { backend_set_config_int(ED_State_s, "V3_FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29) { backend_set_config_int(ED_State_s, "V3_FrameTime_29", ED_FrameTime_29+1); }
backend_set_config_int(ED_State_s, "XAlign"      , ED_XAlign );
backend_set_config_int(ED_State_s, "YAlign"      , ED_YAlign );
ED_alertsave=0; ED_ShowMsgSaving=1;
}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EDITOR LOAD CHAR.INI --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ED_load_charini(){

//carrega dados do ini
char ED_Caminho[99]; sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name); backend_set_config_file(ED_Caminho);
char ED_State_s[3]; sprintf(ED_State_s, "%i", ED_State);
ED_FrameTime_00=0;
ED_FrameTime_01=0; ED_FrameTime_02=0; ED_FrameTime_03=0; ED_FrameTime_04=0; ED_FrameTime_05=0;
ED_FrameTime_06=0; ED_FrameTime_07=0; ED_FrameTime_08=0; ED_FrameTime_09=0; ED_FrameTime_10=0;
ED_FrameTime_11=0; ED_FrameTime_12=0; ED_FrameTime_13=0; ED_FrameTime_14=0; ED_FrameTime_15=0;
ED_FrameTime_16=0; ED_FrameTime_17=0; ED_FrameTime_18=0; ED_FrameTime_19=0; ED_FrameTime_20=0;
ED_FrameTime_21=0; ED_FrameTime_22=0; ED_FrameTime_23=0; ED_FrameTime_24=0; ED_FrameTime_25=0;
ED_FrameTime_26=0; ED_FrameTime_27=0; ED_FrameTime_28=0; ED_FrameTime_29=0; ED_FrameTime=0;
ED_XAlign = backend_get_config_int (ED_State_s, "XAlign", ED_Largura/2 ); //P[1].Largura_100
ED_YAlign = backend_get_config_int (ED_State_s, "YAlign", ED_Altura );

if(ED_State<700){
if (ED_TotalFrames>= 0) {ED_FrameTime_00 = backend_get_config_int(ED_State_s, "FrameTime_00", 6)-1; }
if (ED_TotalFrames>= 1) {ED_FrameTime_01 = backend_get_config_int(ED_State_s, "FrameTime_01", 6)-1; }
if (ED_TotalFrames>= 2) {ED_FrameTime_02 = backend_get_config_int(ED_State_s, "FrameTime_02", 6)-1; }
if (ED_TotalFrames>= 3) {ED_FrameTime_03 = backend_get_config_int(ED_State_s, "FrameTime_03", 6)-1; }
if (ED_TotalFrames>= 4) {ED_FrameTime_04 = backend_get_config_int(ED_State_s, "FrameTime_04", 6)-1; }
if (ED_TotalFrames>= 5) {ED_FrameTime_05 = backend_get_config_int(ED_State_s, "FrameTime_05", 6)-1; }
if (ED_TotalFrames>= 6) {ED_FrameTime_06 = backend_get_config_int(ED_State_s, "FrameTime_06", 6)-1; }
if (ED_TotalFrames>= 7) {ED_FrameTime_07 = backend_get_config_int(ED_State_s, "FrameTime_07", 6)-1; }
if (ED_TotalFrames>= 8) {ED_FrameTime_08 = backend_get_config_int(ED_State_s, "FrameTime_08", 6)-1; }
if (ED_TotalFrames>= 9) {ED_FrameTime_09 = backend_get_config_int(ED_State_s, "FrameTime_09", 6)-1; }
if (ED_TotalFrames>=10) {ED_FrameTime_10 = backend_get_config_int(ED_State_s, "FrameTime_10", 6)-1; }
if (ED_TotalFrames>=11) {ED_FrameTime_11 = backend_get_config_int(ED_State_s, "FrameTime_11", 6)-1; }
if (ED_TotalFrames>=12) {ED_FrameTime_12 = backend_get_config_int(ED_State_s, "FrameTime_12", 6)-1; }
if (ED_TotalFrames>=13) {ED_FrameTime_13 = backend_get_config_int(ED_State_s, "FrameTime_13", 6)-1; }
if (ED_TotalFrames>=14) {ED_FrameTime_14 = backend_get_config_int(ED_State_s, "FrameTime_14", 6)-1; }
if (ED_TotalFrames>=15) {ED_FrameTime_15 = backend_get_config_int(ED_State_s, "FrameTime_15", 6)-1; }
if (ED_TotalFrames>=16) {ED_FrameTime_16 = backend_get_config_int(ED_State_s, "FrameTime_16", 6)-1; }
if (ED_TotalFrames>=17) {ED_FrameTime_17 = backend_get_config_int(ED_State_s, "FrameTime_17", 6)-1; }
if (ED_TotalFrames>=18) {ED_FrameTime_18 = backend_get_config_int(ED_State_s, "FrameTime_18", 6)-1; }
if (ED_TotalFrames>=19) {ED_FrameTime_19 = backend_get_config_int(ED_State_s, "FrameTime_19", 6)-1; }
if (ED_TotalFrames>=20) {ED_FrameTime_20 = backend_get_config_int(ED_State_s, "FrameTime_20", 6)-1; }
if (ED_TotalFrames>=21) {ED_FrameTime_21 = backend_get_config_int(ED_State_s, "FrameTime_21", 6)-1; }
if (ED_TotalFrames>=22) {ED_FrameTime_22 = backend_get_config_int(ED_State_s, "FrameTime_22", 6)-1; }
if (ED_TotalFrames>=23) {ED_FrameTime_23 = backend_get_config_int(ED_State_s, "FrameTime_23", 6)-1; }
if (ED_TotalFrames>=24) {ED_FrameTime_24 = backend_get_config_int(ED_State_s, "FrameTime_24", 6)-1; }
if (ED_TotalFrames>=25) {ED_FrameTime_25 = backend_get_config_int(ED_State_s, "FrameTime_25", 6)-1; }
if (ED_TotalFrames>=26) {ED_FrameTime_26 = backend_get_config_int(ED_State_s, "FrameTime_26", 6)-1; }
if (ED_TotalFrames>=27) {ED_FrameTime_27 = backend_get_config_int(ED_State_s, "FrameTime_27", 6)-1; }
if (ED_TotalFrames>=28) {ED_FrameTime_28 = backend_get_config_int(ED_State_s, "FrameTime_28", 6)-1; }
if (ED_TotalFrames>=29) {ED_FrameTime_29 = backend_get_config_int(ED_State_s, "FrameTime_29", 6)-1; }
}

if(ED_State>=700 && ED_Special_Version==1){
if (ED_TotalFrames>= 0) {ED_FrameTime_00 = backend_get_config_int(ED_State_s, "V1_FrameTime_00", 6)-1; }
if (ED_TotalFrames>= 1) {ED_FrameTime_01 = backend_get_config_int(ED_State_s, "V1_FrameTime_01", 6)-1; }
if (ED_TotalFrames>= 2) {ED_FrameTime_02 = backend_get_config_int(ED_State_s, "V1_FrameTime_02", 6)-1; }
if (ED_TotalFrames>= 3) {ED_FrameTime_03 = backend_get_config_int(ED_State_s, "V1_FrameTime_03", 6)-1; }
if (ED_TotalFrames>= 4) {ED_FrameTime_04 = backend_get_config_int(ED_State_s, "V1_FrameTime_04", 6)-1; }
if (ED_TotalFrames>= 5) {ED_FrameTime_05 = backend_get_config_int(ED_State_s, "V1_FrameTime_05", 6)-1; }
if (ED_TotalFrames>= 6) {ED_FrameTime_06 = backend_get_config_int(ED_State_s, "V1_FrameTime_06", 6)-1; }
if (ED_TotalFrames>= 7) {ED_FrameTime_07 = backend_get_config_int(ED_State_s, "V1_FrameTime_07", 6)-1; }
if (ED_TotalFrames>= 8) {ED_FrameTime_08 = backend_get_config_int(ED_State_s, "V1_FrameTime_08", 6)-1; }
if (ED_TotalFrames>= 9) {ED_FrameTime_09 = backend_get_config_int(ED_State_s, "V1_FrameTime_09", 6)-1; }
if (ED_TotalFrames>=10) {ED_FrameTime_10 = backend_get_config_int(ED_State_s, "V1_FrameTime_10", 6)-1; }
if (ED_TotalFrames>=11) {ED_FrameTime_11 = backend_get_config_int(ED_State_s, "V1_FrameTime_11", 6)-1; }
if (ED_TotalFrames>=12) {ED_FrameTime_12 = backend_get_config_int(ED_State_s, "V1_FrameTime_12", 6)-1; }
if (ED_TotalFrames>=13) {ED_FrameTime_13 = backend_get_config_int(ED_State_s, "V1_FrameTime_13", 6)-1; }
if (ED_TotalFrames>=14) {ED_FrameTime_14 = backend_get_config_int(ED_State_s, "V1_FrameTime_14", 6)-1; }
if (ED_TotalFrames>=15) {ED_FrameTime_15 = backend_get_config_int(ED_State_s, "V1_FrameTime_15", 6)-1; }
if (ED_TotalFrames>=16) {ED_FrameTime_16 = backend_get_config_int(ED_State_s, "V1_FrameTime_16", 6)-1; }
if (ED_TotalFrames>=17) {ED_FrameTime_17 = backend_get_config_int(ED_State_s, "V1_FrameTime_17", 6)-1; }
if (ED_TotalFrames>=18) {ED_FrameTime_18 = backend_get_config_int(ED_State_s, "V1_FrameTime_18", 6)-1; }
if (ED_TotalFrames>=19) {ED_FrameTime_19 = backend_get_config_int(ED_State_s, "V1_FrameTime_19", 6)-1; }
if (ED_TotalFrames>=20) {ED_FrameTime_20 = backend_get_config_int(ED_State_s, "V1_FrameTime_20", 6)-1; }
if (ED_TotalFrames>=21) {ED_FrameTime_21 = backend_get_config_int(ED_State_s, "V1_FrameTime_21", 6)-1; }
if (ED_TotalFrames>=22) {ED_FrameTime_22 = backend_get_config_int(ED_State_s, "V1_FrameTime_22", 6)-1; }
if (ED_TotalFrames>=23) {ED_FrameTime_23 = backend_get_config_int(ED_State_s, "V1_FrameTime_23", 6)-1; }
if (ED_TotalFrames>=24) {ED_FrameTime_24 = backend_get_config_int(ED_State_s, "V1_FrameTime_24", 6)-1; }
if (ED_TotalFrames>=25) {ED_FrameTime_25 = backend_get_config_int(ED_State_s, "V1_FrameTime_25", 6)-1; }
if (ED_TotalFrames>=26) {ED_FrameTime_26 = backend_get_config_int(ED_State_s, "V1_FrameTime_26", 6)-1; }
if (ED_TotalFrames>=27) {ED_FrameTime_27 = backend_get_config_int(ED_State_s, "V1_FrameTime_27", 6)-1; }
if (ED_TotalFrames>=28) {ED_FrameTime_28 = backend_get_config_int(ED_State_s, "V1_FrameTime_28", 6)-1; }
if (ED_TotalFrames>=29) {ED_FrameTime_29 = backend_get_config_int(ED_State_s, "V1_FrameTime_29", 6)-1; }
}

if(ED_State>=700 && ED_Special_Version==2){
if (ED_TotalFrames>= 0) {ED_FrameTime_00 = backend_get_config_int(ED_State_s, "V2_FrameTime_00", 6)-1; }
if (ED_TotalFrames>= 1) {ED_FrameTime_01 = backend_get_config_int(ED_State_s, "V2_FrameTime_01", 6)-1; }
if (ED_TotalFrames>= 2) {ED_FrameTime_02 = backend_get_config_int(ED_State_s, "V2_FrameTime_02", 6)-1; }
if (ED_TotalFrames>= 3) {ED_FrameTime_03 = backend_get_config_int(ED_State_s, "V2_FrameTime_03", 6)-1; }
if (ED_TotalFrames>= 4) {ED_FrameTime_04 = backend_get_config_int(ED_State_s, "V2_FrameTime_04", 6)-1; }
if (ED_TotalFrames>= 5) {ED_FrameTime_05 = backend_get_config_int(ED_State_s, "V2_FrameTime_05", 6)-1; }
if (ED_TotalFrames>= 6) {ED_FrameTime_06 = backend_get_config_int(ED_State_s, "V2_FrameTime_06", 6)-1; }
if (ED_TotalFrames>= 7) {ED_FrameTime_07 = backend_get_config_int(ED_State_s, "V2_FrameTime_07", 6)-1; }
if (ED_TotalFrames>= 8) {ED_FrameTime_08 = backend_get_config_int(ED_State_s, "V2_FrameTime_08", 6)-1; }
if (ED_TotalFrames>= 9) {ED_FrameTime_09 = backend_get_config_int(ED_State_s, "V2_FrameTime_09", 6)-1; }
if (ED_TotalFrames>=10) {ED_FrameTime_10 = backend_get_config_int(ED_State_s, "V2_FrameTime_10", 6)-1; }
if (ED_TotalFrames>=11) {ED_FrameTime_11 = backend_get_config_int(ED_State_s, "V2_FrameTime_11", 6)-1; }
if (ED_TotalFrames>=12) {ED_FrameTime_12 = backend_get_config_int(ED_State_s, "V2_FrameTime_12", 6)-1; }
if (ED_TotalFrames>=13) {ED_FrameTime_13 = backend_get_config_int(ED_State_s, "V2_FrameTime_13", 6)-1; }
if (ED_TotalFrames>=14) {ED_FrameTime_14 = backend_get_config_int(ED_State_s, "V2_FrameTime_14", 6)-1; }
if (ED_TotalFrames>=15) {ED_FrameTime_15 = backend_get_config_int(ED_State_s, "V2_FrameTime_15", 6)-1; }
if (ED_TotalFrames>=16) {ED_FrameTime_16 = backend_get_config_int(ED_State_s, "V2_FrameTime_16", 6)-1; }
if (ED_TotalFrames>=17) {ED_FrameTime_17 = backend_get_config_int(ED_State_s, "V2_FrameTime_17", 6)-1; }
if (ED_TotalFrames>=18) {ED_FrameTime_18 = backend_get_config_int(ED_State_s, "V2_FrameTime_18", 6)-1; }
if (ED_TotalFrames>=19) {ED_FrameTime_19 = backend_get_config_int(ED_State_s, "V2_FrameTime_19", 6)-1; }
if (ED_TotalFrames>=20) {ED_FrameTime_20 = backend_get_config_int(ED_State_s, "V2_FrameTime_20", 6)-1; }
if (ED_TotalFrames>=21) {ED_FrameTime_21 = backend_get_config_int(ED_State_s, "V2_FrameTime_21", 6)-1; }
if (ED_TotalFrames>=22) {ED_FrameTime_22 = backend_get_config_int(ED_State_s, "V2_FrameTime_22", 6)-1; }
if (ED_TotalFrames>=23) {ED_FrameTime_23 = backend_get_config_int(ED_State_s, "V2_FrameTime_23", 6)-1; }
if (ED_TotalFrames>=24) {ED_FrameTime_24 = backend_get_config_int(ED_State_s, "V2_FrameTime_24", 6)-1; }
if (ED_TotalFrames>=25) {ED_FrameTime_25 = backend_get_config_int(ED_State_s, "V2_FrameTime_25", 6)-1; }
if (ED_TotalFrames>=26) {ED_FrameTime_26 = backend_get_config_int(ED_State_s, "V2_FrameTime_26", 6)-1; }
if (ED_TotalFrames>=27) {ED_FrameTime_27 = backend_get_config_int(ED_State_s, "V2_FrameTime_27", 6)-1; }
if (ED_TotalFrames>=28) {ED_FrameTime_28 = backend_get_config_int(ED_State_s, "V2_FrameTime_28", 6)-1; }
if (ED_TotalFrames>=29) {ED_FrameTime_29 = backend_get_config_int(ED_State_s, "V2_FrameTime_29", 6)-1; }
}

if(ED_State>=700 && ED_Special_Version==3){
if (ED_TotalFrames>= 0) {ED_FrameTime_00 = backend_get_config_int(ED_State_s, "V3_FrameTime_00", 6)-1; }
if (ED_TotalFrames>= 1) {ED_FrameTime_01 = backend_get_config_int(ED_State_s, "V3_FrameTime_01", 6)-1; }
if (ED_TotalFrames>= 2) {ED_FrameTime_02 = backend_get_config_int(ED_State_s, "V3_FrameTime_02", 6)-1; }
if (ED_TotalFrames>= 3) {ED_FrameTime_03 = backend_get_config_int(ED_State_s, "V3_FrameTime_03", 6)-1; }
if (ED_TotalFrames>= 4) {ED_FrameTime_04 = backend_get_config_int(ED_State_s, "V3_FrameTime_04", 6)-1; }
if (ED_TotalFrames>= 5) {ED_FrameTime_05 = backend_get_config_int(ED_State_s, "V3_FrameTime_05", 6)-1; }
if (ED_TotalFrames>= 6) {ED_FrameTime_06 = backend_get_config_int(ED_State_s, "V3_FrameTime_06", 6)-1; }
if (ED_TotalFrames>= 7) {ED_FrameTime_07 = backend_get_config_int(ED_State_s, "V3_FrameTime_07", 6)-1; }
if (ED_TotalFrames>= 8) {ED_FrameTime_08 = backend_get_config_int(ED_State_s, "V3_FrameTime_08", 6)-1; }
if (ED_TotalFrames>= 9) {ED_FrameTime_09 = backend_get_config_int(ED_State_s, "V3_FrameTime_09", 6)-1; }
if (ED_TotalFrames>=10) {ED_FrameTime_10 = backend_get_config_int(ED_State_s, "V3_FrameTime_10", 6)-1; }
if (ED_TotalFrames>=11) {ED_FrameTime_11 = backend_get_config_int(ED_State_s, "V3_FrameTime_11", 6)-1; }
if (ED_TotalFrames>=12) {ED_FrameTime_12 = backend_get_config_int(ED_State_s, "V3_FrameTime_12", 6)-1; }
if (ED_TotalFrames>=13) {ED_FrameTime_13 = backend_get_config_int(ED_State_s, "V3_FrameTime_13", 6)-1; }
if (ED_TotalFrames>=14) {ED_FrameTime_14 = backend_get_config_int(ED_State_s, "V3_FrameTime_14", 6)-1; }
if (ED_TotalFrames>=15) {ED_FrameTime_15 = backend_get_config_int(ED_State_s, "V3_FrameTime_15", 6)-1; }
if (ED_TotalFrames>=16) {ED_FrameTime_16 = backend_get_config_int(ED_State_s, "V3_FrameTime_16", 6)-1; }
if (ED_TotalFrames>=17) {ED_FrameTime_17 = backend_get_config_int(ED_State_s, "V3_FrameTime_17", 6)-1; }
if (ED_TotalFrames>=18) {ED_FrameTime_18 = backend_get_config_int(ED_State_s, "V3_FrameTime_18", 6)-1; }
if (ED_TotalFrames>=19) {ED_FrameTime_19 = backend_get_config_int(ED_State_s, "V3_FrameTime_19", 6)-1; }
if (ED_TotalFrames>=20) {ED_FrameTime_20 = backend_get_config_int(ED_State_s, "V3_FrameTime_20", 6)-1; }
if (ED_TotalFrames>=21) {ED_FrameTime_21 = backend_get_config_int(ED_State_s, "V3_FrameTime_21", 6)-1; }
if (ED_TotalFrames>=22) {ED_FrameTime_22 = backend_get_config_int(ED_State_s, "V3_FrameTime_22", 6)-1; }
if (ED_TotalFrames>=23) {ED_FrameTime_23 = backend_get_config_int(ED_State_s, "V3_FrameTime_23", 6)-1; }
if (ED_TotalFrames>=24) {ED_FrameTime_24 = backend_get_config_int(ED_State_s, "V3_FrameTime_24", 6)-1; }
if (ED_TotalFrames>=25) {ED_FrameTime_25 = backend_get_config_int(ED_State_s, "V3_FrameTime_25", 6)-1; }
if (ED_TotalFrames>=26) {ED_FrameTime_26 = backend_get_config_int(ED_State_s, "V3_FrameTime_26", 6)-1; }
if (ED_TotalFrames>=27) {ED_FrameTime_27 = backend_get_config_int(ED_State_s, "V3_FrameTime_27", 6)-1; }
if (ED_TotalFrames>=28) {ED_FrameTime_28 = backend_get_config_int(ED_State_s, "V3_FrameTime_28", 6)-1; }
if (ED_TotalFrames>=29) {ED_FrameTime_29 = backend_get_config_int(ED_State_s, "V3_FrameTime_29", 6)-1; }
}

//salva o tempo de animacao 6 (se o tempo do frame for vazio, usa 6, que é o padrao)
if(ED_State<700){
if (ED_TotalFrames>= 0 && ED_FrameTime_00==5) { backend_set_config_int(ED_State_s, "FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1 && ED_FrameTime_01==5) { backend_set_config_int(ED_State_s, "FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2 && ED_FrameTime_02==5) { backend_set_config_int(ED_State_s, "FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3 && ED_FrameTime_03==5) { backend_set_config_int(ED_State_s, "FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4 && ED_FrameTime_04==5) { backend_set_config_int(ED_State_s, "FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5 && ED_FrameTime_05==5) { backend_set_config_int(ED_State_s, "FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6 && ED_FrameTime_06==5) { backend_set_config_int(ED_State_s, "FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7 && ED_FrameTime_07==5) { backend_set_config_int(ED_State_s, "FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8 && ED_FrameTime_08==5) { backend_set_config_int(ED_State_s, "FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9 && ED_FrameTime_09==5) { backend_set_config_int(ED_State_s, "FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10 && ED_FrameTime_10==5) { backend_set_config_int(ED_State_s, "FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11 && ED_FrameTime_11==5) { backend_set_config_int(ED_State_s, "FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12 && ED_FrameTime_12==5) { backend_set_config_int(ED_State_s, "FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13 && ED_FrameTime_13==5) { backend_set_config_int(ED_State_s, "FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14 && ED_FrameTime_14==5) { backend_set_config_int(ED_State_s, "FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15 && ED_FrameTime_15==5) { backend_set_config_int(ED_State_s, "FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16 && ED_FrameTime_16==5) { backend_set_config_int(ED_State_s, "FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17 && ED_FrameTime_17==5) { backend_set_config_int(ED_State_s, "FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18 && ED_FrameTime_18==5) { backend_set_config_int(ED_State_s, "FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19 && ED_FrameTime_19==5) { backend_set_config_int(ED_State_s, "FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20 && ED_FrameTime_20==5) { backend_set_config_int(ED_State_s, "FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21 && ED_FrameTime_21==5) { backend_set_config_int(ED_State_s, "FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22 && ED_FrameTime_22==5) { backend_set_config_int(ED_State_s, "FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23 && ED_FrameTime_23==5) { backend_set_config_int(ED_State_s, "FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24 && ED_FrameTime_24==5) { backend_set_config_int(ED_State_s, "FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25 && ED_FrameTime_25==5) { backend_set_config_int(ED_State_s, "FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26 && ED_FrameTime_26==5) { backend_set_config_int(ED_State_s, "FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27 && ED_FrameTime_27==5) { backend_set_config_int(ED_State_s, "FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28 && ED_FrameTime_28==5) { backend_set_config_int(ED_State_s, "FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29 && ED_FrameTime_29==5) { backend_set_config_int(ED_State_s, "FrameTime_29", ED_FrameTime_29+1); }
}

if(ED_State>=700 && ED_Special_Version==1){
if (ED_TotalFrames>= 0 && ED_FrameTime_00==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1 && ED_FrameTime_01==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2 && ED_FrameTime_02==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3 && ED_FrameTime_03==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4 && ED_FrameTime_04==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5 && ED_FrameTime_05==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6 && ED_FrameTime_06==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7 && ED_FrameTime_07==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8 && ED_FrameTime_08==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9 && ED_FrameTime_09==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10 && ED_FrameTime_10==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11 && ED_FrameTime_11==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12 && ED_FrameTime_12==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13 && ED_FrameTime_13==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14 && ED_FrameTime_14==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15 && ED_FrameTime_15==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16 && ED_FrameTime_16==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17 && ED_FrameTime_17==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18 && ED_FrameTime_18==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19 && ED_FrameTime_19==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20 && ED_FrameTime_20==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21 && ED_FrameTime_21==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22 && ED_FrameTime_22==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23 && ED_FrameTime_23==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24 && ED_FrameTime_24==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25 && ED_FrameTime_25==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26 && ED_FrameTime_26==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27 && ED_FrameTime_27==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28 && ED_FrameTime_28==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29 && ED_FrameTime_29==5) { backend_set_config_int(ED_State_s, "V1_FrameTime_29", ED_FrameTime_29+1); }
}

if(ED_State>=700 && ED_Special_Version==2){
if (ED_TotalFrames>= 0 && ED_FrameTime_00==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1 && ED_FrameTime_01==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2 && ED_FrameTime_02==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3 && ED_FrameTime_03==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4 && ED_FrameTime_04==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5 && ED_FrameTime_05==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6 && ED_FrameTime_06==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7 && ED_FrameTime_07==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8 && ED_FrameTime_08==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9 && ED_FrameTime_09==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10 && ED_FrameTime_10==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11 && ED_FrameTime_11==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12 && ED_FrameTime_12==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13 && ED_FrameTime_13==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14 && ED_FrameTime_14==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15 && ED_FrameTime_15==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16 && ED_FrameTime_16==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17 && ED_FrameTime_17==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18 && ED_FrameTime_18==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19 && ED_FrameTime_19==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20 && ED_FrameTime_20==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21 && ED_FrameTime_21==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22 && ED_FrameTime_22==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23 && ED_FrameTime_23==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24 && ED_FrameTime_24==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25 && ED_FrameTime_25==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26 && ED_FrameTime_26==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27 && ED_FrameTime_27==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28 && ED_FrameTime_28==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29 && ED_FrameTime_29==5) { backend_set_config_int(ED_State_s, "V2_FrameTime_29", ED_FrameTime_29+1); }
}

if(ED_State>=700 && ED_Special_Version==3){
if (ED_TotalFrames>= 0 && ED_FrameTime_00==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1 && ED_FrameTime_01==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2 && ED_FrameTime_02==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3 && ED_FrameTime_03==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4 && ED_FrameTime_04==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5 && ED_FrameTime_05==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6 && ED_FrameTime_06==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7 && ED_FrameTime_07==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8 && ED_FrameTime_08==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9 && ED_FrameTime_09==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10 && ED_FrameTime_10==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11 && ED_FrameTime_11==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12 && ED_FrameTime_12==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13 && ED_FrameTime_13==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14 && ED_FrameTime_14==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15 && ED_FrameTime_15==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16 && ED_FrameTime_16==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17 && ED_FrameTime_17==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18 && ED_FrameTime_18==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19 && ED_FrameTime_19==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20 && ED_FrameTime_20==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21 && ED_FrameTime_21==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22 && ED_FrameTime_22==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23 && ED_FrameTime_23==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24 && ED_FrameTime_24==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25 && ED_FrameTime_25==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26 && ED_FrameTime_26==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27 && ED_FrameTime_27==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28 && ED_FrameTime_28==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29 && ED_FrameTime_29==5) { backend_set_config_int(ED_State_s, "V3_FrameTime_29", ED_FrameTime_29+1); }
}

}

void ED_load_inputs(int ED_State){
//---
//atualiza tabela de golpes especiais - magias - special

//zera o array dos especiais
for(int indx=0; indx<=9; indx++){
for(int ind=0; ind<=16; ind++){
P[1].Special_Inputs_c[indx][ind]=0;
P[1].Special_Inputs_b[indx][ind]=0;
P[1].Special_Inputs[indx][ind]=0;
}
}

char StrSpecialInput[99];
sprintf(StrSpecialInput, "data/chars/%s/special.ini", P[1].Name);
backend_set_config_file(StrSpecialInput);
char str[3];
//carrega os inputs dos especiais
for(int ind=0; ind<=9; ind++){
if(ind==0) { sprintf(str, "700"); }
if(ind==1) { sprintf(str, "710"); }
if(ind==2) { sprintf(str, "720"); }
if(ind==3) { sprintf(str, "730"); }
if(ind==4) { sprintf(str, "740"); }
if(ind==5) { sprintf(str, "750"); }
if(ind==6) { sprintf(str, "760"); }
if(ind==7) { sprintf(str, "770"); }
if(ind==8) { sprintf(str, "780"); }
if(ind==9) { sprintf(str, "790"); }
P[1].Special_Inputs_c[ind][1]  = backend_get_config_int(str, "c1" , 0); //0 é neutro
P[1].Special_Inputs_c[ind][2]  = backend_get_config_int(str, "c2" , 0);
P[1].Special_Inputs_c[ind][3]  = backend_get_config_int(str, "c3" , 0);
P[1].Special_Inputs_c[ind][4]  = backend_get_config_int(str, "c4" , 0);
P[1].Special_Inputs_c[ind][5]  = backend_get_config_int(str, "c5" , 0);
P[1].Special_Inputs_c[ind][6]  = backend_get_config_int(str, "c6" , 0);
P[1].Special_Inputs_c[ind][7]  = backend_get_config_int(str, "c7" , 0);
P[1].Special_Inputs_c[ind][8]  = backend_get_config_int(str, "c8" , 0);
P[1].Special_Inputs_c[ind][9]  = backend_get_config_int(str, "c9" , 0);
P[1].Special_Inputs_c[ind][10] = backend_get_config_int(str, "c10", 0);
P[1].Special_Inputs_c[ind][11] = backend_get_config_int(str, "c11", 0);
P[1].Special_Inputs_c[ind][12] = backend_get_config_int(str, "c12", 0);
P[1].Special_Inputs_c[ind][13] = backend_get_config_int(str, "c13", 0);
P[1].Special_Inputs_c[ind][14] = backend_get_config_int(str, "c14", 0);
P[1].Special_Inputs_c[ind][15] = backend_get_config_int(str, "c15", 0);
P[1].Special_Inputs_c[ind][16] = backend_get_config_int(str, "c16", 0);
P[1].Special_Inputs_b[ind][1]  = backend_get_config_int(str, "b1" , 0)*-1; //0 é neutro
P[1].Special_Inputs_b[ind][2]  = backend_get_config_int(str, "b2" , 0)*-1;
P[1].Special_Inputs_b[ind][3]  = backend_get_config_int(str, "b3" , 0)*-1;
P[1].Special_Inputs_b[ind][4]  = backend_get_config_int(str, "b4" , 0)*-1;
P[1].Special_Inputs_b[ind][5]  = backend_get_config_int(str, "b5" , 0)*-1;
P[1].Special_Inputs_b[ind][6]  = backend_get_config_int(str, "b6" , 0)*-1;
P[1].Special_Inputs_b[ind][7]  = backend_get_config_int(str, "b7" , 0)*-1;
P[1].Special_Inputs_b[ind][8]  = backend_get_config_int(str, "b8" , 0)*-1;
P[1].Special_Inputs_b[ind][9]  = backend_get_config_int(str, "b9" , 0)*-1;
P[1].Special_Inputs_b[ind][10] = backend_get_config_int(str, "b10", 0)*-1;
P[1].Special_Inputs_b[ind][11] = backend_get_config_int(str, "b11", 0)*-1;
P[1].Special_Inputs_b[ind][12] = backend_get_config_int(str, "b12", 0)*-1;
P[1].Special_Inputs_b[ind][13] = backend_get_config_int(str, "b13", 0)*-1;
P[1].Special_Inputs_b[ind][14] = backend_get_config_int(str, "b14", 0)*-1;
P[1].Special_Inputs_b[ind][15] = backend_get_config_int(str, "b15", 0)*-1;
P[1].Special_Inputs_b[ind][16] = backend_get_config_int(str, "b16", 0)*-1;
}

//contagem da qtde de comandos e botoes
for(int ind=1; ind<=16; ind++){
if( P[1].Special_Inputs_c[0][ind]!=0 ) { P[1].Special_Inputs_c[0][0]++; }
if( P[1].Special_Inputs_b[0][ind]!=0 ) { P[1].Special_Inputs_b[0][0]++; }
if( P[1].Special_Inputs_c[1][ind]!=0 ) { P[1].Special_Inputs_c[1][0]++; }
if( P[1].Special_Inputs_b[1][ind]!=0 ) { P[1].Special_Inputs_b[1][0]++; }
if( P[1].Special_Inputs_c[2][ind]!=0 ) { P[1].Special_Inputs_c[2][0]++; }
if( P[1].Special_Inputs_b[2][ind]!=0 ) { P[1].Special_Inputs_b[2][0]++; }
if( P[1].Special_Inputs_c[3][ind]!=0 ) { P[1].Special_Inputs_c[3][0]++; }
if( P[1].Special_Inputs_b[3][ind]!=0 ) { P[1].Special_Inputs_b[3][0]++; }
if( P[1].Special_Inputs_c[4][ind]!=0 ) { P[1].Special_Inputs_c[4][0]++; }
if( P[1].Special_Inputs_b[4][ind]!=0 ) { P[1].Special_Inputs_b[4][0]++; }
if( P[1].Special_Inputs_c[5][ind]!=0 ) { P[1].Special_Inputs_c[5][0]++; }
if( P[1].Special_Inputs_b[5][ind]!=0 ) { P[1].Special_Inputs_b[5][0]++; }
if( P[1].Special_Inputs_c[6][ind]!=0 ) { P[1].Special_Inputs_c[6][0]++; }
if( P[1].Special_Inputs_b[6][ind]!=0 ) { P[1].Special_Inputs_b[6][0]++; }
if( P[1].Special_Inputs_c[7][ind]!=0 ) { P[1].Special_Inputs_c[7][0]++; }
if( P[1].Special_Inputs_b[7][ind]!=0 ) { P[1].Special_Inputs_b[7][0]++; }
if( P[1].Special_Inputs_c[8][ind]!=0 ) { P[1].Special_Inputs_c[8][0]++; }
if( P[1].Special_Inputs_b[8][ind]!=0 ) { P[1].Special_Inputs_b[8][0]++; }
if( P[1].Special_Inputs_c[9][ind]!=0 ) { P[1].Special_Inputs_c[9][0]++; }
if( P[1].Special_Inputs_b[9][ind]!=0 ) { P[1].Special_Inputs_b[9][0]++; }
}

//input combinado
for(int indx=0; indx<=9; indx++){
for(int ind=1; ind<=P[1].Special_Inputs_c[indx][0]; ind++){
P[1].Special_Inputs[indx][ind] = P[1].Special_Inputs_c[indx][ind];
}
for(int ind=1; ind<=P[1].Special_Inputs_b[indx][0]; ind++){
P[1].Special_Inputs[indx][ind+P[1].Special_Inputs_c[indx][0]] = P[1].Special_Inputs_b[indx][ind];
}
P[1].Special_Inputs[indx][0]=P[1].Special_Inputs_c[indx][0]+P[1].Special_Inputs_b[indx][0];
}

//---

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EDITOR INICIALIZAR --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ED_inicializar(){
ED_MODE=1;

ED_Special_Version=1;
ED_ShowMsgSaving=0;
ED_FrameTime_00=0;
ED_FrameTime_01=0; ED_FrameTime_02=0; ED_FrameTime_03=0; ED_FrameTime_04=0; ED_FrameTime_05=0;
ED_FrameTime_06=0; ED_FrameTime_07=0; ED_FrameTime_08=0; ED_FrameTime_09=0; ED_FrameTime_10=0;
ED_FrameTime_11=0; ED_FrameTime_12=0; ED_FrameTime_13=0; ED_FrameTime_14=0; ED_FrameTime_15=0;
ED_FrameTime_16=0; ED_FrameTime_17=0; ED_FrameTime_18=0; ED_FrameTime_19=0; ED_FrameTime_20=0;
ED_FrameTime_21=0; ED_FrameTime_22=0; ED_FrameTime_23=0; ED_FrameTime_24=0; ED_FrameTime_25=0;
ED_FrameTime_26=0; ED_FrameTime_27=0; ED_FrameTime_28=0; ED_FrameTime_29=0; ED_FrameTime=0;
ED_Pause=0; ED_DrawBlueMode=0; ED_DrawRedMode=0; ED_bt_Null=0;
ED_Mx1=-1; ED_My1=-1; ED_Mx2=-1; ED_My2=-1;
Draw_CHBoxes_ED();
ED_HitBox_tot=0; ED_HurtBox_tot=0;
sprintf(ED_Name, "%s", P[1].Name);
Edtimer=0;
ED_StartFrame=Edtimer;
ED_State=100;
int ED_100_tot=-1; for (int i=0; i<=29; i++) { char txt[50]=""; if ( i< 10 ) { sprintf(txt, "data/chars/%s/100_0%i.pcx", ED_Name, i); }
if ( i>=10 ) { sprintf(txt, "data/chars/%s/100_%i.pcx" , ED_Name, i); }
if ( backend_file_exists(txt)) { ED_100_tot++; } else {i=29;} ED_TotalFrames=ED_100_tot; }
ED_IndexAnim=0;
ED_Lado=1;
ED_XAlign=0;
ED_YAlign=0;
ED_x=320/2;
ED_y=220;
ED_Altura=0;
ED_Largura=0;
ED_Altura_100=0;
ED_Largura_100=0;

//abastece MovPossiveis - Verifica a existencia de Movimentos (imgs nnn_00.pcx) na pasta do personagem
int i=0; char txt[50]="";
for(int ind=100;ind<=999; ind++){
char indINTtoCHAR[3]="";
sprintf(indINTtoCHAR, "%d", ind);
sprintf(txt, "data/chars/%s/%s_00.pcx", ED_Name, indINTtoCHAR ); if ( backend_file_exists(txt)) { MovPossiveis[i]=ind; i++; }
}

//faz o carregamento inicial do char.ini
char ED_State_s[3];
char ED_Caminho[99];

sprintf(ED_State_s, "%i", ED_State);
sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
backend_set_config_file(ED_Caminho);
strcpy(ED_Name_Display, (char *)backend_get_config_string("Info", "Name", "-"));
ED_XAlign    = backend_get_config_int   (ED_State_s, "XAlign" , ED_Largura/2 );
ED_YAlign    = backend_get_config_int   (ED_State_s, "YAlign" , ED_Altura );
ED_Tipo      = backend_get_config_int   ("Info"    , "Type"   , 1 );
ED_TotalFrames   = backend_get_config_int   (ED_State_s, "TotalFrames"   ,   ED_TotalFrames );
if (ED_TotalFrames>= 0) {ED_FrameTime_00 = backend_get_config_int(ED_State_s, "FrameTime_00", 6)-1; }
if (ED_TotalFrames>= 1) {ED_FrameTime_01 = backend_get_config_int(ED_State_s, "FrameTime_01", 6)-1; }
if (ED_TotalFrames>= 2) {ED_FrameTime_02 = backend_get_config_int(ED_State_s, "FrameTime_02", 6)-1; }
if (ED_TotalFrames>= 3) {ED_FrameTime_03 = backend_get_config_int(ED_State_s, "FrameTime_03", 6)-1; }
if (ED_TotalFrames>= 4) {ED_FrameTime_04 = backend_get_config_int(ED_State_s, "FrameTime_04", 6)-1; }
if (ED_TotalFrames>= 5) {ED_FrameTime_05 = backend_get_config_int(ED_State_s, "FrameTime_05", 6)-1; }
if (ED_TotalFrames>= 6) {ED_FrameTime_06 = backend_get_config_int(ED_State_s, "FrameTime_06", 6)-1; }
if (ED_TotalFrames>= 7) {ED_FrameTime_07 = backend_get_config_int(ED_State_s, "FrameTime_07", 6)-1; }
if (ED_TotalFrames>= 8) {ED_FrameTime_08 = backend_get_config_int(ED_State_s, "FrameTime_08", 6)-1; }
if (ED_TotalFrames>= 9) {ED_FrameTime_09 = backend_get_config_int(ED_State_s, "FrameTime_09", 6)-1; }
if (ED_TotalFrames>=10) {ED_FrameTime_10 = backend_get_config_int(ED_State_s, "FrameTime_10", 6)-1; }
if (ED_TotalFrames>=11) {ED_FrameTime_11 = backend_get_config_int(ED_State_s, "FrameTime_11", 6)-1; }
if (ED_TotalFrames>=12) {ED_FrameTime_12 = backend_get_config_int(ED_State_s, "FrameTime_12", 6)-1; }
if (ED_TotalFrames>=13) {ED_FrameTime_13 = backend_get_config_int(ED_State_s, "FrameTime_13", 6)-1; }
if (ED_TotalFrames>=14) {ED_FrameTime_14 = backend_get_config_int(ED_State_s, "FrameTime_14", 6)-1; }
if (ED_TotalFrames>=15) {ED_FrameTime_15 = backend_get_config_int(ED_State_s, "FrameTime_15", 6)-1; }
if (ED_TotalFrames>=16) {ED_FrameTime_16 = backend_get_config_int(ED_State_s, "FrameTime_16", 6)-1; }
if (ED_TotalFrames>=17) {ED_FrameTime_17 = backend_get_config_int(ED_State_s, "FrameTime_17", 6)-1; }
if (ED_TotalFrames>=18) {ED_FrameTime_18 = backend_get_config_int(ED_State_s, "FrameTime_18", 6)-1; }
if (ED_TotalFrames>=19) {ED_FrameTime_19 = backend_get_config_int(ED_State_s, "FrameTime_19", 6)-1; }
if (ED_TotalFrames>=20) {ED_FrameTime_20 = backend_get_config_int(ED_State_s, "FrameTime_20", 6)-1; }
if (ED_TotalFrames>=21) {ED_FrameTime_21 = backend_get_config_int(ED_State_s, "FrameTime_21", 6)-1; }
if (ED_TotalFrames>=22) {ED_FrameTime_22 = backend_get_config_int(ED_State_s, "FrameTime_22", 6)-1; }
if (ED_TotalFrames>=23) {ED_FrameTime_23 = backend_get_config_int(ED_State_s, "FrameTime_23", 6)-1; }
if (ED_TotalFrames>=24) {ED_FrameTime_24 = backend_get_config_int(ED_State_s, "FrameTime_24", 6)-1; }
if (ED_TotalFrames>=25) {ED_FrameTime_25 = backend_get_config_int(ED_State_s, "FrameTime_25", 6)-1; }
if (ED_TotalFrames>=26) {ED_FrameTime_26 = backend_get_config_int(ED_State_s, "FrameTime_26", 6)-1; }
if (ED_TotalFrames>=27) {ED_FrameTime_27 = backend_get_config_int(ED_State_s, "FrameTime_27", 6)-1; }
if (ED_TotalFrames>=28) {ED_FrameTime_28 = backend_get_config_int(ED_State_s, "FrameTime_28", 6)-1; }
if (ED_TotalFrames>=29) {ED_FrameTime_29 = backend_get_config_int(ED_State_s, "FrameTime_29", 6)-1; }

//salva o tempo de animacao 6 (se o tempo do frame for vazio, usa 6, que é o padrao)
if (ED_TotalFrames>= 0 && ED_FrameTime_00==5) { backend_set_config_int(ED_State_s, "FrameTime_00", ED_FrameTime_00+1); }
if (ED_TotalFrames>= 1 && ED_FrameTime_01==5) { backend_set_config_int(ED_State_s, "FrameTime_01", ED_FrameTime_01+1); }
if (ED_TotalFrames>= 2 && ED_FrameTime_02==5) { backend_set_config_int(ED_State_s, "FrameTime_02", ED_FrameTime_02+1); }
if (ED_TotalFrames>= 3 && ED_FrameTime_03==5) { backend_set_config_int(ED_State_s, "FrameTime_03", ED_FrameTime_03+1); }
if (ED_TotalFrames>= 4 && ED_FrameTime_04==5) { backend_set_config_int(ED_State_s, "FrameTime_04", ED_FrameTime_04+1); }
if (ED_TotalFrames>= 5 && ED_FrameTime_05==5) { backend_set_config_int(ED_State_s, "FrameTime_05", ED_FrameTime_05+1); }
if (ED_TotalFrames>= 6 && ED_FrameTime_06==5) { backend_set_config_int(ED_State_s, "FrameTime_06", ED_FrameTime_06+1); }
if (ED_TotalFrames>= 7 && ED_FrameTime_07==5) { backend_set_config_int(ED_State_s, "FrameTime_07", ED_FrameTime_07+1); }
if (ED_TotalFrames>= 8 && ED_FrameTime_08==5) { backend_set_config_int(ED_State_s, "FrameTime_08", ED_FrameTime_08+1); }
if (ED_TotalFrames>= 9 && ED_FrameTime_09==5) { backend_set_config_int(ED_State_s, "FrameTime_09", ED_FrameTime_09+1); }
if (ED_TotalFrames>=10 && ED_FrameTime_10==5) { backend_set_config_int(ED_State_s, "FrameTime_10", ED_FrameTime_10+1); }
if (ED_TotalFrames>=11 && ED_FrameTime_11==5) { backend_set_config_int(ED_State_s, "FrameTime_11", ED_FrameTime_11+1); }
if (ED_TotalFrames>=12 && ED_FrameTime_12==5) { backend_set_config_int(ED_State_s, "FrameTime_12", ED_FrameTime_12+1); }
if (ED_TotalFrames>=13 && ED_FrameTime_13==5) { backend_set_config_int(ED_State_s, "FrameTime_13", ED_FrameTime_13+1); }
if (ED_TotalFrames>=14 && ED_FrameTime_14==5) { backend_set_config_int(ED_State_s, "FrameTime_14", ED_FrameTime_14+1); }
if (ED_TotalFrames>=15 && ED_FrameTime_15==5) { backend_set_config_int(ED_State_s, "FrameTime_15", ED_FrameTime_15+1); }
if (ED_TotalFrames>=16 && ED_FrameTime_16==5) { backend_set_config_int(ED_State_s, "FrameTime_16", ED_FrameTime_16+1); }
if (ED_TotalFrames>=17 && ED_FrameTime_17==5) { backend_set_config_int(ED_State_s, "FrameTime_17", ED_FrameTime_17+1); }
if (ED_TotalFrames>=18 && ED_FrameTime_18==5) { backend_set_config_int(ED_State_s, "FrameTime_18", ED_FrameTime_18+1); }
if (ED_TotalFrames>=19 && ED_FrameTime_19==5) { backend_set_config_int(ED_State_s, "FrameTime_19", ED_FrameTime_19+1); }
if (ED_TotalFrames>=20 && ED_FrameTime_20==5) { backend_set_config_int(ED_State_s, "FrameTime_20", ED_FrameTime_20+1); }
if (ED_TotalFrames>=21 && ED_FrameTime_21==5) { backend_set_config_int(ED_State_s, "FrameTime_21", ED_FrameTime_21+1); }
if (ED_TotalFrames>=22 && ED_FrameTime_22==5) { backend_set_config_int(ED_State_s, "FrameTime_22", ED_FrameTime_22+1); }
if (ED_TotalFrames>=23 && ED_FrameTime_23==5) { backend_set_config_int(ED_State_s, "FrameTime_23", ED_FrameTime_23+1); }
if (ED_TotalFrames>=24 && ED_FrameTime_24==5) { backend_set_config_int(ED_State_s, "FrameTime_24", ED_FrameTime_24+1); }
if (ED_TotalFrames>=25 && ED_FrameTime_25==5) { backend_set_config_int(ED_State_s, "FrameTime_25", ED_FrameTime_25+1); }
if (ED_TotalFrames>=26 && ED_FrameTime_26==5) { backend_set_config_int(ED_State_s, "FrameTime_26", ED_FrameTime_26+1); }
if (ED_TotalFrames>=27 && ED_FrameTime_27==5) { backend_set_config_int(ED_State_s, "FrameTime_27", ED_FrameTime_27+1); }
if (ED_TotalFrames>=28 && ED_FrameTime_28==5) { backend_set_config_int(ED_State_s, "FrameTime_28", ED_FrameTime_28+1); }
if (ED_TotalFrames>=29 && ED_FrameTime_29==5) { backend_set_config_int(ED_State_s, "FrameTime_29", ED_FrameTime_29+1); }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FIM DO CODIGO. EOF                                                                                                                          //
// programado por DANIEL MOURA em 2015-2020 (dev@hamoopi.com)                                                                                  //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
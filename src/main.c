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

#include "backend/platform_compat.h"
#include "core/types.h"
#include "core/globals.h"
#include "modules/input.h"
#include "modules/collision.h"
#include "modules/player.h"
#include "modules/editor.h"
#include "game_loop/intro.h"
#include "game_loop/donation.h"
#include "game_loop/presentation.h"
#include "game_loop/play.h"
#include "game_loop/stage_select.h"
#include "game_loop/char_select.h"
#include "game_loop/options.h"
#include "game_loop/versus.h"
#include "game_loop/edit.h"
#include <stdio.h>
#include <math.h>


///////////////////////////////////////////////////////////////////////////////
// DECLARACOES INICIAIS -------------------------------------------------[**01]
///////////////////////////////////////////////////////////////////////////////

char versao[45] = "HAMOOPI v.001A";

int sair = 0;
void sair_allegro() { sair = 1; }
// Frame timing variables for SDL2
Uint64 frame_start_time = 0;
Uint64 frame_count = 0;  // Global frame counter replacing timer
float delay = 0;
int Horas = 0;
int Minutos = 0;
int Segundos = 0;
int timermenus = -1;
int Ctrl_FPS = 60;
int WindowResNumber = 2;
int WindowResX = 640;
int WindowResY = 480;

int ativa_especial = 0;
int bta = 0;
int btb = 0;
int btc = 0;
int navAtlas = 0; //utilizado para navegar no debug Atlas
int contatofisico = 0;

struct HitSparkDEF HitSpark[99];
struct FireballsDEF Fireball[3];
struct PlayerDEF P[3];

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

int op_sound_volume = 255;
int op_sfx_volume = 255;
char IDIOMA[3];
int IntroMode = 1;
int IntroTimer = 0;
float AnimIntroTimer = 0; //animacao de intro timer
float AnimTransTimer = -1; //animacao de transicao timer
int CtrlAnimIntro[16];
int CtrlAnimTrans[30];
float EndRoundSlowDown = 60;
int EndRoundT = 500; //tempo de espera até reinciar os rounds
int DonationScreen = 0;
int ApresentacaoMode = 0;
int menu_op = 1;
int OptionsMode = 0;
int options_op = 1;
int op_desenhar_sombras = 1;
int op_ShowFrameData = 0;
int GamePlayMode = 0;
int TelaDeVersus = 0;
int TelaDeVersusTimer = 0;
int SelectCharMode = 0;
int SelectCharP1ID = 0;
int SelectCharP2ID = 0;
char ChoiceP1[50];
char ChoiceP2[50];
char ChoiceBG[50];
int NumPersonagensEscolhidos = 0;
char P1BIGDisplaystring[40] = "";
char P2BIGDisplaystring[40] = "";
char P1_Pallete_string[40] = "";
char P2_Pallete_string[40] = "";
int SelectCharTimerAnim = 0;
int EditMode = 0;
int EditModeTime = 0;
int Draw_Debug = 0;
int Draw_Input = 0;
int Draw_Box = 0;
int FadeCtr = 255;
int FadeIN = 0;
int FadeOUT = 1; //inicia em FadeOUT... na intro
float FadeVelocidade = 10;

//modo historia e versus
int ModoHistoria = 0;
int difficulty = 3;
int ModoMapa = 0;
int ModoMapaTimerAnim = 0;
int Qtde_HitBox = 0;
char Lista_de_Personagens_Instalados[9][50];
char Lista_de_Personagens_ArcadeMode[9][50];
char Lista_de_Cenarios_Instalados[9][50];
char Lista_de_Cenarios_ArcadeMode[9][50];
int Qtde_Personagens_Instalados;
int Qtde_Cenarios_Instalados;
int Estagio_Atual = 1;
int Maximo_de_Estagios = 8;
int MapCenterX;
int MapCenterY;
int MapPosX;
int MapPosY;

int desabilita_players = 0;
unsigned int HitPauseKO = 500;
int key_Mouse_L_pressed, key_Mouse_L_hold, key_Mouse_L_released, key_Mouse_L_status;
int key_Mouse_R_pressed, key_Mouse_R_hold, key_Mouse_R_released, key_Mouse_R_status;
int key_F1_pressed, key_F1_hold, key_F1_released, key_F1_status;
int key_F2_pressed, key_F2_hold, key_F2_released, key_F2_status;
int key_F3_pressed, key_F3_hold, key_F3_released, key_F3_status;
int key_F4_pressed, key_F4_hold, key_F4_released, key_F4_status;
int AlturaPiso = 0;
int MeioDaTela = 0;
float VScreen_x = 0;
float VScreen_y = 0;
float VScreen_x2 = 0;
float VScreen_y2 = 0;
float VScreen_w = 640;
float VScreen_h = 480;
int VScreen_FatorZoom = 0;
int Zoom_eixo = 0;
int ZoomMaximoAtingido = 0;
int op_Zoom = 0;
int VariacaoY = 0; //usado no deslocamento do eixo y ex: pulos
int RoundTime = 0;
int RoundTotal = 0;
int RoundAtual = 1;
int timer_rounds = 0; //utilizado para controlar animacoes dos rounds
int timer_final_de_rounds = 0;
int P1_FrameTime_00 = 0;
int P1_FrameTime_01 = 0;
int P1_FrameTime_02 = 0;
int P1_FrameTime_03 = 0;
int P1_FrameTime_04 = 0;
int P1_FrameTime_05 = 0;
int P1_FrameTime_06 = 0;
int P1_FrameTime_07 = 0;
int P1_FrameTime_08 = 0;
int P1_FrameTime_09 = 0;
int P1_FrameTime_10 = 0;
int P1_FrameTime_11 = 0;
int P1_FrameTime_12 = 0;
int P1_FrameTime_13 = 0;
int P1_FrameTime_14 = 0;
int P1_FrameTime_15 = 0;
int P1_FrameTime_16 = 0;
int P1_FrameTime_17 = 0;
int P1_FrameTime_18 = 0;
int P1_FrameTime_19 = 0;
int P1_FrameTime_20 = 0;
int P1_FrameTime_21 = 0;
int P1_FrameTime_22 = 0;
int P1_FrameTime_23 = 0;
int P1_FrameTime_24 = 0;
int P1_FrameTime_25 = 0;
int P1_FrameTime_26 = 0;
int P1_FrameTime_27 = 0;
int P1_FrameTime_28 = 0;
int P1_FrameTime_29 = 0;
int P1_FrameTime = 0;
int ED_FrameTime_00 = 0;
int ED_FrameTime_01 = 0;
int ED_FrameTime_02 = 0;
int ED_FrameTime_03 = 0;
int ED_FrameTime_04 = 0;
int ED_FrameTime_05 = 0;
int ED_FrameTime_06 = 0;
int ED_FrameTime_07 = 0;
int ED_FrameTime_08 = 0;
int ED_FrameTime_09 = 0;
int ED_FrameTime_10 = 0;
int ED_FrameTime_11 = 0;
int ED_FrameTime_12 = 0;
int ED_FrameTime_13 = 0;
int ED_FrameTime_14 = 0;
int ED_FrameTime_15 = 0;
int ED_FrameTime_16 = 0;
int ED_FrameTime_17 = 0;
int ED_FrameTime_18 = 0;
int ED_FrameTime_19 = 0;
int ED_FrameTime_20 = 0;
int ED_FrameTime_21 = 0;
int ED_FrameTime_22 = 0;
int ED_FrameTime_23 = 0;
int ED_FrameTime_24 = 0;
int ED_FrameTime_25 = 0;
int ED_FrameTime_26 = 0;
int ED_FrameTime_27 = 0;
int ED_FrameTime_28 = 0;
int ED_FrameTime_29 = 0;
int ED_FrameTime = 0;
int P2_FrameTime_00 = 0;
int P2_FrameTime_01 = 0;
int P2_FrameTime_02 = 0;
int P2_FrameTime_03 = 0;
int P2_FrameTime_04 = 0;
int P2_FrameTime_05 = 0;
int P2_FrameTime_06 = 0;
int P2_FrameTime_07 = 0;
int P2_FrameTime_08 = 0;
int P2_FrameTime_09 = 0;
int P2_FrameTime_10 = 0;
int P2_FrameTime_11 = 0;
int P2_FrameTime_12 = 0;
int P2_FrameTime_13 = 0;
int P2_FrameTime_14 = 0;
int P2_FrameTime_15 = 0;
int P2_FrameTime_16 = 0;
int P2_FrameTime_17 = 0;
int P2_FrameTime_18 = 0;
int P2_FrameTime_19 = 0;
int P2_FrameTime_20 = 0;
int P2_FrameTime_21 = 0;
int P2_FrameTime_22 = 0;
int P2_FrameTime_23 = 0;
int P2_FrameTime_24 = 0;
int P2_FrameTime_25 = 0;
int P2_FrameTime_26 = 0;
int P2_FrameTime_27 = 0;
int P2_FrameTime_28 = 0;
int P2_FrameTime_29 = 0;
int P2_FrameTime = 0;
int P1_Fireball_FrameTime_00 = 0;
int P1_Fireball_FrameTime_01 = 0;
int P1_Fireball_FrameTime_02 = 0;
int P1_Fireball_FrameTime_03 = 0;
int P1_Fireball_FrameTime_04 = 0;
int P1_Fireball_FrameTime_05 = 0;
int P1_Fireball_FrameTime_06 = 0;
int P1_Fireball_FrameTime_07 = 0;
int P1_Fireball_FrameTime_08 = 0;
int P1_Fireball_FrameTime_09 = 0;
int P1_Fireball_FrameTime_10 = 0;
int P1_Fireball_FrameTime = 0;
int P2_Fireball_FrameTime_00 = 0;
int P2_Fireball_FrameTime_01 = 0;
int P2_Fireball_FrameTime_02 = 0;
int P2_Fireball_FrameTime_03 = 0;
int P2_Fireball_FrameTime_04 = 0;
int P2_Fireball_FrameTime_05 = 0;
int P2_Fireball_FrameTime_06 = 0;
int P2_Fireball_FrameTime_07 = 0;
int P2_Fireball_FrameTime_08 = 0;
int P2_Fireball_FrameTime_09 = 0;
int P2_Fireball_FrameTime_10 = 0;
int P2_Fireball_FrameTime = 0;
int P1_HurtBox01x1 = 0;
int P1_HurtBox01y1 = 0;
int P1_HurtBox01x2 = 0;
int P1_HurtBox01y2 = 0;
int P1_HurtBox02x1 = 0;
int P1_HurtBox02y1 = 0;
int P1_HurtBox02x2 = 0;
int P1_HurtBox02y2 = 0;
int P1_HurtBox03x1 = 0;
int P1_HurtBox03y1 = 0;
int P1_HurtBox03x2 = 0;
int P1_HurtBox03y2 = 0;
int P1_HurtBox04x1 = 0;
int P1_HurtBox04y1 = 0;
int P1_HurtBox04x2 = 0;
int P1_HurtBox04y2 = 0;
int P1_HurtBox05x1 = 0;
int P1_HurtBox05y1 = 0;
int P1_HurtBox05x2 = 0;
int P1_HurtBox05y2 = 0;
int P1_HurtBox06x1 = 0;
int P1_HurtBox06y1 = 0;
int P1_HurtBox06x2 = 0;
int P1_HurtBox06y2 = 0;
int P1_HurtBox07x1 = 0;
int P1_HurtBox07y1 = 0;
int P1_HurtBox07x2 = 0;
int P1_HurtBox07y2 = 0;
int P1_HurtBox08x1 = 0;
int P1_HurtBox08y1 = 0;
int P1_HurtBox08x2 = 0;
int P1_HurtBox08y2 = 0;
int P1_HurtBox09x1 = 0;
int P1_HurtBox09y1 = 0;
int P1_HurtBox09x2 = 0;
int P1_HurtBox09y2 = 0;
int P1_HitBox01x1 = 0;
int P1_HitBox01y1 = 0;
int P1_HitBox01x2 = 0;
int P1_HitBox01y2 = 0;
int P1_HitBox02x1 = 0;
int P1_HitBox02y1 = 0;
int P1_HitBox02x2 = 0;
int P1_HitBox02y2 = 0;
int P1_HitBox03x1 = 0;
int P1_HitBox03y1 = 0;
int P1_HitBox03x2 = 0;
int P1_HitBox03y2 = 0;
int P1_HitBox04x1 = 0;
int P1_HitBox04y1 = 0;
int P1_HitBox04x2 = 0;
int P1_HitBox04y2 = 0;
int P1_HitBox05x1 = 0;
int P1_HitBox05y1 = 0;
int P1_HitBox05x2 = 0;
int P1_HitBox05y2 = 0;
int P1_HitBox06x1 = 0;
int P1_HitBox06y1 = 0;
int P1_HitBox06x2 = 0;
int P1_HitBox06y2 = 0;
int P1_HitBox07x1 = 0;
int P1_HitBox07y1 = 0;
int P1_HitBox07x2 = 0;
int P1_HitBox07y2 = 0;
int P1_HitBox08x1 = 0;
int P1_HitBox08y1 = 0;
int P1_HitBox08x2 = 0;
int P1_HitBox08y2 = 0;
int P1_HitBox09x1 = 0;
int P1_HitBox09y1 = 0;
int P1_HitBox09x2 = 0;
int P1_HitBox09y2 = 0;
int P1_HurtBox_tot = 0;
int P1_HitBox_tot = 0;
int P1_Fireball_HurtBox01x1 = 0;
int P1_Fireball_HurtBox01y1 = 0;
int P1_Fireball_HurtBox01x2 = 0;
int P1_Fireball_HurtBox01y2 = 0;
int P2_Fireball_HurtBox01x1 = 0;
int P2_Fireball_HurtBox01y1 = 0;
int P2_Fireball_HurtBox01x2 = 0;
int P2_Fireball_HurtBox01y2 = 0;
int P2_HurtBox01x1 = 0;
int P2_HurtBox01y1 = 0;
int P2_HurtBox01x2 = 0;
int P2_HurtBox01y2 = 0;
int P2_HurtBox02x1 = 0;
int P2_HurtBox02y1 = 0;
int P2_HurtBox02x2 = 0;
int P2_HurtBox02y2 = 0;
int P2_HurtBox03x1 = 0;
int P2_HurtBox03y1 = 0;
int P2_HurtBox03x2 = 0;
int P2_HurtBox03y2 = 0;
int P2_HurtBox04x1 = 0;
int P2_HurtBox04y1 = 0;
int P2_HurtBox04x2 = 0;
int P2_HurtBox04y2 = 0;
int P2_HurtBox05x1 = 0;
int P2_HurtBox05y1 = 0;
int P2_HurtBox05x2 = 0;
int P2_HurtBox05y2 = 0;
int P2_HurtBox06x1 = 0;
int P2_HurtBox06y1 = 0;
int P2_HurtBox06x2 = 0;
int P2_HurtBox06y2 = 0;
int P2_HurtBox07x1 = 0;
int P2_HurtBox07y1 = 0;
int P2_HurtBox07x2 = 0;
int P2_HurtBox07y2 = 0;
int P2_HurtBox08x1 = 0;
int P2_HurtBox08y1 = 0;
int P2_HurtBox08x2 = 0;
int P2_HurtBox08y2 = 0;
int P2_HurtBox09x1 = 0;
int P2_HurtBox09y1 = 0;
int P2_HurtBox09x2 = 0;
int P2_HurtBox09y2 = 0;
int P2_HitBox01x1 = 0;
int P2_HitBox01y1 = 0;
int P2_HitBox01x2 = 0;
int P2_HitBox01y2 = 0;
int P2_HitBox02x1 = 0;
int P2_HitBox02y1 = 0;
int P2_HitBox02x2 = 0;
int P2_HitBox02y2 = 0;
int P2_HitBox03x1 = 0;
int P2_HitBox03y1 = 0;
int P2_HitBox03x2 = 0;
int P2_HitBox03y2 = 0;
int P2_HitBox04x1 = 0;
int P2_HitBox04y1 = 0;
int P2_HitBox04x2 = 0;
int P2_HitBox04y2 = 0;
int P2_HitBox05x1 = 0;
int P2_HitBox05y1 = 0;
int P2_HitBox05x2 = 0;
int P2_HitBox05y2 = 0;
int P2_HitBox06x1 = 0;
int P2_HitBox06y1 = 0;
int P2_HitBox06x2 = 0;
int P2_HitBox06y2 = 0;
int P2_HitBox07x1 = 0;
int P2_HitBox07y1 = 0;
int P2_HitBox07x2 = 0;
int P2_HitBox07y2 = 0;
int P2_HitBox08x1 = 0;
int P2_HitBox08y1 = 0;
int P2_HitBox08x2 = 0;
int P2_HitBox08y2 = 0;
int P2_HitBox09x1 = 0;
int P2_HitBox09y1 = 0;
int P2_HitBox09x2 = 0;
int P2_HitBox09y2 = 0;
int P2_HurtBox_tot = 0;
int P2_HitBox_tot = 0;
int P1_Fireball_HitBox01x1 = 0;
int P1_Fireball_HitBox01y1 = 0;
int P1_Fireball_HitBox01x2 = 0;
int P1_Fireball_HitBox01y2 = 0;
int P2_Fireball_HitBox01x1 = 0;
int P2_Fireball_HitBox01y1 = 0;
int P2_Fireball_HitBox01x2 = 0;
int P2_Fireball_HitBox01y2 = 0;
int P1_Hit_x = 0;
int P1_Hit_y = 0;
int P2_Hit_x = 0;
int P2_Hit_y = 0;
int colisaoxP1 = 0;
int alturadohitp2 = 0;
int colisaoxP2 = 0;
int alturadohitp1 = 0;
int colisaoxP1Fireball = 0;
int colisaoxP2Fireball = 0;
int temp1x, temp1y, temp2x, temp2y; //usado para corrigir os HBoxes
int HitPause1 = 15;
int HitPause2 = 15;
int HitPause3 = 15;
int P1_DMG1 = 0;
int P1_DMG2 = 0;
int P1_DMG3 = 0;
int P2_DMG1 = 0;
int P2_DMG2 = 0;
int P2_DMG3 = 0;
int MomentoDoP1 = 0;
int MomentoDoP2 = 0;
int ForcaDoGolpeP1 = 0;
int ForcaDoGolpeP2 = 0;
int AHitP1 = 1;
int AHitP2 = 1;
int P1HitPause = 0;
int P2HitPause = 0;
int P1HitOn = 0;
int P2HitOn = 0;
int ShakeDist = 1;
int PlaySoundHitLvl1 = 0;
int PlaySoundHitLvl2 = 0;
int PlaySoundHitLvl3 = 0;
int P1_ContadorDeCor = 0;
int P1_COR_ORIGINAL;
int P1_COR_ORIGINAL_R;
int P1_COR_ORIGINAL_G;
int P1_COR_ORIGINAL_B;
int P1_COR_ALTERNATIVA;
int P1_COR_ALTERNATIVA_R;
int P1_COR_ALTERNATIVA_G;
int P1_COR_ALTERNATIVA_B;
int P2_ContadorDeCor = 0;
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
int FD_P1_Startup = 0;
int FD_P1_Active = 0;
int FD_P1_Recovery = 0;
int FD_P1_Active_IN = -1;
int FD_P1_Active_OUT = -1;
int FD_P1_HitBox01x1;
int FD_P2_Status; //1=STARTUP, 2=ACTIVE, 3=RECOVERY
int FD_P2_Startup = 0;
int FD_P2_Active = 0;
int FD_P2_Recovery = 0;
int FD_P2_Active_IN = -1;
int FD_P2_Active_OUT = -1;
int FD_P2_HitBox01x1;

//Editor
char ED_Name[50] = "";
int Edtimer = 0;
int ED_CharID = 1;
int ED_Tipo;
int ED_MODE = 1;
int ED_Special_Version = 1;
int ED_StartFrame = 0;
int ED_TotalFrames = 0;
int ED_State = 100;
int ED_IndexAnim = 0;
int ED_Lado = 1;
int ED_XAlign = 0;
int ED_YAlign = 0;
int ED_x = 0;
int ED_y = 0;
int ED_Altura = 0;
int ED_Largura = 0;
int ED_Altura_100 = 0;
int ED_Largura_100 = 0;
int MovPossiveis[99];
int MovPossiveisIndex = 0;
int ED_Pause = 0;
int ED_DrawBlueMode = 0;
int ED_DrawRedMode = 0;
int ED_bt_Null = 0;
int ED_CarregarDados = 0;
int ED_Mx1 = -1;
int ED_My1 = -1;
int ED_Mx2 = -1;
int ED_My2 = -1;
int ED_HitBox01x1 = -1;
int ED_HitBox01y1 = -1;
int ED_HitBox01x2 = -1;
int ED_HitBox01y2 = -1;
int ED_HitBox02x1 = -1;
int ED_HitBox02y1 = -1;
int ED_HitBox02x2 = -1;
int ED_HitBox02y2 = -1;
int ED_HitBox03x1 = -1;
int ED_HitBox03y1 = -1;
int ED_HitBox03x2 = -1;
int ED_HitBox03y2 = -1;
int ED_HitBox04x1 = -1;
int ED_HitBox04y1 = -1;
int ED_HitBox04x2 = -1;
int ED_HitBox04y2 = -1;
int ED_HitBox05x1 = -1;
int ED_HitBox05y1 = -1;
int ED_HitBox05x2 = -1;
int ED_HitBox05y2 = -1;
int ED_HitBox06x1 = -1;
int ED_HitBox06y1 = -1;
int ED_HitBox06x2 = -1;
int ED_HitBox06y2 = -1;
int ED_HitBox07x1 = -1;
int ED_HitBox07y1 = -1;
int ED_HitBox07x2 = -1;
int ED_HitBox07y2 = -1;
int ED_HitBox08x1 = -1;
int ED_HitBox08y1 = -1;
int ED_HitBox08x2 = -1;
int ED_HitBox08y2 = -1;
int ED_HitBox09x1 = -1;
int ED_HitBox09y1 = -1;
int ED_HitBox09x2 = -1;
int ED_HitBox09y2 = -1;
int ED_HurtBox01x1 = -1;
int ED_HurtBox01y1 = -1;
int ED_HurtBox01x2 = -1;
int ED_HurtBox01y2 = -1;
int ED_HurtBox02x1 = -1;
int ED_HurtBox02y1 = -1;
int ED_HurtBox02x2 = -1;
int ED_HurtBox02y2 = -1;
int ED_HurtBox03x1 = -1;
int ED_HurtBox03y1 = -1;
int ED_HurtBox03x2 = -1;
int ED_HurtBox03y2 = -1;
int ED_HurtBox04x1 = -1;
int ED_HurtBox04y1 = -1;
int ED_HurtBox04x2 = -1;
int ED_HurtBox04y2 = -1;
int ED_HurtBox05x1 = -1;
int ED_HurtBox05y1 = -1;
int ED_HurtBox05x2 = -1;
int ED_HurtBox05y2 = -1;
int ED_HurtBox06x1 = -1;
int ED_HurtBox06y1 = -1;
int ED_HurtBox06x2 = -1;
int ED_HurtBox06y2 = -1;
int ED_HurtBox07x1 = -1;
int ED_HurtBox07y1 = -1;
int ED_HurtBox07x2 = -1;
int ED_HurtBox07y2 = -1;
int ED_HurtBox08x1 = -1;
int ED_HurtBox08y1 = -1;
int ED_HurtBox08x2 = -1;
int ED_HurtBox08y2 = -1;
int ED_HurtBox09x1 = -1;
int ED_HurtBox09y1 = -1;
int ED_HurtBox09x2 = -1;
int ED_HurtBox09y2 = -1;
int ED_HitBox_tot = 0;
int ED_HurtBox_tot = 0;
int ED_io = 1;
int ED_alertsave = 0;
int ED_alertsave2 = 0;
int ED_ShowMsgSaving = 0;
int ED_MovimentaPivot = 0;
char ED_Name_Display[50] = "char1";

BITMAP *MINIsprDisplayArcadeMode[9];
BITMAP *MINIsprDisplay[9];
BITMAP *P1BIGDisplay;
BITMAP *P2BIGDisplay;
BITMAP *P2BIGDisplayInv;

BITMAP *spr991_00 = NULL;
BITMAP *spr991_01 = NULL;
BITMAP *spr991_02 = NULL;
BITMAP *spr991_03 = NULL;
BITMAP *spr991_04 = NULL;
BITMAP *spr991_05 = NULL;
BITMAP *spr992_00 = NULL;
BITMAP *spr992_01 = NULL;
BITMAP *spr992_02 = NULL;
BITMAP *spr992_03 = NULL;
BITMAP *spr992_04 = NULL;
BITMAP *spr992_05 = NULL;
BITMAP *spr993_00 = NULL;
BITMAP *spr993_01 = NULL;
BITMAP *spr993_02 = NULL;
BITMAP *spr993_03 = NULL;
BITMAP *spr993_04 = NULL;
BITMAP *spr993_05 = NULL;
BITMAP *spr994_00 = NULL;
BITMAP *spr994_01 = NULL;
BITMAP *spr994_02 = NULL;
BITMAP *spr994_03 = NULL;
BITMAP *spr994_04 = NULL;
BITMAP *spr994_05 = NULL;

BITMAP *spr_input_0 = NULL;
BITMAP *spr_input_1 = NULL;
BITMAP *spr_input_2 = NULL;
BITMAP *spr_input_3 = NULL;
BITMAP *spr_input_4 = NULL;
BITMAP *spr_input_5 = NULL;
BITMAP *spr_input_6 = NULL;
BITMAP *spr_input_7 = NULL;
BITMAP *spr_input_8 = NULL;
BITMAP *spr_input_9 = NULL;
BITMAP *spr_input_10 = NULL;
BITMAP *spr_input_11 = NULL;
BITMAP *spr_input_12 = NULL;
BITMAP *spr_input_13 = NULL;
BITMAP *spr_input_14 = NULL;
BITMAP *spr_input_15 = NULL;
BITMAP *spr_input_16 = NULL;
BITMAP *spr_input_17 = NULL;
BITMAP *spr_bg_bar = NULL;
BITMAP *spr_energy_bar = NULL;
BITMAP *spr_energy_bar_full = NULL;
BITMAP *spr_energy_red_bar = NULL;
BITMAP *spr_energy_red_bar_full = NULL;
BITMAP *spr_bg_bar_sp = NULL;
BITMAP *spr_bg_energy_bar_sp = NULL;
BITMAP *GAME_logo = NULL;
BITMAP *flag_BR = NULL;
BITMAP *sel_mark_p1 = NULL;
BITMAP *sel_mark_p2 = NULL;
BITMAP *flag_US = NULL;
BITMAP *SELECT_CHARS = NULL;
BITMAP *VS_SCREEN = NULL;
BITMAP *vs_icon = NULL;
BITMAP *SELECT_BG = NULL;
BITMAP *donation = NULL;
BITMAP *spr_p1_cursor = NULL;
BITMAP *spr_p2_cursor = NULL;
BITMAP *spr_cursor_historia = NULL;
BITMAP *spr_cursor_vazio = NULL;
BITMAP *spr_ponteiro = NULL;
BITMAP *spr_menu_icon = NULL;
BITMAP *GAME_intro = NULL;
BITMAP *GAME_options = NULL;
BITMAP *char_generic = NULL;
BITMAP *char_generic2x = NULL;
BITMAP *spr_mold_results = NULL;
BITMAP *spr_result_perfect = NULL;
BITMAP *spr_result_win = NULL;
BITMAP *spr_splash_round1 = NULL;
BITMAP *spr_splash_round2 = NULL;
BITMAP *spr_splash_round3 = NULL;
BITMAP *spr_splash_round4 = NULL;
BITMAP *spr_splash_round5 = NULL;
BITMAP *spr_splash_fight = NULL;
BITMAP *spr_splash_youwin = NULL;
BITMAP *spr_splash_p1win = NULL;
BITMAP *spr_splash_p2win = NULL;
BITMAP *spr_splash_youlose = NULL;
BITMAP *spr_splash_ko = NULL;
BITMAP *spr_splash_perfect = NULL;
BITMAP *spr_splash_draw = NULL;
BITMAP *spr_splash_time_over = NULL;
BITMAP *spr_num[10];
BITMAP *edit_bt_blue = NULL;
BITMAP *edit_bt_red = NULL;
BITMAP *edit_bt_null = NULL;
BITMAP *edit_bt_null0 = NULL;
BITMAP *edit_prevst = NULL;
BITMAP *edit_nextst = NULL;
BITMAP *edit_prevchar = NULL;
BITMAP *edit_nextchar = NULL;
BITMAP *edit_firstchar = NULL;
BITMAP *edit_lastchar = NULL;
BITMAP *spr_nao_implementado = NULL;
BITMAP *edit_playback = NULL;
BITMAP *edit_pause = NULL;
BITMAP *edit_bt_FrameTime = NULL;
BITMAP *edit_bt_plus = NULL;
BITMAP *edit_bt_minus = NULL;
BITMAP *mouse = NULL;
BITMAP *mouse2 = NULL;
BITMAP *save_file = NULL;
BITMAP *bt_pivot = NULL;
BITMAP *spr000_00 = NULL;
BITMAP *spr000_01 = NULL;
BITMAP *bt_joystick = NULL;
BITMAP *ed_mode1_on = NULL;
BITMAP *ed_mode2_on = NULL;
BITMAP *ed_mode1_off = NULL;
BITMAP *ed_mode2_off = NULL;
BITMAP *bt_reset_input = NULL;
BITMAP *bt_up_1 = NULL;
BITMAP *bt_up_2 = NULL;
BITMAP *bt_up_3 = NULL;
BITMAP *bt_down_1 = NULL;
BITMAP *bt_down_2 = NULL;
BITMAP *bt_down_3 = NULL;
BITMAP *bt_left_1 = NULL;
BITMAP *bt_left_2 = NULL;
BITMAP *bt_left_3 = NULL;
BITMAP *bt_right_1 = NULL;
BITMAP *bt_right_2 = NULL;
BITMAP *bt_right_3 = NULL;
BITMAP *bt_1 = NULL;
BITMAP *bt_2 = NULL;
BITMAP *bt_3 = NULL;
BITMAP *bt_ss_1 = NULL;
BITMAP *bt_ss_2 = NULL;
BITMAP *bt_ss_3 = NULL;
BITMAP *P1_Sombra = NULL;
BITMAP *P2_Sombra = NULL;
BITMAP *P1_Sombra_Aux = NULL;
BITMAP *P2_Sombra_Aux = NULL;
BITMAP *P1_energy_flip = NULL;
BITMAP *P1_energy_red_flip = NULL;
BITMAP *ED_Spr = NULL;
BITMAP *ED_Mini = NULL;
BITMAP *P1_Spr_Aux = NULL;
BITMAP *P2_Spr_Aux = NULL;
BITMAP *ED_Spr_Aux = NULL;
BITMAP *HitSparkspr = NULL;
BITMAP *HitSpark_Aux = NULL;
BITMAP *P1_Pallete = NULL;
BITMAP *P2_Pallete = NULL;

//musicas e efeitos
SAMPLE *intro = NULL;
SAMPLE *round1 = NULL;
SAMPLE *round2 = NULL;
SAMPLE *round3 = NULL;
SAMPLE *fight = NULL;
SAMPLE *ko = NULL;
SAMPLE *perfect = NULL;
SAMPLE *back = NULL;
SAMPLE *choice = NULL;
SAMPLE *confirm = NULL;
SAMPLE *cursor = NULL;
SAMPLE *attacklvl1 = NULL;
SAMPLE *attacklvl2 = NULL;
SAMPLE *attacklvl3 = NULL;
SAMPLE *hitlvl1 = NULL;
SAMPLE *hitlvl2 = NULL;
SAMPLE *hitlvl3 = NULL;
MIDI *bgm_apresentacao = NULL;
MIDI *bgm_continue = NULL;
MIDI *bgm_select_screen = NULL;
MIDI *bgm_versus_mode = NULL;

BITMAP *bg_test = NULL;
BITMAP *bg_hamoopi[9];

BITMAP *bufferx = NULL;
BITMAP *LayerHUD = NULL;
BITMAP *LayerHUDa = NULL;
BITMAP *LayerHUDb = NULL;

FONT *font_debug = NULL;
FONT *font_10 = NULL;
FONT *font_19 = NULL;
FONT *font_20 = NULL;
FONT *font_30 = NULL;

BITMAP *P1_1 = NULL;
BITMAP *P2_1 = NULL;
BITMAP *AnimTrans[30];
BITMAP *MINIspr[9];
BITMAP *MINIsprDisplay[9];
BITMAP *MINIsprDisplayArcadeMode[9];
BITMAP *P1BIGDisplay;
BITMAP *P2BIGDisplay;
BITMAP *P2BIGDisplayInv ;
BITMAP *AnimIntro[16];


int SelectBGID = 1;
int ModoFullscreen = 0;
char bg_choice[40] = "";

///////////////////////////////////////////////////////////////////////////////
// GAME LOOP FUNCTIONS -------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// Forward declarations for game loop and initialization functions
void dispose_game_elements();
void initialize_allegro_subsystems();
void load_fonts();
void load_configuration();
void create_render_buffers();
int load_system_bitmaps();
void load_animation_frames();
void load_audio_resources();
void initialize_character_and_stage_lists();


///////////////////////////////////////////////////////////////////////////////
// INICIALIZACAO ALLEGRO ------------------------------------------------[**02]
///////////////////////////////////////////////////////////////////////////////

/**
 * Initialize Allegro/SDL subsystems
 */
void initialize_allegro_subsystems() {
    set_uformat(U_UTF8); //permite usar acentuação no jogo (diacríticos)
    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    // Timer callback no longer needed - using SDL2's efficient frame timing
    set_window_title("HAMOOPI is Loading... Please wait :) ");
    set_close_button_callback(sair_allegro);
}

/**
 * Load all font resources
 */
void load_fonts() {
    font_debug = load_font("data/system/font_debug.pcx", NULL, NULL);
    font_10 = load_font("data/system/font_10.pcx", NULL, NULL);
    font_19 = load_font("data/system/font_19.pcx", NULL, NULL);
    font_20 = load_font("data/system/font_20.pcx", NULL, NULL);
    font_30 = load_font("data/system/font_30.pcx", NULL, NULL);
}

/**
 * Load configuration from SETUP.ini and initialize game settings
 */
void load_configuration() {
    //carrega os dados do setup.ini
    set_config_file("SETUP.ini");

    //opcao de desenhar sombras
    op_desenhar_sombras = get_config_int("CONFIG", "draw_shadows", 1);
    //opcao que ativa o zoom
    op_Zoom = get_config_int("CONFIG", "zoom", 1);
    //opcao que mostra os inputs ingame
    Draw_Input = get_config_int("CONFIG", "show_inputs", 0);
    //sound e soundfx volumes
    op_sound_volume = get_config_int("CONFIG", "sound_volume", 255);
    op_sfx_volume = get_config_int("CONFIG", "sfx_volume", 255);
    //resolucao de tela no modo windowed
    WindowResX = get_config_int("CONFIG", "window_res_x", 640);
    WindowResY = get_config_int("CONFIG", "window_res_y", 480);
    //define o ResWindowNumber
    if (WindowResX == 320 && WindowResY == 240) WindowResNumber = 1;
    if (WindowResX == 640 && WindowResY == 480) WindowResNumber = 2;
    if (WindowResX == 720 && WindowResY == 480) WindowResNumber = 3; //SD
    if (WindowResX == 800 && WindowResY == 600) WindowResNumber = 4;
    if (WindowResX == 960 && WindowResY == 640) WindowResNumber = 5;
    if (WindowResX == 960 && WindowResY == 720) WindowResNumber = 6;
    if (WindowResX == 1024 && WindowResY == 600) WindowResNumber = 7;
    if (WindowResX == 1280 && WindowResY == 720) WindowResNumber = 8; //HD
    //define se resolucao é fullscreen
    ModoFullscreen = get_config_int("CONFIG", "FullScreen", 0);
    //ajusta a tela com as novas configuracoes
    if (ModoFullscreen == 1) { set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, WindowResX, WindowResY, 0, 0); }
    if (ModoFullscreen == 0) { set_gfx_mode(GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0); }
    //opcao de framedata
    op_ShowFrameData = get_config_int("CONFIG", "frame_data", 0);

    //idioma do jogo
    const char *lang = get_config_string("CONFIG", "language", "BR");
    snprintf(IDIOMA, sizeof(IDIOMA), "%s", lang);

    //define centro do mapa
    MapCenterX = get_config_int("TEMPLATE", "MapCenterX", 320);
    MapCenterY = get_config_int("TEMPLATE", "MapCenterY", 118);
    difficulty = get_config_int("CONFIG", "difficulty", 3);

    //propriedades de round
    RoundTime = get_config_int("CONFIG", "time", 99);
    RoundTime = RoundTime * 60 + 59;
    RoundTotal = get_config_int("CONFIG", "rounds", 3);

    //inputs dos jogadores
    p1_up = get_config_int("P1_CONTROL", "P1_UP", 84);
    p1_down = get_config_int("P1_CONTROL", "P1_DOWN", 85);
    p1_left = get_config_int("P1_CONTROL", "P1_LEFT", 82);
    p1_right = get_config_int("P1_CONTROL", "P1_RIGHT", 83);
    p1_bt1 = get_config_int("P1_CONTROL", "P1_BT1", 1);
    p1_bt2 = get_config_int("P1_CONTROL", "P1_BT2", 19);
    p1_bt3 = get_config_int("P1_CONTROL", "P1_BT3", 4);
    p1_bt4 = get_config_int("P1_CONTROL", "P1_BT4", 26);
    p1_bt5 = get_config_int("P1_CONTROL", "P1_BT5", 24);
    p1_bt6 = get_config_int("P1_CONTROL", "P1_BT6", 3);
    p1_select = get_config_int("P1_CONTROL", "P1_SELECT", 75);
    p1_start = get_config_int("P1_CONTROL", "P1_START", 67);
    p2_up = get_config_int("P2_CONTROL", "P2_UP", 9);
    p2_down = get_config_int("P2_CONTROL", "P2_DOWN", 11);
    p2_left = get_config_int("P2_CONTROL", "P2_LEFT", 10);
    p2_right = get_config_int("P2_CONTROL", "P2_RIGHT", 12);
    p2_bt1 = get_config_int("P2_CONTROL", "P2_BT1", 6);
    p2_bt2 = get_config_int("P2_CONTROL", "P2_BT2", 7);
    p2_bt3 = get_config_int("P2_CONTROL", "P2_BT3", 8);
    p2_bt4 = get_config_int("P2_CONTROL", "P2_BT4", 22);
    p2_bt5 = get_config_int("P2_CONTROL", "P2_BT5", 2);
    p2_bt6 = get_config_int("P2_CONTROL", "P2_BT6", 14);
    p2_select = get_config_int("P2_CONTROL", "P2_SELECT", 18);
    p2_start = get_config_int("P2_CONTROL", "P2_START", 20);

    //propriedades da paleta de cor
    P[1].DefineCorDaPaleta = 0;
    P[2].DefineCorDaPaleta = 0;
}

/**
 * Create all render buffers and sprite atlases
 */
void create_render_buffers() {
    //Valores de Referencia:
    //Genesis [320x224]
    //Snes [256x224]
    //CapcomCPS1 [384x224]
    //NeoGeo [320x224]
    bg_test = create_bitmap(1280, 960); //tamanho max do cenario

    bufferx = create_bitmap(2560, 1920); //layer do cenario e personagens escalonados
    LayerHUD = create_bitmap(WindowResX, WindowResY); //layer das barras de energia
    LayerHUDa = create_bitmap(640, 480); //layer das barras de energia
    LayerHUDb = create_bitmap(WindowResX, WindowResY); //layer das barras de energia

    for (int ind = 0; ind <= 500; ind++) {
        P[1].SprAtlas[ind] = create_bitmap(480, 480); //reserva memoria para sprites dos players
        P[2].SprAtlas[ind] = create_bitmap(480, 480); //reserva memoria para sprites dos players
    }

    P[1].Spr = create_bitmap(480, 480);
    P[2].Spr = create_bitmap(480, 480);
    Fireball[1].Spr = create_bitmap(480, 480);
    Fireball[2].Spr = create_bitmap(480, 480);
    P1_Sombra = create_bitmap(480, 128);
    P2_Sombra = create_bitmap(480, 128);
    P1_Sombra_Aux = create_bitmap(480, 128);
    P2_Sombra_Aux = create_bitmap(480, 128);
    P1_energy_flip = create_bitmap(250, 40);
    P1_energy_red_flip = create_bitmap(250, 40);
    ED_Spr = create_bitmap(480, 480); //Editor
    ED_Mini = create_bitmap(32, 32);
    P1_Spr_Aux = create_bitmap(480, 480); //sprite auxiliar utilizado na funcao de animacao
    P2_Spr_Aux = create_bitmap(480, 480); //sprite auxiliar utilizado na funcao de animacao
    ED_Spr_Aux = create_bitmap(480, 480); //sprite auxiliar utilizado na funcao de animacao
    HitSparkspr = create_bitmap(260, 260);
    HitSpark_Aux = create_bitmap(130, 130);
    P1_Pallete = create_bitmap(32, 10);
    P2_Pallete = create_bitmap(32, 10);
    clear_to_color(HitSparkspr, makecol(255, 0, 255));
    clear_to_color(HitSpark_Aux, makecol(255, 0, 255));
    clear_to_color(P1_Pallete, makecol(255, 0, 255));
    clear_to_color(P2_Pallete, makecol(255, 0, 255));
}

/**
 * Load all system bitmaps (UI elements, sprites, etc.)
 * Returns 0 on success, -1 if critical resources are missing
 */
int load_system_bitmaps() {
    int HamoopiError = 0;

    GAME_logo = load_bitmap("data/system/GAME_logo.png", NULL);
    if (!GAME_logo) { HamoopiError = 1; }
    flag_BR = load_bitmap("data/system/flag_BR.png", NULL);
    if (!flag_BR) { HamoopiError = 1; }
    sel_mark_p1 = load_bitmap("data/system/sel_mark_p1.png", NULL);
    if (!sel_mark_p1) { HamoopiError = 1; }
    sel_mark_p2 = load_bitmap("data/system/sel_mark_p2.png", NULL);
    if (!sel_mark_p2) { HamoopiError = 1; }
    flag_US = load_bitmap("data/system/flag_US.png", NULL);
    if (!flag_US) { HamoopiError = 1; }
    SELECT_CHARS = load_bitmap("data/system/SELECT_CHARS.png", NULL);
    if (!SELECT_CHARS) { HamoopiError = 1; }
    VS_SCREEN = load_bitmap("data/system/VS_SCREEN.png", NULL);
    if (!VS_SCREEN) { HamoopiError = 1; }
    vs_icon = load_bitmap("data/system/vs_icon.png", NULL);
    if (!vs_icon) { HamoopiError = 1; }
    SELECT_BG = load_bitmap("data/system/SELECT_BG.png", NULL);
    if (!SELECT_BG) { HamoopiError = 1; }
    donation = load_bitmap("data/system/donation.png", NULL);
    if (!donation) { HamoopiError = 1; }
    spr_p1_cursor = load_bitmap("data/system/spr_p1_cursor.png", NULL);
    if (!spr_p1_cursor) { HamoopiError = 1; }
    spr_p2_cursor = load_bitmap("data/system/spr_p2_cursor.png", NULL);
    if (!spr_p2_cursor) { HamoopiError = 1; }
    spr_cursor_historia = load_bitmap("data/system/spr_cursor_historia.png", NULL);
    if (!spr_cursor_historia) { HamoopiError = 1; }
    spr_cursor_vazio = load_bitmap("data/system/spr_cursor_vazio.png", NULL);
    if (!spr_cursor_vazio) { HamoopiError = 1; }
    spr_ponteiro = load_bitmap("data/system/spr_ponteiro.png", NULL);
    if (!spr_ponteiro) { HamoopiError = 1; }
    spr_menu_icon = load_bitmap("data/system/spr_menu_icon.png", NULL);
    if (!spr_menu_icon) { HamoopiError = 1; }
    GAME_intro = load_bitmap("data/system/GAME_intro.png", NULL);
    if (!GAME_intro) { HamoopiError = 1; }
    GAME_options = load_bitmap("data/system/GAME_options.png", NULL);
    if (!GAME_options) { HamoopiError = 1; }
    char_generic = load_bitmap("data/system/char_generic.png", NULL);
    if (!char_generic) { HamoopiError = 1; }
    char_generic2x = load_bitmap("data/system/char_generic2x.png", NULL);
    if (!char_generic2x) { HamoopiError = 1; }
    spr_mold_results = load_bitmap("data/system/spr_mold_results.png", NULL);
    if (!spr_mold_results) { HamoopiError = 1; }
    spr_result_perfect = load_bitmap("data/system/spr_result_perfect.png", NULL);
    if (!spr_result_perfect) { HamoopiError = 1; }
    spr_result_win = load_bitmap("data/system/spr_result_win.png", NULL);
    if (!spr_result_win) { HamoopiError = 1; }
    spr_splash_round1 = load_bitmap("data/system/spr_splash_round1.png", NULL);
    if (!spr_splash_round1) { HamoopiError = 1; }
    spr_splash_round2 = load_bitmap("data/system/spr_splash_round2.png", NULL);
    if (!spr_splash_round2) { HamoopiError = 1; }
    spr_splash_round3 = load_bitmap("data/system/spr_splash_round3.png", NULL);
    if (!spr_splash_round3) { HamoopiError = 1; }
    spr_splash_round4 = load_bitmap("data/system/spr_splash_round4.png", NULL);
    if (!spr_splash_round4) { HamoopiError = 1; }
    spr_splash_round5 = load_bitmap("data/system/spr_splash_round5.png", NULL);
    if (!spr_splash_round5) { HamoopiError = 1; }
    spr_splash_fight = load_bitmap("data/system/spr_splash_fight.png", NULL);
    if (!spr_splash_fight) { HamoopiError = 1; }
    spr_splash_youwin = load_bitmap("data/system/spr_splash_youwin.png", NULL);
    if (!spr_splash_youwin) { HamoopiError = 1; }
    spr_splash_p1win = load_bitmap("data/system/spr_splash_p1win.png", NULL);
    if (!spr_splash_p1win) { HamoopiError = 1; }
    spr_splash_p2win = load_bitmap("data/system/spr_splash_p2win.png", NULL);
    if (!spr_splash_p2win) { HamoopiError = 1; }
    spr_splash_youlose = load_bitmap("data/system/spr_splash_youlose.png", NULL);
    if (!spr_splash_youlose) { HamoopiError = 1; }
    spr_splash_ko = load_bitmap("data/system/spr_splash_ko.png", NULL);
    if (!spr_splash_ko) { HamoopiError = 1; }
    spr_splash_perfect = load_bitmap("data/system/spr_splash_perfect.png", NULL);
    if (!spr_splash_perfect) { HamoopiError = 1; }
    spr_splash_draw = load_bitmap("data/system/spr_splash_draw.png", NULL);
    if (!spr_splash_draw) { HamoopiError = 1; }
    spr_splash_time_over = load_bitmap("data/system/spr_splash_time_over.png", NULL);
    if (!spr_splash_time_over) { HamoopiError = 1; }
    bt_joystick = load_bitmap("data/system/bt_joystick.png", NULL);
    if (!bt_joystick) { HamoopiError = 1; }
    ed_mode1_on = load_bitmap("data/system/ed_mode1_on.png", NULL);
    if (!ed_mode1_on) { HamoopiError = 1; }
    ed_mode2_on = load_bitmap("data/system/ed_mode2_on.png", NULL);
    if (!ed_mode2_on) { HamoopiError = 1; }
    ed_mode1_off = load_bitmap("data/system/ed_mode1_off.png", NULL);
    if (!ed_mode1_off) { HamoopiError = 1; }
    ed_mode2_off = load_bitmap("data/system/ed_mode2_off.png", NULL);
    if (!ed_mode2_off) { HamoopiError = 1; }
    bt_reset_input = load_bitmap("data/system/bt_reset_input.png", NULL);
    if (!bt_reset_input) { HamoopiError = 1; }
    bt_up_1 = load_bitmap("data/system/bt_up_1.png", NULL);
    if (!bt_up_1) { HamoopiError = 1; }
    bt_up_2 = load_bitmap("data/system/bt_up_2.png", NULL);
    if (!bt_up_2) { HamoopiError = 1; }
    bt_up_3 = load_bitmap("data/system/bt_up_3.png", NULL);
    if (!bt_up_3) { HamoopiError = 1; }
    bt_down_1 = load_bitmap("data/system/bt_down_1.png", NULL);
    if (!bt_down_1) { HamoopiError = 1; }
    bt_down_2 = load_bitmap("data/system/bt_down_2.png", NULL);
    if (!bt_down_2) { HamoopiError = 1; }
    bt_down_3 = load_bitmap("data/system/bt_down_3.png", NULL);
    if (!bt_down_3) { HamoopiError = 1; }
    bt_left_1 = load_bitmap("data/system/bt_left_1.png", NULL);
    if (!bt_left_1) { HamoopiError = 1; }
    bt_left_2 = load_bitmap("data/system/bt_left_2.png", NULL);
    if (!bt_left_2) { HamoopiError = 1; }
    bt_left_3 = load_bitmap("data/system/bt_left_3.png", NULL);
    if (!bt_left_3) { HamoopiError = 1; }
    bt_right_1 = load_bitmap("data/system/bt_right_1.png", NULL);
    if (!bt_right_1) { HamoopiError = 1; }
    bt_right_2 = load_bitmap("data/system/bt_right_2.png", NULL);
    if (!bt_right_2) { HamoopiError = 1; }
    bt_right_3 = load_bitmap("data/system/bt_right_3.png", NULL);
    if (!bt_right_3) { HamoopiError = 1; }
    bt_1 = load_bitmap("data/system/bt_1.png", NULL);
    if (!bt_1) { HamoopiError = 1; }
    bt_2 = load_bitmap("data/system/bt_2.png", NULL);
    if (!bt_2) { HamoopiError = 1; }
    bt_3 = load_bitmap("data/system/bt_3.png", NULL);
    if (!bt_3) { HamoopiError = 1; }
    bt_ss_1 = load_bitmap("data/system/bt_ss_1.png", NULL);
    if (!bt_ss_1) { HamoopiError = 1; }
    bt_ss_2 = load_bitmap("data/system/bt_ss_2.png", NULL);
    if (!bt_ss_2) { HamoopiError = 1; }
    bt_ss_3 = load_bitmap("data/system/bt_ss_3.png", NULL);
    if (!bt_ss_3) { HamoopiError = 1; }
    spr_input_0 = load_bitmap("data/system/spr_input_0.png", NULL);
    if (!spr_input_0) { HamoopiError = 1; }
    spr_input_1 = load_bitmap("data/system/spr_input_1.png", NULL);
    if (!spr_input_1) { HamoopiError = 1; }
    spr_input_2 = load_bitmap("data/system/spr_input_2.png", NULL);
    if (!spr_input_2) { HamoopiError = 1; }
    spr_input_3 = load_bitmap("data/system/spr_input_3.png", NULL);
    if (!spr_input_3) { HamoopiError = 1; }
    spr_input_4 = load_bitmap("data/system/spr_input_4.png", NULL);
    if (!spr_input_4) { HamoopiError = 1; }
    spr_input_5 = load_bitmap("data/system/spr_input_5.png", NULL);
    if (!spr_input_5) { HamoopiError = 1; }
    spr_input_6 = load_bitmap("data/system/spr_input_6.png", NULL);
    if (!spr_input_6) { HamoopiError = 1; }
    spr_input_7 = load_bitmap("data/system/spr_input_7.png", NULL);
    if (!spr_input_7) { HamoopiError = 1; }
    spr_input_8 = load_bitmap("data/system/spr_input_8.png", NULL);
    if (!spr_input_8) { HamoopiError = 1; }
    spr_input_9 = load_bitmap("data/system/spr_input_9.png", NULL);
    if (!spr_input_9) { HamoopiError = 1; }
    spr_input_10 = load_bitmap("data/system/spr_input_10.png", NULL);
    if (!spr_input_10) { HamoopiError = 1; }
    spr_input_11 = load_bitmap("data/system/spr_input_11.png", NULL);
    if (!spr_input_11) { HamoopiError = 1; }
    spr_input_12 = load_bitmap("data/system/spr_input_12.png", NULL);
    if (!spr_input_12) { HamoopiError = 1; }
    spr_input_13 = load_bitmap("data/system/spr_input_13.png", NULL);
    if (!spr_input_13) { HamoopiError = 1; }
    spr_input_14 = load_bitmap("data/system/spr_input_14.png", NULL);
    if (!spr_input_14) { HamoopiError = 1; }
    spr_input_15 = load_bitmap("data/system/spr_input_15.png", NULL);
    if (!spr_input_15) { HamoopiError = 1; }
    spr_input_16 = load_bitmap("data/system/spr_input_16.png", NULL);
    if (!spr_input_16) { HamoopiError = 1; }
    spr_input_17 = load_bitmap("data/system/spr_input_17.png", NULL);
    if (!spr_input_17) { HamoopiError = 1; }
    spr_bg_bar = load_bitmap("data/system/spr_bg_bar.png", NULL);
    if (!spr_bg_bar) { HamoopiError = 1; }
    spr_energy_bar = load_bitmap("data/system/spr_energy_bar.png", NULL);
    if (!spr_energy_bar) { HamoopiError = 1; }
    spr_energy_bar_full = load_bitmap("data/system/spr_energy_bar_full.png", NULL);
    if (!spr_energy_bar_full) { HamoopiError = 1; }
    spr_energy_red_bar = load_bitmap("data/system/spr_energy_red_bar.png", NULL);
    if (!spr_energy_red_bar) { HamoopiError = 1; }
    spr_energy_red_bar_full = load_bitmap("data/system/spr_energy_red_bar_full.png", NULL);
    if (!spr_energy_red_bar_full) { HamoopiError = 1; }
    spr_bg_bar_sp = load_bitmap("data/system/spr_bg_bar_sp.png", NULL);
    if (!spr_bg_bar_sp) { HamoopiError = 1; }
    spr_bg_energy_bar_sp = load_bitmap("data/system/spr_bg_energy_bar_sp.png", NULL);
    if (!spr_bg_energy_bar_sp) { HamoopiError = 1; }
    spr_num[0] = load_bitmap("data/system/spr_num_0.png", NULL);
    if (!spr_num[0]) { HamoopiError = 1; }
    spr_num[1] = load_bitmap("data/system/spr_num_1.png", NULL);
    if (!spr_num[1]) { HamoopiError = 1; }
    spr_num[2] = load_bitmap("data/system/spr_num_2.png", NULL);
    if (!spr_num[2]) { HamoopiError = 1; }
    spr_num[3] = load_bitmap("data/system/spr_num_3.png", NULL);
    if (!spr_num[3]) { HamoopiError = 1; }
    spr_num[4] = load_bitmap("data/system/spr_num_4.png", NULL);
    if (!spr_num[4]) { HamoopiError = 1; }
    spr_num[5] = load_bitmap("data/system/spr_num_5.png", NULL);
    if (!spr_num[5]) { HamoopiError = 1; }
    spr_num[6] = load_bitmap("data/system/spr_num_6.png", NULL);
    if (!spr_num[6]) { HamoopiError = 1; }
    spr_num[7] = load_bitmap("data/system/spr_num_7.png", NULL);
    if (!spr_num[7]) { HamoopiError = 1; }
    spr_num[8] = load_bitmap("data/system/spr_num_8.png", NULL);
    if (!spr_num[8]) { HamoopiError = 1; }
    spr_num[9] = load_bitmap("data/system/spr_num_9.png", NULL);
    if (!spr_num[9]) { HamoopiError = 1; }
    edit_bt_blue = load_bitmap("data/system/edit_bt_blue.png", NULL);
    if (!edit_bt_blue) { HamoopiError = 1; }
    edit_bt_red = load_bitmap("data/system/edit_bt_red.png", NULL);
    if (!edit_bt_red) { HamoopiError = 1; }
    edit_bt_null = load_bitmap("data/system/edit_bt_null.png", NULL);
    if (!edit_bt_null) { HamoopiError = 1; }
    edit_bt_null0 = load_bitmap("data/system/edit_bt_null0.png", NULL);
    if (!edit_bt_null0) { HamoopiError = 1; }
    edit_prevst = load_bitmap("data/system/edit_prevst.png", NULL);
    if (!edit_prevst) { HamoopiError = 1; }
    edit_nextst = load_bitmap("data/system/edit_nextst.png", NULL);
    if (!edit_nextst) { HamoopiError = 1; }
    edit_prevchar = load_bitmap("data/system/edit_prevchar.png", NULL);
    if (!edit_prevchar) { HamoopiError = 1; }
    edit_nextchar = load_bitmap("data/system/edit_nextchar.png", NULL);
    if (!edit_nextchar) { HamoopiError = 1; }
    edit_firstchar = load_bitmap("data/system/edit_firstchar.png", NULL);
    if (!edit_firstchar) { HamoopiError = 1; }
    edit_lastchar = load_bitmap("data/system/edit_lastchar.png", NULL);
    if (!edit_lastchar) { HamoopiError = 1; }
    spr_nao_implementado = load_bitmap("data/system/spr_nao_implementado.png", NULL);
    if (!spr_nao_implementado) { HamoopiError = 1; }
    edit_playback = load_bitmap("data/system/edit_playback.png", NULL);
    if (!edit_playback) { HamoopiError = 1; }
    edit_pause = load_bitmap("data/system/edit_pause.png", NULL);
    if (!edit_pause) { HamoopiError = 1; }
    edit_bt_FrameTime = load_bitmap("data/system/edit_bt_FrameTime.png", NULL);
    if (!edit_bt_FrameTime) { HamoopiError = 1; }
    edit_bt_plus = load_bitmap("data/system/edit_bt_plus.png", NULL);
    if (!edit_bt_plus) { HamoopiError = 1; }
    edit_bt_minus = load_bitmap("data/system/edit_bt_minus.png", NULL);
    if (!edit_bt_minus) { HamoopiError = 1; }
    mouse = load_bitmap("data/system/mouse.png", NULL);
    if (!mouse) { HamoopiError = 1; }
    mouse2 = load_bitmap("data/system/mouse2.png", NULL);
    if (!mouse2) { HamoopiError = 1; }
    save_file = load_bitmap("data/system/save_file.png", NULL);
    if (!save_file) { HamoopiError = 1; }
    bt_pivot = load_bitmap("data/system/bt_pivot.png", NULL);
    if (!bt_pivot) { HamoopiError = 1; }
    spr000_00 = load_bitmap("data/system/000_00.png", NULL);
    if (!spr000_00) { HamoopiError = 1; }
    spr000_01 = load_bitmap("data/system/000_01.png", NULL);
    if (!spr000_01) { HamoopiError = 1; }
    spr991_00 = load_bitmap("data/system/991_00.png", NULL);
    if (!spr991_00) { HamoopiError = 1; }
    spr991_01 = load_bitmap("data/system/991_01.png", NULL);
    if (!spr991_01) { HamoopiError = 1; }
    spr991_02 = load_bitmap("data/system/991_02.png", NULL);
    if (!spr991_02) { HamoopiError = 1; }
    spr991_03 = load_bitmap("data/system/991_03.png", NULL);
    if (!spr991_03) { HamoopiError = 1; }
    spr991_04 = load_bitmap("data/system/991_04.png", NULL);
    if (!spr991_04) { HamoopiError = 1; }
    spr991_05 = load_bitmap("data/system/991_05.png", NULL);
    if (!spr991_05) { HamoopiError = 1; }
    spr992_00 = load_bitmap("data/system/992_00.png", NULL);
    if (!spr992_00) { HamoopiError = 1; }
    spr992_01 = load_bitmap("data/system/992_01.png", NULL);
    if (!spr992_01) { HamoopiError = 1; }
    spr992_02 = load_bitmap("data/system/992_02.png", NULL);
    if (!spr992_02) { HamoopiError = 1; }
    spr992_03 = load_bitmap("data/system/992_03.png", NULL);
    if (!spr992_03) { HamoopiError = 1; }
    spr992_04 = load_bitmap("data/system/992_04.png", NULL);
    if (!spr992_04) { HamoopiError = 1; }
    spr992_05 = load_bitmap("data/system/992_05.png", NULL);
    if (!spr992_05) { HamoopiError = 1; }
    spr993_00 = load_bitmap("data/system/993_00.png", NULL);
    if (!spr993_00) { HamoopiError = 1; }
    spr993_01 = load_bitmap("data/system/993_01.png", NULL);
    if (!spr993_01) { HamoopiError = 1; }
    spr993_02 = load_bitmap("data/system/993_02.png", NULL);
    if (!spr993_02) { HamoopiError = 1; }
    spr993_03 = load_bitmap("data/system/993_03.png", NULL);
    if (!spr993_03) { HamoopiError = 1; }
    spr993_04 = load_bitmap("data/system/993_04.png", NULL);
    if (!spr993_04) { HamoopiError = 1; }
    spr993_05 = load_bitmap("data/system/993_05.png", NULL);
    if (!spr993_05) { HamoopiError = 1; }
    spr994_00 = load_bitmap("data/system/994_00.png", NULL);
    if (!spr994_00) { HamoopiError = 1; }
    spr994_01 = load_bitmap("data/system/994_01.png", NULL);
    if (!spr994_01) { HamoopiError = 1; }
    spr994_02 = load_bitmap("data/system/994_02.png", NULL);
    if (!spr994_02) { HamoopiError = 1; }
    spr994_03 = load_bitmap("data/system/994_03.png", NULL);
    if (!spr994_03) { HamoopiError = 1; }
    spr994_04 = load_bitmap("data/system/994_04.png", NULL);
    if (!spr994_04) { HamoopiError = 1; }
    spr994_05 = load_bitmap("data/system/994_05.png", NULL);
    if (!spr994_05) { HamoopiError = 1; }
    //defesa - nao implementada ainda :)
    //BITMAP *spr995_00            = load_bitmap("data/system/995_00.png", NULL);               if (!spr995_00)            { HamoopiError=1; }
    //BITMAP *spr995_01            = load_bitmap("data/system/995_01.png", NULL);               if (!spr995_01)            { HamoopiError=1; }
    //BITMAP *spr995_02            = load_bitmap("data/system/995_02.png", NULL);               if (!spr995_02)            { HamoopiError=1; }
    //BITMAP *spr995_03            = load_bitmap("data/system/995_03.png", NULL);               if (!spr995_03)            { HamoopiError=1; }
    //BITMAP *spr995_04            = load_bitmap("data/system/995_04.png", NULL);               if (!spr995_04)            { HamoopiError=1; }
    //BITMAP *spr995_05            = load_bitmap("data/system/995_05.png", NULL);               if (!spr995_05)            { HamoopiError=1; }

    MINIspr[0] = load_bitmap("data/system/000_01.png", NULL);
    if (!MINIspr[0]) { HamoopiError = 1; }

    // Display error message if resources failed to load
    if (HamoopiError == 1) {
        if (strcmp(IDIOMA, "BR") == 0) {
            allegro_message("ARQUIVOS OU DIRETORIOS NAO ENCONTRADOS.");
        }
        if (strcmp(IDIOMA, "US") == 0) {
            allegro_message("FILES OR DIRECTORIES NOT FOUND.");
        }
        return -1;
    }

    return 0;
}

/**
 * Load animation frames for transitions and intro
 */
void load_animation_frames() {
    AnimTrans[0] = load_bitmap("data/system/AnimTrans00.png", NULL);
    if (!AnimTrans[0]) { CtrlAnimTrans[0] = 0; } else { CtrlAnimTrans[0] = 1; }
    AnimTrans[1] = load_bitmap("data/system/AnimTrans01.png", NULL);
    if (!AnimTrans[1]) { CtrlAnimTrans[1] = 0; } else { CtrlAnimTrans[1] = 1; }
    AnimTrans[2] = load_bitmap("data/system/AnimTrans02.png", NULL);
    if (!AnimTrans[2]) { CtrlAnimTrans[2] = 0; } else { CtrlAnimTrans[2] = 1; }
    AnimTrans[3] = load_bitmap("data/system/AnimTrans03.png", NULL);
    if (!AnimTrans[3]) { CtrlAnimTrans[3] = 0; } else { CtrlAnimTrans[3] = 1; }
    AnimTrans[4] = load_bitmap("data/system/AnimTrans04.png", NULL);
    if (!AnimTrans[4]) { CtrlAnimTrans[4] = 0; } else { CtrlAnimTrans[4] = 1; }
    AnimTrans[5] = load_bitmap("data/system/AnimTrans05.png", NULL);
    if (!AnimTrans[5]) { CtrlAnimTrans[5] = 0; } else { CtrlAnimTrans[5] = 1; }
    AnimTrans[6] = load_bitmap("data/system/AnimTrans06.png", NULL);
    if (!AnimTrans[6]) { CtrlAnimTrans[6] = 0; } else { CtrlAnimTrans[6] = 1; }
    AnimTrans[7] = load_bitmap("data/system/AnimTrans07.png", NULL);
    if (!AnimTrans[7]) { CtrlAnimTrans[7] = 0; } else { CtrlAnimTrans[7] = 1; }
    AnimTrans[8] = load_bitmap("data/system/AnimTrans08.png", NULL);
    if (!AnimTrans[8]) { CtrlAnimTrans[8] = 0; } else { CtrlAnimTrans[8] = 1; }
    AnimTrans[9] = load_bitmap("data/system/AnimTrans09.png", NULL);
    if (!AnimTrans[9]) { CtrlAnimTrans[9] = 0; } else { CtrlAnimTrans[9] = 1; }
    AnimTrans[10] = load_bitmap("data/system/AnimTrans10.png", NULL);
    if (!AnimTrans[10]) { CtrlAnimTrans[10] = 0; } else { CtrlAnimTrans[10] = 1; }
    AnimTrans[11] = load_bitmap("data/system/AnimTrans11.png", NULL);
    if (!AnimTrans[11]) { CtrlAnimTrans[11] = 0; } else { CtrlAnimTrans[11] = 1; }
    AnimTrans[12] = load_bitmap("data/system/AnimTrans12.png", NULL);
    if (!AnimTrans[12]) { CtrlAnimTrans[12] = 0; } else { CtrlAnimTrans[12] = 1; }
    AnimTrans[13] = load_bitmap("data/system/AnimTrans13.png", NULL);
    if (!AnimTrans[13]) { CtrlAnimTrans[13] = 0; } else { CtrlAnimTrans[13] = 1; }
    AnimTrans[14] = load_bitmap("data/system/AnimTrans14.png", NULL);
    if (!AnimTrans[14]) { CtrlAnimTrans[14] = 0; } else { CtrlAnimTrans[14] = 1; }
    AnimTrans[15] = load_bitmap("data/system/AnimTrans15.png", NULL);
    if (!AnimTrans[15]) { CtrlAnimTrans[15] = 0; } else { CtrlAnimTrans[15] = 1; }
    AnimTrans[16] = load_bitmap("data/system/AnimTrans16.png", NULL);
    if (!AnimTrans[16]) { CtrlAnimTrans[16] = 0; } else { CtrlAnimTrans[16] = 1; }
    AnimTrans[17] = load_bitmap("data/system/AnimTrans17.png", NULL);
    if (!AnimTrans[17]) { CtrlAnimTrans[17] = 0; } else { CtrlAnimTrans[17] = 1; }
    AnimTrans[18] = load_bitmap("data/system/AnimTrans18.png", NULL);
    if (!AnimTrans[18]) { CtrlAnimTrans[18] = 0; } else { CtrlAnimTrans[18] = 1; }
    AnimTrans[19] = load_bitmap("data/system/AnimTrans19.png", NULL);
    if (!AnimTrans[19]) { CtrlAnimTrans[19] = 0; } else { CtrlAnimTrans[19] = 1; }
    AnimTrans[20] = load_bitmap("data/system/AnimTrans20.png", NULL);
    if (!AnimTrans[20]) { CtrlAnimTrans[20] = 0; } else { CtrlAnimTrans[20] = 1; }
    AnimTrans[21] = load_bitmap("data/system/AnimTrans21.png", NULL);
    if (!AnimTrans[21]) { CtrlAnimTrans[21] = 0; } else { CtrlAnimTrans[21] = 1; }
    AnimTrans[22] = load_bitmap("data/system/AnimTrans22.png", NULL);
    if (!AnimTrans[22]) { CtrlAnimTrans[22] = 0; } else { CtrlAnimTrans[22] = 1; }
    AnimTrans[23] = load_bitmap("data/system/AnimTrans23.png", NULL);
    if (!AnimTrans[23]) { CtrlAnimTrans[23] = 0; } else { CtrlAnimTrans[23] = 1; }
    AnimTrans[24] = load_bitmap("data/system/AnimTrans24.png", NULL);
    if (!AnimTrans[24]) { CtrlAnimTrans[24] = 0; } else { CtrlAnimTrans[24] = 1; }
    AnimTrans[25] = load_bitmap("data/system/AnimTrans25.png", NULL);
    if (!AnimTrans[25]) { CtrlAnimTrans[25] = 0; } else { CtrlAnimTrans[25] = 1; }
    AnimTrans[26] = load_bitmap("data/system/AnimTrans26.png", NULL);
    if (!AnimTrans[26]) { CtrlAnimTrans[26] = 0; } else { CtrlAnimTrans[26] = 1; }
    AnimTrans[27] = load_bitmap("data/system/AnimTrans27.png", NULL);
    if (!AnimTrans[27]) { CtrlAnimTrans[27] = 0; } else { CtrlAnimTrans[27] = 1; }
    AnimTrans[28] = load_bitmap("data/system/AnimTrans28.png", NULL);
    if (!AnimTrans[28]) { CtrlAnimTrans[28] = 0; } else { CtrlAnimTrans[28] = 1; }
    AnimTrans[29] = load_bitmap("data/system/AnimTrans29.png", NULL);
    if (!AnimTrans[29]) { CtrlAnimTrans[29] = 0; } else { CtrlAnimTrans[29] = 1; }

    AnimIntro[0] = load_bitmap("data/system/AnimIntro00.png", NULL);
    if (!AnimIntro[0]) { CtrlAnimIntro[0] = 0; } else { CtrlAnimIntro[0] = 1; }
    AnimIntro[1] = load_bitmap("data/system/AnimIntro01.png", NULL);
    if (!AnimIntro[1]) { CtrlAnimIntro[1] = 0; } else { CtrlAnimIntro[1] = 1; }
    AnimIntro[2] = load_bitmap("data/system/AnimIntro02.png", NULL);
    if (!AnimIntro[2]) { CtrlAnimIntro[2] = 0; } else { CtrlAnimIntro[2] = 1; }
    AnimIntro[3] = load_bitmap("data/system/AnimIntro03.png", NULL);
    if (!AnimIntro[3]) { CtrlAnimIntro[3] = 0; } else { CtrlAnimIntro[3] = 1; }
    AnimIntro[4] = load_bitmap("data/system/AnimIntro04.png", NULL);
    if (!AnimIntro[4]) { CtrlAnimIntro[4] = 0; } else { CtrlAnimIntro[4] = 1; }
    AnimIntro[5] = load_bitmap("data/system/AnimIntro05.png", NULL);
    if (!AnimIntro[5]) { CtrlAnimIntro[5] = 0; } else { CtrlAnimIntro[5] = 1; }
    AnimIntro[6] = load_bitmap("data/system/AnimIntro06.png", NULL);
    if (!AnimIntro[6]) { CtrlAnimIntro[6] = 0; } else { CtrlAnimIntro[6] = 1; }
    AnimIntro[7] = load_bitmap("data/system/AnimIntro07.png", NULL);
    if (!AnimIntro[7]) { CtrlAnimIntro[7] = 0; } else { CtrlAnimIntro[7] = 1; }
    AnimIntro[8] = load_bitmap("data/system/AnimIntro08.png", NULL);
    if (!AnimIntro[8]) { CtrlAnimIntro[8] = 0; } else { CtrlAnimIntro[8] = 1; }
    AnimIntro[9] = load_bitmap("data/system/AnimIntro09.png", NULL);
    if (!AnimIntro[9]) { CtrlAnimIntro[9] = 0; } else { CtrlAnimIntro[9] = 1; }
    AnimIntro[10] = load_bitmap("data/system/AnimIntro10.png", NULL);
    if (!AnimIntro[10]) { CtrlAnimIntro[10] = 0; } else { CtrlAnimIntro[10] = 1; }
    AnimIntro[11] = load_bitmap("data/system/AnimIntro11.png", NULL);
    if (!AnimIntro[11]) { CtrlAnimIntro[11] = 0; } else { CtrlAnimIntro[11] = 1; }
    AnimIntro[12] = load_bitmap("data/system/AnimIntro12.png", NULL);
    if (!AnimIntro[12]) { CtrlAnimIntro[12] = 0; } else { CtrlAnimIntro[12] = 1; }
    AnimIntro[13] = load_bitmap("data/system/AnimIntro13.png", NULL);
    if (!AnimIntro[13]) { CtrlAnimIntro[13] = 0; } else { CtrlAnimIntro[13] = 1; }
    AnimIntro[14] = load_bitmap("data/system/AnimIntro14.png", NULL);
    if (!AnimIntro[14]) { CtrlAnimIntro[14] = 0; } else { CtrlAnimIntro[14] = 1; }
    AnimIntro[15] = load_bitmap("data/system/AnimIntro15.png", NULL);
    if (!AnimIntro[15]) { CtrlAnimIntro[15] = 0; } else { CtrlAnimIntro[15] = 1; }
}

/**
 * Load all audio resources (sounds and music)
 */
void load_audio_resources() {
    intro = load_sample("data/sounds/intro.wav");
    round1 = load_sample("data/sounds/round1.wav");
    round2 = load_sample("data/sounds/round2.wav");
    round3 = load_sample("data/sounds/round3.wav");
    fight = load_sample("data/sounds/fight.wav");
    ko = load_sample("data/sounds/ko.wav");
    perfect = load_sample("data/sounds/perfect.wav");
    back = load_sample("data/sounds/back.wav");
    choice = load_sample("data/sounds/choice.wav");
    confirm = load_sample("data/sounds/confirm.wav");
    cursor = load_sample("data/sounds/cursor.wav");
    attacklvl1 = load_sample("data/sounds/attacklvl1.wav");
    attacklvl2 = load_sample("data/sounds/attacklvl2.wav");
    attacklvl3 = load_sample("data/sounds/attacklvl3.wav");
    hitlvl1 = load_sample("data/sounds/hitlvl1.wav");
    hitlvl2 = load_sample("data/sounds/hitlvl2.wav");
    hitlvl3 = load_sample("data/sounds/hitlvl3.wav");
    bgm_apresentacao = load_midi("data/sounds/bgm_apresentacao.mid");
    bgm_continue = load_midi("data/sounds/bgm_continue.mid");
    bgm_select_screen = load_midi("data/sounds/bgm_select_screen.mid");
    bgm_versus_mode = load_midi("data/sounds/bgm_versus_mode.mid");
}

/**
 * Initialize character and stage lists from configuration
 */
void initialize_character_and_stage_lists() {
    // Create miniature display bitmaps
    MINIspr[1] = create_bitmap(32, 32);
    MINIspr[2] = create_bitmap(32, 32);
    MINIspr[3] = create_bitmap(32, 32);
    MINIspr[4] = create_bitmap(32, 32);
    MINIspr[5] = create_bitmap(32, 32);
    MINIspr[6] = create_bitmap(32, 32);
    MINIspr[7] = create_bitmap(32, 32);
    MINIspr[8] = create_bitmap(32, 32);

    MINIsprDisplay[0] = create_bitmap(64, 64);
    MINIsprDisplay[1] = create_bitmap(64, 64);
    MINIsprDisplay[2] = create_bitmap(64, 64);
    MINIsprDisplay[3] = create_bitmap(64, 64);
    MINIsprDisplay[4] = create_bitmap(64, 64);
    MINIsprDisplay[5] = create_bitmap(64, 64);
    MINIsprDisplay[6] = create_bitmap(64, 64);
    MINIsprDisplay[7] = create_bitmap(64, 64);
    MINIsprDisplay[8] = create_bitmap(64, 64);

    MINIsprDisplayArcadeMode[0] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[1] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[2] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[3] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[4] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[5] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[6] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[7] = create_bitmap(64, 64);
    MINIsprDisplayArcadeMode[8] = create_bitmap(64, 64);

    P1BIGDisplay = create_bitmap(128, 128);
    P2BIGDisplay = create_bitmap(128, 128);
    P2BIGDisplayInv = create_bitmap(128, 128);

    //carrega a lista de personagens instalados
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        char strtemp[9] = "";
        sprintf(strtemp, "char%i", ind);
        strcpy(Lista_de_Personagens_Instalados[ind], (char *)get_config_string("CHARS", strtemp, ""));
    }

    //atualiza a qtde de personagens instalados
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        if (strcmp(Lista_de_Personagens_Instalados[ind], "") != 0) { Qtde_Personagens_Instalados++; }
    }
    //faz o sorteio de personagens do modo historia <nao utilizado no momento, aguardando futura implementacao>
    // Ao sortear, levar em consideracao o total de personagens instalados, abastecendo a lista arcade apropriadamente
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        strcpy(Lista_de_Personagens_ArcadeMode[ind], Lista_de_Personagens_Instalados[ind]);
    }

    //carrega a lista de Cenarios instalados
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        char strtemp[9] = "";
        sprintf(strtemp, "bg%i", ind);
        strcpy(Lista_de_Cenarios_Instalados[ind], (char *)get_config_string("BACKGROUNDS", strtemp, ""));
    }
    //atualiza a qtde de Cenarios instalados
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        if (strcmp(Lista_de_Cenarios_Instalados[ind], "") != 0) { Qtde_Cenarios_Instalados++; }
    }
    //faz o sorteio de Cenarios do modo historia <nao utilizado no momento, aguardando futura implementacao>
    // Ao sortear, levar em consideracao o total de Cenarios instalados, abastecendo a lista arcade apropriadamente
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        strcpy(Lista_de_Cenarios_ArcadeMode[ind], Lista_de_Cenarios_Instalados[ind]);
    }

    //Carrega Miniaturas - SELECT CHARS
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        if (Qtde_Personagens_Instalados >= ind) {
            char MINIstring[99] = "";
            sprintf(MINIstring, "data/chars/%s/000_01.png", Lista_de_Personagens_Instalados[ind]);
            MINIspr[ind] = platform_load_bitmap(MINIstring, NULL);
            if (!MINIspr[ind]) { MINIspr[ind] = load_bitmap("data/system/000_01.png", NULL); }
            stretch_blit(MINIspr[ind], MINIsprDisplay[ind], 0, 0, MINIspr[ind]->w, MINIspr[ind]->h, 0, 0,
                         MINIsprDisplay[1]->w, MINIsprDisplay[1]->h);
            destroy_bitmap(MINIspr[ind]);
        }
    }

    //miniaturas do arcade mode
    for (int ind = 1; ind <= 8; ind++) {
        if (Qtde_Personagens_Instalados >= ind) {
            char MINIstring[99] = "";
            sprintf(MINIstring, "data/chars/%s/000_01.png", Lista_de_Personagens_ArcadeMode[ind]);
            MINIspr[ind] = platform_load_bitmap(MINIstring, NULL);
            if (!MINIspr[ind]) { MINIspr[ind] = load_bitmap("data/system/000_01.png", NULL); }
            stretch_blit(MINIspr[ind], MINIsprDisplayArcadeMode[ind], 0, 0, MINIspr[ind]->w, MINIspr[ind]->h, 0, 0,
                         MINIsprDisplay[1]->w, MINIsprDisplay[1]->h);
            destroy_bitmap(MINIspr[ind]);
        }
    }

    //P1 miniatura da foto ingame
    strcpy(P[1].Name, (char *)get_config_string("CHARS", "char1", ""));
    char P1_1s[40] = "";
    sprintf(P1_1s, "data/chars/%s/000_01.png", P[1].Name);
    P1_1 = load_bitmap(P1_1s, NULL);
    if (!P1_1) { P1_1 = load_bitmap("data/system/000_01.png", NULL); }
    //P2 miniatura da foto ingame
    strcpy(P[2].Name, (char *)get_config_string("CHARS", "char2", ""));
    char P2_1s[40] = "";
    sprintf(P2_1s, "data/chars/%s/000_01.png", P[2].Name);
    P2_1 = load_bitmap(P2_1s, NULL);
    if (!P2_1) { P2_1 = load_bitmap("data/system/000_01.png", NULL); }
}


int main() {
    initialize_allegro_subsystems();
    load_fonts();
    load_configuration();

    //carrega a lista de Cenarios instalados
    for (int ind = 1; ind <= MAX_CHARS; ind++) {
        char strtemp[9] = "";
        sprintf(strtemp, "bg%i", ind);
        strcpy(Lista_de_Cenarios_Instalados[ind], (char *)get_config_string("BACKGROUNDS", strtemp, ""));
    }
    //abastece Atlas de cenario
    for (int ind = 1; ind <= 8; ind++) {
        sprintf(bg_choice, "data/backgrounds/%s/000_00.png", Lista_de_Cenarios_Instalados[ind]);
        bg_hamoopi[ind] = load_bitmap(bg_choice, NULL);
    }

    create_render_buffers();

    if (load_system_bitmaps() != 0) {
        return 1; // Exit if critical resources failed to load
    }

    load_animation_frames();
    initialize_character_and_stage_lists();
    load_audio_resources();

    set_window_title(versao);

    /////////////////////////////////////////////////////////////////////////////
    // LOOP DE JOGO -------------------------------------------------------[**03]
    /////////////////////////////////////////////////////////////////////////////

    // Initialize frame timing for 60 FPS
    frame_start_time = SDL_GetTicks64();

    while (sair == 0) {
        // Start of frame timing
        Uint64 frame_begin = SDL_GetTicks64();
        
        check_keys_P1();
        check_keys_P2(); //verifica teclas key_press, key_hold, key_released
        
        // Update frame-based timers using frame count instead of timer callback
        frame_count++;
        Segundos = ((frame_count / 60) - Minutos * 60) - Horas * 3600;
        if (Segundos >= 60) {
            Minutos++;
            Segundos = 0;
            if (Minutos >= 60) {
                Horas++;
                Minutos = 0;
            }
        }
        if (timermenus < 15) { timermenus++; } //utilizado para melhor navegacao entre os menus
        MeioDaTela = (P[1].x + P[2].x) / 2;
        if (P[1].State == 300 || P[1].State == 310 || P[1].State == 320) { P[1].TempoPulo = P[1].TempoPulo + 1; }
        if (P[2].State == 300 || P[2].State == 310 || P[2].State == 320) { P[2].TempoPulo = P[2].TempoPulo + 1; }
        P[1].ticks_4slot = P[1].ticks_4slot + 1;
        P[2].ticks_4slot = P[2].ticks_4slot + 1;
        if (ModoFullscreen == 0 && key[KEY_ALT] && key[KEY_ENTER]) {
            ModoFullscreen = 1;
            set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);
        }
        if (ModoFullscreen == 1 && key[KEY_ALT] && key[KEY_ENTER]) {
            ModoFullscreen = 0;
            set_gfx_mode(GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0);
        }
        set_volume(op_sfx_volume, op_sound_volume); //volume //set_volume(int digi_volume, int midi_volume);

        if (IntroMode == 1) {
            GameLoop_IntroMode();
        }

        if (DonationScreen == 1) {
            GameLoop_DonationScreen();
        }

        if (ApresentacaoMode == 1) {
            GameLoop_ApresentacaoMode();
        }

        if (OptionsMode == 1) {
            GameLoop_OptionsMode();
        }

        if (SelectCharMode == 1) {
            GameLoop_SelectCharMode();
        }

        if (ModoMapa == 1) {
            GameLoop_ModoMapa();
        }

        if (TelaDeVersus == 1) {
            GameLoop_TelaDeVersus();
        }

        if (GamePlayMode == 1) {
            GameLoop_GamePlayMode();
        }

        if (EditMode == 1) {
            GameLoop_EditMode();
        } //fim if (EditMode==1)

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // FINALIZACOES ------------------------------------------------------------------------------------------------------------------------------ [**10] //
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //efeito de Fade
        if (FadeIN == 1) {
            FadeOUT = 0;
            FadeCtr += FadeVelocidade;
            if (FadeCtr > 255) { FadeCtr = 255; }
        }
        if (FadeOUT == 1) {
            FadeIN = 0;
            FadeCtr -= FadeVelocidade;
            if (FadeCtr < 0) { FadeCtr = 0; }
        }
        if (FadeCtr != 0) {
            set_trans_blender(0, 0, 0, FadeCtr);
            drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
            int fx_w;
            int fx_h;
            fx_w = WindowResX;
            fx_h = WindowResY;
            if (fx_w == 320) {
                fx_w = 640;
                fx_h = 480;
            }
            rectfill(bufferx, 0, 0, fx_w, fx_h, makecol(0, 0, 0));
            if (CtrlAnimTrans[16] == 0) { rectfill(LayerHUDa, 0, 0, fx_w, fx_h, makecol(0, 0, 0)); }
            drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
        }

        //efeito animação de Introducao (AnimIntro)
        if (ApresentacaoMode == 1) {
            if (AnimIntroTimer != -1) {
                for (int ind = 0; ind < 16; ind++) {
                    if (ind == floor(AnimIntroTimer)) {
                        if (CtrlAnimIntro[ind] == 1) { draw_sprite(bufferx, AnimIntro[ind], 0, 120); }
                    }
                }
            }
            if (AnimIntroTimer >= 0) {
                AnimIntroTimer += 0.35;
                if (AnimIntroTimer >= 16) {
                    AnimIntroTimer = 0;
                }
            }
        }

        //Efeito Animacao de Transicao (AnimTrans)
        if (AnimTransTimer != -1) {
            for (int ind = 0; ind <= 14; ind++) {
                if (ind == floor(AnimTransTimer)) {
                    if (CtrlAnimTrans[ind] == 1) {
                        draw_sprite(bufferx, AnimTrans[ind], 0, 0); //bufferx, antes de entrar na tela de gameplay
                    }
                }
            }
        }
        if (AnimTransTimer != -1) {
            for (int ind = 14; ind <= 29; ind++) {
                if (ind == floor(AnimTransTimer)) {
                    if (CtrlAnimTrans[ind] == 1) {
                        draw_sprite(LayerHUDa, AnimTrans[ind], 0, 0); //LayerHUD, ja dentro de gameplay
                    }
                }
            }
        }
        if (AnimTransTimer >= 0) {
            AnimTransTimer += 0.25;
            if (AnimTransTimer >= 30) {
                AnimTransTimer = -1;
            }
        }

        //////////////////////////////
        //BLIT de BUFFERX em SCREEN!//
        //////////////////////////////
        if (GamePlayMode == 0) { stretch_blit(bufferx, screen, 0, 0, 640, 480, 0, 0, screen->w, screen->h); }
        if (GamePlayMode == 1) {
            masked_stretch_blit(LayerHUDa, LayerHUDb, 0, 0, LayerHUDa->w, LayerHUDa->h, 0, 0, LayerHUDb->w,
                                LayerHUDb->h);
            stretch_blit(LayerHUDb, screen, 0, 0, LayerHUDb->w, LayerHUDb->h, 0, 0, screen->w, screen->h);
            //resolucao adaptativa
            //draw_sprite(screen, LayerHUDb, 0, 0); //PS: desativado, resolucao fixa em 640x480, stretch_blit funciona melhor
        }
        //show_mouse(screen);

        // Present the rendered frame to the screen
        platform_present_screen();

        // Frame timing - maintain target FPS based on Ctrl_FPS
        Uint64 frame_end = SDL_GetTicks64();
        Uint64 frame_time = frame_end - frame_begin;
        Uint64 target_frame_time = (Ctrl_FPS > 0) ? (1000 / Ctrl_FPS) : 1000;
        if (frame_time < target_frame_time) {
            SDL_Delay(target_frame_time - frame_time);
        }

        clear(LayerHUD);
        clear_to_color(LayerHUD, makecol(255, 0, 255));
        clear_to_color(LayerHUDa, makecol(255, 0, 255));
        clear_to_color(LayerHUDb, makecol(255, 0, 255));
        clear(bufferx);
    } //(while sair==0)

    //limpa a memoria, destroi imagens e audios utilizados no jogo
    dispose_game_elements();
    return 0;
} //main()

void dispose_game_elements() {
    destroy_bitmap(donation);
    for (int ind = 0; ind <= 500; ind++) {
        destroy_bitmap(P[1].SprAtlas[ind]);
        destroy_bitmap(P[2].SprAtlas[ind]);
    }
    for (int ind = 0; ind < 10; ind++) { destroy_bitmap(spr_num[ind]); }
    for (int ind = 0; ind < 30; ind++) { destroy_bitmap(AnimTrans[ind]); }
    destroy_bitmap(LayerHUD);
    destroy_bitmap(LayerHUDa);
    destroy_bitmap(LayerHUDb);
    destroy_bitmap(ed_mode1_on);
    destroy_bitmap(ed_mode2_on);
    destroy_bitmap(ed_mode1_off);
    destroy_bitmap(ed_mode2_off);
    destroy_bitmap(edit_prevchar);
    destroy_bitmap(edit_nextchar);
    destroy_bitmap(edit_firstchar);
    destroy_bitmap(edit_lastchar);
    destroy_bitmap(spr_nao_implementado);
    destroy_bitmap(bt_reset_input);
    destroy_bitmap(mouse);
    destroy_bitmap(mouse2);
    destroy_bitmap(spr_input_0);
    destroy_bitmap(spr_input_1);
    destroy_bitmap(spr_input_2);
    destroy_bitmap(spr_input_3);
    destroy_bitmap(spr_input_4);
    destroy_bitmap(spr_input_5);
    destroy_bitmap(spr_input_6);
    destroy_bitmap(spr_input_7);
    destroy_bitmap(spr_input_8);
    destroy_bitmap(spr_input_9);
    destroy_bitmap(spr_input_10);
    destroy_bitmap(spr_input_11);
    destroy_bitmap(spr_input_12);
    destroy_bitmap(spr_input_13);
    destroy_bitmap(spr_input_14);
    destroy_bitmap(spr_input_15);
    destroy_bitmap(spr_input_16);
    destroy_bitmap(spr_input_17);
    destroy_bitmap(bufferx);
    destroy_bitmap(bt_joystick);
    destroy_bitmap(bt_up_1);
    destroy_bitmap(bt_up_2);
    destroy_bitmap(bt_up_3);
    destroy_bitmap(bt_down_1);
    destroy_bitmap(bt_down_2);
    destroy_bitmap(bt_down_3);
    destroy_bitmap(bt_left_1);
    destroy_bitmap(bt_left_2);
    destroy_bitmap(bt_left_3);
    destroy_bitmap(bt_right_1);
    destroy_bitmap(bt_right_2);
    destroy_bitmap(bt_right_3);
    destroy_bitmap(bt_1);
    destroy_bitmap(bt_2);
    destroy_bitmap(bt_3);
    destroy_bitmap(bt_ss_1);
    destroy_bitmap(bt_ss_2);
    destroy_bitmap(bt_ss_3);
    destroy_bitmap(P[1].Spr);
    destroy_bitmap(P[2].Spr);
    destroy_bitmap(ED_Spr);
    destroy_bitmap(Fireball[1].Spr);
    destroy_bitmap(Fireball[2].Spr);
    //destroy_bitmap(P1_Spr_Aux); destroy_bitmap(P2_Spr_Aux); destroy_bitmap(ED_Spr_Aux); //desativado, pois sao destruidos durante o loop de jogo
    destroy_bitmap(P1_1);
    destroy_bitmap(P2_1);
    for (int ind = 0; ind < MAX_CHARS; ind++) { destroy_bitmap(MINIsprDisplay[ind]); }
    for (int ind = 0; ind < MAX_CHARS; ind++) { destroy_bitmap(MINIsprDisplayArcadeMode[ind]); }
    destroy_bitmap(P1BIGDisplay);
    destroy_bitmap(P2BIGDisplay);
    destroy_bitmap(P2BIGDisplayInv);
    destroy_bitmap(spr_energy_bar);
    destroy_bitmap(spr_energy_bar_full);
    destroy_bitmap(P1_energy_flip);
    destroy_bitmap(P1_energy_red_flip);
    destroy_bitmap(char_generic);
    destroy_bitmap(char_generic2x);
    destroy_bitmap(spr_mold_results);
    destroy_bitmap(spr_result_perfect);
    destroy_bitmap(spr_result_win);
    destroy_bitmap(spr_splash_draw);
    destroy_bitmap(spr_splash_fight);
    destroy_bitmap(spr_splash_ko);
    destroy_bitmap(spr_splash_perfect);
    destroy_bitmap(spr_splash_round1);
    destroy_bitmap(spr_splash_round2);
    destroy_bitmap(spr_splash_round3);
    destroy_bitmap(spr_splash_round4);
    destroy_bitmap(spr_splash_round5);
    destroy_bitmap(spr_splash_youlose);
    destroy_bitmap(spr_splash_youwin);
    destroy_sample(round1);
    destroy_sample(round2);
    destroy_sample(round3);
    destroy_sample(fight);
    destroy_sample(ko);
    destroy_sample(perfect);
    destroy_sample(intro);
    destroy_sample(back);
    destroy_sample(choice);
    destroy_sample(confirm);
    destroy_sample(cursor);
    destroy_sample(attacklvl1);
    destroy_sample(attacklvl2);
    destroy_sample(attacklvl3);
    destroy_sample(hitlvl1);
    destroy_sample(hitlvl2);
    destroy_sample(hitlvl3);
    destroy_midi(bgm_apresentacao);
    destroy_midi(bgm_continue);
    destroy_midi(bgm_select_screen);
    destroy_midi(bgm_versus_mode);
    clear_keybuf();
}
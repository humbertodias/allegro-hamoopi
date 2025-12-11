#include "play.h"

void GameLoop_GamePlayMode() {
    //inicio de round
    if (timer_rounds == 0) {
        desabilita_players = 1;
        FadeCtr = 255;
        FadeIN = 0;
        FadeOUT = 1;
        //P1 miniatura da foto ingame
        char P1_1s[40] = "";
        sprintf(P1_1s, "data/chars/%s/000_01.png", P[1].Name);
        P1_1 = load_bitmap(P1_1s, NULL);
        if (!P1_1) { P1_1 = load_bitmap("data/system/000_01.png", NULL); }
        //P2 miniatura da foto ingame
        char P2_1s[40] = "";
        sprintf(P2_1s, "data/chars/%s/000_01.png", P[2].Name);
        P2_1 = load_bitmap(P2_1s, NULL);
        if (!P2_1) { P2_1 = load_bitmap("data/system/000_01.png", NULL); }
    }

    //timer_rounds é um contador de frames crescente utilizado em animacoes
    timer_rounds++;
    if (timer_rounds >= 250) { desabilita_players = 0; } else { RoundTime++; }

    //final de round //RoundTime é um contador de frames decrescente utilizado pelo relogio da luta
    if (RoundTime == 60) { RoundTime = 0; } //segundo zero nao conta
    if (RoundTime == 0) {
        desabilita_players = 1;
        if (timer_final_de_rounds == 0) { zeraListaDeInputs(); }
        timer_final_de_rounds++;
    }

    //interrompe o relogio da luta em caso de KO
    if (P[1].Energy == 0 || P[2].Energy == 0) {
        RoundTime++;
        timer_final_de_rounds++;
        desabilita_players = 1;
        zeraListaDeInputs();
    }
    //SlowDown no final do Round Apos o hit que causou o KO
    if (EndRoundSlowDown < 60) {
        if (EndRoundSlowDown == 1) { EndRoundSlowDown = 15; } //ajuste do valor definido na hora do hit. ref Mov 570
        if (timer_final_de_rounds <= 50) { EndRoundSlowDown += 0.2; }
        if (timer_final_de_rounds > 50) { EndRoundSlowDown += 1; }
        if (EndRoundSlowDown > 60) { EndRoundSlowDown = 60; }
        Ctrl_FPS = floor(EndRoundSlowDown);
        //install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS));
    }

    if (timer_final_de_rounds >= EndRoundT) {
        //reinicia rounds ou sai da luta
        RoundAtual++;

        //sair da luta
        int sairDaLuta = 0;
        if (RoundAtual > RoundTotal) { sairDaLuta = 1; }
        for (int ind = 1; ind <= 2; ind++) {
            if (P[ind].Round_Wins >= 1 && RoundTotal == 1) { sairDaLuta = 1; }
            if (P[ind].Round_Wins >= 2 && RoundTotal == 2) { sairDaLuta = 1; }
            if (P[ind].Round_Wins >= 2 && RoundTotal == 3) { sairDaLuta = 1; }
            if (P[ind].Round_Wins >= 3 && RoundTotal == 4) { sairDaLuta = 1; }
            if (P[ind].Round_Wins >= 3 && RoundTotal == 5) { sairDaLuta = 1; }
        }
        if (RoundAtual > RoundTotal) { sairDaLuta = 1; }

        if (sairDaLuta == 1) {
            sairDaLuta = 0;
            desabilita_players = 0;
            timermenus = 0;
            timer_rounds = 0;
            timer_final_de_rounds = 0;
            SelectCharMode = 1;
            GamePlayMode = 0;
            if (ModoHistoria == 0) { strcpy(ChoiceBG, ""); }
            if (P[1].Round_Wins > P[2].Round_Wins) {
                P[1].Wins++;
                P[2].Loses++;
            }
            if (P[1].Round_Wins < P[2].Round_Wins) {
                P[2].Wins++;
                P[1].Loses++;
            }
            if (P[1].Round_Wins == P[2].Round_Wins) {
                P[1].Draws++;
                P[2].Draws++;
            }
            P[1].Round_Wins = 0;
            P[2].Round_Wins = 0;
            play_midi(bgm_select_screen, 1); //bgm
            timer_rounds = 0;
            timer_final_de_rounds = 0;
            set_config_file("SETUP.ini");
            RoundTime = get_config_int("CONFIG", "time", 99);
            RoundTime = RoundTime * 60 + 59;
            //desliga as fireballs
            Fireball[1].Ativa = 0;
            Fireball[2].Ativa = 0;
            P[1].QtdeMagias = 0;
            P[2].QtdeMagias = 0;
            //posicao dos players
            P[1].x = bg_test->w / 2 - 80;
            P[2].x = bg_test->w / 2 + 80;
            AlturaPiso = bg_test->h - 20;
            P[1].y = AlturaPiso;
            P[2].y = AlturaPiso;
            MeioDaTela = (P[1].x + P[2].x) / 2;
            //define estado inicial
            P[1].Lado = 1;
            P[2].Lado = -1;
            P[1].Energy = 1000;
            P[2].Energy = 1000;
            P[1].EnergyRedBar = 1000;
            P[2].EnergyRedBar = 1000;
            P[1].Color = -1;
            P[2].Color = -1;
            P[1].Visible = 1;
            P[2].Visible = 1;
            P[1].RoomLimit = 1;
            P[2].RoomLimit = 1;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
            Draw_CHBoxes_P1();
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
            Draw_CHBoxes_P2();
        }

        /*reinicia a luta*/
        timer_rounds = 0;
        timer_final_de_rounds = 0;
        set_config_file("SETUP.ini");
        RoundTime = get_config_int("CONFIG", "time", 99);
        RoundTime = RoundTime * 60 + 59;
        //desliga as fireballs
        Fireball[1].Ativa = 0;
        Fireball[2].Ativa = 0;
        P[1].QtdeMagias = 0;
        P[2].QtdeMagias = 0;
        //posicao dos players
        P[1].x = bg_test->w / 2 - 80;
        P[2].x = bg_test->w / 2 + 80;
        AlturaPiso = bg_test->h - 20;
        P[1].y = AlturaPiso;
        P[2].y = AlturaPiso;
        MeioDaTela = (P[1].x + P[2].x) / 2;
        //define estado inicial
        P[1].Lado = 1;
        P[2].Lado = -1;
        P[1].Energy = 1000;
        P[2].Energy = 1000;
        P[1].EnergyRedBar = 1000;
        P[2].EnergyRedBar = 1000;
        P[1].Color = -1;
        P[2].Color = -1;
        P[1].Visible = 1;
        P[2].Visible = 1;
        P[1].RoomLimit = 1;
        P[2].RoomLimit = 1;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }

    /*TECLAS DE SISTEMA*/
    if (timermenus == 15) {
        if (key[KEY_ESC]) {
            play_sample(back, 255, 128, 1000, 0);
            Ctrl_FPS = 60;
            //install_int_ex(tempo, BPS_TO_TIMER(60));
            desabilita_players = 0;
            timermenus = 0;
            timer_rounds = 0;
            timer_final_de_rounds = 0;
            SelectCharMode = 1;
            GamePlayMode = 0;
            if (ModoHistoria == 0) { strcpy(ChoiceBG, ""); }
            play_midi(bgm_select_screen, 1); //bgm
            timer_rounds = 0;
            timer_final_de_rounds = 0;
            set_config_file("SETUP.ini");
            RoundTime = get_config_int("CONFIG", "time", 99);
            RoundTime = RoundTime * 60 + 59;
            //desliga as fireballs
            Fireball[1].Ativa = 0;
            Fireball[2].Ativa = 0;
            P[1].QtdeMagias = 0;
            P[2].QtdeMagias = 0;
            //posicao dos players
            P[1].x = bg_test->w / 2 - 80;
            P[2].x = bg_test->w / 2 + 80;
            AlturaPiso = bg_test->h - 20;
            P[1].y = AlturaPiso;
            P[2].y = AlturaPiso;
            //define estado inicial
            P[1].Lado = 1;
            P[2].Lado = -1;
            P[1].Energy = 1000;
            P[2].Energy = 1000;
            P[1].EnergyRedBar = 1000;
            P[2].EnergyRedBar = 1000;
            P[1].Color = -1;
            P[2].Color = -1;
            P[1].Visible = 1;
            P[2].Visible = 1;
            P[1].RoomLimit = 1;
            P[2].RoomLimit = 1;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
            Draw_CHBoxes_P1();
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
            Draw_CHBoxes_P2();
        }
        if (key[KEY_ALT] && key[KEY_F4]) { sair = 1; }
        if (key_F1_status == 1 && Draw_Debug == 0) { Draw_Debug = 1; } else if (key_F1_status == 1 && Draw_Debug == 1) {
            Draw_Debug = 0;
        }
        if (key_F2_status == 1 && Draw_Box == 0) { Draw_Box = 1; } else if (key_F2_status == 1 && Draw_Box == 1) {
            Draw_Box = 0;
        }
        if (key_F3_status == 1 && Draw_Input == 0) { Draw_Input = 1; } else if (key_F3_status == 1 && Draw_Input == 1) {
            Draw_Input = 0;
        }
        if (key_F4_status == 1 && op_ShowFrameData == 0) { op_ShowFrameData = 1; } else if (
            key_F4_status == 1 && op_ShowFrameData == 1) { op_ShowFrameData = 0; }
        if (key[KEY_F5]) {
            P[1].Energy += -10;
            P[1].Special += -10;
        }
        if (key[KEY_F6]) {
            P[1].Energy += 10;
            P[1].Special += 10;
        }
        if (key[KEY_F7]) {
            P[2].Energy += -10;
            P[2].Special += -10;
        }
        if (key[KEY_F8]) {
            P[2].Energy += 10;
            P[2].Special += 10;
        }
        if (key[KEY_F9]) {
            Ctrl_FPS = 1;
            //install_int_ex(tempo, BPS_TO_TIMER( 1));
        }
        if (key[KEY_F10]) {
            Ctrl_FPS += -1;
            if (Ctrl_FPS < 1) { Ctrl_FPS = 1; }
            //install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS));
        }
        if (key[KEY_F11]) {
            Ctrl_FPS += +1;
            if (Ctrl_FPS > 60) { Ctrl_FPS = 60; }
            //install_int_ex(tempo, BPS_TO_TIMER(Ctrl_FPS));
        }
        if (key[KEY_F12]) {
            Ctrl_FPS = 60;
            //install_int_ex(tempo, BPS_TO_TIMER(60));
        }
    }

    if (P[1].Special < 0) { P[1].Special = 0; }
    if (P[1].Special > 1000) { P[1].Special = 1000; }
    if (P[2].Special < 0) { P[2].Special = 0; }
    if (P[2].Special > 1000) { P[2].Special = 1000; }
    if (P[1].Energy < 0) { P[1].Energy = 0; }
    if (P[1].Energy > 1000) { P[1].Energy = 1000; }
    if (P[2].Energy < 0) { P[2].Energy = 0; }
    if (P[2].Energy > 1000) { P[2].Energy = 1000; }

    /*COLISAO*/
    Checar_Colisao();
    Aplicar_HIT();

    //controle dos especiais
    for (int ind = 1; ind <= 2; ind++) {
        P[ind].PodeTestarEspecial = 0;
        if (
            P[ind].key_LEFT_pressed == 1 ||
            P[ind].key_RIGHT_pressed == 1 ||
            P[ind].key_UP_pressed == 1 ||
            P[ind].key_DOWN_pressed == 1 ||
            P[ind].key_BT1_pressed == 1 ||
            P[ind].key_BT2_pressed == 1 ||
            P[ind].key_BT3_pressed == 1 ||
            P[ind].key_BT4_pressed == 1 ||
            P[ind].key_BT5_pressed == 1 ||
            P[ind].key_BT6_pressed == 1 ||
            P[ind].key_SELECT_pressed == 1 ||
            P[ind].key_START_pressed == 1
        ) { P[ind].PodeTestarEspecial = 1; }
    }

    ///////////////////////////////////////////////////////////////////////////
    // MAQUINA DE ESTADOS - FSM -----------------------------------------[**05]
    ///////////////////////////////////////////////////////////////////////////

    //Faz a transicao de um estado para outro e define o comportamento dos personagens.
    //Um pre requisito para ativar os movimentos é ter as imagens correspondentes na pasta do personagem.

    for (int ind = 1; ind <= 2; ind++) {
        int other;
        if (ind == 1) { other = 2; }
        if (ind == 2) { other = 1; }

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
        for (int indxx = 0; indxx <= 9; indxx++) {
            int a = 0;
            int b = P[ind].Special_Inputs[indxx][0] + 1;
            for (int indx = 1; indx <= P[ind].Special_Inputs[indxx][0]; indx++) {
                a++;
                b--;
                P[ind].Special_Inputs_Ord[indxx][a] = P[ind].Special_Inputs[indxx][b];
            }
            P[ind].Special_Inputs_Ord[indxx][0] = P[ind].Special_Inputs[indxx][0];
        }

        //inverte os direcionais
        for (int indx = 0; indx <= 9; indx++) {
            if (P[ind].Lado == -1) {
                for (int inds = 1; inds <= P[ind].Special_Inputs_Ord[indx][0]; inds++) {
                    int a = 0;
                    int b = 0;
                    int c = 0;
                    if (P[ind].Special_Inputs_Ord[indx][inds] == 1) {
                        P[ind].Special_Inputs_Ord[indx][inds] = 3;
                        a = 1;
                    }
                    if (P[ind].Special_Inputs_Ord[indx][inds] == 4) {
                        P[ind].Special_Inputs_Ord[indx][inds] = 6;
                        b = 1;
                    }
                    if (P[ind].Special_Inputs_Ord[indx][inds] == 7) {
                        P[ind].Special_Inputs_Ord[indx][inds] = 9;
                        c = 1;
                    }
                    if (a == 0) {
                        if (P[ind].Special_Inputs_Ord[indx][inds] == 3) {
                            P[ind].Special_Inputs_Ord[indx][inds] = 1;
                            a = 1;
                        }
                    }
                    if (b == 0) {
                        if (P[ind].Special_Inputs_Ord[indx][inds] == 6) {
                            P[ind].Special_Inputs_Ord[indx][inds] = 4;
                            b = 1;
                        }
                    }
                    if (c == 0) {
                        if (P[ind].Special_Inputs_Ord[indx][inds] == 9) {
                            P[ind].Special_Inputs_Ord[indx][inds] = 7;
                            c = 1;
                        }
                    }
                }
            }
        }

        //zera variaveis
        ativa_especial = 0;
        int especial_ativado = -1;

        int AtivadorDeMagia = 0;
        int AtivadorDeMagiaNumeroDoEspecial = 0;

        //testa os inputs dos especiais
        for (int esp = 0; esp <= 9; esp++) {
            ativa_especial = 0;
            for (int indx = 1; indx <= 16; indx++) {
                if (P[ind].Special_Inputs_Ord[esp][0] >= indx) {
                    //prepara os inputs dos botoes
                    bta = -999;
                    btb = -999;
                    btc = -999;
                    if (P[ind].Special_Inputs_Ord[esp][indx] >= -6 && P[ind].Special_Inputs_Ord[esp][indx] <= 1) {
                        bta = P[ind].Special_Inputs_Ord[esp][indx];
                        btb = bta;
                        btc = bta;
                    }
                    if (P[ind].Special_Inputs_Ord[esp][indx] == -7) {
                        bta = -1;
                        btb = -2;
                        btc = -3;
                    }
                    if (P[ind].Special_Inputs_Ord[esp][indx] == -8) {
                        bta = -4;
                        btb = -5;
                        btc = -6;
                    }
                    //teste de comparacao
                    if (P[ind].slot[indx] != P[ind].Special_Inputs_Ord[esp][indx]) {
                        if (P[ind].bt_slot[indx] * -1 != bta) {
                            if (P[ind].bt_slot[indx] * -1 != btb) {
                                if (P[ind].bt_slot[indx] * -1 != btc) {
                                    ativa_especial = 0;
                                } else { ativa_especial++; }
                            } else { ativa_especial++; }
                        } else { ativa_especial++; }
                    } else { ativa_especial++; }
                    if (P[ind].Special_Inputs_Ord[esp][0] == ativa_especial) {
                        //força do golpe
                        if (ind == 1) {
                            if (P[1].bt_slot[1] * -1 == -1 || P[1].bt_slot[1] * -1 == -4) {
                                ForcaDoGolpeP1 = 1;
                                P[1].Special_Version = 1;
                            }
                        }
                        if (ind == 1) {
                            if (P[1].bt_slot[1] * -1 == -2 || P[1].bt_slot[1] * -1 == -5) {
                                ForcaDoGolpeP1 = 2;
                                P[1].Special_Version = 2;
                            }
                        }
                        if (ind == 1) {
                            if (P[1].bt_slot[1] * -1 == -3 || P[1].bt_slot[1] * -1 == -6) {
                                ForcaDoGolpeP1 = 3;
                                P[1].Special_Version = 3;
                            }
                        }
                        if (ind == 2) {
                            if (P[2].bt_slot[1] * -1 == -1 || P[2].bt_slot[1] * -1 == -4) {
                                ForcaDoGolpeP2 = 1;
                                P[2].Special_Version = 1;
                            }
                        }
                        if (ind == 2) {
                            if (P[2].bt_slot[1] * -1 == -2 || P[2].bt_slot[1] * -1 == -5) {
                                ForcaDoGolpeP2 = 2;
                                P[2].Special_Version = 2;
                            }
                        }
                        if (ind == 2) {
                            if (P[2].bt_slot[1] * -1 == -3 || P[2].bt_slot[1] * -1 == -6) {
                                ForcaDoGolpeP2 = 3;
                                P[2].Special_Version = 3;
                            }
                        }
                        especial_ativado = esp;
                    }

                    //Implementa os Especiais / MAGIAS
                    if (P[ind].PodeTestarEspecial == 1) {
                        for (int indx = 0; indx <= 9; indx++) {
                            int num;
                            if (indx == 0) { num = 700; }
                            if (indx == 1) { num = 710; }
                            if (indx == 2) { num = 720; }
                            if (indx == 3) { num = 730; }
                            if (indx == 4) { num = 740; }
                            if (indx == 5) { num = 750; }
                            if (indx == 6) { num = 760; }
                            if (indx == 7) { num = 770; }
                            if (indx == 8) { num = 780; }
                            if (indx == 9) { num = 790; }
                            if (especial_ativado == indx) {
                                if (P[ind].TotalDeFramesMov[num] > -1 && P[ind].State != num) {
                                    // validacao evita soltar especial no ar
                                    // MomentoDoP...==1 significa que o Player esta de Pé
                                    // solucao temporaria
                                    int validacao = 0;
                                    if (ind == 1 && MomentoDoP1 == 1) { validacao = 1; }
                                    if (ind == 2 && MomentoDoP2 == 1) { validacao = 1; }
                                    if (validacao == 1) {
                                        //tudo ok para soltar a magia, mas antes, preciso verificar se
                                        //todos os comandos feitos pelo jogador foram realizados dentro do tempo de 1,5 segundos

                                        //primeiro preciso saber quantos inputs tem o especial em questão
                                        int totaldeinputs = 0;
                                        if (num == 700) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[0][0] + P[ind].Special_Inputs_b[0][0];
                                        }
                                        if (num == 710) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[1][0] + P[ind].Special_Inputs_b[1][0];
                                        }
                                        if (num == 720) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[2][0] + P[ind].Special_Inputs_b[2][0];
                                        }
                                        if (num == 730) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[3][0] + P[ind].Special_Inputs_b[3][0];
                                        }
                                        if (num == 740) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[4][0] + P[ind].Special_Inputs_b[4][0];
                                        }
                                        if (num == 750) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[5][0] + P[ind].Special_Inputs_b[5][0];
                                        }
                                        if (num == 760) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[6][0] + P[ind].Special_Inputs_b[6][0];
                                        }
                                        if (num == 770) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[7][0] + P[ind].Special_Inputs_b[7][0];
                                        }
                                        if (num == 780) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[8][0] + P[ind].Special_Inputs_b[8][0];
                                        }
                                        if (num == 790) {
                                            totaldeinputs =
                                                    P[ind].Special_Inputs_c[9][0] + P[ind].Special_Inputs_b[9][0];
                                        }
                                        //depois preciso somar o total de tempo dos inputs inseridos
                                        int totaldetempodosinputs = 0;
                                        for (int ttime = 1; ttime <= totaldeinputs; ttime++) {
                                            totaldetempodosinputs += P[ind].t_slot[ttime];
                                        }
                                        //agora, ativo o especial se o tempo for menor a 1,5 segundos (90 frames +15 de canja rs)
                                        if (totaldetempodosinputs <= 105) {
                                            AtivadorDeMagia = 1;
                                            AtivadorDeMagiaNumeroDoEspecial = num;
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
        if (AtivadorDeMagia == 1) {
            //inicializa a magia
            P[ind].QtdeMagias = 0;
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            PLAYER_STATE(ind, AtivadorDeMagiaNumeroDoEspecial, 0,
                         P[ind].TotalDeFramesMov[AtivadorDeMagiaNumeroDoEspecial]);
            Fireball[ind].StartFrame = frame_count;
            New_Fireball(ind);

            //som da magia
            for (int iii = 700; iii <= 890; iii += 10) {
                char txtaudio[50] = "";
                if (P[ind].State == iii && P[ind].TotalDeFramesMov[P[ind].State] > 0) {
                    sprintf(txtaudio, "data/chars/%s/%i.wav", P[ind].Name, P[ind].State);
                    SAMPLE *snd = load_sample(txtaudio);
                    if (snd) { play_sample(snd, 255, 128, 1000, 0); }
                    AtivadorDeMagia = 0;
                    //destroy_sample(snd);
                }
            }
        }

        //---

        /*101 Soco Fraco em Pe*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602 || P[ind].State ==
             101)
            && (P[ind].key_BT1_pressed == 1)
            && (abs(P[1].x - P[2].x) >= 60)
            && (P[ind].TotalDeFramesMov[101] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 101;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*102 Soco Medio em Pe*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT2_pressed == 1)
            && (abs(P[1].x - P[2].x) >= 60)
            && (P[ind].TotalDeFramesMov[102] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 102;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*103 Soco Forte em Pe*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT3_pressed == 1)
            && (abs(P[1].x - P[2].x) >= 60)
            && (P[ind].TotalDeFramesMov[103] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 103;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*104 Chute Fraco em Pe*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT4_pressed == 1)
            && (abs(P[1].x - P[2].x) >= 60)
            && (P[ind].TotalDeFramesMov[104] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 104;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*105 Chute Medio em Pe*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT5_pressed == 1)
            && (abs(P[1].x - P[2].x) >= 60)
            && (P[ind].TotalDeFramesMov[105] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 105;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*106 Chute Forte em Pe*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT6_pressed == 1)
            && (abs(P[1].x - P[2].x) >= 60)
            && (P[ind].TotalDeFramesMov[106] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 106;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*151 Soco Fraco em Pe (PERTO)*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT1_pressed == 1)
            && (abs(P[1].x - P[2].x) < 60)) {
            if (P[ind].TotalDeFramesMov[151] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 151;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl1, 255, 128, 1000, 0);
            }
            if (P[ind].TotalDeFramesMov[151] == -1
                && P[ind].TotalDeFramesMov[101] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 101;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl1, 255, 128, 1000, 0);
            }
        }
        /*152 Soco Medio em Pe (PERTO)*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT2_pressed == 1)
            && (abs(P[1].x - P[2].x) < 60)) {
            if (P[ind].TotalDeFramesMov[152] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 152;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl2, 255, 128, 1000, 0);
            }
            if (P[ind].TotalDeFramesMov[152] == -1
                && P[ind].TotalDeFramesMov[102] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 102;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl2, 255, 128, 1000, 0);
            }
        }
        /*153 Soco Forte em Pe (PERTO)*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT3_pressed == 1)
            && (abs(P[1].x - P[2].x) < 60)) {
            if (P[ind].TotalDeFramesMov[153] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 153;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl3, 255, 128, 1000, 0);
            }
            if (P[ind].TotalDeFramesMov[153] == -1
                && P[ind].TotalDeFramesMov[103] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 103;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl3, 255, 128, 1000, 0);
            }
        }
        /*154 Chute Fraco em Pe (PERTO)*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT4_pressed == 1)
            && (abs(P[1].x - P[2].x) < 60)) {
            if (P[ind].TotalDeFramesMov[154] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 154;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl1, 255, 128, 1000, 0);
            }
            if (P[ind].TotalDeFramesMov[154] == -1
                && P[ind].TotalDeFramesMov[104] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 104;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl1, 255, 128, 1000, 0);
            }
        }
        /*155 Chute Medio em Pe (PERTO)*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT5_pressed == 1)
            && (abs(P[1].x - P[2].x) < 60)) {
            if (P[ind].TotalDeFramesMov[155] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 155;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl2, 255, 128, 1000, 0);
            }
            if (P[ind].TotalDeFramesMov[155] == -1
                && P[ind].TotalDeFramesMov[105] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 105;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl2, 255, 128, 1000, 0);
            }
        }
        /*156 Chute Forte em Pe (PERTO)*/
        if ((P[ind].State == 100 || P[ind].State == 410 || P[ind].State == 420 || P[ind].State == 602)
            && (P[ind].key_BT6_pressed == 1)
            && (abs(P[1].x - P[2].x) < 60)) {
            if (P[ind].TotalDeFramesMov[156] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 156;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl3, 255, 128, 1000, 0);
            }
            if (P[ind].TotalDeFramesMov[156] == -1
                && P[ind].TotalDeFramesMov[106] > -1) {
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                int set = 106;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
                play_sample(attacklvl3, 255, 128, 1000, 0);
            }
        }
        /*211 Soco Fraco Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT1_pressed == 1
            && (P[ind].TotalDeFramesMov[211] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 211;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*211 Soco Fraco Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT1_pressed == 1
            && (P[ind].TotalDeFramesMov[211] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 211;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*212 Soco Medio Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT2_pressed == 1
            && (P[ind].TotalDeFramesMov[212] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 212;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*212 Soco Medio Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT2_pressed == 1
            && (P[ind].TotalDeFramesMov[212] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 212;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*213 Soco Forte Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT3_pressed == 1
            && (P[ind].TotalDeFramesMov[213] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 213;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*213 Soco Forte Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT3_pressed == 1
            && (P[ind].TotalDeFramesMov[213] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 213;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*214 Chute Fraco Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT4_pressed == 1
            && (P[ind].TotalDeFramesMov[214] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 214;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*214 Chute Fraco Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT4_pressed == 1
            && (P[ind].TotalDeFramesMov[214] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 214;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*215 Chute Medio Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT5_pressed == 1
            && (P[ind].TotalDeFramesMov[215] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 215;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*215 Chute Medio Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT5_pressed == 1
            && (P[ind].TotalDeFramesMov[215] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 215;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*216 Chute Forte Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT6_pressed == 1
            && (P[ind].TotalDeFramesMov[216] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 216;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*216 Chute Forte Abaixado + Tras*/
        if ((P[ind].State == 200 || P[ind].State == 210)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT6_pressed == 1
            && (P[ind].TotalDeFramesMov[216] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 216;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*221 Soco Fraco Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT1_pressed == 1
            && (P[ind].TotalDeFramesMov[221] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 221;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*221 Soco Fraco Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT1_pressed == 1
            && (P[ind].TotalDeFramesMov[221] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 221;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*222 Soco Medio Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT2_pressed == 1 && (P[ind].TotalDeFramesMov[222] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 222;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*222 Soco Medio Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT2_pressed == 1
            && (P[ind].TotalDeFramesMov[222] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 222;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*223 Soco Forte Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT3_pressed == 1
            && (P[ind].TotalDeFramesMov[223] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 223;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*223 Soco Forte Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT3_pressed == 1
            && (P[ind].TotalDeFramesMov[223] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 223;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*224 Chute Fraco Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT4_pressed == 1
            && (P[ind].TotalDeFramesMov[224] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 224;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*224 Chute Fraco Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT4_pressed == 1
            && (P[ind].TotalDeFramesMov[224] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 224;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*225 Chute Medio Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT5_pressed == 1 && (P[ind].TotalDeFramesMov[225] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 225;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*225 Chute Medio Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT5_pressed == 1
            && (P[ind].TotalDeFramesMov[225] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 225;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*226 Chute Forte Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && P[ind].key_BT6_pressed == 1
            && (P[ind].TotalDeFramesMov[226] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 226;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*226 Chute Forte Abaixado + Frente*/
        if ((P[ind].State == 200 || P[ind].State == 220)
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && P[ind].key_BT6_pressed == 1
            && (P[ind].TotalDeFramesMov[226] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 226;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*201 Soco Fraco Abaixado*/
        if ((P[ind].State == 200 || P[ind].State == 601)
            && P[ind].key_BT1_pressed == 1
            && (P[ind].TotalDeFramesMov[201] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 201;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*202 Soco Medio Abaixado*/
        if ((P[ind].State == 200 || P[ind].State == 601)
            && P[ind].key_BT2_pressed == 1
            && (P[ind].TotalDeFramesMov[202] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 202;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*203 Soco Forte Abaixado*/
        if ((P[ind].State == 200 || P[ind].State == 601)
            && P[ind].key_BT3_pressed == 1
            && (P[ind].TotalDeFramesMov[203] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 203;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*204 Chute Fraco Abaixado*/
        if ((P[ind].State == 200 || P[ind].State == 601)
            && P[ind].key_BT4_pressed == 1
            && (P[ind].TotalDeFramesMov[204] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 204;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*205 Chute Medio Abaixado*/
        if ((P[ind].State == 200 || P[ind].State == 601)
            && P[ind].key_BT5_pressed == 1
            && (P[ind].TotalDeFramesMov[205] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 205;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*206 Chute Forte Abaixado*/
        if ((P[ind].State == 200 || P[ind].State == 601)
            && P[ind].key_BT6_pressed == 1
            && (P[ind].TotalDeFramesMov[206] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 206;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*210 Baixo e Tras*/
        if (P[ind].State == 200
            && P[ind].Lado == 1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && (P[ind].TotalDeFramesMov[210] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 210;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*210 Baixo e Tras*/
        if (P[ind].State == 200
            && P[ind].Lado == -1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && (P[ind].TotalDeFramesMov[210] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 210;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*220 Baixo e Frente*/
        if (P[ind].State == 200
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && (P[ind].TotalDeFramesMov[220] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 220;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*220 Baixo e Frente*/
        if (P[ind].State == 200
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && (P[ind].TotalDeFramesMov[220] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 220;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*410 Andando para Tras*/
        if (P[ind].State == 100
            && P[ind].Lado == 1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && (P[ind].TotalDeFramesMov[410] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 410;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*410 Andando para Tras*/
        if (P[ind].State == 100
            && P[ind].Lado == -1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && (P[ind].TotalDeFramesMov[410] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 410;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*420 Andando para Frente*/
        if (P[ind].State == 100
            && P[ind].Lado == 1
            && (P[ind].key_RIGHT_pressed == 1 || P[ind].key_RIGHT_hold == 1)
            && (P[ind].TotalDeFramesMov[420] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 420;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*420 Andando para Frente*/
        if (P[ind].State == 100
            && P[ind].Lado == -1
            && (P[ind].key_LEFT_pressed == 1 || P[ind].key_LEFT_hold == 1)
            && (P[ind].TotalDeFramesMov[420] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 420;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*507 End Reversao Aerea 507->606*/
        if (P[ind].State == 507
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[606] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 606;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*507 End Reversao Aerea 507->100*/
        if (P[ind].State == 507
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[100] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 100;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*551 End Queda*/
        if (P[ind].State == 550
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[550] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 551;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*552 End Queda continuacao*/
        if (P[ind].State == 551
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[551] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 552;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*571 End Queda p/ KO*/
        if (P[ind].State == 570
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[570] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 571;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*572 End Queda p/ KO continuacao*/
        if (P[ind].State == 571
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[571] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 572;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*601 Abaixando*/
        if (P[ind].State == 100
            && (P[ind].key_DOWN_pressed == 1 || P[ind].key_DOWN_hold == 1)
            && (P[ind].TotalDeFramesMov[601] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 601;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*601 Abaixando*/
        if (P[ind].State == 410
            && (P[ind].key_DOWN_pressed == 1 || P[ind].key_DOWN_hold == 1)
            && (P[ind].TotalDeFramesMov[601] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 601;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*601 Abaixando*/
        if (P[ind].State == 420
            && (P[ind].key_DOWN_pressed == 1 || P[ind].key_DOWN_hold == 1)
            && (P[ind].TotalDeFramesMov[601] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 601;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*601/608 Abaixando/Virando de Lado abaixado*/
        if (P[ind].State == 606 && P[ind].key_DOWN_status > 0) {
            int a = 1;
            if (a == 1 && P[ind].Lado == 1 && P[ind].x < MeioDaTela && (P[ind].TotalDeFramesMov[601] > -1)) {
                a = 0;
                AHitP1 = 1;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 601;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
            if (a == 1 && P[ind].Lado == 1 && P[ind].x > MeioDaTela && (P[ind].TotalDeFramesMov[608] > -1)) {
                a = 0;
                AHitP1 = 1;
                P[ind].Lado = -1;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 608;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
            if (a == 1 && P[ind].Lado == -1 && P[ind].x > MeioDaTela && (P[ind].TotalDeFramesMov[601] > -1)) {
                a = 0;
                AHitP1 = 1;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 601;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
            if (a == 1 && P[ind].Lado == -1 && P[ind].x < MeioDaTela && (P[ind].TotalDeFramesMov[608] > -1)) {
                a = 0;
                AHitP1 = 1;
                P[ind].Lado = 1;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 608;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
        }
        /*602 Levantando*/
        if (P[ind].State == 200
            && (P[ind].key_DOWN_released == 1 || P[ind].key_DOWN_hold == 0)
            && (P[ind].TotalDeFramesMov[602] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 602;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*603 Intro Pulo Tras*/
        if (P[ind].State == 410
            && P[ind].Lado == 1
            && (P[ind].key_UP_status > 0)
            && P[ind].key_LEFT_status > 0
            && P[ind].key_RIGHT_status == 0
            && (P[ind].TotalDeFramesMov[603] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 603;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*603 Intro Pulo Tras*/
        if (P[ind].State == 410
            && P[ind].Lado == -1
            && (P[ind].key_UP_status > 0)
            && P[ind].key_LEFT_status == 0
            && P[ind].key_RIGHT_status > 0
            && (P[ind].TotalDeFramesMov[603] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 603;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*604 Intro Pulo Neutro*/
        if (P[ind].State == 100
            && (P[ind].key_UP_status > 0)
            && P[ind].key_LEFT_status == 0
            && P[ind].key_RIGHT_status == 0
            && (P[ind].TotalDeFramesMov[604] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 604;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*605 Intro Pulo Frente*/
        if (P[ind].State == 420
            && P[ind].Lado == -1
            && (P[ind].key_UP_status > 0)
            && P[ind].key_LEFT_status > 0
            && P[ind].key_RIGHT_status == 0
            && (P[ind].TotalDeFramesMov[605] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 605;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*605 Intro Pulo Frente*/
        if (P[ind].State == 420
            && P[ind].Lado == 1
            && (P[ind].key_UP_status > 0)
            && P[ind].key_LEFT_status == 0
            && P[ind].key_RIGHT_status > 0
            && (P[ind].TotalDeFramesMov[605] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 605;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*606 End Pulo*/
        if ((P[ind].State == 300
             || P[ind].State == 301 || P[ind].State == 302 || P[ind].State == 303
             || P[ind].State == 304 || P[ind].State == 305 || P[ind].State == 306)
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[606] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 606;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*606 End Pulo*/
        if ((P[ind].State == 310
             || P[ind].State == 311 || P[ind].State == 312 || P[ind].State == 313
             || P[ind].State == 314 || P[ind].State == 315 || P[ind].State == 316)
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[606] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 606;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*606 End Pulo*/
        if ((P[ind].State == 320
             || P[ind].State == 321 || P[ind].State == 322 || P[ind].State == 323
             || P[ind].State == 324 || P[ind].State == 325 || P[ind].State == 326)
            && P[ind].y == AlturaPiso
            && P[ind].Vspeed >= 0
            && (P[ind].TotalDeFramesMov[606] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 606;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*301 Pulo Neutro + Soco Fraco*/
        if (P[ind].State == 300
            && P[ind].key_BT1_status == 1
            && (P[ind].TotalDeFramesMov[301] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 301;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*302 Pulo Neutro + Soco Medio*/
        if (P[ind].State == 300
            && P[ind].key_BT2_status == 1
            && (P[ind].TotalDeFramesMov[302] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 302;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*303 Pulo Neutro + Soco Forte*/
        if (P[ind].State == 300
            && P[ind].key_BT3_status == 1
            && (P[ind].TotalDeFramesMov[303] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 303;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*304 Pulo Neutro + Chute Fraco*/
        if (P[ind].State == 300
            && P[ind].key_BT4_status == 1
            && (P[ind].TotalDeFramesMov[304] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 304;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*305 Pulo Neutro + Chute Medio*/
        if (P[ind].State == 300
            && P[ind].key_BT5_status == 1
            && (P[ind].TotalDeFramesMov[305] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 305;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*306 Pulo Neutro + Chute Forte*/
        if (P[ind].State == 300
            && P[ind].key_BT6_status == 1
            && (P[ind].TotalDeFramesMov[306] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 306;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*321 Pulo Frente + Soco Fraco*/
        if ((P[ind].State == 310 || P[ind].State == 320)
            && P[ind].key_BT1_status == 1
            && (P[ind].TotalDeFramesMov[321] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 321;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*322 Pulo Frente + Soco Medio*/
        if ((P[ind].State == 310 || P[ind].State == 320)
            && P[ind].key_BT2_status == 1
            && (P[ind].TotalDeFramesMov[322] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 322;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*323 Pulo Frente + Soco Forte*/
        if ((P[ind].State == 310 || P[ind].State == 320)
            && P[ind].key_BT3_status == 1
            && (P[ind].TotalDeFramesMov[323] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 323;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*324 Pulo Frente + Chute Fraco*/
        if ((P[ind].State == 310 || P[ind].State == 320)
            && P[ind].key_BT4_status == 1
            && (P[ind].TotalDeFramesMov[324] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 324;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl1, 255, 128, 1000, 0);
        }
        /*325 Pulo Frente + Chute Medio*/
        if ((P[ind].State == 310 || P[ind].State == 320)
            && P[ind].key_BT5_status == 1
            && (P[ind].TotalDeFramesMov[325] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 325;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl2, 255, 128, 1000, 0);
        }
        /*326 Pulo Frente + Chute Forte*/
        if ((P[ind].State == 310 || P[ind].State == 320)
            && P[ind].key_BT6_status == 1
            && (P[ind].TotalDeFramesMov[326] > -1)) {
            P[ind].StartFrame = frame_count;
            P[ind].MovStartFrame = P[ind].StartFrame;
            int set = 326;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            play_sample(attacklvl3, 255, 128, 1000, 0);
        }
        /*607 Virando de Lado em Pe*/
        if (P[ind].State == 100
            && (P[ind].x > MeioDaTela
                && P[ind].Lado == 1)
            && (P[ind].TotalDeFramesMov[607] > -1)) {
            P[ind].Lado = -1;
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 607;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*607 Virando de Lado em Pe*/
        if (P[ind].State == 100
            && (P[ind].x < MeioDaTela
                && P[ind].Lado == -1)
            && (P[ind].TotalDeFramesMov[607] > -1)) {
            P[ind].Lado = 1;
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 607;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*607 Virando de Lado em Pe*/
        if (P[ind].State == 420
            && P[ind].Lado == 1
            && P[ind].x > MeioDaTela
            && (P[ind].TotalDeFramesMov[607] > -1)) {
            P[ind].Lado = -1;
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 607;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*607 Virando de Lado em Pe*/
        if (P[ind].State == 420
            && P[ind].Lado == -1
            && P[ind].x < MeioDaTela
            && (P[ind].TotalDeFramesMov[607] > -1)) {
            P[ind].Lado = 1;
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 607;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*608 Virando de Lado Abaixado*/
        if (P[ind].State == 200
            && (P[ind].x > MeioDaTela
                && P[ind].Lado == 1)
            && (P[ind].TotalDeFramesMov[608] > -1)) {
            P[ind].Lado = -1;
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 608;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*608 Virando de Lado Abaixado*/
        if (P[ind].State == 200
            && (P[ind].x < MeioDaTela
                && P[ind].Lado == -1)
            && (P[ind].TotalDeFramesMov[608] > -1)) {
            P[ind].Lado = 1;
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 608;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*608 Virando de Lado Abaixado*/
        if (P[ind].State == 220
            && P[ind].Lado == 1
            && P[ind].x > MeioDaTela
            && (P[ind].TotalDeFramesMov[608] > -1)) {
            P[ind].Lado = -1;
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 608;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*608 Virando de Lado Abaixado*/
        if (P[ind].State == 220
            && P[ind].Lado == -1
            && P[ind].x < MeioDaTela
            && (P[ind].TotalDeFramesMov[608] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 608;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*210 Abaixado Andando para Tras*/
        if (P[ind].State == 210
            && P[ind].key_LEFT_released == 1
            && (P[ind].TotalDeFramesMov[200] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 200;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*210 Abaixado Andando para Tras*/
        if (P[ind].State == 210
            && P[ind].key_RIGHT_released == 1
            && P[ind].Lado == -1
            && (P[ind].TotalDeFramesMov[200] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 200;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*220 Abaixado Andando para Frente*/
        if (P[ind].State == 220
            && P[ind].key_RIGHT_released == 1
            && (P[ind].TotalDeFramesMov[200] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 200;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*220 Abaixado Andando para Frente*/
        if (P[ind].State == 220
            && P[ind].key_LEFT_released == 1
            && P[ind].Lado == -1
            && (P[ind].TotalDeFramesMov[200] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 200;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*210;220 Stop*/
        if ((P[ind].State == 210 || P[ind].State == 220)
            && (P[ind].key_DOWN_released == 1 || P[ind].key_DOWN_hold == 0)) {
            int set = 0;
            if (P[ind].TotalDeFramesMov[602] > -1) { set = 602; } else { set = 100; }
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*100 Parado*/
        if (P[ind].State == 410
            && P[ind].key_LEFT_released == 1
            && (P[ind].TotalDeFramesMov[100] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 100;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*100 Parado*/
        if (P[ind].State == 410
            && P[ind].key_RIGHT_released == 1
            && P[ind].Lado == -1
            && (P[ind].TotalDeFramesMov[100] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 100;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*100 Parado*/
        if (P[ind].State == 420
            && P[ind].key_RIGHT_released == 1
            && (P[ind].TotalDeFramesMov[100] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 100;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*100 Parado*/
        if (P[ind].State == 420
            && P[ind].key_LEFT_released == 1
            && P[ind].Lado == -1
            && (P[ind].TotalDeFramesMov[100] > -1)) {
            P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
            int set = 100;
            PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
        }
        /*611 Ganhou por KO ou Time Over*/
        if (
            P[ind].State == 100
            && timer_final_de_rounds > 0
            && P[ind].Energy >= P[other].Energy
            && (P[other].State == 572
                || P[other].State == 616 || P[other].State == 617
                || P[other].State == 618 || P[other].State == 100)) {
            if (P[ind].TotalDeFramesMov[611] > -1) {
                P[ind].Hspeed = 0;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 611;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
            if (P[ind].TotalDeFramesMov[611] == -1) {
                P[ind].Hspeed = 0;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 100;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
        }
        /*616 Perdeu por Time Over*/
        if ((P[ind].State != 616
             && P[ind].State != 570 && P[ind].State != 571 && P[ind].State != 572
             && P[ind].State != 550 && P[ind].State != 551 && P[ind].State != 552
             && P[ind].State != 623 && P[ind].State != 626
             && P[ind].State != 310
             && P[ind].State != 311 && P[ind].State != 312 && P[ind].State != 313
             && P[ind].State != 314 && P[ind].State != 315 && P[ind].State != 316
             && P[ind].State != 300
             && P[ind].State != 301 && P[ind].State != 302 && P[ind].State != 303
             && P[ind].State != 304 && P[ind].State != 305 && P[ind].State != 306
             && P[ind].State != 320
             && P[ind].State != 321 && P[ind].State != 322 && P[ind].State != 323
             && P[ind].State != 324 && P[ind].State != 325 && P[ind].State != 326
             && P[ind].State != 11 && P[ind].State != 12 && P[ind].State != 13
             && P[ind].State != 16)
            && timer_final_de_rounds > 0
            && P[ind].Energy <= P[other].Energy
            && P[ind].Energy > 0) {
            if (P[ind].TotalDeFramesMov[616] > -1) {
                P[ind].Hspeed = 0;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 616;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
            if (P[ind].TotalDeFramesMov[616] == -1) {
                P[ind].Hspeed = 0;
                P[ind].StartFrame = frame_count; //P[ind].MovStartFrame=P[ind].StartFrame;
                int set = 100;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }
        }

        //SONS DE HIT
        if (PlaySoundHitLvl1 == 1) {
            play_sample(hitlvl1, 255, 128, 1000, 0);
            PlaySoundHitLvl1 = 0;
        }
        if (PlaySoundHitLvl2 == 1) {
            play_sample(hitlvl2, 255, 128, 1000, 0);
            PlaySoundHitLvl2 = 0;
        }
        if (PlaySoundHitLvl3 == 1) {
            play_sample(hitlvl3, 255, 128, 1000, 0);
            PlaySoundHitLvl3 = 0;
        }
    } //fim do for - FSM

    ///////////////////////////////////////////////////////////////////////////
    // DIFS / APLICA ALTERACAO NOS PARAMETROS DOS PERSONAGENS -----------[**06]
    ///////////////////////////////////////////////////////////////////////////

    //Afasta os jogadores quando ocorre sobreposicao de posicao
    //Dois corpos nao ocupam o mesmo lugar no espaço :)
    if (contatofisico == 1) {
        if (P[1].x <= P[2].x) {
            P[1].x -= 1;
            P[2].x += 1;
            if (P[1].x <= 30) {
                P[1].x = 30;
                P[2].x += 1;
            }
            if (P[2].x >= bg_test->w - 30) {
                P[1].x -= 1;
                P[2].x = bg_test->w - 30;
            }
        }
        if (P[1].x > P[2].x) {
            P[1].x += 1;
            P[2].x -= 1;
            if (P[2].x <= 30) {
                P[2].x = 30;
                P[1].x += 1;
            }
            if (P[1].x >= bg_test->w - 30) {
                P[2].x -= 1;
                P[1].x = bg_test->w - 30;
            }
        }
    }

    /* <P1> */
    //DIF01 - Mantem o personagem dentro da tela
    if (P[1].Hspeed != 0 && P1HitPause == 0) {
        P[1].x += P[1].Hspeed;
        if (P[1].x <= 30) {
            P[1].x = 30;
        }
        if (P[1].x >= bg_test->w - 30) {
            P[1].x = bg_test->w - 30;
        }
    }
    //DIF02 - Define a distancia maxima entre os jogadores
    if (op_Zoom == 1) {
        if (abs(P[1].x - P[2].x) > bufferx->h * 0.6) {
            P[1].x += (P[1].Hspeed * -1);
            P[2].x += (P[2].Hspeed * -1);
        }
    }
    if (op_Zoom == 0) { if (abs(P[1].x - P[2].x) > 250) { P[1].x += (P[1].Hspeed * -1); } }
    //DIF03 - Calcula o pulo e o pouso no chao
    if (P[1].Vspeed != 0 && P1HitPause == 0) {
        P[1].y += P[1].Vspeed; //if(P[1].y<=0){P[1].y=0;}
        P[1].ConstanteY += P[1].Vspeed - P[1].Gravity;
        if (P[1].y >= AlturaPiso) {
            P[1].y = AlturaPiso;
            P[1].Hspeed = 0;
            P[1].Vspeed = 0;
            P[1].Gravity = 0;
            P[1].ConstanteY = 0;
        }
    }
    //DIF04 - Aplica gravidade ao Vspeed
    if (P[1].Gravity != 0 && P1HitPause == 0) { P[1].Vspeed += P[1].Gravity; }
    //DIF05 - Reseta velocidade se o player estiver parado no State 100
    if (P[1].State == 100) {
        P[1].Hspeed = 0;
        P[1].Vspeed = 0;
    }

    /* <P2> */
    //DIF01 - Mantem o personagem dentro da tela
    if (P[2].Hspeed != 0 && P2HitPause == 0) {
        P[2].x += P[2].Hspeed;
        if (P[2].x <= 30) {
            P[2].x = 30;
        }
        if (P[2].x >= bg_test->w - 30) {
            P[2].x = bg_test->w - 30;
        }
    }
    //DIF02 - Define a distancia maxima entre os jogadores
    if (op_Zoom == 1) {
        if (abs(P[1].x - P[2].x) > bufferx->h * 0.6) {
            P[1].x += (P[1].Hspeed * -1);
            P[2].x += (P[2].Hspeed * -1);
        }
    }
    if (op_Zoom == 0) { if (abs(P[1].x - P[2].x) > 250) { P[2].x += (P[2].Hspeed * -1); } }
    //DIF03 - Calcula o pulo e o pouso no chao
    if (P[2].Vspeed != 0 && P2HitPause == 0) {
        P[2].y += P[2].Vspeed; //if(P[2].y<=0){P[2].y=0;}
        P[2].ConstanteY += P[2].Vspeed - P[2].Gravity;
        if (P[2].y >= AlturaPiso) {
            P[2].y = AlturaPiso;
            P[2].Hspeed = 0;
            P[2].Vspeed = 0;
            P[2].Gravity = 0;
            P[2].ConstanteY = 0;
        }
    }
    //DIF04 - Aplica gravidade ao Vspeed
    if (P[2].Gravity != 0 && P2HitPause == 0) { P[2].Vspeed += P[2].Gravity; }
    //DIF05 - Reseta velocidade se o player estiver parado no State 100
    if (P[2].State == 100) {
        P[2].Hspeed = 0;
        P[2].Vspeed = 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    // FUNCOES DE DESENHO -----------------------------------------------[**07]
    ///////////////////////////////////////////////////////////////////////////

    int Atuador1 = 0;
    int Atuador2 = 0;

    //clear_to_color(bufferx,makecol(100,149,237)); //fundo azul
    clear_to_color(bufferx, makecol(0,0,0)); //fundo preto

    /* <P1> anim */
    if (P1HitPause == 0 && P2HitPause == 0) {
        int HitStackChange = 0;
        if (P[1].IndexAnim == 0) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_00) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_01;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 1) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_01) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_02;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 2) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_02) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_03;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 3) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_03) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_04;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 4) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_04) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_05;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 5) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_05) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_06;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 6) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_06) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_07;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 7) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_07) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_08;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 8) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_08) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_09;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 9) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_09) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_10;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 10) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_10) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_11;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 11) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_11) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_12;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 12) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_12) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_13;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 13) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_13) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_14;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 14) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_14) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_15;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 15) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_15) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_16;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 16) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_16) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_17;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 17) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_17) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_18;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 18) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_18) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_19;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 19) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_19) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_20;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 20) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_20) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_21;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 21) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_21) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_22;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 22) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_22) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_23;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 23) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_23) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_24;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 24) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_24) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_25;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 25) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_25) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_26;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 26) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_26) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_27;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 27) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_27) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_28;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[1].IndexAnim == 28) {
            if (frame_count > P[1].StartFrame + P1_FrameTime_28) {
                Atuador1 = 1;
                P[1].IndexAnim++;
                P1_FrameTime = P1_FrameTime_29;
                P[1].StartFrame = frame_count;
                Draw_CHBoxes_P1();
                if (strcmp(P[1].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (HitStackChange == 1) {
            if (P[1].State != 301 && P[1].State != 321 && P[1].State != 304 && P[1].State != 324) {
                AHitP1 = 1;
            }
        }
        //if (P[1].IndexAnim==29) {}
    }

    /* <P1> end of anim vai pro LOOP*/
    //vai para o loop, caso nao seja nenhum dos movimentos contidos neste IF
    if (P[1].IndexAnim > P[1].TotalFrames
        && P[1].State != 101 && P[1].State != 102 && P[1].State != 103 && P[1].State != 104 && P[1].State != 105 && P[1]
        .State != 106 //EXCESSOES DE NON LOOPS
        && P[1].State != 151 && P[1].State != 152 && P[1].State != 153 && P[1].State != 154 && P[1].State != 155 && P[1]
        .State != 156 //EXCESSOES DE NON LOOPS
        && P[1].State != 201 && P[1].State != 202 && P[1].State != 203 && P[1].State != 204 && P[1].State != 205 && P[1]
        .State != 206 //EXCESSOES DE NON LOOPS
        //&& P[1].State!=300                                                                                              //EXCESSOES DE NON LOOPS
        && P[1].State != 301 && P[1].State != 302 && P[1].State != 303 && P[1].State != 304 && P[1].State != 305 && P[1]
        .State != 306 //EXCESSOES DE NON LOOPS
        //&& P[1].State!=310                                                                                              //EXCESSOES DE NON LOOPS
        && P[1].State != 311 && P[1].State != 312 && P[1].State != 313 && P[1].State != 314 && P[1].State != 315 && P[1]
        .State != 316 //EXCESSOES DE NON LOOPS
        //&& P[1].State!=320                                                                                              //EXCESSOES DE NON LOOPS
        && P[1].State != 321 && P[1].State != 322 && P[1].State != 323 && P[1].State != 324 && P[1].State != 325 && P[1]
        .State != 326 //EXCESSOES DE NON LOOPS
        && P[1].State != 501 && P[1].State != 502 && P[1].State != 503 && P[1].State != 504 && P[1].State != 505 && P[1]
        .State != 506 //EXCESSOES DE NON LOOPS
        && P[1].State != 507 && P[1].State != 508 && P[1].State != 509 && P[1].State != 511 && P[1].State != 512 && P[1]
        .State != 513 //EXCESSOES DE NON LOOPS
        //&& P[1].State!=550                                                                                              //EXCESSOES DE NON LOOPS
        && P[1].State != 552 && P[1].State != 601 && P[1].State != 602 && P[1].State != 603 && P[1].State != 604 && P[1]
        .State != 605 //EXCESSOES DE NON LOOPS
        && P[1].State != 606 && P[1].State != 607 && P[1].State != 608 && P[1].State != 611 && P[1].State != 612 && P[1]
        .State != 613 //EXCESSOES DE NON LOOPS
        && P[1].State != 616 && P[1].State != 617 && P[1].State != 618
        && P[1].State != 700 && P[1].State != 710 && P[1].State != 720 && P[1].State != 730
        && P[1].State != 740 && P[1].State != 750 && P[1].State != 760
        && P[1].State != 770 && P[1].State != 780 && P[1].State != 790
    ) //EXCESSOES DE NON LOOPS
    {
        P[1].IndexAnim = 0;
        P1_FrameTime = P1_FrameTime_00;
        P[1].StartFrame = frame_count;
        Draw_CHBoxes_P1();
    } //-loop
    /* <P1> Non Loops FSM! */
    //movimentos sem loop terminam e carregam outros movimentos, exemplo: final do soco fraco [101] carrega movimento parado [100]
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 101) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 102) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 103) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 104) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 105) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 106) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 151) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 152) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 153) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 154) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 155) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 156) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 201) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 202) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 203) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 204) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 205) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 206) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 501) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 502) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 503) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 504) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 505) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 506) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 511) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 512) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 513) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 601) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 552) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 602) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 603) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 310, 0, P[1].TotalDeFramesMov[310]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 604) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 300, 0, P[1].TotalDeFramesMov[300]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 605) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 320, 0, P[1].TotalDeFramesMov[320]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 606) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 607) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 608) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 200, 0, P[1].TotalDeFramesMov[200]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 700) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 710) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 720) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 730) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 740) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 750) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 760) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 770) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 780) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 790) {
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 100, 0, P[1].TotalDeFramesMov[100]);
        Draw_CHBoxes_P1();
    }

    //Anim Infinita
    //if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==300) {  }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 301) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 301, P[1].IndexAnim, P[1].TotalDeFramesMov[301]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 302) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 302, P[1].IndexAnim, P[1].TotalDeFramesMov[302]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 303) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 303, P[1].IndexAnim, P[1].TotalDeFramesMov[303]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 304) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 304, P[1].IndexAnim, P[1].TotalDeFramesMov[304]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 305) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 305, P[1].IndexAnim, P[1].TotalDeFramesMov[305]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 306) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 306, 0, P[1].TotalDeFramesMov[306]);
        Draw_CHBoxes_P1();
    }
    //if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==310) {  }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 311) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 311, P[1].IndexAnim, P[1].TotalDeFramesMov[311]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 312) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 312, P[1].IndexAnim, P[1].TotalDeFramesMov[312]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 313) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 313, P[1].IndexAnim, P[1].TotalDeFramesMov[313]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 314) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 314, P[1].IndexAnim, P[1].TotalDeFramesMov[314]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 315) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 315, P[1].IndexAnim, P[1].TotalDeFramesMov[315]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 316) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 316, P[1].IndexAnim, P[1].TotalDeFramesMov[316]);
        Draw_CHBoxes_P1();
    }
    //if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==320) {  }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 321) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 321, P[1].IndexAnim, P[1].TotalDeFramesMov[321]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 322) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 322, P[1].IndexAnim, P[1].TotalDeFramesMov[322]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 323) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 323, P[1].IndexAnim, P[1].TotalDeFramesMov[323]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 324) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 324, P[1].IndexAnim, P[1].TotalDeFramesMov[324]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 325) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 325, P[1].IndexAnim, P[1].TotalDeFramesMov[325]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 326) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 326, P[1].IndexAnim, P[1].TotalDeFramesMov[326]);
        Draw_CHBoxes_P1();
    }
    //if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==507) {  }
    //if (P[1].IndexAnim>P[1].TotalFrames && P[1].State==550) {  }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 611) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 611, P[1].IndexAnim, P[1].TotalDeFramesMov[611]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 612) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 612, P[1].IndexAnim, P[1].TotalDeFramesMov[612]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 613) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 613, P[1].IndexAnim, P[1].TotalDeFramesMov[613]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 616) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 616, P[1].IndexAnim, P[1].TotalDeFramesMov[616]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 617) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 617, P[1].IndexAnim, P[1].TotalDeFramesMov[617]);
        Draw_CHBoxes_P1();
    }
    if (P[1].IndexAnim > P[1].TotalFrames && P[1].State == 618) {
        P[1].IndexAnim--;
        P[1].StartFrame = frame_count;
        PLAYER_STATE(1, 618, P[1].IndexAnim, P[1].TotalDeFramesMov[618]);
        Draw_CHBoxes_P1();
    }

    //garante que o IndexAnim nunca vai ser maior que TotalFrames
    if (P[1].IndexAnim > P[1].TotalFrames) { P[1].IndexAnim = P[1].TotalFrames; }

    /* <P2> anim */
    if (P2HitPause == 0 && P1HitPause == 0) {
        int HitStackChange = 0;
        if (P[2].IndexAnim == 0) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_00) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_01;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 1) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_01) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_02;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 2) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_02) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_03;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 3) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_03) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_04;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 4) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_04) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_05;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 5) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_05) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_06;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 6) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_06) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_07;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 7) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_07) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_08;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 8) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_08) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_09;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 9) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_09) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_10;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 10) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_10) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_11;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 11) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_11) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_12;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 12) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_12) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_13;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 13) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_13) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_14;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 14) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_14) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_15;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 15) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_15) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_16;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 16) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_16) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_17;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 17) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_17) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_18;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 18) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_18) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_19;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 19) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_19) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_20;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 20) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_20) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_21;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 21) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_21) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_22;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 22) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_22) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_23;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 23) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_23) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_24;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 24) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_24) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_25;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 25) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_25) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_26;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 26) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_26) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_27;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 27) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_27) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_28;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (P[2].IndexAnim == 28) {
            if (frame_count > P[2].StartFrame + P2_FrameTime_28) {
                Atuador2 = 1;
                P[2].IndexAnim++;
                P2_FrameTime = P2_FrameTime_29;
                P[2].StartFrame = frame_count;
                Draw_CHBoxes_P2();
                if (strcmp(P[2].HitStack, "Multi") == 0) { HitStackChange = 1; }
            }
        }
        if (HitStackChange == 1) {
            if (P[2].State != 301 && P[2].State != 321 && P[2].State != 304 && P[2].State != 324) {
                AHitP2 = 1;
            }
        }
        //if (P[2].IndexAnim==29) { }
    }
    /* <P2> end of anim vai pro LOOP*/
    //vai para o loop, caso nao seja nenhum dos movimentos contidos neste IF
    if (P[2].IndexAnim > P[2].TotalFrames
        && P[2].State != 101 && P[2].State != 102 && P[2].State != 103 && P[2].State != 104 && P[2].State != 105 && P[2]
        .State != 106 //EXCESSOES DE NON LOOPS
        && P[2].State != 151 && P[2].State != 152 && P[2].State != 153 && P[2].State != 154 && P[2].State != 155 && P[2]
        .State != 156 //EXCESSOES DE NON LOOPS
        && P[2].State != 201 && P[2].State != 202 && P[2].State != 203 && P[2].State != 204 && P[2].State != 205 && P[2]
        .State != 206 //EXCESSOES DE NON LOOPS
        //&& P[2].State!=300                                                                                              //EXCESSOES DE NON LOOPS
        && P[2].State != 301 && P[2].State != 302 && P[2].State != 303 && P[2].State != 304 && P[2].State != 305 && P[2]
        .State != 306 //EXCESSOES DE NON LOOPS
        //&& P[2].State!=310                                                                                              //EXCESSOES DE NON LOOPS
        && P[2].State != 311 && P[2].State != 312 && P[2].State != 313 && P[2].State != 314 && P[2].State != 315 && P[2]
        .State != 316 //EXCESSOES DE NON LOOPS
        //&& P[2].State!=320                                                                                              //EXCESSOES DE NON LOOPS
        && P[2].State != 321 && P[2].State != 322 && P[2].State != 323 && P[2].State != 324 && P[2].State != 325 && P[2]
        .State != 326 //EXCESSOES DE NON LOOPS
        && P[2].State != 501 && P[2].State != 502 && P[2].State != 503 && P[2].State != 504 && P[2].State != 505 && P[2]
        .State != 506 //EXCESSOES DE NON LOOPS
        && P[2].State != 507 && P[2].State != 508 && P[2].State != 509 && P[2].State != 511 && P[2].State != 512 && P[2]
        .State != 513 //EXCESSOES DE NON LOOPS
        //&& P[2].State!=550                                                                                              //EXCESSOES DE NON LOOPS
        && P[2].State != 552 && P[2].State != 601 && P[2].State != 602 && P[2].State != 603 && P[2].State != 604 && P[2]
        .State != 605 //EXCESSOES DE NON LOOPS
        && P[2].State != 606 && P[2].State != 607 && P[2].State != 608 && P[2].State != 611 && P[2].State != 612 && P[2]
        .State != 613 //EXCESSOES DE NON LOOPS
        && P[2].State != 616 && P[2].State != 617 && P[2].State != 618
        && P[2].State != 700 && P[2].State != 710 && P[2].State != 720 && P[2].State != 730
        && P[2].State != 740 && P[2].State != 750 && P[2].State != 760
        && P[2].State != 770 && P[2].State != 780 && P[2].State != 790
    ) //EXCESSOES DE NON LOOPS
    {
        P[2].IndexAnim = 0;
        P2_FrameTime = P2_FrameTime_00;
        P[2].StartFrame = frame_count;
        Draw_CHBoxes_P2();
    } //-loop
    /* <P2> Non Loops FSM! */
    //movimentos sem loop terminam e carregam outros movimentos, exemplo: final do soco fraco [101] carrega movimento parado [100]
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 101) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 102) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 103) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 104) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 105) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 106) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 151) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 152) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 153) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 154) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 155) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 156) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 201) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 202) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 203) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 204) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 205) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 206) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 501) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 502) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 503) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 504) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 505) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 506) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 511) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 512) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 513) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 601) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 552) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 602) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 603) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 310, 0, P[2].TotalDeFramesMov[310]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 604) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 300, 0, P[2].TotalDeFramesMov[300]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 605) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 320, 0, P[2].TotalDeFramesMov[320]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 606) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 607) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 608) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 200, 0, P[2].TotalDeFramesMov[200]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 700) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 710) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 720) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 730) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 740) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 750) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 760) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 770) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 780) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 790) {
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 100, 0, P[2].TotalDeFramesMov[100]);
        Draw_CHBoxes_P2();
    }

    //Anim Infinita
    //if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==300) {  }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 301) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 301, P[2].IndexAnim, P[2].TotalDeFramesMov[301]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 302) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 302, P[2].IndexAnim, P[2].TotalDeFramesMov[302]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 303) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 303, P[2].IndexAnim, P[2].TotalDeFramesMov[303]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 304) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 304, P[2].IndexAnim, P[2].TotalDeFramesMov[304]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 305) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 305, P[2].IndexAnim, P[2].TotalDeFramesMov[305]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 306) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(1, 306, 0, P[2].TotalDeFramesMov[306]);
        Draw_CHBoxes_P2();
    }
    //if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==310) {  }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 311) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 311, P[2].IndexAnim, P[2].TotalDeFramesMov[311]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 312) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 312, P[2].IndexAnim, P[2].TotalDeFramesMov[312]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 313) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 313, P[2].IndexAnim, P[2].TotalDeFramesMov[313]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 314) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 314, P[2].IndexAnim, P[2].TotalDeFramesMov[314]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 315) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 315, P[2].IndexAnim, P[2].TotalDeFramesMov[315]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 316) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 316, P[2].IndexAnim, P[2].TotalDeFramesMov[316]);
        Draw_CHBoxes_P2();
    }
    //if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==320) {  }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 321) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 321, P[2].IndexAnim, P[2].TotalDeFramesMov[321]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 322) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 322, P[2].IndexAnim, P[2].TotalDeFramesMov[322]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 323) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 323, P[2].IndexAnim, P[2].TotalDeFramesMov[323]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 324) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 324, P[2].IndexAnim, P[2].TotalDeFramesMov[324]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 325) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 325, P[2].IndexAnim, P[2].TotalDeFramesMov[325]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 326) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 326, P[2].IndexAnim, P[2].TotalDeFramesMov[326]);
        Draw_CHBoxes_P2();
    }
    //if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==507) {  }
    //if (P[2].IndexAnim>P[2].TotalFrames && P[2].State==550) {  }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 611) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 611, P[2].IndexAnim, P[2].TotalDeFramesMov[611]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 612) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 612, P[2].IndexAnim, P[2].TotalDeFramesMov[612]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 613) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 613, P[2].IndexAnim, P[2].TotalDeFramesMov[613]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 616) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 616, P[2].IndexAnim, P[2].TotalDeFramesMov[616]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 617) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 617, P[2].IndexAnim, P[2].TotalDeFramesMov[617]);
        Draw_CHBoxes_P2();
    }
    if (P[2].IndexAnim > P[2].TotalFrames && P[2].State == 618) {
        P[2].IndexAnim--;
        P[2].StartFrame = frame_count;
        PLAYER_STATE(2, 618, P[2].IndexAnim, P[2].TotalDeFramesMov[618]);
        Draw_CHBoxes_P2();
    }

    //garante que o IndexAnim nunca vai ser maior que TotalFrames
    if (P[2].IndexAnim > P[2].TotalFrames) { P[2].IndexAnim = P[2].TotalFrames; }

    ///////////////////////////////////////////////////////////////////////////
    // ATUADORES --------------------------------------------------------------
    ///////////////////////////////////////////////////////////////////////////

    int LIMITEINF = 0;
    int LIMITESUP = 0;

    if (Atuador1 == 1) { LIMITEINF = 1; } else { LIMITEINF = 2; }
    if (Atuador2 == 1) { LIMITESUP = 2; } else { LIMITESUP = 1; }

    //---
    for (int ind = LIMITEINF; ind <= LIMITESUP; ind++) {
        if (Atuador1 == 1) { Atuador1 = 0; }
        if (Atuador2 == 1) { Atuador2 = 0; }

        //localiza a linha especifica no TableAtlas
        int line = 0;
        for (int indx = 0; indx <= 500; indx++) {
            if (P[ind].State == P[ind].TableAtlas[indx][0]
                && P[ind].IndexAnim == P[ind].TableAtlas[indx][1]) {
                line = P[ind].TableAtlas[indx][2];
            }
            if (line != 0) break;
        }

        //somente aplica os atuadores do 2 frame em diante da animacao
        //lembrando que o atuador do primeiro frame é carregado no LOAD_PLAYER
        if (P[ind].IndexAnim > 0) {
            //X//
            if (P[ind].TableAtlas[line][6] != -5555) {
                P[ind].x += P[ind].TableAtlas[line][6];
            }

            //Y//
            if (P[ind].TableAtlas[line][7] != -5555) {
                P[ind].y += P[ind].TableAtlas[line][7];
            }

            //Vspeed//
            if (P[ind].TableAtlas[line][8] != -5555) {
                P[ind].Vspeed = P[ind].TableAtlas[line][8];
            }

            //Hspeed//
            if (P[ind].TableAtlas[line][9] != -5555) {
                P[ind].Hspeed = P[ind].TableAtlas[line][9];
                if (P[ind].Lado == -1) { P[ind].Hspeed = P[ind].Hspeed * -1; }
            }

            //Gravity//
            if (P[ind].TableAtlas[line][10] != -5555) {
                P[ind].Gravity += P[ind].TableAtlas[line][10];
            }

            //Friction//
            if (P[ind].TableAtlas[line][11] != -5555) {
                P[ind].Friction += P[ind].TableAtlas[line][11];
            }

            //Energy Change//
            if (P[ind].TableAtlas[line][12] != -5555) {
                P[ind].Energy += P[ind].TableAtlas[line][12];
            }
            if (P[ind].Energy > 1000) { P[ind].Energy = 1000; }
            if (P[ind].Energy < 0) { P[ind].Energy = 0; }

            //Special Change//
            if (P[ind].TableAtlas[line][13] != -5555) {
                P[ind].Special += P[ind].TableAtlas[line][13];
            }
            if (P[ind].Special > 1000) { P[ind].Special = 1000; }
            if (P[ind].Special < 0) { P[ind].Special = 0; }

            //Visible//
            if (P[ind].TableAtlas[line][14] != -5555) {
                P[ind].Visible = P[ind].TableAtlas[line][14];
            }

            //RoomLimit// nao implementado
            if (P[ind].TableAtlas[line][15] != -5555) {
                //P[ind].RoomLimit=P[ind].TableAtlas[line][15];
            }

            //HitType//
            if (P[ind].TableAtlas[line][16] != -5555) {
                int a = P[ind].TableAtlas[line][16];
                if (a == 1) { strcpy(P[ind].HitType, "Normal"); }
                if (a == 2) { strcpy(P[ind].HitType, "Fall"); }
            }

            //ChangeState//
            if (P[ind].TableAtlas[line][17] != -5555) {
                int set = P[ind].TableAtlas[line][17];
                P[ind].StartFrame = frame_count;
                P[ind].MovStartFrame = P[ind].StartFrame;
                PLAYER_STATE(ind, set, 0, P[ind].TotalDeFramesMov[set]);
            }

            //Freeze// nao implementado
            if (P[ind].TableAtlas[line][18] != -5555) {
                //P[ind].TableAtlas[line][18];
            }

            //Color// nao implementado
            if (P[ind].TableAtlas[line][19] != -5555) {
                //P[ind].TableAtlas[line][19];
            }

            //HitStack//
            if (P[ind].TableAtlas[line][20] != -5555) {
                int a = P[ind].TableAtlas[line][20];
                if (a == 1) { strcpy(P[ind].HitStack, "Single"); }
                if (a == 2) { strcpy(P[ind].HitStack, "Multi"); }
            }
        }
    }
    //---

    ///////////////////////////////////////////////////////////////////////////
    // DESENHA PERSONAGENS NA TELA --------------------------------------------
    ///////////////////////////////////////////////////////////////////////////

    //desenha o cenario em render 2X em bufferx
    bufferx->w = bg_test->w * 2;
    bufferx->h = bg_test->h * 2;
    stretch_blit(bg_test, bufferx, 0, 0, bg_test->w, bg_test->h, 0, 0, bufferx->w, bufferx->h);

    //---VScreen+Zoom---//

    if (op_Zoom == 1) {
        if ((VScreen_h - VScreen_y) / bufferx->h < 1) {
            ZoomMaximoAtingido = 0;
        } else {
            if (ZoomMaximoAtingido == 0) {
                Zoom_eixo = (VScreen_w - VScreen_x) / 2;
            }
            ZoomMaximoAtingido = 1; //limite max do zoom atingido
        }
    }

    if (P[1].x < MeioDaTela) { VScreen_FatorZoom = abs((P[1].x - 80) - (P[2].x + 80)); }
    //no inicio do round o valor é 320 }
    else { VScreen_FatorZoom = abs((P[2].x - 80) - (P[1].x + 80)); } //no inicio do round o valor é 320 }
    if (VScreen_FatorZoom <= 250) { VScreen_FatorZoom = 250; } //limita a diminuicao do zoom

    if (ZoomMaximoAtingido == 0) {
        //VS_x
        VScreen_x = MeioDaTela * 2 - VScreen_FatorZoom;
        if (VScreen_x > bufferx->w - VScreen_FatorZoom * 2) VScreen_x = bufferx->w - VScreen_FatorZoom * 2;
        if (VScreen_x < 0) { VScreen_x = 0; }
        //VS_y
        VScreen_y = bg_test->h * 2 - (480 * VScreen_FatorZoom / 320);
        VScreen_y += P[1].ConstanteY + P[2].ConstanteY;
        if (VScreen_y < 0) { VScreen_y = 0; }
        //VS_w, VS_h
        VScreen_w = VScreen_x + VScreen_FatorZoom * 2;
        if (VScreen_w > bufferx->w) { VScreen_w = bufferx->w; }
        VScreen_h = VScreen_y + (480 * VScreen_FatorZoom / 320);
        //VS_x2
        VScreen_x2 = VScreen_w - VScreen_x;
        if (VScreen_x2 > bufferx->w) { VScreen_x2 = bufferx->w; }
        //VS_y2
        VScreen_y2 = VScreen_h - VScreen_y;
        if (VScreen_y2 > bufferx->h) { VScreen_y2 = bufferx->h; }
    }

    //desliga o efeito de zoom
    if (op_Zoom == 0) {
        if (ZoomMaximoAtingido == 0) { Zoom_eixo = (VScreen_w - VScreen_x) / 2; }
        ZoomMaximoAtingido = 1;
    }

    if (ZoomMaximoAtingido == 1) {
        VScreen_x = MeioDaTela * 2 - Zoom_eixo;
        if (VScreen_x < 0) { VScreen_x = 0; }
        if ((VScreen_x + Zoom_eixo * 2) > bufferx->w) { VScreen_x = bufferx->w - Zoom_eixo * 2; }
        if (op_Zoom == 1) {
            //calcular a reentrada do zoom
            int ZVScreen_y;
            int ZVScreen_h;
            //VS_y
            ZVScreen_y = bg_test->h * 2 - (480 * VScreen_FatorZoom / 320);
            ZVScreen_y += P[1].ConstanteY + P[2].ConstanteY;
            if (ZVScreen_y < 0) { ZVScreen_y = 0; }
            //VS_h
            ZVScreen_h = ZVScreen_y + (480 * VScreen_FatorZoom / 320);
            //ativa o zoom in
            if ((ZVScreen_h - ZVScreen_y) / bufferx->h < 1) {
                ZoomMaximoAtingido = 0;
                VScreen_h = ZVScreen_h;
                VScreen_y = ZVScreen_y;
            }
        }
    }
    //---fim de VScreen+Zoom---//

    int ShakeTemp1 = ShakeDist;
    int ShakeTemp2 = ShakeDist;
    if (P2HitPause == 0) { ShakeTemp1 = 0; }
    if (P1HitPause == 0) { ShakeTemp2 = 0; }
    int carga; //indexador para o SprAtlas

    //define a prioridade de desenho, quem ataca é desenhado por cima do oponente
    for (int ind = 1; ind <= 2; ind++) {
        if (
            /*P1_HitBox_tot>0 || */
            P[ind].State == 101 || P[ind].State == 102 || P[ind].State == 103 ||
            P[ind].State == 104 || P[ind].State == 105 || P[ind].State == 106 ||
            P[ind].State == 151 || P[ind].State == 152 || P[ind].State == 153 ||
            P[ind].State == 154 || P[ind].State == 155 || P[ind].State == 156 ||
            P[ind].State == 201 || P[ind].State == 202 || P[ind].State == 203 ||
            P[ind].State == 204 || P[ind].State == 205 || P[ind].State == 206 ||
            P[ind].State == 211 || P[ind].State == 212 || P[ind].State == 213 ||
            P[ind].State == 214 || P[ind].State == 215 || P[ind].State == 216 ||
            P[ind].State == 221 || P[ind].State == 222 || P[ind].State == 223 ||
            P[ind].State == 224 || P[ind].State == 225 || P[ind].State == 226 ||
            P[ind].State == 201 || P[ind].State == 202 || P[ind].State == 203 ||
            P[ind].State == 204 || P[ind].State == 205 || P[ind].State == 206 ||
            P[ind].State == 211 || P[ind].State == 212 || P[ind].State == 213 ||
            P[ind].State == 214 || P[ind].State == 215 || P[ind].State == 216 ||
            P[ind].State == 221 || P[ind].State == 222 || P[ind].State == 223 ||
            P[ind].State == 224 || P[ind].State == 225 || P[ind].State == 226 ||
            P[ind].State == 301 || P[ind].State == 302 || P[ind].State == 303 ||
            P[ind].State == 304 || P[ind].State == 305 || P[ind].State == 306 ||
            P[ind].State == 311 || P[ind].State == 312 || P[ind].State == 313 ||
            P[ind].State == 314 || P[ind].State == 315 || P[ind].State == 316 ||
            P[ind].State == 321 || P[ind].State == 322 || P[ind].State == 323 ||
            P[ind].State == 324 || P[ind].State == 325 || P[ind].State == 326 ||
            P[ind].State == 411 || P[ind].State == 412 || P[ind].State == 413 ||
            P[ind].State == 414 || P[ind].State == 415 || P[ind].State == 416 ||
            P[ind].State == 421 || P[ind].State == 422 || P[ind].State == 423 ||
            P[ind].State == 424 || P[ind].State == 425 || P[ind].State == 426 || P[ind].State == 480 ||
            P[ind].State == 611 || P[ind].State == 612 || P[ind].State == 613 ||
            P[ind].State == 701 || P[ind].State == 702 || P[ind].State == 703 ||
            P[ind].State == 704 || P[ind].State == 705 || P[ind].State == 706 ||
            P[ind].State == 707 || P[ind].State == 708 || P[ind].State == 709 || P[ind].State == 710 ||
            P[ind].State == 711 || P[ind].State == 712 || P[ind].State == 713 ||
            P[ind].State == 714 || P[ind].State == 715 || P[ind].State == 716 ||
            P[ind].State == 717 || P[ind].State == 718 || P[ind].State == 719 || P[ind].State == 720 ||
            P[ind].State == 721 || P[ind].State == 722 || P[ind].State == 723 ||
            P[ind].State == 724 || P[ind].State == 725 || P[ind].State == 726 ||
            P[ind].State == 727 || P[ind].State == 728 || P[ind].State == 729 || P[ind].State == 730
        ) { P[ind].Prioridade = 1; } else { P[ind].Prioridade = 0; }
    }

    /* CARREGA SPRITE */
    for (int indx = 1; indx <= 2; indx++) {
        //primeiro, encontra na TableAtlas o indexador correspondente a imagem que vai ser carregada
        //relembrando os Valores do TableAtlas...
        //[ind][0] State
        //[ind][1] Anim
        //[ind][2] TotalDeImagensUtilizadas (numero desta imagem no total de imagens do char)
        carga = 0;
        for (int ind = 0; ind <= 500; ind++) {
            if (P[indx].State == P[indx].TableAtlas[ind][0]
                && P[indx].IndexAnim == P[indx].TableAtlas[ind][1]) {
                carga = P[indx].TableAtlas[ind][2];
            }
            if (carga != 0) break;
        }
        //depois, pega a imagem SprAtlas correspondente ao indexador, e a coloca em P[n].Spr
        blit(P[indx].SprAtlas[carga], P[indx].Spr, 0, 0, 0, 0, P[indx].SprAtlas[carga]->w, P[indx].SprAtlas[carga]->h);
        P[indx].Spr->w = P[indx].SprAtlas[carga]->w;
        P[indx].Spr->h = P[indx].SprAtlas[carga]->h;
        P[indx].Altura = P[indx].Spr->h;
        P[indx].Largura = P[indx].Spr->w;
        if (P[indx].State == 100) {
            P[indx].Altura_100 = P[indx].Altura;
            P[indx].Largura_100 = P[indx].Largura;
        }
    }

    if (op_desenhar_sombras == 1) {
        int x, y;
        //sombra p1 preparacao
        clear_to_color(P1_Sombra, makecol(255, 0, 255));
        clear_to_color(P1_Sombra_Aux, makecol(255, 0, 255));
        P1_Sombra->w = P[1].Spr->w;
        P1_Sombra->h = P[1].Spr->h / 5;
        stretch_sprite(P1_Sombra, P[1].Spr, 0, 0, P[1].Spr->w, P[1].Spr->h/5);
        for (y = 0; y < P1_Sombra->h; y++) {
            for (x = 0; x < P1_Sombra->w; x++) {
                if (getpixel(P1_Sombra, x, y) != makecol(255, 000, 255))
                    putpixel(P1_Sombra, x, y, makecol(000,000,000));
            }
        }
        P1_Sombra_Aux->w = P1_Sombra->w;
        P1_Sombra_Aux->h = P1_Sombra->h;
        ///*debug temp*/clear_to_color(P1_Sombra_Aux, makecol(255, 255, 255));
        ///*debug temp*/line( P1_Sombra_Aux, 0, 0, P1_Sombra_Aux->w, P1_Sombra_Aux->h, makecol(000,000,000) );
        ///*debug temp*/line( P1_Sombra_Aux, 0, P1_Sombra_Aux->h, P1_Sombra_Aux->w, 0, makecol(000,000,000) );
        if (P[1].Visible == 1) {
            if (P[1].Lado == 1) { draw_sprite(P1_Sombra_Aux, P1_Sombra, 0, 0); }
            if (P[1].Lado == -1) { draw_sprite_h_flip(P1_Sombra_Aux, P1_Sombra, 0, 0); }
        }

        //sombra p2 preparacao
        clear_to_color(P2_Sombra, makecol(255, 0, 255));
        clear_to_color(P2_Sombra_Aux, makecol(255, 0, 255));
        P2_Sombra->w = P[2].Spr->w;
        P2_Sombra->h = P[2].Spr->h / 5;
        stretch_sprite(P2_Sombra, P[2].Spr, 0, 0, P[2].Spr->w, P[2].Spr->h/5);
        for (y = 0; y < P2_Sombra->h; y++) {
            for (x = 0; x < P2_Sombra->w; x++) {
                if (getpixel(P2_Sombra, x, y) != makecol(255, 000, 255))
                    putpixel(P2_Sombra, x, y, makecol(000,000,000));
            }
        }
        P2_Sombra_Aux->w = P2_Sombra->w;
        P2_Sombra_Aux->h = P2_Sombra->h;
        ///*debug temp*/clear_to_color(P2_Sombra_Aux, makecol(255, 255, 255));
        ///*debug temp*/line( P2_Sombra_Aux, 0, 0, P2_Sombra_Aux->w, P2_Sombra_Aux->h, makecol(000,000,000) );
        ///*debug temp*/line( P2_Sombra_Aux, 0, P2_Sombra_Aux->h, P2_Sombra_Aux->w, 0, makecol(000,000,000) );
        if (P[2].Visible == 1) {
            if (P[1].Lado == -1) { draw_sprite(P2_Sombra_Aux, P2_Sombra, 0, 0); }
            if (P[1].Lado == 1) { draw_sprite_h_flip(P2_Sombra_Aux, P2_Sombra, 0, 0); }
        }

        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
        set_trans_blender(0, 0, 0, 100);
        /* sombra <P2> no bufferx */
        if (P[2].Visible == 1) {
            if (P[2].Lado == 1) {
                draw_trans_sprite(bufferx, P2_Sombra_Aux, (P[2].x*2+ShakeTemp2*2)-P[2].XAlign*2,
                                  AlturaPiso*2-P2_Sombra_Aux->h+P[2].ConstanteY/3);
            }
            if (P[2].Lado == -1) {
                draw_trans_sprite(bufferx, P2_Sombra_Aux, ((P[2].x*2+ShakeTemp2*2)-P[2].Spr->w)+P[2].XAlign*2,
                                  AlturaPiso*2-P2_Sombra_Aux->h+P[2].ConstanteY/3);
            }
        }
        /* sombra <P1> no bufferx */
        if (P[1].Visible == 1) {
            if (P[1].Lado == 1) {
                draw_trans_sprite(bufferx, P1_Sombra_Aux, (P[1].x*2+ShakeTemp1*2)-P[1].XAlign*2,
                                  AlturaPiso*2-P1_Sombra_Aux->h+P[1].ConstanteY/3);
            }
            if (P[1].Lado == -1) {
                draw_trans_sprite(bufferx, P1_Sombra_Aux, ((P[1].x*2+ShakeTemp1*2)-P[1].Spr->w)+P[1].XAlign*2,
                                  AlturaPiso*2-P1_Sombra_Aux->h+P[1].ConstanteY/3);
            }
        }
        solid_mode();
    }

    for (int indp = 0; indp <= 1; indp++) {
        /* <P2> desenhado no bufferx */
        if (P[2].Visible == 1) {
            if (P[2].Prioridade == indp) {
                if (P[2].State != 607 && P[2].State != 608) {
                    if (P[2].Lado == 1) {
                        draw_sprite(bufferx, P[2].Spr, (P[2].x*2+ShakeTemp2*2)-P[2].XAlign*2, P[2].y*2-P[2].YAlign*2);
                    }
                    if (P[2].Lado == -1) {
                        draw_sprite_h_flip(bufferx, P[2].Spr, ((P[2].x*2+ShakeTemp2*2)-P[2].Spr->w)+P[2].XAlign*2,
                                           P[2].y*2-P[2].YAlign*2);
                    }
                } else {
                    if (P[2].Lado == -1) {
                        draw_sprite(bufferx, P[2].Spr, (P[2].x*2+ShakeTemp2*2)-P[2].XAlign*2, P[2].y*2-P[2].YAlign*2);
                    }
                    if (P[2].Lado == 1) {
                        draw_sprite_h_flip(bufferx, P[2].Spr, ((P[2].x*2+ShakeTemp2*2)-P[2].Spr->w)+P[2].XAlign*2,
                                           P[2].y*2-P[2].YAlign*2);
                    }
                }
            }
        }

        /* <P1> desenhado no bufferx */
        if (P[1].Visible == 1) {
            if (P[1].Prioridade == indp) {
                if (P[1].State != 607 && P[1].State != 608) {
                    if (P[1].Lado == 1) {
                        draw_sprite(bufferx, P[1].Spr, (P[1].x*2+ShakeTemp1*2)-P[1].XAlign*2, P[1].y*2-P[1].YAlign*2);
                    }
                    if (P[1].Lado == -1) {
                        draw_sprite_h_flip(bufferx, P[1].Spr, ((P[1].x*2+ShakeTemp1*2)-P[1].Spr->w)+P[1].XAlign*2,
                                           P[1].y*2-P[1].YAlign*2);
                    }
                } else {
                    if (P[1].Lado == -1) {
                        draw_sprite(bufferx, P[1].Spr, (P[1].x*2+ShakeTemp1*2)-P[1].XAlign*2, P[1].y*2-P[1].YAlign*2);
                    }
                    if (P[1].Lado == 1) {
                        draw_sprite_h_flip(bufferx, P[1].Spr, ((P[1].x*2+ShakeTemp1*2)-P[1].Spr->w)+P[1].XAlign*2,
                                           P[1].y*2-P[1].YAlign*2);
                    }
                }
            }
        }
    }

    //Controle de Fireball´s
    for (int ind = 1; ind <= 2; ind++) {
        if (P[ind].QtdeMagias > 0) {
            //primeiro, encontra na TableAtlas o indexador correspondente a imagem que vai ser carregada
            carga = 0;
            for (int indx = 0; indx <= 500; indx++) {
                if (Fireball[ind].State == P[ind].TableAtlas[indx][0]
                    && Fireball[ind].IndexAnim == P[ind].TableAtlas[indx][1]) {
                    carga = P[ind].TableAtlas[indx][2];
                }
                if (carga != 0) break;
            }
            //depois, pega a imagem SprAtlas correspondente ao indexador, e a coloca em Fireball[n].Spr
            //precisa otimizar, pois nao é reamente necessario fazer  blit toda hora, apenas na hora de mudar o frame de animacao
            blit(P[ind].SprAtlas[carga], Fireball[ind].Spr, 0, 0, 0, 0, P[ind].SprAtlas[carga]->w,
                 P[ind].SprAtlas[carga]->h);
            Fireball[ind].Spr->w = P[ind].SprAtlas[carga]->w;
            Fireball[ind].Spr->h = P[ind].SprAtlas[carga]->h;
        }

        if (Fireball[ind].Ativa == 1 && P[ind].IndexAnim == Fireball[ind].ThrowFireball) { Fireball[ind].Ativa = 2; }
        if (Fireball[ind].Ativa == 2) {
            if (Fireball[ind].HSpeed > 0) { Fireball[ind].x += Fireball[ind].HSpeed * Fireball[ind].Direcao; }
            //movimenta a fireball no Eixo X
            if (Fireball[ind].VSpeed > 0) { Fireball[ind].y += Fireball[ind].VSpeed; } //movimenta a fireball no Eixo Y

            //Teste de colisao das Fireballs
            //No momento testa apenas 1 Hitbox contra 1 Collision Box
            //É necessario armazenar os valores em vetores, matriz bidimensional, para otimizar o codigo

            int P1hb_HurtBox01x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox01x1) * 2;
            int P1hb_HurtBox01x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox01x2) * 2;
            int P1hb_HurtBox01y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox01y1 * 2);
            int P1hb_HurtBox01y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox01y2 * 2);
            int P1hb_HitBox01x1 = ((Fireball[1].x) * 2) + (Fireball[1].Direcao * P1_Fireball_HitBox01x1) * 2;
            int P1hb_HitBox01x2 = ((Fireball[1].x) * 2) + (Fireball[1].Direcao * P1_Fireball_HitBox01x2) * 2;
            int P1hb_HitBox01y1 = (AlturaPiso + (Fireball[1].y * 2) + P1_Fireball_HitBox01y1 * 2);
            int P1hb_HitBox01y2 = (AlturaPiso + (Fireball[1].y * 2) + P1_Fireball_HitBox01y2 * 2);
            int P2hb_HurtBox01x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox01x1) * 2;
            int P2hb_HurtBox01x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox01x2) * 2;
            int P2hb_HurtBox01y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox01y1 * 2);
            int P2hb_HurtBox01y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox01y2 * 2);
            int P2hb_HitBox01x1 = ((Fireball[2].x) * 2) + (Fireball[2].Direcao * P2_Fireball_HitBox01x1) * 2;
            int P2hb_HitBox01x2 = ((Fireball[2].x) * 2) + (Fireball[2].Direcao * P2_Fireball_HitBox01x2) * 2;
            int P2hb_HitBox01y1 = (AlturaPiso + (Fireball[2].y * 2) + P2_Fireball_HitBox01y1 * 2);
            int P2hb_HitBox01y2 = (AlturaPiso + (Fireball[2].y * 2) + P2_Fireball_HitBox01y2 * 2);

            //P1_Fireball x P2 HurtBox
            if (P[1].QtdeMagias > 0) {
                temp1x = P1hb_HitBox01x1;
                temp1y = P1hb_HitBox01y1;
                temp2x = P1hb_HitBox01x2;
                temp2y = P1hb_HitBox01y2;
                if (temp1x <= temp2x) {
                    P1hb_HitBox01x1 = temp1x;
                    P1hb_HitBox01x2 = temp2x;
                } else {
                    P1hb_HitBox01x1 = temp2x;
                    P1hb_HitBox01x2 = temp1x;
                }
                if (P1hb_HitBox01x1 < 0) { P1hb_HitBox01x1 = 0; }
                //x1
                if (colisaoxP2 == 0
                    && P1_Fireball_HitBox01x1 != 0 && P1_Fireball_HitBox01y1 != 0
                    && P1_Fireball_HitBox01x2 != 0 && P1_Fireball_HitBox01y2 != 0
                    && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555
                    && P2_HurtBox01x2 != -5555 && P2_HurtBox01y2 != -5555) {
                    temp1x = P2hb_HurtBox01x1;
                    temp1y = P2hb_HurtBox01y1;
                    temp2x = P2hb_HurtBox01x2;
                    temp2y = P2hb_HurtBox01y2;
                    if (temp1x <= temp2x) {
                        P2hb_HurtBox01x1 = temp1x;
                        P2hb_HurtBox01x2 = temp2x;
                    } else {
                        P2hb_HurtBox01x1 = temp2x;
                        P2hb_HurtBox01x2 = temp1x;
                    }
                    if (P2hb_HurtBox01x1 < 0) { P2hb_HurtBox01x1 = 0; }
                    if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox01x1) && (
                            P2hb_HurtBox01x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                        (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox01y1) && (
                            P2hb_HurtBox01y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                        colisaoxP2Fireball = 1;
                        alturadohitp2 = 1;
                    } else {
                        /* nao acertou o P2 */
                    }
                }
            }

            //P2_Fireball x P1 HurtBox
            if (P[2].QtdeMagias > 0) {
                temp1x = P2hb_HitBox01x1;
                temp1y = P2hb_HitBox01y1;
                temp2x = P2hb_HitBox01x2;
                temp2y = P2hb_HitBox01y2;
                if (temp1x <= temp2x) {
                    P2hb_HitBox01x1 = temp1x;
                    P2hb_HitBox01x2 = temp2x;
                } else {
                    P2hb_HitBox01x1 = temp2x;
                    P2hb_HitBox01x2 = temp1x;
                }
                if (P2hb_HitBox01x1 < 0) { P2hb_HitBox01x1 = 0; }
                //x1
                if (colisaoxP1 == 0
                    && P2_Fireball_HitBox01x1 != 0 && P2_Fireball_HitBox01y1 != 0
                    && P2_Fireball_HitBox01x2 != 0 && P2_Fireball_HitBox01y2 != 0
                    && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555
                    && P1_HurtBox01x2 != -5555 && P1_HurtBox01y2 != -5555) {
                    temp1x = P1hb_HurtBox01x1;
                    temp1y = P1hb_HurtBox01y1;
                    temp2x = P1hb_HurtBox01x2;
                    temp2y = P1hb_HurtBox01y2;
                    if (temp1x <= temp2x) {
                        P1hb_HurtBox01x1 = temp1x;
                        P1hb_HurtBox01x2 = temp2x;
                    } else {
                        P1hb_HurtBox01x1 = temp2x;
                        P1hb_HurtBox01x2 = temp1x;
                    }
                    if (P1hb_HurtBox01x1 < 0) { P1hb_HurtBox01x1 = 0; }
                    if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox01x1) && (
                            P1hb_HurtBox01x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                        (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox01y1) && (
                            P1hb_HurtBox01y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                        colisaoxP1Fireball = 1;
                        alturadohitp2 = 1;
                    } else {
                        /* nao acertou o P1 */
                    }
                }
            }

            //som quando a magia acerta
            if (colisaoxP1Fireball == 1) {
                if (ForcaDoGolpeP2 == 1) { play_sample(hitlvl1, 255, 128, 1000, 0); }
                if (ForcaDoGolpeP2 == 2) { play_sample(hitlvl2, 255, 128, 1000, 0); }
                if (ForcaDoGolpeP2 == 3) { play_sample(hitlvl3, 255, 128, 1000, 0); }
            }
            if (colisaoxP2Fireball == 1) {
                if (ForcaDoGolpeP1 == 1) { play_sample(hitlvl1, 255, 128, 1000, 0); }
                if (ForcaDoGolpeP1 == 2) { play_sample(hitlvl2, 255, 128, 1000, 0); }
                if (ForcaDoGolpeP1 == 3) { play_sample(hitlvl3, 255, 128, 1000, 0); }
            }

            //desenha a Fireball na tela (bufferx)
            if (Fireball[ind].Direcao == 1) {
                draw_sprite(
                    bufferx,
                    Fireball[ind].Spr,
                    (Fireball[ind].x*2)-Fireball[ind].XAlign*2,
                    Fireball[ind].y*2-Fireball[ind].YAlign*2
                );
            }
            if (Fireball[ind].Direcao == -1) {
                draw_sprite_h_flip(
                    bufferx,
                    Fireball[ind].Spr,
                    (Fireball[ind].x*2)-Fireball[ind].XAlign*2,
                    Fireball[ind].y*2-Fireball[ind].YAlign*2
                );
            }
            //destruir a fireball caso ela passe os limites da tela
            //esq
            if (Fireball[ind].x < -300) {
                Fireball[ind].Ativa = 0;
                Fireball[ind].x = -999;
                Fireball[ind].y = -999;
                P[ind].QtdeMagias = 0;
            }
            //dir
            if (Fireball[ind].x > bg_test->w + 300) {
                Fireball[ind].Ativa = 0;
                Fireball[ind].x = -999;
                Fireball[ind].y = -999;
                P[ind].QtdeMagias = 0;
            }
            //circlefill (bufferx, Fireball[ind].x*2, Fireball[ind].y*2, 5, makecol(255,000,000)); //debug de posicionamento fireball
        }

        if (Fireball[ind].Ativa == 2) {
            //animacao da fireball /no momento limitada a 10frames! Preciso otimizar o codigo.
            if (Fireball[ind].IndexAnim == 0) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_00) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_01;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 1) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_01) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_02;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 2) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_02) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_03;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 3) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_03) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_04;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 4) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_04) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_05;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 5) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_05) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_05;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 6) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_06) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_06;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 7) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_07) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_07;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 8) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_08) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_08;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            if (Fireball[ind].IndexAnim == 9) {
                if (frame_count > Fireball[ind].StartFrame + P1_Fireball_FrameTime_09) {
                    Fireball[ind].IndexAnim++;
                    P1_Fireball_FrameTime = P1_Fireball_FrameTime_10;
                    Fireball[ind].StartFrame = frame_count;
                }
            }
            //loop
            if (Fireball[ind].IndexAnim > Fireball[ind].TotalFrames) {
                if (Fireball[ind].State == 701) {
                    Fireball[ind].IndexAnim = 0;
                    P1_Fireball_FrameTime = P1_FrameTime_00;
                    Fireball[ind].StartFrame = frame_count;
                }
                if (Fireball[ind].State == 702) { Fireball[ind].Ativa = 0; }
            }
        }
    }

    //desenha / anima hitboxes

    if (Qtde_HitBox > 0) {
        for (int ind = 1; ind <= Qtde_HitBox; ind++) {
            if (HitSpark[ind].IndexAnim == 0) {
                if (frame_count > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) {
                    HitSpark[ind].IndexAnim++;
                    HitSpark[ind].StartFrame = frame_count;
                }
            }
            if (HitSpark[ind].IndexAnim == 1) {
                if (frame_count > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) {
                    HitSpark[ind].IndexAnim++;
                    HitSpark[ind].StartFrame = frame_count;
                }
            }
            if (HitSpark[ind].IndexAnim == 2) {
                if (frame_count > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) {
                    HitSpark[ind].IndexAnim++;
                    HitSpark[ind].StartFrame = frame_count;
                }
            }
            if (HitSpark[ind].IndexAnim == 3) {
                if (frame_count > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) {
                    HitSpark[ind].IndexAnim++;
                    HitSpark[ind].StartFrame = frame_count;
                }
            }
            if (HitSpark[ind].IndexAnim == 4) {
                if (frame_count > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) {
                    HitSpark[ind].IndexAnim++;
                    HitSpark[ind].StartFrame = frame_count;
                }
            }
            if (HitSpark[ind].IndexAnim == 5) {
                if (frame_count > HitSpark[ind].StartFrame + HitSpark[ind].FrameTime) {
                    HitSpark[ind].IndexAnim++;
                    HitSpark[ind].StartFrame = frame_count;
                }
            }
            if (HitSpark[ind].IndexAnim == 6) {
                Qtde_HitBox--;
            }

            clear_to_color(HitSparkspr, makecol(255, 0, 255));
            //clear_to_color(HitSpark_Aux, makecol(255, 0, 255));
            if (HitSpark[ind].Type == 991 && HitSpark[ind].IndexAnim == 0) { HitSpark_Aux = spr991_00; }
            if (HitSpark[ind].Type == 991 && HitSpark[ind].IndexAnim == 1) { HitSpark_Aux = spr991_01; }
            if (HitSpark[ind].Type == 991 && HitSpark[ind].IndexAnim == 2) { HitSpark_Aux = spr991_02; }
            if (HitSpark[ind].Type == 991 && HitSpark[ind].IndexAnim == 3) { HitSpark_Aux = spr991_03; }
            if (HitSpark[ind].Type == 991 && HitSpark[ind].IndexAnim == 4) { HitSpark_Aux = spr991_04; }
            if (HitSpark[ind].Type == 991 && HitSpark[ind].IndexAnim == 5) { HitSpark_Aux = spr991_05; }
            if (HitSpark[ind].Type == 992 && HitSpark[ind].IndexAnim == 0) { HitSpark_Aux = spr992_00; }
            if (HitSpark[ind].Type == 992 && HitSpark[ind].IndexAnim == 1) { HitSpark_Aux = spr992_01; }
            if (HitSpark[ind].Type == 992 && HitSpark[ind].IndexAnim == 2) { HitSpark_Aux = spr992_02; }
            if (HitSpark[ind].Type == 992 && HitSpark[ind].IndexAnim == 3) { HitSpark_Aux = spr992_03; }
            if (HitSpark[ind].Type == 992 && HitSpark[ind].IndexAnim == 4) { HitSpark_Aux = spr992_04; }
            if (HitSpark[ind].Type == 992 && HitSpark[ind].IndexAnim == 5) { HitSpark_Aux = spr992_05; }
            if (HitSpark[ind].Type == 993 && HitSpark[ind].IndexAnim == 0) { HitSpark_Aux = spr993_00; }
            if (HitSpark[ind].Type == 993 && HitSpark[ind].IndexAnim == 1) { HitSpark_Aux = spr993_01; }
            if (HitSpark[ind].Type == 993 && HitSpark[ind].IndexAnim == 2) { HitSpark_Aux = spr993_02; }
            if (HitSpark[ind].Type == 993 && HitSpark[ind].IndexAnim == 3) { HitSpark_Aux = spr993_03; }
            if (HitSpark[ind].Type == 993 && HitSpark[ind].IndexAnim == 4) { HitSpark_Aux = spr993_04; }
            if (HitSpark[ind].Type == 993 && HitSpark[ind].IndexAnim == 5) { HitSpark_Aux = spr993_05; }
            if (HitSpark[ind].Type == 994 && HitSpark[ind].IndexAnim == 0) { HitSpark_Aux = spr994_00; }
            if (HitSpark[ind].Type == 994 && HitSpark[ind].IndexAnim == 1) { HitSpark_Aux = spr994_01; }
            if (HitSpark[ind].Type == 994 && HitSpark[ind].IndexAnim == 2) { HitSpark_Aux = spr994_02; }
            if (HitSpark[ind].Type == 994 && HitSpark[ind].IndexAnim == 3) { HitSpark_Aux = spr994_03; }
            if (HitSpark[ind].Type == 994 && HitSpark[ind].IndexAnim == 4) { HitSpark_Aux = spr994_04; }
            if (HitSpark[ind].Type == 994 && HitSpark[ind].IndexAnim == 5) { HitSpark_Aux = spr994_05; }

            stretch_blit(HitSpark_Aux, HitSparkspr, 0, 0, HitSpark_Aux->w, HitSpark_Aux->h, 0, 0, HitSpark_Aux->w*2,
                         HitSpark_Aux->h*2);
            draw_sprite(bufferx, HitSparkspr, HitSpark[ind].x+HitSpark[ind].XAlign*2,
                        HitSpark[ind].y+HitSpark[ind].YAlign*2);
        }
    }

    if (Draw_Box == 1) {
        //Desenha Caixas
        if (P1_HurtBox01x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox01x1)*2, ((P[1].y*2)+P1_HurtBox01y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox01x2)*2, ((P[1].y*2)+P1_HurtBox01y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox02x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox02x1)*2, ((P[1].y*2)+P1_HurtBox02y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox02x2)*2, ((P[1].y*2)+P1_HurtBox02y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox03x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox03x1)*2, ((P[1].y*2)+P1_HurtBox03y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox03x2)*2, ((P[1].y*2)+P1_HurtBox03y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox04x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox04x1)*2, ((P[1].y*2)+P1_HurtBox04y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox04x2)*2, ((P[1].y*2)+P1_HurtBox04y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox05x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox05x1)*2, ((P[1].y*2)+P1_HurtBox05y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox05x2)*2, ((P[1].y*2)+P1_HurtBox05y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox06x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox06x1)*2, ((P[1].y*2)+P1_HurtBox06y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox06x2)*2, ((P[1].y*2)+P1_HurtBox06y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox07x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox07x1)*2, ((P[1].y*2)+P1_HurtBox07y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox07x2)*2, ((P[1].y*2)+P1_HurtBox07y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox08x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox08x1)*2, ((P[1].y*2)+P1_HurtBox08y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox08x2)*2, ((P[1].y*2)+P1_HurtBox08y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox09x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HurtBox09x1)*2, ((P[1].y*2)+P1_HurtBox09y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HurtBox09x2)*2, ((P[1].y*2)+P1_HurtBox09y2*2), makecol(000,000,255));
        }
        if (P1_HitBox01x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox01x1)*2, ((P[1].y*2)+P1_HitBox01y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox01x2)*2, ((P[1].y*2)+P1_HitBox01y2*2), makecol(255,000,000));
        }
        if (P1_HitBox02x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox02x1)*2, ((P[1].y*2)+P1_HitBox02y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox02x2)*2, ((P[1].y*2)+P1_HitBox02y2*2), makecol(255,000,000));
        }
        if (P1_HitBox03x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox03x1)*2, ((P[1].y*2)+P1_HitBox03y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox03x2)*2, ((P[1].y*2)+P1_HitBox03y2*2), makecol(255,000,000));
        }
        if (P1_HitBox04x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox04x1)*2, ((P[1].y*2)+P1_HitBox04y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox04x2)*2, ((P[1].y*2)+P1_HitBox04y2*2), makecol(255,000,000));
        }
        if (P1_HitBox05x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox05x1)*2, ((P[1].y*2)+P1_HitBox05y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox05x2)*2, ((P[1].y*2)+P1_HitBox05y2*2), makecol(255,000,000));
        }
        if (P1_HitBox06x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox06x1)*2, ((P[1].y*2)+P1_HitBox06y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox06x2)*2, ((P[1].y*2)+P1_HitBox06y2*2), makecol(255,000,000));
        }
        if (P1_HitBox07x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox07x1)*2, ((P[1].y*2)+P1_HitBox07y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox07x2)*2, ((P[1].y*2)+P1_HitBox07y2*2), makecol(255,000,000));
        }
        if (P1_HitBox08x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox08x1)*2, ((P[1].y*2)+P1_HitBox08y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox08x2)*2, ((P[1].y*2)+P1_HitBox08y2*2), makecol(255,000,000));
        }
        if (P1_HitBox09x1 != -5555) {
            rect(bufferx, (P[1].x*2)+(P[1].Lado*P1_HitBox09x1)*2, ((P[1].y*2)+P1_HitBox09y1*2),
                 (P[1].x*2)+(P[1].Lado*P1_HitBox09x2)*2, ((P[1].y*2)+P1_HitBox09y2*2), makecol(255,000,000));
        }

        if (P2_HurtBox01x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox01x1)*2, ((P[2].y*2)+P2_HurtBox01y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox01x2)*2, ((P[2].y*2)+P2_HurtBox01y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox02x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox02x1)*2, ((P[2].y*2)+P2_HurtBox02y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox02x2)*2, ((P[2].y*2)+P2_HurtBox02y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox03x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox03x1)*2, ((P[2].y*2)+P2_HurtBox03y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox03x2)*2, ((P[2].y*2)+P2_HurtBox03y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox04x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox04x1)*2, ((P[2].y*2)+P2_HurtBox04y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox04x2)*2, ((P[2].y*2)+P2_HurtBox04y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox05x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox05x1)*2, ((P[2].y*2)+P2_HurtBox05y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox05x2)*2, ((P[2].y*2)+P2_HurtBox05y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox06x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox06x1)*2, ((P[2].y*2)+P2_HurtBox06y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox06x2)*2, ((P[2].y*2)+P2_HurtBox06y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox07x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox07x1)*2, ((P[2].y*2)+P2_HurtBox07y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox07x2)*2, ((P[2].y*2)+P2_HurtBox07y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox08x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox08x1)*2, ((P[2].y*2)+P2_HurtBox08y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox08x2)*2, ((P[2].y*2)+P2_HurtBox08y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox09x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HurtBox09x1)*2, ((P[2].y*2)+P2_HurtBox09y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HurtBox09x2)*2, ((P[2].y*2)+P2_HurtBox09y2*2), makecol(000,000,255));
        }
        if (P2_HitBox01x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox01x1)*2, ((P[2].y*2)+P2_HitBox01y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox01x2)*2, ((P[2].y*2)+P2_HitBox01y2*2), makecol(255,000,000));
        }
        if (P2_HitBox02x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox02x1)*2, ((P[2].y*2)+P2_HitBox02y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox02x2)*2, ((P[2].y*2)+P2_HitBox02y2*2), makecol(255,000,000));
        }
        if (P2_HitBox03x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox03x1)*2, ((P[2].y*2)+P2_HitBox03y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox03x2)*2, ((P[2].y*2)+P2_HitBox03y2*2), makecol(255,000,000));
        }
        if (P2_HitBox04x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox04x1)*2, ((P[2].y*2)+P2_HitBox04y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox04x2)*2, ((P[2].y*2)+P2_HitBox04y2*2), makecol(255,000,000));
        }
        if (P2_HitBox05x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox05x1)*2, ((P[2].y*2)+P2_HitBox05y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox05x2)*2, ((P[2].y*2)+P2_HitBox05y2*2), makecol(255,000,000));
        }
        if (P2_HitBox06x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox06x1)*2, ((P[2].y*2)+P2_HitBox06y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox06x2)*2, ((P[2].y*2)+P2_HitBox06y2*2), makecol(255,000,000));
        }
        if (P2_HitBox07x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox07x1)*2, ((P[2].y*2)+P2_HitBox07y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox07x2)*2, ((P[2].y*2)+P2_HitBox07y2*2), makecol(255,000,000));
        }
        if (P2_HitBox08x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox08x1)*2, ((P[2].y*2)+P2_HitBox08y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox08x2)*2, ((P[2].y*2)+P2_HitBox08y2*2), makecol(255,000,000));
        }
        if (P2_HitBox09x1 != +5555) {
            rect(bufferx, (P[2].x*2)+(P[2].Lado*P2_HitBox09x1)*2, ((P[2].y*2)+P2_HitBox09y1*2),
                 (P[2].x*2)+(P[2].Lado*P2_HitBox09x2)*2, ((P[2].y*2)+P2_HitBox09y2*2), makecol(255,000,000));
        }
    } //fim Draw_Box

    if (Draw_Box == 1) {
        //desenha caixas com transparencia
        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        set_trans_blender(0, 0, 0, 77);
        //Desenha Caixas
        if (P1_HurtBox01x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x1)*2, ((P[1].y*2)+P1_HurtBox01y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox01x2)*2, ((P[1].y*2)+P1_HurtBox01y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox02x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox02x1)*2, ((P[1].y*2)+P1_HurtBox02y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox02x2)*2, ((P[1].y*2)+P1_HurtBox02y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox03x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox03x1)*2, ((P[1].y*2)+P1_HurtBox03y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox03x2)*2, ((P[1].y*2)+P1_HurtBox03y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox04x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox04x1)*2, ((P[1].y*2)+P1_HurtBox04y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox04x2)*2, ((P[1].y*2)+P1_HurtBox04y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox05x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox05x1)*2, ((P[1].y*2)+P1_HurtBox05y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox05x2)*2, ((P[1].y*2)+P1_HurtBox05y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox06x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox06x1)*2, ((P[1].y*2)+P1_HurtBox06y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox06x2)*2, ((P[1].y*2)+P1_HurtBox06y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox07x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox07x1)*2, ((P[1].y*2)+P1_HurtBox07y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox07x2)*2, ((P[1].y*2)+P1_HurtBox07y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox08x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox08x1)*2, ((P[1].y*2)+P1_HurtBox08y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox08x2)*2, ((P[1].y*2)+P1_HurtBox08y2*2), makecol(000,000,255));
        }
        if (P1_HurtBox09x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HurtBox09x1)*2, ((P[1].y*2)+P1_HurtBox09y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HurtBox09x2)*2, ((P[1].y*2)+P1_HurtBox09y2*2), makecol(000,000,255));
        }
        if (P1_HitBox01x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox01x1)*2, ((P[1].y*2)+P1_HitBox01y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox01x2)*2, ((P[1].y*2)+P1_HitBox01y2*2), makecol(255,000,000));
        }
        if (P1_HitBox02x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox02x1)*2, ((P[1].y*2)+P1_HitBox02y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox02x2)*2, ((P[1].y*2)+P1_HitBox02y2*2), makecol(255,000,000));
        }
        if (P1_HitBox03x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox03x1)*2, ((P[1].y*2)+P1_HitBox03y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox03x2)*2, ((P[1].y*2)+P1_HitBox03y2*2), makecol(255,000,000));
        }
        if (P1_HitBox04x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox04x1)*2, ((P[1].y*2)+P1_HitBox04y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox04x2)*2, ((P[1].y*2)+P1_HitBox04y2*2), makecol(255,000,000));
        }
        if (P1_HitBox05x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox05x1)*2, ((P[1].y*2)+P1_HitBox05y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox05x2)*2, ((P[1].y*2)+P1_HitBox05y2*2), makecol(255,000,000));
        }
        if (P1_HitBox06x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox06x1)*2, ((P[1].y*2)+P1_HitBox06y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox06x2)*2, ((P[1].y*2)+P1_HitBox06y2*2), makecol(255,000,000));
        }
        if (P1_HitBox07x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox07x1)*2, ((P[1].y*2)+P1_HitBox07y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox07x2)*2, ((P[1].y*2)+P1_HitBox07y2*2), makecol(255,000,000));
        }
        if (P1_HitBox08x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox08x1)*2, ((P[1].y*2)+P1_HitBox08y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox08x2)*2, ((P[1].y*2)+P1_HitBox08y2*2), makecol(255,000,000));
        }
        if (P1_HitBox09x1 != -5555) {
            rectfill(bufferx, ((P[1].x)*2)+(P[1].Lado*P1_HitBox09x1)*2, ((P[1].y*2)+P1_HitBox09y1*2),
                     ((P[1].x)*2)+(P[1].Lado*P1_HitBox09x2)*2, ((P[1].y*2)+P1_HitBox09y2*2), makecol(255,000,000));
        }

        if (P2_HurtBox01x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x1)*2, ((P[2].y*2)+P2_HurtBox01y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox01x2)*2, ((P[2].y*2)+P2_HurtBox01y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox02x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox02x1)*2, ((P[2].y*2)+P2_HurtBox02y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox02x2)*2, ((P[2].y*2)+P2_HurtBox02y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox03x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox03x1)*2, ((P[2].y*2)+P2_HurtBox03y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox03x2)*2, ((P[2].y*2)+P2_HurtBox03y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox04x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox04x1)*2, ((P[2].y*2)+P2_HurtBox04y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox04x2)*2, ((P[2].y*2)+P2_HurtBox04y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox05x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox05x1)*2, ((P[2].y*2)+P2_HurtBox05y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox05x2)*2, ((P[2].y*2)+P2_HurtBox05y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox06x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox06x1)*2, ((P[2].y*2)+P2_HurtBox06y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox06x2)*2, ((P[2].y*2)+P2_HurtBox06y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox07x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox07x1)*2, ((P[2].y*2)+P2_HurtBox07y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox07x2)*2, ((P[2].y*2)+P2_HurtBox07y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox08x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox08x1)*2, ((P[2].y*2)+P2_HurtBox08y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox08x2)*2, ((P[2].y*2)+P2_HurtBox08y2*2), makecol(000,000,255));
        }
        if (P2_HurtBox09x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HurtBox09x1)*2, ((P[2].y*2)+P2_HurtBox09y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HurtBox09x2)*2, ((P[2].y*2)+P2_HurtBox09y2*2), makecol(000,000,255));
        }
        if (P2_HitBox01x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox01x1)*2, ((P[2].y*2)+P2_HitBox01y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox01x2)*2, ((P[2].y*2)+P2_HitBox01y2*2), makecol(255,000,000));
        }
        if (P2_HitBox02x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox02x1)*2, ((P[2].y*2)+P2_HitBox02y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox02x2)*2, ((P[2].y*2)+P2_HitBox02y2*2), makecol(255,000,000));
        }
        if (P2_HitBox03x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox03x1)*2, ((P[2].y*2)+P2_HitBox03y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox03x2)*2, ((P[2].y*2)+P2_HitBox03y2*2), makecol(255,000,000));
        }
        if (P2_HitBox04x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox04x1)*2, ((P[2].y*2)+P2_HitBox04y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox04x2)*2, ((P[2].y*2)+P2_HitBox04y2*2), makecol(255,000,000));
        }
        if (P2_HitBox05x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox05x1)*2, ((P[2].y*2)+P2_HitBox05y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox05x2)*2, ((P[2].y*2)+P2_HitBox05y2*2), makecol(255,000,000));
        }
        if (P2_HitBox06x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox06x1)*2, ((P[2].y*2)+P2_HitBox06y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox06x2)*2, ((P[2].y*2)+P2_HitBox06y2*2), makecol(255,000,000));
        }
        if (P2_HitBox07x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox07x1)*2, ((P[2].y*2)+P2_HitBox07y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox07x2)*2, ((P[2].y*2)+P2_HitBox07y2*2), makecol(255,000,000));
        }
        if (P2_HitBox08x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox08x1)*2, ((P[2].y*2)+P2_HitBox08y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox08x2)*2, ((P[2].y*2)+P2_HitBox08y2*2), makecol(255,000,000));
        }
        if (P2_HitBox09x1 != +5555) {
            rectfill(bufferx, ((P[2].x)*2)+(P[2].Lado*P2_HitBox09x1)*2, ((P[2].y*2)+P2_HitBox09y1*2),
                     ((P[2].x)*2)+(P[2].Lado*P2_HitBox09x2)*2, ((P[2].y*2)+P2_HitBox09y2*2), makecol(255,000,000));
        }
        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
    }

    if (Draw_Debug == 1) {
        line(bufferx, 0, AlturaPiso*2, bufferx->w, AlturaPiso*2, makecol(020,020,020));
        circlefill(bufferx, P[1].x*2, P[1].y*2, 3, makecol(000,000,000));
        circlefill(bufferx, P[1].x*2, P[1].y*2, 1, makecol(255,255,255));
        circlefill(bufferx, P[2].x*2, P[2].y*2, 3, makecol(000,000,000));
        circlefill(bufferx, P[2].x*2, P[2].y*2, 1, makecol(255,255,255));
        textprintf_centre_ex(bufferx, font_debug, MeioDaTela * 2 + 1, AlturaPiso * 2 - 20 + 1, makecol(000, 000, 000),
                             -1, "%i", abs(P[1].x - P[2].x));
        textprintf_centre_ex(bufferx, font_debug, MeioDaTela * 2, AlturaPiso * 2 - 20, makecol(255, 255, 255), -1, "%i",
                             abs(P[1].x - P[2].x));
        circlefill(bufferx, MeioDaTela*2, AlturaPiso*2, 3, makecol(255,000,000));
        circlefill(bufferx, MeioDaTela*2, AlturaPiso*2, 1, makecol(255,255,255));
    }

    /*
                // debug de Spark´s
                if(Qtde_HitBox>0){
                textprintf_centre_ex(LayerHUD, font_debug, 320,  50, makecol(255,255,255), -1, "HitSpark[1].x: %i", HitSpark[1].x);
                textprintf_centre_ex(LayerHUD, font_debug, 320,  60, makecol(255,255,255), -1, "HitSpark[1].y: %i", HitSpark[1].y);
                circlefill (bufferx, HitSpark[1].x, HitSpark[1].y, 5, makecol(000,000,255));
                circlefill (bufferx, HitSpark[1].x, HitSpark[1].y, 3, makecol(255,255,255));
                rect(bufferx,
                HitSpark[1].x-HitSpark[1].XAlign*2,
                HitSpark[1].y-HitSpark[1].YAlign*2,
                HitSpark[1].x+HitSpark[1].XAlign*2,
                HitSpark[1].y+HitSpark[1].YAlign*2, 0);
                }
            */

    /////////////////////////////////
    // DESENHA BUFFERX em LAYERHUD //
    /////////////////////////////////

    stretch_blit(bufferx, LayerHUDa, VScreen_x, VScreen_y, VScreen_x2, VScreen_y2, 0, 0, LayerHUDa->w, LayerHUDa->h);
    stretch_blit(bufferx, LayerHUDb, VScreen_x, VScreen_y, VScreen_x2, VScreen_y2, 0, 0, LayerHUDb->w, LayerHUDb->h);

    /////////////////////////////////////////////////////////////////////////////
    // DEBUG --------------------------------------------------------------[**08]
    /////////////////////////////////////////////////////////////////////////////

    // DEBUG DICAS DE CODIGO --------------------------------------------------------------------------------------------------------------------------
    // exibir um numero inteiro -> textprintf_centre_ex(LayerHUDa, font_debug, 320,  50, makecol(255,255,255), -1, "Texto: %i", variavel_int);
    // exibir um texto / string -> textprintf_centre_ex(LayerHUDa, font_debug, 320,  60, makecol(255,255,255), -1, "Texto: %s", variavel_char);
    // exibir caixa de mensagem -> allegro_message("SUA MENSAGEM AQUI!");
    // exibir caixa de mensagem c/ variaveis numero inteiro -> allegro_message("SUA MENSAGEM AQUI! x: %i y: %i", variavelx, variavely);
    //-------------------------------------------------------------------------------------------------------------------------------------------------

    /*
                //DEBUG TABLEATLAS
                //Use as teclas + e - para visualizar a TableAtlas do P1
                if (key[KEY_PLUS_PAD]) { navAtlas++; if(navAtlas>P[1].TotalDeImagensUtilizadas){navAtlas=P[1].TotalDeImagensUtilizadas;} }
                if (key[KEY_MINUS_PAD]) { navAtlas--; if(navAtlas<0) {navAtlas=0;} }
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 0, 0xff0000, -1, "[%i][%i]", P[1].TableAtlas[navAtlas][0], P[1].TableAtlas[navAtlas][1]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 1, 0xffffff, -1, "NUM_IMG: %i",	P[1].TableAtlas[navAtlas][2]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 2, 0xffffff, -1, "Frame_Time: %i",	P[1].TableAtlas[navAtlas][3]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 3, 0xffffff, -1, "XAlign: %i, YAlign: %i",	P[1].TableAtlas[navAtlas][4], P[1].TableAtlas[navAtlas][5]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 4, 0xffffff, -1, "X: %i, Y: %i",	P[1].TableAtlas[navAtlas][6], P[1].TableAtlas[navAtlas][7]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 5, 0xffffff, -1, "VSpeed: %i, HSpeed: %i",	P[1].TableAtlas[navAtlas][8], P[1].TableAtlas[navAtlas][9]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 6, 0xffffff, -1, "Gravity: %i, Friction: %i",	P[1].TableAtlas[navAtlas][10], P[1].TableAtlas[navAtlas][11]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 7, 0xffffff, -1, "EnergyChange: %i, SpecialChange: %i",	P[1].TableAtlas[navAtlas][12], P[1].TableAtlas[navAtlas][13]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 8, 0xffffff, -1, "Visible: %i, RoomLimit: %i",	P[1].TableAtlas[navAtlas][14], P[1].TableAtlas[navAtlas][15]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15* 9, 0xffffff, -1, "HitType: %i, ChangeState: %i",	P[1].TableAtlas[navAtlas][16], P[1].TableAtlas[navAtlas][17]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*10, 0xffffff, -1, "Freeze: %i, Color: %i",	P[1].TableAtlas[navAtlas][18], P[1].TableAtlas[navAtlas][19]);
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*11, 0xffffff, -1, "HitStack: %i",	P[1].TableAtlas[navAtlas][20]);

                if (strcmp (P[1].HitStack,"Multi")==0){	textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*15, 0xffffff, -1, "P[1].HitStack: MULTI");	}
                if (strcmp (P[1].HitStack,"Single")==0){ textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*15, 0xffffff, -1, "P[1].HitStack: SINGLE"); }
                textprintf_centre_ex(LayerHUDa, font_debug, 320, 50+15*17, 0xffffff, -1, "AHitP1: %i", AHitP1);
            */

    //mostra a lista de especiais na tela
    if (Draw_Debug == 1) {
        for (int indp = 1; indp <= 2; indp++) {
            for (int ind2 = 0; ind2 <= 9; ind2++) {
                for (int ind1 = 1; ind1 <= 16; ind1++) {
                    int espacamentox = 20;
                    int espacamentoy = 20;
                    int mxalign = 70;
                    int myalign = 50;
                    int correcao;
                    if (indp == 2) {
                        correcao = 480;
                        espacamentox = espacamentox * -1;
                    } else { correcao = 0; }
                    if (indp == 1) {
                        if (P[indp].Special_Inputs[ind2][ind1] == 8) {
                            draw_sprite(LayerHUDa, spr_input_0, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 9) {
                            draw_sprite(LayerHUDa, spr_input_1, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 6) {
                            draw_sprite(LayerHUDa, spr_input_2, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 3) {
                            draw_sprite(LayerHUDa, spr_input_3, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 2) {
                            draw_sprite(LayerHUDa, spr_input_4, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 1) {
                            draw_sprite(LayerHUDa, spr_input_5, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 4) {
                            draw_sprite(LayerHUDa, spr_input_6, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 7) {
                            draw_sprite(LayerHUDa, spr_input_7, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -1) {
                            draw_sprite(LayerHUDa, spr_input_8, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -2) {
                            draw_sprite(LayerHUDa, spr_input_9, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -3) {
                            draw_sprite(LayerHUDa, spr_input_10, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -4) {
                            draw_sprite(LayerHUDa, spr_input_11, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -5) {
                            draw_sprite(LayerHUDa, spr_input_12, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -6) {
                            draw_sprite(LayerHUDa, spr_input_13, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -7) {
                            draw_sprite(LayerHUDa, spr_input_16, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -8) {
                            draw_sprite(LayerHUDa, spr_input_17, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                    }
                    if (indp == 2) {
                        if (P[indp].Special_Inputs[ind2][ind1] == 8) {
                            draw_sprite(LayerHUDa, spr_input_0, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 7) {
                            draw_sprite(LayerHUDa, spr_input_1, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 4) {
                            draw_sprite(LayerHUDa, spr_input_2, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 1) {
                            draw_sprite(LayerHUDa, spr_input_3, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 2) {
                            draw_sprite(LayerHUDa, spr_input_4, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 3) {
                            draw_sprite(LayerHUDa, spr_input_5, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 6) {
                            draw_sprite(LayerHUDa, spr_input_6, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == 9) {
                            draw_sprite(LayerHUDa, spr_input_7, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -1) {
                            draw_sprite(LayerHUDa, spr_input_8, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -2) {
                            draw_sprite(LayerHUDa, spr_input_9, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -3) {
                            draw_sprite(LayerHUDa, spr_input_10, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -4) {
                            draw_sprite(LayerHUDa, spr_input_11, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -5) {
                            draw_sprite(LayerHUDa, spr_input_12, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -6) {
                            draw_sprite(LayerHUDa, spr_input_13, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -7) {
                            draw_sprite(LayerHUDa, spr_input_16, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                        if (P[indp].Special_Inputs[ind2][ind1] == -8) {
                            draw_sprite(LayerHUDa, spr_input_17, mxalign+ind1*espacamentox+correcao,
                                        myalign+ind2*espacamentoy);
                        }
                    }
                }
            }
        }
    }

    //FrameData//
    if (op_ShowFrameData == 1) {
        //inicializacao
        rectfill(LayerHUDa, 10, 10, 630, 140, makecol(040,040,040)); //fundo
        int FD_P1_MovFramesTot;
        int FD_P2_MovFramesTot;
        //zerar no inicio do round
        if (timer_rounds == 1) {
            FD_P1_MovFramesTot = 0;
            FD_P1_Status = 0;
            FD_P1_Startup = 0;
            FD_P1_Active = 0;
            FD_P1_Recovery = 0;
            FD_P2_MovFramesTot = 0;
            FD_P2_Status = 0;
            FD_P2_Startup = 0;
            FD_P2_Active = 0;
            FD_P2_Recovery = 0;
        }

        if (P[1].MovStartFrame == P[1].StartFrame) {
            //inicializacao P1
            FD_P1_Status; //1=STARTUP, 2=ACTIVE, 3=RECOVERY
            FD_P1_Startup = 0;
            FD_P1_Active = 0;
            FD_P1_Recovery = 0;
            FD_P1_Active_IN = -1;
            FD_P1_Active_OUT = -1;
            FD_P1_HitBox01x1;
            //chbox.ini
            sprintf(P[1].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[1].Name);
            set_config_file(P[1].Caminho_CHBOX);
            //encontra o inicio de Active (active_in)
            for (int ind = 0; ind <= P[1].TotalFrames; ind++) {
                if (P[1].IndexAnim < 10) { sprintf(P[1].State_chs, "%i_0%i", P[1].State, ind); }
                if (P[1].IndexAnim >= 10) { sprintf(P[1].State_chs, "%i_%i", P[1].State, ind); }
                FD_P1_HitBox01x1 = get_config_int(P[1].State_chs, "HitBox01x1", -5555);
                if (FD_P1_HitBox01x1 != -5555) {
                    FD_P1_Active_IN = ind;
                    break;
                }
            }
            //encontra o final de Active (active_out)
            for (int ind = P[1].TotalFrames; ind >= 0; ind--) {
                if (P[1].IndexAnim < 10) { sprintf(P[1].State_chs, "%i_0%i", P[1].State, ind); }
                if (P[1].IndexAnim >= 10) { sprintf(P[1].State_chs, "%i_%i", P[1].State, ind); }
                FD_P1_HitBox01x1 = get_config_int(P[1].State_chs, "HitBox01x1", -5555);
                if (FD_P1_HitBox01x1 != -5555) {
                    FD_P1_Active_OUT = ind;
                    break;
                }
            }
            //char.ini
            sprintf(P[1].Caminho_CHBOX, "data/chars/%s/char.ini", P[1].Name);
            set_config_file(P[1].Caminho_CHBOX);
            //soma todos os frames de Startup usando active_in-1
            for (int ind = 0; ind <= FD_P1_Active_IN - 1; ind++) {
                sprintf(P[1].State_chs, "%i", P[1].State);
                char Index_chs[15];
                int sum;
                if (P[1].IndexAnim < 10) { sprintf(Index_chs, "FrameTime_0%i", ind); }
                if (P[1].IndexAnim >= 10) { sprintf(Index_chs, "FrameTime_%i", ind); }
                sum = get_config_int(P[1].State_chs, Index_chs, 6);
                if (sum != -5555) { FD_P1_Startup += sum; }
            }
            //soma todos os frames de Recovery usando active_out+1
            for (int ind = FD_P1_Active_OUT + 1; ind <= P[1].TotalFrames; ind++) {
                sprintf(P[1].State_chs, "%i", P[1].State);
                char Index_chs[15];
                int sum;
                if (P[1].IndexAnim < 10) { sprintf(Index_chs, "FrameTime_0%i", ind); }
                if (P[1].IndexAnim >= 10) { sprintf(Index_chs, "FrameTime_%i", ind); }
                sum = get_config_int(P[1].State_chs, Index_chs, 6);
                if (sum != -5555) { FD_P1_Recovery += sum; }
            }
            //soma todos os frames de Active usando o intervalo active_in e active_out
            for (int ind = FD_P1_Active_IN; ind <= FD_P1_Active_OUT; ind++) {
                sprintf(P[1].State_chs, "%i", P[1].State);
                char Index_chs[15];
                int sum;
                if (P[1].IndexAnim < 10) { sprintf(Index_chs, "FrameTime_0%i", ind); }
                if (P[1].IndexAnim >= 10) { sprintf(Index_chs, "FrameTime_%i", ind); }
                sum = get_config_int(P[1].State_chs, Index_chs, 6);
                if (sum != -5555) { FD_P1_Active += sum; }
            }
            //soma todos os frames deste Mov
            FD_P1_MovFramesTot = FD_P1_Startup + FD_P1_Active + FD_P1_Recovery;
        }

        //define o status do P1
        if (frame_count - P[1].MovStartFrame < FD_P1_Startup) { FD_P1_Status = 1; }
        if (((frame_count - P[1].MovStartFrame) >= FD_P1_Startup) && (
                (frame_count - P[1].MovStartFrame) < FD_P1_MovFramesTot - FD_P1_Recovery)) { FD_P1_Status = 2; }
        if (frame_count - P[1].MovStartFrame >= FD_P1_MovFramesTot - FD_P1_Recovery) { FD_P1_Status = 3; }
        if (frame_count - P[1].MovStartFrame >= FD_P1_MovFramesTot) {
            FD_P1_Status = 0;
            FD_P1_Startup = 0;
            FD_P1_Active = 0;
            FD_P1_Recovery = 0;
            FD_P1_MovFramesTot = 0;
        }
        //desenha retangulos: Startup P1
        if (FD_P1_Status == 1) {
            for (int ind = 0; ind <= FD_P1_Startup - 1; ind++) {
                if ((frame_count - P[1].MovStartFrame) >= ind) {
                    rectfill(LayerHUDa, 86+ 15*ind, 50, 86+ 15+15*ind, 50+15, makecol(000,255,000)); //verde
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 51, makecol(050, 050, 050), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 51, makecol(050, 050, 050), -1, "%d", ind + 1);
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 50, makecol(255, 255, 255), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 50, makecol(255, 255, 255), -1, "%d", ind + 1);
                }
                rect(LayerHUDa, 86+ 15*ind, 50, 86+ 15+15*ind, 50+15, makecol(255,255,255));
            }
        }
        //desenha retangulos: Active P1
        if (FD_P1_Status == 2) {
            for (int ind = 0; ind <= FD_P1_Active - 1; ind++) {
                if ((frame_count - P[1].MovStartFrame - FD_P1_Startup) >= ind) {
                    rectfill(LayerHUDa, 86+ 15*ind, 50, 86+ 15+15*ind, 50+15, makecol(255,000,000)); //vermelho
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 51, makecol(050, 050, 050), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 51, makecol(050, 050, 050), -1, "%d", ind + 1);
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 50, makecol(255, 255, 255), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 50, makecol(255, 255, 255), -1, "%d", ind + 1);
                }
                rect(LayerHUDa, 86+ 15*ind, 50, 86+ 15+15*ind, 50+15, makecol(255,255,255));
            }
        }
        //desenha retangulos: Recovery P1
        if (FD_P1_Status == 3) {
            for (int ind = 0; ind <= FD_P1_Recovery - 1; ind++) {
                if ((frame_count - P[1].MovStartFrame - FD_P1_Startup - FD_P1_Active) >= ind) {
                    rectfill(LayerHUDa, 86+ 15*ind, 50, 86+ 15+15*ind, 50+15, makecol(255,255,000)); //amarelo
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 51, makecol(050, 050, 050), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 51, makecol(050, 050, 050), -1, "%d", ind + 1);
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 50, makecol(255, 255, 255), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 50, makecol(255, 255, 255), -1, "%d", ind + 1);
                }
                rect(LayerHUDa, 86+ 15*ind, 50, 86+ 15+15*ind, 50+15, makecol(255,255,255));
            }
        }

        if (P[2].MovStartFrame == P[2].StartFrame) {
            //inicializacao P2
            FD_P2_Status; //1=STARTUP, 2=ACTIVE, 3=RECOVERY
            FD_P2_Startup = 0;
            FD_P2_Active = 0;
            FD_P2_Recovery = 0;
            FD_P2_Active_IN = -1;
            FD_P2_Active_OUT = -1;
            FD_P2_HitBox01x1;
            //chbox.ini
            sprintf(P[2].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[2].Name);
            set_config_file(P[2].Caminho_CHBOX);
            //encontra o inicio de Active (active_in)
            for (int ind = 0; ind <= P[2].TotalFrames; ind++) {
                if (P[2].IndexAnim < 10) { sprintf(P[2].State_chs, "%i_0%i", P[2].State, ind); }
                if (P[2].IndexAnim >= 10) { sprintf(P[2].State_chs, "%i_%i", P[2].State, ind); }
                FD_P2_HitBox01x1 = get_config_int(P[2].State_chs, "HitBox01x1", -5555);
                if (FD_P2_HitBox01x1 != -5555) {
                    FD_P2_Active_IN = ind;
                    break;
                }
            }
            //encontra o final de Active (active_out)
            for (int ind = P[2].TotalFrames; ind >= 0; ind--) {
                if (P[2].IndexAnim < 10) { sprintf(P[2].State_chs, "%i_0%i", P[2].State, ind); }
                if (P[2].IndexAnim >= 10) { sprintf(P[2].State_chs, "%i_%i", P[2].State, ind); }
                FD_P2_HitBox01x1 = get_config_int(P[2].State_chs, "HitBox01x1", -5555);
                if (FD_P2_HitBox01x1 != -5555) {
                    FD_P2_Active_OUT = ind;
                    break;
                }
            }
            //char.ini
            sprintf(P[2].Caminho_CHBOX, "data/chars/%s/char.ini", P[2].Name);
            set_config_file(P[2].Caminho_CHBOX);
            //soma todos os frames de Startup usando active_in-1
            for (int ind = 0; ind <= FD_P2_Active_IN - 1; ind++) {
                sprintf(P[2].State_chs, "%i", P[2].State);
                char Index_chs[15];
                int sum;
                if (P[2].IndexAnim < 10) { sprintf(Index_chs, "FrameTime_0%i", ind); }
                if (P[2].IndexAnim >= 10) { sprintf(Index_chs, "FrameTime_%i", ind); }
                sum = get_config_int(P[2].State_chs, Index_chs, 6);
                if (sum != -5555) { FD_P2_Startup += sum; }
            }
            //soma todos os frames de Recovery usando active_out+1
            for (int ind = FD_P2_Active_OUT + 1; ind <= P[2].TotalFrames; ind++) {
                sprintf(P[2].State_chs, "%i", P[2].State);
                char Index_chs[15];
                int sum;
                if (P[2].IndexAnim < 10) { sprintf(Index_chs, "FrameTime_0%i", ind); }
                if (P[2].IndexAnim >= 10) { sprintf(Index_chs, "FrameTime_%i", ind); }
                sum = get_config_int(P[2].State_chs, Index_chs, 6);
                if (sum != -5555) { FD_P2_Recovery += sum; }
            }
            //soma todos os frames de Active usando o intervalo active_in e active_out
            for (int ind = FD_P2_Active_IN; ind <= FD_P2_Active_OUT; ind++) {
                sprintf(P[2].State_chs, "%i", P[2].State);
                char Index_chs[15];
                int sum;
                if (P[2].IndexAnim < 10) { sprintf(Index_chs, "FrameTime_0%i", ind); }
                if (P[2].IndexAnim >= 10) { sprintf(Index_chs, "FrameTime_%i", ind); }
                sum = get_config_int(P[2].State_chs, Index_chs, 6);
                if (sum != -5555) { FD_P2_Active += sum; }
            }
            //soma todos os frames deste Mov
            FD_P2_MovFramesTot = FD_P2_Startup + FD_P2_Active + FD_P2_Recovery;
        }

        //define o status do P2
        if (frame_count - P[2].MovStartFrame < FD_P2_Startup) { FD_P2_Status = 1; }
        if (((frame_count - P[2].MovStartFrame) >= FD_P2_Startup) && (
                (frame_count - P[2].MovStartFrame) < FD_P2_MovFramesTot - FD_P2_Recovery)) { FD_P2_Status = 2; }
        if (frame_count - P[2].MovStartFrame >= FD_P2_MovFramesTot - FD_P2_Recovery) { FD_P2_Status = 3; }
        if (frame_count - P[2].MovStartFrame >= FD_P2_MovFramesTot) {
            FD_P2_Status = 0;
            FD_P2_Startup = 0;
            FD_P2_Active = 0;
            FD_P2_Recovery = 0;
            FD_P2_MovFramesTot = 0;
        }
        //desenha retangulos: Startup P2
        if (FD_P2_Status == 1) {
            for (int ind = 0; ind <= FD_P2_Startup - 1; ind++) {
                if ((frame_count - P[2].MovStartFrame) >= ind) {
                    rectfill(LayerHUDa, 86+ 15*ind, 65, 86+ 15+15*ind, 65+15, makecol(000,255,000)); //verde
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 66, makecol(050, 050, 050), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 66, makecol(050, 050, 050), -1, "%d", ind + 1);
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 65, makecol(255, 255, 255), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 65, makecol(255, 255, 255), -1, "%d", ind + 1);
                }
                rect(LayerHUDa, 86+ 15*ind, 65, 86+ 15+15*ind, 65+15, makecol(255,255,255));
            }
        }
        //desenha retangulos: Active P2
        if (FD_P2_Status == 2) {
            for (int ind = 0; ind <= FD_P2_Active - 1; ind++) {
                if ((frame_count - P[2].MovStartFrame - FD_P2_Startup) >= ind) {
                    rectfill(LayerHUDa, 86+ 15*ind, 65, 86+ 15+15*ind, 65+15, makecol(255,000,000)); //vermelho
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 66, makecol(050, 050, 050), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 66, makecol(050, 050, 050), -1, "%d", ind + 1);
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 65, makecol(255, 255, 255), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 65, makecol(255, 255, 255), -1, "%d", ind + 1);
                }
                rect(LayerHUDa, 86+ 15*ind, 65, 86+ 15+15*ind, 65+15, makecol(255,255,255));
            }
        }
        //desenha retangulos: Recovery P2
        if (FD_P2_Status == 3) {
            for (int ind = 0; ind <= FD_P2_Recovery - 1; ind++) {
                if ((frame_count - P[2].MovStartFrame - FD_P2_Startup - FD_P2_Active) >= ind) {
                    rectfill(LayerHUDa, 86+ 15*ind, 65, 86+ 15+15*ind, 65+15, makecol(255,255,000)); //amarelo
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 66, makecol(050, 050, 050), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 88 + ind * 15, 66, makecol(050, 050, 050), -1, "%d", ind + 1);
                }
                if (ind < 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 65, makecol(255, 255, 255), -1, "0%d", ind + 1);
                }
                if (ind >= 9) {
                    textprintf_ex(LayerHUDa, font_10, 87 + ind * 15, 65, makecol(255, 255, 255), -1, "%d", ind + 1);
                }
                rect(LayerHUDa, 86+ 15*ind, 65, 86+ 15+15*ind, 65+15, makecol(255,255,255));
            }
        }

        //desenha moldura grande
        for (int ind = 0; ind <= 30; ind++) {
            rect(LayerHUDa, 86+ 15*ind, 50, 86+ 15+15*ind, 50+15, makecol(255,255,255));
            rect(LayerHUDa, 86+ 15*ind, 65, 86+ 15+15*ind, 65+15, makecol(255,255,255));
        }

        //exibe o status
        //txt sombra P1
        if (FD_P1_Status == 0) { textprintf_ex(LayerHUDa, font_10, 88, 81, makecol(0, 0, 0), -1, "P1 STATUS: ---"); }
        if (FD_P1_Status == 1) {
            textprintf_ex(LayerHUDa, font_10, 88, 81, makecol(0, 0, 0), -1, "P1 STATUS: STARTUP");
        }
        if (FD_P1_Status == 2) { textprintf_ex(LayerHUDa, font_10, 88, 81, makecol(0, 0, 0), -1, "P1 STATUS: ACTIVE"); }
        if (FD_P1_Status == 3) {
            textprintf_ex(LayerHUDa, font_10, 88, 81, makecol(0, 0, 0), -1, "P1 STATUS: RECOVERY");
        }
        textprintf_ex(LayerHUDa, font_10, 88, 91, makecol(0, 0, 0), -1, "P1_Startup: %d", FD_P1_Startup);
        textprintf_ex(LayerHUDa, font_10, 88, 101, makecol(0, 0, 0), -1, "P1_Active: %d", FD_P1_Active);
        textprintf_ex(LayerHUDa, font_10, 88, 111, makecol(0, 0, 0), -1, "P1_Recovery: %d", FD_P1_Recovery);
        textprintf_ex(LayerHUDa, font_10, 88, 121, makecol(0, 0, 0), -1, "P1_FramesTot: %d", FD_P1_MovFramesTot);
        //txt P1
        if (FD_P1_Status == 0) {
            textprintf_ex(LayerHUDa, font_10, 87, 80, makecol(255, 255, 255), -1, "P1 STATUS: ---");
        }
        if (FD_P1_Status == 1) {
            textprintf_ex(LayerHUDa, font_10, 87, 80, makecol(255, 255, 255), -1, "P1 STATUS: STARTUP");
        }
        if (FD_P1_Status == 2) {
            textprintf_ex(LayerHUDa, font_10, 87, 80, makecol(255, 255, 255), -1, "P1 STATUS: ACTIVE");
        }
        if (FD_P1_Status == 3) {
            textprintf_ex(LayerHUDa, font_10, 87, 80, makecol(255, 255, 255), -1, "P1 STATUS: RECOVERY");
        }
        textprintf_ex(LayerHUDa, font_10, 87, 90, makecol(255, 255, 255), -1, "P1_Startup: %d", FD_P1_Startup);
        textprintf_ex(LayerHUDa, font_10, 87, 100, makecol(255, 255, 255), -1, "P1_Active: %d", FD_P1_Active);
        textprintf_ex(LayerHUDa, font_10, 87, 110, makecol(255, 255, 255), -1, "P1_Recovery: %d", FD_P1_Recovery);
        textprintf_ex(LayerHUDa, font_10, 87, 120, makecol(255, 255, 255), -1, "P1_FramesTot: %d", FD_P1_MovFramesTot);
        //txt sombra P2
        if (FD_P2_Status == 0) { textprintf_ex(LayerHUDa, font_10, 448, 81, makecol(0, 0, 0), -1, "P2 STATUS: ---"); }
        if (FD_P2_Status == 1) {
            textprintf_ex(LayerHUDa, font_10, 448, 81, makecol(0, 0, 0), -1, "P2 STATUS: STARTUP");
        }
        if (FD_P2_Status == 2) {
            textprintf_ex(LayerHUDa, font_10, 448, 81, makecol(0, 0, 0), -1, "P2 STATUS: ACTIVE");
        }
        if (FD_P2_Status == 3) {
            textprintf_ex(LayerHUDa, font_10, 448, 81, makecol(0, 0, 0), -1, "P2 STATUS: RECOVERY");
        }
        textprintf_ex(LayerHUDa, font_10, 448, 91, makecol(0, 0, 0), -1, "P2_Startup: %d", FD_P2_Startup);
        textprintf_ex(LayerHUDa, font_10, 448, 101, makecol(0, 0, 0), -1, "P2_Active: %d", FD_P2_Active);
        textprintf_ex(LayerHUDa, font_10, 448, 111, makecol(0, 0, 0), -1, "P2_Recovery: %d", FD_P2_Recovery);
        textprintf_ex(LayerHUDa, font_10, 448, 121, makecol(0, 0, 0), -1, "P2_FramesTot: %d", FD_P2_MovFramesTot);
        //txt P2
        if (FD_P2_Status == 0) {
            textprintf_ex(LayerHUDa, font_10, 447, 80, makecol(255, 255, 255), -1, "P2 STATUS: ---");
        }
        if (FD_P2_Status == 1) {
            textprintf_ex(LayerHUDa, font_10, 447, 80, makecol(255, 255, 255), -1, "P2 STATUS: STARTUP");
        }
        if (FD_P2_Status == 2) {
            textprintf_ex(LayerHUDa, font_10, 447, 80, makecol(255, 255, 255), -1, "P2 STATUS: ACTIVE");
        }
        if (FD_P2_Status == 3) {
            textprintf_ex(LayerHUDa, font_10, 447, 80, makecol(255, 255, 255), -1, "P2 STATUS: RECOVERY");
        }
        textprintf_ex(LayerHUDa, font_10, 447, 90, makecol(255, 255, 255), -1, "P2_Startup: %d", FD_P2_Startup);
        textprintf_ex(LayerHUDa, font_10, 447, 100, makecol(255, 255, 255), -1, "P2_Active: %d", FD_P2_Active);
        textprintf_ex(LayerHUDa, font_10, 447, 110, makecol(255, 255, 255), -1, "P2_Recovery: %d", FD_P2_Recovery);
        textprintf_ex(LayerHUDa, font_10, 447, 120, makecol(255, 255, 255), -1, "P2_FramesTot: %d", FD_P2_MovFramesTot);
    } //<-end ShowFrameData

    //Nomes dos Personagens ingame
    textprintf_ex(LayerHUDa, font_debug, 49, 26, makecol(000, 000, 000), -1, "%s", P[1].Name_Display);
    textprintf_right_ex(LayerHUDa, font_debug, 593, 26, makecol(000, 000, 000), -1, "%s", P[2].Name_Display);
    textprintf_ex(LayerHUDa, font_debug, 47, 24, makecol(000, 000, 000), -1, "%s", P[1].Name_Display);
    textprintf_right_ex(LayerHUDa, font_debug, 591, 24, makecol(000, 000, 000), -1, "%s", P[2].Name_Display);
    textprintf_ex(LayerHUDa, font_debug, 47, 26, makecol(000, 000, 000), -1, "%s", P[1].Name_Display);
    textprintf_right_ex(LayerHUDa, font_debug, 591, 26, makecol(000, 000, 000), -1, "%s", P[2].Name_Display);
    textprintf_ex(LayerHUDa, font_debug, 49, 24, makecol(000, 000, 000), -1, "%s", P[1].Name_Display);
    textprintf_right_ex(LayerHUDa, font_debug, 593, 24, makecol(000, 000, 000), -1, "%s", P[2].Name_Display);
    textprintf_ex(LayerHUDa, font_debug, 48, 25, makecol(255, 255, 255), -1, "%s", P[1].Name_Display);
    textprintf_right_ex(LayerHUDa, font_debug, 592, 25, makecol(255, 255, 255), -1, "%s", P[2].Name_Display);

    if (Draw_Input == 1) {
        //INPUT SLOTS sombra
        if (P[1].bt_slot[1] > 0 || P[1].slot[1] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 71 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[1],
                                P[1].slot[1], P[1].bt_slot[1]);
        }
        if (P[1].bt_slot[2] > 0 || P[1].slot[2] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 91 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[2],
                                P[1].slot[2], P[1].bt_slot[2]);
        }
        if (P[1].bt_slot[3] > 0 || P[1].slot[3] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 111 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[3],
                                P[1].slot[3], P[1].bt_slot[3]);
        }
        if (P[1].bt_slot[4] > 0 || P[1].slot[4] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 131 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[4],
                                P[1].slot[4], P[1].bt_slot[4]);
        }
        if (P[1].bt_slot[5] > 0 || P[1].slot[5] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 151 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[5],
                                P[1].slot[5], P[1].bt_slot[5]);
        }
        if (P[1].bt_slot[6] > 0 || P[1].slot[6] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 171 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[6],
                                P[1].slot[6], P[1].bt_slot[6]);
        }
        if (P[1].bt_slot[7] > 0 || P[1].slot[7] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 191 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[7],
                                P[1].slot[7], P[1].bt_slot[7]);
        }
        if (P[1].bt_slot[8] > 0 || P[1].slot[8] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 211 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[8],
                                P[1].slot[8], P[1].bt_slot[8]);
        }
        if (P[1].bt_slot[9] > 0 || P[1].slot[9] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 231 + 20, makecol(000, 000, 000), -1, "[%i]", P[1].t_slot[9],
                                P[1].slot[9], P[1].bt_slot[9]);
        }
        if (P[1].bt_slot[10] > 0 || P[1].slot[10] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 251 + 20, makecol(000, 000, 000), -1, "[%i]",
                                P[1].t_slot[10], P[1].slot[10], P[1].bt_slot[10]);
        }
        if (P[1].bt_slot[11] > 0 || P[1].slot[11] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 271 + 20, makecol(000, 000, 000), -1, "[%i]",
                                P[1].t_slot[11], P[1].slot[11], P[1].bt_slot[11]);
        }
        if (P[1].bt_slot[12] > 0 || P[1].slot[12] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 291 + 20, makecol(000, 000, 000), -1, "[%i]",
                                P[1].t_slot[12], P[1].slot[12], P[1].bt_slot[12]);
        }
        if (P[1].bt_slot[13] > 0 || P[1].slot[13] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 311 + 20, makecol(000, 000, 000), -1, "[%i]",
                                P[1].t_slot[13], P[1].slot[13], P[1].bt_slot[13]);
        }
        if (P[1].bt_slot[14] > 0 || P[1].slot[14] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 331 + 20, makecol(000, 000, 000), -1, "[%i]",
                                P[1].t_slot[14], P[1].slot[14], P[1].bt_slot[14]);
        }
        if (P[1].bt_slot[15] > 0 || P[1].slot[15] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 351 + 20, makecol(000, 000, 000), -1, "[%i]",
                                P[1].t_slot[15], P[1].slot[15], P[1].bt_slot[15]);
        }
        if (P[1].bt_slot[16] > 0 || P[1].slot[16] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 38, 371 + 20, makecol(000, 000, 000), -1, "[%i]",
                                P[1].t_slot[16], P[1].slot[16], P[1].bt_slot[16]);
        }
        //INPUT SLOTS
        if (P[1].bt_slot[1] > 0 || P[1].slot[1] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 70 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[1],
                                P[1].slot[1], P[1].bt_slot[1]);
        }
        if (P[1].bt_slot[2] > 0 || P[1].slot[2] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 90 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[2],
                                P[1].slot[2], P[1].bt_slot[2]);
        }
        if (P[1].bt_slot[3] > 0 || P[1].slot[3] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 110 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[3],
                                P[1].slot[3], P[1].bt_slot[3]);
        }
        if (P[1].bt_slot[4] > 0 || P[1].slot[4] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 130 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[4],
                                P[1].slot[4], P[1].bt_slot[4]);
        }
        if (P[1].bt_slot[5] > 0 || P[1].slot[5] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 150 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[5],
                                P[1].slot[5], P[1].bt_slot[5]);
        }
        if (P[1].bt_slot[6] > 0 || P[1].slot[6] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 170 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[6],
                                P[1].slot[6], P[1].bt_slot[6]);
        }
        if (P[1].bt_slot[7] > 0 || P[1].slot[7] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 190 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[7],
                                P[1].slot[7], P[1].bt_slot[7]);
        }
        if (P[1].bt_slot[8] > 0 || P[1].slot[8] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 210 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[8],
                                P[1].slot[8], P[1].bt_slot[8]);
        }
        if (P[1].bt_slot[9] > 0 || P[1].slot[9] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 230 + 20, makecol(255, 255, 255), -1, "[%i]", P[1].t_slot[9],
                                P[1].slot[9], P[1].bt_slot[9]);
        }
        if (P[1].bt_slot[10] > 0 || P[1].slot[10] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 250 + 20, makecol(255, 255, 255), -1, "[%i]",
                                P[1].t_slot[10], P[1].slot[10], P[1].bt_slot[10]);
        }
        if (P[1].bt_slot[11] > 0 || P[1].slot[11] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 270 + 20, makecol(255, 255, 255), -1, "[%i]",
                                P[1].t_slot[11], P[1].slot[11], P[1].bt_slot[11]);
        }
        if (P[1].bt_slot[12] > 0 || P[1].slot[12] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 290 + 20, makecol(255, 255, 255), -1, "[%i]",
                                P[1].t_slot[12], P[1].slot[12], P[1].bt_slot[12]);
        }
        if (P[1].bt_slot[13] > 0 || P[1].slot[13] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 310 + 20, makecol(255, 255, 255), -1, "[%i]",
                                P[1].t_slot[13], P[1].slot[13], P[1].bt_slot[13]);
        }
        if (P[1].bt_slot[14] > 0 || P[1].slot[14] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 330 + 20, makecol(255, 255, 255), -1, "[%i]",
                                P[1].t_slot[14], P[1].slot[14], P[1].bt_slot[14]);
        }
        if (P[1].bt_slot[15] > 0 || P[1].slot[15] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 350 + 20, makecol(255, 255, 255), -1, "[%i]",
                                P[1].t_slot[15], P[1].slot[15], P[1].bt_slot[15]);
        }
        if (P[1].bt_slot[16] > 0 || P[1].slot[16] > 0) {
            textprintf_right_ex(LayerHUDa, font_debug, 37, 370 + 20, makecol(255, 255, 255), -1, "[%i]",
                                P[1].t_slot[16], P[1].slot[16], P[1].bt_slot[16]);
        }

        for (int i = 0; i <= 16; i++) {
            //Desenha slots usando sprites
            if (P[1].slot[i] == 8) { draw_sprite(LayerHUDa, spr_input_0, 40, 50+i*20+20); }
            if (P[1].slot[i] == 9) { draw_sprite(LayerHUDa, spr_input_1, 40, 50+i*20+20); }
            if (P[1].slot[i] == 6) { draw_sprite(LayerHUDa, spr_input_2, 40, 50+i*20+20); }
            if (P[1].slot[i] == 3) { draw_sprite(LayerHUDa, spr_input_3, 40, 50+i*20+20); }
            if (P[1].slot[i] == 2) { draw_sprite(LayerHUDa, spr_input_4, 40, 50+i*20+20); }
            if (P[1].slot[i] == 1) { draw_sprite(LayerHUDa, spr_input_5, 40, 50+i*20+20); }
            if (P[1].slot[i] == 4) { draw_sprite(LayerHUDa, spr_input_6, 40, 50+i*20+20); }
            if (P[1].slot[i] == 7) { draw_sprite(LayerHUDa, spr_input_7, 40, 50+i*20+20); }
            int a = P[1].bt_slot[i] % 10;
            int b = ((P[1].bt_slot[i] / 10) % 10) % 10;
            int c = ((((P[1].bt_slot[i] / 10) / 10) % 10) % 10) % 10;
            if (a != 0 || b != 0 || c != 0) {
                while (a == 0) {
                    a = b;
                    b = c;
                }
            }
            if (a == b && b == c) {
                b = 0;
                c = 0;
            }
            if (b == c) { c = 0; }
            if (a == 1) { draw_sprite(LayerHUDa, spr_input_8, 60+0*20, 50+i*20+20); }
            if (a == 2) { draw_sprite(LayerHUDa, spr_input_9, 60+0*20, 50+i*20+20); }
            if (a == 3) { draw_sprite(LayerHUDa, spr_input_10, 60+0*20, 50+i*20+20); }
            if (a == 4) { draw_sprite(LayerHUDa, spr_input_11, 60+0*20, 50+i*20+20); }
            if (a == 5) { draw_sprite(LayerHUDa, spr_input_12, 60+0*20, 50+i*20+20); }
            if (a == 6) { draw_sprite(LayerHUDa, spr_input_13, 60+0*20, 50+i*20+20); }
            if (a == 7) { draw_sprite(LayerHUDa, spr_input_14, 60+0*20, 50+i*20+20); }
            if (a == 8) { draw_sprite(LayerHUDa, spr_input_15, 60+0*20, 50+i*20+20); }
            if (b == 1) { draw_sprite(LayerHUDa, spr_input_8, 60+1*20, 50+i*20+20); }
            if (b == 2) { draw_sprite(LayerHUDa, spr_input_9, 60+1*20, 50+i*20+20); }
            if (b == 3) { draw_sprite(LayerHUDa, spr_input_10, 60+1*20, 50+i*20+20); }
            if (b == 4) { draw_sprite(LayerHUDa, spr_input_11, 60+1*20, 50+i*20+20); }
            if (b == 5) { draw_sprite(LayerHUDa, spr_input_12, 60+1*20, 50+i*20+20); }
            if (b == 6) { draw_sprite(LayerHUDa, spr_input_13, 60+1*20, 50+i*20+20); }
            if (b == 7) { draw_sprite(LayerHUDa, spr_input_14, 60+1*20, 50+i*20+20); }
            if (b == 8) { draw_sprite(LayerHUDa, spr_input_15, 60+1*20, 50+i*20+20); }
            if (c == 1) { draw_sprite(LayerHUDa, spr_input_8, 60+2*20, 50+i*20+20); }
            if (c == 2) { draw_sprite(LayerHUDa, spr_input_9, 60+2*20, 50+i*20+20); }
            if (c == 3) { draw_sprite(LayerHUDa, spr_input_10, 60+2*20, 50+i*20+20); }
            if (c == 4) { draw_sprite(LayerHUDa, spr_input_11, 60+2*20, 50+i*20+20); }
            if (c == 5) { draw_sprite(LayerHUDa, spr_input_12, 60+2*20, 50+i*20+20); }
            if (c == 6) { draw_sprite(LayerHUDa, spr_input_13, 60+2*20, 50+i*20+20); }
            if (c == 7) { draw_sprite(LayerHUDa, spr_input_14, 60+2*20, 50+i*20+20); }
            if (c == 8) { draw_sprite(LayerHUDa, spr_input_15, 60+2*20, 50+i*20+20); }
        }

        //INPUT SLOTS P2 sombra
        if (P[2].bt_slot[1] > 0 || P[2].slot[1] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 71 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[1],
                          P[2].slot[1], P[2].bt_slot[1]);
        }
        if (P[2].bt_slot[2] > 0 || P[2].slot[2] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 91 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[2],
                          P[2].slot[2], P[2].bt_slot[2]);
        }
        if (P[2].bt_slot[3] > 0 || P[2].slot[3] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 111 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[3],
                          P[2].slot[3], P[2].bt_slot[3]);
        }
        if (P[2].bt_slot[4] > 0 || P[2].slot[4] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 131 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[4],
                          P[2].slot[4], P[2].bt_slot[4]);
        }
        if (P[2].bt_slot[5] > 0 || P[2].slot[5] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 151 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[5],
                          P[2].slot[5], P[2].bt_slot[5]);
        }
        if (P[2].bt_slot[6] > 0 || P[2].slot[6] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 171 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[6],
                          P[2].slot[6], P[2].bt_slot[6]);
        }
        if (P[2].bt_slot[7] > 0 || P[2].slot[7] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 191 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[7],
                          P[2].slot[7], P[2].bt_slot[7]);
        }
        if (P[2].bt_slot[8] > 0 || P[2].slot[8] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 211 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[8],
                          P[2].slot[8], P[2].bt_slot[8]);
        }
        if (P[2].bt_slot[9] > 0 || P[2].slot[9] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 231 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[9],
                          P[2].slot[9], P[2].bt_slot[9]);
        }
        if (P[2].bt_slot[10] > 0 || P[2].slot[10] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 251 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[10],
                          P[2].slot[10], P[2].bt_slot[10]);
        }
        if (P[2].bt_slot[11] > 0 || P[2].slot[11] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 271 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[11],
                          P[2].slot[11], P[2].bt_slot[11]);
        }
        if (P[2].bt_slot[12] > 0 || P[2].slot[12] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 291 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[12],
                          P[2].slot[12], P[2].bt_slot[12]);
        }
        if (P[2].bt_slot[13] > 0 || P[2].slot[13] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 311 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[13],
                          P[2].slot[13], P[2].bt_slot[13]);
        }
        if (P[2].bt_slot[14] > 0 || P[2].slot[14] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 331 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[14],
                          P[2].slot[14], P[2].bt_slot[14]);
        }
        if (P[2].bt_slot[15] > 0 || P[2].slot[15] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 351 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[15],
                          P[2].slot[15], P[2].bt_slot[15]);
        }
        if (P[2].bt_slot[16] > 0 || P[2].slot[16] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 603, 371 + 20, makecol(000, 000, 000), -1, "[%i]", P[2].t_slot[16],
                          P[2].slot[16], P[2].bt_slot[16]);
        }
        //INPUT SLOTS P2
        if (P[2].bt_slot[1] > 0 || P[2].slot[1] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 70 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[1],
                          P[2].slot[1], P[2].bt_slot[1]);
        }
        if (P[2].bt_slot[2] > 0 || P[2].slot[2] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 90 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[2],
                          P[2].slot[2], P[2].bt_slot[2]);
        }
        if (P[2].bt_slot[3] > 0 || P[2].slot[3] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 110 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[3],
                          P[2].slot[3], P[2].bt_slot[3]);
        }
        if (P[2].bt_slot[4] > 0 || P[2].slot[4] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 130 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[4],
                          P[2].slot[4], P[2].bt_slot[4]);
        }
        if (P[2].bt_slot[5] > 0 || P[2].slot[5] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 150 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[5],
                          P[2].slot[5], P[2].bt_slot[5]);
        }
        if (P[2].bt_slot[6] > 0 || P[2].slot[6] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 170 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[6],
                          P[2].slot[6], P[2].bt_slot[6]);
        }
        if (P[2].bt_slot[7] > 0 || P[2].slot[7] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 190 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[7],
                          P[2].slot[7], P[2].bt_slot[7]);
        }
        if (P[2].bt_slot[8] > 0 || P[2].slot[8] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 210 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[8],
                          P[2].slot[8], P[2].bt_slot[8]);
        }
        if (P[2].bt_slot[9] > 0 || P[2].slot[9] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 230 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[9],
                          P[2].slot[9], P[2].bt_slot[9]);
        }
        if (P[2].bt_slot[10] > 0 || P[2].slot[10] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 250 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[10],
                          P[2].slot[10], P[2].bt_slot[10]);
        }
        if (P[2].bt_slot[11] > 0 || P[2].slot[11] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 270 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[11],
                          P[2].slot[11], P[2].bt_slot[11]);
        }
        if (P[2].bt_slot[12] > 0 || P[2].slot[12] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 290 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[12],
                          P[2].slot[12], P[2].bt_slot[12]);
        }
        if (P[2].bt_slot[13] > 0 || P[2].slot[13] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 310 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[13],
                          P[2].slot[13], P[2].bt_slot[13]);
        }
        if (P[2].bt_slot[14] > 0 || P[2].slot[14] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 330 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[14],
                          P[2].slot[14], P[2].bt_slot[14]);
        }
        if (P[2].bt_slot[15] > 0 || P[2].slot[15] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 350 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[15],
                          P[2].slot[15], P[2].bt_slot[15]);
        }
        if (P[2].bt_slot[16] > 0 || P[2].slot[16] > 0) {
            textprintf_ex(LayerHUDa, font_debug, 602, 370 + 20, makecol(255, 255, 255), -1, "[%i]", P[2].t_slot[16],
                          P[2].slot[16], P[2].bt_slot[16]);
        }

        for (int i = 0; i <= 16; i++) {
            //Desenha slots usando sprites
            if (P[2].slot[i] == 8) { draw_sprite(LayerHUDa, spr_input_0, 580, 50+i*20+20); }
            if (P[2].slot[i] == 9) { draw_sprite(LayerHUDa, spr_input_1, 580, 50+i*20+20); }
            if (P[2].slot[i] == 6) { draw_sprite(LayerHUDa, spr_input_2, 580, 50+i*20+20); }
            if (P[2].slot[i] == 3) { draw_sprite(LayerHUDa, spr_input_3, 580, 50+i*20+20); }
            if (P[2].slot[i] == 2) { draw_sprite(LayerHUDa, spr_input_4, 580, 50+i*20+20); }
            if (P[2].slot[i] == 1) { draw_sprite(LayerHUDa, spr_input_5, 580, 50+i*20+20); }
            if (P[2].slot[i] == 4) { draw_sprite(LayerHUDa, spr_input_6, 580, 50+i*20+20); }
            if (P[2].slot[i] == 7) { draw_sprite(LayerHUDa, spr_input_7, 580, 50+i*20+20); }
            int a = P[2].bt_slot[i] % 10;
            int b = ((P[2].bt_slot[i] / 10) % 10) % 10;
            int c = ((((P[2].bt_slot[i] / 10) / 10) % 10) % 10) % 10;
            if (a != 0 || b != 0 || c != 0) {
                while (a == 0) {
                    a = b;
                    b = c;
                }
            }
            if (a == b && b == c) {
                b = 0;
                c = 0;
            }
            if (b == c) { c = 0; }
            if (a == 1) { draw_sprite(LayerHUDa, spr_input_8, 560-0*20, 50+i*20+20); }
            if (a == 2) { draw_sprite(LayerHUDa, spr_input_9, 560-0*20, 50+i*20+20); }
            if (a == 3) { draw_sprite(LayerHUDa, spr_input_10, 560-0*20, 50+i*20+20); }
            if (a == 4) { draw_sprite(LayerHUDa, spr_input_11, 560-0*20, 50+i*20+20); }
            if (a == 5) { draw_sprite(LayerHUDa, spr_input_12, 560-0*20, 50+i*20+20); }
            if (a == 6) { draw_sprite(LayerHUDa, spr_input_13, 560-0*20, 50+i*20+20); }
            if (a == 7) { draw_sprite(LayerHUDa, spr_input_14, 560-0*20, 50+i*20+20); }
            if (a == 8) { draw_sprite(LayerHUDa, spr_input_15, 560-0*20, 50+i*20+20); }
            if (b == 1) { draw_sprite(LayerHUDa, spr_input_8, 560-1*20, 50+i*20+20); }
            if (b == 2) { draw_sprite(LayerHUDa, spr_input_9, 560-1*20, 50+i*20+20); }
            if (b == 3) { draw_sprite(LayerHUDa, spr_input_10, 560-1*20, 50+i*20+20); }
            if (b == 4) { draw_sprite(LayerHUDa, spr_input_11, 560-1*20, 50+i*20+20); }
            if (b == 5) { draw_sprite(LayerHUDa, spr_input_12, 560-1*20, 50+i*20+20); }
            if (b == 6) { draw_sprite(LayerHUDa, spr_input_13, 560-1*20, 50+i*20+20); }
            if (b == 7) { draw_sprite(LayerHUDa, spr_input_14, 560-1*20, 50+i*20+20); }
            if (b == 8) { draw_sprite(LayerHUDa, spr_input_15, 560-1*20, 50+i*20+20); }
            if (c == 1) { draw_sprite(LayerHUDa, spr_input_8, 560-2*20, 50+i*20+20); }
            if (c == 2) { draw_sprite(LayerHUDa, spr_input_9, 560-2*20, 50+i*20+20); }
            if (c == 3) { draw_sprite(LayerHUDa, spr_input_10, 560-2*20, 50+i*20+20); }
            if (c == 4) { draw_sprite(LayerHUDa, spr_input_11, 560-2*20, 50+i*20+20); }
            if (c == 5) { draw_sprite(LayerHUDa, spr_input_12, 560-2*20, 50+i*20+20); }
            if (c == 6) { draw_sprite(LayerHUDa, spr_input_13, 560-2*20, 50+i*20+20); }
            if (c == 7) { draw_sprite(LayerHUDa, spr_input_14, 560-2*20, 50+i*20+20); }
            if (c == 8) { draw_sprite(LayerHUDa, spr_input_15, 560-2*20, 50+i*20+20); }
        }
    } //fim Draw_Input

    if (Draw_Debug == 1) {
        rect(LayerHUDa, 320-70, 20+240-115, 320+70, 20+240+135, makecol(255,255,255));
        rect(LayerHUDa, 320-75, 20+240-120, 320+75, 20+240+140, makecol(255,255,255));
        rect(LayerHUDa, 320-75-150, 20+240-120-5, 320+75+150, 20+240+140+5, makecol(255,255,255));
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 131, makecol(000, 000, 000), -1, "[F1] DEBUG");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 151, makecol(000, 000, 000), -1, "[F2] H.BOXES");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 171, makecol(000, 000, 000), -1, "[F3] INPUTS");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 191, makecol(000, 000, 000), -1, "[F4] FRAMEDATA");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 211, makecol(000, 000, 000), -1, "[F5] P1 ENERGY-");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 231, makecol(000, 000, 000), -1, "[F6] P1 ENERGY+");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 251, makecol(000, 000, 000), -1, "[F7] P2 ENERGY-");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 271, makecol(000, 000, 000), -1, "[F8] P2 ENERGY-");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 291, makecol(000, 000, 000), -1, "[F9] FPS1");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 311, makecol(000, 000, 000), -1, "[F10] FPS-");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 331, makecol(000, 000, 000), -1, "[F11] FPS+");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 20 + 351, makecol(000, 000, 000), -1, "[F12] FPS60");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 130, makecol(255, 255, 255), -1, "[F1] DEBUG");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 150, makecol(255, 255, 255), -1, "[F2] H.BOXES");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 170, makecol(255, 255, 255), -1, "[F3] INPUTS");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 190, makecol(255, 255, 255), -1, "[F4] FRAMEDATA");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 210, makecol(255, 255, 255), -1, "[F5] P1 ENERGY-");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 230, makecol(255, 255, 255), -1, "[F6] P1 ENERGY+");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 250, makecol(255, 230, 255), -1, "[F7] P2 ENERGY-");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 270, makecol(255, 230, 255), -1, "[F8] P2 ENERGY-");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 290, makecol(255, 255, 255), -1, "[F9] FPS1");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 310, makecol(255, 255, 255), -1, "[F10] FPS-");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 330, makecol(255, 255, 255), -1, "[F11] FPS+");
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 20 + 350, makecol(255, 255, 255), -1, "[F12] FPS60");
        textprintf_centre_ex(LayerHUDa, font_debug, 321, 86, makecol(000, 000, 000), -1, "FPS[%d] [%d]", Ctrl_FPS,
                             frame_count);
        textprintf_centre_ex(LayerHUDa, font_debug, 320, 85, makecol(255, 255, 000), -1, "FPS[%d] [%d]", Ctrl_FPS,
                             frame_count);
        textprintf_right_ex(LayerHUDa, font_debug, 311, 436, makecol(000, 000, 000), -1,
                            "[P1] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[1].x, P[1].y, abs(P[1].Vspeed),
                            abs(P[1].Hspeed), abs(P[1].Gravity), P[1].TempoPulo); //P1
        textprintf_right_ex(LayerHUDa, font_debug, 310, 435, makecol(255, 255, 255), -1,
                            "[P1] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[1].x, P[1].y, abs(P[1].Vspeed),
                            abs(P[1].Hspeed), abs(P[1].Gravity), P[1].TempoPulo); //P1
        textprintf_ex(LayerHUDa, font_debug, 331, 436, makecol(000, 000, 000), -1,
                      "[P2] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[2].x, P[2].y, abs(P[2].Vspeed), abs(P[2].Hspeed),
                      abs(P[2].Gravity), P[2].TempoPulo); //P2
        textprintf_ex(LayerHUDa, font_debug, 330, 435, makecol(255, 255, 255), -1,
                      "[P2] x:%i y:%i Vsp:%i Hsp:%i G.:%i TP:%i", P[2].x, P[2].y, abs(P[2].Vspeed), abs(P[2].Hspeed),
                      abs(P[2].Gravity), P[2].TempoPulo); //P2

        //-status do -P1- sombra
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 171, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        //-status do -P2- sombra
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[%i/0%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 331, 455, makecol(000, 000, 000), -1, "[%i]-[0%i/0%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }

        //-status do -P1-
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim >= 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames >= 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame >= 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[0%i/%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        if (P[1].IndexAnim < 10 && P[1].TotalFrames < 10 && (frame_count - P[1].StartFrame < 10) && P1_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 170, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[0%i/0%i]",
                          P[1].State, P[1].IndexAnim, P[1].TotalFrames, (frame_count - P[1].StartFrame) + 1,
                          P1_FrameTime + 1);
        }
        //-status do -P2-
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim >= 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[%i/0%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames >= 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame >= 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime >= 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[0%i/%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }
        if (P[2].IndexAnim < 10 && P[2].TotalFrames < 10 && (frame_count - P[2].StartFrame < 10) && P2_FrameTime < 10) {
            textprintf_ex(LayerHUDa, font_debug, 330, 454, makecol(255, 255, 255), -1, "[%i]-[0%i/0%i]-[0%i/0%i]",
                          P[2].State, P[2].IndexAnim, P[2].TotalFrames, frame_count - P[2].StartFrame, P2_FrameTime);
        }

        //exibe relogio sombra
        if (Horas >= 10 && Minutos >= 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[%d:%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas >= 10 && Minutos >= 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[%d:%d:0%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas >= 10 && Minutos < 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[%d:0%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas >= 10 && Minutos < 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[%d:0%d:0%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos >= 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[0%d:%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos >= 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[0%d:%d:0%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos < 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[0%d:0%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos < 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 321, 101, makecol(000, 000, 000), -1, "[0%d:0%d:0%d]", Horas,
                                 Minutos, Segundos);
        }
        //exibe relogio
        if (Horas >= 10 && Minutos >= 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[%d:%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas >= 10 && Minutos >= 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[%d:%d:0%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas >= 10 && Minutos < 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[%d:0%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas >= 10 && Minutos < 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[%d:0%d:0%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos >= 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[0%d:%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos >= 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[0%d:%d:0%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos < 10 && Segundos >= 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[0%d:0%d:%d]", Horas,
                                 Minutos, Segundos);
        }
        if (Horas < 10 && Minutos < 10 && Segundos < 10) {
            textprintf_centre_ex(LayerHUDa, font_debug, 320, 100, makecol(255, 255, 255), -1, "[0%d:0%d:0%d]", Horas,
                                 Minutos, Segundos);
        }

        //exibe joystick virtual
        draw_sprite(LayerHUDa, bt_joystick, 5, 440-400);
        draw_sprite(LayerHUDa, bt_joystick, 605, 440-400);
        if (P[1].key_UP_status == 1) { draw_sprite(LayerHUDa, bt_up_1, 005+5, 227+215-400); }
        if (P[1].key_UP_status == 2) { draw_sprite(LayerHUDa, bt_up_2, 005+5, 227+215-400); }
        if (P[1].key_UP_status == 3) { draw_sprite(LayerHUDa, bt_up_3, 005+5, 227+215-400); }
        if (P[1].key_UP_status == 0) {
        }
        if (P[1].key_DOWN_status == 1) { draw_sprite(LayerHUDa, bt_down_1, 005+5, 233+215-400); }
        if (P[1].key_DOWN_status == 2) { draw_sprite(LayerHUDa, bt_down_2, 005+5, 233+215-400); }
        if (P[1].key_DOWN_status == 3) { draw_sprite(LayerHUDa, bt_down_3, 005+5, 233+215-400); }
        if (P[1].key_DOWN_status == 0) {
        }
        if (P[1].key_LEFT_status == 1) { draw_sprite(LayerHUDa, bt_left_1, 002+5, 230+215-400); }
        if (P[1].key_LEFT_status == 2) { draw_sprite(LayerHUDa, bt_left_2, 002+5, 230+215-400); }
        if (P[1].key_LEFT_status == 3) { draw_sprite(LayerHUDa, bt_left_3, 002+5, 230+215-400); }
        if (P[1].key_LEFT_status == 0) {
        }
        if (P[1].key_RIGHT_status == 1) { draw_sprite(LayerHUDa, bt_right_1, 010+5, 230+215-400); }
        if (P[1].key_RIGHT_status == 2) { draw_sprite(LayerHUDa, bt_right_2, 010+5, 230+215-400); }
        if (P[1].key_RIGHT_status == 3) { draw_sprite(LayerHUDa, bt_right_3, 010+5, 230+215-400); }
        if (P[1].key_RIGHT_status == 0) {
        }
        if (P[1].key_BT1_status == 1) { draw_sprite(LayerHUDa, bt_1, 016+5, 229+215-400); }
        if (P[1].key_BT1_status == 2) { draw_sprite(LayerHUDa, bt_2, 016+5, 229+215-400); }
        if (P[1].key_BT1_status == 3) { draw_sprite(LayerHUDa, bt_3, 016+5, 229+215-400); }
        if (P[1].key_BT1_status == 0) {
        }
        if (P[1].key_BT2_status == 1) { draw_sprite(LayerHUDa, bt_1, 023+5, 229+215-400); }
        if (P[1].key_BT2_status == 2) { draw_sprite(LayerHUDa, bt_2, 023+5, 229+215-400); }
        if (P[1].key_BT2_status == 3) { draw_sprite(LayerHUDa, bt_3, 023+5, 229+215-400); }
        if (P[1].key_BT2_status == 0) {
        }
        if (P[1].key_BT3_status == 1) { draw_sprite(LayerHUDa, bt_1, 030+5, 229+215-400); }
        if (P[1].key_BT3_status == 2) { draw_sprite(LayerHUDa, bt_2, 030+5, 229+215-400); }
        if (P[1].key_BT3_status == 3) { draw_sprite(LayerHUDa, bt_3, 030+5, 229+215-400); }
        if (P[1].key_BT3_status == 0) {
        }
        if (P[1].key_BT4_status == 1) { draw_sprite(LayerHUDa, bt_1, 016+5, 234+215-400); }
        if (P[1].key_BT4_status == 2) { draw_sprite(LayerHUDa, bt_2, 016+5, 234+215-400); }
        if (P[1].key_BT4_status == 3) { draw_sprite(LayerHUDa, bt_3, 016+5, 234+215-400); }
        if (P[1].key_BT4_status == 0) {
        }
        if (P[1].key_BT5_status == 1) { draw_sprite(LayerHUDa, bt_1, 023+5, 234+215-400); }
        if (P[1].key_BT5_status == 2) { draw_sprite(LayerHUDa, bt_2, 023+5, 234+215-400); }
        if (P[1].key_BT5_status == 3) { draw_sprite(LayerHUDa, bt_3, 023+5, 234+215-400); }
        if (P[1].key_BT5_status == 0) {
        }
        if (P[1].key_BT6_status == 1) { draw_sprite(LayerHUDa, bt_1, 030+5, 234+215-400); }
        if (P[1].key_BT6_status == 2) { draw_sprite(LayerHUDa, bt_2, 030+5, 234+215-400); }
        if (P[1].key_BT6_status == 3) { draw_sprite(LayerHUDa, bt_3, 030+5, 234+215-400); }
        if (P[1].key_BT6_status == 0) {
        }
        if (P[1].key_SELECT_status == 1) { draw_sprite(LayerHUDa, bt_ss_1, 020+5, 227+215-400); }
        if (P[1].key_SELECT_status == 2) { draw_sprite(LayerHUDa, bt_ss_2, 020+5, 227+215-400); }
        if (P[1].key_SELECT_status == 3) { draw_sprite(LayerHUDa, bt_ss_3, 020+5, 227+215-400); }
        if (P[1].key_SELECT_status == 0) {
        }
        if (P[1].key_START_status == 1) { draw_sprite(LayerHUDa, bt_ss_1, 026+5, 227+215-400); }
        if (P[1].key_START_status == 2) { draw_sprite(LayerHUDa, bt_ss_2, 026+5, 227+215-400); }
        if (P[1].key_START_status == 3) { draw_sprite(LayerHUDa, bt_ss_3, 026+5, 227+215-400); }
        if (P[1].key_START_status == 0) {
        }
    } //fim Draw_Debug

    if (Draw_Debug == 1) {
        //Hit/Collision Box DATA_INFO
        textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 1 * 10, makecol(000, 000, 000), -1, "HurtBox Total: %i",
                            P1_HurtBox_tot);
        textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 2 * 10, makecol(000, 000, 000), -1, "HitBox Total: %i",
                            P1_HitBox_tot);
        if (P1_HurtBox01x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 3 * 10, makecol(000, 000, 000), -1,
                                "HurtBox1: %i,%i,%i,%i", P1_HurtBox01x1, P1_HurtBox01y1, P1_HurtBox01x2,
                                P1_HurtBox01y2);
        }
        if (P1_HurtBox02x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 4 * 10, makecol(000, 000, 000), -1,
                                "HurtBox2: %i,%i,%i,%i", P1_HurtBox02x1, P1_HurtBox02y1, P1_HurtBox02x2,
                                P1_HurtBox02y2);
        }
        if (P1_HurtBox03x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 5 * 10, makecol(000, 000, 000), -1,
                                "HurtBox3: %i,%i,%i,%i", P1_HurtBox03x1, P1_HurtBox03y1, P1_HurtBox03x2,
                                P1_HurtBox03y2);
        }
        if (P1_HurtBox04x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 6 * 10, makecol(000, 000, 000), -1,
                                "HurtBox4: %i,%i,%i,%i", P1_HurtBox04x1, P1_HurtBox04y1, P1_HurtBox04x2,
                                P1_HurtBox04y2);
        }
        if (P1_HurtBox05x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 7 * 10, makecol(000, 000, 000), -1,
                                "HurtBox5: %i,%i,%i,%i", P1_HurtBox05x1, P1_HurtBox05y1, P1_HurtBox05x2,
                                P1_HurtBox05y2);
        }
        if (P1_HurtBox06x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 8 * 10, makecol(000, 000, 000), -1,
                                "HurtBox6: %i,%i,%i,%i", P1_HurtBox06x1, P1_HurtBox06y1, P1_HurtBox06x2,
                                P1_HurtBox06y2);
        }
        if (P1_HurtBox07x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 9 * 10, makecol(000, 000, 000), -1,
                                "HurtBox7: %i,%i,%i,%i", P1_HurtBox07x1, P1_HurtBox07y1, P1_HurtBox07x2,
                                P1_HurtBox07y2);
        }
        if (P1_HurtBox08x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 10 * 10, makecol(000, 000, 000), -1,
                                "HurtBox8: %i,%i,%i,%i", P1_HurtBox08x1, P1_HurtBox08y1, P1_HurtBox08x2,
                                P1_HurtBox08y2);
        }
        if (P1_HurtBox09x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 11 * 10, makecol(000, 000, 000), -1,
                                "HurtBox9: %i,%i,%i,%i", P1_HurtBox09x1, P1_HurtBox09y1, P1_HurtBox09x2,
                                P1_HurtBox09y2);
        }
        if (P1_HitBox01x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 12 * 10, makecol(000, 000, 000), -1,
                                "HitBox1.: %i,%i,%i,%i", P1_HitBox01x1, P1_HitBox01y1, P1_HitBox01x2, P1_HitBox01y2);
        }
        if (P1_HitBox02x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 13 * 10, makecol(000, 000, 000), -1,
                                "HitBox2.: %i,%i,%i,%i", P1_HitBox02x1, P1_HitBox02y1, P1_HitBox02x2, P1_HitBox02y2);
        }
        if (P1_HitBox03x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 14 * 10, makecol(000, 000, 000), -1,
                                "HitBox3.: %i,%i,%i,%i", P1_HitBox03x1, P1_HitBox03y1, P1_HitBox03x2, P1_HitBox03y2);
        }
        if (P1_HitBox04x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 15 * 10, makecol(000, 000, 000), -1,
                                "HitBox4.: %i,%i,%i,%i", P1_HitBox04x1, P1_HitBox04y1, P1_HitBox04x2, P1_HitBox04y2);
        }
        if (P1_HitBox05x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 16 * 10, makecol(000, 000, 000), -1,
                                "HitBox5.: %i,%i,%i,%i", P1_HitBox05x1, P1_HitBox05y1, P1_HitBox05x2, P1_HitBox05y2);
        }
        if (P1_HitBox06x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 17 * 10, makecol(000, 000, 000), -1,
                                "HitBox6.: %i,%i,%i,%i", P1_HitBox06x1, P1_HitBox06y1, P1_HitBox06x2, P1_HitBox06y2);
        }
        if (P1_HitBox07x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 18 * 10, makecol(000, 000, 000), -1,
                                "HitBox7.: %i,%i,%i,%i", P1_HitBox07x1, P1_HitBox07y1, P1_HitBox07x2, P1_HitBox07y2);
        }
        if (P1_HitBox08x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 19 * 10, makecol(000, 000, 000), -1,
                                "HitBox8.: %i,%i,%i,%i", P1_HitBox08x1, P1_HitBox08y1, P1_HitBox08x2, P1_HitBox08y2);
        }
        if (P1_HitBox09x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 20 * 10, makecol(000, 000, 000), -1,
                                "HitBox9.: %i,%i,%i,%i", P1_HitBox09x1, P1_HitBox09y1, P1_HitBox09x2, P1_HitBox09y2);
        }
        if (P1_HurtBox01x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 3 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox02x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 4 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox03x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 5 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox04x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 6 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox05x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 7 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox06x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 8 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox07x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 9 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox08x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 10 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HurtBox09x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 11 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox01x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 12 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox02x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 13 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox03x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 14 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox04x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 15 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox05x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 16 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox06x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 17 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox07x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 18 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox08x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 19 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P1_HitBox09x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 20 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (colisaoxP1 == 1) {
            textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 21 * 10, makecol(000, 000, 000), -1, "COLISAOxP1!!!");
        }
        textprintf_ex(LayerHUDa, font_10, 401, 131 + 1 * 10, makecol(000, 000, 000), -1, "HurtBox Total: %i",
                      P2_HurtBox_tot);
        textprintf_ex(LayerHUDa, font_10, 401, 131 + 2 * 10, makecol(000, 000, 000), -1, "HitBox Total: %i",
                      P2_HitBox_tot);
        if (P2_HurtBox01x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 3 * 10, makecol(000, 000, 000), -1, "HurtBox1: %i,%i,%i,%i",
                          P2_HurtBox01x1, P2_HurtBox01y1, P2_HurtBox01x2, P2_HurtBox01y2);
        }
        if (P2_HurtBox02x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 4 * 10, makecol(000, 000, 000), -1, "HurtBox2: %i,%i,%i,%i",
                          P2_HurtBox02x1, P2_HurtBox02y1, P2_HurtBox02x2, P2_HurtBox02y2);
        }
        if (P2_HurtBox03x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 5 * 10, makecol(000, 000, 000), -1, "HurtBox3: %i,%i,%i,%i",
                          P2_HurtBox03x1, P2_HurtBox03y1, P2_HurtBox03x2, P2_HurtBox03y2);
        }
        if (P2_HurtBox04x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 6 * 10, makecol(000, 000, 000), -1, "HurtBox4: %i,%i,%i,%i",
                          P2_HurtBox04x1, P2_HurtBox04y1, P2_HurtBox04x2, P2_HurtBox04y2);
        }
        if (P2_HurtBox05x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 7 * 10, makecol(000, 000, 000), -1, "HurtBox5: %i,%i,%i,%i",
                          P2_HurtBox05x1, P2_HurtBox05y1, P2_HurtBox05x2, P2_HurtBox05y2);
        }
        if (P2_HurtBox06x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 8 * 10, makecol(000, 000, 000), -1, "HurtBox6: %i,%i,%i,%i",
                          P2_HurtBox06x1, P2_HurtBox06y1, P2_HurtBox06x2, P2_HurtBox06y2);
        }
        if (P2_HurtBox07x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 9 * 10, makecol(000, 000, 000), -1, "HurtBox7: %i,%i,%i,%i",
                          P2_HurtBox07x1, P2_HurtBox07y1, P2_HurtBox07x2, P2_HurtBox07y2);
        }
        if (P2_HurtBox08x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 10 * 10, makecol(000, 000, 000), -1, "HurtBox8: %i,%i,%i,%i",
                          P2_HurtBox08x1, P2_HurtBox08y1, P2_HurtBox08x2, P2_HurtBox08y2);
        }
        if (P2_HurtBox09x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 11 * 10, makecol(000, 000, 000), -1, "HurtBox9: %i,%i,%i,%i",
                          P2_HurtBox09x1, P2_HurtBox09y1, P2_HurtBox09x2, P2_HurtBox09y2);
        }
        if (P2_HitBox01x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 12 * 10, makecol(000, 000, 000), -1, "HitBox1.: %i,%i,%i,%i",
                          P2_HitBox01x1, P2_HitBox01y1, P2_HitBox01x2, P2_HitBox01y2);
        }
        if (P2_HitBox02x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 13 * 10, makecol(000, 000, 000), -1, "HitBox2.: %i,%i,%i,%i",
                          P2_HitBox02x1, P2_HitBox02y1, P2_HitBox02x2, P2_HitBox02y2);
        }
        if (P2_HitBox03x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 14 * 10, makecol(000, 000, 000), -1, "HitBox3.: %i,%i,%i,%i",
                          P2_HitBox03x1, P2_HitBox03y1, P2_HitBox03x2, P2_HitBox03y2);
        }
        if (P2_HitBox04x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 15 * 10, makecol(000, 000, 000), -1, "HitBox4.: %i,%i,%i,%i",
                          P2_HitBox04x1, P2_HitBox04y1, P2_HitBox04x2, P2_HitBox04y2);
        }
        if (P2_HitBox05x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 16 * 10, makecol(000, 000, 000), -1, "HitBox5.: %i,%i,%i,%i",
                          P2_HitBox05x1, P2_HitBox05y1, P2_HitBox05x2, P2_HitBox05y2);
        }
        if (P2_HitBox06x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 17 * 10, makecol(000, 000, 000), -1, "HitBox6.: %i,%i,%i,%i",
                          P2_HitBox06x1, P2_HitBox06y1, P2_HitBox06x2, P2_HitBox06y2);
        }
        if (P2_HitBox07x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 18 * 10, makecol(000, 000, 000), -1, "HitBox7.: %i,%i,%i,%i",
                          P2_HitBox07x1, P2_HitBox07y1, P2_HitBox07x2, P2_HitBox07y2);
        }
        if (P2_HitBox08x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 19 * 10, makecol(000, 000, 000), -1, "HitBox8.: %i,%i,%i,%i",
                          P2_HitBox08x1, P2_HitBox08y1, P2_HitBox08x2, P2_HitBox08y2);
        }
        if (P2_HitBox09x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 20 * 10, makecol(000, 000, 000), -1, "HitBox9.: %i,%i,%i,%i",
                          P2_HitBox09x1, P2_HitBox09y1, P2_HitBox09x2, P2_HitBox09y2);
        }
        if (P2_HurtBox01x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 3 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox02x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 4 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox03x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 5 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox04x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 6 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox05x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 7 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox06x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 8 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox07x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 9 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox08x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 10 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HurtBox09x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 11 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox01x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 12 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox02x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 13 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox03x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 14 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox04x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 15 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox05x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 16 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox06x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 17 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox07x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 18 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox08x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 19 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (P2_HitBox09x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 20 * 10, makecol(000, 000, 000), -1, "----");
        }
        if (colisaoxP2 == 1) {
            textprintf_ex(LayerHUDa, font_10, 401, 131 + 21 * 10, makecol(000, 000, 000), -1, "COLISAOxP2!!!");
        }
        textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 1 * 10, makecol(255, 255, 255), -1, "HurtBox Total: %i",
                            P1_HurtBox_tot);
        textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 2 * 10, makecol(255, 255, 255), -1, "HitBox Total: %i",
                            P1_HitBox_tot);
        if (P1_HurtBox01x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 3 * 10, makecol(255, 255, 255), -1,
                                "HurtBox1: %i,%i,%i,%i", P1_HurtBox01x1, P1_HurtBox01y1, P1_HurtBox01x2,
                                P1_HurtBox01y2);
        }
        if (P1_HurtBox02x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 4 * 10, makecol(255, 255, 255), -1,
                                "HurtBox2: %i,%i,%i,%i", P1_HurtBox02x1, P1_HurtBox02y1, P1_HurtBox02x2,
                                P1_HurtBox02y2);
        }
        if (P1_HurtBox03x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 5 * 10, makecol(255, 255, 255), -1,
                                "HurtBox3: %i,%i,%i,%i", P1_HurtBox03x1, P1_HurtBox03y1, P1_HurtBox03x2,
                                P1_HurtBox03y2);
        }
        if (P1_HurtBox04x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 6 * 10, makecol(255, 255, 255), -1,
                                "HurtBox4: %i,%i,%i,%i", P1_HurtBox04x1, P1_HurtBox04y1, P1_HurtBox04x2,
                                P1_HurtBox04y2);
        }
        if (P1_HurtBox05x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 7 * 10, makecol(255, 255, 255), -1,
                                "HurtBox5: %i,%i,%i,%i", P1_HurtBox05x1, P1_HurtBox05y1, P1_HurtBox05x2,
                                P1_HurtBox05y2);
        }
        if (P1_HurtBox06x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 8 * 10, makecol(255, 255, 255), -1,
                                "HurtBox6: %i,%i,%i,%i", P1_HurtBox06x1, P1_HurtBox06y1, P1_HurtBox06x2,
                                P1_HurtBox06y2);
        }
        if (P1_HurtBox07x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 9 * 10, makecol(255, 255, 255), -1,
                                "HurtBox7: %i,%i,%i,%i", P1_HurtBox07x1, P1_HurtBox07y1, P1_HurtBox07x2,
                                P1_HurtBox07y2);
        }
        if (P1_HurtBox08x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 10 * 10, makecol(255, 255, 255), -1,
                                "HurtBox8: %i,%i,%i,%i", P1_HurtBox08x1, P1_HurtBox08y1, P1_HurtBox08x2,
                                P1_HurtBox08y2);
        }
        if (P1_HurtBox09x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 11 * 10, makecol(255, 255, 255), -1,
                                "HurtBox9: %i,%i,%i,%i", P1_HurtBox09x1, P1_HurtBox09y1, P1_HurtBox09x2,
                                P1_HurtBox09y2);
        }
        if (P1_HitBox01x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 12 * 10, makecol(255, 255, 255), -1,
                                "HitBox1.: %i,%i,%i,%i", P1_HitBox01x1, P1_HitBox01y1, P1_HitBox01x2, P1_HitBox01y2);
        }
        if (P1_HitBox02x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 13 * 10, makecol(255, 255, 255), -1,
                                "HitBox2.: %i,%i,%i,%i", P1_HitBox02x1, P1_HitBox02y1, P1_HitBox02x2, P1_HitBox02y2);
        }
        if (P1_HitBox03x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 14 * 10, makecol(255, 255, 255), -1,
                                "HitBox3.: %i,%i,%i,%i", P1_HitBox03x1, P1_HitBox03y1, P1_HitBox03x2, P1_HitBox03y2);
        }
        if (P1_HitBox04x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 15 * 10, makecol(255, 255, 255), -1,
                                "HitBox4.: %i,%i,%i,%i", P1_HitBox04x1, P1_HitBox04y1, P1_HitBox04x2, P1_HitBox04y2);
        }
        if (P1_HitBox05x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 16 * 10, makecol(255, 255, 255), -1,
                                "HitBox5.: %i,%i,%i,%i", P1_HitBox05x1, P1_HitBox05y1, P1_HitBox05x2, P1_HitBox05y2);
        }
        if (P1_HitBox06x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 17 * 10, makecol(255, 255, 255), -1,
                                "HitBox6.: %i,%i,%i,%i", P1_HitBox06x1, P1_HitBox06y1, P1_HitBox06x2, P1_HitBox06y2);
        }
        if (P1_HitBox07x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 18 * 10, makecol(255, 255, 255), -1,
                                "HitBox7.: %i,%i,%i,%i", P1_HitBox07x1, P1_HitBox07y1, P1_HitBox07x2, P1_HitBox07y2);
        }
        if (P1_HitBox08x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 19 * 10, makecol(255, 255, 255), -1,
                                "HitBox8.: %i,%i,%i,%i", P1_HitBox08x1, P1_HitBox08y1, P1_HitBox08x2, P1_HitBox08y2);
        }
        if (P1_HitBox09x1 != -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 20 * 10, makecol(255, 255, 255), -1,
                                "HitBox9.: %i,%i,%i,%i", P1_HitBox09x1, P1_HitBox09y1, P1_HitBox09x2, P1_HitBox09y2);
        }
        if (P1_HurtBox01x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 3 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox02x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 4 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox03x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 5 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox04x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 6 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox05x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 7 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox06x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 8 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox07x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 9 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox08x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 10 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HurtBox09x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 11 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox01x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 12 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox02x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 13 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox03x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 14 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox04x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 15 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox05x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 16 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox06x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 17 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox07x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 18 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox08x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 19 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P1_HitBox09x1 == -5555) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 20 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (colisaoxP1 == 1) {
            textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 21 * 10, makecol(255, 255, 000), -1, "COLISAOxP1!!!");
        }
        textprintf_ex(LayerHUDa, font_10, 400, 130 + 1 * 10, makecol(255, 255, 255), -1, "HurtBox Total: %i",
                      P2_HurtBox_tot);
        textprintf_ex(LayerHUDa, font_10, 400, 130 + 2 * 10, makecol(255, 255, 255), -1, "HitBox Total: %i",
                      P2_HitBox_tot);
        if (P2_HurtBox01x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 3 * 10, makecol(255, 255, 255), -1, "HurtBox1: %i,%i,%i,%i",
                          P2_HurtBox01x1, P2_HurtBox01y1, P2_HurtBox01x2, P2_HurtBox01y2);
        }
        if (P2_HurtBox02x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 4 * 10, makecol(255, 255, 255), -1, "HurtBox2: %i,%i,%i,%i",
                          P2_HurtBox02x1, P2_HurtBox02y1, P2_HurtBox02x2, P2_HurtBox02y2);
        }
        if (P2_HurtBox03x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 5 * 10, makecol(255, 255, 255), -1, "HurtBox3: %i,%i,%i,%i",
                          P2_HurtBox03x1, P2_HurtBox03y1, P2_HurtBox03x2, P2_HurtBox03y2);
        }
        if (P2_HurtBox04x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 6 * 10, makecol(255, 255, 255), -1, "HurtBox4: %i,%i,%i,%i",
                          P2_HurtBox04x1, P2_HurtBox04y1, P2_HurtBox04x2, P2_HurtBox04y2);
        }
        if (P2_HurtBox05x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 7 * 10, makecol(255, 255, 255), -1, "HurtBox5: %i,%i,%i,%i",
                          P2_HurtBox05x1, P2_HurtBox05y1, P2_HurtBox05x2, P2_HurtBox05y2);
        }
        if (P2_HurtBox06x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 8 * 10, makecol(255, 255, 255), -1, "HurtBox6: %i,%i,%i,%i",
                          P2_HurtBox06x1, P2_HurtBox06y1, P2_HurtBox06x2, P2_HurtBox06y2);
        }
        if (P2_HurtBox07x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 9 * 10, makecol(255, 255, 255), -1, "HurtBox7: %i,%i,%i,%i",
                          P2_HurtBox07x1, P2_HurtBox07y1, P2_HurtBox07x2, P2_HurtBox07y2);
        }
        if (P2_HurtBox08x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 10 * 10, makecol(255, 255, 255), -1, "HurtBox8: %i,%i,%i,%i",
                          P2_HurtBox08x1, P2_HurtBox08y1, P2_HurtBox08x2, P2_HurtBox08y2);
        }
        if (P2_HurtBox09x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 11 * 10, makecol(255, 255, 255), -1, "HurtBox9: %i,%i,%i,%i",
                          P2_HurtBox09x1, P2_HurtBox09y1, P2_HurtBox09x2, P2_HurtBox09y2);
        }
        if (P2_HitBox01x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 12 * 10, makecol(255, 255, 255), -1, "HitBox1.: %i,%i,%i,%i",
                          P2_HitBox01x1, P2_HitBox01y1, P2_HitBox01x2, P2_HitBox01y2);
        }
        if (P2_HitBox02x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 13 * 10, makecol(255, 255, 255), -1, "HitBox2.: %i,%i,%i,%i",
                          P2_HitBox02x1, P2_HitBox02y1, P2_HitBox02x2, P2_HitBox02y2);
        }
        if (P2_HitBox03x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 14 * 10, makecol(255, 255, 255), -1, "HitBox3.: %i,%i,%i,%i",
                          P2_HitBox03x1, P2_HitBox03y1, P2_HitBox03x2, P2_HitBox03y2);
        }
        if (P2_HitBox04x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 15 * 10, makecol(255, 255, 255), -1, "HitBox4.: %i,%i,%i,%i",
                          P2_HitBox04x1, P2_HitBox04y1, P2_HitBox04x2, P2_HitBox04y2);
        }
        if (P2_HitBox05x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 16 * 10, makecol(255, 255, 255), -1, "HitBox5.: %i,%i,%i,%i",
                          P2_HitBox05x1, P2_HitBox05y1, P2_HitBox05x2, P2_HitBox05y2);
        }
        if (P2_HitBox06x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 17 * 10, makecol(255, 255, 255), -1, "HitBox6.: %i,%i,%i,%i",
                          P2_HitBox06x1, P2_HitBox06y1, P2_HitBox06x2, P2_HitBox06y2);
        }
        if (P2_HitBox07x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 18 * 10, makecol(255, 255, 255), -1, "HitBox7.: %i,%i,%i,%i",
                          P2_HitBox07x1, P2_HitBox07y1, P2_HitBox07x2, P2_HitBox07y2);
        }
        if (P2_HitBox08x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 19 * 10, makecol(255, 255, 255), -1, "HitBox8.: %i,%i,%i,%i",
                          P2_HitBox08x1, P2_HitBox08y1, P2_HitBox08x2, P2_HitBox08y2);
        }
        if (P2_HitBox09x1 != +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 20 * 10, makecol(255, 255, 255), -1, "HitBox9.: %i,%i,%i,%i",
                          P2_HitBox09x1, P2_HitBox09y1, P2_HitBox09x2, P2_HitBox09y2);
        }
        if (P2_HurtBox01x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 3 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox02x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 4 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox03x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 5 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox04x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 6 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox05x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 7 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox06x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 8 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox07x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 9 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox08x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 10 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HurtBox09x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 11 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox01x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 12 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox02x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 13 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox03x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 14 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox04x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 15 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox05x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 16 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox06x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 17 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox07x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 18 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox08x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 19 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (P2_HitBox09x1 == +5555) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 20 * 10, makecol(255, 255, 255), -1, "----");
        }
        if (colisaoxP2 == 1) {
            textprintf_ex(LayerHUDa, font_10, 400, 130 + 21 * 10, makecol(255, 255, 000), -1, "COLISAOxP2!!!");
        }

        textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 22 * 10, makecol(000, 000, 000), -1, "MomentoDoP1: %i",
                            MomentoDoP1);
        textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 23 * 10, makecol(000, 000, 000), -1, "ForcaDoGolpe: %i",
                            ForcaDoGolpeP1);
        textprintf_right_ex(LayerHUDa, font_10, 241, 131 + 24 * 10, makecol(000, 000, 000), -1, "P1HitPause: %i",
                            P1HitPause);
        textprintf_right_ex(LayerHUDa, font_10, 240, 131 + 25 * 10, makecol(000, 000, 000), -1, "P1HitType: %s",
                            P[1].HitType_string);
        textprintf_right_ex(LayerHUDa, font_10, 240, 131 + 26 * 10, makecol(000, 000, 000), -1, "P1HitStack: %s",
                            P[1].HitStack_string);
        textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 22 * 10, makecol(255, 255, 255), -1, "MomentoDoP1: %i",
                            MomentoDoP1);
        textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 23 * 10, makecol(255, 255, 255), -1, "ForcaDoGolpe: %i",
                            ForcaDoGolpeP1);
        textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 24 * 10, makecol(255, 255, 255), -1, "P1HitPause: %i",
                            P1HitPause);
        textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 25 * 10, makecol(255, 255, 255), -1, "P1HitType: %s",
                            P[1].HitType_string);
        textprintf_right_ex(LayerHUDa, font_10, 240, 130 + 26 * 10, makecol(255, 255, 255), -1, "P1HitStack: %s",
                            P[1].HitStack_string);
        textprintf_ex(LayerHUDa, font_10, 401, 131 + 22 * 10, makecol(000, 000, 000), -1, "MomentoDoP2: %i",
                      MomentoDoP2);
        textprintf_ex(LayerHUDa, font_10, 401, 131 + 23 * 10, makecol(000, 000, 000), -1, "ForcaDoGolpe: %i",
                      ForcaDoGolpeP2);
        textprintf_ex(LayerHUDa, font_10, 401, 131 + 24 * 10, makecol(000, 000, 000), -1, "P2HitPause: %i", P2HitPause);
        textprintf_ex(LayerHUDa, font_10, 400, 131 + 25 * 10, makecol(000, 000, 000), -1, "P2HitType: %s",
                      P[2].HitType_string);
        textprintf_ex(LayerHUDa, font_10, 400, 131 + 26 * 10, makecol(000, 000, 000), -1, "P2HitStack: %s",
                      P[2].HitStack_string);
        textprintf_ex(LayerHUDa, font_10, 400, 130 + 22 * 10, makecol(255, 255, 255), -1, "MomentoDoP2: %i",
                      MomentoDoP2);
        textprintf_ex(LayerHUDa, font_10, 400, 130 + 23 * 10, makecol(255, 255, 255), -1, "ForcaDoGolpe: %i",
                      ForcaDoGolpeP2);
        textprintf_ex(LayerHUDa, font_10, 400, 130 + 24 * 10, makecol(255, 255, 255), -1, "P2HitPause: %i", P2HitPause);
        textprintf_ex(LayerHUDa, font_10, 400, 130 + 25 * 10, makecol(255, 255, 255), -1, "P2HitType: %s",
                      P[2].HitType_string);
        textprintf_ex(LayerHUDa, font_10, 400, 130 + 26 * 10, makecol(255, 255, 255), -1, "P2HitStack: %s",
                      P[2].HitStack_string);
    }

    /*Barras de energia*/

    //Barra Red
    for (int ind = 1; ind <= 2; ind++) {
        if (P[ind].EnergyRedBar == P[ind].Energy) { P[ind].EnergyRedBarSleep = 60; }
        if (P[ind].EnergyRedBar != P[ind].Energy) {
            P[ind].EnergyRedBarSleep--;
            if (P[ind].EnergyRedBarSleep < 0) { P[ind].EnergyRedBarSleep = 0; }
        }
        if ((P[ind].EnergyRedBar != P[ind].Energy) && P[ind].EnergyRedBarSleep == 0) { P[ind].EnergyRedBar -= 5; }
    }

    draw_sprite(LayerHUDa, spr_bg_bar, 320-(spr_bg_bar->w/2), 0);

    //dica de codigo
    //stretch_blit(BITMAP*source, BITMAP*dest, source_x, source_y, source_width, source_height, dest_x, dest_y, dest_width, dest_height);
    //masked_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);

    //energia

    /*p1red*/
    clear_to_color(P1_energy_red_flip, makecol(255, 0, 255));
    draw_sprite_h_flip(P1_energy_red_flip, spr_energy_red_bar_full, 0, 0);
    masked_blit(P1_energy_red_flip, LayerHUDa, P1_energy_red_flip->w-(P[1].EnergyRedBar*250)/1000, 0,
                50+(P1_energy_red_flip->w-(P[1].EnergyRedBar*250)/1000), 0, P1_energy_red_flip->w,
                P1_energy_red_flip->h);
    /*p2red*/
    masked_blit(spr_energy_red_bar_full, LayerHUDa, 0, 0, 320+20, 0, (P[2].EnergyRedBar*250)/1000,
                spr_energy_red_bar_full->h);
    /*p1*/
    clear_to_color(P1_energy_flip, makecol(255, 0, 255));
    draw_sprite_h_flip(P1_energy_flip, spr_energy_bar_full, 0, 0);
    masked_blit(P1_energy_flip, LayerHUDa, P1_energy_flip->w-((((P[1].Energy*100)/1000)/100)*250), 0,
                50+(P1_energy_flip->w-((((P[1].Energy*100)/1000)/100)*250)), 0, P1_energy_flip->w, P1_energy_flip->h);
    /*p2*/
    masked_blit(spr_energy_bar_full, LayerHUDa, 0, 0, 320+20, 0, (((P[2].Energy*100)/1000)/100)*250,
                spr_energy_bar_full->h);

    //Special
    /*p1*/
    stretch_blit(spr_bg_energy_bar_sp, LayerHUDa, 0, 0, spr_bg_energy_bar_sp->w, spr_bg_energy_bar_sp->h, 30, 457,
                 (P[1].Special*250)/2000, spr_bg_energy_bar_sp->h);
    /*p2*/
    stretch_blit(spr_bg_energy_bar_sp, LayerHUDa, 0, 0, spr_bg_energy_bar_sp->w, spr_bg_energy_bar_sp->h,
                 360+(250-((P[2].Special*125)/1000)), 457, (P[2].Special*250)/2000, spr_bg_energy_bar_sp->h);
    //molduras barra de Special
    /*p1*/
    draw_sprite(LayerHUDa, spr_bg_bar_sp, 0, 440);
    /*p2*/
    draw_sprite_h_flip(LayerHUDa, spr_bg_bar_sp, 480, 440);

    //mini fotos in game
    draw_sprite(LayerHUDa, P1_1, 5, 5);
    draw_sprite_h_flip(LayerHUDa, P2_1, 602, 5);

    /*relogio*/
    //calculo de digitos
    if (RoundTime > 0) { RoundTime = RoundTime - 1; }
    float RelogioTimer = RoundTime / 60 / 10;
    int RelogioTimerParteInteira;
    int RelogioTimerParteDecimal;
    RelogioTimerParteInteira = abs(RelogioTimer);
    RelogioTimerParteDecimal = ((RoundTime / 60) - (RelogioTimerParteInteira * 10));
    //desenha os digitos
    for (int ind = 0; ind <= 9; ind++) {
        if (RelogioTimerParteDecimal == ind) {
            draw_sprite(LayerHUDa, spr_num[ind], 320-10, 0);
        }
        if (RelogioTimerParteInteira == ind) {
            draw_sprite(LayerHUDa, spr_num[ind], 320-30, 0);
        }
    }

    //desenha numero (valor) do Special 1,2,3
    if (P[1].Special < 333) { textprintf_centre_ex(LayerHUDa, font_debug, 18, 449, makecol(255, 255, 255), -1, "0"); }
    if (P[1].Special >= 333 && P[1].Special < 666) {
        textprintf_centre_ex(LayerHUDa, font_debug, 18, 449, makecol(255, 255, 255), -1, "1");
    }
    if (P[1].Special >= 666 && P[1].Special < 999) {
        textprintf_centre_ex(LayerHUDa, font_debug, 18, 449, makecol(255, 255, 255), -1, "2");
    }
    if (P[1].Special == 1000) { textprintf_centre_ex(LayerHUDa, font_debug, 18, 449, makecol(255, 255, 255), -1, "3"); }
    if (P[2].Special < 333) { textprintf_centre_ex(LayerHUDa, font_debug, 622, 449, makecol(255, 255, 255), -1, "0"); }
    if (P[2].Special >= 333 && P[2].Special < 666) {
        textprintf_centre_ex(LayerHUDa, font_debug, 622, 449, makecol(255, 255, 255), -1, "1");
    }
    if (P[2].Special >= 666 && P[2].Special < 999) {
        textprintf_centre_ex(LayerHUDa, font_debug, 622, 449, makecol(255, 255, 255), -1, "2");
    }
    if (P[2].Special == 1000) {
        textprintf_centre_ex(LayerHUDa, font_debug, 622, 449, makecol(255, 255, 255), -1, "3");
    }

    //desenha splash round 1 fight
    if (timer_rounds >= 30 && timer_rounds < 150) {
        if (RoundAtual == 1) {
            draw_sprite(LayerHUDa, spr_splash_round1, 170, 80);
            if (timer_rounds == 30) { play_sample(round1, 255, 128, 1000, 0); }
        }
        if (RoundAtual == 2) {
            draw_sprite(LayerHUDa, spr_splash_round2, 170, 80);
            if (timer_rounds == 30) { play_sample(round2, 255, 128, 1000, 0); }
        }
        if (RoundAtual == 3) {
            draw_sprite(LayerHUDa, spr_splash_round3, 170, 80);
            if (timer_rounds == 30) { play_sample(round3, 255, 128, 1000, 0); }
        }
        if (RoundAtual == 4) { draw_sprite(LayerHUDa, spr_splash_round4, 170, 80); }
        if (RoundAtual == 5) { draw_sprite(LayerHUDa, spr_splash_round5, 170, 80); }
    }
    if (timer_rounds >= 150 && timer_rounds < 250) {
        draw_sprite(LayerHUDa, spr_splash_fight, 120, 100);
        if (timer_rounds == 150) { play_sample(fight, 255, 128, 1000, 0); }
    }

    //desenha splash de vitoria, derrota, draw
    if (timer_final_de_rounds > 0) {
        if (timer_final_de_rounds >= 30 && timer_final_de_rounds < 180) {
            if (P[1].Energy > 0 && P[2].Energy > 0) { draw_sprite(LayerHUDa, spr_splash_time_over, 170, 190); } else
            //time over
            {
                draw_sprite(LayerHUDa, spr_splash_ko, 170, 120);
                if (timer_final_de_rounds == 30) { play_sample(ko, 255, 128, 1000, 0); }
            } //KO
        }

        //Splashs de final de round
        if (timer_final_de_rounds >= 200 && timer_final_de_rounds < 380) {
            int resultadoRound = 1;
            if (ModoHistoria == 1) {
                if (P[1].Energy > P[2].Energy) { draw_sprite(LayerHUDa, spr_splash_youwin, 170, 190); }
            } //youwin
            if (ModoHistoria == 0) {
                if (P[1].Energy > P[2].Energy) { draw_sprite(LayerHUDa, spr_splash_p1win, 170, 190); }
            } //p1win
            if (ModoHistoria == 1) {
                if (P[1].Energy < P[2].Energy) { draw_sprite(LayerHUDa, spr_splash_youlose, 170, 190); }
            } //youlose
            if (ModoHistoria == 0) {
                if (P[1].Energy < P[2].Energy) { draw_sprite(LayerHUDa, spr_splash_p2win, 170, 190); }
            } //p2win
            if (P[1].Energy == P[2].Energy) {
                draw_sprite(LayerHUDa, spr_splash_draw, 170, 190); //draw
                if (timer_final_de_rounds > 300) { timer_final_de_rounds = EndRoundT; }
            } //acelera o reinicio do round em caso de draw
            if ((P[1].Energy == 1000 || P[2].Energy == 1000) && (P[1].Energy != P[2].Energy)) {
                draw_sprite(LayerHUDa, spr_splash_perfect, 170, 100);
                if (timer_final_de_rounds == 200) { play_sample(perfect, 255, 128, 1000, 0); }
            }
        }

        if (timer_final_de_rounds == 1) {
            if (P[1].Energy > P[2].Energy) {
                P[1].Round_Wins++;
                if (P[1].Energy == 1000) { P[1].Perfects++; }
            }
            if (P[1].Energy < P[2].Energy) {
                P[2].Round_Wins++;
                if (P[2].Energy == 1000) { P[2].Perfects++; }
            }
        }
    }

    //desenha molduras com transparencia
    drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    set_trans_blender(0, 0, 0, 77); //aprox 25% transparente
    if (RoundTotal >= 1) { draw_trans_sprite(LayerHUDa, spr_mold_results, 5+40*0+0, 45); }
    if (RoundTotal >= 2) { draw_trans_sprite(LayerHUDa, spr_mold_results, 5+40*1+1, 45); }
    if (RoundTotal >= 4) { draw_trans_sprite(LayerHUDa, spr_mold_results, 5+40*2+2, 45); }
    if (RoundTotal >= 1) { draw_trans_sprite(LayerHUDa, spr_mold_results, 640-5-40*1-1, 45); }
    if (RoundTotal >= 2) { draw_trans_sprite(LayerHUDa, spr_mold_results, 640-5-40*2-2, 45); }
    if (RoundTotal >= 4) { draw_trans_sprite(LayerHUDa, spr_mold_results, 640-5-40*3-3, 45); }
    solid_mode();
    if (P[1].Round_Wins >= 1) { draw_sprite(LayerHUDa, spr_result_win, 5+40*0+0, 45); }
    if (P[1].Round_Wins >= 2) { draw_sprite(LayerHUDa, spr_result_win, 5+40*1+1, 45); }
    if (P[1].Round_Wins >= 3) { draw_sprite(LayerHUDa, spr_result_win, 5+40*2+2, 45); }
    if (P[2].Round_Wins >= 1) { draw_sprite(LayerHUDa, spr_result_win, 640-5-40*1-1, 45); }
    if (P[2].Round_Wins >= 2) { draw_sprite(LayerHUDa, spr_result_win, 640-5-40*2-2, 45); }
    if (P[2].Round_Wins >= 3) { draw_sprite(LayerHUDa, spr_result_win, 640-5-40*3-3, 45); }
}
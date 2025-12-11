#include "char_select.h"

void GameLoop_SelectCharMode()
{
    if (timermenus == 0) { play_midi(bgm_select_screen, 1); } //bgm
    //atribui IDs de Navegação / Carrega primeira imagem BIG ao inicializar
    if (Qtde_Personagens_Instalados >= 1 && timermenus == 0) {
        SelectCharP1ID = 1;
        SelectCharP2ID = Qtde_Personagens_Instalados;
        if (ModoHistoria == 1) {
            strcpy(ChoiceP2, "-P2CPU-");
            strcpy(P[2].Name, "-P2CPU-");
            NumPersonagensEscolhidos = 1;
        }
        //BIG P1
        sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[1]);
        P1BIGDisplay = load_bitmap(P1BIGDisplaystring, NULL);
        if (!P1BIGDisplay) { P1BIGDisplay = load_bitmap("data/system/000_00.png", NULL); }
        //BIG P2
        if (strcmp(ChoiceP2, "-P2CPU-") != 0) {
            if (SelectCharP2ID == 1) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[1]);
            }
            if (SelectCharP2ID == 2) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[2]);
            }
            if (SelectCharP2ID == 3) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[3]);
            }
            if (SelectCharP2ID == 4) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[4]);
            }
            if (SelectCharP2ID == 5) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[5]);
            }
            if (SelectCharP2ID == 6) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[6]);
            }
            if (SelectCharP2ID == 7) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[7]);
            }
            if (SelectCharP2ID == 8) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[8]);
            }
            P2BIGDisplay = load_bitmap(P2BIGDisplaystring, NULL);
            if (!P2BIGDisplay) { P2BIGDisplay = load_bitmap("data/system/000_00.png", NULL); }
        }
    }

    if (timermenus == 15) {
        if (key[KEY_ESC]) {
            play_sample(back, 255, 128, 1000, 0);
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            timermenus = 0;
            NumPersonagensEscolhidos = 0;
            menu_op = 1;
            ApresentacaoMode = 1;
            SelectCharMode = 0;
            ModoHistoria = 0;
            play_midi(bgm_apresentacao, 1); //bgm
        }
        if (key[KEY_ALT] && key[KEY_F4]) { sair = 1; }

        //seleciona o personagem P1
        if (P[1].key_RIGHT_pressed == 1 && NumPersonagensEscolhidos < 2) { SelectCharP1ID++; }
        if (P[1].key_LEFT_pressed == 1 && NumPersonagensEscolhidos < 2) { SelectCharP1ID--; }
        char SelectCharP1Caminho[99];
        if (P[1].key_RIGHT_pressed == 1 && (strcmp(ChoiceP1, "") == 0)) {
            play_sample(cursor, 255, 128, 1000, 0);
            if (SelectCharP1ID > Qtde_Personagens_Instalados) SelectCharP1ID = 1;
            if (SelectCharP1ID == 1) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[1]);
            }
            if (SelectCharP1ID == 2) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[2]);
            }
            if (SelectCharP1ID == 3) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[3]);
            }
            if (SelectCharP1ID == 4) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[4]);
            }
            if (SelectCharP1ID == 5) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[5]);
            }
            if (SelectCharP1ID == 6) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[6]);
            }
            if (SelectCharP1ID == 7) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[7]);
            }
            if (SelectCharP1ID == 8) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[8]);
            }
            P1BIGDisplay = load_bitmap(P1BIGDisplaystring, NULL);
            if (!P1BIGDisplay) { P1BIGDisplay = load_bitmap("data/system/000_00.png", NULL); }
        }
        if (P[1].key_LEFT_pressed == 1 && (strcmp(ChoiceP1, "") == 0)) {
            play_sample(cursor, 255, 128, 1000, 0);
            if (SelectCharP1ID < 1) SelectCharP1ID = Qtde_Personagens_Instalados;
            if (SelectCharP1ID == 8) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[8]);
            }
            if (SelectCharP1ID == 7) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[7]);
            }
            if (SelectCharP1ID == 6) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[6]);
            }
            if (SelectCharP1ID == 5) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[5]);
            }
            if (SelectCharP1ID == 4) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[4]);
            }
            if (SelectCharP1ID == 3) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[3]);
            }
            if (SelectCharP1ID == 2) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[2]);
            }
            if (SelectCharP1ID == 1) {
                sprintf(P1BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[1]);
            }
            P1BIGDisplay = load_bitmap(P1BIGDisplaystring, NULL);
            if (!P1BIGDisplay) { P1BIGDisplay = load_bitmap("data/system/000_00.png", NULL); }
        }

        //seleciona o personagem P2
        if (P[2].key_RIGHT_pressed == 1 && NumPersonagensEscolhidos < 2) { SelectCharP2ID++; }
        if (P[2].key_LEFT_pressed == 1 && NumPersonagensEscolhidos < 2) { SelectCharP2ID--; }
        if (P[2].key_RIGHT_pressed == 1 && (strcmp(ChoiceP2, "") == 0)) {
            play_sample(cursor, 255, 128, 1000, 0);
            if (SelectCharP2ID > Qtde_Personagens_Instalados) SelectCharP2ID = 1;
            if (SelectCharP2ID == 1) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[1]);
            }
            if (SelectCharP2ID == 2) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[2]);
            }
            if (SelectCharP2ID == 3) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[3]);
            }
            if (SelectCharP2ID == 4) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[4]);
            }
            if (SelectCharP2ID == 5) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[5]);
            }
            if (SelectCharP2ID == 6) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[6]);
            }
            if (SelectCharP2ID == 7) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[7]);
            }
            if (SelectCharP2ID == 8) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[8]);
            }
            P2BIGDisplay = load_bitmap(P2BIGDisplaystring, NULL);
            if (!P2BIGDisplay) { P2BIGDisplay = load_bitmap("data/system/000_00.png", NULL); }
        }
        if (P[2].key_LEFT_pressed == 1 && (strcmp(ChoiceP2, "") == 0)) {
            play_sample(cursor, 255, 128, 1000, 0);
            if (SelectCharP2ID < 1) SelectCharP2ID = Qtde_Personagens_Instalados;
            if (SelectCharP2ID == 8) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[8]);
            }
            if (SelectCharP2ID == 7) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[7]);
            }
            if (SelectCharP2ID == 6) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[6]);
            }
            if (SelectCharP2ID == 5) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[5]);
            }
            if (SelectCharP2ID == 4) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[4]);
            }
            if (SelectCharP2ID == 3) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[3]);
            }
            if (SelectCharP2ID == 2) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[2]);
            }
            if (SelectCharP2ID == 1) {
                sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", Lista_de_Personagens_Instalados[1]);
            }
            P2BIGDisplay = load_bitmap(P2BIGDisplaystring, NULL);
            if (!P2BIGDisplay) { P2BIGDisplay = load_bitmap("data/system/000_00.png", NULL); }
        }
    }

    //define nome dos personagens
    //P1 name
    char SelectCharP1Caminho[99];
    if (SelectCharP1ID == 1) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[1]);
    }
    if (SelectCharP1ID == 2) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[2]);
    }
    if (SelectCharP1ID == 3) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[3]);
    }
    if (SelectCharP1ID == 4) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[4]);
    }
    if (SelectCharP1ID == 5) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[5]);
    }
    if (SelectCharP1ID == 6) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[6]);
    }
    if (SelectCharP1ID == 7) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[7]);
    }
    if (SelectCharP1ID == 8) {
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[8]);
    }
    set_config_file(SelectCharP1Caminho);
    strcpy(P[1].Name_Display, (char *)get_config_string("Info", "Name", "-"));
    //P2 name
    char SelectCharP2Caminho[99];
    if (SelectCharP2ID == 1) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[1]);
    }
    if (SelectCharP2ID == 2) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[2]);
    }
    if (SelectCharP2ID == 3) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[3]);
    }
    if (SelectCharP2ID == 4) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[4]);
    }
    if (SelectCharP2ID == 5) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[5]);
    }
    if (SelectCharP2ID == 6) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[6]);
    }
    if (SelectCharP2ID == 7) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[7]);
    }
    if (SelectCharP2ID == 8) {
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", Lista_de_Personagens_Instalados[8]);
    }
    set_config_file(SelectCharP2Caminho);
    strcpy(P[2].Name_Display, (char *)get_config_string("Info", "Name", "-"));

    SelectCharTimerAnim++;
    if (SelectCharTimerAnim > 5) { SelectCharTimerAnim = 0; } //usado para animar o cursor e elementos da tela
    draw_sprite(bufferx, SELECT_CHARS, 0, 0); //bg
    if (NumPersonagensEscolhidos < 2) {
        if (strcmp(IDIOMA, "US") == 0) {
            textprintf_centre_ex(bufferx, font_20, 323, 5, makecol(000, 000, 000), -1, "Select your Character");
            //sombra do texto
            textprintf_centre_ex(bufferx, font_20, 320, 2, makecol(255, 255, 255), -1, "Select your Character"); //texto
        }
        if (strcmp(IDIOMA, "BR") == 0) {
            textprintf_centre_ex(bufferx, font_20, 323, 5, makecol(000, 000, 000), -1, "Escolha seu Personagem");
            //sombra do texto
            textprintf_centre_ex(bufferx, font_20, 320, 2, makecol(255, 255, 255), -1, "Escolha seu Personagem");
            //texto
        }
    }

    //miniaturas
    if (NumPersonagensEscolhidos < 2) {
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*0), 400);
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*1), 400);
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*2), 400);
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*3), 400);
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*4), 400);
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*5), 400);
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*6), 400);
        draw_sprite(bufferx, spr_cursor_vazio, 64+(64*7), 400);
        if (Qtde_Personagens_Instalados >= 1) { draw_sprite(bufferx, MINIsprDisplay[1], 64+(64*0), 400); }
        if (Qtde_Personagens_Instalados >= 2) { draw_sprite(bufferx, MINIsprDisplay[2], 64+(64*1), 400); }
        if (Qtde_Personagens_Instalados >= 3) { draw_sprite(bufferx, MINIsprDisplay[3], 64+(64*2), 400); }
        if (Qtde_Personagens_Instalados >= 4) { draw_sprite(bufferx, MINIsprDisplay[4], 64+(64*3), 400); }
        if (Qtde_Personagens_Instalados >= 5) { draw_sprite(bufferx, MINIsprDisplay[5], 64+(64*4), 400); }
        if (Qtde_Personagens_Instalados >= 6) { draw_sprite(bufferx, MINIsprDisplay[6], 64+(64*5), 400); }
        if (Qtde_Personagens_Instalados >= 7) { draw_sprite(bufferx, MINIsprDisplay[7], 64+(64*6), 400); }
        if (Qtde_Personagens_Instalados >= 8) { draw_sprite(bufferx, MINIsprDisplay[8], 64+(64*7), 400); }
    }

    //seleciona o cenario
    if (Qtde_Cenarios_Instalados >= 1 && NumPersonagensEscolhidos == 2) {
        //ponteiro gps
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2) {
            draw_sprite(bufferx, spr_ponteiro, MapCenterX+MapPosX-16, MapCenterY+MapPosY-16);
        } //16 pq o ponteiro tem 32x32px

        draw_sprite(bufferx, SELECT_BG, 20, 405);
        if (strcmp(IDIOMA, "US") == 0) {
            textprintf_centre_ex(bufferx, font_20, 323, 410, makecol(000, 000, 000), -1, "Background Choice");
            textprintf_centre_ex(bufferx, font_20, 320, 407, makecol(255, 255, 255), -1, "Background Choice");
        }
        if (strcmp(IDIOMA, "BR") == 0) {
            textprintf_centre_ex(bufferx, font_20, 323, 410, makecol(000, 000, 000), -1, "Escolha o Cenario");
            textprintf_centre_ex(bufferx, font_20, 320, 407, makecol(255, 255, 255), -1, "Escolha o Cenario");
        }

        //desenha nome do cenario na tela
        set_config_file("SETUP.ini");
        char bg_read[40] = "";
        if (SelectBGID == 1) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg1", "")); }
        if (SelectBGID == 2) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg2", "")); }
        if (SelectBGID == 3) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg3", "")); }
        if (SelectBGID == 4) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg4", "")); }
        if (SelectBGID == 5) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg5", "")); }
        if (SelectBGID == 6) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg6", "")); }
        if (SelectBGID == 7) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg7", "")); }
        if (SelectBGID == 8) { strcpy(bg_read, (char *)get_config_string("BACKGROUNDS", "bg8", "")); }
        textprintf_centre_ex(bufferx, font_20, 322, 439, makecol(000, 000, 000), -1, "%s", bg_read);
        textprintf_centre_ex(bufferx, font_20, 320, 437, makecol(255, 255, 000), -1, "%s", bg_read);
    }

    //escolha dos personagens
    //p1
    if (timermenus >= 15 && NumPersonagensEscolhidos < 2 && (
            P[1].key_BT1_pressed == 1 || P[1].key_BT2_pressed == 1 || P[1].key_BT3_pressed == 1 || P[1].
            key_SELECT_pressed == 1 ||
            P[1].key_BT4_pressed == 1 || P[1].key_BT5_pressed == 1 || P[1].key_BT6_pressed == 1 || P[1].
            key_START_pressed == 1)) {
        if (strcmp(ChoiceP1, "") == 0) {
            NumPersonagensEscolhidos++;
            play_sample(choice, 255, 128, 1000, 0);
        }
        if (SelectCharP1ID == 1) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[1]); }
        if (SelectCharP1ID == 2) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[2]); }
        if (SelectCharP1ID == 3) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[3]); }
        if (SelectCharP1ID == 4) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[4]); }
        if (SelectCharP1ID == 5) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[5]); }
        if (SelectCharP1ID == 6) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[6]); }
        if (SelectCharP1ID == 7) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[7]); }
        if (SelectCharP1ID == 8) { strcpy(ChoiceP1, Lista_de_Personagens_Instalados[8]); }
        //carrega o tipo grafico do personagem
        char SelectCharP1Caminho[99];
        sprintf(SelectCharP1Caminho, "data/chars/%s/char.ini", ChoiceP1);
        set_config_file(SelectCharP1Caminho);
        P[1].Type = get_config_int("Info", "Type", 1);
        //verifica se o personagem possui paleta de cores
        sprintf(P1_Pallete_string, "data/chars/%s/pallete.png", ChoiceP1);
        P1_Pallete = load_bitmap(P1_Pallete_string, NULL);
        if (!P1_Pallete) { P[1].PossuiPaletaDeCor = 0; } else { P[1].PossuiPaletaDeCor = 1; }
        //define a cor do personagem, se ele tiver paleta de cores
        if (P[1].PossuiPaletaDeCor == 1) {
            if (P[1].key_BT1_pressed == 1) { P[1].DefineCorDaPaleta = 0; }
            if (P[1].key_BT2_pressed == 1) { P[1].DefineCorDaPaleta = 1; }
            if (P[1].key_BT3_pressed == 1) { P[1].DefineCorDaPaleta = 2; }
            if (P[1].key_BT4_pressed == 1) { P[1].DefineCorDaPaleta = 3; }
            if (P[1].key_BT5_pressed == 1) { P[1].DefineCorDaPaleta = 4; }
            if (P[1].key_BT6_pressed == 1) { P[1].DefineCorDaPaleta = 5; }
            if (P[1].key_SELECT_pressed == 1) { P[1].DefineCorDaPaleta = 6; }
            if (P[1].key_START_pressed == 1) { P[1].DefineCorDaPaleta = 7; }
            //if(P[1].key_HOLD_pressed   ==1) { P[1].DefineCorDaPaleta=8; } //precisa ser implementado
        }

        //---
        //atualiza tabela de golpes especiais - magias - special

        //zera o array dos especiais
        for (int indx = 0; indx <= 9; indx++) {
            for (int ind = 0; ind <= 16; ind++) {
                P[1].Special_Inputs_c[indx][ind] = 0;
                P[1].Special_Inputs_b[indx][ind] = 0;
                P[1].Special_Inputs[indx][ind] = 0;
            }
        }

        char StrSpecialInput[99];
        sprintf(StrSpecialInput, "data/chars/%s/special.ini", ChoiceP1);
        set_config_file(StrSpecialInput);
        char str[4];
        //carrega os inputs dos especiais
        for (int ind = 0; ind <= 9; ind++) {
            if (ind == 0) { sprintf(str, "700"); }
            if (ind == 1) { sprintf(str, "710"); }
            if (ind == 2) { sprintf(str, "720"); }
            if (ind == 3) { sprintf(str, "730"); }
            if (ind == 4) { sprintf(str, "740"); }
            if (ind == 5) { sprintf(str, "750"); }
            if (ind == 6) { sprintf(str, "760"); }
            if (ind == 7) { sprintf(str, "770"); }
            if (ind == 8) { sprintf(str, "780"); }
            if (ind == 9) { sprintf(str, "790"); }
            P[1].Special_Inputs_c[ind][1] = get_config_int(str, "c1", 0); //0 é neutro
            P[1].Special_Inputs_c[ind][2] = get_config_int(str, "c2", 0);
            P[1].Special_Inputs_c[ind][3] = get_config_int(str, "c3", 0);
            P[1].Special_Inputs_c[ind][4] = get_config_int(str, "c4", 0);
            P[1].Special_Inputs_c[ind][5] = get_config_int(str, "c5", 0);
            P[1].Special_Inputs_c[ind][6] = get_config_int(str, "c6", 0);
            P[1].Special_Inputs_c[ind][7] = get_config_int(str, "c7", 0);
            P[1].Special_Inputs_c[ind][8] = get_config_int(str, "c8", 0);
            P[1].Special_Inputs_c[ind][9] = get_config_int(str, "c9", 0);
            P[1].Special_Inputs_c[ind][10] = get_config_int(str, "c10", 0);
            P[1].Special_Inputs_c[ind][11] = get_config_int(str, "c11", 0);
            P[1].Special_Inputs_c[ind][12] = get_config_int(str, "c12", 0);
            P[1].Special_Inputs_c[ind][13] = get_config_int(str, "c13", 0);
            P[1].Special_Inputs_c[ind][14] = get_config_int(str, "c14", 0);
            P[1].Special_Inputs_c[ind][15] = get_config_int(str, "c15", 0);
            P[1].Special_Inputs_c[ind][16] = get_config_int(str, "c16", 0);
            P[1].Special_Inputs_b[ind][1] = get_config_int(str, "b1", 0) * -1; //0 é neutro
            P[1].Special_Inputs_b[ind][2] = get_config_int(str, "b2", 0) * -1;
            P[1].Special_Inputs_b[ind][3] = get_config_int(str, "b3", 0) * -1;
            P[1].Special_Inputs_b[ind][4] = get_config_int(str, "b4", 0) * -1;
            P[1].Special_Inputs_b[ind][5] = get_config_int(str, "b5", 0) * -1;
            P[1].Special_Inputs_b[ind][6] = get_config_int(str, "b6", 0) * -1;
            P[1].Special_Inputs_b[ind][7] = get_config_int(str, "b7", 0) * -1;
            P[1].Special_Inputs_b[ind][8] = get_config_int(str, "b8", 0) * -1;
            P[1].Special_Inputs_b[ind][9] = get_config_int(str, "b9", 0) * -1;
            P[1].Special_Inputs_b[ind][10] = get_config_int(str, "b10", 0) * -1;
            P[1].Special_Inputs_b[ind][11] = get_config_int(str, "b11", 0) * -1;
            P[1].Special_Inputs_b[ind][12] = get_config_int(str, "b12", 0) * -1;
            P[1].Special_Inputs_b[ind][13] = get_config_int(str, "b13", 0) * -1;
            P[1].Special_Inputs_b[ind][14] = get_config_int(str, "b14", 0) * -1;
            P[1].Special_Inputs_b[ind][15] = get_config_int(str, "b15", 0) * -1;
            P[1].Special_Inputs_b[ind][16] = get_config_int(str, "b16", 0) * -1;
        }

        //contagem da qtde de comandos e botoes
        for (int ind = 1; ind <= 16; ind++) {
            if (P[1].Special_Inputs_c[0][ind] != 0) { P[1].Special_Inputs_c[0][0]++; }
            if (P[1].Special_Inputs_b[0][ind] != 0) { P[1].Special_Inputs_b[0][0]++; }
            if (P[1].Special_Inputs_c[1][ind] != 0) { P[1].Special_Inputs_c[1][0]++; }
            if (P[1].Special_Inputs_b[1][ind] != 0) { P[1].Special_Inputs_b[1][0]++; }
            if (P[1].Special_Inputs_c[2][ind] != 0) { P[1].Special_Inputs_c[2][0]++; }
            if (P[1].Special_Inputs_b[2][ind] != 0) { P[1].Special_Inputs_b[2][0]++; }
            if (P[1].Special_Inputs_c[3][ind] != 0) { P[1].Special_Inputs_c[3][0]++; }
            if (P[1].Special_Inputs_b[3][ind] != 0) { P[1].Special_Inputs_b[3][0]++; }
            if (P[1].Special_Inputs_c[4][ind] != 0) { P[1].Special_Inputs_c[4][0]++; }
            if (P[1].Special_Inputs_b[4][ind] != 0) { P[1].Special_Inputs_b[4][0]++; }
            if (P[1].Special_Inputs_c[5][ind] != 0) { P[1].Special_Inputs_c[5][0]++; }
            if (P[1].Special_Inputs_b[5][ind] != 0) { P[1].Special_Inputs_b[5][0]++; }
            if (P[1].Special_Inputs_c[6][ind] != 0) { P[1].Special_Inputs_c[6][0]++; }
            if (P[1].Special_Inputs_b[6][ind] != 0) { P[1].Special_Inputs_b[6][0]++; }
            if (P[1].Special_Inputs_c[7][ind] != 0) { P[1].Special_Inputs_c[7][0]++; }
            if (P[1].Special_Inputs_b[7][ind] != 0) { P[1].Special_Inputs_b[7][0]++; }
            if (P[1].Special_Inputs_c[8][ind] != 0) { P[1].Special_Inputs_c[8][0]++; }
            if (P[1].Special_Inputs_b[8][ind] != 0) { P[1].Special_Inputs_b[8][0]++; }
            if (P[1].Special_Inputs_c[9][ind] != 0) { P[1].Special_Inputs_c[9][0]++; }
            if (P[1].Special_Inputs_b[9][ind] != 0) { P[1].Special_Inputs_b[9][0]++; }
        }

        //input combinado
        for (int indx = 0; indx <= 9; indx++) {
            for (int ind = 1; ind <= P[1].Special_Inputs_c[indx][0]; ind++) {
                P[1].Special_Inputs[indx][ind] = P[1].Special_Inputs_c[indx][ind];
            }
            for (int ind = 1; ind <= P[1].Special_Inputs_b[indx][0]; ind++) {
                P[1].Special_Inputs[indx][ind + P[1].Special_Inputs_c[indx][0]] = P[1].Special_Inputs_b[indx][ind];
            }
            P[1].Special_Inputs[indx][0] = P[1].Special_Inputs_c[indx][0] + P[1].Special_Inputs_b[indx][0];
        }
        //---

        if (NumPersonagensEscolhidos == 2) {
            timermenus = 0;
            if (ModoHistoria == 1) { timermenus = 15; }
        }
    }
    //p2
    if (timermenus >= 15 && NumPersonagensEscolhidos < 2 && (
            P[2].key_BT1_pressed == 1 || P[2].key_BT2_pressed == 1 || P[2].key_BT3_pressed == 1 || P[2].
            key_SELECT_pressed == 1 ||
            P[2].key_BT4_pressed == 1 || P[2].key_BT5_pressed == 1 || P[2].key_BT6_pressed == 1 || P[2].
            key_START_pressed == 1)) {
        if (strcmp(ChoiceP2, "") == 0) {
            NumPersonagensEscolhidos++;
            play_sample(choice, 255, 128, 1000, 0);
        }
        if (SelectCharP2ID == 1) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[1]); }
        if (SelectCharP2ID == 2) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[2]); }
        if (SelectCharP2ID == 3) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[3]); }
        if (SelectCharP2ID == 4) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[4]); }
        if (SelectCharP2ID == 5) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[5]); }
        if (SelectCharP2ID == 6) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[6]); }
        if (SelectCharP2ID == 7) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[7]); }
        if (SelectCharP2ID == 8) { strcpy(ChoiceP2, Lista_de_Personagens_Instalados[8]); }
        //carrega o tipo grafico do personagem
        char SelectCharP2Caminho[99];
        sprintf(SelectCharP2Caminho, "data/chars/%s/char.ini", ChoiceP2);
        set_config_file(SelectCharP2Caminho);
        P[2].Type = get_config_int("Info", "Type", 1);
        //verifica se o personagem possui paleta de cores
        sprintf(P2_Pallete_string, "data/chars/%s/pallete.png", ChoiceP2);
        P2_Pallete = load_bitmap(P2_Pallete_string, NULL);
        if (!P2_Pallete) { P[2].PossuiPaletaDeCor = 0; } else { P[2].PossuiPaletaDeCor = 1; }
        //define a cor do personagem, se ele tiver paleta de cores
        if (P[2].PossuiPaletaDeCor == 1) {
            if (P[2].key_BT1_pressed == 1) { P[2].DefineCorDaPaleta = 0; }
            if (P[2].key_BT2_pressed == 1) { P[2].DefineCorDaPaleta = 1; }
            if (P[2].key_BT3_pressed == 1) { P[2].DefineCorDaPaleta = 2; }
            if (P[2].key_BT4_pressed == 1) { P[2].DefineCorDaPaleta = 3; }
            if (P[2].key_BT5_pressed == 1) { P[2].DefineCorDaPaleta = 4; }
            if (P[2].key_BT6_pressed == 1) { P[2].DefineCorDaPaleta = 5; }
            if (P[2].key_SELECT_pressed == 1) { P[2].DefineCorDaPaleta = 6; }
            if (P[2].key_START_pressed == 1) { P[2].DefineCorDaPaleta = 7; }
            //if(P[2].key_HOLD_pressed   ==1) { P[2].DefineCorDaPaleta=8; } //precisa ser implementado
        }

        //---
        //atualiza tabela de golpes especiais - magias - special

        //zera o array dos especiais
        for (int indx = 0; indx <= 9; indx++) {
            for (int ind = 0; ind <= 16; ind++) {
                P[2].Special_Inputs_c[indx][ind] = 0;
                P[2].Special_Inputs_b[indx][ind] = 0;
                P[2].Special_Inputs[indx][ind] = 0;
            }
        }

        char StrSpecialInput[99];
        sprintf(StrSpecialInput, "data/chars/%s/special.ini", ChoiceP2);
        set_config_file(StrSpecialInput);
        char str[4];
        //carrega os inputs dos especiais
        for (int ind = 0; ind <= 9; ind++) {
            if (ind == 0) { sprintf(str, "700"); }
            if (ind == 1) { sprintf(str, "710"); }
            if (ind == 2) { sprintf(str, "720"); }
            if (ind == 3) { sprintf(str, "730"); }
            if (ind == 4) { sprintf(str, "740"); }
            if (ind == 5) { sprintf(str, "750"); }
            if (ind == 6) { sprintf(str, "760"); }
            if (ind == 7) { sprintf(str, "770"); }
            if (ind == 8) { sprintf(str, "780"); }
            if (ind == 9) { sprintf(str, "790"); }
            P[2].Special_Inputs_c[ind][1] = get_config_int(str, "c1", 0); //0 é neutro
            P[2].Special_Inputs_c[ind][2] = get_config_int(str, "c2", 0);
            P[2].Special_Inputs_c[ind][3] = get_config_int(str, "c3", 0);
            P[2].Special_Inputs_c[ind][4] = get_config_int(str, "c4", 0);
            P[2].Special_Inputs_c[ind][5] = get_config_int(str, "c5", 0);
            P[2].Special_Inputs_c[ind][6] = get_config_int(str, "c6", 0);
            P[2].Special_Inputs_c[ind][7] = get_config_int(str, "c7", 0);
            P[2].Special_Inputs_c[ind][8] = get_config_int(str, "c8", 0);
            P[2].Special_Inputs_c[ind][9] = get_config_int(str, "c9", 0);
            P[2].Special_Inputs_c[ind][10] = get_config_int(str, "c10", 0);
            P[2].Special_Inputs_c[ind][11] = get_config_int(str, "c11", 0);
            P[2].Special_Inputs_c[ind][12] = get_config_int(str, "c12", 0);
            P[2].Special_Inputs_c[ind][13] = get_config_int(str, "c13", 0);
            P[2].Special_Inputs_c[ind][14] = get_config_int(str, "c14", 0);
            P[2].Special_Inputs_c[ind][15] = get_config_int(str, "c15", 0);
            P[2].Special_Inputs_c[ind][16] = get_config_int(str, "c16", 0);
            P[2].Special_Inputs_b[ind][1] = get_config_int(str, "b1", 0) * -1; //0 é neutro
            P[2].Special_Inputs_b[ind][2] = get_config_int(str, "b2", 0) * -1;
            P[2].Special_Inputs_b[ind][3] = get_config_int(str, "b3", 0) * -1;
            P[2].Special_Inputs_b[ind][4] = get_config_int(str, "b4", 0) * -1;
            P[2].Special_Inputs_b[ind][5] = get_config_int(str, "b5", 0) * -1;
            P[2].Special_Inputs_b[ind][6] = get_config_int(str, "b6", 0) * -1;
            P[2].Special_Inputs_b[ind][7] = get_config_int(str, "b7", 0) * -1;
            P[2].Special_Inputs_b[ind][8] = get_config_int(str, "b8", 0) * -1;
            P[2].Special_Inputs_b[ind][9] = get_config_int(str, "b9", 0) * -1;
            P[2].Special_Inputs_b[ind][10] = get_config_int(str, "b10", 0) * -1;
            P[2].Special_Inputs_b[ind][11] = get_config_int(str, "b11", 0) * -1;
            P[2].Special_Inputs_b[ind][12] = get_config_int(str, "b12", 0) * -1;
            P[2].Special_Inputs_b[ind][13] = get_config_int(str, "b13", 0) * -1;
            P[2].Special_Inputs_b[ind][14] = get_config_int(str, "b14", 0) * -1;
            P[2].Special_Inputs_b[ind][15] = get_config_int(str, "b15", 0) * -1;
            P[2].Special_Inputs_b[ind][16] = get_config_int(str, "b16", 0) * -1;
        }

        //contagem da qtde de comandos e botoes
        for (int ind = 1; ind <= 16; ind++) {
            if (P[2].Special_Inputs_c[0][ind] != 0) { P[2].Special_Inputs_c[0][0]++; }
            if (P[2].Special_Inputs_b[0][ind] != 0) { P[2].Special_Inputs_b[0][0]++; }
            if (P[2].Special_Inputs_c[1][ind] != 0) { P[2].Special_Inputs_c[1][0]++; }
            if (P[2].Special_Inputs_b[1][ind] != 0) { P[2].Special_Inputs_b[1][0]++; }
            if (P[2].Special_Inputs_c[2][ind] != 0) { P[2].Special_Inputs_c[2][0]++; }
            if (P[2].Special_Inputs_b[2][ind] != 0) { P[2].Special_Inputs_b[2][0]++; }
            if (P[2].Special_Inputs_c[3][ind] != 0) { P[2].Special_Inputs_c[3][0]++; }
            if (P[2].Special_Inputs_b[3][ind] != 0) { P[2].Special_Inputs_b[3][0]++; }
            if (P[2].Special_Inputs_c[4][ind] != 0) { P[2].Special_Inputs_c[4][0]++; }
            if (P[2].Special_Inputs_b[4][ind] != 0) { P[2].Special_Inputs_b[4][0]++; }
            if (P[2].Special_Inputs_c[5][ind] != 0) { P[2].Special_Inputs_c[5][0]++; }
            if (P[2].Special_Inputs_b[5][ind] != 0) { P[2].Special_Inputs_b[5][0]++; }
            if (P[2].Special_Inputs_c[6][ind] != 0) { P[2].Special_Inputs_c[6][0]++; }
            if (P[2].Special_Inputs_b[6][ind] != 0) { P[2].Special_Inputs_b[6][0]++; }
            if (P[2].Special_Inputs_c[7][ind] != 0) { P[2].Special_Inputs_c[7][0]++; }
            if (P[2].Special_Inputs_b[7][ind] != 0) { P[2].Special_Inputs_b[7][0]++; }
            if (P[2].Special_Inputs_c[8][ind] != 0) { P[2].Special_Inputs_c[8][0]++; }
            if (P[2].Special_Inputs_b[8][ind] != 0) { P[2].Special_Inputs_b[8][0]++; }
            if (P[2].Special_Inputs_c[9][ind] != 0) { P[2].Special_Inputs_c[9][0]++; }
            if (P[2].Special_Inputs_b[9][ind] != 0) { P[2].Special_Inputs_b[9][0]++; }
        }

        //input combinado
        for (int indx = 0; indx <= 9; indx++) {
            for (int ind = 1; ind <= P[2].Special_Inputs_c[indx][0]; ind++) {
                P[2].Special_Inputs[indx][ind] = P[2].Special_Inputs_c[indx][ind];
            }
            for (int ind = 1; ind <= P[2].Special_Inputs_b[indx][0]; ind++) {
                P[2].Special_Inputs[indx][ind + P[2].Special_Inputs_c[indx][0]] = P[2].Special_Inputs_b[indx][ind];
            }
            P[2].Special_Inputs[indx][0] = P[2].Special_Inputs_c[indx][0] + P[2].Special_Inputs_b[indx][0];
        }
        //---

        if (NumPersonagensEscolhidos == 2) { timermenus = 0; }
    }

    //atualiza gps do mapa
    if (Qtde_Cenarios_Instalados >= 1 && timermenus == 0) {
        char bg_choice_string[40];
        if (SelectBGID == 1) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[1]);
        }
        if (SelectBGID == 2) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[2]);
        }
        if (SelectBGID == 3) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[3]);
        }
        if (SelectBGID == 4) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[4]);
        }
        if (SelectBGID == 5) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[5]);
        }
        if (SelectBGID == 6) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[6]);
        }
        if (SelectBGID == 7) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[7]);
        }
        if (SelectBGID == 8) {
            sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[8]);
        }
        set_config_file(bg_choice_string);
        MapPosX = get_config_int("DATA", "MapPosX", 0);
        MapPosY = get_config_int("DATA", "MapPosY", 0);
    }

    //cursor p1
    if (strcmp(ChoiceP1, "") == 0) {
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 1) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*0), 400);
        }
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 2) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*1), 400);
        }
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 3) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*2), 400);
        }
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 4) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*3), 400);
        }
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 5) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*4), 400);
        }
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 6) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*5), 400);
        }
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 7) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*6), 400);
        }
        if (SelectCharTimerAnim >= 0 && SelectCharTimerAnim <= 2 && SelectCharP1ID == 8) {
            draw_sprite(bufferx, spr_p1_cursor, 64+(64*7), 400);
        }
    }
    //cursor p2
    if (strcmp(ChoiceP2, "") == 0) {
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 1) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*0), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 2) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*1), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 3) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*2), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 4) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*3), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 5) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*4), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 6) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*5), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 7) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*6), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 8) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*7), 400);
        }
        if (SelectCharTimerAnim >= 3 && SelectCharTimerAnim <= 5 && SelectCharP2ID == 9) {
            draw_sprite(bufferx, spr_p2_cursor, 64+(64*8), 400);
        }
    }
    //marcadores de selecao
    if (strcmp(ChoiceP1, "") == 0) { draw_sprite(bufferx, sel_mark_p1, 64+(64*(SelectCharP1ID-1)), 400); }
    if (strcmp(ChoiceP2, "") == 0) { draw_sprite(bufferx, sel_mark_p2, -32+64+(64*(SelectCharP2ID)), 449); }

    //BIG DISPLAYs
    //P1
    masked_stretch_blit(P1BIGDisplay, bufferx, 0, 0, 128, 128, 5, 140, 256, 256);
    //P2
    if (strcmp(ChoiceP2, "-P2CPU-") != 0) {
        clear_to_color(P2BIGDisplayInv, makecol(255, 0, 255));
        draw_sprite_h_flip(P2BIGDisplayInv, P2BIGDisplay, 0, 0);
        masked_stretch_blit(P2BIGDisplayInv, bufferx, 0, 0, 128, 128, 379, 140, 256, 256);
    }
    //nomes
    textprintf_ex(bufferx, font_10, 12, 382, makecol(000, 000, 000), -1, "%s", P[1].Name_Display);
    textprintf_ex(bufferx, font_10, 10, 380, makecol(255, 255, 255), -1, "%s", P[1].Name_Display);
    if (strcmp(ChoiceP2, "-P2CPU-") != 0) {
        textprintf_right_ex(bufferx, font_10, 632, 382, makecol(000, 000, 000), -1, "%s", P[2].Name_Display);
        textprintf_right_ex(bufferx, font_10, 630, 380, makecol(255, 255, 255), -1, "%s", P[2].Name_Display);
    }

    //escolha do cenario
    if (NumPersonagensEscolhidos == 2 && timermenus >= 15) {
        int AtualizaGPS = 0;
        if (((P[1].key_RIGHT_pressed == 1) || (P[2].key_RIGHT_pressed == 1)) && SelectBGID < Qtde_Cenarios_Instalados) {
            SelectBGID++;
            play_sample(cursor, 255, 128, 1000, 0);
            AtualizaGPS = 1;
        }
        if (((P[1].key_LEFT_pressed == 1) || (P[2].key_LEFT_pressed == 1)) && SelectBGID > 1) {
            SelectBGID--;
            play_sample(cursor, 255, 128, 1000, 0);
            AtualizaGPS = 1;
        }
        if (AtualizaGPS == 1) {
            AtualizaGPS = 0;
            char bg_choice_string[40];
            if (SelectBGID == 1) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[1]);
            }
            if (SelectBGID == 2) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[2]);
            }
            if (SelectBGID == 3) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[3]);
            }
            if (SelectBGID == 4) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[4]);
            }
            if (SelectBGID == 5) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[5]);
            }
            if (SelectBGID == 6) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[6]);
            }
            if (SelectBGID == 7) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[7]);
            }
            if (SelectBGID == 8) {
                sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", Lista_de_Cenarios_Instalados[8]);
            }
            set_config_file(bg_choice_string);
            MapPosX = get_config_int("DATA", "MapPosX", 0);
            MapPosY = get_config_int("DATA", "MapPosY", 0);
        }
        if (strcmp(ChoiceP2, "-P2CPU-") == 0) {
            //estamos no modo arcade
            TelaDeVersusTimer = 0;
            strcpy(P[1].Name, ChoiceP1);
            if (Estagio_Atual == 1) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[1]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[1]);
            }
            if (Estagio_Atual == 2) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[2]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[2]);
            }
            if (Estagio_Atual == 3) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[3]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[3]);
            }
            if (Estagio_Atual == 4) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[4]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[4]);
            }
            if (Estagio_Atual == 5) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[5]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[5]);
            }
            if (Estagio_Atual == 6) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[6]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[6]);
            }
            if (Estagio_Atual == 7) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[7]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[7]);
            }
            if (Estagio_Atual == 8) {
                strcpy(P[2].Name, Lista_de_Personagens_ArcadeMode[8]);
                strcpy(ChoiceBG, Lista_de_Cenarios_ArcadeMode[8]);
            }
            strcpy(ChoiceP1, "");
            strcpy(ChoiceP2, "");
            timermenus = 0;
            NumPersonagensEscolhidos = 0;
            menu_op = 1;
            ModoMapa = 1;
            SelectCharMode = 0;
        }

        if (strcmp(ChoiceBG, "") == 0 &&
            (P[1].key_BT1_pressed == 1 || P[1].key_BT2_pressed == 1 || P[1].key_BT3_pressed == 1 ||
             P[1].key_BT4_pressed == 1 || P[1].key_BT5_pressed == 1 || P[1].key_BT6_pressed == 1 || P[1].
             key_START_pressed == 1 ||
             P[2].key_BT1_pressed == 1 || P[2].key_BT2_pressed == 1 || P[2].key_BT3_pressed == 1 ||
             P[2].key_BT4_pressed == 1 || P[2].key_BT5_pressed == 1 || P[2].key_BT6_pressed == 1 || P[2].
             key_START_pressed == 1)) {
            play_sample(choice, 255, 128, 1000, 0);
            if (SelectBGID == 1) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[1]); }
            if (SelectBGID == 2) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[2]); }
            if (SelectBGID == 3) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[3]); }
            if (SelectBGID == 4) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[4]); }
            if (SelectBGID == 5) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[5]); }
            if (SelectBGID == 6) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[6]); }
            if (SelectBGID == 7) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[7]); }
            if (SelectBGID == 8) { strcpy(ChoiceBG, Lista_de_Cenarios_Instalados[8]); }

            //posiciona os players

            //cenario, atribuicao
            for (int ind = 1; ind <= 8; ind++) {
                if (SelectBGID == ind) {
                    bg_test->w = bg_hamoopi[ind]->w;
                    bg_test->h = bg_hamoopi[ind]->h;
                    blit(bg_hamoopi[ind], bg_test, 0, 0, 0, 0, bg_hamoopi[ind]->w, bg_hamoopi[ind]->h);
                }
            }

            //posicao dos players
            P[1].x = bg_test->w / 2 - 80;
            P[2].x = bg_test->w / 2 + 80;
            AlturaPiso = bg_test->h - 20;
            P[1].y = AlturaPiso;
            P[2].y = AlturaPiso;
            P[1].State = 100;
            P[2].State = 100; //define estado inicial
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

            ///SAIR PARA A PROXIMA TELA///
            if (strcmp(ChoiceP2, "-P2CPU-") != 0) {
                //estamos no modo versus
                TelaDeVersusTimer = 0;
                strcpy(P[1].Name, ChoiceP1);
                strcpy(P[2].Name, ChoiceP2);
                strcpy(ChoiceP1, "");
                strcpy(ChoiceP2, "");
                timermenus = 0;
                NumPersonagensEscolhidos = 0;
                menu_op = 1;
                TelaDeVersus = 1;
                SelectCharMode = 0;
            }
        }
    }

    stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

#include "stage_select.h"

void GameLoop_ModoMapa() {
    if (timermenus == 0) { play_midi(bgm_versus_mode, 0); } //bgm
    if (key[KEY_ESC]) {
        play_sample(back, 255, 128, 1000, 0);
        timermenus = 0;
        menu_op = 1;
        ModoMapa = 0;
        SelectCharMode = 1;
        ModoHistoria = 1;
        strcpy(ChoiceP1, "");
        strcpy(ChoiceP2, "-P2CPU-");
        NumPersonagensEscolhidos = 1;
        SelectCharTimerAnim = 0;
        play_midi(bgm_select_screen, 1); //bgm
    }

    ModoMapaTimerAnim++;
    if (ModoMapaTimerAnim > 5) { ModoMapaTimerAnim = 0; } //usado para animar elementos da tela

    //define qual imagem mostrar para o P2
    sprintf(P2BIGDisplaystring, "data/chars/%s/000_00.png", P[2].Name);
    P2BIGDisplay = load_bitmap(P2BIGDisplaystring, NULL);
    if (!P2BIGDisplay) { P2BIGDisplay = load_bitmap("data/system/000_00.png", NULL); }

    draw_sprite(bufferx, SELECT_CHARS, 0, 0); //bg
    textprintf_centre_ex(bufferx, font_20, 323, 5, makecol(000, 000, 000), -1, "Proximo Oponente");
    textprintf_centre_ex(bufferx, font_20, 320, 2, makecol(255, 255, 255), -1, "Proximo Oponente");
    //miniaturas
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*0), 400);
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*1), 400);
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*2), 400);
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*3), 400);
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*4), 400);
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*5), 400);
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*6), 400);
    draw_sprite(bufferx, spr_cursor_vazio, 64+(64*7), 400);
    if (strcmp(Lista_de_Personagens_ArcadeMode[1], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[1], 64+(64*0), 400);
    }
    if (strcmp(Lista_de_Personagens_ArcadeMode[2], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[2], 64+(64*1), 400);
    }
    if (strcmp(Lista_de_Personagens_ArcadeMode[3], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[3], 64+(64*2), 400);
    }
    if (strcmp(Lista_de_Personagens_ArcadeMode[4], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[4], 64+(64*3), 400);
    }
    if (strcmp(Lista_de_Personagens_ArcadeMode[5], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[5], 64+(64*4), 400);
    }
    if (strcmp(Lista_de_Personagens_ArcadeMode[6], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[6], 64+(64*5), 400);
    }
    if (strcmp(Lista_de_Personagens_ArcadeMode[7], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[7], 64+(64*6), 400);
    }
    if (strcmp(Lista_de_Personagens_ArcadeMode[8], "") != 0) {
        draw_sprite(bufferx, MINIsprDisplayArcadeMode[8], 64+(64*7), 400);
    }

    //A animacao [spr_cursor_historia] esta desligada no momento
    //if (ModoMapaTimerAnim>=0 && ModoMapaTimerAnim<=4){
    if (Estagio_Atual == 1) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*0), 400); }
    if (Estagio_Atual == 2) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*1), 400); }
    if (Estagio_Atual == 3) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*2), 400); }
    if (Estagio_Atual == 4) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*3), 400); }
    if (Estagio_Atual == 5) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*4), 400); }
    if (Estagio_Atual == 6) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*5), 400); }
    if (Estagio_Atual == 7) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*6), 400); }
    if (Estagio_Atual == 8) { draw_sprite(bufferx, spr_cursor_historia, 64+(64*7), 400); }
    //}

    //desenha gps do mapa
    if (timermenus == 0) {
        char bg_choice_string[40];
        sprintf(bg_choice_string, "data/backgrounds/%s/config.ini", ChoiceBG);
        set_config_file(bg_choice_string);
        MapPosX = get_config_int("DATA", "MapPosX", 0);
        MapPosY = get_config_int("DATA", "MapPosY", 0);
    }
    if (ModoMapaTimerAnim >= 0 && ModoMapaTimerAnim <= 2) {
        draw_sprite(bufferx, spr_ponteiro, MapCenterX+MapPosX-16, MapCenterY+MapPosY-16); //16 pq o ponteiro tem 32x32px
    }

    //P1
    masked_stretch_blit(P1BIGDisplay, bufferx, 0, 0, 128, 128, 5, 140, 256, 256);
    //P2
    if (strcmp(ChoiceP2, "-P2CPU-") != 0) {
        clear_to_color(P2BIGDisplayInv, makecol(255, 0, 255));
        draw_sprite_h_flip(P2BIGDisplayInv, P2BIGDisplay, 0, 0);
        masked_stretch_blit(P2BIGDisplayInv, bufferx, 0, 0, 128, 128, 379, 140, 256, 256);
    }

    stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

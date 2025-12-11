#include "edit.h"

void GameLoop_EditMode() {
    if (key[KEY_ESC] && EditMode == 1) {
        play_sample(back, 255, 128, 1000, 0);
        FadeCtr = 255;
        FadeIN = 0;
        FadeOUT = 1;

        if (ED_alertsave == 1) {
            ED_save_charini();
        }
        timermenus = 0;
        ApresentacaoMode = 1;
        EditMode = 0;
        rest(100);
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
    //movimenta o player, dentro do editor
    if (ED_y > 50 / 2 && (P[1].key_W_status == 1 || P[1].key_W_status == 2)) { ED_y--; } //w
    if (ED_y < 470 / 2 && (P[1].key_S_status == 1 || P[1].key_S_status == 2)) { ED_y++; } //s
    if (ED_x > 180 / 2 && (P[1].key_A_status == 1 || P[1].key_A_status == 2)) { ED_x--; } //a
    if (ED_x < 630 / 2 && (P[1].key_D_status == 1 || P[1].key_D_status == 2)) { ED_x++; } //d
    //se segurar o shift, movimenta 1 pixel de cada vez.
    //o codigo abaixo anula o movimento ao manter pressionado,
    //mantendo entao apenas o deslocamento do key_pressed (key_status==1)
    if (ED_y > 50 / 2 && P[1].key_W_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) { ED_y++; } //w+shift
    if (ED_y < 470 / 2 && P[1].key_S_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) { ED_y--; } //s+shift
    if (ED_x > 180 / 2 && P[1].key_A_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) { ED_x++; } //a+shift
    if (ED_x < 630 / 2 && P[1].key_D_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) { ED_x--; } //d+shift
    //movimenta o eixo
    if (ED_MovimentaPivot == 1 && P[1].key_START_status == 1) {
        ED_alertsave2 = 1;
        ED_MovimentaPivot = 0;
    }
    if (ED_MovimentaPivot == 1) {
        int AuxEixoX = 0;
        int AuxEixoY = 0;
        if (ED_y > 50 / 2 && (P[1].key_UP_status == 1 || P[1].key_UP_status == 2)) {
            ED_YAlign++;
            AuxEixoY = -1;
        }
        if (ED_y < 470 / 2 && (P[1].key_DOWN_status == 1 || P[1].key_DOWN_status == 2)) {
            ED_YAlign--;
            AuxEixoY = +1;
        }
        if (ED_x > 180 / 2 && (P[1].key_LEFT_status == 1 || P[1].key_LEFT_status == 2)) {
            ED_XAlign++;
            AuxEixoX = -1;
        }
        if (ED_x < 630 / 2 && (P[1].key_RIGHT_status == 1 || P[1].key_RIGHT_status == 2)) {
            ED_XAlign--;
            AuxEixoX = +1;
        }
        //se segurar o shift, movimenta 1 pixel de cada vez.
        //o codigo abaixo anula o movimento ao manter pressionado,
        //mantendo entao apenas o deslocamento do key_pressed (key_status==1)
        if (ED_y > 50 / 2 && P[1].key_UP_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) {
            ED_YAlign--;
            AuxEixoY = +1;
        }
        if (ED_y < 470 / 2 && P[1].key_DOWN_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) {
            ED_YAlign++;
            AuxEixoY = -1;
        }
        if (ED_x > 180 / 2 && P[1].key_LEFT_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) {
            ED_XAlign--;
            AuxEixoX = +1;
        }
        if (ED_x < 630 / 2 && P[1].key_RIGHT_status == 2 && (key[KEY_LSHIFT] || key[KEY_RSHIFT])) {
            ED_XAlign++;
            AuxEixoX = -1;
        }
    }

    //Inicializa as variaveis do Editor
    if (EditModeTime == 0) {
        ED_inicializar();
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/000_01.png", P[1].Name);
        ED_Mini = load_bitmap(ED_Caminho, NULL);
        if (!ED_Mini) { ED_Mini = load_bitmap("data/system/000_01.png", NULL); }
    }

    //botoes para alterar os STATES
    if (key_Mouse_L_status == 1 && mouse_x > 5 && mouse_x < 81 && mouse_y > 120 && mouse_y < 150) //Recuar States L
    {
        MovPossiveisIndex--;
        if (MovPossiveisIndex < 0) { MovPossiveisIndex = 0; }
        ED_CarregarDados = 1;
    }
    if (key_Mouse_R_status == 1 && mouse_x > 5 && mouse_x < 81 && mouse_y > 120 && mouse_y < 150) //Recuar States R
    {
        MovPossiveisIndex -= 10;
        if (MovPossiveisIndex < 0) { MovPossiveisIndex = 0; }
        ED_CarregarDados = 1;
    }

    if (key_Mouse_L_status == 1 && mouse_x > 88 && mouse_x < 165 && mouse_y > 120 && mouse_y < 150) //Avançar States L
    {
        MovPossiveisIndex++;
        if (MovPossiveis[MovPossiveisIndex] == 0) { MovPossiveisIndex--; }
        ED_CarregarDados = 1;
    }
    if (key_Mouse_R_status == 1 && mouse_x > 88 && mouse_x < 165 && mouse_y > 120 && mouse_y < 150) //Avançar States R
    {
        MovPossiveisIndex += 10;
        if (MovPossiveis[MovPossiveisIndex] == 0) { MovPossiveisIndex -= 10; }
        ED_CarregarDados = 1;
    }

    if
    (
        ED_alertsave == 1 &&
        (
            (key_Mouse_L_status == 1 && mouse_x > 5 && mouse_x < 81 && mouse_y > 120 && mouse_y < 150) ||
            (key_Mouse_R_status == 1 && mouse_x > 5 && mouse_x < 81 && mouse_y > 120 && mouse_y < 150) ||
            (key_Mouse_L_status == 1 && mouse_x > 88 && mouse_x < 165 && mouse_y > 120 && mouse_y < 150) ||
            (key_Mouse_R_status == 1 && mouse_x > 88 && mouse_x < 165 && mouse_y > 120 && mouse_y < 150)
        )
    ) {
        ED_save_charini();
        ED_alertsave = 0;
    }

    if (ED_alertsave2 == 1) //salva o eixo, apos movimentacao do mesmo
    {
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
        set_config_file(ED_Caminho);
        char ED_State_s[16];
        sprintf(ED_State_s, "%i", ED_State);
        set_config_int(ED_State_s, "XAlign", ED_XAlign);
        set_config_int(ED_State_s, "YAlign", ED_YAlign);
        ED_alertsave2 = 0;
    }

    if (ED_CarregarDados == 1) {
        //verifica qtos frames existem na animacao selecionada
        int ED_tot[999];
        for (int ind = 100; ind <= 999; ind++) {
            if (MovPossiveis[MovPossiveisIndex] == ind) {
                ED_State = ind;
                ED_tot[ind] = -1;
                for (int i = 0; i <= 29; i++) {
                    char txt[50] = "";
                    if (i < 10) { sprintf(txt, "data/chars/%s/%i_0%i.png", ED_Name, ind, i); }
                    if (i >= 10) { sprintf(txt, "data/chars/%s/%i_%i.png", ED_Name, ind, i); }
                    if (exists(txt)) { ED_tot[ind]++; } else { i = 29; }
                    ED_TotalFrames = ED_tot[ind];
                }
            }
        }

        ED_load_charini();
        Draw_CHBoxes_ED();
        ED_CarregarDados = 0;
    }

    if (ED_MODE == 1) {
        if (key_Mouse_L_status == 1 && mouse_x > 5 && mouse_x < 55 && mouse_y > 60 && mouse_y < 110) //Draw Hurt Box
        {
            ED_Pause = 1;
            ED_MovimentaPivot = 0;
            ED_DrawBlueMode = 1;
            ED_DrawRedMode = 0;
            ED_bt_Null = 1;
            Draw_CHBoxes_ED();
        }
        if (key_Mouse_L_status == 1 && mouse_x > 60 && mouse_x < 110 && mouse_y > 60 && mouse_y < 110) //Draw Hit Box
        {
            ED_Pause = 1;
            ED_MovimentaPivot = 0;
            ED_DrawRedMode = 1;
            ED_DrawBlueMode = 0;
            ED_bt_Null = 1;
            Draw_CHBoxes_ED();
        }
        if (key_Mouse_L_status == 1 && mouse_x > 115 && mouse_x < 165 && mouse_y > 60 && mouse_y < 110) //Bt Null
        {
            ED_Pause = 0;
            ED_MovimentaPivot = 0;
            ED_DrawBlueMode = 0;
            ED_DrawRedMode = 0;
            ED_bt_Null = 0;
        }
    }

    if (key_Mouse_R_status == 1 && mouse_x > 170 && mouse_y > 40) {
        if (ED_DrawRedMode == 1) {
            char ED_Caminho[99];
            sprintf(ED_Caminho, "data/chars/%s/chbox.ini", P[1].Name);
            set_config_file(ED_Caminho);
            char ED_State_s[16];
            if (ED_IndexAnim < 10) { sprintf(ED_State_s, "%i_0%i", ED_State, ED_IndexAnim); }
            if (ED_IndexAnim >= 10) { sprintf(ED_State_s, "%i_%i", ED_State, ED_IndexAnim); }
            if (ED_HitBox_tot == 9) {
                ED_HitBox09x1 = -5555;
                ED_HitBox09y1 = -5555;
                ED_HitBox09x2 = -5555;
                ED_HitBox09y2 = -5555;
                set_config_int(ED_State_s, "HitBox09x1", ED_HitBox09x1);
                set_config_int(ED_State_s, "HitBox09y1", ED_HitBox09y1);
                set_config_int(ED_State_s, "HitBox09x2", ED_HitBox09x2);
                set_config_int(ED_State_s, "HitBox09y2", ED_HitBox09y2);
            } else if (ED_HitBox_tot == 8) {
                ED_HitBox08x1 = -5555;
                ED_HitBox08y1 = -5555;
                ED_HitBox08x2 = -5555;
                ED_HitBox08y2 = -5555;
                set_config_int(ED_State_s, "HitBox08x1", ED_HitBox08x1);
                set_config_int(ED_State_s, "HitBox08y1", ED_HitBox08y1);
                set_config_int(ED_State_s, "HitBox08x2", ED_HitBox08x2);
                set_config_int(ED_State_s, "HitBox08y2", ED_HitBox08y2);
            } else if (ED_HitBox_tot == 7) {
                ED_HitBox07x1 = -5555;
                ED_HitBox07y1 = -5555;
                ED_HitBox07x2 = -5555;
                ED_HitBox07y2 = -5555;
                set_config_int(ED_State_s, "HitBox07x1", ED_HitBox07x1);
                set_config_int(ED_State_s, "HitBox07y1", ED_HitBox07y1);
                set_config_int(ED_State_s, "HitBox07x2", ED_HitBox07x2);
                set_config_int(ED_State_s, "HitBox07y2", ED_HitBox07y2);
            } else if (ED_HitBox_tot == 6) {
                ED_HitBox06x1 = -5555;
                ED_HitBox06y1 = -5555;
                ED_HitBox06x2 = -5555;
                ED_HitBox06y2 = -5555;
                set_config_int(ED_State_s, "HitBox06x1", ED_HitBox06x1);
                set_config_int(ED_State_s, "HitBox06y1", ED_HitBox06y1);
                set_config_int(ED_State_s, "HitBox06x2", ED_HitBox06x2);
                set_config_int(ED_State_s, "HitBox06y2", ED_HitBox06y2);
            } else if (ED_HitBox_tot == 5) {
                ED_HitBox05x1 = -5555;
                ED_HitBox05y1 = -5555;
                ED_HitBox05x2 = -5555;
                ED_HitBox05y2 = -5555;
                set_config_int(ED_State_s, "HitBox05x1", ED_HitBox05x1);
                set_config_int(ED_State_s, "HitBox05y1", ED_HitBox05y1);
                set_config_int(ED_State_s, "HitBox05x2", ED_HitBox05x2);
                set_config_int(ED_State_s, "HitBox05y2", ED_HitBox05y2);
            } else if (ED_HitBox_tot == 4) {
                ED_HitBox04x1 = -5555;
                ED_HitBox04y1 = -5555;
                ED_HitBox04x2 = -5555;
                ED_HitBox04y2 = -5555;
                set_config_int(ED_State_s, "HitBox04x1", ED_HitBox04x1);
                set_config_int(ED_State_s, "HitBox04y1", ED_HitBox04y1);
                set_config_int(ED_State_s, "HitBox04x2", ED_HitBox04x2);
                set_config_int(ED_State_s, "HitBox04y2", ED_HitBox04y2);
            } else if (ED_HitBox_tot == 3) {
                ED_HitBox03x1 = -5555;
                ED_HitBox03y1 = -5555;
                ED_HitBox03x2 = -5555;
                ED_HitBox03y2 = -5555;
                set_config_int(ED_State_s, "HitBox03x1", ED_HitBox03x1);
                set_config_int(ED_State_s, "HitBox03y1", ED_HitBox03y1);
                set_config_int(ED_State_s, "HitBox03x2", ED_HitBox03x2);
                set_config_int(ED_State_s, "HitBox03y2", ED_HitBox03y2);
            } else if (ED_HitBox_tot == 2) {
                ED_HitBox02x1 = -5555;
                ED_HitBox02y1 = -5555;
                ED_HitBox02x2 = -5555;
                ED_HitBox02y2 = -5555;
                set_config_int(ED_State_s, "HitBox02x1", ED_HitBox02x1);
                set_config_int(ED_State_s, "HitBox02y1", ED_HitBox02y1);
                set_config_int(ED_State_s, "HitBox02x2", ED_HitBox02x2);
                set_config_int(ED_State_s, "HitBox02y2", ED_HitBox02y2);
            } else if (ED_HitBox_tot == 1) {
                ED_HitBox01x1 = -5555;
                ED_HitBox01y1 = -5555;
                ED_HitBox01x2 = -5555;
                ED_HitBox01y2 = -5555;
                set_config_int(ED_State_s, "HitBox01x1", ED_HitBox01x1);
                set_config_int(ED_State_s, "HitBox01y1", ED_HitBox01y1);
                set_config_int(ED_State_s, "HitBox01x2", ED_HitBox01x2);
                set_config_int(ED_State_s, "HitBox01y2", ED_HitBox01y2);
            }
            ED_HitBox_tot--;
        }
        if (ED_HitBox_tot < 0) {
            ED_HitBox_tot = 0;
        }
        if (ED_DrawBlueMode == 1) {
            char ED_Caminho[99];
            sprintf(ED_Caminho, "data/chars/%s/chbox.ini", P[1].Name);
            set_config_file(ED_Caminho);
            char ED_State_s[16];
            if (ED_IndexAnim < 10) { sprintf(ED_State_s, "%i_0%i", ED_State, ED_IndexAnim); }
            if (ED_IndexAnim >= 10) { sprintf(ED_State_s, "%i_%i", ED_State, ED_IndexAnim); }
            if (ED_HurtBox_tot == 9) {
                ED_HurtBox09x1 = -5555;
                ED_HurtBox09y1 = -5555;
                ED_HurtBox09x2 = -5555;
                ED_HurtBox09y2 = -5555;
                set_config_int(ED_State_s, "HurtBox09x1", ED_HurtBox09x1);
                set_config_int(ED_State_s, "HurtBox09y1", ED_HurtBox09y1);
                set_config_int(ED_State_s, "HurtBox09x2", ED_HurtBox09x2);
                set_config_int(ED_State_s, "HurtBox09y2", ED_HurtBox09y2);
            } else if (ED_HurtBox_tot == 8) {
                ED_HurtBox08x1 = -5555;
                ED_HurtBox08y1 = -5555;
                ED_HurtBox08x2 = -5555;
                ED_HurtBox08y2 = -5555;
                set_config_int(ED_State_s, "HurtBox08x1", ED_HurtBox08x1);
                set_config_int(ED_State_s, "HurtBox08y1", ED_HurtBox08y1);
                set_config_int(ED_State_s, "HurtBox08x2", ED_HurtBox08x2);
                set_config_int(ED_State_s, "HurtBox08y2", ED_HurtBox08y2);
            } else if (ED_HurtBox_tot == 7) {
                ED_HurtBox07x1 = -5555;
                ED_HurtBox07y1 = -5555;
                ED_HurtBox07x2 = -5555;
                ED_HurtBox07y2 = -5555;
                set_config_int(ED_State_s, "HurtBox07x1", ED_HurtBox07x1);
                set_config_int(ED_State_s, "HurtBox07y1", ED_HurtBox07y1);
                set_config_int(ED_State_s, "HurtBox07x2", ED_HurtBox07x2);
                set_config_int(ED_State_s, "HurtBox07y2", ED_HurtBox07y2);
            } else if (ED_HurtBox_tot == 6) {
                ED_HurtBox06x1 = -5555;
                ED_HurtBox06y1 = -5555;
                ED_HurtBox06x2 = -5555;
                ED_HurtBox06y2 = -5555;
                set_config_int(ED_State_s, "HurtBox06x1", ED_HurtBox06x1);
                set_config_int(ED_State_s, "HurtBox06y1", ED_HurtBox06y1);
                set_config_int(ED_State_s, "HurtBox06x2", ED_HurtBox06x2);
                set_config_int(ED_State_s, "HurtBox06y2", ED_HurtBox06y2);
            } else if (ED_HurtBox_tot == 5) {
                ED_HurtBox05x1 = -5555;
                ED_HurtBox05y1 = -5555;
                ED_HurtBox05x2 = -5555;
                ED_HurtBox05y2 = -5555;
                set_config_int(ED_State_s, "HurtBox05x1", ED_HurtBox05x1);
                set_config_int(ED_State_s, "HurtBox05y1", ED_HurtBox05y1);
                set_config_int(ED_State_s, "HurtBox05x2", ED_HurtBox05x2);
                set_config_int(ED_State_s, "HurtBox05y2", ED_HurtBox05y2);
            } else if (ED_HurtBox_tot == 4) {
                ED_HurtBox04x1 = -5555;
                ED_HurtBox04y1 = -5555;
                ED_HurtBox04x2 = -5555;
                ED_HurtBox04y2 = -5555;
                set_config_int(ED_State_s, "HurtBox04x1", ED_HurtBox04x1);
                set_config_int(ED_State_s, "HurtBox04y1", ED_HurtBox04y1);
                set_config_int(ED_State_s, "HurtBox04x2", ED_HurtBox04x2);
                set_config_int(ED_State_s, "HurtBox04y2", ED_HurtBox04y2);
            } else if (ED_HurtBox_tot == 3) {
                ED_HurtBox03x1 = -5555;
                ED_HurtBox03y1 = -5555;
                ED_HurtBox03x2 = -5555;
                ED_HurtBox03y2 = -5555;
                set_config_int(ED_State_s, "HurtBox03x1", ED_HurtBox03x1);
                set_config_int(ED_State_s, "HurtBox03y1", ED_HurtBox03y1);
                set_config_int(ED_State_s, "HurtBox03x2", ED_HurtBox03x2);
                set_config_int(ED_State_s, "HurtBox03y2", ED_HurtBox03y2);
            } else if (ED_HurtBox_tot == 2) {
                ED_HurtBox02x1 = -5555;
                ED_HurtBox02y1 = -5555;
                ED_HurtBox02x2 = -5555;
                ED_HurtBox02y2 = -5555;
                set_config_int(ED_State_s, "HurtBox02x1", ED_HurtBox02x1);
                set_config_int(ED_State_s, "HurtBox02y1", ED_HurtBox02y1);
                set_config_int(ED_State_s, "HurtBox02x2", ED_HurtBox02x2);
                set_config_int(ED_State_s, "HurtBox02y2", ED_HurtBox02y2);
            } else if (ED_HurtBox_tot == 1) {
                ED_HurtBox01x1 = -5555;
                ED_HurtBox01y1 = -5555;
                ED_HurtBox01x2 = -5555;
                ED_HurtBox01y2 = -5555;
                set_config_int(ED_State_s, "HurtBox01x1", ED_HurtBox01x1);
                set_config_int(ED_State_s, "HurtBox01y1", ED_HurtBox01y1);
                set_config_int(ED_State_s, "HurtBox01x2", ED_HurtBox01x2);
                set_config_int(ED_State_s, "HurtBox01y2", ED_HurtBox01y2);
            }
            ED_HurtBox_tot--;
        }
        if (ED_HurtBox_tot < 0) {
            ED_HurtBox_tot = 0;
        }
    }

    if ((ED_DrawRedMode == 1 || ED_DrawBlueMode == 1) && key_Mouse_L_status == 1 && mouse_x > 170 && mouse_y > 40)
    //inicia desenho Red/Blue
    {
        ED_Mx1 = mouse_x;
        ED_My1 = mouse_y;
    }

    int atualiza = 0;

    if (key_Mouse_L_status == 1 && mouse_x > 5 && mouse_x < 34 && mouse_y > 172 && mouse_y < 202) //Prev+
    {
        ED_Pause = 1;
        ED_IndexAnim = 0;
        ED_StartFrame = Edtimer;
        atualiza = 1;
        Draw_CHBoxes_ED();
    }

    if (key_Mouse_L_status == 1 && mouse_x > 37 && mouse_x < 66 && mouse_y > 172 && mouse_y < 202) //Prev L
    {
        ED_Pause = 1;
        ED_IndexAnim--;
        if (ED_IndexAnim < 0) { ED_IndexAnim = ED_TotalFrames; }
        ED_StartFrame = Edtimer;
        atualiza = 1;
        Draw_CHBoxes_ED();
    }
    if (key_Mouse_R_status == 1 && mouse_x > 37 && mouse_x < 66 && mouse_y > 172 && mouse_y < 202) //Prev R
    {
        ED_Pause = 1;
        ED_IndexAnim -= 3;
        if (ED_IndexAnim < 0) { ED_IndexAnim = 0; }
        ED_StartFrame = Edtimer;
        atualiza = 1;
        Draw_CHBoxes_ED();
    }

    if (key_Mouse_L_status == 1 && mouse_x > 70 && mouse_x < 100 && mouse_y > 168 && mouse_y < 198) //Pause/Play
    {
        if (ED_Pause == 0) { ED_Pause = 1; } else { ED_Pause = 0; }
    }

    if (key_Mouse_L_status == 1 && mouse_x > 103 && mouse_x < 133 && mouse_y > 172 && mouse_y < 202) //Next L
    {
        ED_Pause = 1;
        ED_IndexAnim++;
        if (ED_IndexAnim > ED_TotalFrames) { ED_IndexAnim = 0; }
        ED_StartFrame = Edtimer;
        atualiza = 1;
        Draw_CHBoxes_ED();
    }
    if (key_Mouse_R_status == 1 && mouse_x > 103 && mouse_x < 133 && mouse_y > 172 && mouse_y < 202) //Next R
    {
        ED_Pause = 1;
        ED_IndexAnim += 3;
        if (ED_IndexAnim > ED_TotalFrames) { ED_IndexAnim = ED_TotalFrames; }
        ED_StartFrame = Edtimer;
        atualiza = 1;
        Draw_CHBoxes_ED();
    }

    if (key_Mouse_L_status == 1 && mouse_x > 135 && mouse_x < 165 && mouse_y > 172 && mouse_y < 202) //Next+
    {
        ED_Pause = 1;
        ED_IndexAnim = ED_TotalFrames;
        ED_StartFrame = Edtimer;
        atualiza = 1;
        Draw_CHBoxes_ED();
    }

    if (atualiza == 1) {
        if (ED_IndexAnim == 0) { ED_FrameTime = ED_FrameTime_00; }
        if (ED_IndexAnim == 1) { ED_FrameTime = ED_FrameTime_01; }
        if (ED_IndexAnim == 2) { ED_FrameTime = ED_FrameTime_02; }
        if (ED_IndexAnim == 3) { ED_FrameTime = ED_FrameTime_03; }
        if (ED_IndexAnim == 4) { ED_FrameTime = ED_FrameTime_04; }
        if (ED_IndexAnim == 5) { ED_FrameTime = ED_FrameTime_05; }
        if (ED_IndexAnim == 6) { ED_FrameTime = ED_FrameTime_06; }
        if (ED_IndexAnim == 7) { ED_FrameTime = ED_FrameTime_07; }
        if (ED_IndexAnim == 8) { ED_FrameTime = ED_FrameTime_08; }
        if (ED_IndexAnim == 9) { ED_FrameTime = ED_FrameTime_09; }
        if (ED_IndexAnim == 10) { ED_FrameTime = ED_FrameTime_10; }
        if (ED_IndexAnim == 11) { ED_FrameTime = ED_FrameTime_11; }
        if (ED_IndexAnim == 12) { ED_FrameTime = ED_FrameTime_12; }
        if (ED_IndexAnim == 13) { ED_FrameTime = ED_FrameTime_13; }
        if (ED_IndexAnim == 14) { ED_FrameTime = ED_FrameTime_14; }
        if (ED_IndexAnim == 15) { ED_FrameTime = ED_FrameTime_15; }
        if (ED_IndexAnim == 16) { ED_FrameTime = ED_FrameTime_16; }
        if (ED_IndexAnim == 17) { ED_FrameTime = ED_FrameTime_17; }
        if (ED_IndexAnim == 18) { ED_FrameTime = ED_FrameTime_18; }
        if (ED_IndexAnim == 19) { ED_FrameTime = ED_FrameTime_19; }
        if (ED_IndexAnim == 20) { ED_FrameTime = ED_FrameTime_20; }
        if (ED_IndexAnim == 21) { ED_FrameTime = ED_FrameTime_21; }
        if (ED_IndexAnim == 22) { ED_FrameTime = ED_FrameTime_22; }
        if (ED_IndexAnim == 23) { ED_FrameTime = ED_FrameTime_23; }
        if (ED_IndexAnim == 24) { ED_FrameTime = ED_FrameTime_24; }
        if (ED_IndexAnim == 25) { ED_FrameTime = ED_FrameTime_25; }
        if (ED_IndexAnim == 26) { ED_FrameTime = ED_FrameTime_26; }
        if (ED_IndexAnim == 27) { ED_FrameTime = ED_FrameTime_27; }
        if (ED_IndexAnim == 28) { ED_FrameTime = ED_FrameTime_28; }
        if (ED_IndexAnim == 29) { ED_FrameTime = ED_FrameTime_29; }
    }
    atualiza = 0;

    if (key_Mouse_L_status == 1 && mouse_x > 6 && mouse_x < 34 && mouse_y > 211 && mouse_y < 238) //Minus Time L
    {
        ED_Pause = 1;
        ED_FrameTime--;
        if (ED_FrameTime < 0) { ED_FrameTime = 0; }
        ED_alertsave = 1;
        atualiza = 1;
    }
    if (key_Mouse_R_status == 1 && mouse_x > 6 && mouse_x < 34 && mouse_y > 211 && mouse_y < 238) //Minus Time R
    {
        ED_Pause = 1;
        ED_FrameTime -= 10;
        if (ED_FrameTime < 0) { ED_FrameTime = 0; }
        ED_alertsave = 1;
        atualiza = 1;
    }

    if (key_Mouse_L_status == 1 && mouse_x > 136 && mouse_x < 164 && mouse_y > 211 && mouse_y < 238) //Plus Time L
    {
        ED_Pause = 1;
        ED_FrameTime++;
        if (ED_FrameTime > 998) { ED_FrameTime = 998; }
        ED_alertsave = 1;
        atualiza = 1;
    }
    if (key_Mouse_R_status == 1 && mouse_x > 136 && mouse_x < 164 && mouse_y > 211 && mouse_y < 238) //Plus Time R
    {
        ED_Pause = 1;
        ED_FrameTime += 10;
        if (ED_FrameTime > 998) { ED_FrameTime = 998; }
        ED_alertsave = 1;
        atualiza = 1;
    }

    if (key_Mouse_L_status == 1 && mouse_x > 5 && mouse_x < 164 && mouse_y > 420 && mouse_y < 450) //Movimenta Pivot
    {
        if (ED_MovimentaPivot == 0) {
            ED_MovimentaPivot = 1;
            ED_DrawBlueMode = 0;
            ED_DrawRedMode = 0;
            ED_bt_Null = 0;
        } else {
            ED_alertsave2 = 1;
            ED_MovimentaPivot = 0;
        }
    }

    if (atualiza == 1) {
        if (ED_IndexAnim == 0) { ED_FrameTime_00 = ED_FrameTime; }
        if (ED_IndexAnim == 1) { ED_FrameTime_01 = ED_FrameTime; }
        if (ED_IndexAnim == 2) { ED_FrameTime_02 = ED_FrameTime; }
        if (ED_IndexAnim == 3) { ED_FrameTime_03 = ED_FrameTime; }
        if (ED_IndexAnim == 4) { ED_FrameTime_04 = ED_FrameTime; }
        if (ED_IndexAnim == 5) { ED_FrameTime_05 = ED_FrameTime; }
        if (ED_IndexAnim == 6) { ED_FrameTime_06 = ED_FrameTime; }
        if (ED_IndexAnim == 7) { ED_FrameTime_07 = ED_FrameTime; }
        if (ED_IndexAnim == 8) { ED_FrameTime_08 = ED_FrameTime; }
        if (ED_IndexAnim == 9) { ED_FrameTime_09 = ED_FrameTime; }
        if (ED_IndexAnim == 10) { ED_FrameTime_10 = ED_FrameTime; }
        if (ED_IndexAnim == 11) { ED_FrameTime_11 = ED_FrameTime; }
        if (ED_IndexAnim == 12) { ED_FrameTime_12 = ED_FrameTime; }
        if (ED_IndexAnim == 13) { ED_FrameTime_13 = ED_FrameTime; }
        if (ED_IndexAnim == 14) { ED_FrameTime_14 = ED_FrameTime; }
        if (ED_IndexAnim == 15) { ED_FrameTime_15 = ED_FrameTime; }
        if (ED_IndexAnim == 16) { ED_FrameTime_16 = ED_FrameTime; }
        if (ED_IndexAnim == 17) { ED_FrameTime_17 = ED_FrameTime; }
        if (ED_IndexAnim == 18) { ED_FrameTime_18 = ED_FrameTime; }
        if (ED_IndexAnim == 19) { ED_FrameTime_19 = ED_FrameTime; }
        if (ED_IndexAnim == 20) { ED_FrameTime_20 = ED_FrameTime; }
        if (ED_IndexAnim == 21) { ED_FrameTime_21 = ED_FrameTime; }
        if (ED_IndexAnim == 22) { ED_FrameTime_22 = ED_FrameTime; }
        if (ED_IndexAnim == 23) { ED_FrameTime_23 = ED_FrameTime; }
        if (ED_IndexAnim == 24) { ED_FrameTime_24 = ED_FrameTime; }
        if (ED_IndexAnim == 25) { ED_FrameTime_25 = ED_FrameTime; }
        if (ED_IndexAnim == 26) { ED_FrameTime_26 = ED_FrameTime; }
        if (ED_IndexAnim == 27) { ED_FrameTime_27 = ED_FrameTime; }
        if (ED_IndexAnim == 28) { ED_FrameTime_28 = ED_FrameTime; }
        if (ED_IndexAnim == 29) { ED_FrameTime_29 = ED_FrameTime; }
    }

    //-ED-anim++
    if (ED_IndexAnim == 0) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_00) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_01;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 1) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_01) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_02;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 2) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_02) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_03;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 3) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_03) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_04;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 4) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_04) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_05;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 5) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_05) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_06;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 6) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_06) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_07;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 7) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_07) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_08;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 8) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_08) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_09;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 9) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_09) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_10;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 10) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_10) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_11;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 11) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_11) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_12;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 12) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_12) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_13;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 13) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_13) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_14;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 14) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_14) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_15;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 15) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_15) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_16;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 16) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_16) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_17;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 17) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_17) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_18;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 18) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_18) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_19;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 19) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_19) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_20;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 20) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_20) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_21;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 21) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_21) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_22;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 22) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_22) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_23;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 23) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_23) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_24;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 24) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_24) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_25;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 25) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_25) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_26;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 26) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_26) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_27;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 27) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_27) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_28;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    if (ED_IndexAnim == 28) {
        if (Edtimer > ED_StartFrame + ED_FrameTime_28) {
            ED_IndexAnim++;
            ED_FrameTime = ED_FrameTime_29;
            ED_StartFrame = Edtimer;
            Draw_CHBoxes_ED();
        }
    }
    //-ED-end of anim
    if (ED_IndexAnim > ED_TotalFrames) {
        ED_IndexAnim = 0;
        ED_FrameTime = ED_FrameTime_00;
        ED_StartFrame = Edtimer;
        Draw_CHBoxes_ED();
    } //-loop

    rectfill(bufferx, 0, 0, 320, 240, makecol(100,149,237));

    //3-Desenha Caixas
    if (ED_bt_Null == 1) {
        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        set_trans_blender(0, 0, 0, 77);
        if (ED_HurtBox01x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox01x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox01y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox01x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox01y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox02x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox02x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox02y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox02x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox02y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox03x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox03x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox03y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox03x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox03y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox04x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox04x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox04y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox04x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox04y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox05x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox05x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox05y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox05x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox05y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox06x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox06x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox06y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox06x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox06y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox07x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox07x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox07y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox07x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox07y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox08x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox08x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox08y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox08x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox08y2*1, makecol(050,000,255));
        }
        if (ED_HurtBox09x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox09x1*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox09y1*1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HurtBox09x2*1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HurtBox09y2*1, makecol(050,000,255));
        }
        if (ED_HitBox01x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox01x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox01y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox01x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox01y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox02x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox02x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox02y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox02x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox02y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox03x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox03x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox03y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox03x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox03y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox04x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox04x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox04y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox04x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox04y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox05x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox05x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox05y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox05x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox05y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox06x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox06x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox06y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox06x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox06y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox07x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox07x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox07y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox07x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox07y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox08x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox08x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox08y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox08x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox08y2 *1, makecol(255,000,050));
        }
        if (ED_HitBox09x1 != -5555) {
            rectfill(bufferx, (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox09x1 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox09y1 *1,
                     (((ED_x-ED_XAlign)*1)+ED_XAlign*1)+ED_HitBox09x2 *1,
                     (((ED_y-ED_YAlign)*1)+ED_YAlign*1)+ED_HitBox09y2 *1, makecol(255,000,050));
        }
        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
    }

    //draw char -ED-
    {
        char txt[7];
        char txt2[40];
        if (ED_IndexAnim < 10) { sprintf(txt, "%i_0%i", ED_State, ED_IndexAnim); } // <10
        else { sprintf(txt, "%i_%i", ED_State, ED_IndexAnim); } //>=10
        if (ED_IndexAnim < 10) {
            if (ED_State != 603 && ED_State != 605) {
                sprintf(txt2, "data/chars/%s/%i_0%i.png", ED_Name, ED_State, ED_IndexAnim);
            } //<10
            if (ED_State == 603 || ED_State == 605) {
                sprintf(txt2, "data/chars/%s/604_0%i.png", ED_Name, ED_IndexAnim);
            }
        } //<10
        else {
            if (ED_State != 603 && ED_State != 605) {
                sprintf(txt2, "data/chars/%s/%i_%i.png", ED_Name, ED_State, ED_IndexAnim);
            } //>=10
            if (ED_State == 603 || ED_State == 605) {
                sprintf(txt2, "data/chars/%s/604_%i.png", ED_Name, ED_IndexAnim);
            }
        } //>=10

        //if (Edtimer-ED_StartFrame==0) { //Atualiza o sprite SOMENTE no primeiro frame de animacao
        clear(ED_Spr);
        ED_Spr_Aux = load_bitmap(txt2, NULL);
        if (!ED_Spr_Aux) { ED_Spr_Aux = char_generic; } //se falhar o carregamento, usar imagem generica
        if (ED_Tipo == 1) {
            ED_Spr->w = ED_Spr_Aux->w * 2;
            ED_Spr->h = ED_Spr_Aux->h * 2;
            stretch_blit(ED_Spr_Aux, ED_Spr, 0, 0, ED_Spr_Aux->w, ED_Spr_Aux->h, 0, 0, ED_Spr->w, ED_Spr->h);
        }
        if (ED_Tipo == 2) {
            ED_Spr->w = ED_Spr_Aux->w;
            ED_Spr->h = ED_Spr_Aux->h;
            blit(ED_Spr_Aux, ED_Spr, 0, 0, 0, 0, ED_Spr_Aux->w, ED_Spr_Aux->h);
        }
        destroy_bitmap(ED_Spr_Aux);
        ED_Altura = ED_Spr->h;
        ED_Largura = ED_Spr->w;
        if (ED_State == 100) {
            ED_Altura_100 = ED_Altura;
            ED_Largura_100 = ED_Largura;
        }
        //}
    }
    //fim draw_char

    rectfill(LayerHUD, 0, 0, 320, 240, makecol(100,149,237));
    rectfill(LayerHUD, 0, 0, 85, 240, makecol( 50, 75,119));
    rectfill(LayerHUD, 0, 0, 320, 20, makecol( 35, 45, 75));

    if (ED_Pause == 0) {
        EditModeTime += 1;
        Edtimer = EditModeTime;
    }

    //draw hud
    stretch_blit(LayerHUD, bufferx, 0, 0, 320, 240, 0, 0, 640, 480);

    //Render Tipo 1 Normal Sprites
    if (ED_Tipo == 1) {
        if (ED_State != 607 && ED_State != 608) {
            if (ED_Lado == 1) { draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
            if (ED_Lado == -1) {
                draw_sprite_h_flip(bufferx, ED_Spr, ((ED_x*2)-P[1].Spr->w)+ED_XAlign*2, ED_y*2-ED_YAlign*2);
            }
        } else {
            //if (ED_Lado==-1) { draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
            if (ED_Lado == 1) { draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
        }
    }

    //Render Tipo 2 HD Sprites
    if (ED_Tipo == 2) {
        if (ED_State != 607 && ED_State != 608) {
            if (ED_Lado == 1) { draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
            if (ED_Lado == -1) {
                draw_sprite_h_flip(bufferx, ED_Spr, ((ED_x*2)-ED_Spr->w)+ED_XAlign*2, ED_y*2-ED_YAlign*2);
            }
        } else {
            //if (ED_Lado==-1) { draw_sprite(bufferx, ED_Spr, (ED_x*2)-ED_XAlign*2, ED_y*2-ED_YAlign*2); }
            if (ED_Lado == 1) {
                draw_sprite_h_flip(bufferx, ED_Spr, ((ED_x*2)-ED_Spr->w)+ED_XAlign*2, ED_y*2-ED_YAlign*2);
            }
        }
    }

    //3b-Desenha Caixas com transparencia
    if (ED_bt_Null == 1) {
        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        set_trans_blender(0, 0, 0, 77);
        if (ED_HurtBox01x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox01x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox01y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox01x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox01y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox02x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox02x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox02y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox02x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox02y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox03x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox03x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox03y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox03x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox03y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox04x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox04x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox04y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox04x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox04y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox05x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox05x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox05y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox05x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox05y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox06x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox06x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox06y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox06x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox06y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox07x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox07x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox07y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox07x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox07y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox08x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox08x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox08y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox08x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox08y2*2, makecol(050,000,255));
        }
        if (ED_HurtBox09x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox09x1*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox09y1*2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HurtBox09x2*2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HurtBox09y2*2, makecol(050,000,255));
        }
        if (ED_HitBox01x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox01x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox01y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox01x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox01y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox02x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox02x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox02y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox02x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox02y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox03x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox03x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox03y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox03x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox03y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox04x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox04x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox04y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox04x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox04y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox05x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox05x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox05y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox05x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox05y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox06x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox06x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox06y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox06x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox06y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox07x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox07x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox07y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox07x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox07y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox08x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox08x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox08y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox08x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox08y2 *2, makecol(255,000,050));
        }
        if (ED_HitBox09x1 != -5555) {
            rectfill(bufferx, (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox09x1 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox09y1 *2,
                     (((ED_x*2-ED_XAlign*2)*1)+ED_XAlign*2)+ED_HitBox09x2 *2,
                     (((ED_y*2-ED_YAlign*2)*1)+ED_YAlign*2)+ED_HitBox09y2 *2, makecol(255,000,050));
        }
        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
    }

    if (ED_MovimentaPivot == 1) //hud para movimentacao do eixo
    {
        line(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)-250, (((ED_y-ED_YAlign)*2)+ED_YAlign*2),
             (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+250, (((ED_y-ED_YAlign)*2)+ED_YAlign*2), makecol(000,000,000));
        line(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2)-250,
             (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+250, makecol(000,000,000));
        circle(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2), 50,
               makecol(000,000,000));
        circle(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2), 100,
               makecol(000,000,000));
        circle(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2), (((ED_y-ED_YAlign)*2)+ED_YAlign*2), 150,
               makecol(000,000,000));
    }
    if (ED_MODE == 1) {
        draw_sprite(bufferx, edit_bt_blue, 5, 60);
        if (ED_DrawBlueMode == 1) {
            rect(bufferx, 5-2, 60-2, 5+edit_bt_blue->w+2, 60+edit_bt_blue->h+2, makecol(255,255,255));
        }
        draw_sprite(bufferx, edit_bt_red, 60, 60);
        if (ED_DrawRedMode == 1) {
            rect(bufferx, 60-2, 60-2, 60+ edit_bt_red->w+2, 60+ edit_bt_red->h+2, makecol(255,255,255));
        }
        draw_sprite(bufferx, edit_bt_null, 115, 60);
        if (ED_bt_Null == 0) { draw_sprite(bufferx, edit_bt_null0, 115, 60); }
    }

    //interface
    draw_sprite(bufferx, edit_prevst, 5, 120);
    draw_sprite(bufferx, edit_nextst, 88, 120);
    draw_sprite(bufferx, edit_prevchar, 173, 6);
    draw_sprite(bufferx, edit_nextchar, 229, 6);
    draw_sprite(bufferx, edit_firstchar, 173, 22);
    draw_sprite(bufferx, edit_lastchar, 229, 22);
    draw_sprite(bufferx, edit_playback, 5, 172);
    if (ED_Pause == 1) { draw_sprite(bufferx, edit_pause, 70, 172); }
    draw_sprite(bufferx, edit_bt_minus, 5, 210);
    draw_sprite(bufferx, edit_bt_FrameTime, 35, 210);
    textprintf_centre_ex(bufferx, font_debug, 90, 215, makecol(255, 255, 255), -1, "%i", ED_FrameTime + 1);
    draw_sprite(bufferx, edit_bt_plus, 135, 210);
    draw_sprite(bufferx, bt_pivot, 5, 420);

    //textprintf_centre_ex(bufferx, font_debug, 84, 463, makecol(255,255,000), -1, "FPS[%d] [%d]", Ctrl_FPS, Edtimer);
    textprintf_centre_ex(bufferx, font_debug, 84, 453, makecol(255, 255, 255), -1, "Mx:%i My:%i", mouse_x - ED_x * 2,
                         mouse_y - ED_y * 2);
    circlefill(bufferx, ((ED_x-ED_XAlign)*2)+ED_XAlign*2, ((ED_y-ED_YAlign)*2)+ED_YAlign*2, 3, makecol(000,000,000));
    circlefill(bufferx, ((ED_x-ED_XAlign)*2)+ED_XAlign*2, ((ED_y-ED_YAlign)*2)+ED_YAlign*2, 1, makecol(255,255,255));

    rectfill(bufferx, 5, 152, 163, 150+19, makecol(000,000,000));
    rect(bufferx, 5, 152, 163, 150+19, makecol(100,100,100));

    //debug - draw states numerados V1
    /*
            for (int ii=0; ii<=14; ii++) { if (ii < 9) { textprintf_ex(bufferx, font_debug, 190      , 50+ ii    *12, makecol(70,105,165), -1, "0%i[%i]", ii+1, MovPossiveis[ii] ); }
            if (ii>= 9) { textprintf_ex(bufferx, font_debug, 190      , 50+ ii    *12, makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); } }
            for (int ii=15; ii<=29; ii++) { textprintf_ex(bufferx, font_debug, 190+ 63*1, 50+(ii-15)*12, makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
            for (int ii=30; ii<=44; ii++) { textprintf_ex(bufferx, font_debug, 190+ 63*2, 50+(ii-30)*12, makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
            for (int ii=45; ii<=59; ii++) { textprintf_ex(bufferx, font_debug, 190+ 63*3, 50+(ii-45)*12, makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
            for (int ii=60; ii<=74; ii++) { textprintf_ex(bufferx, font_debug, 190+ 63*4, 50+(ii-60)*12, makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
            for (int ii=75; ii<=89; ii++) { textprintf_ex(bufferx, font_debug, 190+ 63*5, 50+(ii-75)*12, makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
            for (int ii=90; ii<=98; ii++) { textprintf_ex(bufferx, font_debug, 190+ 63*6, 50+(ii-90)*12, makecol(70,105,165), -1,  "%i[%i]", ii+1, MovPossiveis[ii] ); }
        */

    //debug - draw states numerados V2
    /*
            for (int ii=  0; ii<= 19; ii++) { if(MovPossiveis[ii]!=0) textprintf_ex(bufferx, font_debug, 190      , 50+ ii     *21, makecol(255,255,255), makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
            for (int ii= 20; ii<= 39; ii++) { if(MovPossiveis[ii]!=0) textprintf_ex(bufferx, font_debug, 190+ 37*1, 50+(ii- 20)*21, makecol(255,255,255), makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
            for (int ii= 40; ii<= 59; ii++) { if(MovPossiveis[ii]!=0) textprintf_ex(bufferx, font_debug, 190+ 37*2, 50+(ii- 40)*21, makecol(255,255,255), makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
            for (int ii= 60; ii<= 79; ii++) { if(MovPossiveis[ii]!=0) textprintf_ex(bufferx, font_debug, 190+ 37*3, 50+(ii- 60)*21, makecol(255,255,255), makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
            for (int ii= 80; ii<= 99; ii++) { if(MovPossiveis[ii]!=0) textprintf_ex(bufferx, font_debug, 190+ 37*4, 50+(ii- 80)*21, makecol(255,255,255), makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
            for (int ii=100; ii<=119; ii++) { if(MovPossiveis[ii]!=0) textprintf_ex(bufferx, font_debug, 190+ 37*5, 50+(ii-100)*21, makecol(255,255,255), makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
            for (int ii=120; ii<=139; ii++) { if(MovPossiveis[ii]!=0) textprintf_ex(bufferx, font_debug, 190+ 37*6, 50+(ii-120)*21, makecol(255,255,255), makecol(000,000,000),  "[%i]", MovPossiveis[ii] ); }
        */

    //botoes ED_MODE
    if (key_Mouse_L_status == 1 && mouse_x > 550 && mouse_x < 590 && mouse_y > 0 && mouse_y < 40) { ED_MODE = 1; }
    if (key_Mouse_L_status == 1 && mouse_x > 595 && mouse_x < 635 && mouse_y > 0 && mouse_y < 40) {
        ED_MODE = 2;
        //ED_Pause=1;
        ED_MovimentaPivot = 0;
        ED_DrawBlueMode = 0;
        ED_DrawRedMode = 0;
        ED_bt_Null = 0;
        ED_load_inputs(ED_State);
    }

    if (ED_MODE == 1) {
        draw_sprite(bufferx, ed_mode1_on, 550, 0);
        draw_sprite(bufferx, ed_mode2_off, 595, 0);
    }

    //retangulos marcacao do botoes do ED_MODE
    rectfill(bufferx, 550-90, 0, 550+40-90, 0+40, 0x777777);
    rectfill(bufferx, 595-90, 0, 595+40-90, 0+40, 0x777777);
    rect(bufferx, 550-90, 0, 550+40-90, 0+40, 0xffffff);
    rect(bufferx, 595-90, 0, 595+40-90, 0+40, 0xffffff);

    rect(bufferx, 550, 0, 550+40, 0+40, 0xffffff);
    rect(bufferx, 595, 0, 595+40, 0+40, 0xffffff);

    if (ED_MODE == 2) {
        draw_sprite(bufferx, ed_mode1_off, 550, 0);
        draw_sprite(bufferx, ed_mode2_on, 595, 0);

        //desenha controles dos especiais
        //rect(bufferx,180-2+265, 50-2,630+2,100+2,0xffffff);//moldura grande

        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        set_trans_blender(0, 0, 0, 50);
        rectfill(bufferx, 278, 50, 630, 100, 0x000000);
        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
        rect(bufferx, 278, 50, 630, 100, 0xffffff); //moldura inputs

        draw_sprite(bufferx, bt_reset_input, 195+20*16+90, 47);

        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        set_trans_blender(0, 0, 0, 50);
        rectfill(bufferx, 178, 50, 267, 100, 0x000000);
        drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
        rect(bufferx, 178, 50, 267, 100, 0xffffff); //moldura variation

        if (ED_Special_Version == 1)
            rectfill(bufferx, 195-10, 75, 220-10, 95, 0xff0000); //v1
        if (ED_Special_Version == 2)
            rectfill(bufferx, 220-10, 75, 245-10, 95, 0xff0000); //v2
        if (ED_Special_Version == 3)
            rectfill(bufferx, 245-10, 75, 270-10, 95, 0xff0000); //v3
        rect(bufferx, 195-10, 75, 220-10, 95, 0xffffff); //moldura v1
        rect(bufferx, 220-10, 75, 245-10, 95, 0xffffff); //moldura v2
        rect(bufferx, 245-10, 75, 270-10, 95, 0xffffff); //moldura v3
        textprintf_ex(bufferx, font_debug, 195 - 10, 55, 0xffff00, -1, "Variation");
        textprintf_ex(bufferx, font_debug, 205 - 10, 75, 0xffffff, -1, "1");
        textprintf_ex(bufferx, font_debug, 230 - 10, 75, 0xffffff, -1, "2");
        textprintf_ex(bufferx, font_debug, 255 - 10, 75, 0xffffff, -1, "3");
        textprintf_ex(bufferx, font_debug, 195 + 90, 55, 0xffff00, -1, "Input");

        //desenha inputs no ED
        for (int ind = 0; ind <= 15; ind++) {
            //draw_sprite(bufferx, spr_input_0, 195+20*ind+90, 75);
            circlefill(bufferx, 195+20* ind+90+8, 75+8, 2, 0x000000);
            if (ED_State >= 700) {
                int indexador;
                if (ED_State >= 700 && ED_State < 710) { indexador = 0; }
                if (ED_State == 710 && ED_State < 720) { indexador = 1; }
                if (ED_State == 720 && ED_State < 730) { indexador = 2; }
                if (ED_State == 730 && ED_State < 740) { indexador = 3; }
                if (ED_State == 740 && ED_State < 750) { indexador = 4; }
                if (ED_State == 750 && ED_State < 760) { indexador = 5; }
                if (ED_State == 760 && ED_State < 770) { indexador = 6; }
                if (ED_State == 770 && ED_State < 780) { indexador = 7; }
                if (ED_State == 780 && ED_State < 790) { indexador = 8; }
                if (ED_State == 790 && ED_State < 800) { indexador = 9; }
                if (P[1].Special_Inputs[indexador][ind + 1] == 8) {
                    draw_sprite(bufferx, spr_input_0, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == 9) {
                    draw_sprite(bufferx, spr_input_1, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == 6) {
                    draw_sprite(bufferx, spr_input_2, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == 3) {
                    draw_sprite(bufferx, spr_input_3, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == 2) {
                    draw_sprite(bufferx, spr_input_4, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == 1) {
                    draw_sprite(bufferx, spr_input_5, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == 4) {
                    draw_sprite(bufferx, spr_input_6, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == 7) {
                    draw_sprite(bufferx, spr_input_7, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -1) {
                    draw_sprite(bufferx, spr_input_8, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -2) {
                    draw_sprite(bufferx, spr_input_9, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -3) {
                    draw_sprite(bufferx, spr_input_10, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -4) {
                    draw_sprite(bufferx, spr_input_11, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -5) {
                    draw_sprite(bufferx, spr_input_12, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -6) {
                    draw_sprite(bufferx, spr_input_13, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -7) {
                    draw_sprite(bufferx, spr_input_16, 195+20*ind+90, 75);
                }
                if (P[1].Special_Inputs[indexador][ind + 1] == -8) {
                    draw_sprite(bufferx, spr_input_17, 195+20*ind+90, 75);
                }
            } else {
                if (ED_State == 101) { draw_sprite(bufferx, spr_input_8, 195+20*0+90, 75); }
                if (ED_State == 102) { draw_sprite(bufferx, spr_input_9, 195+20*0+90, 75); }
                if (ED_State == 103) { draw_sprite(bufferx, spr_input_10, 195+20*0+90, 75); }
                if (ED_State == 104) { draw_sprite(bufferx, spr_input_11, 195+20*0+90, 75); }
                if (ED_State == 105) { draw_sprite(bufferx, spr_input_12, 195+20*0+90, 75); }
                if (ED_State == 106) { draw_sprite(bufferx, spr_input_13, 195+20*0+90, 75); }
                if (ED_State == 151) { draw_sprite(bufferx, spr_input_8, 195+20*0+90, 75); }
                if (ED_State == 152) { draw_sprite(bufferx, spr_input_9, 195+20*0+90, 75); }
                if (ED_State == 153) { draw_sprite(bufferx, spr_input_10, 195+20*0+90, 75); }
                if (ED_State == 154) { draw_sprite(bufferx, spr_input_11, 195+20*0+90, 75); }
                if (ED_State == 155) { draw_sprite(bufferx, spr_input_12, 195+20*0+90, 75); }
                if (ED_State == 156) { draw_sprite(bufferx, spr_input_13, 195+20*0+90, 75); }
                if (ED_State >= 200 && ED_State <= 256) { draw_sprite(bufferx, spr_input_4, 195+20*0+90, 75); }
                if (ED_State == 201) { draw_sprite(bufferx, spr_input_8, 195+20*1+90, 75); }
                if (ED_State == 202) { draw_sprite(bufferx, spr_input_9, 195+20*1+90, 75); }
                if (ED_State == 203) { draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
                if (ED_State == 204) { draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
                if (ED_State == 205) { draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
                if (ED_State == 206) { draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
                if (ED_State >= 300 && ED_State <= 306) { draw_sprite(bufferx, spr_input_0, 195+20*0+90, 75); }
                if (ED_State == 301) { draw_sprite(bufferx, spr_input_8, 195+20*1+90, 75); }
                if (ED_State == 302) { draw_sprite(bufferx, spr_input_9, 195+20*1+90, 75); }
                if (ED_State == 303) { draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
                if (ED_State == 304) { draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
                if (ED_State == 305) { draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
                if (ED_State == 306) { draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
                if (ED_State == 310) { draw_sprite(bufferx, spr_input_7, 195+20*0+90, 75); }
                if (ED_State == 311) { draw_sprite(bufferx, spr_input_8, 195+20*1+90, 75); }
                if (ED_State == 312) { draw_sprite(bufferx, spr_input_9, 195+20*1+90, 75); }
                if (ED_State == 313) { draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
                if (ED_State == 314) { draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
                if (ED_State == 315) { draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
                if (ED_State == 316) { draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
                if (ED_State == 320) { draw_sprite(bufferx, spr_input_1, 195+20*0+90, 75); }
                if (ED_State >= 320 && ED_State <= 326) { draw_sprite(bufferx, spr_input_1, 195+20*0+90, 75); }
                if (ED_State == 321) { draw_sprite(bufferx, spr_input_8, 195+20*1+90, 75); }
                if (ED_State == 322) { draw_sprite(bufferx, spr_input_9, 195+20*1+90, 75); }
                if (ED_State == 323) { draw_sprite(bufferx, spr_input_10, 195+20*1+90, 75); }
                if (ED_State == 324) { draw_sprite(bufferx, spr_input_11, 195+20*1+90, 75); }
                if (ED_State == 325) { draw_sprite(bufferx, spr_input_12, 195+20*1+90, 75); }
                if (ED_State == 326) { draw_sprite(bufferx, spr_input_13, 195+20*1+90, 75); }
                if (ED_State == 410) { draw_sprite(bufferx, spr_input_6, 195+20*0+90, 75); }
                if (ED_State == 420) { draw_sprite(bufferx, spr_input_2, 195+20*0+90, 75); }
            }
        }

        rect(bufferx, 10-2, 50-2, 150, 110, 0xffff00); //moldura keys

        //brilho redondo nos botoes

        if (mouse_x > 19 + 20 * 0 - 9 && mouse_x < 19 + 20 * 0 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
            circlefill(bufferx, 19+20*0, 59, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 1 - 9 && mouse_x < 19 + 20 * 1 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
            circlefill(bufferx, 19+20*1, 59, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 2 - 9 && mouse_x < 19 + 20 * 2 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
            circlefill(bufferx, 19+20*2, 59, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 4 - 9 && mouse_x < 19 + 20 * 4 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
            circlefill(bufferx, 19+20*4, 59, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 5 - 9 && mouse_x < 19 + 20 * 5 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
            circlefill(bufferx, 19+20*5, 59, 12, 0xffff00);
        //if(mouse_x>19+20*6-9 && mouse_x<19+20*6+9 && mouse_y>59-9 && mouse_y<59+9) circlefill(bufferx, 19+20*6, 59, 12, 0xffff00);

        if (mouse_x > 19 + 20 * 0 - 9 && mouse_x < 19 + 20 * 0 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
            circlefill(bufferx, 19+20*0, 79, 12, 0xffff00);
        //if(mouse_x>19+20*1-9 && mouse_x<19+20*1+9 && mouse_y>79-9 && mouse_y<79+9) circlefill(bufferx, 19+20*1, 79, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 2 - 9 && mouse_x < 19 + 20 * 2 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
            circlefill(bufferx, 19+20*2, 79, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 4 - 9 && mouse_x < 19 + 20 * 4 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
            circlefill(bufferx, 19+20*4, 79, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 5 - 9 && mouse_x < 19 + 20 * 5 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
            circlefill(bufferx, 19+20*5, 79, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 6 - 9 && mouse_x < 19 + 20 * 6 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
            circlefill(bufferx, 19+20*6, 79, 12, 0xffff00);

        if (mouse_x > 19 + 20 * 0 - 9 && mouse_x < 19 + 20 * 0 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
            circlefill(bufferx, 19+20*0, 99, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 1 - 9 && mouse_x < 19 + 20 * 1 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
            circlefill(bufferx, 19+20*1, 99, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 2 - 9 && mouse_x < 19 + 20 * 2 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
            circlefill(bufferx, 19+20*2, 99, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 4 - 9 && mouse_x < 19 + 20 * 4 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
            circlefill(bufferx, 19+20*4, 99, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 5 - 9 && mouse_x < 19 + 20 * 5 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
            circlefill(bufferx, 19+20*5, 99, 12, 0xffff00);
        if (mouse_x > 19 + 20 * 6 - 9 && mouse_x < 19 + 20 * 6 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
            circlefill(bufferx, 19+20*6, 99, 12, 0xffff00);

        draw_sprite(bufferx, spr_input_7, 10+20*0, 50);
        draw_sprite(bufferx, spr_input_0, 10+20*1, 50);
        draw_sprite(bufferx, spr_input_1, 10+20*2, 50);
        draw_sprite(bufferx, spr_input_6, 10+20*0, 70);
        //draw_sprite(bufferx, spr_input_0, 10+20*1, 70);
        draw_sprite(bufferx, spr_input_2, 10+20*2, 70);
        draw_sprite(bufferx, spr_input_5, 10+20*0, 90);
        draw_sprite(bufferx, spr_input_4, 10+20*1, 90);
        draw_sprite(bufferx, spr_input_3, 10+20*2, 90);
        draw_sprite(bufferx, spr_input_16, 10+20*4, 50);
        draw_sprite(bufferx, spr_input_17, 10+20*5, 50);
        //draw_sprite(bufferx, spr_input_10, 10+20*6, 50);
        draw_sprite(bufferx, spr_input_8, 10+20*4, 70);
        draw_sprite(bufferx, spr_input_9, 10+20*5, 70);
        draw_sprite(bufferx, spr_input_10, 10+20*6, 70);
        draw_sprite(bufferx, spr_input_11, 10+20*4, 90);
        draw_sprite(bufferx, spr_input_12, 10+20*5, 90);
        draw_sprite(bufferx, spr_input_13, 10+20*6, 90);

        //add com&& input list
        int add_command = 0;
        if (key_Mouse_L_status == 1) {
            if (mouse_x > 19 + 20 * 0 - 9 && mouse_x < 19 + 20 * 0 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
                add_command = 7;
            if (mouse_x > 19 + 20 * 1 - 9 && mouse_x < 19 + 20 * 1 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
                add_command = 8;
            if (mouse_x > 19 + 20 * 2 - 9 && mouse_x < 19 + 20 * 2 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
                add_command = 9;

            if (mouse_x > 19 + 20 * 4 - 9 && mouse_x < 19 + 20 * 4 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
                add_command = -7;
            if (mouse_x > 19 + 20 * 5 - 9 && mouse_x < 19 + 20 * 5 + 9 && mouse_y > 59 - 9 && mouse_y < 59 + 9)
                add_command = -8;

            if (mouse_x > 19 + 20 * 0 - 9 && mouse_x < 19 + 20 * 0 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
                add_command = 4;
            //if(mouse_x>19+20*1-9 && mouse_x<19+20*1+9 && mouse_y>79-9 && mouse_y<79+9) add_command=5;
            if (mouse_x > 19 + 20 * 2 - 9 && mouse_x < 19 + 20 * 2 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
                add_command = 6;

            if (mouse_x > 19 + 20 * 4 - 9 && mouse_x < 19 + 20 * 4 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
                add_command = -1;
            if (mouse_x > 19 + 20 * 5 - 9 && mouse_x < 19 + 20 * 5 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
                add_command = -2;
            if (mouse_x > 19 + 20 * 6 - 9 && mouse_x < 19 + 20 * 6 + 9 && mouse_y > 79 - 9 && mouse_y < 79 + 9)
                add_command = -3;

            if (mouse_x > 19 + 20 * 0 - 9 && mouse_x < 19 + 20 * 0 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
                add_command = 1;
            if (mouse_x > 19 + 20 * 1 - 9 && mouse_x < 19 + 20 * 1 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
                add_command = 2;
            if (mouse_x > 19 + 20 * 2 - 9 && mouse_x < 19 + 20 * 2 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
                add_command = 3;

            if (mouse_x > 19 + 20 * 4 - 9 && mouse_x < 19 + 20 * 4 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
                add_command = -4;
            if (mouse_x > 19 + 20 * 5 - 9 && mouse_x < 19 + 20 * 5 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
                add_command = -5;
            if (mouse_x > 19 + 20 * 6 - 9 && mouse_x < 19 + 20 * 6 + 9 && mouse_y > 99 - 9 && mouse_y < 99 + 9)
                add_command = -6;
        }
        if (add_command != 0 && ED_State >= 700) {
            int addcmd = 0;
            if (ED_State == 700) { addcmd = 0; }
            if (ED_State == 710) { addcmd = 1; }
            if (ED_State == 720) { addcmd = 2; }
            if (ED_State == 730) { addcmd = 3; }
            if (ED_State == 740) { addcmd = 4; }
            if (ED_State == 750) { addcmd = 5; }
            if (ED_State == 760) { addcmd = 6; }
            if (ED_State == 770) { addcmd = 7; }
            if (ED_State == 780) { addcmd = 8; }
            if (ED_State == 790) { addcmd = 9; }
            //P[1].Special_Inputs[addcmd][0]++;
            if (add_command > 0) {
                P[1].Special_Inputs_c[addcmd][P[1].Special_Inputs_c[addcmd][0] + 1] = add_command;
                P[1].Special_Inputs_c[addcmd][0]++;
            }
            if (add_command < 0) {
                P[1].Special_Inputs_b[addcmd][P[1].Special_Inputs_b[addcmd][0] + 1] = add_command;
                P[1].Special_Inputs_b[addcmd][0]++;
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

            //BUG// Nota: Tem que salvar o novo input no special.ini!
        }

        //botao reset input list
        if (key_Mouse_L_status == 1 && ED_State >= 700) {
            if (mouse_x > 609 && mouse_x < 609 + 20 && mouse_y > 51 && mouse_y < 51 + 20) {
                int addcmd = 0;
                if (ED_State == 700) { addcmd = 0; }
                if (ED_State == 710) { addcmd = 1; }
                if (ED_State == 720) { addcmd = 2; }
                if (ED_State == 730) { addcmd = 3; }
                if (ED_State == 740) { addcmd = 4; }
                if (ED_State == 750) { addcmd = 5; }
                if (ED_State == 760) { addcmd = 6; }
                if (ED_State == 770) { addcmd = 7; }
                if (ED_State == 780) { addcmd = 8; }
                if (ED_State == 790) { addcmd = 9; }
                //zera o array dos especiais
                for (int ind = 0; ind <= 16; ind++) {
                    P[1].Special_Inputs_c[addcmd][ind] = 0;
                    P[1].Special_Inputs_b[addcmd][ind] = 0;
                    P[1].Special_Inputs[addcmd][ind] = 0;
                }
            }
        }

        //botoes special variation
        if (key_Mouse_L_status == 1 && mouse_x > 185 && mouse_x < 210 && mouse_y > 75 && mouse_y < 95) {
            ED_Special_Version = 1;
            ED_load_charini();
        }
        if (key_Mouse_L_status == 1 && mouse_x > 210 && mouse_x < 235 && mouse_y > 75 && mouse_y < 95) {
            ED_Special_Version = 2;
            ED_load_charini();
        }
        if (key_Mouse_L_status == 1 && mouse_x > 235 && mouse_x < 260 && mouse_y > 75 && mouse_y < 95) {
            ED_Special_Version = 3;
            ED_load_charini();
        }

        //botoes de config e caixas
        for (int ind = 4; ind <= 18; ind++) {
            rectfill(bufferx, 365+220, 58+15*ind, 395+220, 71+15*ind, 0x000000);
            rect(bufferx, 365+220, 58+15*ind, 395+220, 71+15*ind, 0xffffff);
            drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
            set_trans_blender(0, 0, 0, 50);
            rectfill(bufferx, 450, 58+15*ind, 630, 71+15*ind, 0x000000);
            drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
            circlefill(bufferx, 355+220, 65+15*ind, 7, 0x000000);
            circlefill(bufferx, 404+220, 65+15*ind, 7, 0x000000);
            circle(bufferx, 355+220, 65+15*ind, 7, 0xffffff);
            circle(bufferx, 404+220, 65+15*ind, 7, 0xffffff);
            textprintf_centre_ex(bufferx, font_debug, 381 + 220, 55 + 15 * ind, 0xffffff, -1, "999");
            textprintf_centre_ex(bufferx, font_debug, 355 + 220, 55 + 15 * ind, 0xffffff, -1, "-");
            textprintf_centre_ex(bufferx, font_debug, 404 + 220, 55 + 15 * ind, 0xffffff, -1, "+");
        }

        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 3, 0xffff00, -1, "Actuators");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 4, 0xffffff, -1, "X");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 5, 0xffffff, -1, "Y");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 6, 0xffffff, -1, "VSpeed");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 7, 0xffffff, -1, "HSpeed");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 8, 0xffffff, -1, "Gravity");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 9, 0x000000, -1, "Friction");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 10, 0xffffff, -1, "EnergyChange");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 11, 0xffffff, -1, "SpecialChange");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 12, 0xffffff, -1, "Visible");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 13, 0x000000, -1, "RoomLimit");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 14, 0xffffff, -1, "HitType");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 15, 0xffffff, -1, "HitStack");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 16, 0xffffff, -1, "ChangeState");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 17, 0x000000, -1, "Freeze");
        textprintf_ex(bufferx, font_debug, 460, 55 + 15 * 18, 0x000000, -1, "Color");
    }

    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 2; j++) {
            int z = 55;
            if (j == 0) { rectfill(bufferx, 5+j*z, 245+i*15, 53+j*z, 258+i*15, makecol(000,000,000)); }
            if (j != 0) { rectfill(bufferx, 5+j*z, 245+i*15, 53+j*z, 258+i*15, makecol(000,000,000)); }
            if (ED_IndexAnim == i) {
                if (ED_IndexAnim < 9) { rect(bufferx, 5+0*z, 245+i*15, 53+0*55, 258+i*15, makecol(255,000,000)); }
                if (ED_IndexAnim >= 10 && ED_IndexAnim < 20) {
                    rect(bufferx, 5+1*z, 245+i*15, 53+1*55, 258+i*15, makecol(255,000,000));
                }
                if (ED_IndexAnim >= 20 && ED_IndexAnim < 30) {
                    rect(bufferx, 5+2*z, 245+i*15, 53+2*55, 258+i*15, makecol(255,000,000));
                }
            }
        }
    }
    rectfill(bufferx, 5, 396, 163, 413, makecol(000,000,000));
    rect(bufferx, 5, 396, 163, 413, makecol(100,100,100));
    int sum = 0;
    if (ED_TotalFrames >= 0) { sum = sum + ED_FrameTime_00 + 1; }
    if (ED_TotalFrames >= 1) { sum = sum + ED_FrameTime_01 + 1; }
    if (ED_TotalFrames >= 2) { sum = sum + ED_FrameTime_02 + 1; }
    if (ED_TotalFrames >= 3) { sum = sum + ED_FrameTime_03 + 1; }
    if (ED_TotalFrames >= 4) { sum = sum + ED_FrameTime_04 + 1; }
    if (ED_TotalFrames >= 5) { sum = sum + ED_FrameTime_05 + 1; }
    if (ED_TotalFrames >= 6) { sum = sum + ED_FrameTime_06 + 1; }
    if (ED_TotalFrames >= 7) { sum = sum + ED_FrameTime_07 + 1; }
    if (ED_TotalFrames >= 8) { sum = sum + ED_FrameTime_08 + 1; }
    if (ED_TotalFrames >= 9) { sum = sum + ED_FrameTime_09 + 1; }
    if (ED_TotalFrames >= 10) { sum = sum + ED_FrameTime_10 + 1; }
    if (ED_TotalFrames >= 11) { sum = sum + ED_FrameTime_11 + 1; }
    if (ED_TotalFrames >= 12) { sum = sum + ED_FrameTime_12 + 1; }
    if (ED_TotalFrames >= 13) { sum = sum + ED_FrameTime_13 + 1; }
    if (ED_TotalFrames >= 14) { sum = sum + ED_FrameTime_14 + 1; }
    if (ED_TotalFrames >= 15) { sum = sum + ED_FrameTime_15 + 1; }
    if (ED_TotalFrames >= 16) { sum = sum + ED_FrameTime_16 + 1; }
    if (ED_TotalFrames >= 17) { sum = sum + ED_FrameTime_17 + 1; }
    if (ED_TotalFrames >= 18) { sum = sum + ED_FrameTime_18 + 1; }
    if (ED_TotalFrames >= 19) { sum = sum + ED_FrameTime_19 + 1; }
    if (ED_TotalFrames >= 20) { sum = sum + ED_FrameTime_20 + 1; }
    if (ED_TotalFrames >= 21) { sum = sum + ED_FrameTime_21 + 1; }
    if (ED_TotalFrames >= 22) { sum = sum + ED_FrameTime_22 + 1; }
    if (ED_TotalFrames >= 23) { sum = sum + ED_FrameTime_23 + 1; }
    if (ED_TotalFrames >= 24) { sum = sum + ED_FrameTime_24 + 1; }
    if (ED_TotalFrames >= 25) { sum = sum + ED_FrameTime_25 + 1; }
    if (ED_TotalFrames >= 26) { sum = sum + ED_FrameTime_26 + 1; }
    if (ED_TotalFrames >= 27) { sum = sum + ED_FrameTime_27 + 1; }
    if (ED_TotalFrames >= 28) { sum = sum + ED_FrameTime_28 + 1; }
    if (ED_TotalFrames >= 29) { sum = sum + ED_FrameTime_29 + 1; }
    textprintf_centre_ex(bufferx, font_debug, 84, 395, makecol(255, 255, 255), -1, "TOTAL: %i", sum);

    if (ED_TotalFrames >= 0 && ED_FrameTime_00 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 0 * 15, makecol(255, 255, 255), -1, "00. %i",
                             ED_FrameTime_00 + 1);
    }
    if (ED_TotalFrames >= 1 && ED_FrameTime_01 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 1 * 15, makecol(255, 255, 255), -1, "01. %i",
                             ED_FrameTime_01 + 1);
    }
    if (ED_TotalFrames >= 2 && ED_FrameTime_02 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 2 * 15, makecol(255, 255, 255), -1, "02. %i",
                             ED_FrameTime_02 + 1);
    }
    if (ED_TotalFrames >= 3 && ED_FrameTime_03 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 3 * 15, makecol(255, 255, 255), -1, "03. %i",
                             ED_FrameTime_03 + 1);
    }
    if (ED_TotalFrames >= 4 && ED_FrameTime_04 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 4 * 15, makecol(255, 255, 255), -1, "04. %i",
                             ED_FrameTime_04 + 1);
    }
    if (ED_TotalFrames >= 5 && ED_FrameTime_05 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 5 * 15, makecol(255, 255, 255), -1, "05. %i",
                             ED_FrameTime_05 + 1);
    }
    if (ED_TotalFrames >= 6 && ED_FrameTime_06 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 6 * 15, makecol(255, 255, 255), -1, "06. %i",
                             ED_FrameTime_06 + 1);
    }
    if (ED_TotalFrames >= 7 && ED_FrameTime_07 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 7 * 15, makecol(255, 255, 255), -1, "07. %i",
                             ED_FrameTime_07 + 1);
    }
    if (ED_TotalFrames >= 8 && ED_FrameTime_08 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 8 * 15, makecol(255, 255, 255), -1, "08. %i",
                             ED_FrameTime_08 + 1);
    }
    if (ED_TotalFrames >= 9 && ED_FrameTime_09 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 0 * 55, 242 + 9 * 15, makecol(255, 255, 255), -1, "09. %i",
                             ED_FrameTime_09 + 1);
    }
    if (ED_TotalFrames >= 10 && ED_FrameTime_10 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 0 * 15, makecol(255, 255, 255), -1, "10. %i",
                             ED_FrameTime_10 + 1);
    }
    if (ED_TotalFrames >= 11 && ED_FrameTime_11 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 1 * 15, makecol(255, 255, 255), -1, "11. %i",
                             ED_FrameTime_11 + 1);
    }
    if (ED_TotalFrames >= 12 && ED_FrameTime_12 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 2 * 15, makecol(255, 255, 255), -1, "12. %i",
                             ED_FrameTime_12 + 1);
    }
    if (ED_TotalFrames >= 13 && ED_FrameTime_13 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 3 * 15, makecol(255, 255, 255), -1, "13. %i",
                             ED_FrameTime_13 + 1);
    }
    if (ED_TotalFrames >= 14 && ED_FrameTime_14 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 4 * 15, makecol(255, 255, 255), -1, "14. %i",
                             ED_FrameTime_14 + 1);
    }
    if (ED_TotalFrames >= 15 && ED_FrameTime_15 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 5 * 15, makecol(255, 255, 255), -1, "15. %i",
                             ED_FrameTime_15 + 1);
    }
    if (ED_TotalFrames >= 16 && ED_FrameTime_16 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 6 * 15, makecol(255, 255, 255), -1, "16. %i",
                             ED_FrameTime_16 + 1);
    }
    if (ED_TotalFrames >= 17 && ED_FrameTime_17 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 7 * 15, makecol(255, 255, 255), -1, "17. %i",
                             ED_FrameTime_17 + 1);
    }
    if (ED_TotalFrames >= 18 && ED_FrameTime_18 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 8 * 15, makecol(255, 255, 255), -1, "18. %i",
                             ED_FrameTime_18 + 1);
    }
    if (ED_TotalFrames >= 19 && ED_FrameTime_19 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 1 * 55, 242 + 9 * 15, makecol(255, 255, 255), -1, "19. %i",
                             ED_FrameTime_19 + 1);
    }
    if (ED_TotalFrames >= 20 && ED_FrameTime_20 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 0 * 15, makecol(255, 255, 255), -1, "20. %i",
                             ED_FrameTime_20 + 1);
    }
    if (ED_TotalFrames >= 21 && ED_FrameTime_21 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 1 * 15, makecol(255, 255, 255), -1, "21. %i",
                             ED_FrameTime_21 + 1);
    }
    if (ED_TotalFrames >= 22 && ED_FrameTime_22 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 2 * 15, makecol(255, 255, 255), -1, "22. %i",
                             ED_FrameTime_22 + 1);
    }
    if (ED_TotalFrames >= 23 && ED_FrameTime_23 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 3 * 15, makecol(255, 255, 255), -1, "23. %i",
                             ED_FrameTime_23 + 1);
    }
    if (ED_TotalFrames >= 24 && ED_FrameTime_24 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 4 * 15, makecol(255, 255, 255), -1, "24. %i",
                             ED_FrameTime_24 + 1);
    }
    if (ED_TotalFrames >= 25 && ED_FrameTime_25 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 5 * 15, makecol(255, 255, 255), -1, "25. %i",
                             ED_FrameTime_25 + 1);
    }
    if (ED_TotalFrames >= 26 && ED_FrameTime_26 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 6 * 15, makecol(255, 255, 255), -1, "26. %i",
                             ED_FrameTime_26 + 1);
    }
    if (ED_TotalFrames >= 27 && ED_FrameTime_27 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 7 * 15, makecol(255, 255, 255), -1, "27. %i",
                             ED_FrameTime_27 + 1);
    }
    if (ED_TotalFrames >= 28 && ED_FrameTime_28 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 8 * 15, makecol(255, 255, 255), -1, "28. %i",
                             ED_FrameTime_28 + 1);
    }
    if (ED_TotalFrames >= 29 && ED_FrameTime_29 != -1) {
        textprintf_centre_ex(bufferx, font_debug, 30 + 2 * 55, 242 + 9 * 15, makecol(255, 255, 255), -1, "29. %i",
                             ED_FrameTime_29 + 1);
    }

    if (key_Mouse_L_status > 0 && ED_Mx1 > -1 && ED_My1 > -1) {
        //efeito ao desenhar hboxes
        if (ED_DrawRedMode == 1) {
            if (ED_io >= 0 && ED_io <= 1) { rect(bufferx, ED_Mx1, ED_My1, mouse_x, mouse_y, makecol(255,255,255)); }
            if (ED_io >= 2 && ED_io <= 3) { rect(bufferx, ED_Mx1, ED_My1, mouse_x, mouse_y, makecol(255,000,000)); }
        }
        if (ED_DrawBlueMode == 1) {
            if (ED_io >= 0 && ED_io <= 1) { rect(bufferx, ED_Mx1, ED_My1, mouse_x, mouse_y, makecol(255,255,255)); }
            if (ED_io >= 2 && ED_io <= 3) { rect(bufferx, ED_Mx1, ED_My1, mouse_x, mouse_y, makecol(000,000,255)); }
        }
    }
    if (key_Mouse_L_status == 3 && ED_Mx1 > -1 && ED_My1 > -1) {
        ED_Mx2 = mouse_x;
        ED_My2 = mouse_y;
    }

    if (ED_Mx1 > -1 && ED_My1 > -1 && ED_Mx2 > -1 && ED_My2 > -1) {
        // DESENHO DO RETANGULO FEITO!
        if (ED_DrawBlueMode == 1) { ED_HurtBox_tot++; }
        if (ED_HurtBox_tot > 9) { ED_HurtBox_tot = 9; }
        if (ED_DrawRedMode == 1) { ED_HitBox_tot++; }
        if (ED_HitBox_tot > 9) { ED_HitBox_tot = 9; }

        //1-Correcao do box
        int temp1x = 0;
        int temp1y = 0;
        int temp2x = 0;
        int temp2y = 0;
        temp1x = ED_Mx1;
        temp1y = ED_My1;
        temp2x = ED_Mx2;
        temp2y = ED_My2;
        if (temp1x <= temp2x) { ED_Mx1 = temp1x; }
        if (temp1x > temp2x) { ED_Mx1 = temp2x; }
        if (temp1y <= temp2y) { ED_My1 = temp1y; }
        if (temp1y > temp2y) { ED_My1 = temp2y; }
        if (temp2x > temp1x) { ED_Mx2 = temp2x; }
        if (temp2x <= temp1x) { ED_Mx2 = temp1x; }
        if (temp2y > temp1y) { ED_My2 = temp2y; }
        if (temp2y <= temp1y) { ED_My2 = temp1y; }

        // 2- Empilha o box
        if (ED_DrawBlueMode == 1) {
            if (ED_HurtBox_tot == 1) {
                ED_HurtBox01x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox01y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox01x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox01y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 2) {
                ED_HurtBox02x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox02y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox02x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox02y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 3) {
                ED_HurtBox03x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox03y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox03x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox03y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 4) {
                ED_HurtBox04x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox04y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox04x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox04y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 5) {
                ED_HurtBox05x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox05y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox05x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox05y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 6) {
                ED_HurtBox06x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox06y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox06x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox06y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 7) {
                ED_HurtBox07x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox07y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox07x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox07y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 8) {
                ED_HurtBox08x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox08y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox08x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox08y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HurtBox_tot == 9) {
                ED_HurtBox09x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox09y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HurtBox09x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HurtBox09y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            }
        }
        if (ED_DrawRedMode == 1) {
            if (ED_HitBox_tot == 1) {
                ED_HitBox01x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox01y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox01x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox01y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 2) {
                ED_HitBox02x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox02y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox02x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox02y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 3) {
                ED_HitBox03x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox03y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox03x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox03y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 4) {
                ED_HitBox04x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox04y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox04x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox04y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 5) {
                ED_HitBox05x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox05y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox05x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox05y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 6) {
                ED_HitBox06x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox06y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox06x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox06y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 7) {
                ED_HitBox07x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox07y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox07x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox07y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 8) {
                ED_HitBox08x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox08y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox08x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox08y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            } else if (ED_HitBox_tot == 9) {
                ED_HitBox09x1 = ((ED_Mx1 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox09y1 = ((ED_My1 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
                ED_HitBox09x2 = ((ED_Mx2 / 2) - (ED_x - ED_XAlign)) - ED_XAlign;
                ED_HitBox09y2 = ((ED_My2 / 2) - (ED_y - ED_YAlign)) - ED_YAlign;
            }
        }

        //4-salva novo HBox
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/chbox.ini", P[1].Name);
        set_config_file(ED_Caminho);
        char ED_State_s[16];
        if (ED_IndexAnim < 10) { sprintf(ED_State_s, "%i_0%i", ED_State, ED_IndexAnim); }
        if (ED_IndexAnim >= 10) { sprintf(ED_State_s, "%i_%i", ED_State, ED_IndexAnim); }
        if (ED_DrawBlueMode == 1) {
            if (ED_HurtBox_tot == 1) { set_config_int(ED_State_s, "HurtBox01x1", ED_HurtBox01x1); }
            if (ED_HurtBox_tot == 1) { set_config_int(ED_State_s, "HurtBox01y1", ED_HurtBox01y1); }
            if (ED_HurtBox_tot == 1) { set_config_int(ED_State_s, "HurtBox01x2", ED_HurtBox01x2); }
            if (ED_HurtBox_tot == 1) { set_config_int(ED_State_s, "HurtBox01y2", ED_HurtBox01y2); }
            if (ED_HurtBox_tot == 2) { set_config_int(ED_State_s, "HurtBox02x1", ED_HurtBox02x1); }
            if (ED_HurtBox_tot == 2) { set_config_int(ED_State_s, "HurtBox02y1", ED_HurtBox02y1); }
            if (ED_HurtBox_tot == 2) { set_config_int(ED_State_s, "HurtBox02x2", ED_HurtBox02x2); }
            if (ED_HurtBox_tot == 2) { set_config_int(ED_State_s, "HurtBox02y2", ED_HurtBox02y2); }
            if (ED_HurtBox_tot == 3) { set_config_int(ED_State_s, "HurtBox03x1", ED_HurtBox03x1); }
            if (ED_HurtBox_tot == 3) { set_config_int(ED_State_s, "HurtBox03y1", ED_HurtBox03y1); }
            if (ED_HurtBox_tot == 3) { set_config_int(ED_State_s, "HurtBox03x2", ED_HurtBox03x2); }
            if (ED_HurtBox_tot == 3) { set_config_int(ED_State_s, "HurtBox03y2", ED_HurtBox03y2); }
            if (ED_HurtBox_tot == 4) { set_config_int(ED_State_s, "HurtBox04x1", ED_HurtBox04x1); }
            if (ED_HurtBox_tot == 4) { set_config_int(ED_State_s, "HurtBox04y1", ED_HurtBox04y1); }
            if (ED_HurtBox_tot == 4) { set_config_int(ED_State_s, "HurtBox04x2", ED_HurtBox04x2); }
            if (ED_HurtBox_tot == 4) { set_config_int(ED_State_s, "HurtBox04y2", ED_HurtBox04y2); }
            if (ED_HurtBox_tot == 5) { set_config_int(ED_State_s, "HurtBox05x1", ED_HurtBox05x1); }
            if (ED_HurtBox_tot == 5) { set_config_int(ED_State_s, "HurtBox05y1", ED_HurtBox05y1); }
            if (ED_HurtBox_tot == 5) { set_config_int(ED_State_s, "HurtBox05x2", ED_HurtBox05x2); }
            if (ED_HurtBox_tot == 5) { set_config_int(ED_State_s, "HurtBox05y2", ED_HurtBox05y2); }
            if (ED_HurtBox_tot == 6) { set_config_int(ED_State_s, "HurtBox06x1", ED_HurtBox06x1); }
            if (ED_HurtBox_tot == 6) { set_config_int(ED_State_s, "HurtBox06y1", ED_HurtBox06y1); }
            if (ED_HurtBox_tot == 6) { set_config_int(ED_State_s, "HurtBox06x2", ED_HurtBox06x2); }
            if (ED_HurtBox_tot == 6) { set_config_int(ED_State_s, "HurtBox06y2", ED_HurtBox06y2); }
            if (ED_HurtBox_tot == 7) { set_config_int(ED_State_s, "HurtBox07x1", ED_HurtBox07x1); }
            if (ED_HurtBox_tot == 7) { set_config_int(ED_State_s, "HurtBox07y1", ED_HurtBox07y1); }
            if (ED_HurtBox_tot == 7) { set_config_int(ED_State_s, "HurtBox07x2", ED_HurtBox07x2); }
            if (ED_HurtBox_tot == 7) { set_config_int(ED_State_s, "HurtBox07y2", ED_HurtBox07y2); }
            if (ED_HurtBox_tot == 8) { set_config_int(ED_State_s, "HurtBox08x1", ED_HurtBox08x1); }
            if (ED_HurtBox_tot == 8) { set_config_int(ED_State_s, "HurtBox08y1", ED_HurtBox08y1); }
            if (ED_HurtBox_tot == 8) { set_config_int(ED_State_s, "HurtBox08x2", ED_HurtBox08x2); }
            if (ED_HurtBox_tot == 8) { set_config_int(ED_State_s, "HurtBox08y2", ED_HurtBox08y2); }
            if (ED_HurtBox_tot == 9) { set_config_int(ED_State_s, "HurtBox09x1", ED_HurtBox09x1); }
            if (ED_HurtBox_tot == 9) { set_config_int(ED_State_s, "HurtBox09y1", ED_HurtBox09y1); }
            if (ED_HurtBox_tot == 9) { set_config_int(ED_State_s, "HurtBox09x2", ED_HurtBox09x2); }
            if (ED_HurtBox_tot == 9) { set_config_int(ED_State_s, "HurtBox09y2", ED_HurtBox09y2); }
        }
        if (ED_DrawRedMode == 1) {
            if (ED_HitBox_tot == 1) { set_config_int(ED_State_s, "HitBox01x1", ED_HitBox01x1); }
            if (ED_HitBox_tot == 1) { set_config_int(ED_State_s, "HitBox01y1", ED_HitBox01y1); }
            if (ED_HitBox_tot == 1) { set_config_int(ED_State_s, "HitBox01x2", ED_HitBox01x2); }
            if (ED_HitBox_tot == 1) { set_config_int(ED_State_s, "HitBox01y2", ED_HitBox01y2); }
            if (ED_HitBox_tot == 2) { set_config_int(ED_State_s, "HitBox02x1", ED_HitBox02x1); }
            if (ED_HitBox_tot == 2) { set_config_int(ED_State_s, "HitBox02y1", ED_HitBox02y1); }
            if (ED_HitBox_tot == 2) { set_config_int(ED_State_s, "HitBox02x2", ED_HitBox02x2); }
            if (ED_HitBox_tot == 2) { set_config_int(ED_State_s, "HitBox02y2", ED_HitBox02y2); }
            if (ED_HitBox_tot == 3) { set_config_int(ED_State_s, "HitBox03x1", ED_HitBox03x1); }
            if (ED_HitBox_tot == 3) { set_config_int(ED_State_s, "HitBox03y1", ED_HitBox03y1); }
            if (ED_HitBox_tot == 3) { set_config_int(ED_State_s, "HitBox03x2", ED_HitBox03x2); }
            if (ED_HitBox_tot == 3) { set_config_int(ED_State_s, "HitBox03y2", ED_HitBox03y2); }
            if (ED_HitBox_tot == 4) { set_config_int(ED_State_s, "HitBox04x1", ED_HitBox04x1); }
            if (ED_HitBox_tot == 4) { set_config_int(ED_State_s, "HitBox04y1", ED_HitBox04y1); }
            if (ED_HitBox_tot == 4) { set_config_int(ED_State_s, "HitBox04x2", ED_HitBox04x2); }
            if (ED_HitBox_tot == 4) { set_config_int(ED_State_s, "HitBox04y2", ED_HitBox04y2); }
            if (ED_HitBox_tot == 5) { set_config_int(ED_State_s, "HitBox05x1", ED_HitBox05x1); }
            if (ED_HitBox_tot == 5) { set_config_int(ED_State_s, "HitBox05y1", ED_HitBox05y1); }
            if (ED_HitBox_tot == 5) { set_config_int(ED_State_s, "HitBox05x2", ED_HitBox05x2); }
            if (ED_HitBox_tot == 5) { set_config_int(ED_State_s, "HitBox05y2", ED_HitBox05y2); }
            if (ED_HitBox_tot == 6) { set_config_int(ED_State_s, "HitBox06x1", ED_HitBox06x1); }
            if (ED_HitBox_tot == 6) { set_config_int(ED_State_s, "HitBox06y1", ED_HitBox06y1); }
            if (ED_HitBox_tot == 6) { set_config_int(ED_State_s, "HitBox06x2", ED_HitBox06x2); }
            if (ED_HitBox_tot == 6) { set_config_int(ED_State_s, "HitBox06y2", ED_HitBox06y2); }
            if (ED_HitBox_tot == 7) { set_config_int(ED_State_s, "HitBox07x1", ED_HitBox07x1); }
            if (ED_HitBox_tot == 7) { set_config_int(ED_State_s, "HitBox07y1", ED_HitBox07y1); }
            if (ED_HitBox_tot == 7) { set_config_int(ED_State_s, "HitBox07x2", ED_HitBox07x2); }
            if (ED_HitBox_tot == 7) { set_config_int(ED_State_s, "HitBox07y2", ED_HitBox07y2); }
            if (ED_HitBox_tot == 8) { set_config_int(ED_State_s, "HitBox08x1", ED_HitBox08x1); }
            if (ED_HitBox_tot == 8) { set_config_int(ED_State_s, "HitBox08y1", ED_HitBox08y1); }
            if (ED_HitBox_tot == 8) { set_config_int(ED_State_s, "HitBox08x2", ED_HitBox08x2); }
            if (ED_HitBox_tot == 8) { set_config_int(ED_State_s, "HitBox08y2", ED_HitBox08y2); }
            if (ED_HitBox_tot == 9) { set_config_int(ED_State_s, "HitBox09x1", ED_HitBox09x1); }
            if (ED_HitBox_tot == 9) { set_config_int(ED_State_s, "HitBox09y1", ED_HitBox09y1); }
            if (ED_HitBox_tot == 9) { set_config_int(ED_State_s, "HitBox09x2", ED_HitBox09x2); }
            if (ED_HitBox_tot == 9) { set_config_int(ED_State_s, "HitBox09y2", ED_HitBox09y2); }
        }

        //5-Zera os controles de posicao do cursor MXs
        ED_Mx1 = -1;
        ED_My1 = -1;
        ED_Mx2 = -1;
        ED_My2 = -1;
    }

    if (ED_DrawRedMode == 1 || ED_DrawBlueMode == 1) {
        //3-Desenha Caixas
        if (ED_bt_Null == 1) {
            if (ED_HurtBox01x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox01x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox01y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox01x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox01y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox02x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox02x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox02y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox02x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox02y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox03x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox03x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox03y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox03x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox03y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox04x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox04x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox04y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox04x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox04y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox05x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox05x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox05y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox05x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox05y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox06x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox06x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox06y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox06x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox06y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox07x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox07x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox07y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox07x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox07y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox08x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox08x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox08y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox08x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox08y2*2, makecol(000,000,255));
            }
            if (ED_HurtBox09x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox09x1*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox09y1*2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HurtBox09x2*2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HurtBox09y2*2, makecol(000,000,255));
            }
            if (ED_HitBox01x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox01x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox01y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox01x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox01y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox02x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox02x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox02y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox02x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox02y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox03x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox03x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox03y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox03x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox03y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox04x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox04x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox04y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox04x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox04y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox05x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox05x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox05y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox05x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox05y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox06x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox06x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox06y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox06x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox06y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox07x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox07x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox07y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox07x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox07y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox08x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox08x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox08y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox08x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox08y2 *2, makecol(255,000,000));
            }
            if (ED_HitBox09x1 != -5555) {
                rect(bufferx, (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox09x1 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox09y1 *2,
                     (((ED_x-ED_XAlign)*2)+ED_XAlign*2)+ED_HitBox09x2 *2,
                     (((ED_y-ED_YAlign)*2)+ED_YAlign*2)+ED_HitBox09y2 *2, makecol(255,000,000));
            }
        }

        /*
                        //debug do EDITOR
                        //if (key_Mouse_L_status>0 && mouse_x>170 && mouse_y>40) { textprintf_ex(bufferx, font_debug, 190, 50+ 0*15, makecol(255,255,255), -1, "x1[%i] y1[%i] x2:%i y2:%i", ED_Mx1, ED_My1, mouse_x, mouse_y); }
                        if (ED_DrawRedMode ==1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 0*10, makecol(255,255,255), -1, "Modo de Desenho: HitBox"); }
                        if (ED_DrawBlueMode==1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 0*10, makecol(255,255,255), -1, "Modo de Desenho: HurtBox"); }
                        { textprintf_right_ex(bufferx, font_10, 630, 50+ 1*10, makecol(255,255,255), -1, "HurtBox Total: %i", ED_HurtBox_tot); }
                        { textprintf_right_ex(bufferx, font_10, 630, 50+ 2*10, makecol(255,255,255), -1, "HitBox Total: %i", ED_HitBox_tot);  }
                        if (ED_HurtBox01x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 3*10, makecol(255,255,255), -1, "HurtBox1: %i,%i,%i,%i", ED_HurtBox01x1, ED_HurtBox01y1, ED_HurtBox01x2, ED_HurtBox01y2); }
                        if (ED_HurtBox02x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 4*10, makecol(255,255,255), -1, "HurtBox2: %i,%i,%i,%i", ED_HurtBox02x1, ED_HurtBox02y1, ED_HurtBox02x2, ED_HurtBox02y2); }
                        if (ED_HurtBox03x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 5*10, makecol(255,255,255), -1, "HurtBox3: %i,%i,%i,%i", ED_HurtBox03x1, ED_HurtBox03y1, ED_HurtBox03x2, ED_HurtBox03y2); }
                        if (ED_HurtBox04x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 6*10, makecol(255,255,255), -1, "HurtBox4: %i,%i,%i,%i", ED_HurtBox04x1, ED_HurtBox04y1, ED_HurtBox04x2, ED_HurtBox04y2); }
                        if (ED_HurtBox05x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 7*10, makecol(255,255,255), -1, "HurtBox5: %i,%i,%i,%i", ED_HurtBox05x1, ED_HurtBox05y1, ED_HurtBox05x2, ED_HurtBox05y2); }
                        if (ED_HurtBox06x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 8*10, makecol(255,255,255), -1, "HurtBox6: %i,%i,%i,%i", ED_HurtBox06x1, ED_HurtBox06y1, ED_HurtBox06x2, ED_HurtBox06y2); }
                        if (ED_HurtBox07x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 9*10, makecol(255,255,255), -1, "HurtBox7: %i,%i,%i,%i", ED_HurtBox07x1, ED_HurtBox07y1, ED_HurtBox07x2, ED_HurtBox07y2); }
                        if (ED_HurtBox08x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+10*10, makecol(255,255,255), -1, "HurtBox8: %i,%i,%i,%i", ED_HurtBox08x1, ED_HurtBox08y1, ED_HurtBox08x2, ED_HurtBox08y2); }
                        if (ED_HurtBox09x1!=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+11*10, makecol(255,255,255), -1, "HurtBox9: %i,%i,%i,%i", ED_HurtBox09x1, ED_HurtBox09y1, ED_HurtBox09x2, ED_HurtBox09y2); }
                        if (ED_HitBox01x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+12*10, makecol(255,255,255), -1, "HitBox1.: %i,%i,%i,%i", ED_HitBox01x1, ED_HitBox01y1, ED_HitBox01x2, ED_HitBox01y2); }
                        if (ED_HitBox02x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+13*10, makecol(255,255,255), -1, "HitBox2.: %i,%i,%i,%i", ED_HitBox02x1, ED_HitBox02y1, ED_HitBox02x2, ED_HitBox02y2); }
                        if (ED_HitBox03x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+14*10, makecol(255,255,255), -1, "HitBox3.: %i,%i,%i,%i", ED_HitBox03x1, ED_HitBox03y1, ED_HitBox03x2, ED_HitBox03y2); }
                        if (ED_HitBox04x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+15*10, makecol(255,255,255), -1, "HitBox4.: %i,%i,%i,%i", ED_HitBox04x1, ED_HitBox04y1, ED_HitBox04x2, ED_HitBox04y2); }
                        if (ED_HitBox05x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+16*10, makecol(255,255,255), -1, "HitBox5.: %i,%i,%i,%i", ED_HitBox05x1, ED_HitBox05y1, ED_HitBox05x2, ED_HitBox05y2); }
                        if (ED_HitBox06x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+17*10, makecol(255,255,255), -1, "HitBox6.: %i,%i,%i,%i", ED_HitBox06x1, ED_HitBox06y1, ED_HitBox06x2, ED_HitBox06y2); }
                        if (ED_HitBox07x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+18*10, makecol(255,255,255), -1, "HitBox7.: %i,%i,%i,%i", ED_HitBox07x1, ED_HitBox07y1, ED_HitBox07x2, ED_HitBox07y2); }
                        if (ED_HitBox08x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+19*10, makecol(255,255,255), -1, "HitBox8.: %i,%i,%i,%i", ED_HitBox08x1, ED_HitBox08y1, ED_HitBox08x2, ED_HitBox08y2); }
                        if (ED_HitBox09x1 !=-1) { textprintf_right_ex(bufferx, font_10, 630, 50+20*10, makecol(255,255,255), -1, "HitBox9.: %i,%i,%i,%i", ED_HitBox09x1, ED_HitBox09y1, ED_HitBox09x2, ED_HitBox09y2); }
                        if (ED_HurtBox01x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 3*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox02x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 4*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox03x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 5*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox04x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 6*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox05x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 7*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox06x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 8*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox07x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+ 9*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox08x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+10*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HurtBox09x1==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+11*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox01x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+12*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox02x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+13*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox03x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+14*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox04x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+15*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox05x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+16*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox06x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+17*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox07x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+18*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox08x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+19*10, makecol(255,255,255), -1, "----"); }
                        if (ED_HitBox09x1 ==-1) { textprintf_right_ex(bufferx, font_10, 630, 50+20*10, makecol(255,255,255), -1, "----"); }
                    */

        //new EDIT_MODE
        textprintf_right_ex(bufferx, font_10, 56, 98, makecol(255, 255, 255), -1, "%i", ED_HurtBox_tot);
        textprintf_right_ex(bufferx, font_10, 111, 98, makecol(255, 255, 255), -1, "%i", ED_HitBox_tot);
    }

    if (ED_ShowMsgSaving == 1) {
        draw_sprite(bufferx, save_file, 185, 460);
        textprintf_centre_ex(bufferx, font_debug, 425, 458, makecol(255, 255, 255), -1, "Saving...");
    }

    textprintf_centre_ex(bufferx, font_debug, 84, 150, makecol(255, 255, 255), -1, "St [%i] Fr [%i/%i]", ED_State,
                         ED_IndexAnim, ED_TotalFrames);

    //escolha do personagem
    draw_sprite(bufferx, ED_Mini, 192, 5);
    rect(bufferx, 172, 5, 172+15, 5+15, 0xffffff);
    rect(bufferx, 172, 20+1, 172+15, 5+30+1, 0xffffff);
    rect(bufferx, 228, 5, 228+15, 5+15, 0xffffff);
    rect(bufferx, 228, 20+1, 228+15, 5+30+1, 0xffffff);

    int deveinicializar = 0;

    // botao CharID--
    if (key_Mouse_L_status == 1 && mouse_x > 172 && mouse_x < 187 && mouse_y > 5 && mouse_y < 20) {
        ED_CharID--;
        if (ED_CharID < 1) { ED_CharID = 1; }
        strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
        deveinicializar = 1;
    }

    // botao CharID++
    if (key_Mouse_L_status == 1 && mouse_x > 228 && mouse_x < 243 && mouse_y > 5 && mouse_y < 20) {
        ED_CharID++;
        if (ED_CharID > Qtde_Personagens_Instalados) { ED_CharID = Qtde_Personagens_Instalados; }
        strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
        deveinicializar = 1;
    }

    // botao CharID=1
    if (key_Mouse_L_status == 1 && mouse_x > 172 && mouse_x < 187 && mouse_y > 21 && mouse_y < 36) {
        ED_CharID = 1;
        strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
        deveinicializar = 1;
    }

    // botao CharID=Qtde_Personagens_Instalados
    if (key_Mouse_L_status == 1 && mouse_x > 228 && mouse_x < 243 && mouse_y > 21 && mouse_y < 36) {
        ED_CharID = Qtde_Personagens_Instalados;
        strcpy(P[1].Name, Lista_de_Personagens_Instalados[ED_CharID]);
        deveinicializar = 1;
    }

    //render type
    rect(bufferx, 260, 5, 260+15, 5+15, 0xffffff);
    if (ED_Tipo == 2)
        rectfill(bufferx, 260, 5, 260+15, 5+15, 0x00ff00);
    textprintf_ex(bufferx, font_debug, 280, 5 - 2, makecol(255, 255, 255), -1, "HD Sprite");
    if (key_Mouse_L_status == 1 && mouse_x > 260 && mouse_x < 275 && mouse_y > 5 && mouse_y < 20) {
        //	int a=1;
        //	if(ED_Tipo==2 && a==1) { ED_Tipo=1; a=0; deveinicializar=1; }
        //	if(ED_Tipo==1 && a==1) { ED_Tipo=2; a=0; deveinicializar=1; }
        //	char ED_Caminho[99];
        //	sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
        //	set_config_file(ED_Caminho);
        //	if(ED_Tipo==1) set_config_int("Info", "Type", 1);
        //	if(ED_Tipo==2) set_config_int("Info", "Type", 2);
    }

    rect(bufferx, 260, 21, 260+15, 36, 0xffffff);
    textprintf_ex(bufferx, font_debug, 280, 20 - 2, makecol(255, 255, 255), -1, "Onion Skin");

    rect(bufferx, 370, 5, 370+15, 20, 0xffffff);
    textprintf_ex(bufferx, font_debug, 390, 5 - 2, makecol(255, 255, 255), -1, "Grid");
    rect(bufferx, 370, 21, 370+15, 36, 0xffffff);
    textprintf_ex(bufferx, font_debug, 390, 20 - 2, makecol(255, 255, 255), -1, "Floor");

    /*temporario*/
    draw_sprite(bufferx, spr_nao_implementado, 259, 0); /*temporario*/

    //---deve inicializar---//
    if (deveinicializar == 1) {
        ED_inicializar();
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/000_01.png", P[1].Name);
        ED_Mini = load_bitmap(ED_Caminho, NULL);
        if (!ED_Mini) { ED_Mini = load_bitmap("data/system/000_01.png", NULL); }
    }

    textprintf_ex(bufferx, font_debug, 13, 8 - 2, makecol(000, 000, 000), -1, "HAMOOPI EDITOR");
    textprintf_ex(bufferx, font_debug, 10, 5 - 2, makecol(255, 255, 000), -1, "HAMOOPI EDITOR");
    textprintf_ex(bufferx, font_debug, 13, 23 - 2, makecol(0, 0, 0), -1, "%s", P[1].Name);
    textprintf_ex(bufferx, font_debug, 10, 20 - 2, makecol(255, 255, 255), -1, "%s", P[1].Name);

    //mouse
    if (ED_MODE == 1) {
        if (mouse_x > 175 && mouse_y > 45) {
            draw_sprite(bufferx, mouse, mouse_x-(mouse->w/2), mouse_y-(mouse->h/2));
            circle(bufferx, mouse_x, mouse_y, 12, 0xffffff);
        } else {
            draw_sprite(bufferx, mouse2, mouse_x-(mouse->w/2), mouse_y-(mouse->h/2));
        }
    }
    if (ED_MODE == 2) {
        draw_sprite(bufferx, mouse2, mouse_x-(mouse->w/2), mouse_y-(mouse->h/2));
    }

    ED_io++;
    if (ED_io > 3) { ED_io = 0; } //usado para animacoes
}
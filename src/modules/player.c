#include "player.h"

void LOAD_PLAYERS() {
    //conta as imagens dos players, abastece o total de frames de cada movimento
    char txt[50] = "";
    for (int indPlayer = 1; indPlayer <= 2; indPlayer++) {
        P[indPlayer].TotalDeImagensUtilizadas = -1;
        for (int indState = 100; indState <= 999; indState++) {
            P[indPlayer].TotalDeFramesMov[indState] = -1;
            for (int indAnim = 0; indAnim <= 29; indAnim++) {
                if (indAnim < 10) { sprintf(txt, "data/chars/%s/%d_0%d.png", P[indPlayer].Name, indState, indAnim); }
                if (indAnim >= 10) { sprintf(txt, "data/chars/%s/%d_%d.png", P[indPlayer].Name, indState, indAnim); }
                if (exists(txt)) {
                    P[indPlayer].TotalDeFramesMov[indState]++; //contagem de numero de frames de cada State (Movimento)
                    P[indPlayer].TotalDeImagensUtilizadas++; //contagem total da quantidade de frames deste personagem

                    /*COLOCA A IMAGENS NA MEMORIA*/
                    BITMAP *Spr_Aux = create_bitmap(480, 480);
                    Spr_Aux = load_bitmap(txt, NULL);
                    P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->w = Spr_Aux->w;
                    P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->h = Spr_Aux->h;

                    //--!	PALETA DE COR
                    BITMAP *P1_Pallete = create_bitmap(32, 10);
                    BITMAP *P2_Pallete = create_bitmap(32, 10);
                    clear_to_color(P1_Pallete, makecol(255, 0, 255));
                    clear_to_color(P2_Pallete, makecol(255, 0, 255));
                    sprintf(P1_Pallete_string, "data/chars/%s/pallete.png", P[1].Name);
                    P1_Pallete = load_bitmap(P1_Pallete_string, NULL);
                    sprintf(P2_Pallete_string, "data/chars/%s/pallete.png", P[2].Name);
                    P2_Pallete = load_bitmap(P2_Pallete_string, NULL);

                    if (indPlayer == 1) {
                        /*P1 PALETA DE COR*/
                        if (P[1].PossuiPaletaDeCor == 1) {
                            int x, y;
                            //etapa0: conta a quantidade de cores da paleta
                            for (int ind = 0; ind < 32; ind++) {
                                P1_ContadorDeCor = 0;
                                for (int ind = 0; ind < 32; ind++) {
                                    if (getpixel(P1_Pallete, ind, 0) != makecol(255, 0, 255)) { P1_ContadorDeCor++; }
                                }
                            }
                            //etapa1: pega as duas cores
                            for (int ind = 0; ind < P1_ContadorDeCor; ind++) {
                                P1_COR_ORIGINAL = getpixel(P1_Pallete, ind, 0); //cor0
                                P1_COR_ORIGINAL_R = getr(P1_COR_ORIGINAL);
                                P1_COR_ORIGINAL_G = getg(P1_COR_ORIGINAL);
                                P1_COR_ORIGINAL_B = getb(P1_COR_ORIGINAL);
                                P1_COR_ALTERNATIVA = getpixel(P1_Pallete, ind, P[1].DefineCorDaPaleta); //cor escolhida
                                P1_COR_ALTERNATIVA_R = getr(P1_COR_ALTERNATIVA);
                                P1_COR_ALTERNATIVA_G = getg(P1_COR_ALTERNATIVA);
                                P1_COR_ALTERNATIVA_B = getb(P1_COR_ALTERNATIVA);
                                //etapa2: faz a substituicao das cores, se a cor COR_ALTERNATIVA nao for transparente
                                int PodeTrocarAsCores = 1;
                                if (P1_COR_ALTERNATIVA_R == 255 && P1_COR_ALTERNATIVA_G == 0 && P1_COR_ALTERNATIVA_B ==
                                    255) { PodeTrocarAsCores = 0; }
                                if (PodeTrocarAsCores == 1) {
                                    for (y = 0; y < Spr_Aux->h; y++) {
                                        for (x = 0; x < Spr_Aux->w; x++) {
                                            if (getpixel(Spr_Aux, x, y) == makecol(P1_COR_ORIGINAL_R, P1_COR_ORIGINAL_G,
                                                    P1_COR_ORIGINAL_B)) {
                                                putpixel(Spr_Aux, x, y,
                                                         makecol(P1_COR_ALTERNATIVA_R,P1_COR_ALTERNATIVA_G,
                                                             P1_COR_ALTERNATIVA_B));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if (indPlayer == 2) {
                        /*P2 PALETA DE COR*/
                        if (P[2].PossuiPaletaDeCor == 1) {
                            int x, y;
                            //etapa0: conta a quantidade de cores da paleta
                            for (int ind = 0; ind < 32; ind++) {
                                P2_ContadorDeCor = 0;
                                for (int ind = 0; ind < 32; ind++) {
                                    if (getpixel(P2_Pallete, ind, 0) != makecol(255, 0, 255)) { P2_ContadorDeCor++; }
                                }
                            }
                            //etapa1: pega as duas cores
                            for (int ind = 0; ind < P2_ContadorDeCor; ind++) {
                                P2_COR_ORIGINAL = getpixel(P2_Pallete, ind, 0); //cor0
                                P2_COR_ORIGINAL_R = getr(P2_COR_ORIGINAL);
                                P2_COR_ORIGINAL_G = getg(P2_COR_ORIGINAL);
                                P2_COR_ORIGINAL_B = getb(P2_COR_ORIGINAL);
                                P2_COR_ALTERNATIVA = getpixel(P2_Pallete, ind, P[2].DefineCorDaPaleta); //cor escolhida
                                P2_COR_ALTERNATIVA_R = getr(P2_COR_ALTERNATIVA);
                                P2_COR_ALTERNATIVA_G = getg(P2_COR_ALTERNATIVA);
                                P2_COR_ALTERNATIVA_B = getb(P2_COR_ALTERNATIVA);
                                //etapa2: faz a substituicao das cores, se a cor COR_ALTERNATIVA nao for transparente
                                int PodeTrocarAsCores = 1;
                                if (P2_COR_ALTERNATIVA_R == 255 && P2_COR_ALTERNATIVA_G == 0 && P2_COR_ALTERNATIVA_B ==
                                    255) { PodeTrocarAsCores = 0; }
                                if (PodeTrocarAsCores == 1) {
                                    for (y = 0; y < Spr_Aux->h; y++) {
                                        for (x = 0; x < Spr_Aux->w; x++) {
                                            if (getpixel(Spr_Aux, x, y) == makecol(P2_COR_ORIGINAL_R, P2_COR_ORIGINAL_G,
                                                    P2_COR_ORIGINAL_B)) {
                                                putpixel(Spr_Aux, x, y,
                                                         makecol(P2_COR_ALTERNATIVA_R,P2_COR_ALTERNATIVA_G,
                                                             P2_COR_ALTERNATIVA_B));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    destroy_bitmap(P1_Pallete);
                    destroy_bitmap(P2_Pallete);
                    //--!

                    //se for Type 1 dobra o tamanho do Sprite, e abastece o Atlas
                    if (P[indPlayer].Type == 1) {
                        P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->w =
                                P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->w * 2;
                        P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->h =
                                P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->h * 2;
                        //abastece o Atlas type1
                        stretch_blit(Spr_Aux, P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas],
                                     0, 0, Spr_Aux->w, Spr_Aux->h,
                                     0, 0, P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->w,
                                     P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas]->h);
                    }
                    //abastece o Atlas type2
                    if (P[indPlayer].Type == 2) {
                        blit(Spr_Aux, P[indPlayer].SprAtlas[P[indPlayer].TotalDeImagensUtilizadas], 0, 0, 0, 0,
                             Spr_Aux->w, Spr_Aux->h);
                    }
                    destroy_bitmap(Spr_Aux);
                    //tabela do Atlas
                    P[indPlayer].TableAtlas[P[indPlayer].TotalDeImagensUtilizadas][0] = indState;
                    P[indPlayer].TableAtlas[P[indPlayer].TotalDeImagensUtilizadas][1] = indAnim;
                    P[indPlayer].TableAtlas[P[indPlayer].TotalDeImagensUtilizadas][2] = P[indPlayer].
                            TotalDeImagensUtilizadas;

                    AddTableAtlas(indPlayer, indState, indAnim, P[indPlayer].TotalDeImagensUtilizadas);
                } else { indAnim = 29; }
            }
            if (indState == 100) { P[indPlayer].QtdeFrames = P[indPlayer].TotalDeFramesMov[100]; }
        }

        //movimentos ignorados, pois nao sao utilizados em jogos de luta
        // A sequencia de Movs 311-316 correspondem a golpes aereos pulando para tras,
        //   assume-se que sao iguais os golpes aereos pulando para frente.
        // A sequencia 603 e 605 sao end Pulo para frente e para tras,
        //   assume-se que sao iguais o end Pulo do Pulo Neutro.
        P[indPlayer].TotalDeFramesMov[311] = P[indPlayer].TotalDeFramesMov[321]; //movimentos 311-316 ignorados
        P[indPlayer].TotalDeFramesMov[312] = P[indPlayer].TotalDeFramesMov[322]; //movimentos 311-316 ignorados
        P[indPlayer].TotalDeFramesMov[313] = P[indPlayer].TotalDeFramesMov[323]; //movimentos 311-316 ignorados
        P[indPlayer].TotalDeFramesMov[314] = P[indPlayer].TotalDeFramesMov[324]; //movimentos 311-316 ignorados
        P[indPlayer].TotalDeFramesMov[315] = P[indPlayer].TotalDeFramesMov[325]; //movimentos 311-316 ignorados
        P[indPlayer].TotalDeFramesMov[316] = P[indPlayer].TotalDeFramesMov[326]; //movimentos 311-316 ignorados
        P[indPlayer].TotalDeFramesMov[603] = P[indPlayer].TotalDeFramesMov[604]; //movimentos 603 e 605 ignorados
        P[indPlayer].TotalDeFramesMov[605] = P[indPlayer].TotalDeFramesMov[604]; //movimentos 603 e 605 ignorados

        if (indPlayer == 1) { PLAYER_STATE(1, 100, 0, P[indPlayer].QtdeFrames); }
        if (indPlayer == 2) { PLAYER_STATE(2, 100, 0, P[indPlayer].QtdeFrames); }
    }

    //cria o char vazio
    for (int ind = 1; ind <= 2; ind++) {
        if (P[ind].TotalDeImagensUtilizadas == -1) {
            P[ind].TotalDeImagensUtilizadas = 0;
            BITMAP *Spr_Aux = create_bitmap(480, 480);
            Spr_Aux = load_bitmap("data/system/char_generic2x.png", NULL);
            P[ind].SprAtlas[0]->w = Spr_Aux->w;
            P[ind].SprAtlas[0]->h = Spr_Aux->h;
            blit(Spr_Aux, P[ind].SprAtlas[0], 0, 0, 0, 0, Spr_Aux->w, Spr_Aux->h);
            destroy_bitmap(Spr_Aux);
            P[ind].TableAtlas[P[ind].TotalDeImagensUtilizadas][0] = 100;
            P[ind].TableAtlas[P[ind].TotalDeImagensUtilizadas][1] = 0;
            P[ind].TableAtlas[P[ind].TotalDeImagensUtilizadas][2] = P[ind].TotalDeImagensUtilizadas;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// STATES sao funcoes muito importantes para o jogo, PLAYER_STATE() ---------------------------------------------------------------------------[**12]
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PLAYER_STATE(int Player, int State, int IndexAnim, int QtdeFrames) {
    //for(int ind=1;ind<=2;ind++){

    int ind = Player;

    P[ind].State = State;
    P[ind].State = State;

    P[ind].IndexAnim = IndexAnim;
    P[ind].QtdeFrames = QtdeFrames;

    Draw_CHBoxes_P1();
    Draw_CHBoxes_P2();

    char P1_Caminho[99];
    if (ind == 1) {
        sprintf(P1_Caminho, "data/chars/%s/char.ini", P[ind].Name);
        set_config_file(P1_Caminho);
    }

    char P2_Caminho[99];
    if (ind == 2) {
        sprintf(P2_Caminho, "data/chars/%s/char.ini", P[ind].Name);
        set_config_file(P2_Caminho);
    }

    P[ind].Vspeed_temp = P[ind].Vspeed;
    P[ind].Hspeed_temp = P[ind].Hspeed;
    P[ind].Gravity_temp = P[ind].Gravity;

    if (P[ind].State >= 100) { sprintf(P[ind].State_s, "%i", P[ind].State); }
    if (P[ind].State < 100) { sprintf(P[ind].State_s, "0%i", P[ind].State); }

    strcpy(P[ind].Name_Display, (char *)get_config_string("Info", "Name", "-"));

    P[ind].XAlign = get_config_int(P[ind].State_s, "XAlign", P[ind].Largura/2); //P[ind].Largura_100
    P[ind].YAlign = get_config_int(P[ind].State_s, "YAlign", P[ind].Altura);
    P[ind].Vspeed = get_config_float(P[ind].State_s, "Vspeed", 0);
    P[ind].Hspeed = get_config_float(P[ind].State_s, "Hspeed", 0);
    P[ind].Gravity = get_config_float(P[ind].State_s, "Gravity", 0);
    P[ind].Friction = get_config_float(P[ind].State_s, "Friction", 0);
    P[ind].ChangeDamage = get_config_int(P[ind].State_s, "Damage", 0);
    P[ind].Energy += get_config_int(P[ind].State_s, "Energy", 0);
    P[ind].Special += get_config_int(P[ind].State_s, "Special", 0);
    P[ind].EnergyChange = get_config_int(P[ind].State_s, "EnergyChange", 0);
    P[ind].SpecialChange = get_config_int(P[ind].State_s, "SpecialChange", 0);
    P[ind].Visible = get_config_int(P[ind].State_s, "Visible", 1);
    P[ind].RoomLimit = get_config_int(P[ind].State_s, "RoomLimit", 1);
    strcpy(P[ind].HitType, (char *)get_config_string(P[ind].State_s, "HitType","Normal"));
    strcpy(P[ind].HitStack, (char *)get_config_string(P[ind].State_s, "HitStack","Multi"));
    P[ind].HitPause = get_config_int(P[ind].State_s, "HitPause", 0);
    P[ind].ChangeState = get_config_int(P[ind].State_s, "ChangeState", 0);
    P[ind].Freeze = get_config_int(P[ind].State_s, "Freeze", 0);
    P[ind].Color = get_config_int(P[ind].State_s, "Color", -1);
    P[ind].TotalFrames = get_config_int(P[ind].State_s, "TotalFrames", QtdeFrames);

    //Altera a Energia
    P[ind].Energy += P[ind].EnergyChange;
    if (P[ind].Energy > 1000) { P[ind].Energy = 1000; }
    if (P[ind].Energy < 0) { P[ind].Energy = 0; }

    //Altera o Special
    P[ind].Special += P[ind].SpecialChange;
    if (P[ind].Special > 1000) { P[ind].Special = 1000; }
    if (P[ind].Special < 0) { P[ind].Special = 0; }

    if (ind == 1) {
        if (P[1].TotalFrames >= 0) { P1_FrameTime_00 = get_config_int(P[1].State_s, "FrameTime_00", 6) - 1; }
        if (P[1].TotalFrames >= 1) { P1_FrameTime_01 = get_config_int(P[1].State_s, "FrameTime_01", 6) - 1; }
        if (P[1].TotalFrames >= 2) { P1_FrameTime_02 = get_config_int(P[1].State_s, "FrameTime_02", 6) - 1; }
        if (P[1].TotalFrames >= 3) { P1_FrameTime_03 = get_config_int(P[1].State_s, "FrameTime_03", 6) - 1; }
        if (P[1].TotalFrames >= 4) { P1_FrameTime_04 = get_config_int(P[1].State_s, "FrameTime_04", 6) - 1; }
        if (P[1].TotalFrames >= 5) { P1_FrameTime_05 = get_config_int(P[1].State_s, "FrameTime_05", 6) - 1; }
        if (P[1].TotalFrames >= 6) { P1_FrameTime_06 = get_config_int(P[1].State_s, "FrameTime_06", 6) - 1; }
        if (P[1].TotalFrames >= 7) { P1_FrameTime_07 = get_config_int(P[1].State_s, "FrameTime_07", 6) - 1; }
        if (P[1].TotalFrames >= 8) { P1_FrameTime_08 = get_config_int(P[1].State_s, "FrameTime_08", 6) - 1; }
        if (P[1].TotalFrames >= 9) { P1_FrameTime_09 = get_config_int(P[1].State_s, "FrameTime_09", 6) - 1; }
        if (P[1].TotalFrames >= 10) { P1_FrameTime_10 = get_config_int(P[1].State_s, "FrameTime_10", 6) - 1; }
        if (P[1].TotalFrames >= 11) { P1_FrameTime_11 = get_config_int(P[1].State_s, "FrameTime_11", 6) - 1; }
        if (P[1].TotalFrames >= 12) { P1_FrameTime_12 = get_config_int(P[1].State_s, "FrameTime_12", 6) - 1; }
        if (P[1].TotalFrames >= 13) { P1_FrameTime_13 = get_config_int(P[1].State_s, "FrameTime_13", 6) - 1; }
        if (P[1].TotalFrames >= 14) { P1_FrameTime_14 = get_config_int(P[1].State_s, "FrameTime_14", 6) - 1; }
        if (P[1].TotalFrames >= 15) { P1_FrameTime_15 = get_config_int(P[1].State_s, "FrameTime_15", 6) - 1; }
        if (P[1].TotalFrames >= 16) { P1_FrameTime_16 = get_config_int(P[1].State_s, "FrameTime_16", 6) - 1; }
        if (P[1].TotalFrames >= 17) { P1_FrameTime_17 = get_config_int(P[1].State_s, "FrameTime_17", 6) - 1; }
        if (P[1].TotalFrames >= 18) { P1_FrameTime_18 = get_config_int(P[1].State_s, "FrameTime_18", 6) - 1; }
        if (P[1].TotalFrames >= 19) { P1_FrameTime_19 = get_config_int(P[1].State_s, "FrameTime_19", 6) - 1; }
        if (P[1].TotalFrames >= 20) { P1_FrameTime_20 = get_config_int(P[1].State_s, "FrameTime_20", 6) - 1; }
        if (P[1].TotalFrames >= 21) { P1_FrameTime_21 = get_config_int(P[1].State_s, "FrameTime_21", 6) - 1; }
        if (P[1].TotalFrames >= 22) { P1_FrameTime_22 = get_config_int(P[1].State_s, "FrameTime_22", 6) - 1; }
        if (P[1].TotalFrames >= 23) { P1_FrameTime_23 = get_config_int(P[1].State_s, "FrameTime_23", 6) - 1; }
        if (P[1].TotalFrames >= 24) { P1_FrameTime_24 = get_config_int(P[1].State_s, "FrameTime_24", 6) - 1; }
        if (P[1].TotalFrames >= 25) { P1_FrameTime_25 = get_config_int(P[1].State_s, "FrameTime_25", 6) - 1; }
        if (P[1].TotalFrames >= 26) { P1_FrameTime_26 = get_config_int(P[1].State_s, "FrameTime_26", 6) - 1; }
        if (P[1].TotalFrames >= 27) { P1_FrameTime_27 = get_config_int(P[1].State_s, "FrameTime_27", 6) - 1; }
        if (P[1].TotalFrames >= 28) { P1_FrameTime_28 = get_config_int(P[1].State_s, "FrameTime_28", 6) - 1; }
        if (P[1].TotalFrames >= 29) { P1_FrameTime_29 = get_config_int(P[1].State_s, "FrameTime_29", 6) - 1; }
        P1_FrameTime = P1_FrameTime_00;
    }

    if (ind == 2) {
        if (P[2].TotalFrames >= 0) { P2_FrameTime_00 = get_config_int(P[2].State_s, "FrameTime_00", 6) - 1; }
        if (P[2].TotalFrames >= 1) { P2_FrameTime_01 = get_config_int(P[2].State_s, "FrameTime_01", 6) - 1; }
        if (P[2].TotalFrames >= 2) { P2_FrameTime_02 = get_config_int(P[2].State_s, "FrameTime_02", 6) - 1; }
        if (P[2].TotalFrames >= 3) { P2_FrameTime_03 = get_config_int(P[2].State_s, "FrameTime_03", 6) - 1; }
        if (P[2].TotalFrames >= 4) { P2_FrameTime_04 = get_config_int(P[2].State_s, "FrameTime_04", 6) - 1; }
        if (P[2].TotalFrames >= 5) { P2_FrameTime_05 = get_config_int(P[2].State_s, "FrameTime_05", 6) - 1; }
        if (P[2].TotalFrames >= 6) { P2_FrameTime_06 = get_config_int(P[2].State_s, "FrameTime_06", 6) - 1; }
        if (P[2].TotalFrames >= 7) { P2_FrameTime_07 = get_config_int(P[2].State_s, "FrameTime_07", 6) - 1; }
        if (P[2].TotalFrames >= 8) { P2_FrameTime_08 = get_config_int(P[2].State_s, "FrameTime_08", 6) - 1; }
        if (P[2].TotalFrames >= 9) { P2_FrameTime_09 = get_config_int(P[2].State_s, "FrameTime_09", 6) - 1; }
        if (P[2].TotalFrames >= 10) { P2_FrameTime_10 = get_config_int(P[2].State_s, "FrameTime_10", 6) - 1; }
        if (P[2].TotalFrames >= 11) { P2_FrameTime_11 = get_config_int(P[2].State_s, "FrameTime_11", 6) - 1; }
        if (P[2].TotalFrames >= 12) { P2_FrameTime_12 = get_config_int(P[2].State_s, "FrameTime_12", 6) - 1; }
        if (P[2].TotalFrames >= 13) { P2_FrameTime_13 = get_config_int(P[2].State_s, "FrameTime_13", 6) - 1; }
        if (P[2].TotalFrames >= 14) { P2_FrameTime_14 = get_config_int(P[2].State_s, "FrameTime_14", 6) - 1; }
        if (P[2].TotalFrames >= 15) { P2_FrameTime_15 = get_config_int(P[2].State_s, "FrameTime_15", 6) - 1; }
        if (P[2].TotalFrames >= 16) { P2_FrameTime_16 = get_config_int(P[2].State_s, "FrameTime_16", 6) - 1; }
        if (P[2].TotalFrames >= 17) { P2_FrameTime_17 = get_config_int(P[2].State_s, "FrameTime_17", 6) - 1; }
        if (P[2].TotalFrames >= 18) { P2_FrameTime_18 = get_config_int(P[2].State_s, "FrameTime_18", 6) - 1; }
        if (P[2].TotalFrames >= 19) { P2_FrameTime_19 = get_config_int(P[2].State_s, "FrameTime_19", 6) - 1; }
        if (P[2].TotalFrames >= 20) { P2_FrameTime_20 = get_config_int(P[2].State_s, "FrameTime_20", 6) - 1; }
        if (P[2].TotalFrames >= 21) { P2_FrameTime_21 = get_config_int(P[2].State_s, "FrameTime_21", 6) - 1; }
        if (P[2].TotalFrames >= 22) { P2_FrameTime_22 = get_config_int(P[2].State_s, "FrameTime_22", 6) - 1; }
        if (P[2].TotalFrames >= 23) { P2_FrameTime_23 = get_config_int(P[2].State_s, "FrameTime_23", 6) - 1; }
        if (P[2].TotalFrames >= 24) { P2_FrameTime_24 = get_config_int(P[2].State_s, "FrameTime_24", 6) - 1; }
        if (P[2].TotalFrames >= 25) { P2_FrameTime_25 = get_config_int(P[2].State_s, "FrameTime_25", 6) - 1; }
        if (P[2].TotalFrames >= 26) { P2_FrameTime_26 = get_config_int(P[2].State_s, "FrameTime_26", 6) - 1; }
        if (P[2].TotalFrames >= 27) { P2_FrameTime_27 = get_config_int(P[2].State_s, "FrameTime_27", 6) - 1; }
        if (P[2].TotalFrames >= 28) { P2_FrameTime_28 = get_config_int(P[2].State_s, "FrameTime_28", 6) - 1; }
        if (P[2].TotalFrames >= 29) { P2_FrameTime_29 = get_config_int(P[2].State_s, "FrameTime_29", 6) - 1; }
        P2_FrameTime = P2_FrameTime_00;
    }

    if (ind == 1) {
        if (ForcaDoGolpeP1 == 1) {
            if (P[1].TotalFrames >= 0) { P1_FrameTime_00 = get_config_int(P[1].State_s, "V1_FrameTime_00", 6) - 1; }
            if (P[1].TotalFrames >= 1) { P1_FrameTime_01 = get_config_int(P[1].State_s, "V1_FrameTime_01", 6) - 1; }
            if (P[1].TotalFrames >= 2) { P1_FrameTime_02 = get_config_int(P[1].State_s, "V1_FrameTime_02", 6) - 1; }
            if (P[1].TotalFrames >= 3) { P1_FrameTime_03 = get_config_int(P[1].State_s, "V1_FrameTime_03", 6) - 1; }
            if (P[1].TotalFrames >= 4) { P1_FrameTime_04 = get_config_int(P[1].State_s, "V1_FrameTime_04", 6) - 1; }
            if (P[1].TotalFrames >= 5) { P1_FrameTime_05 = get_config_int(P[1].State_s, "V1_FrameTime_05", 6) - 1; }
            if (P[1].TotalFrames >= 6) { P1_FrameTime_06 = get_config_int(P[1].State_s, "V1_FrameTime_06", 6) - 1; }
            if (P[1].TotalFrames >= 7) { P1_FrameTime_07 = get_config_int(P[1].State_s, "V1_FrameTime_07", 6) - 1; }
            if (P[1].TotalFrames >= 8) { P1_FrameTime_08 = get_config_int(P[1].State_s, "V1_FrameTime_08", 6) - 1; }
            if (P[1].TotalFrames >= 9) { P1_FrameTime_09 = get_config_int(P[1].State_s, "V1_FrameTime_09", 6) - 1; }
            if (P[1].TotalFrames >= 10) { P1_FrameTime_10 = get_config_int(P[1].State_s, "V1_FrameTime_10", 6) - 1; }
            if (P[1].TotalFrames >= 11) { P1_FrameTime_11 = get_config_int(P[1].State_s, "V1_FrameTime_11", 6) - 1; }
            if (P[1].TotalFrames >= 12) { P1_FrameTime_12 = get_config_int(P[1].State_s, "V1_FrameTime_12", 6) - 1; }
            if (P[1].TotalFrames >= 13) { P1_FrameTime_13 = get_config_int(P[1].State_s, "V1_FrameTime_13", 6) - 1; }
            if (P[1].TotalFrames >= 14) { P1_FrameTime_14 = get_config_int(P[1].State_s, "V1_FrameTime_14", 6) - 1; }
            if (P[1].TotalFrames >= 15) { P1_FrameTime_15 = get_config_int(P[1].State_s, "V1_FrameTime_15", 6) - 1; }
            if (P[1].TotalFrames >= 16) { P1_FrameTime_16 = get_config_int(P[1].State_s, "V1_FrameTime_16", 6) - 1; }
            if (P[1].TotalFrames >= 17) { P1_FrameTime_17 = get_config_int(P[1].State_s, "V1_FrameTime_17", 6) - 1; }
            if (P[1].TotalFrames >= 18) { P1_FrameTime_18 = get_config_int(P[1].State_s, "V1_FrameTime_18", 6) - 1; }
            if (P[1].TotalFrames >= 19) { P1_FrameTime_19 = get_config_int(P[1].State_s, "V1_FrameTime_19", 6) - 1; }
            if (P[1].TotalFrames >= 20) { P1_FrameTime_20 = get_config_int(P[1].State_s, "V1_FrameTime_20", 6) - 1; }
            if (P[1].TotalFrames >= 21) { P1_FrameTime_21 = get_config_int(P[1].State_s, "V1_FrameTime_21", 6) - 1; }
            if (P[1].TotalFrames >= 22) { P1_FrameTime_22 = get_config_int(P[1].State_s, "V1_FrameTime_22", 6) - 1; }
            if (P[1].TotalFrames >= 23) { P1_FrameTime_23 = get_config_int(P[1].State_s, "V1_FrameTime_23", 6) - 1; }
            if (P[1].TotalFrames >= 24) { P1_FrameTime_24 = get_config_int(P[1].State_s, "V1_FrameTime_24", 6) - 1; }
            if (P[1].TotalFrames >= 25) { P1_FrameTime_25 = get_config_int(P[1].State_s, "V1_FrameTime_25", 6) - 1; }
            if (P[1].TotalFrames >= 26) { P1_FrameTime_26 = get_config_int(P[1].State_s, "V1_FrameTime_26", 6) - 1; }
            if (P[1].TotalFrames >= 27) { P1_FrameTime_27 = get_config_int(P[1].State_s, "V1_FrameTime_27", 6) - 1; }
            if (P[1].TotalFrames >= 28) { P1_FrameTime_28 = get_config_int(P[1].State_s, "V1_FrameTime_28", 6) - 1; }
            if (P[1].TotalFrames >= 29) { P1_FrameTime_29 = get_config_int(P[1].State_s, "V1_FrameTime_29", 6) - 1; }
            P1_FrameTime = P1_FrameTime_00;
        }
        if (ForcaDoGolpeP1 == 2) {
            if (P[1].TotalFrames >= 0) { P1_FrameTime_00 = get_config_int(P[1].State_s, "V2_FrameTime_00", 6) - 1; }
            if (P[1].TotalFrames >= 1) { P1_FrameTime_01 = get_config_int(P[1].State_s, "V2_FrameTime_01", 6) - 1; }
            if (P[1].TotalFrames >= 2) { P1_FrameTime_02 = get_config_int(P[1].State_s, "V2_FrameTime_02", 6) - 1; }
            if (P[1].TotalFrames >= 3) { P1_FrameTime_03 = get_config_int(P[1].State_s, "V2_FrameTime_03", 6) - 1; }
            if (P[1].TotalFrames >= 4) { P1_FrameTime_04 = get_config_int(P[1].State_s, "V2_FrameTime_04", 6) - 1; }
            if (P[1].TotalFrames >= 5) { P1_FrameTime_05 = get_config_int(P[1].State_s, "V2_FrameTime_05", 6) - 1; }
            if (P[1].TotalFrames >= 6) { P1_FrameTime_06 = get_config_int(P[1].State_s, "V2_FrameTime_06", 6) - 1; }
            if (P[1].TotalFrames >= 7) { P1_FrameTime_07 = get_config_int(P[1].State_s, "V2_FrameTime_07", 6) - 1; }
            if (P[1].TotalFrames >= 8) { P1_FrameTime_08 = get_config_int(P[1].State_s, "V2_FrameTime_08", 6) - 1; }
            if (P[1].TotalFrames >= 9) { P1_FrameTime_09 = get_config_int(P[1].State_s, "V2_FrameTime_09", 6) - 1; }
            if (P[1].TotalFrames >= 10) { P1_FrameTime_10 = get_config_int(P[1].State_s, "V2_FrameTime_10", 6) - 1; }
            if (P[1].TotalFrames >= 11) { P1_FrameTime_11 = get_config_int(P[1].State_s, "V2_FrameTime_11", 6) - 1; }
            if (P[1].TotalFrames >= 12) { P1_FrameTime_12 = get_config_int(P[1].State_s, "V2_FrameTime_12", 6) - 1; }
            if (P[1].TotalFrames >= 13) { P1_FrameTime_13 = get_config_int(P[1].State_s, "V2_FrameTime_13", 6) - 1; }
            if (P[1].TotalFrames >= 14) { P1_FrameTime_14 = get_config_int(P[1].State_s, "V2_FrameTime_14", 6) - 1; }
            if (P[1].TotalFrames >= 15) { P1_FrameTime_15 = get_config_int(P[1].State_s, "V2_FrameTime_15", 6) - 1; }
            if (P[1].TotalFrames >= 16) { P1_FrameTime_16 = get_config_int(P[1].State_s, "V2_FrameTime_16", 6) - 1; }
            if (P[1].TotalFrames >= 17) { P1_FrameTime_17 = get_config_int(P[1].State_s, "V2_FrameTime_17", 6) - 1; }
            if (P[1].TotalFrames >= 18) { P1_FrameTime_18 = get_config_int(P[1].State_s, "V2_FrameTime_18", 6) - 1; }
            if (P[1].TotalFrames >= 19) { P1_FrameTime_19 = get_config_int(P[1].State_s, "V2_FrameTime_19", 6) - 1; }
            if (P[1].TotalFrames >= 20) { P1_FrameTime_20 = get_config_int(P[1].State_s, "V2_FrameTime_20", 6) - 1; }
            if (P[1].TotalFrames >= 21) { P1_FrameTime_21 = get_config_int(P[1].State_s, "V2_FrameTime_21", 6) - 1; }
            if (P[1].TotalFrames >= 22) { P1_FrameTime_22 = get_config_int(P[1].State_s, "V2_FrameTime_22", 6) - 1; }
            if (P[1].TotalFrames >= 23) { P1_FrameTime_23 = get_config_int(P[1].State_s, "V2_FrameTime_23", 6) - 1; }
            if (P[1].TotalFrames >= 24) { P1_FrameTime_24 = get_config_int(P[1].State_s, "V2_FrameTime_24", 6) - 1; }
            if (P[1].TotalFrames >= 25) { P1_FrameTime_25 = get_config_int(P[1].State_s, "V2_FrameTime_25", 6) - 1; }
            if (P[1].TotalFrames >= 26) { P1_FrameTime_26 = get_config_int(P[1].State_s, "V2_FrameTime_26", 6) - 1; }
            if (P[1].TotalFrames >= 27) { P1_FrameTime_27 = get_config_int(P[1].State_s, "V2_FrameTime_27", 6) - 1; }
            if (P[1].TotalFrames >= 28) { P1_FrameTime_28 = get_config_int(P[1].State_s, "V2_FrameTime_28", 6) - 1; }
            if (P[1].TotalFrames >= 29) { P1_FrameTime_29 = get_config_int(P[1].State_s, "V2_FrameTime_29", 6) - 1; }
            P1_FrameTime = P1_FrameTime_00;
        }
        if (ForcaDoGolpeP1 == 3) {
            if (P[1].TotalFrames >= 0) { P1_FrameTime_00 = get_config_int(P[1].State_s, "V3_FrameTime_00", 6) - 1; }
            if (P[1].TotalFrames >= 1) { P1_FrameTime_01 = get_config_int(P[1].State_s, "V3_FrameTime_01", 6) - 1; }
            if (P[1].TotalFrames >= 2) { P1_FrameTime_02 = get_config_int(P[1].State_s, "V3_FrameTime_02", 6) - 1; }
            if (P[1].TotalFrames >= 3) { P1_FrameTime_03 = get_config_int(P[1].State_s, "V3_FrameTime_03", 6) - 1; }
            if (P[1].TotalFrames >= 4) { P1_FrameTime_04 = get_config_int(P[1].State_s, "V3_FrameTime_04", 6) - 1; }
            if (P[1].TotalFrames >= 5) { P1_FrameTime_05 = get_config_int(P[1].State_s, "V3_FrameTime_05", 6) - 1; }
            if (P[1].TotalFrames >= 6) { P1_FrameTime_06 = get_config_int(P[1].State_s, "V3_FrameTime_06", 6) - 1; }
            if (P[1].TotalFrames >= 7) { P1_FrameTime_07 = get_config_int(P[1].State_s, "V3_FrameTime_07", 6) - 1; }
            if (P[1].TotalFrames >= 8) { P1_FrameTime_08 = get_config_int(P[1].State_s, "V3_FrameTime_08", 6) - 1; }
            if (P[1].TotalFrames >= 9) { P1_FrameTime_09 = get_config_int(P[1].State_s, "V3_FrameTime_09", 6) - 1; }
            if (P[1].TotalFrames >= 10) { P1_FrameTime_10 = get_config_int(P[1].State_s, "V3_FrameTime_10", 6) - 1; }
            if (P[1].TotalFrames >= 11) { P1_FrameTime_11 = get_config_int(P[1].State_s, "V3_FrameTime_11", 6) - 1; }
            if (P[1].TotalFrames >= 12) { P1_FrameTime_12 = get_config_int(P[1].State_s, "V3_FrameTime_12", 6) - 1; }
            if (P[1].TotalFrames >= 13) { P1_FrameTime_13 = get_config_int(P[1].State_s, "V3_FrameTime_13", 6) - 1; }
            if (P[1].TotalFrames >= 14) { P1_FrameTime_14 = get_config_int(P[1].State_s, "V3_FrameTime_14", 6) - 1; }
            if (P[1].TotalFrames >= 15) { P1_FrameTime_15 = get_config_int(P[1].State_s, "V3_FrameTime_15", 6) - 1; }
            if (P[1].TotalFrames >= 16) { P1_FrameTime_16 = get_config_int(P[1].State_s, "V3_FrameTime_16", 6) - 1; }
            if (P[1].TotalFrames >= 17) { P1_FrameTime_17 = get_config_int(P[1].State_s, "V3_FrameTime_17", 6) - 1; }
            if (P[1].TotalFrames >= 18) { P1_FrameTime_18 = get_config_int(P[1].State_s, "V3_FrameTime_18", 6) - 1; }
            if (P[1].TotalFrames >= 19) { P1_FrameTime_19 = get_config_int(P[1].State_s, "V3_FrameTime_19", 6) - 1; }
            if (P[1].TotalFrames >= 20) { P1_FrameTime_20 = get_config_int(P[1].State_s, "V3_FrameTime_20", 6) - 1; }
            if (P[1].TotalFrames >= 21) { P1_FrameTime_21 = get_config_int(P[1].State_s, "V3_FrameTime_21", 6) - 1; }
            if (P[1].TotalFrames >= 22) { P1_FrameTime_22 = get_config_int(P[1].State_s, "V3_FrameTime_22", 6) - 1; }
            if (P[1].TotalFrames >= 23) { P1_FrameTime_23 = get_config_int(P[1].State_s, "V3_FrameTime_23", 6) - 1; }
            if (P[1].TotalFrames >= 24) { P1_FrameTime_24 = get_config_int(P[1].State_s, "V3_FrameTime_24", 6) - 1; }
            if (P[1].TotalFrames >= 25) { P1_FrameTime_25 = get_config_int(P[1].State_s, "V3_FrameTime_25", 6) - 1; }
            if (P[1].TotalFrames >= 26) { P1_FrameTime_26 = get_config_int(P[1].State_s, "V3_FrameTime_26", 6) - 1; }
            if (P[1].TotalFrames >= 27) { P1_FrameTime_27 = get_config_int(P[1].State_s, "V3_FrameTime_27", 6) - 1; }
            if (P[1].TotalFrames >= 28) { P1_FrameTime_28 = get_config_int(P[1].State_s, "V3_FrameTime_28", 6) - 1; }
            if (P[1].TotalFrames >= 29) { P1_FrameTime_29 = get_config_int(P[1].State_s, "V3_FrameTime_29", 6) - 1; }
            P1_FrameTime = P1_FrameTime_00;
        }
    }

    if (ind == 2) {
        if (ForcaDoGolpeP2 == 1) {
            if (P[2].TotalFrames >= 0) { P2_FrameTime_00 = get_config_int(P[2].State_s, "V1_FrameTime_00", 6) - 1; }
            if (P[2].TotalFrames >= 1) { P2_FrameTime_01 = get_config_int(P[2].State_s, "V1_FrameTime_01", 6) - 1; }
            if (P[2].TotalFrames >= 2) { P2_FrameTime_02 = get_config_int(P[2].State_s, "V1_FrameTime_02", 6) - 1; }
            if (P[2].TotalFrames >= 3) { P2_FrameTime_03 = get_config_int(P[2].State_s, "V1_FrameTime_03", 6) - 1; }
            if (P[2].TotalFrames >= 4) { P2_FrameTime_04 = get_config_int(P[2].State_s, "V1_FrameTime_04", 6) - 1; }
            if (P[2].TotalFrames >= 5) { P2_FrameTime_05 = get_config_int(P[2].State_s, "V1_FrameTime_05", 6) - 1; }
            if (P[2].TotalFrames >= 6) { P2_FrameTime_06 = get_config_int(P[2].State_s, "V1_FrameTime_06", 6) - 1; }
            if (P[2].TotalFrames >= 7) { P2_FrameTime_07 = get_config_int(P[2].State_s, "V1_FrameTime_07", 6) - 1; }
            if (P[2].TotalFrames >= 8) { P2_FrameTime_08 = get_config_int(P[2].State_s, "V1_FrameTime_08", 6) - 1; }
            if (P[2].TotalFrames >= 9) { P2_FrameTime_09 = get_config_int(P[2].State_s, "V1_FrameTime_09", 6) - 1; }
            if (P[2].TotalFrames >= 10) { P2_FrameTime_10 = get_config_int(P[2].State_s, "V1_FrameTime_10", 6) - 1; }
            if (P[2].TotalFrames >= 11) { P2_FrameTime_11 = get_config_int(P[2].State_s, "V1_FrameTime_11", 6) - 1; }
            if (P[2].TotalFrames >= 12) { P2_FrameTime_12 = get_config_int(P[2].State_s, "V1_FrameTime_12", 6) - 1; }
            if (P[2].TotalFrames >= 13) { P2_FrameTime_13 = get_config_int(P[2].State_s, "V1_FrameTime_13", 6) - 1; }
            if (P[2].TotalFrames >= 14) { P2_FrameTime_14 = get_config_int(P[2].State_s, "V1_FrameTime_14", 6) - 1; }
            if (P[2].TotalFrames >= 15) { P2_FrameTime_15 = get_config_int(P[2].State_s, "V1_FrameTime_15", 6) - 1; }
            if (P[2].TotalFrames >= 16) { P2_FrameTime_16 = get_config_int(P[2].State_s, "V1_FrameTime_16", 6) - 1; }
            if (P[2].TotalFrames >= 17) { P2_FrameTime_17 = get_config_int(P[2].State_s, "V1_FrameTime_17", 6) - 1; }
            if (P[2].TotalFrames >= 18) { P2_FrameTime_18 = get_config_int(P[2].State_s, "V1_FrameTime_18", 6) - 1; }
            if (P[2].TotalFrames >= 19) { P2_FrameTime_19 = get_config_int(P[2].State_s, "V1_FrameTime_19", 6) - 1; }
            if (P[2].TotalFrames >= 20) { P2_FrameTime_20 = get_config_int(P[2].State_s, "V1_FrameTime_20", 6) - 1; }
            if (P[2].TotalFrames >= 21) { P2_FrameTime_21 = get_config_int(P[2].State_s, "V1_FrameTime_21", 6) - 1; }
            if (P[2].TotalFrames >= 22) { P2_FrameTime_22 = get_config_int(P[2].State_s, "V1_FrameTime_22", 6) - 1; }
            if (P[2].TotalFrames >= 23) { P2_FrameTime_23 = get_config_int(P[2].State_s, "V1_FrameTime_23", 6) - 1; }
            if (P[2].TotalFrames >= 24) { P2_FrameTime_24 = get_config_int(P[2].State_s, "V1_FrameTime_24", 6) - 1; }
            if (P[2].TotalFrames >= 25) { P2_FrameTime_25 = get_config_int(P[2].State_s, "V1_FrameTime_25", 6) - 1; }
            if (P[2].TotalFrames >= 26) { P2_FrameTime_26 = get_config_int(P[2].State_s, "V1_FrameTime_26", 6) - 1; }
            if (P[2].TotalFrames >= 27) { P2_FrameTime_27 = get_config_int(P[2].State_s, "V1_FrameTime_27", 6) - 1; }
            if (P[2].TotalFrames >= 28) { P2_FrameTime_28 = get_config_int(P[2].State_s, "V1_FrameTime_28", 6) - 1; }
            if (P[2].TotalFrames >= 29) { P2_FrameTime_29 = get_config_int(P[2].State_s, "V1_FrameTime_29", 6) - 1; }
            P2_FrameTime = P2_FrameTime_00;
        }
        if (ForcaDoGolpeP2 == 2) {
            if (P[2].TotalFrames >= 0) { P2_FrameTime_00 = get_config_int(P[2].State_s, "V2_FrameTime_00", 6) - 1; }
            if (P[2].TotalFrames >= 1) { P2_FrameTime_01 = get_config_int(P[2].State_s, "V2_FrameTime_01", 6) - 1; }
            if (P[2].TotalFrames >= 2) { P2_FrameTime_02 = get_config_int(P[2].State_s, "V2_FrameTime_02", 6) - 1; }
            if (P[2].TotalFrames >= 3) { P2_FrameTime_03 = get_config_int(P[2].State_s, "V2_FrameTime_03", 6) - 1; }
            if (P[2].TotalFrames >= 4) { P2_FrameTime_04 = get_config_int(P[2].State_s, "V2_FrameTime_04", 6) - 1; }
            if (P[2].TotalFrames >= 5) { P2_FrameTime_05 = get_config_int(P[2].State_s, "V2_FrameTime_05", 6) - 1; }
            if (P[2].TotalFrames >= 6) { P2_FrameTime_06 = get_config_int(P[2].State_s, "V2_FrameTime_06", 6) - 1; }
            if (P[2].TotalFrames >= 7) { P2_FrameTime_07 = get_config_int(P[2].State_s, "V2_FrameTime_07", 6) - 1; }
            if (P[2].TotalFrames >= 8) { P2_FrameTime_08 = get_config_int(P[2].State_s, "V2_FrameTime_08", 6) - 1; }
            if (P[2].TotalFrames >= 9) { P2_FrameTime_09 = get_config_int(P[2].State_s, "V2_FrameTime_09", 6) - 1; }
            if (P[2].TotalFrames >= 10) { P2_FrameTime_10 = get_config_int(P[2].State_s, "V2_FrameTime_10", 6) - 1; }
            if (P[2].TotalFrames >= 11) { P2_FrameTime_11 = get_config_int(P[2].State_s, "V2_FrameTime_11", 6) - 1; }
            if (P[2].TotalFrames >= 12) { P2_FrameTime_12 = get_config_int(P[2].State_s, "V2_FrameTime_12", 6) - 1; }
            if (P[2].TotalFrames >= 13) { P2_FrameTime_13 = get_config_int(P[2].State_s, "V2_FrameTime_13", 6) - 1; }
            if (P[2].TotalFrames >= 14) { P2_FrameTime_14 = get_config_int(P[2].State_s, "V2_FrameTime_14", 6) - 1; }
            if (P[2].TotalFrames >= 15) { P2_FrameTime_15 = get_config_int(P[2].State_s, "V2_FrameTime_15", 6) - 1; }
            if (P[2].TotalFrames >= 16) { P2_FrameTime_16 = get_config_int(P[2].State_s, "V2_FrameTime_16", 6) - 1; }
            if (P[2].TotalFrames >= 17) { P2_FrameTime_17 = get_config_int(P[2].State_s, "V2_FrameTime_17", 6) - 1; }
            if (P[2].TotalFrames >= 18) { P2_FrameTime_18 = get_config_int(P[2].State_s, "V2_FrameTime_18", 6) - 1; }
            if (P[2].TotalFrames >= 19) { P2_FrameTime_19 = get_config_int(P[2].State_s, "V2_FrameTime_19", 6) - 1; }
            if (P[2].TotalFrames >= 20) { P2_FrameTime_20 = get_config_int(P[2].State_s, "V2_FrameTime_20", 6) - 1; }
            if (P[2].TotalFrames >= 21) { P2_FrameTime_21 = get_config_int(P[2].State_s, "V2_FrameTime_21", 6) - 1; }
            if (P[2].TotalFrames >= 22) { P2_FrameTime_22 = get_config_int(P[2].State_s, "V2_FrameTime_22", 6) - 1; }
            if (P[2].TotalFrames >= 23) { P2_FrameTime_23 = get_config_int(P[2].State_s, "V2_FrameTime_23", 6) - 1; }
            if (P[2].TotalFrames >= 24) { P2_FrameTime_24 = get_config_int(P[2].State_s, "V2_FrameTime_24", 6) - 1; }
            if (P[2].TotalFrames >= 25) { P2_FrameTime_25 = get_config_int(P[2].State_s, "V2_FrameTime_25", 6) - 1; }
            if (P[2].TotalFrames >= 26) { P2_FrameTime_26 = get_config_int(P[2].State_s, "V2_FrameTime_26", 6) - 1; }
            if (P[2].TotalFrames >= 27) { P2_FrameTime_27 = get_config_int(P[2].State_s, "V2_FrameTime_27", 6) - 1; }
            if (P[2].TotalFrames >= 28) { P2_FrameTime_28 = get_config_int(P[2].State_s, "V2_FrameTime_28", 6) - 1; }
            if (P[2].TotalFrames >= 29) { P2_FrameTime_29 = get_config_int(P[2].State_s, "V2_FrameTime_29", 6) - 1; }
            P2_FrameTime = P2_FrameTime_00;
        }
        if (ForcaDoGolpeP2 == 3) {
            if (P[2].TotalFrames >= 0) { P2_FrameTime_00 = get_config_int(P[2].State_s, "V3_FrameTime_00", 6) - 1; }
            if (P[2].TotalFrames >= 1) { P2_FrameTime_01 = get_config_int(P[2].State_s, "V3_FrameTime_01", 6) - 1; }
            if (P[2].TotalFrames >= 2) { P2_FrameTime_02 = get_config_int(P[2].State_s, "V3_FrameTime_02", 6) - 1; }
            if (P[2].TotalFrames >= 3) { P2_FrameTime_03 = get_config_int(P[2].State_s, "V3_FrameTime_03", 6) - 1; }
            if (P[2].TotalFrames >= 4) { P2_FrameTime_04 = get_config_int(P[2].State_s, "V3_FrameTime_04", 6) - 1; }
            if (P[2].TotalFrames >= 5) { P2_FrameTime_05 = get_config_int(P[2].State_s, "V3_FrameTime_05", 6) - 1; }
            if (P[2].TotalFrames >= 6) { P2_FrameTime_06 = get_config_int(P[2].State_s, "V3_FrameTime_06", 6) - 1; }
            if (P[2].TotalFrames >= 7) { P2_FrameTime_07 = get_config_int(P[2].State_s, "V3_FrameTime_07", 6) - 1; }
            if (P[2].TotalFrames >= 8) { P2_FrameTime_08 = get_config_int(P[2].State_s, "V3_FrameTime_08", 6) - 1; }
            if (P[2].TotalFrames >= 9) { P2_FrameTime_09 = get_config_int(P[2].State_s, "V3_FrameTime_09", 6) - 1; }
            if (P[2].TotalFrames >= 10) { P2_FrameTime_10 = get_config_int(P[2].State_s, "V3_FrameTime_10", 6) - 1; }
            if (P[2].TotalFrames >= 11) { P2_FrameTime_11 = get_config_int(P[2].State_s, "V3_FrameTime_11", 6) - 1; }
            if (P[2].TotalFrames >= 12) { P2_FrameTime_12 = get_config_int(P[2].State_s, "V3_FrameTime_12", 6) - 1; }
            if (P[2].TotalFrames >= 13) { P2_FrameTime_13 = get_config_int(P[2].State_s, "V3_FrameTime_13", 6) - 1; }
            if (P[2].TotalFrames >= 14) { P2_FrameTime_14 = get_config_int(P[2].State_s, "V3_FrameTime_14", 6) - 1; }
            if (P[2].TotalFrames >= 15) { P2_FrameTime_15 = get_config_int(P[2].State_s, "V3_FrameTime_15", 6) - 1; }
            if (P[2].TotalFrames >= 16) { P2_FrameTime_16 = get_config_int(P[2].State_s, "V3_FrameTime_16", 6) - 1; }
            if (P[2].TotalFrames >= 17) { P2_FrameTime_17 = get_config_int(P[2].State_s, "V3_FrameTime_17", 6) - 1; }
            if (P[2].TotalFrames >= 18) { P2_FrameTime_18 = get_config_int(P[2].State_s, "V3_FrameTime_18", 6) - 1; }
            if (P[2].TotalFrames >= 19) { P2_FrameTime_19 = get_config_int(P[2].State_s, "V3_FrameTime_19", 6) - 1; }
            if (P[2].TotalFrames >= 20) { P2_FrameTime_20 = get_config_int(P[2].State_s, "V3_FrameTime_20", 6) - 1; }
            if (P[2].TotalFrames >= 21) { P2_FrameTime_21 = get_config_int(P[2].State_s, "V3_FrameTime_21", 6) - 1; }
            if (P[2].TotalFrames >= 22) { P2_FrameTime_22 = get_config_int(P[2].State_s, "V3_FrameTime_22", 6) - 1; }
            if (P[2].TotalFrames >= 23) { P2_FrameTime_23 = get_config_int(P[2].State_s, "V3_FrameTime_23", 6) - 1; }
            if (P[2].TotalFrames >= 24) { P2_FrameTime_24 = get_config_int(P[2].State_s, "V3_FrameTime_24", 6) - 1; }
            if (P[2].TotalFrames >= 25) { P2_FrameTime_25 = get_config_int(P[2].State_s, "V3_FrameTime_25", 6) - 1; }
            if (P[2].TotalFrames >= 26) { P2_FrameTime_26 = get_config_int(P[2].State_s, "V3_FrameTime_26", 6) - 1; }
            if (P[2].TotalFrames >= 27) { P2_FrameTime_27 = get_config_int(P[2].State_s, "V3_FrameTime_27", 6) - 1; }
            if (P[2].TotalFrames >= 28) { P2_FrameTime_28 = get_config_int(P[2].State_s, "V3_FrameTime_28", 6) - 1; }
            if (P[2].TotalFrames >= 29) { P2_FrameTime_29 = get_config_int(P[2].State_s, "V3_FrameTime_29", 6) - 1; }
            P2_FrameTime = P2_FrameTime_00;
        }
    }

    //Mov Automatico ao andar
    if ((P[ind].State == 410 || P[ind].State == 420) && P[ind].Hspeed == 0) {
        P[ind].Hspeed = 2;
        if (P[ind].State == 410) { P[ind].Hspeed = -2; }
    }

    //Mov Automatico ao pular
    if ((P[ind].State == 310 || P[ind].State == 300 || P[ind].State == 320) && (
            P[ind].Vspeed == 0 && P[ind].Gravity == 0)) {
        if (P[ind].State == 300) {
            P[ind].Vspeed = -12;
            P[ind].Gravity = 0.6;
        }
        if (P[ind].State == 310) {
            P[ind].Vspeed = -12;
            P[ind].Gravity = 0.6;
            P[ind].Hspeed = -3;
        }
        if (P[ind].State == 320) {
            P[ind].Vspeed = -12;
            P[ind].Gravity = 0.6;
            P[ind].Hspeed = 3;
        }
    }

    //Mov Automatico reversao aerea
    if ((P[ind].State == 507) && (P[ind].Vspeed == 0 && P[ind].Gravity == 0)) {
        P[ind].Vspeed = -8;
        P[ind].Gravity = 0.5;
        P[ind].Hspeed = -4;
    }

    //Mov Automatico ao cair
    if ((P[ind].State == 550) && (P[ind].Vspeed == 0 && P[ind].Gravity == 0)) {
        P[ind].Vspeed = -8;
        P[ind].Gravity = 0.5;
        P[ind].Hspeed = -1;
    }

    //Mov Automatico ao cair2
    if ((P[ind].State == 551) && (P[ind].Vspeed == 0 && P[ind].Gravity == 0)) {
        P[ind].Vspeed = -1;
        P[ind].Gravity = 0.3;
        P[ind].Hspeed = -1;
    }

    //Mov Automatico ao cair por KO
    if ((P[ind].State == 570)) {
        P[ind].Vspeed = -6;
        P[ind].Gravity = 0.3;
        P[ind].Hspeed = -2;
    }

    //Mov Automatico ao cair2 por KO
    if ((P[ind].State == 571)) {
        P[ind].Vspeed = -1;
        P[ind].Gravity = 0.1;
        P[ind].Hspeed = -1;
    }

    //inverte a velocidade hotizontal se estiver do lado direto da tela
    if (P[ind].Lado == -1) {
        P[ind].Hspeed = P[ind].Hspeed * -1;
    }

    //Atribui atributos do pulo em golpes aereos
    if (P[ind].State == 301 || P[ind].State == 302 || P[ind].State == 303
        || P[ind].State == 304 || P[ind].State == 305 || P[ind].State == 306
        || P[ind].State == 311 || P[ind].State == 312 || P[ind].State == 313
        || P[ind].State == 314 || P[ind].State == 315 || P[ind].State == 316
        || P[ind].State == 321 || P[ind].State == 322 || P[ind].State == 323
        || P[ind].State == 324 || P[ind].State == 325 || P[ind].State == 326) {
        P[ind].Hspeed = P[ind].Hspeed_temp;
        P[ind].Vspeed = P[ind].Vspeed_temp;
        P[ind].Gravity = P[ind].Gravity_temp;
    }

    //}

    //special
    if (P[ind].State >= 700) {
        if (ind == 1) {
            sprintf(P1_Caminho, "data/chars/%s/special.ini", P[ind].Name);
            set_config_file(P1_Caminho);
        }
        if (ind == 2) {
            sprintf(P2_Caminho, "data/chars/%s/special.ini", P[ind].Name);
            set_config_file(P2_Caminho);
        }
        //P[ind].XAlign        = get_config_int   (P[ind].State_s, "XAlign" , P[ind].Largura/2 ); //P[ind].Largura_100
        //P[ind].YAlign        = get_config_int   (P[ind].State_s, "YAlign"      , P[ind].Altura );
        P[ind].Vspeed = get_config_float(P[ind].State_s, "Vspeed", 0);
        P[ind].Hspeed = get_config_float(P[ind].State_s, "Hspeed", 0);
        P[ind].Gravity = get_config_float(P[ind].State_s, "Gravity", 0);
        P[ind].Friction = get_config_float(P[ind].State_s, "Friction", 0);
        P[ind].Energy += get_config_int(P[ind].State_s, "Energy", 0);
        P[ind].Special += get_config_int(P[ind].State_s, "Special", 0);
        P[ind].EnergyChange = get_config_int(P[ind].State_s, "EnergyChange", 0);
        P[ind].SpecialChange = get_config_int(P[ind].State_s, "SpecialChange", 0);
        P[ind].Visible = get_config_int(P[ind].State_s, "Visible", 1);
        P[ind].RoomLimit = get_config_int(P[ind].State_s, "RoomLimit", 1);
        strcpy(P[ind].HitType, (char *)get_config_string(P[ind].State_s, "HitType","Normal"));
        strcpy(P[ind].HitStack, (char *)get_config_string(P[ind].State_s, "HitStack","Multi"));
        P[ind].HitPause = get_config_int(P[ind].State_s, "HitPause", 0);
        P[ind].ChangeState = get_config_int(P[ind].State_s, "ChangeState", 0);
        P[ind].Freeze = get_config_int(P[ind].State_s, "Freeze", 0);
        P[ind].Color = get_config_int(P[ind].State_s, "Color", -1);
        P[ind].TotalFrames = get_config_int(P[ind].State_s, "TotalFrames", QtdeFrames);
        if (ind == 1) {
            if (ForcaDoGolpeP1 == 1) { P[1].ChangeDamage = get_config_int(P[1].State_s, "V1_Damage", 0); }
            if (ForcaDoGolpeP1 == 2) { P[1].ChangeDamage = get_config_int(P[1].State_s, "V2_Damage", 0); }
            if (ForcaDoGolpeP1 == 3) { P[1].ChangeDamage = get_config_int(P[1].State_s, "V3_Damage", 0); }
        }
        if (ind == 2) {
            if (ForcaDoGolpeP2 == 1) { P[2].ChangeDamage = get_config_int(P[2].State_s, "V1_Damage", 0); }
            if (ForcaDoGolpeP2 == 2) { P[2].ChangeDamage = get_config_int(P[2].State_s, "V2_Damage", 0); }
            if (ForcaDoGolpeP2 == 3) { P[2].ChangeDamage = get_config_int(P[2].State_s, "V3_Damage", 0); }
        }
    }

    /*
        //debug - caso especial, char vazio
        if (strcmp (P[ind].Name_Display,"-")==0){
        allegro_message("Char Empty");
        }
    */
}

///////////////////////////////////////////////////////////////////////////////
// DESENHA HIT e COLISION BOXES -----------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// Draw_CHBoxes_P1(), Draw_CHBoxes_P2(), Draw_CHBoxes_ED(), Checar_Colisao(), and Aplicar_HIT() moved to hamoopi_collision.c

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CRIA NOVA FIREBALL ---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void New_Fireball(int Player) {
    char P1_Caminho[99];
    char P2_Caminho[99];
    char P1_Caminho_sp[99];
    char P2_Caminho_sp[99];

    if (P[Player].State == 700 && P[Player].TotalDeFramesMov[701] > -1 && P[Player].QtdeMagias == 0) {
        if (Player == 1) {
            sprintf(P1_Caminho, "data/chars/%s/char.ini", P[Player].Name);
            set_config_file(P1_Caminho);
        }
        if (Player == 2) {
            sprintf(P2_Caminho, "data/chars/%s/char.ini", P[Player].Name);
            set_config_file(P2_Caminho);
        }

        P[Player].QtdeMagias++;
        Fireball[Player].Ativa = 1;
        Fireball[Player].Direcao = P[Player].Lado;
        Fireball[Player].State = 701;
        sprintf(Fireball[Player].State_s, "%i", Fireball[Player].State);
        Fireball[Player].XAlign = get_config_int(Fireball[Player].State_s, "XAlign", 0);
        Fireball[Player].YAlign = get_config_int(Fireball[Player].State_s, "YAlign", 0);
        Fireball[Player].TotalFrames = P[Player].TotalDeFramesMov[701];
        //Fireball[Player].StartFrame=time;
        if (Player == 1) {
            //tem q verificar a força de variacao tb (DMG), vou implementar depois.
            //V1 = fraco, V2 = medio, V3 = forte
            if (ForcaDoGolpeP1 == 1) {
                if (Fireball[Player].TotalFrames >= 0) {
                    P1_Fireball_FrameTime_00 = get_config_int("701", "V1_FrameTime_00", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 1) {
                    P1_Fireball_FrameTime_01 = get_config_int("701", "V1_FrameTime_01", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 2) {
                    P1_Fireball_FrameTime_02 = get_config_int("701", "V1_FrameTime_02", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 3) {
                    P1_Fireball_FrameTime_03 = get_config_int("701", "V1_FrameTime_03", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 4) {
                    P1_Fireball_FrameTime_04 = get_config_int("701", "V1_FrameTime_04", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 5) {
                    P1_Fireball_FrameTime_05 = get_config_int("701", "V1_FrameTime_05", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 6) {
                    P1_Fireball_FrameTime_06 = get_config_int("701", "V1_FrameTime_06", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 7) {
                    P1_Fireball_FrameTime_07 = get_config_int("701", "V1_FrameTime_07", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 8) {
                    P1_Fireball_FrameTime_08 = get_config_int("701", "V1_FrameTime_08", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 9) {
                    P1_Fireball_FrameTime_09 = get_config_int("701", "V1_FrameTime_09", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 10) {
                    P1_Fireball_FrameTime_10 = get_config_int("701", "V1_FrameTime_10", 6) - 1;
                }
            }
            if (ForcaDoGolpeP1 == 2) {
                if (Fireball[Player].TotalFrames >= 0) {
                    P1_Fireball_FrameTime_00 = get_config_int("701", "V2_FrameTime_00", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 1) {
                    P1_Fireball_FrameTime_01 = get_config_int("701", "V2_FrameTime_01", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 2) {
                    P1_Fireball_FrameTime_02 = get_config_int("701", "V2_FrameTime_02", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 3) {
                    P1_Fireball_FrameTime_03 = get_config_int("701", "V2_FrameTime_03", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 4) {
                    P1_Fireball_FrameTime_04 = get_config_int("701", "V2_FrameTime_04", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 5) {
                    P1_Fireball_FrameTime_05 = get_config_int("701", "V2_FrameTime_05", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 6) {
                    P1_Fireball_FrameTime_06 = get_config_int("701", "V2_FrameTime_06", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 7) {
                    P1_Fireball_FrameTime_07 = get_config_int("701", "V2_FrameTime_07", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 8) {
                    P1_Fireball_FrameTime_08 = get_config_int("701", "V2_FrameTime_08", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 9) {
                    P1_Fireball_FrameTime_09 = get_config_int("701", "V2_FrameTime_09", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 10) {
                    P1_Fireball_FrameTime_10 = get_config_int("701", "V2_FrameTime_10", 6) - 1;
                }
            }
            if (ForcaDoGolpeP1 == 3) {
                if (Fireball[Player].TotalFrames >= 0) {
                    P1_Fireball_FrameTime_00 = get_config_int("701", "V3_FrameTime_00", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 1) {
                    P1_Fireball_FrameTime_01 = get_config_int("701", "V3_FrameTime_01", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 2) {
                    P1_Fireball_FrameTime_02 = get_config_int("701", "V3_FrameTime_02", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 3) {
                    P1_Fireball_FrameTime_03 = get_config_int("701", "V3_FrameTime_03", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 4) {
                    P1_Fireball_FrameTime_04 = get_config_int("701", "V3_FrameTime_04", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 5) {
                    P1_Fireball_FrameTime_05 = get_config_int("701", "V3_FrameTime_05", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 6) {
                    P1_Fireball_FrameTime_06 = get_config_int("701", "V3_FrameTime_06", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 7) {
                    P1_Fireball_FrameTime_07 = get_config_int("701", "V3_FrameTime_07", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 8) {
                    P1_Fireball_FrameTime_08 = get_config_int("701", "V3_FrameTime_08", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 9) {
                    P1_Fireball_FrameTime_09 = get_config_int("701", "V3_FrameTime_09", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 10) {
                    P1_Fireball_FrameTime_10 = get_config_int("701", "V3_FrameTime_10", 6) - 1;
                }
            }
            P1_Fireball_FrameTime = P1_Fireball_FrameTime_00;

            sprintf(P1_Caminho_sp, "data/chars/%s/special.ini", P[Player].Name);
            set_config_file(P1_Caminho_sp);

            int LocalPosX = get_config_int(Fireball[Player].State_s, "LocalPosX", 0);
            int LocalPosY = get_config_int(Fireball[Player].State_s, "LocalPosY", 0);
            Fireball[Player].x = P[Player].x + (LocalPosX * Fireball[Player].Direcao);
            Fireball[Player].y = P[Player].y + LocalPosY;
            Fireball[Player].HSpeed = get_config_int("701", "HSpeed", 4) - 1;
            Fireball[Player].HSpeed += 1;
            Fireball[Player].VSpeed = get_config_int("701", "VSpeed", -1) - 1;
            Fireball[Player].VSpeed += 1;
            Fireball[Player].ThrowFireball = get_config_int(P[Player].State_s, "ThrowFireball", 1);

            sprintf(P1_Caminho_sp, "data/chars/%s/chbox.ini", P[Player].Name);
            set_config_file(P1_Caminho_sp);
            P1_Fireball_HurtBox01x1 = get_config_int("701_00", "HurtBox01x1", -15);
            P1_Fireball_HurtBox01y1 = get_config_int("701_00", "HurtBox01y1", -15);
            P1_Fireball_HurtBox01x2 = get_config_int("701_00", "HurtBox01x2", 15);
            P1_Fireball_HurtBox01y2 = get_config_int("701_00", "HurtBox01y2", 15);
            P1_Fireball_HitBox01x1 = get_config_int("701_00", "HitBox01x1", -10);
            P1_Fireball_HitBox01y1 = get_config_int("701_00", "HitBox01y1", -10);
            P1_Fireball_HitBox01x2 = get_config_int("701_00", "HitBox01x2", -10);
            P1_Fireball_HitBox01y2 = get_config_int("701_00", "HitBox01y2", -10);
        }

        if (Player == 2) {
            //tem q verificar a força de variacao tb (DMG), vou implementar depois.
            //V1 = fraco, V2 = medio, V3 = forte
            if (ForcaDoGolpeP2 == 1) {
                if (Fireball[Player].TotalFrames >= 0) {
                    P2_Fireball_FrameTime_00 = get_config_int("701", "V1_FrameTime_00", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 1) {
                    P2_Fireball_FrameTime_01 = get_config_int("701", "V1_FrameTime_01", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 2) {
                    P2_Fireball_FrameTime_02 = get_config_int("701", "V1_FrameTime_02", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 3) {
                    P2_Fireball_FrameTime_03 = get_config_int("701", "V1_FrameTime_03", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 4) {
                    P2_Fireball_FrameTime_04 = get_config_int("701", "V1_FrameTime_04", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 5) {
                    P2_Fireball_FrameTime_05 = get_config_int("701", "V1_FrameTime_05", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 6) {
                    P2_Fireball_FrameTime_06 = get_config_int("701", "V1_FrameTime_06", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 7) {
                    P2_Fireball_FrameTime_07 = get_config_int("701", "V1_FrameTime_07", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 8) {
                    P2_Fireball_FrameTime_08 = get_config_int("701", "V1_FrameTime_08", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 9) {
                    P2_Fireball_FrameTime_09 = get_config_int("701", "V1_FrameTime_09", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 10) {
                    P2_Fireball_FrameTime_10 = get_config_int("701", "V1_FrameTime_10", 6) - 1;
                }
            }
            if (ForcaDoGolpeP2 == 2) {
                if (Fireball[Player].TotalFrames >= 0) {
                    P2_Fireball_FrameTime_00 = get_config_int("701", "V2_FrameTime_00", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 1) {
                    P2_Fireball_FrameTime_01 = get_config_int("701", "V2_FrameTime_01", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 2) {
                    P2_Fireball_FrameTime_02 = get_config_int("701", "V2_FrameTime_02", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 3) {
                    P2_Fireball_FrameTime_03 = get_config_int("701", "V2_FrameTime_03", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 4) {
                    P2_Fireball_FrameTime_04 = get_config_int("701", "V2_FrameTime_04", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 5) {
                    P2_Fireball_FrameTime_05 = get_config_int("701", "V2_FrameTime_05", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 6) {
                    P2_Fireball_FrameTime_06 = get_config_int("701", "V2_FrameTime_06", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 7) {
                    P2_Fireball_FrameTime_07 = get_config_int("701", "V2_FrameTime_07", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 8) {
                    P2_Fireball_FrameTime_08 = get_config_int("701", "V2_FrameTime_08", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 9) {
                    P2_Fireball_FrameTime_09 = get_config_int("701", "V2_FrameTime_09", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 10) {
                    P2_Fireball_FrameTime_10 = get_config_int("701", "V2_FrameTime_10", 6) - 1;
                }
            }
            if (ForcaDoGolpeP2 == 3) {
                if (Fireball[Player].TotalFrames >= 0) {
                    P2_Fireball_FrameTime_00 = get_config_int("701", "V3_FrameTime_00", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 1) {
                    P2_Fireball_FrameTime_01 = get_config_int("701", "V3_FrameTime_01", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 2) {
                    P2_Fireball_FrameTime_02 = get_config_int("701", "V3_FrameTime_02", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 3) {
                    P2_Fireball_FrameTime_03 = get_config_int("701", "V3_FrameTime_03", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 4) {
                    P2_Fireball_FrameTime_04 = get_config_int("701", "V3_FrameTime_04", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 5) {
                    P2_Fireball_FrameTime_05 = get_config_int("701", "V3_FrameTime_05", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 6) {
                    P2_Fireball_FrameTime_06 = get_config_int("701", "V3_FrameTime_06", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 7) {
                    P2_Fireball_FrameTime_07 = get_config_int("701", "V3_FrameTime_07", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 8) {
                    P2_Fireball_FrameTime_08 = get_config_int("701", "V3_FrameTime_08", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 9) {
                    P2_Fireball_FrameTime_09 = get_config_int("701", "V3_FrameTime_09", 6) - 1;
                }
                if (Fireball[Player].TotalFrames >= 10) {
                    P2_Fireball_FrameTime_10 = get_config_int("701", "V3_FrameTime_10", 6) - 1;
                }
            }
            P2_Fireball_FrameTime = P2_Fireball_FrameTime_00;

            sprintf(P2_Caminho_sp, "data/chars/%s/special.ini", P[Player].Name);
            set_config_file(P2_Caminho_sp);

            int LocalPosX = get_config_int(Fireball[Player].State_s, "LocalPosX", 0);
            int LocalPosY = get_config_int(Fireball[Player].State_s, "LocalPosY", 0);
            Fireball[Player].x = P[Player].x + (LocalPosX * Fireball[Player].Direcao);
            Fireball[Player].y = P[Player].y + LocalPosY;
            Fireball[Player].HSpeed = get_config_int("701", "HSpeed", 4) - 1;
            Fireball[Player].HSpeed += 1;
            Fireball[Player].VSpeed = get_config_int("701", "VSpeed", -1) - 1;
            Fireball[Player].VSpeed += 1;
            Fireball[Player].ThrowFireball = get_config_int(P[Player].State_s, "ThrowFireball", 1);

            sprintf(P2_Caminho_sp, "data/chars/%s/chbox.ini", P[Player].Name);
            set_config_file(P2_Caminho_sp);
            P2_Fireball_HurtBox01x1 = get_config_int("701_00", "HurtBox01x1", -15);
            P2_Fireball_HurtBox01y1 = get_config_int("701_00", "HurtBox01y1", -15);
            P2_Fireball_HurtBox01x2 = get_config_int("701_00", "HurtBox01x2", 15);
            P2_Fireball_HurtBox01y2 = get_config_int("701_00", "HurtBox01y2", 15);
            P2_Fireball_HitBox01x1 = get_config_int("701_00", "HitBox01x1", -10);
            P2_Fireball_HitBox01y1 = get_config_int("701_00", "HitBox01y1", -10);
            P2_Fireball_HitBox01x2 = get_config_int("701_00", "HitBox01x2", -10);
            P2_Fireball_HitBox01y2 = get_config_int("701_00", "HitBox01y2", -10);
        }
    }
    if (P[Player].State != 700) {
        Fireball[Player].Ativa = 0;
        Fireball[Player].x = -9999;
        Fireball[Player].y = -9999;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CRIA NOVO HITSPARK ---------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void New_HitBox(int Qtde_HitBoxes) {
    //if ( colisaoxP2==1 ){
    Qtde_HitBox++;

    //SONS DE HIT
    if (colisaoxP1 == 1) {
        if (ForcaDoGolpeP2 == 1) { PlaySoundHitLvl1 = 1; }
        if (ForcaDoGolpeP2 == 2) { PlaySoundHitLvl2 = 1; }
        if (ForcaDoGolpeP2 == 3) { PlaySoundHitLvl3 = 1; }
    }
    if (colisaoxP2 == 1) {
        if (ForcaDoGolpeP1 == 1) { PlaySoundHitLvl1 = 1; }
        if (ForcaDoGolpeP1 == 2) { PlaySoundHitLvl2 = 1; }
        if (ForcaDoGolpeP1 == 3) { PlaySoundHitLvl3 = 1; }
    }

    if (colisaoxP2 == 1) {
        HitSpark[Qtde_HitBoxes].x = P1_Hit_x;
        HitSpark[Qtde_HitBoxes].y = P1_Hit_y;
        if (ForcaDoGolpeP1 == 1) {
            HitSpark[Qtde_HitBoxes].Type = 991;
            HitSpark[Qtde_HitBox].XAlign = -30;
        }
        if (ForcaDoGolpeP1 == 2) {
            HitSpark[Qtde_HitBoxes].Type = 992;
            HitSpark[Qtde_HitBox].XAlign = -50;
        }
        if (ForcaDoGolpeP1 == 3) {
            HitSpark[Qtde_HitBoxes].Type = 993;
            HitSpark[Qtde_HitBox].XAlign = -65;
        }
    }
    if (colisaoxP1 == 1) {
        HitSpark[Qtde_HitBoxes].x = P2_Hit_x;
        HitSpark[Qtde_HitBoxes].y = P2_Hit_y;
        if (ForcaDoGolpeP2 == 1) {
            HitSpark[Qtde_HitBoxes].Type = 991;
            HitSpark[Qtde_HitBox].XAlign = -30;
        }
        if (ForcaDoGolpeP2 == 2) {
            HitSpark[Qtde_HitBoxes].Type = 992;
            HitSpark[Qtde_HitBox].XAlign = -50;
        }
        if (ForcaDoGolpeP2 == 3) {
            HitSpark[Qtde_HitBoxes].Type = 993;
            HitSpark[Qtde_HitBox].XAlign = -65;
        }
    }

    HitSpark[Qtde_HitBoxes].StartFrame = frame_count;
    HitSpark[Qtde_HitBoxes].FrameTime = 1;
    HitSpark[Qtde_HitBoxes].TotalFrames = 5;
    HitSpark[Qtde_HitBoxes].IndexAnim = 0;
    HitSpark[Qtde_HitBoxes].YAlign = HitSpark[Qtde_HitBoxes].XAlign;
    //}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ADITIVO TABLE ATLAS --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AddTableAtlas(int PlayerInd, int State, int AnimIndex, int TotImg) {
    int line = TotImg;
    int ind = PlayerInd;
    P[ind].State = State;
    P[ind].IndexAnim = AnimIndex;

    //char.ini
    char P1_Caminho[99];
    char P2_Caminho[99];
    if (ind == 1) {
        sprintf(P1_Caminho, "data/chars/%s/char.ini", P[ind].Name);
        set_config_file(P1_Caminho);
    }
    if (ind == 2) {
        sprintf(P2_Caminho, "data/chars/%s/char.ini", P[ind].Name);
        set_config_file(P2_Caminho);
    }

    //strcpy(P[ind].Name_Display, (char *)get_config_string("Info", "Name", "-"));

    //-----------------------------------------------------------------------------------------------------------------

    if (P[ind].IndexAnim == 0) {
        snprintf(P[ind].State_s, sizeof(P[ind].State_s), "%d", P[ind].State); //State String

        if (P[ind].State < 700) {
            P[ind].TableAtlas[line][4] = get_config_int(P[ind].State_s, "XAlign", P[ind].Largura/2);
            P[ind].TableAtlas[line][5] = get_config_int(P[ind].State_s, "YAlign", P[ind].Altura);
            P[ind].TableAtlas[line][6] = get_config_int(P[ind].State_s, "X", -5555);
            P[ind].TableAtlas[line][7] = get_config_int(P[ind].State_s, "Y", -5555);
            P[ind].TableAtlas[line][8] = get_config_float(P[ind].State_s, "VSpeed", -5555);
            P[ind].TableAtlas[line][9] = get_config_float(P[ind].State_s, "HSpeed", -5555);
            P[ind].TableAtlas[line][10] = get_config_float(P[ind].State_s, "Gravity", -5555);
            P[ind].TableAtlas[line][11] = get_config_float(P[ind].State_s, "Friction", -5555);
            P[ind].TableAtlas[line][12] = get_config_int(P[ind].State_s, "EnergyChange", -5555);
            P[ind].TableAtlas[line][13] = get_config_int(P[ind].State_s, "SpecialChange", -5555);
            P[ind].TableAtlas[line][14] = get_config_int(P[ind].State_s, "Visible", -5555);
            P[ind].TableAtlas[line][15] = get_config_int(P[ind].State_s, "RoomLimit", -5555);
            strcpy(P[ind].HitType, (char *)get_config_string(P[ind].State_s, "HitType","Normal"));
            //pega o hittype em char
            //if (strcmp (P[ind].HitType,"")==0){ P[ind].TableAtlas[line][16] = -5555; }
            if (strcmp(P[ind].HitType, "Normal") == 0) { P[ind].TableAtlas[line][16] = 1; }
            if (strcmp(P[ind].HitType, "Fall") == 0) { P[ind].TableAtlas[line][16] = 2; }
            P[ind].TableAtlas[line][17] = get_config_int(P[ind].State_s, "ChangeState", -5555);
            P[ind].TableAtlas[line][18] = get_config_int(P[ind].State_s, "Freeze", -5555);
            P[ind].TableAtlas[line][19] = get_config_int(P[ind].State_s, "Color", -5555);
            strcpy(P[ind].HitStack, (char *)get_config_string(P[ind].State_s, "HitStack","Multi"));
            //pega o hitstack em char
            //if (strcmp (P[ind].HitStack,"")==0){ P[ind].TableAtlas[line][20] = -5555; }
            if (strcmp(P[ind].HitStack, "Single") == 0) { P[ind].TableAtlas[line][20] = 1; }
            if (strcmp(P[ind].HitStack, "Multi") == 0) { P[ind].TableAtlas[line][20] = 2; }
        }

        if (P[ind].State >= 700) {
            //carrega X e do char.ini
            P[ind].TableAtlas[line][4] = get_config_int(P[ind].State_s, "XAlign", P[ind].Largura/2);
            P[ind].TableAtlas[line][5] = get_config_int(P[ind].State_s, "YAlign", P[ind].Altura);

            //special.ini
            if (ind == 1) {
                sprintf(P1_Caminho, "data/chars/%s/special.ini", P[ind].Name);
                set_config_file(P1_Caminho);
            }
            if (ind == 2) {
                sprintf(P2_Caminho, "data/chars/%s/special.ini", P[ind].Name);
                set_config_file(P2_Caminho);
            }

            P[ind].TableAtlas[line][6] = get_config_int(P[ind].State_s, "X", -5555);
            P[ind].TableAtlas[line][7] = get_config_int(P[ind].State_s, "Y", -5555);
            P[ind].TableAtlas[line][8] = get_config_float(P[ind].State_s, "VSpeed", -5555);
            P[ind].TableAtlas[line][9] = get_config_float(P[ind].State_s, "HSpeed", -5555);
            P[ind].TableAtlas[line][10] = get_config_float(P[ind].State_s, "Gravity", -5555);
            P[ind].TableAtlas[line][11] = get_config_float(P[ind].State_s, "Friction", -5555);
            P[ind].TableAtlas[line][12] = get_config_int(P[ind].State_s, "EnergyChange", -5555);
            P[ind].TableAtlas[line][13] = get_config_int(P[ind].State_s, "SpecialChange", -5555);
            P[ind].TableAtlas[line][14] = get_config_int(P[ind].State_s, "Visible", -5555);
            P[ind].TableAtlas[line][15] = get_config_int(P[ind].State_s, "RoomLimit", -5555);
            strcpy(P[ind].HitType, (char *)get_config_string(P[ind].State_s, "HitType","Normal"));
            //pega o hittype em char
            //if (strcmp (P[ind].HitType,"")==0){ P[ind].TableAtlas[line][16] = -5555; }
            if (strcmp(P[ind].HitType, "Normal") == 0) { P[ind].TableAtlas[line][16] = 1; }
            if (strcmp(P[ind].HitType, "Fall") == 0) { P[ind].TableAtlas[line][16] = 2; }
            P[ind].TableAtlas[line][17] = get_config_int(P[ind].State_s, "ChangeState", -5555);
            P[ind].TableAtlas[line][18] = get_config_int(P[ind].State_s, "Freeze", -5555);
            P[ind].TableAtlas[line][19] = get_config_int(P[ind].State_s, "Color", -5555);
            strcpy(P[ind].HitStack, (char *)get_config_string(P[ind].State_s, "HitStack","Multi"));
            //pega o hitstack em char
            //if (strcmp (P[ind].HitStack,"")==0){ P[ind].TableAtlas[line][20] = -5555; }
            if (strcmp(P[ind].HitStack, "Single") == 0) { P[ind].TableAtlas[line][20] = 1; }
            if (strcmp(P[ind].HitStack, "Multi") == 0) { P[ind].TableAtlas[line][20] = 2; }
        }
    } //fim "P[ind].IndexAnim==0"

    //-----------------------------------------------------------------------------------------------------------------

    if (P[ind].IndexAnim > 0) {
        if (P[ind].IndexAnim < 10) { sprintf(P[ind].State_s, "%i_0%i", P[ind].State, P[ind].IndexAnim); } //State String
        if (P[ind].IndexAnim >= 10) { sprintf(P[ind].State_s, "%i_%i", P[ind].State, P[ind].IndexAnim); } //State String

        if (P[ind].State < 700) {
            P[ind].TableAtlas[line][4] = get_config_int(P[ind].State_s, "XAlign", -5555);
            P[ind].TableAtlas[line][5] = get_config_int(P[ind].State_s, "YAlign", -5555);
            P[ind].TableAtlas[line][6] = get_config_int(P[ind].State_s, "X", -5555);
            P[ind].TableAtlas[line][7] = get_config_int(P[ind].State_s, "Y", -5555);
            P[ind].TableAtlas[line][8] = get_config_float(P[ind].State_s, "VSpeed", -5555);
            P[ind].TableAtlas[line][9] = get_config_float(P[ind].State_s, "HSpeed", -5555);
            P[ind].TableAtlas[line][10] = get_config_float(P[ind].State_s, "Gravity", -5555);
            P[ind].TableAtlas[line][11] = get_config_float(P[ind].State_s, "Friction", -5555);
            P[ind].TableAtlas[line][12] = get_config_int(P[ind].State_s, "EnergyChange", -5555);
            P[ind].TableAtlas[line][13] = get_config_int(P[ind].State_s, "SpecialChange", -5555);
            P[ind].TableAtlas[line][14] = get_config_int(P[ind].State_s, "Visible", -5555);
            P[ind].TableAtlas[line][15] = get_config_int(P[ind].State_s, "RoomLimit", -5555);
            strcpy(P[ind].HitType, (char *)get_config_string(P[ind].State_s, "HitType","")); //pega o hittype em char
            if (strcmp(P[ind].HitType, "") == 0) { P[ind].TableAtlas[line][16] = -5555; }
            if (strcmp(P[ind].HitType, "Normal") == 0) { P[ind].TableAtlas[line][16] = 1; }
            if (strcmp(P[ind].HitType, "Fall") == 0) { P[ind].TableAtlas[line][16] = 2; }
            P[ind].TableAtlas[line][17] = get_config_int(P[ind].State_s, "ChangeState", -5555);
            P[ind].TableAtlas[line][18] = get_config_int(P[ind].State_s, "Freeze", -5555);
            P[ind].TableAtlas[line][19] = get_config_int(P[ind].State_s, "Color", -5555);
            strcpy(P[ind].HitStack, (char *)get_config_string(P[ind].State_s, "HitStack","")); //pega o hitstack em char
            if (strcmp(P[ind].HitStack, "") == 0) { P[ind].TableAtlas[line][20] = -5555; }
            if (strcmp(P[ind].HitStack, "Single") == 0) { P[ind].TableAtlas[line][20] = 1; }
            if (strcmp(P[ind].HitStack, "Multi") == 0) { P[ind].TableAtlas[line][20] = 2; }
        }

        if (P[ind].State >= 700) {
            //carrega X e do char.ini
            P[ind].TableAtlas[line][4] = get_config_int(P[ind].State_s, "XAlign", -5555);
            P[ind].TableAtlas[line][5] = get_config_int(P[ind].State_s, "YAlign", -5555);

            //special.ini
            if (ind == 1) {
                sprintf(P1_Caminho, "data/chars/%s/special.ini", P[ind].Name);
                set_config_file(P1_Caminho);
            }
            if (ind == 2) {
                sprintf(P2_Caminho, "data/chars/%s/special.ini", P[ind].Name);
                set_config_file(P2_Caminho);
            }

            P[ind].TableAtlas[line][6] = get_config_int(P[ind].State_s, "X", -5555);
            P[ind].TableAtlas[line][7] = get_config_int(P[ind].State_s, "Y", -5555);
            P[ind].TableAtlas[line][8] = get_config_float(P[ind].State_s, "VSpeed", -5555);
            P[ind].TableAtlas[line][9] = get_config_float(P[ind].State_s, "HSpeed", -5555);
            P[ind].TableAtlas[line][10] = get_config_float(P[ind].State_s, "Gravity", -5555);
            P[ind].TableAtlas[line][11] = get_config_float(P[ind].State_s, "Friction", -5555);
            P[ind].TableAtlas[line][12] = get_config_int(P[ind].State_s, "EnergyChange", -5555);
            P[ind].TableAtlas[line][13] = get_config_int(P[ind].State_s, "SpecialChange", -5555);
            P[ind].TableAtlas[line][14] = get_config_int(P[ind].State_s, "Visible", -5555);
            P[ind].TableAtlas[line][15] = get_config_int(P[ind].State_s, "RoomLimit", -5555);
            strcpy(P[ind].HitType, (char *)get_config_string(P[ind].State_s, "HitType","")); //pega o hittype em char
            if (strcmp(P[ind].HitType, "") == 0) { P[ind].TableAtlas[line][16] = -5555; }
            if (strcmp(P[ind].HitType, "Normal") == 0) { P[ind].TableAtlas[line][16] = 1; }
            if (strcmp(P[ind].HitType, "Fall") == 0) { P[ind].TableAtlas[line][16] = 2; }
            P[ind].TableAtlas[line][17] = get_config_int(P[ind].State_s, "ChangeState", -5555);
            P[ind].TableAtlas[line][18] = get_config_int(P[ind].State_s, "Freeze", -5555);
            P[ind].TableAtlas[line][19] = get_config_int(P[ind].State_s, "Color", -5555);
            strcpy(P[ind].HitStack, (char *)get_config_string(P[ind].State_s, "HitStack","")); //pega o hitstack em char
            if (strcmp(P[ind].HitStack, "") == 0) { P[ind].TableAtlas[line][20] = -5555; }
            if (strcmp(P[ind].HitStack, "Single") == 0) { P[ind].TableAtlas[line][20] = 1; }
            if (strcmp(P[ind].HitStack, "Multi") == 0) { P[ind].TableAtlas[line][20] = 2; }
        }
    } //fim "P[ind].IndexAnim>0"
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EDITOR SAVE CHAR.INI --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
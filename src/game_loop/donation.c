#include "donation.h"

void GameLoop_DonationScreen() {
    if (timermenus == 0) {
        FadeIN = 0;
        FadeOUT = 1;
    }

    IntroTimer++;

    if (timermenus == 15) {
        if (key[KEY_ESC]) { sair = 1; }
        if (key[KEY_ALT] && key[KEY_F4]) { sair = 1; }
        if (P[1].key_START_pressed == 1) {
            timermenus = 0;
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            DonationScreen = 0;
            ApresentacaoMode = 1;
        }
    }

    if (IntroTimer == 300 - 30) {
        FadeIN = 1;
        FadeOUT = 0;
    }
    if (IntroTimer >= 300) {
        timermenus = 0;
        DonationScreen = 0;
        ApresentacaoMode = 1;
    }
    draw_sprite(bufferx, donation, 0, 0);

    rectfill(bufferx, 160, 20, 600, 150, makecol(255,255,255));
    rectfill(bufferx, 100, 370, 600, 460, makecol(255,255,255));

    if (strcmp(IDIOMA, "US") == 0) {
        textprintf_centre_ex(bufferx, font_19, 380, 40 + 15, makecol(000, 000, 000), -1, "Please donate any amount of");
        textprintf_centre_ex(bufferx, font_19, 380, 65 + 15, makecol(000, 000, 000), -1, "   to keep project alive");
        textprintf_centre_ex(bufferx, font_19, 320, 65 + 15, makecol(000, 140, 010), -1,
                             "   BTC                        ");
        textprintf_centre_ex(bufferx, font_19, 320, 400, makecol(000, 000, 000), -1, "Thanks, Hamoopi Team");
    }
    if (strcmp(IDIOMA, "BR") == 0) {
        textprintf_centre_ex(bufferx, font_19, 380, 30 + 10, makecol(000, 000, 000), -1,
                             "Por favor considere fazer uma");
        textprintf_centre_ex(bufferx, font_19, 380, 55 + 10, makecol(000, 000, 000), -1,
                             "doação de qualquer quantia de");
        textprintf_centre_ex(bufferx, font_19, 380, 80 + 10, makecol(000, 000, 000), -1,
                             "   para manter o projeto vivo");
        textprintf_centre_ex(bufferx, font_19, 320, 80 + 10, makecol(000, 140, 010), -1,
                             "   BTC                            ");
        textprintf_centre_ex(bufferx, font_19, 320, 400, makecol(000, 000, 000), -1, "Obrigado, Equipe Hamoopi");
    }

    stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}

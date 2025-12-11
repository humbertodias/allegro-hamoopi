#include "collision.h"

void Draw_CHBoxes_P1() {
    P1_HitBox01x1 = -5555;
    P1_HitBox01y1 = -5555;
    P1_HitBox01x2 = -5555;
    P1_HitBox01y2 = -5555;
    P1_HitBox02x1 = -5555;
    P1_HitBox02y1 = -5555;
    P1_HitBox02x2 = -5555;
    P1_HitBox02y2 = -5555;
    P1_HitBox03x1 = -5555;
    P1_HitBox03y1 = -5555;
    P1_HitBox03x2 = -5555;
    P1_HitBox03y2 = -5555;
    P1_HitBox04x1 = -5555;
    P1_HitBox04y1 = -5555;
    P1_HitBox04x2 = -5555;
    P1_HitBox04y2 = -5555;
    P1_HitBox05x1 = -5555;
    P1_HitBox05y1 = -5555;
    P1_HitBox05x2 = -5555;
    P1_HitBox05y2 = -5555;
    P1_HitBox06x1 = -5555;
    P1_HitBox06y1 = -5555;
    P1_HitBox06x2 = -5555;
    P1_HitBox06y2 = -5555;
    P1_HitBox07x1 = -5555;
    P1_HitBox07y1 = -5555;
    P1_HitBox07x2 = -5555;
    P1_HitBox07y2 = -5555;
    P1_HitBox08x1 = -5555;
    P1_HitBox08y1 = -5555;
    P1_HitBox08x2 = -5555;
    P1_HitBox08y2 = -5555;
    P1_HitBox09x1 = -5555;
    P1_HitBox09y1 = -5555;
    P1_HitBox09x2 = -5555;
    P1_HitBox09y2 = -5555;
    P1_HurtBox01x1 = -5555;
    P1_HurtBox01y1 = -5555;
    P1_HurtBox01x2 = -5555;
    P1_HurtBox01y2 = -5555;
    P1_HurtBox02x1 = -5555;
    P1_HurtBox02y1 = -5555;
    P1_HurtBox02x2 = -5555;
    P1_HurtBox02y2 = -5555;
    P1_HurtBox03x1 = -5555;
    P1_HurtBox03y1 = -5555;
    P1_HurtBox03x2 = -5555;
    P1_HurtBox03y2 = -5555;
    P1_HurtBox04x1 = -5555;
    P1_HurtBox04y1 = -5555;
    P1_HurtBox04x2 = -5555;
    P1_HurtBox04y2 = -5555;
    P1_HurtBox05x1 = -5555;
    P1_HurtBox05y1 = -5555;
    P1_HurtBox05x2 = -5555;
    P1_HurtBox05y2 = -5555;
    P1_HurtBox06x1 = -5555;
    P1_HurtBox06y1 = -5555;
    P1_HurtBox06x2 = -5555;
    P1_HurtBox06y2 = -5555;
    P1_HurtBox07x1 = -5555;
    P1_HurtBox07y1 = -5555;
    P1_HurtBox07x2 = -5555;
    P1_HurtBox07y2 = -5555;
    P1_HurtBox08x1 = -5555;
    P1_HurtBox08y1 = -5555;
    P1_HurtBox08x2 = -5555;
    P1_HurtBox08y2 = -5555;
    P1_HurtBox09x1 = -5555;
    P1_HurtBox09y1 = -5555;
    P1_HurtBox09x2 = -5555;
    P1_HurtBox09y2 = -5555;
    P1_HurtBox_tot = 0;
    P1_HitBox_tot = 0;

    sprintf(P[1].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[1].Name);
    if (P[1].IndexAnim < 10) { sprintf(P[1].State_chs, "%i_0%i", P[1].State, P[1].IndexAnim); }
    if (P[1].IndexAnim >= 10) { sprintf(P[1].State_chs, "%i_%i", P[1].State, P[1].IndexAnim); }

    set_config_file(P[1].Caminho_CHBOX);
    P1_HitBox01x1 = get_config_int(P[1].State_chs, "HitBox01x1", -5555);
    if (P1_HitBox01x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox01y1 = get_config_int(P[1].State_chs, "HitBox01y1", -5555);
    P1_HitBox01x2 = get_config_int(P[1].State_chs, "HitBox01x2", -5555);
    P1_HitBox01y2 = get_config_int(P[1].State_chs, "HitBox01y2", -5555);
    P1_HitBox02x1 = get_config_int(P[1].State_chs, "HitBox02x1", -5555);
    if (P1_HitBox02x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox02y1 = get_config_int(P[1].State_chs, "HitBox02y1", -5555);
    P1_HitBox02x2 = get_config_int(P[1].State_chs, "HitBox02x2", -5555);
    P1_HitBox02y2 = get_config_int(P[1].State_chs, "HitBox02y2", -5555);
    P1_HitBox03x1 = get_config_int(P[1].State_chs, "HitBox03x1", -5555);
    if (P1_HitBox03x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox03y1 = get_config_int(P[1].State_chs, "HitBox03y1", -5555);
    P1_HitBox03x2 = get_config_int(P[1].State_chs, "HitBox03x2", -5555);
    P1_HitBox03y2 = get_config_int(P[1].State_chs, "HitBox03y2", -5555);
    P1_HitBox04x1 = get_config_int(P[1].State_chs, "HitBox04x1", -5555);
    if (P1_HitBox04x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox04y1 = get_config_int(P[1].State_chs, "HitBox04y1", -5555);
    P1_HitBox04x2 = get_config_int(P[1].State_chs, "HitBox04x2", -5555);
    P1_HitBox04y2 = get_config_int(P[1].State_chs, "HitBox04y2", -5555);
    P1_HitBox05x1 = get_config_int(P[1].State_chs, "HitBox05x1", -5555);
    if (P1_HitBox05x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox05y1 = get_config_int(P[1].State_chs, "HitBox05y1", -5555);
    P1_HitBox05x2 = get_config_int(P[1].State_chs, "HitBox05x2", -5555);
    P1_HitBox05y2 = get_config_int(P[1].State_chs, "HitBox05y2", -5555);
    P1_HitBox06x1 = get_config_int(P[1].State_chs, "HitBox06x1", -5555);
    if (P1_HitBox06x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox06y1 = get_config_int(P[1].State_chs, "HitBox06y1", -5555);
    P1_HitBox06x2 = get_config_int(P[1].State_chs, "HitBox06x2", -5555);
    P1_HitBox06y2 = get_config_int(P[1].State_chs, "HitBox06y2", -5555);
    P1_HitBox07x1 = get_config_int(P[1].State_chs, "HitBox07x1", -5555);
    if (P1_HitBox07x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox07y1 = get_config_int(P[1].State_chs, "HitBox07y1", -5555);
    P1_HitBox07x2 = get_config_int(P[1].State_chs, "HitBox07x2", -5555);
    P1_HitBox07y2 = get_config_int(P[1].State_chs, "HitBox07y2", -5555);
    P1_HitBox08x1 = get_config_int(P[1].State_chs, "HitBox08x1", -5555);
    if (P1_HitBox08x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox08y1 = get_config_int(P[1].State_chs, "HitBox08y1", -5555);
    P1_HitBox08x2 = get_config_int(P[1].State_chs, "HitBox08x2", -5555);
    P1_HitBox08y2 = get_config_int(P[1].State_chs, "HitBox08y2", -5555);
    P1_HitBox09x1 = get_config_int(P[1].State_chs, "HitBox09x1", -5555);
    if (P1_HitBox09x1 != -5555) { P1_HitBox_tot++; }
    P1_HitBox09y1 = get_config_int(P[1].State_chs, "HitBox09y1", -5555);
    P1_HitBox09x2 = get_config_int(P[1].State_chs, "HitBox09x2", -5555);
    P1_HitBox09y2 = get_config_int(P[1].State_chs, "HitBox09y2", -5555);
    P1_HurtBox01x1 = get_config_int(P[1].State_chs, "HurtBox01x1", -5555);
    if (P1_HurtBox01x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox01y1 = get_config_int(P[1].State_chs, "HurtBox01y1", -5555);
    P1_HurtBox01x2 = get_config_int(P[1].State_chs, "HurtBox01x2", -5555);
    P1_HurtBox01y2 = get_config_int(P[1].State_chs, "HurtBox01y2", -5555);
    P1_HurtBox02x1 = get_config_int(P[1].State_chs, "HurtBox02x1", -5555);
    if (P1_HurtBox02x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox02y1 = get_config_int(P[1].State_chs, "HurtBox02y1", -5555);
    P1_HurtBox02x2 = get_config_int(P[1].State_chs, "HurtBox02x2", -5555);
    P1_HurtBox02y2 = get_config_int(P[1].State_chs, "HurtBox02y2", -5555);
    P1_HurtBox03x1 = get_config_int(P[1].State_chs, "HurtBox03x1", -5555);
    if (P1_HurtBox03x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox03y1 = get_config_int(P[1].State_chs, "HurtBox03y1", -5555);
    P1_HurtBox03x2 = get_config_int(P[1].State_chs, "HurtBox03x2", -5555);
    P1_HurtBox03y2 = get_config_int(P[1].State_chs, "HurtBox03y2", -5555);
    P1_HurtBox04x1 = get_config_int(P[1].State_chs, "HurtBox04x1", -5555);
    if (P1_HurtBox04x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox04y1 = get_config_int(P[1].State_chs, "HurtBox04y1", -5555);
    P1_HurtBox04x2 = get_config_int(P[1].State_chs, "HurtBox04x2", -5555);
    P1_HurtBox04y2 = get_config_int(P[1].State_chs, "HurtBox04y2", -5555);
    P1_HurtBox05x1 = get_config_int(P[1].State_chs, "HurtBox05x1", -5555);
    if (P1_HurtBox05x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox05y1 = get_config_int(P[1].State_chs, "HurtBox05y1", -5555);
    P1_HurtBox05x2 = get_config_int(P[1].State_chs, "HurtBox05x2", -5555);
    P1_HurtBox05y2 = get_config_int(P[1].State_chs, "HurtBox05y2", -5555);
    P1_HurtBox06x1 = get_config_int(P[1].State_chs, "HurtBox06x1", -5555);
    if (P1_HurtBox06x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox06y1 = get_config_int(P[1].State_chs, "HurtBox06y1", -5555);
    P1_HurtBox06x2 = get_config_int(P[1].State_chs, "HurtBox06x2", -5555);
    P1_HurtBox06y2 = get_config_int(P[1].State_chs, "HurtBox06y2", -5555);
    P1_HurtBox07x1 = get_config_int(P[1].State_chs, "HurtBox07x1", -5555);
    if (P1_HurtBox07x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox07y1 = get_config_int(P[1].State_chs, "HurtBox07y1", -5555);
    P1_HurtBox07x2 = get_config_int(P[1].State_chs, "HurtBox07x2", -5555);
    P1_HurtBox07y2 = get_config_int(P[1].State_chs, "HurtBox07y2", -5555);
    P1_HurtBox08x1 = get_config_int(P[1].State_chs, "HurtBox08x1", -5555);
    if (P1_HurtBox08x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox08y1 = get_config_int(P[1].State_chs, "HurtBox08y1", -5555);
    P1_HurtBox08x2 = get_config_int(P[1].State_chs, "HurtBox08x2", -5555);
    P1_HurtBox08y2 = get_config_int(P[1].State_chs, "HurtBox08y2", -5555);
    P1_HurtBox09x1 = get_config_int(P[1].State_chs, "HurtBox09x1", -5555);
    if (P1_HurtBox09x1 != -5555) { P1_HurtBox_tot++; }
    P1_HurtBox09y1 = get_config_int(P[1].State_chs, "HurtBox09y1", -5555);
    P1_HurtBox09x2 = get_config_int(P[1].State_chs, "HurtBox09x2", -5555);
    P1_HurtBox09y2 = get_config_int(P[1].State_chs, "HurtBox09y2", -5555);
}

void Draw_CHBoxes_P2() {
    P2_HitBox01x1 = +5555;
    P2_HitBox01y1 = +5555;
    P2_HitBox01x2 = +5555;
    P2_HitBox01y2 = +5555;
    P2_HitBox02x1 = +5555;
    P2_HitBox02y1 = +5555;
    P2_HitBox02x2 = +5555;
    P2_HitBox02y2 = +5555;
    P2_HitBox03x1 = +5555;
    P2_HitBox03y1 = +5555;
    P2_HitBox03x2 = +5555;
    P2_HitBox03y2 = +5555;
    P2_HitBox04x1 = +5555;
    P2_HitBox04y1 = +5555;
    P2_HitBox04x2 = +5555;
    P2_HitBox04y2 = +5555;
    P2_HitBox05x1 = +5555;
    P2_HitBox05y1 = +5555;
    P2_HitBox05x2 = +5555;
    P2_HitBox05y2 = +5555;
    P2_HitBox06x1 = +5555;
    P2_HitBox06y1 = +5555;
    P2_HitBox06x2 = +5555;
    P2_HitBox06y2 = +5555;
    P2_HitBox07x1 = +5555;
    P2_HitBox07y1 = +5555;
    P2_HitBox07x2 = +5555;
    P2_HitBox07y2 = +5555;
    P2_HitBox08x1 = +5555;
    P2_HitBox08y1 = +5555;
    P2_HitBox08x2 = +5555;
    P2_HitBox08y2 = +5555;
    P2_HitBox09x1 = +5555;
    P2_HitBox09y1 = +5555;
    P2_HitBox09x2 = +5555;
    P2_HitBox09y2 = +5555;
    P2_HurtBox01x1 = +5555;
    P2_HurtBox01y1 = +5555;
    P2_HurtBox01x2 = +5555;
    P2_HurtBox01y2 = +5555;
    P2_HurtBox02x1 = +5555;
    P2_HurtBox02y1 = +5555;
    P2_HurtBox02x2 = +5555;
    P2_HurtBox02y2 = +5555;
    P2_HurtBox03x1 = +5555;
    P2_HurtBox03y1 = +5555;
    P2_HurtBox03x2 = +5555;
    P2_HurtBox03y2 = +5555;
    P2_HurtBox04x1 = +5555;
    P2_HurtBox04y1 = +5555;
    P2_HurtBox04x2 = +5555;
    P2_HurtBox04y2 = +5555;
    P2_HurtBox05x1 = +5555;
    P2_HurtBox05y1 = +5555;
    P2_HurtBox05x2 = +5555;
    P2_HurtBox05y2 = +5555;
    P2_HurtBox06x1 = +5555;
    P2_HurtBox06y1 = +5555;
    P2_HurtBox06x2 = +5555;
    P2_HurtBox06y2 = +5555;
    P2_HurtBox07x1 = +5555;
    P2_HurtBox07y1 = +5555;
    P2_HurtBox07x2 = +5555;
    P2_HurtBox07y2 = +5555;
    P2_HurtBox08x1 = +5555;
    P2_HurtBox08y1 = +5555;
    P2_HurtBox08x2 = +5555;
    P2_HurtBox08y2 = +5555;
    P2_HurtBox09x1 = +5555;
    P2_HurtBox09y1 = +5555;
    P2_HurtBox09x2 = +5555;
    P2_HurtBox09y2 = +5555;
    P2_HurtBox_tot = 0;
    P2_HitBox_tot = 0;

    sprintf(P[2].Caminho_CHBOX, "data/chars/%s/chbox.ini", P[2].Name);
    if (P[2].IndexAnim < 10) { sprintf(P[2].State_chs, "%i_0%i", P[2].State, P[2].IndexAnim); }
    if (P[2].IndexAnim >= 10) { sprintf(P[2].State_chs, "%i_%i", P[2].State, P[2].IndexAnim); }

    set_config_file(P[2].Caminho_CHBOX);
    P2_HitBox01x1 = get_config_int(P[2].State_chs, "HitBox01x1", +5555);
    if (P2_HitBox01x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox01y1 = get_config_int(P[2].State_chs, "HitBox01y1", +5555);
    P2_HitBox01x2 = get_config_int(P[2].State_chs, "HitBox01x2", +5555);
    P2_HitBox01y2 = get_config_int(P[2].State_chs, "HitBox01y2", +5555);
    P2_HitBox02x1 = get_config_int(P[2].State_chs, "HitBox02x1", +5555);
    if (P2_HitBox02x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox02y1 = get_config_int(P[2].State_chs, "HitBox02y1", +5555);
    P2_HitBox02x2 = get_config_int(P[2].State_chs, "HitBox02x2", +5555);
    P2_HitBox02y2 = get_config_int(P[2].State_chs, "HitBox02y2", +5555);
    P2_HitBox03x1 = get_config_int(P[2].State_chs, "HitBox03x1", +5555);
    if (P2_HitBox03x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox03y1 = get_config_int(P[2].State_chs, "HitBox03y1", +5555);
    P2_HitBox03x2 = get_config_int(P[2].State_chs, "HitBox03x2", +5555);
    P2_HitBox03y2 = get_config_int(P[2].State_chs, "HitBox03y2", +5555);
    P2_HitBox04x1 = get_config_int(P[2].State_chs, "HitBox04x1", +5555);
    if (P2_HitBox04x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox04y1 = get_config_int(P[2].State_chs, "HitBox04y1", +5555);
    P2_HitBox04x2 = get_config_int(P[2].State_chs, "HitBox04x2", +5555);
    P2_HitBox04y2 = get_config_int(P[2].State_chs, "HitBox04y2", +5555);
    P2_HitBox05x1 = get_config_int(P[2].State_chs, "HitBox05x1", +5555);
    if (P2_HitBox05x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox05y1 = get_config_int(P[2].State_chs, "HitBox05y1", +5555);
    P2_HitBox05x2 = get_config_int(P[2].State_chs, "HitBox05x2", +5555);
    P2_HitBox05y2 = get_config_int(P[2].State_chs, "HitBox05y2", +5555);
    P2_HitBox06x1 = get_config_int(P[2].State_chs, "HitBox06x1", +5555);
    if (P2_HitBox06x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox06y1 = get_config_int(P[2].State_chs, "HitBox06y1", +5555);
    P2_HitBox06x2 = get_config_int(P[2].State_chs, "HitBox06x2", +5555);
    P2_HitBox06y2 = get_config_int(P[2].State_chs, "HitBox06y2", +5555);
    P2_HitBox07x1 = get_config_int(P[2].State_chs, "HitBox07x1", +5555);
    if (P2_HitBox07x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox07y1 = get_config_int(P[2].State_chs, "HitBox07y1", +5555);
    P2_HitBox07x2 = get_config_int(P[2].State_chs, "HitBox07x2", +5555);
    P2_HitBox07y2 = get_config_int(P[2].State_chs, "HitBox07y2", +5555);
    P2_HitBox08x1 = get_config_int(P[2].State_chs, "HitBox08x1", +5555);
    if (P2_HitBox08x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox08y1 = get_config_int(P[2].State_chs, "HitBox08y1", +5555);
    P2_HitBox08x2 = get_config_int(P[2].State_chs, "HitBox08x2", +5555);
    P2_HitBox08y2 = get_config_int(P[2].State_chs, "HitBox08y2", +5555);
    P2_HitBox09x1 = get_config_int(P[2].State_chs, "HitBox09x1", +5555);
    if (P2_HitBox09x1 != +5555) { P2_HitBox_tot++; }
    P2_HitBox09y1 = get_config_int(P[2].State_chs, "HitBox09y1", +5555);
    P2_HitBox09x2 = get_config_int(P[2].State_chs, "HitBox09x2", +5555);
    P2_HitBox09y2 = get_config_int(P[2].State_chs, "HitBox09y2", +5555);
    P2_HurtBox01x1 = get_config_int(P[2].State_chs, "HurtBox01x1", +5555);
    if (P2_HurtBox01x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox01y1 = get_config_int(P[2].State_chs, "HurtBox01y1", +5555);
    P2_HurtBox01x2 = get_config_int(P[2].State_chs, "HurtBox01x2", +5555);
    P2_HurtBox01y2 = get_config_int(P[2].State_chs, "HurtBox01y2", +5555);
    P2_HurtBox02x1 = get_config_int(P[2].State_chs, "HurtBox02x1", +5555);
    if (P2_HurtBox02x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox02y1 = get_config_int(P[2].State_chs, "HurtBox02y1", +5555);
    P2_HurtBox02x2 = get_config_int(P[2].State_chs, "HurtBox02x2", +5555);
    P2_HurtBox02y2 = get_config_int(P[2].State_chs, "HurtBox02y2", +5555);
    P2_HurtBox03x1 = get_config_int(P[2].State_chs, "HurtBox03x1", +5555);
    if (P2_HurtBox03x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox03y1 = get_config_int(P[2].State_chs, "HurtBox03y1", +5555);
    P2_HurtBox03x2 = get_config_int(P[2].State_chs, "HurtBox03x2", +5555);
    P2_HurtBox03y2 = get_config_int(P[2].State_chs, "HurtBox03y2", +5555);
    P2_HurtBox04x1 = get_config_int(P[2].State_chs, "HurtBox04x1", +5555);
    if (P2_HurtBox04x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox04y1 = get_config_int(P[2].State_chs, "HurtBox04y1", +5555);
    P2_HurtBox04x2 = get_config_int(P[2].State_chs, "HurtBox04x2", +5555);
    P2_HurtBox04y2 = get_config_int(P[2].State_chs, "HurtBox04y2", +5555);
    P2_HurtBox05x1 = get_config_int(P[2].State_chs, "HurtBox05x1", +5555);
    if (P2_HurtBox05x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox05y1 = get_config_int(P[2].State_chs, "HurtBox05y1", +5555);
    P2_HurtBox05x2 = get_config_int(P[2].State_chs, "HurtBox05x2", +5555);
    P2_HurtBox05y2 = get_config_int(P[2].State_chs, "HurtBox05y2", +5555);
    P2_HurtBox06x1 = get_config_int(P[2].State_chs, "HurtBox06x1", +5555);
    if (P2_HurtBox06x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox06y1 = get_config_int(P[2].State_chs, "HurtBox06y1", +5555);
    P2_HurtBox06x2 = get_config_int(P[2].State_chs, "HurtBox06x2", +5555);
    P2_HurtBox06y2 = get_config_int(P[2].State_chs, "HurtBox06y2", +5555);
    P2_HurtBox07x1 = get_config_int(P[2].State_chs, "HurtBox07x1", +5555);
    if (P2_HurtBox07x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox07y1 = get_config_int(P[2].State_chs, "HurtBox07y1", +5555);
    P2_HurtBox07x2 = get_config_int(P[2].State_chs, "HurtBox07x2", +5555);
    P2_HurtBox07y2 = get_config_int(P[2].State_chs, "HurtBox07y2", +5555);
    P2_HurtBox08x1 = get_config_int(P[2].State_chs, "HurtBox08x1", +5555);
    if (P2_HurtBox08x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox08y1 = get_config_int(P[2].State_chs, "HurtBox08y1", +5555);
    P2_HurtBox08x2 = get_config_int(P[2].State_chs, "HurtBox08x2", +5555);
    P2_HurtBox08y2 = get_config_int(P[2].State_chs, "HurtBox08y2", +5555);
    P2_HurtBox09x1 = get_config_int(P[2].State_chs, "HurtBox09x1", +5555);
    if (P2_HurtBox09x1 != +5555) { P2_HurtBox_tot++; }
    P2_HurtBox09y1 = get_config_int(P[2].State_chs, "HurtBox09y1", +5555);
    P2_HurtBox09x2 = get_config_int(P[2].State_chs, "HurtBox09x2", +5555);
    P2_HurtBox09y2 = get_config_int(P[2].State_chs, "HurtBox09y2", +5555);
}

void Draw_CHBoxes_ED() {
    ED_HitBox01x1 = -1;
    ED_HitBox01y1 = -1;
    ED_HitBox01x2 = -1;
    ED_HitBox01y2 = -1;
    ED_HitBox02x1 = -1;
    ED_HitBox02y1 = -1;
    ED_HitBox02x2 = -1;
    ED_HitBox02y2 = -1;
    ED_HitBox03x1 = -1;
    ED_HitBox03y1 = -1;
    ED_HitBox03x2 = -1;
    ED_HitBox03y2 = -1;
    ED_HitBox04x1 = -1;
    ED_HitBox04y1 = -1;
    ED_HitBox04x2 = -1;
    ED_HitBox04y2 = -1;
    ED_HitBox05x1 = -1;
    ED_HitBox05y1 = -1;
    ED_HitBox05x2 = -1;
    ED_HitBox05y2 = -1;
    ED_HitBox06x1 = -1;
    ED_HitBox06y1 = -1;
    ED_HitBox06x2 = -1;
    ED_HitBox06y2 = -1;
    ED_HitBox07x1 = -1;
    ED_HitBox07y1 = -1;
    ED_HitBox07x2 = -1;
    ED_HitBox07y2 = -1;
    ED_HitBox08x1 = -1;
    ED_HitBox08y1 = -1;
    ED_HitBox08x2 = -1;
    ED_HitBox08y2 = -1;
    ED_HitBox09x1 = -1;
    ED_HitBox09y1 = -1;
    ED_HitBox09x2 = -1;
    ED_HitBox09y2 = -1;
    ED_HurtBox01x1 = -1;
    ED_HurtBox01y1 = -1;
    ED_HurtBox01x2 = -1;
    ED_HurtBox01y2 = -1;
    ED_HurtBox02x1 = -1;
    ED_HurtBox02y1 = -1;
    ED_HurtBox02x2 = -1;
    ED_HurtBox02y2 = -1;
    ED_HurtBox03x1 = -1;
    ED_HurtBox03y1 = -1;
    ED_HurtBox03x2 = -1;
    ED_HurtBox03y2 = -1;
    ED_HurtBox04x1 = -1;
    ED_HurtBox04y1 = -1;
    ED_HurtBox04x2 = -1;
    ED_HurtBox04y2 = -1;
    ED_HurtBox05x1 = -1;
    ED_HurtBox05y1 = -1;
    ED_HurtBox05x2 = -1;
    ED_HurtBox05y2 = -1;
    ED_HurtBox06x1 = -1;
    ED_HurtBox06y1 = -1;
    ED_HurtBox06x2 = -1;
    ED_HurtBox06y2 = -1;
    ED_HurtBox07x1 = -1;
    ED_HurtBox07y1 = -1;
    ED_HurtBox07x2 = -1;
    ED_HurtBox07y2 = -1;
    ED_HurtBox08x1 = -1;
    ED_HurtBox08y1 = -1;
    ED_HurtBox08x2 = -1;
    ED_HurtBox08y2 = -1;
    ED_HurtBox09x1 = -1;
    ED_HurtBox09y1 = -1;
    ED_HurtBox09x2 = -1;
    ED_HurtBox09y2 = -1;
    ED_HitBox_tot = 0;
    ED_HurtBox_tot = 0;

    char ED_Caminho_CHBOX[99];
    char ED_State_chs[99];
    sprintf(ED_Caminho_CHBOX, "data/chars/%s/chbox.ini", ED_Name);
    if (ED_IndexAnim < 10) { sprintf(ED_State_chs, "%i_0%i", ED_State, ED_IndexAnim); }
    if (ED_IndexAnim >= 10) { sprintf(ED_State_chs, "%i_%i", ED_State, ED_IndexAnim); }

    set_config_file(ED_Caminho_CHBOX);
    ED_HitBox01x1 = get_config_int(ED_State_chs, "HitBox01x1", -5555);
    if (ED_HitBox01x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox01y1 = get_config_int(ED_State_chs, "HitBox01y1", -5555);
    ED_HitBox01x2 = get_config_int(ED_State_chs, "HitBox01x2", -5555);
    ED_HitBox01y2 = get_config_int(ED_State_chs, "HitBox01y2", -5555);
    ED_HitBox02x1 = get_config_int(ED_State_chs, "HitBox02x1", -5555);
    if (ED_HitBox02x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox02y1 = get_config_int(ED_State_chs, "HitBox02y1", -5555);
    ED_HitBox02x2 = get_config_int(ED_State_chs, "HitBox02x2", -5555);
    ED_HitBox02y2 = get_config_int(ED_State_chs, "HitBox02y2", -5555);
    ED_HitBox03x1 = get_config_int(ED_State_chs, "HitBox03x1", -5555);
    if (ED_HitBox03x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox03y1 = get_config_int(ED_State_chs, "HitBox03y1", -5555);
    ED_HitBox03x2 = get_config_int(ED_State_chs, "HitBox03x2", -5555);
    ED_HitBox03y2 = get_config_int(ED_State_chs, "HitBox03y2", -5555);
    ED_HitBox04x1 = get_config_int(ED_State_chs, "HitBox04x1", -5555);
    if (ED_HitBox04x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox04y1 = get_config_int(ED_State_chs, "HitBox04y1", -5555);
    ED_HitBox04x2 = get_config_int(ED_State_chs, "HitBox04x2", -5555);
    ED_HitBox04y2 = get_config_int(ED_State_chs, "HitBox04y2", -5555);
    ED_HitBox05x1 = get_config_int(ED_State_chs, "HitBox05x1", -5555);
    if (ED_HitBox05x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox05y1 = get_config_int(ED_State_chs, "HitBox05y1", -5555);
    ED_HitBox05x2 = get_config_int(ED_State_chs, "HitBox05x2", -5555);
    ED_HitBox05y2 = get_config_int(ED_State_chs, "HitBox05y2", -5555);
    ED_HitBox06x1 = get_config_int(ED_State_chs, "HitBox06x1", -5555);
    if (ED_HitBox06x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox06y1 = get_config_int(ED_State_chs, "HitBox06y1", -5555);
    ED_HitBox06x2 = get_config_int(ED_State_chs, "HitBox06x2", -5555);
    ED_HitBox06y2 = get_config_int(ED_State_chs, "HitBox06y2", -5555);
    ED_HitBox07x1 = get_config_int(ED_State_chs, "HitBox07x1", -5555);
    if (ED_HitBox07x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox07y1 = get_config_int(ED_State_chs, "HitBox07y1", -5555);
    ED_HitBox07x2 = get_config_int(ED_State_chs, "HitBox07x2", -5555);
    ED_HitBox07y2 = get_config_int(ED_State_chs, "HitBox07y2", -5555);
    ED_HitBox08x1 = get_config_int(ED_State_chs, "HitBox08x1", -5555);
    if (ED_HitBox08x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox08y1 = get_config_int(ED_State_chs, "HitBox08y1", -5555);
    ED_HitBox08x2 = get_config_int(ED_State_chs, "HitBox08x2", -5555);
    ED_HitBox08y2 = get_config_int(ED_State_chs, "HitBox08y2", -5555);
    ED_HitBox09x1 = get_config_int(ED_State_chs, "HitBox09x1", -5555);
    if (ED_HitBox09x1 != -5555) { ED_HitBox_tot++; }
    ED_HitBox09y1 = get_config_int(ED_State_chs, "HitBox09y1", -5555);
    ED_HitBox09x2 = get_config_int(ED_State_chs, "HitBox09x2", -5555);
    ED_HitBox09y2 = get_config_int(ED_State_chs, "HitBox09y2", -5555);
    ED_HurtBox01x1 = get_config_int(ED_State_chs, "HurtBox01x1", -5555);
    if (ED_HurtBox01x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox01y1 = get_config_int(ED_State_chs, "HurtBox01y1", -5555);
    ED_HurtBox01x2 = get_config_int(ED_State_chs, "HurtBox01x2", -5555);
    ED_HurtBox01y2 = get_config_int(ED_State_chs, "HurtBox01y2", -5555);
    ED_HurtBox02x1 = get_config_int(ED_State_chs, "HurtBox02x1", -5555);
    if (ED_HurtBox02x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox02y1 = get_config_int(ED_State_chs, "HurtBox02y1", -5555);
    ED_HurtBox02x2 = get_config_int(ED_State_chs, "HurtBox02x2", -5555);
    ED_HurtBox02y2 = get_config_int(ED_State_chs, "HurtBox02y2", -5555);
    ED_HurtBox03x1 = get_config_int(ED_State_chs, "HurtBox03x1", -5555);
    if (ED_HurtBox03x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox03y1 = get_config_int(ED_State_chs, "HurtBox03y1", -5555);
    ED_HurtBox03x2 = get_config_int(ED_State_chs, "HurtBox03x2", -5555);
    ED_HurtBox03y2 = get_config_int(ED_State_chs, "HurtBox03y2", -5555);
    ED_HurtBox04x1 = get_config_int(ED_State_chs, "HurtBox04x1", -5555);
    if (ED_HurtBox04x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox04y1 = get_config_int(ED_State_chs, "HurtBox04y1", -5555);
    ED_HurtBox04x2 = get_config_int(ED_State_chs, "HurtBox04x2", -5555);
    ED_HurtBox04y2 = get_config_int(ED_State_chs, "HurtBox04y2", -5555);
    ED_HurtBox05x1 = get_config_int(ED_State_chs, "HurtBox05x1", -5555);
    if (ED_HurtBox05x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox05y1 = get_config_int(ED_State_chs, "HurtBox05y1", -5555);
    ED_HurtBox05x2 = get_config_int(ED_State_chs, "HurtBox05x2", -5555);
    ED_HurtBox05y2 = get_config_int(ED_State_chs, "HurtBox05y2", -5555);
    ED_HurtBox06x1 = get_config_int(ED_State_chs, "HurtBox06x1", -5555);
    if (ED_HurtBox06x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox06y1 = get_config_int(ED_State_chs, "HurtBox06y1", -5555);
    ED_HurtBox06x2 = get_config_int(ED_State_chs, "HurtBox06x2", -5555);
    ED_HurtBox06y2 = get_config_int(ED_State_chs, "HurtBox06y2", -5555);
    ED_HurtBox07x1 = get_config_int(ED_State_chs, "HurtBox07x1", -5555);
    if (ED_HurtBox07x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox07y1 = get_config_int(ED_State_chs, "HurtBox07y1", -5555);
    ED_HurtBox07x2 = get_config_int(ED_State_chs, "HurtBox07x2", -5555);
    ED_HurtBox07y2 = get_config_int(ED_State_chs, "HurtBox07y2", -5555);
    ED_HurtBox08x1 = get_config_int(ED_State_chs, "HurtBox08x1", -5555);
    if (ED_HurtBox08x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox08y1 = get_config_int(ED_State_chs, "HurtBox08y1", -5555);
    ED_HurtBox08x2 = get_config_int(ED_State_chs, "HurtBox08x2", -5555);
    ED_HurtBox08y2 = get_config_int(ED_State_chs, "HurtBox08y2", -5555);
    ED_HurtBox09x1 = get_config_int(ED_State_chs, "HurtBox09x1", -5555);
    if (ED_HurtBox09x1 != -5555) { ED_HurtBox_tot++; }
    ED_HurtBox09y1 = get_config_int(ED_State_chs, "HurtBox09y1", -5555);
    ED_HurtBox09x2 = get_config_int(ED_State_chs, "HurtBox09x2", -5555);
    ED_HurtBox09y2 = get_config_int(ED_State_chs, "HurtBox09y2", -5555);
}

///////////////////////////////////////////////////////////////////////////////
// CHECAR COLISAO -------------------------------------------------------[**04]
///////////////////////////////////////////////////////////////////////////////

void Checar_Colisao() {
    //INICIALIZACAO DE VARIAVEIS
    colisaoxP1 = 0;
    alturadohitp1 = 0;
    colisaoxP2 = 0;
    alturadohitp2 = 0;
    int P1hb_HurtBox01x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox01x1) * 2;
    int P1hb_HurtBox01x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox01x2) * 2;
    int P1hb_HurtBox01y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox01y1 * 2);
    int P1hb_HurtBox01y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox01y2 * 2);
    int P1hb_HurtBox02x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox02x1) * 2;
    int P1hb_HurtBox02x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox02x2) * 2;
    int P1hb_HurtBox02y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox02y1 * 2);
    int P1hb_HurtBox02y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox02y2 * 2);
    int P1hb_HurtBox03x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox03x1) * 2;
    int P1hb_HurtBox03x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox03x2) * 2;
    int P1hb_HurtBox03y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox03y1 * 2);
    int P1hb_HurtBox03y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox03y2 * 2);
    int P1hb_HurtBox04x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox04x1) * 2;
    int P1hb_HurtBox04x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox04x2) * 2;
    int P1hb_HurtBox04y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox04y1 * 2);
    int P1hb_HurtBox04y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox04y2 * 2);
    int P1hb_HurtBox05x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox05x1) * 2;
    int P1hb_HurtBox05x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox05x2) * 2;
    int P1hb_HurtBox05y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox05y1 * 2);
    int P1hb_HurtBox05y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox05y2 * 2);
    int P1hb_HurtBox06x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox06x1) * 2;
    int P1hb_HurtBox06x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox06x2) * 2;
    int P1hb_HurtBox06y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox06y1 * 2);
    int P1hb_HurtBox06y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox06y2 * 2);
    int P1hb_HurtBox07x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox07x1) * 2;
    int P1hb_HurtBox07x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox07x2) * 2;
    int P1hb_HurtBox07y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox07y1 * 2);
    int P1hb_HurtBox07y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox07y2 * 2);
    int P1hb_HurtBox08x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox08x1) * 2;
    int P1hb_HurtBox08x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox08x2) * 2;
    int P1hb_HurtBox08y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox08y1 * 2);
    int P1hb_HurtBox08y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox08y2 * 2);
    int P1hb_HurtBox09x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox09x1) * 2;
    int P1hb_HurtBox09x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HurtBox09x2) * 2;
    int P1hb_HurtBox09y1 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox09y1 * 2);
    int P1hb_HurtBox09y2 = (AlturaPiso + (P[1].y * 2) + P1_HurtBox09y2 * 2);
    int P1hb_HitBox01x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox01x1) * 2;
    int P1hb_HitBox01x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox01x2) * 2;
    int P1hb_HitBox01y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox01y1 * 2);
    int P1hb_HitBox01y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox01y2 * 2);
    int P1hb_HitBox02x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox02x1) * 2;
    int P1hb_HitBox02x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox02x2) * 2;
    int P1hb_HitBox02y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox02y1 * 2);
    int P1hb_HitBox02y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox02y2 * 2);
    int P1hb_HitBox03x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox03x1) * 2;
    int P1hb_HitBox03x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox03x2) * 2;
    int P1hb_HitBox03y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox03y1 * 2);
    int P1hb_HitBox03y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox03y2 * 2);
    int P1hb_HitBox04x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox04x1) * 2;
    int P1hb_HitBox04x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox04x2) * 2;
    int P1hb_HitBox04y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox04y1 * 2);
    int P1hb_HitBox04y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox04y2 * 2);
    int P1hb_HitBox05x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox05x1) * 2;
    int P1hb_HitBox05x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox05x2) * 2;
    int P1hb_HitBox05y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox05y1 * 2);
    int P1hb_HitBox05y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox05y2 * 2);
    int P1hb_HitBox06x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox06x1) * 2;
    int P1hb_HitBox06x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox06x2) * 2;
    int P1hb_HitBox06y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox06y1 * 2);
    int P1hb_HitBox06y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox06y2 * 2);
    int P1hb_HitBox07x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox07x1) * 2;
    int P1hb_HitBox07x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox07x2) * 2;
    int P1hb_HitBox07y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox07y1 * 2);
    int P1hb_HitBox07y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox07y2 * 2);
    int P1hb_HitBox08x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox08x1) * 2;
    int P1hb_HitBox08x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox08x2) * 2;
    int P1hb_HitBox08y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox08y1 * 2);
    int P1hb_HitBox08y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox08y2 * 2);
    int P1hb_HitBox09x1 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox09x1) * 2;
    int P1hb_HitBox09x2 = ((P[1].x) * 2) + (P[1].Lado * P1_HitBox09x2) * 2;
    int P1hb_HitBox09y1 = (AlturaPiso + (P[1].y * 2) + P1_HitBox09y1 * 2);
    int P1hb_HitBox09y2 = (AlturaPiso + (P[1].y * 2) + P1_HitBox09y2 * 2);

    int P2hb_HurtBox01x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox01x1) * 2;
    int P2hb_HurtBox01x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox01x2) * 2;
    int P2hb_HurtBox01y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox01y1 * 2);
    int P2hb_HurtBox01y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox01y2 * 2);
    int P2hb_HurtBox02x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox02x1) * 2;
    int P2hb_HurtBox02x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox02x2) * 2;
    int P2hb_HurtBox02y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox02y1 * 2);
    int P2hb_HurtBox02y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox02y2 * 2);
    int P2hb_HurtBox03x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox03x1) * 2;
    int P2hb_HurtBox03x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox03x2) * 2;
    int P2hb_HurtBox03y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox03y1 * 2);
    int P2hb_HurtBox03y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox03y2 * 2);
    int P2hb_HurtBox04x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox04x1) * 2;
    int P2hb_HurtBox04x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox04x2) * 2;
    int P2hb_HurtBox04y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox04y1 * 2);
    int P2hb_HurtBox04y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox04y2 * 2);
    int P2hb_HurtBox05x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox05x1) * 2;
    int P2hb_HurtBox05x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox05x2) * 2;
    int P2hb_HurtBox05y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox05y1 * 2);
    int P2hb_HurtBox05y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox05y2 * 2);
    int P2hb_HurtBox06x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox06x1) * 2;
    int P2hb_HurtBox06x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox06x2) * 2;
    int P2hb_HurtBox06y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox06y1 * 2);
    int P2hb_HurtBox06y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox06y2 * 2);
    int P2hb_HurtBox07x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox07x1) * 2;
    int P2hb_HurtBox07x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox07x2) * 2;
    int P2hb_HurtBox07y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox07y1 * 2);
    int P2hb_HurtBox07y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox07y2 * 2);
    int P2hb_HurtBox08x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox08x1) * 2;
    int P2hb_HurtBox08x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox08x2) * 2;
    int P2hb_HurtBox08y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox08y1 * 2);
    int P2hb_HurtBox08y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox08y2 * 2);
    int P2hb_HurtBox09x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox09x1) * 2;
    int P2hb_HurtBox09x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HurtBox09x2) * 2;
    int P2hb_HurtBox09y1 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox09y1 * 2);
    int P2hb_HurtBox09y2 = (AlturaPiso + (P[2].y * 2) + P2_HurtBox09y2 * 2);
    int P2hb_HitBox01x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox01x1) * 2;
    int P2hb_HitBox01x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox01x2) * 2;
    int P2hb_HitBox01y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox01y1 * 2);
    int P2hb_HitBox01y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox01y2 * 2);
    int P2hb_HitBox02x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox02x1) * 2;
    int P2hb_HitBox02x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox02x2) * 2;
    int P2hb_HitBox02y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox02y1 * 2);
    int P2hb_HitBox02y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox02y2 * 2);
    int P2hb_HitBox03x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox03x1) * 2;
    int P2hb_HitBox03x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox03x2) * 2;
    int P2hb_HitBox03y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox03y1 * 2);
    int P2hb_HitBox03y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox03y2 * 2);
    int P2hb_HitBox04x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox04x1) * 2;
    int P2hb_HitBox04x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox04x2) * 2;
    int P2hb_HitBox04y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox04y1 * 2);
    int P2hb_HitBox04y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox04y2 * 2);
    int P2hb_HitBox05x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox05x1) * 2;
    int P2hb_HitBox05x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox05x2) * 2;
    int P2hb_HitBox05y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox05y1 * 2);
    int P2hb_HitBox05y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox05y2 * 2);
    int P2hb_HitBox06x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox06x1) * 2;
    int P2hb_HitBox06x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox06x2) * 2;
    int P2hb_HitBox06y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox06y1 * 2);
    int P2hb_HitBox06y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox06y2 * 2);
    int P2hb_HitBox07x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox07x1) * 2;
    int P2hb_HitBox07x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox07x2) * 2;
    int P2hb_HitBox07y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox07y1 * 2);
    int P2hb_HitBox07y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox07y2 * 2);
    int P2hb_HitBox08x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox08x1) * 2;
    int P2hb_HitBox08x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox08x2) * 2;
    int P2hb_HitBox08y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox08y1 * 2);
    int P2hb_HitBox08y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox08y2 * 2);
    int P2hb_HitBox09x1 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox09x1) * 2;
    int P2hb_HitBox09x2 = ((P[2].x) * 2) + (P[2].Lado * P2_HitBox09x2) * 2;
    int P2hb_HitBox09y1 = (AlturaPiso + (P[2].y * 2) + P2_HitBox09y1 * 2);
    int P2hb_HitBox09y2 = (AlturaPiso + (P[2].y * 2) + P2_HitBox09y2 * 2);

    //Checar Contato Fisico//
    //preparacao dos hurt boxes
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
    //calcula colisao entre 2 HurtBoxes
    if (
        P2_HurtBox01x1 != +5555 && P2_HurtBox01y1 != +5555 && P2_HurtBox01x2 != +5555 && P2_HurtBox01y2 != +5555 &&
        P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 && P1_HurtBox01y2 != -5555) {
        if (
            (P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HurtBox01x1) &&
            (P1hb_HurtBox01x1 < P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1)) &&
            (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HurtBox01y1) &&
            (P1hb_HurtBox01y1 < P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1))) {
            contatofisico = 1;
        } else {
            contatofisico = 0;
        }
    }
    if (P[1].Energy == 0 || P[2].Energy == 0) { contatofisico = 0; }
    if (P1_HurtBox01x1 == -5555) { contatofisico = 0; }
    if (P2_HurtBox01x1 == 5555) { contatofisico = 0; }

    // Nota sobre os testes de colisao
    // Esse codigo a seguir testa TODAS as 9 caixas de hurt contra TODAS as 9 caixas de hit
    // 9 * 9 = 81 repeticoes do codigo!
    // Desculpem por isso...
    // Me ajudem a otimizar? Valeu! :)

    ///Checar Colisao contra P1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (P2_HitBox_tot >= 1) {
        //1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox01x1 != +5555 && P2_HitBox01y1 != +5555 && P2_HitBox01x2 != +5555 &&
            P2_HitBox01y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox01x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox01x1 + (P2hb_HitBox01x2 - P2hb_HitBox01x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox01y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox01y1 + (P2hb_HitBox01y2 - P2hb_HitBox01y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 1;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 2) {
        //2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox02x1;
        temp1y = P2hb_HitBox02y1;
        temp2x = P2hb_HitBox02x2;
        temp2y = P2hb_HitBox02y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox02x1 = temp1x;
            P2hb_HitBox02x2 = temp2x;
        } else {
            P2hb_HitBox02x1 = temp2x;
            P2hb_HitBox02x2 = temp1x;
        }
        if (P2hb_HitBox02x1 < 0) { P2hb_HitBox02x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox02x1 != +5555 && P2_HitBox02y1 != +5555 && P2_HitBox02x2 != +5555 &&
            P2_HitBox02y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox02x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox02x1 + (P2hb_HitBox02x2 - P2hb_HitBox02x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox02y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox02y1 + (P2hb_HitBox02y2 - P2hb_HitBox02y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 2;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 3) {
        //3//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox03x1;
        temp1y = P2hb_HitBox03y1;
        temp2x = P2hb_HitBox03x2;
        temp2y = P2hb_HitBox03y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox03x1 = temp1x;
            P2hb_HitBox03x2 = temp2x;
        } else {
            P2hb_HitBox03x1 = temp2x;
            P2hb_HitBox03x2 = temp1x;
        }
        if (P2hb_HitBox03x1 < 0) { P2hb_HitBox03x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox03x1 != +5555 && P2_HitBox03y1 != +5555 && P2_HitBox03x2 != +5555 &&
            P2_HitBox03y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox03x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox03x1 + (P2hb_HitBox03x2 - P2hb_HitBox03x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox03y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox03y1 + (P2hb_HitBox03y2 - P2hb_HitBox03y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 3;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 4) {
        //4//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox04x1;
        temp1y = P2hb_HitBox04y1;
        temp2x = P2hb_HitBox04x2;
        temp2y = P2hb_HitBox04y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox04x1 = temp1x;
            P2hb_HitBox04x2 = temp2x;
        } else {
            P2hb_HitBox04x1 = temp2x;
            P2hb_HitBox04x2 = temp1x;
        }
        if (P2hb_HitBox04x1 < 0) { P2hb_HitBox04x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox04x1 != +5555 && P2_HitBox04y1 != +5555 && P2_HitBox04x2 != +5555 &&
            P2_HitBox04y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox04x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox04x1 + (P2hb_HitBox04x2 - P2hb_HitBox04x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox04y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox04y1 + (P2hb_HitBox04y2 - P2hb_HitBox04y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 4;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 5) {
        //5//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox05x1;
        temp1y = P2hb_HitBox05y1;
        temp2x = P2hb_HitBox05x2;
        temp2y = P2hb_HitBox05y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox05x1 = temp1x;
            P2hb_HitBox05x2 = temp2x;
        } else {
            P2hb_HitBox05x1 = temp2x;
            P2hb_HitBox05x2 = temp1x;
        }
        if (P2hb_HitBox05x1 < 0) { P2hb_HitBox05x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox05x1 != +5555 && P2_HitBox05y1 != +5555 && P2_HitBox05x2 != +5555 &&
            P2_HitBox05y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox05x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox05x1 + (P2hb_HitBox05x2 - P2hb_HitBox05x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox05y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox05y1 + (P2hb_HitBox05y2 - P2hb_HitBox05y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 5;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 6) {
        //6//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox06x1;
        temp1y = P2hb_HitBox06y1;
        temp2x = P2hb_HitBox06x2;
        temp2y = P2hb_HitBox06y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox06x1 = temp1x;
            P2hb_HitBox06x2 = temp2x;
        } else {
            P2hb_HitBox06x1 = temp2x;
            P2hb_HitBox06x2 = temp1x;
        }
        if (P2hb_HitBox06x1 < 0) { P2hb_HitBox06x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox06x1 != +5555 && P2_HitBox06y1 != +5555 && P2_HitBox06x2 != +5555 &&
            P2_HitBox06y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox06x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox06x1 + (P2hb_HitBox06x2 - P2hb_HitBox06x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox06y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox06y1 + (P2hb_HitBox06y2 - P2hb_HitBox06y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 6;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 7) {
        //7//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox07x1;
        temp1y = P2hb_HitBox07y1;
        temp2x = P2hb_HitBox07x2;
        temp2y = P2hb_HitBox07y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox07x1 = temp1x;
            P2hb_HitBox07x2 = temp2x;
        } else {
            P2hb_HitBox07x1 = temp2x;
            P2hb_HitBox07x2 = temp1x;
        }
        if (P2hb_HitBox07x1 < 0) { P2hb_HitBox07x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox07x1 != +5555 && P2_HitBox07y1 != +5555 && P2_HitBox07x2 != +5555 &&
            P2_HitBox07y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox07x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox07x1 + (P2hb_HitBox07x2 - P2hb_HitBox07x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox07y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox07y1 + (P2hb_HitBox07y2 - P2hb_HitBox07y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 7;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 8) {
        //8//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox08x1;
        temp1y = P2hb_HitBox08y1;
        temp2x = P2hb_HitBox08x2;
        temp2y = P2hb_HitBox08y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox08x1 = temp1x;
            P2hb_HitBox08x2 = temp2x;
        } else {
            P2hb_HitBox08x1 = temp2x;
            P2hb_HitBox08x2 = temp1x;
        }
        if (P2hb_HitBox08x1 < 0) { P2hb_HitBox08x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox08x1 != +5555 && P2_HitBox08y1 != +5555 && P2_HitBox08x2 != +5555 &&
            P2_HitBox08y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox08x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox08x1 + (P2hb_HitBox08x2 - P2hb_HitBox08x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox08y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox08y1 + (P2hb_HitBox08y2 - P2hb_HitBox08y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 8;
            } else { colisaoxP1 = 0; }
        }
    }

    if (P2_HitBox_tot >= 9) {
        //9//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P2hb_HitBox09x1;
        temp1y = P2hb_HitBox09y1;
        temp2x = P2hb_HitBox09x2;
        temp2y = P2hb_HitBox09y2;
        if (temp1x <= temp2x) {
            P2hb_HitBox09x1 = temp1x;
            P2hb_HitBox09x2 = temp2x;
        } else {
            P2hb_HitBox09x1 = temp2x;
            P2hb_HitBox09x2 = temp1x;
        }
        if (P2hb_HitBox09x1 < 0) { P2hb_HitBox09x1 = 0; }
        //x1
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox01x1 != -5555 && P1_HurtBox01y1 != -5555 && P1_HurtBox01x2 != -5555 &&
            P1_HurtBox01y2 != -5555) {
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
            if ((P1hb_HurtBox01x1 + (P1hb_HurtBox01x2 - P1hb_HurtBox01x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox01x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox01y1 + (P1hb_HurtBox01y2 - P1hb_HurtBox01y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox01y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x2
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox02x1 != -5555 && P1_HurtBox02y1 != -5555 && P1_HurtBox02x2 != -5555 &&
            P1_HurtBox02y2 != -5555) {
            temp1x = P1hb_HurtBox02x1;
            temp1y = P1hb_HurtBox02y1;
            temp2x = P1hb_HurtBox02x2;
            temp2y = P1hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox02x1 = temp1x;
                P1hb_HurtBox02x2 = temp2x;
            } else {
                P1hb_HurtBox02x1 = temp2x;
                P1hb_HurtBox02x2 = temp1x;
            }
            if (P1hb_HurtBox02x1 < 0) { P1hb_HurtBox02x1 = 0; }
            if ((P1hb_HurtBox02x1 + (P1hb_HurtBox02x2 - P1hb_HurtBox02x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox02x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox02y1 + (P1hb_HurtBox02y2 - P1hb_HurtBox02y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox02y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x3
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox03x1 != -5555 && P1_HurtBox03y1 != -5555 && P1_HurtBox03x2 != -5555 &&
            P1_HurtBox03y2 != -5555) {
            temp1x = P1hb_HurtBox03x1;
            temp1y = P1hb_HurtBox03y1;
            temp2x = P1hb_HurtBox03x2;
            temp2y = P1hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox03x1 = temp1x;
                P1hb_HurtBox03x2 = temp2x;
            } else {
                P1hb_HurtBox03x1 = temp2x;
                P1hb_HurtBox03x2 = temp1x;
            }
            if (P1hb_HurtBox03x1 < 0) { P1hb_HurtBox03x1 = 0; }
            if ((P1hb_HurtBox03x1 + (P1hb_HurtBox03x2 - P1hb_HurtBox03x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox03x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox03y1 + (P1hb_HurtBox03y2 - P1hb_HurtBox03y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox03y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x4
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox04x1 != -5555 && P1_HurtBox04y1 != -5555 && P1_HurtBox04x2 != -5555 &&
            P1_HurtBox04y2 != -5555) {
            temp1x = P1hb_HurtBox04x1;
            temp1y = P1hb_HurtBox04y1;
            temp2x = P1hb_HurtBox04x2;
            temp2y = P1hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox04x1 = temp1x;
                P1hb_HurtBox04x2 = temp2x;
            } else {
                P1hb_HurtBox04x1 = temp2x;
                P1hb_HurtBox04x2 = temp1x;
            }
            if (P1hb_HurtBox04x1 < 0) { P1hb_HurtBox04x1 = 0; }
            if ((P1hb_HurtBox04x1 + (P1hb_HurtBox04x2 - P1hb_HurtBox04x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox04x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox04y1 + (P1hb_HurtBox04y2 - P1hb_HurtBox04y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox04y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x5
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox05x1 != -5555 && P1_HurtBox05y1 != -5555 && P1_HurtBox05x2 != -5555 &&
            P1_HurtBox05y2 != -5555) {
            temp1x = P1hb_HurtBox05x1;
            temp1y = P1hb_HurtBox05y1;
            temp2x = P1hb_HurtBox05x2;
            temp2y = P1hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox05x1 = temp1x;
                P1hb_HurtBox05x2 = temp2x;
            } else {
                P1hb_HurtBox05x1 = temp2x;
                P1hb_HurtBox05x2 = temp1x;
            }
            if (P1hb_HurtBox05x1 < 0) { P1hb_HurtBox05x1 = 0; }
            if ((P1hb_HurtBox05x1 + (P1hb_HurtBox05x2 - P1hb_HurtBox05x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox05x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox05y1 + (P1hb_HurtBox05y2 - P1hb_HurtBox05y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox05y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x6
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox06x1 != -5555 && P1_HurtBox06y1 != -5555 && P1_HurtBox06x2 != -5555 &&
            P1_HurtBox06y2 != -5555) {
            temp1x = P1hb_HurtBox06x1;
            temp1y = P1hb_HurtBox06y1;
            temp2x = P1hb_HurtBox06x2;
            temp2y = P1hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox06x1 = temp1x;
                P1hb_HurtBox06x2 = temp2x;
            } else {
                P1hb_HurtBox06x1 = temp2x;
                P1hb_HurtBox06x2 = temp1x;
            }
            if (P1hb_HurtBox06x1 < 0) { P1hb_HurtBox06x1 = 0; }
            if ((P1hb_HurtBox06x1 + (P1hb_HurtBox06x2 - P1hb_HurtBox06x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox06x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox06y1 + (P1hb_HurtBox06y2 - P1hb_HurtBox06y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox06y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x7
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox07x1 != -5555 && P1_HurtBox07y1 != -5555 && P1_HurtBox07x2 != -5555 &&
            P1_HurtBox07y2 != -5555) {
            temp1x = P1hb_HurtBox07x1;
            temp1y = P1hb_HurtBox07y1;
            temp2x = P1hb_HurtBox07x2;
            temp2y = P1hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox07x1 = temp1x;
                P1hb_HurtBox07x2 = temp2x;
            } else {
                P1hb_HurtBox07x1 = temp2x;
                P1hb_HurtBox07x2 = temp1x;
            }
            if (P1hb_HurtBox07x1 < 0) { P1hb_HurtBox07x1 = 0; }
            if ((P1hb_HurtBox07x1 + (P1hb_HurtBox07x2 - P1hb_HurtBox07x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox07x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox07y1 + (P1hb_HurtBox07y2 - P1hb_HurtBox07y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox07y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x8
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox08x1 != -5555 && P1_HurtBox08y1 != -5555 && P1_HurtBox08x2 != -5555 &&
            P1_HurtBox08y2 != -5555) {
            temp1x = P1hb_HurtBox08x1;
            temp1y = P1hb_HurtBox08y1;
            temp2x = P1hb_HurtBox08x2;
            temp2y = P1hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox08x1 = temp1x;
                P1hb_HurtBox08x2 = temp2x;
            } else {
                P1hb_HurtBox08x1 = temp2x;
                P1hb_HurtBox08x2 = temp1x;
            }
            if (P1hb_HurtBox08x1 < 0) { P1hb_HurtBox08x1 = 0; }
            if ((P1hb_HurtBox08x1 + (P1hb_HurtBox08x2 - P1hb_HurtBox08x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox08x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox08y1 + (P1hb_HurtBox08y2 - P1hb_HurtBox08y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox08y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
        //x9
        if (colisaoxP1 == 0 && P2_HitBox09x1 != +5555 && P2_HitBox09y1 != +5555 && P2_HitBox09x2 != +5555 &&
            P2_HitBox09y2 != +5555 && P1_HurtBox09x1 != -5555 && P1_HurtBox09y1 != -5555 && P1_HurtBox09x2 != -5555 &&
            P1_HurtBox09y2 != -5555) {
            temp1x = P1hb_HurtBox09x1;
            temp1y = P1hb_HurtBox09y1;
            temp2x = P1hb_HurtBox09x2;
            temp2y = P1hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P1hb_HurtBox09x1 = temp1x;
                P1hb_HurtBox09x2 = temp2x;
            } else {
                P1hb_HurtBox09x1 = temp2x;
                P1hb_HurtBox09x2 = temp1x;
            }
            if (P1hb_HurtBox09x1 < 0) { P1hb_HurtBox09x1 = 0; }
            if ((P1hb_HurtBox09x1 + (P1hb_HurtBox09x2 - P1hb_HurtBox09x1) > P2hb_HitBox09x1) && (
                    P1hb_HurtBox09x1 < P2hb_HitBox09x1 + (P2hb_HitBox09x2 - P2hb_HitBox09x1)) &&
                (P1hb_HurtBox09y1 + (P1hb_HurtBox09y2 - P1hb_HurtBox09y1) > P2hb_HitBox09y1) && (
                    P1hb_HurtBox09y1 < P2hb_HitBox09y1 + (P2hb_HitBox09y2 - P2hb_HitBox09y1))) {
                colisaoxP1 = 1;
                alturadohitp2 = 9;
            } else { colisaoxP1 = 0; }
        }
    }

    ///Checar Colisao contra P2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (P1_HitBox_tot >= 1) {
        //1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox01x1 != +5555 && P1_HitBox01y1 != +5555 && P1_HitBox01x2 != +5555 &&
            P1_HitBox01y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox01x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox01x1 + (P1hb_HitBox01x2 - P1hb_HitBox01x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox01y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox01y1 + (P1hb_HitBox01y2 - P1hb_HitBox01y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 1;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 2) {
        //2//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox02x1;
        temp1y = P1hb_HitBox02y1;
        temp2x = P1hb_HitBox02x2;
        temp2y = P1hb_HitBox02y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox02x1 = temp1x;
            P1hb_HitBox02x2 = temp2x;
        } else {
            P1hb_HitBox02x1 = temp2x;
            P1hb_HitBox02x2 = temp1x;
        }
        if (P1hb_HitBox02x1 < 0) { P1hb_HitBox02x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox02x1 != +5555 && P1_HitBox02y1 != +5555 && P1_HitBox02x2 != +5555 &&
            P1_HitBox02y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox02x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox02x1 + (P1hb_HitBox02x2 - P1hb_HitBox02x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox02y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox02y1 + (P1hb_HitBox02y2 - P1hb_HitBox02y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 2;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 3) {
        //3//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox03x1;
        temp1y = P1hb_HitBox03y1;
        temp2x = P1hb_HitBox03x2;
        temp2y = P1hb_HitBox03y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox03x1 = temp1x;
            P1hb_HitBox03x2 = temp2x;
        } else {
            P1hb_HitBox03x1 = temp2x;
            P1hb_HitBox03x2 = temp1x;
        }
        if (P1hb_HitBox03x1 < 0) { P1hb_HitBox03x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox03x1 != +5555 && P1_HitBox03y1 != +5555 && P1_HitBox03x2 != +5555 &&
            P1_HitBox03y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox03x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox03x1 + (P1hb_HitBox03x2 - P1hb_HitBox03x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox03y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox03y1 + (P1hb_HitBox03y2 - P1hb_HitBox03y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 3;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 4) {
        //4//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox04x1;
        temp1y = P1hb_HitBox04y1;
        temp2x = P1hb_HitBox04x2;
        temp2y = P1hb_HitBox04y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox04x1 = temp1x;
            P1hb_HitBox04x2 = temp2x;
        } else {
            P1hb_HitBox04x1 = temp2x;
            P1hb_HitBox04x2 = temp1x;
        }
        if (P1hb_HitBox04x1 < 0) { P1hb_HitBox04x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox04x1 != +5555 && P1_HitBox04y1 != +5555 && P1_HitBox04x2 != +5555 &&
            P1_HitBox04y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox04x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox04x1 + (P1hb_HitBox04x2 - P1hb_HitBox04x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox04y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox04y1 + (P1hb_HitBox04y2 - P1hb_HitBox04y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 4;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 5) {
        //5//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox05x1;
        temp1y = P1hb_HitBox05y1;
        temp2x = P1hb_HitBox05x2;
        temp2y = P1hb_HitBox05y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox05x1 = temp1x;
            P1hb_HitBox05x2 = temp2x;
        } else {
            P1hb_HitBox05x1 = temp2x;
            P1hb_HitBox05x2 = temp1x;
        }
        if (P1hb_HitBox05x1 < 0) { P1hb_HitBox05x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox05x1 != +5555 && P1_HitBox05y1 != +5555 && P1_HitBox05x2 != +5555 &&
            P1_HitBox05y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox05x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox05x1 + (P1hb_HitBox05x2 - P1hb_HitBox05x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox05y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox05y1 + (P1hb_HitBox05y2 - P1hb_HitBox05y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 5;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 6) {
        //6//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox06x1;
        temp1y = P1hb_HitBox06y1;
        temp2x = P1hb_HitBox06x2;
        temp2y = P1hb_HitBox06y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox06x1 = temp1x;
            P1hb_HitBox06x2 = temp2x;
        } else {
            P1hb_HitBox06x1 = temp2x;
            P1hb_HitBox06x2 = temp1x;
        }
        if (P1hb_HitBox06x1 < 0) { P1hb_HitBox06x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox06x1 != +5555 && P1_HitBox06y1 != +5555 && P1_HitBox06x2 != +5555 &&
            P1_HitBox06y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox06x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox06x1 + (P1hb_HitBox06x2 - P1hb_HitBox06x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox06y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox06y1 + (P1hb_HitBox06y2 - P1hb_HitBox06y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 6;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 7) {
        //7//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox07x1;
        temp1y = P1hb_HitBox07y1;
        temp2x = P1hb_HitBox07x2;
        temp2y = P1hb_HitBox07y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox07x1 = temp1x;
            P1hb_HitBox07x2 = temp2x;
        } else {
            P1hb_HitBox07x1 = temp2x;
            P1hb_HitBox07x2 = temp1x;
        }
        if (P1hb_HitBox07x1 < 0) { P1hb_HitBox07x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox07x1 != +5555 && P1_HitBox07y1 != +5555 && P1_HitBox07x2 != +5555 &&
            P1_HitBox07y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox07x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox07x1 + (P1hb_HitBox07x2 - P1hb_HitBox07x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox07y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox07y1 + (P1hb_HitBox07y2 - P1hb_HitBox07y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 7;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 8) {
        //8//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox08x1;
        temp1y = P1hb_HitBox08y1;
        temp2x = P1hb_HitBox08x2;
        temp2y = P1hb_HitBox08y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox08x1 = temp1x;
            P1hb_HitBox08x2 = temp2x;
        } else {
            P1hb_HitBox08x1 = temp2x;
            P1hb_HitBox08x2 = temp1x;
        }
        if (P1hb_HitBox08x1 < 0) { P1hb_HitBox08x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox08x1 != +5555 && P1_HitBox08y1 != +5555 && P1_HitBox08x2 != +5555 &&
            P1_HitBox08y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox08x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox08x1 + (P1hb_HitBox08x2 - P1hb_HitBox08x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox08y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox08y1 + (P1hb_HitBox08y2 - P1hb_HitBox08y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 8;
            } else { colisaoxP2 = 0; }
        }
    }

    if (P1_HitBox_tot >= 9) {
        //9//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        temp1x = P1hb_HitBox09x1;
        temp1y = P1hb_HitBox09y1;
        temp2x = P1hb_HitBox09x2;
        temp2y = P1hb_HitBox09y2;
        if (temp1x <= temp2x) {
            P1hb_HitBox09x1 = temp1x;
            P1hb_HitBox09x2 = temp2x;
        } else {
            P1hb_HitBox09x1 = temp2x;
            P1hb_HitBox09x2 = temp1x;
        }
        if (P1hb_HitBox09x1 < 0) { P1hb_HitBox09x1 = 0; }
        //x1
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox01x1 != -5555 && P2_HurtBox01y1 != -5555 && P2_HurtBox01x2 != -5555 &&
            P2_HurtBox01y2 != -5555) {
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
            if ((P2hb_HurtBox01x1 + (P2hb_HurtBox01x2 - P2hb_HurtBox01x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox01x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox01y1 + (P2hb_HurtBox01y2 - P2hb_HurtBox01y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox01y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x2
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox02x1 != -5555 && P2_HurtBox02y1 != -5555 && P2_HurtBox02x2 != -5555 &&
            P2_HurtBox02y2 != -5555) {
            temp1x = P2hb_HurtBox02x1;
            temp1y = P2hb_HurtBox02y1;
            temp2x = P2hb_HurtBox02x2;
            temp2y = P2hb_HurtBox02y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox02x1 = temp1x;
                P2hb_HurtBox02x2 = temp2x;
            } else {
                P2hb_HurtBox02x1 = temp2x;
                P2hb_HurtBox02x2 = temp1x;
            }
            if (P2hb_HurtBox02x1 < 0) { P2hb_HurtBox02x1 = 0; }
            if ((P2hb_HurtBox02x1 + (P2hb_HurtBox02x2 - P2hb_HurtBox02x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox02x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox02y1 + (P2hb_HurtBox02y2 - P2hb_HurtBox02y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox02y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x3
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox03x1 != -5555 && P2_HurtBox03y1 != -5555 && P2_HurtBox03x2 != -5555 &&
            P2_HurtBox03y2 != -5555) {
            temp1x = P2hb_HurtBox03x1;
            temp1y = P2hb_HurtBox03y1;
            temp2x = P2hb_HurtBox03x2;
            temp2y = P2hb_HurtBox03y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox03x1 = temp1x;
                P2hb_HurtBox03x2 = temp2x;
            } else {
                P2hb_HurtBox03x1 = temp2x;
                P2hb_HurtBox03x2 = temp1x;
            }
            if (P2hb_HurtBox03x1 < 0) { P2hb_HurtBox03x1 = 0; }
            if ((P2hb_HurtBox03x1 + (P2hb_HurtBox03x2 - P2hb_HurtBox03x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox03x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox03y1 + (P2hb_HurtBox03y2 - P2hb_HurtBox03y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox03y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x4
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox04x1 != -5555 && P2_HurtBox04y1 != -5555 && P2_HurtBox04x2 != -5555 &&
            P2_HurtBox04y2 != -5555) {
            temp1x = P2hb_HurtBox04x1;
            temp1y = P2hb_HurtBox04y1;
            temp2x = P2hb_HurtBox04x2;
            temp2y = P2hb_HurtBox04y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox04x1 = temp1x;
                P2hb_HurtBox04x2 = temp2x;
            } else {
                P2hb_HurtBox04x1 = temp2x;
                P2hb_HurtBox04x2 = temp1x;
            }
            if (P2hb_HurtBox04x1 < 0) { P2hb_HurtBox04x1 = 0; }
            if ((P2hb_HurtBox04x1 + (P2hb_HurtBox04x2 - P2hb_HurtBox04x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox04x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox04y1 + (P2hb_HurtBox04y2 - P2hb_HurtBox04y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox04y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x5
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox05x1 != -5555 && P2_HurtBox05y1 != -5555 && P2_HurtBox05x2 != -5555 &&
            P2_HurtBox05y2 != -5555) {
            temp1x = P2hb_HurtBox05x1;
            temp1y = P2hb_HurtBox05y1;
            temp2x = P2hb_HurtBox05x2;
            temp2y = P2hb_HurtBox05y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox05x1 = temp1x;
                P2hb_HurtBox05x2 = temp2x;
            } else {
                P2hb_HurtBox05x1 = temp2x;
                P2hb_HurtBox05x2 = temp1x;
            }
            if (P2hb_HurtBox05x1 < 0) { P2hb_HurtBox05x1 = 0; }
            if ((P2hb_HurtBox05x1 + (P2hb_HurtBox05x2 - P2hb_HurtBox05x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox05x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox05y1 + (P2hb_HurtBox05y2 - P2hb_HurtBox05y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox05y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x6
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox06x1 != -5555 && P2_HurtBox06y1 != -5555 && P2_HurtBox06x2 != -5555 &&
            P2_HurtBox06y2 != -5555) {
            temp1x = P2hb_HurtBox06x1;
            temp1y = P2hb_HurtBox06y1;
            temp2x = P2hb_HurtBox06x2;
            temp2y = P2hb_HurtBox06y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox06x1 = temp1x;
                P2hb_HurtBox06x2 = temp2x;
            } else {
                P2hb_HurtBox06x1 = temp2x;
                P2hb_HurtBox06x2 = temp1x;
            }
            if (P2hb_HurtBox06x1 < 0) { P2hb_HurtBox06x1 = 0; }
            if ((P2hb_HurtBox06x1 + (P2hb_HurtBox06x2 - P2hb_HurtBox06x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox06x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox06y1 + (P2hb_HurtBox06y2 - P2hb_HurtBox06y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox06y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x7
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox07x1 != -5555 && P2_HurtBox07y1 != -5555 && P2_HurtBox07x2 != -5555 &&
            P2_HurtBox07y2 != -5555) {
            temp1x = P2hb_HurtBox07x1;
            temp1y = P2hb_HurtBox07y1;
            temp2x = P2hb_HurtBox07x2;
            temp2y = P2hb_HurtBox07y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox07x1 = temp1x;
                P2hb_HurtBox07x2 = temp2x;
            } else {
                P2hb_HurtBox07x1 = temp2x;
                P2hb_HurtBox07x2 = temp1x;
            }
            if (P2hb_HurtBox07x1 < 0) { P2hb_HurtBox07x1 = 0; }
            if ((P2hb_HurtBox07x1 + (P2hb_HurtBox07x2 - P2hb_HurtBox07x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox07x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox07y1 + (P2hb_HurtBox07y2 - P2hb_HurtBox07y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox07y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x8
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox08x1 != -5555 && P2_HurtBox08y1 != -5555 && P2_HurtBox08x2 != -5555 &&
            P2_HurtBox08y2 != -5555) {
            temp1x = P2hb_HurtBox08x1;
            temp1y = P2hb_HurtBox08y1;
            temp2x = P2hb_HurtBox08x2;
            temp2y = P2hb_HurtBox08y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox08x1 = temp1x;
                P2hb_HurtBox08x2 = temp2x;
            } else {
                P2hb_HurtBox08x1 = temp2x;
                P2hb_HurtBox08x2 = temp1x;
            }
            if (P2hb_HurtBox08x1 < 0) { P2hb_HurtBox08x1 = 0; }
            if ((P2hb_HurtBox08x1 + (P2hb_HurtBox08x2 - P2hb_HurtBox08x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox08x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox08y1 + (P2hb_HurtBox08y2 - P2hb_HurtBox08y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox08y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
        //x9
        if (colisaoxP2 == 0 && P1_HitBox09x1 != +5555 && P1_HitBox09y1 != +5555 && P1_HitBox09x2 != +5555 &&
            P1_HitBox09y2 != +5555 && P2_HurtBox09x1 != -5555 && P2_HurtBox09y1 != -5555 && P2_HurtBox09x2 != -5555 &&
            P2_HurtBox09y2 != -5555) {
            temp1x = P2hb_HurtBox09x1;
            temp1y = P2hb_HurtBox09y1;
            temp2x = P2hb_HurtBox09x2;
            temp2y = P2hb_HurtBox09y2;
            if (temp1x <= temp2x) {
                P2hb_HurtBox09x1 = temp1x;
                P2hb_HurtBox09x2 = temp2x;
            } else {
                P2hb_HurtBox09x1 = temp2x;
                P2hb_HurtBox09x2 = temp1x;
            }
            if (P2hb_HurtBox09x1 < 0) { P2hb_HurtBox09x1 = 0; }
            if ((P2hb_HurtBox09x1 + (P2hb_HurtBox09x2 - P2hb_HurtBox09x1) > P1hb_HitBox09x1) && (
                    P2hb_HurtBox09x1 < P1hb_HitBox09x1 + (P1hb_HitBox09x2 - P1hb_HitBox09x1)) &&
                (P2hb_HurtBox09y1 + (P2hb_HurtBox09y2 - P2hb_HurtBox09y1) > P1hb_HitBox09y1) && (
                    P2hb_HurtBox09y1 < P1hb_HitBox09y1 + (P1hb_HitBox09y2 - P1hb_HitBox09y1))) {
                colisaoxP2 = 1;
                alturadohitp1 = 9;
            } else { colisaoxP2 = 0; }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // HIT! houve colisao, o golpe acertou ----------------------------------------------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //aumenta barra de Special
    if (colisaoxP1 == 1 && AHitP2 == 1) {
        P[2].Special += P[2].SpecialChange;
        P[1].EnergyRedBarSleep = 60;
    }
    if (colisaoxP2 == 1 && AHitP1 == 1) {
        P[1].Special += P[1].SpecialChange;
        P[2].EnergyRedBarSleep = 60;
    }

    //Calcula x e y dos hits
    if (colisaoxP1 == 1) {
        if (alturadohitp2 == 1) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox01x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox01y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox01y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 2) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox02x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox02y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox02y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 3) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox03x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox03y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox03y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 4) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox04x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox04y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox04y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 5) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox05x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox05y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox05y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 6) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox06x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox06y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox06y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 7) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox07x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox07y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox07y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 8) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox08x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox08y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox08y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp2 == 9) {
            P2_Hit_x = (P[2].x * 2) + (P[2].Lado * P2_HitBox09x2) * 2;
            int y1 = ((P[2].y * 2) + P2_HitBox09y1 * 2);
            int y2 = ((P[2].y * 2) + P2_HitBox09y2 * 2);
            P2_Hit_y = ((y1 - y2) / 2) + y2;
        }
    }
    if (colisaoxP2 == 1) {
        if (alturadohitp1 == 1) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox01x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox01y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox01y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 2) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox02x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox02y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox02y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 3) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox03x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox03y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox03y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 4) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox04x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox04y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox04y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 5) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox05x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox05y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox05y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 6) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox06x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox06y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox06y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 7) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox07x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox07y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox07y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 8) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox08x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox08y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox08y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
        if (alturadohitp1 == 9) {
            P1_Hit_x = (P[1].x * 2) + (P[1].Lado * P1_HitBox09x2) * 2;
            int y1 = ((P[1].y * 2) + P1_HitBox09y1 * 2);
            int y2 = ((P[1].y * 2) + P1_HitBox09y2 * 2);
            P1_Hit_y = ((y1 - y2) / 2) + y2;
        }
    }

    //if P1_HurtBoxNum==0 { colisaoxP1=0; }
    //if P2_HitBoxNum==0 { colisaoxP1=0; }
}

//Aplicar HIT
void Aplicar_HIT() {
    ///HIT!!!

    MomentoDoP1 = 0;
    MomentoDoP2 = 0;

    //ForcaDoGolpeP1=0;
    //ForcaDoGolpeP2=0;
    //Ao nao zerar a ForcaDoGolpe, essa variavel acaba guardando a forca do ultimo golpe dado

    if (
        P[1].State == 101 || P[1].State == 104 ||
        P[1].State == 111 || P[1].State == 114 ||
        P[1].State == 151 || P[1].State == 154 ||
        P[1].State == 201 || P[1].State == 204 ||
        P[1].State == 211 || P[1].State == 214 ||
        P[1].State == 221 || P[1].State == 224 ||
        P[1].State == 301 || P[1].State == 304 ||
        P[1].State == 311 || P[1].State == 314 ||
        P[1].State == 321 || P[1].State == 324 ||
        P[1].State == 411 || P[1].State == 414 ||
        P[1].State == 421 || P[1].State == 424) { ForcaDoGolpeP1 = 1; }

    if (
        P[1].State == 102 || P[1].State == 105 ||
        P[1].State == 112 || P[1].State == 115 ||
        P[1].State == 152 || P[1].State == 155 ||
        P[1].State == 202 || P[1].State == 205 ||
        P[1].State == 212 || P[1].State == 215 ||
        P[1].State == 222 || P[1].State == 225 ||
        P[1].State == 302 || P[1].State == 305 ||
        P[1].State == 312 || P[1].State == 315 ||
        P[1].State == 322 || P[1].State == 325 ||
        P[1].State == 412 || P[1].State == 415 ||
        P[1].State == 422 || P[1].State == 425) { ForcaDoGolpeP1 = 2; }

    if (
        P[1].State == 103 || P[1].State == 106 ||
        P[1].State == 113 || P[1].State == 116 ||
        P[1].State == 153 || P[1].State == 156 ||
        P[1].State == 203 || P[1].State == 206 ||
        P[1].State == 213 || P[1].State == 216 ||
        P[1].State == 223 || P[1].State == 226 ||
        P[1].State == 303 || P[1].State == 306 ||
        P[1].State == 313 || P[1].State == 316 ||
        P[1].State == 323 || P[1].State == 326 ||
        P[1].State == 413 || P[1].State == 416 ||
        P[1].State == 423 || P[1].State == 426) { ForcaDoGolpeP1 = 3; }

    if (colisaoxP2 == 1 && AHitP1 == 1)New_HitBox(Qtde_HitBox + 1);
    if (colisaoxP1 == 1 && AHitP2 == 1)New_HitBox(Qtde_HitBox + 1);

    if (
        P[1].State == 100 ||
        P[1].State == 101 || P[1].State == 102 || P[1].State == 103 || P[1].State == 104 || P[1].State == 105 || P[1].
        State == 106 ||
        P[1].State == 151 || P[1].State == 152 || P[1].State == 153 || P[1].State == 154 || P[1].State == 155 || P[1].
        State == 156 ||
        P[1].State == 111 || P[1].State == 112 || P[1].State == 113 || P[1].State == 114 || P[1].State == 115 || P[1].
        State == 116 ||
        P[1].State == 411 || P[1].State == 412 || P[1].State == 413 || P[1].State == 414 || P[1].State == 415 || P[1].
        State == 416 ||
        P[1].State == 421 || P[1].State == 422 || P[1].State == 423 || P[1].State == 424 || P[1].State == 425 || P[1].
        State == 426 ||
        P[1].State == 410 || P[1].State == 420 || P[1].State == 602 || P[1].State == 603 || P[1].State == 604 || P[1].
        State == 605 ||
        P[1].State == 606 || P[1].State == 607) { MomentoDoP1 = 1; } //De pe

    if (
        P[1].State == 200 ||
        P[1].State == 201 || P[1].State == 202 || P[1].State == 203 || P[1].State == 204 || P[1].State == 205 || P[1].
        State == 206 ||
        P[1].State == 211 || P[1].State == 212 || P[1].State == 213 || P[1].State == 214 || P[1].State == 215 || P[1].
        State == 216 ||
        P[1].State == 221 || P[1].State == 222 || P[1].State == 223 || P[1].State == 224 || P[1].State == 225 || P[1].
        State == 226 ||
        P[1].State == 601 || P[1].State == 608) { MomentoDoP1 = 2; } //Abaixado

    if (
        P[1].State == 300 || P[1].State == 310 || P[1].State == 320 ||
        P[1].State == 301 || P[1].State == 302 || P[1].State == 303 || P[1].State == 304 || P[1].State == 305 || P[1].
        State == 306 ||
        P[1].State == 311 || P[1].State == 312 || P[1].State == 313 || P[1].State == 314 || P[1].State == 315 || P[1].
        State == 316 ||
        P[1].State == 321 || P[1].State == 322 || P[1].State == 323 || P[1].State == 324 || P[1].State == 325 || P[1].
        State == 326) { MomentoDoP1 = 3; } //Pulando

    if (P[1].State == 501 || P[1].State == 502 || P[1].State == 503) { MomentoDoP1 = 51; } //Hurt em pe
    if (P[1].State == 511 || P[1].State == 512 || P[1].State == 513) { MomentoDoP1 = 51; } //Hurt em pe
    if (P[1].State == 504 || P[1].State == 505 || P[1].State == 506) { MomentoDoP1 = 52; } //Hurt abaixado
    if (P[1].State == 507 || P[1].State == 508 || P[1].State == 509) { MomentoDoP1 = 53; } //Hurt em pe

    if (P[1].State == 250) { MomentoDoP1 = 9; } //Defesa Abaixado
    if (P[1].State == 450) { MomentoDoP1 = 9; } //Defesa em Pe

    if (
        P[2].State == 101 || P[2].State == 104 ||
        P[2].State == 111 || P[2].State == 114 ||
        P[2].State == 151 || P[2].State == 154 ||
        P[2].State == 201 || P[2].State == 204 ||
        P[2].State == 211 || P[2].State == 214 ||
        P[2].State == 221 || P[2].State == 224 ||
        P[2].State == 301 || P[2].State == 304 ||
        P[2].State == 311 || P[2].State == 314 ||
        P[2].State == 321 || P[2].State == 324 ||
        P[2].State == 411 || P[2].State == 414 ||
        P[2].State == 421 || P[2].State == 424) { ForcaDoGolpeP2 = 1; }

    if (
        P[2].State == 102 || P[2].State == 105 ||
        P[2].State == 112 || P[2].State == 115 ||
        P[2].State == 152 || P[2].State == 155 ||
        P[2].State == 202 || P[2].State == 205 ||
        P[2].State == 212 || P[2].State == 215 ||
        P[2].State == 222 || P[2].State == 225 ||
        P[2].State == 302 || P[2].State == 305 ||
        P[2].State == 312 || P[2].State == 315 ||
        P[2].State == 322 || P[2].State == 325 ||
        P[2].State == 412 || P[2].State == 415 ||
        P[2].State == 422 || P[2].State == 425) { ForcaDoGolpeP2 = 2; }

    if (
        P[2].State == 103 || P[2].State == 106 ||
        P[2].State == 113 || P[2].State == 116 ||
        P[2].State == 153 || P[2].State == 156 ||
        P[2].State == 203 || P[2].State == 206 ||
        P[2].State == 213 || P[2].State == 216 ||
        P[2].State == 223 || P[2].State == 226 ||
        P[2].State == 303 || P[2].State == 306 ||
        P[2].State == 313 || P[2].State == 316 ||
        P[2].State == 323 || P[2].State == 326 ||
        P[2].State == 413 || P[2].State == 416 ||
        P[2].State == 423 || P[2].State == 426) { ForcaDoGolpeP2 = 3; }

    if (
        P[2].State == 100 ||
        P[2].State == 101 || P[2].State == 102 || P[2].State == 103 || P[2].State == 104 || P[2].State == 105 || P[2].
        State == 106 ||
        P[2].State == 151 || P[2].State == 152 || P[2].State == 153 || P[2].State == 154 || P[2].State == 155 || P[2].
        State == 156 ||
        P[2].State == 111 || P[2].State == 112 || P[2].State == 113 || P[2].State == 114 || P[2].State == 115 || P[2].
        State == 116 ||
        P[2].State == 411 || P[2].State == 412 || P[2].State == 413 || P[2].State == 414 || P[2].State == 415 || P[2].
        State == 416 ||
        P[2].State == 421 || P[2].State == 422 || P[2].State == 423 || P[2].State == 424 || P[2].State == 425 || P[2].
        State == 426 ||
        P[2].State == 410 || P[2].State == 420 || P[2].State == 602 || P[2].State == 603 || P[2].State == 604 || P[2].
        State == 605 ||
        P[2].State == 606 || P[2].State == 607) { MomentoDoP2 = 1; } //De Pe

    if (
        P[2].State == 200 ||
        P[2].State == 201 || P[2].State == 202 || P[2].State == 203 || P[2].State == 204 || P[2].State == 205 || P[2].
        State == 206 ||
        P[2].State == 211 || P[2].State == 212 || P[2].State == 213 || P[2].State == 214 || P[2].State == 215 || P[2].
        State == 216 ||
        P[2].State == 221 || P[2].State == 222 || P[2].State == 223 || P[2].State == 224 || P[2].State == 225 || P[2].
        State == 226 ||
        P[2].State == 601 || P[2].State == 608) { MomentoDoP2 = 2; } //Abaixado

    if (
        P[2].State == 300 || P[2].State == 310 || P[2].State == 320 ||
        P[2].State == 301 || P[2].State == 302 || P[2].State == 303 || P[2].State == 304 || P[2].State == 305 || P[2].
        State == 306 ||
        P[2].State == 311 || P[2].State == 312 || P[2].State == 313 || P[2].State == 314 || P[2].State == 315 || P[2].
        State == 316 ||
        P[2].State == 321 || P[2].State == 322 || P[2].State == 323 || P[2].State == 324 || P[2].State == 325 || P[2].
        State == 326) { MomentoDoP2 = 3; } //Pulando

    if (P[2].State == 501 || P[2].State == 502 || P[2].State == 503) { MomentoDoP2 = 51; } //Hurt em pe
    if (P[2].State == 511 || P[2].State == 512 || P[2].State == 513) { MomentoDoP2 = 51; } //Hurt em pe
    if (P[2].State == 504 || P[2].State == 505 || P[2].State == 506) { MomentoDoP2 = 52; } //Hurt abaixado
    if (P[2].State == 507 || P[2].State == 508 || P[2].State == 509) { MomentoDoP2 = 53; } //Hurt no ar

    if (P[2].State == 250) { MomentoDoP2 = 9; } //Defesa Abaixado
    if (P[2].State == 450) { MomentoDoP2 = 9; } //Defesa em Pe

    //importante!
    //HitPause Padrao
    HitPause1 = 15;
    HitPause2 = 15;
    HitPause3 = 15; //<-hitpause
    //damage
    if (P[1].ChangeDamage == 0) {
        P1_DMG1 = 50;
        P1_DMG2 = 100;
        P1_DMG3 = 150;
    } else {
        P1_DMG1 = P[1].ChangeDamage;
        P1_DMG2 = P[1].ChangeDamage;
        P1_DMG3 = P[1].ChangeDamage;
    }
    if (P[2].ChangeDamage == 0) {
        P2_DMG1 = 50;
        P2_DMG2 = 100;
        P2_DMG3 = 150;
    } else {
        P2_DMG1 = P[2].ChangeDamage;
        P2_DMG2 = P[2].ChangeDamage;
        P2_DMG3 = P[2].ChangeDamage;
    }

    char P1_Caminho[99];
    char P2_Caminho[99];

    //P2 HitType
    int line = 0;
    for (int indx = 0; indx <= 500; indx++) {
        if (P[2].State == P[2].TableAtlas[indx][0]
            && P[2].IndexAnim == P[2].TableAtlas[indx][1]) {
            line = P[2].TableAtlas[indx][2];
        }
        if (line != 0) break;
    }
    if (P[2].TableAtlas[line][16] == 1) { strcpy(P[2].HitType_string, "Normal"); }
    if (P[2].TableAtlas[line][16] == 2) { strcpy(P[2].HitType_string, "Fall"); }
    if (P[2].TableAtlas[line][20] == 1) { strcpy(P[2].HitStack_string, "Single"); }
    if (P[2].TableAtlas[line][20] == 2) { strcpy(P[2].HitStack_string, "Multi"); }

    if (colisaoxP1 == 1 || colisaoxP1Fireball == 1) {
        //colisao contra P1 de uma fireball lançada pelo P2
        if (colisaoxP1Fireball == 1) {
            if (P[2].TotalDeFramesMov[702] > -1) {
                Fireball[2].State = 702;
                char P2_Caminho[99];
                sprintf(P2_Caminho, "data/chars/%s/char.ini", P[2].Name);
                set_config_file(P2_Caminho);
                Fireball[2].XAlign = get_config_int("702", "XAlign", 0);
                Fireball[2].YAlign = get_config_int("702", "YAlign", 0);
                Fireball[2].TotalFrames = P[2].TotalDeFramesMov[702];
                //Fireball[2].Ativa=0;
                Fireball[2].IndexAnim = 0; //dan
                Fireball[2].VSpeed = 0;
                Fireball[2].HSpeed = 0;
                colisaoxP1Fireball = 0;
                P2_Fireball_HitBox01x1 = +5555;
                P2_Fireball_HitBox01y1 = +5555;
                P2_Fireball_HitBox01x2 = +5555;
                P2_Fireball_HitBox01y2 = +5555;
            } else {
                colisaoxP1Fireball = 0;
                Fireball[2].Ativa = 0;
                Fireball[2].x = -999;
                Fireball[2].y = -999;
                P[2].QtdeMagias = 0;
            }
        }

        //FSM
        if (strcmp(P[2].HitType_string, "Fall") == 0 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]);
            P1HitPause = HitPause3; //teste
            P2HitPause = HitPause3;
            if (ForcaDoGolpeP2 == 1) { P[1].Energy -= P2_DMG1; }
            if (ForcaDoGolpeP2 == 2) { P[1].Energy -= P2_DMG2; }
            if (ForcaDoGolpeP2 == 3) { P[1].Energy -= P2_DMG3; }
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 1 && MomentoDoP2 == 3 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 511, 0, P[1].TotalDeFramesMov[511]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 1 && MomentoDoP2 == 3 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 512, 0, P[1].TotalDeFramesMov[512]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 1 && MomentoDoP2 == 3 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 513, 0, P[1].TotalDeFramesMov[513]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 1 && MomentoDoP2 == 2 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 511, 0, P[1].TotalDeFramesMov[511]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 1 && MomentoDoP2 == 2 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 512, 0, P[1].TotalDeFramesMov[512]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 1 && MomentoDoP2 == 2 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 513, 0, P[1].TotalDeFramesMov[513]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 1 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 501, 0, P[1].TotalDeFramesMov[501]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 1 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 502, 0, P[1].TotalDeFramesMov[502]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 1 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 503, 0, P[1].TotalDeFramesMov[503]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 2 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 504, 0, P[1].TotalDeFramesMov[504]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 2 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 505, 0, P[1].TotalDeFramesMov[505]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 2 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 506, 0, P[1].TotalDeFramesMov[506]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        //reversao aerea do P1 Mov 507
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 3 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 507, 0, P[1].TotalDeFramesMov[507]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 3 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 507, 0, P[1].TotalDeFramesMov[507]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 3 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 507, 0, P[1].TotalDeFramesMov[507]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        //fim das reversoes
        if (ForcaDoGolpeP2 == 51 && MomentoDoP1 == 1 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 501, 0, P[1].TotalDeFramesMov[501]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 51 && MomentoDoP1 == 1 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 502, 0, P[1].TotalDeFramesMov[502]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 51 && MomentoDoP1 == 1 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 503, 0, P[1].TotalDeFramesMov[503]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 51 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 501, 0, P[1].TotalDeFramesMov[501]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 51 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 502, 0, P[1].TotalDeFramesMov[502]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 51 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 503, 0, P[1].TotalDeFramesMov[503]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 52 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 504, 0, P[1].TotalDeFramesMov[504]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 52 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 505, 0, P[1].TotalDeFramesMov[505]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 52 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 506, 0, P[1].TotalDeFramesMov[506]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 53 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]);
            P2HitPause = HitPause1;
            P[1].Energy -= P2_DMG1;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 53 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]);
            P2HitPause = HitPause2;
            P[1].Energy -= P2_DMG2;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 53 && AHitP2 == 1) {
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 550, 0, P[1].TotalDeFramesMov[550]);
            P2HitPause = HitPause3;
            P[1].Energy -= P2_DMG3;
            P2HitOn = P[2].IndexAnim;
        }
        //defesa
        if (ForcaDoGolpeP2 == 1 && MomentoDoP1 == 9 && AHitP2 == 1) {
            AHitP2 = 0;
            P2HitPause = HitPause1;
            P[1].Energy -= 0;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 2 && MomentoDoP1 == 9 && AHitP2 == 1) {
            AHitP2 = 0;
            P2HitPause = HitPause2;
            P[1].Energy -= 0;
            P2HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP2 == 3 && MomentoDoP1 == 9 && AHitP2 == 1) {
            AHitP2 = 0;
            P2HitPause = HitPause3;
            P[1].Energy -= 0;
            P2HitOn = P[2].IndexAnim;
        }
        //derrota por KO
        if (P[1].Energy <= 0) {
            rest(HitPauseKO);
            EndRoundSlowDown = 1;
            AHitP2 = 0;
            P[1].StartFrame = frame_count;
            PLAYER_STATE(1, 570, 0, P[1].TotalDeFramesMov[570]);
            P2HitPause = HitPause3;
            P[1].Energy = 0;
            P2HitOn = P[2].IndexAnim;
        }
    }

    //P1 HitType
    line = 0;
    for (int indx = 0; indx <= 500; indx++) {
        if (P[1].State == P[1].TableAtlas[indx][0]
            && P[1].IndexAnim == P[1].TableAtlas[indx][1]) {
            line = P[1].TableAtlas[indx][2];
        }
        if (line != 0) break;
    }
    if (P[1].TableAtlas[line][16] == 1) { strcpy(P[1].HitType_string, "Normal"); }
    if (P[1].TableAtlas[line][16] == 2) { strcpy(P[1].HitType_string, "Fall"); }
    if (P[1].TableAtlas[line][20] == 1) { strcpy(P[1].HitStack_string, "Single"); }
    if (P[1].TableAtlas[line][20] == 2) { strcpy(P[1].HitStack_string, "Multi"); }

    if (colisaoxP2 == 1 || colisaoxP2Fireball == 1) {
        //colisao contra P2 de uma fireball lançada pelo P1
        if (colisaoxP2Fireball == 1) {
            if (P[1].TotalDeFramesMov[702] > -1) {
                Fireball[1].State = 702;
                char P1_Caminho[99];
                sprintf(P1_Caminho, "data/chars/%s/char.ini", P[1].Name);
                set_config_file(P1_Caminho);
                Fireball[1].XAlign = get_config_int("702", "XAlign", 0);
                Fireball[1].YAlign = get_config_int("702", "YAlign", 0);
                Fireball[1].TotalFrames = P[1].TotalDeFramesMov[702];
                //Fireball[1].Ativa=0;
                Fireball[1].IndexAnim = 0; //dan
                Fireball[1].VSpeed = 0;
                Fireball[1].HSpeed = 0;
                colisaoxP2Fireball = 0;
                P1_Fireball_HitBox01x1 = -5555;
                P1_Fireball_HitBox01y1 = -5555;
                P1_Fireball_HitBox01x2 = -5555;
                P1_Fireball_HitBox01y2 = -5555;
            } else {
                colisaoxP2Fireball = 0;
                Fireball[1].Ativa = 0;
                Fireball[1].x = -999;
                Fireball[1].y = -999;
                P[1].QtdeMagias = 0;
            }
        }

        //FSM
        if (strcmp(P[1].HitType_string, "Fall") == 0 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]);
            P2HitPause = HitPause3; //teste
            P1HitPause = HitPause3;
            if (ForcaDoGolpeP1 == 1) { P[2].Energy -= P1_DMG1; }
            if (ForcaDoGolpeP1 == 2) { P[2].Energy -= P1_DMG2; }
            if (ForcaDoGolpeP1 == 3) { P[2].Energy -= P1_DMG3; }
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 1 && MomentoDoP1 == 3 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 511, 0, P[2].TotalDeFramesMov[511]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 1 && MomentoDoP1 == 3 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 512, 0, P[2].TotalDeFramesMov[512]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 1 && MomentoDoP1 == 3 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 513, 0, P[2].TotalDeFramesMov[513]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 1 && MomentoDoP1 == 2 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 511, 0, P[2].TotalDeFramesMov[511]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 1 && MomentoDoP1 == 2 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 512, 0, P[2].TotalDeFramesMov[512]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 1 && MomentoDoP1 == 2 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 513, 0, P[2].TotalDeFramesMov[513]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 1 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 501, 0, P[2].TotalDeFramesMov[501]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 1 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 502, 0, P[2].TotalDeFramesMov[502]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 1 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 503, 0, P[2].TotalDeFramesMov[503]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 2 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 504, 0, P[2].TotalDeFramesMov[504]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 2 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 505, 0, P[2].TotalDeFramesMov[505]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 2 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 506, 0, P[2].TotalDeFramesMov[506]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        //reversao aerea do P2 Mov 507
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 3 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 507, 0, P[2].TotalDeFramesMov[507]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 3 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 507, 0, P[2].TotalDeFramesMov[507]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 3 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 507, 0, P[2].TotalDeFramesMov[507]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        //fim das reversoes
        if (ForcaDoGolpeP1 == 51 && MomentoDoP2 == 1 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 501, 0, P[2].TotalDeFramesMov[501]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 51 && MomentoDoP2 == 1 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 502, 0, P[2].TotalDeFramesMov[502]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 51 && MomentoDoP2 == 1 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 503, 0, P[2].TotalDeFramesMov[503]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 51 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 501, 0, P[2].TotalDeFramesMov[501]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 51 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 502, 0, P[2].TotalDeFramesMov[502]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 51 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 503, 0, P[2].TotalDeFramesMov[503]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 52 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 504, 0, P[2].TotalDeFramesMov[504]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 52 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 505, 0, P[2].TotalDeFramesMov[505]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 52 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 506, 0, P[2].TotalDeFramesMov[506]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 53 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]);
            P1HitPause = HitPause1;
            P[2].Energy -= P1_DMG1;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 53 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]);
            P1HitPause = HitPause2;
            P[2].Energy -= P1_DMG2;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 53 && AHitP1 == 1) {
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 550, 0, P[2].TotalDeFramesMov[550]);
            P1HitPause = HitPause3;
            P[2].Energy -= P1_DMG3;
            P1HitOn = P[2].IndexAnim;
        }
        //defesa
        if (ForcaDoGolpeP1 == 1 && MomentoDoP2 == 9 && AHitP1 == 1) {
            AHitP1 = 0;
            P1HitPause = HitPause1;
            P[2].Energy -= 0;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 2 && MomentoDoP2 == 9 && AHitP1 == 1) {
            AHitP1 = 0;
            P1HitPause = HitPause2;
            P[2].Energy -= 0;
            P1HitOn = P[2].IndexAnim;
        }
        if (ForcaDoGolpeP1 == 3 && MomentoDoP2 == 9 && AHitP1 == 1) {
            AHitP1 = 0;
            P1HitPause = HitPause3;
            P[2].Energy -= 0;
            P1HitOn = P[2].IndexAnim;
        }
        //derrota por KO
        if (P[2].Energy <= 0) {
            rest(HitPauseKO);
            EndRoundSlowDown = 1;
            AHitP1 = 0;
            P[2].StartFrame = frame_count;
            PLAYER_STATE(2, 570, 0, P[2].TotalDeFramesMov[570]);
            P1HitPause = HitPause3;
            P[2].Energy = 0;
            P1HitOn = P[2].IndexAnim;
        }
    }

    //Chacoalha os personagens após o Hit, e os desloca
    if (P1HitPause > 0 || P2HitPause > 0) {
        ShakeDist = ShakeDist * -1;
        int AcelFraca = 1.8;
        int AcelMedia = 2.0;
        int AcelForte = 2.2;
        if (P1HitPause > 0) {
            P1HitPause--;
            if (P1HitPause == 1) {
                if (ForcaDoGolpeP1 == 1) {
                    P[2].Hspeed = AcelFraca * P[1].Lado;
                    P[2].Friction = 5;
                }
                if (ForcaDoGolpeP1 == 2) {
                    P[2].Hspeed = AcelMedia * P[1].Lado;
                    P[2].Friction = 5;
                }
                if (ForcaDoGolpeP1 == 3) {
                    P[2].Hspeed = AcelForte * P[1].Lado;
                    P[2].Friction = 5;
                }
            }
        }
        if (P2HitPause > 0) {
            P2HitPause--;
            if (P2HitPause == 1) {
                if (ForcaDoGolpeP2 == 1) {
                    P[1].Hspeed = AcelFraca * P[2].Lado;
                    P[1].Friction = 5;
                }
                if (ForcaDoGolpeP2 == 2) {
                    P[1].Hspeed = AcelMedia * P[2].Lado;
                    P[1].Friction = 5;
                }
                if (ForcaDoGolpeP2 == 3) {
                    P[1].Hspeed = AcelForte * P[2].Lado;
                    P[1].Friction = 5;
                }
            }
        }
    }
}
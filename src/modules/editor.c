#include "editor.h"

////////////////////////////////////////////////////////////////////////////////
// EDITOR FUNCTIONS
// Character editor functions for HAMOOPI
////////////////////////////////////////////////////////////////////////////////

void ED_save_charini() {
    if (ED_State < 700) {
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
        set_config_file(ED_Caminho);
        char ED_State_s[3];
        sprintf(ED_State_s, "%i", ED_State);
        if (ED_TotalFrames >= 0) { set_config_int(ED_State_s, "FrameTime_00", ED_FrameTime_00+1); }
        if (ED_TotalFrames >= 1) { set_config_int(ED_State_s, "FrameTime_01", ED_FrameTime_01+1); }
        if (ED_TotalFrames >= 2) { set_config_int(ED_State_s, "FrameTime_02", ED_FrameTime_02+1); }
        if (ED_TotalFrames >= 3) { set_config_int(ED_State_s, "FrameTime_03", ED_FrameTime_03+1); }
        if (ED_TotalFrames >= 4) { set_config_int(ED_State_s, "FrameTime_04", ED_FrameTime_04+1); }
        if (ED_TotalFrames >= 5) { set_config_int(ED_State_s, "FrameTime_05", ED_FrameTime_05+1); }
        if (ED_TotalFrames >= 6) { set_config_int(ED_State_s, "FrameTime_06", ED_FrameTime_06+1); }
        if (ED_TotalFrames >= 7) { set_config_int(ED_State_s, "FrameTime_07", ED_FrameTime_07+1); }
        if (ED_TotalFrames >= 8) { set_config_int(ED_State_s, "FrameTime_08", ED_FrameTime_08+1); }
        if (ED_TotalFrames >= 9) { set_config_int(ED_State_s, "FrameTime_09", ED_FrameTime_09+1); }
        if (ED_TotalFrames >= 10) { set_config_int(ED_State_s, "FrameTime_10", ED_FrameTime_10+1); }
        if (ED_TotalFrames >= 11) { set_config_int(ED_State_s, "FrameTime_11", ED_FrameTime_11+1); }
        if (ED_TotalFrames >= 12) { set_config_int(ED_State_s, "FrameTime_12", ED_FrameTime_12+1); }
        if (ED_TotalFrames >= 13) { set_config_int(ED_State_s, "FrameTime_13", ED_FrameTime_13+1); }
        if (ED_TotalFrames >= 14) { set_config_int(ED_State_s, "FrameTime_14", ED_FrameTime_14+1); }
        if (ED_TotalFrames >= 15) { set_config_int(ED_State_s, "FrameTime_15", ED_FrameTime_15+1); }
        if (ED_TotalFrames >= 16) { set_config_int(ED_State_s, "FrameTime_16", ED_FrameTime_16+1); }
        if (ED_TotalFrames >= 17) { set_config_int(ED_State_s, "FrameTime_17", ED_FrameTime_17+1); }
        if (ED_TotalFrames >= 18) { set_config_int(ED_State_s, "FrameTime_18", ED_FrameTime_18+1); }
        if (ED_TotalFrames >= 19) { set_config_int(ED_State_s, "FrameTime_19", ED_FrameTime_19+1); }
        if (ED_TotalFrames >= 20) { set_config_int(ED_State_s, "FrameTime_20", ED_FrameTime_20+1); }
        if (ED_TotalFrames >= 21) { set_config_int(ED_State_s, "FrameTime_21", ED_FrameTime_21+1); }
        if (ED_TotalFrames >= 22) { set_config_int(ED_State_s, "FrameTime_22", ED_FrameTime_22+1); }
        if (ED_TotalFrames >= 23) { set_config_int(ED_State_s, "FrameTime_23", ED_FrameTime_23+1); }
        if (ED_TotalFrames >= 24) { set_config_int(ED_State_s, "FrameTime_24", ED_FrameTime_24+1); }
        if (ED_TotalFrames >= 25) { set_config_int(ED_State_s, "FrameTime_25", ED_FrameTime_25+1); }
        if (ED_TotalFrames >= 26) { set_config_int(ED_State_s, "FrameTime_26", ED_FrameTime_26+1); }
        if (ED_TotalFrames >= 27) { set_config_int(ED_State_s, "FrameTime_27", ED_FrameTime_27+1); }
        if (ED_TotalFrames >= 28) { set_config_int(ED_State_s, "FrameTime_28", ED_FrameTime_28+1); }
        if (ED_TotalFrames >= 29) { set_config_int(ED_State_s, "FrameTime_29", ED_FrameTime_29+1); }
        set_config_int(ED_State_s, "XAlign", ED_XAlign);
        set_config_int(ED_State_s, "YAlign", ED_YAlign);
        ED_alertsave = 0;
        ED_ShowMsgSaving = 1;
    }

    if (ED_State >= 700 && ED_Special_Version == 1) {
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
        set_config_file(ED_Caminho);
        char ED_State_s[3];
        sprintf(ED_State_s, "%i", ED_State);
        if (ED_TotalFrames >= 0) { set_config_int(ED_State_s, "V1_FrameTime_00", ED_FrameTime_00+1); }
        if (ED_TotalFrames >= 1) { set_config_int(ED_State_s, "V1_FrameTime_01", ED_FrameTime_01+1); }
        if (ED_TotalFrames >= 2) { set_config_int(ED_State_s, "V1_FrameTime_02", ED_FrameTime_02+1); }
        if (ED_TotalFrames >= 3) { set_config_int(ED_State_s, "V1_FrameTime_03", ED_FrameTime_03+1); }
        if (ED_TotalFrames >= 4) { set_config_int(ED_State_s, "V1_FrameTime_04", ED_FrameTime_04+1); }
        if (ED_TotalFrames >= 5) { set_config_int(ED_State_s, "V1_FrameTime_05", ED_FrameTime_05+1); }
        if (ED_TotalFrames >= 6) { set_config_int(ED_State_s, "V1_FrameTime_06", ED_FrameTime_06+1); }
        if (ED_TotalFrames >= 7) { set_config_int(ED_State_s, "V1_FrameTime_07", ED_FrameTime_07+1); }
        if (ED_TotalFrames >= 8) { set_config_int(ED_State_s, "V1_FrameTime_08", ED_FrameTime_08+1); }
        if (ED_TotalFrames >= 9) { set_config_int(ED_State_s, "V1_FrameTime_09", ED_FrameTime_09+1); }
        if (ED_TotalFrames >= 10) { set_config_int(ED_State_s, "V1_FrameTime_10", ED_FrameTime_10+1); }
        if (ED_TotalFrames >= 11) { set_config_int(ED_State_s, "V1_FrameTime_11", ED_FrameTime_11+1); }
        if (ED_TotalFrames >= 12) { set_config_int(ED_State_s, "V1_FrameTime_12", ED_FrameTime_12+1); }
        if (ED_TotalFrames >= 13) { set_config_int(ED_State_s, "V1_FrameTime_13", ED_FrameTime_13+1); }
        if (ED_TotalFrames >= 14) { set_config_int(ED_State_s, "V1_FrameTime_14", ED_FrameTime_14+1); }
        if (ED_TotalFrames >= 15) { set_config_int(ED_State_s, "V1_FrameTime_15", ED_FrameTime_15+1); }
        if (ED_TotalFrames >= 16) { set_config_int(ED_State_s, "V1_FrameTime_16", ED_FrameTime_16+1); }
        if (ED_TotalFrames >= 17) { set_config_int(ED_State_s, "V1_FrameTime_17", ED_FrameTime_17+1); }
        if (ED_TotalFrames >= 18) { set_config_int(ED_State_s, "V1_FrameTime_18", ED_FrameTime_18+1); }
        if (ED_TotalFrames >= 19) { set_config_int(ED_State_s, "V1_FrameTime_19", ED_FrameTime_19+1); }
        if (ED_TotalFrames >= 20) { set_config_int(ED_State_s, "V1_FrameTime_20", ED_FrameTime_20+1); }
        if (ED_TotalFrames >= 21) { set_config_int(ED_State_s, "V1_FrameTime_21", ED_FrameTime_21+1); }
        if (ED_TotalFrames >= 22) { set_config_int(ED_State_s, "V1_FrameTime_22", ED_FrameTime_22+1); }
        if (ED_TotalFrames >= 23) { set_config_int(ED_State_s, "V1_FrameTime_23", ED_FrameTime_23+1); }
        if (ED_TotalFrames >= 24) { set_config_int(ED_State_s, "V1_FrameTime_24", ED_FrameTime_24+1); }
        if (ED_TotalFrames >= 25) { set_config_int(ED_State_s, "V1_FrameTime_25", ED_FrameTime_25+1); }
        if (ED_TotalFrames >= 26) { set_config_int(ED_State_s, "V1_FrameTime_26", ED_FrameTime_26+1); }
        if (ED_TotalFrames >= 27) { set_config_int(ED_State_s, "V1_FrameTime_27", ED_FrameTime_27+1); }
        if (ED_TotalFrames >= 28) { set_config_int(ED_State_s, "V1_FrameTime_28", ED_FrameTime_28+1); }
        if (ED_TotalFrames >= 29) { set_config_int(ED_State_s, "V1_FrameTime_29", ED_FrameTime_29+1); }
        set_config_int(ED_State_s, "XAlign", ED_XAlign);
        set_config_int(ED_State_s, "YAlign", ED_YAlign);
        ED_alertsave = 0;
        ED_ShowMsgSaving = 1;
    }

    if (ED_State >= 700 && ED_Special_Version == 2) {
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
        set_config_file(ED_Caminho);
        char ED_State_s[3];
        sprintf(ED_State_s, "%i", ED_State);
        if (ED_TotalFrames >= 0) { set_config_int(ED_State_s, "V2_FrameTime_00", ED_FrameTime_00+1); }
        if (ED_TotalFrames >= 1) { set_config_int(ED_State_s, "V2_FrameTime_01", ED_FrameTime_01+1); }
        if (ED_TotalFrames >= 2) { set_config_int(ED_State_s, "V2_FrameTime_02", ED_FrameTime_02+1); }
        if (ED_TotalFrames >= 3) { set_config_int(ED_State_s, "V2_FrameTime_03", ED_FrameTime_03+1); }
        if (ED_TotalFrames >= 4) { set_config_int(ED_State_s, "V2_FrameTime_04", ED_FrameTime_04+1); }
        if (ED_TotalFrames >= 5) { set_config_int(ED_State_s, "V2_FrameTime_05", ED_FrameTime_05+1); }
        if (ED_TotalFrames >= 6) { set_config_int(ED_State_s, "V2_FrameTime_06", ED_FrameTime_06+1); }
        if (ED_TotalFrames >= 7) { set_config_int(ED_State_s, "V2_FrameTime_07", ED_FrameTime_07+1); }
        if (ED_TotalFrames >= 8) { set_config_int(ED_State_s, "V2_FrameTime_08", ED_FrameTime_08+1); }
        if (ED_TotalFrames >= 9) { set_config_int(ED_State_s, "V2_FrameTime_09", ED_FrameTime_09+1); }
        if (ED_TotalFrames >= 10) { set_config_int(ED_State_s, "V2_FrameTime_10", ED_FrameTime_10+1); }
        if (ED_TotalFrames >= 11) { set_config_int(ED_State_s, "V2_FrameTime_11", ED_FrameTime_11+1); }
        if (ED_TotalFrames >= 12) { set_config_int(ED_State_s, "V2_FrameTime_12", ED_FrameTime_12+1); }
        if (ED_TotalFrames >= 13) { set_config_int(ED_State_s, "V2_FrameTime_13", ED_FrameTime_13+1); }
        if (ED_TotalFrames >= 14) { set_config_int(ED_State_s, "V2_FrameTime_14", ED_FrameTime_14+1); }
        if (ED_TotalFrames >= 15) { set_config_int(ED_State_s, "V2_FrameTime_15", ED_FrameTime_15+1); }
        if (ED_TotalFrames >= 16) { set_config_int(ED_State_s, "V2_FrameTime_16", ED_FrameTime_16+1); }
        if (ED_TotalFrames >= 17) { set_config_int(ED_State_s, "V2_FrameTime_17", ED_FrameTime_17+1); }
        if (ED_TotalFrames >= 18) { set_config_int(ED_State_s, "V2_FrameTime_18", ED_FrameTime_18+1); }
        if (ED_TotalFrames >= 19) { set_config_int(ED_State_s, "V2_FrameTime_19", ED_FrameTime_19+1); }
        if (ED_TotalFrames >= 20) { set_config_int(ED_State_s, "V2_FrameTime_20", ED_FrameTime_20+1); }
        if (ED_TotalFrames >= 21) { set_config_int(ED_State_s, "V2_FrameTime_21", ED_FrameTime_21+1); }
        if (ED_TotalFrames >= 22) { set_config_int(ED_State_s, "V2_FrameTime_22", ED_FrameTime_22+1); }
        if (ED_TotalFrames >= 23) { set_config_int(ED_State_s, "V2_FrameTime_23", ED_FrameTime_23+1); }
        if (ED_TotalFrames >= 24) { set_config_int(ED_State_s, "V2_FrameTime_24", ED_FrameTime_24+1); }
        if (ED_TotalFrames >= 25) { set_config_int(ED_State_s, "V2_FrameTime_25", ED_FrameTime_25+1); }
        if (ED_TotalFrames >= 26) { set_config_int(ED_State_s, "V2_FrameTime_26", ED_FrameTime_26+1); }
        if (ED_TotalFrames >= 27) { set_config_int(ED_State_s, "V2_FrameTime_27", ED_FrameTime_27+1); }
        if (ED_TotalFrames >= 28) { set_config_int(ED_State_s, "V2_FrameTime_28", ED_FrameTime_28+1); }
        if (ED_TotalFrames >= 29) { set_config_int(ED_State_s, "V2_FrameTime_29", ED_FrameTime_29+1); }
        set_config_int(ED_State_s, "XAlign", ED_XAlign);
        set_config_int(ED_State_s, "YAlign", ED_YAlign);
        ED_alertsave = 0;
        ED_ShowMsgSaving = 1;
    }

    if (ED_State >= 700 && ED_Special_Version == 3) {
        char ED_Caminho[99];
        sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
        set_config_file(ED_Caminho);
        char ED_State_s[3];
        sprintf(ED_State_s, "%i", ED_State);
        if (ED_TotalFrames >= 0) { set_config_int(ED_State_s, "V3_FrameTime_00", ED_FrameTime_00+1); }
        if (ED_TotalFrames >= 1) { set_config_int(ED_State_s, "V3_FrameTime_01", ED_FrameTime_01+1); }
        if (ED_TotalFrames >= 2) { set_config_int(ED_State_s, "V3_FrameTime_02", ED_FrameTime_02+1); }
        if (ED_TotalFrames >= 3) { set_config_int(ED_State_s, "V3_FrameTime_03", ED_FrameTime_03+1); }
        if (ED_TotalFrames >= 4) { set_config_int(ED_State_s, "V3_FrameTime_04", ED_FrameTime_04+1); }
        if (ED_TotalFrames >= 5) { set_config_int(ED_State_s, "V3_FrameTime_05", ED_FrameTime_05+1); }
        if (ED_TotalFrames >= 6) { set_config_int(ED_State_s, "V3_FrameTime_06", ED_FrameTime_06+1); }
        if (ED_TotalFrames >= 7) { set_config_int(ED_State_s, "V3_FrameTime_07", ED_FrameTime_07+1); }
        if (ED_TotalFrames >= 8) { set_config_int(ED_State_s, "V3_FrameTime_08", ED_FrameTime_08+1); }
        if (ED_TotalFrames >= 9) { set_config_int(ED_State_s, "V3_FrameTime_09", ED_FrameTime_09+1); }
        if (ED_TotalFrames >= 10) { set_config_int(ED_State_s, "V3_FrameTime_10", ED_FrameTime_10+1); }
        if (ED_TotalFrames >= 11) { set_config_int(ED_State_s, "V3_FrameTime_11", ED_FrameTime_11+1); }
        if (ED_TotalFrames >= 12) { set_config_int(ED_State_s, "V3_FrameTime_12", ED_FrameTime_12+1); }
        if (ED_TotalFrames >= 13) { set_config_int(ED_State_s, "V3_FrameTime_13", ED_FrameTime_13+1); }
        if (ED_TotalFrames >= 14) { set_config_int(ED_State_s, "V3_FrameTime_14", ED_FrameTime_14+1); }
        if (ED_TotalFrames >= 15) { set_config_int(ED_State_s, "V3_FrameTime_15", ED_FrameTime_15+1); }
        if (ED_TotalFrames >= 16) { set_config_int(ED_State_s, "V3_FrameTime_16", ED_FrameTime_16+1); }
        if (ED_TotalFrames >= 17) { set_config_int(ED_State_s, "V3_FrameTime_17", ED_FrameTime_17+1); }
        if (ED_TotalFrames >= 18) { set_config_int(ED_State_s, "V3_FrameTime_18", ED_FrameTime_18+1); }
        if (ED_TotalFrames >= 19) { set_config_int(ED_State_s, "V3_FrameTime_19", ED_FrameTime_19+1); }
        if (ED_TotalFrames >= 20) { set_config_int(ED_State_s, "V3_FrameTime_20", ED_FrameTime_20+1); }
        if (ED_TotalFrames >= 21) { set_config_int(ED_State_s, "V3_FrameTime_21", ED_FrameTime_21+1); }
        if (ED_TotalFrames >= 22) { set_config_int(ED_State_s, "V3_FrameTime_22", ED_FrameTime_22+1); }
        if (ED_TotalFrames >= 23) { set_config_int(ED_State_s, "V3_FrameTime_23", ED_FrameTime_23+1); }
        if (ED_TotalFrames >= 24) { set_config_int(ED_State_s, "V3_FrameTime_24", ED_FrameTime_24+1); }
        if (ED_TotalFrames >= 25) { set_config_int(ED_State_s, "V3_FrameTime_25", ED_FrameTime_25+1); }
        if (ED_TotalFrames >= 26) { set_config_int(ED_State_s, "V3_FrameTime_26", ED_FrameTime_26+1); }
        if (ED_TotalFrames >= 27) { set_config_int(ED_State_s, "V3_FrameTime_27", ED_FrameTime_27+1); }
        if (ED_TotalFrames >= 28) { set_config_int(ED_State_s, "V3_FrameTime_28", ED_FrameTime_28+1); }
        if (ED_TotalFrames >= 29) { set_config_int(ED_State_s, "V3_FrameTime_29", ED_FrameTime_29+1); }
        set_config_int(ED_State_s, "XAlign", ED_XAlign);
        set_config_int(ED_State_s, "YAlign", ED_YAlign);
        ED_alertsave = 0;
        ED_ShowMsgSaving = 1;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EDITOR LOAD CHAR.INI --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ED_load_charini() {
    //carrega dados do ini
    char ED_Caminho[99];
    sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
    set_config_file(ED_Caminho);
    char ED_State_s[4];
    sprintf(ED_State_s, "%i", ED_State);
    ED_FrameTime_00 = 0;
    ED_FrameTime_01 = 0;
    ED_FrameTime_02 = 0;
    ED_FrameTime_03 = 0;
    ED_FrameTime_04 = 0;
    ED_FrameTime_05 = 0;
    ED_FrameTime_06 = 0;
    ED_FrameTime_07 = 0;
    ED_FrameTime_08 = 0;
    ED_FrameTime_09 = 0;
    ED_FrameTime_10 = 0;
    ED_FrameTime_11 = 0;
    ED_FrameTime_12 = 0;
    ED_FrameTime_13 = 0;
    ED_FrameTime_14 = 0;
    ED_FrameTime_15 = 0;
    ED_FrameTime_16 = 0;
    ED_FrameTime_17 = 0;
    ED_FrameTime_18 = 0;
    ED_FrameTime_19 = 0;
    ED_FrameTime_20 = 0;
    ED_FrameTime_21 = 0;
    ED_FrameTime_22 = 0;
    ED_FrameTime_23 = 0;
    ED_FrameTime_24 = 0;
    ED_FrameTime_25 = 0;
    ED_FrameTime_26 = 0;
    ED_FrameTime_27 = 0;
    ED_FrameTime_28 = 0;
    ED_FrameTime_29 = 0;
    ED_FrameTime = 0;
    ED_XAlign = get_config_int(ED_State_s, "XAlign", ED_Largura/2); //P[1].Largura_100
    ED_YAlign = get_config_int(ED_State_s, "YAlign", ED_Altura);

    if (ED_State < 700) {
        if (ED_TotalFrames >= 0) { ED_FrameTime_00 = get_config_int(ED_State_s, "FrameTime_00", 6) - 1; }
        if (ED_TotalFrames >= 1) { ED_FrameTime_01 = get_config_int(ED_State_s, "FrameTime_01", 6) - 1; }
        if (ED_TotalFrames >= 2) { ED_FrameTime_02 = get_config_int(ED_State_s, "FrameTime_02", 6) - 1; }
        if (ED_TotalFrames >= 3) { ED_FrameTime_03 = get_config_int(ED_State_s, "FrameTime_03", 6) - 1; }
        if (ED_TotalFrames >= 4) { ED_FrameTime_04 = get_config_int(ED_State_s, "FrameTime_04", 6) - 1; }
        if (ED_TotalFrames >= 5) { ED_FrameTime_05 = get_config_int(ED_State_s, "FrameTime_05", 6) - 1; }
        if (ED_TotalFrames >= 6) { ED_FrameTime_06 = get_config_int(ED_State_s, "FrameTime_06", 6) - 1; }
        if (ED_TotalFrames >= 7) { ED_FrameTime_07 = get_config_int(ED_State_s, "FrameTime_07", 6) - 1; }
        if (ED_TotalFrames >= 8) { ED_FrameTime_08 = get_config_int(ED_State_s, "FrameTime_08", 6) - 1; }
        if (ED_TotalFrames >= 9) { ED_FrameTime_09 = get_config_int(ED_State_s, "FrameTime_09", 6) - 1; }
        if (ED_TotalFrames >= 10) { ED_FrameTime_10 = get_config_int(ED_State_s, "FrameTime_10", 6) - 1; }
        if (ED_TotalFrames >= 11) { ED_FrameTime_11 = get_config_int(ED_State_s, "FrameTime_11", 6) - 1; }
        if (ED_TotalFrames >= 12) { ED_FrameTime_12 = get_config_int(ED_State_s, "FrameTime_12", 6) - 1; }
        if (ED_TotalFrames >= 13) { ED_FrameTime_13 = get_config_int(ED_State_s, "FrameTime_13", 6) - 1; }
        if (ED_TotalFrames >= 14) { ED_FrameTime_14 = get_config_int(ED_State_s, "FrameTime_14", 6) - 1; }
        if (ED_TotalFrames >= 15) { ED_FrameTime_15 = get_config_int(ED_State_s, "FrameTime_15", 6) - 1; }
        if (ED_TotalFrames >= 16) { ED_FrameTime_16 = get_config_int(ED_State_s, "FrameTime_16", 6) - 1; }
        if (ED_TotalFrames >= 17) { ED_FrameTime_17 = get_config_int(ED_State_s, "FrameTime_17", 6) - 1; }
        if (ED_TotalFrames >= 18) { ED_FrameTime_18 = get_config_int(ED_State_s, "FrameTime_18", 6) - 1; }
        if (ED_TotalFrames >= 19) { ED_FrameTime_19 = get_config_int(ED_State_s, "FrameTime_19", 6) - 1; }
        if (ED_TotalFrames >= 20) { ED_FrameTime_20 = get_config_int(ED_State_s, "FrameTime_20", 6) - 1; }
        if (ED_TotalFrames >= 21) { ED_FrameTime_21 = get_config_int(ED_State_s, "FrameTime_21", 6) - 1; }
        if (ED_TotalFrames >= 22) { ED_FrameTime_22 = get_config_int(ED_State_s, "FrameTime_22", 6) - 1; }
        if (ED_TotalFrames >= 23) { ED_FrameTime_23 = get_config_int(ED_State_s, "FrameTime_23", 6) - 1; }
        if (ED_TotalFrames >= 24) { ED_FrameTime_24 = get_config_int(ED_State_s, "FrameTime_24", 6) - 1; }
        if (ED_TotalFrames >= 25) { ED_FrameTime_25 = get_config_int(ED_State_s, "FrameTime_25", 6) - 1; }
        if (ED_TotalFrames >= 26) { ED_FrameTime_26 = get_config_int(ED_State_s, "FrameTime_26", 6) - 1; }
        if (ED_TotalFrames >= 27) { ED_FrameTime_27 = get_config_int(ED_State_s, "FrameTime_27", 6) - 1; }
        if (ED_TotalFrames >= 28) { ED_FrameTime_28 = get_config_int(ED_State_s, "FrameTime_28", 6) - 1; }
        if (ED_TotalFrames >= 29) { ED_FrameTime_29 = get_config_int(ED_State_s, "FrameTime_29", 6) - 1; }
    }

    if (ED_State >= 700 && ED_Special_Version == 1) {
        if (ED_TotalFrames >= 0) { ED_FrameTime_00 = get_config_int(ED_State_s, "V1_FrameTime_00", 6) - 1; }
        if (ED_TotalFrames >= 1) { ED_FrameTime_01 = get_config_int(ED_State_s, "V1_FrameTime_01", 6) - 1; }
        if (ED_TotalFrames >= 2) { ED_FrameTime_02 = get_config_int(ED_State_s, "V1_FrameTime_02", 6) - 1; }
        if (ED_TotalFrames >= 3) { ED_FrameTime_03 = get_config_int(ED_State_s, "V1_FrameTime_03", 6) - 1; }
        if (ED_TotalFrames >= 4) { ED_FrameTime_04 = get_config_int(ED_State_s, "V1_FrameTime_04", 6) - 1; }
        if (ED_TotalFrames >= 5) { ED_FrameTime_05 = get_config_int(ED_State_s, "V1_FrameTime_05", 6) - 1; }
        if (ED_TotalFrames >= 6) { ED_FrameTime_06 = get_config_int(ED_State_s, "V1_FrameTime_06", 6) - 1; }
        if (ED_TotalFrames >= 7) { ED_FrameTime_07 = get_config_int(ED_State_s, "V1_FrameTime_07", 6) - 1; }
        if (ED_TotalFrames >= 8) { ED_FrameTime_08 = get_config_int(ED_State_s, "V1_FrameTime_08", 6) - 1; }
        if (ED_TotalFrames >= 9) { ED_FrameTime_09 = get_config_int(ED_State_s, "V1_FrameTime_09", 6) - 1; }
        if (ED_TotalFrames >= 10) { ED_FrameTime_10 = get_config_int(ED_State_s, "V1_FrameTime_10", 6) - 1; }
        if (ED_TotalFrames >= 11) { ED_FrameTime_11 = get_config_int(ED_State_s, "V1_FrameTime_11", 6) - 1; }
        if (ED_TotalFrames >= 12) { ED_FrameTime_12 = get_config_int(ED_State_s, "V1_FrameTime_12", 6) - 1; }
        if (ED_TotalFrames >= 13) { ED_FrameTime_13 = get_config_int(ED_State_s, "V1_FrameTime_13", 6) - 1; }
        if (ED_TotalFrames >= 14) { ED_FrameTime_14 = get_config_int(ED_State_s, "V1_FrameTime_14", 6) - 1; }
        if (ED_TotalFrames >= 15) { ED_FrameTime_15 = get_config_int(ED_State_s, "V1_FrameTime_15", 6) - 1; }
        if (ED_TotalFrames >= 16) { ED_FrameTime_16 = get_config_int(ED_State_s, "V1_FrameTime_16", 6) - 1; }
        if (ED_TotalFrames >= 17) { ED_FrameTime_17 = get_config_int(ED_State_s, "V1_FrameTime_17", 6) - 1; }
        if (ED_TotalFrames >= 18) { ED_FrameTime_18 = get_config_int(ED_State_s, "V1_FrameTime_18", 6) - 1; }
        if (ED_TotalFrames >= 19) { ED_FrameTime_19 = get_config_int(ED_State_s, "V1_FrameTime_19", 6) - 1; }
        if (ED_TotalFrames >= 20) { ED_FrameTime_20 = get_config_int(ED_State_s, "V1_FrameTime_20", 6) - 1; }
        if (ED_TotalFrames >= 21) { ED_FrameTime_21 = get_config_int(ED_State_s, "V1_FrameTime_21", 6) - 1; }
        if (ED_TotalFrames >= 22) { ED_FrameTime_22 = get_config_int(ED_State_s, "V1_FrameTime_22", 6) - 1; }
        if (ED_TotalFrames >= 23) { ED_FrameTime_23 = get_config_int(ED_State_s, "V1_FrameTime_23", 6) - 1; }
        if (ED_TotalFrames >= 24) { ED_FrameTime_24 = get_config_int(ED_State_s, "V1_FrameTime_24", 6) - 1; }
        if (ED_TotalFrames >= 25) { ED_FrameTime_25 = get_config_int(ED_State_s, "V1_FrameTime_25", 6) - 1; }
        if (ED_TotalFrames >= 26) { ED_FrameTime_26 = get_config_int(ED_State_s, "V1_FrameTime_26", 6) - 1; }
        if (ED_TotalFrames >= 27) { ED_FrameTime_27 = get_config_int(ED_State_s, "V1_FrameTime_27", 6) - 1; }
        if (ED_TotalFrames >= 28) { ED_FrameTime_28 = get_config_int(ED_State_s, "V1_FrameTime_28", 6) - 1; }
        if (ED_TotalFrames >= 29) { ED_FrameTime_29 = get_config_int(ED_State_s, "V1_FrameTime_29", 6) - 1; }
    }

    if (ED_State >= 700 && ED_Special_Version == 2) {
        if (ED_TotalFrames >= 0) { ED_FrameTime_00 = get_config_int(ED_State_s, "V2_FrameTime_00", 6) - 1; }
        if (ED_TotalFrames >= 1) { ED_FrameTime_01 = get_config_int(ED_State_s, "V2_FrameTime_01", 6) - 1; }
        if (ED_TotalFrames >= 2) { ED_FrameTime_02 = get_config_int(ED_State_s, "V2_FrameTime_02", 6) - 1; }
        if (ED_TotalFrames >= 3) { ED_FrameTime_03 = get_config_int(ED_State_s, "V2_FrameTime_03", 6) - 1; }
        if (ED_TotalFrames >= 4) { ED_FrameTime_04 = get_config_int(ED_State_s, "V2_FrameTime_04", 6) - 1; }
        if (ED_TotalFrames >= 5) { ED_FrameTime_05 = get_config_int(ED_State_s, "V2_FrameTime_05", 6) - 1; }
        if (ED_TotalFrames >= 6) { ED_FrameTime_06 = get_config_int(ED_State_s, "V2_FrameTime_06", 6) - 1; }
        if (ED_TotalFrames >= 7) { ED_FrameTime_07 = get_config_int(ED_State_s, "V2_FrameTime_07", 6) - 1; }
        if (ED_TotalFrames >= 8) { ED_FrameTime_08 = get_config_int(ED_State_s, "V2_FrameTime_08", 6) - 1; }
        if (ED_TotalFrames >= 9) { ED_FrameTime_09 = get_config_int(ED_State_s, "V2_FrameTime_09", 6) - 1; }
        if (ED_TotalFrames >= 10) { ED_FrameTime_10 = get_config_int(ED_State_s, "V2_FrameTime_10", 6) - 1; }
        if (ED_TotalFrames >= 11) { ED_FrameTime_11 = get_config_int(ED_State_s, "V2_FrameTime_11", 6) - 1; }
        if (ED_TotalFrames >= 12) { ED_FrameTime_12 = get_config_int(ED_State_s, "V2_FrameTime_12", 6) - 1; }
        if (ED_TotalFrames >= 13) { ED_FrameTime_13 = get_config_int(ED_State_s, "V2_FrameTime_13", 6) - 1; }
        if (ED_TotalFrames >= 14) { ED_FrameTime_14 = get_config_int(ED_State_s, "V2_FrameTime_14", 6) - 1; }
        if (ED_TotalFrames >= 15) { ED_FrameTime_15 = get_config_int(ED_State_s, "V2_FrameTime_15", 6) - 1; }
        if (ED_TotalFrames >= 16) { ED_FrameTime_16 = get_config_int(ED_State_s, "V2_FrameTime_16", 6) - 1; }
        if (ED_TotalFrames >= 17) { ED_FrameTime_17 = get_config_int(ED_State_s, "V2_FrameTime_17", 6) - 1; }
        if (ED_TotalFrames >= 18) { ED_FrameTime_18 = get_config_int(ED_State_s, "V2_FrameTime_18", 6) - 1; }
        if (ED_TotalFrames >= 19) { ED_FrameTime_19 = get_config_int(ED_State_s, "V2_FrameTime_19", 6) - 1; }
        if (ED_TotalFrames >= 20) { ED_FrameTime_20 = get_config_int(ED_State_s, "V2_FrameTime_20", 6) - 1; }
        if (ED_TotalFrames >= 21) { ED_FrameTime_21 = get_config_int(ED_State_s, "V2_FrameTime_21", 6) - 1; }
        if (ED_TotalFrames >= 22) { ED_FrameTime_22 = get_config_int(ED_State_s, "V2_FrameTime_22", 6) - 1; }
        if (ED_TotalFrames >= 23) { ED_FrameTime_23 = get_config_int(ED_State_s, "V2_FrameTime_23", 6) - 1; }
        if (ED_TotalFrames >= 24) { ED_FrameTime_24 = get_config_int(ED_State_s, "V2_FrameTime_24", 6) - 1; }
        if (ED_TotalFrames >= 25) { ED_FrameTime_25 = get_config_int(ED_State_s, "V2_FrameTime_25", 6) - 1; }
        if (ED_TotalFrames >= 26) { ED_FrameTime_26 = get_config_int(ED_State_s, "V2_FrameTime_26", 6) - 1; }
        if (ED_TotalFrames >= 27) { ED_FrameTime_27 = get_config_int(ED_State_s, "V2_FrameTime_27", 6) - 1; }
        if (ED_TotalFrames >= 28) { ED_FrameTime_28 = get_config_int(ED_State_s, "V2_FrameTime_28", 6) - 1; }
        if (ED_TotalFrames >= 29) { ED_FrameTime_29 = get_config_int(ED_State_s, "V2_FrameTime_29", 6) - 1; }
    }

    if (ED_State >= 700 && ED_Special_Version == 3) {
        if (ED_TotalFrames >= 0) { ED_FrameTime_00 = get_config_int(ED_State_s, "V3_FrameTime_00", 6) - 1; }
        if (ED_TotalFrames >= 1) { ED_FrameTime_01 = get_config_int(ED_State_s, "V3_FrameTime_01", 6) - 1; }
        if (ED_TotalFrames >= 2) { ED_FrameTime_02 = get_config_int(ED_State_s, "V3_FrameTime_02", 6) - 1; }
        if (ED_TotalFrames >= 3) { ED_FrameTime_03 = get_config_int(ED_State_s, "V3_FrameTime_03", 6) - 1; }
        if (ED_TotalFrames >= 4) { ED_FrameTime_04 = get_config_int(ED_State_s, "V3_FrameTime_04", 6) - 1; }
        if (ED_TotalFrames >= 5) { ED_FrameTime_05 = get_config_int(ED_State_s, "V3_FrameTime_05", 6) - 1; }
        if (ED_TotalFrames >= 6) { ED_FrameTime_06 = get_config_int(ED_State_s, "V3_FrameTime_06", 6) - 1; }
        if (ED_TotalFrames >= 7) { ED_FrameTime_07 = get_config_int(ED_State_s, "V3_FrameTime_07", 6) - 1; }
        if (ED_TotalFrames >= 8) { ED_FrameTime_08 = get_config_int(ED_State_s, "V3_FrameTime_08", 6) - 1; }
        if (ED_TotalFrames >= 9) { ED_FrameTime_09 = get_config_int(ED_State_s, "V3_FrameTime_09", 6) - 1; }
        if (ED_TotalFrames >= 10) { ED_FrameTime_10 = get_config_int(ED_State_s, "V3_FrameTime_10", 6) - 1; }
        if (ED_TotalFrames >= 11) { ED_FrameTime_11 = get_config_int(ED_State_s, "V3_FrameTime_11", 6) - 1; }
        if (ED_TotalFrames >= 12) { ED_FrameTime_12 = get_config_int(ED_State_s, "V3_FrameTime_12", 6) - 1; }
        if (ED_TotalFrames >= 13) { ED_FrameTime_13 = get_config_int(ED_State_s, "V3_FrameTime_13", 6) - 1; }
        if (ED_TotalFrames >= 14) { ED_FrameTime_14 = get_config_int(ED_State_s, "V3_FrameTime_14", 6) - 1; }
        if (ED_TotalFrames >= 15) { ED_FrameTime_15 = get_config_int(ED_State_s, "V3_FrameTime_15", 6) - 1; }
        if (ED_TotalFrames >= 16) { ED_FrameTime_16 = get_config_int(ED_State_s, "V3_FrameTime_16", 6) - 1; }
        if (ED_TotalFrames >= 17) { ED_FrameTime_17 = get_config_int(ED_State_s, "V3_FrameTime_17", 6) - 1; }
        if (ED_TotalFrames >= 18) { ED_FrameTime_18 = get_config_int(ED_State_s, "V3_FrameTime_18", 6) - 1; }
        if (ED_TotalFrames >= 19) { ED_FrameTime_19 = get_config_int(ED_State_s, "V3_FrameTime_19", 6) - 1; }
        if (ED_TotalFrames >= 20) { ED_FrameTime_20 = get_config_int(ED_State_s, "V3_FrameTime_20", 6) - 1; }
        if (ED_TotalFrames >= 21) { ED_FrameTime_21 = get_config_int(ED_State_s, "V3_FrameTime_21", 6) - 1; }
        if (ED_TotalFrames >= 22) { ED_FrameTime_22 = get_config_int(ED_State_s, "V3_FrameTime_22", 6) - 1; }
        if (ED_TotalFrames >= 23) { ED_FrameTime_23 = get_config_int(ED_State_s, "V3_FrameTime_23", 6) - 1; }
        if (ED_TotalFrames >= 24) { ED_FrameTime_24 = get_config_int(ED_State_s, "V3_FrameTime_24", 6) - 1; }
        if (ED_TotalFrames >= 25) { ED_FrameTime_25 = get_config_int(ED_State_s, "V3_FrameTime_25", 6) - 1; }
        if (ED_TotalFrames >= 26) { ED_FrameTime_26 = get_config_int(ED_State_s, "V3_FrameTime_26", 6) - 1; }
        if (ED_TotalFrames >= 27) { ED_FrameTime_27 = get_config_int(ED_State_s, "V3_FrameTime_27", 6) - 1; }
        if (ED_TotalFrames >= 28) { ED_FrameTime_28 = get_config_int(ED_State_s, "V3_FrameTime_28", 6) - 1; }
        if (ED_TotalFrames >= 29) { ED_FrameTime_29 = get_config_int(ED_State_s, "V3_FrameTime_29", 6) - 1; }
    }

    //salva o tempo de animacao 6 (se o tempo do frame for vazio, usa 6, que é o padrao)
    if (ED_State < 700) {
        if (ED_TotalFrames >= 0 && ED_FrameTime_00 == 5) {
            set_config_int(ED_State_s, "FrameTime_00", ED_FrameTime_00+1);
        }
        if (ED_TotalFrames >= 1 && ED_FrameTime_01 == 5) {
            set_config_int(ED_State_s, "FrameTime_01", ED_FrameTime_01+1);
        }
        if (ED_TotalFrames >= 2 && ED_FrameTime_02 == 5) {
            set_config_int(ED_State_s, "FrameTime_02", ED_FrameTime_02+1);
        }
        if (ED_TotalFrames >= 3 && ED_FrameTime_03 == 5) {
            set_config_int(ED_State_s, "FrameTime_03", ED_FrameTime_03+1);
        }
        if (ED_TotalFrames >= 4 && ED_FrameTime_04 == 5) {
            set_config_int(ED_State_s, "FrameTime_04", ED_FrameTime_04+1);
        }
        if (ED_TotalFrames >= 5 && ED_FrameTime_05 == 5) {
            set_config_int(ED_State_s, "FrameTime_05", ED_FrameTime_05+1);
        }
        if (ED_TotalFrames >= 6 && ED_FrameTime_06 == 5) {
            set_config_int(ED_State_s, "FrameTime_06", ED_FrameTime_06+1);
        }
        if (ED_TotalFrames >= 7 && ED_FrameTime_07 == 5) {
            set_config_int(ED_State_s, "FrameTime_07", ED_FrameTime_07+1);
        }
        if (ED_TotalFrames >= 8 && ED_FrameTime_08 == 5) {
            set_config_int(ED_State_s, "FrameTime_08", ED_FrameTime_08+1);
        }
        if (ED_TotalFrames >= 9 && ED_FrameTime_09 == 5) {
            set_config_int(ED_State_s, "FrameTime_09", ED_FrameTime_09+1);
        }
        if (ED_TotalFrames >= 10 && ED_FrameTime_10 == 5) {
            set_config_int(ED_State_s, "FrameTime_10", ED_FrameTime_10+1);
        }
        if (ED_TotalFrames >= 11 && ED_FrameTime_11 == 5) {
            set_config_int(ED_State_s, "FrameTime_11", ED_FrameTime_11+1);
        }
        if (ED_TotalFrames >= 12 && ED_FrameTime_12 == 5) {
            set_config_int(ED_State_s, "FrameTime_12", ED_FrameTime_12+1);
        }
        if (ED_TotalFrames >= 13 && ED_FrameTime_13 == 5) {
            set_config_int(ED_State_s, "FrameTime_13", ED_FrameTime_13+1);
        }
        if (ED_TotalFrames >= 14 && ED_FrameTime_14 == 5) {
            set_config_int(ED_State_s, "FrameTime_14", ED_FrameTime_14+1);
        }
        if (ED_TotalFrames >= 15 && ED_FrameTime_15 == 5) {
            set_config_int(ED_State_s, "FrameTime_15", ED_FrameTime_15+1);
        }
        if (ED_TotalFrames >= 16 && ED_FrameTime_16 == 5) {
            set_config_int(ED_State_s, "FrameTime_16", ED_FrameTime_16+1);
        }
        if (ED_TotalFrames >= 17 && ED_FrameTime_17 == 5) {
            set_config_int(ED_State_s, "FrameTime_17", ED_FrameTime_17+1);
        }
        if (ED_TotalFrames >= 18 && ED_FrameTime_18 == 5) {
            set_config_int(ED_State_s, "FrameTime_18", ED_FrameTime_18+1);
        }
        if (ED_TotalFrames >= 19 && ED_FrameTime_19 == 5) {
            set_config_int(ED_State_s, "FrameTime_19", ED_FrameTime_19+1);
        }
        if (ED_TotalFrames >= 20 && ED_FrameTime_20 == 5) {
            set_config_int(ED_State_s, "FrameTime_20", ED_FrameTime_20+1);
        }
        if (ED_TotalFrames >= 21 && ED_FrameTime_21 == 5) {
            set_config_int(ED_State_s, "FrameTime_21", ED_FrameTime_21+1);
        }
        if (ED_TotalFrames >= 22 && ED_FrameTime_22 == 5) {
            set_config_int(ED_State_s, "FrameTime_22", ED_FrameTime_22+1);
        }
        if (ED_TotalFrames >= 23 && ED_FrameTime_23 == 5) {
            set_config_int(ED_State_s, "FrameTime_23", ED_FrameTime_23+1);
        }
        if (ED_TotalFrames >= 24 && ED_FrameTime_24 == 5) {
            set_config_int(ED_State_s, "FrameTime_24", ED_FrameTime_24+1);
        }
        if (ED_TotalFrames >= 25 && ED_FrameTime_25 == 5) {
            set_config_int(ED_State_s, "FrameTime_25", ED_FrameTime_25+1);
        }
        if (ED_TotalFrames >= 26 && ED_FrameTime_26 == 5) {
            set_config_int(ED_State_s, "FrameTime_26", ED_FrameTime_26+1);
        }
        if (ED_TotalFrames >= 27 && ED_FrameTime_27 == 5) {
            set_config_int(ED_State_s, "FrameTime_27", ED_FrameTime_27+1);
        }
        if (ED_TotalFrames >= 28 && ED_FrameTime_28 == 5) {
            set_config_int(ED_State_s, "FrameTime_28", ED_FrameTime_28+1);
        }
        if (ED_TotalFrames >= 29 && ED_FrameTime_29 == 5) {
            set_config_int(ED_State_s, "FrameTime_29", ED_FrameTime_29+1);
        }
    }

    if (ED_State >= 700 && ED_Special_Version == 1) {
        if (ED_TotalFrames >= 0 && ED_FrameTime_00 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_00", ED_FrameTime_00+1);
        }
        if (ED_TotalFrames >= 1 && ED_FrameTime_01 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_01", ED_FrameTime_01+1);
        }
        if (ED_TotalFrames >= 2 && ED_FrameTime_02 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_02", ED_FrameTime_02+1);
        }
        if (ED_TotalFrames >= 3 && ED_FrameTime_03 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_03", ED_FrameTime_03+1);
        }
        if (ED_TotalFrames >= 4 && ED_FrameTime_04 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_04", ED_FrameTime_04+1);
        }
        if (ED_TotalFrames >= 5 && ED_FrameTime_05 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_05", ED_FrameTime_05+1);
        }
        if (ED_TotalFrames >= 6 && ED_FrameTime_06 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_06", ED_FrameTime_06+1);
        }
        if (ED_TotalFrames >= 7 && ED_FrameTime_07 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_07", ED_FrameTime_07+1);
        }
        if (ED_TotalFrames >= 8 && ED_FrameTime_08 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_08", ED_FrameTime_08+1);
        }
        if (ED_TotalFrames >= 9 && ED_FrameTime_09 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_09", ED_FrameTime_09+1);
        }
        if (ED_TotalFrames >= 10 && ED_FrameTime_10 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_10", ED_FrameTime_10+1);
        }
        if (ED_TotalFrames >= 11 && ED_FrameTime_11 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_11", ED_FrameTime_11+1);
        }
        if (ED_TotalFrames >= 12 && ED_FrameTime_12 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_12", ED_FrameTime_12+1);
        }
        if (ED_TotalFrames >= 13 && ED_FrameTime_13 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_13", ED_FrameTime_13+1);
        }
        if (ED_TotalFrames >= 14 && ED_FrameTime_14 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_14", ED_FrameTime_14+1);
        }
        if (ED_TotalFrames >= 15 && ED_FrameTime_15 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_15", ED_FrameTime_15+1);
        }
        if (ED_TotalFrames >= 16 && ED_FrameTime_16 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_16", ED_FrameTime_16+1);
        }
        if (ED_TotalFrames >= 17 && ED_FrameTime_17 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_17", ED_FrameTime_17+1);
        }
        if (ED_TotalFrames >= 18 && ED_FrameTime_18 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_18", ED_FrameTime_18+1);
        }
        if (ED_TotalFrames >= 19 && ED_FrameTime_19 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_19", ED_FrameTime_19+1);
        }
        if (ED_TotalFrames >= 20 && ED_FrameTime_20 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_20", ED_FrameTime_20+1);
        }
        if (ED_TotalFrames >= 21 && ED_FrameTime_21 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_21", ED_FrameTime_21+1);
        }
        if (ED_TotalFrames >= 22 && ED_FrameTime_22 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_22", ED_FrameTime_22+1);
        }
        if (ED_TotalFrames >= 23 && ED_FrameTime_23 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_23", ED_FrameTime_23+1);
        }
        if (ED_TotalFrames >= 24 && ED_FrameTime_24 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_24", ED_FrameTime_24+1);
        }
        if (ED_TotalFrames >= 25 && ED_FrameTime_25 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_25", ED_FrameTime_25+1);
        }
        if (ED_TotalFrames >= 26 && ED_FrameTime_26 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_26", ED_FrameTime_26+1);
        }
        if (ED_TotalFrames >= 27 && ED_FrameTime_27 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_27", ED_FrameTime_27+1);
        }
        if (ED_TotalFrames >= 28 && ED_FrameTime_28 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_28", ED_FrameTime_28+1);
        }
        if (ED_TotalFrames >= 29 && ED_FrameTime_29 == 5) {
            set_config_int(ED_State_s, "V1_FrameTime_29", ED_FrameTime_29+1);
        }
    }

    if (ED_State >= 700 && ED_Special_Version == 2) {
        if (ED_TotalFrames >= 0 && ED_FrameTime_00 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_00", ED_FrameTime_00+1);
        }
        if (ED_TotalFrames >= 1 && ED_FrameTime_01 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_01", ED_FrameTime_01+1);
        }
        if (ED_TotalFrames >= 2 && ED_FrameTime_02 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_02", ED_FrameTime_02+1);
        }
        if (ED_TotalFrames >= 3 && ED_FrameTime_03 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_03", ED_FrameTime_03+1);
        }
        if (ED_TotalFrames >= 4 && ED_FrameTime_04 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_04", ED_FrameTime_04+1);
        }
        if (ED_TotalFrames >= 5 && ED_FrameTime_05 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_05", ED_FrameTime_05+1);
        }
        if (ED_TotalFrames >= 6 && ED_FrameTime_06 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_06", ED_FrameTime_06+1);
        }
        if (ED_TotalFrames >= 7 && ED_FrameTime_07 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_07", ED_FrameTime_07+1);
        }
        if (ED_TotalFrames >= 8 && ED_FrameTime_08 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_08", ED_FrameTime_08+1);
        }
        if (ED_TotalFrames >= 9 && ED_FrameTime_09 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_09", ED_FrameTime_09+1);
        }
        if (ED_TotalFrames >= 10 && ED_FrameTime_10 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_10", ED_FrameTime_10+1);
        }
        if (ED_TotalFrames >= 11 && ED_FrameTime_11 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_11", ED_FrameTime_11+1);
        }
        if (ED_TotalFrames >= 12 && ED_FrameTime_12 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_12", ED_FrameTime_12+1);
        }
        if (ED_TotalFrames >= 13 && ED_FrameTime_13 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_13", ED_FrameTime_13+1);
        }
        if (ED_TotalFrames >= 14 && ED_FrameTime_14 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_14", ED_FrameTime_14+1);
        }
        if (ED_TotalFrames >= 15 && ED_FrameTime_15 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_15", ED_FrameTime_15+1);
        }
        if (ED_TotalFrames >= 16 && ED_FrameTime_16 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_16", ED_FrameTime_16+1);
        }
        if (ED_TotalFrames >= 17 && ED_FrameTime_17 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_17", ED_FrameTime_17+1);
        }
        if (ED_TotalFrames >= 18 && ED_FrameTime_18 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_18", ED_FrameTime_18+1);
        }
        if (ED_TotalFrames >= 19 && ED_FrameTime_19 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_19", ED_FrameTime_19+1);
        }
        if (ED_TotalFrames >= 20 && ED_FrameTime_20 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_20", ED_FrameTime_20+1);
        }
        if (ED_TotalFrames >= 21 && ED_FrameTime_21 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_21", ED_FrameTime_21+1);
        }
        if (ED_TotalFrames >= 22 && ED_FrameTime_22 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_22", ED_FrameTime_22+1);
        }
        if (ED_TotalFrames >= 23 && ED_FrameTime_23 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_23", ED_FrameTime_23+1);
        }
        if (ED_TotalFrames >= 24 && ED_FrameTime_24 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_24", ED_FrameTime_24+1);
        }
        if (ED_TotalFrames >= 25 && ED_FrameTime_25 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_25", ED_FrameTime_25+1);
        }
        if (ED_TotalFrames >= 26 && ED_FrameTime_26 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_26", ED_FrameTime_26+1);
        }
        if (ED_TotalFrames >= 27 && ED_FrameTime_27 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_27", ED_FrameTime_27+1);
        }
        if (ED_TotalFrames >= 28 && ED_FrameTime_28 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_28", ED_FrameTime_28+1);
        }
        if (ED_TotalFrames >= 29 && ED_FrameTime_29 == 5) {
            set_config_int(ED_State_s, "V2_FrameTime_29", ED_FrameTime_29+1);
        }
    }

    if (ED_State >= 700 && ED_Special_Version == 3) {
        if (ED_TotalFrames >= 0 && ED_FrameTime_00 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_00", ED_FrameTime_00+1);
        }
        if (ED_TotalFrames >= 1 && ED_FrameTime_01 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_01", ED_FrameTime_01+1);
        }
        if (ED_TotalFrames >= 2 && ED_FrameTime_02 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_02", ED_FrameTime_02+1);
        }
        if (ED_TotalFrames >= 3 && ED_FrameTime_03 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_03", ED_FrameTime_03+1);
        }
        if (ED_TotalFrames >= 4 && ED_FrameTime_04 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_04", ED_FrameTime_04+1);
        }
        if (ED_TotalFrames >= 5 && ED_FrameTime_05 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_05", ED_FrameTime_05+1);
        }
        if (ED_TotalFrames >= 6 && ED_FrameTime_06 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_06", ED_FrameTime_06+1);
        }
        if (ED_TotalFrames >= 7 && ED_FrameTime_07 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_07", ED_FrameTime_07+1);
        }
        if (ED_TotalFrames >= 8 && ED_FrameTime_08 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_08", ED_FrameTime_08+1);
        }
        if (ED_TotalFrames >= 9 && ED_FrameTime_09 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_09", ED_FrameTime_09+1);
        }
        if (ED_TotalFrames >= 10 && ED_FrameTime_10 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_10", ED_FrameTime_10+1);
        }
        if (ED_TotalFrames >= 11 && ED_FrameTime_11 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_11", ED_FrameTime_11+1);
        }
        if (ED_TotalFrames >= 12 && ED_FrameTime_12 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_12", ED_FrameTime_12+1);
        }
        if (ED_TotalFrames >= 13 && ED_FrameTime_13 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_13", ED_FrameTime_13+1);
        }
        if (ED_TotalFrames >= 14 && ED_FrameTime_14 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_14", ED_FrameTime_14+1);
        }
        if (ED_TotalFrames >= 15 && ED_FrameTime_15 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_15", ED_FrameTime_15+1);
        }
        if (ED_TotalFrames >= 16 && ED_FrameTime_16 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_16", ED_FrameTime_16+1);
        }
        if (ED_TotalFrames >= 17 && ED_FrameTime_17 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_17", ED_FrameTime_17+1);
        }
        if (ED_TotalFrames >= 18 && ED_FrameTime_18 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_18", ED_FrameTime_18+1);
        }
        if (ED_TotalFrames >= 19 && ED_FrameTime_19 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_19", ED_FrameTime_19+1);
        }
        if (ED_TotalFrames >= 20 && ED_FrameTime_20 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_20", ED_FrameTime_20+1);
        }
        if (ED_TotalFrames >= 21 && ED_FrameTime_21 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_21", ED_FrameTime_21+1);
        }
        if (ED_TotalFrames >= 22 && ED_FrameTime_22 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_22", ED_FrameTime_22+1);
        }
        if (ED_TotalFrames >= 23 && ED_FrameTime_23 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_23", ED_FrameTime_23+1);
        }
        if (ED_TotalFrames >= 24 && ED_FrameTime_24 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_24", ED_FrameTime_24+1);
        }
        if (ED_TotalFrames >= 25 && ED_FrameTime_25 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_25", ED_FrameTime_25+1);
        }
        if (ED_TotalFrames >= 26 && ED_FrameTime_26 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_26", ED_FrameTime_26+1);
        }
        if (ED_TotalFrames >= 27 && ED_FrameTime_27 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_27", ED_FrameTime_27+1);
        }
        if (ED_TotalFrames >= 28 && ED_FrameTime_28 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_28", ED_FrameTime_28+1);
        }
        if (ED_TotalFrames >= 29 && ED_FrameTime_29 == 5) {
            set_config_int(ED_State_s, "V3_FrameTime_29", ED_FrameTime_29+1);
        }
    }
}

void ED_load_inputs(int ED_State) {
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
    sprintf(StrSpecialInput, "data/chars/%s/special.ini", P[1].Name);
    set_config_file(StrSpecialInput);
    char str[3];
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EDITOR INICIALIZAR --------------------------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ED_inicializar() {
    ED_MODE = 1;

    ED_Special_Version = 1;
    ED_ShowMsgSaving = 0;
    ED_FrameTime_00 = 0;
    ED_FrameTime_01 = 0;
    ED_FrameTime_02 = 0;
    ED_FrameTime_03 = 0;
    ED_FrameTime_04 = 0;
    ED_FrameTime_05 = 0;
    ED_FrameTime_06 = 0;
    ED_FrameTime_07 = 0;
    ED_FrameTime_08 = 0;
    ED_FrameTime_09 = 0;
    ED_FrameTime_10 = 0;
    ED_FrameTime_11 = 0;
    ED_FrameTime_12 = 0;
    ED_FrameTime_13 = 0;
    ED_FrameTime_14 = 0;
    ED_FrameTime_15 = 0;
    ED_FrameTime_16 = 0;
    ED_FrameTime_17 = 0;
    ED_FrameTime_18 = 0;
    ED_FrameTime_19 = 0;
    ED_FrameTime_20 = 0;
    ED_FrameTime_21 = 0;
    ED_FrameTime_22 = 0;
    ED_FrameTime_23 = 0;
    ED_FrameTime_24 = 0;
    ED_FrameTime_25 = 0;
    ED_FrameTime_26 = 0;
    ED_FrameTime_27 = 0;
    ED_FrameTime_28 = 0;
    ED_FrameTime_29 = 0;
    ED_FrameTime = 0;
    ED_Pause = 0;
    ED_DrawBlueMode = 0;
    ED_DrawRedMode = 0;
    ED_bt_Null = 0;
    ED_Mx1 = -1;
    ED_My1 = -1;
    ED_Mx2 = -1;
    ED_My2 = -1;
    Draw_CHBoxes_ED();
    ED_HitBox_tot = 0;
    ED_HurtBox_tot = 0;
    sprintf(ED_Name, "%s", P[1].Name);
    Edtimer = 0;
    ED_StartFrame = Edtimer;
    ED_State = 100;
    int ED_100_tot = -1;
    for (int i = 0; i <= 29; i++) {
        char txt[50] = "";
        if (i < 10) { sprintf(txt, "data/chars/%s/100_0%i.png", ED_Name, i); }
        if (i >= 10) { sprintf(txt, "data/chars/%s/100_%i.png", ED_Name, i); }
        if (exists(txt)) { ED_100_tot++; } else { i = 29; }
        ED_TotalFrames = ED_100_tot;
    }
    ED_IndexAnim = 0;
    ED_Lado = 1;
    ED_XAlign = 0;
    ED_YAlign = 0;
    ED_x = 320 / 2;
    ED_y = 220;
    ED_Altura = 0;
    ED_Largura = 0;
    ED_Altura_100 = 0;
    ED_Largura_100 = 0;

    //abastece MovPossiveis - Verifica a existencia de Movimentos (imgs nnn_00.pcx) na pasta do personagem
    int i = 0;
    char txt[50] = "";
    for (int ind = 100; ind <= 999; ind++) {
        char indINTtoCHAR[4] = "";
        sprintf(indINTtoCHAR, "%d", ind);
        sprintf(txt, "data/chars/%s/%s_00.png", ED_Name, indINTtoCHAR);
        if (exists(txt)) {
            MovPossiveis[i] = ind;
            i++;
        }
    }

    //faz o carregamento inicial do char.ini
    char ED_State_s[4];
    char ED_Caminho[99];

    sprintf(ED_State_s, "%i", ED_State);
    sprintf(ED_Caminho, "data/chars/%s/char.ini", P[1].Name);
    set_config_file(ED_Caminho);
    strcpy(ED_Name_Display, (char *)get_config_string("Info", "Name", "-"));
    ED_XAlign = get_config_int(ED_State_s, "XAlign", ED_Largura/2);
    ED_YAlign = get_config_int(ED_State_s, "YAlign", ED_Altura);
    ED_Tipo = get_config_int("Info", "Type", 1);
    ED_TotalFrames = get_config_int(ED_State_s, "TotalFrames", ED_TotalFrames);
    if (ED_TotalFrames >= 0) { ED_FrameTime_00 = get_config_int(ED_State_s, "FrameTime_00", 6) - 1; }
    if (ED_TotalFrames >= 1) { ED_FrameTime_01 = get_config_int(ED_State_s, "FrameTime_01", 6) - 1; }
    if (ED_TotalFrames >= 2) { ED_FrameTime_02 = get_config_int(ED_State_s, "FrameTime_02", 6) - 1; }
    if (ED_TotalFrames >= 3) { ED_FrameTime_03 = get_config_int(ED_State_s, "FrameTime_03", 6) - 1; }
    if (ED_TotalFrames >= 4) { ED_FrameTime_04 = get_config_int(ED_State_s, "FrameTime_04", 6) - 1; }
    if (ED_TotalFrames >= 5) { ED_FrameTime_05 = get_config_int(ED_State_s, "FrameTime_05", 6) - 1; }
    if (ED_TotalFrames >= 6) { ED_FrameTime_06 = get_config_int(ED_State_s, "FrameTime_06", 6) - 1; }
    if (ED_TotalFrames >= 7) { ED_FrameTime_07 = get_config_int(ED_State_s, "FrameTime_07", 6) - 1; }
    if (ED_TotalFrames >= 8) { ED_FrameTime_08 = get_config_int(ED_State_s, "FrameTime_08", 6) - 1; }
    if (ED_TotalFrames >= 9) { ED_FrameTime_09 = get_config_int(ED_State_s, "FrameTime_09", 6) - 1; }
    if (ED_TotalFrames >= 10) { ED_FrameTime_10 = get_config_int(ED_State_s, "FrameTime_10", 6) - 1; }
    if (ED_TotalFrames >= 11) { ED_FrameTime_11 = get_config_int(ED_State_s, "FrameTime_11", 6) - 1; }
    if (ED_TotalFrames >= 12) { ED_FrameTime_12 = get_config_int(ED_State_s, "FrameTime_12", 6) - 1; }
    if (ED_TotalFrames >= 13) { ED_FrameTime_13 = get_config_int(ED_State_s, "FrameTime_13", 6) - 1; }
    if (ED_TotalFrames >= 14) { ED_FrameTime_14 = get_config_int(ED_State_s, "FrameTime_14", 6) - 1; }
    if (ED_TotalFrames >= 15) { ED_FrameTime_15 = get_config_int(ED_State_s, "FrameTime_15", 6) - 1; }
    if (ED_TotalFrames >= 16) { ED_FrameTime_16 = get_config_int(ED_State_s, "FrameTime_16", 6) - 1; }
    if (ED_TotalFrames >= 17) { ED_FrameTime_17 = get_config_int(ED_State_s, "FrameTime_17", 6) - 1; }
    if (ED_TotalFrames >= 18) { ED_FrameTime_18 = get_config_int(ED_State_s, "FrameTime_18", 6) - 1; }
    if (ED_TotalFrames >= 19) { ED_FrameTime_19 = get_config_int(ED_State_s, "FrameTime_19", 6) - 1; }
    if (ED_TotalFrames >= 20) { ED_FrameTime_20 = get_config_int(ED_State_s, "FrameTime_20", 6) - 1; }
    if (ED_TotalFrames >= 21) { ED_FrameTime_21 = get_config_int(ED_State_s, "FrameTime_21", 6) - 1; }
    if (ED_TotalFrames >= 22) { ED_FrameTime_22 = get_config_int(ED_State_s, "FrameTime_22", 6) - 1; }
    if (ED_TotalFrames >= 23) { ED_FrameTime_23 = get_config_int(ED_State_s, "FrameTime_23", 6) - 1; }
    if (ED_TotalFrames >= 24) { ED_FrameTime_24 = get_config_int(ED_State_s, "FrameTime_24", 6) - 1; }
    if (ED_TotalFrames >= 25) { ED_FrameTime_25 = get_config_int(ED_State_s, "FrameTime_25", 6) - 1; }
    if (ED_TotalFrames >= 26) { ED_FrameTime_26 = get_config_int(ED_State_s, "FrameTime_26", 6) - 1; }
    if (ED_TotalFrames >= 27) { ED_FrameTime_27 = get_config_int(ED_State_s, "FrameTime_27", 6) - 1; }
    if (ED_TotalFrames >= 28) { ED_FrameTime_28 = get_config_int(ED_State_s, "FrameTime_28", 6) - 1; }
    if (ED_TotalFrames >= 29) { ED_FrameTime_29 = get_config_int(ED_State_s, "FrameTime_29", 6) - 1; }

    //salva o tempo de animacao 6 (se o tempo do frame for vazio, usa 6, que é o padrao)
    if (ED_TotalFrames >= 0 && ED_FrameTime_00 == 5) { set_config_int(ED_State_s, "FrameTime_00", ED_FrameTime_00+1); }
    if (ED_TotalFrames >= 1 && ED_FrameTime_01 == 5) { set_config_int(ED_State_s, "FrameTime_01", ED_FrameTime_01+1); }
    if (ED_TotalFrames >= 2 && ED_FrameTime_02 == 5) { set_config_int(ED_State_s, "FrameTime_02", ED_FrameTime_02+1); }
    if (ED_TotalFrames >= 3 && ED_FrameTime_03 == 5) { set_config_int(ED_State_s, "FrameTime_03", ED_FrameTime_03+1); }
    if (ED_TotalFrames >= 4 && ED_FrameTime_04 == 5) { set_config_int(ED_State_s, "FrameTime_04", ED_FrameTime_04+1); }
    if (ED_TotalFrames >= 5 && ED_FrameTime_05 == 5) { set_config_int(ED_State_s, "FrameTime_05", ED_FrameTime_05+1); }
    if (ED_TotalFrames >= 6 && ED_FrameTime_06 == 5) { set_config_int(ED_State_s, "FrameTime_06", ED_FrameTime_06+1); }
    if (ED_TotalFrames >= 7 && ED_FrameTime_07 == 5) { set_config_int(ED_State_s, "FrameTime_07", ED_FrameTime_07+1); }
    if (ED_TotalFrames >= 8 && ED_FrameTime_08 == 5) { set_config_int(ED_State_s, "FrameTime_08", ED_FrameTime_08+1); }
    if (ED_TotalFrames >= 9 && ED_FrameTime_09 == 5) { set_config_int(ED_State_s, "FrameTime_09", ED_FrameTime_09+1); }
    if (ED_TotalFrames >= 10 && ED_FrameTime_10 == 5) { set_config_int(ED_State_s, "FrameTime_10", ED_FrameTime_10+1); }
    if (ED_TotalFrames >= 11 && ED_FrameTime_11 == 5) { set_config_int(ED_State_s, "FrameTime_11", ED_FrameTime_11+1); }
    if (ED_TotalFrames >= 12 && ED_FrameTime_12 == 5) { set_config_int(ED_State_s, "FrameTime_12", ED_FrameTime_12+1); }
    if (ED_TotalFrames >= 13 && ED_FrameTime_13 == 5) { set_config_int(ED_State_s, "FrameTime_13", ED_FrameTime_13+1); }
    if (ED_TotalFrames >= 14 && ED_FrameTime_14 == 5) { set_config_int(ED_State_s, "FrameTime_14", ED_FrameTime_14+1); }
    if (ED_TotalFrames >= 15 && ED_FrameTime_15 == 5) { set_config_int(ED_State_s, "FrameTime_15", ED_FrameTime_15+1); }
    if (ED_TotalFrames >= 16 && ED_FrameTime_16 == 5) { set_config_int(ED_State_s, "FrameTime_16", ED_FrameTime_16+1); }
    if (ED_TotalFrames >= 17 && ED_FrameTime_17 == 5) { set_config_int(ED_State_s, "FrameTime_17", ED_FrameTime_17+1); }
    if (ED_TotalFrames >= 18 && ED_FrameTime_18 == 5) { set_config_int(ED_State_s, "FrameTime_18", ED_FrameTime_18+1); }
    if (ED_TotalFrames >= 19 && ED_FrameTime_19 == 5) { set_config_int(ED_State_s, "FrameTime_19", ED_FrameTime_19+1); }
    if (ED_TotalFrames >= 20 && ED_FrameTime_20 == 5) { set_config_int(ED_State_s, "FrameTime_20", ED_FrameTime_20+1); }
    if (ED_TotalFrames >= 21 && ED_FrameTime_21 == 5) { set_config_int(ED_State_s, "FrameTime_21", ED_FrameTime_21+1); }
    if (ED_TotalFrames >= 22 && ED_FrameTime_22 == 5) { set_config_int(ED_State_s, "FrameTime_22", ED_FrameTime_22+1); }
    if (ED_TotalFrames >= 23 && ED_FrameTime_23 == 5) { set_config_int(ED_State_s, "FrameTime_23", ED_FrameTime_23+1); }
    if (ED_TotalFrames >= 24 && ED_FrameTime_24 == 5) { set_config_int(ED_State_s, "FrameTime_24", ED_FrameTime_24+1); }
    if (ED_TotalFrames >= 25 && ED_FrameTime_25 == 5) { set_config_int(ED_State_s, "FrameTime_25", ED_FrameTime_25+1); }
    if (ED_TotalFrames >= 26 && ED_FrameTime_26 == 5) { set_config_int(ED_State_s, "FrameTime_26", ED_FrameTime_26+1); }
    if (ED_TotalFrames >= 27 && ED_FrameTime_27 == 5) { set_config_int(ED_State_s, "FrameTime_27", ED_FrameTime_27+1); }
    if (ED_TotalFrames >= 28 && ED_FrameTime_28 == 5) { set_config_int(ED_State_s, "FrameTime_28", ED_FrameTime_28+1); }
    if (ED_TotalFrames >= 29 && ED_FrameTime_29 == 5) { set_config_int(ED_State_s, "FrameTime_29", ED_FrameTime_29+1); }
}

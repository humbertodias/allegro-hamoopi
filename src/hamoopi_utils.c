// hamoopi_utils.c - Utility functions extracted from HAMOOPI.c
// Input slot management and utility functions

#include "platform_compat.h"
#include "hamoopi_core.h"

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

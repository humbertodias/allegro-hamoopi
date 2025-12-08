#ifndef HAMOOPI_FSM_H
#define HAMOOPI_FSM_H

#include "hamoopi_types.h"

// Funções da Máquina de Estados (FSM)
void PLAYER_STATE(int Player, int State, int AnimIndex, int P1_QtdeFrames);
void AddTableAtlas(int PlayerInd, int State, int AnimIndex, int TotImg);
void LOAD_PLAYERS();
void New_Fireball(int Player);

#endif // HAMOOPI_FSM_H

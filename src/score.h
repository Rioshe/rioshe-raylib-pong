#ifndef SCORE_H
#define SCORE_H
#include "stdbool.h"

void Score_IncrementPlayerOne(void);
void Score_IncrementPlayerTwo(void);
int Score_GetPlayerOne(void);
int Score_GetPlayerTwo(void);
void Score_Init(void);
void Score_Draw(void);
bool Score_DidAnyoneWin(void);
bool Score_DidPlayerOneWin(void);
bool Score_DidPlayerTwoWin(void);

#endif
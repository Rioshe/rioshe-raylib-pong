#ifndef SCORE_H
#define SCORE_H
#include "stdbool.h"

static int s_playerOneScore = 0;
static int s_playerTwoScore = 0;

void Score_IncrementPlayerOne(void);
void Score_IncrementPlayerTwo(void);
int Score_GetPlayerOne();
int Score_GetPlayerTwo();
void Score_Init();
void Score_Draw(void);
bool Score_DidAnyoneWin();
bool Score_DidPlayerOneWin();
bool Score_DidPlayerTwoWin();

#endif
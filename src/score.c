#include "score.h"
#include "raylib.h"
#include "config.h"

static int s_playerOneScore = 0;
static int s_playerTwoScore = 0;

void Score_IncrementPlayerOne(void)
{
    s_playerOneScore+=1;
}

void Score_IncrementPlayerTwo(void)
{
    s_playerTwoScore+=1;
}

int Score_GetPlayerOne(void){
    return s_playerOneScore;
}

int Score_GetPlayerTwo(void){
    return s_playerTwoScore;
}

void Score_Init(void){
    s_playerOneScore = 0;
    s_playerTwoScore = 0;
}

bool Score_DidAnyoneWin(void)
{
    return Score_DidPlayerOneWin() || Score_DidPlayerTwoWin();
}

bool Score_DidPlayerOneWin(void){
    return s_playerOneScore >= GAME_SCORE_TO_WIN;
}

bool Score_DidPlayerTwoWin(void){
    return s_playerTwoScore >= GAME_SCORE_TO_WIN;
}

void Score_Draw(void)
{
    DrawText(TextFormat("%d", s_playerOneScore), 10, 10, 20, WHITE);

    const char* playerTwoScoreText = TextFormat("%d", s_playerTwoScore);
    int fontSize = 20;
    int textWidth = MeasureText(playerTwoScoreText,fontSize);
    DrawText(playerTwoScoreText, CORE_SCREEN_WIDTH - (10+textWidth), 10, fontSize, WHITE);
}
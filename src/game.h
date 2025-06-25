#ifndef GAME_H
#define GAME_H
typedef enum GameState{
    GAMESTATE_NONE = -1,
    GAMESTATE_INITIALISE,
    GAMESTATE_WAITING_FOR_INPUT,
    GAMESTATE_IN_PROGRESS,
    GAMESTATE_POINT_SCORED,
    GAMESTATE_GAME_OVER,
} GameState;

typedef enum PLAYER{
    ONE,
    TWO,
    AI
};

void Game_Init(void);
void Game_Update(void);
void Game_Draw(void);
void Game_Reset(void);
void Game_Shutdown(void);
#endif
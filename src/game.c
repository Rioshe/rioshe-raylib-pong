#include "game.h"
#include "ball.h"
#include "paddles.h"
#include "collision.h"
#include "score.h"
#include "config.h"
#include "sound.h"

static GameState _GameState = GAMESTATE_NONE;
bool g_debugMode = false;

void Game_SetGameState(GameState newState);
void Game_Initialise(void);
void Game_WaitingForInput(void);
void Game_InProgress(void);
void Game_PointScored(void);
void Game_GameOver(void);


void Game_Init(void){
    Game_SetGameState(GAMESTATE_INITIALISE);
}

void Game_Update()
{
    if (IsKeyPressed(KEY_F1)) {
        g_debugMode = !g_debugMode;
    }


    switch (_GameState)
    {
        case GAMESTATE_INITIALISE:
            Game_Initialise();
            break;
        case GAMESTATE_WAITING_FOR_INPUT:
            Game_WaitingForInput();
            break;
        case GAMESTATE_IN_PROGRESS:
            Game_InProgress();
            break;
        case GAMESTATE_POINT_SCORED:
            Game_PointScored();
        case GAMESTATE_GAME_OVER:
            Game_GameOver();
            break;
        default:
            break;
    }

    Score_Draw();
}

void Game_SetGameState(GameState newState){
    if(_GameState != newState){
        _GameState = newState;
    }
}

void Game_Initialise(void){
    Sound_Init();
    Score_Init();
    Ball_Init();
    Paddles_Init();
    Game_SetGameState(GAMESTATE_WAITING_FOR_INPUT);
}

void Game_WaitingForInput(void){

    const char* startMessage = "PRESS SPACE TO START";
    int fontSize = 20;
    int textWidth = MeasureText(startMessage, fontSize);
    DrawText(startMessage, (CORE_SCREEN_WIDTH - textWidth)/2, CORE_SCREEN_HEIGHT / 2 - 100, 20, YELLOW);
    if(IsKeyPressed(KEY_SPACE)){
        Game_SetGameState(GAMESTATE_IN_PROGRESS);
    }
}

void Game_InProgress(void)
{
    Collision_Update();
    Ball_Update();
    Paddles_Update();

    if(Collision_CheckOutOfBounds()){
        Game_SetGameState(GAMESTATE_POINT_SCORED);
    }
}

void Game_PointScored(void)
{
    if(Score_DidAnyoneWin())
    {
        Game_SetGameState(GAMESTATE_GAME_OVER);
    }
    else
    {
        Sound_PlayScored();
        Game_Reset();
        Game_SetGameState(GAMESTATE_WAITING_FOR_INPUT);
    }

}

void Game_GameOver(){

    char* winScreenMessage;
    if (Score_DidPlayerOneWin())
    {
        winScreenMessage = "PLAYER ONE WINS!";
    }

    if (Score_DidPlayerTwoWin())
    {
        winScreenMessage = "PLAYER TWO WINS!";
    }

    int fontSize = 30;
    int textWidth = MeasureText(winScreenMessage, fontSize);
    DrawText(winScreenMessage, (CORE_SCREEN_WIDTH - textWidth)/2, CORE_SCREEN_HEIGHT / 2, fontSize, YELLOW);

    const char* subMessage = "PRESS R TO RESTART";
    fontSize = 20;
    textWidth = MeasureText(subMessage, fontSize);
    DrawText(subMessage, (CORE_SCREEN_WIDTH - textWidth)/2, CORE_SCREEN_HEIGHT / 2 - 100, fontSize, YELLOW);

    if(IsKeyPressed(KEY_R))
    {
        Game_SetGameState(GAMESTATE_INITIALISE);
    }
}

void Game_Draw(){
    Ball_Draw();
    Paddles_Draw();
}

void Game_Reset(){
    Ball_Reset();
    Paddles_Reset();
}

void Game_Shutdown(){
    Ball_Destroy();
    Paddles_Destroy();
    Sound_Cleanup();
}
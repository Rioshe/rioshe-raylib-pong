#include "game.h"
#include "ball.h"
#include "paddles.h"
#include "collision.h"
#include "score.h"
#include "config.h"
#include "sound.h"

static GameState _GameState = GAMESTATE_NONE;
bool g_debugMode = false;

void Game_Init(){
    _Game_SetGameState(GAMESTATE_INITIALISE);
}

void Game_Update()
{
    if (IsKeyPressed(KEY_F1)) {
        g_debugMode = !g_debugMode;
    }


    switch (_GameState)
    {
        case GAMESTATE_INITIALISE:
            _Game_Initialise();
            break;
        case GAMESTATE_WAITING_FOR_INPUT:
            _Game_WaitingForInput();
            break;
        case GAMESTATE_IN_PROGRESS:
            _Game_InProgress();
            break;
        case GAMESTATE_POINT_SCORED:
            _Game_PointScored();
        case GAMESTATE_GAME_OVER:
            _Game_GameOver();
            break;
        default:
            break;
    }

    Score_Draw();
}

void _Game_SetGameState(GameState newState){
    if(_GameState != newState){
        _GameState = newState;
    }
}

void _Game_Initialise(){
    Sound_Init();
    Score_Init();
    Ball_Init();
    Paddles_Init();
    _Game_SetGameState(GAMESTATE_WAITING_FOR_INPUT);
}

void _Game_WaitingForInput(){

    const char* startMessage = "PRESS SPACE TO START";
    int fontSize = 20;
    int textWidth = MeasureText(startMessage, fontSize);
    DrawText(startMessage, (CORE_SCREEN_WIDTH - textWidth)/2, CORE_SCREEN_HEIGHT / 2 - 100, 20, YELLOW);
    if(IsKeyPressed(KEY_SPACE)){
        _Game_SetGameState(GAMESTATE_IN_PROGRESS);
    }
}

void _Game_InProgress()
{
    Collision_Update();
    Ball_Update();
    Paddles_Update();

    if(Collision_CheckOutOfBounds()){
        _Game_SetGameState(GAMESTATE_POINT_SCORED);
    }
}

void _Game_PointScored()
{
    printf("%d %d", Score_GetPlayerOne(), Score_GetPlayerTwo());
    if(Score_DidAnyoneWin())
    {
        _Game_SetGameState(GAMESTATE_GAME_OVER);
    }
    else
    {
        Sound_PlayScored();
        Game_Reset();
        _Game_SetGameState(GAMESTATE_WAITING_FOR_INPUT);
    }

}

void _Game_GameOver(){

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
        _Game_SetGameState(GAMESTATE_INITIALISE);
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
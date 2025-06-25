#include "game.h"
#include "ball.h"
#include "paddles.h"
#include "collision.h"
#include "score.h"

static GameState _GameState = GAMESTATE_NONE;

void Game_Init(){
    _Game_SetGameState(GAMESTATE_INITIALISE);
}

void Game_Update()
{
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
    Ball_Init();
    Paddles_Init();
    _Game_SetGameState(GAMESTATE_WAITING_FOR_INPUT);
}

void _Game_WaitingForInput(){
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

void _Game_PointScored(){
    Game_Reset();
    _Game_SetGameState(GAMESTATE_WAITING_FOR_INPUT);
}

void _Game_GameOver(){

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
}
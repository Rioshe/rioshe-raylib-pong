#include "raylib.h"
#include "game.h"
#include "config.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main(void)
{
    InitWindow(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(MAIN_TARGET_FPS);

    Game_Init();

    while (!WindowShouldClose())
    {
        Game_Update();

        BeginDrawing();
        ClearBackground(BLACK);

        Game_Draw();

        EndDrawing();
    }

    Game_Shutdown();
    CloseWindow();
    return 0;
}

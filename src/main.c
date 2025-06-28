#include "raylib.h"
#include "game.h"
#include "config.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main(void)
{
    InitWindow(CORE_SCREEN_WIDTH, CORE_SCREEN_HEIGHT, CORE_WINDOW_TITLE);
    SetTargetFPS(CORE_TARGET_FPS);
    InitAudioDevice();
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

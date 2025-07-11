#include "ball.h"
#include "assets.h"
#include "config.h"
#include "paddles.h"

static Ball s_ball;
static Texture2D s_textureBall;

void Ball_Setup(void);
void Ball_SwitchDirectionY(void);


void Ball_Init(void){
    s_textureBall = LoadTexture(TEXTURE_BALL_BLUE);
    Ball_Setup();
}

void Ball_Setup(void){
    Rectangle srcRect = {0,0, BALL_WIDTH, BALL_HEIGHT};
    Rectangle dstRect = {CORE_SCREEN_WIDTH/2, CORE_SCREEN_HEIGHT/2, BALL_WIDTH, BALL_HEIGHT};

    s_ball.srcRect = srcRect;
    s_ball.dstRect = dstRect;

    s_ball.direction = (Vector2){
        GetRandomValue(0, 1) == 0 ? -1 : 1,
        GetRandomValue(0, 1) == 0 ? -1 : 1
    };

    s_ball.origin = (Vector2){BALL_WIDTH/2, BALL_HEIGHT/2};
    s_ball.speed = (Vector2){BALL_SPEED, BALL_SPEED};
    s_ball.radius = BALL_RADIUS;
}

void Ball_Update(void)
{
    float deltaTime = GetFrameTime();

    s_ball.dstRect.x += s_ball.speed.x * s_ball.direction.x * deltaTime;
    s_ball.dstRect.y += s_ball.speed.y * s_ball.direction.y * deltaTime;

    if (s_ball.dstRect.y > CORE_SCREEN_HEIGHT - s_textureBall.height || s_ball.dstRect.y < 0)
    {
        Ball_SwitchDirectionY();
    }
}


void Ball_Draw(void){
    DrawTexturePro(s_textureBall, s_ball.srcRect, s_ball.dstRect, s_ball.origin,0, WHITE);

    if(g_debugMode)
    {
        DrawCircleLines(s_ball.dstRect.x, s_ball.dstRect.y, s_ball.radius, RED);
    }
}

void Ball_Reset(void){
    Ball_Setup();
}

void Ball_Destroy(void){
    UnloadTexture(s_textureBall);
}

Ball* Ball_Get(void){
    return &s_ball;
}

void Ball_SwitchDirectionX(void){
    s_ball.direction.x *= -1;
    s_ball.speed.x = s_ball.speed.x + BALL_SPEED_INCREMENT;
}

void Ball_SwitchDirectionY(){
    s_ball.direction.y *= -1;
}
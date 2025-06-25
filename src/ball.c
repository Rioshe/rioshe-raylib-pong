#include "ball.h"
#include "assets.h"
#include "config.h"
#include "paddles.h"

static Ball s_ball;
static Texture2D s_textureBall;

void Ball_Init(){
    s_textureBall = LoadTexture(TEXTURE_BALL_BLUE);
    _Ball_Init();
}

void _Ball_Init(){
    Rectangle srcRect = {0,0, BALL_WIDTH, BALL_HEIGHT};
    Rectangle dstRect = {GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2, BALL_WIDTH, BALL_HEIGHT};

    s_ball.srcRect = srcRect;
    s_ball.dstRect = dstRect;

    s_ball.direction = (Vector2){1, 1};
    s_ball.origin = (Vector2){BALL_WIDTH/2, BALL_HEIGHT/2};
    s_ball.velocity = (Vector2){BALL_SPEED, BALL_SPEED};
    s_ball.radius = BALL_RADIUS;
}

void Ball_Update()
{
    float deltaTime = GetFrameTime();

    s_ball.dstRect.x += s_ball.velocity.x * s_ball.direction.x * deltaTime;
    s_ball.dstRect.y += s_ball.velocity.y * s_ball.direction.y * deltaTime;

    if (s_ball.dstRect.y > GAME_SCREEN_HEIGHT - s_textureBall.height || s_ball.dstRect.y < 0)
    {
        _Ball_SwitchDirectionY();
    }
}


void Ball_Draw(){
    DrawTexturePro(s_textureBall, s_ball.srcRect, s_ball.dstRect, s_ball.origin,0, WHITE);
    DrawCircleLines(s_ball.dstRect.x, s_ball.dstRect.y, s_ball.radius, RED);
}

void Ball_Reset(){
    _Ball_Init();
}

void Ball_Destroy(){
    UnloadTexture(s_textureBall);
}

Ball* Ball_Get(){
    return &s_ball;
}

void Ball_SwitchDirectionX(){
    s_ball.direction.x *= -1;
}

void _Ball_SwitchDirectionY(){
    s_ball.direction.y *= -1;
}
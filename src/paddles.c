#include "paddles.h"
#include "config.h"

static Texture2D s_textureLeftPaddle;
static Texture2D s_textureRightPaddle;
static Paddle s_paddleLeft;
static Paddle s_paddleRight;


void Paddles_Setup(void);
void Paddle_Init(Paddle* paddle, 
    Rectangle srcRect, 
    Rectangle dstRect,
    Vector2 origin,
    int upKey, 
    int downKey);
void Paddle_Update(Paddle* paddle);
void Paddle_Draw(Texture2D texture, Paddle* paddle);



void Paddles_Init(void)
{
    s_textureLeftPaddle = LoadTexture(TEXTURE_PADDLE_BLUE);
    s_textureRightPaddle = LoadTexture(TEXTURE_PADDLE_RED);

    Paddles_Setup();
}

void Paddles_Setup(void){
    Rectangle sourceRect = {0, 0, PADDLE_WIDTH, PADDLE_HEIGHT};
    Vector2 origin = {PADDLE_WIDTH/2, PADDLE_HEIGHT/2};

    float paddlePositionY = CORE_SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2;
    Rectangle dstRectLeft = {50 - PADDLE_WIDTH, paddlePositionY, PADDLE_WIDTH, PADDLE_HEIGHT};
    Paddle_Init(&s_paddleLeft, sourceRect, dstRectLeft, origin, KEY_W, KEY_S);

    Rectangle dstRectRight = {CORE_SCREEN_WIDTH - 50, paddlePositionY, PADDLE_WIDTH, PADDLE_HEIGHT};
    Paddle_Init(&s_paddleRight, sourceRect, dstRectRight, origin, KEY_UP, KEY_DOWN);
}

void Paddle_Init(Paddle* paddle, 
    Rectangle srcRect, 
    Rectangle dstRect,
    Vector2 origin,
    int upKey, 
    int downKey)
{
    paddle->speed = PADDLE_SPEED;
    paddle->upKey = upKey;
    paddle->downKey = downKey;
    paddle->srcRect = srcRect;
    paddle->dstRect = dstRect;
}

void Paddles_Update(void){
    Paddle_Update(&s_paddleLeft);
    Paddle_Update(&s_paddleRight);
}

void Paddle_Update(Paddle* paddle){
    float dt = GetFrameTime();
    if (IsKeyDown(paddle->upKey)) 
    {
        float yPosition = paddle->dstRect.y - (paddle->speed * dt);
        yPosition = yPosition < 0? 0 : yPosition;
        paddle->dstRect.y = yPosition;
    }
    
    if (IsKeyDown(paddle->downKey))
    {
        float yPosition = paddle->dstRect.y + (paddle->speed * dt);
        yPosition = yPosition > CORE_SCREEN_HEIGHT - paddle->dstRect.height? CORE_SCREEN_HEIGHT - paddle->dstRect.height: yPosition;
        paddle->dstRect.y = yPosition;
    }
}

void Paddles_Draw(void){
    Paddle_Draw(s_textureLeftPaddle, &s_paddleLeft);
    Paddle_Draw(s_textureRightPaddle, &s_paddleRight);

    if(g_debugMode)
    {
        DrawRectangleLinesEx(s_paddleLeft.dstRect, 2, GREEN);
        DrawRectangleLinesEx(s_paddleRight.dstRect, 2, GREEN);

    }
}

void Paddle_Draw(Texture2D texture, Paddle* paddle){
    DrawTexturePro(texture, paddle->srcRect, paddle->dstRect, paddle->origin, 0, WHITE);
}

void Paddles_Reset(void){
    Paddles_Setup();
}


void Paddles_Destroy(void){
    UnloadTexture(s_textureLeftPaddle);
    UnloadTexture(s_textureRightPaddle);
}

Rectangle* Paddles_GetLeftRectangle(void){
    return &s_paddleLeft.dstRect;
}

Rectangle* Paddles_GetRightRectangle(void){
    return &s_paddleRight.dstRect;
}
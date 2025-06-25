#ifndef PADDLES_H
#define PADDLES_H
#include "raylib.h"
#include "assets.h"
#include "config.h"

typedef struct PaddleData
{
    float speed;
    int upKey;
    int downKey;
    Rectangle srcRect;
    Rectangle dstRect;
    Vector2 origin;
    float rotation;
} Paddle;


void Paddles_Init(void);
void Paddles_Update(void);
void Paddles_Draw(void);

Rectangle* Paddles_GetLeftRectangle(void);
Rectangle* Paddles_GetRightRectangle(void);

void Paddles_Reset(void);
void Paddles_Destroy(void);
#endif
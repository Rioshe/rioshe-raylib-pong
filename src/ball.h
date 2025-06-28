#ifndef BALL_H
#define BALL_H

#include "raylib.h"

typedef struct BallData
{
    Rectangle srcRect;
    Rectangle dstRect;
    Vector2 direction;
    Vector2 speed;
    Vector2 origin;
    float radius;
} Ball;

//Core
void Ball_Init(void);
void Ball_Update(void);
void Ball_Draw(void);
void Ball_CollisionCheck(void);
void Ball_Reset(void);
void Ball_Destroy(void);

//Helpers
Ball* Ball_Get(void);
void Ball_SwitchDirectionX(void);


#endif
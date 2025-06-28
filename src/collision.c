#include "collision.h"
#include "ball.h"
#include "paddles.h"
#include "config.h"
#include "score.h"
#include "sound.h"

void Collision_Update(){
    Ball* ball = Ball_Get();
    Rectangle* paddleLeftRect = Paddles_GetLeftRectangle();
    Rectangle* paddleRightRect = Paddles_GetRightRectangle();

    Vector2 ballPosition = (Vector2){ball->dstRect.x, ball->dstRect.y};
    float ballRadius = ball->radius;
    bool isCollidingWithLeftPaddle = CheckCollisionCircleRec(ballPosition, ballRadius, *paddleLeftRect);
    bool isCollidingWithRightPaddle = CheckCollisionCircleRec(ballPosition, ballRadius, *paddleRightRect);
    
    if (isCollidingWithLeftPaddle || isCollidingWithRightPaddle)
    {
        Sound_PlayHit();
        Ball_SwitchDirectionX();  // flip X
    }
}

bool Collision_CheckOutOfBounds()
{    
    bool isOutOfBounds = false;
    Ball* ball = Ball_Get();
    Vector2 ballPosition = (Vector2){ball->dstRect.x, ball->dstRect.y};

    if(ballPosition.x > CORE_SCREEN_WIDTH){
        Score_IncrementPlayerOne();
        isOutOfBounds = true;
    }

    if(ballPosition.x < 0){
        Score_IncrementPlayerTwo();
        isOutOfBounds = true;
    }

    return isOutOfBounds;

}
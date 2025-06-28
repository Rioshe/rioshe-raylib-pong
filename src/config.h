#ifndef CONFIG_H
#define CONFIG_H

extern bool g_debugMode;

#define CORE_SCREEN_WIDTH 1920/2
#define CORE_SCREEN_HEIGHT 1080/2
#define CORE_WINDOW_TITLE "Rioshe raylib pong"
#define CORE_TARGET_FPS 60

#define GAME_SCORE_TO_WIN 3

#define PADDLE_SPEED 500
#define PADDLE_WIDTH 24
#define PADDLE_HEIGHT 104

#define BALL_SPEED 200
#define BALL_SPEED_INCREMENT 100
#define BALL_HEIGHT 22
#define BALL_WIDTH 22
#define BALL_RADIUS 11

#endif
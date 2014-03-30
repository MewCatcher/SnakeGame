/**
 * Name: Snake Game
 * Author: MewCatcher
 * Date: 03/25/14
 * Description: This game is an uncommen snake game, it's with AI!
 * Funtion: Main.h contains the globle variables.
 **/

#ifndef _MAIN_H_
#define _MAIN_H_

#include "gameworld.h"
#include "snake.h"
#include "snakeai.h"
#include <GL/gl.h>
#include <GL/freeglut.h>

/* Main globle constanta */
static const int Pixel = 26;
static const int WordsHeight = 1; // pixeles for showing words
static const int width = 600, height = width / Pixel * ( Pixel + WordsHeight );

/* Main globle variables */
static GameWorld gw;
static Snake *PlayerSnake;
static SnakeAI **AISnake;

#endif

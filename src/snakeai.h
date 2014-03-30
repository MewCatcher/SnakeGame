/**
 * FileName: snakeai.h
 * Author: MewCather
 * Date: 03/28/14
 * Description: This file define the class "SnakeAI", whitch process all the
 *              snake's actions. It will think like a human XD
 * Using: A* algorithm
 **/

#ifndef _SNAKEAI_H_
#define _SNAKEAI_H_

#include "gameworld.h"
#include "snake.h"

class SnakeAI : Snake {
public:
    SnakeAI( int id, GameWorld &gw_in );
    ~SnakeAI( );
    
    void setAILevel( int lv );
    void receiveReCalcMsg( );
    
private:
    int AILevel;       // 1 - easy; 2 - medium; 3 - hard; 4 - Smarter than human
    
};

#endif

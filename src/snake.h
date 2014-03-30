/**
 * FileName: snake.h
 * Author: MewCather
 * Date: 03/27/14
 * Description: This file define the class "Snake", whitch process all the
 *              snake's actions. ( Bad designed... )
 **/

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "gameworld.h"

class Snake {
public:
    Snake( int id, GameWorld &gw_in );
    ~Snake( );
    int getID( ) const;
    
    bool SendKeyEvent( int key, int x, int y );
    
    virtual void receiveReCalcMsg( );
    
private:
    int SnakeID;
    GameWorld &GW;
    
};

#endif

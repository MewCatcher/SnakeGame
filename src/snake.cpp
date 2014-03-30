/**
 * FileName: snake.cpp
 * Author: MewCather
 * Date: 03/27/14
 * Description: see header
 * Using: A* algorithm
 **/

#include "snake.h"

Snake::Snake( int id, GameWorld &gw_in ) : SnakeID( id ), GW( gw_in )
{
    return;
}

Snake::~Snake( )
{
    return;
}

int Snake::getID( ) const
{
    return SnakeID;
}

bool Snake::SendKeyEvent( int key, int x, int y )
{
    return GW.SendKeyEvent( SnakeID, key, x, y );
}

void Snake::receiveReCalcMsg( )
{
    // For AI to computing the path
    return;
}

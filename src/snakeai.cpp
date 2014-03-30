/**
 * FileName: snakeai.cpp
 * Author: MewCather
 * Date: 03/28/14
 * Description: see header file
 **/

#include "snakeai.h"


SnakeAI::SnakeAI( int id, GameWorld &gw_in ) : Snake( id, gw_in )
{
    AILevel = 1;
    return;
}

SnakeAI::~SnakeAI( )
{
    return;
}

void SnakeAI::setAILevel( int lv )
{
    if( 1 <= lv && lv <= 4 ) AILevel = lv;
    return;
}

void SnakeAI::receiveReCalcMsg( )
{
    
    switch( AILevel ) {
    case 1: // easy
        
        break;
        
    case 2: // medium
        break;
        
    case 3: // hard
        break;
        
    case 4: // Smarter than human
        break;
        
    default: // ERROR
        break;
    }
    return;
}
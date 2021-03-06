/**
 * FileName: gameworld.cpp
 * Author: MewCather
 * Date: 03/25/14
 * Description: see header
 **/

#include "gameworld.h"
#include "freetype.h"
#include "main.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


GameWorld::GameWorld( )
{
    CurrentScence = GameScreen;
    GameSpeed = GAMESPEED;
    CurrentPlayer = 0;
    GameStatus = 0;
    StatusID = 0;
    CurrentAILevel = 1;
    ThingPos[ 0 ][ 0 ] = ThingPos[ 0 ][ 1 ] = ThingPos[ 1 ][ 0 ] = ThingPos[ 1 ][ 1 ]
                       = ThingPos[ 2 ][ 0 ] = ThingPos[ 2 ][ 1 ] = 0; // Thing initial
    srand( time( NULL ) ); 
    
    /* Generate game world table */
    WorldTable = new unsigned char * [ Pixel ];
    for( int i = 0; i < Pixel; i ++ ) {
        WorldTable[ i ] = new unsigned char [ Pixel ];
        for( int j = 0; j < Pixel; j ++ ) {
            WorldTable[ i ][ j ] = 0x00;
            if( i == 0 || j == 0 || i == Pixel - 1 || j == Pixel - 1 )
                WorldTable[ i ][ j ] = 0xE0;
        }
    }
    
    return;
}

GameWorld::~GameWorld( )
{
    /* Remove game world table */
    for( int i = 0; i < Pixel; i ++ )
        delete [ ] WorldTable[ i ];
    delete [ ] *WorldTable;
    
    //for( int i = 1; i < CurrentPlayer; i ++ )
    //    delete AISnake[ i ];
    
    return;
}

void GameWorld::UpdateWorld( )
{
    switch( CurrentScence ) {
    case MainScreen: // Main Screen
        UpdateWorld_MainScreen( );
        break;
        
    case GameScreen: // Game Screen, containing paused screen
        UpdateWorld_GameScreen( );
        break;
        
    default:
        break;
    }
    return;
}

void GameWorld::setScence( SCENCE sc )
{
    CurrentScence = sc;
    return;
}

void GameWorld::startGame( )
{
    int CurrentPlayer_save = CurrentPlayer;
    CurrentPlayer = 0;
    
    for( int i = 0; i < Pixel; i ++ ) {
        for( int j = 0; j < Pixel; j ++ ) {
            WorldTable[ i ][ j ] = 0x00;
            if( i == 0 || j == 0 || i == Pixel - 1 || j == Pixel - 1 )
                WorldTable[ i ][ j ] = 0xE0;
        }
    }
    
    for( int i = 0; i < CurrentPlayer_save; i ++ ) {
        //if( AISnake[ i ] ) delete AISnake[ i ];
        //AISnake[ i ] = new AISnake( addSnake( ), gw, CurrentAILevel );
        addSnake( );
        SnakeStatus[ i ] = true;
    }
    
    // 0 - Not begin; 1 - In process; 2 - Win; 3 - Lose; 4 - Pause;
    addNewThing( );
    GameStatus = 1;
    
    return;
}
void GameWorld::PauseOrResume( )
{
    if( GameStatus == 1 ) GameStatus = 4;
    else if( GameStatus == 4 ) GameStatus = 1;
    else cerr << "GameStatus error in PauseOrResume( )" << endl;
    return;
}

int GameWorld::addSnake( )
{
    if( CurrentPlayer >= MaxSnake ) return MaxSnake - 1; // as the last one
    int id = CurrentPlayer ++;
    
    SnakeHeadPos[ id ][ 2 ] = 3;          // right direction
    SnakeHeadPos[ id ][ 1 ] = id * 5 + 5; // y
    SnakeHeadPos[ id ][ 0 ] = ( Pixel + SnakeInitialLength ) / 2; // x
    SnakeStatus[ id ] = true;
    
    WorldTable[ SnakeHeadPos[ id ][ 0 ] ][ SnakeHeadPos[ id ][ 1 ] ]
        = 0x20 | (unsigned char)id << 2 | 0x00; // left
    
    for( int i = 1; i < SnakeInitialLength - 1; i ++ ) {
        WorldTable[ SnakeHeadPos[ id ][ 0 ] - i ][ SnakeHeadPos[ id ][ 1 ] ]
            = 0x40 | (unsigned char)id << 2 | 0x00; // Body
    }
    
    WorldTable[ SnakeHeadPos[ id ][ 0 ] - SnakeInitialLength + 1 ][ SnakeHeadPos[ id ][ 1 ] ]
        = 0x60 | (unsigned char)id << 2 | 0x00; // Tail
        
    return id;
}

void GameWorld::goNextStatus( )
{
    if( GameStatus != 1 ) return; // provide more funtion
    //cerr<<"goNextStatus()"<<endl;
    for( int i = 0; i < CurrentPlayer; i ++ ) {
        if( i != 0 && !SnakeStatus[ i ] ) continue;
        if( i == 0 && !SnakeStatus[ i ] ) break; // Player death
        
        deleteTail( i, true );
        
        /* Set body */
        switch( SnakeHeadPos[ i ][ 2 ] ) {
        case 0: // to left
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] &= 0x1F;
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] |= 0x40;
            SnakeHeadPos[ i ][ 0 ] --;
            break;
        case 1: // to down
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] &= 0x1F;
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] |= 0x40;
            SnakeHeadPos[ i ][ 1 ] --;
            break;
        case 2: // to up
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] &= 0x1F;
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] |= 0x40;
            SnakeHeadPos[ i ][ 1 ] ++;
            break;
        case 3: // to right
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] &= 0x1F;
            WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] |= 0x40;
            SnakeHeadPos[ i ][ 0 ] ++;
            break;
        default:
            break;
        }
        
        switch( WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ] & 0xE0 ) { // Things
        case 0x00: // None
            switch( SnakeHeadPos[ i ][ 2 ] ) {
            case 0: // point to right
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x03;
                break;
            case 1: // point to up
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x02;
                break;
            case 2: // point to down
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x01;
                break;
            case 3: // point to left
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x00;
                break;
            default:
                break;
            }
            break;
            
        case 0x80: // Thing A // blue
        case 0xA0: // Thing B // green
        case 0xC0: // Thing C // red
            switch( SnakeHeadPos[ i ][ 2 ] ) {
            case 0: // point to right
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x03;
                break;
            case 1: // point to up
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x02;
                break;
            case 2: // point to down
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x01;
                break;
            case 3: // point to left
                WorldTable[ SnakeHeadPos[ i ][ 0 ] ][ SnakeHeadPos[ i ][ 1 ] ]
                    = 0x20 | (unsigned char)i << 2 | 0x00;
                break;
            default:
                break;
            }
            deleteTail( i, false );
            addNewThing( ); // Thing A/B/C was eaten
            break;
            
        default: // send death message
            SnakeStatus[ i ] = false;
            gameEnd( i );
            break;
        }
    }
    return;
}

void GameWorld::deleteTail( int id, bool backup )
{
    static int x_backup = 0, y_backup = 0, x_previous_backup = 0, y_previous_backup = 0;
    static unsigned char value_backup = 0x00, value_previous_backup = 0x00;
    
    if( !backup ) { // restore
        WorldTable[ x_backup ][ y_backup ] = value_backup;
        WorldTable[ x_previous_backup ][ y_previous_backup ] = value_previous_backup;
        return;
    }
    
    int temp_x = SnakeHeadPos[ id ][ 0 ];
    int temp_y = SnakeHeadPos[ id ][ 1 ];
    
    /*cerr << hex << (unsigned int)( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) << ' '
                << (unsigned int)( WorldTable[ temp_x - 1 ][ temp_y ] & 0xE0 ) << ' '
                << (unsigned int)( WorldTable[ temp_x - 2 ][ temp_y ] & 0xE0 ) << ' '
                << (unsigned int)( WorldTable[ temp_x - 3 ][ temp_y ] & 0xE0 ) << ' '
                << (unsigned int)( WorldTable[ temp_x - 4 ][ temp_y ] & 0xE0 ) << ' '
         << dec<< endl;*/
    
    while( ( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) != 0x60 ) {
        // && ( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) != 0x00 ) { // for safe
    //cerr << hex << (unsigned int)( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) << dec<< endl;
        switch( WorldTable[ temp_x ][ temp_y ] & 0x03 ) {
        case 0x00: // back left
            temp_x --;//cerr<<"1:x:"<<temp_x<<endl;
            if( ( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) == 0x60 ) { // set
                x_previous_backup = temp_x + 1;
                y_previous_backup = temp_y;
                value_previous_backup = WorldTable[ x_previous_backup ][ y_previous_backup ];
                WorldTable[ temp_x + 1 ][ temp_y ] &= 0x1F;
                WorldTable[ temp_x + 1 ][ temp_y ] |= 0x60;
            }
            break;
        case 0x01: // down
            temp_y --;//cerr<<"2:y:"<<temp_y<<endl;
            if( ( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) == 0x60 ) { // set
                x_previous_backup = temp_x;
                y_previous_backup = temp_y + 1;
                value_previous_backup = WorldTable[ x_previous_backup ][ y_previous_backup ];
                WorldTable[ temp_x ][ temp_y + 1 ] &= 0x1F;
                WorldTable[ temp_x ][ temp_y + 1 ] |= 0x60;
            }
            break;
        case 0x02: // up
            temp_y ++;//cerr<<"3:y:"<<temp_y<<endl;
            if( ( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) == 0x60 ) { // set
                x_previous_backup = temp_x;
                y_previous_backup = temp_y - 1;
                value_previous_backup = WorldTable[ x_previous_backup ][ y_previous_backup ];
                WorldTable[ temp_x ][ temp_y - 1 ] &= 0x1F;
                WorldTable[ temp_x ][ temp_y - 1 ] |= 0x60;
            }
            break;
        case 0x03: // right
            temp_x ++;//cerr<<"4:x:"<<temp_x<<endl;
            if( ( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) == 0x60 ) { // set
                x_previous_backup = temp_x - 1;
                y_previous_backup = temp_y;
                value_previous_backup = WorldTable[ x_previous_backup ][ y_previous_backup ];
                WorldTable[ temp_x - 1 ][ temp_y ] &= 0x1F;
                WorldTable[ temp_x - 1 ][ temp_y ] |= 0x60;
            }
            break;
        default:
            break;
        }
    //cerr << hex << (unsigned int)( WorldTable[ temp_x ][ temp_y ] & 0xE0 ) << dec<< endl;
    }
    
    x_backup = temp_x;
    y_backup = temp_y;
    value_backup = WorldTable[ temp_x ][ temp_y ];
    WorldTable[ temp_x ][ temp_y ] = 0;
    return;
}

bool GameWorld::SendKeyEvent( int id, int key, int x, int y )
{
    if( id >= CurrentPlayer ) return false;
    
    switch( key ) {
    case (int)' ':
        switch( GameStatus ) {
        case 0:
            startGame( );
            break;
        case 1:
        case 4:
            PauseOrResume( );
            break;
        case 2:
        case 3:
            break;
        default:
            return false;
        }
        break;
    case (int)'r':
    case (int)'R':
        if( GameStatus != 1 ) startGame( );
        break;
    case GLUT_KEY_LEFT:
        if( ( WorldTable[ SnakeHeadPos[ id ][ 0 ] ][ SnakeHeadPos[ id ][ 1 ] ] & 0x03 ) == 0x00 ) return false;
        else SnakeHeadPos[ id ][ 2 ] = 0x00;
        break;
    case GLUT_KEY_DOWN:
        if( ( WorldTable[ SnakeHeadPos[ id ][ 0 ] ][ SnakeHeadPos[ id ][ 1 ] ] & 0x03 ) == 0x01 ) return false;
        else SnakeHeadPos[ id ][ 2 ] = 0x01;
        break;
    case GLUT_KEY_UP:
        if( ( WorldTable[ SnakeHeadPos[ id ][ 0 ] ][ SnakeHeadPos[ id ][ 1 ] ] & 0x03 ) == 0x02 ) return false;
        else SnakeHeadPos[ id ][ 2 ] = 0x02;
        break;
    case GLUT_KEY_RIGHT:
        if( ( WorldTable[ SnakeHeadPos[ id ][ 0 ] ][ SnakeHeadPos[ id ][ 1 ] ] & 0x03 ) == 0x03 ) return false;
        else SnakeHeadPos[ id ][ 2 ] = 0x03;
        break;
    default:
        break;
    }
    
    UpdateWorld( );
    return true;
}

void GameWorld::gameEnd( int id )
{
    if( id != 0 ) return;
    
    int i = 1;
    for( ; i < CurrentPlayer; i ++ ) if( SnakeStatus[ i ] == true ) break;
    if( i == CurrentPlayer ) GameStatus = 2; // Win
    else GameStatus = 3;                     // Lose
    return;
}

void GameWorld::addNewThing( )
{
    for( int i = 0; i < 3; i ++ ) {
        switch( WorldTable[ ThingPos[ i ][ 0 ] ][ ThingPos[ i ][ 1 ] ] & 0xE0 ) {
        case 0x80:
        case 0xA0:
        case 0xC0:
            break;
        default:
            int loopSize = 0, r;
            for( int j = 1; j < Pixel - 1; j ++ )
                for( int k = 1; k < Pixel - 1; k ++ )
                    if( ( WorldTable[ j ][ k ] & 0xE0 ) == 0x00 ) loopSize ++; // get loop size
                    
            if( !loopSize ) goto ENDWHILE; // no space
            
            r = getRandomValue( 0, loopSize );
            while( r >= 0 ) {
                for( int j = 1; j < Pixel - 1; j ++ ) {
                    for( int k = 1; k < Pixel - 1; k ++ ) {
                        if( ( WorldTable[ j ][ k ] & 0xE0 ) == 0x00 && ( r -- == 0 ) ) {
                            ThingPos[ i ][ 0 ] = j;
                            ThingPos[ i ][ 1 ] = k;
                            WorldTable[ j ][ k ] =  (unsigned char)( i + 4 ) << 5;
                            goto ENDWHILE; // break the loop
                        }
                    }
                }
            }
            ENDWHILE: ;
            break;
        }
    }
    return;
}


/****************************************
 * 
 * Functions for get world information
 * 
 ****************************************/
float GameWorld::getGameSpeed( ) const
{
    return GameSpeed;
}
long long GameWorld::getStatusID( ) const
{
    return StatusID;
}
int GameWorld::getMaxSnake( ) const
{
    return MaxSnake;
}

int GameWorld::getMapWidth( ) const
{
    return width;
}
int GameWorld::getMapHeight( ) const
{
    return height;
}
int GameWorld::getHeadX( int id ) const
{
    return SnakeHeadPos[ id ][ 0 ];
}
int GameWorld::getHeadY( int id ) const
{
    return SnakeHeadPos[ id ][ 1 ];
}
int GameWorld::getHeadDir( int id ) const
{
    return SnakeHeadPos[ id ][ 2 ];
}

unsigned char GameWorld::getValue( int x, int y ) const
{
    if( x < 0 || x > width || y < 0 || y > height ) return 0; // fail
    else return WorldTable[ x ][ y ];
}


/****************************************
 * 
 * Screen for update
 * 
 ****************************************/

void GameWorld::UpdateWorld_MainScreen( )
{
    return;
}

void GameWorld::UpdateWorld_GameScreen( )
{
    static bool inUpdating = false; // Prevent multi-calling this funtion
    
    if( inUpdating ) return;
    else inUpdating = true;
    
    /* Clear background */
    glClear( GL_COLOR_BUFFER_BIT );
    
    /* Draw background */
    glColor3f( 0.0, 0.0, 0.0 ); // black
    glRectf( 0, Pixel, Pixel, Pixel + WordsHeight ); // Top Words Line
    glRectf( 1, 1, Pixel - 1, Pixel - 1 );
    
    /* Test draw martrix */
    /*glColor3f( 1.0, 1.0, 1.0 ); // white
    for( int i = 1; i < Pixel - 1; i ++ ) {
        for( int j = 1; j < Pixel - 1; j ++ ) {
            if( ( i + j ) % 2 ) {
                //glPushMatrix( );
                glRectf( (float)i + 0.1, (float)j + 0.1, i + 1.0 - 0.1, j + 1.0 - 0.1 );
                //glPopMatrix( );
            }
        }
    }*/
    
    
    /* Draw Snakes */
    for( int i = 1; i < Pixel - 1; i ++ ) {
        for( int j = 1; j < Pixel - 1; j ++ ) {
            switch( WorldTable[ i ][ j ] & 0xE0 ) {
            case 0x00: // None / Free
            case 0xF0: // Wall
                break;
                
            case 0x20: // Head // need special process, directions, colors
                glColor3ub( 0xFF, 0xFF, 0xFF );
                if( ( ( WorldTable[ i ][ j ] & 0x1C ) >> 2 ) == 0x00 )
                    glColor3ub( 0x00, 0xFF, 0xFF );
                
                switch( SnakeHeadPos[ ( WorldTable[ i ][ j ] & 0x1C ) >> 2 ][ 2 ] ) {
                case 0x00: // Left
                    glBegin(GL_TRIANGLES);  
                    glVertex2f( i + 0.1, j + 0.5 );
                    glVertex2f( i + 1.0 - 0.1, j + 0.1 );
                    glVertex2f( i + 1.0 - 0.1, j + 1.0 - 0.1 );
                    glEnd();
                    break;
                case 0x01: // Down
                    glBegin(GL_TRIANGLES);
                    glVertex2f( i + 0.5, j + 0.1 );
                    glVertex2f( i + 0.1, j + 1.0 - 0.1 );
                    glVertex2f( i + 1.0 - 0.1, j + 1.0 - 0.1 );
                    glEnd();
                    break;
                case 0x02: // Up
                    glBegin(GL_TRIANGLES);  
                    glVertex2f( i + 0.5, j + 1.0 - 0.1 );
                    glVertex2f( i + 0.1, j + 0.1 );
                    glVertex2f( i + 1.0 - 0.1, j + 0.1 );
                    glEnd();
                    break;
                case 0x03: // Right
                    glBegin(GL_TRIANGLES);  
                    glVertex2f( i + 1.0 - 0.1, j + 0.5 );
                    glVertex2f( i + 0.1, j + 1.0 - 0.1 );
                    glVertex2f( i + 0.1, j + 0.1 );
                    glEnd();
                    break;
                default:
                    break;
                }
                break;
            case 0x40: // Body
                glColor3ub( 0xFF, 0xFF, 0xFF );
                glRectf( (float)i + 0.1, (float)j + 0.1, i + 1.0 - 0.1, j + 1.0 - 0.1 );
                break;
            case 0x60: // Tail
                glColor3ub( 0xA0, 0xA0, 0xA0 );
                glRectf( (float)i + 0.1, (float)j + 0.1, i + 1.0 - 0.1, j + 1.0 - 0.1 );
                break;
                
            case 0x80: // Thing A
                glColor3ub( 0x00, 0x00, 0xFF ); // blue
                glRectf( (float)i + 0.1, (float)j + 0.1, i + 1.0 - 0.1, j + 1.0 - 0.1 );
                break;
            case 0xA0: // Thing B
                glColor3ub( 0x00, 0xFF, 0x00 ); // green
                glRectf( (float)i + 0.1, (float)j + 0.1, i + 1.0 - 0.1, j + 1.0 - 0.1 );
                break;
            case 0xC0: // Thing C
                glColor3ub( 0xFF, 0x00, 0x00 ); // red
                glRectf( (float)i + 0.1, (float)j + 0.1, i + 1.0 - 0.1, j + 1.0 - 0.1 );
                break;
                
            default:
                break;
            }
        }
    }
    
    
    /* Draw text */
    freetype::font_data our_font;
    our_font.init( "./comic.ttf", 40 );
    
    // ****************************************
    // The following formula was calc by me...
    // ****************************************
    glColor3ub(0xff,0xff,0xff);
    glPushMatrix();
    //glLoadIdentity();
    glScalef( 10.0 * glutGet( GLUT_WINDOW_WIDTH ) / 600 * ( (Pixel+WordsHeight) / 52.0 ),
              10.0 * glutGet( GLUT_WINDOW_HEIGHT ) / ( 600 / Pixel * ( Pixel + WordsHeight ) ) * WordsHeight / 2, 1 );
    //glTranslatef( 10, 790.0, 0 );
    freetype::print( our_font, 10.0 * glutGet( GLUT_WINDOW_WIDTH ) / 600,
                     606.0 * glutGet( GLUT_WINDOW_HEIGHT ) / ( 600 / Pixel * ( Pixel + WordsHeight ) ),
                     "Refreshed: % 10lld time(s)", ++ StatusID );
    glPopMatrix();
    
    // GameStatus
    glPushMatrix();
    char StatusWord[ 100 ];
    switch( GameStatus ) {
    case 0:
        glColor3ub( 0xFF, 0x00, 0x00 );
        strcpy( StatusWord, "Not start.\nSpace to start~" );
        break;
    case 1:
        glColor3ub( 0xFF, 0xFF, 0xFF );
        strcpy( StatusWord, "In process." );
        break;
    case 2:
        glColor3ub( 0x00, 0xFF, 0x00 );
        strcpy( StatusWord, "YOU WIN!!\nPress \'R\' to retry~" );
        break;
    case 3:
        glColor3ub( 0x00, 0x00, 0xFF );
        strcpy( StatusWord, "- You lost -\nPress \'R\' to retry~" );
        break;
    case 4:
        glColor3ub( 0xFF, 0xFF, 0x00 );
        strcpy( StatusWord, "(Game Paused)" );
        break;
    default:
        glColor3ub( 0xFF, 0x00, 0x00 );
        strcpy( StatusWord, "- ERROR -" );
        break;
    }
    glScalef( 10.0 * glutGet( GLUT_WINDOW_WIDTH ) / 600 * ( (Pixel+WordsHeight) / 52.0 ),
              10.0 * glutGet( GLUT_WINDOW_HEIGHT ) / ( 600 / Pixel * ( Pixel + WordsHeight ) ) * WordsHeight / 2, 1 );
    freetype::print( our_font, 350.0 * glutGet( GLUT_WINDOW_WIDTH ) / 600,
                     606.0 * glutGet( GLUT_WINDOW_HEIGHT ) / ( 600 / Pixel * ( Pixel + WordsHeight ) ),
                     "Status: %s", StatusWord );
    glPopMatrix();
    
    /*glPushMatrix();
    //glLoadIdentity();
    ///glTranslatef( 0, Pixel , 0 );
    glScalef(20,20,20);
    freetype::print(our_font, 0.0, 0.0, "Changed: %d time(s)", StatusID );
    glPopMatrix();*/
    our_font.clean(); // IMPORTANT

    
    glutSwapBuffers( );
    
    inUpdating = false;
    
    return;
}


/****************************************
 * 
 * Util function
 * 
 ****************************************/
int GameWorld::getRandomValue( int m, int n ) const
{
    return rand() % ( n - m + 1 );
}

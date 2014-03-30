/**
 * Name: Snake Game
 * Author: MewCatcher
 * Date: 03/24/14
 * Description: This game is an uncommen snake game, it's with AI!
 * Funtion: Main.cpp process the window's initialization.
 **/

#include "main.h"
#include <iostream>
//#include <SDL.h>

using namespace std;

/* Funtion list */
void InitialGame( );
void Display( );
void Keyboard( unsigned char key, int x, int y );
void AllKey( int key, int x, int y );
void Mouse( int button, int state, int x, int y );
void Delay( int id );


int main( int argc, char **argv )
{
    cerr << "========================================\n"
            "=         Snake Game (with AI)         =\n"
            "=                     -- by MewCatcher =\n"
            "========================================\n";
    cerr << "Create game\'s main window." << endl;
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( width, height );
    //glViewport(0, 0, width, height);
    glutInitWindowPosition( 0, 0 );
    glutCreateWindow( argv[ 0 ] );
    glOrtho( 0.0, (float)Pixel, 0.0, (float)Pixel + WordsHeight, 0, (float)Pixel );

    cerr << "Initial game scence." << endl;
    InitialGame( );

    cerr << "Display the first interface." << endl;
    glutDisplayFunc( Display );

    cerr << "Set all functions." << endl;
    //glutReshapeFunc( reshape );
    //glutMouseFunc( mouse );
    glutKeyboardFunc( Keyboard );
    glutSpecialFunc( AllKey );
    glutTimerFunc( 1000 / gw.getGameSpeed( ), Delay, 0 );

    cerr << "Main loop." << endl;
    glutMainLoop( );

    cerr << "Exit." << endl; // useless
    return 0;
}


void InitialGame( )
{
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // 1,1,1 white; 0,0,0 black
    glShadeModel( GL_FLAT );
    
    AISnake = new SnakeAI * [ gw.getMaxSnake( ) ];
    PlayerSnake = new Snake( gw.addSnake( ), gw ); // id 0
    for( int i = 1; i < gw.getMaxSnake( ); i ++ )
        AISnake[ i ] = new SnakeAI( gw.addSnake( ), gw );
    
    return;
}

void Display( )
{
    /*glClear( GL_COLOR_BUFFER_BIT );
    glColor3f( 0.0, 0.0, 0.0 );
    
    glPushMatrix( );
    glTranslatef( 10.0, 10.0, 0.0 );
    glRotatef( 45.0, 0.0, 0.0, 1.0 );
    glRectf( -2.5, -2.5, 2.5, 2.5 );
    glPopMatrix( );
    
    glPushMatrix( );
    glTranslatef( 20.0, 20.0, 0.0 );
    glRotatef( 45.0, 0.0, 1.0, 0.0 );
    glRectf( -2.5, -2.5, 2.5, 2.5 );
    glPopMatrix( );
    
    glPushMatrix( );
    glTranslatef( 30.0, 30.0, 0.0 );
    glRotatef( 45.0, 1.0, 0.0, 0.0 );
    glRectf( -2.5, -2.5, 2.5, 2.5 );
    glPopMatrix( );*/
    
    /*for( int i = 0; i < Pixel; i ++ ) {
        for( int j = 0; j < Pixel; j ++ ) {
            if( ( i + j ) % 2 ) {
                //glPushMatrix( );
                glRectf( (float)i, (float)j, i + 1.0, j + 1.0 );
                //glPopMatrix( );
            }
        }
    }*/
    //glutSwapBuffers( ); // Show Buffers
    
    gw.UpdateWorld( );
    return;
}

void Keyboard( unsigned char key, int x, int y )
{
    AllKey( key, x, y );
    return;
}

void AllKey( int key, int x, int y )
{
    /*GLUT_KEY_LEFT
    Left directional key.
    GLUT_KEY_UP
    Up directional key.
    GLUT_KEY_RIGHT
    Right directional key.
    GLUT_KEY_DOWN
    Down directional key.*/
    /*static bool SpaceStatus = false;
    
    switch( key ) {
    //case:
    case (int)' ':
        if( SpaceStatus == false ) {
            SpaceStatus = true;
            glutTimerFunc( 100, Delay, 0 );
            //glutIdleFunc( (void (*)(void) *)(gw.UpdateWorld(void)) );
        }
        else {
            SpaceStatus = false;
            glutIdleFunc( NULL );
        }
        break;
    }*/
    if( key == 'Q' || key == 'q' ) {
        glutLeaveMainLoop( ); // Leave MainLoop, but will not go back main( )
        return;
    }
    
    if( PlayerSnake -> SendKeyEvent( key, x, y ) == false )
        cerr << "Key event received error" << endl;
    return;
}

void Delay( int id )
{
    // need add another interface
    for( int i = 1; i < gw.getMaxSnake( ); i ++ )
        AISnake[ i ] -> receiveReCalcMsg( );
    gw.goNextStatus( );
    glutPostRedisplay( );
    glutTimerFunc( 1000 / gw.getGameSpeed( ), Delay, 0 );
    return;
}

/*void spinDisplay( )
{
    spin += 2.0;
    if( spin > 360.0 )
        spin -= 360.0;
    glutPostRedisplay( );
}

void reshape( int w, int h )
{
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    glOrtho( -50.0, 50.0, -50.0, 50.0, -1.0, 1.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}


void Mouse( int button, int state, int x, int y )
{
    static bool status = false;

    switch( button ) {
case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ) {
        if( status ) {
            glutIdleFunc( NULL );
            status = false;
        }
        else {
            glutIdleFunc( spinDisplay );
            status = true;
        }
    }
    break;

default:
    break;
    }
}
*/

/**
 * FileName: gameworld.h
 * Author: MewCather
 * Date: 03/25/14
 * Description: This file define the class "GameWorld", whitch process all the
 *              game's displaying, and Win/Lose judging.
 * Using: OpenGL, FreeType2
 **/

#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#define MaxSnake           4
#define SnakeInitialLength 8
#define GAMESPEED          8.0

enum SCENCE {
    MainScreen = 1,
    GameScreen,
};

class GameWorld {
public:
    GameWorld( );
    ~GameWorld( );
    
    
    void UpdateWorld( );
    void startGame( );
    bool SendKeyEvent( int id, int key, int x, int y );
    void PauseOrResume( );
    int addSnake( );                // If return negative value, failure; else return id
    void setScence( SCENCE sc );
    void goNextStatus( );           // One second passed, need progress
    bool doesGameEnd( ) const;      // Judge if game ended
    
    float getGameSpeed( ) const;    // get game speed 1.0 standard, larger -> faster
    long long getStatusID( ) const; // get StatusID
    int getMaxSnake( ) const;       // get MaxSnake
    int getMapWidth( ) const;       // get map width
    int getMapHeight( ) const;      // get map height
    int getHeadX( int id ) const;   // get head x position
    int getHeadY( int id ) const;   // get head y position
    int getHeadDir( int id ) const; // get head direction
    unsigned char getValue( int x, int y ) const; // interface for getting table value
    
private:
    /* Game data */
    int CurrentAILevel;             // 1 - easy; 2 - medium; 3 - hard;
                                    // 4 - Smarter than human
    SCENCE CurrentScence;           // Record current scence for drawing
    long long StatusID;             // The unique id marks the status
    float GameSpeed;
    int GameStatus;                 // 0 - Not begin; 1 - In process;
                                    // 2 - Win; 3 - Lose; 4 - Pause;
    
    int CurrentPlayer;              // Including the real player
    //SnakeAI *AISnake[ MaxSnake ];   // AI array
    
    int SnakeHeadPos[ MaxSnake ][ 3 ]; // 0 - x; 1 - y; 2 - dir;; [ 0 ] Player
    bool SnakeStatus[ MaxSnake ];   // true - alive; false - death;
    int ThingPos[ 3 ][ 2 ];         // 0 - x; 1 - y;; [ 0 ] Thing A
                                    // blue - add one; red - ？; green - ?;
    unsigned char **WorldTable;     /* [ unsigned char ] ~ [ 00000000b ]
                                         seperate it in to 3 parts
                                         (1) 0 0 0 | (2) 0 0 0 | (3) 0 0
                                     (1) Artributions
                                         0 0 0: None / Free
                                         0 0 1: Snake Head
                                         0 1 0: Snake Body
                                         0 1 1: Snake Tail
                                         1 0 0: Thing A
                                         1 0 1: Thing B
                                         1 1 0: Thing C
                                         1 1 1: Wall
                                     (2) Identities
                                         0 0 0: Player
                                         0 0 1: Snake AI 1
                                         0 1 0: Snake AI 2
                                         ...  : ...
                                     (3) Directions ( Backwoards )
                                         0 0  : Left  ( to back )
                                         0 1  : Down  ( to back )
                                         1 0  : Up    ( to back )
                                         1 1  : Right ( to back )
                                    */
                                    
    /* Operation function */
    void deleteTail( int id, bool backup ); // id from 0, backup | restore
    void gameEnd( int id );         // check snakes status
    void addNewThing( );            // need a random function
    
    /* Screen making */
    void UpdateWorld_MainScreen( );
    void UpdateWorld_GameScreen( );
    
    /* Util function */
    int getRandomValue( int m, int n ) const; // return value in [ m, n )
    
    
};


#endif

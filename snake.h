//snake.h -- prototypes of functions and structures declarations

#ifndef SNAKE_H_
#define SNAKE_H_

/*************************** STRUCT DECLARATION ***************************/
/* This structure will store x and y coordinates of every object like snake head,
   fruit or every element of snake tail. */
struct position {
    int y;
    int x;
};

/*************************** FUNCTION DECLARATION ***************************/
void showMenu();
void showOptions();
void showControls();
void loadMap(); //By this function every pole of our map will be determine by X,x,O or " "
void drawMap(); //By this function map will be drawn on terminal window
void gameLose();
void gameLogic(); //Just game logic like taillogic, win or pass logic.
void gameReset();
position randomPosition(position); //By this function coordinates of Apple will be "randomly" generated. Also it will check that if coordinates are correct.
position controlPosition(position); //By this function We can steer our snake head.


#endif

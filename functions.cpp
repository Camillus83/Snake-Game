#include <iostream>
#include <time.h> //for generate "random" numbers
#include <windows.h> //for Sleep() function
#include <conio.h> //for _kbhit() function
#include "snake.h"


int TailSize=0;     //When snake eats fruit, variable TailSize will increment by 1 point, to determine lenght of the tail.
int SleepTime=150;  //Sleeptime will change depends on difficulty level
int Score;          
const int WIDTH=20;
char gameBoard[WIDTH][WIDTH]; 
position SnakeHead={9,9}; //struct SnakeHead stores x and y coordinates of sneak head.
position Apple={rand()%(WIDTH-2)+1,rand()%(WIDTH-2)+1}; 
position SnakeTail[100];
char direction;
char command;
char previousdirection;
char difficultyLevel='M'; //defalut difficulty level is Medium
bool right=1;
bool left=0;
bool up=0;
bool down=0;
bool gameOver;
int score;

/************************** LoadMap FUNCTION ******************************/
/*By this function every pole of our map will be determine by X,x,O or " "*/
void loadMap()
{
    system("cls");
    for(int i=0; i<WIDTH; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            if(i==0 || i==(WIDTH-1) || j==0 || j== (WIDTH-1 )) 
            {
                gameBoard[i][j]='*';
            }
            else
            {
                gameBoard[i][j]=' ';
            }
        }
        gameBoard[Apple.y][Apple.x]='O'; //Apple position
        gameBoard[SnakeHead.y][SnakeHead.x]='X'; //Snake head position
        if(TailSize!=0)
        {
            gameBoard[SnakeTail[0].y][SnakeTail[0].x]='x';
            for(int k=1; k<TailSize; k++)
            {
                gameBoard[SnakeTail[k].y][SnakeTail[k].x]='x';
            }
        }
    }
}
/************************** drawMap FUNCTION ***************************/
/*By this function game board will be drawn on terminal window         */
void drawMap()
{
    for(int i=0;i<WIDTH;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {   
            std::cout<<gameBoard[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"\n\n              SCORE:"<<score<<"\n";
}
/************************** Struct Position FUNCTION ***************************/
/*  By this function coordinates of Apple will be "randomly" generated.
    Also it will check that if coordinates are correct.                        */
position randomPosition(position p)
{
    p.x=(rand()%(WIDTH-2) + 1); 
    p.y=(rand()%(WIDTH-2) + 1); 
    return p;
}
/************************** Struct Position FUNCTION ***************************/
/* By this function we can control our snake head                              */
position controlPosition(position p)
{
    if(_kbhit())
    {
        direction=getch();
    }
    if(previousdirection=='w' && direction=='s') {direction='w';}
    if(previousdirection=='s' && direction=='w') {direction='s';}
    if(previousdirection=='a' && direction=='d') {direction='a';}
    if(previousdirection=='d' && direction=='a') {direction='d';}

    switch(direction)
    {
        case 'w': up=1; down=0; right=0; left=0; break;
        case 'a': up=0; down=0; right=0; left=1; break;
        case 's': up=0; down=1; right=0; left=0; break;
        case 'd': up=0; down=0; right=1; left=0; break;
    }

    if(down==1) {
        p.y=p.y+1;
        if(p.y==(WIDTH-1)) {p.y=1;}
    }
    if(up==1) {
        p.y=p.y-1;
        if(p.y==0) {p.y=(WIDTH-2);}
    }
    if(right==1) {
        p.x=p.x+1;
        if(p.x==(WIDTH-1)) {p.x=1;}
        if(p.y==(WIDTH-1)) {p.y=1;}
    }
    if(left==1) {
        p.x=p.x-1;
        if(p.x==0) {p.x=(WIDTH-2);}
        if(p.y==(WIDTH-1)) {p.y=1;}
    }
    previousdirection=direction;
    return p;
}
/************************** GameLogic FUNCTION ***************************/
/*  Just game logic like taillogic, win or pass logic.                   */
void gameLogic()
{
    if(TailSize!=0)
    {
        int prevX, prevY;
        int prev2X, prev2Y;
        prevX=SnakeTail[0].x;
        prevY=SnakeTail[0].y;
        SnakeTail[0].x=SnakeHead.x;
        SnakeTail[0].y=SnakeHead.y;
        for(int k=1; k<TailSize; k++)
        {
            prev2X=SnakeTail[k].x;
            prev2Y=SnakeTail[k].y;

            SnakeTail[k].x=prevX;
            SnakeTail[k].y=prevY;

            prevX=prev2X;
            prevY=prev2Y;
        }
    }

    SnakeHead=controlPosition(SnakeHead);
    
    for(int z=0; z<TailSize; z++)
    {
        if(SnakeHead.x == SnakeTail[z].x && SnakeHead.y == SnakeTail[z].y) gameOver=true; // gameover, snake eats own tail
    }
    
    if(SnakeHead.x == Apple.x && SnakeHead.y == Apple.y)  //snake eats an fruit, score will grown
    {
        score+=10;
        Apple=randomPosition(Apple);
        for(int z=0; z<TailSize; z++)
            {
                if(Apple.x==SnakeTail[z].x && Apple.y==SnakeTail[z].y) //if apple will spawn on our tail, it will again generate apple position and check for every element of snake tail
                {
                    z=0;
                    Apple=randomPosition(Apple);
    
                }   
            }
    TailSize++;
    }
}

void showMenu()
{
    system("cls");
    std::cout<<
" #####  #     #    #    #    # ####### \n"
"#     # ##    #   # #   #   #  #       \n"
"#       # #   #  #   #  #  #   #       \n"
" #####  #  #  # #     # ###    #####   \n"
"      # #   # # ####### #  #   #       \n"
"#     # #    ## #     # #   #  #       \n"
" #####  #     # #     # #    # ####### \n\n\n";

    std::cout<<
"START GAME........................TYPE S\n"
"OPTIONS...........................TYPE O\n"
"CONTROLS..........................TYPE C\n"
"QUIT GAME.........................TYPE Q\n";
    std::cin.clear();
    while(std::cin>>command){
    switch(command)
    {
        case 'S' : gameReset(); break;
        case 'O' : showOptions(); break;
        case 'C' : showControls(); break;
        case 'Q' : exit(0); break;
        default  : std::cout<<"Unknown command\n";
    }
    if(command=='S' || command=='O' || command=='C' || command=='Q' ) {break;}
    std::cin.clear();
    }
}



void showOptions()
{
    system("cls");
    std::cout<<
" #####  #     #    #    #    # ####### \n"
"#     # ##    #   # #   #   #  #       \n"
"#       # #   #  #   #  #  #   #       \n"
" #####  #  #  # #     # ###    #####   \n"
"      # #   # # ####### #  #   #       \n"
"#     # #    ## #     # #   #  #       \n"
" #####  #     # #     # #    # ####### \n\n\n";

    std::cout<<
"..........SET DIFFICULTY LEVEL.........\n"
"............TYPE E for EASY............\n"
"............TYPE M for MEDIUM..........\n"
"............TYPE H for HARD............\n";
    std::cin.clear();
    while(std::cin>>difficultyLevel)
    {
        switch(difficultyLevel)
        {
            case 'E' : SleepTime = 150; break;
            case 'M' : SleepTime = 100; break;
            case 'H' : SleepTime = 50; break;
            default  : std::cout<<"Unknown command\n"; break;
        }
        if(difficultyLevel=='E' || difficultyLevel=='M' || difficultyLevel=='H') {showMenu(); break;}
        std::cin.clear();
    }
}

void showControls()
{
    system("cls");
    std::cout<<
" #####  #     #    #    #    # ####### \n"
"#     # ##    #   # #   #   #  #       \n"
"#       # #   #  #   #  #  #   #       \n"
" #####  #  #  # #     # ###    #####   \n"
"      # #   # # ####### #  #   #       \n"
"#     # #    ## #     # #   #  #       \n"
" #####  #     # #     # #    # ####### \n\n\n";

    std::cout<<
"...............CONTROLS................\n"
"..........TYPE W for going UP..........\n"
"..........TYPE S for going DOWN........\n"
"..........TYPE A for going LEFT........\n"
"..........TYPE D for going RIGHT.......\n"
"TO GO BACK.......................TYPE B\n";
    std::cin.clear();
    while(std::cin>>command)
    {
        if(command == 'B') {showMenu(); break;}
        else std::cout<<"Unknown command\n";
        std::cin.clear();
    }
}

void gameLose()
{
    system("cls");
    std::cout<<
" #####  #     #    #    #    # ####### \n"
"#     # ##    #   # #   #   #  #       \n"
"#       # #   #  #   #  #  #   #       \n"
" #####  #  #  # #     # ###    #####   \n"
"      # #   # # ####### #  #   #       \n"
"#     # #    ## #     # #   #  #       \n"
" #####  #     # #     # #    # ####### \n\n\n";
    
    std::cout<<
"...............YOU LOSE................\n"
"...........YOUR SCORE WAS "<<score<<"...........\n"
".......DO YOU WANT TO PLAY AGAIN?......\n"
".............TYPE Y for yes............\n"
".............TYPE N for no.............\n";
    std::cin.clear();
    while(std::cin>>command)
    {
        if(command=='N') {exit(0); std::cin.clear(); break;}
        if(command=='Y') break;
        if(command!='Y' || command !='N') {std::cout<<"Unknown command\n"; std::cin.clear();}
    }
}

void gameReset()
{
    gameOver = false;
    score = 0;
    TailSize = 0;
    position SnakeTail[100];
}

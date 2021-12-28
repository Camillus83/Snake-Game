#include <iostream>
#include "snake.h"
#include <windows.h>
extern bool gameOver;
extern int SleepTime;
int main()
{
     system("cls");
    srand(time(NULL)); 
    while(true)
    {
        showMenu();
        while(gameOver == false)
        {
            loadMap();
            drawMap();
            gameLogic();
            Sleep(SleepTime);
        }
        gameLose();
    }
    return 0;
}
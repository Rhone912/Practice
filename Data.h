#ifndef SNAKE1212_DATA_H
#define SNAKE1212_DATA_H

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define SPEED 200
#define SNAKE_LENGTH 5
#define MAP_LENGTH 58
#define MAP_WIDTH 26
#define U 1
#define D 2
#define L 3
#define R 4

typedef struct SNAKE
{
    int x;
    int y;
    struct SNAKE *next;
}Snake;
Snake *head, *food, *q, *nexthead;

void CursorPosition();
void CreateMap();
void CreateSnake();
void CreateFood();
void GameInitialization();
void Introduction();
void End();
void GameControl();
void SnakeMove();
void Stop();
void TotheWall();
int BiteItSelf();
void ChangeSpeed();
void EatFoodorNot();


#endif //SNAKE1212_DATA_H

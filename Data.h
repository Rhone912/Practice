#ifndef SNAKE0_DATA_H
#define SNAKE0_DATA_H
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

#define SPEED 200
#define SNAKE_LENGTH 5
#define MAP_LENGTH 58
#define MAP_WIDTH 26
#define U 0
#define D 1
#define L 2
#define R 3

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
void automove();
#endif //SNAKE0_DATA_H

#ifndef SNAKE0_DATA_H
#define SNAKE0_DATA_H

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

#define SPEED 200
#define MAP_LENGTH 58
#define MAP_WIDTH 26
#define U 0
#define D 1
#define L 2
#define R 3
#define FOOD 1
#define WALL 0
#define SNAKE -1
#define BLANK 2
#define MINE 3
#define WEED 4

typedef struct Snake
{
    int x;
    int y;
    struct Snake *next;
    struct Snake *prev;
}Snake;
typedef struct Element
{
    int x;
    int y;
}Element;
typedef struct Rank{
    char name[11];
    int rankscore;
}Rank;
Snake *head,*tail, *q, *nexthead;
Element* weed[5];
Element* mine[5];
Element* Sweed;
Element* food;
Element wall[1200];

void CursorPosition(int x, int y);
void CreateMap();
void CreateSnake();
void CreateFood();
void GameInitialization();
int Introduction();
void End();
void GameControl();
int SnakeMove();
void Stop();
int isWall(int x, int y);
int isSnake(int x, int y);
void ChangeSpeed();
void EatFoodorNot();
void CreateWeed(int x, int y);
int isWeed(int x, int y);
int isFood(int x, int y);
int isMine(int x, int y);
int isSweed(int x, int y);
void weed_flick();
void ClearWeed();
void CreateMine();
void ClearMine();
void ClearFood();
void SaveGame();
int LoadGame();
void ClearGame();
void ClearSmartWeed();
Element* perweed();
Element* permine();
void RankList();
void CreateSmartWeed();
void hideCursor();
int Auto();
void AutoMove(int x, int y ,int steps);

#endif //SNAKE0_DATA_H

#ifndef SNAKE0_DATA_H
#define SNAKE0_DATA_H

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <conio.h>
#include <math.h>
//#include <mmsystem.h>
//#pragma comment(lib, "Winmm.lib")

#define U 0
#define D 1
#define L 2
#define R 3
#define STANDARD 40

extern int mission;
extern unsigned int difficulty;
extern int score,foodscore;
extern int direction;
extern int snake_length;
extern int wallnum;
extern int mission;
extern int autotime;

typedef struct Snake
{
    GLfloat x;
    GLfloat y;
    struct Snake *next;
    struct Snake *prev;
}Snake;
typedef struct Element
{
    GLfloat x;
    GLfloat y;
}Element;
typedef struct Rank{
    char name[11];
    int rankscore;
}Rank;
Snake *head,*tail, *q;
Element newtail;
Element* weed[5];
Element* mine[5];
Element* Sweed;
Element* food;
Element* Pweed;
Element* Cweed;
Element wall[1200];

void CreateMap(int mission);
void CreateSnake();
void CreateFood();
void GameInitialization(int mission);
void End();
int SnakeMove();
int isWall(GLfloat x, GLfloat y);
int isSnake(GLfloat x, GLfloat y);
void MoveJudge();
void CreateWeed();
int isWeed(GLfloat x, GLfloat y);
int isFood(GLfloat x, GLfloat y);
int isMine(GLfloat x, GLfloat y);
int isSweed(GLfloat x, GLfloat y);
void ClearWeed();
void CreateMine();
void ClearMine();
void ClearFood();
void SaveGame();
int LoadGame();
void LoadOption();
void ClearGame();
void ClearSmartWeed();
void CreatePowerWeed();
int isPweed(GLfloat x , GLfloat y);
void ClearPowerWeed();
Element* perweed();
Element* permine();
void CreateSmartWeed();
void ClearSnake();
int Auto();
void AutoMove(GLfloat x, GLfloat y);
int isCweed(GLfloat x , GLfloat y);
void CreateConfusionWeed();
void ClearConfusionWeed();

void GLinit(GLsizei width, GLsizei height);
void ChangeSize(GLsizei w, GLsizei h);
void DrawGlScene();
void OnTimer(int value);
void GameControl(int key, int x, int y);
void KeyPressed(unsigned char key, int x, int y);

#endif //SNAKE0_DATA_H

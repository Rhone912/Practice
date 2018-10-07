#include "Data.h"



void CursorPosition(int x, int y)
{
    COORD pos;
    HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Introduction()//开始界面
{
    CursorPosition(40, 12);

    system("title 贪吃蛇");
    printf("欢迎进入贪吃蛇游戏！");
    system("pause");
    system("cls");
    CursorPosition(25, 12);
    printf("用方向键控制蛇的移动，通过吃食物来获得分数并增长身体。\n");
    CursorPosition(25, 13);
    printf("增加分数的同时会增加游戏速度。\n");
    system("pause");
    printf("进入游戏后按下空格可开始游戏，再次按下空格则游戏暂停。。\n");
    system("cls");
}

void CreateMap()
{
    int i;
    for(i=0;i<MAP_LENGTH+2;i+=2)
    {
        CursorPosition(i, 0);
        printf("■");
        CursorPosition(i, MAP_WIDTH);
        printf("■");
    }
    for(i=1;i<MAP_WIDTH;i++)
    {
        CursorPosition(0, i);
        printf("■");
        CursorPosition(MAP_LENGTH, i);
        printf("■");
    }
}

void CreateSnake()
{
    Snake *tail;
    int i;
    tail=(Snake*)malloc(sizeof(Snake));
    tail->x=12;
    tail->y=5;
    tail->next=NULL;
    for(i=0;i<SNAKE_LENGTH ;i++)
    {
        head=(Snake*)malloc(sizeof(Snake));
        head->next=tail;
        head->x=12+2*i;
        head->y=5;
        tail=head;
    }
    while(tail!=NULL)//从头到为，输出蛇身
    {
        CursorPosition(tail->x, tail->y);
        printf("◆");
        tail=tail->next;
    }
}

void GameInitialization()
{
    system("mode con cols=100 lines=27");
    Introduction();
    CreateMap();
    CreateSnake();
    CreateFood();
    hideCursor();
}

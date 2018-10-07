#include "Data.h"

int score=0,foodscore=10;
int direction = 4;
int speed=SPEED;
int endgameflag=0;

void ChangeSpeed()
{
    if(speed>=SPEED-50)
        speed-=foodscore/2;
    else if(speed>=SPEED-100)
        speed-=foodscore/4;
    else if(speed>=SPEED-150)
        speed-=foodscore/8;
    else if(speed<20)
        ;
}
void EatFoodorNot()
{
    if(nexthead->x==food->x && nexthead->y==food->y)
    {
        nexthead->next=head;
        head=nexthead;
        q=head;
        while(q!=NULL)
        {
            CursorPosition(q->x, q->y);
            printf("◆");
            q=q->next;
        }
        score=score+foodscore;
        ChangeSpeed();
        CreateFood();
    }
    else
    {
        nexthead->next=head;
        head=nexthead;
        q=head;
        while(q->next->next!=NULL)
        {
            CursorPosition(q->x, q->y);
            printf("◆");
            q=q->next;
        }
        CursorPosition(q->next->x, q->next->y);
        printf("  ");
        free(q->next);
        q->next=NULL;
    }
}

int BiteItSelf()
{
    Snake *self;
    self=head->next;
    while(self!=NULL)
    {
        if(self->x==head->x && self->y==head->y)
        {
            return 1;
        }
        self=self->next;
    }
    return 0;
}

void TotheWall()
{
    if(head->x==0 || head->x==56 ||head->y==0 || head->y==26)
    {
        endgameflag=1;
        End();
    }
}

void End()
{

    system("cls");
    CursorPosition(24, 12);
    if(endgameflag==1)
    {
        printf("撞到墙了，游戏结束.");
    }
    else if(endgameflag==2)
    {
        printf("咬到自己了，游戏结束.");
    }
    else if(endgameflag==3)
    {
        printf("游戏已结束。");
    }
    CursorPosition(24, 13);
    printf("得分 ： %d\n",score);
    system("pause");
    exit(0);
}

void CreateFood()
{
    Snake* food_temp;
    srand((unsigned)time(NULL));
    food_temp=(Snake*)malloc(sizeof(Snake));
    do
    {
        food_temp->x=rand()%(MAP_LENGTH-6)+4;
    }
    while ((food_temp->x%2)!=0);
    food_temp->y=rand()%(MAP_WIDTH-6)+4;
    q=head;
    while(q->next != NULL)
    {
        if(q->x==food_temp->x && q->y==food_temp->y)
        {
            free(food_temp);
            CreateFood();
            return;
        }
        q=q->next;
    }
    if(q->x==food_temp->x && q->y==food_temp->y)
    {
        free(food_temp);
        CreateFood();
        return;
    }
    CursorPosition(food_temp->x, food_temp->y);
    food=food_temp;
    printf("●");
}

void SnakeMove()
{
    CursorPosition(64, 8);
    printf("得分：%d  ",score);
    TotheWall();

    nexthead=(Snake*)malloc(sizeof(Snake));
    if(direction==U)
    {
        nexthead->x=head->x;
        nexthead->y=head->y-1;

        EatFoodorNot();
    }
    if(direction==D)
    {
        nexthead->x=head->x;
        nexthead->y=head->y+1;

        EatFoodorNot();
    }
    if(direction==L)
    {
        nexthead->x=head->x-2;
        nexthead->y=head->y;

        EatFoodorNot();
    }
    if(direction==R)
    {
        nexthead->x=head->x+2;
        nexthead->y=head->y;

        EatFoodorNot();
    }
    if(BiteItSelf()==1)
    {
        endgameflag=2;
        End();
    }

}

void Stop()
{
    while(1)
    {
        Sleep(300);
        if(GetAsyncKeyState(VK_SPACE))
        {
            break;
        }

    }
}

void GameControl()
{
    CursorPosition(64, 13);
    printf("用↑.↓.←.→分别控制蛇的移动.");
    CursorPosition(64, 14);
    printf("每个食物价值10分。");
    CursorPosition(64, 15);
    printf("ESC ：退出游戏.SPACE：暂停游戏.");
    CursorPosition(64,16);
    printf("TAB : 自动游戏.");
    direction=R;
    for(;;)
    {
        if(GetAsyncKeyState(VK_UP) && direction!=D)
        {
            direction=U;
        }
        else if(GetAsyncKeyState(VK_DOWN) && direction!=U)
        {
            direction=D;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& direction!=R)
        {
            direction=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& direction!=L)
        {
            direction=R;
        }
        else if(GetAsyncKeyState(VK_SPACE))
        {
            Stop();
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            endgameflag=3;
            break;
        }
        else if(GetAsyncKeyState(VK_TAB))
        {
            automove();
        }
        Sleep(speed);
        SnakeMove();
    }
}

int wheregonext
(int hx, int hy, int fx, int fy)
{
    int p = 0, min = 100;
    int movable[4] = { U,L,D,R };
    int distance[4] = { 0 };
    distance[0] = abs(fx - hx) + abs(fy - (hy-1));
    if (distance[0] <= min && (hy-1 != 0 || hy-1 == fy) && direction!=D) {
        min = distance[0];
        p = 0;
    }
    else
        min = min;
    distance[1] = abs(fx - (hx - 2)) + abs(fy - hy);
    if (distance[1] <= min && (hx-2 != 0 || hx-2 == fx) && direction!=R) {
        min = distance[1];
        p = 1;
    }
    else
        min = min;
    distance[2] = abs(fx - hx) + abs(fy - (hy + 1));
    if (distance[2] <= min && (hy+1 != 26 || hy+1 == fy) && direction!=U) {
        min = distance[2];
        p = 2;
    }
    else
        min = min;
    distance[3] = abs(fx - (hx + 2)) + abs(fy - hy);
    if (distance[3] <= min && (hx+2 != 56 || hx+2 == fx) && direction!=L) {
        min = distance[3];
        p = 3;
    }
    else
        min = min;
    return movable[p];
}


void automove()
{
    while(1)
    {
        direction = wheregonext(head->x,head->y,food->x,food->y);
        Sleep(speed);
        SnakeMove();
        if(GetAsyncKeyState(VK_TAB))
        {
            break;
        }

    }
}


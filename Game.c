#include "Data.h"



int score=0,foodscore=10;
int direction = 0;
int speed=SPEED;

int endgameflag=0;

void ChangeSpeed()
{
    if(speed>=SPEED-50)
        speed=SPEED-score/2;
    else if(speed>=SPEED-100)
        speed=SPEED-score/4;
    else if(speed>=SPEED-150)
        speed=SPEED-score/8;
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
            printf("��");
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
            printf("��");
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
        printf("ײ��ǽ�ˣ���Ϸ����.");
    }
    else if(endgameflag==2)
    {
        printf("ҧ���Լ��ˣ���Ϸ����.");
    }
    else if(endgameflag==3)
    {
        printf("��Ϸ�ѽ�����");
    }
    CursorPosition(24, 13);
    printf("�÷� �� %d\n",score);
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
            break;
        }
        q=q->next;
    }
    CursorPosition(food_temp->x, food_temp->y);
    food=food_temp;
    printf("��");
}

void SnakeMove()
{
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
    printf("�á�.��.��.���ֱ�����ߵ��ƶ�.");
    CursorPosition(64, 14);
    printf("ÿ��ʳ���ֵ10�֡�");
    CursorPosition(64, 15);
    printf("ESC ���˳���Ϸ.SPACE����ͣ��Ϸ.");
    direction=R;
    for(;;)
    {
        CursorPosition(64, 8);
        printf("�÷֣�%d  ",score);
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
        Sleep(speed);
        SnakeMove();
    }
}






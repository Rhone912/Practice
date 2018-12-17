#include "Data.h"

extern int difficulty;
extern int snake_length;
extern time_t begin_time;
int wallnum;
int mission=1;

//���λ��
void CursorPosition(int x, int y) {
    COORD pos;
    HANDLE hOutput;
    pos.X=x;
    pos.Y=y;
    hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}
//���ع��
void hideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//ѡ���Ѷ�
void ChooseDifficulty(){
    system("cls");
    CursorPosition(20, 8);
    printf("�Ѷ�ѡ��");
    CursorPosition(16, 10);
    printf("��������1-3���ֱ��ʾ�򵥣���ͨ������");
    int key;
    for(;;) {
        if((key = getch())=='1'||(key = getch())=='2'||(key = getch())=='3'){
            difficulty=key-'0';
            CursorPosition(16, 12);
            printf("�Ѷ����óɹ�");
            system("pause");
            system("cls");
            break;
        }
    }

}
//�����˵�
void Introduction() {
    system("title ̰����");
    CursorPosition(20, 8);
    printf("���˵�");
    CursorPosition(16, 10);
    printf("1��ѡ���Ѷ�");
    CursorPosition(16, 12);
    printf("Space:������Ϸ");
    int key,flag=0;
    while(((key =getch()) != VK_SPACE) && flag==0)
    {
        if(key == '1')
            flag = 1;
        else if(key == '2')
            flag = 2;
        else if(key == '3')
            flag = 3;
        else if(key == '4')
            flag = 4;
        else if(key == VK_ESCAPE)
            exit(0);
        switch(flag)
        {
            case 1:
                ChooseDifficulty();
                flag=0;
                break;
            case 2:
                flag=0;
                break;
            case 3:
                flag=0;
                break;
            case 4:
                flag=0;
                break;
        }
        Introduction();
    }
    system("cls");
}
//������ͼ
void CreateMap(int mission) {
    int i, k = 0;
    switch (difficulty) {
        case 3:
            for (i = 24-mission*2; i <= 36-mission*2; i += 2) {
                wall[k].x = i;
                wall[k++].y = 13;
                CursorPosition(i, 13);
                printf("��");
            }
            for (i = 9-mission; i <= 17-mission; i++) {
                if(i==13)
                    continue;
                wall[k].x = 30;
                wall[k++].y = i;
                CursorPosition(30, i);
                printf("��");
            }
        case 2:
            for(i=0;i<=MAP_LENGTH-mission*4;i+=2){
                if((i+1)%5==0){
                    wall[k].x=i;
                    wall[k++].y=1;
                    CursorPosition(i, 1);
                    printf("��");
                    wall[k].x=i;
                    wall[k++].y=MAP_WIDTH-mission*2-1;
                    CursorPosition(i, MAP_WIDTH-mission*2-1);
                    printf("��");
                }
            }
            for(i=0;i<=MAP_WIDTH-mission*2;i++){
                if((i+1)%5==0){
                    wall[k].x=2;
                    wall[k++].y=i;
                    CursorPosition(2, i);
                    printf("��");
                    wall[k].x=MAP_LENGTH-mission*4-2;
                    wall[k++].y=i;
                    CursorPosition(MAP_LENGTH-mission*4-2, i);
                    printf("��");
                }
            }
        case 1:
            for(i=0;i<=MAP_LENGTH-mission*4;i+=2) {
                wall[k].x=i;
                wall[k++].y=0;
                CursorPosition(i, 0);
                printf("��");
                wall[k].x=i;
                wall[k++].y=MAP_WIDTH-mission*2;
                CursorPosition(i, MAP_WIDTH-mission*2);
                printf("��");
            }
            for(i=1;i<=MAP_WIDTH-mission*2;i++) {
                wall[k].x=0;
                wall[k++].y=i;
                CursorPosition(0, i);
                printf("��");
                wall[k].x=MAP_LENGTH-mission*4;
                wall[k++].y=i;
                CursorPosition(MAP_LENGTH-mission*4, i);
                printf("��");
            }
    wallnum=k-1;
    }
}
//�����ͼ
void ClearMap(){
    int i;
    for(i=0;i<=wallnum;i++){
        CursorPosition(wall[i].x,wall[i].y);
        printf(" ");
    }
}
//������
void CreateSnake() {
    int i;
    tail=(Snake*)malloc(sizeof(Snake));
    tail->x=12;
    tail->y=5;
    tail->next=NULL;
    tail->prev=NULL;
    for(i=1;i<snake_length ;i++) {
        head=(Snake*)malloc(sizeof(Snake));
        head->next=tail;
        head->x=12+2*i;
        head->y=5;
        tail->prev=head;
        tail=head;
    }
    do {
        CursorPosition(tail->x, tail->y);
        printf("��");
        tail=tail->next;
    }
    while(tail->next!=NULL);
    CursorPosition(tail->x, tail->y);
    printf("��");
}
//�����
void ClearSnake(){
    while(head!=NULL){
        CursorPosition(head->x,head->y);
        printf("  ");
        free(head);
        head=head->next;
    }

    snake_length=5;
}
//��Ϸ��ʼ��
void GameInitialization(int mission) {
    srand((unsigned)time(NULL));
    system("mode con cols=100 lines=27");
    CreateMap(mission);
    CreateSnake();
    CreateFood();
    CreateWeed();
    CreateMine();
    hideCursor();
    begin_time=clock();
}
//�����Ϸ
void ClearGame(){
    ClearSnake();
    ClearWeed();
    ClearMap();
    ClearMine();
    ClearFood();
    mission++;
}

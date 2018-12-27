#include "Data.h"

extern GLfloat unit;
unsigned int difficulty=1;
int mission=1;
int autotime = 0;
int powertime = 0;
int confusiontime = 0;
int score = 0;
int foodscore = 10;
int direction=R;
int endgameflag=0;
int res;
extern char name[11];
GLfloat dx[4]={0.0f,0.0f,-2.0f/STANDARD,2.0f/STANDARD};
GLfloat dy[4]={2.0f/STANDARD,-2.0f/STANDARD,0.0f, 0.0f};

//移动后的判定
void MoveJudge() {
    int i;
    if(isFood(head->x, head->y)){ //吃到了食物
        Snake* node = (Snake*)malloc(sizeof(Snake));
        node->x = newtail.x;
        node->y = newtail.y;
        node->prev = tail;
        tail->next = node;
        node->next = NULL;
        tail = node;
        snake_length++;
        score=score+foodscore;
        free(food);
        food=NULL;
        CreateFood();
        if(autotime>0){
            autotime--;
        }
    }
    else if(isWeed(head->x,head->y) && powertime<=0) { //吃到了毒草
        if(snake_length==1){
            endgameflag=4;
            End();
        }
        snake_length--;
        tail=tail->prev;
        free(tail->next);
        tail->next=NULL;
        score-=20;
    }
    else if(isMine(head->x,head->y) && powertime<=0){ //吃到了地雷
        if(snake_length==1){
            endgameflag=4;
            End();
        }
        for(i=snake_length;i>snake_length/2;i--){
            tail=tail->prev;
            free(tail->next);
            tail->next=NULL;
        }
        snake_length/=2;
        score-=50;
    }
    else if (isSweed(head->x, head->y)){ //吃到了智慧草
        autotime+=2;
        free(Sweed);
        Sweed = NULL;
    }
    else if (isPweed(head->x, head->y)){
        powertime=1000;
        free(Pweed);
        Pweed = NULL;
    }
    else if (isCweed(head->x, head->y)){
        confusiontime+=500;
        free(Cweed);
        Cweed = NULL;
    }
    else if(isWall(head->x,head->y)==1 && powertime<=0){ //撞墙
        endgameflag=1;
        End();
    }
    else if(isSnake(head->x,head->y)==1 && powertime<=0) {
        endgameflag=2;
        End();
    }
    if(powertime>=0)
        powertime-=20;
    if(confusiontime>=0)
        confusiontime-=20;
}

//游戏结束
void End() {
    int i,j;
    FILE *fp;
    Rank listtemp[5];
    if(fopen("rank", "rb")==NULL){
        fp=fopen("rank", "wb");
        fclose(fp);
    }
    fp=fopen("rank", "rb+");
    if(fread(listtemp, sizeof(Rank), 5 ,fp)==0){
        for(i=0;i<5;i++){
            memset(listtemp[i].name, 0 , 11*sizeof(char));
            listtemp[i].rankscore=0;
        }
        fwrite(listtemp, sizeof(Rank), 5, fp);
        rewind(fp);
    };
    fread(listtemp,sizeof(Rank), 5, fp);
    for(i=0;i<5;i++){
        if (listtemp[i].rankscore < score){
            for(j=4;j>i;j--){
                listtemp[j].rankscore=listtemp[j-1].rankscore;
                strcpy(listtemp[j].name, listtemp[j-1].name);
            }
            listtemp[i].rankscore = score;
            strcpy(listtemp[j].name, name);
            break;
        }
    }
    rewind(fp);
    fwrite(listtemp, sizeof(Rank), 5 ,fp);
    fclose(fp);
    glutSetWindowTitle("Game Over");
}

//蛇的移动处理
int SnakeMove() {
    if(autotime>0){
        Auto();
        direction=res;
    }
    newtail.x = tail->x;
    newtail.y = tail->y;
    GLfloat tempx=head->x, tempy=head->y, Tempx, Tempy;
    head->x += dx[direction];
    head->y += dy[direction];
    q=head;
    while(q->next!=NULL){
        Tempx = q->next->x;
        Tempy = q->next->y;
        q->next->x=tempx;
        q->next->y=tempy;
        tempx = Tempx;
        tempy = Tempy;
        q=q->next;
    }
    MoveJudge();
    switch(difficulty){
        case 1:
            if(score>=50*mission){ ;
                ClearGame();
                GameInitialization(mission);
                break;
            }
        case 2:
            if(score>=75*mission){
                ClearGame();
                GameInitialization(mission);
                break;
            }
        case 3:
            if(score>=100*mission){
                ClearGame();
                GameInitialization(mission);
                break;
            }
    }
    return 0;
}
//自动寻路
int Auto() //自动移动
{
    AutoMove(head->x, head->y);
	return 1;
}
void AutoMove(GLfloat x, GLfloat y){
    GLfloat move[4][2] ={{0,2.0f/STANDARD},{0,-2.0f/STANDARD},{-2.0f/STANDARD,0},{2.0f/STANDARD,0}};
    int k=0,shortcut;
    GLfloat nextx,nexty,minfornow=100.0f,distance;
    for(k=U;k<=R;k++){
        nextx=x+move[k][0];
        nexty=y+move[k][1];
        distance=(nextx-food->x)*(nextx-food->x)+(nexty-food->y)*(nexty-food->y);
        if(isSnake(nextx, nexty) || isWall(nextx, nexty)) {
            continue;
        }
        if(isMine(nextx, nexty)){
            distance+=1.0f;
        }
        else if(isWeed(nextx, nexty)){
            distance+=0.5f;
        }
        if(distance < minfornow){
            minfornow = distance;
            shortcut = k;
        }
    }
    res=shortcut;
}
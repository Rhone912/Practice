#include "Data.h"

extern GLfloat unit;

//地雷判定
int isMine(GLfloat x, GLfloat y){
    for(int i=0; i<difficulty; i++)
    {
        if(mine[i] != NULL)
            if((x-mine[i]->x)*(x-mine[i]->x)+(y-mine[i]->y)*(y-mine[i]->y) <= unit*unit/4){
                free(mine[i]);
                mine[i]=NULL;
                return 1;
            }
    }
    return 0;
}

//创建地雷
void CreateMine(){
    switch (difficulty)
    {
        case 1:
            mine[0]=permine();
        case 2:
            mine[0]=permine();
            mine[1]=permine();
        case 3:
            mine[0]=permine();
            mine[1]=permine();
            mine[2]=permine();
        default:break;
    }
}

//单个地雷创建
Element* permine(){
    for(;;){
        int flag=1;
        Element* mine_temp;
        mine_temp=(Element*)malloc(sizeof(Element));
        mine_temp->x = unit*(rand()%STANDARD);
        mine_temp->y = unit*(rand()%STANDARD);
        q=head;
        if(isFood(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isMine(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isWeed(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isSnake(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isSweed(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isPweed(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(flag==1){
            return mine_temp;
        }
    }
}

//清除地雷
void ClearMine(){
    for(int i=0;i<difficulty;i++){
        if(mine[i]!=NULL){
            free(mine[i]);
            mine[i]=NULL;
        }
    }
}


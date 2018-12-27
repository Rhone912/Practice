#include "Data.h"
extern  GLfloat unit;
//智慧草判定
int isSweed(GLfloat x , GLfloat y){
    if(Sweed!=NULL &&(x-Sweed->x)*(x-Sweed->x)+(y-Sweed->y)*(y-Sweed->y) <= unit*unit/4){
        return 1;
    }
    return 0;
}

extern GLfloat unit;

//智慧草的创建
void CreateSmartWeed(){
    for(;;){
        int flag=1;
        Element* Sweed_temp=(Element*)malloc(sizeof(Element));
        Sweed_temp->x = unit*(rand()%STANDARD);
        Sweed_temp->y = unit*(rand()%STANDARD);
        q=head;
        if(isWall(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isWeed(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isSnake(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isFood(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isMine(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(flag==1){
            Sweed=Sweed_temp;
            break;
        }
    }
}

void ClearSmartWeed(){
    if(Sweed!=NULL){
        free(Sweed);
        Sweed=NULL;
    }
}
#include "Data.h"
extern  GLfloat unit;

int isCweed(GLfloat x , GLfloat y){
    if(Cweed!=NULL &&(x-Cweed->x)*(x-Cweed->x)+(y-Cweed->y)*(y-Cweed->y) <= unit*unit/4){
        return 1;
    }
    return 0;
}

void CreateConfusionWeed(){
    for(;;){
        int flag=1;
        Element* Cweed_temp=(Element*)malloc(sizeof(Element));
        Cweed_temp->x = unit*(rand()%STANDARD);
        Cweed_temp->y = unit*(rand()%STANDARD);
        q=head;
        if(isWall(Cweed_temp->x, Cweed_temp->y)){
            free(Cweed_temp);
            flag=0;
        }
        if(isWeed(Cweed_temp->x, Cweed_temp->y)){
            free(Cweed_temp);
            flag=0;
        }
        if(isSnake(Cweed_temp->x, Cweed_temp->y)){
            free(Cweed_temp);
            flag=0;
        }
        if(isFood(Cweed_temp->x, Cweed_temp->y)){
            free(Cweed_temp);
            flag=0;
        }
        if(isMine(Cweed_temp->x, Cweed_temp->y)){
            free(Cweed_temp);
            flag=0;
        }
        if(isSweed(Cweed_temp->x, Cweed_temp->y)){
            free(Cweed_temp);
            flag=0;
        }
        if(isPweed(Cweed_temp->x, Cweed_temp->y)){
            free(Cweed_temp);
            flag=0;
        }
        if(flag==1){
            Cweed=Cweed_temp;
            break;
        }
    }
}

void ClearConfusionWeed(){
    if(Cweed!=NULL){
        free(Cweed);
        Cweed=NULL;
    }
}
#include "Data.h"
extern  GLfloat unit;

int isPweed(GLfloat x , GLfloat y){
    if(Pweed!=NULL &&(x-Pweed->x)*(x-Pweed->x)+(y-Pweed->y)*(y-Pweed->y) <= unit*unit/4){
        return 1;
    }
    return 0;
}

void CreatePowerWeed(){
    for(;;){
        int flag=1;
        Element* Pweed_temp=(Element*)malloc(sizeof(Element));
        Pweed_temp->x = unit*(rand()%STANDARD);
        Pweed_temp->y = unit*(rand()%STANDARD);
        q=head;
        if(isWall(Pweed_temp->x, Pweed_temp->y)){
            free(Pweed_temp);
            flag=0;
        }
        if(isWeed(Pweed_temp->x, Pweed_temp->y)){
            free(Pweed_temp);
            flag=0;
        }
        if(isSnake(Pweed_temp->x, Pweed_temp->y)){
            free(Pweed_temp);
            flag=0;
        }
        if(isFood(Pweed_temp->x, Pweed_temp->y)){
            free(Pweed_temp);
            flag=0;
        }
        if(isMine(Pweed_temp->x, Pweed_temp->y)){
            free(Pweed_temp);
            flag=0;
        }
        if(isSweed(Pweed_temp->x, Pweed_temp->y)){
            free(Pweed_temp);
            flag=0;
        }
        if(flag==1){
            Pweed=Pweed_temp;
            break;
        }
    }
}

void ClearPowerWeed(){
    if(Pweed!=NULL){
        free(Pweed);
        Pweed=NULL;
    }
}
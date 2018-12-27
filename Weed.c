#include "Data.h"

extern GLfloat unit;

//毒草判定
int isWeed(GLfloat x, GLfloat y) {
    for(int i=0; i<difficulty+1; i++)
    {
        if(weed[i] != NULL)
            if((x-weed[i]->x)*(x-weed[i]->x)+(y-weed[i]->y)*(y-weed[i]->y) <= unit*unit/4){
                free(weed[i]);
                weed[i]=NULL;
                return 1;
            }
    }
    return 0;
}

//创建毒草
void CreateWeed() {
    switch (difficulty)
    {
        case 1:
            weed[0]=perweed();
            weed[1]=perweed();
        case 2:
            weed[0]=perweed();
            weed[1]=perweed();
            weed[2]=perweed();
        case 3:
            weed[0]=perweed();
            weed[1]=perweed();
            weed[2]=perweed();
            weed[3]=perweed();
        default:break;
    }
}

//单个毒草创建
Element* perweed(){
    for(;;){
        int flag=1;
        Element* weed_temp;
        weed_temp=(Element*)malloc(sizeof(Element));
        weed_temp->x = unit*(rand()%STANDARD);
        weed_temp->y = unit*(rand()%STANDARD);
        q=head;
        if(isFood(weed_temp->x, weed_temp->y)){
            free(weed_temp);
            flag=0;
        }
        if(isMine(weed_temp->x, weed_temp->y)){
            free(weed_temp);
            flag=0;
        }
        if(isWeed(weed_temp->x, weed_temp->y)){
            free(weed_temp);
            flag=0;
        }
        if(isSnake(weed_temp->x, weed_temp->y)){
            free(weed_temp);
            flag=0;
        }
        if(isSweed(weed_temp->x, weed_temp->y)){
            free(weed_temp);
            flag=0;
        }
        if(isPweed(weed_temp->x, weed_temp->y)){
            free(weed_temp);
            flag=0;
        }
        if(flag==1){
            return weed_temp;
        }
    }
}


//清除毒草
void ClearWeed(){
    for(int i=0;i<difficulty+1;i++){
        if(weed[i]!=NULL){
            free(weed[i]);
            weed[i]=NULL;
        }
    }
}

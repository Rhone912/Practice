#include "Data.h"
extern GLfloat unit;
//食物判定
int isFood(GLfloat x, GLfloat y) {
    if(food!=NULL &&(x-food->x)*(x-food->x)+(y-food->y)*(y-food->y) <= unit*unit/4)
        return 1;
    else
        return 0;
}

//创建食物
void CreateFood() {
    for(;;){
        int flag=1;
        Element* food_temp;
        food_temp=(Element*)malloc(sizeof(Snake));
        food_temp->x = unit*(rand()%STANDARD);
        food_temp->y = unit*(rand()%STANDARD);
        if(isMine(food_temp->x, food_temp->y)){
            free(food_temp);
            flag=0;
        }
        if(isWall(food_temp->x, food_temp->y)){
            free(food_temp);
            flag=0;
        }
        if(isWeed(food_temp->x, food_temp->y)){
            free(food_temp);
            flag=0;
        }
        if(isSnake(food_temp->x, food_temp->y)){
            free(food_temp);
            flag=0;
        }
        if(isSweed(food_temp->x, food_temp->y)){
            free(food_temp);
            flag=0;
        }
        if(isPweed(food_temp->x, food_temp->y)){
            free(food_temp);
            flag=0;
        }
        if(flag==1){
            food=food_temp;
            break;
        }
    }
}

//清除食物
void ClearFood(){
    if(food!=NULL){
        free(food);
        food=NULL;
    }
}
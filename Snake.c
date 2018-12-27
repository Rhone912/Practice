#include "Data.h"

extern GLfloat unit;


//蛇身判定
int isSnake(GLfloat x, GLfloat y) {
    Snake *self;
    self=head->next;
    while(self!=NULL){
        if((x-self->x)*(x-self->x)+(y-self->y)*(y-self->y) < unit*unit/4){
            return 1;
        }
        self=self->next;
    }
    return 0;
}

//创建蛇
void CreateSnake() {
    int i;
    tail=(Snake*)malloc(sizeof(Snake));
    tail->x = unit*5;
    tail->y = unit*4;
    tail->next=NULL;
    tail->prev=NULL;
    for(i=1;i<snake_length ;i++) {
        Snake*node = (Snake*)malloc(sizeof(Snake));
        node->x = tail->x+unit;
        node->y = tail->y;
        node->prev =NULL;
        node->next = tail;
        tail->prev = node;
        tail = node ;
    }
    head = tail;
    while(tail->next!=NULL)
        tail=tail->next;
}
//清除蛇
void ClearSnake(){
    while(tail->prev!=NULL){
        tail=tail->prev;
        free(tail->next);
    }
    free(tail);
    snake_length=5;
}
#include "Data.h"

extern GLfloat unit;
int wallnum;
//创建地图
void CreateMap(int mission) {
    int i, k = 0;
    switch (mission) {
        case 3:
            for(i=10;i<=STANDARD-10;i++){
                if(i==STANDARD/2)
                    continue;
                wall[k].x=unit*STANDARD/2;
                wall[k++].y=i*unit;
            }
        case 2:
            for(i=10;i<=STANDARD-10;i++){
                    wall[k].x=i*unit;
                    wall[k++].y=unit*STANDARD/2;
            }
        case 1:
            for(i=0;i<=STANDARD;i++) {
                wall[k].x=i*unit;
                wall[k++].y=0;
                wall[k].x=i*unit;
                wall[k++].y=STANDARD*unit;
            }
            for(i=0;i<=STANDARD;i++) {
                wall[k].x=0;
                wall[k++].y=i*unit;
                wall[k].x=STANDARD*unit;
                wall[k++].y=i*unit;
            }
            wallnum=k-1;
    }
}
//墙体判定
int isWall(GLfloat x,GLfloat y) {
    for(int i=0;i<wallnum;i++){
        if((x-wall[i].x)*(x-wall[i].x)+(y-wall[i].y)*(y-wall[i].y) <= unit*unit/4) {
            return 1;
        }
    }
    return 0;
}
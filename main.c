#include "Data.h"

int main()
{
   extern int mission;
   int key,loadgameflag;
    loadgameflag=Introduction();
    while(mission<=3){
        if(loadgameflag==0){
            GameInitialization(mission);
        }
        else{
            loadgameflag = 0;
        }
        GameControl();
        system("cls");
        CursorPosition(13,20);
        printf("ͨ����%d�ء�����A�Լ�����һ�ء�",mission);
        for(;;){
            if((key=getch())=='a'){
                break;
            }
        }
        ClearGame();
    }

    return 0;
}

#include "Data.h"

int main()
{
   extern int mission;
   int key;
    Introduction();
    while(mission<=3){
        GameInitialization(mission);
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

#include "Data.h"

int snake_length=5;

//��Ϸ��ʼ��
void GameInitialization(int mission) {
    srand((unsigned)time(NULL));
    CreateMap(mission);
    CreateSnake();
    CreateFood();
    CreateWeed();
    CreateMine();
    CreateSmartWeed();
    CreatePowerWeed();
    CreateConfusionWeed();
}
//�����Ϸ
void ClearGame(){
    ClearSnake();
    ClearWeed();
    ClearMine();
    ClearFood();
    ClearSmartWeed();
    ClearPowerWeed();
    ClearConfusionWeed();
    direction= R;
    mission++;
}


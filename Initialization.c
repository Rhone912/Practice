#include "Data.h"

int snake_length=5;

//游戏初始化
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
//清除游戏
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


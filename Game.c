#include "Data.h"

int score=0,foodscore=10;
int direction = 4;
int speed=SPEED;
int endgameflag=0;
int difficulty=1;
int snake_length=5;
time_t begin_time,current_time;
extern int wallnum;
extern int mission;
int board[60][30]={0};
int min=10000;
int dirs[10000];
int res;
int book[60][30]={0};

//改变游戏速度
void ChangeSpeed() {  //速度改变
    if(speed>=SPEED-50)
        speed-=foodscore/2;
    else if(speed>=SPEED-100)
        speed-=foodscore/4;
    else if(speed>=SPEED-150)
        speed-=foodscore/8;
    else if(speed<20)
        ;
}

//移动后的判定
void EatFoodorNot() { //移动后的判定
    nexthead->next=head;
    head=nexthead;
    q=head;
    int i=1;
    if(isFood(nexthead->x, nexthead->y)){ //吃到了食物
        snake_length++;
        while(q!=NULL){
            CursorPosition(q->x, q->y);
            printf("◆");
            q=q->next;
        }
        score=score+foodscore;
        ChangeSpeed();
        CreateFood();
    }
    else if(isWeed(nexthead->x,nexthead->y)) { //吃到了毒草
        if(snake_length==1){
            endgameflag=4;
            End();
        }
        snake_length--;
        while(i<snake_length) {
            CursorPosition(q->x, q->y);
            printf("◆");
            q=q->next;
            i++;
        }
        if(i==1){
            CursorPosition(q->x, q->y);
            printf("◆");
        }
        CursorPosition(q->next->next->x, q->next->next->y);
        printf("  ");
        free(q->next->next);
        q->next->next=NULL;
        CursorPosition(q->next->x, q->next->y);
        printf("  ");
        free(q->next);
        q->next=NULL;
    }
    else if(isMine(nexthead->x,nexthead->y)){ //吃到了地雷
        if(snake_length==1){
            endgameflag=4;
            End();
        }
        snake_length/=2;
        while(i<snake_length)
        {
            CursorPosition(q->x, q->y);
            printf("◆");
            q=q->next;
            i++;
        }
        if(i==1){
            CursorPosition(q->x, q->y);
            printf("◆");
        }
        while(q!=NULL){
            CursorPosition(q->x, q->y);
            printf("  ");
            q=q->next;
        }
    }
    else if(isWall(nexthead->x,nexthead->y)==1){ //撞墙
        endgameflag=1;
        End();
    }
    else if(isSnake(nexthead->x,nexthead->y)==1) {
        endgameflag=2;
        End();
    }
    else {
        while(i<snake_length)
        {
            CursorPosition(q->x, q->y);
            printf("◆");
            q=q->next;
            i++;
        }
        if(i==1){
            CursorPosition(q->x, q->y);
            printf("◆");
        }
        CursorPosition(q->next->x, q->next->y);
        printf("  ");
        free(q->next);
        q->next=NULL;
    }
}

//食物判定
BOOL isFood(int x, int y) {
    if(x == food->x && y == food->y)
        return TRUE;
    else
        return FALSE;
}

//毒草判定
BOOL isWeed(int x, int y) {
    for(int i=0; i<difficulty+1; i++)
    {
        if(weed[i] != NULL)
            if(x == weed[i]->x && y == weed[i]->y){
                free(weed[i]);
                weed[i]=NULL;
                return TRUE;
            }
    }
    return FALSE;
}

//地雷判定
BOOL isMine(int x, int y){
    for(int i=0; i<difficulty; i++)
    {
        if(mine[i] != NULL)
            if(x == mine[i]->x && y == mine[i]->y){
                free(mine[i]);
                mine[i]=NULL;
                return TRUE;
            }
    }
    return FALSE;
}

//蛇身判定
BOOL isSnake(int x, int y) {
    Snake *self;
    self=head->next;
    while(self!=NULL){
        if(self->x==x && self->y==y){
            return TRUE;
        }
        self=self->next;
    }
    return FALSE;
}

//墙体判定
BOOL isWall(int x,int y) {
    for(int i=0;i<wallnum;i++){
        if(x==wall[i].x && y==wall[i].y) {
                return TRUE;
        }
    }
    return FALSE;
}

//排行榜
void RankList(){
    FILE *fp;
    fp=fopen("rank", "rb");
    Rank list[5];
    int i=1;
    Rank *buf=list;
    fread(buf,sizeof(Rank),5,fp);
    system("cls");
    while(i<=5){
        CursorPosition(24, i+9);
        printf("%d %s %d", i, buf->name, buf->rankscore);
        i++;
        buf++;
    }
    CursorPosition(24, i+10);
    fclose(fp);
    system("pause");
}

//游戏结束
void End() {
    system("cls");
    CursorPosition(24, 12);
    if(endgameflag==1) {
        printf("撞到墙了，游戏结束.");
    }
    else if(endgameflag==2) {
        printf("咬到自己了，游戏结束.");
    }
    else if(endgameflag==3) {
        printf("游戏已结束。");
    }
    else if(endgameflag==4) {
        printf("头已丢失，游戏结束。");
    }

    CursorPosition(24, 13);
    printf("得分 ： %d\n",score);
    CursorPosition(24, 14);
    printf("玩家姓名（10字符以内）:");
    char name[11]={0};
    gets(name);
    int i,j;
    FILE *fp;
    Rank listtemp[5];
    if(fopen("rank", "rb")==NULL){
        fp=fopen("rank", "wb");
        fclose(fp);
    }
    fp=fopen("rank", "rb+");
    if(fread(listtemp, sizeof(Rank), 5 ,fp)==0){
        for(i=0;i<5;i++){
            memset(listtemp[i].name, 0 , 11*sizeof(char));
            listtemp[i].rankscore=0;
        }
        fwrite(listtemp, sizeof(Rank), 5, fp);
        rewind(fp);
    };
    fread(listtemp,sizeof(Rank), 5, fp);
    for(i=0;i<5;i++){
        if (listtemp[i].rankscore < score){
            for(j=4;j>i;j--){
                listtemp[j].rankscore=listtemp[j-1].rankscore;
                strcpy(listtemp[j].name, listtemp[j-1].name);
            }
            listtemp[i].rankscore = score;
            strcpy(listtemp[j].name, name);
            break;
        }
    }
    rewind(fp);
    fwrite(listtemp, sizeof(Rank), 5 ,fp);
    fclose(fp);
    RankList();
    exit(0);
}

//创建食物
void CreateFood() {
    Element* food_temp;
    food_temp=(Element*)malloc(sizeof(Snake));
    do {
        food_temp->x=rand()%(MAP_LENGTH-mission*4-6)+4;
    }
    while ((food_temp->x%2)!=0);
    food_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
    q=head;
    int i;
    if(isMine(food_temp->x, food_temp->y)){
        free(food_temp);
        CreateFood();
        return;
    }
    for(int i=0;i<wallnum;i++){
        if(food_temp->x==wall[i].x && food_temp->y==wall[i].y){
            free(food_temp);
            CreateFood();
            return;
        }
    }
    for(i=0;i<difficulty+1;i++){
        if(weed[i]!=NULL){
            if(weed[i]->x==food->x &&weed[i]->y==food->y){
                free(food_temp);
                CreateFood();
                return;
            }
        }
    }
    while(q != NULL) {
        if((q->x==food_temp->x && q->y==food_temp->y)) {
            free(food_temp);
            CreateFood();
            break;
        }
        q=q->next;
    }
    CursorPosition(food_temp->x, food_temp->y);
    food=food_temp;
    printf("●");
}

//清除食物
void ClearFood(){
    if(food!=NULL){
        CursorPosition(food->x,food->y);
        printf("  ");
        free(food);
        food=NULL;
    }
}

//创建毒草
void CreateWeed() {
    switch (difficulty)
    {
        case 1:
            weed[0]=perweed();
            weed[1]=perweed();
            while(weed[1]->x==weed[0]->x && weed[1]->y==weed[0]->y)
            {
                free(weed[1]);
                weed[1]=perweed();
            }
        case 2:
            weed[0]=perweed();
            weed[1]=perweed();
            while(weed[1]->x==weed[0]->x && weed[1]->y==weed[0]->y)
            {
                free(weed[1]);
                weed[1]=perweed();
            }
            weed[2]=perweed();
            while((weed[2]->x==weed[0]->x && weed[2]->y==weed[0]->y) || (weed[2]->x==weed[1]->x && weed[2]->y==weed[1]->y))
            {
                free(weed[2]);
                weed[2]=perweed();
            }
        case 3:
            weed[0]=perweed();
            weed[1]=perweed();
            while(weed[1]->x==weed[0]->x && weed[1]->y==weed[0]->y)
            {
                free(weed[1]);
                weed[1]=perweed();
            }
            weed[2]=perweed();
            while((weed[2]->x==weed[0]->x && weed[2]->y==weed[0]->y) || (weed[2]->x==weed[1]->x && weed[2]->y==weed[1]->y))
            {
                free(weed[2]);
                weed[2]=perweed();
            }
            weed[3]=perweed();
            while((weed[3]->x==weed[0]->x && weed[3]->y==weed[0]->y) || (weed[3]->x==weed[1]->x && weed[3]->y==weed[1]->y) || (weed[3]->x==weed[2]->x && weed[3]->y==weed[2]->y))
            {
                free(weed[3]);
                weed[3]=perweed();
            }
        default:break;
    }
    for(int i=0;i<difficulty+1;i++)
    {
        CursorPosition(weed[i]->x,weed[i]->y);
        printf("○");
    }
    begin_time=clock();
}

//单个毒草创建
Element* perweed(){
    Element* weed_temp;
    weed_temp=(Element*)malloc(sizeof(Element));
    weed_temp->x=(rand()%(MAP_LENGTH/2-mission*4-6)+2)*2;
    weed_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
    q=head;
    if(weed_temp->x == food->x && weed_temp->y == food->y){
        free(weed_temp);
        return perweed();
    }
    if(isMine(weed_temp->x, weed_temp->y)){
        free(weed_temp);
        return perweed();
    }
    for(int i=0;i<wallnum;i++){
        if(weed_temp->x==wall[i].x && weed_temp->y==wall[i].y){
            free(weed_temp);
            return perweed();
        }
    }
    while(q != NULL) {
        if((q->x==weed_temp->x && q->y==weed_temp->y)) {
            free(weed_temp);
            return perweed();
        }
        q=q->next;
    }
    return weed_temp;
}

//清除毒草
void ClearWeed(){
    for(int i=0;i<difficulty+1;i++){
        if(weed[i]!=NULL){
            CursorPosition(weed[i]->x,weed[i]->y);
            printf("  ");
            free(weed[i]);
            weed[i]=NULL;
        }
    }
}

//创建地雷
void CreateMine(){
    switch (difficulty)
    {
        case 1:
            mine[0]=permine();
        case 2:
            mine[0]=permine();
            mine[1]=permine();
            while(mine[1]->x==mine[0]->x && mine[1]->y==mine[0]->y)
            {
                free(mine[1]);
                mine[1]=permine();
            }
        case 3:
            mine[0]=permine();
            mine[1]=permine();
            while(mine[1]->x==mine[0]->x && mine[1]->y==mine[0]->y)
            {
                free(mine[1]);
                mine[1]=permine();
            }
            mine[2]=permine();
            while((mine[2]->x==mine[0]->x && mine[2]->y==weed[0]->y) || (mine[2]->x==mine[1]->x && mine[2]->y==mine[1]->y))
            {
                free(mine[2]);
                mine[2]=permine();
            }
        default:break;
    }
    for(int i=0;i<difficulty;i++)
    {
        CursorPosition(mine[i]->x,mine[i]->y);
        printf("%c",'\001' );
    }
}

//单个地雷创建
Element* permine(){
    Element* mine_temp;
    mine_temp=(Element*)malloc(sizeof(Element));
    mine_temp->x=(rand()%(MAP_LENGTH/2-mission*4-6)+2)*2;
    mine_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
    q=head;
    if(mine_temp->x == food->x && mine_temp->y == food->y){
        free(mine_temp);
        return perweed();
    }
    if(isMine(mine_temp->x, mine_temp->y)){
        free(mine_temp);
        return perweed();
    }
    for(int i=0;i<wallnum;i++){
        if(mine_temp->x==wall[i].x && mine_temp->y==wall[i].y){
            free(mine_temp);
            return perweed();
        }
    }
    while(q != NULL) {
        if((q->x==mine_temp->x && q->y==mine_temp->y)) {
            free(mine_temp);
            return perweed();
        }
        q=q->next;
    }
    return mine_temp;
};
//清除地雷
void ClearMine(){
    for(int i=0;i<difficulty;i++){
        if(mine[i]!=NULL){
            CursorPosition(mine[i]->x,mine[i]->y);
            printf("  ");
            free(mine[i]);
            mine[i]=NULL;
        }
    }
}

//智慧草的创建
void CreateSmartWeed(){
    if(Sweed!=NULL)
        return;
    Element* Sweed_temp=(Element*)malloc(sizeof(Element));
    Sweed_temp->x=(rand()%(MAP_LENGTH/2-mission*4-6)+2)*2;
    Sweed_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
    q=head;
    int i;
    for(i=0;i<wallnum;i++){
        if(Sweed_temp->x==wall[i].x && Sweed_temp->y==wall[i].y){
            free(Sweed_temp);
            CreateSmartWeed();
            return;
        }
    }
    for(i=0;i<difficulty+2;i++){
        if(weed[i]!=NULL){
            if(weed[i]->x==food->x &&weed[i]->y==food->y){
                free(Sweed_temp);
                CreateMine();
                return;
            }
        }
    }
    if(Sweed_temp->x==food->x || Sweed_temp->x==food->y){
        free(Sweed_temp);
        CreateMine();
        return;
    }

    while(q != NULL) {
        if((q->x==Sweed_temp->x && q->y==Sweed_temp->y)) {
            free(Sweed_temp);
            CreateSmartWeed();
            break;
        }
        q=q->next;
    }
    Sweed=Sweed_temp;
    CursorPosition(Sweed->x,Sweed->y);
    printf("\33[40;33m○\033[0m");
}
//蛇的移动处理
int SnakeMove() {
    current_time=clock();
    CursorPosition(64, 8);
    printf("得分：%d  ",score);
    if((10000-(current_time-begin_time)%10000)/1000==0){
        ClearWeed();
        CreateWeed();
    }
    CursorPosition(64, 10);
    printf("毒草刷新时间：%ld",(long)(10000-(current_time-begin_time)%10000)/1000);
    nexthead=(Snake*)malloc(sizeof(Snake));
    if(direction==U) {
        nexthead->x=head->x;
        nexthead->y=head->y-1;
    }
    else if(direction==D) {
        nexthead->x=head->x;
        nexthead->y=head->y+1;
    }
    else if(direction==L) {
        nexthead->x=head->x-2;
        nexthead->y=head->y;
    }
    else if(direction==R) {
        nexthead->x=head->x+2;
        nexthead->y=head->y;
    }
    EatFoodorNot();
    switch(difficulty){
        case 1:
            if(score>=50*mission){ ;
                difficulty++;
                return 1;
            }
        case 2:
            if(score>=75*mission){
                difficulty++;
                return 1;
            }
        case 3:
            if(score>=100*mission){
                return 1;
            }
    }
    weed_flick();
    return 0;
}

//游戏暂停
void Stop() {
    while(1){
        Sleep(300);
        if(GetAsyncKeyState(VK_SPACE)) {
            break;
        }
    }
}

//游戏基本控制
void GameControl() {
    CursorPosition(64, 8);
    printf("得分：%d  ",score);
    CursorPosition(64, 13);
    printf("用↑.↓.←.→分别控制蛇的移动.");
    CursorPosition(64, 14);
    printf("每个食物价值10分。");
    CursorPosition(64, 15);
    printf("ESC ：退出游戏.SPACE：暂停游戏.");
    CursorPosition(64,16);
    printf("TAB : 自动游戏.");
    direction=R;
    for(;;) {
        if(GetAsyncKeyState(VK_UP) && direction!=D) {
            direction=U;
        }
        else if(GetAsyncKeyState(VK_DOWN) && direction!=U) {
            direction=D;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& direction!=R) {
            direction=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& direction!=L) {
            direction=R;
        }
        else if(GetAsyncKeyState(VK_SPACE)) {
            Stop();
        }
        else if(GetAsyncKeyState(VK_ESCAPE)) {
            endgameflag=3;
            break;
        }
        else if(GetAsyncKeyState(VK_TAB)) {
            if(Auto()==1)
                return;
        }
        Sleep(speed);
        if(SnakeMove()==1){
            return;
        }
    }
}

void weed_flick(){
    int flag=0;
    current_time=clock();
    if((current_time-begin_time)%20000!=0 && (current_time-begin_time)%1000<speed)
        flag=1;
    if(flag==1){
        for(int i=0;i<difficulty+1;i++){
            if(weed[i]!=NULL){
                CursorPosition(weed[i]->x,weed[i]->y);
                printf("  ");
            }
        }
    }
    else{
        for(int i=0;i<difficulty+1;i++){
            if(weed[i]!=NULL){
                CursorPosition(weed[i]->x,weed[i]->y);
                printf("○");
            }
        }
    }
}

//游戏存档
void SaveGame(){

}

//自动寻路算法

int Auto() //自动移动
{
    for(;;){
        min=10000;
        AutoMove(head->x, head->y, 0);
        direction = res;
        Sleep(speed);
        if(SnakeMove()==1){
            return 1;
        }
        if(GetAsyncKeyState(VK_TAB))
            break;
    }
}

BOOL isMovePossible (int x,int y, int direction)
{
    BOOL flag = FALSE;
    switch (direction) {
        case L:
            if (!isWall(x-2,y)&&!isSnake(x-2,y)) flag = TRUE; break;
        case R:
            if (!isWall(x+2,y)&&!isSnake(x+2,y)) flag = TRUE; break;
        case U:
            if (!isWall(x,y-1)&&!isSnake(x,y-1)) flag = TRUE; break;
        case D:
            if (!isWall(x,y+1)&&!isSnake(x,y+1)) flag = TRUE; break;
    }
    return flag;
}

void boardReset ()
{
    int x,y;
    for (x=0;x<=MAP_LENGTH-mission*4;x+=2) {
        for(y=0;y<=MAP_WIDTH-mission*2;y++){
            if (x==food->x && y==food->y)
                board[x][y] = FOOD;
            else if(isSnake(x,y))
                board[x][y] = SNAKE;
            else if(isWeed(x,y))
                board[x][y] = WEED;
            else if(isWall(x,y))
                board[x][y] =  WALL;
            else if( isMine(x, y))
                board[x][y] = MINE;
            else
                board[x][y] = BLANK;
        }
    }
}

void AutoMove(int x, int y, int steps){
    int move[4][2] ={{0,-1},{0,1},{-2,0},{2,0}};
    int nextx, nexty ,k=0,distance,minfornow=10000,shortcut;
    if( x == food-> x && y == food->y ){
        if( steps < min){
            min = steps;
            res = dirs[0];
            return;
        }
    }
    for(k=U;k<=R;k++){
        nextx=x+move[k][0];
        nexty=y+move[k][1];
        distance=abs(nextx-food->x)+abs(nexty-food->y);
        if(isSnake(nextx, nexty) || isWall(nextx, nexty)) {
            continue;
        }
        if(isMine(nextx, nexty)){
            distance+=150;
        }
        else if(isWeed(nextx, nexty)){
            distance+=100;
        }
        if(distance < minfornow){
            minfornow = distance;
            shortcut = k;
        }
    }
    if(steps==0){
        dirs[0]=shortcut;
    }
    AutoMove( x+move[shortcut][0], y+move[shortcut][1], steps+1);
}

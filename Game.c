#include "Data.h"

int score=0,foodscore=10;
int direction = R;
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
int autotime = 0;

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
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
            q=q->next;
        }
        score=score+foodscore;
        ChangeSpeed();
        CreateFood();
        if(autotime>0){
            autotime--;
        }
    }
    else if(isWeed(nexthead->x,nexthead->y)) { //吃到了毒草
        if(snake_length==1){
            endgameflag=4;
            End();
        }
        snake_length--;
        while(i<snake_length) {
            CursorPosition(q->x, q->y);
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
            q=q->next;
            i++;
        }
        if(i==1){
            CursorPosition(q->x, q->y);
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
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
        score-=20;
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
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
            q=q->next;
            i++;
        }
        if(i==1){
            CursorPosition(q->x, q->y);
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
        }
        while(q!=NULL){
            CursorPosition(q->x, q->y);
            printf("  ");
            q=q->next;
        }
        score-=50;
    }
    else if (isSweed(nexthead->x, nexthead->y)){ //吃到了智慧草
        while(i<snake_length)
        {
            CursorPosition(q->x, q->y);
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
            q=q->next;
            i++;
        }
        if(i==1) {
            CursorPosition(q->x, q->y);
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
        }
        CursorPosition(q->next->x, q->next->y);
        printf("  ");
        free(q->next);
        q->next=NULL;
        autotime+=2;
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
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
            q=q->next;
            i++;
        }
        if(i==1){
            CursorPosition(q->x, q->y);
            if(autotime>0){
                printf("\33[40;33m◆\033[0m");
            }
            else
                printf("◆");
        }
        CursorPosition(q->next->x, q->next->y);
        printf("  ");
        free(q->next);
        q->next=NULL;
    }
}

//食物判定
int isFood(int x, int y) {
    if(food!=NULL &&(x == food->x && y == food->y))
        return 1;
    else
        return 0;
}

//毒草判定
int isWeed(int x, int y) {
    for(int i=0; i<difficulty+1; i++)
    {
        if(weed[i] != NULL)
            if(x == weed[i]->x && y == weed[i]->y){
                free(weed[i]);
                weed[i]=NULL;
                return 1;
            }
    }
    return 0;
}

//地雷判定
int isMine(int x, int y){
    for(int i=0; i<difficulty; i++)
    {
        if(mine[i] != NULL)
            if(x == mine[i]->x && y == mine[i]->y){
                free(mine[i]);
                mine[i]=NULL;
                return 1;
            }
    }
    return 0;
}

//蛇身判定
int isSnake(int x, int y) {
    Snake *self;
    self=head->next;
    while(self!=NULL){
        if(self->x==x && self->y==y){
            return 1;
        }
        self=self->next;
    }
    return 0;
}

//墙体判定
int isWall(int x,int y) {
    for(int i=0;i<wallnum;i++){
        if(x==wall[i].x && y==wall[i].y) {
                return 1;
        }
    }
    return 0;
}

//智慧草判定
int isSweed(int x, int y){
    if(Sweed!=NULL &&(x==Sweed->x && y==Sweed->y)){
        return 1;
    }
    return 0;
}

//排行榜
void RankList(){
    FILE *fp;
    fp=fopen("rank", "rb");
    if(fp==NULL){
        CursorPosition(24,12);
        printf("无排行榜文件");
        system("pause");
        return;
    }
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
    system("cls");
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
	scanf("%s", name);
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
    for(;;){
        int flag=1;
        Element* food_temp;
        food_temp=(Element*)malloc(sizeof(Snake));
        do {
            food_temp->x=rand()%(MAP_LENGTH-mission*4-6)+4;
        }
        while ((food_temp->x%2)!=0);
        food_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
        q=head;
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
        if(flag==1){
            CursorPosition(food_temp->x, food_temp->y);
            food=food_temp;
            printf("●");
            break;
        }
    }
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
    for(int i=0;i<difficulty+1;i++)
    {
        CursorPosition(weed[i]->x,weed[i]->y);
        printf("○");
    }
    begin_time=clock();
}

//单个毒草创建
Element* perweed(){
    for(;;){
        int flag=1;
        Element* weed_temp;
        weed_temp=(Element*)malloc(sizeof(Element));
        weed_temp->x=(rand()%(MAP_LENGTH/2-mission*4-6)+2)*2;
        weed_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
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
        if(flag==1){
            return weed_temp;
        }
    }

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
        case 3:
            mine[0]=permine();
            mine[1]=permine();
            mine[2]=permine();
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
    for(;;){
        int flag=1;
        Element* mine_temp;
        mine_temp=(Element*)malloc(sizeof(Element));
        mine_temp->x=(rand()%(MAP_LENGTH/2-mission*4-6)+2)*2;
        mine_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
        q=head;
        if(isFood(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isMine(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isWeed(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isSnake(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(isSweed(mine_temp->x, mine_temp->y)){
            free(mine_temp);
            flag=0;
        }
        if(flag==1){
            return mine_temp;
        }
    }
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
    for(;;){
        int flag=1;
        Element* Sweed_temp=(Element*)malloc(sizeof(Element));
        Sweed_temp->x=(rand()%(MAP_LENGTH/2-mission*4-6)+2)*2;
        Sweed_temp->y=rand()%(MAP_WIDTH-mission*2-6)+4;
        q=head;
        if(isWall(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isWeed(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isSnake(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isFood(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(isMine(Sweed_temp->x, Sweed_temp->y)){
            free(Sweed_temp);
            flag=0;
        }
        if(flag==1){
            Sweed=Sweed_temp;
            CursorPosition(Sweed->x,Sweed->y);
            printf("\33[40;33m○\033[0m");
            break;
        }
    }
}

void ClearSmartWeed(){
    if(Sweed!=NULL){
        CursorPosition(Sweed->x, Sweed->y);
        printf("  ");
        free(Sweed);
        Sweed=NULL;
    }
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
    for(;;) {
        if(autotime>0){
            Auto();
        }
        else if(GetAsyncKeyState(VK_UP) && direction!=D) {
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
            system("cls");
            CursorPosition(20,14);
            printf("游戏已结束，按下S可保存游戏，按下Q可退出游戏并记录分数。");
            while(1){
                if(getch() == 's'){
                    SaveGame();
                    CursorPosition(20,16);
                    printf("游戏保存成功。");
                    Sleep(500);
                    system("pause");
                    End();
                    return;
                }
                else if(getch() == 'q'){
                    End();
                    return;
                }
            }
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
    FILE* fp=fopen("save", "wb");
    fwrite(&mission, sizeof(int), 1 ,fp);
    fwrite(&direction, sizeof(int), 1 ,fp);
    fwrite(&score, sizeof(int), 1, fp);
    fwrite(&speed, sizeof(int), 1 ,fp);
    fwrite(&difficulty, sizeof(int), 1 ,fp);
    fwrite(&snake_length, sizeof(snake_length), 1, fp);
    fwrite(food, sizeof(Element), 1, fp);
    q=head;
    while(q!=NULL){
        fwrite(q, sizeof(Snake), 1, fp);
        q=q->next;
    }
    for(int i=0; i<difficulty+1; i++){
        if(weed[i]!=NULL)
            fwrite(weed[i], sizeof(Element), 1, fp);
    }
    for(int i=0; i<difficulty; i++){
        if(mine[i]!=NULL)
            fwrite(mine[i], sizeof(Element), 1, fp);
    }
    if(Sweed!=NULL){
        fwrite(Sweed, sizeof(Element), 1 ,fp);
    }
    fclose(fp);
}

int LoadGame(){
    srand((unsigned)time(NULL));
    system("mode con cols=100 lines=27");
    system("cls");
    FILE* fp=fopen("save", "rb");
    fread(&mission, sizeof(int), 1, fp);
    fread(&direction, sizeof(int), 1 ,fp);
    fread(&score, sizeof(int), 1, fp);
    fread(&speed, sizeof(int), 1 ,fp);
    fread(&difficulty, sizeof(int), 1 ,fp);
    fread(&snake_length, sizeof(int), 1, fp);
    food=(Element*)malloc(sizeof(Element));
    fread(food, sizeof(Element), 1, fp);
    CreateMap(mission);
    CursorPosition(food->x, food->y);
    printf("●");
    head=(Snake*)malloc(sizeof(Snake));
    fread(head, sizeof(Snake), 1, fp);
    CursorPosition(head->x, head->y);
    printf("◆");
    head->next=NULL;
    head->prev=NULL;
    Snake* p=head;
    int i=1;
    while(i<snake_length){
        q=(Snake*)malloc(sizeof(Snake));
        fread(q, sizeof(Snake), 1, fp);
        CursorPosition(q->x, q->y);
        printf("◆");
        q->next=NULL;
        p->next=q;
        q->prev=p;
        p=q;
        i++;
    }
    for(int i=0; i<difficulty+1; i++){
        weed[i]=(Element*)malloc(sizeof(Element));
        fread(weed[i], sizeof(Element), 1, fp);
        CursorPosition(weed[i]->x, weed[i]->y);
        printf("○");
    }
    for(int i=0; i<difficulty; i++){
        mine[i]=(Element*)malloc(sizeof(Element));
        fread(mine[i], sizeof(Element), 1, fp);
        CursorPosition(mine[i]->x, mine[i]->y);
        printf("%c",'\001' );
    }
    Sweed=(Element*)malloc(sizeof(Element));
    fread(Sweed, sizeof(Element), 1, fp);
    CursorPosition(Sweed->x, Sweed->y);
    printf("\33[40;33m○\033[0m");
    hideCursor();
    fclose(fp);
    return 1;
}

//自动寻路算法

int Auto() //自动移动
{
    min=10000;
    AutoMove(head->x, head->y, 0);
    direction = res;
	return 1;
}

int isMovePossible (int x,int y, int direction)
{
    int flag = 0;
    switch (direction) {
        case L:
            if (!isWall(x-2,y)&&!isSnake(x-2,y)) flag = 1; break;
        case R:
            if (!isWall(x+2,y)&&!isSnake(x+2,y)) flag = 1; break;
        case U:
            if (!isWall(x,y-1)&&!isSnake(x,y-1)) flag = 1; break;
        case D:
            if (!isWall(x,y+1)&&!isSnake(x,y+1)) flag = 1; break;
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
    res=shortcut;
}

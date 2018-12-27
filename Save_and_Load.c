#include "Data.h"

char name[11];
int loadflag=0;
//游戏存档
void SaveGame(){
    FILE* fp=fopen("save", "wb");
    fwrite(&mission, sizeof(int), 1 ,fp);
    fwrite(&direction, sizeof(int), 1 ,fp);
    fwrite(&score, sizeof(int), 1, fp);
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
    if(Pweed!=NULL){
        fwrite(Pweed, sizeof(Element), 1 ,fp);
    }
    if(Cweed!=NULL){
        fwrite(Cweed, sizeof(Element), 1 ,fp);
    }
    fclose(fp);
}

void LoadOption(){
    FILE* fp;
    fp = fopen("option", "rb");
    if(fp==NULL){
        return;
    }
    fread(&difficulty, sizeof(int), 1, fp);
    fread(&name, sizeof(int), 1, fp);
    fread(&loadflag, sizeof(int), 1, fp);
    fclose(fp);
}

int LoadGame(){
    srand((unsigned)time(NULL));
    FILE* fp=fopen("save", "rb");
    fread(&mission, sizeof(int), 1, fp);
    fread(&direction, sizeof(int), 1 ,fp);
    fread(&score, sizeof(int), 1, fp);
    fread(&difficulty, sizeof(int), 1 ,fp);
    fread(&snake_length, sizeof(int), 1, fp);
    food=(Element*)malloc(sizeof(Element));
    fread(food, sizeof(Element), 1, fp);
    CreateMap(mission);
    head=(Snake*)malloc(sizeof(Snake));
    fread(head, sizeof(Snake), 1, fp);
    head->next=NULL;
    head->prev=NULL;
    Snake* p=head;
    int i=1;
    while(i<snake_length){
        q=(Snake*)malloc(sizeof(Snake));
        fread(q, sizeof(Snake), 1, fp);
        q->next=NULL;
        p->next=q;
        q->prev=p;
        p=q;
        i++;
    }
    tail = head;
    while(tail->next!=NULL)
        tail=tail->next;
    for(int i=0; i<difficulty+1; i++){
        weed[i]=(Element*)malloc(sizeof(Element));
        fread(weed[i], sizeof(Element), 1, fp);
    }
    for(int i=0; i<difficulty; i++){
        mine[i]=(Element*)malloc(sizeof(Element));
        fread(mine[i], sizeof(Element), 1, fp);
    }
    Sweed=(Element*)malloc(sizeof(Element));
    fread(Sweed, sizeof(Element), 1, fp);
    Pweed=(Element*)malloc(sizeof(Element));
    fread(Pweed, sizeof(Element), 1, fp);
    Cweed=(Element*)malloc(sizeof(Element));
    fread(Cweed, sizeof(Element), 1, fp);
    fclose(fp);
    return 1;
}

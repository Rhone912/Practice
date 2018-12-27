#include "Data.h"

const GLfloat pi = 3.1415926536f;
const GLfloat unit = 2.0f/STANDARD;
int pausegameflag=0;
int flick=1;
int entergameflag=0;
int weedrefresh = 0;
extern int endgameflag;
extern int window;
extern int powertime;
extern int confusiontime;

void Circle(GLfloat x, GLfloat y, GLfloat r){
    int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < 100; i++)
    {
        glVertex2f(x+r*cos(2*pi/100*i), y+r*sin(2*pi/100*i));
    }
    glEnd();
    glFlush();
}

void GLinit(GLsizei width, GLsizei height){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, (GLdouble)width, 0.0f, (GLdouble)height);
}

void ChangeSize(GLsizei w, GLsizei h){
    GLfloat aspectRatio;
    if(h==0)
        h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio=(GLfloat)w/(GLfloat)h;
    if(w<=h){
        glOrtho(-1.0f,1.0f,-1.0f/aspectRatio, 1.0f/aspectRatio, 1.0f, -1.0f);
    }
    else{
        glOrtho(-1.0*aspectRatio,1.0*aspectRatio,-1.0f, 1.0f, 1.0f, -1.0f);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawGlScene(){
    if(entergameflag==1){
        GameInitialization(mission);
        entergameflag++;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.0f, -1.0f, 0.0f);
    if(confusiontime<=0){
        int i;
        Snake* node = head;
        for(i=1;i<=snake_length;i++){
            if(autotime > 0){
                glColor3f(1.0,1.0,0.0);
            }
            else if(powertime > 0){
                glColor3f(0.3f, 0.2f, 0.7f);
            }
            else{
                glColor3f(0.0f, 1.0f, 0.0f );
            }
            Circle(node->x, node->y, unit/2);
            node = node->next;
        }
        if(food !=NULL){
            glColor3f(1.0f, 0.0f, 0.0f);
            Circle(food->x, food->y, unit/2);
        }
        if(flick){
            for(i=0;i<difficulty+1;i++){
                if(weed[i]!=NULL){
                    glColor3f(0.0f, 0.7f, 0.3f);
                    Circle(weed[i]->x, weed[i]->y, unit/2);
                }
            }
        }
        for(i=0;i<difficulty;i++){
            if(mine[i]!=NULL){
                glColor3f(1.0f, 0.1f, 1.0f);
                glRectf(mine[i]->x-unit/2,mine[i]->y-unit/2,mine[i]->x+unit/2,mine[i]->y+unit/2);
            }
        }
        if(Sweed!=NULL){
            glColor3f(1.0f, 1.0f, 0.0f);
            Circle(Sweed->x, Sweed->y, unit/2);
        }
        if(Pweed!=NULL){
            glColor3f(0.3f, 0.2f, 0.7f);
            Circle(Pweed->x, Pweed->y, unit/2);
        }
        if(Cweed!=NULL){
            glColor3f(0.6f, 0.8f, 1.0f);
            Circle(Cweed->x, Cweed->y, unit/2);
        }
        for(i=0;i<wallnum;i++){
            glColor3f(1.0f,1.0f,1.0f);
            glRectf(wall[i].x-unit/2,wall[i].y-unit/2,wall[i].x+unit/2,wall[i].y+unit/2);
        }
    }
    glutSwapBuffers();
}

void GameControl(int key, int x, int y) {
    if (pausegameflag)
        return;
    else {
        switch (key) {
            case GLUT_KEY_UP:
                if (direction != D)
                    direction = U;
                break;
            case GLUT_KEY_DOWN:
                if (direction != U)
                    direction = D;
                break;
            case GLUT_KEY_RIGHT:
                if (direction != L)
                    direction = R;
                break;
            case GLUT_KEY_LEFT:
                if (direction != R)
                    direction = L;
                break;
            default:
                break;
        }
    }
}

void KeyPressed(unsigned char key, int x, int y){
    if(key == 27){
        SaveGame();
        glutDestroyWindow(window);
        exit(0);
    }
    else if(key==' '){
        pausegameflag=!pausegameflag;
        if(pausegameflag==0){
            glutTimerFunc(40*(4-difficulty),OnTimer, pausegameflag);
        }
    }
}

void OnTimer(int value) {
    if (!value && !pausegameflag && !endgameflag) {
        SnakeMove();
    }
    flick = !flick;
    weedrefresh++;
    if(weedrefresh==100){
        ClearWeed();
        CreateWeed();
        weedrefresh=0;
    }
    glutTimerFunc(40*(4-difficulty), OnTimer, pausegameflag);
};

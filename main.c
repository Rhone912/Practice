#include "Data.h"

#pragma comment(linker, "/subsystem:/"windows/" /entry:/"mainCRTStartup/"" )
extern int pausegameflag;
extern int entergameflag;
extern int loadflag;
int window;

int main(int argc, char *argv[])
{
    LoadOption();
    if(loadflag==1){
        LoadGame();
    }
    else
        GameInitialization(mission);
    //PlaySound("Music.wav",NULL,SND_SYNC | SND_LOOP|  SND_FILENAME);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    GLinit(700, 700);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);
    window=glutCreateWindow("Ã∞≥‘…ﬂ-”Œœ∑ΩÁ√Ê");
    glutDisplayFunc(DrawGlScene);
    glutIdleFunc(DrawGlScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(KeyPressed);
    glutSpecialFunc(GameControl);
    glutTimerFunc(40*(4-difficulty), OnTimer, pausegameflag);
    glutMainLoop();
    return 0;
}

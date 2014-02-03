#include "window.h"

void reshape(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, width/height, 1, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glutSwapBuffers();
    update_game();
}

void init_glut(int argc, char **argv, int window_width, int window_height, char* title){
    glutInit(&argc, argv);
    glutInitWindowPosition(-1, 10);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(title);
    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutReshapeFunc(reshape);
    // glutKeyboardFunc(keyboard_down);
    // glutKeyboardUpFunc(keyboard_up);
}

void setup_game() {
    model = (Data*)malloc(sizeof(Data));
    build_vbo(model);
}

// void keyboard_down(unsigned char key, int x, int y){
//     switch(key){
//         //player controls
//         case 'w':{ player->fwd = true;}break;
//         case 'a':{ player->lft = true;}break;
//         case 's':{ player->bck = true;}break;
//         case 'd':{ player->rt = true;}break;
//     }
// }

// void keyboard_up(unsigned char key, int x, int y){
//     switch(key){
//         case 'w':{ player->fwd =false;}break;
//         case 'a':{ player->lft =false;}break;
//         case 's':{ player->bck =false;}break;
//         case 'd':{ player->rt = false;}break;
//     }
// }

void update_game() {
    
}
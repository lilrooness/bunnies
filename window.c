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
    gluLookAt(player->xpos, 1, player->ypos,//eye position
              player->xpos+player->xdir*10, 1, player->ypos+player->ydir*10,//look at
              0.0, 1.0, 0.0);//up vector

    glPushMatrix();
        glScalef(5, 5, 5);
        glEnableClientState(GL_VERTEX_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, model->vboid);
            glVertexPointer(3, GL_FLOAT, 0, 0);

        glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboid);
            glDrawElements(GL_TRIANGLES, model->faces*3, GL_UNSIGNED_INT, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
        glEnd();
    glPopMatrix();

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
    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);
}

void setup_game() {
    model = (Data*)malloc(sizeof(Data));
    player = (Player*)malloc(sizeof(Player));
    map = (char*)malloc(sizeof(char) * 100);
    player->xpos = 0.0f;
    player->ypos = -10.0f;
    player->xdir = 0.0f;
    player->ydir = 1.0f;
    player->fwd = 0;
    player->bck = 0;
    player->lft = 0;
    player->rt = 0;
    player->turnspeed = 0.01;
    player->angle = 0;

    load_obj(model, "res/bunny.obj.txt", 4968, 2503);
    build_vbo(model);
}

void keyboard_down(unsigned char key, int x, int y){
    switch(key){
        //player controls
        case 'w':{ player->fwd = true;}break;
        case 'a':{ player->lft = true;}break;
        case 's':{ player->bck = true;}break;
        case 'd':{ player->rt = true;}break;
        //environment controls
        // case 'f':{toggle(FOG);}break;
        // case 'l':{toggle(LIGHTING);}break;
        // case 'c':{toggle(COLLISION);}break;
        // case 't':{toggle(SOLID);}break;
    }
}

void keyboard_up(unsigned char key, int x, int y){
    switch(key){
        case 'w':{ player->fwd =false;}break;
        case 'a':{ player->lft =false;}break;
        case 's':{ player->bck =false;}break;
        case 'd':{ player->rt = false;}break;
    }
}

void update_game() {
    if(player->fwd == true) {
        player->xpos += player->xdir*0.1;
        player->ypos += player->ydir*0.1;
    }
    if(player->bck == true) {
        player->xpos -= player->xdir*0.1;
        player->ypos -= player->ydir*0.1;
    }
    if(player->lft == true) {
        player->angle -= player->turnspeed;
        player->xdir = (float)sin(player->angle);
        player->ydir = -(float)cos(player->angle);
    }
    if(player->rt == true) {
        player->angle += player->turnspeed;
        player->xdir = (float)sin(player->angle);
        player->ydir = -(float)cos(player->angle);
    }
}
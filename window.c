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

    drawGround();

    glPushMatrix();
        render_vbo(model);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(player->xpos, -0.4f, player->ypos);
        glRotatef(-90, 1, 0, 0);
        
        glRotatef(player->angle * -57.3f + 176, 0, 0, 1.0f);//really hacky way of doing gun rotation.
        glScalef(0.1f, 0.1f, 0.1f);
        render_vbo(gun);
    glPopMatrix();

    glutSwapBuffers();
    update_game();
}

void drawGround() {
    // glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, stuff_texture);
    glColor3f(255, 0, 0);
    glBegin(GL_QUADS);
        glVertex3f(-100, -3, -100);
        glVertex3f(100, -3, -100);
        glVertex3f(100, -3, 100);
        glVertex3f(-100, -3, 100);
    glEnd();
    glColor3f(255, 255, 255);
    // glDisable(GL_TEXTURE_2D);
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
    gun = (Data*)malloc(sizeof(Data));
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
    player->angle = 10;

    load_obj(model, "res/bunnyn.obj", 4968, 2503, 0);
    load_obj(gun, "res/gun.obj",7251/3 , 7251, 1);

    stuff_texture = SOIL_load_OGL_texture("res/texture.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, stuff_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    build_vbo(gun);
    build_vbo(model);
}

void keyboard_down(unsigned char key, int x, int y){
    switch(key){
        //player controls
        case 'w':{ player->fwd = true;}break;
        case 'a':{ player->lft = true;}break;
        case 's':{ player->bck = true;}break;
        case 'd':{ player->rt = true;}break;
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
    player->xdir = (float)sin(player->angle);
    player->ydir = -(float)cos(player->angle);
}
#include "window.h"

void reshape(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, width/height, 1, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(255, 255, 255);

    gluLookAt(0, 0, 10, 0, 0, -10, 0, 1, 0);

    // skybox();
    glPushMatrix();
    // glScalef(0.5, 0.5, 0.5);
    render_vbo(bunny);
    glPopMatrix();

    glutSwapBuffers();
    update_game();
}

void skybox() {
    glBindTexture(GL_TEXTURE_2D, sky);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        //back panel
        glTexCoord2i(0, 0);
        glVertex3f(-30, -30, -30);

        glTexCoord2i(1, 0);
        glVertex3f(30, -30, -30);

        glTexCoord2i(1, 1);
        glVertex3f(30, 30, -30);

        glTexCoord2i(0, 1);
        glVertex3f(-30, 30, -30);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, grass);
    // glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        //Grass
        glPushMatrix();
        glTranslatef(0, -50, 0);
            glTexCoord2i(0, 0);
            glVertex3f(-30, -30, -20);
    
            glTexCoord2i(1, 0);
            glVertex3f(30, -30, -20);
    
            glTexCoord2i(1, 1);
            glVertex3f(30, 10, -20);
    
            glTexCoord2i(0, 1);
            glVertex3f(-30, 10, -20);
        glPopMatrix();
    glEnd();
    glDisable(GL_TEXTURE_2D);
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
    bunny = (Data*)malloc(sizeof(Data));
    load_obj(bunny, "res/bunny.obj", 4968, 2503, 0);
    build_vbo(bunny);

    sky = SOIL_load_OGL_texture("res/skybox.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, sky);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    grass = SOIL_load_OGL_texture("res/grass.jpeg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, sky);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
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
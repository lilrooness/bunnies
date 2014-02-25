#include "window.h"

void reshape(int width, int height) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, width/height, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(255, 255, 255);
}

void render() {
    // printf("%f\n", angle);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, 0, 10,
              camx, camy, 0,
              // 0, 0, 0,m
              0, 1, 0);
    skybox();

    glUseProgram(shader_program);
    drawTeapot(current_target.x, current_target.y);
    render_vbo(bunny);
    glUseProgram(0);

    char buffer[400];
    int len = 400;
    glGetInfoLogARB(shader_program, 400, &len, buffer);
    printf("%s\n", buffer);

    updatecameraposition();

    glColor3f(255, 0, 0);
    
    glDisable(GL_LIGHTING);
    int i;
    for(i=0; i<psystems; i++) {
        updateparticlesystem(*(particle_systems + i));
        rendersystem(*(particle_systems + (i)));
    }
    glEnable(GL_LIGHTING);

    glColor3f(255, 255, 255);

    glutSwapBuffers();
    // update_game();
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
    glutPassiveMotionFunc(mousecontroller);
    glutMouseFunc(mouseclickcontroller);
    // glutKeyboardFunc(keyboard_down);
    // glutKeyboardUpFunc(keyboard_up);
    init_lighting();
}

void drawTeapot(float x, float y) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(0.2f, 0.2f, 0.2f);
        glRotatef(0, 1, 0, angle);
        glutSolidTeapot(2);
        angle+=0.1;
    glPopMatrix();
}

void setup_game() {
    srand(time(NULL));
    bunny = (Data*)malloc(sizeof(Data));
    load_obj(bunny, "res/meshlabbunnyn.obj", 2483, 1256, 0);

    build_vbo(bunny);

    current_target.x = randomfloat() * 10 - 5;
    current_target.y = randomfloat() * 10 - 5;

    sky = SOIL_load_OGL_texture("res/skybox.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, sky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    grass = SOIL_load_OGL_texture("res/grass.jpeg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, grass);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    particle_systems = (psystem**) malloc(sizeof(psystem*) * MAX_PSYSTEMS);

    shader_program = load_shader("res/toon.frag", "res/toon.vert");
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

void mousecontroller(int x, int y) {
    mousex = x;
    mousey = y;
}

void mouseclickcontroller(int button, int state, int x, int y) {
    *(particle_systems + (psystems++)) = initpsystem(30, camx, camy, 0);
}

void updatecameraposition() {
    int centerx = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centery = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    float distance = dist((float)centerx, (float)mousex, (float)centery, (float)mousey);

        float deltax = (float) (mousex - centerx) / distance;
        float deltay = (float) (mousey - centery) / distance;
    
        camx += deltax * distance * 0.001;
        camy -= deltay * distance * 0.001;
}

float dist(float x1, float x2, float y1, float y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void init_lighting() {
   GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat shininess[] = {50.0};
   GLfloat position[] = {10.0f, 10.0f, 10.0f, 0.0f};
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}


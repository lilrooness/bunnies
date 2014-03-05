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
    if(started == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(0, 0, 10,
                  0, 0, 0,
                  0, 1, 0);
        bitmapString(320, 180, "Place mouse in the center of window !!", 38);
        bitmapString(320, 200, "You will have 30 seconds", 24);
        bitmapString(320, 240, "Click To Start !!", 17);

        glEnable(GL_LIGHTING);
        glUseProgram(shader_program);
            glPushMatrix();
                glTranslatef(-0.6f, -0.5f, 0.0f);
                glRotatef(angle, 0, 1, 0);
                // glScalef(0.5f, 0.5f, 0.5f);
                render_vbo(bunny);
            glPopMatrix();
        glUseProgram(0);
        glDisable(GL_LIGHTING);
        angle += 0.1f;

    } else if(timeLeft > 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
    
        gluLookAt(0, 0, 10,
                  camx, camy, 0,
                  // 0, 0, 0,m
                  0, 1, 0);
        skybox();
    
        glUseProgram(shader_program);
            glPushMatrix();
                glTranslatef(current_target.x, current_target.y, 0);
                render_vbo(bunny);
            glPopMatrix();
        glUseProgram(0);
    
        glUseProgram(trans_shader_program);
            glPushMatrix();
                glTranslatef(camx, camy, 0.0f);
                glScalef(0.5f, 0.5f, 0.5f);
                render_vbo(bomb);
            glPopMatrix();
        glUseProgram(0);
    
        char buffer[400];
        int len = 400;
        glGetInfoLogARB(shader_program, 400, &len, buffer);
        printf("%s\n", buffer);
    
        glColor3f(255, 0, 0);
        
        glDisable(GL_LIGHTING);
        int i;
        for(i=0; i<psystems; i++) {
            updateparticlesystem(*(particle_systems + i));
            rendersystem(*(particle_systems + (i)));
        }
        // glEnable(GL_LIGHTING);
    
        glColor3f(255, 255, 255);
    
        updatecameraposition();
        
        char string[10];
        char timedisp[10];

        sprintf(string, "Score: %d", score);
        sprintf(timedisp, "Time: %d", timeLeft);
        
        bitmapString(20, 20, string, 10);
        bitmapString(500, 20, timedisp, 10);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(0, 0, 10,
                  0, 0, 0,
                  // 0, 0, 0,m
                  0, 1, 0);

        char message[20];
        sprintf(message, "Your Score: %d", score);
        bitmapString(320, 240, "Times Up!", 9);
        bitmapString(320, 260, message, 20);

        glEnable(GL_LIGHTING);
        glUseProgram(shader_program);
            glPushMatrix();
                glTranslatef(-0.6f, -0.5f, 0.0f);
                glRotatef(angle, 0, 1, 0);
                // glScalef(0.5f, 0.5f, 0.5f);
                render_vbo(bunny);
            glPopMatrix();
        glUseProgram(0);
        glDisable(GL_LIGHTING);
        angle += 0.1f;
    }

    glutSwapBuffers();
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
    glutTimerFunc(1000 ,timerfunc, 0);
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

    bomb = (Data*)malloc(sizeof(Data));
    load_obj(bomb, "res/dinamite.obj", 1644, 851, 0);

    build_vbo(bunny);
    build_vbo(bomb);

    current_target.x = randomfloat() * 10 - 5;
    current_target.y = randomfloat() * 10 - 5;

    sky = SOIL_load_OGL_texture("res/skybox.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, sky);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    grass = SOIL_load_OGL_texture("res/fence.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    glBindTexture(GL_TEXTURE_2D, grass);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    particle_systems = (psystem**) malloc(sizeof(psystem*) * MAX_PSYSTEMS);

    shader_program = load_shader("res/toon.frag", "res/toon.vert");
    trans_shader_program = load_shader("res/trans.frag", "res/trans.vert");
    score = 0;
    timeLeft = 30;
    angle = 0;
    started = 0;
}

void mousecontroller(int x, int y) {
    mousex = x;
    mousey = y;
}

void mouseclickcontroller(int button, int state, int x, int y) {
    started = 1;
    *(particle_systems + (psystems++)) = initpsystem(30, camx, camy, 0, 100);

    if(sqrt(pow(camx - current_target.x, 2) + pow(camy - current_target.y, 2)) < 1.0f) {
        score ++;
        current_target.x = randomfloat() * 10 - 5;
        current_target.y = randomfloat() * 10 - 5;
    }
}

void updatecameraposition() {
    int centerx = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centery = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    float distance = dist((float)centerx, (float)mousex, (float)centery, (float)mousey);

    float deltax = (float) (mousex - centerx) / distance;
    float deltay = (float) (mousey - centery) / distance;

    float tempx = camx;
    float tempy = camy;

    camx += deltax * distance * 0.001;
    camy -= deltay * distance * 0.001;
    
    //check for NaNs (IEEE spec all comparisons involving nans evaluate to false)
    if(camx != camx || camy != camy) {
        camx = tempx;
        camy = tempy;
    }
}

float dist(float x1, float x2, float y1, float y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void init_lighting() {
   GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat shininess[] = {50.0};
   GLfloat position[] = {0.0f, 0.0f, 10.0f, 0.0f};
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}

void bitmapString(int x, int y, char *string, int len) {
    //Assume we are in MODEL_VIEW already
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluOrtho2D(0, viewport[2], viewport[3], 0);
    glDepthFunc(GL_ALWAYS);
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);

    int i;
    for (i = 0; i < len; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
        
    glDepthFunc(GL_LEQUAL);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();
}

void timerfunc(int value) {
    timeLeft --;
    //call again in 1 second (registering the callback only calls it once)
    glutTimerFunc(1000 ,timerfunc, 0);
}
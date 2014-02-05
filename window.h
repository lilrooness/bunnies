#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "particle.h"
#include "objloader.h"
#include "bmploader.h"

Data *bunny;
GLuint sky;
GLuint grass;

typedef struct {
	float x, y;
}target;

// float angle1 = 0;
float angle;
int mousex, mousey;
float camx, camy;
target current_target;

void reshape(int width, int height);
void render();
void setup_game();
void update_game();
void init_glut(int argc, char **argv, int window_width, int window_height, char* title);
void keyboard_down(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void drawGround();
void skybox();
void drawTeapot(float x, float y);
float randomfloat();
void mousecontroller(int x, int y);
void updatecameraposition();
float dist(float x1, float x2, float y1, float y2);

#endif
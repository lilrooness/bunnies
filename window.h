#ifndef WINDOW_H
#define WINDOW_H

#define MAX_PSYSTEMS 1000

#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include <math.h>
#include "particle.h"
#include "objloader.h"
#include "bmploader.h"
#include "particle.h"
#include "shader.h"

Data *bunny;
GLuint sky;
GLuint grass;
Data *bomb;

int psystems;
psystem **particle_systems;

typedef struct {
	float x, y;
}target;

int score;
int timeLeft;
int started;

// float angle1 = 0;
float angle;
int mousex, mousey;
float camx, camy;
target current_target;

GLuint shader_program;
GLuint trans_shader_program;

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
void mouseclickcontroller(int button, int state, int x, int y);
void init_lighting();
void print2DText(int x, int y, char *string, int len);
void timerfunc(int value);


#endif
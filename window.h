#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>
#include <math.h>
#include <SOIL/SOIL.h>
#include "objloader.h"
#include "bmploader.h"

Data *model;
GLuint stuff_texture;
// float angle1 = 0;
// float angle = 0;

void reshape(int width, int height);
void render();
void setup_game();
void update_game();
void init_glut(int argc, char **argv, int window_width, int window_height, char* title);
void keyboard_down(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void drawGround();

#endif
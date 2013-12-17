#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include "player.h"
#include "objloader.h"

typedef struct {
	char *map;
	int width;
	int height;
	int stride;
}Map;

Player *player;
char *map;
Data *model;
// float angle = 0;

void reshape(int width, int height);
void render();
void setup_game();
void update_game();
void init_glut(int argc, char **argv, int window_width, int window_height, char* title);
void keyboard_down(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

#endif
#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>

GLuint load_shader(const char *frag, const char *vert);
int line_count(const char *filename);
char* loadShaderText(const char* fileName);
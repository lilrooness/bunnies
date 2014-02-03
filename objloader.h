#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>

typedef struct {
	float *vertexlist;
	float *normallist;
	float *texcoords;
	unsigned int *indiceslist;
	unsigned int *normalindeces;
	int vertices;
	int faces;
	GLuint *vboid;
	GLuint *iboid;
}Data;

typedef struct {
	float x, y, z;
}Vertex;

int load_obj(Data *data ,const char *filename, int faces, int vertecies, int textured);//load obj file into data struct
int delete_obj(Data *data);//free memory for data struct
void build_vbo(Data *data);
void render_vbo(Data *data);
#endif
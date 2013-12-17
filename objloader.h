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
	int vertices;
	int faces;
	GLuint *vboid;
	GLuint *iboid;
}Data;

typedef struct {
	float x, y, z;
}Vertex;

// typedef struct {
// 	Vertex *vertexlist;
// 	Vertex *normallist;
// 	// Vertex *texcoords;
// 	unsigned int *indiceslist;
// 	int vertices;
// 	int faces;
// 	GLuint *vboid;
// 	GLuint *iboid;
// }Data;

int load_obj(Data *data ,const char *filename, int faces, int vertecies);//load obj file into data struct
int delete_obj(Data *data);//free memory for data struct

void build_vbo(Data *data);
#endif
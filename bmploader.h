#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#pragma pack(push, 1)

typedef struct {
	char type[2];
	unsigned int size;
	short reserved1;
	short reserved2;
	unsigned int offset;
}file_header;

typedef struct {
	file_header fileheader;
	unsigned int headersize;
	int width;
	int height;
	short planes;
	short bpp;//bits per pixel
	unsigned int compression;
	unsigned int bitmapsize;
	int horizontalres;
	int verticalres;
	unsigned int colours;//colours
	unsigned int impcolours;//important colours
}bmp_header;

#pragma pack(pop)

typedef struct {
	char *data;
	int horizontalres;
	int verticalres;
}bitmap;

GLuint loadBMP(char* filename);

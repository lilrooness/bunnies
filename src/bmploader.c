#include "bmploader.h"

#define FILE_OPEN_ERROR 1
#define FILE_READ_ERROR 2

GLuint loadBMP(char* filename) {

	GLuint texture;
	bitmap *bitmapdata;

	FILE *fp = fopen(filename, "rb");
	 
	if(fp == NULL) {
		return 1;
	}

	bmp_header *header = (bmp_header*) malloc(sizeof(bmp_header));
	bitmapdata = (bitmap*) malloc(sizeof(bitmap));

	fread(header, sizeof(bmp_header), 1, fp);

	bitmapdata->data = (char *) malloc(sizeof(char) * header->bitmapsize);
	if(bitmapdata->data == NULL) {
		return 2;
	}

	fseek(fp, header->fileheader.offset, SEEK_SET);
	fread(bitmapdata->data, sizeof(char), header->bitmapsize, fp);
	fclose(fp);

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, header->width, header->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmapdata->data);

	free(bitmapdata);
	free(header);

	return texture;
}
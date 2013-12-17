#include "objloader.h"


/**
* load data from object file into Data struct
*/
int load_obj(Data *data ,const char *filename, int faces, int vertecies) {
	data->vertices = vertecies;
	data->faces = faces;
	data->vertexlist = (float*)malloc(sizeof(float) * data->vertices*3);
	data->indiceslist = (int*)malloc(sizeof(int)*data->faces*3);

	FILE *fp = fopen("./res/bunny.obj", "r");
	float v1, v2, v3;//3 vertcies per line
	unsigned int f1, f2, f3;//3 faces per line
	char type;//line type (vertex, face, ...)
	int vertexarraycursor = 0;
	char *line = (char*)malloc(sizeof(char) * 300);//allocate maximum line size
	int indicescursor = 0;

	while(fgets(line, 128, fp) != NULL) {
		switch(line[0]) {
			case 'v': {
				sscanf(line, "%c %f %f %f", &type, &v1, &v2, &v3);
				data->vertexlist[vertexarraycursor++] = v1;
				data->vertexlist[vertexarraycursor++] = v2;
				data->vertexlist[vertexarraycursor++] = v3;
			}break;
			case 'f': {
				sscanf(line, "%c %u %u %u", &type, &f1, &f2, &f3);
				data->indiceslist[indicescursor++] = f1 - 1;
				data->indiceslist[indicescursor++] = f2 - 1;
				data->indiceslist[indicescursor++] = f3 - 1;
			}break;
		}
	}
	fclose(fp);
	return 0;//no error
}

int delete_obj(Data *data) {
	return 0;//no error
}

void build_vbo(Data *data) {
	data->vboid = malloc(sizeof(GLuint));
	data->iboid = malloc(sizeof(GLuint));
	glGenBuffers(1, data->vboid);
	glGenBuffers(1, data->iboid);
	
	glBindBuffer(GL_ARRAY_BUFFER, data->vboid);
	glBufferData(GL_ARRAY_BUFFER, data->vertices*3*sizeof(float), data->vertexlist, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->iboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->faces*3*sizeof(int), data->indiceslist, GL_STATIC_DRAW);
}
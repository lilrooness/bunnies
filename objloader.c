#include "objloader.h"


/**
* load data from object file into Data struct
*/
int load_obj(Data *data ,const char *filename, int faces, int vertecies, int textured) {
	data->vertices = vertecies;
	data->faces = faces;
	data->vertexlist = (float*)malloc(sizeof(float) * data->vertices*3);
	data->normallist = (float*)malloc(sizeof(float) * data->vertices*3);
	data->indiceslist = (unsigned int*)malloc(sizeof(unsigned int)*data->faces*3);
	data->normalindeces = (unsigned int*)malloc(sizeof(unsigned int)*data->faces*3);

	FILE *fp = fopen(filename, "r");
	float v1, v2, v3;//3 vertcies per line
	unsigned int f1, f2, f3, n1, n2, n3, t1, t2, t3;//3 faces per line
	char type;//line type (vertex, face, ...)
	int vertexarraycursor = 0;
	int normalarraycursor = 0;
	int indicescursor = 0;
	int normalindicescursor = 0;

	char *line = (char*)malloc(sizeof(char) * 300);//allocate maximum line size

	while(fgets(line, 128, fp) != NULL) {
		switch(line[0]) {
			case 'v': {
				if(line[1] == 'n') {
					sscanf(line, "%c%c %f %f %f", &type, &type, &v1, &v2, &v3);
					data->normallist[normalarraycursor++] = v1;
					data->normallist[normalarraycursor++] = v2;
					data->normallist[normalarraycursor++] = v3;
				} else if(line[1] == 't'){
					//TODO VERTEX TEXTURE
				} else {
					sscanf(line, "%c %f %f %f", &type, &v1, &v2, &v3);
					data->vertexlist[vertexarraycursor++] = v1;
					data->vertexlist[vertexarraycursor++] = v2;
					data->vertexlist[vertexarraycursor++] = v3;
				}
			}break;
			case 'f': {
				if(textured == 0) {
					sscanf(line, "%c %u//%u %u//%u %u//%u", &type, &f1, &n1, &f2, &n2, &f3, &n3);
					data->indiceslist[indicescursor++] = f1 - 1;
					data->indiceslist[indicescursor++] = f2 - 1;
					data->indiceslist[indicescursor++] = f3 - 1;

					data->normalindeces[normalindicescursor++] = n1 - 1;
					data->normalindeces[normalindicescursor++] = n2 - 1;
					data->normalindeces[normalindicescursor++] = n3 - 1;
				} else {
					sscanf(line, "%c %u/%u/%u %u/%u/%u %u/%u/%u", &type, &f1, &t1, &n1, &f2, &t2, &n2, &f3, &t3, &n3);
					data->indiceslist[indicescursor++] = f1 - 1;
					data->indiceslist[indicescursor++] = f2 - 1;
					data->indiceslist[indicescursor++] = f3 - 1;
					
					//TODO TEXTURE INDICIES
					data->normalindeces[normalindicescursor++] = n1 - 1;
					data->normalindeces[normalindicescursor++] = n2 - 1;
					data->normalindeces[normalindicescursor++] = n3 - 1;
				}
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
	
	glBindBuffer(GL_ARRAY_BUFFER, (GLuint*)data->vboid);
	glBufferData(GL_ARRAY_BUFFER, data->vertices*3*sizeof(float), data->vertexlist, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint*)data->iboid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->faces*3*sizeof(int), data->indiceslist, GL_STATIC_DRAW);
}

void render_vbo(Data *data) {
	glEnableClientState(GL_VERTEX_ARRAY);
    	glBindBuffer(GL_ARRAY_BUFFER, (GLuint*)data->vboid);
    	glVertexPointer(3, GL_FLOAT, 0, 0);

    glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint*)data->iboid);
    	glDrawElements(GL_TRIANGLES, data->faces*3, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_ELEMENT_ARRAY_BUFFER);
}


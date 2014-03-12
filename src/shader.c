#include "shader.h"

GLuint load_shader(const char *frag, const char *vert) {

	int vlines = 0;
	int flines = 0;

	char* fshader = NULL;
	fshader = loadShaderText(frag);
	const char* fSource = fshader;

	char* vshader = NULL;
	vshader = loadShaderText(vert);
	const char* vSource = vshader;

	GLuint shader_program = glCreateProgram();

	GLuint frag_program = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	
	glShaderSourceARB(frag_program, 1, &fSource, NULL);
	glCompileShaderARB(frag_program);

	int fstatus;
	glGetObjectParameterivARB(frag_program, GL_OBJECT_COMPILE_STATUS_ARB, &fstatus);

	if(fstatus) {
		printf("Fragment shader compile succesufull\n");
	} else {
		printf("Problem compiling fragment shader\n");
		char err_buff[512];
		glGetShaderInfoLog(frag_program, 512, NULL, err_buff);
		printf("%s\n", err_buff);
	}

	GLuint vert_program = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	
	glShaderSourceARB(vert_program, 1, &vSource, NULL);
	glCompileShaderARB(vert_program);

	int vstatus;
	glGetObjectParameterivARB(vert_program, GL_OBJECT_COMPILE_STATUS_ARB, &vstatus);

	if(vstatus) {
		printf("Vertex shader compile succesufull\n");
	} else {
		printf("Problem compiling vertex shader\n");
		char err_buff[512];
		glGetShaderInfoLog(vert_program, 512, NULL, err_buff);
		printf("%s\n", err_buff);
	}

	glAttachShader(shader_program, vert_program);
	glAttachShader(shader_program, frag_program);

	glLinkProgram(shader_program);

	GLint link_status;
	glGetObjectParameterivARB(shader_program, GL_OBJECT_LINK_STATUS_ARB, &link_status);

	if(!link_status) {
		char err_buff[512];
		glGetProgramInfoLog(shader_program, 512, NULL, err_buff);
		printf("Problem linking program\n");
		printf("%s\n", err_buff);
		exit(1);
	}else {
		printf("Link Successful");
	}

	return shader_program;
}

char* loadShaderText(const char* fileName) {
    FILE *fp;
	char *content = NULL;

	int count=0;
    fp = fopen(fileName, "r");

    if (fp != NULL) {

        fseek(fp, 0, SEEK_END);
        count = ftell(fp);
        rewind(fp);

        if (count > 0) {
            content = (char *)malloc(sizeof(char) * (count+1));
            count = fread(content,sizeof(char),count,fp);
            content[count] = '\0';
        }
        fclose(fp);
    }

	return content;
}

int line_count(const char *filename) {
	FILE *fp = fopen(filename, "r");
	int lines = 0;
	char ch[400];
	while (NULL != fgets(ch, 400, fp)) {
		++lines;
	}
	fclose(fp);
	printf("finished couting lines %d: %s\n", lines, filename);
	return lines+1;
} 
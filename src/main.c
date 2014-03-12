#include "window.h"

int main(int argc, char **argv) {
	// printf("This is a short demo");
	init_glut(argc, argv, 640, 480, "SMMSCR Demo");
	setup_game();
	glutMainLoop();
	return 0;
}


CC = gcc
CFLAGS = -framework OpenGL -framework GLUT -lSOIL

demo: player.o window.o main.o objloader.o bmploader.o
	$(CC) $(CFLAGS) -o bin/demo player.o window.o objloader.o main.o bmploader.o

window.o: window.h window.c
	$(CC) $(CFLAGS) -c window.c

player.o: player.h player.c
	$(CC) $(CFLAGS) -c player.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

objloader.o: objloader.c
	$(CC) $(CFLAGS) -c objloader.c

bmploader.o: bmploader.c
	$(CC) $(CFLAGS) -c bmploader.c

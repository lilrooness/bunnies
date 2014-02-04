CC = gcc
CFLAGS = -framework OpenGL -framework GLUT -lSOIL

demo: window.o main.o objloader.o
	$(CC) $(CFLAGS) -o bin/demo window.o objloader.o main.o

window.o: window.h window.c
	$(CC) $(CFLAGS) -c window.c

# player.o: player.h player.c
# 	$(CC) $(CFLAGS) -c player.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

objloader.o: objloader.c
	$(CC) $(CFLAGS) -c objloader.c

# bmploader.o: bmploader.c
# 	$(CC) $(CFLAGS) -c bmploader.c

CC = gcc
CFLAGS = -framework OpenGL -framework GLUT -lSOIL -Wall

demo: window.o main.o objloader.o particle.o shader.o
	$(CC) $(CFLAGS) -o bin/demo shader.o particle.o window.o objloader.o main.o;

window.o: window.h window.c
	$(CC) $(CFLAGS) -c window.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

objloader.o: objloader.c
	$(CC) $(CFLAGS) -c objloader.c

particle.o: particle.c
	$(CC) $(CFLAGS) -c particle.c

shader.o: shader.c
	$(CC) $(CFLAGS) -c shader.c

clean:
	rm *.o

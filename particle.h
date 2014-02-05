#include <math.h>

typedef struct {
	float xpos, ypos, zpos;
	float mass;
	float xvel, yvel, zvel;
	float xacc, yacc, zacc;
}particle;

typedef struct {
	particle *particles;
	int maxparticles;
	int currentparticles;
}psystem;

void updateparticlesystem(psystem *particlesystem);

void updateparticle(particle *p);

void applyforce(float x, float y, float z, particle *p);

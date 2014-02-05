#include "particle.h"

void updateparticlesystem(psystem *particlesystem) {
	int i;
	for(i = 0; i < particlesystem->currentparticles; i++) {
		updateparticle(particlesystem->particles+i);
	}
}

void updateparticle(particle *p) {
	p->xvel += p->xacc;
	p->yvel += p->yacc;
	p->zvel += p->zacc;

	p->xpos += p->xvel;
	p->ypos += p->yvel;
	p->zpos += p->zvel;

	p->xacc = 0.0f;
	p->yacc = 0.0f;
	p->zacc = 0.0f;

}

void applyforce(float x, float y, float z, particle *p) {
	p->xacc = x / p->mass;
	p->yacc = y / p->mass;
	p->zacc = y / p->mass;
}

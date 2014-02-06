#include "particle.h"

void updateparticlesystem(psystem *particlesystem) {
	int i;
	for(i = 0; i < particlesystem->currentparticles; i++) {
		updateparticle(particlesystem->particles+i);
	}
}

void updateparticle(particle *p) {

	//apply gravity
	applyforce(0.0f, -0.001f, 0.0f, p);

	p->xvel += p->xacc;
	p->yvel += p->yacc;
	p->zvel += p->zacc;

	p->xpos += p->xvel;
	p->ypos += p->yvel;
	p->zpos += p->zvel;

	p->xacc = 0.0f;
	p->yacc = 0.0f;
	p->zacc = 0.0f;

	if(p->lifetime < 0) {
		p->lifetime = randomfloat() * 100;

		p->xpos = 0;
		p->ypos = 0;
		p->zpos = 0;

		// p->xacc = 0.0f;
		// p->yacc = 0.0f;
		// p->zacc = 0.0f;

		p->xvel = 0.0f;
		p->yvel = 0.0f;
		p->zvel = 0.0f;

		applyRandomForce(p);
	} else {
		p->lifetime --;
	}
}

void applyforce(float x, float y, float z, particle *p) {
	p->xacc += x / p->mass;
	p->yacc += y / p->mass;
	p->zacc += y / p->mass;
}

psystem* initpsystem(int max, float x, float y, float z) {

	psystem *particlesystem = (psystem*) malloc(sizeof(psystem));
	particlesystem->particles = (particle*) malloc(sizeof(particle) * max);
	particlesystem->maxparticles = max;
	particlesystem->currentparticles = max;

	particlesystem->x = x;
	particlesystem->y = y;
	particlesystem->z = z;

	int i;
	for(i=0; i<particlesystem->currentparticles; i++) {
		(particlesystem->particles + i)->xpos = x;
		(particlesystem->particles + i)->ypos = y;
		(particlesystem->particles + i)->zpos = z;

		(particlesystem->particles + i)->xvel = 0.0f;
		(particlesystem->particles + i)->yvel = 0.0f;
		(particlesystem->particles + i)->zvel = 0.0f;

		(particlesystem->particles + i)->xacc = 0.0f;
		(particlesystem->particles + i)->yacc = 0.0f;
		(particlesystem->particles + i)->zacc = 0.0f;

		(particlesystem->particles + i)->mass = 1;
		(particlesystem->particles + i)->lifetime = randomfloat() * 100;

		applyRandomForce(particlesystem->particles + i);
	}

	return particlesystem;
}

void rendersystem(psystem *particlesystem) {
	glPushMatrix();
	glTranslatef(particlesystem->x, particlesystem->y, particlesystem->z);
	int i;
	for(i = 0; i < particlesystem->currentparticles; i++) {
		glPushMatrix();
			glTranslatef((particlesystem->particles + i)->xpos,
						 (particlesystem->particles + i)->ypos, 
						 (particlesystem->particles + i)->zpos);
			glBegin(GL_POINTS);
				glVertex3f(0, 0, 0);
			glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}

float randomfloat() {
    return (float)rand() / (float)RAND_MAX;
}

void applyRandomForce(particle *p) {
	applyforce((randomfloat() * 0.1) - 0.05,
				   (randomfloat() * 0.1) - 0.05, 
				   (randomfloat() * 0.1) - 0.05, 
				   p);
}

#ifndef PARTICLE_H
#define PARTICLE_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>

typedef struct {
	float xpos, ypos, zpos;
	float mass;
	float xvel, yvel, zvel;
	float xacc, yacc, zacc;
	float lifetime;
}particle;

typedef struct {
	float x, y, z;
	particle *particles;
	int maxparticles;
	int currentparticles;
	int lifetime;
}psystem;

void updateparticlesystem(psystem *particlesystem);

void updateparticle(particle *p, int deadSystem);

void applyforce(float x, float y, float z, particle *p);

psystem* initpsystem(int max, float x, float y, float z, int lifetime);

float randomfloat();

void rendersystem(psystem *particlesystem);

void applyRandomForce(particle *p);

#endif
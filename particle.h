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
}psystem;

void updateparticlesystem(psystem *particlesystem);

void updateparticle(particle *p);

void applyforce(float x, float y, float z, particle *p);

psystem* initpsystem(int max, float x, float y, float z);

float randomfloat();

void rendersystem(psystem *particlesystem);

void applyRandomForce(particle *p);

#endif
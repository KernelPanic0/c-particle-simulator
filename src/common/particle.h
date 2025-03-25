#pragma once // include guard
#include "raylib.h"
#include "common.h"

typedef struct {
    Particle systemParticlePool[MAX_PARTICLES];
    Vector2 position;
    ParticleType type;
} ParticleSystem;

extern unsigned int particleSystemsCount;
extern ParticleSystem particleSystems[MAX_PARTICLE_SYSTEMS];
extern Particle particlePool[MAX_PARTICLES];

void AddToParticleSystem(Vector2 position, ParticleType type);
void UpdateParticleSystem();
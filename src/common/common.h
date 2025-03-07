#pragma once // include guard
#include "raylib.h"

extern const int screenWidth;
extern const int screenHeight;
extern float gravity;
#define MAX_PARTICLES 100
#define MAX_PARTICLE_SYSTEMS 20

typedef enum ParticleType {
    PARTICLE_SPARKS,
    PARTICLE_FIRE,
    PARTICLE_SMOKE
} ParticleType;


typedef struct {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float alpha;
    float size;
    float rotation;
    enum ParticleType type;
    bool active;
} Particle;
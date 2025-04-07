#pragma once // include guard
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

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
    Color initialColor;
    Color finalColor;
    Color color;
    float alpha;
    Vector2 initialSize;
    Vector2 size;
    float rotation;
    enum ParticleType type;
    bool active;
} Particle;

typedef struct {
    Vector2 position;
    Vector2 size;
    float rotation;
    Color color;
} ParticleDrawParams;

void DrawFireParticle(ParticleDrawParams params);

float GetRandomFloat(float min, float max); // is this too much to ask for raylib :-( ....
const char* EnumAsPChr(ParticleType type);
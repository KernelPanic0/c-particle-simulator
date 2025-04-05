#include "common.h"

const int screenWidth = 800;
const int screenHeight = 450;
float gravity = 9.0f;

float GetRandomFloat(float min, float max) {
    // Generate a random integer between 0 and RAND_MAX
    int randInt = GetRandomValue(0, RAND_MAX);
    
    // Map the integer to the range [min, max]
    return min + (randInt / (float)RAND_MAX) * (max - min);
}

//dbg 
const char* EnumAsPChr(ParticleType type) {
    switch (type) {
        case PARTICLE_SPARKS: return "Sparks";
        case PARTICLE_FIRE: return "Fire";
        case PARTICLE_SMOKE: return "Smoke";
    }
}

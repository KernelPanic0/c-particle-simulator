#include "raylib.h"
#include "common/particle.h"
#include "common/common.h"
#include "stdlib.h"
#include <string.h> // memcpy

void InitialiseSparks(Vector2 pos);
void UpdateSparks();
void AddToParticleSystem(Vector2 position, ParticleType type);
void UpdateParticleSystem();
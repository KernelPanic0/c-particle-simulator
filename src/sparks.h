#pragma once
#include "raylib.h"
#include "common/common.h"
#include "common/particle.h"
#include <string.h> // memcpy

void InitSparks(Vector2 pos);
void InitPhysics(Particle* pParticle, ParticleSystem* pParticleSystem);
void ApplyPhysics(Particle* pParticle);
void UpdateSparks();
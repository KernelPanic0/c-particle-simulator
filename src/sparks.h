#pragma once
#include "raylib.h"
#include "common/common.h"
#include "common/particle.h"
#include <string.h> // memcpy

void InitSparks(Vector2 pos);
void InitSparksPhysics(Particle* pParticle, ParticleSystem* pParticleSystem);
void ApplySparksPhysics(Particle* pParticle);
void UpdateSparks();
void DrawSparks(Particle particle);
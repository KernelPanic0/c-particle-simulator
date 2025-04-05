#pragma once
#include "raylib.h"
#include "common/common.h"
#include "common/particle.h"
#include <string.h> // memcpy

void InitFire(Vector2 pos);
void InitFirePhysics(Particle* pParticle, ParticleSystem* pParticleSystem);
void ApplyFirePhysics(Particle* pParticle);
void UpdateFire();
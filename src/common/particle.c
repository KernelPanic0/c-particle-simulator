#include "raylib.h"
#include "particle.h"
#include "../sparks.h"
#include "../fire.h"
#include "stdio.h"

unsigned int particleSystemsCount = 0;
// For stationary particles
ParticleSystem particleSystems[MAX_PARTICLE_SYSTEMS];
// For following cursor around
Particle particlePool[MAX_PARTICLES] = {};

void AddToParticleSystem(Vector2 position, ParticleType type) {
    if (particleSystemsCount != MAX_PARTICLE_SYSTEMS) {
        ParticleSystem newParticleSystem;
        particlePool->type = type;
        memcpy(newParticleSystem.systemParticlePool, particlePool, sizeof(Particle) * MAX_PARTICLES); // replace newParticleSystem.particlePool with particlePool. Copies all bytes.
        newParticleSystem.position = position;
        newParticleSystem.type = type;
        newParticleSystem.systemParticlePool->active = true;
        
        memcpy(&particleSystems[particleSystemsCount], &newParticleSystem, sizeof(ParticleSystem));
        particleSystemsCount += 1;
    } else {
        puts("full");
    }
}

void InitParticleSystems() {
    for (int i = 0; i < MAX_PARTICLE_SYSTEMS; i++) {
        particleSystems[i].position = (Vector2){-1, -1};

    }
}

void UpdateParticleSystem() {
    for (int i = 0; i < particleSystemsCount; i++) {
        // if (i > 0 && i == particleSystemsCount) return; // might cause bug
        Particle* pParticlePool = particleSystems[i].systemParticlePool;
        for (int i2 = 0; i2 < MAX_PARTICLES; i2++)
        {
            if (!pParticlePool[i2].active)
            {
                pParticlePool[i2].active = true;
                // Reinstantiate physics application
                switch (pParticlePool[i2].type) {
                    case PARTICLE_SPARKS:
                        InitSparksPhysics(&pParticlePool[i2], &particleSystems[i]); // pass in as pointer 
                        break;
                    case PARTICLE_FIRE:
                        InitFirePhysics(&pParticlePool[i2], &particleSystems[i]);
                        break;
                }

                break; // break so that the pParticlePool[i2] gets physics applied to it
            }
        }
        float deltaTime = GetFrameTime(); // time between current and previous frame
        for (int i = 0; i < MAX_PARTICLES; i++)
        {           
                if (pParticlePool[i].active)
                {
                    // apply physics to particle
                    ApplySparksPhysics(&pParticlePool[i]);
                    pParticlePool[i].alpha -= 0.01f;
    
                    if (pParticlePool[i].alpha <= 0.0f) pParticlePool[i].active = false; 
            }
        }

        
        // Draw active particles
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (pParticlePool[i].active) DrawRectangleV(pParticlePool[i].position, (Vector2){ 3, 3 }, pParticlePool[i].color);
        }
    }
}
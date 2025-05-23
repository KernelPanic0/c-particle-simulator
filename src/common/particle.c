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
        Particle* pParticlePool = particleSystems[i].systemParticlePool;
        for (int i2 = 0; i2 < MAX_PARTICLES; i2++)
        {
            if (!pParticlePool[i2].active)
            {
                pParticlePool[i2].active = true;
                // Reinstantiate physics application
                switch (particleSystems[i].type) {
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
        for (int i2 = 0; i2 < MAX_PARTICLES; i2++)
        {           
            if (pParticlePool[i2].active)
            {
                if (pParticlePool[i2].alpha <= 0.0f) pParticlePool[i2].active = false; 
                // apply physics to particle
                switch (particleSystems[i].type) {
                    case PARTICLE_SPARKS:
                        ApplySparksPhysics(&pParticlePool[i2]); 
                        pParticlePool[i2].alpha -= 0.01f;
                        pParticlePool[i2].color.a = (pParticlePool[i2].alpha * 255); 
                        DrawSparks(pParticlePool[i2]);
                        break;
                    case PARTICLE_FIRE:
                        ApplyFirePhysics(&pParticlePool[i2]);
                        DrawFire(pParticlePool[i2]);
                        break;
                }
                
            }
        }
    }
}


#include "raylib.h"
#include "particle.h"
#include "../sparks.h"

unsigned int particleSystemsCount = 0;
ParticleSystem particleSystems[MAX_PARTICLE_SYSTEMS];
Particle particlePool[MAX_PARTICLES] = {};

void AddToParticleSystem(Vector2 position, ParticleType type) {
    if (particleSystemsCount != MAX_PARTICLE_SYSTEMS) {
        ParticleSystem newParticleSystem;
        memcpy(newParticleSystem.systemParticlePool, particlePool, sizeof(Particle) * MAX_PARTICLES); // replace newParticleSystem.particlePool with particlePool.
        newParticleSystem.position = position;
        newParticleSystem.type = type;
    
        memcpy(&particleSystems[particleSystemsCount], &newParticleSystem, sizeof(ParticleSystem));
        particleSystemsCount += 1;
    }
}

void UpdateParticleSystem() {
    for (int i = 0; i < particleSystemsCount; i++) {
        Particle* pParticlePool = particleSystems[i].systemParticlePool;
        for (int i2 = 0; i2 < MAX_PARTICLES; i2++)
        {
            if (!pParticlePool[i2].active)
            {
                // apply physics to particle
                switch (pParticlePool[i2].type) {
                    case PARTICLE_SPARKS: 
                        InitPhysics(&pParticlePool[i2], &particleSystems[i]); // pass in as pointer 
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
                    ApplyPhysics(&pParticlePool[i]);
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
#include "sparks.h"
#include "stdio.h"

typedef struct {
    Particle systemParticlePool[MAX_PARTICLES];
    Vector2 position;
    ParticleType type;
} ParticleSystem;

unsigned int particleSystemsCount = 0;
ParticleSystem particleSystems[MAX_PARTICLE_SYSTEMS];
Particle particlePool[MAX_PARTICLES] = {};

void InitialiseSparks(Vector2 pos) {
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particlePool[i].position = pos;
        particlePool[i].velocity = (Vector2){ GetRandomValue(-2, 2), GetRandomValue(-13, 8)};
        particlePool[i].color = (Color){ 252, 157, 3, 255 };
        particlePool[i].alpha = 1.0f;
        particlePool[i].size = (float)GetRandomValue(1, 5)/60.0f;
        particlePool[i].rotation = (float)GetRandomValue(0, 360);
        particlePool[i].active = false;
    }
    // Init ParticleSystems
    for (int i = 0; i < MAX_PARTICLE_SYSTEMS; i++) {
        particleSystems[i].position = (Vector2){-1, -1};
    }
}

void AddToParticleSystem(Vector2 position, ParticleType type) {
    if (particleSystemsCount != MAX_PARTICLE_SYSTEMS) {
        ParticleSystem newParticleSystem;
        memcpy(newParticleSystem.systemParticlePool, particlePool, sizeof(Particle) * MAX_PARTICLES); // replace newParticleSystem.particlePool with particlePool. This is probably somehow unsafe... but i dont care
        newParticleSystem.position = position;
        newParticleSystem.type = type;
    
        particleSystems[particleSystemsCount] = newParticleSystem;
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
                pParticlePool[i2].active = true;
                pParticlePool[i2].velocity = (Vector2){GetRandomValue(-2, 2), GetRandomValue(-13, 8)};
                pParticlePool[i2].alpha = 1.0f;
                pParticlePool[i2].position = particleSystems[i].position;
                break; // break so that the pParticlePool[i] gets physics applied to it
            }
        }

        float deltaTime = GetFrameTime(); // time between current and previous frame
        for (int i = 0; i < MAX_PARTICLES; i++)
        {           
                if (pParticlePool[i].active)
                {
                    if (pParticlePool[i].position.y < screenHeight - 4) {
                        pParticlePool[i].position.y += pParticlePool[i].velocity.y;
                        pParticlePool[i].position.x += pParticlePool[i].velocity.x;
                        pParticlePool[i].velocity.y += gravity * deltaTime;
                        pParticlePool[i].position.y += gravity/2;  
                    }
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

void UpdateSparks() {
    // reenable all inactive particles
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particlePool[i].active)
        {
            particlePool[i].active = true;
            particlePool[i].velocity = (Vector2){GetRandomValue(-2, 2), GetRandomValue(-13, 8)};
            particlePool[i].alpha = 1.0f;
            particlePool[i].position = GetMousePosition();
            break; // break so that the particlePool[i] gets physics applied to it
        }
    }

    float deltaTime = GetFrameTime(); // time between current and previous frame
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particlePool[i].active)
        {
            if (particlePool[i].position.y < screenHeight - 4) {
                particlePool[i].position.y += particlePool[i].velocity.y;
                particlePool[i].position.x += particlePool[i].velocity.x;
                particlePool[i].velocity.y += gravity * deltaTime;
                particlePool[i].position.y += gravity/2;  
            }
            particlePool[i].alpha -= 0.01f;

            if (particlePool[i].alpha <= 0.0f) particlePool[i].active = false; 
        }
    }

    
    // Draw active particles
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particlePool[i].active) DrawRectangleV(particlePool[i].position, (Vector2){ 3, 3 }, particlePool[i].color);
    }
}
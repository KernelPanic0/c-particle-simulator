#include "sparks.h"
#include "stdio.h"
#include "common/particle.h"

void InitFire(Vector2 pos) {
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particlePool[i].position = pos;
        particlePool[i].velocity = (Vector2){GetRandomValue(-1, 1), GetRandomValue(1, 2)};
        particlePool[i].color = (Color){ 252, 78, 3, 255 };
        particlePool[i].alpha = 1.0f;
        particlePool[i].size = (float)GetRandomValue(1, 5)/10.0f;
        particlePool[i].rotation = (float)GetRandomValue(-45, 45);
        particlePool[i].active = false;
        particlePool[i].type = PARTICLE_FIRE; // needs to be here because by default .type is set to 0 which is PARTICLE_SPARKS as its the first in the enum
    }
}

void InitFirePhysics(Particle* pParticle, ParticleSystem* pParticleSystem) {
    pParticle->active = true;
    pParticle->velocity = (Vector2){GetRandomFloat(-1, 1), GetRandomFloat(1, 2)};
    pParticle->size = (float)GetRandomValue(1, 5)/10.0f;
    pParticle->rotation = (float)GetRandomValue(-45, 45);
    pParticle->alpha = 1.0f;
    pParticle->position = pParticleSystem->position;
}

void ApplyFirePhysics(Particle* pParticle) {
    pParticle->position.y -= pParticle->velocity.y;
    pParticle->position.x += pParticle->velocity.x;
    pParticle->rotation += 2.0f;
}

void UpdateFire() {
    // reenable all inactive particles
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particlePool[i].active)
        {
            particlePool[i].active = true;
            particlePool[i].velocity = (Vector2){GetRandomFloat(-1, 1), GetRandomFloat(1, 2)};
            particlePool[i].alpha = 1.0f;
            particlePool[i].rotation = 1.0f;
            particlePool[i].position = GetMousePosition();
            break; // break so that the particlePool[i] gets physics applied to it
        }
    }

    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particlePool[i].active)
        {
            particlePool[i].position.y -= particlePool[i].velocity.y;
            particlePool[i].position.x += particlePool[i].velocity.x;
            particlePool[i].rotation += 20.0f;
            particlePool[i].alpha -= 0.01f;

            if (particlePool[i].alpha <= 0.0f) particlePool[i].active = false; 
        }
    }

    
    // Draw active particles
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particlePool[i].active) DrawRectangleV(particlePool[i].position, (Vector2){ 13, 13 }, particlePool[i].color);
    }
}
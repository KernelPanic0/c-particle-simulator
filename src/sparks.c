#include "sparks.h"
#include "stdio.h"
#include "common/particle.h"

void InitSparks(Vector2 pos) {
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particlePool[i].position = pos;
        particlePool[i].velocity = (Vector2){ GetRandomFloat(-2, 2), GetRandomFloat(-13, 8)};
        particlePool[i].color = (Color){ 252, 157, 3, 255 };
        particlePool[i].alpha = 1.0f;
        particlePool[i].initialSize = (Vector2){ 3, 3 };
        particlePool[i].size = particlePool[i].initialSize;
        particlePool[i].rotation = (float)GetRandomValue(0, 360);
        particlePool[i].active = false;
    }
}

void InitSparksPhysics(Particle* pParticle, ParticleSystem* pParticleSystem) {
    pParticle->velocity = (Vector2){GetRandomValue(-2, 2), GetRandomValue(-13, 8)};
    pParticle->alpha = 1.0f;
    pParticle->position = pParticleSystem->position;

}

void ApplySparksPhysics(Particle* pParticle) {    
    if (pParticle->position.y < screenHeight - 4) { // use -> to deref and access a member of Particle
        float deltaTime = GetFrameTime(); // time between current and previous frame
        pParticle->position.y += pParticle->velocity.y;
        pParticle->position.x += pParticle->velocity.x;
        pParticle->velocity.y += gravity * deltaTime;
        pParticle->position.y += gravity/2;
    }
}

void DrawSparks(Particle particle) {
    DrawRectangleV(particle.position, particle.size, particle.color);
}

void UpdateSparks() {
    // reenable all inactive particles
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particlePool[i].active)
        {
            particlePool[i].active = true;
            particlePool[i].velocity = (Vector2){GetRandomFloat(-2, 2), GetRandomFloat(-13, 8)};
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
            ApplySparksPhysics(&particlePool[i]);
            particlePool[i].alpha -= 0.01f;
            particlePool[i].color.a = (particlePool[i].alpha * 255); 

            if (particlePool[i].alpha <= 0.0f) particlePool[i].active = false; 
        }
        if (particlePool[i].active) DrawRectangleV(particlePool[i].position, particlePool[i].size, particlePool[i].color);
    }
}
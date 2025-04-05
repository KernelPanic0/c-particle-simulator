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
        particlePool[i].size = (float)GetRandomValue(1, 5)/60.0f;
        particlePool[i].rotation = (float)GetRandomValue(0, 360);
        particlePool[i].active = false;
    }
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
        // if (particlePool[2].active) {
        //     puts("true");
        // } else {
        //     puts("false");
        // }
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
        if (particlePool[i].active) DrawRectangleV(particlePool[i].position, (Vector2){ 3, 3 }, particlePool[i].color); // set alpha
    }
}

void InitSparksPhysics(Particle* pParticle, ParticleSystem* pParticleSystem) {
    pParticle->active = true;
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
        pParticle->active = true;
    }
}
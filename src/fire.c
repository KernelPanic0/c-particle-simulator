#include "sparks.h"
#include "stdio.h"
#include "common/particle.h"

void InitFire(Vector2 pos) {
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particlePool[i].position = pos;
        particlePool[i].velocity = (Vector2){GetRandomValue(-1, 1), GetRandomValue(1, 2)};
        // particlePool[i].color = (Color){ 252, 78, 3, 255 };
        particlePool[i].finalColor = (Color){240, 213, 7, 255};  // Start: Orange-yellow
        particlePool[i].initialColor = (Color){255, 50, 0, 0};        // End: Red (fading to transparent)
        particlePool[i].color = particlePool[i].initialColor;
        particlePool[i].alpha = 1.0f;
        particlePool[i].initialSize = (Vector2){ 13, 13 };
        particlePool[i].size = particlePool[i].initialSize;
        particlePool[i].rotation = (float)GetRandomValue(-45, 45);
        particlePool[i].active = false;
        particlePool[i].type = PARTICLE_FIRE; // needs to be here because by default .type is set to 0 which is PARTICLE_SPARKS as its the first in the enum
    }
}

void InitFirePhysics(Particle* pParticle, ParticleSystem* pParticleSystem) {
    pParticle->active = true;
    pParticle->velocity = (Vector2){GetRandomFloat(-1, 1), GetRandomFloat(1, 2)};
    pParticle->size = (Vector2){ 13, 13 };
    pParticle->rotation = (float)GetRandomValue(-45, 45);
    pParticle->alpha = 1.0f;
    pParticle->position = pParticleSystem->position;
}

void ApplyFirePhysics(Particle* pParticle) {
    pParticle->position.y -= pParticle->velocity.y;
    pParticle->position.x += pParticle->velocity.x;
    pParticle->rotation += 5.0f;

    pParticle->alpha -= 0.01f;
    // pParticle->color.a = (pParticle->alpha * 255); 
    pParticle->size.x = (pParticle->alpha * pParticle->initialSize.x);
    pParticle->size.y = (pParticle->alpha * pParticle->initialSize.y);

    // lerp between initialColor and finalColor
    pParticle->color.r = pParticle->initialColor.r + (pParticle->finalColor.r - pParticle->initialColor.r) * (1.0f - pParticle->alpha);
    pParticle->color.g = pParticle->initialColor.g + (pParticle->finalColor.g - pParticle->initialColor.g) * (1.0f - pParticle->alpha);
    pParticle->color.b = pParticle->initialColor.b + (pParticle->finalColor.b - pParticle->initialColor.b) * (1.0f - pParticle->alpha);

    // apply alpha to interpolated colour
    pParticle->color.a = (pParticle->alpha * 255);
}

void DrawFire(Particle particle) {
    Rectangle rect = {
        .x = particle.position.x,
        .y = particle.position.y,
        .width = particle.size.x,
        .height = particle.size.y
    };

    Vector2 origin = { particle.size.x / 2, particle.size.y / 2 };

    DrawRectanglePro(rect, origin, particle.rotation, particle.color);

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
            particlePool[i].size = (Vector2){ 13, 13 };
            particlePool[i].finalColor = (Color){240, 213, 7, 255};  // Start: Orange-yellow
            particlePool[i].initialColor = (Color){255, 50, 0, 0};        // End: Red (fading to transparent)
            particlePool[i].color = particlePool[i].initialColor;
            particlePool[i].rotation = 1.0f;
            particlePool[i].position = GetMousePosition();
            break; // break so that the particlePool[i] gets physics applied to it
        }
    }

    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particlePool[i].active)
        {
            ApplyFirePhysics(&particlePool[i]);

            if (particlePool[i].alpha <= 0.0f) particlePool[i].active = false; 

            // draw
            DrawFire(particlePool[i]);
        }
    }
}
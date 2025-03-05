#include "sparks.h"
#include "common/particle.h"
#include "common/common.h"

Particle particlePool[MAX_PARTICLES] = {};
void initialiseSparks() {
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particlePool[i].position = (Vector2){ 0, 0 };
        particlePool[i].velocity = (Vector2){ GetRandomValue(-2, 2), GetRandomValue(-13, 8)};
        particlePool[i].color = (Color){ 252, 157, 3, 255 };
        particlePool[i].alpha = 1.0f;
        particlePool[i].size = (float)GetRandomValue(1, 5)/60.0f;
        particlePool[i].rotation = (float)GetRandomValue(0, 360);
        particlePool[i].active = false;
    }
}

void updateSparks() {
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!particlePool[i].active)
        {
            particlePool[i].active = true;
            particlePool[i].velocity = (Vector2){GetRandomValue(-2, 2), GetRandomValue(-13, 8)};
            particlePool[i].alpha = 1.0f;
            particlePool[i].position = GetMousePosition();
            i = MAX_PARTICLES;
        }
    }

    float deltaTime = GetFrameTime();
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

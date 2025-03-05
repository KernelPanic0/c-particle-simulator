#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

#include "sparks.h"
#include "common/common.h"

// Particle structure with basic data
enum ParticleType {
    PARTICLE_SPARKS,
    PARTICLE_FIRE
};

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float alpha;
    float size;
    float rotation;
    enum ParticleType type;
    bool active;
} Particle;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    

    InitWindow(screenWidth, screenHeight, "raylib particle system simulator e");


    int blending = BLEND_ALPHA;

    SetTargetFPS(200);
    // main update loop
    while (!WindowShouldClose())    // detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        initialiseSparks();
        // Activate one particle every frame and Update active particles
        // NOTE: Particles initial position should be mouse position when activated
        // NOTE: Particles fall down with gravity and rotation... and disappear after 2 seconds (alpha = 0)
        // NOTE: When a particle disappears, active = false and it can be reused.

        if (IsKeyPressed(KEY_SPACE))
        {
            if (blending == BLEND_ALPHA) blending = BLEND_ADDITIVE;
            else blending = BLEND_ALPHA;
            
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginBlendMode(blending);
            
            updateSparks();

            EndBlendMode();

            DrawText("PRESS SPACE to CHANGE BLENDING MODE", 180, 20, 20, BLACK);

            if (blending == BLEND_ALPHA) DrawText("ALPHA BLENDING", 290, screenHeight - 40, 20, BLACK);
            else DrawText("ADDITIVE BLENDING", 280, screenHeight - 40, 20, RAYWHITE);

            // char buffer[50];  // Create a buffer to store the formatted text
            // sprintf(buffer, "%.2f", deltaTime);

            // DrawText(buffer, 300, screenHeight-50, 10, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // UnloadTexture(smoke);

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
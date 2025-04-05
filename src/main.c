#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

#include "sparks.h"
#include "fire.h"
#include "common/particle.h"
#include "common/common.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    

    InitWindow(screenWidth, screenHeight, "raylib particle system simulator");

    int blending = BLEND_ADDITIVE;

    SetTargetFPS(200);
    InitParticleSystems();
    // InitFire((Vector2){ 0, 0 });
    InitSparks((Vector2){ 0, 0 });
    // main update loop
    while (!WindowShouldClose())    // detect window close button or ESC key
    {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            AddToParticleSystem(GetMousePosition(), PARTICLE_SPARKS);
        }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground((Color){16, 19, 23, 1});

            BeginBlendMode(blending);
            


            // For sparks that follow your cursor
            UpdateSparks();
            // UpdateFire();
            // For sparks that have been placed down into a particle system
            UpdateParticleSystem();

            EndBlendMode();

            DrawText("Particle System Simulator", 180, 20, 20, RAYWHITE);

            DrawText("Additive Blending Enabled", 280, screenHeight - 40, 20, RAYWHITE);

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
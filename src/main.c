#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

#include "sparks.h"
#include "common/common.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    

    InitWindow(screenWidth, screenHeight, "raylib particle system simulator e");


    int blending = BLEND_ADDITIVE;

    SetTargetFPS(200);
    // main update loop
    InitialiseSparks((Vector2){ 0, 0 });
    while (!WindowShouldClose())    // detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Activate one particle every frame and Update active particles
        // NOTE: Particles initial position should be mouse position when activated
        // NOTE: Particles fall down with gravity and rotation... and disappear after 2 seconds (alpha = 0)
        // NOTE: When a particle disappears, active = false and it can be reused.

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            AddToParticleSystem(GetMousePosition(), PARTICLE_SPARKS);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);

            BeginBlendMode(blending);
            
            UpdateSparks();

            UpdateParticleSystem();

            EndBlendMode();

            DrawText("Particle System Simulator", 180, 20, 20, BLACK);

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
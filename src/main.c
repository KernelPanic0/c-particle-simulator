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

    bool sparksEnabled = true;

    SetTargetFPS(200);
    InitParticleSystems();
    // InitFire((Vector2){ 0, 0 });
    InitSparks((Vector2){ 0, 0 });
    // main update loop


    while (!WindowShouldClose())    // detect window close button or ESC key
    {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (sparksEnabled) {
                AddToParticleSystem(GetMousePosition(), PARTICLE_SPARKS);
            } else {
                AddToParticleSystem(GetMousePosition(), PARTICLE_FIRE);

            }
        }

        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
        {
            sparksEnabled = !sparksEnabled;
            if (sparksEnabled) {
                InitSparks((Vector2){ 0, 0 });
            } else {
                InitFire((Vector2){ 0, 0 });
            }
        }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground((Color){16, 19, 23, 1});

            BeginBlendMode(BLEND_ADDITIVE);
            


            // For sparks that follow your cursor
            if (sparksEnabled) {
                UpdateSparks();
            } else {
                UpdateFire();
            }
            // For sparks that have been placed down into a particle system
            UpdateParticleSystem();

            EndBlendMode();

            DrawText("Particle System Simulator", 180, 20, 20, RAYWHITE);

            if (sparksEnabled) {
                DrawText("Sparks", screenWidth/2, screenHeight - 40, 20, RAYWHITE);
            } else {
                DrawText("Fire", screenWidth/2, screenHeight - 40, 20, RAYWHITE);
            }

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
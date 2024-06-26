#include "raylib.h"
#include "rcamera.h"
#include "rlights.h"

Camera camera = { 0 };
int cameraMode = CAMERA_FIRST_PERSON;

void InitGame()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    camera.position = (Vector3){ 0.0f, 2.0f, 4.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    cameraMode = CAMERA_FIRST_PERSON;

    // Define the camera to look into our 3d world (position, target, up vector)
    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
}

int main ()
{
    InitGame();

    Vector3 positions[10];
    for (int i = 0; i < 10; i++)
    {
        positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), 0.0f, (float)GetRandomValue(-15, 15) };
    }

        // Main game loop
        while (!WindowShouldClose()) // Detect window close button or ESC key
        {

            // Update camera computes movement internally depending on the camera mode
            // Some default standard keyboard/mouse inputs are hardcoded to simplify use
            // For advance camera controls, it's reecommended to compute camera movement manually
            // UpdateCamera(&camera, cameraMode);                  // Update camera
            // UpdateCameraPro(&camear, )

            // Camera PRO usage example (EXPERIMENTAL)
            // This new camera function allows custom movement/rotation values to be directly provided
            // as input parameters, with this approach, rcamera module is internally independent of raylib inputs
            UpdateCameraPro(&camera,
                            (Vector3){
                                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) * 0.1f - // Move forward-backward
                                    (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * 0.1f,
                                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * 0.1f - // Move right-left
                                    (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * 0.1f,
                                0.0f // Move up-down
                            },
                            (Vector3){
                                GetMouseDelta().x * 0.1f, // Rotation: yaw
                                GetMouseDelta().y * 0.1f, // Rotation: pitch
                                0.0f					  // Rotation: roll
                            },
                            GetMouseWheelMove() * 2.0f); // Move to target (zoom)
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
                DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
                DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
                DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

                // Draw randomly placed cubes
                for (int i = 0; i < 10; i++) 
                {
                    DrawCube(positions[i], 1.0f, 20.0f, 1.0f, RED);
                }

                    EndMode3D();

                // Draw info boxes
                DrawRectangle(5, 5, 330, 100, Fade(SKYBLUE, 0.5f));
                DrawRectangleLines(5, 5, 330, 100, BLUE);

                DrawText("Camera controls:", 15, 15, 10, BLACK);
                DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 10, BLACK);
                DrawText("- Look around: arrow keys or mouse", 15, 45, 10, BLACK);

                DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
                DrawRectangleLines(600, 5, 195, 100, BLUE);

                DrawText("Camera status:", 610, 15, 10, BLACK);
                DrawText(TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" : (cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON"
                                                                                     : (cameraMode == CAMERA_THIRD_PERSON)   ? "THIRD_PERSON"
                                                                                     : (cameraMode == CAMERA_ORBITAL)        ? "ORBITAL"
                                                                                                                             : "CUSTOM"),
                         610, 30, 10, BLACK);
                DrawText(TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" : (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC"
                                                                                                                                                               : "CUSTOM"),
                         610, 45, 10, BLACK);
                DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
                DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 75, 10, BLACK);
                DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);

                EndDrawing();
                //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
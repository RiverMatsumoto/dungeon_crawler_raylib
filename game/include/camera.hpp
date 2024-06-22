#include "raylib.h"
#

#ifndef CAMERA_HPP
#define CAMERA_HPP

class CamControls
{
public:
    CamControls() 
    {
        // Define the camera to look into our 3d world
        camera = { 0 };
        camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
    }




private:
    Camera camera;
}; // Camera

#endif // CAMERA_HPP
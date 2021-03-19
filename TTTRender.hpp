#pragma once
#include "TTTBoard.hpp"

class Window
{
public:
    const char* windowName;
    Camera2D camera;
    float speedOf_camera = 50;

    // Size information
    int screenHeight;
    int screenWidth;

    // Timing information
    int targetFPS;

    Window();
    Window(const char* _windowName, Camera2D _camera, float _speedOf_camera, int _screenHeight, int _screenWidth, int _targetFPS);
    void InitializeWindow();
    //void UpdateRenderFrame(Board board);
};
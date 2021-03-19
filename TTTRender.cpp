#include "TTTRender.hpp"
#include "TTTBoard.hpp"

Window::Window()
{
    windowName = (char*)"Tic Tac Toe 5 x 5";
    speedOf_camera = 50.0f;
    screenHeight = 750;
    screenWidth = 1500;
    targetFPS = 25;

    camera = { 0 };
    camera.offset = Vector2{ (float)screenWidth / 2.0f , (float)screenHeight / 2.0f };
    camera.zoom = 1.0f;
}

Window::Window(const char* _windowName, Camera2D _camera, float _speedOf_camera, int _screenHeight, int _screenWidth, int _targetFPS)
{
    windowName = _windowName;
    camera = _camera;
    speedOf_camera = _speedOf_camera;
    screenHeight = _screenHeight;
    screenWidth = _screenWidth;
    targetFPS = _targetFPS;
}

void Window::InitializeWindow()
{
    InitWindow(screenWidth, screenHeight, windowName);
    SetTargetFPS(targetFPS);
}

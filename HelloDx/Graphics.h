#pragma once
#include <Windows.h>

const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
class Render;
class Graphics
{
public:
    Graphics();
    ~Graphics();

    bool Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen);
    void Shutdown();
    bool Frame();
private:
    Render *m_render = nullptr;
};

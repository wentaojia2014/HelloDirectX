#pragma once
#include <Windows.h>
namespace TaoD3D
{
class D3D;
class Model;
class ColorShader;
class Camera;
class Graphics
{
public:
    Graphics();
    ~Graphics();

    bool Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen);
    void Shutdown();
    bool Frame();

private:
    D3D *m_d3d = nullptr;
    Model *m_model = nullptr;
    ColorShader *m_shader = nullptr;
    Camera *m_camera = nullptr;
};
} // namespace TaoD3D

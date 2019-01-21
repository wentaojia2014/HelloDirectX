#pragma once
#include <Windows.h>
namespace TaoD3D
{
class D3D;
class Model;
class Shader;
class Camera;
class Light;
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
    Shader *m_shader = nullptr;
    Camera *m_camera = nullptr;
    Light *m_light = nullptr;
};
} // namespace TaoD3D

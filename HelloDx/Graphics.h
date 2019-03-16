#pragma once
#include <Windows.h>
#include "Interface/IGraphics.h"
namespace Tao3D
{
class D3D;
class Model;
class Shader;
class Camera;
class Light;
class Graphics : public IGraphics
{
public:
    Graphics();
    ~Graphics();

    bool Init(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen) override;
    void Uninit() override;
    bool Frame();

private:
    D3D *m_d3d = nullptr;
    Model *m_model = nullptr;
    Shader *m_shader = nullptr;
    Camera *m_camera = nullptr;
    Light *m_light = nullptr;
};
} // namespace Tao3D

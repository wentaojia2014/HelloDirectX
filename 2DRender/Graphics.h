#pragma once

#include "Interface/IGraphics.h"

#include <memory>

namespace Tao3D
{
class D3D;
class Model;
class Shader;
class Camera;
class Light;
class Bitmap;
class Graphics : public IGraphics
{
public:
    Graphics();
    ~Graphics();

    bool Init(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen) override;
    void Uninit() override;
    bool Frame();

private:
    std::unique_ptr<D3D> m_d3d = nullptr;
    std::unique_ptr<Model> m_model = nullptr;
    std::unique_ptr<Shader> m_shader = nullptr;
    std::unique_ptr<Camera> m_camera = nullptr;
    std::unique_ptr<Light> m_light = nullptr;
    std::unique_ptr<Bitmap> m_bitmap = nullptr;
};
} // namespace Tao3D

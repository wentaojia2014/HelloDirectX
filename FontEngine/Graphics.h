#pragma once

#include "Interface/IGraphics.h"

#include <memory>

namespace Tao3D
{
class D3D;
class Camera;
class Text;
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
    std::unique_ptr<Camera> m_camera = nullptr;
    std::unique_ptr<Text> m_text = nullptr;
};
} // namespace Tao3D

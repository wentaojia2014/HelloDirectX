#pragma once
#include "IRender.h"
#include <DirectXTK/SpriteFont.h>
#include <DirectXTK/SimpleMath.h>
#include <memory>
namespace Tao3D
{
class TextRender : public IRender
{
public:
    TextRender();
    ~TextRender();
    void init(int width, int height) override;
    void update() override;
    bool render() override;

private:
    std::unique_ptr<DirectX::SpriteFont> m_font = nullptr;
    DirectX::SimpleMath::Vector2 m_fontPos;
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch = nullptr;
    DirectX::SimpleMath::Vector2 m_mousePos;
};
} // namespace Tao3D

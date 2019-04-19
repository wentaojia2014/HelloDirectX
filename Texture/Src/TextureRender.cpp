#include "TextureRender.h"

#include "Application.h"
#include "Common.h"

#define USE_DDS

#ifdef USE_DDS
#include <DirectXTK/DDSTextureLoader.h>
#else
#include <DirectXTK/WICTextureLoader.h>
#endif

#include <algorithm>

namespace Tao3D
{
TextureRender::TextureRender() {}

TextureRender::~TextureRender() {}
void TextureRender::init(int width, int height)
{
    ThrowIfFailed(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED), "CoInitializeEx");
    m_spriteBatch = std::make_unique<SpriteBatch>(gContext);
    m_commanStates = std::make_unique<CommonStates>(gDevice);

    ComPtr<ID3D11Resource> resource;
#ifdef USE_DDS
    ThrowIfFailed(CreateDDSTextureFromFile(gDevice, L"cat.DDS", resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile");
#else
    ThrowIfFailed(CreateWICTextureFromFile(gDevice, L"cat.png", resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile");
#endif
    ComPtr<ID3D11Texture2D> cat;
    ThrowIfFailed(resource.As(&cat), "As");

    CD3D11_TEXTURE2D_DESC catDesc;
    cat->GetDesc(&catDesc);
    m_origin.x = static_cast<float>(catDesc.Width) / 2;
    m_origin.y = static_cast<float>(catDesc.Height) / 2;

    m_screenPos.x = static_cast<float>(width) / 2;
    m_screenPos.y = static_cast<float>(height) / 2;
    m_point = std::chrono::high_resolution_clock::now();
}
void TextureRender::update()
{
    auto kb = gKeyboard.GetState();
    if (kb.Escape)
    {
        gApp.quit();
    }
}
bool TextureRender::render()
{
#ifdef USE_DDS
    m_spriteBatch->Begin();
#else
    m_spriteBatch->Begin(SpriteSortMode_Deferred, m_commanStates->NonPremultiplied());
#endif
    // auto cost = std::chrono::high_resolution_clock::now() - m_point;
    // auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(cost).count();
    static int degree = 0;
    static int acc = 0;
    float rotation = sinf((degree * 1.0f) * XM_PI / 180);
    acc++;
    if (acc == 10)
    {
        acc = 0;
        degree++;
    }
    m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::PapayaWhip, rotation, m_origin);
    m_spriteBatch->End();
    return true;
}
} // namespace Tao3D

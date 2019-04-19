#include "TextureRender.h"

#include "Application.h"
#include "Common.h"

#define USE_DDS

#include <DirectXTK/DDSTextureLoader.h>
#include <DirectXTK/WICTextureLoader.h>

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

    ThrowIfFailed(CreateWICTextureFromFile(gDevice, L"starfield.png", nullptr, m_background.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile");
    ThrowIfFailed(CreateWICTextureFromFile(gDevice, L"shipanimated.png", nullptr, m_shipTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile");
    m_scrollBackground = std::make_unique<ScrollingBackground>();
    m_scrollBackground->Load(m_background.Get());
    m_scrollBackground->SetWindow(width, height);
    m_ship = std::make_unique<AnimatedTexture>();
    m_ship->Load(m_shipTexture.Get(), 4, 20);

    ComPtr<ID3D11Texture2D> cat;
    ThrowIfFailed(resource.As(&cat), "As");

    CD3D11_TEXTURE2D_DESC catDesc;
    cat->GetDesc(&catDesc);
    m_screenRect.left = 0;
    m_screenRect.top = 0;
    m_screenRect.bottom = height;
    m_screenRect.right = width;

    m_origin.x = static_cast<float>(catDesc.Width) / 2;
    m_origin.y = static_cast<float>(catDesc.Height) / 2;
    m_tileRect.left = catDesc.Width * 2;
    m_tileRect.right = catDesc.Width * 6;
    m_tileRect.top = catDesc.Height * 2;
    m_tileRect.bottom = catDesc.Height * 6;
    m_screenPos.x = static_cast<float>(width) / 2;
    m_screenPos.y = static_cast<float>(height) / 2;
    m_shipPos.x = static_cast<float>(width) / 2;
    m_shipPos.y = static_cast<float>(height) / 2 + height / 4;

    m_point = std::chrono::high_resolution_clock::now();
}
void TextureRender::update()
{
    auto kb = gKeyboard.GetState();
    if (kb.Escape)
    {
        gApp.quit();
    }
    auto cost = std::chrono::high_resolution_clock::now() - m_point;
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(cost).count();
    m_ship->Update(elapsedTime);
    m_scrollBackground->Update(elapsedTime);
}
bool TextureRender::render()
{
#ifdef USE_DDS
    m_spriteBatch->Begin(SpriteSortMode_Deferred, nullptr, m_commanStates->LinearWrap());
#else
    m_spriteBatch->Begin(SpriteSortMode_Deferred, m_commanStates->NonPremultiplied());
#endif

    static int degree = 0;
    static int acc = 0;
    float rotation = sinf((degree * 1.0f) * XM_PI / 180);
    acc++;
    if (acc == 10)
    {
        acc = 0;
        degree++;
    }
    float scale = rotation + 2.0f;
    //m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::ForestGreen, rotation, m_origin, scale);
    //m_spriteBatch->Draw(m_texture.Get(), m_screenPos, &m_tileRect, Colors::White, 0.f, m_origin);
    //m_spriteBatch->Draw(m_background.Get(), m_screenRect);
    m_scrollBackground->Draw(m_spriteBatch.get());
    //m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, rotation, m_origin, scale);
    m_ship->Draw(m_spriteBatch.get(), m_shipPos);
    m_spriteBatch->End();
    return true;
}
} // namespace Tao3D

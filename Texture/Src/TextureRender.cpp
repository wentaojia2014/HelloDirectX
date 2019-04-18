#include "TextureRender.h"

#include "Application.h"
#include "Common.h"

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
    ComPtr<ID3D11Resource> resource;
    ThrowIfFailed(CreateWICTextureFromFile(gDevice, L"cat.png", resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile");
    ComPtr<ID3D11Texture2D> cat;
    ThrowIfFailed(resource.As(&cat), "As");

    CD3D11_TEXTURE2D_DESC catDesc;
    cat->GetDesc(&catDesc);
    m_origin.x = static_cast<float>(catDesc.Width) / 2;
    m_origin.y = static_cast<float>(catDesc.Height) / 2;

    m_screenPos.x = static_cast<float>(width) / 2;
    m_screenPos.y = static_cast<float>(height) / 2;
}
void TextureRender::update()
{
    auto kb = gKeyboard.GetState();
    if (kb.Escape)
    {
        gApp.quit();
    }
    // if (kb.Home)
    //{
    //    m_cameraPos = START_POSITION.v;
    //    m_pitch = m_yaw = 0;
    //}
    // Vector3 move = Vector3::Zero;
    // if (kb.Up || kb.W)
    //{
    //    move.y += m_cameraSpeed;
    //}
    // if (kb.Down || kb.S)
    //{
    //    move.y -= m_cameraSpeed;
    //}
    // if (kb.Left || kb.A)
    //{
    //    move.x += m_cameraSpeed;
    //}
    // if (kb.Right || kb.D)
    //{
    //    move.x -= m_cameraSpeed;
    //}
    // if (kb.PageUp || kb.Space)
    //{
    //    move.z += m_cameraSpeed;
    //}
    // if (kb.PageDown || kb.X)
    //{
    //    move.z -= m_cameraSpeed;
    //}
    // Quaternion q = Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0.f);
    // move = Vector3::Transform(move, q);
    // move *= MOVEMENT_GAIN;
    // m_cameraPos += move;
    // Vector3 halfBound = (Vector3(ROOM_BOUNDS.v) / Vector3(2.f)) - Vector3(0.1f, 0.1f, 0.1f);
    // m_cameraPos = Vector3::Min(m_cameraPos, halfBound);
    // m_cameraPos = Vector3::Max(m_cameraPos, -halfBound);

    // auto mouse = gMouse.GetState();
    // if (mouse.positionMode == Mouse::MODE_RELATIVE)
    //{
    //    Vector3 delta = Vector3(float(mouse.x), float(mouse.y), 0.f) * ROTATION_GAIN;
    //    m_pitch -= delta.y;
    //    m_yaw -= delta.x;

    //    float limit = XM_PI / 2.0f - 0.01f;

    //    m_pitch = (std::max)(-limit, m_pitch);
    //    m_pitch = (std::min)(limit, m_pitch);
    //    if (m_yaw > XM_PI)
    //    {
    //        m_yaw -= XM_PI * 2.0f;
    //    }
    //    else if (m_yaw < -XM_PI)
    //    {
    //        m_yaw += XM_PI * 2.0f;
    //    }
    //}
    // gMouse.SetMode(mouse.leftButton ? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE);
}
bool TextureRender::render()
{
    m_spriteBatch->Begin();
    m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::PapayaWhip, 0.f, m_origin);
    m_spriteBatch->End();
    return true;
}
} // namespace Tao3D

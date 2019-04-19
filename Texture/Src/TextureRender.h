#pragma once
#include "DXResources.h"
#include "IRender.h"
#include <DirectXTK/CommonStates.h>
#include <DirectXTK/GeometricPrimitive.h>
#include <DirectXTK/SimpleMath.h>
#include <DirectXTK/SpriteBatch.h>

#include "AnimatedTexture.h"

#include <chrono>
namespace Tao3D
{
const XMVECTORF32 START_POSITION = { 0.f, -1.5f, 0.f, 0.f };
const XMVECTORF32 ROOM_BOUNDS = { 8.f, 6.f, 12.f, 0.f };
const float ROTATION_GAIN = 0.004f;
const float MOVEMENT_GAIN = 0.07f;
using Microsoft::WRL::ComPtr;
class TextureRender : public IRender
{
public:
    TextureRender();
    ~TextureRender();
    void init(int width, int height) override;
    void update() override;
    bool render() override;

private:
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch = nullptr;
    std::unique_ptr<DirectX::CommonStates> m_commanStates = nullptr;
    std::unique_ptr<AnimatedTexture> m_ship = nullptr;
    ComPtr<ID3D11ShaderResourceView> m_texture;
    ComPtr<ID3D11ShaderResourceView> m_background;
    ComPtr<ID3D11ShaderResourceView> m_shipTexture;
    std::chrono::time_point<std::chrono::steady_clock> m_point;
    Vector2 m_shipPos;
    Vector2 m_screenPos;
    Vector2 m_origin;
    RECT m_tileRect = { 0 };
    RECT m_screenRect = { 0 };
};
} // namespace Tao3D

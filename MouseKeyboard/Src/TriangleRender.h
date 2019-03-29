#pragma once
#include "DXResources.h"
#include "IRender.h"
#include <DirectXTK/GeometricPrimitive.h>
#include <DirectXTK/SimpleMath.h>
namespace Tao3D
{
const XMVECTORF32 START_POSITION = { 0.f, -1.5f, 0.f, 0.f };
const XMVECTORF32 ROOM_BOUNDS = { 8.f, 6.f, 12.f, 0.f };
const float ROTATION_GAIN = 0.004f;
const float MOVEMENT_GAIN = 0.07f;
using Microsoft::WRL::ComPtr;
class TriangleRender : public IRender
{
public:
    TriangleRender();
    ~TriangleRender();
    void init(int width, int height) override;
    void update() override;
    bool render() override;

private:
    std::unique_ptr<DirectX::GeometricPrimitive> m_room;
    ComPtr<ID3D11ShaderResourceView> m_rootTex;
    DirectX::SimpleMath::Vector3 m_cameraPos;
    DirectX::SimpleMath::Matrix m_proj;
    float m_pitch;
    float m_yaw;
    float m_cameraSpeed = 0.01f;
};
} // namespace Tao3D

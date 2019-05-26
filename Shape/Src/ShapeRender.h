#pragma once
#include "DXResources.h"
#include "IRender.h"
#include <DirectXTK/CommonStates.h>
#include <DirectXTK/Effects.h>
#include <DirectXTK/GeometricPrimitive.h>
#include <DirectXTK/PrimitiveBatch.h>
#include <DirectXTK/VertexTypes.h>
#include <memory>
namespace Tao3D
{
using Microsoft::WRL::ComPtr;
class ShapeRender : public IRender
{
public:
    ShapeRender();
    ~ShapeRender();
    void init(int width, int height) override;
    void update() override;
    bool render() override;

private:
    std::unique_ptr<DirectX::CommonStates> m_states = nullptr;
    std::unique_ptr<DirectX::BasicEffect> m_effect = nullptr;
    std::unique_ptr<DirectX::GeometricPrimitive> m_shape = nullptr;
    ComPtr<ID3D11InputLayout> m_inputLayout;
    DirectX::SimpleMath::Matrix m_world;
    DirectX::SimpleMath::Matrix m_view;
    DirectX::SimpleMath::Matrix m_proj;
};
} // namespace Tao3D

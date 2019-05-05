#pragma once
#include "DXResources.h"
#include "IRender.h"
#include <DirectXTK/CommonStates.h>
#include <DirectXTK/Effects.h>
#include <DirectXTK/PrimitiveBatch.h>
#include <DirectXTK/VertexTypes.h>
#include <memory>
#include <chrono>
namespace Tao3D
{
using Microsoft::WRL::ComPtr;
class GridRender : public IRender
{
public:
    GridRender();
    ~GridRender();
    void init(int width, int height) override;
    void update() override;
    bool render() override;

private:
    std::unique_ptr<DirectX::CommonStates> m_states = nullptr;
    std::unique_ptr<DirectX::BasicEffect> m_effect = nullptr;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch = nullptr;
    ComPtr<ID3D11InputLayout> m_inputLayout;
    ComPtr<ID3D11RasterizerState> m_raster;
    std::chrono::high_resolution_clock::time_point m_startPoint;
    DirectX::SimpleMath::Matrix m_world;
    DirectX::SimpleMath::Matrix m_view;
    DirectX::SimpleMath::Matrix m_proj;
};
} // namespace Tao3D

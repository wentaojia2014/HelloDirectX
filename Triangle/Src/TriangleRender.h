#pragma once
#include "DXResources.h"
#include "IRender.h"
#include <DirectXTK/CommonStates.h>
#include <DirectXTK/Effects.h>
#include <DirectXTK/PrimitiveBatch.h>
#include <DirectXTK/VertexTypes.h>
#include <memory>
namespace Tao3D
{
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
    std::unique_ptr<DirectX::CommonStates> m_states = nullptr;
    std::unique_ptr<DirectX::BasicEffect> m_effect = nullptr;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch = nullptr;
    ComPtr<ID3D11InputLayout> m_inputLayout;
};
} // namespace Tao3D

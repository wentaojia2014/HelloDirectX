#include "TriangleRender.h"

#include "Application.h"
#include "Common.h"

#include <algorithm>
#include <DirectXTK/DirectXHelpers.h>
#include <DirectXColors.h>
namespace Tao3D
{
TriangleRender::TriangleRender() {}

TriangleRender::~TriangleRender() {}
void TriangleRender::init(int width, int height)
{
    m_states = std::make_unique<CommonStates>(gDevice);
    m_effect = std::make_unique<BasicEffect>(gDevice);
    m_effect->SetVertexColorEnabled(true);
    void const *shaderByteCode;
    size_t byteCodeLength;
    m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
    ThrowIfFailed(
        gDevice->CreateInputLayout(
            VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf()),
        "CreateInputLayout");
    m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(gContext);
}
void TriangleRender::update()
{
    auto kb = gKeyboard.GetState();
    if (kb.Escape)
    {
        gApp.quit();
    }
}
bool TriangleRender::render()
{
    gContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xffffffff);
    gContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
    gContext->RSSetState(m_states->CullNone());

    m_effect->Apply(gContext);
    gContext->IASetInputLayout(m_inputLayout.Get());

    m_primitiveBatch->Begin();
    VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f), Colors::SeaGreen);
    VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f), Colors::SeaGreen);
    VertexPositionColor v3(Vector3(-0.5f, -0.5f, 0.5f), Colors::SeaGreen);
    m_primitiveBatch->DrawTriangle(v1, v2, v3);
    m_primitiveBatch->End();
    return true;
}
} // namespace Tao3D

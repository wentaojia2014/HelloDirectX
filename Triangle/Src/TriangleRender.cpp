#include "TriangleRender.h"

#include "Application.h"
#include "Common.h"

#include <DirectXColors.h>
#include <DirectXTK/DirectXHelpers.h>
#include <algorithm>
namespace Tao3D
{
TriangleRender::TriangleRender() {}

TriangleRender::~TriangleRender() {}
void TriangleRender::init(int width, int height)
{
    m_states = std::make_unique<CommonStates>(gDevice);
    auto projection = Matrix::CreateScale(2.f / float(width), -2.f / float(height), 1.f) * Matrix::CreateTranslation(-1.f, 1.f, 0.f);

    m_effect = std::make_unique<BasicEffect>(gDevice);
    m_effect->SetProjection(projection);
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
    gContext->RSSetState(m_states->CullCounterClockwise());

    m_effect->Apply(gContext);
    gContext->IASetInputLayout(m_inputLayout.Get());

    m_primitiveBatch->Begin();
    // VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f), Colors::SeaGreen);
    // VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f), Colors::SeaGreen);
    // VertexPositionColor v3(Vector3(-0.5f, -0.5f, 0.5f), Colors::SeaGreen);
    VertexPositionColor v1(Vector3(500.f, 150.f, 0.f), Colors::PaleVioletRed);
    VertexPositionColor v2(Vector3(700.f, 450.f, 0.f), Colors::SeaGreen);
    VertexPositionColor v3(Vector3(300.f, 450.f, 0.f), Colors::LightGoldenrodYellow);
    m_primitiveBatch->DrawTriangle(v1, v2, v3);
    m_primitiveBatch->End();
    return true;
}
} // namespace Tao3D

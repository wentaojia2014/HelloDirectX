#include "GridRender.h"

#include "Application.h"
#include "Common.h"

#include <DirectXColors.h>
#include <DirectXTK/DirectXHelpers.h>
#include <algorithm>
namespace Tao3D
{
GridRender::GridRender() {}

GridRender::~GridRender() {}
void GridRender::init(int width, int height)
{
    m_states = std::make_unique<CommonStates>(gDevice);

    m_world = gResource.getWorldMatrix();
    m_view = Matrix::CreateLookAt(Vector3(2.f, 4.f, 2.f), Vector3::Zero, Vector3::UnitY);
    m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f, float(width) / float(height), 0.1f, 10.f);

    m_effect = std::make_unique<BasicEffect>(gDevice);
    m_effect->SetProjection(m_proj);
    m_effect->SetView(m_view);
    m_effect->SetVertexColorEnabled(true);

    void const *shaderByteCode;
    size_t byteCodeLength;
    m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
    ThrowIfFailed(
        gDevice->CreateInputLayout(
            VertexPositionColor::InputElements, VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf()),
        "CreateInputLayout");
    m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(gContext);
    CD3D11_RASTERIZER_DESC rastDesc(
        D3D11_FILL_SOLID,
        D3D11_CULL_NONE,
        FALSE,
        D3D11_DEFAULT_DEPTH_BIAS,
        D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
        TRUE,
        FALSE,
        FALSE,
        TRUE);
    ThrowIfFailed(gDevice->CreateRasterizerState(&rastDesc, m_raster.ReleaseAndGetAddressOf()), "CreateRasterizerState");

    m_startPoint = std::chrono::high_resolution_clock::now();
}
void GridRender::update()
{
    auto kb = gKeyboard.GetState();
    if (kb.Escape)
    {
        gApp.quit();
    }
    auto now = std::chrono::high_resolution_clock::now();
    auto cost = now - m_startPoint;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(cost).count();
    m_world = Matrix::CreateRotationY(cosf((float)seconds));
}
bool GridRender::render()
{
    gContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
    gContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
    gContext->RSSetState(m_raster.Get());
    m_effect->SetWorld(m_world);
    m_effect->Apply(gContext);
    gContext->IASetInputLayout(m_inputLayout.Get());

    m_primitiveBatch->Begin();

    Vector3 xAxis(2.0f, 0.f, 0.f);
    Vector3 yAxis(0.0f, 0.f, 2.f);
    Vector3 origin = Vector3::Zero;

    size_t division = 20;
    for (int i = 0; i <= division; ++i)
    {
        float percent = float(i) / division;
        percent = 2.0f * percent - 1.0f;
        {
            Vector3 scale = xAxis * percent + origin;
            VertexPositionColor v1(scale - yAxis, Colors ::White);
            VertexPositionColor v2(scale + yAxis, Colors ::White);
            m_primitiveBatch->DrawLine(v1, v2);
        }
        {
            Vector3 scale = yAxis * percent + origin;
            VertexPositionColor v1(scale - xAxis, Colors ::White);
            VertexPositionColor v2(scale + xAxis, Colors ::White);
            m_primitiveBatch->DrawLine(v1, v2);
        }
    }

    m_primitiveBatch->End();
    return true;
}
} // namespace Tao3D

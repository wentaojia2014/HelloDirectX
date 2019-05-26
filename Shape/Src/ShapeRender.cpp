#include "ShapeRender.h"

#include "Application.h"
#include "Common.h"

#include <DirectXColors.h>
#include <DirectXTK/DirectXHelpers.h>
#include <algorithm>
namespace Tao3D
{
ShapeRender::ShapeRender() {}

ShapeRender::~ShapeRender() {}
void ShapeRender::init(int width, int height)
{
    m_states = std::make_unique<CommonStates>(gDevice);

    m_world = gResource.getWorldMatrix();
    m_view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f), Vector3(2.f, 2.f, -20.f), Vector3::UnitY);
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
    m_shape = GeometricPrimitive::CreateCube(gContext);
    //m_shape = GeometricPrimitive::CreateBox(gContext, {10.f, 10.f, 1.f});
    //m_shape = GeometricPrimitive::CreateSphere(gContext);
    //m_shape = GeometricPrimitive::CreateGeoSphere(gContext);
    //m_shape = GeometricPrimitive::CreateCylinder(gContext);
    //m_shape = GeometricPrimitive::CreateCone(gContext);
    //m_shape = GeometricPrimitive::CreateTorus(gContext);
    //m_shape = GeometricPrimitive::CreateTetrahedron(gContext);
    //m_shape = GeometricPrimitive::CreateOctahedron(gContext);
    //m_shape = GeometricPrimitive::CreateDodecahedron(gContext);
    //m_shape = GeometricPrimitive::CreateIcosahedron(gContext);
    //m_shape = GeometricPrimitive::CreateTeapot(gContext);
}
void ShapeRender::update()
{
    auto kb = gKeyboard.GetState();
    if (kb.Escape)
    {
        gApp.quit();
    }

    m_world = Matrix::CreateTranslation(2.f, 2.f, 0.f);
    //m_world = Matrix::CreateRotationZ(static_cast<float>(angle / 360.f * XM_PI));
    m_effect->SetWorld(m_world);
}
bool ShapeRender::render()
{
    gContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
    gContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
    m_effect->Apply(gContext);
    gContext->IASetInputLayout(m_inputLayout.Get());
    static int angle = 0;
    static int frameCount = 0;
    frameCount++;
    if (frameCount > 30)
    {
        frameCount = 0;
        angle++;
    }
    auto world = Matrix::CreateTranslation(2.f, 2.f, 0.f);
    world *= Matrix::CreateRotationZ(static_cast<float>(angle / 360.f * XM_PI));
    m_shape->Draw(m_world, m_view, m_proj);
   
    return true;
}
} // namespace Tao3D

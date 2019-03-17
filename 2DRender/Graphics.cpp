#include "Graphics.h"

#include "Bitmap.h"
#include "D3D.h"
#include "Implement/Camera.h"
#include "Light.h"
#include "Shader.h"
namespace Tao3D
{
using namespace DirectX;
Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Init(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
{
    m_d3d = std::make_unique<D3D>();
    m_d3d->Initialize(screenWidth, screenHeight, hwnd, fullScreen);

    m_camera = std::make_unique<Camera>();
    m_camera->SetPosition(0.0f, 0.0f, -8.0f);

    m_shader = std::make_unique<Shader>();
    m_shader->Initialize(m_d3d->GetDevice(), L"lightV.cso", L"lightP.cso");

    m_light = std::make_unique<Light>();
    m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
    m_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_light->SetDirection(0.0f, 0.0f, 1.0f);
    m_light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_light->SetSpecularPower(32.0f);

    m_bitmap = std::make_unique<Bitmap>();
    m_bitmap->Init(m_d3d->GetDevice(), screenWidth, screenHeight, L"seafloor.dds", 256, 256);
    return true;
}

void Graphics::Uninit()
{
    m_d3d->Shutdown();
    m_shader->Shutdown();
}

bool Graphics::Frame()
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX ortho;
    bool ret = true;
    static float rotation = 0.0f;

    rotation += (float)XM_PI * 0.0001f;
    if (rotation > 360.0f)
    {
        rotation -= 360.0f;
    }
    m_d3d->BeginScene(0.6f, 0.0f, 0.0f, 1.0f);

    m_camera->Render();
    m_camera->GetViewMatrix(view);

    m_d3d->GetWorldMatrix(world);
    m_d3d->GetOrthoMatrix(ortho);
    m_d3d->TurnZBufferOff();

    m_bitmap->Render(m_d3d->GetDeviceContext(), 100, 100);
    m_shader->Render(
        m_d3d->GetDeviceContext(),
        m_bitmap->GetIndexCount(),
        { world, view, ortho },
        m_bitmap->GetTexture(),
        { m_light->GetAmbientColor(), m_light->GetDiffuseColor(), m_light->GetDirection() },
        { m_camera->GetPosition(), 0.0f });
    m_d3d->TurnZBufferOn();
    m_d3d->EndScene();

    return ret;
}
} // namespace Tao3D

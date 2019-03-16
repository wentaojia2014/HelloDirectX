#include "Graphics.h"

#include "Camera.h"
#include "D3D.h"
#include "Light.h"
#include "Model.h"
#include "Shader.h"
namespace TaoD3D
{
    using namespace DirectX;
Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
{
    m_d3d = new D3D;
    m_d3d->Initialize(screenWidth, screenHeight, hwnd, fullScreen);

    m_camera = new Camera;
    m_camera->SetPosition(0.0f, 0.0f, -8.0f);

    m_shader = new Shader;
    m_shader->Initialize(m_d3d->GetDevice(), L"lightV.cso", L"lightP.cso");

    m_model = new Model;
    m_model->Initialize(m_d3d->GetDevice(), m_d3d->GetDeviceContext(), L"qingzhi.jpg", u8"cube.txt");

    m_light = new Light;
    m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
    m_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_light->SetDirection(0.0f, 0.0f, 1.0f);
    m_light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_light->SetSpecularPower(32.0f);
    return true;
}

void Graphics::Shutdown()
{
    SafeShutdown(m_d3d);
    SafeShutdown(m_model);
    SafeShutdown(m_shader);
    SafeShutdown(m_camera);
    SafeDelete(m_light);
}

bool Graphics::Frame()
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX project;
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
    m_d3d->GetProjectMatrix(project);
    world = XMMatrixRotationY(rotation);
    m_model->Render(m_d3d->GetDeviceContext());
    m_shader->Render(
        m_d3d->GetDeviceContext(),
        m_model->GetIndexCount(),
        { world, view, project },
        m_model->GetTexture(),
        { m_light->GetAmbientColor(), m_light->GetDiffuseColor(), m_light->GetDirection() },
        { m_camera->GetPosition(), 0.0f });

    m_d3d->EndScene();

    return ret;
}
} // namespace TaoD3D

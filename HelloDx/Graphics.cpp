#include "Graphics.h"

#include "Camera.h"
#include "D3D.h"
#include "Light.h"
#include "Model.h"
#include "Shader.h"
namespace TaoD3D
{
Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
{
    m_d3d = new D3D;
    m_d3d->Initialize(screenWidth, screenHeight, hwnd, fullScreen);

    m_camera = new Camera;
    m_camera->SetPosition(0.0f, 0.0f, -8.0f);

    m_shader = new Shader;
    m_shader->Initialize(m_d3d->GetDevice(), u8"lightV.shader", u8"lightP.shader");

    m_model = new Model;
    m_model->Initialize(m_d3d->GetDevice(), u8"qingzhi.jpg", u8"cubecube.txt");

    m_light = new Light;
    m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
    m_light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_light->SetDirection(1.0f, 0.0f, 0.0f);
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
    D3DXMATRIX world;
    D3DXMATRIX view;
    D3DXMATRIX project;
    bool ret = true;
    static float rotation = 0.0f;

    rotation += (float)D3DX_PI * 0.001;
    if (rotation > 360.0f)
    {
        rotation -= 360.0f;
    }
    m_d3d->BeginScene(0.6f, 0.0f, 0.0f, 1.0f);
    m_camera->Render();
    m_camera->GetViewMatrix(view);
    m_d3d->GetWorldMatrix(world);
    m_d3d->GetProjectMatrix(project);

    D3DXMatrixRotationY(&world, rotation);
    m_model->Render(m_d3d->GetDeviceContext());
    m_shader->Render(
        m_d3d->GetDeviceContext(),
        m_model->GetIndexCount(),
        { world, view, project },
        m_model->GetTexture(),
        { m_light->GetAmbientColor(), m_light->GetDiffuseColor(), m_light->GetDirection(), 0.0f });

    m_d3d->EndScene();

    return ret;
}
} // namespace TaoD3D

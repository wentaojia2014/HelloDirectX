#include "Graphics.h"

#include "Camera.h"
#include "D3D.h"
#include "Model.h"
#include "TextureShader.h"
namespace TaoD3D
{
Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
{
    m_d3d = new D3D;
    m_d3d->Initialize(screenWidth, screenHeight, hwnd, fullScreen);

    m_camera = new Camera;
    m_camera->SetPosition(0.0f, 0.0f, -7.0f);
    
	m_shader = new TextureShader;
    m_shader->Initialize(m_d3d->GetDevice(), u8"vertex.shader", u8"pixel.shader");

    m_model = new Model;
    m_model->Initialize(m_d3d->GetDevice(), u8"qingzhi.jpg");

    return true;
}

void Graphics::Shutdown()
{
    SafeShutdown(m_d3d);
    SafeShutdown(m_model);
    SafeShutdown(m_shader);
    SafeShutdown(m_camera);
}

bool Graphics::Frame()
{
    D3DXMATRIX world;
    D3DXMATRIX view;
    D3DXMATRIX project;
    bool ret = true;

    m_d3d->BeginScene(0.6f, 0.0f, 0.0f, 1.0f);
    m_camera->Render();
    m_camera->GetViewMatrix(view);
    m_d3d->GetWorldMatrix(world);
    m_d3d->GetProjectMatrix(project);
    m_model->Render(m_d3d->GetDeviceContext());
    m_shader->Render(m_d3d->GetDeviceContext(), m_model->GetIndexCount(), { world, view, project }, m_model->GetTexture());

    m_d3d->EndScene();

    return ret;
}
} // namespace TaoD3D

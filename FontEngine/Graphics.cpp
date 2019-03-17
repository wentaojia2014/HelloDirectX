#include "Graphics.h"

#include "D3D.h"
#include "Implement/Camera.h"
#include "Text.h"
namespace Tao3D
{
using namespace DirectX;
Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Init(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
{
    XMMATRIX baseView;
    m_d3d = std::make_unique<D3D>();
    m_d3d->Initialize(screenWidth, screenHeight, hwnd, fullScreen);

    m_camera = std::make_unique<Camera>();
    m_camera->SetPosition(0.0f, 0.0f, -1.0f);
    m_camera->Render();
    m_camera->GetViewMatrix(baseView);

    m_text = std::make_unique<Text>();
    m_text->Init(m_d3d->GetDevice(), m_d3d->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseView);
    return true;
}

void Graphics::Uninit()
{
    m_text->Uninit();
    m_d3d->Shutdown();
}

bool Graphics::Frame()
{
    XMMATRIX world;
    XMMATRIX ortho;
    bool ret = true;

    m_d3d->BeginScene(0.6f, 0.0f, 0.0f, 1.0f);

    m_camera->Render();

    m_d3d->GetWorldMatrix(world);
    m_d3d->GetOrthoMatrix(ortho);
    m_d3d->TurnZBufferOff();
    m_d3d->TurnAlphaBlendingOn();
    m_text->Render(m_d3d->GetDeviceContext(), world, ortho);
    m_d3d->TurnAlphaBlendingOff();
    m_d3d->TurnZBufferOn();
    m_d3d->EndScene();

    return ret;
}
} // namespace Tao3D

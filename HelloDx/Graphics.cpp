#include "Graphics.h"

#include "Render.h"

Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
{
    m_render = new Render;
    return m_render->Initialize(screenWidth, screenHeight, hwnd, fullScreen);
    
}

void Graphics::Shutdown()
{
    m_render->Shutdown();
    delete m_render;
    m_render = nullptr;
}

bool Graphics::Frame()
{
    bool ret;
    m_render->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
    ret = m_render->render();
    m_render->EndScene();
    return ret;
}


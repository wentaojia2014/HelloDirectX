#include "Graphics.h"

#include "Render.h"

Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    m_render = new Render;
    return m_render->Initialize(screenWidth, screenHeight, hwnd);
    
}

void Graphics::Shutdown()
{
    m_render->Shutdown();
    delete m_render;
    m_render = nullptr;
}

bool Graphics::Frame()
{
    return m_render->render();
}


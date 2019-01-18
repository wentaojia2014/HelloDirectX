#pragma once
#include <windowsx.h>

#include <D3DX11.h>

#include <D3DX10.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

class Render
{
public:
    bool render();
    bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
    void Shutdown();

protected:
    bool InitD3D(int screenWidth, int screenHeight, HWND hwnd);
    bool InitPipeLine();
    bool InitGraphics();

private:
    IDXGISwapChain *m_swapChain = nullptr;
    ID3D11Device *m_device = nullptr;
    ID3D11DeviceContext *m_context = nullptr;
    ID3D11RenderTargetView *m_targetView = nullptr;
    ID3D11VertexShader *m_vs = nullptr;
    ID3D11PixelShader *m_ps = nullptr;
    ID3D11Buffer *m_vBuffer = nullptr;
    ID3D11InputLayout *m_layout = nullptr;
};

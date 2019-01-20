#pragma once
#include <windowsx.h>

#include <D3DX11.h>

#include <D3Dcommon.h>
#include <D3DX10.h>
#include <D3DX10math.h>
#include <DXGI.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

class Render
{
public:
    bool render();
    bool Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen);
    void Shutdown();

    void BeginScene(float r, float g, float b, float a);
    void EndScene();
    ID3D11Device *GetDevice()
    {
        return m_device;
    }
    ID3D11DeviceContext *GetDeviceContext()
    {
        return m_context;
    }

protected:
    void InitSwapChain( HWND hwnd, bool fullScreen);
    void InitPipeLine();
    void InitGraphics();
    void InitRefreshRate();
    void InitDepthStencilBuffer();
    void InitRaster();
    void InitRenderTarget();
    void InitViewPort();

private:
    int m_screenWidth;
    int m_screenHeight;
    IDXGISwapChain *m_swapChain = nullptr;
    ID3D11Device *m_device = nullptr;
    ID3D11DeviceContext *m_context = nullptr;
    ID3D11RenderTargetView *m_targetView = nullptr;
    ID3D11Texture2D *m_depthStencilBuffer = nullptr;
    ID3D11DepthStencilState *m_depthStencilState = nullptr;
    ID3D11DepthStencilView *m_depthStencilView = nullptr;
    ID3D11RasterizerState *m_rasterState = nullptr;
    ID3D11VertexShader *m_vs = nullptr;
    ID3D11PixelShader *m_ps = nullptr;
    ID3D11Buffer *m_vBuffer = nullptr;
    ID3D11InputLayout *m_layout = nullptr;

    D3DXMATRIX m_projectMat;
    D3DXMATRIX m_worldMat;
    D3DXMATRIX m_orthoMat;
    unsigned int m_numerator;
    unsigned int m_denominator;
    bool m_vsyncEnabled = true;
    int m_videoCardMemory;
    char m_videoCardDescription[128];
};

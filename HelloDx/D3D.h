#pragma once
#include "D3DHeader.h"
namespace TaoD3D
{
class D3D
{
public:
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
    void GetProjectMatrix(D3DXMATRIX &mat);
    void GetWorldMatrix(D3DXMATRIX &mat);
    void GetOrthoMatrix(D3DXMATRIX &mat);

protected:
    void InitSwapChain(HWND hwnd, bool fullScreen);
    void InitMatrix();
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

    unsigned int m_numerator;
    unsigned int m_denominator;
    bool m_vsyncEnabled = true;
    int m_videoCardMemory;
    char m_videoCardDescription[128];
    D3DXMATRIX m_projectMat;
    D3DXMATRIX m_worldMat;
    D3DXMATRIX m_orthoMat;
};
} // namespace TaoD3D

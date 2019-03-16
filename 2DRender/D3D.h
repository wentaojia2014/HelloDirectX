#pragma once
#include "D3DHeader.h"

namespace Tao3D
{
using namespace DirectX;
using Microsoft::WRL::ComPtr;
class D3D
{

public:
    bool Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen);
    void Shutdown();

    void BeginScene(float r, float g, float b, float a);
    void EndScene();
    ID3D11Device *GetDevice()
    {
        return m_device.Get();
    }
    ID3D11DeviceContext *GetDeviceContext()
    {
        return m_context.Get();
    }
    void GetProjectMatrix(XMMATRIX &mat);
    void GetWorldMatrix(XMMATRIX &mat);
    void GetOrthoMatrix(XMMATRIX &mat);
    void TurnZBufferOn();
    void TurnZBufferOff();
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

    ComPtr<IDXGISwapChain> m_swapChain = nullptr;
    ComPtr<ID3D11Device> m_device = nullptr;
    ComPtr<ID3D11DeviceContext> m_context = nullptr;
    ComPtr<ID3D11RenderTargetView> m_targetView = nullptr;
    ComPtr<ID3D11Texture2D> m_depthStencilBuffer = nullptr;
    ComPtr<ID3D11DepthStencilState> m_depthStencilState = nullptr;
    ComPtr<ID3D11DepthStencilState> m_depthDisabledStencilState = nullptr;
    ComPtr<ID3D11DepthStencilView> m_depthStencilView = nullptr;
    ComPtr<ID3D11RasterizerState> m_rasterState = nullptr;
    ComPtr < ID3D11Texture2D> m_backBuffer = nullptr;
    unsigned int m_numerator;
    unsigned int m_denominator;
    bool m_vsyncEnabled = false;
    int m_videoCardMemory;
    char m_videoCardDescription[128];
    XMMATRIX m_projectMat;
    XMMATRIX m_worldMat;
    XMMATRIX m_orthoMat;
};
} // namespace Tao3D

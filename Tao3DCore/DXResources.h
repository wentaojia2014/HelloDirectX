#pragma once

#include <Windows.h>

#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <D3D11.h>

#include <DXGI.h>
#include <DirectXTK/SimpleMath.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
namespace Tao3D
{
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;
class DXResources
{
public:
    bool init(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen);
    void uninit();
    void setClearColor(float r, float g, float b, float a);
    void beginScene();
    void endScene();
    ID3D11Device *getDevice()
    {
        return m_device.Get();
    }
    ID3D11DeviceContext *getDeviceContext()
    {
        return m_context.Get();
    }
    Matrix &getProjectionMatrix()
    {
        return m_projection;
    }
    Matrix &getWorldMatrix()
    {
        return m_world;
    }
    Matrix &getOrthoMatrix()
    {
        return m_ortho;
    }

    void turnZBufferOn();
    void turnZBufferOff();

    void turnAlphaBlendingOn();
    void turnAlphaBlendingOff();

protected:
    void initSwapChain(HWND hwnd, bool fullScreen);
    void initMatrix();
    void initRefreshRate();
    void initDepthStencilBuffer();
    void initRaster();
    void initRenderTarget();
    void initViewPort();
    void initBlend();

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
    ComPtr<ID3D11Texture2D> m_backBuffer = nullptr;

    ComPtr<ID3D11BlendState> m_alphaEnabledBlendingState = nullptr;
    ComPtr<ID3D11BlendState> m_alphaDisabledBlendingState = nullptr;
    unsigned int m_numerator;
    unsigned int m_denominator;
    bool m_vsyncEnabled = false;
    int m_videoCardMemory;
    char m_videoCardDescription[128];
    Matrix m_projection;
    Matrix m_world;
    Matrix m_ortho;
    float m_clearColor[4] = { 0.2f, 0.3f, 0.4f, 1.0f };
};

} // namespace Tao3D

#pragma once
#include <Windows.h>
#include <windowsx.h>

#include <D3DX11.h>
#include <D3DX10.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

class Graphics
{
public:
    Graphics();
    ~Graphics();

    bool Initialize(int screenWidth, int screenHeight, HWND hwnd);
    void Shutdown();
    bool Frame();

protected:
    bool Render();
    bool InitD3D(int screenWidth, int screenHeight, HWND hwnd);
    bool InitPipeLine();
    bool InitGraphics();
	
private:
     IDXGISwapChain *gSwapChain = nullptr;
     ID3D11Device *gDevice = nullptr;
     ID3D11DeviceContext *gContext = nullptr;
     ID3D11RenderTargetView *gTargetView = nullptr;
     ID3D11VertexShader *gVs = nullptr;
     ID3D11PixelShader *gPs = nullptr;
     ID3D11Buffer *gVBuffer = nullptr;
     ID3D11InputLayout *gLayout = nullptr;

};

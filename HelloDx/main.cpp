#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

//#include "System.h"
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nShowCmd)
//{
//    System s;
//    if (s.Initialize())
//    {
//        s.Run();
//    }
//    s.Shutdown();
//    return 0;
//}
#include <windows.h>
#include <windowsx.h>

#include <D3DX11.h>

#include <D3DX10.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

const static int X = 300;
const static int Y = 100;
const static int W = 800;
const static int H = 600;

struct Vertex
{
    float x, y, z;
    D3DXCOLOR color;
};

IDXGISwapChain *gSwapChain = nullptr;
ID3D11Device *gDevice = nullptr;
ID3D11DeviceContext *gContext = nullptr;
ID3D11RenderTargetView *gTargetView = nullptr;
ID3D11VertexShader *gVs = nullptr;
ID3D11PixelShader *gPs = nullptr;
ID3D11Buffer *gVBuffer = nullptr;
ID3D11InputLayout *gLayout = nullptr;

void InitD3D(HWND hWnd);
void InitPipeLine();
void InitGraphics();
void RenderFrame();
void CleanD3D();
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void InitD3D(HWND hWnd)
{
    // Direct3D init
    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof scd);
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = W;
    scd.BufferDesc.Height = H;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = true;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, &gSwapChain, &gDevice, nullptr, &gContext);
    // get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
    // create render target
    gDevice->CreateRenderTargetView(pBackBuffer, nullptr, &gTargetView);

    pBackBuffer->Release();
    // set render target
    gContext->OMSetRenderTargets(1, &gTargetView, nullptr);
    // set view port
    D3D11_VIEWPORT viewPort;
    ZeroMemory(&viewPort, sizeof viewPort);
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    viewPort.Width = W;
    viewPort.Height = H;
    gContext->RSSetViewports(1, &viewPort);
}
void InitPipeLine()
{
    ID3D10Blob *vs, *ps;
    D3DX11CompileFromFile(u8"shaders.shader", nullptr, nullptr, "VShader", "vs_4_0", 0, 0, 0, &vs, 0, 0);
    D3DX11CompileFromFile(u8"shaders.shader", nullptr, nullptr, "PShader", "ps_4_0", 0, 0, 0, &ps, 0, 0);
    gDevice->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &gVs);
    gDevice->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &gPs);
    gContext->VSSetShader(gVs, nullptr, 0);
    gContext->PSSetShader(gPs, nullptr, 0);

    D3D11_INPUT_ELEMENT_DESC ied[] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
    gDevice->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), vs->GetBufferPointer(), vs->GetBufferSize(), &gLayout);
    gContext->IASetInputLayout(gLayout);
}
void InitGraphics()
{
    // Vertex vertex = {0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)};
    Vertex vertexs[] = {
        { 0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
        { 0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
        { -0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) },
    };

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof bd);
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = sizeof vertexs;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    gDevice->CreateBuffer(&bd, nullptr, &gVBuffer);

    D3D11_MAPPED_SUBRESOURCE ms;
    gContext->Map(gVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    memcpy(ms.pData, vertexs, sizeof vertexs);
    gContext->Unmap(gVBuffer, 0);
}
void RenderFrame()
{
    gContext->ClearRenderTargetView(gTargetView, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

	UINT stride = sizeof(Vertex);
    UINT offset = 0;
    gContext->IASetVertexBuffers(0, 1, &gVBuffer, &stride, &offset);
    gContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    gContext->Draw(3, 0);
    gSwapChain->Present(0, 0);

}
void CleanD3D()
{
    gVs->Release();
    gPs->Release();
    gSwapChain->SetFullscreenState(false, nullptr);
    gLayout->Release();
    gSwapChain->Release();
    gVBuffer->Release();
    gTargetView->Release();
    gDevice->Release();
    gContext->Release();
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nShowCmd)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // window handle, filled by a function
    HWND hWnd;
    // this struct hold information for the window class info
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof wc);

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = u8"WindowClass1";

    RegisterClassEx(&wc);
    RECT windowRect = { 0, 0, W, H };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
    hWnd = CreateWindowEx(
        0,
        u8"WindowClass1",
        u8"Hello Window",
        WS_OVERLAPPEDWINDOW,
        X,
        Y,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,
        nullptr,
        hInstance,
        nullptr);
    ShowWindow(hWnd, nShowCmd);
    InitD3D(hWnd);
    InitPipeLine();
    InitGraphics();
    MSG msg;
    bool notOver = true;
    while (notOver)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
            {
                notOver = false;
            }
        }
        RenderFrame();
    }
    CleanD3D();
    return static_cast<int>(msg.wParam);
}

#include "Graphics.h"
#include <string>
struct Vertex
{
    float x, y, z;
    D3DXCOLOR color;
};
static std::string GetLastErrorAsString()
{
    // Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0)
        return std::string("errorMessageID is 0"); // No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = ::FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorMessageID,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)(&messageBuffer),
        0,
        nullptr);
    std::string message(messageBuffer, size);

    // Free the buffer.
    ::LocalFree(messageBuffer);

    return message;
}

template <typename T>
void ThrowIfFailed(HRESULT hr, T &&msg)
{
    if (FAILED(hr))
    {
        OutputDebugStringA(GetLastErrorAsString().data());
        throw std::system_error
        {
            hr, std::system_category(), std::forward<T>(msg)
        };
	}
}
Graphics::Graphics() {}

Graphics::~Graphics() {}

bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    if (!InitD3D(screenWidth, screenHeight, hwnd))
    {
        return false;
    }
    if (!InitPipeLine())
    {
        return false;
    }
    if (!InitGraphics())
    {
        return false;
    }
    return true;
}
bool Graphics::InitD3D(int screenWidth, int screenHeight, HWND hwnd)
{
    // Direct3D init
    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof scd);
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = screenWidth;
    scd.BufferDesc.Height = screenHeight;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = true;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    ThrowIfFailed(
        D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, &gSwapChain, &gDevice, nullptr, &gContext),
        "D3D11CreateDeviceAndSwapChain ");
    // get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    ThrowIfFailed(gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer), "GetBuffer");
    // create render target
    ThrowIfFailed(gDevice->CreateRenderTargetView(pBackBuffer, nullptr, &gTargetView), "CreateRenderTargetView");

    pBackBuffer->Release();
    // set render target
    gContext->OMSetRenderTargets(1, &gTargetView, nullptr);
    // set view port
    D3D11_VIEWPORT viewPort;
    ZeroMemory(&viewPort, sizeof viewPort);
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    viewPort.Width = screenWidth;
    viewPort.Height = screenHeight;
    gContext->RSSetViewports(1, &viewPort);

    return true;
}
bool Graphics::InitPipeLine()
{
    ID3D10Blob *vs, *ps;
    ThrowIfFailed(D3DX11CompileFromFile(u8"shaders.shader", nullptr, nullptr, "VShader", "vs_4_0", 0, 0, 0, &vs, 0, 0), "D3DX11CompileFromFile");
    ThrowIfFailed(D3DX11CompileFromFile(u8"shaders.shader", nullptr, nullptr, "PShader", "ps_4_0", 0, 0, 0, &ps, 0, 0), "D3DX11CompileFromFile");
    ThrowIfFailed(gDevice->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &gVs), "CreateVertexShader");
    ThrowIfFailed(gDevice->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &gPs), "CreatePixelShader");
    gContext->VSSetShader(gVs, nullptr, 0);
    gContext->PSSetShader(gPs, nullptr, 0);

    D3D11_INPUT_ELEMENT_DESC ied[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    ThrowIfFailed(gDevice->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), vs->GetBufferPointer(), vs->GetBufferSize(), &gLayout),"CreateInputLayout");
    gContext->IASetInputLayout(gLayout);
    return true;
}
bool Graphics::InitGraphics()
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
    ThrowIfFailed(gDevice->CreateBuffer(&bd, nullptr, &gVBuffer), "CreateBuffer");

    D3D11_MAPPED_SUBRESOURCE ms;
    ThrowIfFailed(gContext->Map(gVBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms), "Map");
    memcpy(ms.pData, vertexs, sizeof vertexs);
    gContext->Unmap(gVBuffer, 0);
    return true;
}
void Graphics::Shutdown()
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

bool Graphics::Frame()
{
    return Render();
}

bool Graphics::Render()
{
    gContext->ClearRenderTargetView(gTargetView, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    gContext->IASetVertexBuffers(0, 1, &gVBuffer, &stride, &offset);
    gContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    gContext->Draw(3, 0);
	if (FAILED(gSwapChain->Present(0, 0))) 
	{
        return false;
	}
    return true;
}

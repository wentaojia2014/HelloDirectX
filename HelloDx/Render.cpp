#include "Render.h"
#include "Common.h"
struct Vertex
{
    float x, y, z;
    D3DXCOLOR color;
};

bool Render::Initialize(int screenWidth, int screenHeight, HWND hwnd)
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

void Render::Shutdown()
{
    m_vs->Release();
    m_ps->Release();
    m_swapChain->SetFullscreenState(false, nullptr);
    m_layout->Release();
    m_swapChain->Release();
    m_vBuffer->Release();
    m_targetView->Release();
    m_device->Release();
    m_context->Release();
}

bool Render::InitD3D(int screenWidth, int screenHeight, HWND hwnd)
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
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &scd, &m_swapChain, &m_device, nullptr, &m_context),
        "D3D11CreateDeviceAndSwapChain ");
    // get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    ThrowIfFailed(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer), "GetBuffer");
    // create render target
    ThrowIfFailed(m_device->CreateRenderTargetView(pBackBuffer, nullptr, &m_targetView), "CreateRenderTargetView");

    pBackBuffer->Release();
    // set render target
    m_context->OMSetRenderTargets(1, &m_targetView, nullptr);
    // set view port
    D3D11_VIEWPORT viewPort;
    ZeroMemory(&viewPort, sizeof viewPort);
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    viewPort.Width = screenWidth;
    viewPort.Height = screenHeight;
    m_context->RSSetViewports(1, &viewPort);

    return true;
}
bool Render::InitPipeLine()
{
    ID3D10Blob *vs, *ps;
    ThrowIfFailed(D3DX11CompileFromFile(u8"shaders.shader", nullptr, nullptr, "VShader", "vs_4_0", 0, 0, 0, &vs, 0, 0), "D3DX11CompileFromFile");
    ThrowIfFailed(D3DX11CompileFromFile(u8"shaders.shader", nullptr, nullptr, "PShader", "ps_4_0", 0, 0, 0, &ps, 0, 0), "D3DX11CompileFromFile");
    ThrowIfFailed(m_device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &m_vs), "CreateVertexShader");
    ThrowIfFailed(m_device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &m_ps), "CreatePixelShader");
    m_context->VSSetShader(m_vs, nullptr, 0);
    m_context->PSSetShader(m_ps, nullptr, 0);

    D3D11_INPUT_ELEMENT_DESC ied[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    ThrowIfFailed(m_device->CreateInputLayout(ied, sizeof(ied) / sizeof(ied[0]), vs->GetBufferPointer(), vs->GetBufferSize(), &m_layout), "CreateInputLayout");
    m_context->IASetInputLayout(m_layout);
    return true;
}
bool Render::InitGraphics()
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
    ThrowIfFailed(m_device->CreateBuffer(&bd, nullptr, &m_vBuffer), "CreateBuffer");

    D3D11_MAPPED_SUBRESOURCE ms;
    ThrowIfFailed(m_context->Map(m_vBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms), "Map");
    memcpy(ms.pData, vertexs, sizeof vertexs);
    m_context->Unmap(m_vBuffer, 0);
    return true;
}
bool Render::render()
{
    m_context->ClearRenderTargetView(m_targetView, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_context->IASetVertexBuffers(0, 1, &m_vBuffer, &stride, &offset);
    m_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_context->Draw(3, 0);
    if (FAILED(m_swapChain->Present(0, 0)))
    {
        return false;
    }
    return true;
}

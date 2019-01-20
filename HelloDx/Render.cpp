#include "Render.h"
#include "Common.h"
struct Vertex
{
    float x, y, z;
    D3DXCOLOR color;
};

bool Render::Initialize(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    InitRefreshRate();
    InitSwapChain(hwnd, fullScreen);
    InitViewPort();
    InitDepthStencilBuffer();
    InitRaster();
    InitRenderTarget();
    InitPipeLine();
    InitGraphics();
    
    return true;
}

void Render::Shutdown()
{
    m_swapChain->SetFullscreenState(false, nullptr);
    m_vs->Release();
    m_ps->Release();
    m_layout->Release();
    m_swapChain->Release();
    m_vBuffer->Release();
    m_targetView->Release();
    m_device->Release();
    m_context->Release();
    m_depthStencilBuffer->Release();
    m_depthStencilState->Release();
    m_depthStencilView->Release();
    m_rasterState->Release();
}
void Render::InitRefreshRate()
{
    IDXGIFactory *factory;
    IDXGIAdapter *adapter;
    IDXGIOutput *adapterOutput;
    unsigned int numModes;
    DXGI_MODE_DESC *modeList;
    DXGI_ADAPTER_DESC adapterDesc;
    ThrowIfFailed(CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&factory), "CreateDXGIFactory");

    ThrowIfFailed(factory->EnumAdapters(0, &adapter), "EnumAdapters");
    ThrowIfFailed(adapter->EnumOutputs(0, &adapterOutput), "EnumOutputs");
    ThrowIfFailed(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr), "");
    modeList = new DXGI_MODE_DESC[numModes];
    ThrowIfFailed(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, modeList), "");
    for (int i = 0; i < numModes; ++i)
    {
        if (modeList[i].Width == m_screenWidth && modeList[i].Height == m_screenHeight)
        {
            m_numerator = modeList[i].RefreshRate.Numerator;
            m_denominator = modeList[i].RefreshRate.Denominator;
            break;
        }
    }
    ThrowIfFailed(adapter->GetDesc(&adapterDesc), "GetDesc");
    m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
    size_t strLen = 0;
    wcstombs_s(&strLen, m_videoCardDescription, 128, adapterDesc.Description, 128);
    delete[] modeList;
    modeList = nullptr;
    adapterOutput->Release();
    factory->Release();
}
void Render::InitDepthStencilBuffer()
{
    // depth buffer
    D3D11_TEXTURE2D_DESC depthBufferDesc;
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;


    ZeroMemory(&depthBufferDesc, sizeof depthBufferDesc);
    depthBufferDesc.Width = m_screenWidth;
    depthBufferDesc.Height = m_screenHeight;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;
    ThrowIfFailed(m_device->CreateTexture2D(&depthBufferDesc, nullptr, &m_depthStencilBuffer), "CreateTexture2D");

    ZeroMemory(&depthStencilDesc, sizeof depthStencilDesc);
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    ThrowIfFailed(m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState), "CreateDepthStencilState");
    m_context->OMSetDepthStencilState(m_depthStencilState, 1);

    ZeroMemory(&depthStencilViewDesc, sizeof depthStencilViewDesc);
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    ThrowIfFailed(m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView), "CreateDepthStencilView");
}
void Render::InitSwapChain(HWND hwnd, bool fullScreen)
{
    // Direct3D init
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof swapChainDesc);
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = m_screenWidth;
    swapChainDesc.BufferDesc.Height = m_screenHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    if (m_vsyncEnabled)
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = m_numerator;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = m_denominator;
    }
    else
    {
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    }
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.SampleDesc.Count = 8;
    swapChainDesc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
    swapChainDesc.Windowed = !fullScreen;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    ThrowIfFailed(
        D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, nullptr, &m_context),
        "D3D11CreateDeviceAndSwapChain ");
}
void Render::InitRenderTarget()
{
    // get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    ThrowIfFailed(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer), "GetBuffer");
    // create render target
    ThrowIfFailed(m_device->CreateRenderTargetView(pBackBuffer, nullptr, &m_targetView), "CreateRenderTargetView");

    pBackBuffer->Release();
    // set render target
    m_context->OMSetRenderTargets(1, &m_targetView, m_depthStencilView);
}
void Render::InitRaster()
{
    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof rasterDesc);

    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;
    ThrowIfFailed(m_device->CreateRasterizerState(&rasterDesc, &m_rasterState), "CreateRasterizerState");
    m_context->RSSetState(m_rasterState);
}
void Render::InitViewPort()
{
    // set view port
    D3D11_VIEWPORT viewPort;
    ZeroMemory(&viewPort, sizeof viewPort);
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;
    viewPort.Width = m_screenWidth;
    viewPort.Height = m_screenHeight;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    m_context->RSSetViewports(1, &viewPort);
}
void Render::InitPipeLine()
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
}
void Render::InitGraphics()
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


    float fieldOfView = (float)D3DX_PI / 4.0f;
    float screenAspect = (float)m_screenWidth / m_screenHeight;
    float screenNear = 0.1f;
    float screenFar = 1000.0f;
    D3DXMatrixPerspectiveFovLH(&m_projectMat, fieldOfView, screenAspect, screenNear, screenNear);
    D3DXMatrixIdentity(&m_worldMat);
    D3DXMatrixOrthoLH(&m_orthoMat, (float)m_screenWidth, (float)m_screenHeight, screenNear, screenFar);
}
bool Render::render()
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_context->IASetVertexBuffers(0, 1, &m_vBuffer, &stride, &offset);
    m_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_context->Draw(3, 0);
    return true;
}
void Render::BeginScene(float r, float g, float b, float a) 
{
    float color[4];
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;

    m_context->ClearRenderTargetView(m_targetView, color);
    m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void Render::EndScene() 
{
    if (m_vsyncEnabled)
    {
        m_swapChain->Present(1, 0);
    }
    else
    {
        m_swapChain->Present(0, 0);
    }
}

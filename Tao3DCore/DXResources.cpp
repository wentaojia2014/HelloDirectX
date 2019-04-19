#include "DXResources.h"
#include "Common.h"
namespace Tao3D
{
    bool DXResources::init(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen)
    {
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;
        initRefreshRate();
        initSwapChain(hwnd, fullScreen);
        initDepthStencilBuffer();
        initRenderTarget();
        initRaster();
        initViewPort();
        initMatrix();
        initBlend();
        return true;
    }
    void DXResources::uninit()
    {
        m_swapChain->SetFullscreenState(false, nullptr);
    }
    void DXResources::setClearColor(float r, float g, float b, float a)
    {
        m_clearColor[0] = r;
        m_clearColor[1] = g;
        m_clearColor[2] = b;
        m_clearColor[3] = a;
    }
    void DXResources::beginScene()
    {
        m_context->ClearRenderTargetView(m_targetView.Get(), m_clearColor);
        m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    }
    void DXResources::endScene()
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
    void DXResources::turnZBufferOn()
    {
        m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);
    }
    void DXResources::turnZBufferOff()
    {
        m_context->OMSetDepthStencilState(m_depthDisabledStencilState.Get(), 1);
    }
    void DXResources::turnAlphaBlendingOn()
    {
        float blendFactor[4] = { 0 };
        m_context->OMSetBlendState(m_alphaEnabledBlendingState.Get(), blendFactor, 0xffffffff);
    }
    void DXResources::turnAlphaBlendingOff()
    {
        float blendFactor[4] = { 0 };
        m_context->OMSetBlendState(m_alphaDisabledBlendingState.Get(), blendFactor, 0xffffffff);
    }
    void DXResources::initSwapChain(HWND hwnd, bool fullScreen)
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
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
        swapChainDesc.Windowed = !fullScreen;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
        UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        ThrowIfFailed(
            D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                creationFlags,
                &featureLevel,
                1,
                D3D11_SDK_VERSION,
                &swapChainDesc,
                m_swapChain.GetAddressOf(),
                m_device.GetAddressOf(),
                nullptr,
                m_context.GetAddressOf()),
            "D3D11CreateDeviceAndSwapChain ");
    }
    void DXResources::initMatrix()
    {
        float fieldOfView = static_cast<float>(XM_PI) / 4.0f;
        float screenAspect = static_cast<float>(m_screenWidth) / m_screenHeight;
        float screenNear = 0.1f;
        float screenFar = 1000.0f;
        m_projection = Matrix::CreatePerspectiveFieldOfView(fieldOfView, screenAspect, screenNear, screenFar);
        m_world = Matrix::Identity;
        m_ortho = Matrix::CreateOrthographic(static_cast<float>(m_screenWidth), static_cast<float>(m_screenHeight), screenNear, screenFar);
    }
    void DXResources::initRefreshRate()
    {
        ComPtr<IDXGIFactory> factory = nullptr;
        ComPtr < IDXGIAdapter> adapter = nullptr;
        ComPtr < IDXGIOutput> adapterOutput = nullptr;

        unsigned int numModes = 0;
        DXGI_MODE_DESC *modeList;
        DXGI_ADAPTER_DESC adapterDesc;
        ThrowIfFailed(CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)factory.GetAddressOf()), "CreateDXGIFactory");

        ThrowIfFailed(factory->EnumAdapters(0, adapter.GetAddressOf()), "EnumAdapters");
        ThrowIfFailed(adapter->EnumOutputs(0, adapterOutput.GetAddressOf()), "EnumOutputs");
        ThrowIfFailed(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr), "GetDisplayModeList");
        modeList = new DXGI_MODE_DESC[numModes];
        ThrowIfFailed(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, modeList), "GetDisplayModeList");
        for (unsigned int i = 0; i < numModes; ++i)
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
    }
    void DXResources::initDepthStencilBuffer()
    {
        // depth buffer
        D3D11_TEXTURE2D_DESC depthBufferDesc;
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

        ZeroMemory(&depthBufferDesc, sizeof depthBufferDesc);
        depthBufferDesc.Width = m_screenWidth;
        depthBufferDesc.Height = m_screenHeight;
        depthBufferDesc.MipLevels = 1;
        depthBufferDesc.ArraySize = 1;
        depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthBufferDesc.SampleDesc.Count = 1;
        depthBufferDesc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;
        depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        ThrowIfFailed(m_device->CreateTexture2D(&depthBufferDesc, nullptr, m_depthStencilBuffer.GetAddressOf()), "CreateTexture2D");

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
        ThrowIfFailed(m_device->CreateDepthStencilState(&depthStencilDesc, m_depthStencilState.GetAddressOf()), "CreateDepthStencilState");
        m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 1);

        ZeroMemory(&depthStencilViewDesc, sizeof depthStencilViewDesc);
        depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

        ThrowIfFailed(m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), &depthStencilViewDesc, m_depthStencilView.GetAddressOf()), "CreateDepthStencilView");


        depthDisabledStencilDesc.DepthEnable = false;
        depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

        depthDisabledStencilDesc.StencilEnable = true;
        depthDisabledStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
        depthDisabledStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
        depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

        depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
        depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
        ThrowIfFailed(m_device->CreateDepthStencilState(&depthDisabledStencilDesc, m_depthDisabledStencilState.GetAddressOf()), "CreateDepthStencilState");

    }
    void DXResources::initRaster()
    {
        D3D11_RASTERIZER_DESC rasterDesc;
        ZeroMemory(&rasterDesc, sizeof rasterDesc);

        rasterDesc.AntialiasedLineEnable = false;
        rasterDesc.CullMode = D3D11_CULL_BACK;
        rasterDesc.DepthClipEnable = true;
        rasterDesc.FillMode = D3D11_FILL_SOLID;
        rasterDesc.FrontCounterClockwise = false;
        rasterDesc.MultisampleEnable = false;
        rasterDesc.ScissorEnable = false;
        ThrowIfFailed(m_device->CreateRasterizerState(&rasterDesc, m_rasterState.GetAddressOf()), "CreateRasterizerState");
        m_context->RSSetState(m_rasterState.Get());
    }
    void DXResources::initRenderTarget()
    {
        // get the address of the back buffer

        ThrowIfFailed(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)(m_backBuffer.GetAddressOf())), "GetBuffer");
        // create render target
        ThrowIfFailed(m_device->CreateRenderTargetView(m_backBuffer.Get(), nullptr, m_targetView.GetAddressOf()), "CreateRenderTargetView");

        // set render target
        m_context->OMSetRenderTargets(1, m_targetView.GetAddressOf(), m_depthStencilView.Get());

    }
    void DXResources::initViewPort()
    {
        // set view port
        D3D11_VIEWPORT viewPort;
        ZeroMemory(&viewPort, sizeof viewPort);
        viewPort.TopLeftX = 0;
        viewPort.TopLeftY = 0;
        viewPort.Width = static_cast<float>(m_screenWidth);
        viewPort.Height = static_cast<float>(m_screenHeight);
        viewPort.MinDepth = 0.0f;
        viewPort.MaxDepth = 1.0f;
        m_context->RSSetViewports(1, &viewPort);

    }
    void DXResources::initBlend()
    {
        D3D11_BLEND_DESC blendDesc = { 0 };
        blendDesc.RenderTarget[0].BlendEnable = true;
        blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
        blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

        ThrowIfFailed(m_device->CreateBlendState(&blendDesc, m_alphaEnabledBlendingState.GetAddressOf()), "CreateBlendState");

        blendDesc.RenderTarget[0].BlendEnable = false;
        ThrowIfFailed(m_device->CreateBlendState(&blendDesc, m_alphaDisabledBlendingState.GetAddressOf()), "CreateBlendState");

    }
}
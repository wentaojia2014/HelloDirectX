#include "System.h"

static System *D3DAPP = nullptr;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            return 0;
        }
        default:
            return D3DAPP->Messagehandler(hwnd, message, wparam, lparam);
    }
}
System::System() {}

System::~System() {}

System::System(System &&) {}

System::System(const System &) {}

bool System::Initialize(LPSTR lpCmd, int nShowCmd)
{
    (void)lpCmd;

    int w = 1024;
    int h = 768;
    
    InitializeWindow(w, h, nShowCmd);
    m_input = new Input();
    if (!m_input)
    {
        return false;
    }
    m_input->Initialize();

    m_graphics = new Graphics();
    if (!m_graphics)
    {
        return false;
    }
    return m_graphics->Initialize(w, h, m_hwnd);
}

void System::Shutdown()
{
    if (m_graphics)
    {
        m_graphics->Shutdown();
        delete m_graphics;
        m_graphics = nullptr;
    }
    if (m_input)
    {
        delete m_input;
        m_input = nullptr;
    }
    this->ShutdownWindow();
}

void System::Run()
{
    MSG msg = { 0 };
    bool done = false;
    bool result = false;
    while (!done)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                done = true;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            result = Frame();
            if (!result)
            {
                done = true;
            }
        }
    }
}

bool System::Frame()
{
    if (m_input->IsKeyDown(VK_ESCAPE))
    {
        return false;
    }
    return m_graphics->Frame();
}

void System::InitializeWindow(int w, int h, int nShowCmd)
{
    WNDCLASSEX wc;
    DEVMODE dmScreenSettings;
    int posX, posY;
    D3DAPP = this;
    ZeroMemory(&wc, sizeof wc);
    m_hInstance = GetModuleHandle(nullptr);
    m_applicationName = "Engine";

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = m_hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = m_applicationName;
    wc.cbSize = sizeof wc;

    RegisterClassEx(&wc);
    unsigned long screenW = GetSystemMetrics(SM_CXSCREEN);
    unsigned long screenH = GetSystemMetrics(SM_CYSCREEN);
    if (m_fullScreen)
    {
        w = screenW;
        h = screenH;

        memset(&dmScreenSettings, 0, sizeof dmScreenSettings);
        dmScreenSettings.dmSize = sizeof dmScreenSettings;
        dmScreenSettings.dmPelsWidth = (unsigned long)w;
        dmScreenSettings.dmPelsHeight = (unsigned long)h;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

        posX = posY = 0;
    }
    else
    {
        posX = (screenW - w) / 2;
        posY = (screenH - h) / 2;
    }
    RECT rect = { 0, 0, w, h };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    m_hwnd = CreateWindowEx(
        0,
        m_applicationName,
        m_applicationName,
        WS_OVERLAPPEDWINDOW,
        posX,
        posY,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        m_hInstance,
        nullptr);

    ShowWindow(m_hwnd, nShowCmd);
    //SetForegroundWindow(mHwnd);
    //SetFocus(mHwnd);
}

void System::ShutdownWindow()
{
    if (m_fullScreen)
    {
        ChangeDisplaySettings(nullptr, 0);
    }
    DestroyWindow(m_hwnd);
    m_hwnd = nullptr;

    UnregisterClass(m_applicationName, m_hInstance);
    m_hInstance = nullptr;

    D3DAPP = nullptr;
}

LRESULT
System::Messagehandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            m_input->KeyDown((unsigned int)wparam);
            return 0;
        }
        case WM_KEYUP:
        {
            m_input->KeyRelease((unsigned int)wparam);
            return 0;
        }
		
        default:
        {
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
    }
    return LRESULT();
}

#include "stdafx.h"

#include "System.h"
#include "../Common/Common.h"

#include <cassert>
namespace Tao3D
{
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
System::System(IInput *input, IGraphics *graphics) : m_input(input), m_graphics(graphics) 
{
    assert(input);
    assert(graphics);
}

System::~System() {}

bool System::Init(LPSTR lpCmd, int nShowCmd, int width, int height)
{
    (void)lpCmd;

    InitializeWindow(width, height, nShowCmd);
    
    if (!m_input->Init()) 
    {
        return false;
    }

    return m_graphics->Init(width, height, m_hwnd, m_fullScreen);
}

void System::Uninit()
{
    ShutdownWindow();
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
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (msg.message == WM_QUIT)
        {
            done = true;
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
    WNDCLASSEX wc = { 0 };
    DEVMODE dmScreenSettings;
    int posX, posY;

    D3DAPP = this;

    m_hInstance = GetModuleHandle(nullptr);
    m_applicationName = "Engine";

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m_hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = m_applicationName;
    wc.cbSize = sizeof wc;

    RegisterClassEx(&wc);

    unsigned long screenW = GetSystemMetrics(SM_CXSCREEN);
    unsigned long screenH = GetSystemMetrics(SM_CYSCREEN);
    if (m_fullScreen)
    {
        w = screenW;
        h = screenH;

        ZeroMemory(&dmScreenSettings, sizeof dmScreenSettings);
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
    // SetForegroundWindow(mHwnd);
    // SetFocus(mHwnd);
}

void System::ShutdownWindow()
{
    ShowCursor(true);
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
            m_input->KeyDown((uint32_t)wparam);
            return 0;
        }
        case WM_KEYUP:
        {
            m_input->KeyUp((uint32_t)wparam);
            return 0;
        }

        default:
        {
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
    }
    return LRESULT();
}
} // namespace Tao3D

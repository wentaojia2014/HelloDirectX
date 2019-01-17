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

bool System::Initialize()
{
    int w = 1024;
    int h = 768;

    InitializeWindow(w, h);
    mInput = new Input();
    if (!mInput)
    {
        return false;
    }
    mInput->Initialize();

    mGraphics = new Graphics();
    if (!mGraphics)
    {
        return false;
    }
    return mGraphics->Initialize(w, h, mHwnd);
}

void System::Shutdown()
{
    if (mGraphics)
    {
        mGraphics->Shutdown();
        delete mGraphics;
        mGraphics = nullptr;
    }
    if (mInput)
    {
        delete mInput;
        mInput = nullptr;
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
    if (mInput->IsKeyDown(VK_ESCAPE))
    {
        return false;
    }
    return mGraphics->Frame();
}

void System::InitializeWindow(int &w, int &h)
{
    WNDCLASSEX wc;
    DEVMODE dmScreenSettings;
    int posX, posY;
    D3DAPP = this;
    mHinstance = GetModuleHandle(nullptr);
    mApplicationName = "Engine";
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = mHinstance;
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = mApplicationName;
    wc.cbSize = sizeof(WNDCLASSEX);

    RegisterClassEx(&wc);

    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    if (FULL_SCREEN)
    {
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
        w = 800;
        h = 600;

        posX = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        posY = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
    }
    RECT rect = { 0, 0, w, h };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    mHwnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName, WS_OVERLAPPEDWINDOW, posX, posY, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, mHinstance, nullptr);

    ShowWindow(mHwnd, SW_SHOW);
    SetForegroundWindow(mHwnd);
    SetFocus(mHwnd);
}

void System::ShutdownWindow()
{
    if (FULL_SCREEN)
    {
        ChangeDisplaySettings(nullptr, 0);
    }
    DestroyWindow(mHwnd);
    mHwnd = nullptr;

    UnregisterClass(mApplicationName, mHinstance);
    mHinstance = nullptr;

    D3DAPP = nullptr;
}

LRESULT
System::Messagehandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
        case WM_KEYDOWN:
        {
            mInput->KeyDown((unsigned int)wparam);
            return 0;
        }
        case WM_KEYUP:
        {
            mInput->KeyRelease((unsigned int)wparam);
            return 0;
        }
        default:
        {
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
    }
    return LRESULT();
}

#include "MainWindow.h"
#include "Application.h"
namespace Tao3D
{
LRESULT CALLBACK MainWindow::MessageRouter(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    MainWindow *me = (MainWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (me == nullptr)
    {
        if (message == WM_CREATE)
        {
            me = static_cast<MainWindow *>(((LPCREATESTRUCT)lparam)->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)me);
        }
        else
        {
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
    }
    return me->messageHandler(hwnd, message, wparam, lparam);
}
MainWindow::MainWindow() 
{
}
MainWindow::~MainWindow() {}
void MainWindow::init(int width, int height, LPCSTR title, bool fullScreen)
{
    m_w = width;
    m_h = height;
    m_title = title;
    m_fullScreen = fullScreen;

    WNDCLASSEX wc = { 0 };
    DEVMODE dmScreenSettings;
    int posX, posY;
    m_hInstance = GetModuleHandle(nullptr);
    m_applicationName = title;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MessageRouter;
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
        width = screenW;
        height = screenH;

        ZeroMemory(&dmScreenSettings, sizeof dmScreenSettings);
        dmScreenSettings.dmSize = sizeof dmScreenSettings;
        dmScreenSettings.dmPelsWidth = (unsigned long)width;
        dmScreenSettings.dmPelsHeight = (unsigned long)height;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

        posX = posY = 0;
    }
    else
    {
        posX = (screenW - width) / 2;
        posY = (screenH - height) / 2;
    }
    RECT rect = { 0, 0, width, height };
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
        this);
}
LRESULT MainWindow::messageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message)
    {
        case WM_CLOSE:
        {
            if (m_fullScreen)
            {
                ChangeDisplaySettings(nullptr, 0);
            }
            DestroyWindow(m_hwnd);
            m_hwnd = nullptr;
            UnregisterClass(m_applicationName, m_hInstance);
            m_hInstance = nullptr;
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_ACTIVATEAPP:
            DirectX::Keyboard::ProcessMessage(message, wparam, lparam);
            DirectX::Mouse::ProcessMessage(message, wparam, lparam);
            break;
        case WM_INPUT:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        case WM_MOUSEHOVER:
            DirectX::Mouse::ProcessMessage(message, wparam, lparam);
            break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            DirectX::Keyboard::ProcessMessage(message, wparam, lparam);
            break;
        default:
        {
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
    }
    return 0;
}
void MainWindow::resize(int width, int height) {}
void MainWindow::showFullScreen()
{
    ShowWindow(m_hwnd, SHOW_FULLSCREEN);
}
void MainWindow::show()
{
    ShowWindow(m_hwnd, SHOW_OPENWINDOW);
}
void MainWindow::hide()
{
    ShowWindow(m_hwnd, HIDE_WINDOW);
}

} // namespace Tao3D

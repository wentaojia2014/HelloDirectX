#include "MainWindow.h"
#include "Application.h"
namespace Tao3D
{
static MainWindow *pMainWindow = nullptr;
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
            return pMainWindow->messageHandler(hwnd, message, wparam, lparam);
    }
}
MainWindow::MainWindow(int w, int h, LPCSTR title, bool fullScreen) : m_w(w), m_h(h), m_title(title), m_fullScreen(fullScreen)
{
    pMainWindow = this;
    WNDCLASSEX wc = { 0 };
    DEVMODE dmScreenSettings;
    int posX, posY;
    m_hInstance = GetModuleHandle(nullptr);
    m_applicationName = title;

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

}
MainWindow::~MainWindow() 
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
}
LRESULT MainWindow::messageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) 
{
    switch (message)
    {
        case WM_KEYDOWN:
        {

            return 0;
        }
        case WM_KEYUP:
        {

            return 0;
        }

        default:
        {
            return DefWindowProc(hwnd, message, wparam, lparam);
        }
    }
    return 0;
}
void MainWindow::resize(int width, int height) 
{

}
void MainWindow::showFullScreen() 
{

}
void MainWindow::show() 
{
    ShowWindow(m_hwnd, SHOW_OPENWINDOW);
    UpdateWindow(m_hwnd);
}
void MainWindow::hide() 
{
    ShowWindow(m_hwnd, HIDE_WINDOW);
}
bool MainWindow::frame() 
{
    return true;
}
} // namespace Tao3D
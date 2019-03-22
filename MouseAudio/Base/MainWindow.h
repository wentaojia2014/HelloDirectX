#pragma once
#include "IWindow.h"
#include <string>
namespace Tao3D
{
class MainWindow : public IWindow
{
public:
    MainWindow(int width, int height, LPCSTR title, bool fullScreen = false);
    ~MainWindow();
    LRESULT messageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) override;
    void resize(int width, int height) override;
    void showFullScreen() override;
    void show() override;
    void hide() override;
    bool frame() override;

private:
    int m_w;
    int m_h;
    LPCSTR m_title;
    bool m_fullScreen = false;
    LPCSTR m_applicationName;
    HINSTANCE m_hInstance;
    HWND m_hwnd;
};
} // namespace Tao3D
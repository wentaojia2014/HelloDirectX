#pragma once
#include <Windows.h>
namespace Tao3D
{
class IWindow
{
public:
    IWindow() {}
    virtual void init(int width, int height, LPCSTR title, bool fullScreen = false) = 0;
    virtual LRESULT messageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) = 0;
    virtual void resize(int width, int height) = 0;
    virtual void showFullScreen() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool frame() = 0;
    virtual HWND getHwnd() const = 0;
public:
    virtual ~IWindow() {}
};
} // namespace Tao3D
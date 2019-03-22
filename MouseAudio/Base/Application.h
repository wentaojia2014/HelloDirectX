#pragma once
#include "IWindow.h"
#include <Windows.h>
namespace Tao3D
{
#define gApp (Application::Instance())

class Application
{
public:
    Application();
    static Application &Instance()
    {
        return *self;
    }
    void setWindow(IWindow *window);
    IWindow *getWindow() const 
    {
        return pWindow;
    }
    void exec();

private:
    static Application *self;
    IWindow *pWindow = nullptr;
};

} // namespace Tao3D
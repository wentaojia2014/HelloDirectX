#include "Application.h"
#include <cassert>
namespace Tao3D
{
Application *Application::self = nullptr;

Application::Application()
{
    self = this;
}
void Application::init(int width, int height, LPCSTR title, bool fullScreen)
{
    pWindow->init(width, height, title, fullScreen);
    m_resources.init(width, height, pWindow->getHwnd(), fullScreen);
    m_mouse.SetWindow(pWindow->getHwnd());
}
void Application::setWindow(IWindow *window)
{
    pWindow = window;
}
void Application::exec()
{
    assert(pWindow != nullptr);

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
            result = pWindow->frame();
            if (!result)
            {
                done = true;
            }
        }
    }
}
} // namespace Tao3D
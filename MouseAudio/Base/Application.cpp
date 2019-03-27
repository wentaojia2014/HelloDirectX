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
    m_pWindow->init(width, height, title, fullScreen);
    m_resources.init(width, height, m_pWindow->getHwnd(), fullScreen);
    m_pRender->init(width, height);
    m_mouse.SetWindow(m_pWindow->getHwnd());
}
void Application::setWindow(IWindow *window)
{
    m_pWindow = window;
}
void Application::setRender(IRender *render)
{
    m_pRender = render;
}
void Application::exec()
{
    assert(m_pWindow != nullptr);

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
            m_pRender->update();
            result = m_pRender->render();
            if (!result)
            {
                done = true;
            }
        }
    }
}
void Application::quit()
{
    PostQuitMessage(0);
}
} // namespace Tao3D
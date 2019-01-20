#pragma once
#include "Graphics.h"
#include "Input.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
namespace TaoD3D
{
class System
{
public:
    System();
    ~System();
    System(System &&);
    System(const System &);
    bool Initialize(LPSTR lpCmd, int nShowCmd);
    void Shutdown();
    void Run();
    LRESULT CALLBACK Messagehandler(HWND hwnd, UINT message, WPARAM param, LPARAM lparam);

private:
    bool Frame();
    void InitializeWindow(int w, int h, int nShowCmd);
    void ShutdownWindow();

private:
    LPCSTR m_applicationName;
    HINSTANCE m_hInstance;
    HWND m_hwnd;

    Input *m_input = nullptr;
    Graphics *m_graphics = nullptr;
    bool m_fullScreen = false;
};
} // namespace TaoD3D

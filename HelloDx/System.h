#pragma once
#include "Graphics.h"
#include "Input.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

class System
{
public:
    System();
    ~System();
    System(System &&);
    System(const System &);
    bool    Initialize();
    void    Shutdown();
    void    Run();
    LRESULT CALLBACK
            Messagehandler(HWND hwnd, UINT message, WPARAM param, LPARAM lparam);

private:
    bool Frame();
    void InitializeWindow(int &w, int &h);
    void ShutdownWindow();

private:
    LPCSTR    mApplicationName;
    HINSTANCE mHinstance;
    HWND      mHwnd;

    Input *   mInput    = nullptr;
    Graphics *mGraphics = nullptr;
};

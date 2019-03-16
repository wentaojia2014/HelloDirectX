#pragma once

#include "../Tao3DGlobal.h"

#include "../Interface/IGraphics.h"
#include "../Interface/IInput.h"
#include "../Interface/ISystem.h"

namespace Tao3D
{
    
class Tao3DAPI System : public ISystem
{
public:
    System(IInput *input, IGraphics *graphics);
    ~System();
    
    bool Init(LPSTR lpCmd, int nShowCmd, int width, int height) override;
    void Uninit() override;
    void Run() override;

    LRESULT CALLBACK Messagehandler(HWND hwnd, UINT message, WPARAM param, LPARAM lparam);

private:
    bool Frame();
    void InitializeWindow(int w, int h, int nShowCmd);
    void ShutdownWindow();

private:
    LPCSTR m_applicationName;
    HINSTANCE m_hInstance;
    HWND m_hwnd;

    IInput *m_input = nullptr;
    IGraphics *m_graphics = nullptr;
    bool m_fullScreen = false;
};
} // namespace Tao3D

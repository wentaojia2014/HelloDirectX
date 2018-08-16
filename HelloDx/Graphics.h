#pragma once
#include <Windows.h>
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLE = true;
const float SCREEN_DEPTH = 1000.0;
const float SCREEN_NEAR = 0.1f;

class Graphics {
public:
    Graphics ();
    ~Graphics ();
    Graphics (const Graphics &);
    Graphics (Graphics &&);

    bool Initialize (int screenWidth, int screenHeight, HWND hwnd);
    void Shutdown ();
    bool Frame ();
private:
    bool Render ();
};


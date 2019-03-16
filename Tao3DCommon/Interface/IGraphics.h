#pragma once
#include <Windows.h>
#include "../Tao3DGlobal.h"
class Tao3DAPI IGraphics
{
public: 
    virtual bool Init(int screenWidth, int screenHeight, HWND hwnd, bool fullScreen) = 0;
    
    virtual void Uninit() = 0;

    virtual bool Frame() = 0;
public: 
    virtual ~IGraphics() {}
};
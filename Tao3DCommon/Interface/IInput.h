#pragma once

#include "../Tao3DGlobal.h"
class Tao3DAPI IInput
{
public: 
    virtual bool Init() = 0;
    
    virtual void Uninit() = 0;

    virtual void KeyDown(uint32_t key) = 0;

    virtual void KeyUp(uint32_t key) = 0;
    
    virtual bool IsKeyDown(uint32_t key) = 0;
public: 
    virtual ~IInput() {}
};
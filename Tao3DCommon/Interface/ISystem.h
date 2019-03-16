#pragma once
#include "../Tao3DGlobal.h"
class Tao3DAPI ISystem 
{
public: 
    virtual bool Init(LPSTR lpCmd, int nShowCmd, int width, int height) = 0;
    
    virtual void Uninit() = 0;

    virtual void Run() = 0;

public: 
    virtual ~ISystem() {}
};
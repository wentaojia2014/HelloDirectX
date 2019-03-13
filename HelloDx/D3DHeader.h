#pragma once

#include <Windows.h>

#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <D3D11.h>

#include <DirectXMath.h>
//#include <DirectXCollision.h>
// #include <DirectXColors.h>
// #include <DirectXPackedVector.h>
#include <d3dcompiler.h>
#include <DXGI.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment( lib, "dxguid.lib")

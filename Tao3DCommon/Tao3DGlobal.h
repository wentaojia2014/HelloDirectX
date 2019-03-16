#pragma once

#ifdef Tao3DCommon_LIBRARY
#define Tao3DAPI __declspec(dllexport)
#else 
#define Tao3DAPI __declspec(dllimport)
#endif

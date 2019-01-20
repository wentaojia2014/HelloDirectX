#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "System.h"
using namespace TaoD3D;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nShowCmd)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    System s;
    if (s.Initialize(lpCmd, nShowCmd))
    {
        s.Run();
    }
    s.Shutdown();
    return 0;
}

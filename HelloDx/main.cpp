#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Tao3DCommon.h"
#include "Graphics.h"
using namespace Tao3D;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nShowCmd)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Input input;
    Graphics graph;
    System s(&input, &graph);
    if (s.Init(lpCmd, nShowCmd, 800, 600))
    {
        s.Run();
    }
    s.Uninit();
    return 0;
}

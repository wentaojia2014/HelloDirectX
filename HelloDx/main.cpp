#define _CRTDBG_MAP_ALLOC
#include <Windows.h>
#include <crtdbg.h>
#include <windowsx.h>
LRESULT CALLBACK WindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nShowCmd)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    OutputDebugString(lpCmd);
    auto t = MessageBox(nullptr, lpCmd, "HeHe", MB_ICONEXCLAMATION | MB_OK);
    // window handle, filled by a function
    HWND hWnd;
    // this struct hold information for the window class info
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof wc);

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = u8"WindowClass1";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL, u8"WindowClass1", u8"Hello Window", WS_OVERLAPPEDWINDOW, 300, 200, 500, 400, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hWnd, nShowCmd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

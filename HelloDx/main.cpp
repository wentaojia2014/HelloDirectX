#include "System.h"
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmd, int nShowCmd) {
    System *s = new System ();
    if (!s) {
        return 0;
    }
    if (s->Initialize ()) {
        s->Run ();
    }
    s->Shutdown ();
    delete s;
    s = nullptr;
    return 0;
}

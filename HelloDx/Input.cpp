#include "Input.h"

Input::Input() {}

Input::Input(const Input &) {}

Input::Input(Input &&) {}

Input::~Input() {}

void Input::Initialize()
{
    for (int i = 0; i < KEY_COUNT; ++i)
    {
        mKey[i] = false;
    }
}

void Input::KeyDown(unsigned int wParam)
{
    mKey[wParam] = true;
}

void Input::KeyRelease(unsigned int wParam)
{
    mKey[wParam] = false;
}

bool Input::IsKeyDown(unsigned int wParam)
{
    return mKey[wParam];
}

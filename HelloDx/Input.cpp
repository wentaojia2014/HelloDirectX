#include "Input.h"

Input::Input() {}

Input::Input(const Input &) {}

Input::Input(Input &&) {}

Input::~Input() {}

void Input::Initialize()
{
    for (int i = 0; i < KEY_COUNT; ++i)
    {
        m_key[i] = false;
    }
}

void Input::KeyDown(unsigned int wParam)
{
    m_key[wParam] = true;
}

void Input::KeyRelease(unsigned int wParam)
{
    m_key[wParam] = false;
}

bool Input::IsKeyDown(unsigned int wParam)
{
    return m_key[wParam];
}

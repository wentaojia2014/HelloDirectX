#include "stdafx.h"

#include "Input.h"

namespace Tao3D
{
Input::Input() {}

Input::~Input() {}

bool Input::Init()
{
    for (int i = 0; i < KEY_COUNT; ++i)
    {
        m_key[i] = false;
    }
    return true;
}
void Input::KeyDown(uint32_t key)
{
    m_key[key] = true;
}

void Input::KeyUp(uint32_t key)
{
    m_key[key] = false;
}

bool Input::IsKeyDown(uint32_t key)
{
    return m_key[key];
}
} // namespace Tao3D

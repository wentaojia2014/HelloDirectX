#pragma once
#include "../Interface/IInput.h"
#include "../Tao3DGlobal.h"

namespace Tao3D
{
static const int KEY_COUNT = 256;
class Tao3DAPI Input : public IInput
{
public:
    Input();
    ~Input();

    bool Init() override;

    void Uninit() override {}

    void KeyDown(uint32_t key) override;

    void KeyUp(uint32_t key) override;

    bool IsKeyDown(uint32_t key) override;

private:
    bool m_key[KEY_COUNT];
};
} // namespace Tao3D

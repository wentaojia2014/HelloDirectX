#pragma once
namespace TaoD3D
{
static const int KEY_COUNT = 256;
class Input
{
public:
    Input();
    Input(const Input &);
    Input(Input &&);
    ~Input();
    void Initialize();
    void KeyDown(unsigned int wParam);
    void KeyRelease(unsigned int wParam);
    bool IsKeyDown(unsigned int wParam);

private:
    bool m_key[KEY_COUNT];
};
} // namespace TaoD3D

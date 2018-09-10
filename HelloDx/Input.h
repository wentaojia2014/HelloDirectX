#pragma once

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
    bool mKey[KEY_COUNT];
};

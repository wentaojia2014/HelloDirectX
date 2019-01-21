#pragma once
#include "D3DHeader.h"
namespace TaoD3D
{
class Texture
{
public:
    bool Initialize(ID3D11Device *device, const char *textureFile);
    void Shutdown();
    ID3D11ShaderResourceView *GetTexture();

private:
    ID3D11ShaderResourceView *m_texture = nullptr;
};
} // namespace TaoD3D

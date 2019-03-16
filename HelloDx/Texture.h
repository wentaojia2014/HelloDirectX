#pragma once
#include "D3DHeader.h"
namespace Tao3D
{
using Microsoft::WRL::ComPtr;
class Texture
{
public:
    bool Initialize(ID3D11Device *device, ID3D11DeviceContext *context, LPCWSTR textureFile);
    void Shutdown();
    ID3D11ShaderResourceView *GetTexture();

private:
    ComPtr<ID3D11ShaderResourceView> m_texture = nullptr;
};
} // namespace Tao3D

#include "Texture.h"

#include "Common.h"

namespace TaoD3D
{
bool Texture::Initialize(ID3D11Device *device, const char *textureFile)
{
    HRESULT re;
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(device, textureFile, nullptr, nullptr, &m_texture, &re)))
	{
        OutputDebugString("failed to load texture\n");
        return false;
	}
    return true;
}
void Texture::Shutdown()
{
    SafeRelease(m_texture);
}
ID3D11ShaderResourceView *Texture::GetTexture()
{
    return m_texture;
}
} // namespace TaoD3D

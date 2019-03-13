#include "Texture.h"

#include "Common.h"
#include "WICTextureLoader.h"
namespace TaoD3D
{
bool Texture::Initialize(ID3D11Device *device, ID3D11DeviceContext *context, LPCWSTR textureFile)
{
	if (FAILED(CreateWICTextureFromFile(device, context, textureFile, nullptr, &m_texture)))
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

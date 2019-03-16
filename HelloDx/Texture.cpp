#include "Texture.h"

#include "Common.h"
#include <DirectXTK/WICTextureLoader.h>
namespace TaoD3D
{
using namespace DirectX;
bool Texture::Initialize(ID3D11Device *device, ID3D11DeviceContext *context, LPCWSTR textureFile)
{
	if (FAILED(CreateWICTextureFromFile(device, context, textureFile, nullptr, m_texture.GetAddressOf())))
	{
        OutputDebugString("failed to load texture\n");
        return false;
	}
    return true;
}
void Texture::Shutdown()
{
}
ID3D11ShaderResourceView *Texture::GetTexture()
{
    return m_texture.Get();
}
} // namespace TaoD3D

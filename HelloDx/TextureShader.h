#pragma once
#include "D3DHeader.h"

namespace TaoD3D
{
struct MatBuffer
{
    D3DXMATRIX world;
    D3DXMATRIX view;
    D3DXMATRIX project;
};
class TextureShader
{
public:
    bool Initialize(ID3D11Device *device, const char *vertexShaderFile, const char *pixelShaderFile);
    void Shutdown();
    void Render(ID3D11DeviceContext *context, int indexCount, MatBuffer mats, ID3D11ShaderResourceView *texture);

private:
    ID3D11VertexShader *m_vertexShader = nullptr;
    ID3D11PixelShader *m_pixelShader = nullptr;
    ID3D11InputLayout *m_layout = nullptr;
    ID3D11Buffer *m_matBuffer = nullptr;
    ID3D11SamplerState *m_sampleState = nullptr;
};
} // namespace TaoD3D

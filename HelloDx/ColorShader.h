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
class ColorShader
{
public:
    bool Initialize(ID3D11Device *device);
    void Shutdown();
    void Render(ID3D11DeviceContext *context, int indexCount, MatBuffer mats);

private:
    ID3D11VertexShader *m_vertexShader = nullptr;
    ID3D11PixelShader *m_pixelShader = nullptr;
    ID3D11InputLayout *m_layout = nullptr;
    ID3D11Buffer *m_matBuffer = nullptr;
};
} // namespace TaoD3D

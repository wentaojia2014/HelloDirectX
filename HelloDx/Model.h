#pragma once
#include "Common.h"

#include <D3D11.h>
#include <D3DX10math.h>

namespace TaoD3D
{
struct Vertex
{
    float x, y, z;
    D3DXCOLOR color;
};
class Model
{
public:
    bool Initialize(ID3D11Device *device);
    void Shutdown();
    void Render(ID3D11DeviceContext *context);

    int GetIndexCount();

private:
    ID3D11Buffer *m_vertexBuffer = nullptr;
    ID3D11Buffer *m_indexBuffer = nullptr;
    int m_vertexCount = 0;
    int m_indexCount = 0;
};
} // namespace TaoD3D

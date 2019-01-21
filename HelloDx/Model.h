#pragma once
#include "Texture.h"

#include "Common.h"

#include <D3D11.h>
#include <D3DX10math.h>

namespace TaoD3D
{
struct Vertex
{
    D3DXVECTOR3 position;
    D3DXVECTOR2 texture;
    D3DXVECTOR3 normal;
};
struct ModelData
{
    float x, y, z;
    float tu, tv;
    float nx, ny, nz;
};
class Model
{
public:
    bool Initialize(ID3D11Device *device, const char *textureFile, const char *modelFile);
    void Shutdown();
    void Render(ID3D11DeviceContext *context);

    int GetIndexCount();

    ID3D11ShaderResourceView *GetTexture();

protected:
    bool loadModelData(const char *modelFile);

private:
    ID3D11Buffer *m_vertexBuffer = nullptr;
    ID3D11Buffer *m_indexBuffer = nullptr;
    int m_vertexCount = 0;
    int m_indexCount = 0;
    Texture m_texture;
    ModelData *m_data = nullptr;
};
} // namespace TaoD3D

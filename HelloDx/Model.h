#pragma once
#include "Texture.h"

#include "Common.h"

namespace TaoD3D
{
using namespace DirectX;
using Microsoft::WRL::ComPtr;
struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT2 texture;
    XMFLOAT3 normal;
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
    bool Initialize(ID3D11Device *device, ID3D11DeviceContext *context, LPCWSTR textureFile, const char *modelFile);
    void Shutdown();
    void Render(ID3D11DeviceContext *context);

    int GetIndexCount();

    ID3D11ShaderResourceView *GetTexture();

protected:
    bool loadModelData(const char *modelFile);

private:
    ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
    ComPtr<ID3D11Buffer> m_indexBuffer = nullptr;
    int m_vertexCount = 0;
    int m_indexCount = 0;
    Texture m_texture;
    ModelData *m_data = nullptr;
};
} // namespace TaoD3D

#pragma once
#include "D3DHeader.h"

namespace Tao3D
{
using namespace DirectX;
using Microsoft::WRL::ComPtr;
class Bitmap
{
public:
    Bitmap();
    ~Bitmap();

    void Init(ID3D11Device *device, int screenWidth, int screenHeight, LPCWSTR filename, int mapWidth, int mapHeight);
    void Uninit();
    bool Render(ID3D11DeviceContext *context, int x, int y);

    int GetIndexCount() const
    {
        return m_indexCount;
    }
    ID3D11ShaderResourceView *GetTexture();

private:
    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT2 texture;
    };
    static const int COUNT = 6;

    ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
    ComPtr<ID3D11Buffer> m_indexBuffer = nullptr;
    ComPtr<ID3D11Resource> m_texture = nullptr;
    ComPtr<ID3D11ShaderResourceView> m_textureView = nullptr;

    int m_vertexCount = COUNT;
    int m_indexCount = COUNT;
    int m_screenWidth = 0;
    VertexType m_vertices[COUNT];
    unsigned long m_indices[COUNT];
    int m_screenHeight = 0;
    int m_bitmapWidth = 0;
    int m_bitmapHeight = 0;
    int m_lastX = 0;
    int m_lastY = 0;
};

} // namespace Tao3D

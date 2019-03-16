#include "Bitmap.h"
#include "Common/Common.h"
#include <DirectXTK/DDSTextureLoader.h>
namespace Tao3D
{

Bitmap::Bitmap() {}

Bitmap::~Bitmap() {}
void Bitmap::Init(ID3D11Device *device, int screenWidth, int screenHeight, LPCWSTR filename, int mapWidth, int mapHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_bitmapWidth = mapWidth;
    m_bitmapHeight = mapHeight;

    // init vertex buffer and index buffer
    D3D11_BUFFER_DESC vertexDesc, indexDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;

    for (int i = 0; i < m_indexCount; ++i)
    {
        m_indices[i] = i;
    }
    vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexDesc.ByteWidth = sizeof m_vertices;
    vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexDesc.MiscFlags = 0;
    vertexDesc.StructureByteStride = 0;

    vertexData.pSysMem = m_vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    ThrowIfFailed(device->CreateBuffer(&vertexDesc, &vertexData, m_vertexBuffer.GetAddressOf()), "CreateBuffer");

    indexDesc.Usage = D3D11_USAGE_DEFAULT;
    indexDesc.ByteWidth = sizeof m_indices;
    indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexDesc.CPUAccessFlags = 0;
    indexDesc.MiscFlags = 0;
    indexDesc.StructureByteStride = 0;

    indexData.pSysMem = m_indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    ThrowIfFailed(device->CreateBuffer(&indexDesc, &indexData, m_indexBuffer.GetAddressOf()), "CreateBuffer");

    // load texture
    ThrowIfFailed(CreateDDSTextureFromFile(device, filename, m_texture.GetAddressOf(), m_textureView.GetAddressOf()), "CreateDDSTextureFromFile");

}
void Bitmap::Uninit() {}
bool Bitmap::Render(ID3D11DeviceContext *context, int x, int y)
{
    //update buffers
    float left, top, right, bottom;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    VertexType *verticesPtr = nullptr;
    if ((x == m_lastX) && (y == m_lastY) )
    {
        return true;
    }
    m_lastX = x;
    m_lastY = y;
    left = (float)(m_screenWidth / 2 * -1) + x;
    right = left + m_bitmapWidth;
    top = (float)(m_screenHeight / 2) - y;
    bottom = top - m_bitmapHeight;

    m_vertices[0].position = XMFLOAT3(left, top, 0.0f);
    m_vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

    m_vertices[1].position = XMFLOAT3(right, bottom, 0.0f);
    m_vertices[1].texture = XMFLOAT2(1.0f, 1.0f);

    m_vertices[2].position = XMFLOAT3(left, bottom, 0.0f);
    m_vertices[2].texture = XMFLOAT2(0.0f, 1.0f);

    m_vertices[3].position = XMFLOAT3(left, top, 0.0f);
    m_vertices[3].texture = XMFLOAT2(0.0f, 0.0f);

    m_vertices[4].position = XMFLOAT3(right, top, 0.0f);
    m_vertices[4].texture = XMFLOAT2(1.0f, 0.0f);

    m_vertices[5].position = XMFLOAT3(right, bottom, 0.0f);
    m_vertices[5].texture = XMFLOAT2(1.0f, 1.0f);

    ThrowIfFailed(context->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");
    verticesPtr = (VertexType *)mappedResource.pData;
    memcpy(verticesPtr, (void *)m_vertices, sizeof m_vertices);
    context->Unmap(m_vertexBuffer.Get(), 0);

    //render buffers
    unsigned int offset = 0;
    unsigned int stride = sizeof VertexType;
    context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    return true;
}
ID3D11ShaderResourceView *Bitmap::GetTexture()
{
    return m_textureView.Get();
}
} // namespace Tao3D

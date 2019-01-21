#include "Model.h"
namespace TaoD3D
{
bool Model::Initialize(ID3D11Device *device, const char *textureFile)
{
    // Vertex vertex = {0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)};
    Vertex vertexs[] = {
        { { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
        { { -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
    };
    m_vertexCount = sizeof vertexs / sizeof vertexs[0];
    unsigned long indexs[] = { 0, 1, 2, 2, 3, 0 };
    m_indexCount = sizeof(indexs) / sizeof(indexs[0]);
    D3D11_BUFFER_DESC bufferDesc, indexDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;

    ZeroMemory(&bufferDesc, sizeof bufferDesc);
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof vertexs;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    ZeroMemory(&vertexData, sizeof vertexData);
    vertexData.pSysMem = vertexs;

    ThrowIfFailed(device->CreateBuffer(&bufferDesc, &vertexData, &m_vertexBuffer), "CreateBuffer");

    ZeroMemory(&indexDesc, sizeof indexDesc);
    indexDesc.Usage = D3D11_USAGE_DEFAULT;
    indexDesc.ByteWidth = sizeof indexs;
    indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ZeroMemory(&indexData, sizeof indexData);
    indexData.pSysMem = indexs;
    ThrowIfFailed(device->CreateBuffer(&indexDesc, &indexData, &m_indexBuffer), "CreateBuffer");

	return m_texture.Initialize(device, textureFile);
}
void Model::Shutdown()
{
    SafeRelease(m_indexBuffer);
    SafeRelease(m_vertexBuffer);
    m_texture.Shutdown();
}
void Model::Render(ID3D11DeviceContext *context)
{
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
int Model::GetIndexCount()
{
    return m_indexCount;
}
ID3D11ShaderResourceView *Model::GetTexture()
{
    return m_texture.GetTexture();
}
} // namespace TaoD3D

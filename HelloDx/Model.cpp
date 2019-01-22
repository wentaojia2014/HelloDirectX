#include "Model.h"
#include <fstream>
namespace TaoD3D
{
bool Model::Initialize(ID3D11Device *device, const char *textureFile, const char *modelFile)
{
    if (!loadModelData(modelFile))
    {
        return false;
    }
    // Vertex vertex = {0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)};
    Vertex *vertexs = new Vertex[m_vertexCount];
    unsigned long *indexs = new unsigned long[m_indexCount];
    for (int i = 0; i < m_vertexCount; ++i)
    {
        vertexs[i].position = D3DXVECTOR3(m_data[i].x, m_data[i].y, m_data[i].z);
        vertexs[i].texture = D3DXVECTOR2(m_data[i].tu, m_data[i].tv);
        vertexs[i].normal = D3DXVECTOR3(m_data[i].nx, m_data[i].ny, m_data[i].nz);
        indexs[i] = i;
    }

    D3D11_BUFFER_DESC bufferDesc, indexDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;

    ZeroMemory(&bufferDesc, sizeof bufferDesc);
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(Vertex) * m_vertexCount;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    ZeroMemory(&vertexData, sizeof vertexData);
    vertexData.pSysMem = vertexs;

    ThrowIfFailed(device->CreateBuffer(&bufferDesc, &vertexData, &m_vertexBuffer), "CreateBuffer");

    ZeroMemory(&indexDesc, sizeof indexDesc);
    indexDesc.Usage = D3D11_USAGE_DEFAULT;
    indexDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ZeroMemory(&indexData, sizeof indexData);
    indexData.pSysMem = indexs;
    ThrowIfFailed(device->CreateBuffer(&indexDesc, &indexData, &m_indexBuffer), "CreateBuffer");
    SafeDeleteArray(vertexs);
    SafeDeleteArray(indexs);
    return m_texture.Initialize(device, textureFile);
}
void Model::Shutdown()
{
    SafeRelease(m_indexBuffer);
    SafeRelease(m_vertexBuffer);
    SafeDeleteArray(m_data);
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
bool Model::loadModelData(const char *modelFile)
{
    using namespace std;
    ifstream fin;
    char input;
    int i;

    fin.open(modelFile);
    if (fin.fail ())
    {
        return false;
    }
    fin.get(input);
    while (input != ':')
    {
        fin.get(input);
    }
    fin >> m_vertexCount;
    m_indexCount = m_vertexCount;
    m_data = new ModelData[m_vertexCount];
    fin.get(input);
    while (input != ':')
    {
        fin.get(input);
    }
    fin.get(input);
    fin.get(input);
    for (i = 0; i < m_vertexCount; ++i)
    {
        fin >> m_data[i].x >> m_data[i].y >> m_data[i].z;
        fin >> m_data[i].tu >> m_data[i].tv;
        fin >> m_data[i].nx >> m_data[i].ny >> m_data[i].nz;
    }
    fin.close();
    return true;
}
} // namespace TaoD3D

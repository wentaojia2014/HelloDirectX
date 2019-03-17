#include "Text.h"
#include "Common/Common.h"
namespace Tao3D
{
Text::Text() {}

Text::~Text() {}
void Text::Init(ID3D11Device *device, ID3D11DeviceContext *context, HWND hwnd, int screenWidth, int screenHeight, XMMATRIX baseView)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_baseView = baseView;

    m_font = std::make_unique<Font>();
    m_font->Init(device, L"fontdata.txt", L"font.dds");
    m_shader = std::make_unique<FontShader>();
    m_shader->Init(device, hwnd);
    initSentence(&m_sentence1, 16, device);
    updateSentence(m_sentence1, "Hello", 100, 100, 1.0f, 1.0f, 1.0f, context);
    initSentence(&m_sentence2, 16, device);
    updateSentence(m_sentence2, "Goodbye", 100, 200, 1.0f, 1.0f, 1.0f, context);
}
void Text::Uninit()
{
    delete m_sentence1;
    delete m_sentence2;
}
bool Text::Render(ID3D11DeviceContext *context, XMMATRIX world, XMMATRIX ortho)
{
    renderSentence(context, m_sentence1, world, ortho);
    renderSentence(context, m_sentence2, world, ortho);
    return true;
}
void Text::initSentence(SentenceType **sentence, int maxLength, ID3D11Device *device)
{
    VertexType *verticesPtr = nullptr;
    D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
    D3D11_BUFFER_DESC indexBufferDesc = { 0 };
    D3D11_SUBRESOURCE_DATA vertexData = { 0 }, indexData = { 0 };

    *sentence = new SentenceType;
    (*sentence)->maxLength = maxLength;
    (*sentence)->vertexCount = 6 * maxLength;
    (*sentence)->indexCount = (*sentence)->vertexCount;

    VertexType *vertices = new VertexType[(*sentence)->vertexCount];
    unsigned long *indices = new unsigned long[(*sentence)->indexCount];
    ZeroMemory(vertices, sizeof(VertexType) * (*sentence)->vertexCount);
    for (int i = 0; i < (*sentence)->indexCount; ++i)
    {
        indices[i] = i;
    }

    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof vertices;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    vertexData.pSysMem = vertices;
    ThrowIfFailed(device->CreateBuffer(&vertexBufferDesc, &vertexData, (*sentence)->vertexBuffer.GetAddressOf()), "CreateBuffer");

    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof indices;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexData.pSysMem = indices;
    ThrowIfFailed(device->CreateBuffer(&indexBufferDesc, &indexData, (*sentence)->indexBuffer.GetAddressOf()), "CreateBuffer");

    delete[] vertices;
    delete[] indices;
}

void Text::updateSentence(SentenceType *sentence, const char *text, int posX, int posY, float red, float green, float blue, ID3D11DeviceContext *context)
{
    int numLetters = (int)strlen(text);
    if (numLetters > sentence->maxLength)
    {
        throw std::exception("letters too long");
    }
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    sentence->red = red;
    sentence->green = green;
    sentence->blue = blue;
    VertexType *vertices = new VertexType[sentence->vertexCount];
    ZeroMemory(vertices, sizeof vertices);
    float drawX = (float)((m_screenWidth / 2) * -1) + posX;
    float drawY = (float)((m_screenHeight / 2) - posY);
    m_font->BuildVertexArray((void *)vertices, text, drawX, drawY);
    ThrowIfFailed(context->Map(sentence->vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");
    VertexType *verticesPtr = (VertexType *)mappedResource.pData;
    memcpy(verticesPtr, (void *)vertices, sizeof vertices);
    context->Unmap(sentence->vertexBuffer.Get(), 0);

    delete[] vertices;
}
void Text::renderSentence(ID3D11DeviceContext *context, SentenceType *sentence, XMMATRIX world, XMMATRIX ortho)
{
    XMFLOAT4 pixelColor;
    unsigned int stride = sizeof VertexType;
    unsigned int offset = 0;

    context->IASetVertexBuffers(0, 1, sentence->vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(sentence->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    pixelColor = XMFLOAT4(sentence->red, sentence->green, sentence->blue, 1.0f);
    m_shader->Render(context, sentence->indexCount, { world, m_baseView, ortho }, m_font->GetTexture(), pixelColor);
}
} // namespace Tao3D

#pragma once
#include "D3DHeader.h"
#include "Font.h"
#include "FontShader.h"
#include <memory>
namespace Tao3D
{
using namespace DirectX;
using Microsoft::WRL::ComPtr;
class Text
{
public:
    Text();
    ~Text();

    void Init(ID3D11Device *device, ID3D11DeviceContext *context, HWND hwnd, int screenWidth, int screenHeight, XMMATRIX baseView);
    void Uninit();
    bool Render(ID3D11DeviceContext *context, XMMATRIX world, XMMATRIX ortho);

private:
    struct SentenceType
    {
        ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
        ComPtr<ID3D11Buffer> indexBuffer = nullptr;
        int vertexCount;
        int indexCount;
        int maxLength;
        float red, green, blue;
    };
    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT2 texture;
    };

    void initSentence(SentenceType **sentence, int maxLength, ID3D11Device *device);
    void updateSentence(SentenceType *sentence, const char * text, int posX, int posY, float red, float green, float blue, ID3D11DeviceContext *context);
    void renderSentence(ID3D11DeviceContext *context, SentenceType *sentence, XMMATRIX world, XMMATRIX ortho);
private:
    std::unique_ptr<Font> m_font = nullptr;
    std::unique_ptr<FontShader> m_shader = nullptr;
    int m_screenWidth;
    int m_screenHeight;
    XMMATRIX m_baseView;
    SentenceType *m_sentence1 = nullptr;
    SentenceType *m_sentence2 = nullptr;
};

} // namespace Tao3D

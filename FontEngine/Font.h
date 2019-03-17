#pragma once
#include "D3DHeader.h"
namespace Tao3D
{
using namespace DirectX;
using Microsoft::WRL::ComPtr;
class Font
{
public:
    Font();
    ~Font();

    void Init(ID3D11Device *device, LPCWSTR fontFilename, LPCWSTR textureFilename);
    void Uninit();
    ID3D11ShaderResourceView *GetTexture();
    void BuildVertexArray(void *vertices, const char *sentence, float drawX, float drawY);

private:
    struct FontType
    {
        float left, right;
        int size;
    };
    struct VertexType
    {
        XMFLOAT3 position;
        XMFLOAT2 texture;
    };
    static const int FONTCOUNT = 95;
    FontType m_fonts[FONTCOUNT];

    ComPtr<ID3D11ShaderResourceView> m_textureView = nullptr;
};
} // namespace Tao3D

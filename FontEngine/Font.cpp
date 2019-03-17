#include "Font.h"

#include "Common/Common.h"
#include <DirectXTEX.h>
#include <fstream>
namespace Tao3D
{
Font::Font() {}

Font::~Font() {}
void Font::Init(ID3D11Device *device, LPCWSTR fontFilename, LPCWSTR textureFilename)
{
    // load font
    std::ifstream fin;
    char t;
    fin.open(fontFilename);
    if (fin.fail())
    {
        throw std::exception("open file failed");
        return;
    }
    for (int i = 0; i < FONTCOUNT; ++i)
    {
        fin.get(t);
        while (t != ' ')
        {
            fin.get(t);
        }
        fin.get(t);
        while (t != ' ')
        {
            fin.get(t);
        }
        fin >> m_fonts[i].left >> m_fonts[i].right >> m_fonts[i].size;
    }
    fin.close();
    
    // load texture
    ScratchImage image;
    TexMetadata meta;
    ThrowIfFailed(LoadFromDDSFile(textureFilename, 0, &meta, image), "LoadFromDDSFile");
    ThrowIfFailed(CreateShaderResourceView(device, image.GetImages(), image.GetImageCount(), meta, m_textureView.GetAddressOf()), "CreateShaderResourceView");
}
void Font::Uninit() {}
ID3D11ShaderResourceView *Font::GetTexture()
{
    return m_textureView.Get();
}
void Font::BuildVertexArray(void *vertices, const char *sentence, float drawX, float drawY)
{
    VertexType *verticesPtr = (VertexType *)vertices;
    int numLetters = (int)strlen(sentence);
    int letter = 0;
    int index = 0;
    for (int i = 0; i < numLetters; ++i)
    {
        letter = (int)sentence[i] - 32;
        if (letter == 0)
        {
            drawX = drawX + 3.0f;
        }
        else
        {
            const FontType &font = m_fonts[letter];

            verticesPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);
            verticesPtr[index].texture = XMFLOAT2(font.left, 0.0f);
            index++;

            verticesPtr[index].position = XMFLOAT3(drawX + font.size, drawY - 16, 0.0f);
            verticesPtr[index].texture = XMFLOAT2(font.right, 1.0f);
            index++;

            verticesPtr[index].position = XMFLOAT3(drawX, drawY - 16, 0.0f);
            verticesPtr[index].texture = XMFLOAT2(font.left, 1.0f);
            index++;

            verticesPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f);
            verticesPtr[index].texture = XMFLOAT2(font.left, 0.0f);
            index++;

            verticesPtr[index].position = XMFLOAT3(drawX + font.size, drawY, 0.0f);
            verticesPtr[index].texture = XMFLOAT2(font.right, 0.0f);
            index++;

            verticesPtr[index].position = XMFLOAT3(drawX + font.size, drawY - 16, 0.0f);
            verticesPtr[index].texture = XMFLOAT2(font.right, 1.0f);
            index++;

            drawX += font.size + 1.0f;
        }
    }
}
} // namespace Tao3D

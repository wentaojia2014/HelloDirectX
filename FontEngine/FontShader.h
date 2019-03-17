#pragma once
#include "D3DHeader.h"
namespace Tao3D
{
using namespace DirectX;
using Microsoft::WRL::ComPtr;
struct ConstantBuffer
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX project;
};
class FontShader
{
public:
    FontShader();
    ~FontShader();
    void Init(ID3D11Device *device, HWND hwnd);
    void Uninit();
    bool Render(ID3D11DeviceContext *context, int indexCount, ConstantBuffer mats, ID3D11ShaderResourceView *texture, XMFLOAT4 pixelColor);

private:
    struct PixelBufferType
    {
        XMFLOAT4 pixelColor;
    };
    ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
    ComPtr<ID3D11PixelShader> m_pixelShader = nullptr;
    ComPtr<ID3D11InputLayout> m_layout = nullptr;
    ComPtr<ID3D11Buffer> m_constantBuffer = nullptr;
    ComPtr<ID3D11SamplerState> m_sampleState = nullptr;
    ComPtr<ID3D11Buffer> m_pixelBuffer = nullptr;
};

} // namespace Tao3D

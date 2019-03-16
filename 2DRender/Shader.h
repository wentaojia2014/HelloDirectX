#pragma once
#include "D3DHeader.h"

namespace Tao3D
{
using namespace DirectX;
using Microsoft::WRL::ComPtr;
struct MatBuffer
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX project;
};
struct CameraBuffer
{
    XMFLOAT3 cameraPosition;
    float padding;
};
struct LightBuffer
{
    XMFLOAT4 ambientColor;
    XMFLOAT4 diffuseColor;
    XMFLOAT4 speculatColor;
    XMFLOAT3 lightDirection;
    float specularPower;
};

class Shader
{
public:
    bool Initialize(ID3D11Device *device, LPCWSTR vertexShaderBindaryFile, LPCWSTR pixelShaderBinaryFile);
    void Shutdown();
    void Render(ID3D11DeviceContext *context, int indexCount, MatBuffer mats, ID3D11ShaderResourceView *texture, LightBuffer lightBuf, CameraBuffer cameraBuf);

private:
    ComPtr<ID3D11VertexShader> m_vertexShader = nullptr;
    ComPtr<ID3D11PixelShader> m_pixelShader = nullptr;
    ComPtr<ID3D11InputLayout> m_layout = nullptr;
    ComPtr<ID3D11Buffer> m_matBuffer = nullptr;
    ComPtr<ID3D11SamplerState> m_sampleState = nullptr;

    ComPtr<ID3D11Buffer> m_lightBuffer = nullptr;
    ComPtr<ID3D11Buffer> m_cameraBuffer = nullptr;
};
} // namespace Tao3D

#pragma once
#include "D3DHeader.h"

namespace TaoD3D
{
using namespace DirectX;
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
    bool Initialize(ID3D11Device *device, LPCWSTR vertexShaderFile, LPCWSTR pixelShaderFile);
    void Shutdown();
    void Render(ID3D11DeviceContext *context
        , int indexCount
        , MatBuffer mats
        , ID3D11ShaderResourceView *texture
        , LightBuffer lightBuf
        , CameraBuffer cameraBuf);

private:
    ID3D11VertexShader *m_vertexShader = nullptr;
    ID3D11PixelShader *m_pixelShader = nullptr;
    ID3D11InputLayout *m_layout = nullptr;
    ID3D11Buffer *m_matBuffer = nullptr;
    ID3D11SamplerState *m_sampleState = nullptr;

    ID3D11Buffer *m_lightBuffer = nullptr;
    ID3D11Buffer *m_cameraBuffer = nullptr;
    
};
} // namespace TaoD3D

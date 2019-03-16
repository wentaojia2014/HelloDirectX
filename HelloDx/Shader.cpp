#include "Common.h"
#include "Shader.h"
#include "DirectXTK/DirectXHelpers.h"
namespace TaoD3D
{
bool Shader::Initialize(ID3D11Device *device, LPCWSTR vertexShaderBindaryFile, LPCWSTR pixelShaderBinaryFile)
{
    ComPtr<ID3D10Blob> vs = nullptr, ps = nullptr, errorMessage = nullptr;
    ThrowIfFailed(D3DReadFileToBlob(vertexShaderBindaryFile, vs.GetAddressOf()), "D3DReadFileToBlob");
    ThrowIfFailed(D3DReadFileToBlob(pixelShaderBinaryFile, ps.GetAddressOf()), "D3DReadFileToBlob");
    
    ThrowIfFailed(device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf()), "CreateVertexShader");
    ThrowIfFailed(device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, m_pixelShader.GetAddressOf()), "CreatePixelShader");

    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    ThrowIfFailed(
        device->CreateInputLayout(
            inputElementDesc, _countof(inputElementDesc), vs->GetBufferPointer(), vs->GetBufferSize(), m_layout.GetAddressOf()),
        "CreateInputLayout");

    D3D11_BUFFER_DESC matrixBufferDesc;
    ZeroMemory(&matrixBufferDesc, sizeof matrixBufferDesc);
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(MatBuffer);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ThrowIfFailed(device->CreateBuffer(&matrixBufferDesc, nullptr, m_matBuffer.GetAddressOf()), "CreateBuffer");

    D3D11_SAMPLER_DESC samplerDesc;

    ZeroMemory(&samplerDesc, sizeof samplerDesc);
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    ThrowIfFailed(device->CreateSamplerState(&samplerDesc, m_sampleState.GetAddressOf()), "CreateSamplerState");

    D3D11_BUFFER_DESC lightBufferDesc;
    ZeroMemory(&lightBufferDesc, sizeof lightBufferDesc);
    lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    lightBufferDesc.ByteWidth = sizeof LightBuffer;
    lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    ThrowIfFailed(device->CreateBuffer(&lightBufferDesc, nullptr, m_lightBuffer.GetAddressOf()), "CreateBuffer");
    
    D3D11_BUFFER_DESC cameraBufferDesc;
    ZeroMemory(&cameraBufferDesc, sizeof cameraBufferDesc);
    cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    cameraBufferDesc.ByteWidth = sizeof CameraBuffer;
    cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ThrowIfFailed(device->CreateBuffer(&cameraBufferDesc, nullptr, m_cameraBuffer.GetAddressOf()), "CreateBuffer");
    
    return true;
}
void Shader::Shutdown()
{
}
void Shader::Render(ID3D11DeviceContext *context
    , int indexCount
    , MatBuffer mats
    , ID3D11ShaderResourceView *texture
    , LightBuffer lightBuf
    , CameraBuffer cameraBuf)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    mats.world = XMMatrixTranspose(mats.world);
    mats.view = XMMatrixTranspose(mats.view);
    mats.project = XMMatrixTranspose(mats.project);

    ThrowIfFailed(context->Map(m_matBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");

    MatBuffer *pMatBuffer = (MatBuffer *)mappedResource.pData;
    pMatBuffer->world = mats.world;
    pMatBuffer->project = mats.project;
    pMatBuffer->view = mats.view;
    context->Unmap(m_matBuffer.Get(), 0);

    context->VSSetConstantBuffers(0, 1, m_matBuffer.GetAddressOf());
    context->PSSetShaderResources(0, 1, &texture);

    ThrowIfFailed(context->Map(m_lightBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");
    LightBuffer *pLightBuffer = (LightBuffer *)mappedResource.pData;
    pLightBuffer->ambientColor = lightBuf.ambientColor;
    pLightBuffer->diffuseColor = lightBuf.diffuseColor;
    pLightBuffer->speculatColor = lightBuf.speculatColor;
    pLightBuffer->lightDirection = lightBuf.lightDirection;
    pLightBuffer->specularPower = lightBuf.specularPower;
    context->Unmap(m_lightBuffer.Get(), 0);
    context->PSSetConstantBuffers(0, 1, m_lightBuffer.GetAddressOf());

    ThrowIfFailed(context->Map(m_cameraBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");
    CameraBuffer *pCameraBuffer = (CameraBuffer *)mappedResource.pData;
    pCameraBuffer->cameraPosition = cameraBuf.cameraPosition;
    pCameraBuffer->padding = cameraBuf.padding;
    context->Unmap(m_cameraBuffer.Get(), 0);
    context->PSSetConstantBuffers(1, 1, m_cameraBuffer.GetAddressOf());

    context->IASetInputLayout(m_layout.Get());
    context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

    context->PSSetSamplers(0, 1, m_sampleState.GetAddressOf());
    context->DrawIndexed(indexCount, 0, 0);
}
} // namespace TaoD3D

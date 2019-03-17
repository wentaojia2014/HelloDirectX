#include "FontShader.h"
#include "Common/Common.h"
#include "DirectXTK/DirectXHelpers.h"
namespace Tao3D
{

FontShader::FontShader() {}

FontShader::~FontShader() {}
void FontShader::Init(ID3D11Device *device, HWND hwnd) 
{
    ComPtr<ID3D10Blob> vs = nullptr, ps = nullptr;
    D3D11_INPUT_ELEMENT_DESC polygonLayout[2] = { 0 };
    unsigned int numElements = 0;
    D3D11_BUFFER_DESC constantBufferDesc = { 0 };
    D3D11_SAMPLER_DESC samplerDesc;
    D3D11_BUFFER_DESC pixelBufferDesc = { 0 };
    
    ThrowIfFailed(D3DReadFileToBlob(L"fontV.cso", vs.GetAddressOf()), "D3DReadFileToBlob");
    ThrowIfFailed(D3DReadFileToBlob(L"fontP.cso", ps.GetAddressOf()), "D3DReadFileToBlob");

    ThrowIfFailed(device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf()), "CreateVertexShader");
    ThrowIfFailed(device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, m_pixelShader.GetAddressOf()), "CreatePixelShader");

    polygonLayout[0].SemanticName = "POSITION";
    polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    
    polygonLayout[1].SemanticName = "TEXCOORD";
    polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
    polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    numElements = _countof(polygonLayout);
    ThrowIfFailed(device->CreateInputLayout(polygonLayout, numElements, vs->GetBufferPointer(), vs->GetBufferSize(), m_layout.GetAddressOf()), "CreateInputLayout");

    constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constantBufferDesc.ByteWidth = sizeof ConstantBuffer;
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ThrowIfFailed(device->CreateBuffer(&constantBufferDesc, nullptr, m_constantBuffer.GetAddressOf()), "CreateBuffer");

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    ThrowIfFailed(device->CreateSamplerState(&samplerDesc, m_sampleState.GetAddressOf()), "CreateSamplerState");

    pixelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    pixelBufferDesc.ByteWidth = sizeof PixelBufferType;
    pixelBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    pixelBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    ThrowIfFailed(device->CreateBuffer(&pixelBufferDesc, nullptr, m_pixelBuffer.GetAddressOf()), "CreateBuffer");

}
void FontShader::Uninit() {}
bool FontShader::Render(ID3D11DeviceContext *context, int indexCount, ConstantBuffer mats, ID3D11ShaderResourceView *texture, XMFLOAT4 pixelColor)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    //update buffer

    ThrowIfFailed(context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");
    ConstantBuffer *constantBufferPtr = (ConstantBuffer *)mappedResource.pData;
    constantBufferPtr->world = XMMatrixTranspose(mats.world);
    constantBufferPtr->view = XMMatrixTranspose(mats.view);
    constantBufferPtr->project = XMMatrixTranspose(mats.project);
    context->Unmap(m_constantBuffer.Get(), 0);

    context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
    context->PSSetShaderResources(0, 1, &texture);

    ThrowIfFailed(context->Map(m_pixelBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");
    PixelBufferType *pPixelBuffer = (PixelBufferType *)mappedResource.pData;
    pPixelBuffer->pixelColor = pixelColor;
    context->Unmap(m_pixelBuffer.Get(), 0);

    context->PSSetConstantBuffers(0, 1, m_pixelBuffer.GetAddressOf());

    //render
    context->IASetInputLayout(m_layout.Get());
    context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
    context->PSSetSamplers(0, 1, m_sampleState.GetAddressOf());
    context->DrawIndexed(indexCount, 0, 0);

    return true;
}
} // namespace Tao3D

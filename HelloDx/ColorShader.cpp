#include "ColorShader.h"
#include "Common.h"
namespace TaoD3D
{
bool ColorShader::Initialize(ID3D11Device *device)
{
    const char *shaderFile = u8"shaders.shader";
    ID3D10Blob *vs, *ps, *errorMessage;
    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    if (FAILED(D3DX11CompileFromFile(shaderFile, nullptr, nullptr, "VShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &vs, &errorMessage, 0)))
    {
        if (errorMessage)
        {
            OutputDebugString((const char *)errorMessage->GetBufferPointer());
        }
        else
        {
            OutputDebugString(GetLastErrorAsString().data());
        }
        return false;
    }
    if (FAILED(D3DX11CompileFromFile(shaderFile, nullptr, nullptr, "PShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &ps, &errorMessage, 0)))
    {
        if (errorMessage)
        {
            OutputDebugString((const char *)errorMessage->GetBufferPointer());
        }
        else
        {
            OutputDebugStringA(GetLastErrorAsString().data());
        }
        return false;
    }
    ThrowIfFailed(device->CreateVertexShader(vs->GetBufferPointer(), vs->GetBufferSize(), nullptr, &m_vertexShader), "CreateVertexShader");
    ThrowIfFailed(device->CreatePixelShader(ps->GetBufferPointer(), ps->GetBufferSize(), nullptr, &m_pixelShader), "CreatePixelShader");

    ThrowIfFailed(
        device->CreateInputLayout(
            inputElementDesc, sizeof(inputElementDesc) / sizeof(inputElementDesc[0]), vs->GetBufferPointer(), vs->GetBufferSize(), &m_layout),
        "CreateInputLayout");
    vs->Release();
    ps->Release();

    D3D11_BUFFER_DESC matrixBufferDesc;
    ZeroMemory(&matrixBufferDesc, sizeof matrixBufferDesc);
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof MatBuffer;
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ThrowIfFailed(device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matBuffer), "CreateBuffer");
    return true;
}
void ColorShader::Shutdown()
{
    m_pixelShader->Release();
    m_vertexShader->Release();
    m_layout->Release();
    m_matBuffer->Release();
}
void ColorShader::Render(ID3D11DeviceContext *context, int indexCount, MatBuffer mats)
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;

    D3DXMatrixTranspose(&mats.world, &mats.world);
    D3DXMatrixTranspose(&mats.view, &mats.view);
    D3DXMatrixTranspose(&mats.project, &mats.project);
   
    ThrowIfFailed(context->Map(m_matBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource), "Map");

    MatBuffer *pMatBuffer = (MatBuffer *)mappedResource.pData;
    pMatBuffer->world = mats.world;
    pMatBuffer->project = mats.project;
    pMatBuffer->view = mats.view;
    context->Unmap(m_matBuffer, 0);

    context->VSSetConstantBuffers(0, 1, &m_matBuffer);

    context->IASetInputLayout(m_layout);
    context->VSSetShader(m_vertexShader, nullptr, 0);
    context->PSSetShader(m_pixelShader, nullptr, 0);
    context->DrawIndexed(indexCount, 0, 0);
}
} // namespace TaoD3D

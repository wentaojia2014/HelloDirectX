#pragma once
#include "D3DHeader.h"
namespace TaoD3D
{
using namespace DirectX;
class Light
{
public:
    void SetAmbientColor(float r, float g, float b, float a);
    void SetDiffuseColor(float r, float g, float b, float a);
    void SetSpecularColor(float r, float g, float b, float a);
    void SetDirection(float x, float y, float z);
    void SetSpecularPower(float power);

    XMFLOAT4 GetAmbientColor();
    XMFLOAT4 GetDiffuseColor();
    XMFLOAT4 GetSpecularColor();
    XMFLOAT4 GetDirection();
    float GetSpecularPower();
private:
    XMFLOAT4 m_ambientColor;
    XMFLOAT4 m_diffuseColor;
    XMFLOAT4 m_specularColor;
    XMFLOAT4 m_direction;
    float m_specularPower;
};
} // namespace TaoD3D
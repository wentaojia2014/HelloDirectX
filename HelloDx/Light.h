#pragma once
#include "D3DHeader.h"
namespace TaoD3D
{
class Light
{
public:
    void SetAmbientColor(float r, float g, float b, float a);
    void SetDiffuseColor(float r, float g, float b, float a);
    void SetSpecularColor(float r, float g, float b, float a);
    void SetDirection(float x, float y, float z);
    void SetSpecularPower(float power);
    D3DXVECTOR4 GetAmbientColor();
    D3DXVECTOR4 GetDiffuseColor();
    D3DXVECTOR4 GetSpecularColor();
    D3DXVECTOR3 GetDirection();
    float GetSpecularPower();
private:
    D3DXVECTOR4 m_ambientColor;
    D3DXVECTOR4 m_diffuseColor;
    D3DXVECTOR4 m_specularColor;
    D3DXVECTOR3 m_direction;
    float m_specularPower;
};
} // namespace TaoD3D
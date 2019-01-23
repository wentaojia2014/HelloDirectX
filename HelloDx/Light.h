#pragma once
#include "D3DHeader.h"
namespace TaoD3D
{
class Light
{
public:
    void SetAmbientColor(float r, float g, float b, float a);
    void SetDiffuseColor(float r, float g, float b, float a);
    void SetDirection(float x, float y, float z);
    D3DXVECTOR4 GetAmbientColor();
    D3DXVECTOR4 GetDiffuseColor();
    D3DXVECTOR3 GetDirection();

private:
    D3DXVECTOR4 m_ambientColor;
    D3DXVECTOR4 m_diffuseColor;
    D3DXVECTOR3 m_direction;
};
} // namespace TaoD3D
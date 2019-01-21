#include "Light.h"
namespace TaoD3D
{
void Light::SetDiffuseColor(float r, float g, float b, float a)
{
    m_diffuseColor = D3DXVECTOR4(r, g, b, a);
}
void Light::SetDirection(float x, float y, float z)
{
    m_direction = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR4 Light::GetDiffuseColor()
{
    return m_diffuseColor;
}
D3DXVECTOR3 Light::GetDirection()
{
    return m_direction;
}
} // namespace TaoD3D
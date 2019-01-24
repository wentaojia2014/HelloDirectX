#include "Light.h"
namespace TaoD3D
{
void Light::SetAmbientColor(float r, float g, float b, float a)
{
    m_ambientColor = D3DXVECTOR4(r, g, b, a);
}
void Light::SetDiffuseColor(float r, float g, float b, float a)
{
    m_diffuseColor = D3DXVECTOR4(r, g, b, a);
}
void Light::SetSpecularColor(float r, float g, float b, float a) {
    m_specularColor = D3DXVECTOR4(r, g, b, a);
}
void Light::SetDirection(float x, float y, float z)
{
    m_direction = D3DXVECTOR3(x, y, z);
}

void Light::SetSpecularPower(float power) {
    m_specularPower = power;
}

D3DXVECTOR4 Light::GetAmbientColor()
{
    return m_ambientColor;
}
D3DXVECTOR4 Light::GetDiffuseColor()
{
    return m_diffuseColor;
}
D3DXVECTOR4 Light::GetSpecularColor()
{
    return m_specularColor;
}
D3DXVECTOR3 Light::GetDirection()
{
    return m_direction;
}
float Light::GetSpecularPower()
{
    return m_specularPower;
}
} // namespace TaoD3D

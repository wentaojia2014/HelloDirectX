#include "Light.h"
namespace Tao3D
{
void Light::SetAmbientColor(float r, float g, float b, float a)
{
    m_ambientColor = XMFLOAT4(r, g, b, a);
}
void Light::SetDiffuseColor(float r, float g, float b, float a)
{
    m_diffuseColor = XMFLOAT4(r, g, b, a);
}
void Light::SetSpecularColor(float r, float g, float b, float a)
{
    m_specularColor = XMFLOAT4(r, g, b, a);
}
void Light::SetDirection(float x, float y, float z)
{
    m_direction = XMFLOAT4(x, y, z, 1);
}

void Light::SetSpecularPower(float power)
{
    m_specularPower = power;
}

XMFLOAT4 Light::GetAmbientColor()
{
    return m_ambientColor;
}
XMFLOAT4 Light::GetDiffuseColor()
{
    return m_diffuseColor;
}
XMFLOAT4 Light::GetSpecularColor()
{
    return m_specularColor;
}
XMFLOAT4 Light::GetDirection()
{
    return m_direction;
}
float Light::GetSpecularPower()
{
    return m_specularPower;
}
} // namespace Tao3D

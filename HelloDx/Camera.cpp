#include "Camera.h"
namespace TaoD3D
{
void Camera::SetPosition(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}
void Camera::SetRotation(float x, float y, float z)
{
    m_rX = x;
    m_rY = y;
    m_rZ = z;
}
D3DXVECTOR3 Camera::GetPosition()
{
    return D3DXVECTOR3(m_x, m_y, m_z);
}
D3DXVECTOR3 Camera::GetRotation()
{
    return D3DXVECTOR3(m_rX, m_rY, m_rZ);
}
void Camera::Render()
{
    D3DXVECTOR3 up = { 0.0f, 1.0f, 0.0f };
    D3DXVECTOR3 position = { m_x, m_y, m_z };
    D3DXVECTOR3 lookAt = { 0.0f, 0.0f, 1.0f };

    float yaw = m_rX * 0.0174532925f;
    float pitch = m_rY * 0.0174532925f;
    float roll = m_rZ * 0.0174532925f;
    D3DXMATRIX rotationMat;

    D3DXMatrixRotationYawPitchRoll(&rotationMat, yaw, pitch, roll);
    D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMat);
    D3DXVec3TransformCoord(&up, &up, &rotationMat);
    lookAt = position + lookAt;
    D3DXMatrixLookAtLH(&m_viewMat, &position, &lookAt, &up);
}
void Camera::GetViewMatrix(D3DXMATRIX &view)
{
    view = m_viewMat;
}
} // namespace TaoD3D

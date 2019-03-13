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
XMFLOAT3 Camera::GetPosition()
{
    return XMFLOAT3(m_x, m_y, m_z);
}
XMFLOAT3 Camera::GetRotation()
{
    return XMFLOAT3(m_rX, m_rY, m_rZ);
}
void Camera::Render()
{
    XMVECTOR up = { 0.0f, 1.0f, 0.0f };
    XMVECTOR position = { m_x, m_y, m_z };
    XMVECTOR lookAt = { 0.0f, 0.0f, 1.0f };

    float pitch = m_rX * 0.0174532925f;
    float yaw = m_rY * 0.0174532925f;
    float roll = m_rZ * 0.0174532925f;
    XMMATRIX rotationMat;

    rotationMat = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

    lookAt = XMVector3TransformCoord(lookAt, rotationMat);
    up = XMVector3TransformCoord(up, rotationMat);
    lookAt = position + lookAt;
    m_viewMat = XMMatrixLookAtLH(position, lookAt, up);
}
void Camera::GetViewMatrix(XMMATRIX &view)
{
    view = m_viewMat;
}
} // namespace TaoD3D

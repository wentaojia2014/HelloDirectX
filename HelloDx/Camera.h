#pragma once
#include "D3DHeader.h"

namespace TaoD3D
{
class Camera
{
public:
    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    D3DXVECTOR3 GetPosition();
    D3DXVECTOR3 GetRotation();

    void Render();
    void GetViewMatrix(D3DXMATRIX &view);
    void Shutdown() {}

private:
    float m_x = 0.0f, m_y = 0.0f, m_z = 0.0f;
    float m_rX = 0.0f, m_rY = 0.0f, m_rZ = 0.0f;
    D3DXMATRIX m_viewMat;
};
} // namespace TaoD3D

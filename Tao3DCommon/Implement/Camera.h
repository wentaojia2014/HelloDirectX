#pragma once

#include "../Tao3DGlobal.h"

#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")

namespace Tao3D
{
using namespace DirectX;

#pragma warning(disable: 4251)
class Tao3DAPI Camera
{
public:
    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    XMFLOAT3 GetPosition();
    XMFLOAT3 GetRotation();

    void Render();
    void GetViewMatrix(XMMATRIX &view);

private:
    float m_x = 0.0f, m_y = 0.0f, m_z = 0.0f;
    float m_rX = 0.0f, m_rY = 0.0f, m_rZ = 0.0f;

    XMMATRIX m_viewMat;
};
} // namespace Tao3D

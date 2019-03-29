#include "TriangleRender.h"

#include "Application.h"
#include "Common.h"

#include <DirectXTK/DDSTextureLoader.h>
#include <algorithm>

namespace Tao3D
{
TriangleRender::TriangleRender()
{
    m_cameraPos = START_POSITION.v;
}

TriangleRender::~TriangleRender() {}
void TriangleRender::init(int width, int height)
{
    m_room = GeometricPrimitive::CreateBox(gContext, XMFLOAT3(ROOM_BOUNDS[0], ROOM_BOUNDS[1], ROOM_BOUNDS[2]), false, true);
    ThrowIfFailed(CreateDDSTextureFromFile(gDevice, L"roomtexture.dds", nullptr, m_rootTex.GetAddressOf()), "CreateDDSTextureFromFile");
    m_proj = Matrix::CreatePerspectiveFieldOfView(XMConvertToRadians(70.0f), (float)width / height, 0.01f, 100.f);
}
void TriangleRender::update()
{
    auto kb = gKeyboard.GetState();
    if (kb.Escape)
    {
        gApp.quit();
    }
    if (kb.Home)
    {
        m_cameraPos = START_POSITION.v;
        m_pitch = m_yaw = 0;
    }
    Vector3 move = Vector3::Zero;
    if (kb.Up || kb.W)
    {
        move.y += m_cameraSpeed;
    }
    if (kb.Down || kb.S)
    {
        move.y -= m_cameraSpeed;
    }
    if (kb.Left || kb.A)
    {
        move.x += m_cameraSpeed;
    }
    if (kb.Right || kb.D)
    {
        move.x -= m_cameraSpeed;
    }
    if (kb.PageUp || kb.Space)
    {
        move.z += m_cameraSpeed;
    }
    if (kb.PageDown || kb.X)
    {
        move.z -= m_cameraSpeed;
    }
    Quaternion q = Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0.f);
    move = Vector3::Transform(move, q);
    move *= MOVEMENT_GAIN;
    m_cameraPos += move;
    Vector3 halfBound = (Vector3(ROOM_BOUNDS.v) / Vector3(2.f)) - Vector3(0.1f, 0.1f, 0.1f);
    m_cameraPos = Vector3::Min(m_cameraPos, halfBound);
    m_cameraPos = Vector3::Max(m_cameraPos, -halfBound);

    auto mouse = gMouse.GetState();
    if (mouse.positionMode == Mouse::MODE_RELATIVE)
    {
        Vector3 delta = Vector3(float(mouse.x), float(mouse.y), 0.f) * ROTATION_GAIN;
        m_pitch -= delta.y;
        m_yaw -= delta.x;

        float limit = XM_PI / 2.0f - 0.01f;

        m_pitch = (std::max)(-limit, m_pitch);
        m_pitch = (std::min)(limit, m_pitch);
        if (m_yaw > XM_PI)
        {
            m_yaw -= XM_PI * 2.0f;
        }
        else if (m_yaw < -XM_PI)
        {
            m_yaw += XM_PI * 2.0f;
        }
    }
    gMouse.SetMode(mouse.leftButton ? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE);
}
bool TriangleRender::render()
{
    gResource.beginScene(0.2f, 0.3f, 0.4f, 1.0f);
    float y = sinf(m_pitch);
    float r = cosf(m_pitch);
    float z = r * cosf(m_yaw);
    float x = r * sinf(m_yaw);
    XMVECTOR lookAt = m_cameraPos + Vector3(x, y, z);
    XMMATRIX view = XMMatrixLookAtRH(m_cameraPos, lookAt, Vector3::Up);

    m_room->Draw(Matrix::Identity, view, m_proj, Colors::White, m_rootTex.Get());
    gResource.endScene();
    return true;
}
} // namespace Tao3D

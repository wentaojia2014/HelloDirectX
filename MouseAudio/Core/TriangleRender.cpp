#include "TriangleRender.h"
#include "../Base/Application.h"
namespace Tao3D
{
TriangleRender::TriangleRender() {}

TriangleRender::~TriangleRender() {}

bool Tao3D::TriangleRender::render()
{
    gResource.beginScene(0.2f, 0.3f, 0.4f, 1.0f);

    gResource.endScene();
    return true;
}
} // namespace Tao3D

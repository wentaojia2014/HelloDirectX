#pragma once
#include "../Base/IRender.h"
namespace Tao3D {
    class TriangleRender : public IRender
    {
    public:
        TriangleRender();
        ~TriangleRender();

        bool render() override;
    private:

    };
}

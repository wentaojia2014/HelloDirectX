#pragma once

namespace Tao3D
{
    class IRender 
    {
    public:
        virtual ~IRender() {}

        virtual bool render() = 0;
    };
}
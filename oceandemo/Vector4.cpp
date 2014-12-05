
#include "Vector4.h"

#include <cassert>
#include <cstring>

namespace od
{
    Vector4::Vector4() {}

    Vector4::Vector4(float x, float y, float z, float m)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = m;
    }

    Vector4::Vector4(const Vector4& other)
    {
        std::memcpy(data, other.data, 4*sizeof(float));
    }

    const Vector4& Vector4::operator = (const Vector4& other)
    {
        if (this != &other)
        {
            std::memcpy(data, other.data, 4*sizeof(float));
        }
        return *this;
    }

    float& Vector4::operator () (unsigned int i) 
    {
        assert(i < 4);
        return data[i];
    }

    float Vector4::operator () (unsigned int i) const
    {
        assert(i < 4);
        return data[i];
    }
}

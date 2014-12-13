
#include "Vector4.h"

#include <cassert>
#include <cstring>

#include "Vector2.h"
#include "Vector3.h"

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

    Vector4::Vector4(const Vector2& other, float z, float m)
    {
        data[0] = other(0);
        data[1] = other(1);
        data[2] = z;
        data[3] = m;
    }

    Vector4::Vector4(const Vector3& other, float m)
    {
        data[0] = other(0);
        data[1] = other(1);
        data[2] = other(2);
        data[3] = m;
    }

    Vector4::Vector4(const Vector<4>& other)
    : Vector<4>(other) {}
}

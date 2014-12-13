
#include "Vector2.h"

#include "Vector3.h"
#include "Vector4.h"

namespace od
{
    Vector2::Vector2() {}

    Vector2::Vector2(float x, float y)
    {
        data[0] = x;
        data[1] = y;
    }

    Vector2::Vector2(const Vector3& other)
    {
        data[0] = other(0);
        data[1] = other(1);
    }

    Vector2::Vector2(const Vector4& other)
    {
        data[0] = other(0);
        data[1] = other(1);
    }

    Vector2::Vector2(const Vector<2>& other)
    : Vector<2>(other) {}
}

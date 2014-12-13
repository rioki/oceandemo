
#include "Vector3.h"

#include "Vector2.h"
#include "Vector4.h"

namespace od
{
    Vector3::Vector3() {}

    Vector3::Vector3(float x, float y, float z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }

    Vector3::Vector3(const Vector2& other, float z)
    {
        data[0] = other(0);
        data[1] = other(1);
        data[2] = z;
    }

    Vector3::Vector3(const Vector4& other)
    {
        data[0] = other(0);
        data[1] = other(1);
        data[2] = other(2);
    }

    Vector3::Vector3(const Vector<3>& other)
    : Vector<3>(other) {}
  
    Vector3 cross(Vector3 a, Vector3 b)
    {
        return Vector3((a(1) * b(2)) - (a(2) * b(1)),
                       (a(2) * b(0)) - (a(0) * b(2)),
                       (a(0) * b(1)) - (a(1) * b(0)));
    }
   
}

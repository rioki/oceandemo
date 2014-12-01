
#include "Vector3.h"

#include <cmath>

namespace od
{
    Vector3::Vector3() {}

    Vector3::Vector3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z) {}

    Vector3 operator - (const Vector3& v)
    {
        return Vector3(-v.x, -v.y, -v.z);
    }

    Vector3 operator + (const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    Vector3 operator - (const Vector3& a, const Vector3& b)
    {
        return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    Vector3 operator * (const Vector3& v, float s)
    {
        return Vector3(v.x * s, v.y * s, v.z * s);
    }

    Vector3 operator * (float s, const Vector3& v)
    {
        return v * s;
    }

    Vector3 operator / (const Vector3& v, float s)
    {
        return Vector3(v.x / s, v.y / s, v.z / s);
    }

    float dot(Vector3 a, Vector3 b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    
    Vector3 cross(Vector3 a, Vector3 b)
    {
        return Vector3((a.y * b.z) - (a.z * b.y),
                       (a.z * b.x) - (a.x * b.z),
                       (a.x * b.y) - (a.y * b.x));
    }
    
    float length(Vector3 v)
    {
        return std::sqrt(dot(v, v));
    }

    Vector3 normalize(Vector3 v)
    {
        return v / length(v);
    }
}


#include "Vector3.h"

#include <cassert>
#include <cstring>
#include <cmath>

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

    Vector3::Vector3(const Vector2& other)
    {
        data[0] = other(0);
        data[1] = other(1);
        data[2] = 0.0;
    }

    Vector3::Vector3(const Vector4& other)
    {
        data[0] = other(0);
        data[1] = other(1);
        data[2] = other(2);
    }

    Vector3::Vector3(const Vector3& other)
    {
        std::memcpy(data, other.data, 3*sizeof(float));
    }

    const Vector3& Vector3::operator = (const Vector3& other)
    {
        if (this != &other)
        {
            std::memcpy(data, other.data, 3*sizeof(float));
        }
        return *this;
    }

    float& Vector3::operator () (unsigned int i)    
    {
        assert(i < 3);
        return data[i];
    }

    float Vector3::operator () (unsigned int i) const
    {
        assert(i < 3);
        return data[i];
    }

    const Vector3& Vector3::operator += (const Vector3& other)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            data[i] += other.data[i];
        }
        return *this;
    }    
    
    const Vector3& Vector3::operator -= (const Vector3& other)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            data[i] -= other.data[i];
        }
        return *this;
    }

    Vector3 operator - (const Vector3& v)
    {
        return Vector3(-v(0), -v(1), -v(2));
    }

    Vector3 operator + (const Vector3& a, const Vector3& b)
    {
        Vector3 t(a);
        t += b;
        return t;
    }

    Vector3 operator - (const Vector3& a, const Vector3& b)
    {
        Vector3 t(a);
        t -= b;
        return t;
    }

    Vector3 operator * (const Vector3& v, float s)
    {
        return Vector3(v(0) * s, v(1) * s, v(2) * s);
    }

    Vector3 operator * (float s, const Vector3& v)
    {
        return v * s;
    }

    Vector3 operator / (const Vector3& v, float s)
    {
        return Vector3(v(0) / s, v(1) / s, v(2) / s);
    }

    float dot(Vector3 a, Vector3 b)
    {
        return a(0) * b(0) + a(1) * b(1) + a(2) * b(2);
    }
    
    Vector3 cross(Vector3 a, Vector3 b)
    {
        return Vector3((a(1) * b(2)) - (a(2) * b(1)),
                       (a(2) * b(0)) - (a(0) * b(2)),
                       (a(0) * b(1)) - (a(1) * b(0)));
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

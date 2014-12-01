
#ifndef _OD_VECTOR3_H_
#define _OD_VECTOR3_H_

namespace od
{
    class Vector3
    {
    public:
        float x, y, z;

        Vector3();

        Vector3(float _x, float _y, float _z);

    };

    Vector3 operator - (const Vector3& v);

    Vector3 operator + (const Vector3& a, const Vector3& b);
    Vector3 operator - (const Vector3& a, const Vector3& b);

    Vector3 operator * (const Vector3& v, float s);
    Vector3 operator * (float s, const Vector3& v);
    Vector3 operator / (const Vector3& v, float s);

    float dot(Vector3 a, Vector3 b);
    Vector3 cross(Vector3 a, Vector3 b);

    float length(Vector3 v);
    Vector3 normalize(Vector3 v);
}

#endif

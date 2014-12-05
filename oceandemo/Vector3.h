
#ifndef _OD_VECTOR3_H_
#define _OD_VECTOR3_H_

namespace od
{
    class Vector2;
    class Vector4;

    class Vector3
    {
    public:
        Vector3();

        Vector3(float x, float y, float z);

        explicit Vector3(const Vector2& other);

        explicit Vector3(const Vector4& other);

        Vector3(const Vector3& other);

        const Vector3& operator = (const Vector3& other);

        float& operator () (unsigned int i);

        float operator () (unsigned int i) const;

        const Vector3& operator += (const Vector3& other);
        const Vector3& operator -= (const Vector3& other);

    private:
        float data[3];
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

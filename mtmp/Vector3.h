
#ifndef _OD_VECTOR3_H_
#define _OD_VECTOR3_H_

#include "Vector.h"

namespace od
{
    class Vector2;
    class Vector4;

    class Vector3 : public Vector<3>
    {
    public:
        Vector3();

        Vector3(float x, float y, float z);

        explicit Vector3(const Vector2& other, float z = 0.0f);

        explicit Vector3(const Vector4& other);

        Vector3(const Vector<3>& other);
    };

    Vector3 cross(Vector3 a, Vector3 b);    
}

#endif

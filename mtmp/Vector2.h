
#ifndef _OD_VECTOR2_H_
#define _OD_VECTOR2_H_

#include "Vector.h"

namespace od
{
    class Vector3;
    class Vector4;
    
    class Vector2 : public Vector<2>
    {
    public:

        Vector2();

        Vector2(float x, float y);

        Vector2(const Vector3& other);

        Vector2(const Vector4& other);

        Vector2(const Vector<2>& other);        
    };
}

#endif

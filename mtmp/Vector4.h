
#ifndef _OD_VECTOR4_H_
#define _OD_VECTOR4_H_

#include "Vector.h"

namespace od
{
    class Vector2;
    class Vector3;
    
    class Vector4 : public Vector<4>
    {
    public:
        Vector4();

        Vector4(float x, float y, float z, float m);
        
        Vector4(const Vector2& other, float z, float m);

        Vector4(const Vector3& other, float m);

        Vector4(const Vector<4>& other);

        
       
    };
}

#endif

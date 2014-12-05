
#include "Vector2.h"

#include <cassert>
#include <cstring>

namespace od
{
    Vector2::Vector2() {}

    Vector2::Vector2(float x, float y)
    {
        data[0] = x;
        data[1] = y;
    }

    Vector2::Vector2(const Vector2& other)
    {
        std::memcpy(data, other.data, 2*sizeof(float));
    }

    const Vector2& Vector2::operator = (const Vector2& other)
    {
        if (this != &other)
        {
            std::memcpy(data, other.data, 2*sizeof(float));
        }
        return *this;
    }

    float& Vector2::operator () (unsigned int i)    
    {
        assert(i < 2);
        return data[i];
    }

    float Vector2::operator () (unsigned int i) const
    {
        assert(i < 2);
        return data[i];
    }
}


#ifndef _OD_VECTOR2_H_
#define _OD_VECTOR2_H_

namespace od
{
    class Vector2
    {
    public:

        Vector2();

        Vector2(float x, float y);

        Vector2(const Vector2& other);

        const Vector2& operator = (const Vector2& other);

        float& operator () (unsigned int i);
        float operator () (unsigned int i) const;

    private:
        float data[2];

    };
}

#endif

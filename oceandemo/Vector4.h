
#ifndef _OD_VECTOR4_H_
#define _OD_VECTOR4_H_

namespace od
{
    class Vector4 
    {
    public:
        Vector4();

        Vector4(float x, float y, float z, float m);

        Vector4(const Vector4& other);

        const Vector4& operator = (const Vector4& other);

        float& operator () (unsigned int i);
        float operator () (unsigned int i) const;

    private:
        float data[4];
    };
}

#endif

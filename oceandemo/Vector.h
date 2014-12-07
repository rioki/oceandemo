
#ifndef _OD_VECTOR_H_
#define _OD_VECTOR_H_

#include <cassert>
#include <cstring>

namespace od
{
    template <unsigned int N>
    class Vector
    {
    public:
        Vector() {}

        Vector(const Vector<N>& other) 
        {
            std::memcpy(data, other.data, N * sizeof(float));
        }

        const Vector<N>& operator = (const Vector<N>& other)
        {
            if (this != &other)
            {
                std::memcpy(data, other.data, N * sizeof(float));
            }
            return *this;
        }

        const Vector<N>& operator += (const Vector<N>& other)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] += other.data[i];
            }
            return *this;
        }

        const Vector<N>& operator -= (const Vector<N>& other)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                data[i] -= other.data[i];
            }
            return *this;
        }

        float& operator () (unsigned int i)
        {
            assert(i < N);
            return data[i];
        }

        float operator () (unsigned int i) const
        {
            assert(i < N);
            return data[i];
        }

        const float* c_array() const
        {
            return data;
        }

    protected:
        float data[N];
    };

    template <unsigned int N>
    Vector<N> operator + (const Vector<N>& v)
    {
        return v;
    }

    template <unsigned int N>
    Vector<N> operator - (const Vector<N>& v)
    {
        Vector<N> r;
        for (unsigned int i = 0; i < N; i++)
        {
            r(i) = -v(i);
        }
        return r;
    }

    template <unsigned int N>
    Vector<N> operator + (const Vector<N>& a, const Vector<N>& b)
    {
        Vector<N> r(a);
        r += b;
        return r;
    }

    template <unsigned int N>
    Vector<N> operator - (const Vector<N>& a, const Vector<N>& b)
    {
        Vector<N> r(a);
        r -= b;
        return r;
    }

    template <unsigned int N>
    Vector<N> operator * (const Vector<N>& v, float s)
    {
        Vector<N> r;
        for (unsigned int i = 0; i < N; i++)
        {
            r(i) = v(i) * s;
        }
        return r;
    }

    template <unsigned int N>
    Vector<N> operator * (float s, const Vector<N>& v)
    {
         return v * s;
    }

    template <unsigned int N>
    float dot(const Vector<N>& a, const Vector<N>& b) 
    {
        float r = 0;
        for (unsigned int i = 0; i < N; i++)
        {
            r += a(i) * b(i);
        }
        return r;
    }

    template <unsigned int N>
    float length(Vector<N> v)
    {
        return std::sqrt(dot(v, v));
    }

    template <unsigned int N>
    Vector<N> normalize(Vector<N> v)
    {
        return v * (1 / length(v));
    }
}

#endif

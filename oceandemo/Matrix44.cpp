
#include "Matrix44.h"

#include <cassert>
#include <cstring>
#include <cmath>

#define PI 3.1415926535897932384626433832795f

namespace od
{
    Matrix44::Matrix44() {}

    Matrix44::Matrix44(float v) 
    {
        std::memset(data, 0, 16 * sizeof(float));
        data[0] = data[5] = data[10] = data[15] = v;        
    }

    Matrix44::Matrix44(float v0, float v4, float v8,  float v12,
                       float v1, float v5, float v9,  float v13,
                       float v2, float v6, float v10, float v14,
                       float v3, float v7, float v11, float v15)
    {
        data[0] = v0;
        data[1] = v1;
        data[2] = v2;
        data[3] = v3;
        data[4] = v4;
        data[5] = v5;
        data[6] = v6;
        data[7] = v7;
        data[8] = v8;
        data[9] = v9;
        data[10] = v10;
        data[11] = v11;
        data[12] = v12;
        data[13] = v13;
        data[14] = v14;
        data[15] = v15;
    }

    Matrix44::Matrix44(const Matrix44& m)
    {
        std::memcpy(data, m.data, 16 * sizeof(float));
    }

    const Matrix44& Matrix44::operator = (const Matrix44& m)
    {
        if (this != &m) 
        {
            std::memcpy(data, m.data, 16 * sizeof(float));
        }
        return *this;
    }

    float& Matrix44::operator () (unsigned int i, unsigned j)
    {
        assert(i < 4 && j < 4);
        return data[i * 4 + j];
    }

    float Matrix44::operator () (unsigned int i, unsigned j) const
    {
        assert(i < 4 && j < 4);
        return data[i * 4 + j];
    }

    const float* Matrix44::c_array() const
    {
        return data;
    }

    Matrix44 operator + (const Matrix44& a, const Matrix44& b)
    {
        Matrix44 tmp;

        for (unsigned int i = 0; i < 4; i++) 
        {
            for (unsigned int j = 0; j < 4; j++) 
            {
                tmp(i, j) = a(i, j) + b(i, j);
            }
        }

        return tmp;
    }

    Matrix44 operator - (const Matrix44& a, const Matrix44& b)
    {
        Matrix44 tmp;

        for (unsigned int i = 0; i < 4; i++) 
        {
            for (unsigned int j = 0; j < 4; j++) 
            {
                tmp(i, j) = a(i, j) - b(i, j);
            }
        }

        return tmp;
    }

    Matrix44 operator * (const Matrix44& a, const Matrix44& b)
    {
        Matrix44 tmp;

        for (unsigned int i = 0; i < 4; i++)
        {
            for (unsigned int j = 0; j < 4; j++)
            {
                for (unsigned int k = 0; k < 4; k++)
                {
                    tmp(i, j) += a(k, j) * b(i, k);
                }                
            }
        }

        return tmp;
    }
    
    Vector4 operator * (const Matrix44& m, const Vector4& v)
    {
        Vector4 r(0, 0, 0, 0);
        
        for (unsigned int i = 0; i < 4; i++)
        {
            for (unsigned int j = 0; j < 4; j++)
            {
               r(i) += m(j,i) * v(j); 
            }
        }
        
        return r;
    }    

    Matrix44 frustum(float left, float right, float bottom, float top, float znear, float zfar)
    {
        float temp1 = 2.0f * znear;
        float temp2 = right - left;
        float temp3 = top - bottom;
        float temp4 = zfar - znear;

        return Matrix44(temp1/temp2,         0.0,  (right + left) / temp2,                     0.0,
                                0.0, temp1/temp3,  (top + bottom) / temp3,                     0.0,
                                0.0,         0.0, (-zfar - znear) / temp4, (-temp1 * zfar) / temp4,
                                0.0,         0.0,                      -1,                     0.0);       
    }

    Matrix44 perspective(float fov, float aspect, float znear, float zfar)
    {
        float ymax, xmax;
        ymax = znear * std::tan(fov * PI / 360.0f);
        xmax = ymax * aspect;
        return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    Matrix44 lookat(Vector3 position, Vector3 target, Vector3 up)
    {
        Vector3 forward = normalize(target - position);

        Vector3 side    = normalize(cross(forward, up));
        // correct up to be perfectly perpendicular
        Vector3 up2     = cross(side, forward);

        Matrix44 r(    side(0),     side(1),     side(2), 0.0,
                         up(0),       up(1),       up(2), 0.0,
                   -forward(0), -forward(1), -forward(2), 0.0,
                           0.0,         0.0,         0.0, 1.0);
        translate(r, position);
        return r;

    }

    void translate(Matrix44& m, const Vector3& p)
    {
        m(3, 0) = m(0, 0)*p(0) + m(1, 0)*p(1) + m(2, 0)*p(2) + m(3, 0);
        m(3, 1) = m(0, 1)*p(0) + m(1, 1)*p(1) + m(2, 1)*p(2) + m(3, 1);
        m(3, 2) = m(0, 2)*p(0) + m(1, 2)*p(1) + m(2, 2)*p(2) + m(3, 2);
        m(3, 3) = m(0, 3)*p(0) + m(1, 3)*p(1) + m(2, 3)*p(2) + m(3, 3);
    }
}
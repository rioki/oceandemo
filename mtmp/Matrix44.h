
#ifndef _OD_MATRIX44_H_
#define _OD_MATRIX44_H_

#include "Vector3.h"
#include "VEctor4.h"

#include "Matrix.h"

namespace od
{
    class Matrix44 : public Matrix<4, 4>
    {
    public:

        Matrix44();

        Matrix44(float v);

        Matrix44(float v0, float v4, float v8,  float v12,
                 float v1, float v5, float v9,  float v13,
                 float v2, float v6, float v10, float v14,
                 float v3, float v7, float v11, float v15);

        Matrix44(const Matrix<4, 4>& other);
    };    

    Matrix44 frustum(float left, float right, float bottom, float top, float znear, float zfar);
    Matrix44 perspective(float fov, float aspect, float znear, float zfar);
    Matrix44 lookat(Vector3 position, Vector3 target, Vector3 up);

    Matrix44 translate(const Matrix44& m, const Vector3& p);
    Matrix44 rotate(const Matrix44& m, const Vector3& v, float angle);

    Vector3 transform(const Matrix44& m, const Vector3& v);
}

#endif

/*
    rgm - Rioki's Graphic Math Library

    Copyright (c) 2014 Sean "rioki" Farrell

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef _RGM_GL_H_
#define _RGM_GL_H_

#include "vector.h"
#include "matrix.h"
#include <cmath>

#define PI 3.1415926535897932384626433832795f

namespace rgm
{
    template <typename T>
    matrix4<T> frustum(T left, T right, T bottom, T top, T znear, T zfar)
    {
        T temp1 = (T)2 * znear;
        T temp2 = right - left;
        T temp3 = top - bottom;
        T temp4 = zfar - znear;

        return matrix4<T>  (temp1/temp2,        (T)0,  (right + left) / temp2,                    (T)0,
                                   (T)0, temp1/temp3,  (top + bottom) / temp3,                    (T)0,
                                   (T)0,        (T)0, (-zfar - znear) / temp4, (-temp1 * zfar) / temp4,
                                   (T)0,        (T)0,                      -1,                    (T)0);       
    }

    template <typename T>
    matrix4<T> perspective(T fov, T aspect, T znear, T zfar)
    {
        T ymax = znear * std::tan(fov * PI / 360.0f);
        T xmax = ymax * aspect;
        return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    template <typename T>
    matrix4<T> lookat(vector<T, 3> position, vector<T, 3> target, vector<T, 3> up)
    {
        vector<T, 3> forward = normalize(position - target);

        vector<T, 3> side    = normalize(cross(forward, up));
        // correct up to be perfectly perpendicular
        vector<T, 3> up2     = cross(side, forward);

        matrix4<T>   r(    side[0],     side[1],     side[2], (T)0,
                             up[0],       up[1],       up[2], (T)0,
                       -forward[0], -forward[1], -forward[2], (T)0,
                              (T)0,        (T)0,        (T)0, (T)1);
        r = translate(r, position);
        return r;

    }

    template <typename T>
    matrix<T, 4> translate(const matrix<T, 4>& m, const vector<T, 3>& p)
    {
        matrix<T, 4> m2(m);
        
        m2[3][0] = m[0][0] * p[0] + m[1][0] * p[1] + m[2][0] * p[2] + m[3][0];
        m2[3][1] = m[0][1] * p[0] + m[1][1] * p[1] + m[2][1] * p[2] + m[3][1];
        m2[3][2] = m[0][2] * p[0] + m[1][2] * p[1] + m[2][2] * p[2] + m[3][2];
        m2[3][3] = m[0][3] * p[0] + m[1][3] * p[1] + m[2][3] * p[2] + m[3][3];

        return m2;
    }

    template <typename T>
    matrix<T, 4> rotate(const matrix<T, 4>& m, const vector<T, 3>& v, T angle)
    {
        T a = angle * PI / 360.0f;
        T c = std::cos(a);
        T s = std::sin(a);
        
        vector<T, 3> axis = normalize(v);

        vector<T, 3> t = axis * (1 - c);

        matrix<T, 3> d(1);
        d[0][0] = c + t[0] * axis[0];
        d[0][1] = 0 + t[0] * axis[1] + s * axis[2];
        d[0][2] = 0 + t[0] * axis[2] - s * axis[1];

        d[1][0] = 0 + t[1] * axis[0] - s * axis[2];
        d[1][1] = c + t[1] * axis[1];
        d[1][2] = 0 + t[1] * axis[2] + s * axis[0];

        d[2][0] = 0 + t[2] * axis[0] + s * axis[1];
        d[2][1] = 0 + t[2] * axis[1] - s * axis[0];
        d[2][2] = c + t[2] * axis[2];
        
        matrix<T, 4> r;
        r[0] = m[0] * d[0][0] + m[1] * d[0][1] + m[2] * d[0][2];
        r[1] = m[0] * d[1][0] + m[1] * d[1][1] + m[2] * d[1][2];
        r[2] = m[0] * d[2][0] + m[1] * d[2][1] + m[2] * d[2][2];
        r[3] = m[3];
        
        return r;
    }

    template <typename T>
    vector<T, 3> transform(const matrix<T, 4>& m, const vector<T, 3>& v)
    {
        return vector<T, 3>(m * vector<T, 4>(v, 0.0f));
    }

}

#undef PI

#endif

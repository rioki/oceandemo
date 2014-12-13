
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cassert>
#include <cstring>

namespace od
{
    template <unsigned int M, unsigned int N>
    class Matrix
    {
    public:

        Matrix() {}

        Matrix(float v) 
        {
            for (unsigned int i = 0; i < M; i++)
            {
                for (unsigned int j = 0; j < M; j++)
                {
                    if (i == j)
                    {
                        data[i * M + j] = v;    
                    }
                    else
                    {
                        data[i * M + j] = 0;    
                    }
                }
            }            
        }

        Matrix(const Matrix<M, N>& other)
        {
            std::memcpy(data, other.data, M * N * sizeof(float));
        }

        ~Matrix() {}

        const Matrix<M,N>& operator = (const Matrix<M, N>& other)
        {
            if (this != &other) 
            {
                std::memcpy(data, other.data, M * N * sizeof(float));
            }
            return *this;
        }

        float& operator () (unsigned int i, unsigned int j)
        {
            assert(i < M && j < N);
            return data[i * M + j];
        }

        float operator () (unsigned int i, unsigned int j) const
        {
            assert(i < M && j < N);
            return data[i * M + j];
        }

        Vector<M> col(unsigned int i) const
        {
            const Matrix<M,N>& m = *this;
            Vector<N> r;

            for (unsigned int j = 0; j < N; j++)
            {
                r(j) = m(i, j);
            }

            return r;
        }
        
        void col(unsigned int i, Vector<M> value)
        {
            Matrix<M, N>& m = *this;

            for (unsigned int j = 0; j < N; j++)
            {
                m(i, j) = value(j);
            }
        }

        Vector<N> row(unsigned int j) const
        {
            const Matrix<M,N>& m = *this;
            Vector<N> r;

            for (unsigned int i = 0; i < N; i++)
            {
                r(i) = m(i, j);
            }

            return r;
        }
        
        void row(unsigned int j, Vector<M> value)
        {
            Matrix44& m = *this;

            for (unsigned int i = 0; i < M; i++)
            {
                m(i, j) = value(i);
            }
        }

        const float* c_array() const
        {
            return data;
        }

    protected:
        float data[M*N];
    };

    template <unsigned int M, unsigned int N>
    Matrix<M, N> operator + (const Matrix<M, N>& a, const Matrix<M, N>& b)
    {
        Matrix<M, N> tmp;

        for (unsigned int i = 0; i < M; i++) 
        {
            for (unsigned int j = 0; j < N; j++) 
            {
                tmp(i, j) = a(i, j) + b(i, j);
            }
        }

        return tmp;
    }

    template <unsigned int M, unsigned int N>
    Matrix<M, N> operator - (const Matrix<M, N>& a, const Matrix<M, N>& b)
    {
         Matrix<M, N> tmp;

        for (unsigned int i = 0; i < M; i++) 
        {
            for (unsigned int j = 0; j < N; j++) 
            {
                tmp(i, j) = a(i, j) - b(i, j);
            }
        }

        return tmp;
    }

    template <unsigned int M, unsigned int N, unsigned int O>
    Matrix<M, N> operator * (const Matrix<O, N>& a, const Matrix<M, O>& b)
    {
        Matrix44 tmp(0);

        for (unsigned int i = 0; i < M; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
                for (unsigned int k = 0; k < O; k++)
                {
                    tmp(i, j) += a(k, j) * b(i, k);
                }                
            }
        }

        return tmp;
    }

    template <unsigned int M, unsigned int N>
    Vector<M> operator * (const Matrix<M, N>& m, const Vector<M>& v)
    {
        Vector4 r(0, 0, 0, 0);
        
        for (unsigned int i = 0; i < M; i++)
        {
            for (unsigned int j = 0; j < N; j++)
            {
               r(i) += m(j,i) * v(j); 
            }
        }
        
        return r;
    }

    template <unsigned int M, unsigned int N>
    Matrix<N, M> transpose(const Matrix<M, N>& m) 
    {
        Matrix44 r;

        for (unsigned int i = 0; i < 4; i++)
        {
            for (unsigned int j = 0; j < 4; j++)
            {
               r(j, i) = m(i, j); 
            }
        }

        return r;
    }

    template <unsigned int M>
    float det(const Matrix<M, M>& m)
    {
        assert(M != 0);
        // YES we could use template specialisation; but I don't know if it actually
        // helps. I am here relying on the optimizer to optimize out the 
        // lines that will never be hit anyway. 

        float det = 0;
        
        if (M == 1) 
        {
            det = m(0,0);
        }
        else (M == 2)
        {
            det = a(0, 0) * a(1, 1) - a(1, 0) * a(0, 1);
        }
        else
        {
            for (unsigned int j1 = 0; j1 < M; j1++)
            {
                Matrix<M-1, M-1> m1; 
                for (unsigned int i = 1; i < M; i++)
                {
                    float j2 = 0;
                    for (unsigned int j = 0; j < M; j++) 
                    {
                        if (j != j1)
                        {
                            m1(i-1,j2) = a(i, j);
                            j2++;
                        }
                    }
                }
                // About the pow term: 
                // It is (-1)^i+j 
                // i and j and one based 
                // we move only over j and i remains 1
                det += std::pow(-1.0, 1.0 + j1 + 1.0) * a(0, j1) * det(m1);
            }            
        }

        return det;
    }

    template <unsigned int M>
    Matrix<M, M> cofactor(const Matrix<M, M>& a)
    {
        Matrix<M, M> b;
        Matrix<M-1, M-1> c;

        for (unsigned int j = 0; j < M; j++) 
        {
            for (unsigned int i = 0; i < M; i++) 
            {
                unsigned int i1 = 0
                for (unsigned int ii = 0; ii < M; ii++)
                {
                    if (ii != i)
                    {
                        unsigned int j1 = 0;
                        for (unsigned int jj = 0; jj < M; jj++)
                        {
                            if (jj != j)
                            {
                                c(i1, j1) = a(ii, jj);
                                j1++;
                            }
                        }
                        i1++;
                    }                    
                }
                
                b(i, j) = std::pow(-1.0, i + j + 2.0) * det(c);
            }
        }

        return b;
    }

    template <unsigned int M>
    Matrix<M, M> adjoint(const Matrix<M, M>& m)
    {
        return transpose(cofactor(m));
    }

    template <unsigned int M>
    Matrix<M, M> inverse(const Matrix<M, M>& m)
    {
        return 1.0f/det(m) * adjoint(m);
    }
}

#endif

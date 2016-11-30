#ifndef MATH_MAT4X4_H
#define MATH_MAT4X4_H

#include "base/macros.h"
#include "math/vec4.h"

class Mat4x4
{
public:
    Mat4x4();
    Mat4x4(const Mat4x4& m);
    ~Mat4x4();

    Mat4x4& operator=(const Mat4x4& m);

    friend inline const Vec4 operator*(const Mat4x4& m, const Vec4& v);
    friend inline const Mat4x4 operator*(const Mat4x4& m1, const Mat4x4& m2);

    inline const float* getMatAddress() const { return &_m[0][0];}

    inline float& operator()(int i, int j)
    {
        TE_ASSERT(i < 4, "row must be less than four");
        TE_ASSERT(j < 4, "column must be less than four");
        return _m[i][j];
    }

    inline const float& operator()(int i, int j) const
    {
        TE_ASSERT(i < 4, "row must be less than four");
        TE_ASSERT(j < 4, "column must be less than four");
        return _m[i][j];
    }

    static Mat4x4 zero()
    {
        Mat4x4 mat;
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                mat(i, j) = 0;
        return mat;
    }

    static Mat4x4 identity()
    {
        Mat4x4 mat;
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                if (i == j) mat(i, j) = 1;
                else mat(i, j) = 0;
        return mat;
    }

private:
    float _m[4][4];
};

inline const Vec4 operator*(const Mat4x4& m, const Vec4& v)
{
    float x = m(0, 0) * v.x() + m(0, 1) * v.y() + m(0, 2) * v.z() + m(0, 3) * v.w();
    float y = m(1, 0) * v.x() + m(1, 1) * v.y() + m(1, 2) * v.z() + m(1, 3) * v.w();
    float z = m(2, 0) * v.x() + m(2, 1) * v.y() + m(2, 2) * v.z() + m(2, 3) * v.w();
    float w = m(3, 0) * v.x() + m(3, 1) * v.y() + m(3, 2) * v.z() + m(3, 3) * v.w();
    return Vec4(x, y, z, w);
}

inline const Mat4x4 operator*(const Mat4x4& m1, const Mat4x4& m2)
{
    Mat4x4 mat;
    for (int i = 0; i < 4; ++ i)
        for (int j = 0; j < 4; ++ j)
            for (int k = 0; k < 4; ++ k)
                mat(i, j) += m1(i, k) * m2(k, j);
    return mat;
}




#endif // MATH_MAT4X4_H
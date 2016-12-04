
#include "Core/math/Matrix.h"

namespace te
{
    Mat4x4::Mat4x4()
    {
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                _m[i][j] = 0;
    }

    Mat4x4::Mat4x4(const Mat4x4& m)
    {
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                _m[i][j] = m(i, j);
    }

    Mat4x4::~Mat4x4(){}

    Mat4x4& Mat4x4::operator=(const Mat4x4& m)
    {
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                _m[i][j] = m(i, j);
        return *this;
    }

    void Mat4x4::computeDeterminant()
    {

    }

    void Mat4x4::computeInverse()
    {

    }

    void Mat4x4::computeTranspose()
    {

    }

    Mat4x4 Mat4x4::zero()
    {
        Mat4x4 mat;
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                mat(i, j) = 0;
        return mat;
    }

    Mat4x4 Mat4x4::identity()
    {
        Mat4x4 mat;
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                if (i == j) mat(i, j) = 1;
                else mat(i, j) = 0;
        return mat;
    }

    // this relationship means that we use left-handed coordinate
    Mat4x4 Mat4x4::ortho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        Mat4x4 mat;
        mat(0, 0) = 2 / (right - left);
        mat(1, 1) = 2 / (top - bottom);
        mat(2, 2) = -2 / (zfar - znear);
        mat(0, 3) = - (right + left) / (right - left);
        mat(1, 3) = - (top + bottom) / (top - bottom);
        mat(2, 3) = - (zfar + znear) / (zfar - znear);
        mat(3, 3) = 1;

        return mat;
    }

    Mat4x4 Mat4x4::perspective(float fov, float aspect, float znear, float zfar)
    {

    }
}



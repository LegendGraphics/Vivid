
#include "Core/math/Matrix.h"

namespace te
{
    Mat4x4::Mat4x4()
    {
        SET_ROW(0,  1, 0, 0, 0)
        SET_ROW(1,  0, 1, 0, 0)
        SET_ROW(2,  0, 0, 1, 0)
        SET_ROW(3,  0, 0, 0, 1)
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

    void Mat4x4::makeZero()
    {
        SET_ROW(0,  0, 0, 0, 0)
        SET_ROW(1,  0, 0, 0, 0)
        SET_ROW(2,  0, 0, 0, 0)
        SET_ROW(3,  0, 0, 0, 0)
    }

    void Mat4x4::makeIdentity()
    {
        SET_ROW(0,  1, 0, 0, 0)
        SET_ROW(1,  0, 1, 0, 0)
        SET_ROW(2,  0, 0, 1, 0)
        SET_ROW(3,  0, 0, 0, 1)
    }

    void Mat4x4::makeOrtho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        float tx = - (right + left) / (right - left);
        float ty = - (top + bottom) / (top - bottom);
        float tz = - (zfar + znear) / (zfar - znear);

        SET_ROW(0, 2.0/(right-left),               0.0,                0.0, 0.0)
        SET_ROW(1,              0.0,  2.0/(top-bottom),                0.0, 0.0)
        SET_ROW(2,              0.0,               0.0,  -2.0/(zfar-znear), 0.0)
        SET_ROW(3,               tx,                ty,                 tz, 1.0)
    }

    void Mat4x4::makePerspective(float fov, float aspect, float znear, float zfar)
    {
        
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
        mat.makeZero();
        return mat;
    }

    Mat4x4 Mat4x4::identity()
    {
        Mat4x4 mat;
        mat.makeIdentity();
        return mat;
    }

    Mat4x4 Mat4x4::ortho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        Mat4x4 mat;
        mat.makeOrtho(left, right, bottom, top, znear, zfar);
        return mat;
    }

    Mat4x4 Mat4x4::perspective(float fov, float aspect, float znear, float zfar)
    {
        Mat4x4 mat;
        mat.perspective(fov, aspect, znear, zfar);
        return mat;
    }
}



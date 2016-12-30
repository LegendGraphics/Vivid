
#include "math/Matrix.h"

namespace te
{
    Mat4x4::Mat4x4()
    {
        SET_ROW(0,  1, 0, 0, 0)
        SET_ROW(1,  0, 1, 0, 0)
        SET_ROW(2,  0, 0, 1, 0)
        SET_ROW(3,  0, 0, 0, 1)
    }

    Mat4x4::Mat4x4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33)
    {
        SET_ROW(0, m00, m01, m02, m03)
        SET_ROW(1, m10, m11, m12, m13)
        SET_ROW(2, m20, m21, m22, m23)
        SET_ROW(3, m30, m31, m32, m33)
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

    void Mat4x4::set(float m00, float m01, float m02, float m03,
                     float m10, float m11, float m12, float m13,
                     float m20, float m21, float m22, float m23,
                     float m30, float m31, float m32, float m33)
    {
        SET_ROW(0,  m00, m01, m02, m03)
        SET_ROW(1,  m10, m11, m12, m13)
        SET_ROW(2,  m20, m21, m22, m23)
        SET_ROW(3,  m30, m31, m32, m33)
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
        float tan_fov = tan(fov*0.5);
        float right  =  tan_fov * aspect * znear;
        float left   = -right;
        float top    =  tan_fov * znear;
        float bottom =  -top;
        makeFrustum(left, right, bottom, top, znear, zfar);
    }

    void Mat4x4::makeFrustum(float left, float right, float bottom, float top, float znear, float zfar)
    {
        float A = (right + left) / (right - left);
        float B = (top + bottom) / (top - bottom);
        float C = -(zfar + znear) / (zfar - znear);
        float D = -2.0 * zfar * znear / (zfar - znear);
        float E = 2.0 * znear / (right - left);
        float F = 2.0 * znear / (top - bottom);

        SET_ROW(0,   E, 0.0,  A, 0.0)
        SET_ROW(1, 0.0,   F,  B, 0.0)
        SET_ROW(2, 0.0, 0.0,  C,   D)
        SET_ROW(3, 0.0, 0.0, -1,   0)
    }

    float Mat4x4::computeDeterminant() const
    {
        float det    =  _m[0][3]*_m[1][2]*_m[2][1]*_m[3][0] - _m[0][2]*_m[1][3]*_m[2][1]*_m[3][0] - 
                        _m[0][3]*_m[1][1]*_m[2][2]*_m[3][0] + _m[0][1]*_m[1][3]*_m[2][2]*_m[3][0] +
                        _m[0][2]*_m[1][1]*_m[2][3]*_m[3][0] - _m[0][1]*_m[1][2]*_m[2][3]*_m[3][0] - 
                        _m[0][3]*_m[1][2]*_m[2][0]*_m[3][1] + _m[0][2]*_m[1][3]*_m[2][0]*_m[3][1] +
                        _m[0][3]*_m[1][0]*_m[2][2]*_m[3][1] - _m[0][0]*_m[1][3]*_m[2][2]*_m[3][1] - 
                        _m[0][2]*_m[1][0]*_m[2][3]*_m[3][1] + _m[0][0]*_m[1][2]*_m[2][3]*_m[3][1] +
                        _m[0][3]*_m[1][1]*_m[2][0]*_m[3][2] - _m[0][1]*_m[1][3]*_m[2][0]*_m[3][2] - 
                        _m[0][3]*_m[1][0]*_m[2][1]*_m[3][2] + _m[0][0]*_m[1][3]*_m[2][1]*_m[3][2] +
                        _m[0][1]*_m[1][0]*_m[2][3]*_m[3][2] - _m[0][0]*_m[1][1]*_m[2][3]*_m[3][2] - 
                        _m[0][2]*_m[1][1]*_m[2][0]*_m[3][3] + _m[0][1]*_m[1][2]*_m[2][0]*_m[3][3] +
                        _m[0][2]*_m[1][0]*_m[2][1]*_m[3][3] - _m[0][0]*_m[1][2]*_m[2][1]*_m[3][3] - 
                        _m[0][1]*_m[1][0]*_m[2][2]*_m[3][3] + _m[0][0]*_m[1][1]*_m[2][2]*_m[3][3];
        return det;
    }

    // Cramer's rule
    // inv(A) = adj(A) / det(A)
    // http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
    const Mat4x4 Mat4x4::computeInverse() const
    {
        Mat4x4 inv_mat;
        inv_mat._m[0][0] = _m[1][2]*_m[2][3]*_m[3][1] - _m[1][3]*_m[2][2]*_m[3][1] + _m[1][3]*_m[2][1]*_m[3][2] - _m[1][1]*_m[2][3]*_m[3][2] - _m[1][2]*_m[2][1]*_m[3][3] + _m[1][1]*_m[2][2]*_m[3][3];
        inv_mat._m[0][1] = _m[0][3]*_m[2][2]*_m[3][1] - _m[0][2]*_m[2][3]*_m[3][1] - _m[0][3]*_m[2][1]*_m[3][2] + _m[0][1]*_m[2][3]*_m[3][2] + _m[0][2]*_m[2][1]*_m[3][3] - _m[0][1]*_m[2][2]*_m[3][3];
        inv_mat._m[0][2] = _m[0][2]*_m[1][3]*_m[3][1] - _m[0][3]*_m[1][2]*_m[3][1] + _m[0][3]*_m[1][1]*_m[3][2] - _m[0][1]*_m[1][3]*_m[3][2] - _m[0][2]*_m[1][1]*_m[3][3] + _m[0][1]*_m[1][2]*_m[3][3];
        inv_mat._m[0][3] = _m[0][3]*_m[1][2]*_m[2][1] - _m[0][2]*_m[1][3]*_m[2][1] - _m[0][3]*_m[1][1]*_m[2][2] + _m[0][1]*_m[1][3]*_m[2][2] + _m[0][2]*_m[1][1]*_m[2][3] - _m[0][1]*_m[1][2]*_m[2][3];
        inv_mat._m[1][0] = _m[1][3]*_m[2][2]*_m[3][0] - _m[1][2]*_m[2][3]*_m[3][0] - _m[1][3]*_m[2][0]*_m[3][2] + _m[1][0]*_m[2][3]*_m[3][2] + _m[1][2]*_m[2][0]*_m[3][3] - _m[1][0]*_m[2][2]*_m[3][3];
        inv_mat._m[1][1] = _m[0][2]*_m[2][3]*_m[3][0] - _m[0][3]*_m[2][2]*_m[3][0] + _m[0][3]*_m[2][0]*_m[3][2] - _m[0][0]*_m[2][3]*_m[3][2] - _m[0][2]*_m[2][0]*_m[3][3] + _m[0][0]*_m[2][2]*_m[3][3];
        inv_mat._m[1][2] = _m[0][3]*_m[1][2]*_m[3][0] - _m[0][2]*_m[1][3]*_m[3][0] - _m[0][3]*_m[1][0]*_m[3][2] + _m[0][0]*_m[1][3]*_m[3][2] + _m[0][2]*_m[1][0]*_m[3][3] - _m[0][0]*_m[1][2]*_m[3][3];
        inv_mat._m[1][3] = _m[0][2]*_m[1][3]*_m[2][0] - _m[0][3]*_m[1][2]*_m[2][0] + _m[0][3]*_m[1][0]*_m[2][2] - _m[0][0]*_m[1][3]*_m[2][2] - _m[0][2]*_m[1][0]*_m[2][3] + _m[0][0]*_m[1][2]*_m[2][3];
        inv_mat._m[2][0] = _m[1][1]*_m[2][3]*_m[3][0] - _m[1][3]*_m[2][1]*_m[3][0] + _m[1][3]*_m[2][0]*_m[3][1] - _m[1][0]*_m[2][3]*_m[3][1] - _m[1][1]*_m[2][0]*_m[3][3] + _m[1][0]*_m[2][1]*_m[3][3];
        inv_mat._m[2][1] = _m[0][3]*_m[2][1]*_m[3][0] - _m[0][1]*_m[2][3]*_m[3][0] - _m[0][3]*_m[2][0]*_m[3][1] + _m[0][0]*_m[2][3]*_m[3][1] + _m[0][1]*_m[2][0]*_m[3][3] - _m[0][0]*_m[2][1]*_m[3][3];
        inv_mat._m[2][2] = _m[0][1]*_m[1][3]*_m[3][0] - _m[0][3]*_m[1][1]*_m[3][0] + _m[0][3]*_m[1][0]*_m[3][1] - _m[0][0]*_m[1][3]*_m[3][1] - _m[0][1]*_m[1][0]*_m[3][3] + _m[0][0]*_m[1][1]*_m[3][3];
        inv_mat._m[2][3] = _m[0][3]*_m[1][1]*_m[2][0] - _m[0][1]*_m[1][3]*_m[2][0] - _m[0][3]*_m[1][0]*_m[2][1] + _m[0][0]*_m[1][3]*_m[2][1] + _m[0][1]*_m[1][0]*_m[2][3] - _m[0][0]*_m[1][1]*_m[2][3];
        inv_mat._m[3][0] = _m[1][2]*_m[2][1]*_m[3][0] - _m[1][1]*_m[2][2]*_m[3][0] - _m[1][2]*_m[2][0]*_m[3][1] + _m[1][0]*_m[2][2]*_m[3][1] + _m[1][1]*_m[2][0]*_m[3][2] - _m[1][0]*_m[2][1]*_m[3][2];
        inv_mat._m[3][1] = _m[0][1]*_m[2][2]*_m[3][0] - _m[0][2]*_m[2][1]*_m[3][0] + _m[0][2]*_m[2][0]*_m[3][1] - _m[0][0]*_m[2][2]*_m[3][1] - _m[0][1]*_m[2][0]*_m[3][2] + _m[0][0]*_m[2][1]*_m[3][2];
        inv_mat._m[3][2] = _m[0][2]*_m[1][1]*_m[3][0] - _m[0][1]*_m[1][2]*_m[3][0] - _m[0][2]*_m[1][0]*_m[3][1] + _m[0][0]*_m[1][2]*_m[3][1] + _m[0][1]*_m[1][0]*_m[3][2] - _m[0][0]*_m[1][1]*_m[3][2];
        inv_mat._m[3][3] = _m[0][1]*_m[1][2]*_m[2][0] - _m[0][2]*_m[1][1]*_m[2][0] + _m[0][2]*_m[1][0]*_m[2][1] - _m[0][0]*_m[1][2]*_m[2][1] - _m[0][1]*_m[1][0]*_m[2][2] + _m[0][0]*_m[1][1]*_m[2][2];
        inv_mat = inv_mat * (1.0 / computeDeterminant());

        return inv_mat;
    }

    const Mat4x4 Mat4x4::computeTranspose() const
    {
        Mat4x4 transpose;
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                transpose._m[i][j] = _m[j][i];
        return transpose;
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



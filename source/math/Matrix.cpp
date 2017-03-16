
#include "math/Matrix.h"
#include "math/Quaternion.h"
#include "math/MathUtils.h"

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

    void Mat4x4::makeTranslate(float x, float y, float z)
    {
        SET_ROW(0, 1, 0, 0, x)
        SET_ROW(1, 0, 1, 0, y)
        SET_ROW(2, 0, 0, 1, z)
        SET_ROW(3, 0, 0, 0, 1)
    }

    void Mat4x4::makeScale(float x, float y, float z)
    {
        SET_ROW(0, x, 0, 0, 0)
        SET_ROW(1, 0, y, 0, 0)
        SET_ROW(2, 0, 0, z, 0)
        SET_ROW(3, 0, 0, 0, 1)
    }

    // we use quaternion to build rotation
    void Mat4x4::makeRotate(float x, float y, float z)
    {
        *this = Quaternion(Vector3(x, y, z)).convertToMatrix();
    }

    // remember we use right-hand system, so the z-axis of camera coordinate is outside of the screen,
    // that is to say znear and zfar will be negative...but many API has explicitly changed it to positive
    // and add a minus sign in the matrix construction. After that, it seems to be a left-hand system shown
    // by the interface(e.g. Wikipedia)
    // https://en.wikipedia.org/wiki/Orthographic_projection
    void Mat4x4::makeOrtho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        float tx = - (right + left) / (right - left);
        float ty = - (top + bottom) / (top - bottom);
        float tz = - (zfar + znear) / (zfar - znear);

        SET_ROW(0, 2.0/(right-left),               0.0,                0.0,  tx)
        SET_ROW(1,              0.0,  2.0/(top-bottom),                0.0,  ty)
        SET_ROW(2,              0.0,               0.0,   2.0/(zfar-znear),  tz)
        SET_ROW(3,              0.0,               0.0,                0.0, 1.0)
    }

    // fov(degree) in y-axis, aspect = width(x-axis)/height(y-axis), z-axis points outside of screen(znear and zfar < 0)
    // see http://ogldev.atspace.co.uk/www/tutorial12/tutorial12.html for more info
    // the matrix structure is different from the article since our z is negative
    void Mat4x4::makePerspective(float fov, float aspect, float znear, float zfar)
    {
        float tan_fov = std::tan(degree_to_radians(fov*0.5));
        float zrange = znear - zfar;

        SET_ROW(0, -1.0 / (aspect * tan_fov),            0.0,                       0.0,                         0.0)
        SET_ROW(1,                       0.0, -1.0 / tan_fov,                       0.0,                         0.0)
        SET_ROW(2,                       0.0,            0.0, (- zfar - znear) / zrange, 2.0 * znear * zfar / zrange)
        SET_ROW(3,                       0.0,            0.0,                       1.0,                         0.0)
    }

    // right-hand of camera coordinate, x-y plane is the screen
    //                  ^ y                     
    //                  |                       
    //                  |                       
    //                  o----->  x              
    //                 /                        
    //                /                         
    //               z                          
    void Mat4x4::makeLookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        Vector3 z_axis = eye - center;
        z_axis.normalize();
        Vector3 x_axis = Vector3::cross(up, z_axis);
        x_axis.normalize();
        Vector3 y_axis = Vector3::cross(z_axis, x_axis);
        y_axis.normalize();

        SET_ROW(0, x_axis.x, x_axis.y, x_axis.z, -Vector3::dot(x_axis, eye))
        SET_ROW(1, y_axis.x, y_axis.y, y_axis.z, -Vector3::dot(y_axis, eye))
        SET_ROW(2, z_axis.x, z_axis.y, z_axis.z, -Vector3::dot(z_axis, eye))
        SET_ROW(3,      0.0,      0.0,      0.0,                          1)
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

    Mat4x4 Mat4x4::translate(float x, float y, float z)
    {
        Mat4x4 mat;
        mat.makeTranslate(x, y, z);
        return mat;
    }

    Mat4x4 Mat4x4::scale(float x, float y, float z)
    {
        Mat4x4 mat;
        mat.makeScale(x, y, z);
        return mat;
    }

    Mat4x4 Mat4x4::rotate(float x, float y, float z)
    {
        Mat4x4 mat;
        mat.makeRotate(x, y, z);
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
        mat.makePerspective(fov, aspect, znear, zfar);
        return mat;
    }

    Mat4x4 Mat4x4::lookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        Mat4x4 mat;
        mat.makeLookAt(eye, center, up);
        return mat;
    }

}



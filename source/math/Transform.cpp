#include "math/Transform.h"

namespace te
{
    Transform::Transform()
    {
        _m = Mat4x4::identity();
    }

    Transform::Transform(const Mat4x4& m)
        :_m(m)
    {
    }

    Transform::Transform(const Transform& t)
        : _m(t._m)
    {
    }

    Transform& Transform::operator=(const Transform& t)
    {
        _m = t._m;
        return *this;
    }

    void Transform::translate(float x, float y, float z)
    {
        Mat4x4 mat = Mat4x4::identity();
        mat(0, 3) = x;
        mat(1, 3) = y;
        mat(2, 3) = z;
        _m = mat * _m;
    }

    Transform Transform::trans(float x, float y)
    {
        Mat4x4 mat = Mat4x4::identity();
        mat(0, 3) = x;
        mat(1, 3) = y;

        return Transform(mat);
    }

    // this relationship means that we use left-handed coordinate
    Transform Transform::ortho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        Mat4x4 mat;
        mat(0, 0) = 2 / (right - left);
        mat(1, 1) = 2 / (top - bottom);
        mat(2, 2) = -2 / (zfar - znear);
        mat(0, 3) = -(right + left) / (right - left);
        mat(1, 3) = -(top + bottom) / (top - bottom);
        mat(2, 3) = -(zfar + znear) / (zfar - znear);
        mat(3, 3) = 1;

        return Transform(mat);
    }

    Transform Transform::lookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        Mat4x4 mat;
        Vector3 z_axis = center - eye;
        z_axis.normalize();
        
        Vector3 x_axis = Vector3::cross(z_axis, up);
        x_axis.normalize();

        Vector3 y_axis = Vector3::cross(x_axis, z_axis);
        y_axis.normalize();


        mat(0, 0) = x_axis.x;
        mat(0, 1) = x_axis.y;
        mat(0, 2) = x_axis.z;
        mat(0, 3) = -Vector3::dot(x_axis, eye);

        mat(1, 0) = y_axis.x;
        mat(1, 1) = y_axis.y;
        mat(1, 2) = y_axis.z;
        mat(1, 3) = -Vector3::dot(y_axis, eye);

        mat(2, 0) = z_axis.x;
        mat(2, 1) = z_axis.y;
        mat(2, 2) = z_axis.z;
        mat(2, 3) = -Vector3::dot(z_axis, eye);

        mat(3, 3) = 1;

        return Transform(mat);
    }

    Transform Transform::lookAt(const Vector2& eye)
    {
        Mat4x4 mat = Mat4x4::identity();
        mat(0, 3) = -eye.x;
        mat(1, 3) = -eye.y;
        mat(1, 1) = 1;

        return Transform(mat);
    }

    Transform Transform::identity()
    {
        return Transform(Mat4x4::identity());
    }
}
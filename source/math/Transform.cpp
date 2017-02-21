#include "math/Transform.h"

namespace te
{
    Transform::Transform()
    {
        _m = Matrix::identity();
    }

    Transform::Transform(const Matrix& m)
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

    void Transform::makeTranslate(float x, float y, float z)
    {
        _m = Matrix::translate(x, y, z) * _m;
    }

    void Transform::makeScale(float x, float y, float z)
    {
        _m = Matrix::scale(x, y, z) * _m;
    }

    void Transform::makeRotate(float x, float y, float z)
    {
        _m = Matrix::rotate(x, y, z) * _m;
    }

    Transform Transform::translate(float x, float y, float z)
    {
        Matrix mat = Matrix::translate(x, y, z);
        return Transform(mat);
    }

    Transform Transform::scale(float x, float y, float z)
    {
        Matrix mat = Matrix::scale(x, y, z);
        return Transform(mat);
    }

    Transform Transform::rotate(float x, float y, float z)
    {
        Matrix mat = Matrix::rotate(x, y, z);
        return Transform(mat);
    }

    // this relationship means that we use left-handed coordinate
    Transform Transform::ortho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        Matrix mat = Matrix::ortho(left, right, bottom, top, znear, zfar);
        return Transform(mat);
    }

    Transform Transform::lookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        Matrix mat;
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

    Transform Transform::identity()
    {
        return Transform(Matrix::identity());
    }
}
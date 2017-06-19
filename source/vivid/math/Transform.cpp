#include "vivid/math/Transform.h"

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

    Transform Transform::rotateX(float x)
    {
        Matrix mat = Matrix::rotateX(x);
        return Transform(mat);
    }

    Transform Transform::rotateY(float y)
    {
        Matrix mat = Matrix::rotateY(y);
        return Transform(mat);
    }

    Transform Transform::rotateZ(float z)
    {
        Matrix mat = Matrix::rotateZ(z);
        return Transform(mat);
    }

    Transform Transform::perspective(float fov, float aspect, float znear, float zfar)
    {
        Matrix mat = Matrix::perspective(fov, aspect, znear, zfar);
        return Transform(mat);
    }

    Transform Transform::ortho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        Matrix mat = Matrix::ortho(left, right, bottom, top, znear, zfar);
        return Transform(mat);
    }

    Transform Transform::lookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        Matrix mat = Matrix::lookAt(eye, center, up);
        return Transform(mat);
    }

    Transform Transform::identity()
    {
        return Transform(Matrix::identity());
    }
}

#include "common/Transform.h"

#include <cmath>

Transform::Transform()
    :_x(0.0), _y(0.0), _z(0.0),
    _sx(0.0), _sy(0.0), _sz(0.0),
    _rx(0.0), _ry(0.0), _rz(0.0)
{}

Transform::~Transform(){}

void Transform::init()
{

}

void Transform::update()
{

}

void Transform::setX(float x)
{
    _x = x;
}

void Transform::setY(float y)
{
    _y = y;
}

void Transform::setZ(float z)
{
    _z = z;
}

void Transform::setPosition(float x, float y, float z)
{
    _x = x; _y = y; _z = z;
}

Matrix Transform::getPositionMatrix()
{
    Matrix mat = Matrix::identity();
    mat(0, 3) = _x;
    mat(1, 3) = _y;
    mat(2, 3) = _z;

    return mat;
}

Matrix Transform::getScaleMatrix()
{
    Matrix mat = Matrix::identity();
    mat(0, 0) = _sx;
    mat(1, 1) = _sy;
    mat(2, 2) = _sz;

    return mat;
}

Matrix Transform::getRotationMatrix()
{
   
}

Matrix Transform::getXAxisRotation()
{
    Matrix mat = Matrix::identity();
    mat(1, 1) = cos(_rx);
    mat(1, 2) = -sin(_rx);
    mat(2, 1) = sin(_rx);
    mat(2, 2) = cos(_rx);

    return mat;
}

Matrix Transform::getYAxisRotation()
{
    Matrix mat = Matrix::identity();
    mat(0, 0) = cos(_ry);
    mat(0, 2) = sin(_ry);
    mat(2, 0) = -sin(_ry);
    mat(2, 2) = cos(_ry);

    return mat;
}

Matrix Transform::getZAxisRotation()
{
    Matrix mat = Matrix::identity();
    mat(0, 0) = cos(_rz);
    mat(0, 1) = -sin(_rz);
    mat(1, 0) = sin(_rz);
    mat(1, 1) = cos(_rz);

    return mat;
}




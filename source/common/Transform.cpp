
#include "common/Transform.h"

#include <cmath>

namespace te
{
    Transform::Transform()
    {}

    Transform::~Transform(){}

    void Transform::init()
    {

    }

    void Transform::update()
    {

    }

    void Transform::translate(const Vector3& translation)
    {
        _local_pos.set(translation.x, translation.y, translation.z);
    }

    void Transform::translate(float x, float y, float z)
    {
        _local_pos.set(x, y, z);
    }

    void Transform::rotate(const Vector3& euler_angles)
    {
        _local_euler_angles = euler_angles;
    }
    void Transform::rotate(float rx, float ry, float rz)
    {
        _local_euler_angles = Vector3(rx, ry, rz);
    }

    void Transform::scale(const Vector3& scale)
    {
        _local_scale = scale;
    }
    void Transform::scale(float sx, float sy, float sz)
    {
        _local_scale = Vector3(sx, sy, sz);
    }

    const Vector3& Transform::getPosition()
    {
        return _local_pos;
    }
    const Vector3& Transform::getScale()
    {
        return _local_scale;
    }
    const Vector3& Transform::getEulerAngles()
    {
        return _local_euler_angles;
    }
    const Quaternion& Transform::getRotation()
    {
        return Quaternion(_local_euler_angles);
    }

}








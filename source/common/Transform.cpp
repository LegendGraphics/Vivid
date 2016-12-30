
#include "common/Transform.h"
#include "common/Node.h"

#include <cmath>

namespace te
{
    Transform::Transform()
        :_local_pos(0, 0, 0),
        _local_scale(1, 1, 1),
        _local_euler_angles(0, 0, 0),
        _world_pos(0, 0, 0),
        _world_scale(1, 1, 1),
        _world_euler_angles(0, 0, 0),
        _dirty(true)
    {}

    Transform::Transform(const Vector3& position)
        :_local_pos(0, 0, 0),
        _local_scale(1, 1, 1),
        _local_euler_angles(0, 0, 0),
        _world_pos(0, 0, 0),
        _world_scale(1, 1, 1),
        _world_euler_angles(0, 0, 0),
        _dirty(true)
    {
        translate(position);
    }

    Transform::Transform(float x, float y, float z)
        :_local_pos(0, 0, 0),
        _local_scale(1, 1, 1),
        _local_euler_angles(0, 0, 0),
        _world_pos(0, 0, 0),
        _world_scale(1, 1, 1),
        _world_euler_angles(0, 0, 0),
        _dirty(true)
    {
        translate(x, y, z);
    }

    Transform::~Transform(){}

    void Transform::init()
    {

    }

    void Transform::update()
    {
        Node* parent = _owner->getParent();
        Transform* pt = parent->getComponent<Transform>();
        //world.transform = pt.world.transform * local.transform
        _world_pos = Vector4to3(pt->getTranslateMatrix(TransformRef::RELATIVE_TO_WORLD) * 
            Vector3to4(_local_pos));
        _world_scale = Vector4to3(pt->getScaleMatrix(TransformRef::RELATIVE_TO_WORLD) *
            Vector3to4(_local_scale));
        _world_rot = pt->getWorldRotation() * _local_rot;
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

    const Vector3& Transform::getLocalPosition()
    {
        return _local_pos;
    }
    const Vector3& Transform::getLocalScale()
    {
        return _local_scale;
    }
    const Vector3& Transform::getLocalEulerAngles()
    {
        return _local_euler_angles;
    }
    const Quaternion& Transform::getLocalRotation()
    {
        return Quaternion(_local_euler_angles);
    }

    const Vector3& Transform::getWorldPosition()
    {
        return _world_pos;
    }
    const Vector3& Transform::getWorldScale()
    {
        return _world_scale;
    }
    const Vector3& Transform::getWorldEulerAngles()
    {
        return _world_euler_angles;
    }
    const Quaternion& Transform::getWorldRotation()
    {
        return Quaternion(_world_euler_angles);
    }

    // we usually use the order of TRS to combine the translation, rotation and scale 
    Matrix Transform::getInnerMatrix(const TransformRef& tr)
    {
        return getTranslateMatrix(tr) * getRotateMatrix(tr) * getScaleMatrix(tr);
    }

    Matrix Transform::getTranslateMatrix(const TransformRef& tr)
    {
        float tx, ty, tz;
        if (tr == TransformRef::RELATIVE_TO_PARENT)
        {
            tx = _local_pos.x;
            ty = _local_pos.y;
            tz = _local_pos.z;
        }
        else
        {
            tx = _world_pos.x;
            ty = _world_pos.y;
            tz = _world_pos.z;
        }
        return Matrix(1, 0, 0, tx,
                      0, 1, 0, ty,
                      0, 0, 1, tz,
                      0, 0, 0,  1);
    }

    Matrix Transform::getScaleMatrix(const TransformRef& tr)
    {
        float sx, sy, sz;
        if (tr == TransformRef::RELATIVE_TO_PARENT)
        {
            sx = _local_scale.x;
            sy = _local_scale.y;
            sz = _local_scale.z;
        }
        else
        {
            sx = _world_scale.x;
            sy = _world_scale.y;
            sz = _world_scale.z;
        }
        return Matrix(sx,  0,  0, 0,
                       0, sy,  0, 0,
                       0,  0, sz, 0,
                       0,  0,  0, 1);
    }

    // use quaternion as inner rotation
    Matrix Transform::getRotateMatrix(const TransformRef& tr)
    {
        if (tr == TransformRef::RELATIVE_TO_PARENT)
        {
            return _local_rot.convertToMatrix();
        }
        else
        {
            return _world_rot.convertToMatrix();
        }
    }

}



#include "common/SpaceState.h"
#include "common/Node.h"

#include <cmath>

namespace te
{
    SpaceState::SpaceState()
        :Component(ComponentType::SPACE_STATE),
        _local_scale(1, 1, 1),
        _world_scale(1, 1, 1),
        _dirty(true)
    {
    }

    SpaceState::SpaceState(const Vector3& position)
        :Component(ComponentType::SPACE_STATE),
        _local_scale(1, 1, 1),
        _world_scale(1, 1, 1),
        _dirty(true)
    {
        translate(position);
    }

    SpaceState::SpaceState(float x, float y, float z)
        :Component(ComponentType::SPACE_STATE),
        _local_scale(1, 1, 1),
        _world_scale(1, 1, 1),
        _dirty(true)
    {
        translate(x, y, z);
    }

    SpaceState::SpaceState(const Vector3& position, const Vector3& scale, const Vector3& rotation)
        :Component(ComponentType::SPACE_STATE)
    {
        this->translate(position);
        this->scale(scale);
        this->rotate(rotation);
    }

    SpaceState::~SpaceState(){}

    void SpaceState::accumulateTransform()
    {
        //Node* parent = _owner->getParent();
        //SpaceState* pt = parent->getComponent<SpaceState>();
        ////world.SpaceState = pt.world.SpaceState * local.SpaceState
        //_world_pos = Vector4to3(pt->getTranslateTransform(SpaceStateRef::RELATIVE_TO_WORLD) *
        //    Vector3to4(_local_pos));
        //_world_scale = Vector4to3(pt->getScaleTransform(SpaceStateRef::RELATIVE_TO_WORLD) *
        //    Vector3to4(_local_scale));
        //_world_rot = pt->getWorldRotation() * _local_rot;
    }

    void SpaceState::translate(const Vector3& translation)
    {
        _local_pos.set(translation.x, translation.y, translation.z);
    }

    void SpaceState::translate(float x, float y, float z)
    {
        _local_pos.set(x, y, z);
    }

    void SpaceState::scale(const Vector3& scale)
    {
        _local_scale.set(scale.x, scale.y, scale.z);
    }

    void SpaceState::scale(float sx, float sy, float sz)
    {
        _local_scale.set(sx, sy, sz);
    }

    void SpaceState::rotate(const Vector3& euler_angles)
    {
        _local_euler_angles.set(euler_angles.x, euler_angles.y, euler_angles.z);
        _local_rot = Quaternion(_local_euler_angles);
    }

    void SpaceState::rotate(float rx, float ry, float rz)
    {
        _local_euler_angles.set(rx, ry, rz);
        _local_rot = Quaternion(_local_euler_angles);
    }

    const Vector3& SpaceState::getLocalPosition()
    {
        return _local_pos;
    }
    const Vector3& SpaceState::getLocalScale()
    {
        return _local_scale;
    }
    const Vector3& SpaceState::getLocalEulerAngles()
    {
        return _local_euler_angles;
    }
    const Quaternion& SpaceState::getLocalRotation()
    {
        return _local_rot;
    }

    const Vector3& SpaceState::getWorldPosition()
    {
        return _world_pos;
    }
    const Vector3& SpaceState::getWorldScale()
    {
        return _world_scale;
    }
    const Vector3& SpaceState::getWorldEulerAngles()
    {
        return _world_euler_angles;
    }
    const Quaternion& SpaceState::getWorldRotation()
    {
        return _world_rot;
    }

    // we usually use the order of TRS to combine the translation, rotation and scale 
    Transform SpaceState::getInnerTransform(const SpaceStateRef& tr)
    {
        return getTranslateTransform(tr) * getRotateTransform(tr) * getScaleTransform(tr);
    }

    Transform SpaceState::getTranslateTransform(const SpaceStateRef& tr)
    {
        float tx, ty, tz;
        if (tr == SpaceStateRef::RELATIVE_TO_PARENT)
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
        return Transform::translate(tx, ty, tz);
    }

    Transform SpaceState::getScaleTransform(const SpaceStateRef& tr)
    {
        float sx, sy, sz;
        if (tr == SpaceStateRef::RELATIVE_TO_PARENT)
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
        return Transform::scale(sx, sy, sz);
    }

    // use quaternion as inner rotation
    Transform SpaceState::getRotateTransform(const SpaceStateRef& tr)
    {
        if (tr == SpaceStateRef::RELATIVE_TO_PARENT)
        {
            return Transform(_local_rot.convertToMatrix());
        }
        else
        {
            return Transform(_world_rot.convertToMatrix());
        }
    }

}


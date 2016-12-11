#ifndef COMMON_TRANSFORM_H
#define COMMON_TRANSFORM_H

#include "common/component.h"
#include "Core/math/Vector3.h"
#include "Core/math/Quaternion.h"

class Transform: public Component
{
public:
    Transform();
    virtual ~Transform();

    virtual void init();
    virtual void update();

    void translate(const Vector3& translation);
    void translate(float x, float y, float z);

    void rotate(const Vector3& euler_angles);
    void rotate(float rx, float ry, float rz);

    void scale(const Vector3& scale);
    void scale(float sx, float sy, float sz);

    // using local as example
    // but I need to keep both local and world transform data
    const Vector3& getPosition();
    const Vector3& getScale();
    const Vector3& getEulerAngles();
    const Quaternion& getRotation();

protected:
    Vector3 _world_pos;
    Vector3 _world_scale;
    Vector3 _world_euler_angles; // (x, y, z) = (roll, pitch, yaw)
    Quaternion _world_rot; // use quaternion to represent rotation? how about euler angles?
    
    Vector3 _local_pos;
    Vector3 _local_scale;
    Vector3 _local_euler_angles;
    Quaternion _local_rot; 

};
#endif // COMMON_TRANSFORM_H
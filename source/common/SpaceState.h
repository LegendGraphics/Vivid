#ifndef COMMON_SPACE_STATE_H
#define COMMON_SPACE_STATE_H

#include "common/Component.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"

namespace te
{
    // store position, scale and rotation data
    class SpaceState : public Component
    {
    public:
        enum class SpaceStateRef
        {
            RELATIVE_TO_PARENT,
            RELATIVE_TO_WORLD
        };

    public:
        SpaceState();
        SpaceState(const Vector3& position);
        SpaceState(float x, float y, float z);
        virtual ~SpaceState();

        virtual void init();
        virtual void update();

        void translate(const Vector3& translation);
        void translate(float x, float y, float z);

        void rotate(const Vector3& euler_angles);
        void rotate(float rx, float ry, float rz);

        void scale(const Vector3& scale);
        void scale(float sx, float sy, float sz);

        // using local as example
        // but I need to keep both local and world SpaceState data
        const Vector3& getLocalPosition();
        const Vector3& getLocalScale();
        const Vector3& getLocalEulerAngles();
        const Quaternion& getLocalRotation();

        const Vector3& getWorldPosition();
        const Vector3& getWorldScale();
        const Vector3& getWorldEulerAngles();
        const Quaternion& getWorldRotation();

        Matrix getTranslateMatrix(const SpaceStateRef& tr);
        Matrix getScaleMatrix(const SpaceStateRef& tr);
        Matrix getRotateMatrix(const SpaceStateRef& tr);
        Matrix getInnerMatrix(const SpaceStateRef& tr);

    protected:
        Vector3 _local_pos;
        Vector3 _local_scale;
        Vector3 _local_euler_angles;
        Quaternion _local_rot;

        Vector3 _world_pos;
        Vector3 _world_scale;
        Vector3 _world_euler_angles; // (x, y, z) = (roll, pitch, yaw)
        Quaternion _world_rot; // use quaternion to represent rotation? how about euler angles?    

        bool _dirty;

    };
}


#endif // COMMON_SPACE_STATE_H
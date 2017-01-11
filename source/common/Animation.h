#ifndef COMMON_ANIMATION_H
#define COMMON_ANIMATION_H

#include "common/Component.h"
#include "common/AnimationClip.h"
#include "math/Matrix.h"

namespace te
{
    struct SkeletonJoint
    {
        std::string name;
        int parent_idx;
        Matrix inv_binding;
    };

    using SkeletonJoints = std::vector<SkeletonJoint>;

    struct Skeleton
    {
        int id;
        int joint_count;
        SkeletonJoints joints;
    };

    class Animation : public Component
    {
    public:
        Animation() = default;
        virtual ~Animation() = default;

    protected:
        Skeleton*   _skeleton;
        AnimationClips*  _clips;
    };
}

#endif // COMMON_ANIMATION_H
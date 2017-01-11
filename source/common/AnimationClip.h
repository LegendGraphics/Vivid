#ifndef COMMON_ANIMATION_CLIP_H
#define COMMON_ANIMATION_CLIP_H

#include <vector>

#include "common/Object.h"
#include "math/Quaternion.h"

namespace te
{
    struct AnimationPose
    {
        Vector3 translation;
        Vector3 scale;
        Quaternion rotation;
    };

    using AnimationPoses = std::vector<AnimationPose>;

    class AnimationClip: public Object
    {
    public:
        AnimationClip() = default;
        virtual ~AnimationClip() = default;

    protected:
        float _duration;
        AnimationPoses _poses;
    };

    using AnimationClips = std::vector<AnimationClip*>;
}

#endif // COMMON_ANIMATION_CLIP_H
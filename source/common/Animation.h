#ifndef COMMON_ANIMATION_H
#define COMMON_ANIMATION_H

#include "common/Component.h"
#include "common/AnimationClip.h"
#include "math/Matrix.h"

namespace te
{
    class Animation : public Component
    {
    public:
        Animation() = default;
        virtual ~Animation() = default;

        void setSkeleton(SkeletonRes* skel_res);
        void addAnimClip(AnimClipRes* clip_res);

    protected:
        Skeleton*   _skeleton;
        AnimationClips*  _clips;
    };
}

#endif // COMMON_ANIMATION_H
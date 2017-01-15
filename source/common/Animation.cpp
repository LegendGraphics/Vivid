#include "common/Animation.h"

namespace te
{
    void Animation::setSkeleton(SkeletonRes* skel_res)
    {
        // build skeleton
        skel_res->buildSkeleton(_skeleton);
    }
    
    void Animation::addAnimClip(AnimClipRes* clip_res)
    {
        // build AnimationClip
        AnimationClip* clip = new AnimationClip;
        clip_res->buildAnimClip(clip);
        _clips->push_back(clip);
    }
}
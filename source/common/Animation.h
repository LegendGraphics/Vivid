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

        virtual void init();
        virtual void update();

        void setSkeleton(SkeletonRes* skel_res);
        void addClipFromRes(AnimClipRes* clip_res);
        void addClip(AnimationClip* clip);
        void removeClip(AnimationClip* clip);
        int getClipCount() const;

        AnimationPoses blend(const AnimationPoses& ps1, const AnimationPoses& ps2, float w);
        AnimationPoses interpolate(float time, int clip_index);
        
        void play(const std::string& anim_name);
        void stop();

        bool isPlaying(const std::string& anim_name);

    protected:
        Skeleton*   _skeleton;
        AnimationClips*  _clips;
        std::vector<int> _actives;
    };
}

#endif // COMMON_ANIMATION_H
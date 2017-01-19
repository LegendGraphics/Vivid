#ifndef COMMON_ANIMATION_H
#define COMMON_ANIMATION_H

#include "common/Component.h"
#include "common/AnimationClip.h"
#include "math/Matrix.h"

namespace te
{
    class AnimClipContainer : public Object
    {
    private:
        using AnimationClips = std::unordered_map<std::string, AnimationClip*>;
    public:
        int getAnimClipNum();
        AnimationClip* getAnimClip(const std::string& name);
        AnimationClip* createAnimClip(const std::string& name, float length);
        void addAnimClip(const std::string& name, AnimationClip* clip);
        bool hasAnimClip(const std::string& name);
        void removeAnimClip(const std::string& name);

    private:
        AnimationClips _clips;
    };

    class Animation : public Component
    {
    public:
        Animation() = default;
        virtual ~Animation() = default;

        virtual void init();
        virtual void update();

        //void setSkeleton(SkeletonRes* skel_res);
        //void addClipFromRes(AnimClipRes* clip_res);

        void addAnimClip(const std::string& name, AnimationClip* clip);
        void removeAnimClip(const std::string& name);
        int getAnimClipNum() const;
        bool hasAnimClip(const std::string& name);

        AnimationPoses blend(const AnimationPoses& ps1, const AnimationPoses& ps2, float w);
        AnimationPoses interpolate(float time, int clip_index);
        
        void play(const std::string& anim_name);
        void stop();

        bool isPlaying(const std::string& anim_name);

    protected:
        //Skeleton*   _skeleton;
        AnimClipContainer*  _clip_container;
    };
}

#endif // COMMON_ANIMATION_H
#ifndef COMMON_ANIMATION_CLIP_H
#define COMMON_ANIMATION_CLIP_H

#include <vector>

#include "common/Object.h"
#include "common/Resource.h"
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


    class AnimationRes : public Resource
    {
    private:
        struct Frame
        {
            Quaternion  rotation;
            Vector3     translation;
            Vector3     scale;
            Matrix      baked_mat;
        };

        // a single joint's animation clip
        struct AnimResEnitity 
        {
            std::string name;
            bool compressed;
            std::vector<Frame> frames;
        };
    public:
        bool load(const char *data, int size);
        void release();
    protected:
        int _frame_num;
        std::vector<AnimResEnitity>  _entities;
    };

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
#ifndef COMMON_ANIMATION_CLIP_H
#define COMMON_ANIMATION_CLIP_H

#include <vector>

#include "common/Object.h"
#include "common/Resource.h"
#include "math/Quaternion.h"

namespace te
{
    class Skeleton;
    class AnimationClip;

    class SkeletonRes : public Resource
    {
    private:
        struct JointEntity
        {
            std::string name;
            int parent_idx;
            Matrix inv_binding;
        };
    public:
        bool load(const std::string & res);
        void unload(){}
        void release();

        friend class Skeleton;

    protected:
        std::vector<JointEntity> _entities;
        int _skel_num;
        std::vector<int> _num_list;
    };


    class AnimClipRes : public Resource
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
        struct AnimResEntity 
        {
            std::string name;
            bool compressed;
            std::vector<Frame> frames;
        };
    public:
        bool load(const std::string & res);
        void unload(){}
        void release();

        void initAnimClip(AnimationClip* anim_clip);
    protected:
        int _frame_num;
        std::vector<AnimResEntity>  _entities;
    };

    // using linear array to store skeleton and related poses
    struct SkeletonJoint
    {
        std::string name;
        int parent_idx;
        Matrix inv_binding;
    };

    using SkeletonJoints = std::vector<SkeletonJoint>;

    struct AnimationPose
    {
        Vector3 translation;
        Vector3 scale;
        Quaternion rotation;
    };

    using AnimationPoses = std::vector<AnimationPose>;

    class Skeleton : public Object
    {
    public:
        Skeleton() = default;
        virtual ~Skeleton() = default;

        void init(SkeletonRes* res);

        void resize(int size);
        SkeletonJoint& getJoint(int index);
        SkeletonJoint& getParentJoint(int index);
        int getJointNum() const{ return _joints.size(); }
    protected:
        SkeletonJoints _joints;
    };

    class AnimationClip: public Object
    {
    public:
        AnimationClip() = default;
        AnimationClip(const AnimationClip& anim_clip, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~AnimationClip() = default;

        OBJECT_META_FUNCTION(AnimationClip);

        void init(AnimClipRes* res);

        void setFrameNum(int num);
        AnimationPoses& getAnimPoses(int index) { return _key_frames[index]; }
        float getDuration() const { return _duration; }
        int getFrameNum() const { return _key_frames.size(); }

    protected:
        float _duration;
        std::vector<AnimationPoses> _key_frames;
    };
}

#endif // COMMON_ANIMATION_CLIP_H
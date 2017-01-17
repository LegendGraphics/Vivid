#include "common/Animation.h"

namespace te
{
    void Animation::setSkeleton(SkeletonRes* skel_res)
    {
        // build skeleton
        skel_res->buildSkeleton(_skeleton);
    }

    void Animation::addClipFromRes(AnimClipRes* clip_res)
    {
        // build AnimationClip
        AnimationClip* clip = new AnimationClip;
        clip_res->buildAnimClip(clip);
        addClip(clip);
    }

    void Animation::addClip(AnimationClip* clip)
    {
        _clips->push_back(clip);
    }

    void Animation::removeClip(AnimationClip* clip)
    {
        AnimationClips::iterator position = std::find(_clips->begin(), _clips->end(), clip);
        if (position != _clips->end())
            _clips->erase(position);
    }

    int Animation::getClipCount() const
    {
        return _clips->size();
    }

    void Animation::play(const std::string& anim_name)
    {

    }

    void Animation::stop()
    {

    }

    bool Animation::isPlaying(const std::string& anim_name)
    {
        return true;
    }

    AnimationPoses Animation::blend(const AnimationPoses& ps1, const AnimationPoses& ps2, float w)
    {
        assert(ps1.size() == ps2.size());
        AnimationPoses poses(ps1.size());
        for (size_t i = 0, i_end = ps1.size(); i < i_end; ++i)
        {
            const AnimationPose& p1 = ps1[i];
            const AnimationPose& p2 = ps2[i];
            poses[i].translation = p1.translation * w + p2.translation * (1 - w);
            poses[i].scale = p1.scale * w + p2.scale * (1 - w);
            poses[i].rotation = p1.rotation * w + p2.rotation * (1 - w);
        }

        return poses;
    }

    AnimationPoses Animation::interpolate(float time, int clip_index)
    {
        AnimationClip* clip = (*_clips)[clip_index];
        float delta = 1.0 / (clip->getFrameNum() - 1);
        int key = int(time / delta);
        float weight = time - delta * key;
        
        return blend(clip->getAnimPose(key), clip->getAnimPose(key + 1), weight);
    }

    void Animation::init()
    {

    }

    void Animation::update()
    {

    }
}
#include "common/Animation.h"

namespace te
{
    int AnimClipContainer::getAnimClipNum()
    {
        return _clips.size();
    }

    AnimationClip* AnimClipContainer::getAnimClip(const std::string& name)
    {
        if (hasAnimClip(name)) return _clips[name];
        else return nullptr;
    }

    AnimationClip* AnimClipContainer::createAnimClip(const std::string& name, float length)
    {
        if (!hasAnimClip(name)) 
            _clips.insert({ name, new AnimationClip });
        return _clips[name];
    }

    void AnimClipContainer::addAnimClip(const std::string& name, AnimationClip* clip)
    {
        if (!hasAnimClip(name))
            _clips.insert({ name, clip });
    }

    bool AnimClipContainer::hasAnimClip(const std::string& name)
    {
        if (_clips.find(name) != _clips.end()) return true;
        else return false;
    }
    void AnimClipContainer::removeAnimClip(const std::string& name)
    {
        if (hasAnimClip(name)) _clips.erase(name);
    }

    //void Animation::setSkeleton(SkeletonRes* skel_res)
    //{
    //    // build skeleton
    //    skel_res->buildSkeleton(_skeleton);
    //}

    //void Animation::addClipFromRes(AnimClipRes* clip_res)
    //{
    //    // build AnimationClip
    //    AnimationClip* clip = new AnimationClip;
    //    clip_res->buildAnimClip(clip);
    //    addClip(clip);
    //}

    void Animation::addAnimClip(const std::string& name, AnimationClip* clip)
    {
        _clip_container->addAnimClip(name, clip);
    }

    void Animation::removeAnimClip(const std::string& name)
    {
        _clip_container->removeAnimClip(name);
    }

    int Animation::getAnimClipNum() const
    {
        return _clip_container->getAnimClipNum();
    }

    bool Animation::hasAnimClip(const std::string& name)
    {
        return _clip_container->hasAnimClip(name);
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
        AnimationClip* clip = nullptr; //(*_clips)[clip_index];
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
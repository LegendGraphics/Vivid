#include "common/Animation.h"

namespace te
{
    AnimClipContainer::AnimClipContainer(const AnimClipContainer& container, const CopyOperator& copyop)
    {}

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

    Animation::Animation()
        :_clip_container(new AnimClipContainer),
        _state_set(new AnimStateSet)
    {}

    void Animation::addAnimClip(const std::string& name, AnimationClip* clip)
    {
        _clip_container->addAnimClip(name, clip);
        _state_set->addAnimationState(name);
    }

    void Animation::removeAnimClip(const std::string& name)
    {
        _clip_container->removeAnimClip(name);
        _state_set->removeAnimationState(name);
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

    AnimationPoses Animation::blend(const AnimationPoses& ps1, const AnimationPoses& ps2, float w1, float w2)
    {
        assert(ps1.size() == ps2.size());
        AnimationPoses poses(ps1.size());
        for (size_t i = 0, i_end = ps1.size(); i < i_end; ++i)
        {
            const AnimationPose& p1 = ps1[i];
            const AnimationPose& p2 = ps2[i];
            poses[i].translation = p1.translation * w1 + p2.translation * w2;
            poses[i].scale = p1.scale * w1 + p2.scale * w2;
            poses[i].rotation = p1.rotation * w1 + p2.rotation * w2;
        }

        return poses;
    }

    AnimationPoses Animation::interpolate()
    {
        AnimationClip* clip = _clip_container->getAnimClip(_current_anim);
        AnimationState* state = _state_set->getAnimationState(_current_anim);
        AnimBlendParas paras = state->getBlendParas();
        
        return blend(clip->getAnimPoses(paras.first), clip->getAnimPoses(paras.second), paras.fw, paras.sw);
    }

    void Animation::init()
    {

    }

    void Animation::update()
    {

    }
}
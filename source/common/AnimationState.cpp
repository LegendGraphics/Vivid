#include "common/AnimationState.h"

namespace te
{
    AnimationState::AnimationState()
        :_time_pos(0),
        _weight(1),
        _enabled(true),
        _loop(false),
        _frame_num(0),
        _duration(0),
        _elapsed(0)
    {}

    AnimationState::AnimationState(const AnimationState& state, const CopyOperator& copyop)
    {}

    void AnimationState::setTimePosition(float time_pos)
    {
        _time_pos = time_pos;
    }

    float AnimationState::getTimePosition() const
    {
        return _time_pos;
    }

    void AnimationState::setWeight(float weight)
    {
        _weight = weight;
    }

    float AnimationState::getWeight() const
    {
        return _weight;
    }

    void AnimationState::setEnabled(bool enabled)
    {
        _enabled = enabled;
    }

    bool AnimationState::getEnabled() const
    {
        return _enabled;
    }

    void AnimationState::setLoop(bool loop)
    {
        _loop = loop;
    }

    bool AnimationState::getLoop() const
    {
        return _loop;
    }

    void AnimationState::setKeyFrameNum(int num)
    {
        _frame_num = num;
    }
    int AnimationState::getKeyFrameNum() const
    {
        return _frame_num;
    }

    void AnimationState::setDurationTime(float duration_time)
    {
        _duration = duration_time;
    }
    float AnimationState::getDurationTime() const
    {
        return _duration;
    }

    void AnimationState::addDeltaTime(float delta_time)
    {
        _elapsed += delta_time;
    }

    AnimBlendParas AnimationState::getBlendParas()
    {
        float r = _elapsed / _duration;
        float d = 1.0 / (_frame_num - 1);
        AnimBlendParas paras;
        paras.first = int(r / d);
        paras.second = paras.first + 1;
        paras.fw = r - paras.first * d;
        paras.sw = 1 - paras.fw;
        return paras;
    }

    AnimStateSet::AnimStateSet(const AnimStateSet& state_set, const CopyOperator& copyop )
    {}


    AnimationState* AnimStateSet::getAnimationState(const std::string& name)
    {
        if (hasAnimationState(name)) return _states[name];
        else return nullptr;
    }
    void AnimStateSet::addAnimationState(const std::string& name)
    {
        if (!hasAnimationState(name))
        {
            _states.insert({ name, new AnimationState });
        }
    }
    bool AnimStateSet::hasAnimationState(const std::string& name)
    {
        if (_states.find(name) != _states.end()) return true;
        else return false;
    }
    void AnimStateSet::removeAnimationState(const std::string& name)
    {
        if (hasAnimationState(name)) _states.erase(name);
    }
    void AnimStateSet::removeAllAnimationStates()
    {
        _states.clear();
    }
}
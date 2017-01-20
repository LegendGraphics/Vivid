#include "common/AnimationState.h"

namespace te
{
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

    AnimationState* AnimationStateSet::getAnimationState(const std::string& name)
    {
        if (hasAnimationState(name)) return _states[name];
        else return nullptr;
    }
    bool AnimationStateSet::hasAnimationState(const std::string& name)
    {
        if (_states.find(name) != _states.end()) return true;
        else return false;
    }
    void AnimationStateSet::removeAnimationState(const std::string& name)
    {
        if (hasAnimationState(name)) _states.erase(name);
    }
    void AnimationStateSet::removeAllAnimationStates()
    {
        _states.clear();
    }
}
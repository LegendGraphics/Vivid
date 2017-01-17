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
}
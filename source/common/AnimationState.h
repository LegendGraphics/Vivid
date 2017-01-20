#ifndef COMMON_ANIMATION_STATE_H
#define COMMON_ANIMATION_STATE_H

#include <unordered_map>
#include "common/Object.h"

namespace te
{
    class AnimationState : public Object
    {
    public:
        AnimationState() = default;
        virtual ~AnimationState() = default;

        void setTimePosition(float time_pos);
        float getTimePosition() const;

        void setWeight(float weight);
        float getWeight() const;

        void setEnabled(bool enabled);
        bool getEnabled() const;

        void setLoop(bool loop);
        bool getLoop() const;
    protected:
        float _time_pos;
        float _weight;
        bool _enabled;
        bool _loop;
    };

    class AnimationStateSet : public Object
    {
    private:
        using AnimationStateMap = std::unordered_map<std::string, AnimationState*>;

    public:
        AnimationState* getAnimationState(const std::string& name);
        bool hasAnimationState(const std::string& name);
        void removeAnimationState(const std::string& name);
        void removeAllAnimationStates();

    private:
        AnimationStateMap _states;
    };
}



#endif // COMMON_ANIMATION_STATE_H
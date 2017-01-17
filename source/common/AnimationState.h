#ifndef COMMON_ANIMATION_STATE_H
#define COMMON_ANIMATION_STATE_H

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
}



#endif // COMMON_ANIMATION_STATE_H
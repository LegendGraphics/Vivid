#ifndef COMMON_ANIMATION_STATE_H
#define COMMON_ANIMATION_STATE_H

#include <unordered_map>
#include "common/Object.h"

namespace te
{
    struct AnimBlendParas
    {
        int first;
        int second;
        float fw;
        float sw;
    };

    class AnimationState : public Object
    {
    public:
        AnimationState();
        AnimationState(const AnimationState& state, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~AnimationState() = default;

        OBJECT_META_FUNCTION(AnimationState);

        void setTimePosition(float time_pos);
        float getTimePosition() const;

        void setWeight(float weight);
        float getWeight() const;

        void setEnabled(bool enabled);
        bool getEnabled() const;

        void setLoop(bool loop);
        bool getLoop() const;

        void setKeyFrameNum(int num);
        int getKeyFrameNum() const;

        void setDurationTime(float duration_time);
        float getDurationTime() const;

        void addDeltaTime(float delta_time);

        AnimBlendParas getBlendParas();

    protected:
        float _time_pos;
        float _weight;
        bool _enabled;
        bool _loop;
        int _frame_num;
        float _duration;
        float _elapsed;
    };

    class AnimStateSet : public Object
    {
    private:
        using AnimationStateMap = std::unordered_map<std::string, AnimationState*>;

    public:
        AnimStateSet() = default;
        AnimStateSet(const AnimStateSet& state_set, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~AnimStateSet() = default;

        OBJECT_META_FUNCTION(AnimStateSet);

        AnimationState* getAnimationState(const std::string& name);
        void addAnimationState(const std::string& name);
        bool hasAnimationState(const std::string& name);
        void removeAnimationState(const std::string& name);
        void removeAllAnimationStates();

    private:
        AnimationStateMap _states;
    };
}



#endif // COMMON_ANIMATION_STATE_H
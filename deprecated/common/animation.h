#ifndef COMMON_ANIMATION_H
#define COMMON_ANIMATION_H

#include <vector>

#include "base/ref.h"
#include "common/image.h"
#include "common/sprite.h"

class Sprite;

class Animation: public Ref
{
public:
    typedef std::vector<RefPtr<Image>> AnimationFrames;

public:
    Animation();
    Animation(const std::string& animation_folder);
    virtual ~Animation();

    void bindSprite(Sprite* sprite);

    void setDuration(float duration);

    void update(float delta_time);

private:
    std::vector<RefPtr<Image>> _anim_frames;
    RefPtr<Sprite> _sprite;

    int _frame_index;
    int _frame_num;
    bool _loop;

    float _duration;
    float _unit;
    float _elapsed;
};

#endif // COMMON_ANIMATION_H
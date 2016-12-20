
#include "common/animation.h"
#include "base/file_loader.h"

Animation::Animation()
:_frame_index(0),
_loop(true),
_frame_num(0),
_duration(0),
_unit(0),
_elapsed(0),
_sprite(NULL)
{
}

Animation::Animation(const std::string& animation_folder)
:_frame_index(0),
_loop(true),
_frame_num(0),
_duration(0),
_unit(0),
_elapsed(0),
_sprite(NULL)
{
    
    _anim_frames = loadAnimation(animation_folder);
    _frame_num = _anim_frames.size();

    setDuration(0.5);
}

Animation::~Animation(){}

void Animation::bindSprite(Sprite* sprite)
{
    _sprite = sprite;
}

void Animation::setDuration(float duration)
{
    _duration = duration;
    _unit = _duration / _frame_num;
}

void Animation::update(float delta_time)
{
    if (_anim_frames.empty())
    {
        TE_ERROR("Animation resource doesn't exists!");
        return;
    }
    
    _elapsed += delta_time;

    if (_elapsed >= _unit)
    {
        _sprite->loadTexture(_anim_frames[_frame_index].get());
        if (++_frame_index >= _frame_num && _loop)
            _frame_index = 0;

        _elapsed = 0;
    }    
}
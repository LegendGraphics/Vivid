#include "base/Timer.h"

namespace te
{
    Timer::Timer()
        :_enabled(false),
        _elapsed(0)
    {}

    Timer::~Timer(){}

    void Timer::setEnabled(bool enabled)
    {
        if (enabled && !_enabled)
        {
            _start = getCurrentTime();
            _enabled = true;
        }
        else if (!enabled && _enabled)
        {
            TimePoint end = getCurrentTime();
            _elapsed += TimeDuration(end - _start).count();
            _enabled = false;
        }
    }

    void Timer::reset()
    {
        _elapsed = 0;
        if (_enabled) _start = getCurrentTime();
    }

    float Timer::getElapsedTime()
    {
        if (_enabled)
        {
            TimePoint end = getCurrentTime();
            _elapsed += TimeDuration(end - _start).count();
            _start = end;
        }

        return (float)_elapsed;
    }

    Timer::TimePoint Timer::getCurrentTime()
    {
        return system_clock::now();
    }
}
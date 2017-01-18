
#include "base/scheduler.h"

namespace te
{
    TimerCallback::TimerCallback()
        :_elapsed(0.0f),
        _interval(0.0f),
        _loop(true)
    {
    }


    void TimerCallback::update(float dt)
    {
        // accumulate elapsed time
        _elapsed += dt;

        // if _interval == 0, should trigger once every frame
        float interval = (_interval > 0) ? _interval : _elapsed;
        while (_elapsed >= interval)
        {
            trigger(interval);
            _elapsed -= interval;

            if (!_loop)
            {
                cancel();
                break;
            }
        }
    }


    TimerFuncCallback::TimerFuncCallback(const TimerCallbackFunc& callback, const std::string& key, float seconds)
        :_callback(callback),
        _key(key)
    {
        setInterval(seconds);
    }

    void TimerFuncCallback::trigger(float dt)
    {
        if (_callback) _callback(dt);
    }

    void TimerFuncCallback::cancel()
    {
        //Scheduler::getInstance()->unschedule(_key);
    }

    void Scheduler::schedule(const std::string& key, TimerCallback* timer)
    {
        if (_timer_map.find(key) != _timer_map.end())
        {
            TE_LOG("Already has the same key!");
            return;
        }

        _timer_map[key] = timer;
    }

    void Scheduler::unschedule(const std::string& key)
    {
        TimerMap::iterator itr = _timer_map.find(key);
        if (itr != _timer_map.end())
            _timer_map.erase(itr);
    }

    void Scheduler::update(float dt)
    {
        for (TimerMap::iterator itr = _timer_map.begin(); itr != _timer_map.end(); ++itr)
            itr->second->update(dt);
    }
}


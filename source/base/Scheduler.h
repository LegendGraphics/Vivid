#ifndef BASE_SCHEDULER_H
#define BASE_SCHEDULER_H

#include <map>
#include <string>

#include "common/Object.h"

namespace te
{
    class TimerCallback : public Object
    {
    protected:
        TimerCallback();
    public:
        inline float getInterval() const { return _interval; }
        void setInterval(float interval) { _interval = interval; }

        void setLoop(bool loop) { _loop = loop; }

        virtual void trigger(float dt) = 0;
        virtual void cancel() = 0;

        void update(float dt);

    protected:
        float _elapsed;
        float _interval;
        bool _loop;
    };

    class TimerFuncCallback : public TimerCallback
    {
    public:
        typedef void(*TimerCallbackFunc)(float);
    public:
        TimerFuncCallback(const TimerCallbackFunc& callback, const std::string& key, float seconds);

        const TimerCallbackFunc& getTimerCallback() const { return _callback; }
        const std::string& getKey() const { return _key; }

        virtual void trigger(float dt);
        virtual void cancel();

    protected:
        TimerCallbackFunc _callback;
        std::string _key;
    };


    class Scheduler : public Object
    {
    private:
        typedef std::map<std::string, TimerCallback*> TimerMap;

    public:
        void update(float dt);

        void schedule(const std::string& key, TimerCallback* timer);
        void unschedule(const std::string& key);

    private:
        TimerMap _timer_map;

    };

}


#endif // BASE_SCHEDULER_H




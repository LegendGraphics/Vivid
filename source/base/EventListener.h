#ifndef BASE_EVENT_LISTENER_H
#define BASE_EVENT_LISTENER_H

#include "base/Event.h"

namespace te
{
    class EventListenerBase
    {
    public:
        virtual ~EventListenerBase() {};
        void exec(Event* event) { call(event); }

    private:
        virtual void call(Event*) = 0;
    };


    template <class T>
    class EventListener : public EventListenerBase
    {
    public:
        typedef void(T::*EventCallback)(Event*);
    public:
        EventListener(ListenType listen_type, T* instance, EventCallback callback) : _listen_type(listen_type) , _instance(instance), _callback(callback) {};
        virtual ~EventListener() {};

        ListenType getListenType() const { return _listen_type; }

        void call(Event* event)
        {
            (_instance->*_callback)(event);
        }

        void setListenerId(size_t listener_id)
        {
            _instance->_listener_id = listener_id;
        }

    protected:
        ListenType      _listen_type;
        T*              _instance;
        EventCallback   _callback;
    };
}


#endif // BASE_EVENT_LISTENER_H
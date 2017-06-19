#ifndef BASE_EVENT_LISTENER_H
#define BASE_EVENT_LISTENER_H

#include <functional>
#include <unordered_map>
#include "vivid/base/Event.h"

namespace vivid
{
    class EventListenerBase
    {
    public:
        EventListenerBase(ListenType listen_type);
        ListenType getListenType() const { return _listen_type; }
        void setListenerId(size_t listener_id);
        size_t getListenerId() const { return _listener_id; }

        void exec(Event* event) { call(event); }
    protected:
        virtual void call(Event*) = 0;
    protected:
        ListenType      _listen_type;
        size_t          _listener_id;
    };

    class EventFunctionalListener : public EventListenerBase
    {
    public:
        typedef std::function<void(Event*)> EventCallback;
    public:
        EventFunctionalListener(ListenType listen_type, EventCallback callback);
        virtual ~EventFunctionalListener();

    protected:
        void call(Event* event);

    protected:
        EventCallback   _callback;
    };

    template <class T>
    class EventClassListener : public EventListenerBase
    {
    public:
        typedef std::function<void(T&, Event*)> EventCallback;
    public:
        EventClassListener(ListenType listen_type, T* instance, EventCallback callback) 
            : EventListenerBase(listen_type) , _instance(instance), _callback(callback) {};
        virtual ~EventClassListener() {};
        
    protected:
        void call(Event* event)
        {
            _callback(*_instance, event);
        }

    protected:
        T*              _instance;
        EventCallback   _callback;
    };
}


#endif // BASE_EVENT_LISTENER_H

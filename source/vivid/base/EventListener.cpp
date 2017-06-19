
#include "vivid/base/EventListener.h"

namespace vivid
{
    EventListenerBase::EventListenerBase(ListenType listen_type)
        :_listen_type(listen_type)
    {}

    void EventListenerBase::setListenerId(size_t listener_id)
    {
        _listener_id = listener_id;
    }

    EventFunctionalListener::EventFunctionalListener(ListenType listen_type, EventCallback callback) 
        : EventListenerBase(listen_type), _callback(callback) {};

    EventFunctionalListener::~EventFunctionalListener() {};

    void EventFunctionalListener::call(Event* event)
    {
        _callback(event);
    }
}

#ifndef BASE_EVENT_DISPATCHER_H
#define BASE_EVENT_DISPATCHER_H

#include <map>
#include <vector>

#include "base/ref.h"

class Event;
class EventListener;

class EventDispatcher: public Ref
{
private:
    typedef std::vector<EventListener*> EventListenerList;
    typedef std::map<int, EventListenerList> EventListenerMap;

public:
    EventDispatcher();
    ~EventDispatcher();

    void addEventListener(EventListener* event_listener);
    void removeEventListener(EventListener* event_listener);
    
    void dispatch(Event* event);

private:
    EventListenerMap _listener_map;
};
#endif // BASE_EVENT_DISPATCHER_H
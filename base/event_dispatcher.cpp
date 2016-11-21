#include <algorithm>

#include "base/event_dispatcher.h"
#include "base/event.h"
#include "base/event_listener.h"
#include "base/macros.h"

EventDispatcher::EventDispatcher(){}

EventDispatcher::~EventDispatcher(){}



void EventDispatcher::dispatch(Event* event)
{
    int key = event->getKey();
    EventListenerMap::iterator itr = _listener_map.find(key);
    if (itr == _listener_map.end())
    {
        TE_LOG("No related event listener exists!");
        return;
    }
    EventListenerList& eventlistener_list = _listener_map[key];
    for (EventListenerList::iterator itr = eventlistener_list.begin();
        itr != eventlistener_list.end(); ++ itr)
    {
        (*itr)->exec(event);
    }
}


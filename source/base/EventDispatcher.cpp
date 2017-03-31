#include <algorithm>

#include "base/EventDispatcher.h"
#include "base/Event.h"
#include "base/EventListener.h"

namespace te
{
    EventDispatcher::EventDispatcher() {}

    EventDispatcher::~EventDispatcher() {}



    void EventDispatcher::dispatch(Event* event)
    {
        int key = event->getKey();
        EventListenerMap::iterator itr = _listener_map.find(key);
        if (itr == _listener_map.end())
        {
            //TE_LOG("No related event listener exists!");
            return;
        }
        EventListenerList& eventlistener_list = _listener_map[key];
        for (EventListenerList::iterator itr = eventlistener_list.begin();
        itr != eventlistener_list.end(); ++itr)
        {
            (*itr)->exec(event);
        }
    }

}


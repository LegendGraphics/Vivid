#include <algorithm>

#include "base/EventDispatcher.h"
#include "base/Event.h"
#include "base/EventListener.h"

namespace te
{
    EventDispatcher* Singleton<EventDispatcher>::_singleton = nullptr;

    void EventDispatcher::dispatch(Event* event)
    {
        ListenType listen_type = event->getListenType();
        EventListenerMap::iterator itr = _listener_map.find(listen_type);
        if (itr == _listener_map.end())
        {
            //TE_LOG("No related event listener exists!");
            return;
        }
        EventListenerList& eventlistener_list = _listener_map[listen_type];
        for (EventListenerList::iterator itr = eventlistener_list.begin();
        itr != eventlistener_list.end(); ++itr)
        {
            (*itr)->exec(event);
        }
    }

    void EventDispatcher::removeEventListener(ListenType listen_type, size_t listener_id)
    {
        if (_listener_map.find(listen_type) != _listener_map.end())
        {
            _listener_map[listen_type][listener_id] = nullptr;
            if (_free_map.find(listen_type) == _free_map.end())
            {
                EventListenerFreeList free_list;
                free_list.push_back(listener_id);
                _free_map.insert(std::make_pair(listen_type, free_list));
            }
            else
                _free_map[listen_type].push_back(listener_id);
        }
        else
        {
            //log
        }
    }

}


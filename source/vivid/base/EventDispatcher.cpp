#include <algorithm>

#include "vivid/base/EventDispatcher.h"
#include "vivid/base/Event.h"
#include "vivid/base/EventListener.h"
#include "vivid/io/Logger.h"

namespace te
{
    EventDispatcher* Singleton<EventDispatcher>::_singleton = nullptr;

    void EventDispatcher::dispatch(Event* event)
    {
        ListenType listen_type = event->getListenType();
        EventListenerMap::iterator itr = _listener_map.find(listen_type);
        if (itr == _listener_map.end())
        {
            cLog << StringUtils::format("ListenType %d: Event has not related event listener!", listen_type);
            return;
        }
        EventListenerList& eventlistener_list = _listener_map[listen_type];
        for (EventListenerList::iterator itr = eventlistener_list.begin();
        itr != eventlistener_list.end(); ++itr)
        {
            if (*itr) (*itr)->exec(event);
            else continue;  // Null because of removing...may have performance issue
        }
    }

    void EventDispatcher::addEventListener(EventFunctionalListener* event_listener)
    {
        ListenType listen_type = event_listener->getListenType();
        if (_free_map.find(listen_type) == _free_map.end() || _free_map[listen_type].empty())
        {
            if (_listener_map.find(listen_type) == _listener_map.end())
            {
                EventListenerList eventlistener_list;
                eventlistener_list.push_back(event_listener);
                _listener_map.insert(std::make_pair(listen_type, eventlistener_list));
            }
            else
                _listener_map[listen_type].push_back(event_listener);
            event_listener->setListenerId(_listener_map[listen_type].size() - 1);
        }
        else
        {
            // allocate the first null position to the listener
            size_t free_pos = _free_map[listen_type][0];
            _listener_map[listen_type][free_pos] = event_listener;
            _free_map[listen_type].erase(_free_map[listen_type].begin());
            event_listener->setListenerId(free_pos);
        }
    }

    void EventDispatcher::removeEventListener(ListenType listen_type, size_t listener_id)
    {
        if (_listener_map.find(listen_type) != _listener_map.end() && _listener_map[listen_type].size() > listener_id)
        {
            delete _listener_map[listen_type][listener_id];
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
            cLog << StringUtils::format("ListenType %d or ListenId %d doesn't exists!", listen_type, listener_id);
        }
    }

    size_t connect(ListenType listen_type, EventFunctionalListener::EventCallback call_back)
    {
        EventFunctionalListener* event_listener = new EventFunctionalListener(listen_type, call_back);
        EventDispatcher::getInstance()->addEventListener(event_listener);
        return event_listener->getListenerId();
    }

    void unconnect(ListenType listen_type, size_t listener_id)
    {
        EventDispatcher::getInstance()->removeEventListener(listen_type, listener_id);
    }

}


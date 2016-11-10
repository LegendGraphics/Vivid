#include <algorithm>

#include "base/event_dispatcher.h"
#include "base/event.h"
#include "base/event_listener.h"
#include "base/macros.h"

EventDispatcher::EventDispatcher(){}

EventDispatcher::~EventDispatcher(){}

void EventDispatcher::addEventListener(EventListener* event_listener)
{
    int key = event_listener->getKey();
    if (_listener_map.find(key) == _listener_map.end())
    {
        EventListenerList eventlistener_list;
        eventlistener_list.push_back(event_listener);
        _listener_map.insert(std::make_pair(key, eventlistener_list));
    }
    else
        _listener_map[key].push_back(event_listener);
}

void EventDispatcher::removeEventListener(EventListener* event_listener)
{
    int key = event_listener->getKey();
    EventListenerMap::iterator map_itr = _listener_map.find(key);
    if (map_itr == _listener_map.end())
        TE_LOG("No such event listener exists!");
    else 
    {
        EventListenerList& eventlistener_list = _listener_map[key];
        EventListenerList::iterator list_itr = std::find(eventlistener_list.begin(), eventlistener_list.end(), event_listener);
        _listener_map[key].erase(list_itr);
    }
}

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
        if ((*itr)->getType() == EventListener::CPP_LISTENER)
            ((*itr)->getEventCallBack())(event);
        else
            (*itr)->invokeLuaCallback(event);
    }
}


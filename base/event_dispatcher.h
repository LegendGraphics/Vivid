#ifndef BASE_EVENT_DISPATCHER_H
#define BASE_EVENT_DISPATCHER_H

#include <map>
#include <vector>

#include "base/ref.h"

class Event;
class EventListenerBase;

class EventDispatcher: public Ref
{
private:
    typedef std::vector<EventListenerBase*> EventListenerList;
    typedef std::map<int, EventListenerList> EventListenerMap;

public:
    EventDispatcher();
    ~EventDispatcher();

    template <class T>
    void addEventListener(EventListener* event_listener);

    void removeEventListener(EventListener* event_listener);
    
    void dispatch(Event* event);

private:
    EventListenerMap _listener_map;
};


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

#endif // BASE_EVENT_DISPATCHER_H
#ifndef BASE_EVENT_DISPATCHER_H
#define BASE_EVENT_DISPATCHER_H

#include <unordered_map>
#include <vector>

#include "base/EventListener.h"
#include "base/Singleton.hpp"

namespace te
{
    class Event;
    class EventListenerBase;

    class EventDispatcher : public Singleton<EventDispatcher>
    {
    private:
        typedef std::vector<EventListenerBase*> EventListenerList;
        typedef std::vector<size_t> EventListenerFreeList;
        typedef std::unordered_map<ListenType, EventListenerList> EventListenerMap;
        typedef std::unordered_map<ListenType, EventListenerFreeList> EventListenerFreeMap;

    public:
        template <class T>
        void addEventListener(EventClassListener<T>* event_listener);

        void addEventListener(EventFunctionalListener* event_listener);

        void removeEventListener(ListenType listen_type, size_t listener_id);

        void dispatch(Event* event);

    private:
        EventListenerMap        _listener_map;
        EventListenerFreeMap    _free_map;
    };

    template <class T>
    void EventDispatcher::addEventListener(EventClassListener<T>* event_listener)
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

    template <class T>
    size_t connect(ListenType listen_type, T* instance, typename EventClassListener<T>::EventCallback call_back)
    {
        EventClassListener<T>* event_listener = new EventClassListener<T>(listen_type, instance, call_back);
        EventDispatcher::getInstance()->addEventListener(event_listener);
        return event_listener->getListenerId();
    }
    size_t connect(ListenType listen_type, EventFunctionalListener::EventCallback call_back);
    void unconnect(ListenType listen_type, size_t listener_id);
}


#endif // BASE_EVENT_DISPATCHER_H
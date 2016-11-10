#ifndef BASE_EVENT_LISTENER_H
#define BASE_EVENT_LISTENER_H

#include <string>

#include "base/ref.h"
#include "base/event.h"

typedef int LUA_CALLBACK;

class EventListener: public Ref
{
public:
    enum ListenerType
    {
        LUA_LISTENER,
        CPP_LISTENER
    };

public:
    typedef void(*EventCallback)(Event*); 
 
public:
    EventListener(int key, LUA_CALLBACK callback);
    EventListener(int key, const EventCallback& callback);
    virtual ~EventListener();

    int getKey() const { return _key; }
    int getType() const { return _type; }
    const EventCallback& getEventCallBack() const { return _callback; }
    int getLuaCallback() const { return _lua_callback; }
    
    void invokeLuaCallback(Event*);

protected:
    int _key;
    ListenerType _type;
    EventCallback _callback;
    LUA_CALLBACK _lua_callback;
};

#endif // BASE_EVENT_LISTENER_H
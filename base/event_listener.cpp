
#include "base/event_listener.h"
#include "base/macros.h"
#include "scripting/lua_utils.h"

EventListener::EventListener(int key, const EventCallback& callback)
:_key(key),
_callback(callback),
_type(CPP_LISTENER)
{
}

EventListener::EventListener(int key, LUA_CALLBACK callback)
:_key(key),
_lua_callback(callback),
_type(LUA_LISTENER)
{
}

EventListener::~EventListener(){}

void EventListener::invokeLuaCallback(Event* event)
{
    if(_lua_callback > 0)
    {
        TE_LOG("lua callback handler:%d", _lua_callback);
        MouseEvent* mouse_event = dynamic_cast<MouseEvent*>(event);
        tolua_pushusertype(L, mouse_event, "MouseEvent");
        toluafix_execute_function_by_handler(L, _lua_callback, 1);
    }
}

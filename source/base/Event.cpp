
#include "base/Event.h"

namespace te
{
    Event::Event()
        :_type(EventType::UNDEFINED)
    {

    }

    Event::Event(EventType type)
        :_type(type)
    {
    }

    EventKey Event::mapToKey() const
    {
        return EventKey(_type);
    }

    Event::~Event() {}

    MouseEvent::MouseEvent(MouseEventType mouse_type, MouseButton mouse_button, float x, float y)
        :Event(EventType::MOUSE),
        _mouse_type(mouse_type),
        _mouse_button(mouse_button),
        _x(x),
        _y(y)
    {}

    MouseEvent::~MouseEvent() {}

    EventKey MouseEvent::mapToKey() const
    {
        return EventKey(_type) + EventKey(_mouse_type) + EventKey(_mouse_button);
    }
}


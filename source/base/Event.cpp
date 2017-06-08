
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

    Event::~Event() {}

    MouseEvent::MouseEvent(MouseEventType mouse_type, MouseButton mouse_button, float x, float y)
        :Event(EventType::MOUSE),
        _mouse_type(mouse_type),
        _mouse_button(mouse_button),
        _x(x),
        _y(y)
    {}

    MouseEvent::~MouseEvent() {}

    ListenType MouseEvent::mapToListenType() const
    {
        return ListenType(EventKey(_type) + EventKey(_mouse_button));
    }
}


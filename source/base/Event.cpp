
#include "base/Event.h"

namespace te
{
    Event::Event(int key)
        :_key(key)
    {

    }

    Event::~Event() {}


    MouseEvent::MouseEvent(int key, float x, float y)
        :Event(key),
        _x(x),
        _y(y)
    {

    }

    MouseEvent::~MouseEvent() {}
}


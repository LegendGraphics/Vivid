#ifndef BASE_EVENT_H
#define BASE_EVENT_H

namespace te
{
    using EventKey = unsigned int;

    class Event
    {
    public:
        enum class EventType: EventKey
        {
            UNDEFINED   = 0 << 8, 
            MOUSE       = 1 << 8,
            KEYBOARD    = 2 << 8
        };

    public:
        Event();
        Event(EventType type);
        virtual ~Event();

        EventKey getKey() const { return mapToKey(); }
        EventType type() { return _type; }
    protected:
        virtual EventKey mapToKey() const;
    protected:
        EventType   _type;
    };

    class MouseEvent : public Event
    {
    public:
        enum class MouseEventType: EventKey
        {
            MOUSE_NONE      =   0 << 4,
            MOUSE_DOWN      =   1 << 4,
            MOUSE_UP        =   2 << 4,
            MOUSE_MOVE      =   3 << 4,
            MOUSE_SCROLL    =   4 << 4
        };

        enum class MouseButton: EventKey
        {
            BUTTON_UNSET,
            BUTTON_LEFT,
            BUTTON_RIGHT,
            BUTTON_MIDDLE
        };

    public:
        MouseEvent(MouseEventType mouse_type, MouseButton mouse_button, float x, float y);
        virtual ~MouseEvent();

        float getX() { return _x; }
        float getY() { return _y; }

    protected:
        EventKey mapToKey() const override;
    protected:
        MouseEventType  _mouse_type;
        MouseButton     _mouse_button;
        float _x;
        float _y;
    };

}


#endif // BASE_EVENT_H
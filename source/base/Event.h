#ifndef BASE_EVENT_H
#define BASE_EVENT_H

namespace te
{
    using EventKey = unsigned int;

    enum class ListenType: EventKey;

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

        ListenType getListenType() const { return mapToListenType(); }
        EventType type() { return _type; }
    protected:
        virtual ListenType mapToListenType() const = 0;
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
        ListenType mapToListenType() const override;
    protected:
        MouseEventType  _mouse_type;
        MouseButton     _mouse_button;
        float _x;
        float _y;
    };

    enum class ListenType : EventKey
    {
        MOUSE_LEFT = EventKey(Event::EventType::MOUSE) + EventKey(MouseEvent::MouseButton::BUTTON_LEFT),
        MOUSE_RIGHT = EventKey(Event::EventType::MOUSE) + EventKey(MouseEvent::MouseButton::BUTTON_RIGHT),
        MOUSE_MIDDLE = EventKey(Event::EventType::MOUSE) + EventKey(MouseEvent::MouseButton::BUTTON_MIDDLE),
    };

}


#endif // BASE_EVENT_H
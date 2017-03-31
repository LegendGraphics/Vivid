#ifndef BASE_EVENT_H
#define BASE_EVENT_H

namespace te
{
    enum EventType
    {
        TE_MOUSE_LEFT_DOWN = 0,
        TE_MOUSE_LEFT_UP = 1,
        TE_MOUSE_RIGHT_DOWN = 2,
        TE_MOUSE_RIGHT_UP = 3
    };

    class Event
    {
    public:
        Event(int key);
        virtual ~Event();

        int getKey() { return _key; }

    protected:
        int _key;
    };


    class MouseEvent : public Event
    {
    public:
        MouseEvent(int key, float x, float y);
        virtual ~MouseEvent();

        float getX() { return _x; }
        float getY() { return _y; }

    protected:
        float _x;
        float _y;
    };

}


#endif // BASE_EVENT_H
#include "common/Node.h"
#include "base/EventDispatcher.h"

using namespace te;

class Foo
{
public:
    void memberFunction(Event* event)
    {
        std::cout << "Foo::memberFunction" << std::endl;
    }
};

int main()
{
    int id1 = connect(ListenType::MOUSE_LEFT, [](Event*) {
        std::cout << "Xiaochen Fan" << std::endl;
    });
    EventDispatcher::getInstance()->dispatch(new MouseEvent(
        MouseEvent::MouseEventType::MOUSE_DOWN,
        MouseEvent::MouseButton::BUTTON_LEFT,
        100,
        100));

    unconnect(ListenType::MOUSE_LEFT, id1);
    EventDispatcher::getInstance()->dispatch(new MouseEvent(
        MouseEvent::MouseEventType::MOUSE_DOWN,
        MouseEvent::MouseButton::BUTTON_LEFT,
        100,
        100));


    int id2 = connect(ListenType::MOUSE_LEFT, [](Event*) {
        std::cout << "Lin Ma" << std::endl;
    });
    EventDispatcher::getInstance()->dispatch(new MouseEvent(
        MouseEvent::MouseEventType::MOUSE_DOWN,
        MouseEvent::MouseButton::BUTTON_LEFT,
        100,
        100));

    connect<Foo>(ListenType::MOUSE_LEFT, new Foo, &Foo::memberFunction);
    EventDispatcher::getInstance()->dispatch(new MouseEvent(
        MouseEvent::MouseEventType::MOUSE_DOWN,
        MouseEvent::MouseButton::BUTTON_LEFT,
        100,
        100));

    
    return 0;
}
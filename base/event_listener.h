#ifndef BASE_EVENT_LISTENER_H
#define BASE_EVENT_LISTENER_H

#include <string>

#include "base/ref.h"
#include "base/event.h"

class EventListenerBase: public Ref
{
public:
  virtual ~EventListenerBase() {};
  void exec(Event* event) {call(event);}

private:
  virtual void call(Event*) = 0;
};


template <class T>
class EventListener: public EventListenerBase
{
public:
    typedef void(T::*EventCallback)(Event*);
public:
    EventListener(int key, T* instance, EventCallback callback):_instance(instance), _callback(callback){};
    virtual ~EventListener();

    int getKey() const { return _key; }

    void call(Event* event)
    {
        (_instance->*_callback)(event);
    }

protected:
    int _key;
    T*  _instance;
    EventCallback _callback;
};



#endif // BASE_EVENT_LISTENER_H
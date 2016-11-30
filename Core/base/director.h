#ifndef BASE_DIRECTOR_H
#define BASE_DIRECTOR_H

#include <boost/chrono.hpp>


#include "base/ref.h"
#include "base/refptr.hpp"
#include "base/data_types.h"
#include "base/scheduler.h"
#include "base/event_dispatcher.h"
#include "common/scene.h"
#include "common/node_visitor.h"
#include "renderer/renderer.h"


class GLFWwindow;

enum TEStatus
{
    TE_RUNNING = 0,
    TE_STOPPED = 1
};

class Director: public Ref
{
public:
    static Director* getInstance();

    void setWindowSize(float window_width, float window_height);
    const Size& getWindowSize() const{ return _window_size; }

    void setActiveScene(Scene* active_scene);
    Scene* getActiveScene() { return _active_scene.get(); }

    Scheduler* getScheduler() { return _scheduler.get(); }

    EventDispatcher* getEventDispatcher() { return _event_dispatcher.get(); }

    float getDeltaTime() const { return _delta_time; }

    void start();

private:
    bool initialize();

    /** calculates delta time since last time it was called */    
    void calculateDeltaTime();

    void initWindow();

    void mainLoop();

    void updateLogic();
    void updateScene();

    static void onEvent(GLFWwindow* window, int button, int action, int mods);

private:
    Director(){};

private:
    typedef boost::chrono::steady_clock::time_point BoostTime;
    typedef boost::chrono::duration<float> BoostDuration;

private:
    static Director* _director;

    TEStatus _te_status; 

    RefPtr<Scheduler> _scheduler;
    RefPtr<Scene> _active_scene;
    RefPtr<Renderer> _renderer;
    RefPtr<NodeVisitor> _node_visitor;
    RefPtr<EventDispatcher> _event_dispatcher;

    GLFWwindow* _window;
    
    /* last time the main loop was updated */
    BoostTime _last_update; 
    /* delta time since last tick to main loop */
	float _delta_time;
    
    Size _window_size;

};

#endif // BASE_DIRECTOR_H
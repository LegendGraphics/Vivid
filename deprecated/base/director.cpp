
#include <algorithm>
#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "base/director.h"
#include "base/macros.h"
#include "base/event.h"
#include "scripting/lua_utils.h"


Director* Director::_director = NULL;

Director* Director::getInstance()
{
    if (!_director)
    {
        _director = new Director();
        _director->initialize();
    }

    return _director;
}

bool Director::initialize()
{
    _scheduler = new Scheduler();
    _renderer = new Renderer();
    _node_visitor = new NodeVisitor();
    _event_dispatcher = new EventDispatcher();
    _active_scene = NULL;
    _te_status = TE_STOPPED;

    return true;
}

void Director::setWindowSize(float window_width, float window_height)
{
    _window_size = Size(window_width, window_height);
}

void Director::setActiveScene(Scene* active_scene)
{
    _active_scene = active_scene;
}


void Director::calculateDeltaTime()
{
    BoostTime current_time = boost::chrono::steady_clock::now();

    _delta_time = BoostDuration(current_time - _last_update).count();
    _delta_time = std::max(0.0f, _delta_time);

    _last_update = current_time;
}

void Director::mainLoop()
{   
    while (_te_status == TE_RUNNING)
    {
        calculateDeltaTime();
        TE_LOG("fps:%f", 1.0 / _delta_time);

        updateScriptLogic();
        
        updateLogic();

        updateScene();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }   
}

void Director::updateLogic()
{
    // logic
    _scheduler->update(_delta_time);
}

void Director::updateScene()
{
    // render
    _renderer->clear();
    if (_active_scene)
        _renderer->render(_active_scene.get(), _node_visitor.get());
}

void Director::initWindow()
{
    int width = (int)_window_size.width;
    int height = (int)_window_size.height;

    TE_ASSERT(width != 0 || height != 0, "Please set right window's size!");
    
    // init window
    if (!glfwInit()) 
    {
        TE_ERROR("Unable to initialize GLFW ... exiting");
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    _window = glfwCreateWindow(width, height, "TinyEngine", NULL, NULL);
    if (!_window)
    {
        TE_ERROR("Unable to initialize window ... exiting");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(_window);

    glfwSetMouseButtonCallback(_window, Director::onEvent);
    
    // init shader functions
    if (glewInit()) 
    {
        TE_ERROR("Unable to initialize GLEW ... exiting");
        exit(EXIT_FAILURE);
    }

}

void Director::start()
{
    _last_update = boost::chrono::steady_clock::now();
    _te_status = TE_RUNNING;

    initWindow();
    mainLoop();
}

void Director::onEvent(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {   
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        MouseEvent event(TE_MOUSE_LEFT_DOWN, float(xpos), float(ypos));
        Director::getInstance()->getEventDispatcher()->dispatch(&event);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        MouseEvent event(TE_MOUSE_LEFT_UP, float(xpos), float(ypos));
        Director::getInstance()->getEventDispatcher()->dispatch(&event);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        MouseEvent event(TE_MOUSE_RIGHT_DOWN, float(xpos), float(ypos));
        Director::getInstance()->getEventDispatcher()->dispatch(&event);
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        MouseEvent event(TE_MOUSE_RIGHT_UP, float(xpos), float(ypos));
        Director::getInstance()->getEventDispatcher()->dispatch(&event);
    }
}
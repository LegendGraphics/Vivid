#include "vivid/base/Director.h"

#include <algorithm>
#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "vivid/common/NodeVisitor.h"
#include "vivid/common/Scene.h"
#include "vivid/common/Camera.h"
#include "vivid/base/Assert.h"
#include "vivid/base/EventDispatcher.h"
#include "vivid/io/Logger.h"
#include "vivid/renderer/RenderInterface.h"

namespace te
{
    Director* Singleton<Director>::_singleton = nullptr;

    bool Director::initialize()
    {
        // init engine modules
        RenderInterface::getInstance()->init();
        RenderInterface::getInstance()->registerWorld();
        return true;
    }

    void Director::setActiveScene(Scene* active_scene)
    {
        _active_scene = active_scene;
    }


    void Director::calculateDeltaTime()
    {
        _delta_time = _timer.getElapsedTime();
        //std::cout << _delta_time << std::endl;
        _delta_time = std::max(0.0f, _delta_time);

        _timer.reset();
    }

    void Director::mainLoop()
    {
        while (true)
        {
            calculateDeltaTime();
            //TE_LOG("fps:%f", 1.0 / _delta_time);
            //std::cout << "fps:" << 1.0 / _delta_time << std::endl;
            spacingUpdate();
            cullingUpdate();
            _active_scene->getActiveCamera()->updateBehavior();
            renderingUpdate();

            // waiting events
            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }

    void Director::cullingUpdate()
    {
        // culling scene
        CullingVisitor visitor(NodeVisitor::TraversalMode::TRAVERSE_CHILDREN, _active_scene->getActiveCamera());
        visitor.apply(_active_scene->getSceneRoot());
    }

    void Director::spacingUpdate()
    {
        // update space status
        BehaviorVisitor visitor(NodeVisitor::TraversalMode::TRAVERSE_CHILDREN);
        visitor.apply(_active_scene->getSceneRoot());
    }

    void Director::renderingUpdate()
    {
        RenderInterface::getInstance()->setCamera(_active_scene->getActiveCamera()->getComponent<CameraState>());

        // update world
        RenderResourceVisitor visitor_update(NodeVisitor::TraversalMode::TRAVERSE_CHILDREN, RenderInterface::getInstance(), _active_scene);
        visitor_update.apply(_active_scene->getSceneRoot());
        RenderInterface::getInstance()->updateWorld();

        // render world
        RenderVisitor visitor(NodeVisitor::TraversalMode::TRAVERSE_CHILDREN, RenderInterface::getInstance(), _active_scene);
        visitor.apply(_active_scene->getSceneRoot());
        RenderInterface::getInstance()->renderWorld();
    }

    void Director::start()
    {
        _timer.setEnabled(true);

        FocusCamera* focus_camera = new FocusCamera;
        focus_camera->getComponent<CameraState>()->setCameraMode(CameraState::CameraMode::ORTHOGONAL);
        focus_camera->getComponent<CameraState>()->setViewPort(Vector4(0, 0, 800, 600));
        focus_camera->getComponent<CameraState>()->setViewTransform(CameraState::CameraViewParas(
            Vector3(200, 300, 200), Vector3(0, 100, 0), Vector3(0, 1, 0)));
        focus_camera->getComponent<CameraState>()->setOrthoProjectTransform(CameraState::CameraOrthoParas(
            -100, 100, -100, 100, -10, -1000));
        _active_scene->setActiveCamera(focus_camera);

        initWindow();
        RenderInterface::getInstance()->openDevice();

        mainLoop();
    }

    void Director::initWindow()
    {
        int width = 800;
        int height = 600;

       // ASSERT(width != 0 || height != 0, "Please set right window's size!");

        // init window
        if (!glfwInit())
        {
            cLog << ("Unable to initialize GLFW ... exiting");
            exit(EXIT_FAILURE);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        _window = glfwCreateWindow(width, height, "TinyEngine", NULL, NULL);
        if (!_window)
        {
            cLog << ("Unable to initialize window ... exiting");
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(_window);

        glfwSetMouseButtonCallback(_window, Director::onEvent);


        // init shader functions
        if (glewInit())
        {
            cLog << ("Unable to initialize GLEW ... exiting");
            exit(EXIT_FAILURE);
        }

    }

    // temporarily put GUI staff in Director class
    void Director::onEvent(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MouseEvent event(MouseEvent::MouseEventType::MOUSE_DOWN, MouseEvent::MouseButton::BUTTON_LEFT, (xpos), float(ypos));
            EventDispatcher::getInstance()->dispatch(&event);
        }
        else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MouseEvent event(MouseEvent::MouseEventType::MOUSE_UP, MouseEvent::MouseButton::BUTTON_LEFT, (xpos), float(ypos));
            EventDispatcher::getInstance()->dispatch(&event);
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MouseEvent event(MouseEvent::MouseEventType::MOUSE_DOWN, MouseEvent::MouseButton::BUTTON_RIGHT, (xpos), float(ypos));
            EventDispatcher::getInstance()->dispatch(&event);
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MouseEvent event(MouseEvent::MouseEventType::MOUSE_UP, MouseEvent::MouseButton::BUTTON_RIGHT, (xpos), float(ypos));
            EventDispatcher::getInstance()->dispatch(&event);

        }
    }

    Vector2 Director::getCurMousePos()
    {
        double xpos, ypos;
        glfwGetCursorPos(_window, &xpos, &ypos);
        return Vector2(xpos, ypos);
    }

}

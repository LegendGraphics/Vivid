#include "base/Director.h"

#include <algorithm>

namespace te
{
    Director* Director::_director = nullptr;

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
        // init engine modules

        return true;
    }

    void Director::setActiveScene(Scene* active_scene)
    {
        _active_scene = active_scene;
    }


    void Director::calculateDeltaTime()
    {
        _delta_time = _timer.getElapsedTime();
        _delta_time = std::max(0.0f, _delta_time);

        _timer.setEnabled(false);
    }

    void Director::mainLoop()
    {
        while (true)
        {
            calculateDeltaTime();
            //TE_LOG("fps:%f", 1.0 / _delta_time);

            cullUpdate();
            logicUpdate();
            sceneUpdate();

            // waiting events
        }
    }

    void Director::cullUpdate()
    {
        // culling scene
    }

    void Director::logicUpdate()
    {
        // update logic status
    }

    void Director::sceneUpdate()
    {
        // rendering scene
    }



    void Director::start()
    {
        _timer.setEnabled(true);

        mainLoop();
    }

}

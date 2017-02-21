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
        std::cout << _delta_time << std::endl;
        _delta_time = std::max(0.0f, _delta_time);

        _timer.reset();
    }

    void Director::mainLoop()
    {
        while (true)
        {
            calculateDeltaTime();
            //TE_LOG("fps:%f", 1.0 / _delta_time);
            std::cout << "fps:" << 1.0 / _delta_time << std::endl;
            cullUpdate();
            logicUpdate();
            sceneUpdate();
            for (int i = 0; i < 1000000; ++i) int a = 1;

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

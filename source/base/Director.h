#ifndef BASE_DIRECTOR_H
#define BASE_DIRECTOR_H

#include "base/Timer.h"

class GLFWwindow;

namespace te
{
    // init engine modules:
    //   - scene module
    //   - renderer module
    //   - event module
    //   ...

    // start main loop, updates in looping:
    //   - culling update
    //   - logic update
    //   - rendering update

    class Scene;
    class RenderInterface;

    class Director
    {
    public:
        static Director* getInstance();

        void setActiveScene(Scene* active_scene);
        Scene* getActiveScene() { return _active_scene; }

        float getDeltaTime() const { return _delta_time; }

        void start();

    private:
        bool initialize();

        /** calculates delta time since last time it was called */
        void calculateDeltaTime();

        void mainLoop();

        void spacingUpdate();
        void cullingUpdate();
        void renderingUpdate();

        void initWindow();
        void initResource();

    private:
        Director() {};

    private:
        static Director* _director;

        Scene* _active_scene;

        /* delta time since last tick to main loop */
        float _delta_time;

        Timer   _timer;

        GLFWwindow* _window;
    };

}


#endif // BASE_DIRECTOR_H
#ifndef COMMON_SCENE_H
#define COMMON_SCENE_H

#include "common/Resource.h"

namespace te
{
    // xml file
    class SceneGraphRes : public Resource
    {
    public:
        void release();
        bool load(const char *data, int size);

    private:
        friend class SceneManager;
    };
}

#endif // COMMON_SCENE_H
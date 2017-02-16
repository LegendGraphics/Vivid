#include "common/Scene.h"

namespace te
{
    void SceneGraphRes::release()
    {
    }


    bool SceneGraphRes::load(const char *data, int size)
    {
        if (!Resource::load(data, size)) return false;

        // need to parse xml file

        return true;
    }
}


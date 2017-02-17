#include "common/Scene.h"
#include "./3rdparty/rapid_xml/include/utXML.h"

namespace te
{
    void SceneGraphRes::release()
    {
    }


    bool SceneGraphRes::load(const char *data, int size)
    {
        if (!Resource::load(data, size)) return false;

        XMLDoc doc;
        doc.parseBuffer(data, size);
        if (doc.hasError())
        {
            return false;
        }

        // Parse scene nodes and load resources
        XMLNode root = doc.getRootNode();
        if (!root.isEmpty())
        {
            parseNode(root, 0x0);
        }
        else
        {
            return false;
        }

        return true;
    }
}


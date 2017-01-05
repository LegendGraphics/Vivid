#ifndef COMMON_RESOURCE_H
#define COMMON_RESOURCE_H

#include "common/Object.h"

namespace te
{
    class Resource : public Object
    {
    public:
        Resource(int type, int flags);
        Resource(const Resource& resource, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Resource();
        
        OBJECT_META_FUNCTION(Resource);

        virtual void release();
        virtual bool load(const char *data, int size);
        void unload();

    protected:
        int                  _type;
        int                  _flags;

        bool                 _loaded;

        friend class ResourceManager;
    };
}

#endif // COMMON_RESOURCE_H
#ifndef COMMON_OBJECT_H
#define COMMON_OBJECT_H

#include <string>

#include "base/ref.h"
#include "common/copy_operator.h"


namespace te
{
    class Object: public Ref 
    {
    public:

        // some meta macros needed
        // and what is meta data for object?
        virtual Object* clone(const CopyOperator& copyop) const = 0;

        virtual bool isSameKindAs(const Object*) const { return true; }

        virtual std::string libraryName() const = 0;
        virtual std::string className() const = 0;

        virtual void setName( const std::string& name ) { _name = name; }
        inline const std::string& getName() const { return _name; }

    protected:
        virtual ~Object();

        std::string _name;
        unsigned int _id;

        TE_DECLARE_INTERFACE()
    };
}


#endif // COMMON_OBJECT_H
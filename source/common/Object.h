#ifndef COMMON_OBJECT_H
#define COMMON_OBJECT_H

#include <string>

#include "base/ref.h"
#include "common/CopyOperator.h"

#define OBJECT_META_FUNCTION(CLASS)																		\
virtual std::string className() const { return #CLASS; }												\
virtual Object* clone(const CopyOperator& copyop) const { return new CLASS(*this, copyop); }			\
virtual bool isSameKindAs(const Object* object) const { return dynamic_cast<const CLASS *>(object) != nullptr; }

namespace te
{
	static unsigned int ObjectId = 0;

    class Object: public Ref 
    {
    public:
		Object();
		virtual ~Object() = default;

		virtual std::string className() const = 0;
        virtual Object* clone(const CopyOperator& copyop) const = 0;
		virtual bool isSameKindAs(const Object* object) { return true; }

        void setName(const std::string& name) { _name = name; }
        inline const std::string& getName() const { return _name; }

		inline unsigned int getId() const { return _id;  }

    protected:
        std::string _name;
        unsigned int _id;

        TE_DECLARE_INTERFACE()
    };
}


#endif // COMMON_OBJECT_H
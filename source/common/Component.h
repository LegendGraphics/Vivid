#ifndef COMMON_COMPONENT_H
#define COMMON_COMPONENT_H

#include <string>
#include <array>
#include <bitset>

#include "base/ref.h"
#include "base/refptr.hpp"
#include "common/object.h"


namespace te
{
    class Component: public Object
    {
        public:
            Component();
			Component(const Component& component, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
            virtual ~Component();

			OBJECT_META_FUNCTION(Component);

            virtual void init();
            virtual void update();

            bool isEnabled() const { return _enabled; }
            void setEnabled(bool enabled);

            const std::string& getName() const { return _name; }
            void setName(const std::string& name);

        protected:
            std::string _name;
            bool _enabled;
    };

}


#endif // COMMON_COMPONENT_H
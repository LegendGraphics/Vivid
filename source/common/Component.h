#ifndef COMMON_COMPONENT_H
#define COMMON_COMPONENT_H

#include <string>
#include <array>
#include <bitset>

#include "base/Ref.h"
#include "base/Refptr.hpp"
#include "base/String.h"
#include "common/Clone.h"


namespace te
{
    class Node;

    class Component: public Ref
    {
    public:
        Component();
        Component(const Component& component, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Component();

        virtual void init();
        virtual void update();

        inline bool isEnabled() const { return _enabled; }
        void setEnabled(bool enabled);

        inline const String& getName() const { return _name; }
        void setName(const String& name);

        inline Node* getOwner() const { return _owner; }
        void setOwner(Node* owner);

    protected:
        String _name;
        bool _enabled;
        Node* _owner;
    };

}


#endif // COMMON_COMPONENT_H
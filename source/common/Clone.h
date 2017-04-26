#ifndef COMMON_CLONE_H
#define COMMON_CLONE_H

#define ENABLE_CLONE(CLASS)                                                                     \
virtual CLASS* clone(const CopyOperator& copyop) const { return new CLASS(*this, copyop); }

namespace te
{
    class Node;
    class NodeTree;
    class Component;
    class ComponentContainer;
    class Scene;

    class CopyOperator
    {
    public:
        enum Options
        {
            SHALLOW_COPY,
            DEEP_COPY
        };

        CopyOperator(const Options& flag = SHALLOW_COPY) :_flag(flag) {}
        CopyOperator& operator=(const Options& flag) { _flag = flag; return *this; }
        virtual ~CopyOperator() {}

        inline bool operator==(const Options& flag) const { return _flag == flag; }

        virtual Node* operator()(const Node* node) const;
        virtual NodeTree* operator()(const NodeTree* node_tree) const;
        virtual Component* operator()(const Component* component) const;
        virtual ComponentContainer* operator()(const ComponentContainer* ccontainer) const;
        virtual Scene* operator()(const Scene* scene) const;

    private:
        Options _flag;
    };

    struct Cloneable
    {
        virtual Cloneable*  clone(const CopyOperator& copyop) { return nullptr; }
    };

}


#endif // COMMON_CLONE_H
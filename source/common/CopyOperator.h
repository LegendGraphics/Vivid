#ifndef COMMON_COPY_OPERATOR_H
#define COMMON_COPY_OPERATOR_H

namespace te
{
    class Object;
    class Node;
	class ComponentContainer;


    class CopyOperator
    {
    public:
        enum Options
        {
            SHALLOW_COPY,
            DEEP_COPY
        };

        CopyOperator(const Options& flag = SHALLOW_COPY):_flag(flag) {}
		CopyOperator& operator=(const Options& flag) { _flag = flag; return *this; }
        virtual ~CopyOperator() {}

		inline bool operator==(const Options& flag) const { return _flag == flag; }

        virtual Object*	operator()(const Object* object) const;
        virtual Node* operator()(const Node* node) const;
		virtual ComponentContainer*	operator()(const ComponentContainer* ccontainer) const;

    private:
        Options _flag;
    };
}


namespace te
{
    template<typename T>
    T* clone(const T* t, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY)
    {
        if (t)
        {
            Object* obj = t->clone(copyop);

            T* ptr = dynamic_cast<T*>(obj);
            if (ptr) return ptr;
            else
            {
                // log output
                return nullptr;
            }
        }
        else
        {
            // log output
            return nullptr;
        }
    }
}

#endif // COMMON_COPY_OPERATOR_H
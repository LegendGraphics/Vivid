#ifndef COMMON_COPY_OPERATOR_H
#define COMMON_COPY_OPERATOR_H

namespace te
{
    class Object;
    class Node;


    class CopyOperator
    {
    public:
        enum Options
        {
            SHALLOW_COPY,
            DEEP_COPY
        };

        CopyOperator(const Options& flag = SHALLOW_COPY):_flag(flag) {}
        virtual ~CopyOperator() {}

        //virtual Object* operator()(const Object* object) const;
        //virtual Node*   operator()(const Node* node) const;

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
            RefPtr<te::Object> obj = t->clone(copyop);

            T* ptr = dynamic_cast<T*>(obj.get());
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
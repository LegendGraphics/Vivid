#ifndef COMMON_COPY_OPERATOR_H
#define COMMON_COPY_OPERATOR_H

namespace te
{
    class CopyOperator
    {
    public:
        enum class Options
        {
            SHALLOW_COPY          = 0,
            DEEP_COPY_OBJECTS     = 1<<0,
            DEEP_COPY_NODES       = 1<<1
        };

    };
}

#endif // COMMON_COPY_OPERATOR_H
#ifndef BASE_VARIANT_H
#define BASE_VARIANT_H

namespace te
{
    class Var
    {
    private:
        union ValueUnion
        {
            double d;
            float  f;
            int    i;
            bool   b;
            void   *ptr;
        };

        ValueUnion _value;
    };
}

#endif // BASE_VARIANT_H
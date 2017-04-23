#ifndef BASE_VARIANT_H
#define BASE_VARIANT_H

#include "base/String.h"

namespace te
{
    class Var
    {
    public:
        enum class ValueType
        {
            UNDEFINED,
            DOUBLE,
            FLOAT,
            INT,
            BOOL,
            STRING
        };

    private:
        class VariantType;
        class VariantDouble;
        class VariantFloat;
        class VariantInt;
        class VariantBool;
        class VariantString;

    private:
        union ValueUnion
        {
            double  d;
            float   f;
            int     i;
            bool    b;
            char*   s;
        };
        
    public:
        Var(const Var& var);
        Var(double d);
        Var(float f);
        Var(int i);
        Var(bool b);
        Var(String s);
        ~Var();

        Var& operator=(const Var& var);
        Var& operator=(double d);
        Var& operator=(float f);
        Var& operator=(int i);
        Var& operator=(bool b);
        Var& operator=(String s);

        double toDouble();
        float toFloat();
        int toInt();
        bool toBool();
        String toString();

        ValueType type();

    private:
        void destroyVar();

    private:
        ValueUnion              _value;
        const VariantType*      _type;
    };
}

#endif // BASE_VARIANT_H
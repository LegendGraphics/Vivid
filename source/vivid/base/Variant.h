#ifndef VIVID_BASE_VARIANT_H
#define VIVID_BASE_VARIANT_H

#include "vivid/base/String.h"

namespace vivid
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

            ValueUnion() { memset(this, 0, sizeof(ValueUnion)); }
        };
        
    public:
        Var();
        Var(const Var& var);
        Var(double d);
        Var(float f);
        Var(int i);
        Var(bool b);
        Var(const char* s);
        Var(String s);
        ~Var();

        Var& operator=(const Var& var);
        Var& operator=(double d);
        Var& operator=(float f);
        Var& operator=(int i);
        Var& operator=(bool b);
        Var& operator=(const char* s);
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

#endif // VIVID_BASE_VARIANT_H

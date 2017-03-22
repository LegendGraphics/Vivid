#ifndef BASE_VARIANT_H
#define BASE_VARIANT_H

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
            BOOL
        };

    private:
        class VariantType;
        class VariantDouble;
        class VariantFloat;
        class VariantInt;
        class VariantBool;

    private:
        union ValueUnion
        {
            double d;
            float  f;
            int    i;
            bool   b;
        };
        
    public:
        Var(const Var& var);
        Var& operator=(const Var& var);
        Var& operator=(double d);
        Var& operator=(float f);
        Var& operator=(int i);
        Var& operator=(bool b);

        Var(double d);
        Var(float f);
        Var(int i);
        Var(bool b);

        double toDouble();
        float toFloat();
        int toInt();
        bool toBool();

        ValueType type();

    private:
        ValueUnion              _value;
        const VariantType*      _type;
    };
}

#endif // BASE_VARIANT_H
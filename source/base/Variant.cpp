#include "base/Variant.h"

namespace te
{
    class Var::VariantType
    {
    public:
        VariantType() noexcept {}
        virtual ~VariantType() noexcept {}

        virtual void setDouble(ValueUnion& value, double d) const noexcept {}
        virtual void setFloat(ValueUnion& value, float f) const noexcept {}
        virtual void setInt(ValueUnion& value, int i) const noexcept {}
        virtual void setBool(ValueUnion& value, bool b) const noexcept {}
        virtual void setString(ValueUnion& value, String s) const noexcept {}


        virtual double toDouble(const ValueUnion& value) const noexcept { return 0; }
        virtual float toFloat(const ValueUnion& value) const noexcept { return 0; }
        virtual int toInt(const ValueUnion& value) const noexcept { return 0; }
        virtual bool toBool(const ValueUnion& value) const noexcept { return false; }
        virtual String toString(const ValueUnion& value) const noexcept { return ""; }

        virtual bool isDouble() const noexcept { return false; }
        virtual bool isFloat() const noexcept { return false; }
        virtual bool isInt() const noexcept { return false; }
        virtual bool isBool() const noexcept { return false; }
        virtual bool isString() const noexcept { return false; }
    };

    class Var::VariantDouble: public Var::VariantType
    {
    public:
        VariantDouble() noexcept {}
        virtual ~VariantDouble() noexcept {}

        static const VariantDouble instance;

        virtual void setDouble(ValueUnion& value, double d) const noexcept { value.d = d; }

        virtual double toDouble(const ValueUnion& value) const noexcept override { return value.d; }
        virtual float toFloat(const ValueUnion& value) const noexcept override { return (float)value.d; }
        virtual int toInt(const ValueUnion& value) const noexcept override { return (int)value.d; }
        virtual bool toBool(const ValueUnion& value) const noexcept override { return value.d != 0; }
        virtual String toString(const ValueUnion& value) const noexcept override { return std::to_string(value.d); }

        virtual bool isDouble() const noexcept override { return true; }
    };

    class Var::VariantFloat : public Var::VariantType
    {
    public:
        VariantFloat() noexcept {}
        virtual ~VariantFloat() noexcept {}

        static const VariantFloat instance;

        virtual void setFloat(ValueUnion& value, float f) const noexcept { value.f = f; }

        virtual double toDouble(const ValueUnion& value) const noexcept override { return double(value.f); }
        virtual float toFloat(const ValueUnion& value) const noexcept override { return value.f; }
        virtual int toInt(const ValueUnion& value) const noexcept override { return (int)value.f; }
        virtual bool toBool(const ValueUnion& value) const noexcept override { return value.f != 0; }
        virtual String toString(const ValueUnion& value) const noexcept override { return std::to_string(value.f); }

        virtual bool isFloat() const noexcept override { return true; }
    };

    class Var::VariantInt : public Var::VariantType
    {
    public:
        VariantInt() noexcept {}
        virtual ~VariantInt() noexcept {}

        static const VariantInt instance;

        virtual void setInt(ValueUnion& value, int i) const noexcept { value.i = i; }

        virtual double toDouble(const ValueUnion& value) const noexcept override { return (double)value.i; }
        virtual float toFloat(const ValueUnion& value) const noexcept override { return (float)value.i; }
        virtual int toInt(const ValueUnion& value) const noexcept override { return value.i; }
        virtual bool toBool(const ValueUnion& value) const noexcept override { return value.i != 0; }
        virtual String toString(const ValueUnion& value) const noexcept override { return std::to_string(value.i); }

        virtual bool isInt() const noexcept override { return true; }
    };

    class Var::VariantBool : public Var::VariantType
    {
    public:
        VariantBool() noexcept {}
        virtual ~VariantBool() noexcept {}

        static const VariantBool instance;

        virtual void setBool(ValueUnion& value, bool b) const noexcept { value.b = b; }

        virtual double toDouble(const ValueUnion& value) const noexcept override { return value.b ? 1.0 : 0.0; }
        virtual float toFloat(const ValueUnion& value) const noexcept override { return value.b ? 1.0 : 0.0; }
        virtual int toInt(const ValueUnion& value) const noexcept override { return value.b ? 1 : 0; }
        virtual bool toBool(const ValueUnion& value) const noexcept override { return value.b; }
        virtual String toString(const ValueUnion& value) const noexcept override { return std::to_string(value.b); }

        virtual bool isBool() const noexcept override { return true; }
    };

    class Var::VariantString : public Var::VariantType
    {
    public:
        VariantString() noexcept {}
        virtual ~VariantString() noexcept {}

        static const VariantString instance;

        virtual void setString(ValueUnion& value, String s) const noexcept { if (value.s) delete[] value.s; value.s = StringUtils::convertToChar(s); }

        virtual double toDouble(const ValueUnion& value) const noexcept override { return std::stod(value.s); }
        virtual float toFloat(const ValueUnion& value) const noexcept override { return std::stof(value.s); }
        virtual int toInt(const ValueUnion& value) const noexcept override { return std::stoi(value.s); }
        virtual bool toBool(const ValueUnion& value) const noexcept override { return strlen(value.s) != 0; }
        virtual String toString(const ValueUnion& value) const noexcept override { return StringUtils::convertToString(value.s); }

        virtual bool isString() const noexcept override { return true; }
    };


    const Var::VariantDouble        Var::VariantDouble::instance;
    const Var::VariantFloat         Var::VariantFloat::instance;
    const Var::VariantInt           Var::VariantInt::instance;
    const Var::VariantBool          Var::VariantBool::instance;
    const Var::VariantString        Var::VariantString::instance;


    Var::Var(const Var& var)
    {
        *this = var;
    }

    Var::Var(double d)
        :_type(&VariantDouble::instance)
    {
        _type->setDouble(_value, d);
    }

    Var::Var(float f)
        : _type(&VariantFloat::instance)
    {
        _type->setFloat(_value, f);
    }

    Var::Var(int i)
        : _type(&VariantInt::instance)
    {
        _type->setInt(_value, i);
    }

    Var::Var(bool b)
        : _type(&VariantBool::instance)
    {
        _type->setBool(_value, b);
    }

    Var::Var(String s)
        : _type(&VariantString::instance)
    {
        _type->setString(_value, s);
    }

    Var::~Var()
    {
        destroyVar();
    }

    Var& Var::operator=(const Var& var)
    {
        this->_type = var._type;
        this->_value = var._value;
        return *this;
    }

    Var& Var::operator=(double d)
    {
        _type = &VariantDouble::instance;
        _type->setDouble(_value, d);
        return *this;
    }

    Var& Var::operator=(float f)
    {
        _type = &VariantFloat::instance;
        _type->setFloat(_value, f);
        return *this;
    }

    Var& Var::operator=(int i)
    {
        _type = &VariantInt::instance;
        _type->setInt(_value, i);
        return *this;
    }

    Var& Var::operator=(bool b)
    {
        _type = &VariantBool::instance;
        _type->setBool(_value, b);
        return *this;
    }

    Var& Var::operator=(String s)
    {
        _type = &VariantString::instance;
        _type->setString(_value, s);
        return *this;
    }


    double Var::toDouble()
    {
        return _type->toDouble(_value);
    }

    float Var::toFloat()
    {
        return _type->toFloat(_value);
    }

    int Var::toInt()
    {
        return _type->toInt(_value);
    }

    bool Var::toBool()
    {
        return _type->toBool(_value);
    }

    String Var::toString()
    {
        return _type->toString(_value);
    }

    Var::ValueType Var::type()
    {
        if (_type->isDouble()) return ValueType::DOUBLE;
        else if (_type->isFloat()) return ValueType::FLOAT;
        else if (_type->isInt()) return ValueType::INT;
        else if (_type->isBool()) return ValueType::BOOL;
        else if (_type->isString()) return ValueType::STRING;
        else return ValueType::UNDEFINED;
    }

    void Var::destroyVar()
    {
        // String need to be deleted manually
        if (_type->isString()) delete[] (_value.s);
    }
}
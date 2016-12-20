
#include "math/Vector3.h"
#include <cmath>



namespace te
{
    Vector3::Vector3()
        :x(0.0),
        y(0.0),
        z(0.0)
    {
    }

    Vector3::Vector3(const Vector3& v)
        :x(v.x),
        y(v.y),
        z(v.z)
    {
    }

    Vector3::Vector3(float x, float y, float z)
        :x(x),
        y(y),
        z(z)
    {}

    Vector3::~Vector3(){}

    Vector3& Vector3::operator=(const Vector3& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return *this;
    }

    void Vector3::set(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void Vector3::normalize()
    {
        (*this) /= length();
    }

    Vector3 Vector3::normalized() const
    {
        return (*this) / length();
    }

    float Vector3::length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    float Vector3::squaredLength() const
    {
        return (x * x + y * y + z * z);
    }

    float Vector3::dot(const Vector3& v1, const Vector3& v2)
    {
        return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }

    Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
    {
        float x = v1.y * v2.z - v1.z * v2.y;
        float y = - (v1.x * v2.z - v1.z * v2.x);
        float z = v1.x * v2.y - v1.y * v2.x;

        return Vector3(x, y, z);
    }

    float Vector3::angle(const Vector3& from_v, const Vector3& to_v)
    {
        float cos_angle = dot(from_v, to_v) / (from_v.length() * to_v.length());
        return acos(cos_angle);
    }
}


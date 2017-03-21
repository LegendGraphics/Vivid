
#ifndef MATH_VECTOR4_H
#define MATH_VECTOR4_H

#include <vector>

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace te
{
    class Vector4
    {
    public:
        Vector4();
        Vector4(const Vector4& v);
        Vector4(float x, float y, float z, float w);
        Vector4& operator=(const Vector4& v);
        ~Vector4();

        inline const Vector4 operator+(const Vector4& v) const { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
        inline Vector4& operator+=(const Vector4& v) { this->x += v.x; this->y += v.y; this->z += v.z; this->w += v.w; return *this; }
        inline const Vector4 operator-(const Vector4& v) const { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
        inline Vector4& operator-=(const Vector4& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; this->w -= v.w; return *this; }
        inline const Vector4 operator*(float s) const { return Vector4(x * s, y * s, z * s, w * s); }
        inline Vector4& operator*=(float s) { this->x *= s; this->y *= s; this->z *= s; this->w *= s; return *this; }
        inline const Vector4 operator/(float s) const { return Vector4(x / s, y / s, z / s, w / s); }
        inline Vector4& operator/=(float s) { this->x /= s; this->y /= s; this->z /= s; this->w /= s; return *this; }
        inline bool operator==(const Vector4& v) const
        {
            if ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w)) return true;
            else return false;
        }
        inline bool operator!=(const Vector4& v) const
        {
            return !(*this == v);
        }  

        void set(float x, float y, float z);
        void normalize();
        Vector4 normalized() const;
        float length() const;
        float squaredLength() const;

    public:
        float x;
        float y;
        float z;
        float w;

    public:
        static float dot(const Vector4& v1, const Vector4& v2);
    };

    typedef std::vector<Vector4> Vec4Array;

    Vector2 Vector4to2(const Vector4& vec4);
    Vector3 Vector4to3(const Vector4& vec4);
    Vector4 Vector2to4(const Vector2& vec2);
    Vector4 Vector3to4(const Vector3& vec3);
}



#endif // MATH_VECTOR4_H
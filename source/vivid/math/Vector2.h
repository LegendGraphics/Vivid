
#ifndef MATH_VECTOR2_H
#define MATH_VECTOR2_H

#include <vector>

#include "vivid/math/Vector3.h"

namespace te
{
    class Vector2
    {
    public:
        Vector2();
        Vector2(const Vector2& v);
        Vector2(float x, float y);
        Vector2& operator=(const Vector2& v);
        ~Vector2();

        inline const Vector2 operator+(const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
        inline Vector2& operator+=(const Vector2& v) { this->x += v.x; this->y += v.y; return *this; }
        inline const Vector2 operator-(const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
        inline Vector2& operator-=(const Vector2& v) { this->x -= v.x; this->y -= v.y; return *this; }
        inline const Vector2 operator*(float s) const { return Vector2(x * s, y * s); }
        inline Vector2& operator*=(float s) { this->x *= s; this->y *= s; return *this; }
        inline const Vector2 operator/(float s) const { return Vector2(x / s, y / s); }
        inline Vector2& operator/=(float s) { this->x /= s; this->y /= s; return *this; }
        inline bool operator==(const Vector2& v) const
        {
            if ((x == v.x) && (y == v.y)) return true;
            else return false;
        }
        inline bool operator!=(const Vector2& v) const
        {
            return !(*this == v);
        }  

        void set(float x, float y);
        void normalize();
        Vector2 normalized() const;
        float length() const;
        float squaredLength() const;

    public:
        float x;
        float y;

    public:
        static float dot(const Vector2& v1, const Vector2& v2);
        static float angle(const Vector2& from_v, const Vector2& to_v); // [0, pi]
    };

    typedef std::vector<Vector2> Vec2Array;

    Vector3 Vector2to3(const Vector2& vec2);
    Vector2 Vector3to2(const Vector3& vec3);

}


#endif // MATH_VECTOR2_H
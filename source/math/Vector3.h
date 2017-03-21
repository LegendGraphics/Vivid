
#ifndef MATH_VECTOR3_H
#define MATH_VECTOR3_H

#include <vector>

namespace te
{
    class Vector3
    {
    public:
        Vector3();
        Vector3(const Vector3& v);
        Vector3(float x, float y, float z);
        Vector3& operator=(const Vector3& v);
        ~Vector3();

        inline const Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
        inline Vector3& operator+=(const Vector3& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
        inline const Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
        inline Vector3& operator-=(const Vector3& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return *this; }
        inline const Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
        inline Vector3& operator*=(float s) { this->x *= s; this->y *= s; this->z *= s; return *this; }
        inline const Vector3 operator/(float s) const { return Vector3(x / s, y / s, z / s); }
        inline Vector3& operator/=(float s) { this->x /= s; this->y /= s; this->z /= s; return *this; }
        inline bool operator==(const Vector3& v) const
        {
            if ((x == v.x) && (y == v.y) && (z == v.z)) return true;
            else return false;
        }
        inline bool operator!=(const Vector3& v) const
        {
            return !(*this == v);
        }  

        void set(float x, float y, float z);
        void normalize();
        Vector3 normalized() const;
        float length() const;
        float squaredLength() const;

    public:
        float x;
        float y;
        float z;

    public:
        static float dot(const Vector3& v1, const Vector3& v2);
        static Vector3 cross(const Vector3& v1, const Vector3& v2);
        static float angle(const Vector3& from_v, const Vector3& to_v); // [0, pi]

    };

    typedef std::vector<Vector3> Vec3Array;
    typedef Vector3 Vec3f;
}

#endif // MATH_VECTOR3_H
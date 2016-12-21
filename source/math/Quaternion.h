#ifndef MATH_QUATERNION_H
#define MATH_QUATERNION_H

#include "math/Vector3.h"
#include "math/Matrix.h"

namespace te
{
    class Quaternion
    {
    public:
        Quaternion() { v = Vector3(0.0, 0.0, 0.0); w = 1.0f; }

        inline Quaternion& operator+=(const Quaternion& q) 
        {
            v += q.v;
            w += q.w;
            return *this;
        }
        friend inline Quaternion operator+(const Quaternion& q1, const Quaternion& q2) 
        {
            Quaternion ret = q1;
            return ret += q2;
        }
        inline Quaternion& operator-=(const Quaternion& q) 
        {
            v -= q.v;
            w -= q.w;
            return *this;
        }
        friend inline Quaternion operator-(const Quaternion& q1, const Quaternion& q2) 
        {
            Quaternion ret = q1;
            return ret -= q2;
        }
        inline Quaternion& operator*=(float f) 
        {
            v *= f;
            w *= f;
            return *this;
        }
        inline Quaternion operator*(float f) const 
        {
            Quaternion ret = *this;
            ret.v *= f;
            ret.w *= f;
            return ret;
        }
        inline Quaternion& operator/=(float f) 
        {
            v /= f;
            w /= f;
            return *this;
        }
        inline Quaternion operator/(float f) const 
        {
            Quaternion ret = *this;
            ret.v /= f;
            ret.w /= f;
            return ret;
        }
        Matrix convertToMatrix() const;
        Vector3 convertToEulerAngles() const;
        Quaternion(const Matrix& m);
        Quaternion(const Vector3& euler_angles);

    public:
        Vector3 v;
        float w;

    public:
        static float dot(const Quaternion& q1, const Quaternion& q2);
        static Quaternion normalize(const Quaternion& q);
        static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
    };
}



#endif // MATH_QUATERNION_H
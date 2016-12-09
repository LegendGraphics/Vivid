
#include "Core/math/Quaternion.h"

namespace te
{
    // https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
    Matrix Quaternion::convertToMatrix() const 
    {
        float xx = v.x * v.x, yy = v.y * v.y, zz = v.z * v.z;
        float xy = v.x * v.y, xz = v.x * v.z, yz = v.y * v.z;
        float wx = v.x * w,   wy = v.y * w,   wz = v.z * w;

        Matrix m;
        m.set(0, 1.f - 2.f * (yy + zz),       2.f * (xy + wz),       2.f * (xz - wy),     0,
              1,       2.f * (xy - wz), 1.f - 2.f * (xx + zz),       2.f * (yz + wx),     0,
              2,       2.f * (xz + wy),       2.f * (yz - wx), 1.f - 2.f * (xx + yy),     0,
              3,                   0.0,                   0.0,                   0.0,     1);

        return m;
    }

    // https://en.wikipedia.org/wiki/Rotation_matrix#Quaternion
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
    Quaternion::Quaternion(const Matrix& m) 
    {
        float trace = m(0, 0) + m(1, 1) + m(2, 2);
        if (trace > 0.f) 
        {
            // Compute w from matrix trace, then xyz
            // 4w^2 = m[0][0] + m[1][1] + m[2][2] + m[3][3] (but m[3][3] == 1)
            float s = sqrtf(trace + 1.0);
            w = s / 2.0f;
            s = 0.5f / s;
            v.x = (m(2, 1) - m(1, 2)) * s;
            v.y = (m(0, 2) - m(2, 0)) * s;
            v.z = (m(1, 0) - m(0, 1)) * s;
        }
        else 
        {
            // Compute largest of $x$, $y$, or $z$, then remaining components
            const int nxt[3] = {1, 2, 0};
            float q[3];
            int i = 0;
            if (m(1, 1) > m(0, 0)) i = 1;
            if (m(2, 2) > m(1, 1)) i = 2;
            int j = nxt[i];
            int k = nxt[j];
            float s = sqrtf((m(i, i) - (m(j, j) + m(k, k))) + 1.0);
            q[i] = s * 0.5f;
            if (s != 0.f) s = 0.5f / s;
            w = (m(k, j) - m(j, k)) * s;
            q[j] = (m(j, i) + m(i, j)) * s;
            q[k] = (m(k, i) + m(i, k)) * s;
            v.x = q[0];
            v.y = q[1];
            v.z = q[2];
        }
    }


    float Quaternion::dot(const Quaternion& q1, const Quaternion& q2)
    {
        return q1.w * q2.w + Vector3::dot(q1.v, q2.v);
    }

    Quaternion Quaternion::normalize(const Quaternion& q)
    {

    }

    Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t) 
    {
    }
}
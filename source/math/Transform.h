#ifndef BASE_TRANSFORM_H
#define BASE_TRANSFORM_H

#include "common/Component.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"

namespace te
{
    class Transform
    {
    public:
        Transform();
        Transform(const Mat4x4& m);
        Transform(const Transform& t);
        Transform& operator=(const Transform& t);

        inline const Vector4 operator*(const Vector4& v) const { return Vector4(_m * v); }
        inline const Transform operator*(const Transform& t) const { return Transform(_m * t._m); }

        void translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        static Transform trans(float x, float y);
        static Transform ortho(float left, float right, float bottom, float top, float znear = -1.0, float zfar = 1.0);
        static Transform lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
        static Transform lookAt(const Vector2& eye);
        static Transform identity();

    private:
        Mat4x4 _m;
    };
}


#endif // BASE_TRANSFORM_H
#ifndef BASE_TRANSFORM_H
#define BASE_TRANSFORM_H

#include "math/Matrix.h"
#include "math/Quaternion.h"

namespace te
{
    class Transform
    {
    public:
        Transform();
        Transform(const Matrix& m);
        Transform(const Transform& t);
        Transform& operator=(const Transform& t);

        inline const Vector4 operator*(const Vector4& v) const { return Vector4(_m * v); }
        inline const Transform operator*(const Transform& t) const { return Transform(_m * t._m); }

        void makeTranslate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void makeScale(float x = 1.0f, float y = 1.0f, float z = 1.0f);
        void makeRotate(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    public:
        static Transform translate(float x, float y, float z);
        static Transform scale(float x, float y, float z);
        static Transform rotate(float x, float y, float z);
        static Transform ortho(float left, float right, float bottom, float top, float znear = -1.0, float zfar = 1.0);
        static Transform lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
        static Transform identity();

    private:
        Matrix _m;
    };
}


#endif // BASE_TRANSFORM_H
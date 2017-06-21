#ifndef VIVID_MATH_TRANSFORM_H
#define VIVID_MATH_TRANSFORM_H

#include "vivid/math/Matrix.h"
#include "vivid/math/Quaternion.h"

namespace vivid
{
    class Transform
    {
    public:
        Transform();
        Transform(const Matrix& m);
        Transform(const Transform& t);
        Transform& operator=(const Transform& t);

        inline const Vector4 operator*(const Vector4& v) const { return Vector4(_m * v); }
        inline const Vector3 operator*(const Vector3& v) const { return Vector4to3(_m * Vector3to4(v)); }
        inline const Transform operator*(const Transform& t) const { return Transform(_m * t._m); }

        void makeTranslate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        void makeScale(float x = 1.0f, float y = 1.0f, float z = 1.0f);
        void makeRotate(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        const Matrix& rawMatrix() const { return _m; }

    public:
        static Transform translate(float x, float y, float z);
        static Transform scale(float x, float y, float z);
        static Transform rotate(float x, float y, float z);
        static Transform rotateX(float x);
        static Transform rotateY(float y);
        static Transform rotateZ(float z);
        static Transform perspective(float fov, float aspect, float znear, float zfar);
        static Transform ortho(float left, float right, float bottom, float top, float znear = -1.0, float zfar = 1.0);
        static Transform lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
        static Transform identity();

    private:
        Matrix _m;
    };
}


#endif // VIVID_MATH_TRANSFORM_H

#ifndef MATH_TRANSFORM_H
#define MATH_TRANSFORM_H

#include "math/mat4x4.h"
#include "math/vec4.h"
#include "math/vec3.h"
#include "math/vec2.h"

class Transform
{
public:
    Transform();
    Transform(const Mat4x4& m);
    Transform(const Transform& t);
    Transform& operator=(const Transform& t);

    inline const Vec4 operator*(const Vec4& v) const { return Vec4(_m * v); }
    inline const Transform operator*(const Transform& t) const { return Transform(_m * t._m); }

    void translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    inline const float* getMatAddress() const { return _m.getMatAddress(); }
    
    static Transform trans(float x, float y);
    static Transform ortho(float left, float right, float bottom, float top, float znear = -1.0, float zfar = 1.0);
    static Transform lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
    static Transform lookAt(const Vec2& eye);
    static Transform identity();

private:
    Mat4x4 _m;
};

#endif // MATH_TRANSFORM_H
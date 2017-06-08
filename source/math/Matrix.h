#ifndef MATH_MAT4X4_H
#define MATH_MAT4X4_H

#include "math/Vector4.h"
#include "base/Assert.h"

#define SET_ROW(row, v1, v2, v3, v4 )    \
                    _m[(row)][0] = (v1); \
                    _m[(row)][1] = (v2); \
                    _m[(row)][2] = (v3); \
                    _m[(row)][3] = (v4);


namespace te
{

    class Mat4x4
    {
    public:
        Mat4x4();
        Mat4x4(float m00, float m01, float m02, float m03,
               float m10, float m11, float m12, float m13,
               float m20, float m21, float m22, float m23,
               float m30, float m31, float m32, float m33);
        Mat4x4(const Mat4x4& m);
        Mat4x4& operator=(const Mat4x4& m);
        ~Mat4x4();

        friend inline const Vector4 operator*(const Mat4x4& m, const Vector4& v);
        friend inline const Mat4x4 operator*(const Mat4x4& m1, const Mat4x4& m2);
        friend inline Mat4x4& operator*(Mat4x4& m, float s);

        inline float& operator()(int i, int j)
        {
            mASSERT(i < 4, "row must be less than four");
            mASSERT(j < 4, "column must be less than four");
            return _m[i][j];
        }

        inline const float& operator()(int i, int j) const
        {
            mASSERT(i < 4, "row must be less than four");
            mASSERT(j < 4, "column must be less than four");
            return _m[i][j];
        }

        void set(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33);

        inline const float* ptr() const { return (float*)_m;}
        inline float* ptr() { return (float*)_m; }
        inline float determinant() const { return computeDeterminant(); }
        inline const Mat4x4 inverse() const { return computeInverse(); }
        inline const Mat4x4 transpose() const { return computeTranspose(); }

        void makeZero();
        void makeIdentity();
        void makeTranslate(float x, float y, float z);
        void makeScale(float x, float y, float z);
        void makeRotate(float x, float y, float z);
        void makeRotateX(float x);
        void makeRotateY(float y);
        void makeRotateZ(float z);
        void makeOrtho(float left, float right, float bottom, float top, float znear, float zfar);
        void makePerspective(float fov, float aspect, float znear, float zfar);
        void makeLookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

    private:
        float computeDeterminant() const;
        const Mat4x4 computeInverse() const;
        const Mat4x4 computeTranspose() const;

    protected:
        float _m[4][4];

    public:
        static Mat4x4 zero();
        static Mat4x4 identity();
        static Mat4x4 translate(float x, float y, float z);
        static Mat4x4 scale(float x, float y, float z);
        static Mat4x4 rotate(float x, float y, float z);
        static Mat4x4 rotateX(float x);
        static Mat4x4 rotateY(float y);
        static Mat4x4 rotateZ(float z);
        static Mat4x4 ortho(float left, float right, float bottom, float top, float znear, float zfar);
        static Mat4x4 perspective(float fov, float aspect, float znear, float zfar);
        static Mat4x4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

    };

    inline const Vector4 operator*(const Mat4x4& m, const Vector4& v)
    {
        float x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w;
        float y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w;
        float z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w;
        float w = m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z + m(3, 3) * v.w;
        return Vector4(x, y, z, w);
    }

    inline const Mat4x4 operator*(const Mat4x4& m1, const Mat4x4& m2)
    {
        Mat4x4 mat;
        mat.makeZero();
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                for (int k = 0; k < 4; ++ k)
                    mat(i, j) += m1(i, k) * m2(k, j);
        return mat;
    }

    inline Mat4x4& operator*(Mat4x4& m, float s)
    {
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                m(i, j) *= s;
        return m;
    }

    //Matrix computeLocalToWorld(NodePath* node_path)
    //{
    //    // accumulate transforms from the path...
    //    Matrix world_matrix;
    //    for (auto& node : node_path)
    //    {
    //        Transform* transform = node->getComponent<Transform>();
    //        Matrix mat = transform->getPositionMatrix();
    //        world_matrix = world_matrix * mat;
    //    }

    //    return world_matrix;
    //}

    typedef Mat4x4 Matrix;
}

#endif // MATH_MAT4X4_H
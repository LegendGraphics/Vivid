#ifndef MATH_MAT4X4_H
#define MATH_MAT4X4_H

#include "base/macros.h"
#include "Core/math/Vector4.h"

namespace te
{
    typedef Mat4x4 Matrix;

    class Mat4x4
    {
    public:
        Mat4x4();
        Mat4x4(const Mat4x4& m);
        Mat4x4& operator=(const Mat4x4& m);
        virtual ~Mat4x4();

        friend inline const Vector4 operator*(const Mat4x4& m, const Vector4& v);
        friend inline const Mat4x4 operator*(const Mat4x4& m1, const Mat4x4& m2);

        inline float& operator()(int i, int j)
        {
            TE_ASSERT(i < 4, "row must be less than four");
            TE_ASSERT(j < 4, "column must be less than four");
            return _m[i][j];
        }

        inline const float& operator()(int i, int j) const
        {
            TE_ASSERT(i < 4, "row must be less than four");
            TE_ASSERT(j < 4, "column must be less than four");
            return _m[i][j];
        }

        inline const float* getMatAddress() const { return &_m[0][0];}
        inline float determinant() const { return _determinant; }
        inline const Mat4x4& inverse() const { return _inverse; }
        inline const Mat4x4& transpose() const { return _transpose; }

    private:
        void computeDeterminant();
        void computeInverse();
        void computeTranspose();

    protected:
        float _m[4][4];
        float _determinant;
        Mat4x4 _inverse;
        Mat4x4 _transpose;

    public:
        static Mat4x4 zero();
        static Mat4x4 identity();
        static Mat4x4 ortho(float left, float right, float bottom, float top, float znear, float zfar);
        static Mat4x4 perspective(float fov, float aspect, float znear, float zfar);
        
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
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j)
                for (int k = 0; k < 4; ++ k)
                    mat(i, j) += m1(i, k) * m2(k, j);
        return mat;
    }

    Matrix computeLocalToWorld(NodePath* node_path)
    {
        // accumulate transforms from the path...
        Matrix world_matrix;
        for (auto& node : node_path)
        {
            Transform* transform = node->getComponent<Transform>();
            Matrix mat = transform->getPositionMatrix();
            world_matrix = world_matrix * mat;
        }

        return world_matrix;
    }

}

#endif // MATH_MAT4X4_H
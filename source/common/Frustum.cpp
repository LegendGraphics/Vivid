#include "common/Frustum.h"
#include "math/MathUtils.h"

namespace te
{
    void Frustum::buildViewFrustum(const Matrix& view_mat, const Matrix& proj_mat)
    {
        // This routine works with the OpenGL projection matrix
        // The view matrix is the inverse camera transformation matrix
        // Note: Frustum corners are not updated!

        Matrix m = proj_mat * view_mat;

        _planes[0] = Plane(-(m(0,3) + m(0,0)), -(m(1,3) + m(1,0)),
            -(m(2,3) + m(2,0)), -(m(3,3) + m(3,0)));    // Left
        _planes[1] = Plane(-(m(0,3) - m(0,0)), -(m(1,3) - m(1,0)),
            -(m(2,3) - m(2,0)), -(m(3,3) - m(3,0)));    // Right
        _planes[2] = Plane(-(m(0,3) + m(0,1)), -(m(1,3) + m(1,1)),
            -(m(2,3) + m(2,1)), -(m(3,3) + m(3,1)));    // Bottom
        _planes[3] = Plane(-(m(0,3) - m(0,1)), -(m(1,3) - m(1,1)),
            -(m(2,3) - m(2,1)), -(m(3,3) - m(3,1)));    // Top
        _planes[4] = Plane(-(m(0,3) + m(0,2)), -(m(1,3) + m(1,2)),
            -(m(2,3) + m(2,2)), -(m(3,3) + m(3,2)));    // Near
        _planes[5] = Plane(-(m(0,3) - m(0,2)), -(m(1,3) - m(1,2)),
            -(m(2,3) - m(2,2)), -(m(3,3) - m(3,2)));    // Far

        _origin = Vector4to3(view_mat.inverse() * Vector4(0, 0, 0, 1));

        // Calculate corners
        Matrix mm = m.inverse();
        Vector4 corner = mm * Vector4(-1, -1, -1, 1);
        _corners[0] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
        corner = mm * Vector4(1, -1, -1, 1);
        _corners[1] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
        corner = mm * Vector4(1, 1, -1, 1);
        _corners[2] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
        corner = mm * Vector4(-1, 1, -1, 1);
        _corners[3] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
        corner = mm * Vector4(-1, -1, 1, 1);
        _corners[4] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
        corner = mm * Vector4(1, -1, 1, 1);
        _corners[5] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
        corner = mm * Vector4(1, 1, 1, 1);
        _corners[6] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
        corner = mm * Vector4(-1, 1, 1, 1);
        _corners[7] = Vector3(corner.x / corner.w, corner.y / corner.w, corner.z / corner.w);
    }

    bool Frustum::cullSphere(Vector3 pos, float rad) const
    {
        for (int i = 0; i < 6; ++i)
        {
            if (_planes[i].distToPlane(pos) > rad) return true;
        }

        return false;
    }

    bool Frustum::cullBox(const BoundingBox& bb) const
    {
        for (int i = 0; i < 6; ++i)
        {
            const Vector3& n = _planes[i].getNormal();

            Vector3 positive = bb.getMin();
            if (n.x <= 0) positive.x = bb.getMax().x;
            if (n.y <= 0) positive.y = bb.getMax().y;
            if (n.z <= 0) positive.z = bb.getMax().z;

            if (_planes[i].distToPlane(positive) > 0) return true;
        }

        return false;
    }

    bool Frustum::cullFrustum(const Frustum& frust) const
    {
        for (int i = 0; i < 6; ++i)
        {
            bool all_out = true;

            for (int j = 0; j < 8; ++j)
            {
                if (_planes[i].distToPlane(frust._corners[j]) < 0)
                {
                    all_out = false;
                    break;
                }
            }

            if (all_out) return true;
        }

        return false;
    }

    void Frustum::calcAABB(Vector3& min, Vector3& max) const
    {
        min.x = te::MAX_FLOAT; min.y = te::MAX_FLOAT; min.z = te::MAX_FLOAT;
        max.x = -te::MAX_FLOAT; max.y = -te::MAX_FLOAT; max.z = -te::MAX_FLOAT;

        for (int i = 0; i < 8; ++i)
        {
            if (_corners[i].x < min.x) min.x = _corners[i].x;
            if (_corners[i].y < min.y) min.y = _corners[i].y;
            if (_corners[i].z < min.z) min.z = _corners[i].z;
            if (_corners[i].x > max.x) max.x = _corners[i].x;
            if (_corners[i].y > max.y) max.y = _corners[i].y;
            if (_corners[i].z > max.z) max.z = _corners[i].z;
        }

    }
}
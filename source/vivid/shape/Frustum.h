#ifndef COMMON_FRUSTUM_H
#define COMMON_FRUSTUM_H

#include "vivid/shape/Plane.h"
#include "vivid/shape/BoundingBox.h"
#include "vivid/math/Matrix.h"

namespace vivid
{
    class Node;

    class Frustum
    {
    public:
        Frustum() = default;
        virtual ~Frustum() = default;

        const Vector3& getOrigin() const { return _origin; }
        const Vector3& getCorner(int index) const { return _corners[index]; }

        void buildFrustum(const Matrix& view_mat, const Matrix& proj_mat);

        bool cullSphere(Vector3 pos, float rad) const;
        bool cullBox(const BoundingBox& bb) const;
        bool cullFrustum(const Frustum& frust) const;

        void calcAABB(Vector3& min, Vector3& max) const;

    protected:
        Plane _planes[6];
        Vector3 _origin;
        Vector3 _corners[8];
    };
}



#endif // COMMON_FRUSTUM_H

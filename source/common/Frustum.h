#ifndef COMMON_FRUSTUM_H
#define COMMON_FRUSTUM_H

#include "common/Object.h"
#include "common/Plane.h"
#include "common/BoundingBox.h"
#include "math/Matrix.h"

namespace te
{
    class Node;

    class Frustum : public Object
    {
    public:
        Frustum() = default;
        virtual ~Frustum() = default;

        const Vector3& getOrigin() const { return _origin; }
        const Vector3& getCorner(int index) const { return _corners[index]; }

        void buildViewFrustum(const Matrix& view_mat, const Matrix& proj_mat);

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

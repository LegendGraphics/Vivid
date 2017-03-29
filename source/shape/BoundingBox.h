#ifndef COMMON_BOUNDING_BOX_H
#define COMMON_BOUNDING_BOX_H

#include "math/Vector3.h"

namespace te
{
    class BoundingBox
    {
    public:
        BoundingBox(const Vector3& center, const Vector3& size);

        bool contains(const Vector3& point);
        //bool intersectRay(const Ray& ray);
        bool intersect(const BoundingBox& bb);

        inline Vector3 getMax() const { return _max; }
        inline Vector3 getMin() const { return _min; }
        inline Vector3 getCenter() const { return _center; }

        bool makeUnion(const BoundingBox& bb);

    protected:
        Vector3 _center;
        Vector3 _max;
        Vector3 _min;
    };
}
#endif // COMMON_BOUNDING_BOX_H
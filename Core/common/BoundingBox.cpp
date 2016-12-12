#include "Core/common/BoundingBox.h"

namespace te
{
    BoundingBox::BoundingBox(const Vector3& center, const Vector3& size)
    {
        _center = center;
        _min = center - size / 2.0;
        _max = center + size / 2.0;
    }

    bool BoundingBox::contains(const Vector3& point)
    {

    }

    bool BoundingBox::intersectRay(const Ray& ray)
    {

    }

    bool BoundingBox::intersect(const BoundingBox& bb)
    {

    }
}
#include "common/BoundingSphere.h"

namespace te
{
    BoundingSphere::BoundingSphere(const Vector3& center, float radius)
        :_center(center),
        _radius(radius)
    {
    }

    bool BoundingSphere::contains(const Vector3& point)
    {
        if ((point - _center).length() <= _radius)
            return true;
        else return false;
    }

    /*bool BoundingSphere::intersectRay(const Ray& ray)
    {

    }*/

    bool BoundingSphere::intersect(const BoundingSphere& bs)
    {
        Vector3 center_dist = bs._center - _center;
        float radius_dist = bs._radius + _radius;

        if (center_dist.length() <= radius_dist)
            return true;
        else
            return false;
    }
}
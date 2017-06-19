#include "vivid/shape/BoundingBox.h"

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
        if ((point.x >= _min.x && point.x <= _max.x) &&
            (point.y >= _min.y && point.y <= _max.y) &&
            (point.z >= _min.z && point.z <= _max.z))
            return true;
        else return false;
    }

    /*bool BoundingBox::intersectRay(const Ray& ray)
    {

    }*/

    bool BoundingBox::intersect(const BoundingBox& bb)
    {
        Vector3 half_diag1 = (_max - _min) / 2.0;
        Vector3 half_diag2 = (bb._max - bb._min) / 2.0;
        Vector3 center_dist = bb._center - _center;

        if (fabs(center_dist.x) <= (half_diag1.x + half_diag2.x) &&
            fabs(center_dist.y) <= (half_diag1.y + half_diag2.y) &&
            fabs(center_dist.z) <= (half_diag1.z + half_diag2.z))
            return true;
        else
            return false;
    }

    bool BoundingBox::makeUnion(const BoundingBox& bb)
    {
        bool changed = false;

        // Ignore zero-size boxes
        if (_min == _max)
        {
            changed = true;
            _min = bb._min;
            _max = bb._max;
        }
        else if (bb._min != bb._max)
        {
            if (bb._min.x < _min.x) { changed = true; _min.x = bb._min.x; }
            if (bb._min.y < _min.y) { changed = true; _min.y = bb._min.y; }
            if (bb._min.z < _min.z) { changed = true; _min.z = bb._min.z; }

            if (bb._max.x > _max.x) { changed = true; _max.x = bb._max.x; }
            if (bb._max.y > _max.y) { changed = true; _max.y = bb._max.y; }
            if (bb._max.z > _max.z) { changed = true; _max.z = bb._max.z; }
        }

        return changed;
    }
}
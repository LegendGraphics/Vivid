#include "common/Ray.h"
#include "math/Vector3.h"

namespace te
{
    Ray::Ray(const Vector3& origin, const Vector3& direction)
        :_origin(origin),
        _direction(direction)
    {

    }

    Vector3 Ray::getPoint(float distance) const
    {
        float x = _origin.x + distance * _direction.x;
        float y = _origin.y + distance * _direction.y;
        float z = _origin.z + distance * _direction.z;

        return Vector3(x, y, z);
    }
}
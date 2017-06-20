#ifndef COMMON_RAY_H
#define COMMON_RAY_H

#include "vivid/math/Vector3.h"

namespace vivid
{
    class Ray
    {
    public:
        Ray(const Vector3& origin, const Vector3& direction);

        Vector3 getPoint(float distance) const;
    protected:
        Vector3 _direction;
        Vector3 _origin;
    };
}

#endif // COMMON_RAY_H
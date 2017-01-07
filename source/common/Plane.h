#ifndef COMMON_PLANE_H
#define COMMON_PLANE_H

#include "common/Object.h"
#include "math/Vector3.h"

namespace te
{
    class Plane : public Object
    {
    public:
        Plane();
        Plane(const float a, const float b, const float c, const float d);
        Plane(const Vector3& normal, float distance);
        Plane(const Plane& plane, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        Plane& operator=(const Plane& plane);
        virtual ~Plane();

        OBJECT_META_FUNCTION(Plane);

        void setNormal(const Vector3& normal);
        inline Vector3 getNormal() const { return _normal; }

        void setDistance(float distance);
        inline float getDistance() const { return _distance; }

        float distToPlane(const Vector3& position) const;

    protected:
        Vector3 _normal;
        float _distance;
    };
}



#endif // COMMON_PLANE_H

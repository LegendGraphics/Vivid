#include "vivid/shape/Plane.h"

namespace te
{
    Plane::Plane() {}

    Plane::Plane(const float a, const float b, const float c, const float d)
    {
        _normal = Vector3(a, b, c);
        _distance = d;
    }

    Plane::Plane(const Vector3& normal, float distance)
        :_normal(normal),
        _distance(distance)
    {}

    Plane& Plane::operator=(const Plane& plane)
    {
        _normal = plane._normal;
        _distance = plane._distance;
        return *this;
    }

    Plane::~Plane() {}

    void Plane::setNormal(const Vector3& normal)
    {
        _normal = normal;
    }

    void Plane::setDistance(float distance)
    {
        _distance = distance;
    }

    // signed distance
    float Plane::distToPlane(const Vector3& position) const
    {
        return (Vector3::dot(_normal, position) + _distance) / _normal.length();
    }

}
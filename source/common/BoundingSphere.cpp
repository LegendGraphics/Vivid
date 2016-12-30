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
		if ((point - _center).length() < _radius)
			return true;
		else return false;
	}

	/*bool BoundingSphere::intersectRay(const Ray& ray)
	{

	}*/

	bool BoundingSphere::intersect(const BoundingSphere& bb)
	{
		Vector3 centerDist = bb.getCenter() - _center;
		float radiusDist = bb.getRadius() + _radius;

		if (Vector3::dot(centerDist, centerDist) <= radiusDist * radiusDist)
			return true;
		else
			return false;
	}
}
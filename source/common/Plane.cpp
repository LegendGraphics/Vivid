#include "common/Plane.h"

namespace te
{
	Plane::Plane(){}

	Plane::Plane(const Vector3& normal, float distance)
		:_normal(normal),
		_distance(distance)
	{}

	Plane::Plane(const Plane& plane, const CopyOperator& copyop)
	{
	}

	Plane::~Plane(){}

	void Plane::setNormal(const Vector3& normal)
	{
		_normal = normal;
	}

	void Plane::setDistance(float distance)
	{
		_distance = distance;
	}

	bool Plane::sphereInPlane(const Vector3& position, float radius) const
	{
		return true;
	}
}
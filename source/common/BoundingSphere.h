#ifndef COMMON_BOUNDING_SPHERE_H
#define COMMON_BOUNDING_SPHERE_H

#include "math/Vector3.h"
#include "common/Object.h"

namespace te
{
	class BoundingSphere : public Object
	{
	public:
		BoundingSphere(const Vector3& center, float radius);

		bool contains(const Vector3& point);
		//bool intersectRay(const Ray& ray);
		bool intersect(const BoundingSphere& bb);

	protected:
		Vector3 _center;
		float _radius;
	};
}
#endif // COMMON_BOUNDING_SPHERE_H
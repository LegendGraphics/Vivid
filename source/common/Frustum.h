#ifndef COMMON_FRUSTUM_H
#define COMMON_FRUSTUM_H

#include "common/Object.h"
#include "common/Plane.h"

namespace te
{
	class Node;

	class Frustum : public Object
	{
	public:
		Frustum();
		virtual ~Frustum();

		bool isInsideFrustum(Node* node);

	protected:
		Plane _planes[6];
	};
}



#endif // COMMON_FRUSTUM_H

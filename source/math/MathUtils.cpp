#include "math/MathUtils.h"

namespace te
{
    const float MathUtils::MAX_FLOAT = 3.402823466e+38F;
    const float MathUtils::PI = 3.141592F;

    float MathUtils::degreeToRadians(float degree)
    {
        return degree * PI / 180;
    }
}

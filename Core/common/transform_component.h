#ifndef COMMON_TRANSFORM_H
#define COMMON_TRANSFORM_H

#include "common/component.h"

class TransformComponent: public Component
{
public:
    TransformComponent();
    virtual ~TransformComponent();

    virtual void update(float delta_time);

    void setX(float x);
    inline float getX() const { return _x; }

    void setY(float y);
    inline float getY() const { return _y; }

    void setZ(float z);
    inline float getZ() const { return _z; }

    void setPosition(float x, float y, float z);

protected:
    float _x, _y, _z;
    float _sx, _sy, _sz;
    float _rx, _ry, _rz;
};
#endif // COMMON_TRANSFORM_H
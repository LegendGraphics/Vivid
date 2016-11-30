
#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include <vector>
#include <cmath>

class Vec2
{
public:
    Vec2();
    Vec2(const Vec2& v);
    Vec2(float x, float y);
    ~Vec2();

    Vec2& operator=(const Vec2& v);

    inline const Vec2 operator+(const Vec2& v) const { return Vec2(_x + v._x, _y + v._y); }
    inline Vec2& operator+=(const Vec2& v) { this->_x += v._x; this->_y += v._y; return *this; }
    inline const Vec2 operator-(const Vec2& v) const { return Vec2(_x - v._x, _y - v._y); }
    inline Vec2& operator-=(const Vec2& v) { this->_x -= v._x; this->_y -= v._y; return *this; }
    inline const Vec2 operator*(float s) const { return Vec2(_x * s, _y * s); }
    inline Vec2& operator*=(float s) { this->_x *= s; this->_y *= s; return *this; }
    inline const Vec2 operator/(float s) const { return Vec2(_x / s, _y / s); }
    inline Vec2& operator/=(float s) { this->_x /= s; this->_y /= s; return *this; }
    
    inline bool operator==(const Vec2& v) 
    {
        if ((fabs(_x - v._x) < 1e-3) && (fabs(_y - v._y) < 1e-3))
            return true;
        else return false;
    }
    
    inline float& x() { return _x; }
    inline float& y() { return _y; }

    inline const float& x() const { return _x; }
    inline const float& y() const { return _y; }

    const Vec2 normalize();
    float dot(const Vec2& v);
    float length();

private:
    float _x;
    float _y;
};

typedef std::vector<Vec2> Vec2Array;

#endif // MATH_VEC2_H
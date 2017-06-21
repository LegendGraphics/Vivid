#ifndef VIVID_COMMON_LIGHT_H
#define VIVID_COMMON_LIGHT_H

#include "vivid/common/Component.h"
#include "vivid/math/Vector4.h"

namespace vivid
{
    struct Color
    {
        float r;
        float g;
        float b;
        float a;

        Color() {};
        Color(const Color& v) { *this = v; }
        Color(const Vector4& vec) { *this = vec; }
        Color(float r, float g, float b, float a = 1.0f) { this->r = r; this->g = g; this->b = b; this->a = a; }
        Color& operator=(const Color& v)
        {
            this->r = v.r; this->g = v.g; this->b = v.b; this->a = v.a;
            *this;
        }
        Color& operator=(const Vector4& vec)
        {
            this->r = vec.x; this->g = vec.y; this->b = vec.z; this->a = vec.w;
            *this;
        }
        ~Color() {};

        inline const Color operator+(const Color& v) const { return Color(r + v.r, g + v.g, b + v.b, a + v.a); }
        inline Color& operator+=(const Color& v) { this->r += v.r; this->g += v.g; this->b += v.b; this->a += v.a; return *this; }
        inline const Color operator-(const Color& v) const { return Color(r - v.r, g - v.g, b - v.b, a - v.a); }
        inline Color& operator-=(const Color& v) { this->r -= v.r; this->g -= v.g; this->b -= v.b; this->a -= v.a; return *this; }
        inline const Color operator*(float s) const { return Color(r * s, g * s, b * s, a * s); }
        inline Color& operator*=(float s) { this->r *= s; this->g *= s; this->b *= s; this->a *= s; return *this; }
        inline const Color operator/(float s) const { return Color(r / s, g / s, b / s, a / s); }
        inline Color& operator/=(float s) { this->r /= s; this->g /= s; this->b /= s; this->a /= s; return *this; }


        static Color black;
        static Color white;
        static Color red;
        static Color green;
        static Color blue;
    };

    Color Color::black = Color(0, 0, 0, 1);
    Color Color::white = Color(1, 1, 1, 1);
    Color Color::red = Color(1, 0, 0, 1);
    Color Color::green = Color(0, 1, 0, 1);
    Color Color::blue = Color(0, 0, 1, 1);


    enum class LightType
    {
        SPOT,
        DIRECTVIVID_IONAL,
        POINT,
        AREA
    };


    class Light : public ComData
    {
    protected:
        int         _area_size;
        Color       _color;
        float       _range;
        float       _intensity;
        LightType   _type;

    };
}


#endif // VIVID_COMMON_LIGHT_H


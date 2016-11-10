#ifndef BASE_DATA_TYPES_H
#define BASE_DATA_TYPES_H

struct Size
{
    Size()
    {
        width = 0.0f;
        height = 0.0f;
    }
    Size(float w, float h)
    {
        width = w;
        height = h;
    }

    bool hasZero()
    {
        if (width == 0.0f || height == 0.0f)
            return true;
        else
            return false;
    }

    float width;
    float height;
};

#endif // BASE_DATA_TYPES_H
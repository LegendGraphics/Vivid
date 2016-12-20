#ifndef COMMON_IMAGE_H
#define COMMON_IMAGE_H

#include <string>

#include "base/ref.h"

class Image: public Ref
{
public:
    Image();
    Image(const std::string& filename);
    ~Image();

    bool load(const std::string& filename);
    inline int getWidth() { return _w; }
    inline int getHeight() { return _h; }
    inline unsigned char* getRawData() { return _img; }

private:
    unsigned char* _img;
    int _w;
    int _h;
};

#endif // COMMON_IMAGE_H
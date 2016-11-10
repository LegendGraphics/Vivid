
#ifndef RENDERER_TEXTURE_H
#define RENDERER_TEXTURE_H

#include "base/ref.h"
#include "base/refptr.hpp"

class Image;

class GLTexture: public Ref 
{
public:
    GLTexture();
    GLTexture(Image* image);
    virtual ~GLTexture();

    bool load(Image* image);

    void bind();
    void clear();

    inline int getPixelWidth() { return _pixel_width; }
    inline int getPixelHeight() { return _pixel_height; }

private:
    GLuint _tex;
    int _pixel_width;
    int _pixel_height;
    RefPtr<Image> _image;
};
#endif // RENDERER_TEXTURE_H
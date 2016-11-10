
#include <gl/glew.h>

#include "renderer/gl_texture.h"
#include "common/image.h"
#include "base/macros.h"


GLTexture::GLTexture()
:_tex(0),
_pixel_width(0),
_pixel_height(0)
{
}

GLTexture::GLTexture(Image* image)
:_tex(0),
_pixel_width(0),
_pixel_height(0)
{
    load(image);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &_tex);
}

bool GLTexture::load(Image* image)
{
    if (image == NULL)
    {
        TE_ERROR("Can't create GLTexture. Image is nil");
        return false;
    }
    
    _image = image;
    _pixel_width = image->getWidth();
    _pixel_height = image->getHeight();
    
    return true;
}

void GLTexture::bind()
{
    unsigned char* raw_data = _image->getRawData();

    glGenTextures(1, &_tex);
    glBindTexture(GL_TEXTURE_2D, _tex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pixel_width, _pixel_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raw_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void GLTexture::clear()
{
    glDeleteTextures(1, &_tex);
}
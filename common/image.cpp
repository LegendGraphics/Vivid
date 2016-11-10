
#include <SOIL.h>
#include "common/image.h"


Image::Image()
: _img(NULL)
{

}

Image::Image(const std::string& filename)
{
    load(filename);
}

Image::~Image()
{
    if (_img != NULL)
        SOIL_free_image_data(_img);
}

bool Image::load(const std::string& filename)
{
    _img = SOIL_load_image
        (
        filename.c_str(),
        &_w,
        &_h,
        0,
        SOIL_LOAD_RGBA
        );

    if (_img == 0) return false;
    else return true;
}
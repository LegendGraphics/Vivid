
#include "ui/ui_button.h"
#include "common/image.h"

UIButton::UIButton(){}

UIButton::~UIButton(){}

bool UIButton::setImage(const std::string& image_file)
{
    if (_image->load(image_file))
    {
        setContentSize((float)_image->getWidth(), (float)_image->getHeight());
        _has_image = true;
        return true;
    }
    else return false;
}
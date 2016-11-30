#ifndef UI_UI_BUTTON_H
#define UI_UI_BUTTON_H

#include "ui/ui_widget.h"

class UIButton: public UIWidget
{
public:
    UIButton();
    virtual ~UIButton();
    
    bool setImage(const std::string& image_file);
};

#endif // UI_UI_BUTTON_H
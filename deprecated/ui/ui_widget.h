//#ifndef UI_UI_WIDGET_H
//#define UI_UI_WIDGET_H
//
//#include <string>
//
//#include "base/refptr.hpp"
//#include "common/node.h"
//
//class Image;
//
//class UIWidget: public Node
//{
//public:
//    UIWidget();
//    virtual ~UIWidget();
//
//    virtual void accept(NodeVisitor* node_visitor);
//    virtual void draw(Renderer* renderer);
//    
//    // (x, y) in opengl coordinate
//    bool isInWidget(float x, float y);
//    
//    void setWidgetName(const std::string& name);
//    inline const std::string& getWidgetName() { return _name; }
//
//    UIWidget* seekWidgetByName(const std::string& name);
//
//
//protected:
//    void updateInLocalReference();
//    void updateInWorldReference();
//
//protected:
//    static std::string VERTEX_SHADER; 
//    static std::string FRAGMENT_SHADER;
//
//protected:
//    std::string _name;
//    
//    bool _has_image;
//    RefPtr<Image> _image;
//    // four vertices ordered by clockwise from x axis to y axis
//    Vec2 _v0;
//    Vec2 _v1;
//    Vec2 _v2;
//    Vec2 _v3;
//};
//
//#endif // UI_UI_WIDGET_H
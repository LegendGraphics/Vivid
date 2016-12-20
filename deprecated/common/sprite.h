#ifndef COMMON_SPRITE_H
#define COMMON_SPRITE_H

#include <string>
#include <map>

#include "base/refptr.hpp"
#include "common/node.h"

class Image;
class Animation;

class Sprite: public Node
{
public:
    Sprite();
    virtual ~Sprite();

    virtual void accept(NodeVisitor* node_visitor);
    virtual void draw(Renderer* renderer);

    bool loadTexture(const std::string& image_file);
    bool loadTexture(Image* image);

    virtual void update(float delta_time);
    
    void registerAnimation(const std::string& anim_name, Animation* animation);
    void play(const std::string& anim_name);
    void stop(const std::string& anim_name);

    void setUI(bool ui);

protected:
    void updateInLocalReference();
    void updateInWorldReference();

protected:
    static std::string VERTEX_SHADER; 
    static std::string FRAGMENT_SHADER;

protected:
    RefPtr<Image> _image;
    // four vertices ordered by clockwise from x axis to y axis
    Vec2 _v0;
    Vec2 _v1;
    Vec2 _v2;
    Vec2 _v3;

    std::map<std::string, RefPtr<Animation>> _animations;

    bool _ui;

    static int SPRITE_ID; 
    int _id;
};

#endif // COMMON_SPRITE_H
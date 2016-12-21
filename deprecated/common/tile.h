#ifndef COMMON_TILE_H
#define COMMON_TILE_H

#include "base/refptr.hpp"
#include "common/image.h"
#include "common/node.h"

class Tile: public Node
{
public:
    Tile();
    Tile(Image* image);
    virtual ~Tile();

    virtual void draw(Renderer* renderer);

protected:
    void updateInLocalReference();
    void updateInWorldReference();

protected:
    static std::string VERTEX_SHADER; 
    static std::string FRAGMENT_SHADER;

public:
    static const int TILE_WIDTH = 400;
    static const int TILE_HEIGHT = 320;

protected:
    RefPtr<Image> _image;
    // four vertices ordered by clockwise from x axis to y axis
    Vec2 _v0;
    Vec2 _v1;
    Vec2 _v2;
    Vec2 _v3;
};

#endif // COMMON_TILE_H
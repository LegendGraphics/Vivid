#ifndef COMMON_SCENE_H
#define COMMON_SCENE_H

#include <vector>
#include <string>

#include "base/refptr.hpp"
#include "common/tile.h"
#include "common/node.h"
#include "common/camera.h"

class Scene: public Node
{
public:
    static const int BLOCK_SIZE = 20;

public:
    typedef std::vector<RefPtr<Tile>> SceneArray;
    typedef std::vector<SceneArray> SceneGrid;
    typedef std::vector<std::vector<bool>> SceneBlock;
    
    struct VisibleBoundary
    {
        int left;
        int right;
        int bottom;
        int top;
    };

    
public:
    Scene();
    Scene(const std::string& scene_folder, int row, int col,
        const std::string& block_file, int brow, int bcol);
    virtual ~Scene();

    virtual void accept(NodeVisitor* node_visitor);
    virtual void draw(Renderer* renderer);
    
    void setActiveCamera(Camera* camera);
    Camera* getActiveCamera() { return _active_camera.get(); }

    bool isBlocked(float x, float y);

private:
    void initTileLayout();
    void updateVisibleBoundary();
    
private:
    RefPtr<Camera> _active_camera;

    SceneGrid _scene_grid;
    int _grid_row;
    int _grid_col;

    SceneBlock _scene_block;

    VisibleBoundary _vis_bound;
};
#endif // COMMON_SCENE_H
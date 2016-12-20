
#include "common/scene.h"
#include "base/file_loader.h"
#include "common/node_visitor.h"

Scene::Scene()
:_active_camera(new Camera),
_grid_row(0),
_grid_col(0)
{
}

Scene::Scene(const std::string& scene_folder, int row, int col,
             const std::string& block_file, int brow, int bcol)
:_active_camera(new Camera)
{
    _scene_grid = loadScene(scene_folder, row, col);
    _grid_row = row;
    _grid_col = col;

    initTileLayout();

    _scene_block = loadSceneBlock(block_file, brow, bcol);

    TE_ASSERT((row * Tile::TILE_HEIGHT == brow * Scene::BLOCK_SIZE) && 
        (col * Tile::TILE_WIDTH == bcol * Scene::BLOCK_SIZE), "Scene and block sizes are not matched!");
}

Scene::~Scene(){}

void Scene::initTileLayout()
{
    for (int i = 0; i < _grid_row; ++ i)
    {
        float height_pos = float(i * Tile::TILE_HEIGHT);
        for (int j = 0; j < _grid_col; ++ j)
        {
            float width_pos = float(j * Tile::TILE_WIDTH);
            _scene_grid[i][j]->setPosition(width_pos, height_pos);
        }
    }

    setContentSize(_grid_col * Tile::TILE_WIDTH, _grid_row * Tile::TILE_HEIGHT);
}


void Scene::accept(NodeVisitor* node_visitor)
{
    node_visitor->apply(this);
}

void Scene::draw(Renderer* renderer)
{
    updateVisibleBoundary();

    for (int j = _vis_bound.left; j <= _vis_bound.right; ++ j)
        for (int i = _vis_bound.bottom; i <= _vis_bound.top; ++ i)
            _scene_grid[i][j]->draw(renderer);
}

void Scene::updateVisibleBoundary()
{
    const Camera::ViewBoundary& view_bound = _active_camera->getViewBoundary();
    
    _vis_bound.left = TE_MAX(int(view_bound.left / Tile::TILE_WIDTH), 0);
    _vis_bound.right = TE_MIN(int(view_bound.right / Tile::TILE_WIDTH), _grid_col-1);
    _vis_bound.bottom = TE_MAX(int(view_bound.bottom / Tile::TILE_HEIGHT), 0);
    _vis_bound.top = TE_MIN(int(view_bound.top / Tile::TILE_HEIGHT), _grid_row-1);
}

void Scene::setActiveCamera(Camera* camera)
{
    _active_camera = camera;
}

bool Scene::isBlocked(float x, float y)
{
    int r_idx = (int)(y/BLOCK_SIZE);
    int c_idx = (int)(x/BLOCK_SIZE);
    return _scene_block[r_idx][c_idx];
}
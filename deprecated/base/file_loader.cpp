#include <fstream>

#include <algorithm>
#include <boost/filesystem.hpp>

#include "base/file_loader.h"

using namespace boost::filesystem;

Animation::AnimationFrames loadAnimation(const std::string& animation_folder)
{
    Animation::AnimationFrames anim_frames;
    path p(animation_folder);
    for (directory_iterator& i = directory_iterator(p); 
        i != directory_iterator(); i++)
    {
        if (!is_directory(i->path())) //we eliminate directories
        {
            std::string file_path = animation_folder + "/" + i->path().filename().string();
            anim_frames.push_back(new Image(file_path));
        }
        else
            continue;
    }
    return anim_frames;
}

Scene::SceneGrid loadScene(const std::string& scene_folder, int row, int col)
{
    Scene::SceneGrid scene_grid(row, Scene::SceneArray(col));
    path p(scene_folder);
    
    int count = 0;
    for (directory_iterator& i = directory_iterator(p); 
        i != directory_iterator(); i++)
    {
        if (!is_directory(i->path())) //we eliminate directories
        {
            std::string file_path = scene_folder + "/" + i->path().filename().string();
            scene_grid[count/col][count%col] = new Tile(new Image(file_path));
            count ++;
        }
        else
            continue;
    }

    TE_ASSERT(count == row*col, "Scene files are broken!");

    std::reverse(scene_grid.begin(), scene_grid.end());
    
    return scene_grid;
}

Scene::SceneBlock loadSceneBlock(const std::string& block_file, int row, int col)
{
    Scene::SceneBlock scene_block(row, std::vector<bool>(col, true));

    ifstream in(block_file);

    if (!in) 
    {
        TE_ERROR("Could not open the block file!");
        return scene_block;
    }
    
    int count = 0;
    char ch;
    while (in >> ch) {
        int r = count / col;
        int c = count % col;
        scene_block[r][c] = bool(ch - '0');
        count ++;
    }

    in.close();

    std::reverse(scene_block.begin(), scene_block.end());
    
    return scene_block;
}
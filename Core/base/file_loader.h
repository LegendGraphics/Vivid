#ifndef BASE_FILE_LOADER_H
#define BASE_FILE_LOADER_H

#include "base/refptr.hpp"
#include "common/image.h"
#include "common/animation.h"
#include "common/scene.h"

Animation::AnimationFrames loadAnimation(const std::string& animation_folder);

Scene::SceneGrid loadScene(const std::string& scene_folder, int row, int col);

Scene::SceneBlock loadSceneBlock(const std::string& block_file, int row, int col);

#endif // BASE_FILE_LOADER_H
#ifndef RENDERER_SHADER_LOADER_H
#define RENDERER_SHADER_LOADER_H

#include <fstream>
#include <gl/glew.h>

unsigned long getFileLength(std::ifstream& file);
int loadShader(const char* filename, GLchar*& ShaderSource);
bool unloadShader(GLchar* ShaderSource);

#endif // RENDERER_SHADER_LOADER_H
#version 430
uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 worldMat;
in vec3 vertPos;
in vec3 normal;
in vec2 texCoords0;
out vec3 g_normal;
out vec2 g_texPos;
void main() {
    gl_Position = projMat * viewMat * worldMat * vec4( vertPos, 1.0 );
    g_normal = normal;
    g_texPos = texCoords0;
};
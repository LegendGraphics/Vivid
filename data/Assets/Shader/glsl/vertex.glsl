#version 430
uniform mat4 viewProjMat;
uniform mat4 worldMat;
in vec3 vertPos;
in vec3 normal;
out vec3 g_normal;
void main() {
    gl_Position = viewProjMat * worldMat * vec4( vertPos, 1.0 );
    g_normal = normal;
};
#version 430
uniform vec4 color;
in vec3 g_normal;
out vec4 fragColor;
void main() {
    fragColor = clamp(max(dot(normalize(g_normal),normalize(vec3(0.3,0.5,1))),0.0), 0, 1) * color;
};
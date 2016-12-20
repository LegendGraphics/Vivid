#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 vertexUV;
uniform mat4 MVP;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){

    // Output position of the vertex
    vec4 v = vec4(position, 0.0, 1.0);
    gl_Position =  MVP * v;

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}

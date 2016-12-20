

int main(int argc, char** argv)
{ 

	return 0;
}





//#version 330 core
//
//// Input vertex data, different for all executions of this shader.
//layout(location = 0) in vec2 position;
//layout(location = 1) in vec2 vertexUV;
//
//// Output data ; will be interpolated for each fragment.
//out vec2 UV;
//
//void main(){
//
//    // Output position of the vertex
//    gl_Position =  vec4(position, 0.0, 1.0);
//
//    // UV of the vertex. No special space for this one.
//    UV = vertexUV;
//}



//#version 330 core
//
//// Interpolated values from the vertex shaders
//in vec2 UV;
//
//// Ouput data
//out vec3 color;
//
//// Values that stay constant for the whole mesh.
//uniform sampler2D myTextureSampler;
//
//void main(){
//
//    // Output color = color of the texture at the specified UV
//    color = texture( myTextureSampler, UV ).rgb;
//}
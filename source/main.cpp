#include <iostream>
#include <memory>
#include "io/MeshLoader.h"
#include "common/Mesh.h"
#include "common/MeshFilter.h"
#include "common/Node.h"
#include "common/Transform.h"

using namespace te;

int main(int argc, char** argv)
{ 
	MeshLoader mesh_loader;
	Mesh* m = mesh_loader.readObjFile("cube.obj");

	Node* root = new Node;
	root->addComponent<MeshFilter>(m);
	root->addComponent<Transform>(Vector3(0.0f, 0.0f, 0.0f));


	Node* n1 = new Node;
	n1->addComponent<MeshFilter>(m);
	n1->addComponent<Transform>(0.0f, 0.0f, 0.0f);

	Node* n2 = new Node;
	n2->addComponent<MeshFilter>(m);
	n2->addComponent<Transform>(0.0f, 0.0f, 0.0f);

	Node* m1 = new Node;
	m1->addComponent<MeshFilter>(m);
	m1->addComponent<Transform>(0.0f, 0.0f, 0.0f);

	Node* m2 = new Node;
	m2->addComponent<MeshFilter>(m);
	m2->addComponent<Transform>(0.0f, 0.0f, 0.0f);

	root->addChild(n1);
	root->addChild(n2);
	n1->addChild(m1);
	n2->addChild(m2);

	delete root;

	getchar();
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
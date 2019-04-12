#include "Model.h"

Model::Model(std::string filename) {
	AssimpAdaptor modelLoader = AssimpAdaptor();
	modelLoader.openFile(filename);
	modelLoader.getMeshes(&meshes);
}

Model::~Model() {

}

void Model::display() {
	for(int i = 0; i < meshes.size(); i++)
	{
		meshes[i].display();
	}
}

void Mesh::addVertex(glm::vec3 &vertex, glm::vec3 &normal, glm::vec2 &uv)
{
	vertices.push_back(vertex);
	normals.push_back(normal);
	uvCoords.push_back(uv);
}

void Mesh::setMaterial(GLuint texture, float shininess)
{

}

void Mesh::display()
{
	//glScaled(5.0,5.0,5.0);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_TRIANGLES);
	//std::cout << "displaying model: " << vertices.size() <<  std::endl;
	
	for(int i = 0; i < vertices.size(); i++)
	{
		
		glVertex3d(vertices[i].x,vertices[i].y,vertices[i].z);
		glNormal3d(normals[i].x,normals[i].y,normals[i].z);
		glTexCoord2d(uvCoords[i].x,uvCoords[i].y);
	}
	glEnd();
}
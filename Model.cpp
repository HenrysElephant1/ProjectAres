#include "Model.h"

Model::Model(std::string filename) {
	AssimpAdaptor modelLoader = AssimpAdaptor();
	modelLoader.openFile(filename);
	modelLoader.getMeshes(&meshes);
}

Model::~Model() {

}

void Model::display() {
	glUseProgram(GLManager::lightingShader);
	for(int i = 0; i < meshes.size(); i++)
	{
		meshes[i].display();
	}
	glUseProgram(0);
}

void Mesh::addVertex(glm::vec3 &vertex, glm::vec3 &normal, glm::vec2 &uv)
{
	vertices.push_back(vertex);
	normals.push_back(normal);
	uvCoords.push_back(uv);
}

void Mesh::setMaterial(GLuint texture, float shininess_in)
{
	colorTexture = texture;
	shininess = shininess_in;
}

void Mesh::display()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	//std::cout << "texture: " << colorTexture << std::endl; 
	glBegin(GL_TRIANGLES);	
	for(int i = 0; i < vertices.size(); i++)
	{
		glNormal3d(normals[i].x,normals[i].y,normals[i].z);
		glTexCoord2d(uvCoords[i].x,uvCoords[i].y);
		glVertex3d(vertices[i].x,vertices[i].y,vertices[i].z);
		
		//std::cout << "UV: " << uvCoords[i].x << ", " << uvCoords[i].y << std::endl;
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
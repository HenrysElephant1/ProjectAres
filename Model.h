#ifndef MODEL_H
#define MODEL_H

#include "AssimpAdaptor.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
//#include <OpenGL/gl3.h>


class Mesh {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoords;

	GLuint colorTexture;
	float shininess;

public:
	void addVertex(glm::vec3 &vertex, glm::vec3 &normal, glm::vec2 &uv);
	void setMaterial(GLuint texture, float shininess);
	Mesh(){}
	~Mesh(){}
	void display();
};


class Model {
private:
	std::vector<Mesh> meshes;
	

public:
	Model(std::string filename);
	~Model();

	void display();
};

#endif
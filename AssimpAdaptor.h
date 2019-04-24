#ifndef ASSIMPADAPTOR_H
#define ASSIMPADAPTOR_H


#include "GLManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
//#include <OpenGL/gl.h>
#include "Model.h"

class Mesh; // forward declaration

struct MeshData {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoords;
	int materialIndex;
};

struct MaterialData {
	GLuint colorTexture;
	float shininess;
};

class AssimpAdaptor {
private:
	std::vector<MeshData> meshes;
	std::vector<MaterialData> materials;

	void processScene(const aiScene* scene, std::string & filename);
	void processNodes(aiNode * node, const aiScene* scene);
	void createMesh(const aiMesh* m, std::string &name, const aiScene * scene);
	void processMaterials(const aiScene* scene, std::string & filename);
	aiMatrix4x4 getTransformation(const aiScene * scene, std::string &name);
	aiMatrix4x4 getTransformationHelper(aiNode * node);


public:
	AssimpAdaptor();
	bool openFile(std::string& filename);
	void getMeshes(std::vector<Mesh> * returnList);

};

#endif
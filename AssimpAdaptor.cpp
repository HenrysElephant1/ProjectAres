#include "AssimpAdaptor.h"

AssimpAdaptor::AssimpAdaptor(){
}

bool AssimpAdaptor::openFile(std::string& filename)
{
	Assimp::Importer Importer;
	const aiScene* scene = Importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);// | aiProcess_FlipUVs);

	if(scene)
	{
		processScene(scene, filename);
		//delete scene;
		return true;
	}
	else {
		std::cout << "Error loading file: " << filename << "\n" << Importer.GetErrorString() << std::endl;
		return false;
	}

}

void AssimpAdaptor::processScene(const aiScene* scene, std::string & filename)
{
	std::cout << "Reading Scene" << std::endl;

	processNodes(scene->mRootNode, scene);
	std::cout << "Finished Reading scene" << std::endl;
	processMaterials(scene, filename);
}

void AssimpAdaptor::processNodes(aiNode * node, const aiScene* scene)
{
	//std::cout << "Node name: " << node->mName.C_Str() << ", Number of Meshes: " << node->mNumMeshes << std::endl;
	std::string nodeName = std::string(node->mName.C_Str());
	for(int i = 0; i < node->mNumMeshes; i++)
	{	
		createMesh(scene->mMeshes[node->mMeshes[i]], nodeName, scene);
	}
	for(int i = 0; i < node->mNumChildren; i++)
	{
		processNodes(node->mChildren[i], scene);
	}
}

void AssimpAdaptor::createMesh(const aiMesh* m, std::string &name, const aiScene * scene)
{
	int index = meshes.size();
	meshes.push_back(MeshData());
	meshes[index].materialIndex = m->mMaterialIndex + materials.size();

	aiMatrix4x4 transform = getTransformation(scene, name);
	aiMatrix4x4 normalMatrix = transform;
	normalMatrix.Inverse().Transpose();


	for(unsigned int i = 0; i < m->mNumFaces; i++)
	{
		const aiFace &face = m->mFaces[i];
		for(int j = 0; j < 3; j++)
		{
			int vertIndex = face.mIndices[j];
			aiVector3D position = transform * (m->mVertices[vertIndex]);
			aiVector3D uv = (m->mTextureCoords[0][vertIndex]);
			aiVector3D normal = normalMatrix * (m->mNormals[vertIndex]);

			meshes[index].vertices.push_back(glm::vec3(position.x, position.y, position.z));
			meshes[index].normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
			meshes[index].uvCoords.push_back(glm::vec2(uv.x, uv.y));
			//std::cout << "UV: " << uv.x << ", " << uv.y << std::endl;
		}


	}

}

void AssimpAdaptor::processMaterials(const aiScene* scene, std::string & filename)
{
	std::string::size_type pathEnd = filename.find_last_of("/");
	std::string directory;

	if(pathEnd == std::string::npos)
		directory = ".";
	else if(pathEnd == 0)
		directory = "/";
	else directory = filename.substr(0,pathEnd);
	int materialIndexOffset = materials.size();

	std::cout << "Number of Materials: " << scene->mNumMaterials << std::endl;
	std::cout << "has Textures: " << scene->mNumTextures << std::endl;
	for(int i = 0; i < scene->mNumMaterials; i++)
	{
		int materialIndex = materialIndexOffset + i;
		materials.push_back(MaterialData());
		const aiMaterial* currentMaterial = scene->mMaterials[i];
		aiString matName;
		currentMaterial->Get(AI_MATKEY_NAME, matName);
		std::cout << "Name: " << matName.C_Str() << std::endl;
		//get all color properties of the material

		//read ambient color property
		// aiColor3D ambientColor;
		// if(currentMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == AI_SUCCESS)
		// {
		// 	materials[materialIndex].ambient = glm::vec3(ambientColor.r,ambientColor.g,ambientColor.b);
		// }
		// //read diffuse color property
		// aiColor3D diffuseColor;
		// if(currentMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS)
		// {
		// 	materials[materialIndex].diffuse = glm::vec3(diffuseColor.r,diffuseColor.g,diffuseColor.b);
		// }
		// //read specular color property
		// aiColor3D specularColor;
		// if(currentMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS)
		// {
		// 	materials[materialIndex].specular = glm::vec3(specularColor.r,specularColor.g,specularColor.b);
		// }
		// //read transparent color property
		// aiColor3D transparentColor;
		// if(currentMaterial->Get(AI_MATKEY_COLOR_TRANSPARENT, transparentColor) == AI_SUCCESS)
		// {
		// 	materials[materialIndex].transparentColor = glm::vec3(transparentColor.r,transparentColor.g,transparentColor.b);
		// }


		//read floating point properties for the material
		// float opacity;
		// if(currentMaterial->Get(AI_MATKEY_OPACITY, opacity) == AI_SUCCESS)
		// {
		// 	materials[materialIndex].opacity = opacity;
		// }

		float shiny;
		if(currentMaterial->Get(AI_MATKEY_SHININESS, shiny) == AI_SUCCESS)
		{
			materials[materialIndex].shininess = shiny;
			//std::cout << "Shininess " << shiny << std::endl;
		}

		// load diffuse texture for the material
		if(currentMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			//std::cout << "Diffuse Texture Exists" << std::endl;
			aiString texture_path;
			if(currentMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string file_path = directory + "/" + texture_path.data;
				std::cout << "Color Texture: " << file_path << std::endl;
				materials[materialIndex].colorTexture = GLManager::loadTexture(file_path);
			}
		}

	}
}


aiMatrix4x4 AssimpAdaptor::getTransformation(const aiScene * scene, std::string &name)
{
	aiNode * root = scene->mRootNode;
	return getTransformationHelper(root->FindNode(name.c_str()));
}

aiMatrix4x4 AssimpAdaptor::getTransformationHelper(aiNode * node)
{
	if(node->mParent == NULL)
		return node->mTransformation;
	return getTransformationHelper(node->mParent) * node->mTransformation;
}




void AssimpAdaptor::getMeshes(std::vector<Mesh> * returnList)
{
	for(int i = 0; i < meshes.size(); i++)
	{
		int index = returnList->size();
		returnList->push_back(Mesh());
		for(int j = 0; j < meshes[i].vertices.size(); j++)
		{
			returnList->at(index).addVertex(meshes[i].vertices[j], meshes[i].normals[j], meshes[i].uvCoords[j]);
			returnList->at(index).setMaterial(materials[meshes[i].materialIndex].colorTexture,materials[meshes[i].materialIndex].shininess);
		}
	}
}



#include "GLManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLManager::GLManager(){}

int GLManager::screenWidth = 1;
int GLManager::screenHeight = 1;
int GLManager::fov = 55;
float GLManager::asp = 1;
bool GLManager::QUIT = false;
GLuint GLManager::lightingShader = 0;
std::map<std::string, GLuint> GLManager::textures;

void GLManager::setFOV( int newFOV ) {
	fov = newFOV;
	project();
}

void GLManager::reshape( int width, int height ) {
	screenWidth = width;
	screenHeight = height;
	asp = width / (float)height;
	project();
	glViewport(0,0,width,height);
}

void GLManager::project() {
	// Tell OpenGL we want to manipulate the projection matrix
    glMatrixMode(GL_PROJECTION);
    // Undo previous transformations
    glLoadIdentity();
    // Perspective transformation
    gluPerspective(fov,asp,NEAR_PLANE,FAR_PLANE);
    // Switch to manipulating the model matrix
    glMatrixMode(GL_MODELVIEW);
}

int GLManager::getScreenWidth() {
	return screenWidth;
}

int GLManager::getScreenHeight() {
	return screenHeight;
}

void GLManager::beginRender() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_COLOR_MATERIAL);
}

void GLManager::endRender() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void GLManager::switchTo2D() {
	glDisable(GL_LIGHTING);
	// Save projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-asp,asp,-1,1,-1,1); // Create orthogonal view with coordinates -asp <= x <= asp, -1 <= y <= 1
	// Save modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void GLManager::switchTo3D() {
	// Return to previously saved projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	// Return to previously saved modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

// std::string & filename
GLuint GLManager::loadTexture( std::string & filename ) {
	if(textures.count(filename) > 0)
		return textures.at(filename);
	// if(textures[filename] != textures.end())
	// 	return textures.at(filename);
	stbi_set_flip_vertically_on_load(true);

	int width;
	int height;
	int numChannels;
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &numChannels, STBI_rgb_alpha); //filename.c_str()
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if(image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(image);
		textures.insert(std::pair<std::string, GLuint>(filename, tex));
		return tex;
	}
	std::cout << "Failed to load texture: " << filename << std::endl;
	return 0;
}

Loc GLManager::getMenuCoords( int x, int y ) {
	Loc retStruct;
	retStruct.x = x/(float)screenHeight * 2 - asp;
	retStruct.y = y/(float)screenHeight * -2 + 1;
	return retStruct;
}


void GLManager::debug( std::string loc ) { 
	GLenum err;
	int i = 0;
	while((err = glGetError()) != GL_NO_ERROR)
		std::cout << "Error #" << ++i << " at " << loc << ": " << err << std::endl;
}


GLuint GLManager::createProgram(const char* vertexShader, const char* fragShader)
{
	//create program
	GLuint program = glCreateProgram();

	//read shaders
	GLuint vertex = loadShaderFromFile(GL_VERTEX_SHADER, vertexShader);
	GLuint fragment = loadShaderFromFile(GL_FRAGMENT_SHADER, fragShader);

	//attach shaders
	glAttachShader(program,vertex);
	glAttachShader(program,fragment);

	//link program
	glLinkProgram(program);

	// print program log in case of errors

	//add program to vector
	// Shader* s = new Shader(program);
	// int index = shaders.size();
	// shaders.push_back(s);

	return program;
}

GLuint GLManager::loadShaderFromFile(GLenum type, const char* filename)
{
	GLuint shader = glCreateShader(type);
	FILE* file = std::fopen(filename, "r");
	if(file == NULL)
	{
		std::cout << "Could not open file: " << filename << std::endl;
		return 0;
	}
	std::fseek(file,0,SEEK_END);
	int n = std::ftell(file);
	std::fseek(file,0,SEEK_SET);
	char * buffer = (char*)malloc(n+1);
	if(buffer == NULL)
	{
		std::cout << "Unable to allocate number of bytes needed for " << filename << std::endl;
		return 0; 
	}
	int read = std::fread(buffer, n, 1, file);
	if(read != 1)
	{
		std::cout << "Problem reading file: " << filename << std::endl;
	}
	buffer[n] = 0;
	std::fclose(file);

	glShaderSource(shader,1,(const char**)&buffer, NULL);

	free(buffer);
	glCompileShader(shader);

	int logLength = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	if(logLength > 1)
	{
		char * log = (char *)malloc(logLength+1);
		if(log == NULL) 
			{std::cout << "Unable to allocate memory to print log" << std::endl;}
		else {
			glGetShaderInfoLog(shader,logLength,NULL,log);
			log[logLength] = 0;
			std::cout << "Log for "<< filename <<":" << log << std::endl;
		}
	}
	glGetShaderiv(shader, GL_COMPILE_STATUS, &logLength);
	if(logLength == 0) {std::cout << "Error Compiling " << filename << std::endl;}

	return shader;
}

float GLManager::getMapViewHeight( float width, float height ) {
	float mapAsp = width/height;
	float useFOV = fov/2.0;
	float useFar = width/2.0;
	if( mapAsp < asp-.5 ) {
		useFOV = Atan(Tan(useFOV) / asp);
		// std::cout << "UseFOV: " << useFOV << std::endl;
		useFar = height/2.0;
	}
	return useFar / Tan(useFOV);
}

glm::mat4 GLManager::getInvPerspMat() {
	return glm::inverse( glm::perspective((float)(fov), asp, (float)NEAR_PLANE, (float)FAR_PLANE) );
}

glm::vec4 GLManager::getNDC( int mx, int my ) {
	glm::vec4 retLoc = glm::vec4(2.0*mx/(float)screenWidth - 1.0, 2.0*my/(float)screenHeight - 1.0, -1, 1);
	return retLoc;
}

void GLManager::doLighting( float posx, float posy, float posz ) {
	// Light color properties
	float Ambient[] = {0.2,0.2,0.2,1.0};
	float Diffuse[] = {0.8,0.8,0.8,1.0};
	float Specular[] = {1.0,1.0,1.0,1.0};
	float Position[] = {posx, posy, posz};
	glLightfv( GL_LIGHT0, GL_AMBIENT, Ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, Diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, Specular );
	glLightfv( GL_LIGHT0, GL_POSITION, Position );
}

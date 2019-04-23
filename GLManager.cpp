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
std::map<const char*, GLuint> GLManager::textures;

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
    gluPerspective(fov,asp,1,500);
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
	glUseProgram(lightingShader);
}

void GLManager::endRender() {
	glDisable(GL_DEPTH_TEST);
	glUseProgram(0);
}

void GLManager::switchTo2D() {
	glUseProgram(0);
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
	glUseProgram(lightingShader);
}

// std::string & filename
GLuint GLManager::loadTexture( const char* filename ) {
	if(textures.count(filename) > 0)
		return textures.at(filename);
	stbi_set_flip_vertically_on_load(true);

	int width;
	int height;
	int numChannels;
	unsigned char* image = stbi_load(filename, &width, &height, &numChannels, STBI_rgb_alpha); //filename.c_str()
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
		textures.insert(std::pair<const char*, GLuint>(filename, tex));
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

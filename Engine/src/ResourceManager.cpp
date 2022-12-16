#include "../include/ResourceManager.h"

namespace Engine {

	std::map<std::string, Shader>		ResourceManager::shaders;
	std::map<std::string, Texture2D>	ResourceManager::textures;

	Shader ResourceManager::loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile) {

		std::string vertexCode;
		std::string fragmentCode;

		try {
			//Open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			//Read file's buffer content into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			//Close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			//Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::exception e) {
			std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
		}

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		//Create shader object from source code
		Shader shader;

		shader.vFileName = vShaderFile;
		shader.fFileName = fShaderFile;

		shader.compile(vShaderCode, fShaderCode);

		return shader;
	}

	Texture2D ResourceManager::loadTextureFromFile(const GLchar* file, GLboolean alpha) {

		Texture2D texture;

		if (alpha) {
			texture.internal_format = GL_RGBA;
			texture.image_format = GL_RGBA;
		}

		//Load image
		int width, height;
		unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.image_format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

		texture.generate(width, height, image);

		SOIL_free_image_data(image);

		return texture;

	}

	Shader ResourceManager::loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, std::string name) {
		shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
		return shaders[name];
	}

	Shader ResourceManager::getShader(std::string name) {
		return shaders[name];
	}

	Texture2D ResourceManager::loadTexture(const GLchar* file, GLboolean alpha, std::string name) {
		textures[name] = loadTextureFromFile(file, alpha);
		return textures[name];
	}

	Texture2D ResourceManager::getTexture(std::string name) {
		return textures[name];
	}

	void ResourceManager::clear() {
		//Properly delete all shaders
		for (auto iter : shaders)
			glDeleteProgram(iter.second.id);
		//Properly delete all textures
		for (auto iter : textures)
			glDeleteProgram(iter.second.id);
	}

}
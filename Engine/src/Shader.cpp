#include "../include/Shader.h"

namespace Engine {

	Shader& Shader::use() {
		glUseProgram(id);
		return *this;
	}

	GLuint Shader::getProgramID() const {
		return id;
	}

	void Shader::compile(const GLchar* vertexSource, const GLchar* fragmentSource) {

		GLuint sVertex, sFragment;

		//Vertex Shader
		sVertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(sVertex, 1, &vertexSource, NULL);
		glCompileShader(sVertex);
		checkCompileErrors(sVertex, "VERTEX");

		//Fragment Shader
		sFragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(sFragment, 1, &fragmentSource, NULL);
		glCompileShader(sFragment);
		checkCompileErrors(sFragment, "FRAGMENT");

		//Shader Program
		id = glCreateProgram();
		glAttachShader(id, sVertex);
		glAttachShader(id, sFragment);
		glLinkProgram(id);
		checkCompileErrors(id, "PROGRAM");

		glDeleteShader(sVertex);
		glDeleteShader(sFragment);

	}

	void Shader::setFloat(const GLchar* name, GLfloat value, GLboolean useShader) {
		if (useShader) this->use();
		glUniform1f(glGetUniformLocation(this->id, name), value);
	}

	void Shader::setInteger(const GLchar* name, GLint value, GLboolean useShader) {
		if (useShader) this->use();
		glUniform1i(glGetUniformLocation(this->id, name), value);
	}

	void Shader::setVector3f(const GLchar *name, const glm::vec3& value, GLboolean useShader) {
		if (useShader) this->use();
		glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
	}

	void Shader::setMatrix4(const GLchar *name, const glm::mat4& matrix, GLboolean useShader) {
		if (useShader) this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::checkCompileErrors(GLuint object, std::string type) {

		GLint success;
		GLchar infoLog[1024];

		if (type != "PROGRAM") {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
					<< infoLog << "\n -- --------------------------------------------------- -- "
					<< std::endl;
			}
			else {
				if (type == "VERTEX")
					std::cout << getShaderName(vFileName) << " foi compilado com sucesso." << std::endl;
				else if (type == "FRAGMENT")
					std::cout << getShaderName(fFileName) << " foi compilado com sucesso." << std::endl;
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object, 1024, NULL, infoLog);
				std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
					<< infoLog << "\n -- --------------------------------------------------- -- "
					<< std::endl;
			}
			else
				std::cout << std::endl << "Programa foi linkado com sucesso." << std::endl << std::endl;
		}

	}

	std::string Shader::getShaderName(const GLchar* filePath) {
		std::string filePathString(filePath), outString;
		std::stringstream ss;
		for (int i = static_cast<int>(filePathString.size()) - 1; !(filePathString[i] == '/' || filePathString[i] == '\\'); i--)
			ss << filePathString[i];
		outString = ss.str();
		ss.str("");
		for (std::string::reverse_iterator rit = outString.rbegin(); rit != outString.rend(); ++rit)
			ss << *rit;
		return ss.str();
	}

}
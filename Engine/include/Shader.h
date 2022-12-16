#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <sstream>
#include <string>
#include <iostream>

namespace Engine {

	class Shader {

	private:
		void checkCompileErrors(GLuint object, std::string type);
		std::string getShaderName(const GLchar* filePath);

	public:
		GLuint id;

		const GLchar* vFileName;
		const GLchar* fFileName;

		Shader() {}

		Shader& use();
		GLuint getProgramID() const;

		void compile(const GLchar* vertexSource, const GLchar* fragmentSource);

		//Funções uteis
		void setFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
		void setInteger(const GLchar* name, GLint value, GLboolean useShader = false);
		void setVector3f(const GLchar *name, const glm::vec3& value, GLboolean useShader = false);
		void setMatrix4(const GLchar *name, const glm::mat4& matrix, GLboolean useShader = false);

	};

}
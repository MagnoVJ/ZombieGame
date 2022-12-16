#pragma once

#include "Shader.h"
#include "Texture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

namespace Engine {

	class SpriteRenderer {

	private:
		Shader shader;
		void initRenderData();

	public:
		GLuint quadVAO;
		GLuint VBO;

		SpriteRenderer(Shader& shader);
		~SpriteRenderer();

		void drawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat rotate = 0.0);
	
	};

}
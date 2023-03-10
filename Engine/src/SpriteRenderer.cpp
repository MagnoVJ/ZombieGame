#include "../include/SpriteRenderer.h"

namespace Engine {

	SpriteRenderer::SpriteRenderer(Shader& shader) {

		this->shader = shader;

		initRenderData();

	}

	SpriteRenderer::~SpriteRenderer() {
		glDeleteVertexArrays(1, &quadVAO);
	}

	void SpriteRenderer::initRenderData() {

		GLfloat vertices[] = {
			// Pos       // Tex
			0.0f, 1.0f,  0.0f, 1.0f,
			1.0f, 0.0f,  1.0f, 0.0f,
			0.0f, 0.0f,  0.0f, 0.0f,

			0.0f, 1.0f,  0.0f, 1.0f,
			1.0f, 1.0f,  1.0f, 1.0f,
			1.0f, 0.0f,  1.0f, 0.0f
		};

		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(quadVAO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void SpriteRenderer::drawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, glm::vec3 color, GLfloat rotate) {

		glm::mat4 model;

		model = glm::translate(glm::mat4(), glm::vec3(position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		model = glm::scale(model, glm::vec3(size, 1.0f));

		shader.use();

		shader.setMatrix4("model", model);
		shader.setVector3f("spriteColor", color);

		glActiveTexture(GL_TEXTURE0);

		texture.bind();

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

	}

}
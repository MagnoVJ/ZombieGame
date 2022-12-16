#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {

	class Camera {

	private:
		glm::mat4 projectionMatrix;
		void applyChanges();

	public:
		glm::mat4 cameraMatrix;
		int widthScreen, heightScreen;

		float camPosX, camPosY;
		float camScale;
		GLuint programShaderID;

		Camera(int widthScreen, int heightScreen, float camPosX, float camPosY);
		~Camera();

		void init(GLuint programShaderID);

		void moveCamera(float amountX, float amountY);
		void scaleCamera(float scale);

		glm::vec2 screenToWorldPoint(glm::vec2 pointScreenSpace);
		glm::vec2 worldToScreenPoint(glm::vec2 pointWorldSpace);
		glm::vec2 screenToTextMapPoint(glm::vec2 pointScreenSpace, glm::vec2 tileDimensions);

	};

}
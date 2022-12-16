#include "../include/Camera.h"

namespace Engine {

	Camera::Camera(int widthScreen, int heightScreen, float camPosX, float camPosY) : widthScreen(widthScreen), heightScreen(heightScreen), camPosX(camPosX), camPosY(camPosY), camScale(1.0f) {

		projectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(widthScreen), static_cast<GLfloat>(heightScreen), 0.0f, -1.0f, 1.0f);

		cameraMatrix = projectionMatrix;

	}

	Camera::~Camera() {}

	void Camera::init(GLuint programShaderID) {

		this->programShaderID = programShaderID;

		glUseProgram(this->programShaderID);
		glUniformMatrix4fv(glGetUniformLocation(this->programShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	}

	void Camera::moveCamera(float amountX, float amountY) {

		camPosX += amountX;
		camPosY += amountY;

		applyChanges();

	}

	void Camera::scaleCamera(float scaleAmount) {

		float camScaleAnt = camScale;

		camScale += scaleAmount;

		if (camScale <= 0) {
			camScale = camScaleAnt;
			return;
		}

		applyChanges();

	}

	void Camera::applyChanges() {

		glm::vec3 translate(-camPosX, -camPosY, 0.0f);
		cameraMatrix = glm::translate(projectionMatrix, translate);

		glm::vec3 scale(camScale, camScale, 0.0f);
		cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;

		glUseProgram(programShaderID);
		glUniformMatrix4fv(glGetUniformLocation(programShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	}

	glm::vec2 Camera::screenToWorldPoint(glm::vec2 pointScreenSpace) {

		glm::vec2 pointWorldSpace;

		pointWorldSpace = pointScreenSpace - glm::vec2(widthScreen / 2, heightScreen / 2);
		pointWorldSpace /= camScale;
		pointWorldSpace += glm::vec2(camPosX, camPosY);
		pointWorldSpace.y *= -1;

		return pointWorldSpace;

	}

	glm::vec2 Camera::worldToScreenPoint(glm::vec2 pointWorldSpace) {

		pointWorldSpace.y *= -1;
		pointWorldSpace -= glm::vec2(camPosX, camPosY);
		pointWorldSpace *= camScale;
		pointWorldSpace = pointWorldSpace + glm::vec2(widthScreen / 2, heightScreen / 2);

		return pointWorldSpace;

	}

	glm::vec2 Camera::screenToTextMapPoint(glm::vec2 pointScreenSpace, glm::vec2 tileDimensions) {

		float xRet = 0, yRet = 0;

		float decValue = tileDimensions.x - 1;

		while(pointScreenSpace.x - decValue > 0) {
			xRet++;
			decValue += tileDimensions.x;
		}

		decValue = tileDimensions.y - 1;

		while(pointScreenSpace.y - decValue > 0) {
			yRet++;
			decValue += tileDimensions.y;
		}

		return glm::vec2(xRet, yRet);

	}

}
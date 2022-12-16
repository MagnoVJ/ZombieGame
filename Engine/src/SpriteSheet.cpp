#include "../include/SpriteSheet.h"

namespace Engine {

	SpriteSheet::SpriteSheet(GLfloat movementCooloff, GLfloat cyclesMov, GLfloat cyclesAnim, double textCoordUpdateDelay) : movementCooloff(movementCooloff), cyclesMov(cyclesMov), cyclesAnim(cyclesAnim), textCoordUpdateDelay(textCoordUpdateDelay) { }

	SpriteSheet::~SpriteSheet( ) { }

	void SpriteSheet::modifyTexCoord( ) {

		glBindVertexArray(renderer->quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);

		glBufferSubData(GL_ARRAY_BUFFER,  2 * sizeof(GLfloat), 2 * sizeof(GLfloat), topLeftCoord);
		glBufferSubData(GL_ARRAY_BUFFER,  6 * sizeof(GLfloat), 2 * sizeof(GLfloat), bottomRightCoord);
		glBufferSubData(GL_ARRAY_BUFFER, 10 * sizeof(GLfloat), 2 * sizeof(GLfloat), bottomLeftCoord);

		glBufferSubData(GL_ARRAY_BUFFER, 14 * sizeof(GLfloat), 2 * sizeof(GLfloat), topLeftCoord);
		glBufferSubData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), 2 * sizeof(GLfloat), topRightCoord);
		glBufferSubData(GL_ARRAY_BUFFER, 22 * sizeof(GLfloat), 2 * sizeof(GLfloat), bottomRightCoord);

		glBindVertexArray(0);

	}

	void SpriteSheet::setCoords(float tlx, float tly, float brx, float bry, float blx, float bly, float trx, float tRy) {

		topLeftCoord[0] = tlx;
		topLeftCoord[1] = tly;

		bottomRightCoord[0] = brx;
		bottomRightCoord[1] = bry;

		bottomLeftCoord[0] = blx;
		bottomLeftCoord[1] = bly;

		topRightCoord[0] = trx;
		topRightCoord[1] = tRy;

	}

	void SpriteSheet::setXCoords(float tlx, float brx, float blx, float trx) {

		topLeftCoord[0] = tlx;
		bottomRightCoord[0] = brx;
		bottomLeftCoord[0] = blx;
		topRightCoord[0] = trx;

	}

	void SpriteSheet::setYCoords(float tly, float bry, float bly, float tRy) {

		topLeftCoord[1] = tly;
		bottomRightCoord[1] = bry;
		bottomLeftCoord[1] = bly;
		topRightCoord[1] = tRy;

	}

}
#pragma once

#include <GL/glew.h>
#include "SpriteRenderer.h"

namespace Engine {

	class SpriteSheet {

	public:
		Texture2D texture;
		SpriteRenderer* renderer;

		SpriteSheet(GLfloat movementCooloff, GLfloat cyclesMov, GLfloat cyclesAnim, double textCoordUpdateDelay);
		~SpriteSheet( );

		void modifyTexCoord( );

		void setCoords(float tlx, float tly, float brx, float bry, float blx, float bly, float trx, float tRy);

		void setXCoords(float tlx, float brx, float blx, float trx);
		void setYCoords(float tly, float bry, float bly, float tRy);

		GLfloat topLeftCoord[2];
		GLfloat bottomRightCoord[2];
		GLfloat bottomLeftCoord[2];
		GLfloat topRightCoord[2];

		double textCoordUpdateDelay;

		GLfloat cyclesMov; //Quanto menor o valor mais rápido o personagem moverá
		GLfloat cyclesAnim; //Quanto maior o valor mais rápido a sprite será animada

		GLfloat amountToMove;
		GLfloat movementCooloff;

	};

}
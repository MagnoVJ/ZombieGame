#pragma once

#include "DirMovement.h"
#include "Camera.h"
#include "TextMap.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <queue>
#include <memory>

namespace Engine {

	struct Passo {

		glm::vec2 mapTextPos;
		DirMovement dirMovement;

		Passo(glm::vec2 mapTextPos, DirMovement dirMovement) : mapTextPos(mapTextPos), dirMovement(dirMovement) { }

	};

	struct AStarNode {

		GLfloat F;
		GLfloat G;
		GLfloat H;
		glm::vec2 positionTS;
		AStarNode* parent;

		void calculateH(glm::vec2 destiny) {
			H = (abs(destiny.x - positionTS.x) + abs(destiny.y - positionTS.y)) * 10;
		}

		void calculateG( ) {
			G = parent->G + 10;
		}

		void calculateF( ) {
			F = G + H;
		}

	};

	class GameObject {

	protected:
		glm::vec2 positionScreen;

		void worldToScreenPoint(glm::vec3 camProps, glm::vec2 screenProps);

		std::queue<Passo> aStarPathfinding(glm::vec2 originTS, glm::vec2 destinyTS, TextMap* textMap);

	public:
		glm::vec2 position;
		glm::vec2 size;
		GLfloat rotation;

		GameObject(glm::vec2 position, glm::vec2 size, GLfloat rotation = 0.0f);
		~GameObject( );

	};

}
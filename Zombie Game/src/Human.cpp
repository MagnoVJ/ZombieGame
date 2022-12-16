#include "../include/Human.h"

Human::Human(Engine::Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotation)
	: GameObject(position, size, rotation), behavior(Behavior::WAITING), waitingCooloff(2), spriteSheet(0, 0.4, 10, 0) {

	spriteSheet.setCoords(    0.0f, 1 / 4.0f, 
						  1 / 4.0f,     0.0f,
						      0.0f,     0.0f,
						  1 / 4.0f, 1 / 4.0f);

	spriteSheet.texture = texture;
	spriteSheet.renderer = new Engine::SpriteRenderer(Engine::ResourceManager::getShader("Basic_shader"));

	spriteSheet.modifyTexCoord( );

}

Human::~Human( ) { }

void Human::positTextCoordsAcord( ) {

	if(dirMovement == DirMovement::DOWN) {

		spriteSheet.setCoords(    0.0f, 1 / 4.0f, 
						      1 / 4.0f,     0.0f,
						          0.0f,     0.0f,
						      1 / 4.0f, 1 / 4.0f);

	}
	else if(dirMovement == DirMovement::UP) {

		spriteSheet.setCoords(    0.0f, 2 / 4.0f,
						      1 / 4.0f, 1 / 4.0f,
						          0.0f, 1 / 4.0f,
						      1 / 4.0f, 2 / 4.0f);

	}
	else if(dirMovement == DirMovement::LEFT) {

		spriteSheet.setCoords(    0.0f, 3 / 4.0f,
						      1 / 4.0f, 2 / 4.0f,
						          0.0f, 2 / 4.0f,
						      1 / 4.0f, 3 / 4.0f);

	}
	else if(dirMovement == DirMovement::RIGHT) {

		spriteSheet.setCoords(    0.0f,     1.0f,
						      1 / 4.0f, 3 / 4.0f,
						          0.0f, 3 / 4.0f,
						      1 / 4.0f,     1.0f);

	}

	spriteSheet.modifyTexCoord( );

}

void Human::update(Engine::TextMap* textMap, Engine::Camera& camera, double deltaTime) {

	if(behavior == Behavior::WAITING) {

		waitingCooloff -= deltaTime;

		if(waitingCooloff <= 0) {

			waitingCooloff = 2;
			behavior = Behavior::WALKING;
			
			//Sequencia de passos para obter destinos válidos
			std::vector<glm::vec2> listOfTilesAvailable;

			for(int y = 0; y < textMap->quantVerticalTiles; y++)
				for(int x = 0; x < textMap->quantHorizontalTiles; x++)
					if(textMap->fileStringMod[x + y * textMap->quantHorizontalTiles] == '0')
						listOfTilesAvailable.push_back(glm::vec2(x, y));

			glm::vec2 destino = listOfTilesAvailable[rand( ) % listOfTilesAvailable.size( )];

			std::cout << "(" << destino.x << ", " << destino.y << ")" << std::endl;

			sequenciaDeMovimentos = aStarPathfinding(positionTextMap, destino, textMap);

		}

	}
	else {

		//Input equivalent
		if(spriteSheet.movementCooloff == 0) {

			if(!sequenciaDeMovimentos.empty()) {

				Engine::Passo targetPosition = sequenciaDeMovimentos.front( );
				sequenciaDeMovimentos.pop( );

				glm::vec2 targetPosWorld = textMap->textMapPosToWorldPos(targetPosition.mapTextPos, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

				textMap->fileStringMod[positionTextMap.x + positionTextMap.y * textMap->quantHorizontalTiles] = '0';
				textMap->fileStringMod[targetPosition.mapTextPos.x + targetPosition.mapTextPos.y * textMap->quantHorizontalTiles] = 'H';

				GLfloat distancia;

				if(targetPosition.dirMovement == DirMovement::DOWN || targetPosition.dirMovement == DirMovement::UP) 
					distancia = glm::abs(targetPosWorld.y - position.y);
				else if(targetPosition.dirMovement == DirMovement::LEFT || targetPosition.dirMovement == DirMovement::RIGHT)
					distancia = glm::abs(targetPosWorld.x - position.x);

				spriteSheet.amountToMove = distancia / spriteSheet.cyclesMov;
				spriteSheet.movementCooloff = distancia;
				positionTextMap = targetPosition.mapTextPos;

				switch(targetPosition.dirMovement) {
				case DirMovement::DOWN:
					dirMovement = DirMovement::DOWN;
					break;
				case DirMovement::UP:
					dirMovement = DirMovement::UP;
					break;
				case DirMovement::LEFT:
					dirMovement = DirMovement::LEFT;
					break;
				case DirMovement::RIGHT:
					dirMovement = DirMovement::RIGHT;
					break;
				}

				positTextCoordsAcord( );

			}
			else {

				dirMovement = DirMovement::DOWN;

				positTextCoordsAcord( );

				behavior = Behavior::WAITING;

			}

		}

		//Update equivalent
		if(spriteSheet.movementCooloff > 0) {

			float amountToMoveWithDeltaTime = spriteSheet.amountToMove * deltaTime;

			if(spriteSheet.textCoordUpdateDelay > 0)
				spriteSheet.textCoordUpdateDelay -= spriteSheet.cyclesAnim * deltaTime;
			if(spriteSheet.textCoordUpdateDelay < 0)
				spriteSheet.textCoordUpdateDelay = 0;

			if(dirMovement == DirMovement::LEFT) {
				position.x -= amountToMoveWithDeltaTime;
				spriteSheet.movementCooloff -= amountToMoveWithDeltaTime;
			}
			else if(dirMovement == DirMovement::UP) {
				position.y += amountToMoveWithDeltaTime;
				spriteSheet.movementCooloff -= amountToMoveWithDeltaTime;
			}
			else if(dirMovement == DirMovement::RIGHT) {
				position.x += amountToMoveWithDeltaTime;
				spriteSheet.movementCooloff -= amountToMoveWithDeltaTime;
			}
			else if(dirMovement == DirMovement::DOWN) {
				position.y -= amountToMoveWithDeltaTime;
				spriteSheet.movementCooloff -= amountToMoveWithDeltaTime;
			}

			if(spriteSheet.bottomRightCoord[0] < 4 / 4.0f && spriteSheet.textCoordUpdateDelay == 0) { //Poderia ser topRightCoord também por exemplo

				spriteSheet.topLeftCoord[0] += 1 / 4.0f;
				spriteSheet.bottomRightCoord[0] += 1 / 4.0f;
				spriteSheet.bottomLeftCoord[0] += 1 / 4.0f;
				spriteSheet.topRightCoord[0] += 1 / 4.0f;

				spriteSheet.textCoordUpdateDelay = 1;

			}
			else if(spriteSheet.bottomRightCoord[0] >= 4 / 4.0f && spriteSheet.textCoordUpdateDelay == 0) {

				spriteSheet.setXCoords(0.0f, 1 / 4.0f, 0.0f, 1 / 4.0f);

				spriteSheet.textCoordUpdateDelay = 1;

			}

			spriteSheet.modifyTexCoord( );

		}
		if(spriteSheet.movementCooloff == 0) {

			if(spriteSheet.topLeftCoord[0] != 0.0f) {

				spriteSheet.setXCoords(0.0f, 1 / 4.0f, 0.0f, 1 / 4.0f);

				spriteSheet.modifyTexCoord( );

			}

		}
		if(spriteSheet.movementCooloff <= 0) {
			spriteSheet.movementCooloff = 0;
			spriteSheet.textCoordUpdateDelay = 0;
		}

	}

}

void Human::draw(glm::vec3 camProps, glm::vec2 screenProps) {

	worldToScreenPoint(camProps, screenProps);

	spriteSheet.renderer->drawSprite(spriteSheet.texture, positionScreen, size, glm::vec3(1.0), rotation);

}
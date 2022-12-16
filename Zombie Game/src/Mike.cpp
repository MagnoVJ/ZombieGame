#include "../include/Mike.h"

Mike::Mike(Engine::Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotation)
	: GameObject(position, size, rotation), spriteSheet(0, 0.4, 10, 0), aiming(Engine::keysProcessed[GLFW_KEY_SPACE]) {

	spriteSheet.setCoords(    0.0f, 1 / 4.0f, 
						  1 / 5.0f,     0.0f,
						      0.0f,     0.0f,
						  1 / 5.0f, 1 / 4.0f);

	spriteSheet.texture = texture;
	spriteSheet.renderer = new Engine::SpriteRenderer(Engine::ResourceManager::getShader("Basic_shader"));

}

Mike::~Mike( ) { }

void Mike::positTextCoordsAcord( ) {

	if(dirMovement == DirMovement::DOWN) {

		spriteSheet.setCoords(    0.0f, 1 / 4.0f, 
						      1 / 5.0f,     0.0f,
						          0.0f,     0.0f,
						      1 / 5.0f, 1 / 4.0f);

	}
	else if(dirMovement == DirMovement::UP) {

		spriteSheet.setCoords(    0.0f, 2 / 4.0f,
						      1 / 5.0f, 1 / 4.0f,
						          0.0f, 1 / 4.0f,
						      1 / 5.0f, 2 / 4.0f);

	}
	else if(dirMovement == DirMovement::LEFT) {

		spriteSheet.setCoords(    0.0f, 3 / 4.0f,
						      1 / 5.0f, 2 / 4.0f,
						          0.0f, 2 / 4.0f,
						      1 / 5.0f, 3 / 4.0f);

	}
	else if(dirMovement == DirMovement::RIGHT) {

		spriteSheet.setCoords(    0.0f,     1.0f,
						      1 / 5.0f, 3 / 4.0f,
						          0.0f, 3 / 4.0f,
						      1 / 5.0f,     1.0f);

	}

	spriteSheet.modifyTexCoord( );

}

void Mike::input(Engine::TextMap* textMap, Engine::Camera& camera, std::vector<Beam>& listOfBeams) {

	if(Engine::keys[GLFW_KEY_SPACE])
		Engine::keysProcessed[GLFW_KEY_SPACE] = GL_TRUE;

	if(!aiming) {

		if(Engine::keys[GLFW_KEY_LEFT]) {

			glm::vec2 targetPosition = glm::vec2(positionTextMap.x - 1, positionTextMap.y);

			if(targetPosition.x >= 0 && textMap->fileString[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] == '0')
				if(spriteSheet.movementCooloff == 0) {

					glm::vec2 targetPosWorld = textMap->textMapPosToWorldPos(targetPosition, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					textMap->fileStringMod[positionTextMap.x + positionTextMap.y * textMap->quantHorizontalTiles] = '0';
					textMap->fileStringMod[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] = 'P';

					GLfloat distancia = glm::abs(targetPosWorld.x - position.x);

					spriteSheet.amountToMove = distancia / spriteSheet.cyclesMov;
					spriteSheet.movementCooloff = distancia;
					positionTextMap = targetPosition;
					dirMovement = DirMovement::LEFT;

					positTextCoordsAcord( );

				}

			Engine::keysProcessed[GLFW_KEY_LEFT] = GL_TRUE;

		}
		if(Engine::keys[GLFW_KEY_UP]) {

			glm::vec2 targetPosition = glm::vec2(positionTextMap.x, positionTextMap.y - 1);

			if(targetPosition.y >= 0 && textMap->fileString[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] == '0')
				if(spriteSheet.movementCooloff == 0) {

					glm::vec2 targetPosWorld = textMap->textMapPosToWorldPos(targetPosition, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					textMap->fileStringMod[positionTextMap.x + positionTextMap.y * textMap->quantHorizontalTiles] = '0';
					textMap->fileStringMod[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] = 'P';

					GLfloat distancia = glm::abs(targetPosWorld.y - position.y);

					spriteSheet.amountToMove = distancia / spriteSheet.cyclesMov;
					spriteSheet.movementCooloff = distancia;
					positionTextMap = targetPosition;
					dirMovement = DirMovement::UP;

					positTextCoordsAcord( );

				}

			Engine::keysProcessed[GLFW_KEY_UP] = GL_TRUE;

		}
		if(Engine::keys[GLFW_KEY_RIGHT]) {

			glm::vec2 targetPosition = glm::vec2(positionTextMap.x + 1, positionTextMap.y);

			if(targetPosition.x <= textMap->quantHorizontalTiles - 1 && textMap->fileString[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] == '0')
				if(spriteSheet.movementCooloff == 0) {

					glm::vec2 targetPosWorld = textMap->textMapPosToWorldPos(targetPosition, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					textMap->fileStringMod[positionTextMap.x + positionTextMap.y * textMap->quantHorizontalTiles] = '0';
					textMap->fileStringMod[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] = 'P';

					GLfloat distancia = glm::abs(targetPosWorld.x - position.x);

					spriteSheet.amountToMove = distancia / spriteSheet.cyclesMov;
					spriteSheet.movementCooloff = distancia;
					positionTextMap = targetPosition;
					dirMovement = DirMovement::RIGHT;

					positTextCoordsAcord( );

				}

			Engine::keysProcessed[GLFW_KEY_RIGHT] = GL_TRUE;

		}
		if(Engine::keys[GLFW_KEY_DOWN]) {

			glm::vec2 targetPosition = glm::vec2(positionTextMap.x, positionTextMap.y + 1);

			if(targetPosition.y <= textMap->quantVerticalTiles - 1 && textMap->fileString[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] == '0')
				if(spriteSheet.movementCooloff == 0) {

					glm::vec2 targetPosWorld = textMap->textMapPosToWorldPos(targetPosition, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					textMap->fileStringMod[positionTextMap.x + positionTextMap.y * textMap->quantHorizontalTiles] = '0';
					textMap->fileStringMod[targetPosition.x + targetPosition.y * textMap->quantHorizontalTiles] = 'P';

					GLfloat distancia = glm::abs(targetPosWorld.y - position.y);

					spriteSheet.amountToMove = distancia / spriteSheet.cyclesMov;
					spriteSheet.movementCooloff = distancia;
					positionTextMap = targetPosition;
					dirMovement = DirMovement::DOWN;

					positTextCoordsAcord( );

				}

			Engine::keysProcessed[GLFW_KEY_DOWN] = GL_TRUE;

		}

	}
	else {

		if(spriteSheet.movementCooloff == 0) {

			if(Engine::keys[GLFW_KEY_UP] && !Engine::keysProcessed[GLFW_KEY_UP]) {

				if(dirMovement != DirMovement::UP)
					dirMovement = DirMovement::UP;
				else {

					glm::vec2 mikePositionInSS = camera.worldToScreenPoint(position);
					glm::vec2 beamPositionInSS = glm::vec2(mikePositionInSS.x + 1, mikePositionInSS.y - 5 - 10); //O 10 adicional é para deslocar o topo da sprite do beam para a ponta da arma
					glm::vec2 beamPositionInWS = camera.screenToWorldPoint(beamPositionInSS);

					glm::vec2 beamPositionInTS = camera.screenToTextMapPoint(beamPositionInSS, textMap->sizeEachTile);

					Beam beam(Engine::ResourceManager::getTexture("Beam"), beamPositionInWS, glm::vec2(21, 21));

					beam.dirMovement = DirMovement::UP;

					listOfBeams.push_back(beam);

				}

				Engine::keysProcessed[GLFW_KEY_UP] = GL_TRUE;

			}
			if(Engine::keys[GLFW_KEY_DOWN] && !Engine::keysProcessed[GLFW_KEY_DOWN]) {

				if(dirMovement != DirMovement::DOWN)
					dirMovement = DirMovement::DOWN;
				else {

					glm::vec2 mikePositionInSS = camera.worldToScreenPoint(position);
					glm::vec2 beamPositionInSS = glm::vec2(mikePositionInSS.x - 1, mikePositionInSS.y + 15 + 10); //O 10 adicional é para deslocar o topo da sprite do beam para a ponta da arma
					glm::vec2 beamPositionInWS = camera.screenToWorldPoint(beamPositionInSS);

					glm::vec2 beamPositionInTS = camera.screenToTextMapPoint(beamPositionInSS, textMap->sizeEachTile);

					Beam beam(Engine::ResourceManager::getTexture("Beam"), beamPositionInWS, glm::vec2(21, 21), 180.0f);

					beam.dirMovement = DirMovement::DOWN;

					listOfBeams.push_back(beam);

				}

				Engine::keysProcessed[GLFW_KEY_DOWN] = GL_TRUE;
			
			}
			if(Engine::keys[GLFW_KEY_RIGHT] && !Engine::keysProcessed[GLFW_KEY_RIGHT]) {

				if(dirMovement != DirMovement::RIGHT)
					dirMovement = DirMovement::RIGHT;
				else {

					glm::vec2 mikePositionInSS = camera.worldToScreenPoint(position);
					glm::vec2 beamPositionInSS = glm::vec2(mikePositionInSS.x + 17 + 10, mikePositionInSS.y + 8);
					glm::vec2 beamPositionInWS = camera.screenToWorldPoint(beamPositionInSS);

					glm::vec2 beamPositionInTS = camera.screenToTextMapPoint(beamPositionInSS, textMap->sizeEachTile);

					Beam beam(Engine::ResourceManager::getTexture("Beam"), beamPositionInWS, glm::vec2(21, 21), 90.0f);

					beam.dirMovement = DirMovement::RIGHT;

					listOfBeams.push_back(beam);

				}

				Engine::keysProcessed[GLFW_KEY_RIGHT] = GL_TRUE;

			}
			if(Engine::keys[GLFW_KEY_LEFT] && !Engine::keysProcessed[GLFW_KEY_LEFT]) {

				if(dirMovement != DirMovement::LEFT)
					dirMovement = DirMovement::LEFT;
				else {

					glm::vec2 mikePositionInSS = camera.worldToScreenPoint(position);
					glm::vec2 beamPositionInSS = glm::vec2(mikePositionInSS.x - 17 - 10, mikePositionInSS.y + 8);
					glm::vec2 beamPositionInWS = camera.screenToWorldPoint(beamPositionInSS);

					glm::vec2 beamPositionInTS = camera.screenToTextMapPoint(beamPositionInSS, textMap->sizeEachTile);

					Beam beam(Engine::ResourceManager::getTexture("Beam"), beamPositionInWS, glm::vec2(21, 21), -90.0f);

					beam.dirMovement = DirMovement::LEFT;

					listOfBeams.push_back(beam);

				}

				Engine::keysProcessed[GLFW_KEY_LEFT] = GL_TRUE;

			}

			positTextCoordsAcord( );

			spriteSheet.setXCoords(4 / 5.0f, 1.0f, 4 / 5.0f, 1.0f);

			spriteSheet.modifyTexCoord( );

		}

	}

}

void Mike::update(double deltaTime) {

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

		if(spriteSheet.bottomRightCoord[0] < 4 / 5.0f && spriteSheet.textCoordUpdateDelay == 0) { //Poderia ser topRightCoord também por exemplo

			spriteSheet.topLeftCoord[0] += 1 / 5.0f;
			spriteSheet.bottomRightCoord[0] += 1 / 5.0f;
			spriteSheet.bottomLeftCoord[0] += 1 / 5.0f;
			spriteSheet.topRightCoord[0] += 1 / 5.0f;

			spriteSheet.textCoordUpdateDelay = 1;

		}
		else if(spriteSheet.bottomRightCoord[0] >= 4 / 5.0f && spriteSheet.textCoordUpdateDelay == 0) {

			spriteSheet.setXCoords(0.0f, 1 / 5.0f, 0.0f, 1 / 5.0f);

			spriteSheet.textCoordUpdateDelay = 1;

		}

		spriteSheet.modifyTexCoord( );

	}
	if(spriteSheet.movementCooloff == 0) {

		//Volta para a primeira sprite caso não aja movimento ALTERAR QUANDO A SPRITESHEET SER MODIFICADA!
		if(spriteSheet.topLeftCoord[0] != 0.0f && !aiming) {

			spriteSheet.setXCoords(0.0f, 1 / 5.0f, 0.0f, 1 / 5.0f);

			spriteSheet.modifyTexCoord( );

		}

	}

	if(spriteSheet.movementCooloff <= 0) {
		spriteSheet.movementCooloff = 0;
		spriteSheet.textCoordUpdateDelay = 0;
	}

}

void Mike::draw(glm::vec3 camProps, glm::vec2 screenProps) {

	worldToScreenPoint(camProps, screenProps);

	spriteSheet.renderer->drawSprite(spriteSheet.texture, positionScreen, size, glm::vec3(1.0), rotation);

}
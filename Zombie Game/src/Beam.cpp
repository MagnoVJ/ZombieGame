#include "../include/Beam.h"

Beam::Beam(Engine::Texture2D texture, glm::vec2 position, glm::vec2 size, GLfloat rotation) : GameObject(position, size, rotation), spriteSheet(0, 0, 10, 1), speed(400), recentlyBorn(GL_TRUE), expAnimation(GL_FALSE), deleteMe(GL_FALSE), contOffScreen(0) { 

	spriteSheet.texture = texture;
	spriteSheet.renderer = new Engine::SpriteRenderer(Engine::ResourceManager::getShader("Basic_shader"));

}

Beam::~Beam( ) { }

void Beam::update(double deltaTime, Engine::Camera& camera, Engine::TextMap* textMap) {

	//recentlyBornInt: usada para evitar que a posição do beam seja atualizada no mesmo frame que ele foi criado
	GLboolean recentlyBornInt = recentlyBorn;

	if(!expAnimation) {

		if(dirMovement == DirMovement::LEFT) {

			glm::vec2 hitPointSS;

			if(recentlyBorn) {

				recentlyBorn = GL_FALSE;

				hitPointSS = camera.worldToScreenPoint(position);
				hitPointSS = glm::vec2(hitPointSS.x - static_cast<int>(size.y / 2), hitPointSS.y);

				glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

				if(hitPointTS.x >= 0 && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

					if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

						spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

						rotation += 90.0f; //Volta a rotação para o estado original
						size = textMap->sizeEachTile;

						hitPointTS.x++;
						position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

						//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
						glm::vec2 posSS = camera.worldToScreenPoint(position);
						posSS.y += 6;
						position = camera.screenToWorldPoint(posSS);

						spriteSheet.setCoords(    0.0f, 2 / 4.0f,
											  1 / 4.0f, 1 / 4.0f,
										          0.0f, 1 / 4.0f,
										      1 / 4.0f, 2 / 4.0f);

						spriteSheet.modifyTexCoord( );

						expAnimation = GL_TRUE;

					}

					return;

				}

			}

			glm::vec2 positionProxFrame = glm::vec2(position.x - speed * deltaTime, position.y);

			hitPointSS = camera.worldToScreenPoint(positionProxFrame);
			hitPointSS = glm::vec2(hitPointSS.x - static_cast<int>(size.y / 2), hitPointSS.y);

			glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

			if(hitPointTS.x >= 0 && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

				if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

					spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

					rotation += 90.0f; //Volta a rotação para o estado original
					size = textMap->sizeEachTile;

					hitPointTS.x++;
					position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
					glm::vec2 posSS = camera.worldToScreenPoint(position);
					posSS.y += 6;
					position = camera.screenToWorldPoint(posSS);

					spriteSheet.setCoords(    0.0f, 2 / 4.0f,
										  1 / 4.0f, 1 / 4.0f,
										      0.0f, 1 / 4.0f,
										  1 / 4.0f, 2 / 4.0f);

					spriteSheet.modifyTexCoord( );

					expAnimation = GL_TRUE;

				}

				return;

			}

			if(!recentlyBornInt)
				position = glm::vec2(position.x - speed * deltaTime, position.y);

			if(hitPointTS.x == 0)
				if(++contOffScreen > 50) //50 é completamente arbitrário
					deleteMe = GL_TRUE;

		}
		else if(dirMovement == DirMovement::RIGHT) {

			glm::vec2 hitPointSS;

			if(recentlyBorn) {

				recentlyBorn = GL_FALSE;

				hitPointSS = camera.worldToScreenPoint(position);
				hitPointSS = glm::vec2(hitPointSS.x + static_cast<int>(size.y / 2), hitPointSS.y);

				glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

				if(hitPointTS.x < textMap->quantHorizontalTiles && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

					if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

						spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

						rotation -= 90.0f; //Volta a rotação para o estado original
						size = textMap->sizeEachTile;

						hitPointTS.x--;
						position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

						//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
						glm::vec2 posSS = camera.worldToScreenPoint(position);
						posSS.y += 6;
						position = camera.screenToWorldPoint(posSS);

						spriteSheet.setCoords(    0.0f, 1 / 4.0f,
										      1 / 4.0f,     0.0f,
										          0.0f,     0.0f,
										      1 / 4.0f, 1 / 4.0f);

						spriteSheet.modifyTexCoord( );

						expAnimation = GL_TRUE;

					}

					return;

				}

			}

			glm::vec2 positionProxFrame = glm::vec2(position.x + speed * deltaTime, position.y);

			hitPointSS = camera.worldToScreenPoint(positionProxFrame);
			hitPointSS = glm::vec2(hitPointSS.x + static_cast<int>(size.y / 2), hitPointSS.y);

			glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

			if(hitPointTS.x < textMap->quantHorizontalTiles && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

				if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

					spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

					rotation -= 90.0f; //Volta a rotação para o estado original
					size = textMap->sizeEachTile;

					hitPointTS.x--;
					position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
					glm::vec2 posSS = camera.worldToScreenPoint(position);
					posSS.y += 6;
					position = camera.screenToWorldPoint(posSS);

					spriteSheet.setCoords(    0.0f, 1 / 4.0f,
										  1 / 4.0f,     0.0f,
										      0.0f,     0.0f,
										  1 / 4.0f, 1 / 4.0f);

					spriteSheet.modifyTexCoord( );

					expAnimation = GL_TRUE;

				}

				return;

			}

			if(!recentlyBornInt)
				position = glm::vec2(position.x + speed * deltaTime, position.y);

			if(hitPointTS.x >= textMap->quantHorizontalTiles + 1)
				deleteMe = GL_TRUE;

		}
		else if(dirMovement == DirMovement::UP) {

			glm::vec2 hitPointSS;

			if(recentlyBorn) {

				recentlyBorn = GL_FALSE;

				hitPointSS = camera.worldToScreenPoint(position);
				hitPointSS = glm::vec2(hitPointSS.x, hitPointSS.y - static_cast<int>(size.y / 2));

				glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

				if(hitPointTS.y >= 0 && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

					if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

						spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

						size = textMap->sizeEachTile;

						hitPointTS.y++;
						position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

						//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
						glm::vec2 posSS = camera.worldToScreenPoint(position);
						posSS.x += 1;
						position = camera.screenToWorldPoint(posSS);

						spriteSheet.setCoords(    0.0f, 3 / 4.0f,
										      1 / 4.0f, 2 / 4.0f,
										          0.0f, 2 / 4.0f,
										      1 / 4.0f, 3 / 4.0f);

						spriteSheet.modifyTexCoord( );

						expAnimation = GL_TRUE;

					}

					return;

				}

			}

			glm::vec2 positionProxFrame = glm::vec2(position.x, position.y + speed * deltaTime);

			hitPointSS = camera.worldToScreenPoint(positionProxFrame);
			hitPointSS = glm::vec2(hitPointSS.x, hitPointSS.y - static_cast<int>(size.y / 2));

			glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

			if(hitPointTS.y >= 0 && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

				if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

					spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

					size = textMap->sizeEachTile;

					hitPointTS.y++;
					position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
					glm::vec2 posSS = camera.worldToScreenPoint(position);
					posSS.x += 1;
					position = camera.screenToWorldPoint(posSS);

					spriteSheet.setCoords(    0.0f, 3 / 4.0f,
										  1 / 4.0f, 2 / 4.0f,
										      0.0f, 2 / 4.0f,
										  1 / 4.0f, 3 / 4.0f);

					spriteSheet.modifyTexCoord( );

					expAnimation = GL_TRUE;

				}

				return;

			}

			if(!recentlyBornInt)
				position = glm::vec2(position.x, position.y + speed * deltaTime);

			if(hitPointTS.y == 0)
				if(++contOffScreen > 50) //50 é completamente arbitrário
					deleteMe = GL_TRUE;

		}
		else if(dirMovement == DirMovement::DOWN) {

			glm::vec2 hitPointSS;

			if(recentlyBorn) {

				recentlyBorn = GL_FALSE;

				hitPointSS = camera.worldToScreenPoint(position);
				hitPointSS = glm::vec2(hitPointSS.x, hitPointSS.y + static_cast<int>(size.y / 2));

				glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

				if(hitPointTS.y < textMap->quantVerticalTiles && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

					if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

						spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

						rotation -= 180.0f; //Volta a rotação para o estado original
						size = textMap->sizeEachTile;

						hitPointTS.y--;
						position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

						//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
						glm::vec2 posSS = camera.worldToScreenPoint(position);
						posSS.x -= 1;
						position = camera.screenToWorldPoint(posSS);

						spriteSheet.setCoords(    0.0f,     1.0f,
										      1 / 4.0f, 3 / 4.0f,
										          0.0f, 3 / 4.0f,
										      1 / 4.0f,     1.0f);

						spriteSheet.modifyTexCoord( );

						expAnimation = GL_TRUE;

					}

					return;

				}

			}

			glm::vec2 positionProxFrame = glm::vec2(position.x, position.y - speed * deltaTime);

			hitPointSS = camera.worldToScreenPoint(positionProxFrame);
			hitPointSS = glm::vec2(hitPointSS.x, hitPointSS.y + static_cast<int>(size.y / 2));

			glm::vec2 hitPointTS = camera.screenToTextMapPoint(hitPointSS, textMap->sizeEachTile);

			if(hitPointTS.y < textMap->quantVerticalTiles && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != '0' && textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] != 'P') {

				if(textMap->fileStringMod[hitPointTS.x + hitPointTS.y * textMap->quantHorizontalTiles] == '1') {

					spriteSheet.texture = Engine::ResourceManager::getTexture("Beam_Exp");

					rotation -= 180.0f; //Volta a rotação para o estado original
					size = textMap->sizeEachTile;

					hitPointTS.y--;
					position = textMap->textMapPosToWorldPos(hitPointTS, glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

					//Essa sequencia de passos, serve para posicionar a sprite no rumo do shot
					glm::vec2 posSS = camera.worldToScreenPoint(position);
					posSS.x -= 1;
					position = camera.screenToWorldPoint(posSS);

					spriteSheet.setCoords(    0.0f,     1.0f,
										  1 / 4.0f, 3 / 4.0f,
										      0.0f, 3 / 4.0f,
										  1 / 4.0f,     1.0f);

					spriteSheet.modifyTexCoord( );

					expAnimation = GL_TRUE;

				}

				return;

			}

			if(!recentlyBornInt)
				position = glm::vec2(position.x, position.y - speed * deltaTime);

			if(hitPointTS.y >= textMap->quantVerticalTiles + 1)
				deleteMe = GL_TRUE;

		}

	}
	//Else somente responsável pela animação
	else {

		if(spriteSheet.textCoordUpdateDelay > 0)
			spriteSheet.textCoordUpdateDelay -= spriteSheet.cyclesAnim * deltaTime;
		if(spriteSheet.textCoordUpdateDelay < 0)
			spriteSheet.textCoordUpdateDelay = 0;

		if(spriteSheet.bottomRightCoord[0] < 4 / 4.0f && spriteSheet.textCoordUpdateDelay == 0) {

			spriteSheet.topLeftCoord[0] += 1 / 4.0f;
			spriteSheet.bottomRightCoord[0] += 1 / 4.0f;
			spriteSheet.bottomLeftCoord[0] += 1 / 4.0f;
			spriteSheet.topRightCoord[0] += 1 / 4.0f;

			spriteSheet.textCoordUpdateDelay = 1;

			spriteSheet.modifyTexCoord( );

		}
		else if(spriteSheet.bottomRightCoord[0] >= 4 / 4.0f && spriteSheet.textCoordUpdateDelay == 0)
			deleteMe = GL_TRUE;

	}

}

void Beam::draw(glm::vec3 camProps, glm::vec2 screenProps) {

	worldToScreenPoint(camProps, screenProps);

	spriteSheet.renderer->drawSprite(spriteSheet.texture, positionScreen, size, glm::vec3(1.0), rotation);

}
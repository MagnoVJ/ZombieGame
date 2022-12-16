#pragma once

#include <Engine_inc_all.h>

#include "Beam.h"
#include "DirMovement.h"

class Mike : public Engine::GameObject {

private:
	void positTextCoordsAcord( ); //Posiciona as coordenadas da textura no início da sequencia de sprite correta baseada na direção que Mike está atualmente movendo.

public:
	Mike(Engine::Texture2D texture, glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(10.0f), GLfloat rotation = 0.0f);
	~Mike();

	Engine::SpriteSheet spriteSheet;

	DirMovement dirMovement;

	GLboolean& aiming;

	glm::vec2 positionTextMap;

	void input(Engine::TextMap* textMap, Engine::Camera& camera, std::vector<Beam>& listOfBeams);
	void update(double deltaTime);
	void draw(glm::vec3 camProps, glm::vec2 screenProps);

};
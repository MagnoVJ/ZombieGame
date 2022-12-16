#pragma once

#include <Engine_inc_all.h>

#include <DirMovement.h>

#include <queue>

enum Behavior { WAITING, WALKING};

class Human : public Engine:: GameObject {

private:
	Behavior behavior;
	GLfloat waitingCooloff;

	std::queue<Engine::Passo> sequenciaDeMovimentos;

	void positTextCoordsAcord(); //Posiciona as coordenadas da textura no in�cio da sequencia de sprite correta baseada na dire��o que Mike est� atualmente movendo.

public:
	Human(Engine::Texture2D texture, glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(10.0f), GLfloat rotation = 0.0f);
	~Human( );

	Engine::SpriteSheet spriteSheet;

	DirMovement dirMovement;

	glm::vec2 positionTextMap;

	void update(Engine::TextMap* textMap, Engine::Camera& camera, double deltaTime);
	void draw(glm::vec3 camProps, glm::vec2 screenProps);

};
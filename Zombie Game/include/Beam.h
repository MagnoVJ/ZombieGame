#pragma once

#include <Engine_inc_all.h>

#include "DirMovement.h"

class Beam : public Engine::GameObject {

private:
	GLshort contOffScreen;

public:
	Beam(Engine::Texture2D texture, glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(10.0f), GLfloat rotation = 0.0f);
	~Beam( );

	Engine::SpriteSheet spriteSheet;

	GLfloat speed;
	DirMovement dirMovement;
	GLboolean recentlyBorn;
	GLboolean expAnimation;
	GLboolean deleteMe;

	void update(double deltaTime, Engine::Camera& camera, Engine::TextMap* textMap);
	void draw(glm::vec3 camProps, glm::vec2 screenProps);

};
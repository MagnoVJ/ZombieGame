#pragma once

#include "Texture2D.h"
#include "SpriteRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

namespace Engine {

	class TextMap {

	private:
		int screenWidth;
		int screenHeight;

		void loadFileMap(const char* fileMapPath);


	public:
		int quantHorizontalTiles;
		int quantVerticalTiles;

		glm::vec2 sizeEachTile;

		std::string fileString;
		std::string fileStringMod;

		std::vector<Texture2D> textures;

		glm::vec2 textMapPosToWorldPos(glm::vec2 textMapPos, glm::vec3 camProps, glm::vec2 screenProps);

		TextMap(const char* fileMapPath, int screenWidth, int screenHeight);
		~TextMap();

		void draw(SpriteRenderer& renderer);

	};

}
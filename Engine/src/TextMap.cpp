#include "../include/TextMap.h"

namespace Engine {

	TextMap::TextMap(const char* fileMapPath, int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
	
		loadFileMap(fileMapPath);

		fileStringMod = fileString;

		sizeEachTile.x = screenWidth / quantHorizontalTiles;
		sizeEachTile.y = screenHeight / quantVerticalTiles;

	}

	TextMap::~TextMap( ) { }

	glm::vec2 TextMap::textMapPosToWorldPos(glm::vec2 textMapPos, glm::vec3 camProps, glm::vec2 screenProps) {

		glm::vec2 posTextMap = glm::vec2(textMapPos.x * sizeEachTile.x, textMapPos.y * sizeEachTile.y);

		//Desloca position para ficar no centro do tile selecionado
		posTextMap.x += sizeEachTile.x / 2.0f;
		posTextMap.y += sizeEachTile.y / 2.0f;

		//Converte screen to world (Mesma método utilizado por camera)
		glm::vec2 pointWorldSpace;
		pointWorldSpace = posTextMap - glm::vec2(screenProps.x / 2, screenProps.y / 2);
		pointWorldSpace /= camProps.z;
		pointWorldSpace += glm::vec2(camProps.x, camProps.y);
		pointWorldSpace.y *= -1;

		return pointWorldSpace;

	}

	void TextMap::loadFileMap(const char* fileMapPath) {

		std::string quantQdsHori;
		std::string quantQdsVert;
		std::string line;

		std::stringstream lineStream;

		try {
			std::ifstream mapFile(fileMapPath);

			std::getline(mapFile, quantQdsHori);
			std::getline(mapFile, quantQdsVert);

			while(std::getline(mapFile, line))
				lineStream << line;

			mapFile.close( );

			fileString = lineStream.str( );

		}
		catch(std::exception e) {
			std::cout << "Falha em ler o arquivo de mapa" << std::endl;
		}

		//Remove espaço branco
		fileString.erase(std::remove_if(fileString.begin( ), fileString.end( ), isspace), fileString.end( ));

		quantHorizontalTiles = std::stoi(quantQdsHori);
		quantVerticalTiles = std::stoi(quantQdsVert);

	}

	void TextMap::draw(SpriteRenderer& renderer) {

		int ind = 0;

		for(int y = 0; y <= screenHeight - sizeEachTile.y; y += sizeEachTile.y)
			for(int x = 0; x <= screenWidth - sizeEachTile.x; x += sizeEachTile.x) {

				std::stringstream ss;
				std::string s;
				ss << fileString[ind];
				ss >> s;
				int typString = std::stoi(s);

				renderer.drawSprite(textures[typString], glm::vec2((float)x, (float)y), sizeEachTile, glm::vec3(1.0f));

				ind++;

			}

	}

}
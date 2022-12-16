#include "../include/GameObject.h"

namespace Engine {

	GameObject::GameObject(glm::vec2 position, glm::vec2 size, GLfloat rotation) : position(position), size(size), rotation(rotation) { }

	GameObject::~GameObject( ) { }

	void GameObject::worldToScreenPoint(glm::vec3 camProps, glm::vec2 screenProps) {

		positionScreen = position;

		positionScreen.y *= -1;
		positionScreen -= glm::vec2(camProps.x, camProps.y);
		positionScreen *= camProps.z;
		positionScreen = positionScreen + glm::vec2(screenProps.x / 2, screenProps.y / 2);

		positionScreen = glm::vec2(positionScreen.x - size.x / 2, positionScreen.y - size.y / 2);

	}

	std::queue<Passo> GameObject::aStarPathfinding(glm::vec2 originTS, glm::vec2 destinyTS, TextMap* textMap) {

		std::vector<AStarNode> openList;
		std::vector<AStarNode> closedList;

		std::vector<AStarNode*> aStarNodeVectorToDeallocate;

		AStarNode aNode;

		aNode.positionTS = originTS;
		aNode.G = 0.0f;

		openList.push_back(aNode);
		
		int i = 0;

		do {

			float x, y;

			switch(i) {
			case 0: x = -1.0f; y = 0.0f; break;
			case 1: x = 0.0f; y = -1.0f; break;
			case 2: x = 1.0f; y = 0.0f; break;
			case 3: x = 0.0f; y = 1.0f; break;
			}

			if(aNode.positionTS.x + x >= 0 && aNode.positionTS.x + x < textMap->quantHorizontalTiles && aNode.positionTS.y + y >= 0 && aNode.positionTS.y + y < textMap->quantVerticalTiles)
				if(textMap->fileString[aNode.positionTS.x + x + (aNode.positionTS.y + y) * textMap->quantHorizontalTiles] == '0') {

					AStarNode adjNode;

					adjNode.positionTS = glm::vec2(aNode.positionTS.x + x, aNode.positionTS.y + y);
					adjNode.parent = new AStarNode(aNode);

					aStarNodeVectorToDeallocate.push_back(adjNode.parent);

					adjNode.calculateG( );
					adjNode.calculateH(destinyTS);
					adjNode.calculateF( );

					openList.push_back(adjNode);

				}

		} while(++i < 4);

		openList.erase(openList.begin( ));
		closedList.push_back(aNode);

		do {

			int li = 0;
			float lowestF = openList[li].F;

			for(int i = 1; i < openList.size( ); i++)
				if(openList[i].F < lowestF) {
					lowestF = openList[i].F;
					li = i;
				}

			closedList.push_back(openList[li]);

			openList.erase(openList.begin( ) + li);

			AStarNode nodeLF = closedList[closedList.size( ) - 1];

			i = 0;

			do {

				float x, y;

				switch(i) {
				case 0: x = -1.0f; y = 0.0f; break;
				case 1: x = 0.0f; y = -1.0f; break;
				case 2: x = 1.0f; y = 0.0f; break;
				case 3: x = 0.0f; y = 1.0f; break;
				}

				if(nodeLF.positionTS.x + x >= 0 && nodeLF.positionTS.x + x < textMap->quantHorizontalTiles && nodeLF.positionTS.y + y >= 0 && nodeLF.positionTS.y + y < textMap->quantVerticalTiles)
					if(textMap->fileString[nodeLF.positionTS.x + x + (nodeLF.positionTS.y + y) * textMap->quantHorizontalTiles] == '0') {

						auto verifClosedList = [=] ( ) -> bool {

							glm::vec2 pos = glm::vec2(nodeLF.positionTS.x + x, nodeLF.positionTS.y + y);

							for(AStarNode asn : closedList)
								if(asn.positionTS.x == pos.x && asn.positionTS.y == pos.y)
									return true;

							return false;

						};

						auto verifOpenList = [=] (int& i2) -> bool {

							glm::vec2 pos = glm::vec2(nodeLF.positionTS.x + x, nodeLF.positionTS.y + y);

							for(int i = 0; i < openList.size( ); i++)
								if(openList[i].positionTS.x == pos.x && openList[i].positionTS.y == pos.y) {
									i2 = i;
									return true;
								}

							return false;

						};

						if(!verifClosedList( )) {

							int i2;

							if(verifOpenList(i2)) {

								if(openList[i2].G > nodeLF.G + 10.0f) {

									openList[i2].parent = new AStarNode(closedList[closedList.size( ) - 1]);

									aStarNodeVectorToDeallocate.push_back(openList[i2].parent);

									openList[i2].calculateG( );
									openList[i2].calculateH(destinyTS);
									openList[i2].calculateF( );

								}

							}
							else {

								AStarNode adjNode;

								adjNode.positionTS = glm::vec2(nodeLF.positionTS.x + x, nodeLF.positionTS.y + y);
								adjNode.parent = new AStarNode(closedList[closedList.size( ) - 1]);

								aStarNodeVectorToDeallocate.push_back(adjNode.parent);

								adjNode.calculateG( );
								adjNode.calculateH(destinyTS);
								adjNode.calculateF( );

								openList.push_back(adjNode);

							}

						}

					}

			} while(++i < 4);

		} while(!(closedList[closedList.size( ) - 1].positionTS.x == destinyTS.x && closedList[closedList.size( ) - 1].positionTS.y == destinyTS.y));


		AStarNode eachNode = closedList[closedList.size( ) - 1];

		std::vector<AStarNode> nodes;

		while(!(eachNode.positionTS.x == aNode.positionTS.x && eachNode.positionTS.y == aNode.positionTS.y)) {
			nodes.insert(nodes.begin( ), eachNode);
			eachNode = *eachNode.parent;
		}

		nodes.insert(nodes.begin( ), aNode);

		std::queue<Passo> seqDePassos;

		for(int i = 1; i < nodes.size( ); i++) {

			DirMovement dirMovement;

			if(nodes[i - 1].positionTS.x < nodes[i].positionTS.x && nodes[i - 1].positionTS.y == nodes[i].positionTS.y)
				dirMovement = DirMovement::RIGHT;
			else if(nodes[i - 1].positionTS.x > nodes[i].positionTS.x && nodes[i - 1].positionTS.y == nodes[i].positionTS.y)
				dirMovement = DirMovement::LEFT;
			else if(nodes[i - 1].positionTS.x == nodes[i].positionTS.x && nodes[i - 1].positionTS.y < nodes[i].positionTS.y)
				dirMovement = DirMovement::DOWN;
			else if(nodes[i - 1].positionTS.x == nodes[i].positionTS.x && nodes[i - 1].positionTS.y > nodes[i].positionTS.y)
				dirMovement = DirMovement::UP;

			seqDePassos.push(Passo(nodes[i].positionTS, dirMovement));

		}

		for(int i = 0; i < aStarNodeVectorToDeallocate.size( ); i++)
			delete aStarNodeVectorToDeallocate[i];

		return seqDePassos;

	}

}
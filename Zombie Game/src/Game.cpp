#include "../include/Game.h"

GameState Game::state = GameState::GAME_ACTIVE;

int widthScreen = 800;
int heightScreen = 600;

Engine::Engine Game::engine = Engine::Engine(Game::setup, Game::update, Game::draw, Game::input, "Zombie Game", widthScreen, heightScreen);
Engine::Camera Game::camera = Engine::Camera(widthScreen, heightScreen, 0.0f, 0.0f);

Engine::SpriteRenderer* renderer;

Engine::TextMap* textMap;

Mike* player_mike;

std::vector<Human> listOfHumans;

std::vector<Beam> listOfBeams;

void Game::input( ) {

	if(state == GameState::GAME_ACTIVE) {

		player_mike->input(textMap, camera, listOfBeams);

	}

}

void Game::setup( ) {

	srand(static_cast<unsigned int>(time(NULL)));

	Engine::ResourceManager::loadShader(PROJECTDIR"shaders\\basic_shader.vert", PROJECTDIR"shaders\\basic_shader.frag", "Basic_shader");

	Engine::ResourceManager::loadTexture(PROJECTDIR"Data\\Brick_Block_40x40_BL.png", GL_FALSE, "Brick_Block");
	Engine::ResourceManager::loadTexture(PROJECTDIR"Data\\ground_40x40_BL.jpg", GL_FALSE, "Ground");

	Engine::ResourceManager::loadTexture(PROJECTDIR"Data\\Mike_SpriteSheet.png", GL_TRUE, "Mike");
	Engine::ResourceManager::loadTexture(PROJECTDIR"Data\\Beam.png", GL_TRUE, "Beam");
	Engine::ResourceManager::loadTexture(PROJECTDIR"Data\\Exp_SpriteSheet.png", GL_TRUE, "Beam_Exp");

	Engine::ResourceManager::loadTexture(PROJECTDIR"Data\\Humans\\Human_SpriteSheet_BL_0.png", GL_TRUE, "Human_0");

	Engine::ResourceManager::getShader("Basic_shader").use( ).setInteger("image", 0);

	camera.init(Engine::ResourceManager::getShader("Basic_shader").getProgramID( ));

	renderer = new Engine::SpriteRenderer(Engine::ResourceManager::getShader("Basic_shader"));

	textMap = new Engine::TextMap(PROJECTDIR"Data\\map.txt", widthScreen, heightScreen);

	textMap->textures.push_back(Engine::ResourceManager::getTexture("Ground"));
	textMap->textures.push_back(Engine::ResourceManager::getTexture("Brick_Block"));

	textMap->fileStringMod[10 + 7 * textMap->quantHorizontalTiles] = 'P';

	player_mike = new Mike(Engine::ResourceManager::getTexture("Mike"), glm::vec2(0, 0), glm::vec2(40, 40));

	player_mike->positionTextMap = glm::vec2(10, 7);
	player_mike->position = textMap->textMapPosToWorldPos(glm::vec2(player_mike->positionTextMap.x, player_mike->positionTextMap.y), glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));
	player_mike->dirMovement = DirMovement::DOWN;

	player_mike->spriteSheet.modifyTexCoord( );

	std::vector<glm::vec2> listOfTilesAvailable;

	/*Obtem as posições disponiveis para spawnar os humanos e guarda essas posições em listTilesAvailable*/
	for(int y = 0; y < textMap->quantVerticalTiles; y++) 
		for(int x = 0; x < textMap->quantHorizontalTiles; x++) 
			if(textMap->fileStringMod[x + y * textMap->quantHorizontalTiles] == '0')
				listOfTilesAvailable.push_back(glm::vec2(x, y));

	for(int i = 0; i < 1;/*No futuro mudar para 4 humanos*/i++) {

		//int k = ; //1 porque atualmente só tem 1 spritesheet
		//char c = k + '0';

		std::stringstream ss;
		ss << "Human_";
		ss << rand( ) % 1;

		Human human(Engine::ResourceManager::getTexture(ss.str()), glm::vec2(0, 0), glm::vec2(40, 40));

		glm::vec2 p = listOfTilesAvailable[rand( ) % listOfTilesAvailable.size( )];

		textMap->fileStringMod[p.x + p.y * textMap->quantHorizontalTiles] = 'H';

		human.positionTextMap = p;
		human.position = textMap->textMapPosToWorldPos(glm::vec2(p.x, p.y), glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));
		human.dirMovement = DirMovement::DOWN;

		listOfHumans.push_back(human);

	}

}

void Game::update( ) {

	player_mike->update(engine.timeHandler.deltaTime);

	for(int i = 0; i < listOfBeams.size( ); i++) {

		listOfBeams[i].update(engine.timeHandler.deltaTime, camera, textMap);

		if(listOfBeams[i].deleteMe)
			listOfBeams.erase(listOfBeams.begin() + i);

	}

	for(int i = 0; i < listOfHumans.size( ); i++) {

		listOfHumans[i].update(textMap, camera, engine.timeHandler.deltaTime);

	}

}

void Game::draw( ) {

	textMap->draw(*renderer);

	//Se a direção for Up desenha o player após os beams
	if(player_mike->dirMovement == DirMovement::UP) {

		for(Beam& beam : listOfBeams)
			beam.draw(glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

		player_mike->draw(glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));
	
	}
	else {

		player_mike->draw(glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

		for(Beam& beam : listOfBeams)
			beam.draw(glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

	}

	for(Human& human : listOfHumans)
		human.draw(glm::vec3(camera.camPosX, camera.camPosY, camera.camScale), glm::vec2(camera.widthScreen, camera.heightScreen));

	//std::cout << listOfBeams.size( ) << std::endl;

}
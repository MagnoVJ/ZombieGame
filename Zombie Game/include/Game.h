#pragma once

#include "Mike.h"
#include "Beam.h"
#include "Human.h"

#include <Engine_inc_all.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <time.h>
#include <string>
#include <iostream>

enum GameState {
	GAME_ACTIVE
};

class Game {

public:

	static Engine::Engine engine;
	static Engine::Camera camera;

	static GameState state;

	static void setup( );
	static void update( );
	static void draw( );

	static void input( );

};
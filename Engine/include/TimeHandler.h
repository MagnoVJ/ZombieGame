#pragma once

#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <thread>

namespace Engine {

	using namespace std::chrono_literals;

	class Time {

	private: 
		static int frames;
		static int lastFrameAmount;
		static double lestGameTime;

	public:

		static double deltaTime;
		static double lastFrame;

		Time();
		~Time();

		static void calcDeltaTime();
		static void drawFPS();

	};

}
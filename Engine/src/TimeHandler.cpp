#include "../include/TimeHandler.h"

namespace Engine {

	double Time::deltaTime = 0.0;
	double Time::lastFrame = 0.0;

	int Time::frames = 0;
	int Time::lastFrameAmount = 0;
	double Time::lestGameTime = 0;

	Time::Time() { }

	Time::~Time() { }

	void Time::calcDeltaTime() {
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	void Time::drawFPS( ) {

		double getTime = glfwGetTime( );

		frames++;

		if(getTime - lestGameTime > 1.0) {
			lestGameTime = getTime;
			lastFrameAmount = frames;
			frames = 0;
		}

		std::cout << lastFrameAmount << std::endl;

	}

}
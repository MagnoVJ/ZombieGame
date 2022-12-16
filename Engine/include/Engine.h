#pragma once

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TimeHandler.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <windows.h>
#include "wglext.h"

#include <string>
#include <iostream>

namespace Engine {

#define PROJECTDIR "C:\\Users\\MagnoVJ\\Documents\\Visual Studio 2015\\Projects\\Zombie Game\\Zombie Game\\"

	extern int globalScreenWidth;
	extern int globalScreenHeight;

	extern void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	extern GLboolean keys[1024];
	extern GLboolean keysProcessed[1024];

	extern GLdouble currXMousePos;
	extern GLdouble currYMousePos;

	extern GLboolean rightButtonMouse, rightButtonMouseProcessed;
	extern GLboolean leftButtonMouse, leftButtonMouseProcessed;
	extern GLboolean middleButtonMouse, middleButtonMouseProcessed;

	class Engine {

	private:
		GLFWwindow* window;

		std::string aplicationName;

		void init();
		void input();
		void draw();

		void(*ptrSetup)();
		void(*ptrUpdate)();
		void(*ptrDraw)();

		void(*ptrInput)();

		//Responsável por verificar se a extenção necessária para desativar/ativar vsinc é suportada pela placa de vídeo
		bool WGLExtensionSupported(const char *extension_name);

		//Ponteiros para utilizar enable/disable vsinc
		PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT;
		PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT;

	public:
		int screenWidth;
		int screenHeight;

		static Time timeHandler;

		Engine(void(*ptrSetup)(), void(*ptrUpdate)(), void(*ptrDraw)(), void(*ptrInput)(), std::string aplicationName, int screenWidth, int screenHeight);

		void run();

	};

}
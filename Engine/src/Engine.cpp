#include "../include/Engine.h"

namespace Engine {

	int globalScreenWidth;
	int globalScreenHeight;

	GLboolean keys[1024];
	GLboolean keysProcessed[1024];

	GLdouble currXMousePos;
	GLdouble currYMousePos;

	GLboolean rightButtonMouse, rightButtonMouseProcessed;
	GLboolean leftButtonMouse, leftButtonMouseProcessed;
	GLboolean middleButtonMouse, middleButtonMouseProcessed;

	Engine::Engine(void(*ptrSetup)(), void(*ptrUpdate)(), void(*ptrDraw)(), void(*ptrInput)(), std::string aplicationName, int screenWidth, int screenHeight) : aplicationName(aplicationName), screenWidth(screenWidth), screenHeight(screenHeight) {

		this->ptrSetup = ptrSetup;
		this->ptrUpdate = ptrUpdate;
		this->ptrDraw = ptrDraw;
		this->ptrInput = ptrInput;

		globalScreenWidth = this->screenWidth;
		globalScreenHeight = this->screenHeight;

		for(int i = 0; i < 1024; i++)
			keysProcessed[i] = GL_FALSE;

		rightButtonMouseProcessed = GL_FALSE;
		leftButtonMouseProcessed = GL_FALSE;
		middleButtonMouseProcessed = GL_FALSE;

	}

	void Engine::input() {

		ptrInput();

	}

	void Engine::init() {

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(screenWidth, screenHeight, aplicationName.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(window);

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);

		glewInit();

		//OpenGL configuration
		glewExperimental = GL_TRUE;

		glewInit();
		glGetError(); //catch glewInit() bug

		glViewport(0, 0, screenWidth, screenHeight);

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		if (WGLExtensionSupported("WGL_EXT_swap_control")) {
			// Extension is supported, init pointers.
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			// this is another function from WGL_EXT_swap_control extension
			wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
		}

		wglSwapIntervalEXT(1);

	}

	void Engine::run() {

		init();

		ptrSetup();

		while (!glfwWindowShouldClose(window)) {

			input( );

			ptrUpdate( );

			draw( );

			//timeHandler.drawFPS( );
			timeHandler.calcDeltaTime( );

		}

		glfwTerminate();

	}

	void Engine::draw() {

		glfwPollEvents();

		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ptrDraw();

		glfwSwapBuffers(window);

	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		if (key >= 0 && key < 1024) {
			if (action == GLFW_PRESS) 
				keys[key] = GL_TRUE;
			else if (action == GLFW_RELEASE) {
				keys[key] = GL_FALSE;
				keysProcessed[key] = GL_FALSE;
			}
		}

	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

		if (xpos > globalScreenWidth)
			xpos = globalScreenWidth;
		else if (xpos < 0)
			xpos = 0;

		if (ypos > globalScreenHeight)
			ypos = globalScreenHeight;
		else if (ypos < 0)
			ypos = 0;

		currXMousePos = xpos;
		currYMousePos = ypos;

	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
			leftButtonMouse = GL_TRUE;
		else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
			leftButtonMouse = GL_FALSE;
			leftButtonMouseProcessed = GL_FALSE;
		}

		if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
			rightButtonMouse = GL_TRUE;
		else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
			rightButtonMouse = GL_FALSE;
			rightButtonMouseProcessed = GL_FALSE;
		}

		if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
			middleButtonMouse = GL_TRUE;
		else if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
			middleButtonMouse = GL_FALSE;
			middleButtonMouseProcessed = GL_FALSE;
		}

	}

	bool Engine::WGLExtensionSupported(const char *extension_name) {
		// this is pointer to function which returns pointer to string with list of all wgl extensions
		PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

		// determine pointer to wglGetExtensionsStringEXT function
		_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

		if (strstr(_wglGetExtensionsStringEXT(), extension_name) == NULL) {
			// string was not found
			return false;
		}

		// extension is supported
		return true;
	}

}
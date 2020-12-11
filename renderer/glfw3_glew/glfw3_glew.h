#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <glew/glew.h>    // Initialize with glewInit()
#include <GLFW/glfw3.h>

//#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


extern GLFWwindow* mainWindow;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int test_state;


namespace glfw3_glew {


	//------------------------Debugging functions----------------------------------------
	void glfw_error_callback(int error, const char* description);

	void glClearError();

	bool glLogCall(const char* function, const char* file, int line);

	//------------------------------------------------------------------------------------------------

	static const char* glsl_version;

	//-----------------Main Functions--------------------------------------------------
	int Create_Main_Window();
	void Render();
	void Terminate();

}
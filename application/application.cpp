
#include "glfw3_glew\glfw3_glew.h"

#include <windows.h>

GLFWwindow* mainWindow = nullptr;
int SCREEN_WIDTH = 900;
int SCREEN_HEIGHT = 900;

int test_state = 0;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		test_state++;
		if (test_state > 10)
			test_state = 10;
		std::cout << "state: " << test_state << std::endl;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		test_state--;
		if (test_state < 0)
			test_state = 0;
		std::cout << "state: " << test_state << std::endl;
	}
}

void MainLoop() 
{

	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();
		glfw3_glew::Render();

	}
}


int main() {

	////---------------Set the console window size------------------------------
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 775, 800, TRUE); // 800 width, 100 height
	MoveWindow(console, 0, 0, 775, 800, TRUE);
	////---------------------------------------------------------------------------

	glfw3_glew::Create_Main_Window();
	
	glfwSetKeyCallback(mainWindow, key_callback);

    MainLoop();

    glfw3_glew::Terminate();
    return 0;
}

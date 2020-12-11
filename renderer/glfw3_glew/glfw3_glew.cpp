#include "glfw3_glew/glfw3_glew.h"
#include "Bezier.h"

#include <math.h>

//documentation opengl3:
// http://docs.gl/

//fast circle drawing algoritm
//http://slabode.exofire.net/circle_draw.shtml

////-----------Enable nvidia card
extern "C" {
#include <windows.h>
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

#include <stdio.h>                        // Header File For Standard Input/Output    ( ADD )
#include <stdarg.h>                       // Header File For Variable Argument Routines   ( ADD )

namespace glfw3_glew 
{

	static Bezier bezierCurve1;
	static Bezier bezierCurve2;

	//---debugging--------------------------------------------------------------
	void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	void glClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool glLogCall(const char* function, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			std::cout << "[OpenGL ERROR]: (" << error << "): " << function << " " << file << " " << line << std::endl;
			return false;
		}
		return true;
	}
	//---------------------------------------------------------------------------

	

	int Create_Main_Window()
	{
		// Setup window
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
			return 1;

		// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else

	// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		//---- let op: core profile is beter. maar compatible is makkelijker om lijnen te tekenen voor debug
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
		//glfwWindowHint(GLFW_DECORATED, false);

		glfwWindowHint(GLFW_SAMPLES, 4);

	// Create window with graphics context
		mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", NULL, NULL);
		glEnable(GL_MULTISAMPLE);

		if (mainWindow == NULL)
			return 1;
		glfwMakeContextCurrent(mainWindow);

		glfwSwapInterval(1); // Enable vsync

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

		//initialize glew
		bool err = glewInit() != GLEW_OK;
		if (err)
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			return 1;
		}
		std::cout << glGetString(GL_VERSION) << std::endl;

		//glfwMaximizeWindow(mainWindow);

		bezierCurve1.Points.emplace_back(Vector2{ 0.0f, 0.0f });
		bezierCurve1.Points.back().handleIn.Set(-10, -15);
		bezierCurve1.Points.back().handleOut.Set(10, 15);

		bezierCurve1.Points.emplace_back(Vector2{ 40, 50 });
		bezierCurve1.Points.back().handleIn.Set(20, -20);
		bezierCurve1.Points.back().handleOut.Set(60, 45);

		bezierCurve1.Points.emplace_back(Vector2{ 40, -50 });
		bezierCurve1.Points.back().handleIn.Set(40, 0);
		bezierCurve1.Points.back().handleOut.Set(20, -80);

		return 0;
	}

	//---------------------------the actual rendering-----------------------------------------------
	//----------------------------------------------------------------------------------------------

	void Terminate()
	{
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}

	/////////////////////////////////
	float x = 1;
	
	void Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		x -= 0.0001f;
		glScalef(x, x, x);
		glBegin(GL_TRIANGLES);

		glIndexi(1);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2i(1, 1);
		glIndexi(2);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2i(-1, -1);
		glIndexi(3);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(1, -1);

		glIndexi(4);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2i(1, 1);
		glIndexi(5);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2i(-1, -1);
		glIndexi(6);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(-1, 1);

		glEnd();
		glFlush();
		glfwSwapBuffers(mainWindow);
	}
}
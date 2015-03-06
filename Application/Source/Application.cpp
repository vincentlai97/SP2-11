#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "MyScene.h"
#include "StartMenu.h"
#include "WinMenu.h"
#include "LoseMenu.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void resize_callback (GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool Application::Mouse_Click(unsigned short button)
{
	return glfwGetMouseButton(m_window, button);
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	width = 1920;
	height = 1080;
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(width, height, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	glfwSetWindowSizeCallback(m_window, resize_callback);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	state = MAINMENU;
}

void Application::Run()
{
	//Main Loop
	Scene *scene[4];

	scene[0] = new MyScene();
	scene[0]->Init(m_window, width, height);

	scene[1] = new GameState();
	scene[1]->Init(m_window, width, height);

	scene[2] = new WinState();
	scene[2]->Init(m_window, width, height);

	scene[3] = new LoseState();
	scene[3]->Init(m_window, width, height);

	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		if (state == 0)
		{
			scene[0] = new MyScene();
			scene[0]->Init(m_window, width, height);
		}

		m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
		while (!IsKeyPressed('R') && !IsKeyPressed(VK_ESCAPE) && !glfwWindowShouldClose(m_window))
		{
			scene[state]->Update(m_timer.getElapsedTime(), m_window, width, height);
			scene[state]->Render();

			//Swap buffers
			glfwSwapBuffers(m_window);
			//Get and organize events, like keyboard and mouse input, window resizing, etc...
			glfwPollEvents();
			m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

			if (state != scene[state]->returnstate() && scene[state]->returnstate() == GAME)
			{
				state = scene[state]->returnstate();
				break;
			}
			state = scene[state]->returnstate();
			if (IsKeyPressed('R'))
			{
				state = MAINMENU;
			}
		} //Check if the ESC key had been pressed or if the window had been closed
	}
	scene[state]->Exit();
	delete scene[state];
}

int Application::getWidth()
{
	return width;
}

int Application::getHeight()
{
	return height;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

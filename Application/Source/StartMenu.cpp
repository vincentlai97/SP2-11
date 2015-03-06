#include "StartMenu.h"
#include "GL\glew.h"
#include "Application.h"
#include "Utility.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

#include "shader.hpp"

void GameState::Init(GLFWwindow* m_window, float w, float h)
{
	xPos = w / 2;
	yPos = h / 2;

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPos(m_window, xPos, yPos);

	//Set background color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.1) ;
    glEnable(GL_ALPHA_TEST) ;

	//Generate default VAO
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	glUseProgram(m_programID);

	//Start_Screen
	mesh = MeshBuilder::GenerateQuad("Start Screen", Color(1, 1, 1), 10, 10);
	mesh->textureID = LoadTGA("Image//Start_Screen.tga");
}

void GameState::Update(double dt, GLFWwindow* m_window, float w, float h)
{
	state = Application::MAINMENU;

	glfwGetCursorPos(m_window, &xPos, &yPos);
	xPosition = &xPos;
	yPosition = &yPos;
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if(Application::Mouse_Click(0))
	{
		if (*xPosition > 185 && *xPosition < 585 && *yPosition > 165 && *yPosition < 240)
		{
			state = Application::GAME;
			xPos = w / 2;
			yPos = h / 2;
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else if (*xPosition > 185 && *xPosition < 585 && *yPosition > 318 && *yPosition < 390)
		{
			xPos = w / 2;
			yPos = h / 2;
		}
		else if (*xPosition < 585 && *xPosition > 185 && *yPosition > 475 && *yPosition < 548)
		{
			exit(0); //Exit the game
		}
	}
}

void GameState::Render()
{	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render VBO here

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.LoadMatrix(ortho);
	viewStack.LoadIdentity();

	modelStack.PushMatrix();
	modelStack.Translate(40, 30, 0);
	modelStack.Scale(8, 6.5, 6.5);
	RenderMesh(mesh);
	modelStack.PopMatrix();
}

void GameState::RenderMesh(Mesh *mesh)
{
	Mtx44 modelView, modelView_inverse_transpose;

	load();
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	mesh->Render();

	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void GameState::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void GameState::load()
{
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
}

void GameState::reset()
{
	modelStack.LoadIdentity();
	load();
}
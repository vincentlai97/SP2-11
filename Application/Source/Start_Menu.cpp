#include "newScene.h"
#include "GL\glew.h"
#include "Utility.h"
#include "Application.h"

#include "shader.hpp"

void GameState::Start_Screen()
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();

	modelStack.PushMatrix();
	modelStack.Translate(40, 30, 0);
	modelStack.Scale(8, 6.5, 6.5);
	RenderMesh(meshList[startscreen], false);
	modelStack.PopMatrix();

	viewStack.PopMatrix();
	projectionStack.PopMatrix();

}
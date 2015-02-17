#include "SceneText.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <string.h>

#include "shader.hpp"

SceneText::SceneText()
{
}

SceneText::~SceneText()
{
}

void SceneText::Init(GLFWwindow* m_window, float w, float h)
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

	//Generate default VAO
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	glUseProgram(m_programID);

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 2;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	
	//skybox
	meshList[WALL] = MeshBuilder::GenerateQuad("wall", Color(1, 1, 1), 1.f, 1.f);
	meshList[WALL]->textureID = LoadTGA("Image//Wall.tga");
	meshList[TILE] = MeshBuilder::GenerateQuad("tile", Color(1, 1, 1), 1.f, 1.f);
	meshList[TILE]->textureID = LoadTGA("Image//Tile.tga");
	meshList[EXTFRONT] = MeshBuilder::GenerateQuad("Exterior Front Side", Color(1, 1, 1), 1.f, 1.f);
	meshList[EXTFRONT]->textureID = LoadTGA("Image//ExtFront.tga");
	meshList[EXTSIDE] = MeshBuilder::GenerateQuad("Exterior Side", Color(1, 1, 1), 1.f, 1.f);
	meshList[EXTSIDE]->textureID = LoadTGA("Image//ExtSide.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//skyfront.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//skyback.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//skytop.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skybottom.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//skyright.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//skyleft.tga");
	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//grass.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//cambria.tga");

	v.push_back(Vector3(400, 200, -300));
	v.push_back(Vector3(-400, 0, -320));
	v.push_back(Vector3(400, 200, 320));
	v.push_back(Vector3(-400, 0, 300));
	v.push_back(Vector3(400, 0, 300));
	v.push_back(Vector3(-400, -20, -300));
	v.push_back(Vector3(400, 220, 300));
	v.push_back(Vector3(-400, 200, -300));
	v.push_back(Vector3(-400, 200, 300));
	v.push_back(Vector3(-420, 0, -300));
	v.push_back(Vector3(420, 200, 300));
	v.push_back(Vector3(400, 0, -300));

	camera.Init(Vector3(0, 20, -50), Vector3(0, 0, 0), Vector3(0, 1, 0));
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f/3.f, 0.1f, 10000.0f); //FOV, Aspect Ration, Near plane, Far plane
	projectionStack.LoadMatrix(projection);
}

void SceneText::Update(double dt, GLFWwindow* m_window, float w, float h)
{
	glfwGetCursorPos(m_window, &xPos, &yPos);

	glfwSetCursorPos(m_window, w / 2, h / 2);
	
	const float LSPEED = 5.f;

	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if(Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	fps = 1.f / dt;
	camera.Update(dt, v, w / 2, h / 2, &xPos, &yPos);
}

void SceneText::Render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render VBO here

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	RenderMesh(meshList[GEO_AXES], false);

	RenderInterior();

	//Environment Front
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -2000);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	//Environment Back
	modelStack.PushMatrix();
	modelStack.Translate(0, 13.5, 2000);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	//Environment Top
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 2000.05, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	//Environment Bottom
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Translate(0, -1980, 0);
	modelStack.Rotate(90, -1, 0, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	//Environment Left
	modelStack.PushMatrix();
	modelStack.Translate(-2000, 30, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	//Environemtn Right
	modelStack.PushMatrix();
	modelStack.Translate(2000, 13, 0);
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	//Exterior Front
	modelStack.PushMatrix();
	modelStack.Translate(0, 100, 300);
	modelStack.Scale(800, 200, 500);
	RenderMesh(meshList[EXTFRONT], false);
	modelStack.PopMatrix();

	//Exterior Left
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 100, 400);
	modelStack.Scale(600, 200, 500);
	RenderMesh(meshList[EXTSIDE], false);
	modelStack.PopMatrix();

	//Exterior Right
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 100, 400);
	modelStack.Scale(600, 200, 500);
	RenderMesh(meshList[EXTSIDE], false);
	modelStack.PopMatrix();

	//Exterior Back
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 100, 300);
	modelStack.Scale(800, 200, 500);
	RenderMesh(meshList[EXTSIDE], false);
	modelStack.PopMatrix();

	//Environment Floor
	for(int i = 0; i <= 20; i++)
	{
		for(int a = 0; a < 20; a++)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, -1, 0);
			modelStack.Translate(i * 100 - 800, -20, a * 100 - 800);
			modelStack.Rotate(90, -1, 0, 0);
			modelStack.Scale(100, 100, 100);
			RenderMesh(meshList[GEO_FLOOR], false);
			modelStack.PopMatrix();
		}
	}

	std::string str = to_string(fps);
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + str, Color(0, 0, 0), 2, 30, 29.5);
}

void SceneText::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}


void SceneText::load()
{
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
}

void SceneText::reset()
{
	modelStack.LoadIdentity();
	load();
}

void SceneText::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 modelView, modelView_inverse_transpose;
	
	load();
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneText::RenderInterior()
{
	for (int count = 0; count < 2; count++)
	for (int countx = -20; countx < 20; countx++)
	{
		for (int countz = -15; countz < 15; countz++)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(countx * 20 + 10, 90 * count, countz * 20 + 10);
				modelStack.Rotate(90 + count * 180, -1, 0, 0);
				modelStack.Scale(20, 20, 20);

				if (!(countx > 13 && countz < -13 && count == 1))
				RenderMesh(meshList[TILE], false);
			} modelStack.PopMatrix();
		}
	}

	for (int count = 0; count < 2; count++)
	for (int countx = -20; countx < 20; countx++)
	{
		for (int countz = -15; countz < 15; countz++)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(countx * 20 + 10, 90 * count+ 110, countz * 20 + 10);
				modelStack.Rotate(90 + count * 180, -1, 0, 0);
				modelStack.Scale(20, 20, 20);
				
				if (!(countx > 13 && countz < -13 && count == 0))
				RenderMesh(meshList[TILE], false);
			} modelStack.PopMatrix();
		}
	}

	for (int count = -1; count < 2; count += 2)
	{
		for (int hor = -20; hor < 20; hor++)
		{
			for (int ver = 0; ver < 10; ver ++)
			{
				modelStack.PushMatrix(); {
					modelStack.Translate(hor * 20 + 10, ver * 20 + 10, 300 * count);
					modelStack.Rotate(90 + 90 * count, 0, 1, 0);
					modelStack.Scale(20, 20, 20);
					RenderMesh(meshList[WALL], false);
				} modelStack.PopMatrix();
			}
		}
	}
	for (int count = -1; count < 2; count += 2)
	{
		for (int hor = -15; hor < 15; hor++)
		{
			for (int ver = 0; ver < 10; ver ++)
			{
				modelStack.PushMatrix(); {
					modelStack.Translate(-400 * count, ver * 20 + 10, hor * 20 + 10);
					modelStack.Rotate(90 * count, 0, 1, 0);
					modelStack.Scale(20, 20, 20);
					RenderMesh(meshList[WALL], false);
				} modelStack.PopMatrix();
			}
		}
	}
}

void SceneText::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

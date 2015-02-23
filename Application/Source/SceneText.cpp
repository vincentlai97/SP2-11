#include "SceneText.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Object.h"
#include <string.h>
#include "CollisionBox.h"

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

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 60, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0.4;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	light[1].type = Light::LIGHT_DIRECTIONAL;
	light[1].position.Set(-600, 500, 1900);
	light[1].color.Set(1, 1, 1);
	light[1].power = 0.2;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);


	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//skybox
	meshList[INT_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//Interior Walls.obj");
	meshList[INT_WALL]->textureID = LoadTGA("Image//Wall.tga");
	meshList[INT_WALL]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[INT_WALL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[INT_WALL]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[INT_WALL]->material.kShininess = 3.f;

	meshList[INT_FLOOR] = MeshBuilder::GenerateOBJ("tile", "OBJ//Interior Tiles.obj");
	meshList[INT_FLOOR]->textureID = LoadTGA("Image//Tile.tga");
	meshList[INT_FLOOR]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[INT_FLOOR]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[INT_FLOOR]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[INT_FLOOR]->material.kShininess = 3.f;

	meshList[WHITE_GLASS] = MeshBuilder::GenerateOBJ("tile", "OBJ//White Glass.obj");
	meshList[WHITE_GLASS]->textureID = LoadTGA("Image//White Glass.tga");
	meshList[WHITE_GLASS]->material.kAmbient.Set(.8, .8, .8);
	meshList[WHITE_GLASS]->material.kDiffuse.Set(.6, .6, .6);
	meshList[WHITE_GLASS]->material.kSpecular.Set(.3, .3, .3);
	meshList[WHITE_GLASS]->material.kShininess = 5;

	meshList[ESCALATOR] = MeshBuilder::GenerateQuad("escalator", Color(0, 0, 0), 1.f, 1.f);
	meshList[ESCALATOR]->textureID = LoadTGA("Image//Travelator.tga");
	meshList[ESCALATOR]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ESCALATOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[ESCALATOR]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[ESCALATOR]->material.kShininess = 1.f;

	meshList[ELEVATOR] = MeshBuilder::GenerateOBJ("Elevator", "OBJ//Elevator.obj");
	meshList[ELEVATOR]->textureID = LoadTGA("Image//metal.tga");
	meshList[ELEVATOR]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ELEVATOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[ELEVATOR]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[ELEVATOR]->material.kShininess = 1.f;

	// Exterior
	meshList[EXT_WALL_BOT] = MeshBuilder::GenerateOBJ("extwallbot", "OBJ//Exterior Walls Bottom.obj");
	meshList[EXT_WALL_BOT]->textureID = LoadTGA("Image//White Wall.tga");

	meshList[EXT_WALL_MID] = MeshBuilder::GenerateOBJ("extwallbot", "OBJ//Exterior Walls Middle.obj");
	meshList[EXT_WALL_MID]->textureID = LoadTGA("Image//Black Wall.tga");

	meshList[EXT_WALL_TOP] = MeshBuilder::GenerateOBJ("extwallbot", "OBJ//Exterior Walls Top.obj");
	meshList[EXT_WALL_TOP]->textureID = LoadTGA("Image//Red Wall.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//skyfront.tga");
	meshList[GEO_FRONT]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[GEO_FRONT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_FRONT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_FRONT]->material.kShininess = 3.f;

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//skyback.tga");
	meshList[GEO_BACK]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[GEO_BACK]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BACK]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_BACK]->material.kShininess = 3.f;

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//skytop.tga");
	meshList[GEO_TOP]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[GEO_TOP]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_TOP]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_TOP]->material.kShininess = 3.f;

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skybottom.tga");
	meshList[GEO_BOTTOM]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[GEO_BOTTOM]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOTTOM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_BOTTOM]->material.kShininess = 3.f;

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//skyright.tga");
	meshList[GEO_LEFT]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[GEO_LEFT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_LEFT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_LEFT]->material.kShininess = 3.f;

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//skyleft.tga");
	meshList[GEO_RIGHT]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[GEO_RIGHT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_RIGHT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_RIGHT]->material.kShininess = 3.f;

	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//grass.tga");
	meshList[GEO_FLOOR]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[GEO_FLOOR]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_FLOOR]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_FLOOR]->material.kShininess = 3.f;

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//Door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//blueglass.tga");
	meshList[GEO_DOOR]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DOOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_DOOR]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DOOR]->material.kShininess = 10.f;

	meshList[eDoor] = MeshBuilder::GenerateOBJ("eDoor", "OBJ//Door.obj");
	meshList[eDoor]->textureID = LoadTGA("Image//metal.tga");
	meshList[eDoor]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoor]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[eDoor]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[eDoor]->material.kShininess = 3.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1,1,1), 36, 36, 1);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//cambria.tga");

	Object NewObj;

	//Trolley Obj
	meshList[trolley] = MeshBuilder::GenerateOBJ("Trolley", "OBJ//Trolley.obj");
	meshList[trolley]->textureID = LoadTGA("Image//Steeltexture.tga");
	NewObj.mesh = meshList[trolley];
	NewObj.Position = Vector3(-100, 0, 0);
	NewObj.Size = Vector3(3, 3, 3);
	NewObj.Name = "Trolley";
	obj.push_back(NewObj);
	meshList[trolley]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[trolley]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kShininess = 3.f;


	//Shelf Obj 1st Row
	meshList[shelf] = MeshBuilder::GenerateOBJ("Shelf", "OBJ//shelf.obj");
	meshList[shelf]->textureID = LoadTGA("Image//Steeltexture.tga");
	meshList[shelf]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[shelf]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[shelf]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[shelf]->material.kShininess = 5.f;
	NewObj.mesh = meshList[shelf];

	for (int pos = 250; pos > 100; pos -= 50)
	{

		NewObj.Position = Vector3(250, 0, pos);
		NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
		NewObj.PosMax = Vector3(290, 40, pos + 10);
		NewObj.PosMin = Vector3(210, 0, pos - 10);
		NewObj.Name = "Shelf";
		v.push_back(CollisionBox(NewObj.Position, Vector3(40, 40, 10), Vector3(-40, 0, -10)));
		obj.push_back(NewObj);
	}
	//Shelf Obj 2st Row
	for (int pos = 250; pos > 100; pos -= 50)
	{
		NewObj.Position = Vector3(100, 0, pos);
		NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
		NewObj.PosMax = Vector3(140, 40, pos + 10);
		NewObj.PosMin = Vector3(60, 0, pos - 10);
		NewObj.Name = "Shelf";
		v.push_back(CollisionBox(NewObj.Position, Vector3(40, 40, 10), Vector3(-40, 0, -10)));
		obj.push_back(NewObj);
	}
	//Can4 face side
	meshList[Can4] = MeshBuilder::GenerateOBJ("Can4", "OBJ//Can4.obj");
	meshList[Can4]->textureID = LoadTGA("Image//Can4.tga");
	meshList[Can4]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Can4]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Can4]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Can4]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Can4];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{	
			NewObj.Name = "Sausages";
			NewObj.Price = 2.00;
			NewObj.Position = Vector3(row, column, 255);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			obj.push_back(NewObj);		
		}
	}
	//Can4 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Name = "Sausages";
			NewObj.Price = 2.00;
			NewObj.Position = Vector3(row, column, 241);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			obj.push_back(NewObj);

		}
	}

	//Box 1 face side
	meshList[Box1] = MeshBuilder::GenerateOBJ("Box1", "OBJ//Box1.obj");
	meshList[Box1]->textureID = LoadTGA("Image//Box1.tga");
	meshList[Box1]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Box1]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Box1]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Box1]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Box1];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 205);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Zuku";
			NewObj.Price = 3.00;
			obj.push_back(NewObj);

		}
	}
	//Box 1 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 192);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Zuku";
			NewObj.Price = 3.00;
			obj.push_back(NewObj);

		}
	}


	//Box 2 face side
	meshList[Box2] = MeshBuilder::GenerateOBJ("Box2", "OBJ//Box2.obj");
	meshList[Box2]->textureID = LoadTGA("Image//Box2.tga");
	meshList[Box2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Box2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Box2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Box2]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Box2];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 156);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Doritos";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}
	//Box 2 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 141);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Doritos";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}

	//Box 3 face side
	meshList[Box3] = MeshBuilder::GenerateOBJ("Box3", "OBJ//Box3.obj");
	meshList[Box3]->textureID = LoadTGA("Image//Box3.tga");
	meshList[Box3]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Box3]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Box3]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Box3]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Box3];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 155);
			NewObj.Size = Vector3(0.5f, 0.5f, 0.5f);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Granola";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}
	//Box 3 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 141);
			NewObj.Size = Vector3(0.5f, 0.5f, 0.5f);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Granola";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}

	//Can3 face side
	meshList[Can3] = MeshBuilder::GenerateOBJ("Can3", "OBJ//Can.obj");
	meshList[Can3]->textureID = LoadTGA("Image//Can3.tga");
	meshList[Can3]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Can3]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Can3]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Can3]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Can3];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 205);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Fishy Tuna";
			NewObj.Price = 3.50;
			obj.push_back(NewObj);

		}
	}
	//Can3 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 191);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Fishy Tuna";
			NewObj.Price = 3.50;
			obj.push_back(NewObj);

		}
	}

	//Can2 face side
	meshList[Can2] = MeshBuilder::GenerateOBJ("Can2", "OBJ//Can.obj");
	meshList[Can2]->textureID = LoadTGA("Image//Can2.tga");
	meshList[Can2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Can2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Can2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Can2]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Can2];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 255);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = 90.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Dog Ham";
			NewObj.Price = 4.00;
			obj.push_back(NewObj);

		}
	}
	//Can2 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 241);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = -90.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Dog Ham";
			NewObj.Price = 4.00;
			obj.push_back(NewObj);

		}
	}

	//Display Circular cabinet
	meshList[DisplayCircular] = MeshBuilder::GenerateOBJ("DisplayCircular", "OBJ//DisplayCircular.obj");
	meshList[DisplayCircular]->textureID = LoadTGA("Image//DisplayCircular.tga");
	meshList[DisplayCircular]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[DisplayCircular]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[DisplayCircular]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[DisplayCircular]->material.kShininess = 5.f;
	NewObj.mesh = meshList[DisplayCircular];
	NewObj.Position = Vector3(0, 11, 0);
	NewObj.Size = Vector3(5, 5, 5);
	NewObj.rotation = 0.0f;
	NewObj.Rotation = Vector3(0, 1, 0);
	NewObj.Name = "Circular Cabinet";
	NewObj.Price = 0.00;
	obj.push_back(NewObj);
	
	//Interior Hitbox
	v.push_back(CollisionBox(Vector3(0, 80, -300.5), 800, 160, 1)); // Front
	v.push_back(CollisionBox(Vector3(0, 80, 300.5), 800, 160, 1)); // Back
	v.push_back(CollisionBox(Vector3(0, -0.5, 0), 800, 1, 600)); // Bottom
	v.push_back(CollisionBox(Vector3(0, 160.5, 0), 800, 1, 600)); // Top
	v.push_back(CollisionBox(Vector3(0, 80, 0), 800, 20, 600)); // Middle
	v.push_back(CollisionBox(Vector3(-400.5, 80, 0), 1, 160, 600)); // Left
	v.push_back(CollisionBox(Vector3(400.5, 80, 0), 1, 160, 600)); // Right

	//Elevator Hitbox
	v.push_back(CollisionBox(Vector3(-370, 32.5, 170), 50, 35, 10));
	//v.push_back(Vector3(-345, 50, 175)); //Down Left Front
	//v.push_back(Vector3(-395, 15, 165));
	
	v.push_back(CollisionBox(Vector3(-370, 32.5, 130), 50, 35, 10));
	//v.push_back(Vector3(-345, 50, 135)); //Down Right Front
	//v.push_back(Vector3(-395, 15, 125));

	v.push_back(CollisionBox(Vector3(-370, 112.5, 170), 50, 35, 10));
	//v.push_back(Vector3(-345, 150, 175)); //Up Left Front
	//v.push_back(Vector3(-395, 105, 165));
	
	v.push_back(CollisionBox(Vector3(-370, 112.5, 130), 50, 35, 10));
	//v.push_back(Vector3(-345, 150, 135)); //Up Right Front
	//v.push_back(Vector3(-395, 105, 125));

	elevatorUp.push_back(CollisionBox(Vector3(-370, 32.5, 150), Vector3(20, 17.5, 15), Vector3(-20, -17.5, -15)));
	//elevatorUp.push_back(Vector3(-350, 50, 165));
	//elevatorUp.push_back(Vector3(-395, 15, 135));
	
	elevatorDown.push_back(CollisionBox(Vector3(-370, 105, 150), Vector3(20, 5, 15), Vector3(-20, -5, -15)));
	//elevatorDown.push_back(Vector3(-350, 120, 165));
	//elevatorDown.push_back(Vector3(-395, 110, 135));

	//Escalator Hitbox
	v.push_back(CollisionBox(Vector3(-290, 45, 260), 140, 90, 80)); // Travelator
	v.push_back(CollisionBox(Vector3(-290, 45, 260), 160, 150, 20)); // Travelator Handle
	travelatorUp.push_back(CollisionBox(Vector3(-290, 45, 280), 150, 90, 20));
	travelatorDown.push_back(CollisionBox(Vector3(-295, 50, 240), 150, 90, 20));

	camera.Init(Vector3(0, 20, 50), Vector3(0, 0, 0), Vector3(0, 1, 0));
	cameraCollisionBox.set(Vector3(0, 20, 50), Vector3(5, 5, 5), Vector3(-5, -15, -5));
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f/3.f, 0.1f, 10000.0f); //FOV, Aspect Ration, Near plane, Far plane
	projectionStack.LoadMatrix(projection);
}

float OpenDoorR = 0;
float OpenDoorL = 0;

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

	if(Application::IsKeyPressed('Z'))
	{
		light[0].power = 0.4; 
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}

	if(Application::IsKeyPressed('X'))
	{
		light[0].power = 0; 
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}

	fps = 1.f / dt;

	if (cameraCollisionBox.checkCollision(travelatorUp))
	{
		camera.position.x -= 50 * dt;
		camera.target.x -= 50 * dt;
		camera.position.y += 31 * dt;
		camera.target.y += 31 * dt;
	}
	else if (cameraCollisionBox.checkCollision(travelatorDown))
	{
		camera.position.x += 50 * dt;
		camera.target.x += 50 * dt;
		camera.position.y -= 25 * dt;
		camera.target.y -= 25 * dt;
	}

	if(cameraCollisionBox.checkCollision(elevatorUp) && Application::IsKeyPressed(VK_UP))
	{
		camera.position.y = 120;
		camera.target.y = 120;
	}

	else if(cameraCollisionBox.checkCollision(elevatorDown) && Application::IsKeyPressed(VK_DOWN))
	{
		camera.position.y = 20;
		camera.target.y = 20;
	}

	//Door will open when person stand at entrance
	if(camera.position.z >= 295 && camera.position.z <= 400 && camera.position.x >= -70 && camera.position.x <= 70)
	{
		OpenDoorR += 120 * dt;
		OpenDoorL -= 120 * dt;

		if(OpenDoorR >= 70)
		{
			OpenDoorR -= 120 * dt;
		}
		if(OpenDoorL <= -70)
		{
			OpenDoorL += 120 * dt;
		}
	}

	else if(camera.position.z >= 250 && camera.position.z <= 300 && camera.position.x >= -70 && camera.position.x <= 70)
	{ 
		OpenDoorR += 120 * dt;
		OpenDoorL -= 120 * dt;
		if(OpenDoorR >= 70)
		{
			OpenDoorR -= 120 * dt;
		}

		if(OpenDoorL <= -70)
		{
			OpenDoorL += 120 * dt;
		}
	}

	else
	{
		OpenDoorR -= 120 * dt;
		OpenDoorL += 120 * dt;

		if(OpenDoorR <= -1)
		{
			OpenDoorR += 120 * dt;
		}

		if(OpenDoorL >= 1)
		{
			OpenDoorL -= 120 * dt;
		}
	}
	camera.Update(dt, cameraCollisionBox, v, w / 2, h / 2, &xPos, &yPos);
	cameraCollisionBox.Centre = camera.position;
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

	if(light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}

	else if(light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}

	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}


	if(light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace1 = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace1.x);
	}

	else if(light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);
		Vector3 spotDirection_cameraspace1 = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace1.x);
	}

	else
	{
		Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);
	}

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	
	//Objects
	for (int i = 0; i < obj.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(obj[i].Position.x, obj[i].Position.y, obj[i].Position.z);
		modelStack.Scale(obj[i].Size.x, obj[i].Size.y, obj[i].Size.z);
		modelStack.Rotate(obj[i].rotation, obj[i].Rotation.x, obj[i].Rotation.y, obj[i].Rotation.z);
		RenderMesh(obj[i].mesh, true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();

	RenderSkyBox();

	modelStack.PushMatrix();
	modelStack.Translate(OpenDoorL, 0, 0);
	modelStack.Translate(38, -5, 297);
	modelStack.Scale(11.7, 7, 2);
	RenderMesh(meshList[GEO_DOOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(OpenDoorR, 0, 0);
	modelStack.Translate(107, -5, 297);
	modelStack.Scale(11.7, 7, 2);
	RenderMesh(meshList[GEO_DOOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-354, -2, 115);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5.5, 4, 2);
	RenderMesh(meshList[eDoor], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-354, 88, 115);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5.5, 4, 2);
	RenderMesh(meshList[eDoor], false);
	modelStack.PopMatrix();

	RenderInterior();
	RenderExterior();
	RenderObjects();

	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + to_string(fps), Color(0, 0, 0), 2, 30, 29.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "X:" + to_string(camera.position.x), Color(0, 0, 0), 2, 1, 0.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y:" + to_string(camera.position.y), Color(0, 0, 0), 2, 1, 1.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z:" + to_string(camera.position.z), Color(0, 0, 0), 2, 1, 2.5);

	RenderTextOnScreen(meshList[GEO_TEXT], "TargetX:" + to_string(camera.target.x), Color(0, 0, 0), 2, 1, 3.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "TargetY:" + to_string(camera.target.y), Color(0, 0, 0), 2, 1, 4.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "TargetZ:" + to_string(camera.target.z), Color(0, 0, 0), 2, 1, 5.5);


	//Crosshair
	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 5, 8.5f, 6.5f);

	//Object information when camera position is close to object
	for (int i = 0; i < obj.size(); i++)
	{
		if ((camera.target.x < obj[i].Position.x + 1.5f) && (camera.target.x > obj[i].Position.x - 1.5f) && (camera.target.y < obj[i].Position.y + 5) && (camera.target.y > obj[i].Position.y - 5) && (camera.target.z < obj[i].Position.z + 10) && (camera.target.z > obj[i].Position.z - 10))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Name:" + obj[i].Name, Color(1, 1, 0), 3, 1, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Price:$" + to_price(obj[i].Price), Color(1, 1, 0), 3, 1, 14);
			RenderTextOnScreen(meshList[GEO_TEXT], "ObjPosX:" + to_string(obj[i].Position.x), Color(1, 0, 0), 3, 1, 16);
			RenderTextOnScreen(meshList[GEO_TEXT], "ObjPosY:" + to_string(obj[i].Position.y), Color(1, 0, 0), 3, 1, 17);
			RenderTextOnScreen(meshList[GEO_TEXT], "ObjPosz:" + to_string(obj[i].Position.z), Color(1, 0, 0), 3, 1, 18);
		}
	}

	modelStack.PushMatrix();
	modelStack.Translate(-220, 0, 260);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(float(90) - 32.735, -1, 0, 0);
	modelStack.Scale(80, 166.43, 0);
	modelStack.Translate(0, 0.5, 0);
	RenderMesh(meshList[ESCALATOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-374, 0, 150);
	modelStack.Scale(5, 6.5, 5);
	RenderMesh(meshList[ELEVATOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-374, 90, 150);
	modelStack.Scale(5, 6.5, 5);
	RenderMesh(meshList[ELEVATOR], true);
	modelStack.PopMatrix();

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

void SceneText::RenderInterior()
{
	modelStack.PushMatrix(); {
		modelStack.Scale(20, 20, 20);
		
		RenderMesh(meshList[INT_WALL], false);
		RenderMesh(meshList[INT_FLOOR], false);
		RenderMesh(meshList[WHITE_GLASS], false);
	} modelStack.PopMatrix();
}

void SceneText::RenderExterior()
{
	modelStack.PushMatrix(); {
		modelStack.Scale(20, 20, 20);

		for (int count = 0; count < 3; count++)
			RenderMesh(meshList[EXT_WALL + count], false);
	} modelStack.PopMatrix();
}

void SceneText::RenderSkyBox()
{
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

	//Environment Right
	modelStack.PushMatrix();
	modelStack.Translate(2000, 13, 0);
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	//Environment Floor
	for(int i = 0; i <= 20; i++)
	{
		for(int a = 0; a < 20; a++)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, -1, 0);
			modelStack.Translate(i * 100 - 800, -1, a * 100 - 800);
			modelStack.Rotate(90, -1, 0, 0);
			modelStack.Scale(100, 100, 100);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();
		}
	}
}

void SceneText::RenderObjects()
{
	for (int i = 0; i < obj.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(obj[i].Position.x, obj[i].Position.y, obj[i].Position.z);
		modelStack.Scale(obj[i].Size.x, obj[i].Size.y, obj[i].Size.z);
		modelStack.Rotate(obj[i].rotation, obj[i].Rotation.x, obj[i].Rotation.y, obj[i].Rotation.z);
		RenderMesh(obj[i].mesh, false);
		modelStack.PopMatrix();
	}
}

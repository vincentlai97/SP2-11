#include "SceneText.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Object.h"
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
	meshList[WALL] = MeshBuilder::GenerateQuad("wall", Color(1, 1, 1), 1.f, 1.f);
	meshList[WALL]->textureID = LoadTGA("Image//Wall.tga");
	meshList[WALL]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[WALL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[WALL]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[WALL]->material.kShininess = 3.f;

	meshList[TILE] = MeshBuilder::GenerateQuad("tile", Color(1, 1, 1), 1.f, 1.f);
	meshList[TILE]->textureID = LoadTGA("Image//Tile.tga");
	meshList[TILE]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[TILE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[TILE]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[TILE]->material.kShininess = 3.f;

	meshList[ESCALATOR] = MeshBuilder::GenerateQuad("escalator", Color(0, 0, 0), 1.f, 1.f);

	meshList[EXTFRONT] = MeshBuilder::GenerateQuad("Exterior Front Side", Color(1, 1, 1), 1.f, 1.f);
	meshList[EXTFRONT]->textureID = LoadTGA("Image//ExtFront.tga");
	meshList[EXTFRONT]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[EXTFRONT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[EXTFRONT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[EXTFRONT]->material.kShininess = 3.f;

	meshList[EXTSIDE] = MeshBuilder::GenerateQuad("Exterior Side", Color(1, 1, 1), 1.f, 1.f);
	meshList[EXTSIDE]->textureID = LoadTGA("Image//ExtSide.tga");
	meshList[EXTSIDE]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[EXTSIDE]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[EXTSIDE]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[EXTSIDE]->material.kShininess = 3.f;

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

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1,1,1), 36, 36, 1);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//cambria.tga");

	//Trolley Obj
	meshList[trolley] = MeshBuilder::GenerateOBJ("Trolley", "OBJ//Trolley.obj");
	meshList[trolley]->textureID = LoadTGA("Image//Steeltexture.tga");
	Object Trolley;
	Trolley.Position = Vector3(-100, 0, 0);
	Trolley.Size = Vector3(3, 3, 3);
	Trolley.ENUM = trolley;
	obj.push_back(Trolley);
	meshList[trolley]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[trolley]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kShininess = 3.f;


	//Shelf Obj 1st Row
	for (int pos = 250; pos > 100; pos -= 50)
	{
		meshList[shelf] = MeshBuilder::GenerateOBJ("Shelf", "OBJ//shelf.obj");
		meshList[shelf]->textureID = LoadTGA("Image//Steeltexture.tga");
		Object Shelf;
		Shelf.Position = Vector3(250, 0, pos);
		Shelf.Size = Vector3(3.5f, 3.5f, 3.5f);
		Shelf.ENUM = shelf;
		obj.push_back(Shelf);
		meshList[shelf]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		meshList[shelf]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[shelf]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		meshList[shelf]->material.kShininess = 5.f;
	}
	//Shelf Obj 2st Row
	for (int pos = 250; pos > 100; pos -= 50)
	{
		meshList[shelf] = MeshBuilder::GenerateOBJ("Shelf", "OBJ//shelf.obj");
		meshList[shelf]->textureID = LoadTGA("Image//Steeltexture.tga");
		Object Shelf;
		Shelf.Position = Vector3(100, 0, pos);
		Shelf.Size = Vector3(3.5f, 3.5f, 3.5f);
		Shelf.ENUM = shelf;
		obj.push_back(Shelf);
		meshList[shelf]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		meshList[shelf]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[shelf]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		meshList[shelf]->material.kShininess = 5.f;
	}
	//Can4 face side
	for (float column = 33, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			meshList[Can4] = MeshBuilder::GenerateOBJ("Can4", "OBJ//Can4.obj");
			meshList[Can4]->textureID = LoadTGA("Image//Can4.tga");
			Object CAN4;
			CAN4.Position = Vector3(row, column, 250);
			CAN4.Size = Vector3(3.5f, 3.5f, 3.5f);
			CAN4.ENUM = Can4;
			obj.push_back(CAN4);
			meshList[Can4]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
			meshList[Can4]->material.kDiffuse.Set(1.f, 1.f, 1.f);
			meshList[Can4]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
			meshList[Can4]->material.kShininess = 5.f;
		}
	}

	//Can4 back side
	for (float column = 33, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			meshList[Can4] = MeshBuilder::GenerateOBJ("Can4", "OBJ//Can4.obj");
			meshList[Can4]->textureID = LoadTGA("Image//Can4.tga");
			Object CAN4;
			CAN4.Position = Vector3(row, column, 245);
			CAN4.Size = Vector3(3.5f, 3.5f, 3.5f);
			CAN4.rotation = 180.0f;
			CAN4.Rotation = Vector3(0, 1, 0);
			CAN4.ENUM = Can4;
			obj.push_back(CAN4);
			meshList[Can4]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
			meshList[Can4]->material.kDiffuse.Set(1.f, 1.f, 1.f);
			meshList[Can4]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
			meshList[Can4]->material.kShininess = 5.f;
		}
	}

	//Box 1 face side
	for (float column = 33, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			meshList[Box1] = MeshBuilder::GenerateOBJ("Box1", "OBJ//Box1.obj");
			meshList[Box1]->textureID = LoadTGA("Image//Box1.tga");
			Object BOX1;
			BOX1.Position = Vector3(row, column, 200);
			BOX1.Size = Vector3(3.5f, 3.5f, 3.5f);
			//BOX1.rotation = 180.0f;
			//BOX1.Rotation = Vector3(0, 1, 0);
			BOX1.ENUM = Box1;
			obj.push_back(BOX1);
			meshList[Box1]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
			meshList[Box1]->material.kDiffuse.Set(1.f, 1.f, 1.f);
			meshList[Box1]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
			meshList[Box1]->material.kShininess = 5.f;
		}
	}
	//Box 1 back side
	for (float column = 33, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			meshList[Box1] = MeshBuilder::GenerateOBJ("Box1", "OBJ//Box1.obj");
			meshList[Box1]->textureID = LoadTGA("Image//Box1.tga");
			Object BOX1;
			BOX1.Position = Vector3(row, column, 195);
			BOX1.Size = Vector3(3.5f, 3.5f, 3.5f);
			BOX1.rotation = 180.0f;
			BOX1.Rotation = Vector3(0, 1, 0);
			BOX1.ENUM = Box1;
			obj.push_back(BOX1);
			meshList[Box1]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
			meshList[Box1]->material.kDiffuse.Set(1.f, 1.f, 1.f);
			meshList[Box1]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
			meshList[Box1]->material.kShininess = 5.f;
		}
	}


	//Box 1 face side
	for (float column = 33, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			meshList[Box2] = MeshBuilder::GenerateOBJ("Box2", "OBJ//Box2.obj");
			meshList[Box2]->textureID = LoadTGA("Image//Box2.tga");
			Object BOX2;
			BOX2.Position = Vector3(row, column, 150);
			BOX2.Size = Vector3(3.5f, 3.5f, 3.5f);
			BOX2.ENUM = Box2;
			obj.push_back(BOX2);
			meshList[Box2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
			meshList[Box2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
			meshList[Box2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
			meshList[Box2]->material.kShininess = 5.f;
		}
	}
	//Box 1 back side
	for (float column = 33, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 135; row += 5)
		{
			meshList[Box2] = MeshBuilder::GenerateOBJ("Box2", "OBJ//Box2.obj");
			meshList[Box2]->textureID = LoadTGA("Image//Box2.tga");
			Object BOX2;
			BOX2.Position = Vector3(row, column, 145);
			BOX2.Size = Vector3(3.5f, 3.5f, 3.5f);
			BOX2.rotation = 180.0f;
			BOX2.Rotation = Vector3(0, 1, 0);
			BOX2.ENUM = Box2;
			obj.push_back(BOX2);
			meshList[Box2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
			meshList[Box2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
			meshList[Box2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
			meshList[Box2]->material.kShininess = 5.f;
		}
	}

	
	//Interior Hitbox
	v.push_back(Vector3(400, 160, -300)); // front
	v.push_back(Vector3(-400, 0, -320));
	v.push_back(Vector3(400, 160, 320)); // back
	v.push_back(Vector3(-400, 0, 300));
	v.push_back(Vector3(400, 0, 300)); // bottom
	v.push_back(Vector3(-400, -20, -300));
	v.push_back(Vector3(400, 180, 300)); // top
	v.push_back(Vector3(-400, 160, -300));
	v.push_back(Vector3(-400, 160, 300)); // left
	v.push_back(Vector3(-420, 0, -300));
	v.push_back(Vector3(420, 160, 300)); // right
	v.push_back(Vector3(400, 0, -300));
	v.push_back(Vector3(400, 90, 300)); // middle
	v.push_back(Vector3(-400, 70, -300));

	//Escalator Hitbox
	v.push_back(Vector3(360, 90, -220));
	v.push_back(Vector3(220, 0, -300));
	escalatorUp.push_back(Vector3(360, 90, -260));
	escalatorUp.push_back(Vector3(210, 0, -300));
	escalatorDown.push_back(Vector3(360, 95, -220));
	escalatorDown.push_back(Vector3(220, 21, -260));

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

	if(Application::IsKeyPressed('Z')) //Turns eye light on
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
	if (camera.checkCollision(escalatorUp, Vector3(0, 0, 0)))
	{
		camera.position.x += 45 * dt;
		camera.position.y += 30 * dt;
		camera.target.x += 45 * dt;
		camera.target.y += 30 * dt;
		
	}
	else if (camera.checkCollision(escalatorDown, Vector3(0, 0, 0)))
	{
		camera.position.x -= 50 * dt;
		camera.position.y -= 30 * dt;
		camera.target.x -= 50 * dt;
		camera.target.y -= 30 * dt;
		
	}
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
		RenderMesh(meshList[obj[i].ENUM], false);
		RenderMesh(meshList[obj[i].ENUM], true);

		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();

	RenderInterior();

	
	modelStack.PushMatrix(); {
		modelStack.Translate(220, 0, -260);
		modelStack.Rotate(90, 0, -1, 0);
		modelStack.Rotate(float(90) - 32.735, -1, 0, 0);
		modelStack.Scale(80, 166.43, 0);
		modelStack.Translate(0, 0.5, 0);

		RenderMesh(meshList[ESCALATOR], false);
	} modelStack.PopMatrix();

	RenderExterior();

	RenderSkyBox();
	
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + to_string(fps), Color(0, 0, 0), 2, 30, 29.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "X:" + to_string(camera.position.x), Color(0, 0, 0), 2, 1, 0.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y:" + to_string(camera.position.y), Color(0, 0, 0), 2, 1, 1.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z:" + to_string(camera.position.z), Color(0, 0, 0), 2, 1, 2.5);

	//Crosshair
	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 5, 8.5f, 6.5f);
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

void SceneText::RenderInterior()
{
	// First floor Floor and Ceiling
	for (int count = 0; count < 2; count++)
	for (int countx = -20; countx < 20; countx++)
	{
		for (int countz = -15; countz < 15; countz++)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(countx * 20 + 10, 70 * count, countz * 20 + 10);
				modelStack.Rotate(90 + count * 180, -1, 0, 0);
				modelStack.Scale(20, 20, 20);

				if (!(countx > 10 && countx < 18 && countz < -11 && count == 1))
				RenderMesh(meshList[TILE], true);
			} modelStack.PopMatrix();
		}
	}
	
	// Second floor Floor and Ceiling
	for (int count = 0; count < 2; count++)
	for (int countx = -20; countx < 20; countx++)
	{
		for (int countz = -15; countz < 15; countz++)
		{
			modelStack.PushMatrix(); {
				modelStack.Translate(countx * 20 + 10, 70 * count + 90, countz * 20 + 10);
				modelStack.Rotate(90 + count * 180, -1, 0, 0);
				modelStack.Scale(20, 20, 20);
				
				if (!(countx > 10 && countx < 18 && countz < -11 && count == 0))
				RenderMesh(meshList[TILE], true);
			} modelStack.PopMatrix();
		}
	}

	// Front and Back
	for (int count = -1; count < 2; count += 2)
	{
		for (int hor = -20; hor < 20; hor++)
		{
			for (int ver = 0; ver < 8; ver ++)
			{
				modelStack.PushMatrix(); {
					modelStack.Translate(hor * 20 + 10, ver * 20 + 10, 300 * count);
					modelStack.Rotate(90 + 90 * count, 0, 1, 0);
					modelStack.Scale(20, 20, 20);
					RenderMesh(meshList[WALL], true);
				} modelStack.PopMatrix();
			}
		}
	}

	// Left and Right
	for (int count = -1; count < 2; count += 2)
	{
		for (int hor = -15; hor < 15; hor++)
		{
			for (int ver = 0; ver < 8; ver ++)
			{
				modelStack.PushMatrix(); {
					modelStack.Translate(-400 * count, ver * 20 + 10, hor * 20 + 10);
					modelStack.Rotate(90 * count, 0, 1, 0);
					modelStack.Scale(20, 20, 20);
					RenderMesh(meshList[WALL], true);
				} modelStack.PopMatrix();
			}
		}
	}
}

void SceneText::RenderExterior()
{
	//Exterior Front
	modelStack.PushMatrix();
	modelStack.Translate(0, 100, 300);
	modelStack.Scale(800, 200, 500);
	RenderMesh(meshList[EXTFRONT], true);
	modelStack.PopMatrix();

	//Exterior Left
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 100, 400);
	modelStack.Scale(600, 200, 500);
	RenderMesh(meshList[EXTSIDE], true);
	modelStack.PopMatrix();

	//Exterior Right
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 100, 400);
	modelStack.Scale(600, 200, 500);
	RenderMesh(meshList[EXTSIDE], true);
	modelStack.PopMatrix();

	//Exterior Back
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 100, 300);
	modelStack.Scale(800, 200, 500);
	RenderMesh(meshList[EXTSIDE], true);
	modelStack.PopMatrix();
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

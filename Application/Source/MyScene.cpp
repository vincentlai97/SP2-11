#include "MyScene.h"
#include "GL\glew.h"
#include "Application.h"
#include "Utility.h"

#include "shader.hpp"

MyScene::MyScene()
{
}

MyScene::~MyScene()
{
}

void MyScene::Init(GLFWwindow* m_window, float w, float h)
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

	//Item init
	itemList.push_back("Can10");
	itemList.push_back("Can9");
	itemList.push_back("Can8");
	itemList.push_back("Can7");
	itemList.push_back("Can6");
	itemList.push_back("Can5");
	itemList.push_back("Can4");
	itemList.push_back("Can3");
	itemList.push_back("Can2");
	itemList.push_back("Can1");

	//CheckList init
	srand(time(NULL));
	random_shuffle(itemList.begin(), itemList.end());
	for (int i = 0; i < itemList.size(); i++)
	{
		checkList.push_back(itemList[i]);
	}

	//RenderCheckList();

	LoadMesh();

	InitCollisionBox();

	buttonBuffer = 0;

	OpenDoorR = 0;
	OpenDoorL = 0;
	//Level 1 eDoor
	OpeneDoor = 0;
	CloseeDoor = 0;
	eDoorOpened = false;
	//Level 2 eDoor
	OpeneDoor2 = 0;
	CloseeDoor2 = 0;
	eDoorOpened2 = false;

	Path* path = new Path(Vector3(-90, 0, 30), Vector3(-90, 0, 70));
	ai.paths.push_back(path);
	path = new Path(Vector3(-90, 0, 70), Vector3(-210, 0, 70), Vector3(0, 0, -1));
	ai.paths.push_back(path);
	path = new Path(Vector3(-210, 0, 70), Vector3(-210, 0, 30));
	ai.paths.push_back(path);
	path = new Path(Vector3(-210, 0, 30), Vector3(-90, 0, 30), Vector3(0, 0, 1));
	ai.paths.push_back(path);

	ai.pos = Vector3(-210, 0, 50);
	ai.dir = Vector3(0, 0, 1);
	ai.path = ai.paths[2];
	ai.endofpath = false;

	camera.Init(Vector3(0, 20, 50), Vector3(0, 0, 0), Vector3(0, 1, 0));
	cameraCollisionBox.set(Vector3(0, 20, 50), Vector3(5, 5, 5), Vector3(-5, -15, -5));
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f/3.f, 0.1f, 10000.0f); //FOV, Aspect Ration, Near plane, Far plane
	projectionStack.LoadMatrix(projection);
}

void MyScene::Update(double dt, GLFWwindow* m_window, float w, float h)
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


	//Loop to find eDoorButton OBJ
	for (int i = 0; i < obj.size(); i++)
	{
		//Level 1 Elevator door open
		if ((obj[i]->name == "eDoorButton") && (camera.target.x < obj[i]->collisionBox.Centre.x + 30) && (camera.target.x > obj[i]->collisionBox.Centre.x - 30) && (camera.target.y < obj[i]->collisionBox.Centre.y + 25) && (camera.target.y > obj[i]->collisionBox.Centre.y - 5) && (camera.target.z < obj[i]->collisionBox.Centre.z + 20) && (camera.target.z > obj[i]->collisionBox.Centre.z - 20))
		{
			
			if (Application::Mouse_Click(0) && eDoorOpened == false)
			{
				eDoorOpened = true;
				v.pop_back();
			}
			if (eDoorOpened == true && OpeneDoor < 10)
			{
				OpeneDoor += float(12 * dt);	
			}
		}

		if ((obj[i]->name == "eDoorButton2") && (camera.target.x < obj[i]->collisionBox.Centre.x + 30) && (camera.target.x > obj[i]->collisionBox.Centre.x - 30) && (camera.target.y < obj[i]->collisionBox.Centre.y + 25) && (camera.target.y > obj[i]->collisionBox.Centre.y - 5) && (camera.target.z < obj[i]->collisionBox.Centre.z + 20) && (camera.target.z > obj[i]->collisionBox.Centre.z - 20))
		{
			if (Application::Mouse_Click(0) && eDoorOpened2 == false)
			{
				eDoorOpened2 = true;
				v.pop_back();
			}
			if (eDoorOpened2 == true && OpeneDoor2 < 10)
			{
				OpeneDoor2 += float(12 * dt);
			}
		}	Application::IsKeyPressed('E');
	}

	//Level 1 Elevator door close
	if (camera.position.x < -360 && camera.position.y < 42 && camera.position.z < 160 && camera.position.z > 140)
	{
		if (eDoorOpened)
			v.push_back(CollisionBox(Vector3(-350, 65, 150), 5, 150, 10));
		eDoorOpened = false;
		if (eDoorOpened == false && OpeneDoor > 0)
		{
			OpeneDoor -= float(12 * dt);
		}
	}

	//Level 2 Elevator door close
	if (camera.position.x < -360 && camera.position.y > 42 && camera.position.z < 160 && camera.position.z > 140)
	{
		if (eDoorOpened2)
			v.push_back(CollisionBox(Vector3(-350, 65, 150), 5, 150, 10));
		eDoorOpened2 = false;
		if (eDoorOpened2 == false && OpeneDoor2 > 0)
		{
			OpeneDoor2 -= float(12 * dt);
		}
	}

	//Level 1 eDoor Autoclose
	if (camera.position.x > -250 || camera.position.z < 100 && camera.position.y < 42)
	{
		if (eDoorOpened)
			v.push_back(CollisionBox(Vector3(-350, 65, 150), 5, 150, 10));
		eDoorOpened = false;
		if (eDoorOpened == false && OpeneDoor > 0)
		{
			OpeneDoor -= float(12 * dt);
		}
	}
	//Level 2 eDoor Autoclose
	if (camera.position.x > -250 || camera.position.z < 100 && camera.position.y > 42)
	{
		if (eDoorOpened2)
			v.push_back(CollisionBox(Vector3(-350, 65, 150), 5, 150, 10));
		eDoorOpened2 = false;
		if (eDoorOpened2 == false && OpeneDoor2 > 0)
		{
			OpeneDoor2 -= float(12 * dt);
		}
	}

	{
		Object* targeted = targetObject();
		if (!targeted->name.empty())
			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targeted->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targeted->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targeted->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targeted->getTaken() && inventory.size() < 10)
				{
					targeted->setTaken(true);
					inventory.push_back(targeted);
				}
				buttonBuffer = 0.5;
			}
	}

	updateAI(dt);

	camera.Update(dt, cameraCollisionBox, v, w / 2, h / 2, &xPos, &yPos);
	cameraCollisionBox.Centre = camera.position;

	if (buttonBuffer > 0) buttonBuffer -= dt;
}

void MyScene::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void MyScene::load()
{
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
}

void MyScene::reset()
{
	modelStack.LoadIdentity();
	load();
}
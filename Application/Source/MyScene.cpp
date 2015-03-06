#include "MyScene.h"
#include "GL\glew.h"
#include "Application.h"
#include "Utility.h"
#include <fstream>

#include "shader.hpp"

MyScene::MyScene()
{
}

MyScene::~MyScene()
{
}

void MyScene::Init(GLFWwindow* m_window, float w, float h)
{
	//Gamestates for menu screens
	//stages gameState = START_SCREEN;

	xPos = w / 2;
	yPos = h / 2;

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPos(m_window, xPos, yPos);

	//Run Music Background and Sound effects
	InitSound();

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
	//Player name input
	PlayerName = "<UNDEFINED>";
	insert = false;
	insertBuffer = 0;
	eraseBuffer = 0;
	PNameBuffer = 0;
	//Init AI dialogue
	insert = false;
	talk = false;
	talkBuffer = 0;
	insertBuffer = 0;
	letterBuffer = 0;
	insertL = false;
	PlayerName = "<UNDEFINED>";

	ifstream msg;
	string dia;

	msg.open("Source//AIDialogue.txt");
	while (!msg.eof())
	{
		getline(msg, dia);
		message.push_back(dia);
	}
	msg.close();


	//Loading of obj names from text file
	ifstream Name;
	string Temp;

	Name.open("Source//Name.txt");
	while (!Name.eof())
	{
		getline(Name, Temp);
		temp.push_back(Temp);
	}
	Name.close();

	//Itemlist init
	for (int i = 0; i < temp.size(); i++)
	{
		const char* tempy = temp[i].c_str();
		itemList.push_back(tempy);
	}
	//CheckList init
	checklistout = false;
	srand(time(NULL));
	random_shuffle(itemList.begin(), itemList.end());
	for (int i = 0; i < 1 && i < itemList.size(); i++)
	{
		checkList.push_back(itemList[i]);
	}

	//Payment Init
	srand(time(NULL));
	random_shuffle(itemList.begin(), itemList.end());
	for(int i = 0; i < 5 && i < itemList.size(); i++)
	{
		paymentList.push_back(itemList[i]);
	}

	LoadMesh();

	InitCollisionBox();

	InitShelfPaths();

	InitAICharacters(shelfCharacters, shelfCharactersCollisionBox, shelfpaths, 3);
	v.insert(v.end(), shelfCharactersCollisionBox.begin(), shelfCharactersCollisionBox.end());
	shelfCharactersCollisionBox.push_back(&cameraCollisionBox);
	
	InitFruitstandPaths();

	InitAICharacters(fruitstandCharacters, fruitstandCharactersCollisionBox, fruitstandpaths, 3);
	v.insert(v.end(), fruitstandCharactersCollisionBox.begin(), fruitstandCharactersCollisionBox.end());
	fruitstandCharactersCollisionBox.push_back(&cameraCollisionBox);

	InitGuardPaths();

	InitAICharacters(guards, guardsCollisionBox, guardspaths, 1);
	guardsCollisionBox.insert(guardsCollisionBox.end(), shelfCharactersCollisionBox.begin(), shelfCharactersCollisionBox.end());
	guardsCollisionBox.insert(guardsCollisionBox.end(), fruitstandCharactersCollisionBox.begin(), fruitstandCharactersCollisionBox.end());

	buttonBuffer = 0;
	checklistBuffer = 0;

	OpenDoorR = 0;
	OpenDoorL = 0;
	eDoorOpen = false;
	eDoorClosed = false;

	//Using the toilet
	SitDown = 0;
	ToiletUsed = false;
	TDoorOpen = false;

	
	soundJump = false;
	money = 100;
	win = false;
	busted = false;
	gameover = false;
	
	camera.Init(Vector3(0, 20, 50), Vector3(0, 0, 0), Vector3(0, 1, 0));
	cameraCollisionBox.set(Vector3(0, 20, 50), Vector3(5, 5, 5), Vector3(-5, -15, -5));
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f/3.f, 0.1f, 10000.0f); //FOV, Aspect Ration, Near plane, Far plane
	projectionStack.LoadMatrix(projection);

	state = 1;
}

void MyScene::Update(double dt, GLFWwindow* m_window, float w, float h)
{
	glfwGetCursorPos(m_window, &xPos, &yPos);

	glfwSetCursorPos(m_window, w / 2, h / 2);

	//Update the sound every frame
	UpdateSound(dt);

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


	InteractDoor(dt);

	InteractElevator(dt);
	InteractElevatorButton(dt);
	InteractElevatorDoor(dt);

	//Loop to use Toilet
	for (int i = 0; i < obj.size(); i++)
	{
		//Turn Camera around to face the door
		if ((obj[i]->name == "Toiletbowl") && (camera.target.x < obj[i]->collisionBox.Centre.x + 15) && (camera.target.x > obj[i]->collisionBox.Centre.x - 15) && (camera.target.y < obj[i]->collisionBox.Centre.y + 25) && (camera.target.y > obj[i]->collisionBox.Centre.y - 5) && (camera.target.z < obj[i]->collisionBox.Centre.z + 20) && (camera.target.z > obj[i]->collisionBox.Centre.z - 20))
		{
			if (Application::Mouse_Click(0) && ToiletUsed == false)
			{
				ToiletUsed = true;
				SitDown +=5;
			}

			if (ToiletUsed == true && SitDown <= 10)
			{
				camera.ToggleToilet = true;
				camera.target.z	+= 180;
				camera.target.y -= 10;
				camera.position.z == camera.target.z;
			}

			if (Application::IsKeyPressed('F') && ToiletUsed == true)
			{
				camera.ToggleToilet = false;
				ToiletUsed = false;
				camera.target.y += 10;
			}
		}
	}

	for (int i = 0; i < obj.size(); i++)
	{
	if ((obj[i]->name == "ToiletDoor") && (camera.target.x < obj[i]->collisionBox.Centre.x + 15) && (camera.target.x > obj[i]->collisionBox.Centre.x - 15) && (camera.target.y < obj[i]->collisionBox.Centre.y + 25) && (camera.target.y > obj[i]->collisionBox.Centre.y - 5) && (camera.target.z < obj[i]->collisionBox.Centre.z + 20) && (camera.target.z > obj[i]->collisionBox.Centre.z - 20))
		{
			if (Application::Mouse_Click(0) && TDoorOpen)
			{
				TDoorOpen = true;
				translateDoorX += 10 * dt;
			}

			if (Application::Mouse_Click(0) && TDoorOpen)
			{
				TDoorOpen = false;
			}
		}
	}

	//ShelfItems
	{
		int targeted = MyScene::targeted(shelfItemsCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = shelfItems[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	//GreenApple
	{
		int targeted = MyScene::targeted(AppleCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = Apple[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	//Strawberry Icecream
	{
		int targeted = MyScene::targeted(ICCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = IC[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	//FerreroRocher Objects
	{
		int targeted = MyScene::targeted(FRCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = FR[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	//Pizza Objects
	{
		int targeted = MyScene::targeted(pizzaCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = pizza[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	//Chips Objects
	{
		int targeted = MyScene::targeted(ChipsCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = Chips[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	//Sugar Objects
	{
		int targeted = MyScene::targeted(sugarCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = sugar[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	//Dre Objects
	{
		int targeted = MyScene::targeted(dreCollisionBox);
		if (targeted != -1)
		{
			Gettable* targetedObj = dre[targeted];

			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				if (targetedObj->getTaken() && inventory.size())
				{
					Vector3 temp;
					temp = inventory[0]->collisionBox.Centre;
					inventory[0]->collisionBox.Centre = targetedObj->collisionBox.Centre;
					inventory[0]->setTaken(false);
					targetedObj->collisionBox.Centre = temp;
					inventory.erase(inventory.begin());
				}
				else if (!targetedObj->getTaken() && inventory.size() < 10)
				{
					targetedObj->setTaken(true);
					inventory.push_back(targetedObj);
				}
				buttonBuffer = 0.5;
			}
		}
	}
	
	//AI Dialogue
	Application::IsKeyPressed(VK_RETURN);
	if (Application::Mouse_Click(0) && talkBuffer <= 0)
	{
		random_shuffle(dialogue.begin(), dialogue.end());
		for (int count = 0; count < shelfCharacters.size(); count++)
		{
			Character character(*shelfCharacters[count]);
			if (camera.position.x < character.pos.x + 20 && camera.position.x > character.pos.x - 20 && camera.position.z < character.pos.z + 20 && camera.position.z > character.pos.z - 20)
			{
				talk = !talk;
				talkBuffer = 0.5;
			}
		}
		for (int count = 0; count < fruitstandCharacters.size(); count++)
		{
			Character character(*fruitstandCharacters[count]);
			if (camera.position.x < character.pos.x + 20 && camera.position.x > character.pos.x - 20 && camera.position.z < character.pos.z + 20 && camera.position.z > character.pos.z - 20)
			{
				talk = !talk;
				talkBuffer = 0.5;
			}
		}
	}

	if (talk == true)
	{
		if (Application::IsKeyPressed(VK_RETURN) && answerBuffer <= 0)
		{
			insertL = !insertL;
			answerBuffer = 0.5;
			if (insertL == false)
			{
				Answer = "";
				for (int i = 0; i < LetterList.size(); i++)
				{
					Answer += LetterList[i];
				}
				LetterList.clear();
				talk = false;
			}
		}
		if (insertL == true && letterBuffer <= 0)
		{
			for (char letter = 'A'; letter < 'Z'; letter++)
			{
				if (Application::IsKeyPressed(letter))
				{
					LetterList.push_back(letter);
					letterBuffer = 0.2;
				}
			}
			if (Application::IsKeyPressed(VK_BACK) && LetterList.size() != 0 && eraseBuffer <= 0)
			{
				LetterList.erase(LetterList.begin() + LetterList.size() - 1);
				eraseBuffer = 0.2;
			}
		}
	}
	else
	{
		updateAI(dt);
	}
	//Player name input
	if (insert == false && talk == false)
	{
		//Don't update camera if user choses to input text
		camera.Update(dt, cameraCollisionBox, v, w / 2, h / 2, &xPos, &yPos);
		cameraCollisionBox.Centre = camera.position;
		if (Application::IsKeyPressed('P') && checklistBuffer <= 0)
		{
			checklistout = !checklistout;
			checklistBuffer = 0.5;
		}
	}
	if (Application::IsKeyPressed(VK_HOME) && insertBuffer <= 0)
	{
		insert = !insert;
		insertBuffer = 0.5;
		if (insert == false)
		{
			PlayerName = "";
			for (int i = 0; i < PNameList.size(); i++)
			{
				PlayerName += PNameList[i];
			}
			PNameList.clear();
		}
	}

	if (insert == true && PNameBuffer <= 0)
	{
		for (char letter = 'A'; letter < 'Z'; letter++)
		{
			if (Application::IsKeyPressed(letter))
			{
				PNameList.push_back(letter);
				PNameBuffer = 0.2;
			}
		}

		if (Application::IsKeyPressed(VK_BACK) && PNameList.size() != 0 && eraseBuffer <= 0)
		{
			PNameList.erase(PNameList.begin() + PNameList.size() - 1);
			eraseBuffer = 0.2;
		}
	}	

	{
		int targeted = MyScene::targeted(cashiersCollisionBox);
		if (targeted != -1)
		{
			if (Application::Mouse_Click(0) && buttonBuffer <= 0)
			{
				int count = 0;
				for (int i = 0; i < checkList.size(); i++)
				{
					for (int j = 0; j < inventory.size(); j++)
					{
						if (checkList[i] == inventory[j]->name)
						{
							count++;
							break;
						}
					}
				}
				if (count == checkList.size())
				{
					checkoutprice = 0;
					for (int count = 0; count < inventory.size(); count++)
					{
						checkoutprice += inventory[count]->getPrice();
					}
					if (money < checkoutprice) enoughmoney = false;
					else
					{
						inventory.clear();
						win = true;
						inventory.push_back(paperbag);
						checkList.clear();
					}
				}
				else completeInventory = false;
			}
		}
		else
		{
			checkoutprice = 0;
			completeInventory = true;
			enoughmoney = true;
		}
	}

	translateCarX += 50 * dt;

	if(translateCarX >= 1000)
	{
		translateCarX = -400;
	}

//Entering into cashier scenario
	for(int i = 0; i < obj.size(); i++)
	{
		if((obj[i]->name == "Cashier Table" && obj[i]->position == 4) && (camera.target.x < obj[i]->collisionBox.Centre.x + 15) && (camera.target.x > obj[i]->collisionBox.Centre.x - 15) && (camera.target.y < obj[i]->collisionBox.Centre.y + 25) && (camera.target.y > obj[i]->collisionBox.Centre.y - 5) && (camera.target.z < obj[i]->collisionBox.Centre.z + 20) && (camera.target.z > obj[i]->collisionBox.Centre.z - 20))
		{
			translateCustomerZ += 120 * dt;
			if(Application::Mouse_Click(0) && mouseBuffer < 0)
			{
				camera.Update(dt, cameraCollisionBox, v, w / 2, h / 2, &xPos, &yPos);
				cameraCollisionBox.Centre = camera.position;
				mouseBuffer += 0.5;
				cashierScene = true;
			}

			if(cashierScene == true)
			{
				camera.Init(Vector3(325, 15, 200), Vector3(0, 0, 150), Vector3(0, 1, 0));
				cashierScene = false;
			}

			else if(Application::IsKeyPressed('E')) // Exits cashier scenario
			{
				camera.Init(Vector3(335, 15, 200), Vector3(0, 0, 150), Vector3(0, 1, 0));
			}

			//Customer Movements
			if(translateCustomerZ >= 200)
			{
				translateCustomerZ = 200;
				customer = true;
				insertNum = true;
				paid = true;
			}

			/*if(insertNum == true)
			{
				if (Application::IsKeyPressed(VK_RETURN) && answerBuffer <= 0)
				{
					insertL = !insertL;
					answerBuffer = 0.5;
					if (insertL == false)
					{
						AnswerNum = "";
						for (int i = 0; i < NumList.size(); i++)
						{
							AnswerNum += NumList[i];
						}
						NumList.clear();
						insertNum = false;
					}
				}
				if (insertL == true && letterBuffer <= 0)
				{
					for (char letter = '0'; letter < '10'; letter++)
					{
						if (Application::IsKeyPressed(letter))
						{
							NumList.push_back(letter);
							letterBuffer = 0.2;
						}
					}
					if (Application::IsKeyPressed(VK_BACK) && NumList.size() != 0 && eraseBuffer <= 0)
					{
						NumList.erase(LetterList.begin() + NumList.size() - 1);
						eraseBuffer = 0.2;
					}
				}
			}*/
		}
	}
				if(Application::IsKeyPressed('T') && paid == true)
			{
				translateCustomerZ1 += 120 * dt;
			}

			if(paid == true && customer == true)
			{
				
			}
				if(translateCustomerZ1 >= 280)
				{
					translateCustomerZ1 = 160;
				}

	if (buttonBuffer > 0) buttonBuffer -= dt;
	if (checklistBuffer > 0) checklistBuffer -= dt;
	if (talkBuffer > 0) talkBuffer -= dt;
	if (insertBuffer > 0) insertBuffer -= dt;
	if (PNameBuffer > 0) PNameBuffer -= dt;
	if (PNumBuffer > 0) PNumBuffer -= dt;
	if (letterBuffer > 0) letterBuffer -= dt;
	if (eraseBuffer > 0) eraseBuffer -= dt;
	if (answerBuffer > 0) answerBuffer -= dt;
	if (mouseBuffer > 0) mouseBuffer -= dt;
	if (paidBuffer > 0) paidBuffer -= dt;

	if (win && targeted(car->collisionBox)) 
		if (Application::Mouse_Click(0)) state = 2;
}

void MyScene::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

	engine->drop();
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
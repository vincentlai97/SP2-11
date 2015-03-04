#ifndef MYSCENE_H
#define MYSCENE_H

#include <math.h>
#include "Mtx44.h"
#include "MatrixStack.h"
#include "MyMath.h"

#include "Scene.h"
#include "timer.h"
#include "Mesh.h"
#include "Light.h"
#include "Camera2.h"
#include "CameraFly.h"
#include "Object.h"
#include "Gettable.h"
#include "CollisionBox.h"
#include "Character.h"
#include "AICharacter.h"

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") 
using namespace irrklang;

#include <algorithm> //To random vectorlist content

class MyScene : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		INT_WALL,
		INT_FLOOR,
		WHITE_GLASS,
		EXT_WALL,
		EXT_WALL_BOT = EXT_WALL,
		EXT_WALL_MID,
		EXT_WALL_TOP,
		SKYBOX_TOP,
		SKYBOX_FRONT,
		SKYBOX_BACK,
		SKYBOX_LEFT,
		SKYBOX_RIGHT,
		SKYBOX_FLOOR,
		Building1,
		Building2,
		Building3,
		ELEVATOR,
		ESCALATOR,
		ESCALATOR_HANDLE,
		GEO_TEXT,
		GEO_DOOR,
		trolley,
		shelf,
		Toy_Shelves,
		TaC,
		Banner,
		ClothesRack,
		Cafeteria,
		CafeteriaCashier,
		Doorman,
		RestroomBack,
		RestroomLeft,
		RestroomRight,
		RestroomTop,
		Shelf_Items,
		Can1 = Shelf_Items,
		Can2,
		Can3,
		Can4,
		Box1,
		Box2,
		Box3,
		Cashier,
		Cashier_Head = Cashier,
		Cashier_Body,
		Cashier_Arm,
		Cashier_Leg,
		DisplayCircular,
		CashierTable,
		CheckList,
		Inventory,
		Selector,
		Coke,
		GEO_LIGHTBALL,
		Character_1,
		TEST,
		road,
		Car,
		Car2,
		Car3,
		Toiletbowl,
		Fridge, 
		Fruitstand,
		Pizza,
		IceCream,
		Chocolate,
		Detergent,
		AppleRed,
		AppleGreen,
		ToiletDoor,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	enum SOUND_TYPES
	{
		BG_MUSIC = 0,
		FOOTSTEPS,
		JUMP,
		OPENDOOR,
		REACH,
		SOUND_TOTAL,
	};

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL]; //Store handlers for uniform parameters
	unsigned sound_parameters[SOUND_TOTAL];
	Light light[2];
	void load();
	void reset();
	
	MS modelStack, viewStack, projectionStack;

	Camera2 camera;
	CollisionBox cameraCollisionBox;

	int gameState;

	float fps;
	float buttonBuffer;
	float checklistBuffer;
	float talkBuffer;
	float insertBuffer;
	float PNameBuffer;
	float letterBuffer;
	float eraseBuffer;
	float answerBuffer;
	string PlayerName;
	string Answer;

	double xPos;
	double yPos;
	
	float OpenDoorR;
	float OpenDoorL;
	bool eDoorOpen;
	bool eDoorClosed;
	bool testSound;

	float SitDown;
	float StandUp;
	bool ToiletUsed;

	bool checklistout;
	bool talk;
	bool insert;
	bool insertL;

	float translateCarX;

	std::vector<CollisionBox*> v;
	std::vector<CollisionBox> travelatorUp;
	std::vector<CollisionBox> travelatorDown;
	std::vector<CollisionBox> elevatorUp;
	std::vector<CollisionBox> elevatorDown;
	std::vector<CollisionBox> elevatorArea;
	std::vector<CollisionBox*> cashierArea;

	std::vector<Object*> obj;

	Object* eDoor1;
	Object* eDoor2;
	Object* eDoorButton1;
	Object* eDoorButton2;

	std::vector<Gettable*> shelfItems;
	std::vector<CollisionBox*> shelfItemsCollisionBox;
	std::vector<Gettable*> pizza;
	std::vector<CollisionBox*> pizzaCollisionBox;
	std::vector<Gettable*> chocolate;
	std::vector<CollisionBox*> chocolateCollisionBox;
	std::vector<Gettable*> detergent;
	std::vector<CollisionBox*> detergentCollisionBox;
	std::vector<Gettable*> RedApple;
	std::vector<CollisionBox*> RedAppleCollisionBox;
	std::vector<Gettable*> GreenApple;
	std::vector<CollisionBox*> GreenAppleCollisionBox;

	std::vector<Object*> inventory;
	std::vector<const char*> itemList;
	std::vector<const char*> checkList;

	std::vector<Path*> shelfpaths;
	std::vector<string> temp;
	std::vector<string> message;
	std::vector<string> dialogue;
	std::vector<char> PNameList;
	std::vector<char> LetterList;

	std::vector<Character*> cashiers;
	std::vector<CollisionBox*> cashiersCollisionBox;
	float checkoutprice;

	std::vector<Character*> shelfCharacters;
	std::vector<CollisionBox*> shelfCharactersCollisionBox;


	void LoadMesh();
	void LoadCansMesh();
	void LoadPizzaMesh();
	void LoadIceCreamMesh();
	void LoadChocolateMesh();
	void LoadDetergentMesh();
	void LoadAppleRedMesh();
	void LoadAppleGreenMesh();

	void InitCollisionBox();
	void InitShelfPaths();
	void InitAICharacters(std::vector<Character*>& character, std::vector<CollisionBox*>& characterCollisionBox, std::vector<Path*> paths, int num);
	int InitSound();

	void InteractDoor(double dt);
	void InteractElevator(double dt);
	void InteractElevatorButton(double dt);
	void InteractElevatorDoor(double dt);
	void updateAI(double dt);

	int targeted(const std::vector<CollisionBox*> v);
	bool targeted(const CollisionBox collisionBox);
	void takeShelfItems();
	
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderOnScreen();
	void RenderInterior();
	void RenderExterior();
	void RenderBuildings();
	void RenderSkyBox();
	void RenderObjects();
	void RenderCharacter(std::vector<Character*> characters);
	void RenderTargetDetails();
	void RenderInventory();
	void RenderRoad();
	void RenderCar();
	void RenderPCar();
	void RenderCheckList();
	
	void Start_Screen();
	void RenderScreens();

	ISoundEngine* engine;
	ISound* sound[SOUND_TOTAL];

public:
	MyScene();
	~MyScene();

	virtual void Init(GLFWwindow* m_window, float w, float h);
	virtual void Update(double dt, GLFWwindow* m_window, float w, float h);
	virtual void UpdateSound(double dt);
	virtual void Render();
	virtual void Exit();
};

#endif
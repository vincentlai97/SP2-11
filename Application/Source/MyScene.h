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
		FENCE,
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
		Basin,
		Fridge, 
		Fruitstand,
		Pizza,
		IceCream,
		Chocolate,
		Detergent,
		AppleRed,
		AppleGreen,
		FerreroRocher,
		LaysChips,
		Sugar,
		Dre,
		ShirtBlue,
		ShirtGreen,
		ShirtRed,
		ShirtYellow,
		PaymentList,
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
		PAID,
		OPENDOOR,
		REACH,
		SOUND_TOTAL,
	};

	enum ROLE {
		CUSTOMER,
		CASHIER,
		THIEF,
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
	bool lockCamera;

	int gameState;

	float fps;
	float buttonBuffer;
	float checklistBuffer;
	float talkBuffer;
	float insertBuffer;
	float PNameBuffer;
	float PNumBuffer;
	float letterBuffer;
	float eraseBuffer;
	float answerBuffer;
	float mouseBuffer;
	float paidBuffer;
	string PlayerName;
	string Answer;
	string AnswerNum;

	float money;
	float checkoutprice;
	bool completeInventory;
	bool enoughmoney;
	bool win;
	bool busted;
	int role;
	bool gameover;

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

	float OpenToilet;
	float CloseToilet;
	bool TDoorOpen;
	bool TDoorLocked;

	bool checklistout;
	bool talk;
	bool insert;
	bool insertL;

	float translateCarX;

	bool soundJump;
	bool soundTake;
	bool soundPaid;
	bool soundUpDown;
	bool up_down;
	
	float translateDoorX;

	std::vector<Character*> customer;
	bool paying;
	int rounds;

	std::vector<CollisionBox*> v;
	std::vector<CollisionBox> travelatorUp;
	std::vector<CollisionBox> travelatorDown;
	std::vector<CollisionBox*> cashierArea;

	std::vector<Object*> obj;

	Object* emptyCashier;

	Object* paperbag;

	Object* car;
	Object* T_Handle;

	Object* DoorL;
	Object* DoorR;
	CollisionBox doorArea;

	CollisionBox fenceArea;

	Object* eDoor1;
	Object* eDoor2;
	Object* eDoorButton1;
	Object* eDoorButton2;
	CollisionBox elevatorUp;
	CollisionBox elevatorDown;
	CollisionBox elevatorArea;

	std::vector<Gettable*> shelfItems;
	std::vector<CollisionBox*> shelfItemsCollisionBox;
	std::vector<Gettable*> pizza;
	std::vector<CollisionBox*> pizzaCollisionBox;
	std::vector<Gettable*> chocolate;
	std::vector<CollisionBox*> chocolateCollisionBox;
	std::vector<Gettable*> detergent;
	std::vector<CollisionBox*> detergentCollisionBox;
	std::vector<Gettable*> Apple;
	std::vector<CollisionBox*> AppleCollisionBox;
	std::vector<Gettable*> FR;
	std::vector<CollisionBox*> FRCollisionBox;
	std::vector<Gettable*> Chips;
	std::vector<CollisionBox*> ChipsCollisionBox;
	std::vector<Gettable*> sugar;
	std::vector<CollisionBox*> sugarCollisionBox;
	std::vector<Gettable*> dre;
	std::vector<CollisionBox*> dreCollisionBox;
	std::vector<Gettable*> IC;
	std::vector<CollisionBox*> ICCollisionBox;

	std::vector<Gettable*> Blue;
	std::vector<CollisionBox*> BlueCollisionBox;
	std::vector<Gettable*> Red;
	std::vector<CollisionBox*> RedCollisionBox;
	std::vector<Gettable*> Green;
	std::vector<CollisionBox*> GreenCollisionBox;
	std::vector<Gettable*> Yellow;
	std::vector<CollisionBox*> YellowCollisionBox;

	std::vector<Object*> inventory;
	std::vector<Object*> CustInventory;
	std::vector<const char*> itemList;
	std::vector<const char*> checkList;
	std::vector<const char*> paymentList;

	std::vector<string> name;
	std::vector<float> price;
	std::vector<string> message;
	std::vector<string> dialogue;
	std::vector<char> PNameList;
	std::vector<char> LetterList;
	std::vector<char> NumList;
	string ans;

	std::vector<Character*> cashiers;
	std::vector<CollisionBox*> cashiersCollisionBox;

	std::vector<Character*> guards;
	std::vector<CollisionBox*> guardsCollisionBox;
	std::vector<Path*> guardspaths;

	std::vector<Character*> shelfCharacters;
	std::vector<CollisionBox*> shelfCharactersCollisionBox;
	std::vector<Path*> shelfpaths;

	std::vector<Character*> fruitstandCharacters;
	std::vector<CollisionBox*> fruitstandCharactersCollisionBox;
	std::vector<Path*> fruitstandpaths;

	void InitCollisionBox();
	void InitShelfPaths();
	void InitFruitstandPaths();
	void InitGuardPaths();
	void InitGuardPaths(float xMax, float xMin, float zMax, float zMin);
	void InitAICharacters(std::vector<Character*>& character, std::vector<CollisionBox*>& characterCollisionBox, std::vector<Path*> paths, int num);
	int InitSound();

	void LoadMesh();

	void LoadDoorMesh();
	void LoadElevatorMesh();

	void LoadCansMesh();
	void LoadPizzaMesh();
	void LoadIceCreamMesh();
	void LoadChocolateMesh();
	void LoadDetergentMesh();
	void LoadAppleRedMesh();
	void LoadAppleGreenMesh();
	void LoadFRMesh();
	void LoadChipsMesh();
	void LoadSugarMesh();
	void LoadDreMesh();
	void LoadBlueMesh();
	void LoadRedMesh();
	void LoadGreenMesh();
	void LoadYellowMesh();

	void InteractDoor(double dt);

	void InteractElevator(double dt);
	void InteractElevatorButton(double dt);
	void InteractElevatorDoor(double dt);

	void UpdateAI(double dt);

	void UpdateRole();

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
	void RenderDoor();
	void RenderCharacter(std::vector<Character*> characters);
	void RenderTargetDetails();
	void RenderInventory();
	void RenderRoad();
	void RenderCar();
	void RenderPCar();
	void RenderCheckList();
	void RenderPList();
	void RenderPayment();

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

	bool getBusted() {return busted;};
};

#endif
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
		eDoor,
		eDoorStand,
		eDoorStand2,
		eDoorButton,
		eDoorButton2,
		trolley,
		shelf,
		Toy_Shelves,
		TaC,
		Banner,
		ClothesRack,
		Cafeteria,
		CafeteriaCashier,
		Doorman,
		Shelf_Items,
		Can1 = Shelf_Items,
		Can2,
		Can3,
		Can4,
		Box1,
		Box2,
		Box3,
		DisplayCircular,
		CashierTable,
		CheckList,
		Inventory,
		Selector,
		Coke,
		GEO_LIGHTBALL,
		TEST,
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

	enum stages
	{
		START_SCREEN = 0,
		OPTION_SCREEN,
		GAME_SCREEN,
		PAUSE_SCREEN,
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

	float fps;
	float buttonBuffer;
	float checklistBuffer;
	float talkBuffer;

	double xPos;
	double yPos;
	
	float OpenDoorR;
	float OpenDoorL;
	//Level 1 eDoor
	float OpeneDoor;
	float CloseeDoor;
	bool eDoorOpened;
	//Level 2 eDoor
	float OpeneDoor2;
	float CloseeDoor2;
	bool eDoorOpened2;
	bool testSound;

	bool checklistout;
	bool talk;

	std::vector<CollisionBox> v;
	std::vector<CollisionBox> travelatorUp;
	std::vector<CollisionBox> travelatorDown;
	std::vector<CollisionBox> elevatorUp;
	std::vector<CollisionBox> elevatorDown;
	std::vector<Object*> obj;
	std::vector<Object*> inventory;
	std::vector<const char*> itemList;
	std::vector<const char*> checkList;
	std::vector<Path*> shelfpaths;
	std::vector<string> temp;
	std::vector<string> message;
	std::vector<string> dialogue;

	AICharacter ai;

	void LoadMesh();
	void LoadCansMesh();

	void InitCollisionBox();
	void InitShelfPaths();
	int InitSound();

	void updateAI(double dt);

	Object* targetObject();
	
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderOnScreen();
	void RenderInterior();
	void RenderExterior();
	void RenderBuildings();
	void RenderSkyBox();
	void RenderObjects();
	void RenderCharacters();
	void RenderTargetDetails();
	void RenderInventory();

	void RenderCheckList();
	
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
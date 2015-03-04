#ifndef NEWSCENE_H
#define NEWSCENE_H

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
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Application.h"

class GameState : public Scene
{
	enum SCREENS
	{
		startscreen,
		optionscreen,
		choosescreen,
		TOTAL_SCREENS,
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

	enum stages
	{
		START_SCREEN = 0,
		OPTION_SCREEN,
		CHOOSE_SCREEN,
		GAMEPLAY,
		PAUSE_SCREEN,
		END_GAME,
		CREDIT
	};

private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	Mesh* meshList[TOTAL_SCREENS];
	unsigned m_parameters[U_TOTAL]; //Store handlers for uniform parameters
	Light light[2];

	int gameState;
	
	void Start_Screen();
	void Options_Screen();
	void Choose_Screen();
	void RenderScreens();
	void LoadMesh();

	void load();
	void reset();
	
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	
	MS modelStack, viewStack, projectionStack;

	Camera2 camera;
	CollisionBox cameraCollisionBox;
	
	double xPos;
	double yPos;

	double* xPosition;
	double* yPosition;

	float mouseBuffer;
	bool mouseBuff;

public:
	virtual void Init(GLFWwindow* m_window, float w, float h);
	virtual void Update(double dt, GLFWwindow* m_window, float w, float h);
	virtual void Render();
	virtual void Exit();

};

#endif
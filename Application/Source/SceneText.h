#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H
#include "Scene.h"
#include <math.h>
#include "Camera2.h"
#include "CameraFly.h"
#include "Camera2.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include "MyMath.h"
#include "Mesh.h"
#include "Light.h"
#include "Object.h"

class SceneText : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		WALL,
		TILE,
		WHITE_GLASS,
		EXT_WALL,
		EXT_WALL_BOT = EXT_WALL,
		EXT_WALL_MID,
		EXT_WALL_TOP,
		ELEVATOR,
		ESCALATOR,
		ESCALATOR_HANDLE,
		GEO_TEXT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_FLOOR,
		GEO_DOOR,
		eDoor,
		trolley,
		shelf,
		Can2,
		Can3,
		Can4,
		Box1,
		Box2,
		Box3,
		GEO_LIGHTBALL,
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


private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL]; //Store handlers for uniform parameters
	Light light[2];
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkyBox();
	void RenderInterior();
	void RenderExterior();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
public:
	SceneText();
	~SceneText();

	virtual void Init(GLFWwindow* m_window, float w, float h);
	virtual void Update(double dt, GLFWwindow* m_window, float w, float h);
	virtual void Render();
	virtual void Exit();

	MS modelStack, viewStack, projectionStack;

	Camera2 camera;
	CollisionBox cameraCollisionBox;

	void load();
	void reset();

	float fps;

	double xPos;
	double yPos;

	std::vector<CollisionBox> v;
	std::vector<CollisionBox> travelatorUp;
	std::vector<CollisionBox> travelatorDown;
	std::vector<Object> obj;
};

#endif
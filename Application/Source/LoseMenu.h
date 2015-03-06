#ifndef LOSINGSCENE_H
#define LOSINGSCENE_H

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
#include "MyScene.h"

class LoseState : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TOTAL,
	};


private:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	Mesh* mesh;
	unsigned m_parameters[U_TOTAL]; //Store handlers for uniform parameters

	void load();
	void reset();
	
	void RenderMesh(Mesh *mesh);
	
	MS modelStack, viewStack, projectionStack;

	double xPos;
	double yPos;

	double* xPosition;
	double* yPosition;
public:
	virtual void Init(GLFWwindow* m_window, float w, float h);
	virtual void Update(double dt, GLFWwindow* m_window, float w, float h);
	virtual void Render();
	virtual void Exit();
};

#endif
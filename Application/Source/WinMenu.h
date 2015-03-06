#ifndef WINNINGSCENE_H
#define WINNINGSCENE_H

#include "Scene.h"
#include "Mesh.h"
#include <math.h>
#include "Mtx44.h"
#include "MatrixStack.h"
#include "MyMath.h"

class WinState : public Scene
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
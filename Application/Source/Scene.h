#ifndef SCENE_H
#define SCENE_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class Scene
{
public:
	int state;
	Scene() {}
	~Scene() {}

	virtual void Init(GLFWwindow* m_window, float w, float h) = 0;
	virtual void Update(double dt, GLFWwindow* m_window, float w, float h) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	
	int returnstate() {return state;};
};

#endif
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

	static bool Mouse_Click(unsigned short button);

	int getWidth();
	int getHeight();
	int state;

private:
	int height;
	int width;

	//Declare a window object
	StopWatch m_timer;
};

#endif
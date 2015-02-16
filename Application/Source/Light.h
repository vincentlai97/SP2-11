#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;

public:
	Light()
	{position = (0, 0, 0); color = (0, 0, 0); power = 0.f; kC = 0.f; kL = 0.f; kQ = 0.f;}
	~Light() {}
};

#endif
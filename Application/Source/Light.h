#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	
	Position position;
	Color color;
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float power;
	float kC, kL, kQ;
	float cosCutoff;
	float cosInner;
	float exponent;

public:
	Light()
	{position = (0, 0, 0); color = (0, 0, 0); power = 0.f; kC = 0.f; kL = 0.f; kQ = 0.f;}
	~Light() {}
};

#endif
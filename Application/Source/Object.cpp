#include "Object.h"


Object::Object()
{
	mesh = 0;
	centre = Vector3(0,0,0);
	size = Vector3(1, 1, 1);
	angle = 0.0f;
	rotation= Vector3(1, 1, 1);
	posMax = (0, 0, 0);
	posMin = (0, 0, 0);
	name = "";
	position = 0;
	Price = 0;
}

Object::~Object()
{
}

void Object::Reset()
{
	mesh = 0;
	centre = Vector3(0,0,0);
	size = Vector3(1, 1, 1);
	angle = 0.0f;
	rotation= Vector3(1, 1, 1);
	posMax = (0, 0, 0);
	posMin = (0, 0, 0);
	name = "";
	position = 0;
}
#include "Object.h"


Object::Object()
{
	mesh = 0;
	collisionBox.set(Vector3(0, 0, 0), 0, 0, 0);
	size = Vector3(1, 1, 1);
	angle = 0.0f;
	rotation= Vector3(1, 1, 1);
	name = "";
	position = 0;
	price = 0;
}

Object::~Object()
{
}

void Object::Reset()
{
	mesh = 0;
	collisionBox.set(Vector3(0, 0, 0), 0, 0, 0);
	size = Vector3(1, 1, 1);
	angle = 0.0f;
	rotation= Vector3(1, 1, 1);
	name = "";
	position = 0;
	price = 0;
}
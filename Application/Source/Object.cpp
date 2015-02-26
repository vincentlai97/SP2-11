#include "Object.h"


Object::Object()
{
	mesh = 0;
	collisionBox.set(Vector3(0, 0, 0), 0, 0, 0);
	size = Vector3(1, 1, 1);
	angle = 0.0f;
	rotation= Vector3(1, 1, 1);
	name = "";
	position = -1;
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
	position = -1;
}

void Object::set(Object other)
{
	this->mesh = other.mesh;
	this->collisionBox = other.collisionBox;
	this->size = other.size;
	this->angle = other.angle;
	this->rotation = other.rotation;
	this->name = other.name;
	this->position = other.position;
}
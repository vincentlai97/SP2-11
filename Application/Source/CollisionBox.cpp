#include "CollisionBox.h"

CollisionBox::CollisionBox(void)
{
}

CollisionBox::CollisionBox(Vector3 Centre, Vector3 Max, Vector3 Min)
{
	this->Centre = Centre;
	this->Max = Max;
	this->Min = Min;
}

CollisionBox::CollisionBox(Vector3 Centre, float xLength, float yLength, float zLength)
{
	this->Centre = Centre;
	this->Max = Vector3(xLength/2, yLength/2, zLength/2);
	this->Min = Vector3(-xLength/2, -yLength/2, -zLength/2);
}

CollisionBox::~CollisionBox(void)
{
}

void CollisionBox::set(Vector3 Centre, Vector3 Max, Vector3 Min)
{
	this->Centre = Centre;
	this->Max = Max;
	this->Min = Min;
}

void CollisionBox::set(Vector3 Centre, float xLength, float yLength, float zLength)
{
	this->set(Centre, Vector3(xLength/2, yLength/2, zLength/2), Vector3(-xLength/2, -yLength/2, -zLength/2));
}

float CollisionBox::xMax()
{
	return Centre.x + Max.x;
}

float CollisionBox::yMax()
{
	return Centre.y + Max.y;
}

float CollisionBox::zMax()
{
	return Centre.z + Max.z;
}

float CollisionBox::xMin()
{
	return Centre.x + Min.x;
}

float CollisionBox::yMin()
{
	return Centre.y + Min.y;
}

float CollisionBox::zMin()
{
	return Centre.z + Min.z;
}

bool CollisionBox::checkCollision(CollisionBox v, Vector3 incr)
{
	if (xMax() + incr.x > v.xMin() && xMin() + incr.x < v.xMax())
	if (yMax() + incr.y > v.yMin() && yMin() + incr.y < v.yMax())
	if (zMax() + incr.z > v.zMin() && zMin() + incr.z < v.zMax())
	{
		return true;
	}
	return false;
}

bool CollisionBox::checkCollision(std::vector<CollisionBox> v, Vector3 incr)
{
	for (int count = 0; count < v.size(); count++)
	{
		if (CollisionBox::checkCollision(v[count], incr))
			return true;
	}
	return false;
}

bool CollisionBox::checkCollision(std::vector<CollisionBox*> v, Vector3 incr)
{
	for (int count = 0; count < v.size(); count++)
	{
		if (CollisionBox::checkCollision(*v[count], incr))
			return true;
	}
	return false;
}
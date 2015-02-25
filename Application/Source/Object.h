#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Mesh.h"
#include "CollisionBox.h"

using namespace std;

class Object
{
private:
public:
	Mesh* mesh;
	CollisionBox collisionBox;
	Vector3 size;
	float angle;
	Vector3 rotation;
	string name;
	int position;

	Object();
	~Object();
	void Reset();

	virtual bool isGettable() {return false;};
	virtual float getPrice() {return 0;};
	virtual bool getTaken() {return false;};
	virtual void setTaken(bool taken) {};
};
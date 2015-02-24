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
	float price;

	Object();
	~Object();
	void Reset();
};
#pragma once
#include <iostream>
#include <string>
#include "Vector3.h"
#include <vector>
#include "Mesh.h"

using namespace std;


class Object
{
	
private:
public:
	Mesh* mesh;
	Vector3 Position;
	Vector3 Size;
	float rotation;
	Vector3 Rotation;
	Vector3 PosMax;
	Vector3 PosMin;
	string Name;
	Object();
	~Object();
};

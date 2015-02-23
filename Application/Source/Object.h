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
	Vector3 centre;
	Vector3 size;
	float angle;
	Vector3 rotation;
	Vector3 posMax;
	Vector3 posMin;
	string name;
	int position;
	float price;

	Object();
	~Object();
	void Reset();
};
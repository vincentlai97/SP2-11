#pragma once
#include <iostream>
#include <string>
#include "Vector3.h"
#include <vector>



using namespace std;


class Object
{
	
private:
public:
	int ENUM;
	Vector3 Size;
	Vector3 Position;
	float rotation;
	Vector3 Rotation;
	Vector3 PosMax;
	Vector3 PosMin;
	Object();
	~Object();
};

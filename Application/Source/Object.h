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
	Object();
	~Object();
};

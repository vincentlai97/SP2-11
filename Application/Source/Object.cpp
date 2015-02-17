#include "Object.h"


Object::Object()
{
	Position = Vector3(0,0,0);
	Size = Vector3(1, 1, 1);
	rotation = 0.0f;
	Rotation= Vector3(1, 1, 1);

}



Object::~Object()
{
}

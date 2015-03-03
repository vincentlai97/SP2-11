#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <vector>

#include "Vector3.h"

class CollisionBox
{
private:
public:
	Vector3 Centre;
	Vector3 Max;
	Vector3 Min;

	CollisionBox(void);
	CollisionBox(Vector3 Centre, Vector3 Max, Vector3 Min);
	CollisionBox(Vector3 Centre, float xLength, float yLength, float zLength);
	~CollisionBox(void);
	void set(Vector3 Centre, Vector3 Max, Vector3 Min);
	void set(Vector3 Centre, float xLength, float yLength, float zLength);

	float xMax();
	float yMax();
	float zMax();
	float xMin();
	float yMin();
	float zMin();
	
	bool checkCollision(CollisionBox v, Vector3 incr = Vector3(0, 0, 0));
	bool checkCollision(std::vector<CollisionBox> v, Vector3 incr = Vector3(0, 0, 0));
	bool checkCollision(std::vector<CollisionBox*> v, Vector3 incr = Vector3(0, 0, 0));
};

#endif
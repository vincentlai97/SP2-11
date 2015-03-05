#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "Vector3.h"
#include "Mesh.h"
#include "CollisionBox.h"

class Character {
private:
public:
	enum BODYPARTS {
		HEAD,
		BODY,
		ARM,
		LEG,
	};
	std::vector<Mesh*> mesh;
	Vector3 pos;
	Vector3 lookdir;
	float angle;
	CollisionBox collisionBox;
	
	Character(void) {collisionBox = CollisionBox(pos, Vector3(4, 15, 4), Vector3(-4, 0, -4));};
	~Character(void) {};

	virtual void update(double dt, std::vector<CollisionBox*> collisionBox) {};
	virtual void track(double dt, std::vector<CollisionBox*> collisionBox, Vector3 dest) {};
};

#endif
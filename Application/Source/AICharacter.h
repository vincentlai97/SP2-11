#ifndef AI_CHARACTER_H
#define AI_CHARACTER_H

#include <vector>

#include "Character.h"
#include "Pathing.h"

class AICharacter : public Character {
private:
public:
	Vector3 dir;
	std::vector<Path*> paths;
	Path* path;
	bool endofpath;
	float turntime;
	float looktime;
	bool collide;
	
	AICharacter(void) : Character() {dir = Vector3(0, 0, 0); turntime = 0; looktime = 0; angle = 0;};
	~AICharacter(void) {};

	void update(double dt, std::vector<CollisionBox*> collisionBox);
	bool isendofpath();
	void track(double dt, std::vector<CollisionBox*> collisionBox, Vector3 dest);
};

#endif
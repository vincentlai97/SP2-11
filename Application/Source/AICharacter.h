#ifndef AI_CHARACTER_H
#define AI_CHARACTER_H

#include <vector>

#include "Pathing.h"

class AICharacter {
private:
public:
	Vector3 pos;
	Vector3 dir;
	std::vector<Path*> paths;
	Path* path;
	bool endofpath;
	float waitime;
	
	AICharacter(void) {};
	~AICharacter(void) {};

	void update(double dt);
	bool isendofpath();
};

#endif
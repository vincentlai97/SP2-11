#ifndef AI_CHARACTER_H
#define AI_CHARACTER_H

#include <vector>

#include "Pathing.h"

class AICharacter {
private:
public:
	Vector3 pos;
	Vector3 dir;
	Vector3 lookdir;
	std::vector<Path*> paths;
	Path* path;
	bool endofpath;
	float turntime;
	float looktime;
	
	AICharacter(void) {turntime = 0; looktime = 0;};
	~AICharacter(void) {};

	void update(double dt);
	bool isendofpath();
};

#endif
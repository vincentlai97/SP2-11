#ifndef PATHING_H
#define PATHING_H

#include <vector>

#include "Path.h"
#include "CollisionBox.h"

class Pathing {
private:
public:
	Pathing(void) {};
	~Pathing(void) {};
	
	static bool moveAlong(Vector3& current, Vector3 dir, const std::vector<Path*>& paths, float dist);
	static bool moveAlong(Vector3& current, Vector3 dir, const Path* path, float dist);
	static Path* selectPath(const Vector3& current, Vector3& dir, const std::vector<Path*>& paths);
};

#endif
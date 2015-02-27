#include "Pathing.h"
#include <time.h>

bool Pathing::moveAlong(Vector3& current, Vector3 dir, const std::vector<Path*>& paths, float dist)
{
	int index;
	dir.Normalize();
	for (int count = 0; count < paths.size(); count++)
	{
		Vector3 foo = paths[count]->dir().Normalized();
		if (dir == (paths[count]->dir()).Normalized()) //check if dir is parallel to path && moving from start to end
		{
			if ((current - paths[count]->point[Path::START]) == Vector3(0, 0, 0) || (current - paths[count]->point[Path::START]).Normalized() == dir) // check if current is on path
			{
				return moveAlong(current, dir, paths[count], dist);
			}
		}
		else if (-dir == (paths[count]->dir()).Normalized()) //check if dir is parallel to path && moving from end to start
		{
			if ((current - paths[count]->point[Path::END]) == Vector3(0, 0, 0) || (current - paths[count]->point[Path::END]).Normalized() == dir) // check if current is on path
			{
				return moveAlong(current, dir, &(-*paths[count]), dist);
			}
		}
	}
}

bool Pathing::moveAlong(Vector3& current, Vector3 dir, const Path* path, float dist)
{
	float maxDist = (path->point[Path::END] - current).Length();

	if (dist > maxDist)
	{
		current = path->point[Path::END];
		return true;
	}
	else
	{
		current += dir * dist;
		return false;
	}
}


Path* Pathing::selectPath(const Vector3& current, Vector3& dir, const std::vector<Path*>& paths)
{
	srand(time(NULL));
	dir.Normalize();

	std::vector<int> indices;

	for (int count = 0; count < paths.size(); count++)
	{
		if (paths[count]->point[Path::START] == current || paths[count]->point[Path::END] == current)
		{
			indices.push_back(count);
			indices.push_back(count);
			indices.push_back(count);
			indices.push_back(count);
		}
		if (current == paths[count]->point[Path::END] && dir == paths[count]->dir().Normalized())
		{
			indices.pop_back();
			indices.pop_back();
			indices.pop_back();
		}
		else if (current == paths[count]->point[Path::START] && dir == -paths[count]->dir().Normalized())
		{
			indices.pop_back();
			indices.pop_back();
			indices.pop_back();
		}
	}

	int selected = indices[rand()%indices.size()];
	
	if (current == paths[selected]->point[Path::START])
		dir = paths[selected]->dir().Normalized();
	else if (current == paths[selected]->point[Path::END])
		dir = -paths[selected]->dir().Normalized();

	return paths[selected];
}
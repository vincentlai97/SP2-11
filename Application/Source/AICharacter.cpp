#include "AICharacter.h"

void AICharacter::update(double dt)
{
	if (turntime > 0) turntime -= dt;
	else
	{
		if (endofpath)
		{
			path = Pathing::selectPath(pos, dir, paths);
			lookdir = dir;
			endofpath = false;
		}
		else
		{
			if (looktime > 0) looktime -= dt;
			else
			{
				srand(time(NULL));
				lookdir = dir;
				if (rand()%20 == 0 && path->haveSide()) 
				{
					looktime = 100 * dt;
					lookdir = path->side;
				}
				if (Pathing::moveAlong(pos, dir, path, 10 * dt))
				{
					endofpath = true;
					turntime = 50 * dt;
				}
			}
		}
	}
	std::cout << looktime << " " << path->haveSide() << std::endl;
}

bool AICharacter::isendofpath()
{
	for (int count = 0; count < paths.size(); count++)
	{
		for (int count1 = 0; count1 < 2; count1++)
		{
			if (paths[count]->point[count1] == pos)
				return true;
		}
	}
	return false;
}
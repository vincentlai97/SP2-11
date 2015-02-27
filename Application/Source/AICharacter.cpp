#include "AICharacter.h"

void AICharacter::update(double dt)
{
	if (waitime > 0) waitime -= dt;
	else
	{
		if (endofpath)
		{
			path = Pathing::selectPath(pos, dir, paths);
			endofpath = false;
		}
		else
		{
			if (Pathing::moveAlong(pos, dir, paths, 20 * dt))
			{
				endofpath = true;
				waitime = 3;
			}
		}
	}
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
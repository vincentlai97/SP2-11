#include "AICharacter.h"

void AICharacter::update(double dt, std::vector<CollisionBox*> collisionBox)
{
	for (int count = 0; count < collisionBox.size(); count++)
	{
		if (collisionBox[count] == &this->collisionBox)
			collisionBox.erase(collisionBox.begin() + count);
	}

	if (endofpath)
	{
		path = Pathing::selectPath(pos, dir, paths);
		angle = dir.Angle(Vector3(0, 0, 1)) * (dir.x > 0 ? 1 : -1);
		endofpath = false;
	}
	else
	{
		if (looktime > 0) looktime -= dt;
		else
		{
			srand(time(NULL));
			lookdir = dir;
			angle = dir.Angle(Vector3(0, 0, 1)) * (dir.x > 0 ? 1 : -1);
			if (rand()%20 == 0 && path->haveSide()) 
			{
				looktime = 100 * dt;
				lookdir = path->side;
				angle = lookdir.Angle(Vector3(0, 0, 1)) * (dir.x > 0 ? 1 : -1);
			}
			if (Pathing::moveAlong(pos, dir, path, 10 * dt))
			{
				endofpath = true;
				turntime = 50 * dt;
			}
		}
	}
<<<<<<< Updated upstream
	/*std::cout << looktime << " " << path->haveSide() << std::endl;*/
=======

	if (this->collisionBox.checkCollision(collisionBox) && !collide)
	{
		collide = true;
		dir = -dir;
		angle = dir.Angle(Vector3(0, 0, 1)) * (dir.x > 0 ? 1 : -1);
	}
	else if (!this->collisionBox.checkCollision(collisionBox)) collide = false;

	this->collisionBox.Centre = pos;
>>>>>>> Stashed changes
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
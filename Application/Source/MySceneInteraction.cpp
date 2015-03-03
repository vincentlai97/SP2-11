#include "MyScene.h"

int MyScene::targeted(const std::vector<CollisionBox*> v)
{
	Vector3 view = camera.target - camera.position;
	view.Normalize();

	CollisionBox target(camera.position, 0, 0, 0);

	for (int count1 = 10; count1 <= 20; count1++)
	{
		target.Centre += view;
		for (int count = 0; count < v.size(); count++)
		{
			if (target.checkCollision(*v[count]))
			{
				return count;
			}
		}
	}
	return -1;
}
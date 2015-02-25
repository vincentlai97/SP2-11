#include "MyScene.h"

Object* MyScene::targetObject()
{
	Vector3 view = camera.target - camera.position;
	view.Normalize();

	CollisionBox target(camera.position, 0, 0, 0);

	for (int count1 = 0; count1 < 10; count1++)
	{
		target.Centre += view;
		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->isGettable())
				if ((target.Centre - obj[count]->collisionBox.Centre).Length() < 5)
					if (target.checkCollision(obj[count]->collisionBox))
					{
						return obj[count];
					}
		}
	}
	return &Object();
}
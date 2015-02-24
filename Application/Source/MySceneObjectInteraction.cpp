#include "MyScene.h"

Object MyScene::targetObject()
{
	Vector3 view = camera.target - camera.position;
	view.Normalize();
	view *= 10;

	CollisionBox target(camera.position + view, 2, 2, 2);

	for (int count = 0; count < obj.size(); count++)
	{
		if ((target.Centre - obj[count].collisionBox.Centre).Length() < 5)
		if (target.checkCollision(obj[count].collisionBox))
			return obj[count];
	}
	return Object();
}
#include "MyScene.h"
#include "Application.h"

void MyScene::UpdateAI(double dt)
{
	for (int count = 0; count < shelfCharacters.size(); count++)
		shelfCharacters[count]->update(dt, shelfCharactersCollisionBox);
	for (int count = 0; count < fruitstandCharacters.size(); count++)
		fruitstandCharacters[count]->update(dt, fruitstandCharactersCollisionBox);
	for (int count = 0; count < guards.size(); count++)
	{
		guards[0] -> track(dt, guardsCollisionBox, camera.position);
		if (guards[0]->collisionBox.checkCollision(cameraCollisionBox))
			state = Application::LOSE;
	}
}
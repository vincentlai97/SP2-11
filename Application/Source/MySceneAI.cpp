#include "MyScene.h"

void MyScene::updateAI(double dt)
{
	for (int count = 0; count < shelfCharacters.size(); count++)
		shelfCharacters[count]->update(dt, shelfCharactersCollisionBox);
	for (int count = 0; count < fruitstandCharacters.size(); count++)
		fruitstandCharacters[count]->update(dt, fruitstandCharactersCollisionBox);
	//guards[0] -> track(dt, guardsCollisionBox, camera.position);
	if (guards[0]->collisionBox.checkCollision(cameraCollisionBox))
		busted = true;
}
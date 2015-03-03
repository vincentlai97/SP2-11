#include "MyScene.h"

void MyScene::updateAI(double dt)
{
	for (int count = 0; count < shelfCharacters.size(); count++)
		shelfCharacters[count]->update(dt, shelfCharactersCollisionBox);
}
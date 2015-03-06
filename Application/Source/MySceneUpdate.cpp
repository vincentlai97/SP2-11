#include "MyScene.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Application.h"

void MyScene::UpdateRole()
{
	if (role == CUSTOMER)
	{
		if (cameraCollisionBox.checkCollision(fenceArea))
		{
			if (!win && inventory.size() > 0 && inventory[0]->name != "paperbag")
			{
				role = THIEF;

				AICharacter *ai = new AICharacter;

				ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Head.obj"));
				ai->mesh[0]->textureID = LoadTGA("Image//Face.tga");
				ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Body.obj"));
				ai->mesh[1]->textureID = LoadTGA("Image//GuardShirt.tga");
				ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Limb.obj"));
				ai->mesh[2]->textureID = LoadTGA("Image//GuardLimbs.tga");
				ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Limb.obj"));
				ai->mesh[3]->textureID = LoadTGA("Image//GuardLimbs.tga");

				ai->paths = guardspaths;

				ai->pos = Vector3(0, 0, 295);
				ai->endofpath = true;

				ai->collisionBox.Centre = ai->pos;

				guards.push_back(ai);
				guardsCollisionBox.push_back(&ai->collisionBox);

				guardsCollisionBox.insert(guardsCollisionBox.end(), shelfCharactersCollisionBox.begin(), shelfCharactersCollisionBox.end());
				guardsCollisionBox.insert(guardsCollisionBox.end(), fruitstandCharactersCollisionBox.begin(), fruitstandCharactersCollisionBox.end());
			}
		}
		else if (targeted(emptyCashier->collisionBox) && Application::Mouse_Click(0))
		{
			role = CASHIER;
			camera.position = Vector3(325, 15, 205);
			camera.target = Vector3(315, 15, 205);
			camera.up = Vector3(0, 1, 0);
			paying = false;
			rounds = 0;
		}
	}

	if (role == CASHIER)
	{
		if (rounds == 5)
		{
			role == CUSTOMER;
			camera.position = Vector3(345, 15, 205);
			camera.target = Vector3(335, 15, 205);
		}
	}
}
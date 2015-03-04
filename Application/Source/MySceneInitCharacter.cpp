#include "MyScene.h"

#include <time.h>
#include "MeshBuilder.h"
#include "LoadTGA.h"

void MyScene::InitAICharacters(std::vector<Character*>& character, std::vector<CollisionBox*>& characterCollisionBox, std::vector<Path*> paths, int num)
{
	srand(time(NULL));
	for (int count = 0; count < num; count++)
	{
		AICharacter *ai = new AICharacter;
		
		ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Head.obj"));
		ai->mesh[0]->textureID = LoadTGA("Image//Face.tga");
		ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Body.obj"));
		ai->mesh[1]->textureID = LoadTGA("Image//CustomerShirt1.tga");
		ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Limb.obj"));
		ai->mesh[2]->textureID = LoadTGA("Image//CustomerLimbs1.tga");
		ai->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Limb.obj"));
		ai->mesh[3]->textureID = LoadTGA("Image//CustomerLimbs1.tga");

		ai->paths = paths;
		
		ai->pos = paths[rand()%paths.size()]->point[rand()%2];
		ai->endofpath = true;

		ai->collisionBox.Centre = ai->pos;

		character.push_back(ai);
		characterCollisionBox.push_back(&ai->collisionBox);
	}
}
#include "MyScene.h"

void MyScene::InitCollisionBox()
{
	CollisionBox* collisionBox;

	//Exterior Hitbox
	collisionBox = new CollisionBox(Vector3(0, -0.5, 400), 2200, 1, 1690); //Bottom
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(0,  500, 1000), 200, 200, 200); //Front
	v.push_back(collisionBox);
	//Interior Hitbox
	collisionBox = new CollisionBox(Vector3(0, 115, 300.5), 800, 90, 1); // Front Top
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(235, 80, 300.5), 330, 160, 1); // Front Right
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(-235, 80, 300.5), 330, 160, 1); // Front Left
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(0, 80, -300.5), 800, 160, 1); // Back
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(0, -0.5, 0), 800, 1, 600); // Bottom
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(0, 160.5, 0), 800, 1, 600); // Top
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(0, 80, 0), 800, 20, 600); // Middle
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(-400.5, 80, 0), 1, 160, 600); // Left
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(400.5, 80, 0), 1, 160, 600); // Right
	v.push_back(collisionBox);
	doorArea = CollisionBox(Vector3(0, 35, 300), 140, 70, 100);

	//Elevator Hitbox
	collisionBox = new CollisionBox(Vector3(-370, 32.5, 170), 50, 35, 10); //Elevator on Level One
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(-370, 32.5, 130), 50, 35, 10);
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(-370, 112.5, 170), 50, 35, 10); //Elevator on Level Two
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(-370, 112.5, 130), 50, 35, 10);
	v.push_back(collisionBox);
	elevatorUp = CollisionBox(Vector3(-380, 10, 150), 40, 20, 30);
	elevatorDown = CollisionBox(Vector3(-380, 100, 150), 40, 20, 30);
	elevatorArea = CollisionBox(Vector3(-360, 80, 150), 80, 160, 30);

	//Escalator Hitbox
	collisionBox = new CollisionBox(Vector3(-290, 45, 260), 140, 90, 80); // Travelator
	v.push_back(collisionBox);
	collisionBox = new CollisionBox(Vector3(-290, 45, 260), 160, 150, 20); // Travelator Handle
	v.push_back(collisionBox);
	travelatorUp.push_back(CollisionBox(Vector3(-290, 45, 280), 150, 90, 20));
	travelatorDown.push_back(CollisionBox(Vector3(-295, 50, 240), 150, 90, 20));
}
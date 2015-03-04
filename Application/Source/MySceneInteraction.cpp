#include "MyScene.h"
#include "Application.h"

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

bool MyScene::targeted(const CollisionBox collisionBox)
{

	Vector3 view = camera.target - camera.position;
	view.Normalize();

	CollisionBox target(camera.position, 0, 0, 0);

	for (int count1 = 10; count1 <= 20; count1++)
	{
		target.Centre += view;
		if (target.checkCollision(collisionBox))
			return true;
	}
	return false;
}

void MyScene::InteractDoor(double dt)
{
	if (cameraCollisionBox.checkCollision(doorArea))
	{
		if (DoorR->collisionBox.Centre.x < 105)
		{
			DoorR->collisionBox.Centre.x += dt * 30;
			DoorL->collisionBox.Centre.x -= dt * 30;
		}
	}
	else if (DoorR->collisionBox.Centre.x > 35)
	{
		DoorR->collisionBox.Centre.x -= dt * 30;
		DoorL->collisionBox.Centre.x += dt * 30;
	}
}

void MyScene::InteractElevator(double dt)
{
	if(cameraCollisionBox.checkCollision(elevatorUp) && Application::IsKeyPressed(VK_UP))
	{
		camera.position.y = 120;
		camera.target.y = 120;
	}
	else if(cameraCollisionBox.checkCollision(elevatorDown) && Application::IsKeyPressed(VK_DOWN))
	{
		camera.position.y = 20;
		camera.target.y = 20;
	}
}

void MyScene::InteractElevatorButton(double dt)
{
	if (targeted(eDoorButton1->collisionBox) || targeted(eDoorButton2->collisionBox))
	{
		if (Application::Mouse_Click(0) && !eDoorOpen)
		{
			eDoorOpen = true;
		}
	}

	if (targeted(eDoor1->collisionBox) || targeted(eDoor2->collisionBox))
		if(cameraCollisionBox.checkCollision(elevatorUp) || cameraCollisionBox.checkCollision(elevatorDown))
	{
		if (Application::Mouse_Click(0) && eDoorClosed)
		{
			eDoorOpen = true;
			eDoorClosed = false;
		}
	}
}

void MyScene::InteractElevatorDoor(double dt)
{
	if (eDoorOpen && eDoor1->collisionBox.Centre.y < 40)
	{
		eDoor1->collisionBox.Centre.y += 15 * dt;
		eDoor2->collisionBox.Centre.y += 15 * dt;
	}
	else if (cameraCollisionBox.checkCollision(elevatorUp) || cameraCollisionBox.checkCollision(elevatorDown)) eDoorOpen = false;

	if (!eDoorOpen && eDoor1->collisionBox.Centre.y > 0)
	{
		eDoor1->collisionBox.Centre.y -= 15 * dt;
		eDoor2->collisionBox.Centre.y -= 15 * dt;
	}

	if (eDoor1->collisionBox.Centre.y < 0) eDoorClosed = true;
	
	if (!cameraCollisionBox.checkCollision(elevatorArea)) eDoorOpen = false;
}
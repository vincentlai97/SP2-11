#include "MyScene.h"

void MyScene::InitShelfPaths()
{
	Path* path;
	Vector3 start, end, side;

	float X[] = {-90, -210, -240, -360};
	float Z[] = {70, 30, -5, -45, -80, -120, -155, -195, -230, -270};

	for (int countx = 0; countx < 3; countx++)
	{
		for (int countz = 0; countz < 10; countz++)
		{
			start = Vector3(X[countx], 0, Z[countz]);
			end = Vector3(X[countx + 1], 0, Z[countz]);

			side.z = (countx+1)%2; // countx : even, odd / side.z : 1, 0
			side.z *= (countz%2 ? 1 : -1); // countz : even, odd / side.z : -1, 1

			path = new Path(start, end, side);
			shelfpaths.push_back(path);
		}
	}

	side = Vector3(0, 0, 0);
	for (int countx = 0; countx < 4; countx++)
	{
		for (int countz = 0; countz < 9; countz++)
		{
			start = Vector3(X[countx], 0, Z[countz]);
			end = Vector3(X[countx], 0, Z[countz + 1]);

			path = new Path(start, end, side);
			shelfpaths.push_back(path);
		}
	}
}

void MyScene::InitFruitstandPaths()
{
	Path* path;
	Vector3 start, end, side;

	float X[] = {265, 230, 215, 180, 165, 130, 115, 80, 65, 30};
	float Z[] = {100, 60, 25, -15, -50, -90, -125, -165, -200, -240};

	for (int countx = 0; countx < 9; countx++)
	{
		for (int countz = 0; countz < 10; countz++)
		{
			start = Vector3(X[countx], 0, Z[countz]);
			end = Vector3(X[countx + 1], 0, Z[countz]);
			
			side.z = (countx+1)%2; // countx : even, odd / side.z : 1, 0
			side.z *= (countz%2 ? 1 : -1); // countz : even, odd / side.z : -1, 1

			path = new Path(start, end, side);
			fruitstandpaths.push_back(path);
		}
	}
	
	side = Vector3();
	for (int countx = 0; countx < 10; countx++)
	{
		for (int countz = 0; countz < 9; countz++)
		{
			start = Vector3(X[countx], 0, Z[countz]);
			end = Vector3(X[countx], 0, Z[countz + 1]);
			
			side.x = (countx+1)%2; // countx : even, odd / side.z : 1, 0
			side.x *= (countz%2 ? 1 : -1); // countz : even, odd / side.z : -1, 1
			
			path = new Path(start, end, side);
			fruitstandpaths.push_back(path);
		}
	}
}

void MyScene::InitGuardPaths()
{
	InitGuardPaths(395, 285, 295, 175);
	InitGuardPaths(285, 85, 295, 235);
	InitGuardPaths(85, 75, 290, 240);
	InitGuardPaths(75, -75, 295, 240);
	InitGuardPaths(-85, -215, 295, 65);
	InitGuardPaths(-215, -395, 215, 180);
	InitGuardPaths(-215, -340, 180, 65);
	InitGuardPaths(-340, -395, 120, 65);
	InitGuardPaths(-355, -395, 65, -295);
	InitGuardPaths(-205, -245, 65, -295);
	InitGuardPaths(105, -85, 235, 95);
	InitGuardPaths(35, -95, 95, -295);
	InitGuardPaths(-245, -355, 35, -10);
	InitGuardPaths(-245, -355, -40, -85);
	InitGuardPaths(-245, -355, -115, -160);
	InitGuardPaths(-245, -355, -190, -235);
	InitGuardPaths(-245, -355, -265, -295);
	InitGuardPaths(-95, -205, 35, -10);
	InitGuardPaths(-95, -205, -40, -85);
	InitGuardPaths(-95, -205, -115, -160);
	InitGuardPaths(-95, -205, -190, -235);
	InitGuardPaths(-95, -205, -265, -295);
	InitGuardPaths(380, 105, 175, 95);
	InitGuardPaths(380, 260, 95, -230);
	InitGuardPaths(330, 35, -235, -295);
	InitGuardPaths(85, 60, 95, -235);
	InitGuardPaths(135, 110, 95, -235);
	InitGuardPaths(185, 160, 95, -235);
	InitGuardPaths(235, 210, 95, -235);
	InitGuardPaths(60, 35, 65, 20);
	InitGuardPaths(60, 35, -10, -55);
	InitGuardPaths(60, 35, -85, -130);
	InitGuardPaths(60, 35, -160, -205);
	InitGuardPaths(110, 85, 65, 20);
	InitGuardPaths(110, 85, -10, -55);
	InitGuardPaths(110, 85, -85, -130);
	InitGuardPaths(110, 85, -160, -205);
	InitGuardPaths(160, 35, 65, 20);
	InitGuardPaths(160, 35, -10, -55);
	InitGuardPaths(160, 35, -85, -130);
	InitGuardPaths(160, 35, -160, -205);
	InitGuardPaths(210, 85, 65, 20);
	InitGuardPaths(210, 85, -10, -55);
	InitGuardPaths(210, 85, -85, -130);
	InitGuardPaths(210, 85, -160, -205);
	InitGuardPaths(260, 35, 65, 20);
	InitGuardPaths(260, 35, -10, -55);
	InitGuardPaths(260, 35, -85, -130);
	InitGuardPaths(260, 35, -160, -205);
	InitGuardPaths(395, 375, -230, -270);
	InitGuardPaths(10, -10, 240, 230);
}

void MyScene::InitGuardPaths(float xMax, float xMin, float zMax, float zMin)
{
	Path* path;
	Vector3 start, end, side;

	for (float x = xMax; x > xMin; x-= 5)
	{
		for (float z = zMax; z >= zMin; z -= 5)
		{
			start = Vector3(x, 0, z);
			end = Vector3(x-5, 0, z);

			path = new Path(start, end, side);
			guardspaths.push_back(path);
		}
	}
	
	for (float x = xMax; x >= xMin; x-= 5)
	{
		for (float z = zMax; z > zMin; z -= 5)
		{
			start = Vector3(x, 0, z);
			end = Vector3(x, 0, z-5);

			path = new Path(start, end, side);
			guardspaths.push_back(path);
		}
	}
}
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
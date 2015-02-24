#include "MyScene.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

void MyScene::LoadMesh()
{
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//skybox
	meshList[INT_WALL] = MeshBuilder::GenerateOBJ("wall", "OBJ//Interior Walls.obj");
	meshList[INT_WALL]->textureID = LoadTGA("Image//Wall.tga");
	meshList[INT_WALL]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[INT_WALL]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[INT_WALL]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[INT_WALL]->material.kShininess = 3.f;

	meshList[INT_FLOOR] = MeshBuilder::GenerateOBJ("tile", "OBJ//Interior Tiles.obj");
	meshList[INT_FLOOR]->textureID = LoadTGA("Image//Tile.tga");
	meshList[INT_FLOOR]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[INT_FLOOR]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[INT_FLOOR]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[INT_FLOOR]->material.kShininess = 3.f;

	meshList[WHITE_GLASS] = MeshBuilder::GenerateOBJ("white glass", "OBJ//White Glass.obj");
	meshList[WHITE_GLASS]->textureID = LoadTGA("Image//White Glass.tga");
	meshList[WHITE_GLASS]->material.kAmbient.Set(.8, .8, .8);
	meshList[WHITE_GLASS]->material.kDiffuse.Set(.6, .6, .6);
	meshList[WHITE_GLASS]->material.kSpecular.Set(.3, .3, .3);
	meshList[WHITE_GLASS]->material.kShininess = 10;

	meshList[ESCALATOR] = MeshBuilder::GenerateQuad("escalator", Color(0, 0, 0), 1.f, 1.f);
	meshList[ESCALATOR]->textureID = LoadTGA("Image//Travelator.tga");
	meshList[ESCALATOR]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ESCALATOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[ESCALATOR]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[ESCALATOR]->material.kShininess = 1.f;

	meshList[ELEVATOR] = MeshBuilder::GenerateOBJ("Elevator", "OBJ//Elevator.obj");
	meshList[ELEVATOR]->textureID = LoadTGA("Image//metal.tga");
	meshList[ELEVATOR]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ELEVATOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[ELEVATOR]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[ELEVATOR]->material.kShininess = 1.f;

	// Exterior
	meshList[EXT_WALL_BOT] = MeshBuilder::GenerateOBJ("extwallbot", "OBJ//Exterior Walls Bottom.obj");
	meshList[EXT_WALL_BOT]->textureID = LoadTGA("Image//White Wall.tga");

	meshList[EXT_WALL_MID] = MeshBuilder::GenerateOBJ("extwallbot", "OBJ//Exterior Walls Middle.obj");
	meshList[EXT_WALL_MID]->textureID = LoadTGA("Image//Black Wall.tga");

	meshList[EXT_WALL_TOP] = MeshBuilder::GenerateOBJ("extwallbot", "OBJ//Exterior Walls Top.obj");
	meshList[EXT_WALL_TOP]->textureID = LoadTGA("Image//Red Wall.tga");

	meshList[SKYBOX_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[SKYBOX_FRONT]->textureID = LoadTGA("Image//skyfront.tga");
	meshList[SKYBOX_FRONT]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[SKYBOX_FRONT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_FRONT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_FRONT]->material.kShininess = 3.f;

	meshList[SKYBOX_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[SKYBOX_BACK]->textureID = LoadTGA("Image//skyback.tga");
	meshList[SKYBOX_BACK]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[SKYBOX_BACK]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_BACK]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_BACK]->material.kShininess = 3.f;

	meshList[SKYBOX_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[SKYBOX_TOP]->textureID = LoadTGA("Image//skytop.tga");
	meshList[SKYBOX_TOP]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[SKYBOX_TOP]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_TOP]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_TOP]->material.kShininess = 3.f;

	meshList[SKYBOX_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[SKYBOX_LEFT]->textureID = LoadTGA("Image//skyright.tga");
	meshList[SKYBOX_LEFT]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[SKYBOX_LEFT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_LEFT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_LEFT]->material.kShininess = 3.f;

	meshList[SKYBOX_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[SKYBOX_RIGHT]->textureID = LoadTGA("Image//skyleft.tga");
	meshList[SKYBOX_RIGHT]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[SKYBOX_RIGHT]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_RIGHT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_RIGHT]->material.kShininess = 3.f;

	meshList[SKYBOX_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1), 1.f, 1.f);
	meshList[SKYBOX_FLOOR]->textureID = LoadTGA("Image//grass.tga");
	meshList[SKYBOX_FLOOR]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[SKYBOX_FLOOR]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_FLOOR]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[SKYBOX_FLOOR]->material.kShininess = 3.f;

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//Door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//blueglass.tga");
	meshList[GEO_DOOR]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DOOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_DOOR]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DOOR]->material.kShininess = 10.f;

	meshList[eDoor] = MeshBuilder::GenerateOBJ("eDoor", "OBJ//Door.obj");
	meshList[eDoor]->textureID = LoadTGA("Image//metal.tga");
	meshList[eDoor]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoor]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[eDoor]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[eDoor]->material.kShininess = 3.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1,1,1), 36, 36, 1);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//cambria.tga");

	Object NewObj;

	//Trolley Obj
	meshList[trolley] = MeshBuilder::GenerateOBJ("Trolley", "OBJ//Trolley.obj");
	meshList[trolley]->textureID = LoadTGA("Image//Steeltexture.tga");
	meshList[trolley]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[trolley]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kShininess = 3.f;
	NewObj.mesh = meshList[trolley];
	NewObj.centre = Vector3(-100, 0, 0);
	NewObj.size = Vector3(3, 3, 3);
	NewObj.name = "Trolley";
	obj.push_back(NewObj);

	meshList[shelf] = MeshBuilder::GenerateOBJ("Shelf", "OBJ//shelf.obj");
	meshList[shelf]->textureID = LoadTGA("Image//Steeltexture.tga");
	meshList[shelf]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[shelf]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[shelf]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[shelf]->material.kShininess = 5.f;
	
	NewObj.mesh = meshList[shelf];
	NewObj.name = "Shelf";
	NewObj.posMax = Vector3(40, 40, 10);
	NewObj.posMin = Vector3(-40, 0, -10);
	NewObj.size = Vector3(3.5f, 3.5f, 3.5f);

	for (int posX = 250; posX >= 100; posX -= 150)
	{
		for (int posZ = 250; posZ >= 150; posZ -= 50)
		{
			NewObj.centre = Vector3(posX, 0, posZ);
			NewObj.position = 0;
			v.push_back(CollisionBox(NewObj.centre, NewObj.posMax, NewObj.posMin));
			obj.push_back(NewObj);
		}
	}

	NewObj.Reset();

	//Can4 face side
	meshList[Can4] = MeshBuilder::GenerateOBJ("Can4", "OBJ//Can4.obj");
	meshList[Can4]->textureID = LoadTGA("Image//Can4.tga");
	meshList[Can4]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Can4]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Can4]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Can4]->material.kShininess = 5.f;

	NewObj.mesh = meshList[Can4];
	NewObj.name = "Sausages";
	NewObj.size = Vector3(3.5f, 3.5f, 3.5f);
	NewObj.price = 2.00;

	for (float posX = 75; posX <= 120; posX += 5)
	{
		for (float posY = 35; posY >= 0; posY -= 6.4f)
		{
			for (float posZ = 255; posZ >= 241; posZ -= 14)
			{	
				NewObj.centre = Vector3(posX, posY, posZ);
				obj.push_back(NewObj);		
			}
		}
	}

	//Box 1 face side
	/*meshList[Box1] = MeshBuilder::GenerateOBJ("Box1", "OBJ//Box1.obj");
	meshList[Box1]->textureID = LoadTGA("Image//Box1.tga");
	meshList[Box1]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Box1]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Box1]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Box1]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Box1];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 205);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Zuku";
			NewObj.Price = 3.00;
			obj.push_back(NewObj);

		}
	}
	//Box 1 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 192);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Zuku";
			NewObj.Price = 3.00;
			obj.push_back(NewObj);

		}
	}


	//Box 2 face side
	meshList[Box2] = MeshBuilder::GenerateOBJ("Box2", "OBJ//Box2.obj");
	meshList[Box2]->textureID = LoadTGA("Image//Box2.tga");
	meshList[Box2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Box2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Box2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Box2]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Box2];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 156);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Doritos";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}
	//Box 2 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 75; row < 125; row += 5)
		{
			NewObj.Position = Vector3(row, column, 141);
			NewObj.Size = Vector3(3.5f, 3.5f, 3.5f);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Doritos";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}

	//Box 3 face side
	meshList[Box3] = MeshBuilder::GenerateOBJ("Box3", "OBJ//Box3.obj");
	meshList[Box3]->textureID = LoadTGA("Image//Box3.tga");
	meshList[Box3]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Box3]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Box3]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Box3]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Box3];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 155);
			NewObj.Size = Vector3(0.5f, 0.5f, 0.5f);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Granola";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}
	//Box 3 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 141);
			NewObj.Size = Vector3(0.5f, 0.5f, 0.5f);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Granola";
			NewObj.Price = 2.50;
			obj.push_back(NewObj);

		}
	}

	//Can3 face side
	meshList[Can3] = MeshBuilder::GenerateOBJ("Can3", "OBJ//Can.obj");
	meshList[Can3]->textureID = LoadTGA("Image//Can3.tga");
	meshList[Can3]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Can3]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Can3]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Can3]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Can3];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 205);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = 0.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Fishy Tuna";
			NewObj.Price = 3.50;
			obj.push_back(NewObj);

		}
	}
	//Can3 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 191);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = 180.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Fishy Tuna";
			NewObj.Price = 3.50;
			obj.push_back(NewObj);

		}
	}

	//Can2 face side
	meshList[Can2] = MeshBuilder::GenerateOBJ("Can2", "OBJ//Can.obj");
	meshList[Can2]->textureID = LoadTGA("Image//Can2.tga");
	meshList[Can2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Can2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Can2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Can2]->material.kShininess = 5.f;
	NewObj.mesh = meshList[Can2];
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 255);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = 90.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Dog Ham";
			NewObj.Price = 4.00;
			obj.push_back(NewObj);

		}
	}
	//Can2 back side
	for (float column = 35, count = 0; count <= 5; column -= 6.4f)
	{
		count++;
		for (int row = 225, count = 0; count <= 10; row += 5)
		{
			count++;
			NewObj.Position = Vector3(row, column, 241);
			NewObj.Size = Vector3(3, 3, 3);
			NewObj.rotation = -90.0f;
			NewObj.Rotation = Vector3(0, 1, 0);
			NewObj.Name = "Dog Ham";
			NewObj.Price = 4.00;
			obj.push_back(NewObj);

		}
	}*/

	//Display Circular cabinet
	/*meshList[DisplayCircular] = MeshBuilder::GenerateOBJ("DisplayCircular", "OBJ//DisplayCircular.obj");
	meshList[DisplayCircular]->textureID = LoadTGA("Image//DisplayCircular.tga");
	meshList[DisplayCircular]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[DisplayCircular]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[DisplayCircular]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[DisplayCircular]->material.kShininess = 5.f;
	NewObj.mesh = meshList[DisplayCircular];
	NewObj.Position = Vector3(0, 11, 0);
	NewObj.Size = Vector3(5, 5, 5);
	NewObj.rotation = 0.0f;
	NewObj.Rotation = Vector3(0, 1, 0);
	NewObj.Name = "Circular Cabinet";
	NewObj.Price = 0.00;
	obj.push_back(NewObj);*/

}
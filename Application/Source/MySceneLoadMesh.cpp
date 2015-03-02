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

	meshList[ESCALATOR] = MeshBuilder::GenerateOBJ("escalator", "OBJ//travel.obj");
	meshList[ESCALATOR]->textureID = LoadTGA("Image//travel.tga");
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

	//Buildings
	meshList[Building1] = MeshBuilder::GenerateOBJ("Building1", "OBJ//Building.obj");
	meshList[Building1]->textureID = LoadTGA("Image//BuildingTexture.tga");
	meshList[Building1]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[Building1]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[Building1]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[Building1]->material.kShininess = 10.f;

	meshList[Building2] = MeshBuilder::GenerateOBJ("Building2", "OBJ//Building.obj");
	meshList[Building2]->textureID = LoadTGA("Image//BuildingTexture2.tga");
	meshList[Building2]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[Building2]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[Building2]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[Building2]->material.kShininess = 10.f;

	meshList[Building3] = MeshBuilder::GenerateOBJ("Building3", "OBJ//Building.obj");
	meshList[Building3]->textureID = LoadTGA("Image//BuildingTexture3.tga");
	meshList[Building3]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[Building3]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[Building3]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[Building3]->material.kShininess = 10.f;

	
	//Door
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

	Object* NewObj = new Object;

	//Trolley Obj
	meshList[trolley] = MeshBuilder::GenerateOBJ("Trolley", "OBJ//Trolley.obj");
	meshList[trolley]->textureID = LoadTGA("Image//metal.tga");
	meshList[trolley]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[trolley]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[trolley]->material.kShininess = 3.f;

	meshList[shelf] = MeshBuilder::GenerateOBJ("Shelf", "OBJ//shelf.obj");
	meshList[shelf]->textureID = LoadTGA("Image//Steeltexture.tga");
	meshList[shelf]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[shelf]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[shelf]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[shelf]->material.kShininess = 5.f;

	for (int posX = -300, count = 0; posX <= -150; posX += 150)
	{
		for (int posZ = -250; posZ <= 75; posZ += 75)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[shelf];
			NewObj->name = "shelf";
			NewObj->collisionBox.Max = Vector3(50, 40, 10);
			NewObj->collisionBox.Min = Vector3(-50, 0, -10);
			NewObj->size = Vector3(4, 4, 4);
			NewObj->collisionBox.Centre = Vector3(posX, 0, posZ);
			NewObj->position = count++;
			v.push_back(NewObj->collisionBox);
			obj.push_back(NewObj);
		}
	}

	meshList[CashierTable] = MeshBuilder::GenerateOBJ("CashierTable", "OBJ//CashierTable.obj");
	meshList[CashierTable]->textureID = LoadTGA("Image//CashierTable.tga");
	meshList[CashierTable]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[CashierTable]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[CashierTable]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[CashierTable]->material.kShininess = 5.f;


	for (int posX = 120, count = 0; posX <= 270; posX += 50)
	{
		NewObj = new Object;
		NewObj->mesh = meshList[CashierTable];
		NewObj->name = "Cashier Table";
		NewObj->collisionBox = CollisionBox(Vector3(posX, 0, 200), Vector3(10,10,20), Vector3(-10,0,-20));
		NewObj->size = Vector3(4,4,4);
		NewObj->angle = 180.0f;
		NewObj->rotation = Vector3(0, 1, 0);
		NewObj->position = count++;
		v.push_back(NewObj->collisionBox);
		obj.push_back(NewObj);
	}

	//Toy Shelves - 2nd Floor
	meshList[Toy_Shelves] = MeshBuilder::GenerateOBJ("Toy_Shelves", "OBJ//Toy_Shelf.obj");
	meshList[Toy_Shelves]->textureID = LoadTGA("Image//Toy_Shelf.tga");
	meshList[Toy_Shelves]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Toy_Shelves]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Toy_Shelves]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Toy_Shelves]->material.kShininess = 5.f;

	for(int posX = 250, count = 0; posX > 0; posX -= 50)
	{
		for (int posZ = 250; posZ >= 50; posZ -= 50)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[Toy_Shelves];
			NewObj->name = "Toy_Shelves";
			NewObj->collisionBox = CollisionBox(Vector3(posX, 90, posZ), Vector3(10, 40, 10), Vector3(-10, 0, -10));
			NewObj->size = Vector3(4, 4, 4);
			NewObj->position = count++;
			v.push_back(NewObj->collisionBox);
			obj.push_back(NewObj);
		}
	}

	//Cafeteria Tables and Chairs - 2nd Floor
	meshList[TaC] = MeshBuilder::GenerateOBJ("TaC", "OBJ//Mahogany.obj");
	meshList[TaC]->textureID = LoadTGA("Image//Mahogany.tga");
	meshList[TaC]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[TaC]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[TaC]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[TaC]->material.kShininess = 5.f;

	for(int posX = -300, count = 0; posX < -125; posX += 75)
	{
		for (int posZ = -150; posZ < 50; posZ += 75)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[TaC];
			NewObj->name = "TaC";
			NewObj->collisionBox = CollisionBox(Vector3(posX, 90, posZ), Vector3(15, 40, 10), Vector3(-20, 0, -12));
			NewObj->size = Vector3(2, 2, 2);
			NewObj->position = count++;
			v.push_back(NewObj->collisionBox);
			obj.push_back(NewObj);
		}
	}

	//Cafeteria Banner
	meshList[Banner] = MeshBuilder::GenerateOBJ("Banner", "OBJ//Banner.obj");
	meshList[Banner]->textureID = LoadTGA("Image//LimeGreen.tga");
	meshList[Banner]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Banner]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Banner]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Banner]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[Banner];
	NewObj->collisionBox = CollisionBox(Vector3(-370, 90, -294), Vector3(40, 40, 40), Vector3(-40, 0, -40));
	NewObj->angle = -90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->size = Vector3(3, 4, 3);
	NewObj->name = "Banner";
	v.push_back(NewObj->collisionBox);
	obj.push_back(NewObj);

	////Clothes Racks - 2nd Floor
	meshList[ClothesRack] = MeshBuilder::GenerateOBJ("ClothesRack", "OBJ//ClothesRack.obj");
	meshList[ClothesRack]->textureID = LoadTGA("Image//Wood_Texture.tga");
	meshList[ClothesRack]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ClothesRack]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[ClothesRack]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[ClothesRack]->material.kShininess = 5.f;

	for(int posX = 250, count = 0; posX > 0; posX -= 50)
	{
		for (int posZ = -50; posZ > -300; posZ -= 50)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[ClothesRack];
			NewObj->name = "ClothesRack";
			NewObj->collisionBox = CollisionBox(Vector3(posX, 90, posZ), Vector3(10, 40, 10), Vector3(-10, 0, -10));
			NewObj->size = Vector3(4, 4, 4);
			NewObj->position = count++;
			v.push_back(NewObj->collisionBox);
			obj.push_back(NewObj);
		}
	}

	//Cafeteria Table
	meshList[Cafeteria] = MeshBuilder::GenerateOBJ("Cafeteria", "OBJ//Cafeteria.obj");
	meshList[Cafeteria]->textureID = LoadTGA("Image//Marble.tga");
	meshList[Cafeteria]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Cafeteria]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Cafeteria]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Cafeteria]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[Cafeteria];
	NewObj->collisionBox = CollisionBox(Vector3(-365, 90, -265), Vector3(40, 40, 40), Vector3(-40, 0, -40));
	NewObj->size = Vector3(3, 4, 3);
	NewObj->name = "Cafeteria";
	v.push_back(NewObj->collisionBox);
	obj.push_back(NewObj);

	//Cafeteria Cashier
	meshList[CafeteriaCashier] = MeshBuilder::GenerateOBJ("CafeteriaCashier", "OBJ//CafeteriaCashier.obj");
	meshList[CafeteriaCashier]->textureID = LoadTGA("Image//Shiny_Silver.tga");
	meshList[CafeteriaCashier]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[CafeteriaCashier]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[CafeteriaCashier]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[CafeteriaCashier]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[CafeteriaCashier];
	NewObj->collisionBox.Centre = Vector3(-365, 90, -265);
	NewObj->size = Vector3(3, 3, 3);
	NewObj->name = "CafeteriaCashier";
	obj.push_back(NewObj);

	//Doorman
	meshList[Doorman] = MeshBuilder::GenerateOBJ("Doorman", "OBJ//Doorman.obj");
	meshList[Doorman]->textureID = LoadTGA("Image//Red_Apron.tga");
	meshList[Doorman]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Doorman]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Doorman]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Doorman]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[Doorman];
	NewObj->collisionBox.Centre = Vector3(-365, 90, -265);
	NewObj->size = Vector3(3, 3, 3);
	NewObj->name = "Doorman";
	obj.push_back(NewObj);

	LoadCansMesh();

	meshList[TEST] = MeshBuilder::GenerateCube("test", Color(1, 0, 1));

	//Display Circular cabinet
	/*meshList[DisplayCircular] = MeshBuilder::GenerateOBJ("DisplayCircular", "OBJ//DisplayCircular.obj");
	meshList[DisplayCircular]->textureID = LoadTGA("Image//DisplayCircular.tga");
	meshList[DisplayCircular]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[DisplayCircular]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[DisplayCircular]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[DisplayCircular]->material.kShininess = 5.f;
	NewObj->mesh = meshList[DisplayCircular];
	NewObj->Position = Vector3(0, 11, 0);
	NewObj->Size = Vector3(5, 5, 5);
	NewObj->rotation = 0.0f;
	NewObj->Rotation = Vector3(0, 1, 0);
	NewObj->Name = "Circular Cabinet";
	NewObj->Price = 0.00;
	obj.push_back(NewObj);*/

	//Door Stand
	meshList[eDoorStand] = MeshBuilder::GenerateOBJ("eDoorStand", "OBJ//doorStand.obj");
	meshList[eDoorStand]->textureID = LoadTGA("Image//metal.tga");
	meshList[eDoorStand]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorStand]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorStand]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorStand]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[eDoorStand];
	NewObj->collisionBox.Centre = Vector3(-340, 0, 130);
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorStand";
	obj.push_back(NewObj);

	//Door Button
	meshList[eDoorButton] = MeshBuilder::GenerateOBJ("eDoorButton", "OBJ//Button.obj");
	meshList[eDoorButton]->textureID = LoadTGA("Image//Button.tga");
	meshList[eDoorButton]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorButton]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorButton]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorButton]->material.kShininess = 5.f;
	
	NewObj = new Object;
	NewObj->mesh = meshList[eDoorButton];
	NewObj->collisionBox.Centre = Vector3(-339, 14, 130);
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorButton";
	obj.push_back(NewObj);

	//Door Stand
	meshList[eDoorStand2] = MeshBuilder::GenerateOBJ("eDoorStand2", "OBJ//doorStand.obj");
	meshList[eDoorStand2]->textureID = LoadTGA("Image//metal.tga");
	meshList[eDoorStand2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorStand2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorStand2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorStand2]->material.kShininess = 5.f;
	
	NewObj = new Object;
	NewObj->mesh = meshList[eDoorStand2];
	NewObj->collisionBox.Centre = Vector3(-340, 91, 130);
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorStand2";
	obj.push_back(NewObj);

	//Door Button
	meshList[eDoorButton2] = MeshBuilder::GenerateOBJ("eDoorButton2", "OBJ//Button.obj");
	meshList[eDoorButton2]->textureID = LoadTGA("Image//Button.tga");
	meshList[eDoorButton2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorButton2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorButton2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorButton2]->material.kShininess = 5.f;
	
	NewObj = new Object;
	NewObj->mesh = meshList[eDoorButton2];
	NewObj->collisionBox.Centre = Vector3(-339, 105, 130);
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorButton2";
	obj.push_back(NewObj);

	//CheckList
	meshList[CheckList] = MeshBuilder::GenerateQuad("CheckList", Color(1, 1, 1), 1, 1);

	//Inventory
	meshList[Inventory] = MeshBuilder::GenerateQuad("Inventory", Color(1, 1, 1), 10, 1);
	meshList[Inventory]->textureID = LoadTGA("Image//Inventory.tga");
}

void MyScene::LoadCansMesh()
{
	Gettable* newObj;
	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Can Texture ";
		texturepath += '1' + typecount;
		texturepath += ".tga";

		meshList[Shelf_Items + typecount] = MeshBuilder::GenerateOBJ("Can4", "OBJ//Can.obj");
		meshList[Shelf_Items + typecount]->textureID = LoadTGA(texturepath.c_str());
		meshList[Shelf_Items + typecount]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		meshList[Shelf_Items + typecount]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[Shelf_Items + typecount]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		meshList[Shelf_Items + typecount]->material.kShininess = 5.f;


		Vector3 shelf;
		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "shelf" && obj[count]->position == typecount)
				shelf= obj[count]->collisionBox.Centre;
		}

		for (float countx = -4, count = 0; countx < 5; countx++)
		{
			for (float county = 0; county < 5; county++)
			{
				for (float countz = -1; countz < 2; countz += 2)
				{	
					newObj = new Gettable();
					newObj->mesh = meshList[Shelf_Items + typecount];
					std::string name = "Can";
					name += '1' + typecount;
					newObj->name = name;
					newObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(1.6, 4, 1.6), Vector3(-1.6, 0, -1.6));
					newObj->size = Vector3(4, 4, 4);
					newObj->price = 2.00;
					newObj->collisionBox.Centre = Vector3(countx * 8, 2 + county * 8, countz * 7);
					newObj->collisionBox.Centre += shelf;
					newObj->position = count++;
					obj.push_back(newObj);
				}
			}
		}
	}
}
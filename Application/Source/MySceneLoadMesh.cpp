#include "MyScene.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include <fstream>	

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

	meshList[FENCE] = MeshBuilder::GenerateOBJ("fence", "OBJ//Fence.obj");
	meshList[FENCE]->textureID = LoadTGA("Image//metal.tga");
	meshList[FENCE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[FENCE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[FENCE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[FENCE]->material.kShininess = 1.f;

	meshList[ESCALATOR] = MeshBuilder::GenerateOBJ("escalator", "OBJ//travel.obj");
	meshList[ESCALATOR]->textureID = LoadTGA("Image//handle.tga");
	meshList[ESCALATOR]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ESCALATOR]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[ESCALATOR]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[ESCALATOR]->material.kShininess = 1.f;

	meshList[ESCALATOR_HANDLE] = MeshBuilder::GenerateOBJ("handle", "OBJ//TravelatorH.obj");
	meshList[ESCALATOR_HANDLE]->textureID = LoadTGA("Image//handle.tga");
	meshList[ESCALATOR_HANDLE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ESCALATOR_HANDLE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[ESCALATOR_HANDLE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[ESCALATOR_HANDLE]->material.kShininess = 1.f;

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

	meshList[Fridge] = MeshBuilder::GenerateOBJ("Fridge", "OBJ//Fridge.obj");
	meshList[Fridge]->textureID = LoadTGA("Image//Fridge.tga");
	meshList[Fridge]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[Fridge]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Fridge]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[Fridge]->material.kShininess = 3.f;

	for (int posZ = -150, count = 0; posZ <= 150; posZ += 75)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[Fridge];
			NewObj->name = "Fridge";
			NewObj->collisionBox = CollisionBox(Vector3(390, 0, posZ), Vector3(10, 10, 20), Vector3(-10, 0, -20));
			NewObj->size = Vector3(3, 3, 3);
			NewObj->angle = 180.0f;
			NewObj->rotation = Vector3(0, 1, 0);
			NewObj->position = count++;
			v.push_back(&NewObj->collisionBox);
			obj.push_back(NewObj);
		}

	//Fruitstand
	meshList[Fruitstand] = MeshBuilder::GenerateOBJ("Fruitstand", "OBJ//Fruitstand.obj");
	meshList[Fruitstand]->textureID = LoadTGA("Image//Fruits.tga");
	meshList[Fruitstand]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
	meshList[Fruitstand]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Fruitstand]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[Fruitstand]->material.kShininess = 3.f;

	for (int posX = 250, count = 0; posX >= 50; posX -= 50)
	{
		for (int posZ = -225; posZ <= 125; posZ += 75)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[Fruitstand];
			NewObj->name = "Fruitstand";
			NewObj->collisionBox = CollisionBox(Vector3(posX, 0, posZ), Vector3(10, 10, 10), Vector3(-10, 0, -5));
			NewObj->size = Vector3(4, 4, 4);
			NewObj->angle = -90.0f;
			NewObj->rotation = Vector3(0, 1, 0);
			NewObj->position = count++;
			v.push_back(&NewObj->collisionBox);
			obj.push_back(NewObj);
		}
	}

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
			v.push_back(&NewObj->collisionBox);
			obj.push_back(NewObj);
		}
	}

	meshList[CashierTable] = MeshBuilder::GenerateOBJ("CashierTable", "OBJ//CashierTable.obj");
	meshList[CashierTable]->textureID = LoadTGA("Image//CashierTable.tga");
	meshList[CashierTable]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[CashierTable]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[CashierTable]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[CashierTable]->material.kShininess = 5.f;


	for (int posX = 120, count = 0; count < 5; posX += 50)
	{
		NewObj = new Object;
		NewObj->mesh = meshList[CashierTable];
		NewObj->name = "Cashier Table";
		NewObj->collisionBox = CollisionBox(Vector3(posX, 0, 200), Vector3(10,15,20), Vector3(-10,0,-20));
		NewObj->size = Vector3(4,4,4);
		NewObj->angle = 180.0f;
		NewObj->rotation = Vector3(0, 1, 0);
		NewObj->position = count++;
		v.push_back(&NewObj->collisionBox);
		obj.push_back(NewObj);
		if (count == 5) emptyCashier = NewObj;
	}

	//Toy Shelves - 2nd Floor
	meshList[Toy_Shelves] = MeshBuilder::GenerateOBJ("Toy_Shelves", "OBJ//Toy_Shelf.obj");
	meshList[Toy_Shelves]->textureID = LoadTGA("Image//Toy_Shelf.tga");
	meshList[Toy_Shelves]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Toy_Shelves]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Toy_Shelves]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Toy_Shelves]->material.kShininess = 5.f;

	for (int posX = 250, count = 0; posX > 0; posX -= 50)
	{
		for (int posZ = 250; posZ >= 50; posZ -= 50)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[Toy_Shelves];
			NewObj->name = "Toy_Shelves";
			NewObj->collisionBox = CollisionBox(Vector3(posX, 90, posZ), Vector3(10, 40, 10), Vector3(-10, 0, -10));
			NewObj->size = Vector3(4, 4, 4);
			NewObj->position = count++;
			v.push_back(&NewObj->collisionBox);
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

	for (int posX = -300, count = 0; posX < -125; posX += 75)
	{
		for (int posZ = -150; posZ < 50; posZ += 75)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[TaC];
			NewObj->name = "TaC";
			NewObj->collisionBox = CollisionBox(Vector3(posX, 90, posZ), Vector3(15, 40, 10), Vector3(-20, 0, -12));
			NewObj->size = Vector3(3, 3, 3);
			NewObj->position = count++;
			v.push_back(&NewObj->collisionBox);
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
	v.push_back(&NewObj->collisionBox);
	obj.push_back(NewObj);

	////Clothes Racks - 2nd Floor
	meshList[ClothesRack] = MeshBuilder::GenerateOBJ("ClothesRack", "OBJ//ClothesRack.obj");
	meshList[ClothesRack]->textureID = LoadTGA("Image//Wood_Texture.tga");
	meshList[ClothesRack]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[ClothesRack]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[ClothesRack]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[ClothesRack]->material.kShininess = 5.f;

	for (int posX = 250, count = 0; posX > 0; posX -= 50)
	{
		for (int posZ = -50; posZ > -300; posZ -= 50)
		{
			NewObj = new Object;
			NewObj->mesh = meshList[ClothesRack];
			NewObj->name = "ClothesRack";
			NewObj->collisionBox = CollisionBox(Vector3(posX, 90, posZ), Vector3(10, 40, 10), Vector3(-10, 0, -10));
			NewObj->size = Vector3(4, 4, 4);
			NewObj->position = count++;
			v.push_back(&NewObj->collisionBox);
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
	v.push_back(&NewObj->collisionBox);
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

	for (int count = 0; count < 4; count++)
	{
		Character* cashier = new Character;
		cashier->mesh.push_back(MeshBuilder::GenerateOBJ("cashier", "OBJ//Head.obj"));
		cashier->mesh[0]->textureID = LoadTGA("Image//Face.tga");
		cashier->mesh[0]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		cashier->mesh[0]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		cashier->mesh[0]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		cashier->mesh[0]->material.kShininess = 5.f;
		cashier->mesh.push_back(MeshBuilder::GenerateOBJ("cashier", "OBJ//Body.obj"));
		cashier->mesh[1]->textureID = LoadTGA("Image//CashierShirt.tga");
		cashier->mesh[1]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		cashier->mesh[1]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		cashier->mesh[1]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		cashier->mesh[1]->material.kShininess = 5.f;
		cashier->mesh.push_back(MeshBuilder::GenerateOBJ("cashier", "OBJ//Limb.obj"));
		cashier->mesh[2]->textureID = LoadTGA("Image//CashierLimbs.tga");
		cashier->mesh[2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		cashier->mesh[2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		cashier->mesh[2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		cashier->mesh[2]->material.kShininess = 5.f;
		cashier->mesh.push_back(MeshBuilder::GenerateOBJ("cashier", "OBJ//Limb.obj"));
		cashier->mesh[3]->textureID = LoadTGA("Image//CashierLimbs.tga");
		cashier->mesh[3]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		cashier->mesh[3]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		cashier->mesh[3]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		cashier->mesh[3]->material.kShininess = 5.f;
		cashier->pos = Vector3(50 * count + 125, 0, 205);
		cashier->angle = -90;
		cashier->collisionBox.set(Vector3(cashier->pos), Vector3(15, 20, 15), Vector3(-15, 0, -15));
		cashiers.push_back(cashier);
		cashiersCollisionBox.push_back(&cashier->collisionBox);
	}

	{
		Character* customer = new Character;
		customer->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Head.obj"));
		customer->mesh[0]->textureID = LoadTGA("Image//Face.tga");
		customer->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Body.obj"));
		customer->mesh[1]->textureID = LoadTGA("Image//CustomerShirt1.tga");
		customer->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Limb.obj"));
		customer->mesh[2]->textureID = LoadTGA("Image//CustomerLimbs1.tga");
		customer->mesh.push_back(MeshBuilder::GenerateOBJ("customer", "OBJ//Limb.obj"));
		customer->mesh[3]->textureID = LoadTGA("Image//CustomerLimbs1.tga");

		customer->pos = Vector3(305, 0, 205);
		customer->angle = 90;
		MyScene::customer.push_back(customer);
	}

	//Restroom Wall - Back
	meshList[RestroomBack] = MeshBuilder::GenerateOBJ("RestroomBack", "OBJ//Restroom_Back.obj");
	meshList[RestroomBack]->textureID = LoadTGA("Image//Toilet.tga");
	meshList[RestroomBack]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[RestroomBack]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[RestroomBack]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[RestroomBack]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[RestroomBack];
	NewObj->collisionBox = CollisionBox(Vector3(350, 0, -275), Vector3(20, 40, -15), Vector3(-20, 0, -20));
	NewObj->angle = -90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->size = Vector3(4, 6, 4);
	NewObj->name = "RestroomBack";
	v.push_back(&NewObj->collisionBox);
	obj.push_back(NewObj);

	//Restroom Wall - Left
	meshList[RestroomLeft] = MeshBuilder::GenerateOBJ("RestroomLeft", "OBJ//Restroom_Left.obj");
	meshList[RestroomLeft]->textureID = LoadTGA("Image//Toilet.tga");
	meshList[RestroomLeft]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[RestroomLeft]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[RestroomLeft]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[RestroomLeft]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[RestroomLeft];
	NewObj->collisionBox = CollisionBox(Vector3(350, 0, -276), Vector3(-13, 40, 40), Vector3(-15, 0, -10));
	NewObj->angle = -90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->size = Vector3(4, 6, 4);
	NewObj->name = "RestroomLeft";
	v.push_back(&NewObj->collisionBox);
	obj.push_back(NewObj);

	//Restroom Wall - Right
	meshList[RestroomRight] = MeshBuilder::GenerateOBJ("RestroomRight", "OBJ//Restroom_Right.obj");
	meshList[RestroomRight]->textureID = LoadTGA("Image//Toilet.tga");
	meshList[RestroomRight]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[RestroomRight]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[RestroomRight]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[RestroomRight]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[RestroomRight];
	NewObj->collisionBox = CollisionBox(Vector3(350, 0, -276), Vector3(20, 40, 40), Vector3(15, 0, -10));
	NewObj->angle = -90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->size = Vector3(4, 6, 4);
	NewObj->name = "RestroomRight";
	v.push_back(&NewObj->collisionBox);
	obj.push_back(NewObj);

	//Restroom Wall - Top
	meshList[RestroomTop] = MeshBuilder::GenerateOBJ("RestroomTop", "OBJ//Restroom_Top.obj");
	meshList[RestroomTop]->textureID = LoadTGA("Image//Toilet.tga");
	meshList[RestroomTop]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[RestroomTop]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[RestroomTop]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[RestroomTop]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[RestroomTop];
	NewObj->collisionBox = CollisionBox(Vector3(350, 0, -276), Vector3(20, 50, 50), Vector3(-20, 46, -10));
	NewObj->angle = -90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->size = Vector3(4, 6, 4);
	NewObj->name = "RestroomTop";
	v.push_back(&NewObj->collisionBox);
	obj.push_back(NewObj);

	//Toiletbowl
	meshList[Toiletbowl] = MeshBuilder::GenerateOBJ("Toiletbowl", "OBJ//Toiletbowl.obj");
	meshList[Toiletbowl]->textureID = LoadTGA("Image//Pearly_White.tga");
	meshList[Toiletbowl]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Toiletbowl]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Toiletbowl]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Toiletbowl]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[Toiletbowl];
	NewObj->collisionBox = CollisionBox(Vector3(350, 0, -285), Vector3(1, 50, 2), Vector3(-2, 0, -10));
	NewObj->angle = -90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->size = Vector3(3.5, 3.5, 3.5);
	NewObj->name = "Toiletbowl";
	v.push_back(&NewObj->collisionBox);
	obj.push_back(NewObj);

	//Basin
	meshList[Basin] = MeshBuilder::GenerateOBJ("Basin", "OBJ//Basin.obj");
	meshList[Basin]->textureID = LoadTGA("Image//Pearly_White.tga");
	meshList[Basin]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[Basin]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[Basin]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[Basin]->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = meshList[Basin];
	NewObj->collisionBox = CollisionBox(Vector3(383, 0, -285), Vector3(1, 50, 2), Vector3(-2, 0, -10));
	NewObj->angle = -90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->size = Vector3(3.5, 3.5, 3.5);
	NewObj->name = "Basin";
	v.push_back(&NewObj->collisionBox);
	obj.push_back(NewObj);

	LoadDoorMesh();
	LoadElevatorMesh();
	
	LoadCansMesh();
	LoadDetergentMesh();
	LoadChocolateMesh();
	LoadAppleRedMesh();
	LoadAppleGreenMesh();
	LoadIceCreamMesh();
	LoadFRMesh();
	LoadPizzaMesh();
	LoadChipsMesh();
	LoadSugarMesh();
	LoadDreMesh();
	LoadBlueMesh();
	LoadGreenMesh();
	LoadRedMesh();
	LoadYellowMesh();

	//CheckList
	meshList[CheckList] = MeshBuilder::GenerateQuad("CheckList", Color(1, 1, 1), 1, 1);

	//Payment List
	meshList[PaymentList] = MeshBuilder::GenerateQuad("Payment", Color(1, 1, 1), 1, 1);

	//Inventory
	meshList[Inventory] = MeshBuilder::GenerateQuad("Inventory", Color(1, 1, 1), 10, 1);
	meshList[Inventory]->textureID = LoadTGA("Image//Inventory.tga");

	//Inventory Selector
	meshList[Selector] = MeshBuilder::GenerateQuad("Selector", Color(1, 1, 1), 1, 1);
	meshList[Selector]->textureID = LoadTGA("Image//Selector.tga");

	//Main Road
	meshList[road]= MeshBuilder::GenerateQuad("main road", Color(1, 1, 1), 15, 10);
	meshList[road] ->textureID = LoadTGA("Image//road.tga");
	
	NewObj = new Object;
	NewObj->mesh = MeshBuilder::GenerateOBJ("Car", "OBJ//Car.obj");
	NewObj->mesh->textureID = LoadTGA("Image//car.tga");
	NewObj->collisionBox = CollisionBox(Vector3(-40, 8, 710), 15, 10, 10);
	NewObj->size = Vector3(5, 5, 5);
	NewObj->angle = 90;
	NewObj->rotation = Vector3(0, 1, 0);
	obj.push_back(NewObj);
	car = NewObj;
	v.push_back(&NewObj->collisionBox);

	meshList[Car2] = MeshBuilder::GenerateOBJ("Car2", "OBJ//Car.obj");
	meshList[Car2]->textureID = LoadTGA("Image//car2.tga");

	meshList[Car3] = MeshBuilder::GenerateOBJ("Car3", "OBJ//Car.obj");
	meshList[Car3]->textureID = LoadTGA("Image//car3.tga");

	Mesh* paperbag = MeshBuilder::GenerateOBJ("paperbag", "OBJ//paperbag.obj");
	paperbag->textureID = LoadTGA("Image//paperbag.tga");
	paperbag->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	paperbag->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	paperbag->material.kSpecular.Set(1.f, 1.f, 1.f);
	paperbag->material.kShininess = 3.f;

	NewObj = new Gettable;
	NewObj->mesh = paperbag;
	NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0));
	NewObj->size = Vector3(1, 1, 1);
	NewObj->angle = 0;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "PaperBag";
	MyScene::paperbag = NewObj;

	meshList[TEST] = MeshBuilder::GenerateCube("test", Color(1, 0, 1), 0.1);
}

void MyScene::LoadElevatorMesh()
{
	Object* NewObj;

	//Elevator Door
	Mesh* door = MeshBuilder::GenerateOBJ("eDoor", "OBJ//Door.obj");
	door->textureID = LoadTGA("Image//metal.tga");
	door->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	door->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	door->material.kSpecular.Set(1.f, 1.f, 1.f);
	door->material.kShininess = 3.f;

	NewObj = new Object;
	NewObj->mesh = door;
	NewObj->collisionBox = CollisionBox(Vector3(-350, 0, 150), Vector3(0.5, 50, 15), Vector3(-0.5, 0, -15));
	NewObj->size = Vector3(4, 5, 1);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoor1";
	obj.push_back(NewObj);
	eDoor1 = NewObj;
	v.push_back(&NewObj->collisionBox);
	
	NewObj = new Object;
	NewObj->mesh = door;
	NewObj->collisionBox = CollisionBox(Vector3(-350, 90, 150), Vector3(0.5, 50, 15), Vector3(-0.5, 0, -15));
	NewObj->size = Vector3(4, 5, 1);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoor2";
	obj.push_back(NewObj);
	eDoor2 = NewObj;
	v.push_back(&NewObj->collisionBox);

	//Door Stand
	Mesh* stand = MeshBuilder::GenerateOBJ("eDoorStand", "OBJ//doorStand.obj");
	stand->textureID = LoadTGA("Image//metal.tga");
	stand->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	stand->material.kDiffuse.Set(1.f, 1.f, 1.f);
	stand->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	stand->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = stand;
	NewObj->collisionBox = CollisionBox(Vector3(-340, 0, 130), Vector3(3, 15, 3), Vector3(-3, 0, -3));
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorStand1";
	obj.push_back(NewObj);
	v.push_back(&NewObj->collisionBox);
	
	NewObj = new Object;
	NewObj->mesh = stand;
	NewObj->collisionBox = CollisionBox(Vector3(-340, 90, 130), Vector3(3, 15, 3), Vector3(-3, 0, -3));
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorStand2";
	obj.push_back(NewObj);
	v.push_back(&NewObj->collisionBox);

	//Door Button
	Mesh* button = MeshBuilder::GenerateOBJ("eDoorButton", "OBJ//Button.obj");
	button->textureID = LoadTGA("Image//Button.tga");
	button->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	button->material.kDiffuse.Set(1.f, 1.f, 1.f);
	button->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	button->material.kShininess = 5.f;

	NewObj = new Object;
	NewObj->mesh = button;
	NewObj->collisionBox = CollisionBox(Vector3(-339, 15, 130), 3, 3, 3);
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorButton1";
	obj.push_back(NewObj);
	eDoorButton1 = NewObj;

	NewObj = new Object;
	NewObj->mesh = button;
	NewObj->collisionBox = CollisionBox(Vector3(-339, 105, 130), 3, 3, 3);
	NewObj->size = Vector3(2, 2, 2);
	NewObj->angle = 90.0f;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "eDoorButton2";
	obj.push_back(NewObj);
	eDoorButton2 = NewObj;
}

void MyScene::LoadDoorMesh()
{
	Object* NewObj;

	Mesh* door = MeshBuilder::GenerateOBJ("door", "OBJ//Door.obj");
	door->textureID = LoadTGA("Image//blueglass.tga");
	door->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	door->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	door->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	door->material.kShininess = 10.f;

	NewObj = new Object;
	NewObj->mesh = door;
	NewObj->collisionBox = CollisionBox(Vector3(-35, 0, 300), Vector3(35, 70, 1), Vector3(-35, 0, 0));
	NewObj->size = Vector3(7, 7, 1);
	NewObj->angle = 0;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "DoorL";
	DoorL = NewObj;
	v.push_back(&NewObj->collisionBox);

	NewObj = new Object;
	NewObj->mesh = door;
	NewObj->collisionBox = CollisionBox(Vector3(35, 0, 300), Vector3(35, 70, 1), Vector3(-35, 0, 0));
	NewObj->size = Vector3(7, 7, 1);
	NewObj->angle = 0;
	NewObj->rotation = Vector3(0, 1, 0);
	NewObj->name = "DoorR";
	DoorR = NewObj;
	v.push_back(&NewObj->collisionBox);
}

void MyScene::LoadCansMesh()
{
	Gettable* newObj;
	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Can Texture ";
		texturepath += '1' + typecount;
		texturepath += ".tga";

		meshList[Shelf_Items + typecount] = MeshBuilder::GenerateOBJ("Can", "OBJ//Can.obj");
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
					newObj->name = name[typecount];
					newObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(1.6, 4, 1.6), Vector3(-1.6, 0, -1.6));
					newObj->size = Vector3(4, 4, 4);
					newObj->price = 2.00;
					newObj->collisionBox.Centre = Vector3(countx * 8, 2 + county * 8, countz * 7);
					newObj->collisionBox.Centre += shelf;
					newObj->position = count++;
					obj.push_back(newObj);
					shelfItems.push_back(newObj);
					shelfItemsCollisionBox.push_back(&(newObj->collisionBox));
				}
			}
		}
	}
}

void MyScene::LoadIceCreamMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//IceCream.tga ";
		texturepath += '1' + typecount;

		meshList[IceCream] = MeshBuilder::GenerateOBJ("IceCream", "OBJ//IceCream.obj");
		meshList[IceCream]->textureID = LoadTGA("Image//IceCream.tga");
		meshList[IceCream]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[IceCream]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[IceCream]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[IceCream]->material.kShininess = 3.f;

		Vector3 Fridge;

		for (int count = 0; count < obj.size(); count++)
			{
				if (obj[count]->name == "Fridge" && obj[count]->position == typecount)
					Fridge = obj[count]->collisionBox.Centre;
			}

		for (float countx = -1, count = 0; countx < 0; countx++)
			{
				for (float county = 1.3; county < 4.3; county++)
				{
					for (float countz = -2; countz < 4; countz += 2)
					{	
						NewObj = new Gettable();
						NewObj->mesh = meshList[IceCream];
						NewObj->name = "IceCream";
						NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
						NewObj->size = Vector3(3, 3, 3);
						NewObj->angle = -90.0f;
	                    NewObj->rotation = Vector3(0, 1, 0);
						NewObj->price = 5.00;
						NewObj->collisionBox.Centre = Vector3(countx * 2, county * 5, countz * 7);
						NewObj->collisionBox.Centre += Fridge;
						NewObj->position = count++;
						obj.push_back(NewObj);
					    IC.push_back(NewObj);
					    ICCollisionBox.push_back(&(NewObj->collisionBox));	
					}
				}
			}
	    }
}

void MyScene::LoadChocolateMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Chocolate.tga ";
		texturepath += '1' + typecount;

		meshList[Chocolate] = MeshBuilder::GenerateOBJ("Chocolate", "OBJ//Chocolate.obj");
		meshList[Chocolate]->textureID = LoadTGA("Image//Chocolate.tga");
		meshList[Chocolate]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[Chocolate]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[Chocolate]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[Chocolate]->material.kShininess = 3.f;

		Vector3 shelf;

		for (int count = 0; count < obj.size(); count++)
			{
				if (obj[count]->name == "shelf" && obj[count]->position == typecount)
					shelf = obj[count]->collisionBox.Centre;
			}

		for (float countx = 8, count = 0; countx < 10; countx++)
			{
				for (float county = 0; county < 5; county++)
				{
					for (float countz = -1; countz < 2; countz += 2)
					{	
						NewObj = new Gettable();
						NewObj->mesh = meshList[Chocolate];
						NewObj->name = "Chocolate";
						NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
						NewObj->size = Vector3(4, 4, 4);
						NewObj->price = 1.60;
						NewObj->collisionBox.Centre = Vector3(countx * 20, 2 + county * 8, countz * 7);
						NewObj->collisionBox.Centre += shelf;
						NewObj->position = count++;
						obj.push_back(NewObj); 
						shelfItems.push_back(NewObj);
						shelfItemsCollisionBox.push_back(&(NewObj->collisionBox));
					}
				}
			}
	    }
}

void MyScene::LoadDetergentMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Detergent.tga ";
		texturepath += '1' + typecount;

		meshList[Detergent] = MeshBuilder::GenerateOBJ("Detergent", "OBJ//Detergent.obj");
		meshList[Detergent]->textureID = LoadTGA("Image//Detergent.tga");
		meshList[Detergent]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[Detergent]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[Detergent]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[Detergent]->material.kShininess = 3.f;

		Vector3 shelf;

		for (int count = 0; count < obj.size(); count++)
			{
				if (obj[count]->name == "shelf" && obj[count]->position == typecount)
					shelf = obj[count]->collisionBox.Centre;
			}

		for (float countx = 6, count = 0; countx < 8; countx++)
			{
				for (float county = 0; county < 5; county++)
				{
					for (float countz = -1; countz < 2; countz += 2)
					{	
						NewObj = new Gettable();
						NewObj->mesh = meshList[Detergent];
						NewObj->name = "Detergent";
						NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
						NewObj->size = Vector3(1.5, 1.5, 1.5);
						NewObj->price = 3.60;
						NewObj->collisionBox.Centre = Vector3(countx * 20, 2 + county * 8, countz * 7);
						NewObj->collisionBox.Centre += shelf;
						NewObj->position = count++;
						obj.push_back(NewObj); 
						shelfItems.push_back(NewObj);
						shelfItemsCollisionBox.push_back(&(NewObj->collisionBox));
					}
				}
			}
	    }
}

void MyScene::LoadAppleRedMesh()
{
	Gettable* newObj;
	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//AppleRed.tga";
		texturepath += '1' + typecount;

		meshList[AppleRed] = MeshBuilder::GenerateOBJ("AppleRed", "OBJ//AppleRed.obj");
	    meshList[AppleRed]->textureID = LoadTGA("Image//AppleRed.tga");
		meshList[AppleRed]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		meshList[AppleRed]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[AppleRed]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		meshList[AppleRed]->material.kShininess = 5.f;

		Vector3 Fruitstand;
		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "Fruitstand" && obj[count]->position == typecount)
				Fruitstand = obj[count]->collisionBox.Centre;
		}

		for (float countx = -4.14, count = 0; countx < 0; countx++)
		{
			for (float county = 1.4; county < 2; county++)
			{
				for (float countz = 0.125; countz < 1; countz++)
				{	
					newObj = new Gettable();
					newObj->mesh = meshList[AppleRed];
					newObj->name = "Red Apple";
					newObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(1.6, 4, 1.6), Vector3(-1.6, 0, -1.6));
					newObj->size = Vector3(1, 1, 1);
					newObj->price = 1.00;
					newObj->collisionBox.Centre = Vector3(countx * 50, county * 8, countz * 50);
					newObj->collisionBox.Centre += Fruitstand;
					newObj->position = count++;
					obj.push_back(newObj);
					Apple.push_back(newObj);
					AppleCollisionBox.push_back(&(newObj->collisionBox));
				}
			}
		}
	}
}

void MyScene::LoadAppleGreenMesh()
{
	Gettable* newObj;
	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//AppleGreen.tga";
		texturepath += '1' + typecount;

		meshList[AppleGreen] = MeshBuilder::GenerateOBJ("AppleGreen", "OBJ//AppleGreen.obj");
		meshList[AppleGreen]->textureID = LoadTGA("Image//AppleGreen.tga");
		meshList[AppleGreen]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		meshList[AppleGreen]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[AppleGreen]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		meshList[AppleGreen]->material.kShininess = 5.f;

		Vector3 Fruitstand;
		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "Fruitstand" && obj[count]->position == typecount)
				Fruitstand = obj[count]->collisionBox.Centre;
		}

		for (float countx = -4, count = 0; countx < 1; countx++)
		{
			for (float county = 1.5; county < 2; county++)
			{
				for (float countz = 0.125; countz < 1; countz++)
				{	
					newObj = new Gettable();
					newObj->mesh = meshList[AppleGreen];
					newObj->name = "Green Apple";
					newObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(1.6, 4, 1.6), Vector3(-1.6, 0, -1.6));
					newObj->size = Vector3(1, 1, 1);
					newObj->price = 1.00;
					newObj->collisionBox.Centre = Vector3(countx * 50, county * 8, countz * 50);
					newObj->collisionBox.Centre += Fruitstand;
					newObj->position = count++;
					obj.push_back(newObj);
					Apple.push_back(newObj);
					AppleCollisionBox.push_back(&(newObj->collisionBox));
				}
			}
		}
	}
}

void MyScene::LoadFRMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//FerreroRocher.tga ";
		texturepath += '1' + typecount;

		meshList[FerreroRocher] = MeshBuilder::GenerateOBJ("FerreroRocher", "OBJ//FerreroRocher.obj");
		meshList[FerreroRocher]->textureID = LoadTGA("Image//FerreroRocher.tga");
		meshList[FerreroRocher]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[FerreroRocher]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[FerreroRocher]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[FerreroRocher]->material.kShininess = 3.f;

		Vector3 Toy_Shelves;

		for (int count = 0; count < obj.size(); count++)
			{
				if (obj[count]->name == "Toy_Shelves" && obj[count]->position == typecount)
					Toy_Shelves = obj[count]->collisionBox.Centre;
			}

		for (float countx = -0.5, count = 0; countx < 1.5; countx++)
			{
				for (float county = 0; county < 4; county++)
				{
					for (float countz = -2; countz < 4; countz += 2)
					{	
						NewObj = new Gettable();
						NewObj->mesh = meshList[FerreroRocher];
						NewObj->name = "FerreroRocher";
						NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
						NewObj->size = Vector3(3, 3, 3);
						NewObj->angle = -90.0f;
	                    NewObj->rotation = Vector3(0, 1, 0);
						NewObj->price = 8.00;
						NewObj->collisionBox.Centre = Vector3(countx * 10, 2 + county * 7.3, countz * 4);
						NewObj->collisionBox.Centre += Toy_Shelves;
						NewObj->position = count++;
					    FR.push_back(NewObj);
					    FRCollisionBox.push_back(&(NewObj->collisionBox));	
						obj.push_back(NewObj);
					}
				}
			}
	    }
}

void MyScene::LoadPizzaMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Pizza.tga ";
		texturepath += '1' + typecount;

		meshList[Pizza] = MeshBuilder::GenerateOBJ("Pizza", "OBJ//Pizza.obj");
		meshList[Pizza]->textureID = LoadTGA("Image//Pizza.tga");
		meshList[Pizza]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[Pizza]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[Pizza]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[Pizza]->material.kShininess = 3.f;

		Vector3 Toy_Shelves;

		for (int count = 0; count < obj.size(); count++)
			{
				if (obj[count]->name == "Toy_Shelves" && obj[count]->position == typecount)
					Toy_Shelves = obj[count]->collisionBox.Centre;
			}

		for (float countx = -5.5, count = 0; countx < -3.5; countx++)
			{
				for (float county = 0; county < 4; county++)
				{
					for (float countz = -2; countz < 4; countz += 2)
					{	
						NewObj = new Gettable();
						NewObj->mesh = meshList[Pizza];
						NewObj->name = "Pizza";
						NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
						NewObj->size = Vector3(3, 3, 3);
						NewObj->angle = -90.0f;
	                    NewObj->rotation = Vector3(0, 1, 0);
						NewObj->price = 8.00;
						NewObj->collisionBox.Centre = Vector3(countx * 10, 2 + county * 7.2, countz * 4);
						NewObj->collisionBox.Centre += Toy_Shelves;
						NewObj->position = count++;
					    pizza.push_back(NewObj);
					    pizzaCollisionBox.push_back(&(NewObj->collisionBox));	
						obj.push_back(NewObj);
					}
				}
			}
	    }
}

void MyScene::LoadChipsMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//LaysChips.tga ";
		texturepath += '1' + typecount;

		meshList[LaysChips] = MeshBuilder::GenerateOBJ("LaysChips", "OBJ//LaysChips.obj");
		meshList[LaysChips]->textureID = LoadTGA("Image//LaysChips.tga");
		meshList[LaysChips]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[LaysChips]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[LaysChips]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[LaysChips]->material.kShininess = 3.f;

		Vector3 Toy_Shelves;

		for (int count = 0; count < obj.size(); count++)
			{
				if (obj[count]->name == "Toy_Shelves" && obj[count]->position == typecount)
					Toy_Shelves = obj[count]->collisionBox.Centre;
			}

		for (float countx = -10.5, count = 0; countx < -8.5; countx++)
			{
				for (float county = 0; county < 4; county++)
				{
					for (float countz = -2; countz < 4; countz += 2)
					{	
						NewObj = new Gettable();
						NewObj->mesh = meshList[LaysChips];
						NewObj->name = "LaysChips";
						NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
						NewObj->size = Vector3(4, 4, 4);
						NewObj->angle = -90.0f;
	                    NewObj->rotation = Vector3(0, 1, 0);
						NewObj->price = 1.20;
						NewObj->collisionBox.Centre = Vector3(countx * 10, 2 + county * 7.2, countz * 4);
						NewObj->collisionBox.Centre += Toy_Shelves;
						NewObj->position = count++;
					    Chips.push_back(NewObj);
					    ChipsCollisionBox.push_back(&(NewObj->collisionBox));	
						obj.push_back(NewObj);
					}
				}
			}
	    }
}

void MyScene::LoadSugarMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Sugar.tga ";
		texturepath += '1' + typecount;

		meshList[Sugar] = MeshBuilder::GenerateOBJ("Sugar", "OBJ//Sugar.obj");
		meshList[Sugar]->textureID = LoadTGA("Image//Sugar.tga");
		meshList[Sugar]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[Sugar]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[Sugar]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[Sugar]->material.kShininess = 3.f;

		Vector3 Toy_Shelves;

		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "Toy_Shelves" && obj[count]->position == typecount)
				Toy_Shelves = obj[count]->collisionBox.Centre;
		}

		for (float countx = -15.25, count = 0; countx < -13.25; countx++)
		{
			for (float county = 0; county < 4; county++)
			{
				for (float countz = -2; countz < 4; countz += 2)
				{	
					NewObj = new Gettable();
					NewObj->mesh = meshList[Sugar];
					NewObj->name = "Sugar";
					NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
					NewObj->size = Vector3(1.5, 1.5, 1.5);
					NewObj->angle = -90.0f;
					NewObj->rotation = Vector3(0, 1, 0);
					NewObj->price = 0.80;
					NewObj->collisionBox.Centre = Vector3(countx * 10.2, 2 + county * 7.2, countz * 4);
					NewObj->collisionBox.Centre += Toy_Shelves;
					NewObj->position = count++;
					sugar.push_back(NewObj);
					sugarCollisionBox.push_back(&(NewObj->collisionBox));	
					obj.push_back(NewObj);
				}
			}
		}
	}
}

void MyScene::LoadDreMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Dre.tga ";
		texturepath += '1' + typecount;

		meshList[Dre] = MeshBuilder::GenerateOBJ("Dre", "OBJ//Dre.obj");
		meshList[Dre]->textureID = LoadTGA("Image//Dre.tga");
		meshList[Dre]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[Dre]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[Dre]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[Dre]->material.kShininess = 3.f;

		Vector3 Toy_Shelves;

		for (int count = 0; count < obj.size(); count++)
			{
				if (obj[count]->name == "Toy_Shelves" && obj[count]->position == typecount)
					Toy_Shelves = obj[count]->collisionBox.Centre;
			}
		
		for (float countx = -25.5, count = 0; countx < -23.5; countx++)
			{
				for (float county = 0; county < 3.5; county++)
				{
					for (float countz = -2; countz < 3; countz += 2)
					{	
						NewObj = new Gettable();
						NewObj->mesh = meshList[Dre];
						NewObj->name = "Dre";
						NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
						NewObj->size = Vector3(3, 3, 3);
						NewObj->angle = -90.0f;
	                    NewObj->rotation = Vector3(0, 1, 0);
						NewObj->price = 0.80;
						NewObj->collisionBox.Centre = Vector3(countx * 8, 2 + county * 7, countz * 4);
						NewObj->collisionBox.Centre += Toy_Shelves;
						NewObj->position = count++;
					    dre.push_back(NewObj);
					    dreCollisionBox.push_back(&(NewObj->collisionBox));	
						obj.push_back(NewObj);
					}
				}
			}
	    }
}

void MyScene::LoadBlueMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//BlueShirt.tga ";
		texturepath += '1' + typecount;

		meshList[ShirtBlue] = MeshBuilder::GenerateOBJ("Blue", "OBJ//ShirtBlue.obj");
		meshList[ShirtBlue]->textureID = LoadTGA("Image//BlueShirt.tga");
		meshList[ShirtBlue]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[ShirtBlue]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[ShirtBlue]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[ShirtBlue]->material.kShininess = 3.f;

		Vector3 ClothesRack;

		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "ClothesRack" && obj[count]->position == typecount)
				ClothesRack = obj[count]->collisionBox.Centre;
		}

		for (float countx = -4, count = 0; countx < 1; countx++)
		{
			for (float county = 0.31; county < 0.41; county++)
			{
				for (float countz = 3; countz < 8; countz += 2)
				{	
					NewObj = new Gettable();
					NewObj->mesh = meshList[ShirtBlue];
					NewObj->name = "Blue";
					NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
					NewObj->size = Vector3(3, 3, 3);
					NewObj->angle = -90.0f;
					NewObj->rotation = Vector3(0, 1, 0);
					NewObj->price = 21.00;
					NewObj->collisionBox.Centre = Vector3(countx * 50, county * 10, countz * 1);
					NewObj->collisionBox.Centre += ClothesRack;
					NewObj->position = count++;
					Blue.push_back(NewObj);
					BlueCollisionBox.push_back(&(NewObj->collisionBox));	
					obj.push_back(NewObj);
				}
			}
		}
	}
}

void MyScene::LoadGreenMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//GreenShirt.tga ";
		texturepath += '1' + typecount;

		meshList[ShirtGreen] = MeshBuilder::GenerateOBJ("Green", "OBJ//ShirtGreen.obj");
		meshList[ShirtGreen]->textureID = LoadTGA("Image//GreenShirt.tga");
		meshList[ShirtGreen]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[ShirtGreen]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[ShirtGreen]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[ShirtGreen]->material.kShininess = 3.f;

		Vector3 ClothesRack;

		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "ClothesRack" && obj[count]->position == typecount)
				ClothesRack = obj[count]->collisionBox.Centre;
		}

		for (float countx = 5, count = 0; countx < 8; countx++)
		{
			for (float county = 0.1; county < 0.2; county++)
			{
				for (float countz = 0; countz < 2; countz += 2)
				{	
					NewObj = new Gettable();
					NewObj->mesh = meshList[ShirtGreen];
					NewObj->name = "Green";
					NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
					NewObj->size = Vector3(3, 3, 3);
					//NewObj->angle = -90.0f;
					//NewObj->rotation = Vector3(0, 1, 0);
					NewObj->price = 21.00;
					NewObj->collisionBox.Centre = Vector3(countx * 1, county * 10, countz * 20);
					NewObj->collisionBox.Centre += ClothesRack;
					NewObj->position = count++;
					Green.push_back(NewObj);
					GreenCollisionBox.push_back(&(NewObj->collisionBox));	
					obj.push_back(NewObj);
				}
			}
		}
	}
}

void MyScene::LoadYellowMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//YellowShirt.tga ";
		texturepath += '1' + typecount;

		meshList[ShirtYellow] = MeshBuilder::GenerateOBJ("Yellow", "OBJ//ShirtYellow.obj");
		meshList[ShirtYellow]->textureID = LoadTGA("Image//YellowShirt.tga");
		meshList[ShirtYellow]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[ShirtYellow]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[ShirtYellow]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[ShirtYellow]->material.kShininess = 3.f;

		Vector3 ClothesRack;

		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "ClothesRack" && obj[count]->position == typecount)
				ClothesRack = obj[count]->collisionBox.Centre;
		}

		for (float countx = -207, count = 0; countx < -204; countx++)
		{
			for (float county = 0.5; county < 0.6; county++)
			{
				for (float countz = 0; countz < 2; countz += 2)
				{	
					NewObj = new Gettable();
					NewObj->mesh = meshList[ShirtYellow];
					NewObj->name = "Yellow";
					NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
					NewObj->size = Vector3(3, 3, 3);
					NewObj->price = 21.00;
					NewObj->collisionBox.Centre = Vector3(countx * 1, 2 + county * 7, countz * 4);
					NewObj->collisionBox.Centre += ClothesRack;
					NewObj->position = count++;
					Yellow.push_back(NewObj);
					YellowCollisionBox.push_back(&(NewObj->collisionBox));	
					obj.push_back(NewObj);
				}
			}
		}
	}
}

void MyScene::LoadRedMesh()
{
	Gettable* NewObj;

	for (int typecount = 0; typecount < 5; typecount++)
	{
		std::string texturepath = "Image//Red.tga ";
		texturepath += '1' + typecount;

		meshList[ShirtRed] = MeshBuilder::GenerateOBJ("Red", "OBJ//ShirtRed.obj");
		meshList[ShirtRed]->textureID = LoadTGA("Image//Red.tga");
		meshList[ShirtRed]->material.kAmbient.Set(0.25f, 0.25f, 0.25f);
		meshList[ShirtRed]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[ShirtRed]->material.kSpecular.Set(1.f, 1.f, 1.f);
		meshList[ShirtRed]->material.kShininess = 3.f;

		Vector3 ClothesRack;

		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count]->name == "ClothesRack" && obj[count]->position == typecount)
				ClothesRack = obj[count]->collisionBox.Centre;
		}

		for (float countx = -4, count = 0; countx < 1; countx++)
		{
			for (float county = 0.75; county < 0.85; county++)
			{
				for (float countz = -8; countz < -2; countz += 2)
				{	
					NewObj = new Gettable();
					NewObj->mesh = meshList[ShirtRed];
					NewObj->name = "Red";
					NewObj->collisionBox = CollisionBox(Vector3(0, 0, 0), Vector3(10, 10, 5), Vector3(-10, 0, -5));
					NewObj->size = Vector3(3, 3, 3);
					NewObj->angle = -90.0f;
					NewObj->rotation = Vector3(0, 1, 0);
					NewObj->price = 21.00;
					NewObj->collisionBox.Centre = Vector3(countx * 50, county * 10, countz * 1);
					NewObj->collisionBox.Centre += ClothesRack;
					NewObj->position = count++;
					Red.push_back(NewObj);
					RedCollisionBox.push_back(&(NewObj->collisionBox));	
					obj.push_back(NewObj);
				}
			}
		}
	}
}


















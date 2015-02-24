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
	NewObj.collisionBox.Centre = Vector3(-100, 0, 0);
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
	NewObj.name = "shelf";
	NewObj.collisionBox.Max = Vector3(50, 40, 10);
	NewObj.collisionBox.Min = Vector3(-50, 0, -10);
	NewObj.size = Vector3(4, 4, 4);

	for (int posX = -300, count = 0; posX <= -150; posX += 150)
	{
		for (int posZ = -250; posZ <= 75; posZ += 75)
		{
			NewObj.collisionBox.Centre = Vector3(posX, 0, posZ);
			NewObj.position = count++;
			v.push_back(NewObj.collisionBox);
			obj.push_back(NewObj);
		}
	}

	LoadCansMesh();

	meshList[TEST] = MeshBuilder::GenerateCube("test", Color(1, 0, 1));

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

	//Door Stand
	meshList[eDoorStand] = MeshBuilder::GenerateOBJ("eDoorStand", "OBJ//doorStand.obj");
	meshList[eDoorStand]->textureID = LoadTGA("Image//metal.tga");
	meshList[eDoorStand]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorStand]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorStand]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorStand]->material.kShininess = 5.f;
	NewObj.mesh = meshList[eDoorStand];
	NewObj.collisionBox.Centre = Vector3(-340, 0, 130);
	NewObj.size = Vector3(2, 2, 2);
	NewObj.angle = 90.0f;
	NewObj.rotation = Vector3(0, 1, 0);
	NewObj.name = "eDoorStand";
	NewObj.price = 0.00;
	obj.push_back(NewObj);

	//Door Button
	meshList[eDoorButton] = MeshBuilder::GenerateOBJ("eDoorButton", "OBJ//Button.obj");
	meshList[eDoorButton]->textureID = LoadTGA("Image//Button.tga");
	meshList[eDoorButton]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorButton]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorButton]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorButton]->material.kShininess = 5.f;
	NewObj.mesh = meshList[eDoorButton];
	NewObj.collisionBox.Centre = Vector3(-339, 14, 130);
	NewObj.size = Vector3(2, 2, 2);
	NewObj.angle = 90.0f;
	NewObj.rotation = Vector3(0, 1, 0);
	NewObj.name = "eDoorButton";
	NewObj.price = 0.00;
	obj.push_back(NewObj);

	//Door Stand
	meshList[eDoorStand2] = MeshBuilder::GenerateOBJ("eDoorStand2", "OBJ//doorStand.obj");
	meshList[eDoorStand2]->textureID = LoadTGA("Image//metal.tga");
	meshList[eDoorStand2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorStand2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorStand2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorStand2]->material.kShininess = 5.f;
	NewObj.mesh = meshList[eDoorStand2];
	NewObj.collisionBox.Centre = Vector3(-340, 91, 130);
	NewObj.size = Vector3(2, 2, 2);
	NewObj.angle = 90.0f;
	NewObj.rotation = Vector3(0, 1, 0);
	NewObj.name = "eDoorStand2";
	NewObj.price = 0.00;
	obj.push_back(NewObj);

	//Door Button
	meshList[eDoorButton2] = MeshBuilder::GenerateOBJ("eDoorButton2", "OBJ//Button.obj");
	meshList[eDoorButton2]->textureID = LoadTGA("Image//Button.tga");
	meshList[eDoorButton2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[eDoorButton2]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[eDoorButton2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[eDoorButton2]->material.kShininess = 5.f;
	NewObj.mesh = meshList[eDoorButton2];
	NewObj.collisionBox.Centre = Vector3(-339, 105, 130);
	NewObj.size = Vector3(2, 2, 2);
	NewObj.angle = 90.0f;
	NewObj.rotation = Vector3(0, 1, 0);
	NewObj.name = "eDoorButton2";
	NewObj.price = 0.00;
	obj.push_back(NewObj);
}

void MyScene::LoadCansMesh()
{
	for (int typecount = 0; typecount < 5; typecount++)
	{
		Object newObj;
		std::string texturepath = "Image//Can Texture ";
		texturepath += '1' + typecount;
		texturepath += ".tga";

		meshList[Shelf_Items + typecount] = MeshBuilder::GenerateOBJ("Can4", "OBJ//Can.obj");
		meshList[Shelf_Items + typecount]->textureID = LoadTGA(texturepath.c_str());
		meshList[Shelf_Items + typecount]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
		meshList[Shelf_Items + typecount]->material.kDiffuse.Set(1.f, 1.f, 1.f);
		meshList[Shelf_Items + typecount]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
		meshList[Shelf_Items + typecount]->material.kShininess = 5.f;

		newObj.mesh = meshList[Shelf_Items + typecount];
		newObj.name = "Can" + ('1' + typecount);
		newObj.collisionBox = CollisionBox(Vector3(0, 0, 0), .8f, 1, .8f);
		newObj.size = Vector3(4, 4, 4);
		newObj.price = 2.00;

		Vector3 shelf;
		for (int count = 0; count < obj.size(); count++)
		{
			if (obj[count].name == "shelf" && obj[count].position == typecount)
				shelf= obj[count].collisionBox.Centre;
		}

		for (float countx = -4, count = 0; countx < 5; countx++)
		{
			for (float county = 0; county < 4; county++)
			{
				for (float countz = -1; countz < 2; countz += 2)
				{	
					newObj.collisionBox.Centre = Vector3(countx * 8, 2 + county * 8, countz * 7);
					newObj.collisionBox.Centre += shelf;
					newObj.position = count++;
					obj.push_back(newObj);
				}
			}
		}
	}
}
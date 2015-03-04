#include "MyScene.h"
#include "newScene.h"
#include "GL\glew.h"
#include "Utility.h"
#include "Application.h"

#include "shader.hpp"

void MyScene::Render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render VBO here

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	if(light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}

	else if(light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}

	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}


	if(light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace1 = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace1.x);
	}

	else if(light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);
		Vector3 spotDirection_cameraspace1 = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace1.x);
	}

	else
	{
		Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);
	}

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	//Render Exterior Buildings
	modelStack.PushMatrix(); {
		RenderBuildings();
	}modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(-200, 0, 0);
		modelStack.Rotate(90, 0, 1, 0);
		RenderBuildings();
	}modelStack.PopMatrix();
	modelStack.PushMatrix(); {
		modelStack.Translate(0, 0, 200);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderBuildings();
	}modelStack.PopMatrix();

	modelStack.PushMatrix();{
	RenderRoad();
	}modelStack.PopMatrix();

	modelStack.PushMatrix();{
		modelStack.Translate(-500, 0, 0);
		modelStack.Translate(translateCarX, 8, 610);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderCar();
	}modelStack.PopMatrix();

	modelStack.PushMatrix();{
		modelStack.Translate(-40, 8, 710);
		modelStack.Rotate(90, 0, 1, 0);
		RenderPCar();
	}modelStack.PopMatrix();

	RenderSkyBox();

	modelStack.PushMatrix();
	modelStack.Translate(-220, 0, 260);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(float(90) - 32.735, -1, 0, 0);
	modelStack.Scale(80, 166.43, 0);
	modelStack.Translate(0, 0.5, 0);
	RenderMesh(meshList[ESCALATOR], false);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(-280, 40, 260);
	//modelStack.Rotate(-10, 0, 0, 1);
	//modelStack.Scale(18, 14, 10);
	//modelStack.Translate(-0.5, 0.5, 0);
	//RenderMesh(meshList[ESCALATOR_HANDLE], false);
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-374, 0, 150);
	modelStack.Scale(5, 6.5, 5);
	RenderMesh(meshList[ELEVATOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-374, 90, 150);
	modelStack.Scale(5, 6.5, 5);
	RenderMesh(meshList[ELEVATOR], true);
	modelStack.PopMatrix();


	RenderObjects();

	RenderInterior();
	RenderDoor();
	RenderCharacter(cashiers);
	RenderCharacter(shelfCharacters);

	RenderExterior();
	
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + to_string(fps), Color(0, 0, 0), 2, 30, 29.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "X:" + to_string(camera.position.x), Color(1, 0, 1), 2, 1, 24.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y:" + to_string(camera.position.y), Color(1, 0, 1), 2, 1, 25.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z:" + to_string(camera.position.z), Color(1, 0, 1), 2, 1, 26.5);

	RenderTextOnScreen(meshList[GEO_TEXT], "TargetX:" + to_string(camera.target.x), Color(0, 0, 0), 2, 1, 27.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "TargetY:" + to_string(camera.target.y), Color(0, 0, 0), 2, 1, 28.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "TargetZ:" + to_string(camera.target.z), Color(0, 0, 0), 2, 1, 29.5);

	if (targeted(eDoorButton1->collisionBox) || targeted(eDoorButton2->collisionBox))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Click to open door", Color(1, 1, 0), 3, 1, 19);
	}
	
	if ((targeted(eDoor1->collisionBox) || targeted(eDoor2->collisionBox)))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Click to open door", Color(1, 1, 0), 3, 1, 19);
	}

	//Elevator Interaction
	if (camera.position.x < -360 && camera.position.y < 42 && camera.position.z < 160 && camera.position.z > 140)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press UP Arrow Key to go Level 2", Color(1, 1, 0), 2, 1, 19);
	}
	else if (camera.position.x < -360 && camera.position.y > 42 && camera.position.z < 160 && camera.position.z > 140)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press DOWN Arrow Key to go Level 1", Color(1, 1, 0), 2, 1, 19);
	}
	
	//Toilet Interaction
	
	/*if (targeted(ToiletDoor->collisionBox))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Click to Open Door.", Color(1, 1, 0), 3, 1, 19);
	}

	if (TDoorLocked == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Unlock Door first.", Color(1, 1, 0), 3, 1, 19);
	}*/

	for (int i = 0; i < obj.size(); i++)
	{
		if ((obj[i]->name == "Toiletbowl") && (camera.target.x < obj[i]->collisionBox.Centre.x + 30) && (camera.target.x > obj[i]->collisionBox.Centre.x - 10) && (camera.target.y < obj[i]->collisionBox.Centre.y + 25) && (camera.target.y > obj[i]->collisionBox.Centre.y - 5) && (camera.target.z < obj[i]->collisionBox.Centre.z + 20) && (camera.target.z > obj[i]->collisionBox.Centre.z - 20))
		{
			if (ToiletUsed == false)
			{
			    RenderTextOnScreen(meshList[GEO_TEXT], "Click to use the toilet", Color(1, 1, 0), 3, 1, 19);
			}

			else if (ToiletUsed == true)
			{
			    RenderTextOnScreen(meshList[GEO_TEXT], "Press F to flush and Stand up", Color(1, 1, 0), 3, 1, 19);
			}
		}
	}

	/*for (int i = 0; i < obj.size(); i++)
	{
		if ((obj[i]->name == "ToiletDoor") && (camera.target.x < obj[i]->collisionBox.Centre.x + 30) && (camera.target.x > obj[i]->collisionBox.Centre.x - 10) && (camera.target.y < obj[i]->collisionBox.Centre.y + 25) && (camera.target.y > obj[i]->collisionBox.Centre.y - 5) && (camera.target.z < obj[i]->collisionBox.Centre.z + 20) && (camera.target.z > obj[i]->collisionBox.Centre.z - 20))
		{

		}
	}*/

	RenderTargetDetails();
	if (checklistout == false)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'P'", Color(1, 0, 0), 2, 31, 17);
		RenderTextOnScreen(meshList[GEO_TEXT], "for", Color(1, 0, 0), 2, 31, 16);
		RenderTextOnScreen(meshList[GEO_TEXT], "Checklist.", Color(1, 0, 0), 2, 31, 15);
	}
	else if (checklistout == true)
	{
		RenderOnScreen();
		RenderCheckList();
	}
	//Player Name
	RenderTextOnScreen(meshList[GEO_TEXT], "Hi" + PlayerName, Color(1, 0, 0), 3, 1, 18);
	RenderTextOnScreen(meshList[GEO_TEXT], "Reply:" + Answer, Color(1, 0, 0), 3, 1, 17);

	for (int xPos = 1, count = 0; count < PNameList.size(); xPos++, count++)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], to_string(PNameList[count]), Color(1, 0, 0), 3, xPos, 14);
	}
	if (insert == false && talk == false)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Home' to edit your name.", Color(0, 0, 0), 2, 1, 23);
	}
	else if (insert == true && talk == false)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Home' to lock in your name.", Color(0, 0, 0), 2, 1, 23);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Backspace' to delete a character.", Color(0, 0, 0), 2, 1, 22);
	}
	//AI Dialogue
	srand(time(NULL));
	random_shuffle(message.begin(), message.end());
	for (int i = 0; i < message.size(); i++)
	{
		dialogue.push_back(message[i]);
	}
	for (int xPos = 1, count = 0; count < LetterList.size(); xPos++, count++)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], to_string(LetterList[count]), Color(1, 0, 0), 3, xPos, 14);
	}
	for (int count = 0; count < shelfCharacters.size(); count++)
	{
		Character character(*shelfCharacters[count]);
		if (talk == false && camera.position.x < character.pos.x + 20 && camera.position.x > character.pos.x - 20 && camera.position.z < character.pos.z + 20 && camera.position.z > character.pos.z - 20)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Click to interact.", Color(0, 0, 0), 2, 11, 19);
		}
	}

	if (talk == true && insertL == false)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue[0], Color(0, 0, 0), 3, 11, 12);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Enter' to insert reply.", Color(0, 0, 0), 2, 1, 23);
	}
	else if (insertL == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Enter' to lock in response.", Color(0, 0, 0), 2, 1, 23);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Backspace' to delete a character.", Color(0, 0, 0), 2, 1, 22	);
	}
	
	//Crosshair
	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 5, 8.3, 6);
	
	RenderInventory();

	if (!completeInventory) RenderTextOnScreen(meshList[GEO_TEXT], "You don't have all the items in the checklist", Color(0, 1, 0), 5, 8.3, 6);
	else if (!enoughmoney) RenderTextOnScreen(meshList[GEO_TEXT], "Not Enough Money", Color(0, 1, 0), 5, 8.3, 6);

	if (gameover) RenderTextOnScreen(meshList[GEO_TEXT], "GAMEOVER!", Color(0, 1, 0), 5, 8.3, 6);
}

void MyScene::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 modelView, modelView_inverse_transpose;

	load();
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void MyScene::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void MyScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void MyScene::RenderOnScreen()
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode

	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, meshList[CheckList]->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	modelStack.PushMatrix();
	modelStack.Translate(70, 20, 0);
	modelStack.Scale(20, 30, 1);
	RenderMesh(meshList[CheckList], false);
	modelStack.PopMatrix();


	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
}

void MyScene::RenderInterior()
{
	modelStack.PushMatrix(); {
		modelStack.Scale(20, 20, 20);

		RenderMesh(meshList[INT_WALL], false);
		RenderMesh(meshList[INT_FLOOR], false);
		RenderMesh(meshList[WHITE_GLASS], false);
	} modelStack.PopMatrix();
}

void MyScene::RenderExterior()
{
	modelStack.PushMatrix(); {
		modelStack.Scale(20, 20, 20);

		for (int count = 0; count < 3; count++)
			RenderMesh(meshList[EXT_WALL + count], false);
	} modelStack.PopMatrix();
}

void MyScene::RenderBuildings()
{
	for (int xPos = -100, count = 0; count < 6; count++)
	{
		modelStack.PushMatrix(); {
			modelStack.Scale(10, 10, 10);
			modelStack.Translate(xPos, 0, 100);
			RenderMesh(meshList[Building1], false);
		} modelStack.PopMatrix();
		xPos += 10;
		modelStack.PushMatrix(); {
			modelStack.Scale(10, 10, 10);
			modelStack.Translate(xPos, 0, 100);
			RenderMesh(meshList[Building2], false);
		} modelStack.PopMatrix();
		xPos += 10;
		modelStack.PushMatrix(); {
			modelStack.Scale(10, 10, 10);
			modelStack.Translate(xPos, 0, 100);
			RenderMesh(meshList[Building3], false);
		} modelStack.PopMatrix();
		xPos += 10;
	}
}

void MyScene::RenderSkyBox()
{
	//Environment Front
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -2000);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[SKYBOX_FRONT], false);
	modelStack.PopMatrix();

	//Environment Back
	modelStack.PushMatrix();
	modelStack.Translate(0, 13.5, 2000);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[SKYBOX_BACK], false);
	modelStack.PopMatrix();

	//Environment Top
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 2000.05, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[SKYBOX_TOP], false);
	modelStack.PopMatrix();

	//Environment Left
	modelStack.PushMatrix();
	modelStack.Translate(-2000, 30, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[SKYBOX_LEFT], false);
	modelStack.PopMatrix();

	//Environment Right
	modelStack.PushMatrix();
	modelStack.Translate(2000, 13, 0);
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Scale(4000, 4000, 4000);
	RenderMesh(meshList[SKYBOX_RIGHT], false);
	modelStack.PopMatrix();

	//Environment Floor
	for (int i = 0; i <= 20; i++)
	{
		for (int a = 0; a < 20; a++)
		{
			modelStack.PushMatrix();
			modelStack.Rotate(90, 0, -1, 0);
			modelStack.Translate(i * 100 - 800, -1, a * 100 - 800);
			modelStack.Rotate(90, -1, 0, 0);
			modelStack.Scale(100, 100, 100);
			RenderMesh(meshList[SKYBOX_FLOOR], false);
			modelStack.PopMatrix();
		}
	}
}

void MyScene::RenderObjects()
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (!obj[i]->getTaken())
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj[i]->collisionBox.Centre.x, obj[i]->collisionBox.Centre.y, obj[i]->collisionBox.Centre.z);
			modelStack.Rotate(obj[i]->angle, obj[i]->rotation.x, obj[i]->rotation.y, obj[i]->rotation.z);
			modelStack.Scale(obj[i]->size.x, obj[i]->size.y, obj[i]->size.z);
			RenderMesh(obj[i]->mesh, false);
			modelStack.PopMatrix();
		}
	}
}
void MyScene::RenderDoor()
{
	modelStack.PushMatrix();
	modelStack.Translate(DoorL->collisionBox.Centre.x, DoorL->collisionBox.Centre.y, DoorL->collisionBox.Centre.z);
	modelStack.Rotate(DoorL->angle, DoorL->rotation.x, DoorL->rotation.y, DoorL->rotation.z);
	modelStack.Scale(DoorL->size.x, DoorL->size.y, DoorL->size.z);
	RenderMesh(DoorL->mesh, false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(DoorR->collisionBox.Centre.x, DoorR->collisionBox.Centre.y, DoorR->collisionBox.Centre.z);
	modelStack.Rotate(DoorR->angle, DoorR->rotation.x, DoorR->rotation.y, DoorR->rotation.z);
	modelStack.Scale(DoorR->size.x, DoorR->size.y, DoorR->size.z);
	RenderMesh(DoorR->mesh, false);
	modelStack.PopMatrix();

}
void MyScene::RenderCharacter(std::vector<Character*> characters)
{
	for (int count = 0; count < characters.size(); count++)
	{
		Character character(*characters[count]);
		modelStack.PushMatrix(); {
			modelStack.Translate(character.pos.x, character.pos.y, character.pos.z);
			modelStack.Rotate(character.angle, 0, 1, 0);
			modelStack.Scale(2, 2, 2);

			RenderMesh(character.mesh[0], false);
			RenderMesh(character.mesh[1], false);
			for (int count = -1; count < 2; count += 2)
			{
				modelStack.PushMatrix(); {
					modelStack.Translate(1.5 * count, 6.375, 0);
					modelStack.Translate(0.625 * count, 0.625, 0);

					RenderMesh(character.mesh[2], false);
				} modelStack.PopMatrix();

				modelStack.PushMatrix(); {
					modelStack.Translate(0.75 * count, 3, 0);

					RenderMesh(character.mesh[3], false);
				} modelStack.PopMatrix();
			}
		} modelStack.PopMatrix();
	}
}

void MyScene::RenderTargetDetails()
{
	Vector3 view = camera.target - camera.position;
	
	int targeted = MyScene::targeted(shelfItemsCollisionBox);
	if (targeted != -1)
	{
		Gettable* targetedObj = shelfItems[targeted];

		if (targetedObj->name.size() && !targetedObj->getTaken())
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Name:" + targetedObj->name, Color(1, 1, 0), 3, 1, 19);
			RenderTextOnScreen(meshList[GEO_TEXT], "Price:$" + to_price(targetedObj->getPrice()), Color(1, 1, 0), 3, 1, 18);
		}
	}

	targeted = MyScene::targeted(cashiersCollisionBox);
	if (targeted != -1)
	{
		if (checkoutprice) RenderTextOnScreen(meshList[GEO_TEXT], "Price:$" + to_price(checkoutprice), Color(1, 1, 0), 3, 1, 18);
		else RenderTextOnScreen(meshList[GEO_TEXT], "Click to check out", Color (1, 0, 1), 3, 1, 19);
	}
}

void MyScene::RenderCheckList()
{
	int count = 0;
	//CheckList Init
	RenderTextOnScreen(meshList[GEO_TEXT], "CHECKLIST:", Color(1, 0, 0), 2, 31, 17);
	for (int zPos = 16, i = 0; zPos > 6, i < checkList.size(); zPos--, i++)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], checkList[i], Color(0, 0, 0), 2, 31, zPos);
	}
	for (int zPos = 16, i = 0; i < checkList.size(); zPos--, i++)
	{
		for (int j = 0; j < inventory.size(); j++)
		{
			if (checkList[i] == inventory[j]->name)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "---------------------", Color(0, 0, 0), 2, 31, zPos);
				count++;
				break;
			}
		}
	}
	if (count == checkList.size())
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Complete", Color(0, 0, 0), 2, 31, 5);
	}


}

void MyScene::RenderInventory()
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();

	//Inventory
	modelStack.PushMatrix();
	modelStack.Translate(40.5, 5, 0);
	modelStack.Scale(6, 5, 1);
	RenderMesh(meshList[Inventory], false);
	for(int i = 0, xPos = -5; i < inventory.size(); i++, xPos++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(xPos + 0.45, -0.4, 0); //-4.6
		modelStack.Scale(0.8, 0.8, 0.8);
		RenderMesh(inventory[i]->mesh, false);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	if (inventory.size() >= 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(13, 5, 0);
		modelStack.Scale(6, 6, 2);
		RenderMesh(meshList[Selector], false);
		modelStack.PopMatrix();
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			modelStack.PushMatrix();
			modelStack.Translate(13, 5, 0);
			modelStack.Scale(6, 6, 2);
			RenderMesh(meshList[Selector], false);
			modelStack.PopMatrix();
		}
	}

	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

void MyScene::RenderRoad()
{
	for(int i = 5; i <= 40; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((i * 50) - 1200, 0.2, 650);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[road], false);
		modelStack.PopMatrix();
	}
}

void MyScene::RenderCar()
{
	for(int zPos = -100, count = 0; count < 1; count++)
	{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, zPos);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[Car2], false);
	modelStack.PopMatrix();
	
	zPos += 80;

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, zPos);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[Car3], false);
	modelStack.PopMatrix();

	zPos += 80;
	}
}

void MyScene::RenderPCar()
{
	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[Car], false);
	modelStack.PopMatrix();
}
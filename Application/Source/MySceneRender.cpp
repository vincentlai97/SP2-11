#include "MyScene.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Vertex.h"
#include "Utility.h"

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

	RenderSkyBox();
	RenderInterior();
	RenderExterior();

	modelStack.PushMatrix();
	modelStack.Translate(OpenDoorL, 0, 0);
	modelStack.Translate(38, -5, 297);
	modelStack.Scale(11.7, 7, 2);
	RenderMesh(meshList[GEO_DOOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(OpenDoorR, 0, 0);
	modelStack.Translate(107, -5, 297);
	modelStack.Scale(11.7, 7, 2);
	RenderMesh(meshList[GEO_DOOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-354, -2, 115);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5.5, 4, 2);
	RenderMesh(meshList[eDoor], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-354, 88, 115);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(5.5, 4, 2);
	RenderMesh(meshList[eDoor], false);
	modelStack.PopMatrix();

	RenderObjects();

	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:" + to_string(fps), Color(0, 0, 0), 2, 30, 29.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "X:" + to_string(camera.position.x), Color(0, 0, 0), 2, 1, 0.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y:" + to_string(camera.position.y), Color(0, 0, 0), 2, 1, 1.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z:" + to_string(camera.position.z), Color(0, 0, 0), 2, 1, 2.5);

	RenderTextOnScreen(meshList[GEO_TEXT], "TargetX:" + to_string(camera.target.x), Color(0, 0, 0), 2, 1, 3.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "TargetY:" + to_string(camera.target.y), Color(0, 0, 0), 2, 1, 4.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "TargetZ:" + to_string(camera.target.z), Color(0, 0, 0), 2, 1, 5.5);

	//Crosshair
	RenderTextOnScreen(meshList[GEO_TEXT], "+", Color(0, 1, 0), 5, 8.5f, 6.5f);

	//Object information when camera position is close to object
	for (int i = 0; i < obj.size(); i++)
	{
		if ((camera.target.x < obj[i].centre.x + 1.5f) && (camera.target.x > obj[i].centre.x - 1.5f) && (camera.target.y < obj[i].centre.y + 5) && (camera.target.y > obj[i].centre.y - 5) && (camera.target.z < obj[i].centre.z + 10) && (camera.target.z > obj[i].centre.z - 10))
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Name:" + obj[i].name, Color(1, 1, 0), 3, 1, 15);
			RenderTextOnScreen(meshList[GEO_TEXT], "Price:$" + to_price(obj[i].price), Color(1, 1, 0), 3, 1, 14);
			RenderTextOnScreen(meshList[GEO_TEXT], "ObjPosX:" + to_string(obj[i].centre.x), Color(1, 0, 0), 3, 1, 16);
			RenderTextOnScreen(meshList[GEO_TEXT], "ObjPosY:" + to_string(obj[i].centre.y), Color(1, 0, 0), 3, 1, 17);
			RenderTextOnScreen(meshList[GEO_TEXT], "ObjPosz:" + to_string(obj[i].centre.z), Color(1, 0, 0), 3, 1, 18);
		}
	}

	modelStack.PushMatrix();
	modelStack.Translate(-220, 0, 260);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(float(90) - 32.735, -1, 0, 0);
	modelStack.Scale(80, 166.43, 0);
	modelStack.Translate(0, 0.5, 0);
	RenderMesh(meshList[ESCALATOR], false);
	modelStack.PopMatrix();

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
	for(int i = 0; i <= 20; i++)
	{
		for(int a = 0; a < 20; a++)
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
		modelStack.PushMatrix();
		modelStack.Translate(obj[i].centre.x, obj[i].centre.y, obj[i].centre.z);
		modelStack.Scale(obj[i].size.x, obj[i].size.y, obj[i].size.z);
		modelStack.Rotate(obj[i].angle, obj[i].rotation.x, obj[i].rotation.y, obj[i].rotation.z);
		RenderMesh(obj[i].mesh, false);
		modelStack.PopMatrix();
	}
}
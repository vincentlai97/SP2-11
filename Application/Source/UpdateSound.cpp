#include "MyScene.h"
#include "Camera2.h"
#include "GL\glew.h"
#include "Application.h"
#include "Utility.h"

#include "shader.hpp"

void MyScene::UpdateSound(double dt)
{
	sound[BG_MUSIC];
	if(sound[BG_MUSIC])
	{
		sound[BG_MUSIC]->setMaxDistance(500.f);
		sound[BG_MUSIC]->setMinDistance(0.f);
	}

	sound[FOOTSTEPS]->setIsPaused(true);
	
	if(Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D'))
	{
		sound[FOOTSTEPS]->setIsPaused(false);
	}

	if(Application::IsKeyPressed(VK_SPACE) && soundJump == true)
	{
		sound[JUMP] = engine->play2D("../irrKlang/media/Jumping.mp3", false);
		soundJump = false;
	}

	if(!Application::IsKeyPressed(VK_SPACE))
	{
		soundJump = true;
	}

	/*if(Application::IsKeyPressed('T') && soundPaid == true && paid == true)
	{
		sound[PAID] = engine->play2D("../irrKlang/media/Coin.mp3", false);
		soundPaid = false;
	}

	if(!Application::IsKeyPressed('T') && paid == true)
	{
		soundPaid = true;
	}*/

	if((Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed(VK_DOWN)) && up_down == true)
	{
		sound[REACH] = engine->play2D("../irrKlang/media/DingDing.mp3", false);
		soundUpDown = false;
	}

	if((Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed(VK_DOWN)) && up_down == true)
	{
		soundUpDown = true;
	}

	//if(Application::IsKeyPressed(VK_UP) && cameraCollisionBox.checkCollision(elevatorUp) || Application::IsKeyPressed(VK_DOWN) && cameraCollisionBox.checkCollision(elevatorDown))
	//{
	//	sound[REACH]->setIsPaused(false);
	//	//sound[REACH]->setPlaybackSpeed(1.2f);
	//}

	float multMusic = 0.1f;
	Vector3 viewMusic = 0.0f;
	viewMusic = (camera.target + camera.position);
	engine->setListenerPosition(vec3df(multMusic * viewMusic.x, multMusic * viewMusic.y, multMusic * viewMusic.z), vec3df(1, 1, 1));
	engine->update();
}

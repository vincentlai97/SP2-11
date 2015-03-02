#include "MyScene.h"
#include "GL\glew.h"
#include "Application.h"
#include "Utility.h"

#include "shader.hpp"

int MyScene::InitSound()
{
	engine = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
	//engine->setDefault3DSoundMaxDistance(100.f);
	//engine->setDefault3DSoundMinDistance(0.0f);
	engine->setSoundVolume(1.0f);
	if(!engine)
	{
		cout << "Sound Engine is not working" << endl << endl;
		return 0;
	}

	if(engine)
	{
		cout << "Sound Engine is working" << endl << endl;
	}

	//Set up Background Music
	sound[BG_MUSIC] = engine->play3D("../irrKlang/media/MarketMusic.mp3", vec3df(10, 10, 10), true);
	
	//Set up Footsteps Music
	sound[FOOTSTEPS] = engine->play2D("../irrKlang/media/Footstep.mp3", true, true);
	sound[FOOTSTEPS]->setVolume(0.8f);

	//Set up Jumping Music
	sound[JUMP] = engine->play2D("../irrKlang/media/Jump.mp3", true, true);
	sound[JUMP]->setVolume(0.8f);

	//Set up lift level Music
	sound[REACH] = engine->play2D("../irrKlang/media/Bell.mp3", true, true);
	sound[REACH]->setVolume(0.8f);

	//Set up Opening of doors Music
	//sound[OPENDOOR] = engine->play2D("../irrKlang/media/doorOpen.mp3", true, true);
	
	
	return 0;
}
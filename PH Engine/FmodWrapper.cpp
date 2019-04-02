/*==============================================================================
3D Example
Copyright (c), Firelight Technologies Pty, Ltd 2004-2018.

This example shows how to basic 3D positioning of sounds.

Zachary Khamis Jan 21, 2019

==============================================================================*/
#pragma once
#include "FmodWrapper.h"
#include <iostream>
#include <Windows.h>
using namespace std;

void FmodErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		if (result != FMOD_OK)
		{
			cout << FMOD_ErrorString(result) << endl;
			system("pause");
			//exit(0);
		}
	}
}


bool SoundEngine::Init()
{
	if (!init)
	{
		//Create a System object and initialize.

		result = FMOD::System_Create(&system);
		FmodErrorCheck(result);

		if (result != FMOD_OK) return false;

		result = system->getVersion(&version);
		FmodErrorCheck(result);

		result = system->init(100, FMOD_INIT_3D_RIGHTHANDED, extradriverdata);
		//result = system->setAdvancedSettings();
		FmodErrorCheck(result);

		/*
			Set the distance units. (meters/feet etc).
		*/
		result = system->set3DSettings(1.0, 1.0f, 1.0f);

		FmodErrorCheck(result);

		//Got this far, it must have worked  
		init = true;
	}
	return true;
}

//cleans itself up after the scope
SoundEngine::~SoundEngine()
{
	if (init)
	{
		result = system->close();
		FmodErrorCheck(result);
		result = system->release();
		FmodErrorCheck(result);
		init = false;
	}
}

void SoundEngine::Update()
{
	//UPDATE THE LISTENER
	result = system->set3DListenerAttributes(0, &listener.pos, &listener.vel, &listener.foreward, &listener.up);
	FmodErrorCheck(result);

	result = system->update();
	FmodErrorCheck(result);
}

FMOD_RESULT Sound::result;
SoundEngine Sound::engine;

Sound::~Sound()
{


	result = sound->release();
	FmodErrorCheck(result);
}

bool Sound::Load(const char * fileName)
{
	if (!init)
	{
		engine.Init();

		result = engine.system->createSound(fileName, FMOD_3D, 0, &sound);
		FmodErrorCheck(result);
		if (result != FMOD_OK)return false;
		result = sound->set3DMinMaxDistance(5.0f, 30.0f);
		//engine.system->setAdvancedSettings(FMOD_INIT_3D_RIGHTHANDED);

		FmodErrorCheck(result);

		init = true;
	}
	return true;

}

FMOD::Channel* Sound::Play(bool loop)
{
	if (init)
	{
		engine.Init();
		result = engine.system->playSound(sound, 0, true, &channel);
		FmodErrorCheck(result);
		result = channel->set3DAttributes(&pos, &vel);
		FmodErrorCheck(result);

		//loops the sound
		if (loop)
		{
			channel->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			channel->setMode(FMOD_LOOP_OFF);
		}
		result = channel->setPaused(false);
		FmodErrorCheck(result);
	}
	return channel;
}

void Sound::switchMode()
{
	if (!switched) {
		channel->setMode(FMOD_3D_LINEARROLLOFF);

		switched = true;
	}
	else if (switched) {
		channel->setMode(FMOD_3D_INVERSEROLLOFF);
		switched = false;
	}

}

void Sound::SetPosition(FMOD::Channel * thisChannel, FMOD_VECTOR newPos, FMOD_VECTOR newVel)
{

	result = thisChannel->set3DAttributes(&newPos, &newVel);
	FmodErrorCheck(result);


}

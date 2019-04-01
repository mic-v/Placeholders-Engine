/*==============================================================================
3D Example
Copyright (c), Firelight Technologies Pty, Ltd 2004-2018.

This example shows how to basic 3D positioning of sounds.

Zachary Khamis Jan 21, 2019

==============================================================================*/
#pragma once
//adds library
#pragma comment(lib,"../External/FMOD/lib/fmod_vc.lib")

#include "fmod.hpp"
#include "fmod_errors.h"

void FmodErrorCheck(FMOD_RESULT result);

struct Listener
{
	FMOD_VECTOR pos = { 0.0f,0.0f,0.0f };
	FMOD_VECTOR vel = { 0.0f,0.0f,0.0f };
	FMOD_VECTOR foreward{ 0.0f,0.0f,1.0f };
	FMOD_VECTOR up = { 0.0f,1.0f,0.0f };
};

class SoundEngine
{
private:
	unsigned int     version;
	void            *extradriverdata = 0;
	FMOD_RESULT      result;
	bool init = false;


public:
	~SoundEngine();
	void Update();
	bool Init();

	Listener listener;
	FMOD::System *system;
};

class Sound
{
private:
	FMOD::Channel   *channel = 0; //what plays the sound
	//chanel1->
	bool init = false;
	static FMOD_RESULT result;
	bool switched = false;

public:
	~Sound();
	bool Load(const char* fileName);
	FMOD::Channel* Play(bool loop);
	void switchMode();
	static void SetPosition(FMOD::Channel* thisChannel, FMOD_VECTOR newPos, FMOD_VECTOR newVel = { 0.0f,0.0f,0.0f });

	FMOD::Sound   *sound;	//is just a sound
	//sound1->

	FMOD_VECTOR pos = { 0.0f , 0.0f, 3.0f };
	FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
	static SoundEngine engine;
};
#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <thread>				//Used for multithreading
#include <chrono>				//Used for clock access
#include <string>
#include "minisdl_audio.h"
#include <fstream>

// These variables and functions are need in Sound c++, so they are added to Sound C++ files scopes.
class Play
{
public:
	Play();
	void playNote();
	void stopNote();
	int start_Sound();
};

float volumeAssigner();
extern bool getData;
extern int sector;
extern int playedSounds[2][20];
extern int notes[13];
extern int counterStart;
extern int recvArray[3];
#endif